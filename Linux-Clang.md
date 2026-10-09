# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 15, 2026)
#### Using the following commits:
----
| Jsonifier: [3b56371](https://github.com/nihilai-collective/jsonifier/commit/3b56371)  
| Glaze: [5520fb0](https://github.com/stephenberry/glaze/commit/5520fb0)  
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

`simdjson (ondemand)` results include this harness's field-mapping layer (per-field lookups, string copies and `unescaped_key()` for maps, in `include/common.hpp`), since materializing into the shared test structs is what these tests measure; hand-tuned glue written by a simdjson specialist could perform differently.

`Results.csv` additionally carries `jsonifier (combined)` and `simdjson (combined)` summary rows. Each is a best-of-variants tally: per test, only the better-ranked of that library's two variants counts, and a test counts as a win when that position is 1 and no other library shares it, so two variants of the same library tying for first count as one win. These rows are not independent results and should not be summed with the per-variant rows.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ae63a25](https://github.com/nihilai-collective/benchmarksuite/commit/ae63a25).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1897.56 | 0.576428 | 765.199ms | 905 | 30 | 206.213 | 454.833 | 0.182882 | 2.8944 | 13.9138 | 2.51271 | 0.00110497 | 3.68324e-05 | 0 | 1(Win) | true |
| glaze | 1563.39 | 0.0570527 | 775.249ms | 905 | 4890 | 485.09 | 552.053 | 0.594944 | 3.51078 | 17.589 | 2.29171 | 0.00110814 | 0.000126315 | 1.46878e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 337.449 | 0.0413451 | 975.397ms | 905 | 2560 | 2862.66 | 2557.65 | 0.165311 | 15.2591 | 46.8055 | 6.81658 | 0.0113493 | 0.000140711 | 2.37396e-05 | 3(Loss) | true |
| simdjson (ondemand) | 226.931 | 0.057272 | 1101.51ms | 905 | 40 | 189.782 | 3803.25 | 0.0144592 | 22.5228 | 90.9072 | 10.6895 | 0.0302486 | 0.000138122 | 0 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2019.93 | 0.443382 | 760.644ms | 905 | 640 | 2296.99 | 427.28 | 0.11141 | 2.73853 | 13.2829 | 2.39227 | 0.00110497 | 0.000177831 | 8.11464e-05 | 1(Win) | true |
| glaze | 1659.04 | 0.14313 | 770.702ms | 905 | 80 | 44.3538 | 520.225 | 0.167914 | 3.34493 | 16.9249 | 2.17127 | 0.00110497 | 0 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 335.688 | 0.0933899 | 971.274ms | 905 | 30 | 172.961 | 2571.07 | 0.0466515 | 15.3583 | 46.1878 | 6.69613 | 0.0143646 | 0 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 232.047 | 0.0231541 | 1093.96ms | 905 | 4890 | 3626.7 | 3719.4 | 0.0541634 | 22.2336 | 90.2928 | 10.5691 | 0.0249317 | 0.000130834 | 1.60436e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2363.64 | 0.0701431 | 757.327ms | 905 | 4890 | 320.786 | 365.147 | 0.0382905 | 2.39581 | 8.82572 | 0.919398 | 0.00337005 | 5.21981e-05 | 4.97125e-06 | 1(Win) | true |
| glaze | 189.789 | 0.0251085 | 1179.28ms | 905 | 4890 | 6375.35 | 4547.55 | 0.0880775 | 27.1219 | 112.29 | 22.8729 | 0.0680564 | 0.000264832 | 6.37223e-05 | 2(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5110.59 | 0.0734342 | 735.422ms | 905 | 640 | 9.84309 | 168.88 | 0.209584 | 1.24582 | 5.35249 | 0.272928 | 0.00220822 | 2.58978e-05 | 0 | 1(Win) | true |
| glaze | 429.037 | 0.0647538 | 931.111ms | 905 | 1280 | 2171.94 | 2011.65 | 0.0585307 | 12.1489 | 24.5017 | 3.14918 | 0.00114814 | 0.000186464 | 1.64019e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1325.46 | 0.0591468 | 850.326ms | 1811 | 2560 | 1520.57 | 1303.02 | 0.00734523 | 4.00264 | 19.2203 | 4.15185 | 0.000865587 | 7.09639e-05 | 5.82379e-06 | 1(Win) | true |
| glaze | 995.37 | 0.0657537 | 894.456ms | 1811 | 640 | 833.083 | 1735.14 | 0.152598 | 5.28797 | 26.4837 | 4.27002 | 0.00148744 | 7.1611e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 414.335 | 0.204497 | 1141.73ms | 1811 | 80 | 5812.97 | 4168.38 | 0.108438 | 12.5364 | 34.8272 | 6.201 | 0.00279542 | 0.000220872 | 0.000124241 | 3(Loss) | true |
| simdjson (ondemand) | 258.548 | 0.0204884 | 1389.99ms | 1811 | 4890 | 9159.62 | 6680 | 0.200717 | 19.8877 | 69.672 | 9.56765 | 0.0018685 | 9.73374e-05 | 1.9874e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1449.96 | 0.0528496 | 834.194ms | 1811 | 2560 | 1014.5 | 1191.14 | 0.0412053 | 3.66442 | 18.1452 | 3.90834 | 0.000828056 | 0.000116907 | 2.30794e-05 | 1(Win) | true |
| glaze | 1078.07 | 0.154399 | 876.841ms | 1811 | 30 | 183.551 | 1602.03 | 0.0916342 | 5.01417 | 25.4859 | 4.04583 | 0.00250322 | 0.000128842 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 425.635 | 0.0812443 | 1133.77ms | 1811 | 160 | 1738.87 | 4057.71 | 0.00215634 | 12.2237 | 33.7405 | 5.95859 | 0.000552181 | 0.000148399 | 9.66317e-05 | 3(Loss) | true |
| simdjson (ondemand) | 263.302 | 0.0245586 | 1379.75ms | 1811 | 2560 | 6643.17 | 6559.41 | 0.0080329 | 19.6595 | 68.5947 | 9.32413 | 0.00164813 | 0.000125319 | 4.44333e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 340.512 | 0.0490652 | 1230.9ms | 1811 | 1280 | 7927.39 | 5072.08 | 0.015339 | 15.0595 | 64.032 | 11.4914 | 0.0171957 | 8.80039e-05 | 2.71777e-05 | 1(Win) | true |
| glaze | 306.139 | 0.0351701 | 1287.2ms | 1798 | 2560 | 9934.11 | 5601.07 | 0.0585552 | 16.8417 | 70.8409 | 12.1763 | 0.022336 | 0.000220514 | 0.000122097 | 2(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 866.4 | 0.102733 | 923.656ms | 1811 | 640 | 2684.11 | 1993.43 | 0.096396 | 5.96375 | 20.6025 | 1.69354 | 0.000554769 | 6.12576e-05 | 1.72557e-06 | 1(Win) | true |
| glaze | 705.503 | 0.0929779 | 979.463ms | 1798 | 320 | 1634.15 | 2430.47 | 0.148081 | 7.42308 | 27.3231 | 2.17242 | 0.000802976 | 0.000119925 | 2.08565e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3052.51 | 0.0847455 | 840.524ms | 3862 | 1280 | 1338.3 | 1206.58 | 0.136224 | 1.74065 | 8.80606 | 1.10513 | 0.000261563 | 5.70462e-05 | 1.71948e-05 | 1(Win) | true |
| glaze | 1791.55 | 0.0518645 | 925.693ms | 3862 | 2560 | 2910.36 | 2055.81 | 0.00361006 | 2.91284 | 14.0352 | 1.73045 | 0.000262372 | 4.90557e-05 | 1.14295e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 959.243 | 0.0315099 | 1104.63ms | 3862 | 2560 | 3747.15 | 3839.58 | 0.0220511 | 5.42677 | 15.5495 | 2.11678 | 0.000266924 | 5.42141e-05 | 1.98246e-05 | 3(Loss) | true |
| simdjson (ondemand) | 582.502 | 0.0375162 | 1362.36ms | 3862 | 4890 | 27515.4 | 6322.88 | 0.0275657 | 8.90912 | 27.717 | 3.60565 | 0.0136108 | 0.000113687 | 3.73309e-05 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3384.07 | 0.0245666 | 825.502ms | 3862 | 4890 | 349.577 | 1088.36 | 0.094202 | 1.57727 | 8.31072 | 0.996893 | 0.000259516 | 8.03275e-05 | 2.65287e-05 | 1(Win) | true |
| glaze | 1848.3 | 0.0401709 | 917.235ms | 3862 | 640 | 410.093 | 1992.69 | 0.204158 | 2.8093 | 13.5342 | 1.62118 | 0.0002913 | 3.3985e-05 | 2.83208e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 986.928 | 0.138771 | 1094.42ms | 3862 | 40 | 1072.78 | 3731.88 | 0.214157 | 5.27593 | 15.0611 | 2.00958 | 0.000517866 | 3.884e-05 | 6.47333e-06 | 3(Loss) | true |
| simdjson (ondemand) | 585.761 | 0.0681497 | 1343.68ms | 3862 | 160 | 2937.87 | 6287.71 | 0.0430218 | 8.84777 | 27.2266 | 3.4956 | 0.0179667 | 2.75117e-05 | 3.23666e-06 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 932.877 | 0.0228924 | 1116.37ms | 3862 | 4890 | 3994.53 | 3948.1 | 0.00938143 | 5.58717 | 26.2022 | 5.48162 | 0.00629054 | 3.35183e-05 | 5.82467e-07 | 1(Win) | true |
| glaze | 774.931 | 0.0438196 | 1198.53ms | 3862 | 80 | 346.997 | 4752.8 | 0.0163088 | 6.70656 | 28.7685 | 5.60849 | 0.00687468 | 0.00028159 | 0.000110047 | 2(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5091.16 | 0.0517977 | 808.321ms | 3862 | 2560 | 359.461 | 723.428 | 0.0272216 | 1.06941 | 5.69161 | 0.787416 | 0.000271374 | 4.59202e-05 | 1.71948e-06 | 1(Win) | true |
| glaze | 2611.4 | 0.0934681 | 888.349ms | 3862 | 80 | 139.025 | 1410.39 | 0.0982805 | 2.03107 | 8.50388 | 0.951321 | 0.00432095 | 4.20766e-05 | 1.61833e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1759.4 | 0.067293 | 1241.22ms | 9578 | 640 | 7811.57 | 5191.7 | 0.00370196 | 2.94959 | 14.2247 | 2.70505 | 0.00190068 | 1.25613e-05 | 8.15671e-07 | 1(Win) | true |
| glaze | 1426.18 | 0.0320566 | 1359.92ms | 9578 | 1280 | 5395.67 | 6404.72 | 0.0654606 | 3.63315 | 17.5231 | 3.48131 | 0.00156226 | 1.53346e-05 | 5.7097e-07 | 2(Loss) | true |
| jsonifier (two-stage) | 1163.41 | 0.015121 | 1508.68ms | 9578 | 4890 | 6892.11 | 7851.31 | 0.00577748 | 4.44813 | 18.4946 | 3.26196 | 0.00154297 | 1.96428e-05 | 2.54076e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1149.39 | 0.0298753 | 1518.1ms | 9578 | 2560 | 14430.4 | 7947.08 | 0.022591 | 4.4995 | 17.6365 | 3.00439 | 0.00351779 | 4.88995e-05 | 2.27164e-05 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2734.94 | 0.0585716 | 1188.69ms | 9578 | 1280 | 4898.21 | 3339.85 | 0.121105 | 1.90528 | 9.9502 | 1.76481 | 0.000890305 | 1.19904e-05 | 4.07836e-07 | 1(Win) | true |
| glaze | 2024.08 | 0.034506 | 1316.66ms | 9578 | 2560 | 6207.63 | 4512.82 | 0.0451634 | 2.56632 | 13.1551 | 2.49948 | 0.000419744 | 1.75777e-05 | 3.67052e-07 | 2(Loss) | true |
| jsonifier (two-stage) | 1531.63 | 0.0252343 | 1453.01ms | 9578 | 2560 | 5797.79 | 5963.75 | 0.0594568 | 3.38512 | 14.2825 | 2.34162 | 0.00040131 | 1.59464e-05 | 1.30507e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1473.42 | 0.0329258 | 1480.43ms | 9578 | 4890 | 20373.9 | 6199.37 | 0.010146 | 3.50971 | 13.4394 | 2.0758 | 0.00290893 | 1.76358e-05 | 2.19914e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4388.81 | 0.0734725 | 927.759ms | 9578 | 1280 | 2993.06 | 2081.27 | 0.00123874 | 1.19658 | 5.23857 | 1.08426 | 0.00147286 | 2.16969e-05 | 4.56776e-06 | 1(Win) | true |
| glaze | 2014.04 | 0.0198029 | 1171.51ms | 9578 | 4890 | 3944.37 | 4535.3 | 0.366662 | 2.58025 | 12.6472 | 2.59115 | 0.000928337 | 2.2696e-05 | 7.23796e-06 | 2(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12062.4 | 0.134228 | 813.573ms | 9578 | 320 | 330.61 | 757.253 | 0.0656585 | 0.450294 | 2.07538 | 0.299123 | 0.000882883 | 1.95761e-05 | 3.26269e-06 | 1(Win) | true |
| glaze | 5567.05 | 0.0772266 | 904.144ms | 9578 | 640 | 1027.57 | 1640.78 | 0.0532615 | 0.948006 | 4.37941 | 0.710483 | 0.000297231 | 1.9413e-05 | 4.56776e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3382.12 | 0.0441108 | 823.686ms | 3873 | 640 | 148.521 | 1092.09 | 0.0220286 | 1.58047 | 8.4046 | 1.03537 | 0.000517202 | 2.66266e-05 | 0 | 1(Win) | true |
| glaze | 1967.03 | 0.0508326 | 901.666ms | 3873 | 1280 | 1166.18 | 1877.74 | 0.0167699 | 2.6722 | 13.1064 | 1.62897 | 0.000259812 | 4.23606e-05 | 2.82404e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 963.634 | 0.0362177 | 1098.86ms | 3873 | 2560 | 4933.47 | 3832.97 | 0.046552 | 5.40301 | 15.3073 | 2.04674 | 0.000943128 | 6.80795e-05 | 2.43069e-05 | 3(Loss) | true |
| simdjson (ondemand) | 566.429 | 0.0247028 | 1373.8ms | 3873 | 1280 | 3321.3 | 6520.82 | 0.0343852 | 9.14643 | 27.2301 | 3.65841 | 0.0138315 | 8.04851e-05 | 3.28799e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3783.12 | 0.0184904 | 810.102ms | 3873 | 2560 | 83.4309 | 976.332 | 0.0731637 | 1.41688 | 7.95895 | 0.938807 | 0.000322445 | 4.90172e-05 | 1.1397e-05 | 1(Win) | true |
| glaze | 2050.34 | 0.0260683 | 891.309ms | 3873 | 4890 | 1078.4 | 1801.45 | 0.00372688 | 2.56741 | 12.63 | 1.52672 | 0.000323143 | 4.62538e-05 | 5.86093e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 989.822 | 0.0377584 | 1087.35ms | 3873 | 1280 | 2541.08 | 3731.56 | 0.0242174 | 5.25065 | 14.8706 | 1.95249 | 0.000766525 | 4.07468e-05 | 3.42919e-06 | 3(Loss) | true |
| simdjson (ondemand) | 574.222 | 0.0131744 | 1362.58ms | 3873 | 4890 | 3511.63 | 6432.32 | 0.0425797 | 9.02372 | 26.802 | 3.55952 | 0.0161142 | 7.04896e-05 | 2.6559e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 903.994 | 0.0265562 | 1131.31ms | 3873 | 4890 | 5757.09 | 4085.85 | 0.0280731 | 5.74297 | 25.693 | 5.34573 | 0.00912579 | 5.50716e-05 | 1.70548e-05 | 1(Win) | true |
| glaze | 877.308 | 0.021983 | 1143.02ms | 3873 | 4890 | 4188.65 | 4210.13 | 0.0197661 | 5.92538 | 29.2907 | 5.76814 | 0.00579583 | 0.000108823 | 6.52623e-05 | 2(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5231.14 | 0.26936 | 808.446ms | 3873 | 40 | 144.687 | 706.075 | 0.00354057 | 1.04107 | 5.49522 | 0.764782 | 0.000651949 | 9.03692e-05 | 3.22747e-05 | 1(Win) | true |
| glaze | 2534.28 | 0.0795595 | 893.841ms | 3873 | 2560 | 3441.99 | 1457.45 | 0.221056 | 2.08797 | 8.46424 | 0.946037 | 0.00393873 | 7.30216e-05 | 2.74335e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1027.48 | 0.113595 | 6080.84ms | 2090234 | 40 | 1.94276e+08 | 1.94009e+06 | 0.222036 | 4.98966 | 25.1987 | 5.22865 | 0.0161571 | 0.0681541 | 0.000320766 | 1(Win) | true |
| jsonifier (two-stage) | 900.672 | 0.0832774 | 6923.81ms | 2090234 | 160 | 5.43539e+08 | 2.21324e+06 | 0.10627 | 5.65908 | 27.692 | 5.53801 | 0.0198466 | 0.107912 | 0.000147026 | 2(Loss) | true |
| glaze | 853.92 | 0.103344 | 7283.89ms | 2090234 | 80 | 4.65605e+08 | 2.33441e+06 | 0.0874877 | 5.98381 | 30.0319 | 5.97971 | 0.0187028 | 0.0666688 | 0.000264073 | 3(Loss) | true |
| simdjson (ondemand) | 667.655 | 0.124938 | 9345.54ms | 2090234 | 80 | 1.11317e+09 | 2.98568e+06 | 0.135021 | 7.70084 | 31.2719 | 5.64401 | 0.0256788 | 0.113519 | 0.000674584 | 4(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1255.07 | 0.157808 | 6085.2ms | 2090234 | 30 | 1.88468e+08 | 1.58829e+06 | 0.0849252 | 4.07184 | 19.8866 | 3.93822 | 0.0156423 | 0.0436384 | 0.000151068 | 1(Win) | true |
| jsonifier (two-stage) | 1076.94 | 0.0715152 | 6891.16ms | 2090234 | 160 | 2.80364e+08 | 1.85099e+06 | 0.0749814 | 4.72871 | 22.4239 | 4.2638 | 0.0190347 | 0.0824742 | 0.000214817 | 2(Loss) | true |
| glaze | 1018.08 | 0.135723 | 7278.93ms | 2090234 | 40 | 2.82484e+08 | 1.958e+06 | 0.1684 | 5.03506 | 24.6752 | 4.68503 | 0.0178071 | 0.0419233 | 0.000232079 | 3(Loss) | true |
| simdjson (ondemand) | 765.934 | 0.139442 | 9241.82ms | 2090234 | 80 | 1.05363e+09 | 2.60258e+06 | 0.446086 | 6.6297 | 25.9516 | 4.35977 | 0.0215986 | 0.080447 | 0.000109479 | 4(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1617.79 | 0.133695 | 7824.63ms | 2090234 | 80 | 2.17104e+08 | 1.23218e+06 | 0.230226 | 3.13526 | 7.88068 | 0.405689 | 0.000227146 | 0.0504865 | 1.31265e-05 | 1(Win) | true |
| glaze | 963.904 | 0.137337 | 6426.39ms | 2090234 | 30 | 2.42002e+08 | 2.06805e+06 | 0.0657282 | 5.24339 | 9.34203 | 0.53407 | 0.000239463 | 0.0699286 | 0.000380851 | 2(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1612.27 | 0.135782 | 7805.35ms | 2090234 | 80 | 2.25471e+08 | 1.2364e+06 | 0.252207 | 3.13644 | 7.88051 | 0.405653 | 0.00022473 | 0.0504494 | 6.2194e-06 | 1(Win) | true |
| glaze | 1006.97 | 0.117142 | 6177.29ms | 2090234 | 40 | 2.15103e+08 | 1.97961e+06 | 0.111913 | 5.07669 | 9.33804 | 0.533131 | 0.000232354 | 0.0436828 | 2.00934e-05 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2709.09 | 0.0946144 | 7279.47ms | 6661897 | 160 | 7.87743e+08 | 2.34517e+06 | 0.0458649 | 1.85963 | 9.57902 | 1.77961 | 0.00593327 | 0.0566333 | 0.000278274 | 1(Win) | true |
| jsonifier | 2687.37 | 0.0948976 | 7339.13ms | 6661897 | 80 | 4.02661e+08 | 2.36412e+06 | 0.150832 | 1.89245 | 9.9967 | 2.13073 | 0.00512409 | 0.0341969 | 5.71252e-05 | 2(Loss) | true |
| glaze | 2056.21 | 0.0904818 | 9532.24ms | 6661897 | 30 | 2.3448e+08 | 3.0898e+06 | 0.235015 | 2.46468 | 12.3605 | 2.44199 | 0.00665466 | 0.0357287 | 1.3985e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1999.29 | 0.179855 | 9951.39ms | 6661897 | 30 | 9.79961e+08 | 3.17776e+06 | 1.07269 | 2.56519 | 10.6579 | 1.81032 | 0.00733117 | 0.0582954 | 0.000303077 | 4(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3219.48 | 0.0963219 | 7390.8ms | 6661897 | 30 | 1.08391e+08 | 1.97339e+06 | 0.589712 | 1.59348 | 8.34824 | 1.73184 | 0.00491616 | 0.025973 | 2.24611e-05 | 1(Win) | true |
| jsonifier (two-stage) | 3203.02 | 0.163421 | 7318.91ms | 6661897 | 30 | 3.15219e+08 | 1.98353e+06 | 0.202147 | 1.57313 | 7.93151 | 1.38081 | 0.0057318 | 0.0484457 | 7.61795e-05 | 2(Loss) | true |
| glaze | 2391.26 | 0.0618866 | 9472.52ms | 6661897 | 160 | 4.32569e+08 | 2.65687e+06 | 0.343619 | 2.14785 | 10.7039 | 2.04276 | 0.00635899 | 0.0269141 | 0.000163454 | 3(Loss) | true |
| simdjson (ondemand) | 2286.87 | 0.162086 | 9832.69ms | 6661897 | 80 | 1.62216e+09 | 2.77816e+06 | 0.0146303 | 2.23442 | 8.98999 | 1.40787 | 0.00602441 | 0.0468489 | 0.000184977 | 4(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4679.94 | 0.0256455 | 8609.98ms | 6661897 | 40 | 4.84839e+06 | 1.35755e+06 | 0.0231607 | 1.07943 | 2.56177 | 0.127289 | 6.82276e-05 | 0.0278574 | 1.8238e-05 | 1(Win) | true |
| glaze | 3299.72 | 0.149176 | 6035.03ms | 6661897 | 80 | 6.59981e+08 | 1.9254e+06 | 0.23621 | 1.53867 | 4.23031 | 0.469317 | 7.61607e-05 | 0.063552 | 0.00123469 | 2(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4679.91 | 0.0155919 | 8617ms | 6661897 | 40 | 1.79216e+06 | 1.35756e+06 | 0.0431193 | 1.07925 | 2.56171 | 0.127277 | 6.79724e-05 | 0.0278322 | 4.32534e-05 | 1(Win) | true |
| glaze | 3916.34 | 0.200428 | 5089.88ms | 6661897 | 30 | 3.17156e+08 | 1.62225e+06 | 0.0115875 | 1.30541 | 4.22889 | 0.468987 | 8.15033e-05 | 0.0247974 | 2.12052e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2480.27 | 0.0404602 | 5127.11ms | 500299 | 1280 | 7.75402e+06 | 192367 | 0.0522988 | 2.06346 | 9.04531 | 1.72847 | 0.0109149 | 0.0118792 | 1.18273e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1856.66 | 0.0850493 | 6797.81ms | 500299 | 80 | 3.82143e+06 | 256979 | 0.0970393 | 2.77281 | 12.4502 | 2.15156 | 0.0136956 | 0.0402849 | 1.40166e-05 | 2(Loss) | true |
| glaze | 1831.14 | 0.0386287 | 6848.14ms | 500299 | 1280 | 1.29672e+07 | 260560 | 0.0814111 | 2.78233 | 12.4419 | 2.3514 | 0.0141758 | 0.00666449 | 4.71983e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1247.39 | 0.0738318 | 9942.94ms | 500299 | 1280 | 1.02082e+08 | 382495 | 0.208431 | 4.10841 | 14.7542 | 2.41235 | 0.0162816 | 0.0337335 | 9.35238e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3054.15 | 0.0565271 | 9887.96ms | 500299 | 640 | 4.99082e+06 | 156221 | 0.221397 | 1.66007 | 7.89165 | 1.45101 | 0.00824168 | 0.00531945 | 2.72025e-06 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2197.98 | 0.0335599 | 6587.6ms | 500299 | 640 | 3.39653e+06 | 217074 | 0.0200626 | 2.34082 | 11.2938 | 1.87381 | 0.0103704 | 0.0295421 | 6.98332e-06 | 2(Tie) | true |
| glaze STATISTICAL TIE | 2192.23 | 0.18301 | 6662.24ms | 500299 | 40 | 6.34591e+06 | 217642 | 0.227756 | 2.3231 | 11.2942 | 2.07629 | 0.00990068 | 0.00314272 | 1.40416e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1448.88 | 0.0756776 | 9386.58ms | 500299 | 1280 | 7.94947e+07 | 329304 | 0.0717778 | 3.5432 | 13.5785 | 2.12564 | 0.00843086 | 0.0158633 | 2.87016e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10388.6 | 0.0187337 | 5356.58ms | 500299 | 4890 | 361992 | 45927.4 | 0.363151 | 0.49211 | 2.16041 | 0.353109 | 0.00242394 | 0.00510682 | 2.69696e-06 | 1(Win) | true |
| glaze | 5662.57 | 0.12368 | 9213.2ms | 500299 | 640 | 6.95039e+06 | 84259 | 0.0111944 | 0.898948 | 3.64366 | 0.51536 | 0.00150928 | 0.0205265 | 1.52378e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10451.7 | 0.0290932 | 5320.75ms | 500299 | 1280 | 225775 | 45650 | 0.048385 | 0.490856 | 2.15935 | 0.352871 | 0.00241875 | 0.00503516 | 6.41804e-07 | 1(Win) | true |
| glaze | 6667.72 | 0.0545113 | 7936.55ms | 500299 | 4890 | 7.44023e+06 | 71557 | 0.200236 | 0.762711 | 3.63048 | 0.512286 | 0.00142724 | 0.000986303 | 1.45598e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4435.9 | 0.108788 | 8163.89ms | 1439562 | 80 | 9.06875e+06 | 309492 | 0.204924 | 1.14657 | 5.28384 | 0.791855 | 0.00464879 | 0.0539499 | 3.54709e-05 | 1(Win) | true |
| jsonifier | 3880.39 | 0.0381164 | 9214.41ms | 1439562 | 160 | 2.90974e+06 | 353798 | 0.0247183 | 1.30256 | 5.72284 | 1.19503 | 0.00364638 | 0.0218511 | 3.72726e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3089.81 | 0.244279 | 5789.07ms | 1439562 | 80 | 9.42452e+07 | 444323 | 0.260915 | 1.63622 | 5.98872 | 0.878847 | 0.00559735 | 0.049496 | 3.97777e-05 | 3(Loss) | true |
| glaze | 3046.69 | 0.0579969 | 5839.22ms | 1439562 | 320 | 2.18558e+07 | 450612 | 0.0584831 | 1.67679 | 7.46764 | 1.44421 | 0.00633584 | 0.0179246 | 3.30721e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5135.16 | 0.0512213 | 7938.74ms | 1439562 | 640 | 1.20014e+07 | 267347 | 0.169182 | 0.984097 | 4.88141 | 0.695189 | 0.0034968 | 0.0461615 | 1.60986e-05 | 1(Win) | true |
| jsonifier | 4358.43 | 0.0739582 | 9099.91ms | 1439562 | 320 | 1.7367e+07 | 314993 | 0.199992 | 1.15608 | 5.32384 | 1.09903 | 0.00281814 | 0.0157309 | 1.86016e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3532.21 | 0.149165 | 5539.94ms | 1439562 | 80 | 2.68903e+07 | 388673 | 0.534207 | 1.43001 | 5.58259 | 0.779873 | 0.00321235 | 0.0381184 | 1.00551e-05 | 3(Loss) | true |
| glaze | 3373.47 | 0.080037 | 5781.13ms | 1439562 | 160 | 1.6975e+07 | 406962 | 0.0253682 | 1.51292 | 7.0683 | 1.34848 | 0.00479686 | 0.0132384 | 3.63175e-05 | 4(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17904.7 | 0.0566801 | 8541.54ms | 1439562 | 80 | 151105 | 76676.7 | 0.0451612 | 0.282384 | 0.872306 | 0.124264 | 0.000607841 | 0.0174298 | 4.45448e-06 | 1(Win) | true |
| glaze | 5819.23 | 0.233205 | 6266.72ms | 1439584 | 30 | 9.08112e+06 | 235924 | 0.175778 | 0.864662 | 2.78636 | 0.504926 | 0.000931125 | 0.0601496 | 1.25499e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17931.3 | 0.107419 | 8510.65ms | 1439562 | 1280 | 8.65793e+06 | 76563 | 0.071801 | 0.281908 | 0.871917 | 0.124177 | 0.000586634 | 0.0173459 | 2.80196e-06 | 1(Win) | true |
| glaze | 7849.44 | 0.27119 | 9339.48ms | 1439584 | 160 | 3.59967e+07 | 174903 | 0.0316024 | 0.638592 | 2.78084 | 0.503639 | 0.000930438 | 0.0155771 | 8.67872e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2290.58 | 0.0173712 | 3093.85ms | 56369 | 4890 | 81275.1 | 23469 | 0.190199 | 2.21582 | 9.38101 | 1.84325 | 0.00294976 | 4.28523e-05 | 2.86347e-05 | 1(Win) | true |
| glaze | 1950.55 | 0.0304627 | 3499.31ms | 56369 | 4890 | 344677 | 27560.3 | 0.338196 | 2.60405 | 11.6512 | 2.30941 | 0.00619758 | 6.2479e-05 | 4.23698e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1786.86 | 0.220556 | 3778.94ms | 56369 | 80 | 352233 | 30085 | 0.234886 | 2.83102 | 12.2301 | 2.17825 | 0.00650601 | 2.94932e-05 | 2.12883e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1453.47 | 0.0995696 | 4557.8ms | 56369 | 640 | 867967 | 36985.8 | 0.0207006 | 3.4807 | 14.2872 | 2.35333 | 0.0083393 | 0.000149961 | 0.000101729 | 4(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3166.34 | 0.053991 | 2809.62ms | 56369 | 320 | 26888 | 16977.9 | 0.0396445 | 1.59976 | 7.19524 | 1.35464 | 0.00376698 | 8.14943e-06 | 3.54805e-06 | 1(Win) | true |
| glaze | 2940.02 | 0.0597303 | 2937.95ms | 56369 | 2560 | 305358 | 18284.8 | 0.0406295 | 1.72955 | 9.14373 | 1.74876 | 0.0027733 | 1.60771e-05 | 9.14732e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2432.66 | 0.0229858 | 3337.99ms | 56369 | 2560 | 66050.9 | 22098.3 | 0.0138796 | 2.08186 | 10.0494 | 1.69105 | 0.0036776 | 2.28267e-05 | 1.44278e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1892.27 | 0.232011 | 4049.14ms | 56369 | 40 | 173777 | 28409.1 | 0.618362 | 2.64753 | 11.8668 | 1.81811 | 0.00648273 | 5.80993e-05 | 4.30201e-05 | 4(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13903.1 | 0.148615 | 1143.17ms | 56369 | 2560 | 84533.1 | 3866.6 | 0.166143 | 0.364638 | 1.48635 | 0.250457 | 0.0001768 | 1.24112e-05 | 6.18137e-06 | 1(Win) | true |
| glaze | 5919.47 | 0.134978 | 1658.05ms | 56369 | 2560 | 384661 | 9081.5 | 0.141327 | 0.855379 | 3.1055 | 0.486775 | 0.000140806 | 3.43371e-05 | 2.06438e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14268.4 | 0.0575147 | 1130.96ms | 56369 | 1280 | 6010.35 | 3767.61 | 0.0452664 | 0.358142 | 1.47668 | 0.248293 | 0.000181644 | 8.63451e-06 | 4.50436e-06 | 1(Win) | true |
| glaze | 6087.61 | 0.138499 | 1635.69ms | 56369 | 2560 | 382933 | 8830.67 | 0.112121 | 0.834641 | 3.02993 | 0.469833 | 0.000139122 | 8.86319e-06 | 3.7005e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2844.33 | 0.0236193 | 3912.1ms | 94370 | 4890 | 273118 | 31641.3 | 0.0930673 | 1.77886 | 7.94241 | 1.32429 | 0.00332397 | 7.16797e-05 | 5.68835e-05 | 1(Win) | true |
| glaze | 2465.23 | 0.0758877 | 4441.94ms | 94370 | 320 | 245611 | 36507.1 | 0.0290356 | 2.05225 | 9.45979 | 1.92792 | 0.00534045 | 1.38418e-05 | 8.04678e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2389.57 | 0.0148424 | 4516.63ms | 94370 | 4890 | 152807 | 37662.9 | 0.118856 | 2.1247 | 9.06651 | 1.43008 | 0.00336131 | 4.36692e-05 | 2.9781e-05 | 3(Loss) | true |
| jsonifier | 2115.34 | 0.110588 | 4975.79ms | 94370 | 320 | 708390 | 42545.5 | 0.0334456 | 2.38803 | 8.47431 | 1.82438 | 0.00528137 | 2.2882e-05 | 1.59942e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3809.71 | 0.0179559 | 3464.78ms | 94370 | 4890 | 87985 | 23623.4 | 0.081336 | 1.32833 | 6.64036 | 1.03339 | 0.00173002 | 1.5689e-05 | 1.06334e-05 | 1(Win) | true |
| glaze | 3323.94 | 0.286904 | 3798.81ms | 94370 | 30 | 181033 | 27075.8 | 0.0773736 | 1.52252 | 7.96997 | 1.59524 | 0.00282258 | 8.12405e-06 | 1.41288e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3137.15 | 0.0618973 | 3993.27ms | 94370 | 320 | 100900 | 28687.9 | 0.1262 | 1.62166 | 7.62045 | 1.11076 | 0.00234128 | 8.24547e-06 | 4.20552e-06 | 3(Loss) | true |
| jsonifier | 2602.08 | 0.0177189 | 4560.11ms | 94370 | 2560 | 96147.7 | 34587.1 | 0.0472485 | 1.94736 | 7.17825 | 1.53465 | 0.0039139 | 2.23025e-05 | 1.62674e-05 | 4(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17624.2 | 0.0787443 | 1246.17ms | 94370 | 40 | 646.769 | 5106.52 | 0.0236569 | 0.289389 | 0.980629 | 0.156639 | 0.000117622 | 3.97372e-06 | 1.58949e-06 | 1(Win) | true |
| glaze | 5031 | 0.0576883 | 2539.38ms | 94370 | 2560 | 272631 | 17888.7 | 0.0111899 | 1.00449 | 3.42178 | 0.637343 | 0.00147859 | 1.8424e-05 | 1.17432e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17959.8 | 0.0341953 | 1247.58ms | 94370 | 2560 | 7516.9 | 5011.09 | 0.15654 | 0.286803 | 0.975006 | 0.155379 | 0.000101007 | 3.93233e-06 | 1.95375e-06 | 1(Win) | true |
| glaze | 5721.49 | 0.0822114 | 2317.86ms | 94370 | 640 | 107027 | 15729.9 | 0.107425 | 0.887689 | 3.36923 | 0.625209 | 0.00144153 | 6.49041e-06 | 3.46045e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2664.04 | 0.0428484 | 1156.7ms | 11812 | 4890 | 16052.5 | 4228.46 | 0.0974369 | 1.92156 | 9.35392 | 1.62496 | 0.00303158 | 8.55253e-05 | 4.71428e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1969.81 | 0.090182 | 1307.05ms | 11812 | 80 | 2127.78 | 5718.71 | 0.327017 | 2.58594 | 12.7329 | 2.1352 | 0.00441077 | 3.80969e-05 | 1.79902e-05 | 2(Loss) | true |
| glaze | 1823.47 | 0.0466124 | 1358.17ms | 11812 | 2560 | 21227.3 | 6177.69 | 0.0472433 | 2.80536 | 13.7083 | 2.69527 | 0.00249445 | 8.32707e-05 | 4.59014e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1377.93 | 0.0214935 | 1561.13ms | 11812 | 4890 | 15097.8 | 8175.15 | 0.0448948 | 3.69182 | 16.5564 | 2.87459 | 0.00305968 | 7.13115e-05 | 3.90577e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3119.72 | 0.041928 | 1141.47ms | 11812 | 4890 | 11208.1 | 3610.84 | 0.129896 | 1.64886 | 8.42973 | 1.4095 | 0.00209566 | 2.59692e-05 | 1.03704e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2195.82 | 0.0269775 | 1296.55ms | 11812 | 4890 | 9366.23 | 5130.1 | 0.0295427 | 2.32253 | 11.8085 | 1.91974 | 0.00352253 | 5.05015e-05 | 2.8168e-05 | 2(Loss) | true |
| glaze | 2077.48 | 0.0720228 | 1326.15ms | 11812 | 1280 | 19521.9 | 5422.33 | 0.0469049 | 2.45248 | 12.5167 | 2.4288 | 0.00126374 | 2.74483e-05 | 8.73053e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1495.18 | 0.0592749 | 1548.01ms | 11812 | 640 | 12763.8 | 7534.06 | 0.0745638 | 3.40583 | 15.7 | 2.68414 | 0.00199532 | 2.71175e-05 | 1.19053e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11118.3 | 0.167931 | 831.388ms | 11812 | 80 | 231.589 | 1013.17 | 0.108688 | 0.473707 | 2.08043 | 0.340163 | 0.000169319 | 2.11649e-05 | 0 | 1(Win) | true |
| glaze | 4018.86 | 0.0780324 | 1017.73ms | 11812 | 4890 | 23393.8 | 2802.99 | 0.225817 | 1.27882 | 5.23298 | 0.806722 | 0.000379081 | 5.0363e-05 | 2.34589e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11895.1 | 0.0813746 | 821.088ms | 11812 | 160 | 95.0187 | 947.013 | 0.0725441 | 0.444534 | 2.03327 | 0.329241 | 9.68295e-05 | 6.8786e-06 | 0 | 1(Win) | true |
| glaze | 4469.58 | 0.126215 | 985.556ms | 11812 | 4890 | 49481.6 | 2520.33 | 0.375374 | 1.15029 | 4.9647 | 0.74763 | 0.000424441 | 3.76554e-05 | 1.70531e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4307.86 | 0.034577 | 1429.74ms | 31235 | 2560 | 14634.4 | 6914.81 | 0.0615148 | 1.17905 | 5.75006 | 0.855867 | 0.0020374 | 2.58249e-05 | 1.45445e-05 | 1(Win) | true |
| jsonifier | 3674.37 | 0.0827888 | 1552.34ms | 31235 | 160 | 7207.45 | 8106.98 | 0.00362355 | 1.38279 | 6.12563 | 1.22801 | 0.00346486 | 2.46118e-05 | 9.20442e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3243.56 | 0.0712504 | 1673.4ms | 31235 | 640 | 27402.7 | 9183.73 | 0.0688852 | 1.57095 | 7.06792 | 1.12599 | 0.00139407 | 1.63078e-05 | 7.7037e-06 | 3(Loss) | true |
| glaze | 2711.96 | 0.0288222 | 1838.76ms | 31235 | 2560 | 25657.4 | 10984 | 0.127857 | 1.87228 | 8.22885 | 1.63041 | 0.00581608 | 2.72131e-05 | 1.4632e-05 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4643.74 | 0.0315887 | 1433.41ms | 31235 | 4890 | 20077.9 | 6414.66 | 0.014442 | 1.09974 | 5.43349 | 0.781527 | 0.00193791 | 1.28847e-05 | 6.14119e-06 | 1(Win) | true |
| jsonifier | 3941.82 | 0.0910323 | 1542.62ms | 31235 | 80 | 3785.92 | 7556.93 | 0.197441 | 1.29008 | 5.80903 | 1.15371 | 0.00344926 | 1.16056e-05 | 4.00192e-07 | 2(Loss) | true |
| simdjson (ondemand) | 3459.14 | 0.0696445 | 1656.98ms | 31235 | 4890 | 175886 | 8611.4 | 0.0448699 | 1.47209 | 6.73616 | 1.05251 | 0.000909446 | 3.26177e-05 | 1.93009e-05 | 3(Loss) | true |
| glaze | 2884.01 | 0.146581 | 1818.72ms | 31235 | 30 | 6876.51 | 10328.7 | 0.280307 | 1.76035 | 7.82305 | 1.54032 | 0.00560482 | 1.06718e-05 | 7.47025e-06 | 4(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18597.1 | 0.107944 | 900.646ms | 31235 | 640 | 1913.24 | 1601.76 | 0.0438779 | 0.279089 | 0.912598 | 0.128574 | 3.3366e-05 | 9.45454e-06 | 4.00192e-06 | 1(Win) | true |
| glaze | 5013.6 | 0.0417179 | 1345.52ms | 31235 | 4890 | 30042.6 | 5941.44 | 0.105954 | 1.01428 | 3.62936 | 0.650777 | 0.00226222 | 1.92681e-05 | 9.67663e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19338.6 | 0.0745503 | 879.858ms | 31235 | 80 | 105.492 | 1540.34 | 0.0721723 | 0.268659 | 0.893613 | 0.12422 | 3.20154e-05 | 1.20058e-05 | 5.2025e-06 | 1(Win) | true |
| glaze | 5543.04 | 0.0446915 | 1280.66ms | 31235 | 2560 | 14766.5 | 5373.95 | 0.0432092 | 0.917998 | 3.51404 | 0.625004 | 0.00219856 | 9.27945e-06 | 2.76383e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2711.5 | 0.0238426 | 4539.13ms | 108313 | 640 | 52799.4 | 38095.3 | 0.0610725 | 1.86545 | 8.33845 | 1.68084 | 0.00263522 | 1.12665e-05 | 6.8234e-06 | 1(Win) | true |
| glaze | 2431.79 | 0.0500646 | 4998.67ms | 108313 | 1280 | 578870 | 42477.1 | 0.107285 | 2.09199 | 10.038 | 1.80511 | 0.00239436 | 5.58855e-05 | 3.83942e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1982.09 | 0.0423654 | 5960.58ms | 108313 | 320 | 155986 | 52114.4 | 0.0175365 | 2.5516 | 11.5491 | 2.0157 | 0.00276502 | 1.02135e-05 | 6.83782e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1730.6 | 0.016813 | 6713.82ms | 108313 | 2560 | 257811 | 59687.6 | 0.0775416 | 2.91705 | 14.1945 | 2.02199 | 0.00280266 | 2.37881e-05 | 1.57854e-05 | 4(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3284.99 | 0.0527375 | 4095.04ms | 108313 | 320 | 88000.1 | 31444.7 | 0.155395 | 1.54447 | 7.53282 | 1.49704 | 0.0021559 | 9.40561e-06 | 5.19328e-06 | 1(Win) | true |
| glaze | 2747.07 | 0.106908 | 4703.3ms | 108313 | 320 | 517118 | 37601.9 | 0.0190363 | 1.8414 | 9.30506 | 1.63885 | 0.0021735 | 6.57816e-06 | 2.01961e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2262.23 | 0.0160041 | 5515.94ms | 108313 | 2560 | 136707 | 45660.7 | 0.0447625 | 2.23753 | 10.743 | 1.8322 | 0.00242842 | 2.35321e-05 | 1.60234e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1911.11 | 0.0288132 | 6352.12ms | 108313 | 1280 | 310444 | 54049.9 | 0.15659 | 2.64346 | 13.4839 | 1.86414 | 0.00229901 | 1.32284e-05 | 7.047e-06 | 4(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18143.9 | 0.0245648 | 1310.11ms | 108313 | 4890 | 9563.93 | 5693.11 | 0.00252234 | 0.279887 | 1.23758 | 0.32046 | 0.000191443 | 4.14991e-06 | 2.05041e-06 | 1(Win) | true |
| glaze | 5051.99 | 0.252363 | 2806.78ms | 108313 | 2560 | 6.81598e+06 | 20446.5 | 0.105162 | 1.00309 | 2.7376 | 0.384719 | 0.000273419 | 1.01666e-05 | 6.33292e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18297.3 | 0.0398572 | 1304.68ms | 108313 | 640 | 3240.26 | 5645.37 | 0.0025464 | 0.27835 | 1.23253 | 0.319343 | 0.000191776 | 3.46219e-06 | 1.52913e-06 | 1(Win) | true |
| glaze | 6390.86 | 0.122883 | 2354.61ms | 108313 | 2560 | 1.00987e+06 | 16163 | 0.215102 | 0.796656 | 2.69244 | 0.374221 | 0.00026269 | 3.37563e-06 | 1.47864e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3483.25 | 0.0126362 | 6613.13ms | 213963 | 4890 | 267949 | 58580.6 | 0.0144263 | 1.4539 | 6.6935 | 1.07535 | 0.00154854 | 1.34878e-05 | 9.54143e-06 | 1(Win) | true |
| simdjson (ondemand) | 3130.64 | 0.171882 | 7235.44ms | 213963 | 320 | 4.01625e+06 | 65178.7 | 0.00751244 | 1.61499 | 7.80958 | 1.05123 | 0.00145333 | 2.81445e-05 | 1.50727e-05 | 2(Loss) | true |
| glaze | 3031.87 | 0.0180242 | 7463.27ms | 213963 | 4890 | 719577 | 67302.1 | 0.0363274 | 1.66801 | 7.93387 | 1.46002 | 0.00266832 | 2.98936e-05 | 2.33379e-05 | 3(Loss) | true |
| jsonifier | 2856.51 | 0.0111974 | 7897.1ms | 213963 | 4890 | 312859 | 71433.7 | 0.203331 | 1.77147 | 6.84427 | 1.51046 | 0.00184935 | 9.04634e-06 | 6.07199e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3896.8 | 0.0711362 | 6173.03ms | 213963 | 80 | 111002 | 52363.7 | 0.0521148 | 1.29737 | 6.28448 | 0.982226 | 0.00138015 | 4.84897e-06 | 1.57738e-06 | 1(Win) | true |
| simdjson (ondemand) | 3436.35 | 0.0231023 | 6891.51ms | 213963 | 1280 | 240881 | 59380.2 | 0.161286 | 1.47474 | 7.46635 | 0.974599 | 0.00125212 | 1.83954e-05 | 1.44702e-05 | 2(Loss) | true |
| glaze | 3335.19 | 0.0257331 | 7054.93ms | 213963 | 1280 | 317271 | 61181.1 | 0.0335622 | 1.51455 | 7.56426 | 1.37629 | 0.0023272 | 7.71527e-06 | 4.64449e-06 | 3(Loss) | true |
| jsonifier | 3152.66 | 0.0136164 | 7420.44ms | 213963 | 4890 | 379799 | 64723.4 | 0.14851 | 1.6029 | 6.43455 | 1.41705 | 0.00160188 | 8.54361e-06 | 5.09138e-06 | 4(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22643.9 | 0.0279106 | 1637.97ms | 213963 | 2560 | 16194 | 9011.3 | 0.0128468 | 0.22461 | 0.729949 | 0.163715 | 8.50578e-05 | 2.57054e-06 | 1.28527e-06 | 1(Win) | true |
| glaze | 5724.02 | 0.0673351 | 4318.38ms | 213963 | 2560 | 1.47502e+06 | 35648.2 | 0.0269831 | 0.880077 | 3.04102 | 0.571146 | 0.000664263 | 1.83315e-05 | 1.27048e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22634.4 | 0.0704466 | 1635.03ms | 213963 | 40 | 1613.32 | 9015.1 | 0.00665594 | 0.224475 | 0.727383 | 0.163145 | 8.99688e-05 | 1.34369e-05 | 1.05158e-05 | 1(Win) | true |
| glaze | 6863.57 | 0.0315478 | 3729.72ms | 213963 | 4890 | 430155 | 29729.6 | 0.332321 | 0.741217 | 3.01408 | 0.564888 | 0.000664189 | 9.52327e-06 | 7.07746e-06 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 859.008 | 0.0835621 | 6343ms | 1834197 | 160 | 4.63273e+08 | 2.03633e+06 | 0.269785 | 5.87434 | 26.3894 | 5.71761 | 0.0292728 | 0.0817494 | 0.000437266 | 1(Win) | true |
| jsonifier (two-stage) | 749.552 | 0.0691256 | 7292.29ms | 1834197 | 160 | 4.16376e+08 | 2.33369e+06 | 0.0712685 | 6.70098 | 30.5108 | 6.31043 | 0.0347052 | 0.145356 | 0.000924553 | 2(Loss) | true |
| glaze | 720.405 | 0.081376 | 7573.27ms | 1834197 | 160 | 6.2467e+08 | 2.42811e+06 | 0.210037 | 7.02863 | 30.8943 | 6.449 | 0.0344169 | 0.0810929 | 0.00125263 | 3(Loss) | true |
| simdjson (ondemand) | 615.045 | 0.0905885 | 8854.2ms | 1834197 | 160 | 1.06205e+09 | 2.84406e+06 | 0.236133 | 8.2179 | 34.9111 | 6.13733 | 0.0445167 | 0.146783 | 0.00102872 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 956.459 | 0.123101 | 6352.71ms | 1834197 | 30 | 1.52057e+08 | 1.82886e+06 | 0.0446562 | 5.28497 | 23.3775 | 5.01151 | 0.0289206 | 0.0553796 | 0.00024712 | 1(Win) | true |
| jsonifier (two-stage) | 821.654 | 0.0730398 | 7284.84ms | 1834197 | 160 | 3.8686e+08 | 2.12891e+06 | 0.0670205 | 6.14108 | 27.5001 | 5.60431 | 0.0339558 | 0.119174 | 0.00153025 | 2(Loss) | true |
| glaze | 790.412 | 0.0781918 | 7550.28ms | 1834197 | 80 | 2.39551e+08 | 2.21306e+06 | 0.0586643 | 6.39529 | 27.8769 | 5.74246 | 0.033089 | 0.0575109 | 0.000458566 | 3(Loss) | true |
| simdjson (ondemand) | 669.548 | 0.0950208 | 8795.76ms | 1834197 | 80 | 4.93011e+08 | 2.61255e+06 | 0.340765 | 7.5288 | 31.8884 | 5.43166 | 0.0400279 | 0.118122 | 0.000780328 | 4(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 843.259 | 0.13976 | 6450.66ms | 1834197 | 30 | 2.52149e+08 | 2.07436e+06 | 0.123886 | 5.974 | 12.5149 | 0.907941 | 0.00193035 | 0.0593139 | 0.000538619 | 1(Win) | true |
| glaze | 615.691 | 0.115835 | 8804.82ms | 1833577 | 160 | 1.7317e+09 | 2.84012e+06 | 0.0574987 | 8.24677 | 15.5348 | 0.9499 | 0.00138737 | 0.0490445 | 0.00171774 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 847.324 | 0.0862195 | 6430.71ms | 1834197 | 160 | 5.06902e+08 | 2.06441e+06 | 0.166349 | 5.97615 | 12.5147 | 0.907901 | 0.00164089 | 0.0591051 | 0.000713183 | 1(Win) | true |
| glaze | 618.602 | 0.104118 | 8817.03ms | 1833577 | 80 | 6.92978e+08 | 2.82675e+06 | 0.566734 | 8.28134 | 15.534 | 0.94973 | 0.00112745 | 0.048968 | 0.000483249 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3528.41 | 0.0769454 | 8355.73ms | 9930848 | 160 | 6.82493e+08 | 2.68415e+06 | 0.086579 | 1.42114 | 7.00757 | 1.5666 | 0.00483647 | 0.0295133 | 0.000540418 | 1(Win) | true |
| jsonifier (two-stage) | 3485.9 | 0.0920412 | 8469.06ms | 9930848 | 160 | 1.00052e+09 | 2.71689e+06 | 0.0575378 | 1.43962 | 6.66696 | 1.20709 | 0.00677605 | 0.0540502 | 0.00103106 | 2(Loss) | true |
| simdjson (ondemand) | 2871.74 | 0.186851 | 10253.9ms | 9930848 | 80 | 3.03784e+09 | 3.29793e+06 | 0.0275278 | 1.75669 | 7.48952 | 1.17945 | 0.00781352 | 0.0533885 | 0.0010341 | 3(Loss) | true |
| glaze | 2748.84 | 0.213273 | 5185.52ms | 9930848 | 40 | 2.15976e+09 | 3.44538e+06 | 0.0091198 | 1.84779 | 8.55404 | 1.7604 | 0.00756645 | 0.0288325 | 0.00364294 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3845.54 | 0.0994649 | 8342.76ms | 9930848 | 160 | 9.60103e+08 | 2.4628e+06 | 0.492117 | 1.30761 | 6.45214 | 1.43637 | 0.0047911 | 0.0247487 | 0.000609146 | 1(Win) | true |
| jsonifier (two-stage) | 3797.82 | 0.167606 | 8452.36ms | 9930848 | 160 | 2.79512e+09 | 2.49374e+06 | 0.0285668 | 1.33204 | 6.11087 | 1.07665 | 0.00659914 | 0.0492469 | 0.000737316 | 2(Loss) | true |
| simdjson (ondemand) | 3127.04 | 0.166345 | 10100.9ms | 9930848 | 80 | 2.03056e+09 | 3.02868e+06 | 0.193441 | 1.61739 | 6.93095 | 1.04917 | 0.00692698 | 0.0478241 | 0.000971999 | 3(Loss) | true |
| glaze | 2952.1 | 0.171706 | 5175.87ms | 9930848 | 30 | 9.10346e+08 | 3.20816e+06 | 0.199328 | 1.72707 | 7.99721 | 1.63012 | 0.00734705 | 0.0244512 | 0.00257536 | 4(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6158.28 | 0.070815 | 9834.1ms | 9930848 | 320 | 3.79537e+08 | 1.5379e+06 | 0.314249 | 0.819598 | 2.44785 | 0.163898 | 0.000276921 | 0.0248665 | 0.00112297 | 1(Win) | true |
| glaze | 3698.95 | 0.392702 | 7951.37ms | 9930228 | 40 | 4.04339e+09 | 2.56024e+06 | 0.0813016 | 1.37924 | 4.13205 | 0.480833 | 0.000998638 | 0.0416711 | 0.0023852 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6173.04 | 0.0782043 | 9761.49ms | 9930848 | 40 | 5.75833e+07 | 1.53422e+06 | 0.109453 | 0.817852 | 2.44781 | 0.163891 | 0.000284545 | 0.0248618 | 0.000574795 | 1(Win) | true |
| glaze | 4066.74 | 0.173778 | 7247.83ms | 9930228 | 80 | 1.3101e+09 | 2.3287e+06 | 0.00526663 | 1.24693 | 4.13176 | 0.480769 | 0.000999492 | 0.0223825 | 0.000427494 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 874.227 | 0.112542 | 6238.86ms | 1834197 | 160 | 8.11316e+08 | 2.00088e+06 | 0.0289566 | 5.76408 | 26.0041 | 5.60287 | 0.030369 | 0.0826458 | 0.00018563 | 1(Win) | true |
| jsonifier (two-stage) | 754.552 | 0.254406 | 7230.44ms | 1834197 | 40 | 1.39133e+09 | 2.31823e+06 | 0.00585358 | 6.67282 | 30.134 | 6.20633 | 0.0353236 | 0.146441 | 0.000248597 | 2(Loss) | true |
| glaze | 721.104 | 0.129549 | 7553.88ms | 1834197 | 80 | 7.90048e+08 | 2.42576e+06 | 0.0873064 | 7.07439 | 30.8621 | 6.43835 | 0.0345504 | 0.0827211 | 0.000245496 | 3(Loss) | true |
| simdjson (ondemand) | 614.78 | 0.265961 | 8880.01ms | 1834197 | 160 | 9.16234e+09 | 2.84529e+06 | 0.0284989 | 8.29395 | 34.9013 | 6.13077 | 0.0447075 | 0.147314 | 0.00274685 | 4(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 980.263 | 0.204842 | 6259.45ms | 1834197 | 160 | 2.1378e+09 | 1.78445e+06 | 0.100614 | 5.16909 | 23.0233 | 4.90795 | 0.0294763 | 0.0562441 | 6.40369e-05 | 1(Win) | true |
| jsonifier (two-stage) | 841.372 | 0.163565 | 7276.51ms | 1834197 | 30 | 3.46911e+08 | 2.07902e+06 | 0.223228 | 6.00785 | 27.1553 | 5.51203 | 0.0343429 | 0.119967 | 0.000115073 | 2(Loss) | true |
| glaze | 791.238 | 0.0709746 | 7588.34ms | 1834197 | 160 | 3.93916e+08 | 2.21075e+06 | 0.132988 | 6.43646 | 27.8797 | 5.74306 | 0.033472 | 0.0590144 | 0.000364983 | 3(Loss) | true |
| simdjson (ondemand) | 677.169 | 0.222248 | 8727.58ms | 1834197 | 160 | 5.27344e+09 | 2.58315e+06 | 0.303849 | 7.4935 | 31.9106 | 5.43541 | 0.0397096 | 0.118379 | 0.000572107 | 4(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 891.116 | 0.132779 | 6099.92ms | 1834197 | 80 | 5.43463e+08 | 1.96296e+06 | 0.0291564 | 5.70603 | 12.5231 | 0.907978 | 0.00131354 | 0.0599003 | 0.000436233 | 1(Win) | true |
| glaze | 602.478 | 0.473386 | 8954.17ms | 1833577 | 30 | 5.6633e+09 | 2.90241e+06 | 0.0279827 | 8.41649 | 15.5344 | 0.950102 | 0.00176 | 0.07609 | 0.000557471 | 2(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 893.242 | 0.0877984 | 6124.49ms | 1834197 | 160 | 4.72985e+08 | 1.95829e+06 | 0.491176 | 5.70939 | 12.5229 | 0.907938 | 0.00131603 | 0.0600529 | 0.000443627 | 1(Win) | true |
| glaze | 630.87 | 0.172773 | 8653.9ms | 1833577 | 160 | 3.66938e+09 | 2.77178e+06 | 0.255916 | 8.13359 | 15.5335 | 0.949903 | 0.0018834 | 0.0488314 | 0.00156213 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3542.99 | 0.587293 | 8356.16ms | 9930848 | 30 | 7.39374e+09 | 2.67311e+06 | 0.778904 | 1.42119 | 6.59729 | 1.18774 | 0.0068507 | 0.0543315 | 0.00124615 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3536.62 | 0.108287 | 8298.76ms | 9930848 | 80 | 6.72725e+08 | 2.67792e+06 | 0.0430088 | 1.42111 | 6.91004 | 1.54736 | 0.00494522 | 0.0298432 | 0.00291029 | 1(Tie) | true |
| simdjson (ondemand) | 2882.63 | 0.492964 | 10256.7ms | 9930848 | 40 | 1.04927e+10 | 3.28547e+06 | 0.0517532 | 1.75072 | 7.48772 | 1.17838 | 0.00779698 | 0.0534808 | 0.000994233 | 3(Loss) | true |
| glaze | 2726.56 | 0.116434 | 5228.7ms | 9930848 | 80 | 1.30856e+09 | 3.47354e+06 | 0.0298612 | 1.86001 | 8.54911 | 1.75847 | 0.00761221 | 0.0290259 | 0.00273181 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3857.65 | 0.485097 | 8404.07ms | 9930848 | 80 | 1.13468e+10 | 2.45507e+06 | 0.0170119 | 1.31242 | 6.04725 | 1.05957 | 0.00671297 | 0.0494007 | 0.000687771 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3822.65 | 0.599396 | 8383.22ms | 9930848 | 160 | 3.52851e+10 | 2.47755e+06 | 0.420061 | 1.31895 | 6.3596 | 1.41905 | 0.00480481 | 0.0248884 | 0.00046261 | 1(Tie) | true |
| simdjson (ondemand) | 3150.57 | 0.624427 | 10068.6ms | 9930848 | 40 | 1.40934e+10 | 3.00606e+06 | 0.150505 | 1.61549 | 6.93523 | 1.04994 | 0.00689235 | 0.0479085 | 0.0010064 | 3(Loss) | true |
| glaze | 2934.19 | 0.0992445 | 5253.43ms | 9930848 | 40 | 4.10457e+08 | 3.22773e+06 | 0.147898 | 1.72826 | 7.99779 | 1.62991 | 0.00739682 | 0.0246623 | 0.0010937 | 4(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6215.91 | 0.100796 | 9655.77ms | 9930848 | 80 | 1.88686e+08 | 1.52364e+06 | 0.292416 | 0.818551 | 2.44617 | 0.163898 | 0.000353945 | 0.0248613 | 0.000381409 | 1(Win) | true |
| glaze | 3075.51 | 0.414796 | 9735.26ms | 9930228 | 80 | 1.3051e+10 | 3.07923e+06 | 0.447502 | 1.65878 | 4.16785 | 0.480858 | 0.0010287 | 0.0756343 | 0.0144124 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6272.65 | 0.0375714 | 9610.32ms | 9930848 | 320 | 1.02976e+08 | 1.50985e+06 | 0.0367647 | 0.817561 | 2.44613 | 0.163891 | 0.000363309 | 0.024853 | 0.00031897 | 1(Win) | true |
| glaze | 4111.82 | 0.2944 | 7137.22ms | 9930228 | 160 | 7.35608e+09 | 2.30317e+06 | 0.0238864 | 1.24418 | 4.16747 | 0.480771 | 0.00102254 | 0.0222894 | 0.00056207 | 2(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1475.21 | 0.104776 | 5395.71ms | 642697 | 320 | 6.06433e+07 | 415482 | 0.265051 | 3.43448 | 17.3838 | 3.44076 | 0.00865267 | 0.0260192 | 3.17607e-05 | 1(Win) | true |
| jsonifier | 1455.63 | 0.0664885 | 5454.73ms | 642697 | 320 | 2.50814e+07 | 421070 | 0.066002 | 3.50994 | 18.4362 | 3.61852 | 0.00957451 | 0.0194319 | 0.000129031 | 2(Loss) | true |
| jsonifier (two-stage) | 1207.19 | 0.0387161 | 6554.41ms | 642697 | 640 | 2.47299e+07 | 507727 | 0.0394933 | 4.20027 | 21.4635 | 3.9833 | 0.0102246 | 0.0516444 | 2.11195e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1168.54 | 0.067515 | 6782.52ms | 642697 | 640 | 8.02616e+07 | 524522 | 0.14813 | 4.35755 | 21.8834 | 3.45389 | 0.0108871 | 0.0704564 | 5.87223e-05 | 4(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1668.44 | 0.0505226 | 5122.48ms | 642697 | 640 | 2.20467e+07 | 367364 | 0.0789936 | 3.06264 | 16.1579 | 3.16854 | 0.00786908 | 0.00335342 | 3.15565e-05 | 1(Win) | true |
| jsonifier | 1541.25 | 0.171262 | 5468.22ms | 642697 | 30 | 1.39158e+07 | 397680 | 0.121636 | 3.29357 | 17.3143 | 3.36294 | 0.00923136 | 0.0166537 | 4.97902e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1296.39 | 0.0751249 | 6448.53ms | 642697 | 160 | 2.0185e+07 | 472792 | 0.0220494 | 3.91911 | 20.6231 | 3.17267 | 0.00936516 | 0.031821 | 2.33002e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1274.87 | 0.0602904 | 6546.59ms | 642697 | 320 | 2.68859e+07 | 480772 | 0.0817514 | 3.98939 | 20.3415 | 3.7277 | 0.00992296 | 0.0460114 | 2.00522e-05 | 4(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1287.92 | 0.0463274 | 6129.58ms | 642697 | 320 | 1.55546e+07 | 475901 | 0.16742 | 3.97885 | 7.70341 | 0.792762 | 6.26705e-05 | 0.00572542 | 6.05651e-05 | 1(Win) | true |
| glaze | 1038.03 | 0.0303163 | 7614.87ms | 642692 | 320 | 1.02539e+07 | 590464 | 0.218075 | 4.95227 | 10.1803 | 0.702824 | 0.000145817 | 0.0424591 | 3.57675e-05 | 2(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1294.9 | 0.0391283 | 6128.2ms | 642697 | 80 | 2.74419e+06 | 473338 | 0.100227 | 3.97808 | 7.70255 | 0.792569 | 6.3074e-05 | 0.00546737 | 7.55605e-05 | 1(Win) | true |
| glaze | 1076.35 | 0.0189911 | 7357.06ms | 642692 | 40 | 467794 | 569439 | 0.33078 | 4.78329 | 10.1783 | 0.702395 | 0.000146299 | 0.00353809 | 4.97906e-06 | 2(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze STATISTICAL TIE | 2279.11 | 0.0998374 | 6610.88ms | 1225964 | 80 | 2.09847e+07 | 512995 | 0.133609 | 2.22486 | 12.2 | 2.54149 | 0.00473631 | 0.0292539 | 2.55921e-05 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2277.51 | 0.0764824 | 6638.3ms | 1225964 | 640 | 9.86592e+07 | 513354 | 0.052263 | 2.2264 | 12.027 | 2.13045 | 0.00459696 | 0.0572806 | 1.09123e-05 | 1(Tie) | true |
| simdjson (ondemand) | 2151.11 | 0.0580332 | 7019.28ms | 1225964 | 320 | 3.1837e+07 | 543519 | 0.0478363 | 2.37563 | 12.1078 | 1.8334 | 0.00442847 | 0.0613293 | 3.98513e-05 | 3(Loss) | true |
| jsonifier | 2025.33 | 0.127759 | 7457.17ms | 1225964 | 80 | 4.35145e+07 | 577274 | 0.236277 | 2.50182 | 13.0979 | 2.69713 | 0.0049825 | 0.0241342 | 3.28109e-05 | 4(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 2529.98 | 0.0929611 | 6327.91ms | 1225964 | 160 | 2.95286e+07 | 462126 | 0.0695741 | 2.00809 | 11.5566 | 2.39858 | 0.00438957 | 0.0107086 | 1.05784e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2397.91 | 0.0796011 | 6636.38ms | 1225964 | 640 | 9.64068e+07 | 487579 | 0.223142 | 2.11652 | 11.4389 | 1.99653 | 0.00435991 | 0.0528624 | 5.66391e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2364.97 | 0.0512265 | 6699.51ms | 1225964 | 640 | 4.10463e+07 | 494371 | 0.0999154 | 2.14582 | 11.4471 | 1.68597 | 0.00382982 | 0.0354754 | 1.80967e-05 | 3(Loss) | true |
| jsonifier | 2118.64 | 0.0878849 | 7457.94ms | 1225964 | 160 | 3.76349e+07 | 551850 | 0.0278732 | 2.40456 | 12.5097 | 2.56318 | 0.00480549 | 0.0216947 | 9.54351e-06 | 4(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4103.13 | 0.135222 | 7448.33ms | 1225964 | 40 | 5.93854e+06 | 284946 | 0.000807176 | 1.23556 | 4.12011 | 0.402579 | 2.40627e-05 | 0.0125178 | 1.05223e-05 | 1(Win) | true |
| glaze | 1776.44 | 0.0665522 | 8471.59ms | 1225970 | 640 | 1.2279e+08 | 658155 | 0.0257728 | 2.86177 | 6.40389 | 0.609045 | 0.00011277 | 0.0325009 | 1.63965e-05 | 2(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4097.22 | 0.0335074 | 7460.14ms | 1225964 | 640 | 5.85112e+06 | 285357 | 0.200919 | 1.23558 | 4.11982 | 0.402519 | 2.64091e-05 | 0.0124003 | 3.15568e-06 | 1(Win) | true |
| glaze | 1842.74 | 0.0612103 | 8125.34ms | 1225970 | 640 | 9.65292e+07 | 634476 | 0.236567 | 2.75767 | 6.40233 | 0.608707 | 0.000108551 | 0.0121022 | 2.56825e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1686.11 | 0.0767805 | 6187.85ms | 409725 | 30 | 949809 | 231743 | 0.0078973 | 3.05384 | 13.5129 | 2.4884 | 0.013638 | 0.0289056 | 8.33893e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1432.87 | 0.0592295 | 7183.47ms | 409725 | 320 | 8.34834e+06 | 272701 | 0.0761746 | 3.56023 | 16.0389 | 2.88488 | 0.014393 | 0.0585115 | 0.000122353 | 2(Loss) | true |
| glaze | 1212.45 | 0.0811494 | 8434.37ms | 409725 | 640 | 4.3773e+07 | 322276 | 0.129064 | 4.20799 | 17.2052 | 3.43186 | 0.0252401 | 0.0192172 | 3.60455e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1129.25 | 0.0845718 | 9084.55ms | 409725 | 320 | 2.74033e+07 | 346020 | 0.100163 | 4.53733 | 18.6052 | 3.3425 | 0.0139371 | 0.0629789 | 0.000352035 | 4(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2520.15 | 0.0762256 | 5310.93ms | 409725 | 80 | 1.11744e+06 | 155048 | 0.122723 | 2.0076 | 10.0304 | 1.72188 | 0.00794859 | 0.00249265 | 2.01049e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2050.24 | 0.0425104 | 6267.62ms | 409725 | 640 | 4.20095e+06 | 190585 | 0.0686025 | 2.4801 | 12.5575 | 2.11837 | 0.00830518 | 0.0141644 | 1.81028e-05 | 2(Loss) | true |
| glaze | 1510.64 | 0.136591 | 8018.56ms | 409725 | 640 | 7.98893e+07 | 258662 | 0.0788958 | 3.3543 | 14.2302 | 2.76542 | 0.0203335 | 0.00506705 | 2.74918e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1446.41 | 0.0590961 | 8226.59ms | 409725 | 1280 | 3.26236e+07 | 270148 | 0.0392027 | 3.52601 | 15.5127 | 2.64196 | 0.00611995 | 0.0126016 | 5.77312e-05 | 4(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14462.8 | 0.0600386 | 3461.82ms | 409725 | 320 | 84195.6 | 27017.1 | 0.0974405 | 0.352476 | 1.7106 | 0.290607 | 0.000610387 | 0.00624638 | 2.64659e-06 | 1(Win) | true |
| glaze | 3507.11 | 0.169326 | 6098.16ms | 409725 | 640 | 2.27779e+07 | 111415 | 0.301988 | 1.44547 | 5.49083 | 0.863313 | 0.0110692 | 0.0315954 | 3.02184e-05 | 2(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14567 | 0.0373392 | 3434.39ms | 409725 | 2560 | 256812 | 26824 | 0.123846 | 0.351669 | 1.70926 | 0.290305 | 0.000477045 | 0.00601801 | 1.25866e-05 | 1(Win) | true |
| glaze | 3855.18 | 0.150107 | 5597.44ms | 409725 | 2560 | 5.9257e+07 | 101356 | 0.562007 | 1.33123 | 5.47384 | 0.859369 | 0.0109943 | 0.00870061 | 5.83995e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2531.8 | 0.0345614 | 7794.06ms | 785750 | 640 | 6.69691e+06 | 295975 | 0.110158 | 2.02619 | 9.05911 | 1.53181 | 0.00863701 | 0.0531028 | 2.3083e-05 | 1(Win) | true |
| jsonifier | 2251.72 | 0.0330859 | 8657.39ms | 785750 | 640 | 7.75899e+06 | 332790 | 0.0500538 | 2.25386 | 9.64038 | 1.93632 | 0.00705347 | 0.0288876 | 2.39878e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2007.83 | 0.27172 | 9705.6ms | 785750 | 30 | 3.08516e+07 | 373213 | 0.00333154 | 2.53316 | 10.3041 | 1.77083 | 0.00806682 | 0.0565285 | 0.000271545 | 3(Loss) | true |
| glaze | 1808.8 | 0.0525867 | 5361.83ms | 785750 | 640 | 3.03752e+07 | 414280 | 0.0953811 | 2.82522 | 11.801 | 2.33372 | 0.0139088 | 0.0227401 | 7.80365e-05 | 4(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3482.49 | 0.0326316 | 6916.81ms | 785750 | 1280 | 6.31067e+06 | 215176 | 0.0079723 | 1.4629 | 7.24147 | 1.13164 | 0.00538484 | 0.0231607 | 2.72868e-05 | 1(Win) | true |
| jsonifier | 3005.49 | 0.0413224 | 7763.64ms | 785750 | 30 | 318442 | 249327 | 0.0321368 | 1.71336 | 7.82525 | 1.53672 | 0.00426925 | 0.0063664 | 6.47365e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2548.71 | 0.077545 | 8871.63ms | 785750 | 640 | 3.32672e+07 | 294012 | 0.225455 | 2.00412 | 8.69474 | 1.40618 | 0.00388476 | 0.0225543 | 5.68704e-05 | 3(Loss) | true |
| glaze | 2166.5 | 0.127707 | 5137.5ms | 785750 | 160 | 3.12179e+07 | 345881 | 0.00668085 | 2.35668 | 10.2528 | 1.98694 | 0.0112269 | 0.00735385 | 8.03373e-06 | 4(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18016.3 | 0.409206 | 4942.34ms | 785750 | 4890 | 1.41654e+08 | 41592.8 | 0.00515062 | 0.281219 | 1.0144 | 0.15155 | 0.000265098 | 0.0115575 | 5.62395e-06 | 1(Win) | true |
| glaze | 3999.28 | 0.184346 | 10021.8ms | 785750 | 320 | 3.81787e+07 | 187371 | 0.0198977 | 1.26372 | 4.43425 | 0.800315 | 0.00644835 | 0.0517655 | 0.000119233 | 2(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17995.1 | 0.380221 | 4942.16ms | 785750 | 4890 | 1.22586e+08 | 41641.9 | 0.543818 | 0.280876 | 1.01373 | 0.151401 | 0.000269173 | 0.0114093 | 5.36395e-06 | 1(Win) | true |
| glaze | 4603.66 | 0.832738 | 8834.9ms | 785750 | 30 | 5.51188e+07 | 162772 | 0.307926 | 1.09758 | 4.42505 | 0.798136 | 0.00642041 | 0.0139639 | 3.20713e-05 | 2(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7120.65 | 0.170585 | 4348.42ms | 264040 | 80 | 291119 | 35363.1 | 0.0665505 | 0.710947 | 3.44514 | 0.443887 | 0.00113316 | 4.82881e-06 | 2.08302e-06 | 1(Win) | true |
| jsonifier | 6992.35 | 0.0315102 | 4342.59ms | 264040 | 4890 | 629657 | 36012 | 0.0109614 | 0.718257 | 3.46315 | 0.448474 | 0.00122475 | 8.23371e-06 | 3.46279e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5645.19 | 0.0529414 | 5209.1ms | 264040 | 1280 | 713811 | 44605.8 | 0.0586428 | 0.896826 | 4.14008 | 0.458546 | 0.000678741 | 2.11172e-05 | 1.63298e-05 | 3(Loss) | true |
| glaze | 3436.07 | 0.107126 | 8057.19ms | 264040 | 80 | 493056 | 73283.7 | 0.00479324 | 1.46786 | 6.48988 | 1.20295 | 0.00300092 | 1.193e-05 | 8.09536e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7273.19 | 0.0560708 | 4378.41ms | 264040 | 2560 | 964724 | 34621.4 | 0.0211393 | 0.697054 | 3.38543 | 0.429954 | 0.00113299 | 1.04935e-05 | 5.6129e-06 | 1(Win) | true |
| jsonifier | 7186.22 | 0.0715361 | 4439.42ms | 264040 | 640 | 402132 | 35040.4 | 0.135285 | 0.703487 | 3.40047 | 0.43373 | 0.00128174 | 3.44408e-06 | 1.84631e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5767.08 | 0.0192501 | 5200.3ms | 264040 | 4890 | 345464 | 43663.1 | 0.0373803 | 0.875728 | 4.06673 | 0.443581 | 0.000741702 | 9.78116e-06 | 7.18581e-06 | 3(Loss) | true |
| glaze | 3494.48 | 0.0195712 | 8002.16ms | 264040 | 2560 | 509155 | 72058.9 | 0.224869 | 1.44545 | 6.40614 | 1.18417 | 0.00284325 | 9.92096e-06 | 7.2018e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9025.91 | 0.0289936 | 4985.06ms | 399947 | 2560 | 384296 | 42258.3 | 0.137522 | 0.560395 | 2.79215 | 0.311014 | 0.000726557 | 4.07085e-06 | 2.7113e-06 | 1(Win) | true |
| jsonifier | 8951.02 | 0.03299 | 5020.24ms | 399947 | 2560 | 505898 | 42611.8 | 0.0960016 | 0.564972 | 2.79734 | 0.312269 | 0.000782284 | 1.17389e-05 | 8.76386e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7410.12 | 0.0268091 | 5879.66ms | 399947 | 4890 | 931169 | 51472.7 | 0.133438 | 0.682102 | 3.17253 | 0.322029 | 0.000424756 | 9.5846e-06 | 7.51224e-06 | 3(Loss) | true |
| glaze | 4315.16 | 0.0620872 | 9622.82ms | 399947 | 160 | 481875 | 88390.5 | 0.0237709 | 1.17367 | 5.60539 | 1.05224 | 0.0019546 | 3.53172e-06 | 2.18779e-06 | 4(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9194.8 | 0.0369468 | 4962.32ms | 399947 | 2560 | 601331 | 41482.1 | 0.0253434 | 0.549287 | 2.75328 | 0.30199 | 0.000725289 | 6.94721e-06 | 5.08954e-06 | 1(Win) | true |
| jsonifier | 9127.39 | 0.0245639 | 5111.46ms | 399947 | 4890 | 515249 | 41788.4 | 0.0731336 | 0.553928 | 2.75803 | 0.303105 | 0.000795228 | 1.2086e-05 | 9.46342e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7536.75 | 0.0398788 | 5895.85ms | 399947 | 2560 | 1.0427e+06 | 50607.9 | 0.0493156 | 0.668758 | 3.1311 | 0.313689 | 0.000461456 | 7.29491e-06 | 5.29758e-06 | 3(Loss) | true |
| glaze | 4401.52 | 0.0424744 | 9529.57ms | 399947 | 640 | 867031 | 86656.3 | 0.00156146 | 1.15711 | 5.55043 | 1.03992 | 0.00193038 | 1.15328e-05 | 8.83711e-06 | 4(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2037.57 | 0.0472308 | 6729.5ms | 264040 | 1280 | 4.36089e+06 | 123583 | 0.0149764 | 2.51234 | 8.13456 | 1.45925 | 0.0109836 | 0.000210864 | 7.93411e-05 | 1(Win) | true |
| glaze | 1958.24 | 0.080533 | 6965.79ms | 264040 | 320 | 3.43168e+06 | 128589 | 0.15252 | 2.59226 | 10.0219 | 1.80161 | 0.00890086 | 0.000160747 | 6.52718e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1833.2 | 0.0795974 | 7427.91ms | 264040 | 1280 | 1.53014e+07 | 137360 | 0.0968035 | 2.78508 | 9.24675 | 1.52315 | 0.0134301 | 0.000749534 | 0.000165331 | 3(Loss) | true |
| simdjson (ondemand) | 1773.67 | 0.04729 | 7636.51ms | 264040 | 2560 | 1.15391e+07 | 141970 | 0.0650027 | 2.86386 | 10.1441 | 1.54094 | 0.0101864 | 0.00277318 | 0.000167758 | 4(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2579.55 | 0.0383258 | 6189.21ms | 264040 | 2560 | 3.58321e+06 | 97617 | 0.112603 | 1.97737 | 6.71705 | 1.13649 | 0.00777224 | 3.91513e-05 | 1.90741e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2493.27 | 0.0282539 | 6289.09ms | 264040 | 2560 | 2.08448e+06 | 100995 | 0.0605876 | 2.04717 | 7.84218 | 1.20417 | 0.00416873 | 0.000134742 | 3.78642e-05 | 2(Loss) | true |
| glaze | 2427.23 | 0.080293 | 6421.81ms | 264040 | 320 | 2.22036e+06 | 103743 | 0.155758 | 2.10383 | 8.58649 | 1.47343 | 0.00718137 | 3.33875e-05 | 1.57647e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2176.45 | 0.0876286 | 7073.8ms | 264040 | 1280 | 1.31566e+07 | 115697 | 0.0967779 | 2.33515 | 8.78218 | 1.23291 | 0.0070988 | 0.000681037 | 5.01907e-05 | 4(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18862.5 | 0.0367696 | 2078.65ms | 264040 | 2560 | 61681.8 | 13349.6 | 0.206015 | 0.269398 | 1.07262 | 0.162566 | 1.00926e-05 | 2.12237e-05 | 1.24301e-05 | 1(Win) | true |
| glaze | 5945.43 | 0.214699 | 5025.48ms | 263923 | 2560 | 2.11488e+07 | 42334.4 | 0.366013 | 0.862433 | 2.25655 | 0.339808 | 0.000464374 | 0.00402003 | 3.83753e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19306.4 | 0.104735 | 2064.39ms | 264040 | 40 | 7464.2 | 13042.7 | 0.0038973 | 0.267684 | 1.0705 | 0.162089 | 1.15513e-05 | 3.88199e-06 | 2.55643e-06 | 1(Win) | true |
| glaze | 7010.75 | 0.14039 | 4346.01ms | 263923 | 4890 | 1.24225e+07 | 35901.5 | 0.237892 | 0.726473 | 2.23443 | 0.33478 | 0.000442164 | 2.43851e-05 | 1.64538e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2614.84 | 0.224998 | 7847.86ms | 399947 | 2560 | 2.7575e+08 | 145867 | 0.0158367 | 1.945 | 6.67157 | 1.02534 | 0.00870846 | 0.00281709 | 0.000110985 | 1(Win) | true |
| simdjson (ondemand) | 2501.29 | 0.299057 | 8200.8ms | 399947 | 1280 | 2.66191e+08 | 152489 | 0.0903469 | 2.0298 | 7.14161 | 1.03806 | 0.00710098 | 0.00404057 | 0.000107571 | 2(Loss) | true |
| glaze | 2346 | 0.107365 | 8686.09ms | 399947 | 1280 | 3.90017e+07 | 162582 | 0.082762 | 2.1736 | 8.45403 | 1.52911 | 0.00746057 | 0.000577522 | 0.000115564 | 3(Loss) | true |
| jsonifier | 2039.94 | 0.0630758 | 9967.86ms | 399947 | 320 | 4.45087e+06 | 186976 | 0.157923 | 2.5104 | 7.03676 | 1.35799 | 0.00769651 | 0.00237101 | 0.000127447 | 4(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3277.96 | 0.207183 | 7259.81ms | 399947 | 80 | 4.64939e+06 | 116359 | 0.0334736 | 1.56454 | 5.74088 | 0.813641 | 0.00640135 | 0.000618832 | 2.76599e-05 | 1(Win) | true |
| simdjson (ondemand) | 3055.64 | 0.0850747 | 7567.96ms | 399947 | 1280 | 1.44348e+07 | 124825 | 0.27017 | 1.65528 | 6.24792 | 0.83579 | 0.00508465 | 0.00158366 | 8.59821e-05 | 2(Loss) | true |
| glaze | 2818.46 | 0.0471367 | 8001.66ms | 399947 | 2560 | 1.04169e+07 | 135329 | 0.107847 | 1.80892 | 7.5185 | 1.3161 | 0.00525176 | 0.000105008 | 2.44652e-05 | 3(Loss) | true |
| jsonifier | 2368.41 | 0.045286 | 9381.94ms | 399947 | 1280 | 6.80816e+06 | 161045 | 0.0769937 | 2.16248 | 6.10374 | 1.14578 | 0.00565805 | 0.000371067 | 8.82695e-05 | 4(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22759.5 | 0.0750683 | 2435.23ms | 399947 | 30 | 4748.02 | 16758.7 | 0.195904 | 0.226916 | 0.778601 | 0.11092 | 3.2671e-05 | 3.5088e-05 | 1.56687e-05 | 1(Win) | true |
| glaze | 5171.72 | 0.428258 | 8169.73ms | 399830 | 1280 | 1.27615e+08 | 73729.3 | 0.0932316 | 0.981973 | 2.54919 | 0.45877 | 0.00073261 | 0.00535516 | 4.74479e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22701.7 | 0.0557401 | 2421.9ms | 399947 | 2560 | 224525 | 16801.4 | 0.0446913 | 0.225329 | 0.777183 | 0.110602 | 9.64581e-06 | 2.89247e-05 | 1.16217e-05 | 1(Win) | true |
| glaze | 6447.51 | 0.165026 | 6699.8ms | 399830 | 640 | 6.09613e+06 | 59140.3 | 0.0521659 | 0.795684 | 2.53274 | 0.454951 | 0.00073162 | 5.92166e-05 | 1.97662e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1034.6 | 0.0502452 | 1155.28ms | 4630 | 1280 | 5885.94 | 4267.84 | 0.0366159 | 5.02396 | 23.0756 | 4.68013 | 0.00828361 | 6.14201e-05 | 2.19357e-05 | 1(Win) | true |
| jsonifier (two-stage) | 942.27 | 0.132671 | 1195.46ms | 4630 | 320 | 12368.3 | 4686.04 | 0.0774174 | 5.50405 | 25.7786 | 5.02225 | 0.00645451 | 2.4973e-05 | 2.02484e-06 | 2(Loss) | true |
| glaze | 814.358 | 0.0527456 | 1267.11ms | 4630 | 2560 | 20938.4 | 5422.08 | 0.0569611 | 6.32058 | 29.4497 | 5.77668 | 0.00548765 | 0.000103182 | 5.69486e-05 | 3(Loss) | true |
| simdjson (ondemand) | 731.856 | 0.089838 | 1332.05ms | 4630 | 1280 | 37604.6 | 6033.31 | 0.0264358 | 7.0925 | 30.8024 | 5.44644 | 0.00358616 | 0.000103435 | 5.60205e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1303.46 | 0.117372 | 1154.25ms | 4630 | 320 | 5058.78 | 3387.53 | 0.0716373 | 4.00238 | 18.7393 | 3.67495 | 0.00546099 | 2.29482e-05 | 2.02484e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1162.24 | 0.0529302 | 1195.52ms | 4630 | 2560 | 10351.9 | 3799.15 | 0.00177874 | 4.47211 | 21.4445 | 4.01793 | 0.00440141 | 4.58963e-05 | 1.94047e-05 | 2(Loss) | true |
| glaze | 984.095 | 0.0985545 | 1273.98ms | 4630 | 320 | 6257.35 | 4486.88 | 0.00459653 | 5.28125 | 25.0134 | 4.74816 | 0.0027585 | 7.69438e-05 | 3.37473e-05 | 3(Loss) | true |
| simdjson (ondemand) | 828.825 | 0.070101 | 1351.24ms | 4630 | 2560 | 35704.6 | 5327.44 | 0.0267485 | 6.2428 | 27.3433 | 4.64883 | 0.00146826 | 9.30582e-05 | 4.78368e-05 | 4(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1611.96 | 0.0602399 | 1001.01ms | 4630 | 4890 | 13314.6 | 2739.21 | 0.0380273 | 3.22986 | 7.95616 | 0.458964 | 0.00027508 | 7.88403e-05 | 3.66596e-05 | 1(Win) | true |
| glaze | 973.851 | 0.0934469 | 1175.49ms | 4630 | 640 | 11489.1 | 4534.07 | 0.0511667 | 5.34033 | 9.73197 | 0.673219 | 0.000222057 | 5.83828e-05 | 2.80103e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1638.42 | 0.128307 | 992.535ms | 4630 | 4890 | 58468.5 | 2694.98 | 0.153433 | 3.18048 | 7.84536 | 0.433262 | 0.000219251 | 5.68887e-05 | 1.97874e-05 | 1(Win) | true |
| glaze | 1027.07 | 0.0575891 | 1149.64ms | 4630 | 40 | 245.189 | 4299.12 | 0.0335227 | 5.06675 | 9.2527 | 0.565875 | 0.000431965 | 5.39957e-05 | 2.15983e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2739.82 | 0.0424403 | 1240.96ms | 14795 | 2560 | 12228.8 | 5149.84 | 0.0575915 | 1.88524 | 8.95904 | 1.61724 | 0.00223542 | 4.68908e-05 | 2.65081e-05 | 1(Win) | true |
| jsonifier | 2547.39 | 0.0500548 | 1287.49ms | 14795 | 2560 | 19677.5 | 5538.85 | 0.067248 | 2.02697 | 9.4219 | 1.98074 | 0.00374097 | 3.13926e-05 | 1.65016e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2164.39 | 0.0538498 | 1388.34ms | 14795 | 4890 | 60260.9 | 6518.97 | 0.0584752 | 2.3914 | 10.4788 | 1.74417 | 0.00109915 | 3.00494e-05 | 1.54532e-05 | 3(Loss) | true |
| glaze | 1952.19 | 0.131614 | 1454.18ms | 14795 | 40 | 3619.48 | 7227.57 | 0.0510515 | 2.65391 | 12.1984 | 2.37864 | 0.0051808 | 1.68976e-05 | 1.01386e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3308.81 | 0.0538376 | 1247.14ms | 14795 | 2560 | 13492.7 | 4264.26 | 0.0263982 | 1.55917 | 7.6 | 1.3022 | 0.00151096 | 2.40527e-05 | 1.27788e-05 | 1(Win) | true |
| jsonifier | 3085.33 | 0.0415156 | 1280.44ms | 14795 | 2560 | 9227.63 | 4573.13 | 0.0725121 | 1.68735 | 8.05921 | 1.66475 | 0.00260392 | 1.99603e-05 | 8.23758e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2450.09 | 0.0852299 | 1403.02ms | 14795 | 2560 | 61672.4 | 5758.82 | 0.0567827 | 2.10744 | 9.40352 | 1.49605 | 0.00050302 | 3.43233e-05 | 1.73464e-05 | 3(Loss) | true |
| glaze | 2215.05 | 0.0573778 | 1455.65ms | 14795 | 2560 | 34197.3 | 6369.89 | 0.0101746 | 2.3347 | 10.8195 | 2.05914 | 0.00448634 | 4.71813e-05 | 3.02045e-05 | 4(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5028.27 | 0.0664381 | 1008.56ms | 14795 | 4890 | 16995.6 | 2806.06 | 0.155796 | 1.03672 | 2.57999 | 0.144644 | 6.88344e-05 | 3.62832e-05 | 1.85217e-05 | 1(Win) | true |
| glaze | 3455.78 | 0.0874775 | 1138.66ms | 14795 | 4890 | 62379.4 | 4082.91 | 0.126246 | 1.50072 | 4.43961 | 0.532342 | 0.000951463 | 2.47831e-05 | 9.95196e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5173.16 | 0.17732 | 998.529ms | 14795 | 30 | 701.706 | 2727.47 | 0.140348 | 1.01085 | 2.54059 | 0.135519 | 6.75904e-05 | 1.12651e-05 | 0 | 1(Win) | true |
| glaze | 3946.31 | 0.0625142 | 1085.75ms | 14795 | 4890 | 24429.5 | 3575.39 | 0.322176 | 1.31887 | 4.23853 | 0.486313 | 0.00100811 | 2.05674e-05 | 6.62082e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1920.02 | 0.077649 | 984.042ms | 5092 | 2560 | 9873.64 | 2529.2 | 0.0191859 | 2.73357 | 11.0485 | 2.06422 | 0.00119895 | 6.25215e-05 | 2.93045e-05 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1549.56 | 0.0910334 | 1048.41ms | 5092 | 1280 | 10417.7 | 3133.86 | 0.00782719 | 3.3682 | 13.7196 | 2.39415 | 0.00125519 | 6.55133e-05 | 3.08388e-05 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1546.43 | 0.11211 | 1044.83ms | 5092 | 640 | 7932.09 | 3140.21 | 0.148648 | 3.35346 | 14.2099 | 2.72113 | 0.000845382 | 4.90966e-05 | 1.59564e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1262.08 | 0.0328837 | 1118.81ms | 5092 | 1280 | 2049.16 | 3847.71 | 0.190797 | 4.11946 | 15.6133 | 2.64434 | 0.00195803 | 6.13708e-05 | 3.00717e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2336.78 | 0.0732942 | 1052.74ms | 5092 | 4890 | 11344.6 | 2078.12 | 0.18268 | 2.24501 | 9.39376 | 1.66084 | 0.00183463 | 4.494e-05 | 1.78314e-05 | 1(Win) | true |
| glaze | 1843.08 | 0.0689813 | 1056.3ms | 5092 | 4890 | 16153.3 | 2634.78 | 0.159649 | 2.8367 | 12.5717 | 2.32266 | 0.00097382 | 8.10847e-05 | 4.08034e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1839.62 | 0.0491086 | 1056.65ms | 5092 | 4890 | 8217.61 | 2639.74 | 0.0451834 | 2.83844 | 12.206 | 2.01787 | 0.00149451 | 5.60244e-05 | 1.98796e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1449.46 | 0.0748986 | 1110.04ms | 5092 | 4890 | 30790.8 | 3350.29 | 0.0624421 | 3.59361 | 13.8887 | 2.2309 | 0.00159655 | 7.83538e-05 | 2.89158e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8884.36 | 0.0718402 | 783.11ms | 5092 | 1280 | 197.365 | 546.591 | 0.861817 | 0.621156 | 2.28888 | 0.399647 | 0.000196386 | 5.44666e-05 | 2.31675e-05 | 1(Win) | true |
| glaze | 3135.88 | 0.152247 | 885.247ms | 5092 | 4890 | 27181.1 | 1548.56 | 0.035935 | 1.67959 | 4.63708 | 0.709348 | 0.000202812 | 6.93979e-05 | 3.01206e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9572.93 | 0.125868 | 773.045ms | 5092 | 40 | 16.3071 | 507.275 | 0.0542406 | 0.582011 | 2.17969 | 0.374902 | 0.000196386 | 4.90966e-05 | 0 | 1(Win) | true |
| glaze | 3926.51 | 0.266339 | 856.003ms | 5092 | 640 | 6944.04 | 1236.75 | 0.0674196 | 1.34895 | 4.10134 | 0.593087 | 0.000212957 | 4.2039e-05 | 1.16604e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3161.54 | 0.138813 | 1089.4ms | 11724 | 40 | 963.999 | 3536.53 | 0.0708762 | 1.65261 | 6.89193 | 1.09408 | 0.000678096 | 3.62504e-05 | 1.06619e-05 | 1(Win) | true |
| jsonifier | 2697 | 0.0657567 | 1145.61ms | 11724 | 1280 | 9512.19 | 4145.68 | 0.0233732 | 1.92923 | 7.41718 | 1.51041 | 0.000897731 | 1.91248e-05 | 6.73032e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2669.4 | 0.0785048 | 1154.97ms | 11724 | 1280 | 13839.7 | 4188.54 | 0.167664 | 1.94563 | 7.51348 | 1.18245 | 0.00086308 | 5.16435e-05 | 2.49888e-05 | 3(Loss) | true |
| glaze | 2403.86 | 0.0910776 | 1195.72ms | 11724 | 640 | 11485.2 | 4651.23 | 0.114254 | 2.15242 | 9.13605 | 1.76996 | 0.00142416 | 1.31941e-05 | 2.93202e-06 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3708.36 | 0.0507946 | 1116.67ms | 11724 | 4890 | 11469.2 | 3015.05 | 0.059894 | 1.40023 | 6.17315 | 0.918885 | 0.000761586 | 2.26407e-05 | 7.98879e-06 | 1(Win) | true |
| jsonifier | 3045.52 | 0.0545445 | 1173.68ms | 11724 | 4890 | 19608.3 | 3671.26 | 0.067933 | 1.69993 | 6.69831 | 1.33512 | 0.00107802 | 3.31761e-05 | 1.68846e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3039.46 | 0.0358151 | 1151ms | 11724 | 4890 | 8487.89 | 3678.57 | 0.00751118 | 1.70737 | 6.7664 | 1.00348 | 0.000763278 | 2.34082e-05 | 8.82604e-06 | 3(Loss) | true |
| glaze | 2684.83 | 0.060537 | 1203.19ms | 11724 | 2560 | 16270.4 | 4164.46 | 0.304403 | 1.92319 | 8.41633 | 1.59536 | 0.00147544 | 3.11194e-05 | 1.60262e-05 | 4(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18165.9 | 0.0876657 | 792.547ms | 11724 | 80 | 23.291 | 615.487 | 0.0996137 | 0.307592 | 1.12282 | 0.176731 | 8.52951e-05 | 1.38605e-05 | 0 | 1(Win) | true |
| glaze | 3733.04 | 0.182802 | 1036.12ms | 11746 | 4890 | 147139 | 3000.74 | 0.170574 | 1.40072 | 3.6054 | 0.656053 | 0.000525576 | 2.13796e-05 | 7.26001e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18978 | 0.153215 | 785.931ms | 11724 | 40 | 32.5923 | 589.15 | 0.155834 | 0.293571 | 1.07361 | 0.165387 | 8.52951e-05 | 5.54418e-05 | 1.27943e-05 | 1(Win) | true |
| glaze | 4486.42 | 0.152016 | 984.923ms | 11746 | 2560 | 36880.6 | 2496.84 | 0.154878 | 1.1669 | 3.33441 | 0.594586 | 0.000518794 | 2.51748e-05 | 9.41145e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2086.79 | 0.0599935 | 948.949ms | 4857 | 2560 | 4539.71 | 2219.68 | 0.0205857 | 2.5147 | 9.46181 | 1.75108 | 0.000524292 | 6.3375e-05 | 2.67816e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1805.1 | 0.104907 | 986.465ms | 4857 | 1280 | 9275.85 | 2566.06 | 0.149223 | 2.89482 | 11.5077 | 1.97118 | 0.0008361 | 8.83068e-05 | 4.6164e-05 | 2(Loss) | true |
| glaze | 1754.06 | 0.0658077 | 995.73ms | 4857 | 2560 | 7731.05 | 2640.72 | 0.187251 | 2.98639 | 11.9269 | 2.25654 | 0.000820497 | 5.59759e-05 | 2.78271e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1472.86 | 0.0637992 | 1046.69ms | 4857 | 2560 | 10305.9 | 3144.91 | 0.323802 | 3.52807 | 13.3972 | 2.21289 | 0.000541985 | 0.000143559 | 8.22749e-05 | 4(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2769.2 | 0.0589678 | 919.076ms | 4857 | 4890 | 4757.34 | 1672.68 | 0.143919 | 1.90645 | 7.32489 | 1.25983 | 0.000415398 | 7.01031e-05 | 3.15359e-05 | 1(Win) | true |
| glaze | 2489.16 | 0.352506 | 943.663ms | 4857 | 30 | 1290.88 | 1860.87 | 0.0537673 | 2.11573 | 9.03809 | 1.61931 | 0.000892183 | 2.74518e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 2247.92 | 0.0449531 | 958.957ms | 4857 | 4890 | 4195.67 | 2060.57 | 0.114131 | 2.33814 | 9.59625 | 1.52728 | 0.000696273 | 8.92183e-05 | 4.69038e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1936.07 | 0.0709202 | 991.86ms | 4857 | 1280 | 3685.06 | 2392.47 | 0.15725 | 2.70505 | 10.9339 | 1.67758 | 0.00124932 | 2.97573e-05 | 4.02126e-06 | 4(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9925.71 | 0.283116 | 768.925ms | 4857 | 30 | 52.3678 | 466.667 | 0.0428755 | 0.561911 | 1.77599 | 0.31398 | 0.000205888 | 4.80406e-05 | 2.74518e-05 | 1(Win) | true |
| glaze | 3819.79 | 0.206025 | 854.27ms | 4857 | 4890 | 30521.6 | 1212.63 | 0.228062 | 1.39531 | 3.84085 | 0.640107 | 0.000207994 | 7.46082e-05 | 2.77886e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11225.5 | 0.112346 | 764.633ms | 4857 | 30 | 6.44713 | 412.633 | 0.0645838 | 0.523279 | 1.65349 | 0.284332 | 0.000205888 | 3.43147e-05 | 6.86295e-06 | 1(Win) | true |
| glaze | 4096.38 | 0.257028 | 833.448ms | 4857 | 4890 | 41305.3 | 1130.75 | 0.0985212 | 1.30542 | 3.32839 | 0.524398 | 0.000282854 | 5.30931e-05 | 1.81468e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2632.88 | 0.0747089 | 992.913ms | 7376 | 4890 | 19482 | 2671.71 | 0.0947689 | 1.99194 | 8.0884 | 1.30382 | 0.000397409 | 8.9302e-05 | 5.17624e-05 | 1(Win) | true |
| glaze | 2190.86 | 0.060343 | 1050.83ms | 7376 | 2560 | 9609.66 | 3210.75 | 0.0285499 | 2.38082 | 9.98671 | 1.968 | 0.00100071 | 0.000101046 | 6.13264e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2134.54 | 0.0848422 | 1059.02ms | 7376 | 640 | 5003.08 | 3295.47 | 0.292066 | 2.42786 | 9.28715 | 1.47939 | 0.000773412 | 2.77505e-05 | 9.32077e-06 | 3(Loss) | true |
| jsonifier | 2034.35 | 0.120179 | 1069.97ms | 7376 | 2560 | 44206.8 | 3457.77 | 0.0418504 | 2.56457 | 8.76885 | 1.78037 | 0.00104504 | 7.88029e-05 | 4.90929e-05 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3200.04 | 0.0876637 | 971.584ms | 7376 | 1280 | 4753.14 | 2198.19 | 0.0332415 | 1.64473 | 6.86077 | 1.01763 | 0.000776907 | 2.22427e-05 | 6.35507e-06 | 1(Win) | true |
| glaze | 2985.38 | 0.137872 | 985.954ms | 7376 | 40 | 422.141 | 2356.25 | 0.0699775 | 1.7562 | 8.04027 | 1.53905 | 0.000765998 | 2.03362e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 2830.1 | 0.170276 | 1014.43ms | 7376 | 30 | 537.361 | 2485.53 | 0.028155 | 1.85143 | 7.6471 | 1.12324 | 0.000763738 | 0.000117498 | 4.06725e-05 | 3(Loss) | true |
| jsonifier | 2442.59 | 0.124169 | 1041.79ms | 7376 | 640 | 8183.63 | 2879.85 | 0.291481 | 2.13788 | 7.38896 | 1.46367 | 0.000988213 | 2.09717e-05 | 5.9314e-06 | 4(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14245.4 | 0.215354 | 775.322ms | 7376 | 160 | 180.932 | 493.794 | 0.0721976 | 0.390321 | 1.2561 | 0.207023 | 0.000135575 | 2.28783e-05 | 1.27101e-05 | 1(Win) | true |
| glaze | 3121.57 | 0.18557 | 958.202ms | 7376 | 1280 | 22383.2 | 2253.45 | 0.152151 | 1.67707 | 3.92815 | 0.703634 | 0.000348893 | 7.84851e-05 | 3.44233e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15759 | 0.090582 | 766.922ms | 7376 | 1280 | 209.257 | 446.368 | 0.149073 | 0.357025 | 1.17584 | 0.188856 | 0.000135787 | 1.4193e-05 | 4.97814e-06 | 1(Win) | true |
| glaze | 3636.59 | 0.263743 | 925.471ms | 7376 | 640 | 16656.8 | 1934.31 | 0.116588 | 1.44705 | 3.6128 | 0.632592 | 0.000272209 | 1.82179e-05 | 2.54203e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2452.77 | 0.0544071 | 891.193ms | 4390 | 640 | 551.959 | 1706.9 | 0.213564 | 2.14165 | 10.0749 | 1.78861 | 0.000984126 | 3.2033e-05 | 1.3881e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1831.66 | 0.108463 | 955.751ms | 4390 | 1280 | 7867.1 | 2285.7 | 0.132136 | 2.85806 | 13.477 | 2.30068 | 0.00171572 | 7.95487e-05 | 3.55923e-05 | 2(Loss) | true |
| glaze | 1786.41 | 0.0956662 | 954.545ms | 4390 | 1280 | 6434.22 | 2343.6 | 0.0952152 | 2.93094 | 13.6248 | 2.65535 | 0.000828766 | 3.89735e-05 | 6.58457e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1386.71 | 0.0835362 | 1031.65ms | 4390 | 1280 | 8141.75 | 3019.11 | 0.0603601 | 3.76723 | 16.505 | 2.8533 | 0.00135998 | 4.76936e-05 | 1.47708e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2910.78 | 0.110498 | 893.804ms | 4390 | 1280 | 3233.17 | 1438.32 | 0.109569 | 1.81784 | 8.84579 | 1.50068 | 0.00101776 | 2.70501e-05 | 5.16088e-06 | 1(Win) | true |
| glaze | 2110.84 | 0.0585041 | 944.467ms | 4390 | 2560 | 3446.92 | 1983.39 | 0.0556659 | 2.49488 | 12.1355 | 2.32665 | 0.000812927 | 2.59823e-05 | 2.58044e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2069.96 | 0.0739247 | 956.45ms | 4390 | 4890 | 10931.9 | 2022.57 | 0.599646 | 2.52411 | 12.2472 | 2.01276 | 0.00169962 | 5.82752e-05 | 2.24064e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1566.71 | 0.112234 | 1010.43ms | 4390 | 640 | 5756.86 | 2672.25 | 0.238135 | 3.33582 | 15.0517 | 2.53394 | 0.000460208 | 4.37785e-05 | 1.17454e-05 | 4(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11370.4 | 0.0790581 | 757.429ms | 4390 | 640 | 54.231 | 368.203 | 0.147044 | 0.501981 | 2.25718 | 0.377449 | 0.000228146 | 7.47437e-06 | 4.62699e-06 | 1(Win) | true |
| glaze | 3797.73 | 0.164757 | 830.421ms | 4390 | 4890 | 16131.7 | 1102.4 | 0.557236 | 1.40419 | 5.35626 | 0.83918 | 0.000481201 | 8.50138e-05 | 3.91296e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12306.6 | 0.0876734 | 753.556ms | 4390 | 1280 | 113.868 | 340.195 | 0.0410901 | 0.466162 | 2.13007 | 0.347836 | 0.000239536 | 3.00755e-05 | 1.42369e-05 | 1(Win) | true |
| glaze | 3727 | 0.166366 | 831.852ms | 4390 | 4890 | 17078.5 | 1123.32 | 0.324075 | 1.42662 | 4.95558 | 0.749887 | 0.000543296 | 5.19399e-05 | 1.6863e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4032.96 | 0.0540659 | 1004.02ms | 11521 | 2560 | 5554.18 | 2724.37 | 0.0960594 | 1.28842 | 6.09609 | 0.931169 | 0.00098197 | 2.25471e-05 | 8.54418e-06 | 1(Win) | true |
| jsonifier | 3447.67 | 0.0468092 | 1044.6ms | 11521 | 4890 | 10881.8 | 3186.87 | 0.144199 | 1.50076 | 6.50725 | 1.31187 | 0.00250575 | 2.15841e-05 | 9.38981e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3264.42 | 0.0655425 | 1073.64ms | 11521 | 1280 | 6229.07 | 3365.76 | 0.144097 | 1.59648 | 7.08637 | 1.12534 | 0.000568934 | 2.44798e-05 | 1.08498e-05 | 3(Loss) | true |
| glaze | 2718.54 | 0.0769173 | 1131.54ms | 11521 | 4890 | 47256.9 | 4041.61 | 0.0630632 | 1.90678 | 8.34216 | 1.64647 | 0.00405178 | 1.68804e-05 | 5.07653e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4498.02 | 0.189861 | 1006.12ms | 11521 | 320 | 6882.71 | 2442.69 | 0.00818835 | 1.16285 | 5.62937 | 0.822064 | 0.000971867 | 1.98008e-05 | 4.06866e-06 | 1(Win) | true |
| jsonifier | 3752.35 | 0.0507032 | 1047.66ms | 11521 | 4890 | 10778.4 | 2928.11 | 0.0930887 | 1.38176 | 6.03854 | 1.20224 | 0.00258005 | 1.79276e-05 | 7.13554e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3605.56 | 0.080527 | 1059.68ms | 11521 | 2560 | 15415.5 | 3047.31 | 0.0120766 | 1.43105 | 6.55151 | 1.00746 | 0.00031427 | 3.40411e-05 | 1.63424e-05 | 3(Loss) | true |
| glaze | 2964.47 | 0.0574826 | 1119.18ms | 11521 | 1280 | 5809.92 | 3706.32 | 0.0401391 | 1.74651 | 7.77363 | 1.52122 | 0.00422367 | 9.96821e-06 | 1.49184e-06 | 4(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22178.6 | 0.397471 | 775.733ms | 11521 | 30 | 116.317 | 495.4 | 0.215779 | 0.250331 | 0.988977 | 0.143564 | 8.6798e-05 | 2.02529e-05 | 1.15731e-05 | 1(Win) | true |
| glaze | 4776.22 | 0.114775 | 962.985ms | 11521 | 4890 | 34089 | 2300.41 | 0.305466 | 1.08839 | 3.77962 | 0.681191 | 0.00122829 | 3.70445e-05 | 1.68981e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23974.5 | 0.113469 | 772.776ms | 11521 | 4890 | 1322.35 | 458.29 | 0.178233 | 0.232223 | 0.939502 | 0.132107 | 8.69933e-05 | 1.82294e-05 | 1.14843e-05 | 1(Win) | true |
| glaze | 5322.69 | 0.214244 | 937.808ms | 11521 | 4890 | 95641 | 2064.23 | 0.0152599 | 0.979604 | 3.54362 | 0.629807 | 0.00122975 | 2.23119e-05 | 8.1118e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2741.01 | 0.201169 | 893.494ms | 4669 | 40 | 427.179 | 1624.47 | 0.0138487 | 1.925 | 7.76697 | 1.55644 | 0.00112444 | 3.74813e-05 | 0 | 1(Win) | true |
| glaze | 2205.02 | 0.0876998 | 932.689ms | 4669 | 4890 | 15336.6 | 2019.35 | 0.1186 | 2.37495 | 9.72435 | 1.7357 | 0.000576574 | 6.0443e-05 | 3.33313e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1957.29 | 0.0640248 | 953.438ms | 4669 | 2560 | 5430.91 | 2274.93 | 0.0741231 | 2.65903 | 10.9242 | 1.87685 | 0.00117807 | 3.95728e-05 | 9.62131e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1600.16 | 0.127625 | 1006.15ms | 4669 | 30 | 378.368 | 2782.67 | 0.0299383 | 3.20814 | 13.764 | 1.98522 | 0.00127079 | 0.000114229 | 7.13929e-06 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2979.46 | 0.0584011 | 879.645ms | 4669 | 4890 | 3724.98 | 1494.47 | 0.0943565 | 1.76674 | 7.31484 | 1.44656 | 0.00122564 | 3.99012e-05 | 1.58554e-05 | 1(Win) | true |
| glaze | 2485.91 | 0.110513 | 916.466ms | 4669 | 160 | 626.938 | 1791.17 | 0.0425517 | 2.11808 | 8.95074 | 1.5635 | 0.000748287 | 1.7402e-05 | 4.01585e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2100.13 | 0.0610596 | 945.903ms | 4669 | 320 | 536.308 | 2120.21 | 0.306516 | 2.49896 | 10.4712 | 1.76676 | 0.00108562 | 2.07486e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1776.53 | 0.148707 | 990.605ms | 4669 | 40 | 555.682 | 2506.4 | 0.0119708 | 2.94779 | 12.9728 | 1.81174 | 0.00108696 | 3.21268e-05 | 0 | 4(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12750.2 | 0.162594 | 764.142ms | 4669 | 40 | 12.8968 | 349.225 | 0.00715922 | 0.451258 | 1.41551 | 0.361319 | 0.000214179 | 6.42536e-05 | 1.07089e-05 | 1(Win) | true |
| glaze | 3544.51 | 0.294131 | 857.972ms | 4669 | 4890 | 66761.5 | 1256.23 | 0.141731 | 1.49151 | 3.2266 | 0.491969 | 0.000219829 | 3.83682e-05 | 1.10812e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14104.8 | 0.537172 | 758.557ms | 4669 | 2560 | 7361.74 | 315.688 | 0.13059 | 0.411845 | 1.29599 | 0.333904 | 0.000214346 | 2.03302e-05 | 3.4302e-06 | 1(Win) | true |
| glaze | 3756.1 | 0.341763 | 847.992ms | 4669 | 2560 | 42020.7 | 1185.46 | 0.187044 | 1.42718 | 2.7085 | 0.375669 | 0.000250321 | 1.90753e-05 | 4.09951e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3489.14 | 0.0683286 | 981.712ms | 9249 | 160 | 477.396 | 2528 | 0.0266938 | 1.50034 | 6.31636 | 0.992107 | 0.000670343 | 1.82452e-05 | 1.3515e-06 | 1(Win) | true |
| simdjson (ondemand) | 2997.48 | 0.112384 | 1029.41ms | 9249 | 40 | 437.464 | 2942.65 | 0.104891 | 1.74235 | 7.57887 | 1.03038 | 0.000689264 | 2.1624e-05 | 0 | 2(Loss) | true |
| glaze | 2842.86 | 0.0512606 | 1039.94ms | 9249 | 4890 | 12369.6 | 3102.7 | 0.0746321 | 1.8357 | 7.68907 | 1.41583 | 0.0015596 | 2.12039e-05 | 7.47331e-06 | 3(Loss) | true |
| jsonifier | 2827.39 | 0.142493 | 1037.8ms | 9249 | 40 | 790.43 | 3119.68 | 0.0355398 | 1.84483 | 6.43853 | 1.42448 | 0.000978484 | 5.67629e-05 | 2.70299e-05 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3668.28 | 0.0380702 | 975.31ms | 9249 | 4890 | 4097.73 | 2404.54 | 0.0817068 | 1.43277 | 6.12326 | 0.944318 | 0.000554506 | 2.20441e-05 | 7.42909e-06 | 1(Win) | true |
| simdjson (ondemand) | 3210.23 | 0.0401512 | 1011.96ms | 9249 | 4890 | 5951.45 | 2747.63 | 0.0689474 | 1.61921 | 7.17948 | 0.942805 | 0.00060609 | 2.67315e-05 | 8.2914e-06 | 2(Loss) | true |
| glaze | 3076.82 | 0.155982 | 1021.34ms | 9249 | 320 | 6398.59 | 2866.77 | 0.0543652 | 1.69601 | 7.29819 | 1.3289 | 0.00145996 | 2.70299e-05 | 1.82452e-05 | 3(Loss) | true |
| jsonifier | 2929.72 | 0.0963509 | 1037.32ms | 9249 | 1280 | 10771.1 | 3010.71 | 0.0363155 | 1.76855 | 6.24565 | 1.37669 | 0.00100028 | 1.69782e-05 | 5.23705e-06 | 4(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 22591.4 | 0.187573 | 767.654ms | 9249 | 80 | 42.9074 | 390.438 | 0.0352293 | 0.25211 | 0.82117 | 0.183047 | 0.00010812 | 4.05449e-06 | 0 | 1(Win) | true |
| glaze | 4271.68 | 0.43332 | 937.908ms | 9249 | 320 | 25618.9 | 2064.89 | 0.141454 | 1.22809 | 3.26479 | 0.619419 | 0.000437885 | 4.0207e-05 | 1.99346e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24554.5 | 0.0532628 | 760.408ms | 9249 | 1280 | 46.8581 | 359.223 | 0.132706 | 0.232784 | 0.765921 | 0.170505 | 0.000108204 | 9.29155e-06 | 1.52043e-06 | 1(Win) | true |
| glaze | 4719.51 | 0.176033 | 917.738ms | 9249 | 4890 | 52929.1 | 1868.95 | 0.185172 | 1.11416 | 3.00551 | 0.560709 | 0.000389939 | 1.59637e-05 | 6.54467e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 835.666 | 0.0357625 | 1256.01ms | 4604 | 4890 | 17265.1 | 5254.15 | 0.0942075 | 6.20937 | 24.4885 | 5.36099 | 0.00474825 | 0.000127967 | 7.03576e-05 | 1(Win) | true |
| jsonifier (two-stage) | 727.159 | 0.100953 | 1338.32ms | 4604 | 640 | 23781.1 | 6038.18 | 0.294283 | 7.06056 | 28.0187 | 5.7891 | 0.0066525 | 0.000180889 | 0.000109619 | 2(Loss) | true |
| glaze | 657.682 | 0.0318947 | 1403.71ms | 4604 | 4890 | 22170.9 | 6676.05 | 0.134378 | 7.80902 | 33.1205 | 6.8914 | 0.00769745 | 9.39878e-05 | 4.52172e-05 | 3(Loss) | true |
| simdjson (ondemand) | 593.728 | 0.0316706 | 1475.77ms | 4604 | 4890 | 26823.6 | 7395.17 | 0.042903 | 8.65462 | 35.7967 | 6.60057 | 0.00726402 | 0.000159504 | 8.81691e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1024.31 | 0.0554635 | 1251.98ms | 4604 | 1280 | 7234.85 | 4286.5 | 0.0437229 | 5.07548 | 20.0767 | 4.35035 | 0.00414229 | 8.00934e-05 | 3.93679e-05 | 1(Win) | true |
| jsonifier (two-stage) | 887.8 | 0.0489298 | 1323.86ms | 4604 | 160 | 936.931 | 4945.61 | 0.0331211 | 5.85507 | 23.7561 | 4.81386 | 0.00479882 | 5.43006e-05 | 9.50261e-06 | 2(Loss) | true |
| glaze | 784.324 | 0.0587685 | 1387.62ms | 4604 | 1280 | 13854.1 | 5598.09 | 0.0100192 | 6.60602 | 28.5215 | 5.83514 | 0.00739456 | 5.17553e-05 | 1.84961e-05 | 3(Loss) | true |
| simdjson (ondemand) | 680.965 | 0.0436022 | 1482.23ms | 4604 | 1280 | 10116.9 | 6447.78 | 0.00893071 | 7.60585 | 32.777 | 5.90486 | 0.00597341 | 5.9561e-05 | 1.51024e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1336.09 | 0.0431301 | 1055.38ms | 4604 | 4890 | 9823.58 | 3286.25 | 0.382116 | 3.91969 | 9.40421 | 0.65921 | 0.000665244 | 8.18618e-05 | 3.18031e-05 | 1(Win) | true |
| glaze | 797.163 | 0.0589043 | 1274.68ms | 4604 | 2560 | 26947 | 5507.93 | 0.0405855 | 6.51752 | 12.2769 | 1.00521 | 0.000538594 | 9.53654e-05 | 4.38647e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1364.49 | 0.219352 | 1048.29ms | 4604 | 30 | 1494.63 | 3217.83 | 0.0881286 | 3.82703 | 9.28041 | 0.629887 | 0.000506806 | 0.000144802 | 7.96409e-05 | 1(Win) | true |
| glaze | 862.755 | 0.139913 | 1234.07ms | 4604 | 2560 | 129793 | 5089.18 | 0.0578635 | 6.00275 | 11.72 | 0.886187 | 0.000564302 | 0.000100032 | 3.90286e-05 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3433.42 | 0.161761 | 1420.91ms | 24579 | 160 | 19513.8 | 6827.12 | 0.055538 | 1.50698 | 6.2876 | 1.12641 | 0.00134312 | 9.15416e-06 | 1.77997e-06 | 1(Win) | true |
| jsonifier | 3037 | 0.0424947 | 1511ms | 24579 | 4890 | 52603.9 | 7718.27 | 0.0448706 | 1.69956 | 6.64616 | 1.50283 | 0.00202728 | 3.92458e-05 | 2.27304e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2798.29 | 0.0884489 | 1572.99ms | 24579 | 80 | 4391.54 | 8376.66 | 0.00253687 | 1.85026 | 7.75422 | 1.28585 | 0.00160147 | 3.9668e-05 | 1.42398e-05 | 3(Loss) | true |
| glaze | 2336.65 | 0.0371208 | 1736.01ms | 24579 | 2560 | 35499.1 | 10031.6 | 0.118184 | 2.20484 | 9.45437 | 1.91957 | 0.0042632 | 4.63111e-05 | 2.71446e-05 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3980.64 | 0.0453589 | 1411.27ms | 24579 | 2560 | 18263.7 | 5888.6 | 0.31292 | 1.29398 | 5.48948 | 0.943977 | 0.00114861 | 3.25322e-05 | 2.0136e-05 | 1(Win) | true |
| jsonifier | 3500.03 | 0.163428 | 1496.42ms | 24579 | 320 | 38334.1 | 6697.18 | 0.0533056 | 1.4698 | 5.83331 | 1.31694 | 0.00184889 | 6.75119e-05 | 5.1365e-05 | 2(Loss) | true |
| simdjson (ondemand) | 3165.74 | 0.0358734 | 1577.94ms | 24579 | 4890 | 34501.1 | 7404.4 | 0.00109234 | 1.63222 | 7.1435 | 1.146 | 0.000914958 | 3.00271e-05 | 1.65736e-05 | 3(Loss) | true |
| glaze | 2661.57 | 0.118867 | 1731.1ms | 24579 | 30 | 3287.76 | 8806.97 | 0.178328 | 1.98088 | 8.65214 | 1.73429 | 0.00414988 | 9.4932e-06 | 4.06851e-06 | 4(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7196.63 | 0.0471969 | 1055.24ms | 24579 | 4890 | 11556 | 3257.13 | 0.125119 | 0.721533 | 1.90663 | 0.122991 | 0.000121381 | 1.9835e-05 | 9.0772e-06 | 1(Win) | true |
| glaze | 3950.57 | 0.172196 | 1326.91ms | 24579 | 1280 | 133618 | 5933.42 | 0.000421344 | 1.31391 | 3.54844 | 0.470646 | 0.000243698 | 1.78951e-05 | 8.35952e-06 | 2(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7428.94 | 0.0720578 | 1048.57ms | 24579 | 2560 | 13233.5 | 3155.28 | 0.077674 | 0.69851 | 1.88637 | 0.118353 | 0.000105098 | 1.20466e-05 | 5.53064e-06 | 1(Win) | true |
| glaze | 4285.42 | 0.176644 | 1279.08ms | 24579 | 1280 | 119495 | 5469.79 | 0.103902 | 1.20865 | 3.40327 | 0.43765 | 0.000236864 | 3.23574e-05 | 1.66237e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 923.41 | 0.0542535 | 1205.17ms | 4604 | 2560 | 17036.4 | 4754.89 | 0.0806645 | 5.61933 | 22.5756 | 4.96786 | 0.00584325 | 0.000128709 | 6.99969e-05 | 1(Win) | true |
| jsonifier (two-stage) | 791.306 | 0.0522088 | 1285.6ms | 4604 | 160 | 1342.73 | 5548.69 | 0.0113753 | 6.55885 | 27.1127 | 5.61924 | 0.00591741 | 6.78758e-05 | 2.17202e-05 | 2(Loss) | true |
| glaze | 676.716 | 0.0392674 | 1381.75ms | 4604 | 4890 | 31741.8 | 6488.27 | 0.0552352 | 7.63594 | 32.3705 | 6.72796 | 0.00950916 | 0.000118151 | 6.12076e-05 | 3(Loss) | true |
| simdjson (ondemand) | 594.611 | 0.0347261 | 1474.35ms | 4604 | 4890 | 32153.3 | 7384.18 | 0.0319695 | 8.64792 | 35.0037 | 6.42148 | 0.0102869 | 0.000155195 | 8.52819e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1136.19 | 0.0448183 | 1206.6ms | 4604 | 2560 | 7679.27 | 3864.42 | 0.0469307 | 4.56608 | 18.4033 | 4.01032 | 0.00552305 | 8.13661e-05 | 3.97922e-05 | 1(Win) | true |
| jsonifier (two-stage) | 971.642 | 0.0702709 | 1276.3ms | 4604 | 80 | 806.677 | 4518.86 | 0.0462166 | 5.35245 | 22.8506 | 4.64422 | 0.00443907 | 8.14509e-05 | 5.70156e-05 | 2(Loss) | true |
| glaze | 787.382 | 0.0456153 | 1374.28ms | 4604 | 4890 | 31639.5 | 5576.35 | 0.154837 | 6.54405 | 28.1664 | 5.7576 | 0.00821776 | 9.8474e-05 | 5.05029e-05 | 3(Loss) | true |
| simdjson (ondemand) | 673.502 | 0.133877 | 1477.95ms | 4604 | 320 | 24375.4 | 6519.23 | 0.140888 | 7.61433 | 32.6952 | 5.88305 | 0.00625136 | 3.59742e-05 | 1.08601e-05 | 4(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1421.54 | 0.23118 | 1035.84ms | 4604 | 40 | 2039.45 | 3088.7 | 0.155164 | 3.60529 | 9.39553 | 0.660947 | 0.000494136 | 0.000233493 | 0.000179192 | 1(Win) | true |
| glaze | 829.498 | 0.0506869 | 1257.29ms | 4604 | 2560 | 18427.7 | 5293.22 | 0.0664616 | 6.2514 | 12.2359 | 1.00413 | 0.000659922 | 0.000153484 | 8.69658e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1469.37 | 0.0759927 | 1030.4ms | 4604 | 4890 | 25215.1 | 2988.16 | 0.0938607 | 3.55568 | 9.27129 | 0.631625 | 0.000509204 | 8.6037e-05 | 3.83769e-05 | 1(Win) | true |
| glaze | 838.729 | 0.107965 | 1252.29ms | 4604 | 4890 | 156206 | 5234.96 | 0.0111758 | 6.18842 | 11.7163 | 0.887056 | 0.000731159 | 0.000157061 | 6.76037e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3672.28 | 0.0416227 | 1376.63ms | 24579 | 2560 | 18069.9 | 6383.05 | 0.0253904 | 1.40419 | 6.1226 | 1.09573 | 0.00107065 | 4.68674e-05 | 2.88133e-05 | 1(Win) | true |
| jsonifier | 3224.54 | 0.102603 | 1465.22ms | 24579 | 40 | 2225.21 | 7269.38 | 0.0828133 | 1.60642 | 6.36458 | 1.45746 | 0.00199967 | 1.42398e-05 | 7.1199e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2815.19 | 0.0865666 | 1581.47ms | 24579 | 80 | 4156.26 | 8326.38 | 0.0111105 | 1.83933 | 7.52443 | 1.23422 | 0.00193102 | 1.57655e-05 | 8.13703e-06 | 3(Loss) | true |
| glaze | 2401.38 | 0.0890347 | 1718.35ms | 24579 | 320 | 24170 | 9761.21 | 0.241362 | 2.14755 | 9.22731 | 1.86777 | 0.00406979 | 6.86562e-06 | 2.03426e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4341.45 | 0.125735 | 1371.4ms | 24579 | 30 | 1382.58 | 5399.2 | 0.0611575 | 1.19602 | 5.32865 | 0.913992 | 0.00106595 | 4.88222e-05 | 1.89864e-05 | 1(Win) | true |
| jsonifier | 3720.09 | 0.0747525 | 1467.17ms | 24579 | 640 | 14198.9 | 6301.02 | 0.521168 | 1.39269 | 5.57085 | 1.27568 | 0.00173109 | 1.14427e-05 | 4.57708e-06 | 2(Loss) | true |
| simdjson (ondemand) | 3131.46 | 0.030554 | 1577.73ms | 24579 | 4890 | 25578.8 | 7485.45 | 0.0382989 | 1.64093 | 7.14729 | 1.14574 | 0.000988125 | 2.35375e-05 | 1.28379e-05 | 3(Loss) | true |
| glaze | 2647.77 | 0.0755333 | 1714.22ms | 24579 | 1280 | 57234 | 8852.86 | 0.0962743 | 1.94414 | 8.46521 | 1.6933 | 0.00391397 | 1.7164e-05 | 9.50379e-06 | 4(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7914.98 | 0.0554367 | 1024.94ms | 24579 | 4890 | 13180.6 | 2961.52 | 0.208352 | 0.657445 | 1.90569 | 0.123032 | 0.00010168 | 1.84456e-05 | 8.82759e-06 | 1(Win) | true |
| glaze | 3893.51 | 0.0660254 | 1337.81ms | 24579 | 4890 | 77264.2 | 6020.37 | 0.244499 | 1.3253 | 3.55523 | 0.471378 | 0.000329982 | 2.90703e-05 | 1.57832e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8056.64 | 0.115892 | 1021.83ms | 24579 | 640 | 7276.29 | 2909.45 | 0.0259325 | 0.647589 | 1.88547 | 0.118394 | 0.000102349 | 1.53205e-05 | 7.50132e-06 | 1(Win) | true |
| glaze | 4122.02 | 0.0786408 | 1305.6ms | 24579 | 4890 | 97794.5 | 5686.63 | 0.0738202 | 1.24737 | 3.41031 | 0.437813 | 0.000316803 | 2.50434e-05 | 1.31623e-05 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1017.52 | 0.183735 | 831.753ms | 1181 | 160 | 661.781 | 1106.89 | 0.0829337 | 5.24329 | 20.8611 | 4.28196 | 0.00635584 | 7.93819e-05 | 3.17528e-05 | 1(Win) | true |
| glaze | 883.246 | 0.0657724 | 848.754ms | 1181 | 2560 | 1800.79 | 1275.17 | 0.119541 | 5.98159 | 24.2227 | 4.93988 | 0.00354043 | 0.000105843 | 4.39908e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 865.708 | 0.0822384 | 856.297ms | 1181 | 2560 | 2930.53 | 1301 | 0.19063 | 6.11494 | 24.3141 | 4.69094 | 0.00451749 | 0.000238807 | 0.000125026 | 3(Loss) | true |
| simdjson (ondemand) | 739.627 | 0.0966856 | 883.861ms | 1181 | 320 | 693.664 | 1522.78 | 0.376178 | 7.03745 | 29.3251 | 5.11854 | 0.00352985 | 5.82134e-05 | 5.29213e-06 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1251.77 | 0.227021 | 826.011ms | 1181 | 2560 | 10681.3 | 899.76 | 0.0301205 | 4.32826 | 17.6207 | 3.53176 | 0.00423866 | 0.000105181 | 6.71438e-05 | 1(Win) | true |
| glaze | 1198.04 | 0.154165 | 829.511ms | 1181 | 320 | 672.175 | 940.112 | 0.271833 | 4.48434 | 17.9822 | 3.52752 | 0.00286039 | 7.40898e-05 | 1.58764e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1033.73 | 0.0721188 | 850.776ms | 1181 | 4890 | 3019.2 | 1089.54 | 0.118704 | 5.14982 | 21.0728 | 3.94073 | 0.00252619 | 0.000137487 | 6.06051e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1015.09 | 0.0586483 | 857.823ms | 1181 | 640 | 271.009 | 1109.55 | 0.0680638 | 5.2541 | 22.6342 | 3.62743 | 0.00185886 | 6.74746e-05 | 2.38146e-05 | 4(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1276.53 | 0.042357 | 814.276ms | 1181 | 640 | 89.3853 | 882.303 | 0.154664 | 4.21888 | 8.29975 | 0.883997 | 0.00084674 | 2.38146e-05 | 0 | 1(Win) | true |
| glaze | 964.475 | 0.249764 | 839.062ms | 1181 | 40 | 340.281 | 1167.78 | 0.124726 | 5.53743 | 10.5089 | 0.905165 | 0.00192633 | 0.000211685 | 0 | 2(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1331.85 | 0.0323129 | 806.16ms | 1181 | 320 | 23.894 | 845.656 | 0.00739126 | 4.05167 | 7.87045 | 0.784928 | 0.00084674 | 6.61516e-05 | 2.64606e-06 | 1(Win) | true |
| glaze | 985.186 | 0.144193 | 840.363ms | 1181 | 80 | 217.392 | 1143.22 | 0.0568244 | 5.41758 | 9.98984 | 0.788315 | 0.00151355 | 4.2337e-05 | 2.11685e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1723.03 | 0.0749386 | 863.739ms | 2496 | 2560 | 2743.82 | 1381.5 | 0.0660382 | 3.07865 | 12.4816 | 2.30008 | 0.00204734 | 6.60432e-05 | 2.80136e-05 | 1(Win) | true |
| glaze | 1583.04 | 0.0556836 | 867.78ms | 2496 | 4890 | 3428.24 | 1503.67 | 0.258292 | 3.33353 | 14.8429 | 3.09055 | 0.00201533 | 8.16849e-05 | 4.68643e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1539.61 | 0.141541 | 883.838ms | 2496 | 160 | 766.219 | 1546.09 | 0.0226429 | 3.43333 | 14.4419 | 2.42628 | 0.00183043 | 3.00481e-05 | 7.51202e-06 | 3(Loss) | true |
| jsonifier | 1532.75 | 0.0666592 | 880.418ms | 2496 | 4890 | 5240.54 | 1553.01 | 0.159431 | 3.41522 | 13.6326 | 2.92428 | 0.00258909 | 0.00010692 | 5.93997e-05 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 2058.28 | 0.0623592 | 849.521ms | 2496 | 4890 | 2543.25 | 1156.48 | 0.0452534 | 2.60338 | 11.8978 | 2.42228 | 0.00187064 | 4.17846e-05 | 2.122e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2025.97 | 0.0825312 | 857.712ms | 2496 | 4890 | 4597.98 | 1174.93 | 0.275461 | 2.63628 | 10.9479 | 1.94511 | 0.0015117 | 8.43886e-05 | 2.58082e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2020.39 | 0.10776 | 858.264ms | 2496 | 2560 | 4126.42 | 1178.18 | 0.169111 | 2.62306 | 11.3774 | 1.74079 | 0.000846511 | 7.41812e-05 | 3.50561e-05 | 3(Loss) | true |
| jsonifier | 1772.17 | 0.0717213 | 873.538ms | 2496 | 4890 | 4538.2 | 1343.2 | 0.00201891 | 2.98861 | 12.0994 | 2.56931 | 0.00217968 | 6.45614e-05 | 2.75287e-05 | 4(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4276.87 | 0.0999589 | 781.434ms | 2496 | 1280 | 396.178 | 556.569 | 0.177742 | 1.28732 | 3.96595 | 0.403045 | 0.000405023 | 6.54172e-05 | 3.16131e-05 | 1(Win) | true |
| glaze | 1627.48 | 0.122057 | 875.7ms | 2507 | 320 | 1028.86 | 1469.06 | 0.0134032 | 3.25337 | 7.02553 | 0.885919 | 0.00181492 | 4.11348e-05 | 2.61767e-05 | 2(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4481.28 | 0.0628477 | 780.458ms | 2496 | 640 | 71.3255 | 531.181 | 0.139236 | 1.23561 | 3.83293 | 0.371795 | 0.000466371 | 1.9406e-05 | 6.26002e-06 | 1(Win) | true |
| glaze | 1740.55 | 0.0521161 | 863.461ms | 2507 | 4890 | 2506.03 | 1373.62 | 0.0742085 | 3.06078 | 6.29318 | 0.724771 | 0.00205747 | 6.20757e-05 | 3.30363e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2293.07 | 0.0634149 | 947.234ms | 4926 | 320 | 540.114 | 2048.69 | 0.138768 | 2.29112 | 10.242 | 1.78766 | 0.00417301 | 6.97828e-05 | 2.79131e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1806 | 0.101723 | 988.925ms | 4926 | 1280 | 8961.97 | 2601.21 | 0.0798342 | 2.89123 | 12.8985 | 2.19874 | 0.00414605 | 3.505e-05 | 5.8681e-06 | 2(Loss) | true |
| glaze | 1429.88 | 0.147119 | 1060.75ms | 4926 | 80 | 1869.04 | 3285.45 | 0.137155 | 3.64621 | 15.4464 | 3.02213 | 0.00266951 | 8.12018e-05 | 3.80633e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1202 | 0.0403666 | 1119.95ms | 4926 | 4890 | 12171.3 | 3908.33 | 0.0296906 | 4.33292 | 16.9844 | 2.95737 | 0.00407777 | 0.000112005 | 5.41345e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2860.33 | 0.0622213 | 933.557ms | 4926 | 320 | 334.184 | 1642.4 | 0.345196 | 1.84648 | 8.55867 | 1.3987 | 0.00364139 | 2.2838e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 2165.39 | 0.0929821 | 988.644ms | 4926 | 160 | 651.082 | 2169.49 | 0.0446333 | 2.42412 | 11.215 | 1.80978 | 0.00394971 | 5.96326e-05 | 1.26878e-05 | 2(Loss) | true |
| glaze | 1812.63 | 0.149253 | 1026.5ms | 4926 | 640 | 9576.26 | 2591.7 | 0.103502 | 2.88048 | 12.7471 | 2.42712 | 0.00233899 | 2.37896e-05 | 2.85475e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1450.11 | 0.063641 | 1086.77ms | 4926 | 2560 | 10881.7 | 3239.61 | 0.0494976 | 3.58568 | 14.6354 | 2.43687 | 0.00453897 | 3.56844e-05 | 1.15776e-05 | 4(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12607.4 | 0.117527 | 762.237ms | 4926 | 320 | 61.3707 | 372.622 | 0.2868 | 0.451825 | 1.89911 | 0.331912 | 0.000203004 | 3.04507e-05 | 1.90317e-06 | 1(Win) | true |
| glaze | 3566.12 | 0.165778 | 854.866ms | 4926 | 4890 | 23321.7 | 1317.34 | 0.173152 | 1.49037 | 6.05522 | 0.98782 | 0.000400363 | 5.96974e-05 | 2.37461e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14029.5 | 0.0817394 | 755.181ms | 4926 | 1280 | 95.8914 | 334.852 | 0.678139 | 0.409957 | 1.7838 | 0.305116 | 0.000203004 | 3.07679e-05 | 9.83303e-06 | 1(Win) | true |
| glaze | 3961.32 | 0.178416 | 843.871ms | 4926 | 4890 | 21892.2 | 1185.92 | 0.0798794 | 1.33847 | 5.49858 | 0.867235 | 0.000265193 | 3.4955e-05 | 1.53187e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3215.48 | 0.0408345 | 1007.04ms | 9463 | 4890 | 6422.9 | 2806.62 | 0.0887402 | 1.62746 | 7.36236 | 1.16718 | 0.00225867 | 3.40363e-05 | 1.40035e-05 | 1(Win) | true |
| jsonifier | 2618.72 | 0.100019 | 1071.86ms | 9463 | 640 | 7603.68 | 3446.2 | 0.181643 | 1.9843 | 7.95879 | 1.57656 | 0.0027984 | 1.68419e-05 | 3.63257e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2169.86 | 0.0776094 | 1143.21ms | 9463 | 4890 | 50948.7 | 4159.09 | 0.0751897 | 2.38646 | 9.44331 | 1.56832 | 0.00218319 | 5.85641e-05 | 2.52841e-05 | 3(Loss) | true |
| glaze | 2092.88 | 0.0676391 | 1162.33ms | 9463 | 1280 | 10888.7 | 4312.05 | 0.227692 | 2.47339 | 10.8657 | 2.11656 | 0.00258267 | 2.55931e-05 | 7.10002e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3809.43 | 0.051772 | 1002.97ms | 9463 | 2560 | 3850.94 | 2369.02 | 0.0881049 | 1.37777 | 6.486 | 0.964705 | 0.00211878 | 1.7296e-05 | 4.49943e-06 | 1(Win) | true |
| jsonifier | 3002.54 | 0.0855158 | 1081.92ms | 9463 | 1280 | 8456.36 | 3005.66 | 0.0806941 | 1.7402 | 7.08232 | 1.37398 | 0.00268942 | 1.68419e-05 | 3.79769e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2651.55 | 0.0879601 | 1102.35ms | 9463 | 320 | 2868 | 3403.53 | 0.0251514 | 1.97063 | 8.19751 | 1.29272 | 0.00225384 | 2.17954e-05 | 9.90701e-06 | 3(Loss) | true |
| glaze | 2498.08 | 0.078916 | 1133.3ms | 9463 | 1280 | 10403.7 | 3612.63 | 0.0190701 | 2.08441 | 9.47596 | 1.80968 | 0.0028462 | 1.51082e-05 | 2.39419e-06 | 4(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19997.5 | 0.214251 | 783.386ms | 9463 | 80 | 74.7897 | 451.288 | 0.180365 | 0.279428 | 1.1154 | 0.173729 | 0.000105675 | 1.58512e-05 | 0 | 1(Win) | true |
| glaze | 4045 | 0.254756 | 949.762ms | 9463 | 640 | 20675.1 | 2231.05 | 0.0759747 | 1.29904 | 4.76223 | 0.875093 | 0.000264022 | 2.27861e-05 | 7.76049e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23933.2 | 0.296793 | 753.378ms | 9463 | 80 | 100.197 | 377.075 | 0.0663438 | 0.24174 | 1.05199 | 0.158829 | 0.000105675 | 1.71721e-05 | 2.64187e-06 | 1(Win) | true |
| glaze | 4745.04 | 0.096136 | 913.91ms | 9463 | 2560 | 8558.34 | 1901.9 | 0.100395 | 1.10768 | 4.44933 | 0.803339 | 0.000268851 | 2.5139e-05 | 9.24654e-06 | 2(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 5312.98 | 0.195543 | 767.871ms | 2821 | 30 | 29.4126 | 506.367 | 0.0263383 | 1.04711 | 3.96172 | 0.531372 | 0.000708968 | 0 | 0 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 5287.89 | 0.208419 | 770.803ms | 2821 | 160 | 179.902 | 508.769 | 0.974405 | 1.07049 | 3.96172 | 0.531372 | 0.000928306 | 5.98192e-05 | 1.55087e-05 | 1(Tie) | true |
| simdjson (ondemand) | 5265.45 | 0.255557 | 775.353ms | 2821 | 4890 | 8337.22 | 510.938 | 0.360025 | 1.05418 | 4.20489 | 0.470755 | 0.000365213 | 3.58834e-05 | 1.7253e-05 | 3(Loss) | true |
| glaze | 3242.96 | 0.407008 | 800.661ms | 2821 | 1280 | 14592.8 | 829.587 | 0.186773 | 1.67304 | 6.52038 | 1.20489 | 0.000654411 | 1.4124e-05 | 3.32329e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5647.86 | 0.386942 | 768.978ms | 2821 | 2560 | 8697.02 | 476.342 | 0.917616 | 1.00161 | 3.80964 | 0.496278 | 0.000698583 | 3.15713e-05 | 4.70799e-06 | 1(Win) | true |
| jsonifier | 5570.59 | 0.248998 | 770.501ms | 2821 | 40 | 57.8436 | 482.95 | 0.127525 | 1.00173 | 3.80964 | 0.496278 | 0.000726693 | 5.31726e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 5409.03 | 0.172878 | 774.341ms | 2821 | 40 | 29.5737 | 497.375 | 0.0955927 | 1.02813 | 4.12159 | 0.451967 | 0.000372208 | 2.65863e-05 | 1.77242e-05 | 3(Loss) | true |
| glaze | 3269.09 | 0.761875 | 803.349ms | 2821 | 2560 | 100638 | 822.956 | 0.197897 | 1.64283 | 6.43885 | 1.18646 | 0.000547512 | 2.50631e-05 | 9.41599e-06 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 6900.42 | 0.384721 | 782.294ms | 4147 | 80 | 388.956 | 573.138 | 0.48433 | 0.820207 | 3.19773 | 0.379069 | 0.000491319 | 7.23415e-05 | 5.42561e-05 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 6822.28 | 0.35979 | 775.257ms | 4147 | 4890 | 21272.3 | 579.702 | 0.353405 | 0.806541 | 3.26356 | 0.338799 | 0.000244886 | 1.91333e-05 | 5.17781e-06 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 6780.63 | 0.136287 | 781.866ms | 4147 | 80 | 50.5505 | 583.263 | 0.130559 | 0.812159 | 3.19773 | 0.379069 | 0.000482276 | 2.10996e-05 | 0 | 2(Tie) | true |
| glaze | 4031.13 | 0.0739608 | 825.054ms | 4147 | 160 | 84.2439 | 981.087 | 0.33903 | 1.33042 | 5.59151 | 1.05329 | 0.000479262 | 3.01423e-06 | 0 | 4(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7282.73 | 0.209731 | 781.578ms | 4147 | 2560 | 3320.83 | 543.05 | 0.10491 | 0.760608 | 3.09429 | 0.355197 | 0.000276084 | 3.52288e-05 | 1.43176e-05 | 1(Win) | true |
| jsonifier (two-stage) | 7217.89 | 0.0599767 | 777.571ms | 4147 | 2560 | 276.472 | 547.928 | 0.547356 | 0.771258 | 3.09429 | 0.355197 | 0.000395335 | 3.69243e-05 | 1.25279e-05 | 2(Loss) | true |
| simdjson (ondemand) | 7014.23 | 0.053466 | 774.388ms | 4147 | 2560 | 232.65 | 563.838 | 0.72876 | 0.785923 | 3.20738 | 0.326019 | 0.000241232 | 2.0817e-05 | 9.98463e-06 | 3(Loss) | true |
| glaze | 4065.96 | 0.0852724 | 813.336ms | 4147 | 1280 | 880.581 | 972.683 | 0.00706758 | 1.3193 | 5.53581 | 1.04075 | 0.000475118 | 8.85429e-06 | 3.57939e-06 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2654.85 | 0.235351 | 825.58ms | 2821 | 4890 | 27814.3 | 1013.36 | 0.220531 | 2.02505 | 6.42396 | 1.11804 | 0.00213372 | 9.22094e-05 | 3.58834e-05 | 1(Win) | true |
| glaze | 2553.29 | 0.0742465 | 822.897ms | 2821 | 1280 | 783.373 | 1053.67 | 0.135503 | 2.09451 | 8.49061 | 1.46118 | 0.000837469 | 0.000124069 | 8.83441e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2371.68 | 0.19638 | 837.017ms | 2821 | 80 | 396.99 | 1134.35 | 0.15009 | 2.29036 | 8.22581 | 1.28111 | 0.000708968 | 7.08968e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2323.9 | 0.0464726 | 837.917ms | 2821 | 4890 | 1415.38 | 1157.67 | 0.317979 | 2.30107 | 8.84651 | 1.23999 | 0.00036601 | 8.26405e-05 | 3.39986e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2986.43 | 0.240311 | 818.869ms | 2821 | 4890 | 22917 | 900.848 | 0.216794 | 1.81633 | 5.90145 | 0.985112 | 0.00177757 | 6.79247e-05 | 2.65319e-05 | 1(Win) | true |
| glaze | 2750.92 | 0.114326 | 824.441ms | 2821 | 1280 | 1600.12 | 977.97 | 0.1678 | 1.95252 | 7.99504 | 1.33676 | 0.000712292 | 6.89583e-05 | 3.37868e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2631.9 | 0.201183 | 826.369ms | 2821 | 1280 | 5413.25 | 1022.19 | 0.0736993 | 2.04329 | 7.51897 | 1.11237 | 0.000361131 | 4.70799e-05 | 6.64658e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2460.24 | 0.096431 | 837.141ms | 2821 | 1280 | 1423.3 | 1093.52 | 0.319047 | 2.17177 | 8.44559 | 1.14002 | 0.00070703 | 4.37566e-05 | 2.21553e-05 | 4(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8483.7 | 0.0997063 | 754.745ms | 2821 | 1280 | 127.965 | 317.116 | 0.14809 | 0.685455 | 1.55087 | 0.243531 | 0.000354484 | 3.37868e-05 | 1.4124e-05 | 1(Win) | true |
| glaze | 4415.06 | 0.683986 | 783.404ms | 2819 | 1280 | 22203.5 | 608.918 | 0.1878 | 1.2567 | 2.98723 | 0.461511 | 0.000358339 | 5.0439e-05 | 2.10624e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9666.09 | 0.237 | 751.354ms | 2821 | 40 | 17.4045 | 278.325 | 0.277678 | 0.621854 | 1.43353 | 0.215881 | 0.000363346 | 7.08968e-05 | 1.77242e-05 | 1(Win) | true |
| glaze | 5238.67 | 0.224782 | 773.83ms | 2819 | 2560 | 3406.51 | 513.185 | 0.803819 | 1.07094 | 2.53601 | 0.367152 | 0.00035626 | 3.4365e-05 | 1.03926e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3160.9 | 0.0832865 | 851.413ms | 4147 | 4890 | 5310.13 | 1251.19 | 0.333706 | 1.67978 | 6.42103 | 0.86207 | 0.000504861 | 7.73713e-05 | 3.68364e-05 | 1(Win) | true |
| jsonifier (two-stage) | 3148.29 | 0.0969456 | 846.399ms | 4147 | 4890 | 7252.45 | 1256.2 | 0.0642167 | 1.68388 | 6.07379 | 0.877984 | 0.000511026 | 5.19754e-05 | 1.65197e-05 | 2(Loss) | true |
| glaze | 2895.15 | 0.0605625 | 861.247ms | 4147 | 4890 | 3346.89 | 1366.04 | 0.0869596 | 1.83252 | 7.67012 | 1.34555 | 0.000367674 | 5.17781e-05 | 2.37686e-05 | 3(Loss) | true |
| jsonifier | 2366.85 | 0.0554817 | 901.159ms | 4147 | 80 | 68.757 | 1670.95 | 0.338478 | 2.22865 | 6.10707 | 1.17458 | 0.000732457 | 6.32988e-05 | 0 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3596.07 | 0.0741571 | 841.468ms | 4147 | 160 | 106.424 | 1099.78 | 0.0482817 | 1.51132 | 5.65397 | 0.775259 | 0.000241138 | 5.12419e-05 | 3.01423e-06 | 1(Win) | true |
| simdjson (ondemand) | 3408.13 | 0.0805873 | 846.502ms | 4147 | 2560 | 2238.77 | 1160.43 | 0.150311 | 1.56548 | 6.14878 | 0.794068 | 0.000282113 | 6.2451e-05 | 2.27009e-05 | 2(Loss) | true |
| glaze | 3092.15 | 0.101801 | 861.203ms | 4147 | 2560 | 4339.98 | 1279.01 | 0.0957162 | 1.71816 | 7.272 | 1.24885 | 0.000454866 | 2.84468e-05 | 1.02672e-05 | 3(Loss) | true |
| jsonifier | 2606.3 | 0.157554 | 888.825ms | 4147 | 4890 | 27950.2 | 1517.43 | 0.667062 | 2.0299 | 5.7509 | 1.08416 | 0.000488292 | 7.62865e-05 | 3.7083e-05 | 4(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11175.2 | 0.237017 | 761.107ms | 4147 | 40 | 28.1436 | 353.9 | 0.103715 | 0.517145 | 1.11671 | 0.167591 | 0.000241138 | 2.41138e-05 | 0 | 1(Win) | true |
| glaze | 4111.7 | 0.186443 | 823.854ms | 4145 | 4890 | 15711.1 | 961.397 | 0.131009 | 1.30314 | 3.35995 | 0.610133 | 0.000242439 | 6.31505e-05 | 2.26947e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12461.6 | 0.554981 | 752.818ms | 4147 | 30 | 93.0678 | 317.367 | 0.168332 | 0.464874 | 1.03497 | 0.1483 | 0.000241138 | 6.43035e-05 | 0 | 1(Win) | true |
| glaze | 4743.84 | 0.283026 | 809.396ms | 4145 | 640 | 3559.79 | 833.288 | 0.420282 | 1.14011 | 2.78191 | 0.479855 | 0.000242008 | 1.77171e-05 | 4.14656e-06 | 2(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3590.45 | 0.240478 | 6810.58ms | 466906 | 640 | 5.69234e+07 | 124017 | 0.182146 | 1.42532 | 6.2505 | 0.830776 | 0.00420015 | 0.0029356 | 3.81568e-05 | 1(Win) | true |
| glaze | 2910.79 | 0.0306559 | 8240.04ms | 466906 | 1280 | 2.81498e+06 | 152974 | 0.134784 | 1.75451 | 7.42684 | 1.5035 | 0.00243986 | 0.00149391 | 4.42156e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1329.13 | 0.493001 | 8822.81ms | 466906 | 1280 | 3.49163e+09 | 335013 | 0.00311775 | 3.80545 | 15.023 | 2.4314 | 0.00799458 | 0.0921703 | 0.000278052 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3583.02 | 0.172129 | 6848.21ms | 466906 | 30 | 1.37274e+06 | 124274 | 0.22579 | 1.41596 | 6.24936 | 0.830523 | 0.00411617 | 0.00273417 | 9.42374e-06 | 1(Win) | true |
| glaze | 2872.21 | 0.20096 | 8299.43ms | 466906 | 1280 | 1.24238e+08 | 155029 | 0.253346 | 1.78168 | 7.42572 | 1.50325 | 0.00249564 | 0.0013695 | 4.06198e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1330.8 | 0.537588 | 8779.62ms | 466906 | 1280 | 4.14139e+09 | 334594 | 0.132511 | 3.80081 | 15.0237 | 2.43158 | 0.00813137 | 0.0945505 | 0.000377405 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4449.61 | 0.245284 | 8060.46ms | 699405 | 2560 | 3.46093e+08 | 149902 | 0.0123127 | 1.14174 | 4.0221 | 0.649008 | 0.00527824 | 0.00173277 | 1.87146e-05 | 1(Win) | true |
| glaze | 4005.18 | 0.0895274 | 8905.2ms | 699405 | 1280 | 2.84534e+07 | 166535 | 0.0864118 | 1.27685 | 4.84003 | 1.13546 | 0.00197485 | 0.00368599 | 6.75105e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1477.83 | 0.347353 | 6461ms | 767297 | 160 | 4.73305e+08 | 495153 | 0.455181 | 3.41929 | 13.9013 | 2.23378 | 0.00972004 | 0.0730998 | 0.000284717 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4444.63 | 0.43896 | 8097.12ms | 699405 | 640 | 2.77725e+08 | 150070 | 0.250914 | 1.14415 | 4.02129 | 0.648827 | 0.00530773 | 0.00135372 | 1.66816e-05 | 1(Win) | true |
| glaze | 4017.07 | 0.0658601 | 8951ms | 699405 | 160 | 1.91339e+06 | 166043 | 0.0599599 | 1.27781 | 4.83925 | 1.13529 | 0.00194091 | 0.00355341 | 4.04004e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1468.92 | 0.30902 | 6538.38ms | 767297 | 160 | 3.79164e+08 | 498157 | 0.553549 | 3.44648 | 13.9013 | 2.23379 | 0.00954152 | 0.0904503 | 0.000268214 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3584.05 | 0.0572475 | 8989.72ms | 631514 | 2560 | 2.36903e+07 | 168038 | 0.198231 | 1.40967 | 7.01636 | 1.20741 | 0.00313765 | 1.38346e-05 | 1.23581e-05 | 1(Win) | true |
| glaze | 2675.24 | 0.178528 | 5927.45ms | 631514 | 30 | 4.8459e+06 | 225124 | 0.141691 | 1.90077 | 8.57774 | 1.52634 | 0.00229332 | 1.0715e-05 | 9.39541e-06 | 2(Loss) | true |
