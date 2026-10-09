# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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
| simdjson (reflection) | `haswell` |
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

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

`simdjson (ondemand)` results include this harness's field-mapping layer (per-field lookups, string copies and `unescaped_key()` for maps, in `include/common.hpp`), since materializing into the shared test structs is what these tests measure; hand-tuned glue written by a simdjson specialist could perform differently.

`Results.csv` additionally carries `jsonifier (combined)` and `simdjson (combined)` summary rows. Each is a best-of-variants tally: per test, only the better-ranked of that library's two variants counts, and a test counts as a win when that position is 1 and no other library shares it, so two variants of the same library tying for first count as one win. These rows are not independent results and should not be summed with the per-variant rows.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ae63a25](https://github.com/nihilai-collective/benchmarksuite/commit/ae63a25).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1827.05 | 0.2273 | 759.736ms | 905 | 160 | 184.465 | 472.387 | 0.111014 | 3.05077 | 14.7127 | 2.73039 | 0.00140193 | 4.14365e-05 | 6.90608e-06 | 1(Win) | true |
| glaze | 792.585 | 0.0722379 | 832.322ms | 905 | 80 | 49.5024 | 1088.94 | 0.0126286 | 6.74214 | 18.6398 | 3.27514 | 0.00251381 | 9.66851e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 275.293 | 0.0494542 | 1031.43ms | 905 | 640 | 1538.48 | 3135.11 | 0.0907389 | 18.9483 | 55.7846 | 8.35913 | 0.00650207 | 0.000132942 | 4.14365e-05 | 3(Loss) | true |
| simdjson (ondemand) | 183.559 | 0.126852 | 1186.44ms | 905 | 320 | 11383.8 | 4701.88 | 0.0508698 | 28.2771 | 103.829 | 10.5669 | 0.0430007 | 6.56077e-05 | 1.38122e-05 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1943.97 | 0.0844515 | 756.3ms | 905 | 4890 | 687.451 | 443.975 | 0.0142249 | 2.88168 | 14.147 | 2.61768 | 0.002649 | 0.000136257 | 3.59285e-05 | 1(Win) | true |
| glaze | 739.456 | 0.0657756 | 826.955ms | 905 | 2560 | 1508.84 | 1167.18 | 0.185956 | 7.2033 | 18.2972 | 3.16243 | 0.00118526 | 0.000109634 | 3.06457e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 277.106 | 0.020442 | 1024.72ms | 905 | 320 | 129.719 | 3114.61 | 0.0395471 | 18.8381 | 55.2188 | 8.24641 | 0.00658149 | 4.48895e-05 | 3.45304e-06 | 3(Loss) | true |
| simdjson (ondemand) | 189.185 | 0.0304468 | 1168.89ms | 905 | 4890 | 9434.4 | 4562.06 | 0.0479916 | 27.4377 | 103.491 | 10.4541 | 0.0398138 | 0.000106204 | 1.87552e-05 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2248.84 | 0.154623 | 747.494ms | 905 | 160 | 56.3445 | 383.788 | 0.605374 | 2.52144 | 10.0729 | 0.743646 | 0.00332873 | 1.38122e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 255.346 | 0.0296204 | 1051ms | 905 | 4890 | 4901.5 | 3380.02 | 0.0266946 | 20.3919 | 93.9878 | 20.7525 | 0.0527015 | 0.000110045 | 2.41783e-05 | 2(Loss) | true |
| glaze | 208.499 | 0.0334492 | 1131.73ms | 905 | 4890 | 9374.92 | 4139.46 | 0.00844966 | 24.9147 | 109.319 | 23.0707 | 0.0870535 | 0.000235682 | 7.47947e-05 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3389.47 | 0.161944 | 734.039ms | 905 | 320 | 54.4145 | 254.634 | 0.872762 | 1.78634 | 7.77459 | 0.271823 | 0.00223066 | 2.07182e-05 | 1.38122e-05 | 1(Win) | true |
| simdjson (reflection) | 3274.52 | 0.137247 | 742.902ms | 905 | 640 | 83.7505 | 263.573 | 0.0918018 | 1.81279 | 8.45414 | 1.05193 | 0.00110497 | 2.58978e-05 | 5.17956e-06 | 2(Loss) | true |
| glaze | 685.95 | 0.019305 | 842.09ms | 905 | 320 | 18.8799 | 1258.22 | 0.0407488 | 7.74748 | 21.8155 | 3.36685 | 0.00553522 | 4.14365e-05 | 1.03591e-05 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1160.25 | 0.0692636 | 864.207ms | 1811 | 2560 | 2721.37 | 1488.57 | 0.0899848 | 4.55249 | 20.9486 | 3.93484 | 0.000564476 | 9.922e-05 | 7.98074e-06 | 1(Win) | true |
| glaze | 983.205 | 0.0512349 | 890.535ms | 1811 | 160 | 129.599 | 1756.61 | 0.00604896 | 5.35955 | 26.4208 | 4.12369 | 0.00101118 | 3.79625e-05 | 6.90226e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 343.708 | 0.0478864 | 1221.38ms | 1811 | 2560 | 14822.5 | 5024.92 | 0.032476 | 15.1089 | 42.5229 | 6.12645 | 0.00154805 | 0.000113887 | 3.60212e-05 | 3(Loss) | true |
| simdjson (ondemand) | 233.443 | 0.0658799 | 1458.22ms | 1811 | 640 | 15204.1 | 7398.4 | 0.0125856 | 22.1675 | 84.1138 | 11.1403 | 0.00226826 | 7.24738e-05 | 1.89812e-05 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1238.98 | 0.0450068 | 853.093ms | 1811 | 4890 | 1924.74 | 1393.97 | 0.117671 | 4.27747 | 20.0337 | 3.72336 | 0.000981505 | 9.94829e-05 | 3.45537e-05 | 1(Win) | true |
| glaze | 1075.78 | 0.0436384 | 871.892ms | 1811 | 2560 | 1256.51 | 1605.44 | 0.0462568 | 4.90544 | 25.7079 | 3.88515 | 0.00110846 | 5.58652e-05 | 1.12162e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 348.858 | 0.114468 | 1212.1ms | 1811 | 640 | 20553.5 | 4950.74 | 0.038077 | 14.8953 | 41.6041 | 5.91497 | 0.00113283 | 3.9688e-05 | 2.58835e-06 | 3(Loss) | true |
| simdjson (ondemand) | 237.021 | 0.024269 | 1444.97ms | 1811 | 4890 | 15292.4 | 7286.71 | 0.0579133 | 21.8272 | 83.1474 | 10.9288 | 0.000585493 | 6.43647e-05 | 2.37133e-05 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 352.551 | 0.0433638 | 1256.75ms | 1997 | 1280 | 7023.87 | 5402.02 | 0.00684108 | 14.7069 | 64.0496 | 11.651 | 0.00193924 | 0.000128709 | 2.22991e-05 | 1(Win) | true |
| jsonifier | 351.278 | 0.0776341 | 1215.21ms | 1811 | 80 | 1165.55 | 4916.64 | 0.157127 | 14.7889 | 63.0083 | 11.19 | 0.0185119 | 0.000179459 | 8.28272e-05 | 2(Loss) | true |
| glaze | 306.521 | 0.0468013 | 1278.5ms | 1798 | 1280 | 8773.72 | 5594.09 | 0.0426189 | 16.915 | 70.0234 | 12.3521 | 0.021686 | 0.000116014 | 2.91122e-05 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 886.592 | 0.0194493 | 915.308ms | 1811 | 640 | 91.871 | 1948.03 | 0.0077007 | 5.93646 | 20.3611 | 1.3661 | 0.00069454 | 1.55301e-05 | 8.62783e-07 | 1(Win) | true |
| simdjson (reflection) | 653.263 | 0.0698615 | 1021.46ms | 1997 | 1280 | 5309.65 | 2915.35 | 0.180245 | 8.02373 | 25.2954 | 2.57787 | 0.000796507 | 3.36442e-05 | 3.91212e-06 | 2(Loss) | true |
| glaze | 640.539 | 0.0512223 | 1001.95ms | 1798 | 4890 | 9194.23 | 2676.98 | 0.22077 | 8.13358 | 26.4755 | 2.36263 | 0.00069334 | 0.000101226 | 4.24239e-05 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3350.22 | 0.118584 | 823.293ms | 3862 | 2560 | 4350.8 | 1099.36 | 0.0870228 | 1.58804 | 7.43345 | 0.948991 | 0.000324476 | 5.27981e-05 | 1.21375e-05 | 1(Win) | true |
| glaze | 1803.86 | 0.125746 | 918.043ms | 3862 | 1280 | 8437.58 | 2041.78 | 0.0938097 | 2.90447 | 14.4231 | 1.82626 | 0.000263788 | 5.17866e-05 | 1.75994e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 778.607 | 0.057514 | 1186.17ms | 3862 | 1280 | 9474.28 | 4730.36 | 0.0486645 | 6.67442 | 17.4679 | 2.04014 | 0.000268239 | 3.78285e-05 | 6.27104e-06 | 3(Loss) | true |
| simdjson (ondemand) | 530.73 | 0.028465 | 1415.52ms | 3862 | 4890 | 19081.3 | 6939.67 | 0.512527 | 9.86771 | 31.579 | 3.36018 | 0.00435511 | 3.92371e-05 | 8.15454e-06 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3766.63 | 0.15426 | 804.389ms | 3862 | 640 | 1456.15 | 977.822 | 0.00159796 | 1.4209 | 6.95236 | 0.838685 | 0.000265811 | 2.02292e-05 | 2.4275e-06 | 1(Win) | true |
| glaze | 1865.33 | 0.050698 | 908.209ms | 3862 | 2560 | 2565.29 | 1974.5 | 0.0108029 | 2.81477 | 14.1336 | 1.71129 | 0.000322149 | 3.42884e-05 | 7.2825e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 805.475 | 0.0253891 | 1165.78ms | 3862 | 4890 | 6590.58 | 4572.57 | 0.0889644 | 6.50368 | 16.9886 | 1.92983 | 0.000263752 | 5.80879e-05 | 1.88508e-05 | 3(Loss) | true |
| simdjson (ondemand) | 532.595 | 0.0281885 | 1408.03ms | 3862 | 4890 | 18581.7 | 6915.37 | 0.0808169 | 9.71334 | 31.0642 | 3.24521 | 0.00567344 | 3.27241e-05 | 1.0908e-05 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 992.183 | 0.0316259 | 1091.53ms | 3862 | 4890 | 6739.62 | 3712.11 | 0.0556935 | 5.20784 | 26.5132 | 5.20145 | 0.00531729 | 3.79133e-05 | 2.85938e-06 | 1(Win) | true |
| jsonifier | 941.156 | 0.100415 | 1112.8ms | 3862 | 640 | 9882.88 | 3913.37 | 0.0113007 | 5.52166 | 25.8286 | 5.37468 | 0.00863825 | 4.61225e-05 | 8.49625e-06 | 2(Loss) | true |
| glaze | 828.371 | 0.0735444 | 1164.38ms | 3862 | 640 | 6843.12 | 4446.19 | 0.0218282 | 6.27248 | 28.956 | 5.8348 | 0.0086419 | 4.73362e-05 | 8.90083e-06 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5392.95 | 0.0315586 | 807.861ms | 3862 | 640 | 29.7294 | 682.945 | 0.122093 | 1.01195 | 5.50414 | 0.748058 | 0.000507752 | 2.913e-05 | 1.21375e-06 | 1(Win) | true |
| simdjson (reflection) | 4142.33 | 0.0871995 | 817.016ms | 3862 | 1280 | 769.439 | 889.136 | 0.0683132 | 1.29965 | 6.48835 | 0.533662 | 0.000486916 | 2.50842e-05 | 5.66416e-06 | 2(Loss) | true |
| glaze | 2590.36 | 0.0450089 | 887.582ms | 3862 | 4890 | 2002.68 | 1421.84 | 0.0150757 | 2.05007 | 8.6709 | 1.15122 | 0.0056771 | 3.03942e-05 | 6.08943e-06 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1798.05 | 0.0428453 | 1228.24ms | 9578 | 2560 | 12128.1 | 5080.12 | 0.0913267 | 2.85865 | 14.5105 | 2.70746 | 0.00145308 | 2.54489e-05 | 6.36224e-06 | 1(Win) | true |
| glaze | 1467.89 | 0.0284722 | 1345.63ms | 9578 | 4890 | 15350.3 | 6222.74 | 0.0930407 | 3.50879 | 17.7694 | 3.52621 | 0.00160653 | 2.10733e-05 | 6.46932e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1068.51 | 0.055801 | 1585.8ms | 9578 | 640 | 14563.2 | 8548.62 | 0.243651 | 4.84023 | 18.9848 | 3.2629 | 0.00145483 | 3.18112e-05 | 3.26269e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1044.1 | 0.0590283 | 1595.82ms | 9578 | 640 | 17067.5 | 8748.52 | 0.0154824 | 4.95244 | 18.9983 | 2.90959 | 0.00376987 | 1.56609e-05 | 3.26269e-07 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2718.17 | 0.088493 | 1192.4ms | 9578 | 80 | 707.467 | 3360.46 | 0.0643927 | 1.91879 | 10.5229 | 1.82074 | 0.00035498 | 1.43558e-05 | 1.04406e-05 | 1(Win) | true |
| glaze | 2035.76 | 0.0446421 | 1307.17ms | 9578 | 2560 | 10271.4 | 4486.93 | 0.0706717 | 2.52828 | 13.5749 | 2.56421 | 0.000316929 | 1.93722e-05 | 4.56776e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1327.98 | 0.0661724 | 1552.03ms | 9578 | 4890 | 101305 | 6878.35 | 0.0499727 | 3.87599 | 14.9819 | 2.38192 | 0.000120675 | 1.8981e-05 | 4.09937e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1257.83 | 0.145511 | 1575.4ms | 9578 | 1280 | 142925 | 7261.94 | 0.0569215 | 4.06973 | 15.0039 | 2.02673 | 0.00698345 | 1.61503e-05 | 1.63134e-06 | 4(Loss) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3947.01 | 0.263402 | 954.478ms | 9578 | 30 | 1114.74 | 2314.23 | 0.0992863 | 1.32815 | 5.34673 | 1.07037 | 0.0021264 | 4.52426e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 3759.83 | 0.149544 | 960.215ms | 9578 | 640 | 8447.58 | 2429.45 | 0.0063676 | 1.38064 | 6.09772 | 1.14429 | 0.00023736 | 2.95273e-05 | 2.93642e-06 | 2(Loss) | true |
| glaze | 2056.86 | 0.0303831 | 1166.41ms | 9578 | 4890 | 8902.51 | 4440.89 | 0.0801363 | 2.52309 | 12.5878 | 2.57559 | 0.000744207 | 2.24612e-05 | 8.1774e-06 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11712.4 | 0.0971714 | 822.476ms | 9578 | 4890 | 2808.28 | 779.88 | 0.49615 | 0.458891 | 2.34089 | 0.316454 | 0.000559799 | 1.96855e-05 | 8.1347e-06 | 1(Win) | true |
| simdjson (reflection) | 9468.2 | 0.371147 | 843.119ms | 9578 | 30 | 384.616 | 964.733 | 0.0795325 | 0.557312 | 3.02412 | 0.331489 | 0.000247094 | 1.39208e-05 | 0 | 2(Loss) | true |
| glaze | 6356 | 0.0427202 | 887.098ms | 9578 | 320 | 120.614 | 1437.11 | 0.0308874 | 0.833783 | 4.38046 | 0.677699 | 0.000154325 | 8.15671e-06 | 3.26269e-07 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3382.19 | 0.105629 | 822.347ms | 3873 | 160 | 212.907 | 1092.07 | 0.0543989 | 1.57756 | 7.25226 | 0.904467 | 0.000358249 | 4.84121e-05 | 0 | 1(Win) | true |
| glaze | 1956.59 | 0.0542334 | 905.774ms | 3873 | 2560 | 2683.31 | 1887.77 | 0.0464347 | 2.68399 | 12.7563 | 1.80377 | 0.000367428 | 3.53005e-05 | 7.86696e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 859.982 | 0.0348852 | 1141.94ms | 3873 | 80 | 179.592 | 4294.95 | 0.057659 | 6.04913 | 16.1046 | 1.98761 | 0.00131035 | 2.25923e-05 | 3.22747e-06 | 3(Loss) | true |
| simdjson (ondemand) | 521.739 | 0.0685727 | 1423.31ms | 3873 | 640 | 15082.4 | 7079.37 | 0.0608652 | 9.91804 | 31.2107 | 3.47018 | 0.0100249 | 4.43777e-05 | 1.04893e-05 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3890.73 | 0.14686 | 804.128ms | 3873 | 640 | 1244 | 949.328 | 0.0164563 | 1.39831 | 6.7449 | 0.786471 | 0.000294507 | 5.68842e-05 | 7.26181e-06 | 1(Win) | true |
| glaze | 2089.97 | 0.0461185 | 889.98ms | 3873 | 80 | 53.1441 | 1767.29 | 0.155139 | 2.56654 | 12.4735 | 1.69171 | 0.000545443 | 1.61374e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 884.758 | 0.0680068 | 1130.05ms | 3873 | 4890 | 39414.9 | 4174.68 | 0.0440683 | 5.87112 | 15.5794 | 1.86755 | 0.00102487 | 5.85037e-05 | 2.11205e-05 | 3(Loss) | true |
| simdjson (ondemand) | 528.604 | 0.0246586 | 1412.81ms | 3873 | 4890 | 14517.1 | 6987.43 | 0.0315512 | 9.79661 | 30.7033 | 3.35812 | 0.0132763 | 6.71103e-05 | 2.52918e-05 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 917.183 | 0.0389324 | 1122.52ms | 3873 | 2560 | 6292.82 | 4027.09 | 0.0346846 | 5.66789 | 25.3814 | 5.22954 | 0.00947606 | 7.64507e-05 | 1.97683e-05 | 1(Win) | true |
| simdjson (reflection) | 899.07 | 0.0856817 | 1122.52ms | 3873 | 40 | 495.615 | 4108.23 | 0.0966636 | 5.78593 | 26.9101 | 5.27085 | 0.0119868 | 5.16396e-05 | 1.93648e-05 | 2(Loss) | true |
| glaze | 892.428 | 0.0283904 | 1134.51ms | 3873 | 4890 | 6751.48 | 4138.8 | 0.0163459 | 5.81919 | 28.5074 | 5.78828 | 0.00618539 | 9.15044e-05 | 4.80491e-05 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4971 | 0.176932 | 816.51ms | 3873 | 160 | 276.528 | 743.025 | 0.166272 | 1.09313 | 5.37774 | 0.734831 | 0.000532533 | 2.74335e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 4459.72 | 0.0534195 | 808.682ms | 3873 | 640 | 125.274 | 828.209 | 0.0233993 | 1.21655 | 6.42267 | 0.530338 | 0.000515992 | 1.2103e-05 | 1.2103e-06 | 2(Loss) | true |
| glaze | 2640.91 | 0.129513 | 885.245ms | 3873 | 640 | 2099.88 | 1398.6 | 0.0208958 | 2.00696 | 7.7875 | 0.993029 | 0.00424292 | 4.47812e-05 | 1.93648e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 931.613 | 0.0943742 | 6682ms | 2090234 | 160 | 6.52448e+08 | 2.13973e+06 | 0.0255629 | 5.46763 | 27.1875 | 5.44724 | 0.0213368 | 0.107249 | 0.000107267 | 1(Win) | true |
| jsonifier | 920.079 | 0.0710312 | 6732.14ms | 2090234 | 160 | 3.7893e+08 | 2.16656e+06 | 0.0032914 | 5.51763 | 24.6466 | 5.1365 | 0.0335039 | 0.0685271 | 8.28167e-05 | 2(Loss) | true |
| simdjson (reflection) | 892.44 | 0.083876 | 6971.22ms | 2090234 | 160 | 5.61601e+08 | 2.23366e+06 | 0.0487861 | 5.72938 | 28.069 | 5.14276 | 0.0190876 | 0.108097 | 0.000286843 | 3(Loss) | true |
| simdjson (ondemand) | 792.567 | 0.0592493 | 7838.68ms | 2090234 | 160 | 3.55307e+08 | 2.51512e+06 | 0.067888 | 6.44851 | 30.0622 | 5.60833 | 0.0256478 | 0.114102 | 0.000295858 | 4(Loss) | true |
| glaze | 733.908 | 0.0539197 | 8477.29ms | 2090234 | 160 | 3.4318e+08 | 2.71615e+06 | 0.130524 | 6.97768 | 30.6003 | 6.01798 | 0.028724 | 0.0667064 | 0.000406731 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 1117.41 | 0.0937902 | 6668.7ms | 2090234 | 160 | 4.47922e+08 | 1.78395e+06 | 0.160527 | 4.53414 | 21.939 | 4.19644 | 0.0206299 | 0.0816817 | 0.000263565 | 1(Win) | true |
| jsonifier | 1106.96 | 0.143267 | 6701.91ms | 2090234 | 40 | 2.66243e+08 | 1.80079e+06 | 0.124057 | 4.59283 | 19.3407 | 3.86912 | 0.0329648 | 0.0436305 | 9.46545e-05 | 2(Loss) | true |
| simdjson (reflection) | 1073.7 | 0.0972545 | 6918.28ms | 2090234 | 160 | 5.21629e+08 | 1.85657e+06 | 0.0522432 | 4.76116 | 22.8276 | 3.89155 | 0.0177933 | 0.0802964 | 7.09012e-05 | 3(Loss) | true |
| simdjson (ondemand) | 951.563 | 0.140159 | 7708.9ms | 2090234 | 40 | 3.4484e+08 | 2.09487e+06 | 0.00299112 | 5.36635 | 24.7804 | 4.35367 | 0.0218646 | 0.0786631 | 0.000165663 | 4(Loss) | true |
| glaze | 848.166 | 0.0935548 | 8507.47ms | 2090234 | 80 | 3.86768e+08 | 2.35025e+06 | 0.0104877 | 6.0213 | 25.2683 | 4.74989 | 0.0278319 | 0.0419015 | 0.000177773 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2135.2 | 0.0211865 | 5955.23ms | 2090234 | 320 | 1.25194e+07 | 933590 | 0.137266 | 2.40974 | 7.63896 | 0.373374 | 0.000315708 | 0.0507163 | 3.74465e-05 | 1(Win) | true |
| glaze | 1467.15 | 0.0896395 | 8620.61ms | 2090234 | 160 | 2.37335e+08 | 1.35869e+06 | 0.151409 | 3.47348 | 9.69978 | 0.65141 | 0.0117045 | 0.0689981 | 6.5223e-05 | 2(Loss) | true |
| simdjson (reflection) | 1054.35 | 0.0601611 | 5892.27ms | 2090326 | 160 | 2.07021e+08 | 1.89074e+06 | 0.1346 | 4.8839 | 15.3147 | 1.4617 | 0.0160526 | 0.0503839 | 6.27414e-05 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2135.78 | 0.0104482 | 5962.16ms | 2090234 | 160 | 1.52152e+06 | 933337 | 0.00734382 | 2.40899 | 7.6388 | 0.37334 | 0.000321519 | 0.0506257 | 3.0185e-05 | 1(Win) | true |
| glaze | 1547.55 | 0.0397563 | 8170.37ms | 2090234 | 160 | 4.19595e+07 | 1.2881e+06 | 0.140709 | 3.31891 | 9.69575 | 0.650458 | 0.0117324 | 0.0432851 | 2.92372e-05 | 2(Loss) | true |
| simdjson (reflection) | 1053.02 | 0.0292552 | 5922.45ms | 2090326 | 160 | 4.90769e+07 | 1.89311e+06 | 0.14579 | 4.88577 | 15.3145 | 1.46167 | 0.0160917 | 0.0503198 | 0.000286594 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2703.27 | 0.0998312 | 7330.82ms | 6661897 | 160 | 8.80787e+08 | 2.35022e+06 | 0.0515796 | 1.86427 | 9.38362 | 1.74083 | 0.00562135 | 0.0564682 | 0.000375782 | 1(Win) | true |
| simdjson (reflection) | 2586.71 | 0.159185 | 7646.82ms | 6661897 | 40 | 6.11459e+08 | 2.45613e+06 | 0.0207701 | 1.96219 | 9.72653 | 1.6535 | 0.00518068 | 0.0564856 | 0.000449996 | 2(Loss) | true |
| jsonifier | 2488.54 | 0.114861 | 7950.54ms | 6661897 | 40 | 3.43961e+08 | 2.55301e+06 | 0.503529 | 2.04376 | 9.6957 | 2.12314 | 0.00991256 | 0.0340802 | 8.34259e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2322.59 | 0.0642102 | 8507.79ms | 6661897 | 80 | 2.46802e+08 | 2.73543e+06 | 0.0112349 | 2.17699 | 10.3516 | 1.79939 | 0.00722832 | 0.058133 | 0.000128458 | 4(Loss) | true |
| glaze | 1882.84 | 0.148497 | 5107.89ms | 6661897 | 30 | 7.53221e+08 | 3.3743e+06 | 0.0948925 | 2.70758 | 13.2529 | 2.49542 | 0.00891083 | 0.0357103 | 0.00240735 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3174.75 | 0.104625 | 7342.3ms | 6661897 | 30 | 1.31512e+08 | 2.00119e+06 | 0.267816 | 1.58362 | 7.74433 | 1.34995 | 0.00541463 | 0.048332 | 0.000241328 | 1(Win) | true |
| simdjson (reflection) | 3067.96 | 0.161521 | 7587.05ms | 6661897 | 40 | 4.47522e+08 | 2.07085e+06 | 0.00967183 | 1.65889 | 8.08195 | 1.26095 | 0.00485944 | 0.0476052 | 0.000340481 | 2(Loss) | true |
| jsonifier | 2926.11 | 0.0501965 | 7925.08ms | 6661897 | 160 | 1.90056e+08 | 2.17124e+06 | 0.183345 | 1.74999 | 8.05699 | 1.73237 | 0.00970618 | 0.0258902 | 0.000244296 | 3(Loss) | true |
| simdjson (ondemand) | 2767.37 | 0.0873007 | 8331.9ms | 6661897 | 80 | 3.21355e+08 | 2.29578e+06 | 0.220413 | 1.84209 | 8.69422 | 1.40575 | 0.00612573 | 0.0472871 | 0.000156555 | 4(Loss) | true |
| glaze | 2109.05 | 0.122237 | 5102.96ms | 6661897 | 80 | 1.08472e+09 | 3.01239e+06 | 0.555469 | 2.41295 | 11.6028 | 2.10383 | 0.00851888 | 0.0269456 | 0.00042854 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6193.82 | 0.0293582 | 6519.99ms | 6661897 | 80 | 7.25487e+06 | 1.02575e+06 | 0.0275882 | 0.830584 | 2.48861 | 0.11715 | 0.000115288 | 0.027822 | 4.64883e-05 | 1(Win) | true |
| glaze | 3306.88 | 0.143669 | 6049.86ms | 6661897 | 30 | 2.28564e+08 | 1.92123e+06 | 0.164744 | 1.54931 | 4.40917 | 0.355583 | 0.00380595 | 0.0632216 | 0.00174288 | 2(Loss) | true |
| simdjson (reflection) | 182.855 | 0.154531 | 10452.5ms | 6661989 | 30 | 8.64858e+10 | 3.47454e+07 | 0.0352756 | 27.9784 | 93.63 | 17.091 | 0.111899 | 0.255006 | 0.121468 | 3(Loss) | true |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6197.07 | 0.0336807 | 6520.55ms | 6661897 | 160 | 1.90768e+07 | 1.02521e+06 | 0.0114728 | 0.830484 | 2.48856 | 0.117139 | 0.000113972 | 0.0278034 | 7.34157e-05 | 1(Win) | true |
| glaze | 3914.56 | 0.0358331 | 5087.6ms | 6661897 | 160 | 5.41151e+07 | 1.62299e+06 | 0.217413 | 1.31407 | 4.40771 | 0.355242 | 0.00380962 | 0.0246046 | 0.000216199 | 2(Loss) | true |
| simdjson (reflection) | 180.749 | 0.18712 | 10496.7ms | 6661989 | 30 | 1.29782e+11 | 3.51501e+07 | 0.643738 | 28.1663 | 93.6318 | 17.0923 | 0.111566 | 0.255679 | 0.125004 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2491.95 | 0.043037 | 5100.82ms | 500299 | 640 | 4.34555e+06 | 191465 | 0.353455 | 2.06066 | 8.90818 | 1.68597 | 0.0117037 | 0.00664837 | 7.22568e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1903.79 | 0.0461213 | 6591.16ms | 500299 | 640 | 8.55076e+06 | 250617 | 0.108045 | 2.68239 | 11.8355 | 2.05069 | 0.0129969 | 0.0364432 | 0.00029136 | 2(Loss) | true |
| glaze | 1831.62 | 0.0683281 | 6840.72ms | 500299 | 320 | 1.01377e+07 | 260492 | 0.0740297 | 2.7898 | 11.5528 | 2.25999 | 0.0138774 | 0.00438041 | 0.000180973 | 3(Loss) | true |
| simdjson (reflection) | 1431.28 | 0.0468455 | 8717.01ms | 500299 | 640 | 1.56072e+07 | 333354 | 0.0565146 | 3.56716 | 14.6252 | 2.32334 | 0.0186228 | 0.0271349 | 0.000138067 | 4(Loss) | true |
| simdjson (ondemand) | 1390.91 | 0.0569015 | 8991.55ms | 500299 | 320 | 1.21916e+07 | 343030 | 0.0787657 | 3.68485 | 14.1858 | 2.32507 | 0.0177318 | 0.0327231 | 0.000167806 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3088.12 | 0.0256352 | 9909.11ms | 500299 | 2560 | 4.0159e+06 | 154502 | 0.0520226 | 1.65636 | 7.78625 | 1.41428 | 0.00848161 | 0.00346541 | 1.50309e-05 | 1(Win) | true |
| jsonifier (two-stage) | 2285.43 | 0.0334997 | 6392.13ms | 500299 | 640 | 3.1303e+06 | 208767 | 0.113554 | 2.2494 | 10.7146 | 1.77966 | 0.00946052 | 0.0260834 | 1.70617e-05 | 2(Loss) | true |
| glaze | 2219.53 | 0.063442 | 6594.51ms | 500299 | 160 | 2.97586e+06 | 214966 | 0.17657 | 2.31832 | 10.4414 | 1.99184 | 0.0093372 | 0.00206244 | 1.43539e-05 | 3(Loss) | true |
| simdjson (reflection) | 1687.09 | 0.0619401 | 8221.27ms | 500299 | 320 | 9.81919e+06 | 282808 | 0.0434295 | 3.0197 | 13.5199 | 2.05243 | 0.011634 | 0.0124689 | 2.2093e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1646.37 | 0.0548199 | 8314.11ms | 500299 | 320 | 8.07661e+06 | 289802 | 0.121472 | 3.08203 | 13.0522 | 2.04681 | 0.00945655 | 0.0153982 | 2.66153e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12843.2 | 0.0204775 | 4481.46ms | 500299 | 4890 | 282991 | 37149.7 | 0.0966204 | 0.398619 | 1.88008 | 0.301488 | 0.000726465 | 0.000999474 | 5.01581e-06 | 1(Win) | true |
| simdjson (reflection) | 11361.2 | 0.100375 | 4956.98ms | 500299 | 320 | 568606 | 41995.9 | 0.0945629 | 0.45303 | 2.16983 | 0.197412 | 0.00125355 | 0.000858674 | 7.41432e-06 | 2(Loss) | true |
| glaze | 6177.18 | 0.0342579 | 8499.14ms | 500299 | 4890 | 3.42381e+06 | 77239.5 | 0.0845358 | 0.817235 | 3.61253 | 0.52616 | 0.00135089 | 0.0244999 | 1.1896e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12923.8 | 0.0229821 | 4444.71ms | 500299 | 2560 | 184290 | 36918.2 | 0.00759539 | 0.39707 | 1.87899 | 0.30124 | 0.00071948 | 0.000579925 | 6.31654e-06 | 1(Win) | true |
| simdjson (reflection) | 11307.9 | 0.0491791 | 4962.03ms | 500299 | 640 | 275573 | 42193.7 | 0.121804 | 0.452321 | 2.16878 | 0.197174 | 0.00123107 | 9.40219e-05 | 7.59233e-06 | 2(Loss) | true |
| glaze | 7175.26 | 0.098885 | 7372.92ms | 500299 | 4890 | 2.11424e+07 | 66495.5 | 0.10778 | 0.706884 | 3.59893 | 0.523033 | 0.00135087 | 0.00303328 | 1.15375e-05 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4349.27 | 0.0626864 | 8264.74ms | 1439562 | 640 | 2.50585e+07 | 315656 | 0.214235 | 1.16423 | 4.99633 | 0.74542 | 0.00465398 | 0.0605157 | 6.44944e-05 | 1(Win) | true |
| jsonifier | 4072.58 | 0.0622085 | 8821.37ms | 1439562 | 320 | 1.40725e+07 | 337101 | 0.170437 | 1.26181 | 5.34455 | 1.17098 | 0.00441693 | 0.0226031 | 7.48361e-05 | 2(Loss) | true |
| simdjson (reflection) | 3531.4 | 0.0583499 | 5035.75ms | 1439562 | 320 | 1.64663e+07 | 388762 | 0.0850023 | 1.44507 | 6.02057 | 0.848101 | 0.00619159 | 0.0510122 | 4.69869e-05 | 3(Loss) | true |
| simdjson (ondemand) | 3422.48 | 0.0753774 | 5191.49ms | 1439562 | 160 | 1.46279e+07 | 401134 | 0.0233128 | 1.49493 | 5.87525 | 0.850676 | 0.00594568 | 0.0547926 | 9.65181e-05 | 4(Loss) | true |
| glaze | 2950.46 | 0.0866007 | 5959.73ms | 1439562 | 80 | 1.29901e+07 | 465308 | 0.0372974 | 1.71754 | 7.70271 | 1.43071 | 0.00654217 | 0.0178433 | 6.76247e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 5047.72 | 0.088545 | 8046.28ms | 1439562 | 1280 | 7.42348e+07 | 271979 | 0.093744 | 1.00337 | 4.60736 | 0.651512 | 0.00342276 | 0.0526592 | 3.77296e-05 | 1(Win) | true |
| jsonifier | 4626.34 | 0.0588331 | 8650.87ms | 1439562 | 320 | 9.7539e+06 | 296751 | 0.0663058 | 1.10615 | 4.95855 | 1.0776 | 0.00326058 | 0.0156232 | 1.44163e-05 | 2(Loss) | true |
| simdjson (reflection) | 4096.1 | 0.0490596 | 9604.9ms | 1439562 | 320 | 8.65202e+06 | 335166 | 0.0803416 | 1.25072 | 5.63536 | 0.753747 | 0.00398594 | 0.0387851 | 1.58642e-05 | 3(Loss) | true |
| simdjson (ondemand) | 4056.66 | 0.0452835 | 9630.78ms | 1439562 | 320 | 7.51546e+06 | 338425 | 0.0184612 | 1.26549 | 5.47338 | 0.751918 | 0.00313384 | 0.0409481 | 1.81891e-05 | 4(Loss) | true |
| glaze | 3321.33 | 0.0428083 | 5848.24ms | 1439562 | 80 | 2.50485e+06 | 413350 | 0.0466136 | 1.54913 | 7.31761 | 1.33799 | 0.00491131 | 0.0118476 | 5.27504e-05 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18863 | 0.011749 | 8083.05ms | 1439562 | 4890 | 357560 | 72781.3 | 0.00328144 | 0.272925 | 0.745943 | 0.104967 | 0.000264054 | 0.0171697 | 8.19722e-06 | 1(Win) | true |
| glaze | 6085.93 | 0.0727824 | 5970.1ms | 1439584 | 1280 | 3.45051e+07 | 225585 | 0.229715 | 0.836729 | 2.99198 | 0.365933 | 0.000653284 | 0.0595946 | 9.01736e-06 | 2(Loss) | true |
| simdjson (reflection) | 540.265 | 0.531486 | 7909.11ms | 1439562 | 160 | 2.91844e+10 | 2.54111e+06 | 0.420161 | 9.31373 | 34.227 | 5.77438 | 0.0137389 | 0.304962 | 0.00124174 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18910.3 | 0.0529978 | 8063.61ms | 1439562 | 80 | 118432 | 72599.1 | 0.0612923 | 0.272465 | 0.745706 | 0.104916 | 0.000268241 | 0.0170604 | 8.18825e-06 | 1(Win) | true |
| glaze | 8221.31 | 0.090358 | 8938.22ms | 1439584 | 1280 | 2.91431e+07 | 166992 | 0.189027 | 0.619415 | 2.98646 | 0.364671 | 0.000651695 | 0.0169781 | 2.22851e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.939 | 0.732952 | 7880.07ms | 1439562 | 80 | 2.80966e+10 | 2.55685e+06 | 0.483426 | 9.36891 | 34.2268 | 5.77436 | 0.0136993 | 0.305855 | 0.00148899 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2263.51 | 0.139112 | 3070.51ms | 56369 | 80 | 87324.4 | 23749.7 | 0.0107358 | 2.23487 | 9.31728 | 1.80693 | 0.00353696 | 1.28617e-05 | 3.54805e-06 | 1(Win) | true |
| glaze | 1923.08 | 0.254835 | 3517.36ms | 56369 | 320 | 1.62388e+06 | 27953.9 | 0.145103 | 2.63589 | 11.1858 | 2.23776 | 0.00609211 | 4.66236e-05 | 2.16764e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1856.26 | 0.0417955 | 3628.43ms | 56369 | 1280 | 187530 | 28960.2 | 0.123307 | 2.75629 | 12.0313 | 2.07681 | 0.00506488 | 3.84187e-05 | 2.37692e-05 | 3(Loss) | true |
| simdjson (reflection) | 1545.77 | 0.085208 | 4231.4ms | 56369 | 160 | 140499 | 34777.3 | 0.0241056 | 3.32767 | 13.7054 | 2.34038 | 0.00643439 | 6.16474e-05 | 4.23548e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1436.89 | 0.0369374 | 4483.11ms | 56369 | 1280 | 244444 | 37412.6 | 0.0480556 | 3.57473 | 14.1816 | 2.61987 | 0.0104987 | 4.95202e-05 | 2.55709e-05 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3346.46 | 0.0355133 | 2665.71ms | 56369 | 2560 | 83316.8 | 16064.1 | 0.0748323 | 1.53236 | 7.32459 | 1.37104 | 0.000666749 | 1.33814e-05 | 8.01083e-06 | 1(Win) | true |
| glaze | 2798.68 | 0.287222 | 3035.51ms | 56369 | 320 | 973999 | 19208.2 | 0.0640591 | 1.81814 | 8.94705 | 1.75133 | 0.00338051 | 4.21331e-06 | 1.27508e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2513.04 | 0.0349339 | 3219.38ms | 56369 | 1280 | 71480.5 | 21391.5 | 0.0226192 | 2.05009 | 10.0304 | 1.63865 | 0.00209594 | 2.50165e-05 | 1.74215e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1835.08 | 0.0382522 | 4042.52ms | 56369 | 2560 | 321457 | 29294.4 | 0.0906866 | 2.80577 | 12.0084 | 2.15871 | 0.0081416 | 2.10665e-05 | 1.25914e-05 | 4(Loss) | true |
| simdjson (reflection) | 1816.74 | 0.0366241 | 4075.5ms | 56369 | 1280 | 150328 | 29590.2 | 0.0985707 | 2.81928 | 12.1135 | 1.97757 | 0.00406103 | 1.35685e-05 | 6.02891e-06 | 5(Loss) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13826.8 | 0.0860476 | 1119.79ms | 56369 | 640 | 7163.03 | 3887.94 | 0.066717 | 0.376034 | 1.57815 | 0.243201 | 0.000220035 | 4.79541e-06 | 2.41156e-06 | 1(Win) | true |
| simdjson (reflection) | 11307.9 | 0.0925366 | 1205.7ms | 56369 | 640 | 12385.8 | 4754 | 0.0261361 | 0.452039 | 1.85554 | 0.281999 | 0.000151818 | 5.62698e-06 | 1.91262e-06 | 2(Loss) | true |
| glaze | 6305.85 | 0.0675237 | 1596.94ms | 56369 | 2560 | 84829.4 | 8525.05 | 0.0336805 | 0.809076 | 3.28862 | 0.476698 | 7.6782e-05 | 1.06441e-05 | 5.30821e-06 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14035.8 | 0.086929 | 1116.51ms | 56369 | 640 | 7094.44 | 3830.05 | 0.0156631 | 0.370532 | 1.56847 | 0.241001 | 0.000217152 | 2.24525e-06 | 1.10877e-07 | 1(Win) | true |
| simdjson (reflection) | 11272.9 | 0.169317 | 1210.95ms | 56369 | 30 | 1955.84 | 4768.77 | 0.406552 | 0.45243 | 1.84555 | 0.279675 | 0.000160254 | 1.83316e-05 | 8.87012e-06 | 2(Loss) | true |
| glaze | 6917.19 | 0.110486 | 1511.93ms | 56369 | 2560 | 188745 | 7771.6 | 0.200272 | 0.743971 | 3.21134 | 0.459384 | 6.29224e-05 | 1.09491e-05 | 5.32207e-06 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2860.7 | 0.0298896 | 3885.87ms | 94370 | 1280 | 113181 | 31460.2 | 0.0559199 | 1.80008 | 7.76635 | 1.25527 | 0.00340348 | 1.34444e-05 | 7.93916e-06 | 1(Win) | true |
| jsonifier | 2528.94 | 0.0375768 | 4290.33ms | 94370 | 2560 | 457794 | 35587.3 | 0.0145174 | 2.02189 | 7.7623 | 1.70781 | 0.00448371 | 1.0667e-05 | 5.68739e-06 | 2(Loss) | true |
| simdjson (reflection) | 2502.49 | 0.0398013 | 4338.64ms | 94370 | 640 | 131129 | 35963.5 | 0.114304 | 2.05475 | 8.77354 | 1.42357 | 0.00293459 | 1.97693e-05 | 1.22854e-05 | 3(Loss) | true |
| glaze | 2427.5 | 0.0445272 | 4421.97ms | 94370 | 1280 | 348827 | 37074.4 | 0.107361 | 2.09651 | 9.02229 | 1.8663 | 0.006474 | 2.38258e-05 | 1.29725e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2321.52 | 0.0837194 | 4586.48ms | 94370 | 320 | 337074 | 38766.9 | 0.0783881 | 2.19898 | 9.04878 | 1.58832 | 0.00476568 | 3.21871e-05 | 2.35112e-05 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3751.13 | 0.0191105 | 3473.16ms | 94370 | 4890 | 102800 | 23992.3 | 0.0354577 | 1.37251 | 6.58573 | 0.997394 | 0.00130423 | 7.05789e-06 | 3.77273e-06 | 1(Win) | true |
| glaze | 3272.68 | 0.0964302 | 3826.2ms | 94370 | 80 | 56257.2 | 27499.9 | 0.0241423 | 1.57536 | 7.68555 | 1.57643 | 0.0032713 | 2.38423e-06 | 3.97372e-07 | 2(Loss) | true |
| jsonifier | 3166.62 | 0.0426559 | 3919.14ms | 94370 | 320 | 47031 | 28420.9 | 0.0128223 | 1.62793 | 6.57518 | 1.44848 | 0.00323597 | 2.48358e-06 | 6.29172e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2882.65 | 0.0373245 | 4232.41ms | 94370 | 1280 | 173813 | 31220.7 | 0.0830564 | 1.78295 | 7.75657 | 1.31451 | 0.00472104 | 5.97714e-06 | 3.33627e-06 | 4(Loss) | true |
| simdjson (reflection) | 2833.84 | 0.0178532 | 4266.33ms | 94370 | 4890 | 157203 | 31758.4 | 0.068621 | 1.79526 | 7.81078 | 1.20332 | 0.00229397 | 9.61494e-06 | 5.41531e-06 | 5(Loss) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18726.4 | 0.0483567 | 1210.34ms | 94370 | 2560 | 13826.5 | 4805.96 | 0.164503 | 0.274042 | 0.991035 | 0.14547 | 0.000118889 | 1.13499e-05 | 6.91676e-06 | 1(Win) | true |
| glaze | 6217.8 | 0.0509592 | 2188.26ms | 94370 | 2560 | 139277 | 14474.3 | 0.144086 | 0.816243 | 3.47775 | 0.472735 | 0.000255125 | 8.05506e-06 | 4.52839e-06 | 2(Loss) | true |
| simdjson (reflection) | 547.343 | 0.190273 | 8777.8ms | 94370 | 2560 | 2.50577e+08 | 164427 | 0.0798362 | 9.31279 | 34.821 | 6.36616 | 0.0229685 | 0.00532726 | 0.000625989 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19177.7 | 0.0571619 | 1199.82ms | 94370 | 640 | 4605.41 | 4692.86 | 0.0381043 | 0.270791 | 0.985006 | 0.144103 | 0.000119013 | 2.26833e-06 | 8.60973e-07 | 1(Win) | true |
| glaze | 7251.81 | 0.0954557 | 1988.35ms | 94370 | 320 | 44908.5 | 12410.4 | 0.00571562 | 0.712338 | 3.42499 | 0.460666 | 0.000230807 | 1.78817e-06 | 3.64258e-07 | 2(Loss) | true |
| simdjson (reflection) | 552.383 | 0.17681 | 8761.38ms | 94370 | 2560 | 2.12444e+08 | 162927 | 0.421202 | 9.24793 | 34.8218 | 6.36638 | 0.0227481 | 0.00959886 | 8.26285e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2682.91 | 0.0797121 | 1138.3ms | 11812 | 640 | 7169.09 | 4198.73 | 0.0619619 | 1.93661 | 9.33817 | 1.5748 | 0.00100996 | 2.0239e-05 | 3.4393e-06 | 1(Win) | true |
| glaze | 2011.04 | 0.0435785 | 1281.16ms | 11812 | 320 | 1906.79 | 5601.49 | 0.0957133 | 2.58089 | 12.8662 | 2.45767 | 0.00172838 | 3.22765e-05 | 1.66674e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1964.95 | 0.0258656 | 1298.52ms | 11812 | 4890 | 10752.2 | 5732.86 | 0.0164973 | 2.63787 | 12.7753 | 2.03281 | 0.00445654 | 2.95703e-05 | 7.25407e-06 | 3(Loss) | true |
| simdjson (reflection) | 1309.45 | 0.0356672 | 1586.22ms | 11812 | 1280 | 12050.7 | 8602.67 | 0.0296326 | 3.95118 | 14.7332 | 2.46089 | 0.00859785 | 3.35993e-05 | 1.20375e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1129.15 | 0.0366527 | 1722.6ms | 11812 | 320 | 4278.63 | 9976.34 | 0.0161659 | 4.58211 | 15.6598 | 2.71597 | 0.00740058 | 3.09537e-05 | 1.00533e-05 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3110.88 | 0.092356 | 1128.37ms | 11812 | 40 | 447.374 | 3621.1 | 0.0193349 | 1.6753 | 8.49136 | 1.37809 | 0.000423298 | 8.46597e-06 | 0 | 1(Win) | true |
| glaze | 2326.31 | 0.048526 | 1254.68ms | 11812 | 1280 | 7067.62 | 4842.36 | 0.0470841 | 2.23157 | 11.8219 | 2.21961 | 0.000595991 | 9.52421e-06 | 8.59825e-07 | 2(Loss) | true |
| jsonifier (two-stage) | 2143 | 0.145084 | 1297.37ms | 11812 | 320 | 18612 | 5256.55 | 0.0293001 | 2.42 | 11.9272 | 1.83635 | 0.00427796 | 1.87839e-05 | 6.61404e-06 | 3(Loss) | true |
| simdjson (reflection) | 1380.83 | 0.0431862 | 1590.88ms | 11812 | 1280 | 15887.9 | 8158 | 0.0478308 | 3.7378 | 14.1959 | 2.33068 | 0.00823031 | 1.37572e-05 | 2.64561e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1191.59 | 0.0282444 | 1720.43ms | 11812 | 2560 | 18251.4 | 9453.56 | 0.00197508 | 4.33813 | 14.821 | 2.53082 | 0.00679953 | 1.19714e-05 | 2.51333e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11596.9 | 0.0814498 | 816.391ms | 11812 | 2560 | 1602.46 | 971.367 | 0.0481129 | 0.462591 | 2.44531 | 0.300711 | 8.49904e-05 | 1.06155e-05 | 4.76211e-06 | 1(Win) | true |
| simdjson (reflection) | 10148.7 | 0.0910288 | 828.843ms | 11812 | 2560 | 2613.5 | 1109.97 | 0.0220255 | 0.525751 | 2.44836 | 0.348544 | 0.000100666 | 2.50672e-05 | 8.69746e-06 | 2(Loss) | true |
| glaze | 4230.98 | 0.146939 | 989.047ms | 11812 | 4890 | 74842.5 | 2662.45 | 0.0124839 | 1.23558 | 4.53581 | 0.718338 | 9.15155e-05 | 1.59624e-05 | 5.48816e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12064 | 0.0300311 | 809.642ms | 11812 | 1280 | 100.651 | 933.755 | 0.146037 | 0.445847 | 2.40222 | 0.290721 | 8.47258e-05 | 9.25965e-06 | 4.4314e-06 | 1(Win) | true |
| simdjson (reflection) | 10539.2 | 0.160298 | 829.404ms | 11812 | 1280 | 3757.48 | 1068.84 | 0.250311 | 0.507053 | 2.40222 | 0.337961 | 0.00018645 | 2.04374e-05 | 6.01877e-06 | 2(Loss) | true |
| glaze | 5488.01 | 0.163771 | 926.097ms | 11812 | 4890 | 55258.7 | 2052.62 | 0.175299 | 0.956384 | 4.26414 | 0.658568 | 0.000139403 | 1.89575e-05 | 7.68689e-06 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4190.08 | 0.0308284 | 1442.51ms | 31235 | 4890 | 23488.2 | 7109.18 | 0.0228197 | 1.22177 | 5.79081 | 0.822459 | 0.00153154 | 1.13069e-05 | 2.44207e-06 | 1(Win) | true |
| jsonifier | 4080.79 | 0.0268821 | 1464.14ms | 31235 | 4890 | 18829.2 | 7299.57 | 0.107194 | 1.25522 | 5.74817 | 1.19004 | 0.00229197 | 1.39912e-05 | 3.83661e-06 | 2(Loss) | true |
| simdjson (reflection) | 3062.87 | 0.0242166 | 1701.37ms | 31235 | 4890 | 27124.4 | 9725.53 | 0.0423621 | 1.68397 | 6.4479 | 0.969009 | 0.00350401 | 1.15164e-05 | 3.69912e-06 | 3(Loss) | true |
| glaze | 2930.78 | 0.0386828 | 1744.18ms | 31235 | 1280 | 19786.3 | 10163.9 | 0.014049 | 1.76326 | 8.54774 | 1.56176 | 0.00603797 | 8.9543e-06 | 4.52717e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2594.42 | 0.113464 | 1870.65ms | 31235 | 80 | 13577.1 | 11481.5 | 0.224421 | 1.96079 | 6.79536 | 1.06509 | 0.00298223 | 6.80327e-06 | 1.60077e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4557.44 | 0.0597261 | 1440.42ms | 31235 | 1280 | 19506.5 | 6536.12 | 0.00944182 | 1.13042 | 5.44767 | 0.742981 | 0.00137844 | 5.8278e-06 | 1.00048e-06 | 1(Win) | true |
| jsonifier | 4418.89 | 0.0301046 | 1453.01ms | 31235 | 4890 | 20138.6 | 6741.06 | 0.0675264 | 1.15982 | 5.40519 | 1.11052 | 0.00221067 | 6.02334e-06 | 2.03615e-06 | 2(Loss) | true |
| simdjson (reflection) | 3218.83 | 0.0838601 | 1704.61ms | 31235 | 320 | 19272.9 | 9254.31 | 0.0454725 | 1.60498 | 6.24703 | 0.920058 | 0.00359773 | 5.2025e-06 | 7.00336e-07 | 3(Loss) | true |
| glaze | 3094.07 | 0.0259397 | 1747.01ms | 31235 | 4890 | 30497.4 | 9627.45 | 0.0967039 | 1.65106 | 8.19129 | 1.47901 | 0.00562401 | 5.67634e-06 | 2.154e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2790.66 | 0.0347465 | 1844.32ms | 31235 | 2560 | 35215.3 | 10674.2 | 0.0105237 | 1.84162 | 6.47437 | 0.993885 | 0.00286643 | 1.3594e-05 | 5.97787e-06 | 5(Loss) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18601.4 | 0.117786 | 883.183ms | 31235 | 640 | 2276.99 | 1601.38 | 0.0578936 | 0.283604 | 1.03342 | 0.114103 | 3.21154e-05 | 4.15199e-06 | 6.50312e-07 | 1(Win) | true |
| glaze | 6909.78 | 0.0799496 | 1158.31ms | 31235 | 4890 | 58089.2 | 4310.99 | 0.0682317 | 0.750563 | 3.60051 | 0.476229 | 0.000163671 | 9.42129e-06 | 3.75149e-06 | 2(Loss) | true |
| simdjson (reflection) | 545.699 | 0.143366 | 6157.99ms | 31235 | 2560 | 1.56788e+07 | 54586.9 | 0.306214 | 9.28351 | 36.0948 | 6.44636 | 0.0115691 | 4.99365e-05 | 2.61e-05 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19372.6 | 0.0480081 | 874.776ms | 31235 | 320 | 174.376 | 1537.64 | 0.00609739 | 0.27304 | 1.01511 | 0.109941 | 3.20154e-05 | 3.00144e-06 | 8.00384e-07 | 1(Win) | true |
| glaze | 7639.46 | 0.091015 | 1115.98ms | 31235 | 4890 | 61587.5 | 3899.23 | 0.349657 | 0.679419 | 3.48362 | 0.450424 | 0.000159789 | 1.02069e-05 | 3.55508e-06 | 2(Loss) | true |
| simdjson (reflection) | 552.052 | 0.280593 | 6118.08ms | 31235 | 640 | 1.4671e+07 | 53958.8 | 0.0763311 | 9.27791 | 36.0902 | 6.44518 | 0.0115831 | 4.18701e-05 | 2.57123e-05 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3444.12 | 0.0353485 | 3755.69ms | 108313 | 4890 | 549613 | 29991.8 | 0.0165112 | 1.48548 | 6.99659 | 1.47858 | 0.00194574 | 1.19607e-05 | 7.41055e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2300.64 | 0.0322968 | 5223.82ms | 108313 | 1280 | 269149 | 44898.5 | 0.0124393 | 2.21262 | 9.90744 | 1.77912 | 0.00251836 | 5.56835e-06 | 2.46681e-06 | 2(Loss) | true |
| glaze | 2113.95 | 0.151899 | 5648.45ms | 108313 | 80 | 440732 | 48863.7 | 0.0106941 | 2.4367 | 10.1404 | 1.90792 | 0.00309358 | 9.00169e-06 | 5.07788e-06 | 3(Loss) | true |
| simdjson (reflection) | 1876.4 | 0.0220465 | 6228.51ms | 108313 | 2560 | 377076 | 55049.7 | 0.00876333 | 2.71251 | 12.8609 | 1.96032 | 0.00250501 | 6.95683e-06 | 3.08351e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1414.98 | 0.0824014 | 8081.31ms | 108313 | 40 | 144740 | 73001.2 | 0.0705851 | 3.63987 | 14.4684 | 2.44855 | 0.00324569 | 4.52393e-05 | 4.20079e-05 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4081.82 | 0.0384732 | 3437.5ms | 108313 | 1280 | 121334 | 25306.2 | 0.153072 | 1.25156 | 6.30284 | 1.33117 | 0.00201799 | 3.39006e-06 | 1.83207e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2589.71 | 0.0235773 | 4891.81ms | 108313 | 2560 | 226406 | 39886.8 | 0.0112812 | 1.98086 | 9.21115 | 1.63126 | 0.0025941 | 5.72343e-06 | 3.34318e-06 | 2(Loss) | true |
| glaze | 2357.13 | 0.0375278 | 5308.58ms | 108313 | 1280 | 346188 | 43822.5 | 0.0306042 | 2.18536 | 9.49227 | 1.76988 | 0.00268079 | 6.24636e-06 | 2.71926e-06 | 3(Loss) | true |
| simdjson (reflection) | 1962.86 | 0.115387 | 6216.83ms | 108313 | 30 | 110616 | 52625 | 0.117676 | 2.62322 | 12.545 | 1.88766 | 0.00225519 | 2.7082e-05 | 2.27735e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1520.68 | 0.0114395 | 7708.28ms | 108313 | 2560 | 154576 | 67927.3 | 0.00407531 | 3.3868 | 13.8293 | 2.31662 | 0.00269504 | 1.03433e-05 | 5.99391e-06 | 5(Loss) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19492.9 | 0.0360334 | 1253.54ms | 108313 | 2560 | 9333.76 | 5299.11 | 0.00954703 | 0.266008 | 1.17942 | 0.304857 | 0.000111803 | 4.32052e-06 | 2.43796e-06 | 1(Win) | true |
| simdjson (reflection) | 16086.2 | 0.138614 | 1380.38ms | 108313 | 160 | 12676.3 | 6421.37 | 0.237797 | 0.322397 | 1.49044 | 0.193781 | 0.000194171 | 3.98152e-06 | 2.01961e-06 | 2(Loss) | true |
| glaze | 5764.66 | 0.080866 | 2525.18ms | 108313 | 2560 | 537510 | 17918.7 | 0.0139674 | 0.890921 | 2.95889 | 0.382512 | 0.000159686 | 5.4277e-06 | 2.60746e-06 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19709.3 | 0.0570997 | 1249.23ms | 108313 | 1280 | 11462.9 | 5240.93 | 0.0560773 | 0.263085 | 1.17457 | 0.303759 | 0.000109896 | 2.20715e-06 | 5.4818e-07 | 1(Win) | true |
| simdjson (reflection) | 15916.9 | 0.035834 | 1377.48ms | 108313 | 4890 | 26445.1 | 6489.67 | 0.0835507 | 0.325263 | 1.48547 | 0.192664 | 0.000207529 | 4.11592e-06 | 2.03153e-06 | 2(Loss) | true |
| glaze | 6577.11 | 0.0504088 | 2305.15ms | 108313 | 2560 | 160451 | 15705.3 | 0.0182603 | 0.784628 | 2.91371 | 0.372153 | 0.000155221 | 4.45757e-06 | 2.26485e-06 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3882.55 | 0.0245757 | 5985.68ms | 213963 | 2560 | 427065 | 52555.9 | 0.0119753 | 1.3064 | 5.78912 | 0.945243 | 0.00134179 | 2.49094e-05 | 1.86948e-05 | 1(Win) | true |
| jsonifier | 3484.54 | 0.0203034 | 6593.91ms | 213963 | 4890 | 691251 | 58559 | 0.0101758 | 1.46145 | 5.83859 | 1.37358 | 0.00219867 | 8.64014e-06 | 5.77571e-06 | 2(Loss) | true |
| simdjson (reflection) | 3378.9 | 0.0886135 | 6763.44ms | 213963 | 2560 | 7.33106e+06 | 60389.8 | 0.0326107 | 1.50681 | 7.2082 | 1.02406 | 0.00127701 | 1.93484e-05 | 1.28618e-05 | 3(Loss) | true |
| glaze | 2876.08 | 0.0811172 | 7828.83ms | 213963 | 320 | 1.05986e+06 | 70947.5 | 0.0461704 | 1.77317 | 8.05163 | 1.54186 | 0.00202126 | 5.55003e-06 | 3.65133e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2585.32 | 0.0595666 | 8636.54ms | 213963 | 320 | 707302 | 78926.9 | 0.0758991 | 1.9725 | 8.01423 | 1.26861 | 0.0017561 | 6.32411e-06 | 4.22094e-06 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4308.11 | 0.0184893 | 5643.77ms | 213963 | 4890 | 375021 | 47364.4 | 0.00405776 | 1.18021 | 5.43702 | 0.870515 | 0.00136489 | 2.76982e-06 | 1.53592e-06 | 1(Win) | true |
| jsonifier | 3800.27 | 0.0255457 | 6284.73ms | 213963 | 2560 | 481641 | 53693.8 | 0.086886 | 1.33736 | 5.48747 | 1.29887 | 0.00201325 | 7.35743e-06 | 5.22323e-06 | 2(Loss) | true |
| simdjson (reflection) | 3514.91 | 0.0626343 | 6785.73ms | 213963 | 80 | 105770 | 58053 | 0.00217469 | 1.46564 | 7.05252 | 0.987956 | 0.00123695 | 1.58906e-05 | 1.33785e-05 | 3(Loss) | true |
| glaze | 3102.42 | 0.0527249 | 7564.65ms | 213963 | 640 | 769642 | 65771.6 | 0.0214947 | 1.65366 | 7.72417 | 1.47233 | 0.00181134 | 6.76227e-06 | 3.96535e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2731.55 | 0.0510531 | 8325.48ms | 213963 | 640 | 930858 | 74701.5 | 0.030023 | 1.85374 | 7.69706 | 1.20298 | 0.00147393 | 2.82613e-05 | 2.27405e-05 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24369.6 | 0.0433065 | 1568.46ms | 213963 | 2560 | 33661 | 8373.19 | 0.0397503 | 0.210406 | 0.656464 | 0.154662 | 5.13304e-05 | 2.77684e-06 | 1.59928e-06 | 1(Win) | true |
| glaze | 6191.49 | 0.0949436 | 4024.33ms | 213963 | 4890 | 4.78771e+06 | 32956.7 | 0.305179 | 0.818442 | 3.2118 | 0.397242 | 0.000377069 | 4.82194e-05 | 1.75001e-05 | 2(Loss) | true |
| simdjson (reflection) | 506.161 | 0.262578 | 5220.04ms | 213963 | 640 | 7.17126e+08 | 403134 | 0.361833 | 10.0089 | 36.9056 | 6.81106 | 0.0242367 | 0.19664 | 0.000146265 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 24724.3 | 0.0608419 | 1560.69ms | 213963 | 30 | 756.409 | 8253.07 | 0.0444082 | 0.209462 | 0.653917 | 0.154083 | 5.20339e-05 | 2.18106e-06 | 1.24632e-06 | 1(Win) | true |
| glaze | 7507.21 | 0.259918 | 3440.67ms | 213963 | 160 | 798570 | 27180.7 | 0.0540993 | 0.675555 | 3.18456 | 0.391091 | 0.000365133 | 1.13922e-06 | 1.75264e-07 | 2(Loss) | true |
| simdjson (reflection) | 504.939 | 0.539047 | 5266.45ms | 213963 | 160 | 7.59229e+08 | 404110 | 0.0428347 | 10.0882 | 36.8871 | 6.80613 | 0.0242872 | 0.197049 | 0.000993221 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 755.887 | 0.194635 | 7132.62ms | 1834197 | 30 | 6.0861e+08 | 2.31414e+06 | 0.504139 | 6.6442 | 25.8937 | 5.46646 | 0.0392885 | 0.0811599 | 0.000606787 | 1(Win) | true |
| simdjson (reflection) | 740.215 | 0.086075 | 7343.28ms | 1834197 | 80 | 3.30994e+08 | 2.36313e+06 | 0.0482416 | 6.85849 | 30.8698 | 5.22799 | 0.0337727 | 0.134994 | 6.81906e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 728.096 | 0.0776253 | 7485.82ms | 1834197 | 160 | 5.56469e+08 | 2.40247e+06 | 0.0175357 | 6.94062 | 29.7109 | 6.05133 | 0.0319857 | 0.143571 | 0.00110829 | 3(Loss) | true |
| glaze | 661.523 | 0.0910406 | 8264.4ms | 1834197 | 160 | 9.2724e+08 | 2.64424e+06 | 0.341763 | 7.73064 | 31.9282 | 6.36382 | 0.0324468 | 0.082449 | 0.00113435 | 4(Loss) | true |
| simdjson (ondemand) | 619.544 | 0.115825 | 8783.42ms | 1834197 | 80 | 8.55543e+08 | 2.82341e+06 | 0.0995536 | 8.251 | 33.3307 | 6.10892 | 0.0418191 | 0.146155 | 0.000167757 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 843.526 | 0.0784785 | 7123.37ms | 1834197 | 160 | 4.23756e+08 | 2.07371e+06 | 0.0882045 | 6.01262 | 22.8879 | 4.76646 | 0.0385993 | 0.0554568 | 0.00011517 | 1(Win) | true |
| simdjson (reflection) | 833.761 | 0.0957421 | 7079.63ms | 1834197 | 40 | 1.61389e+08 | 2.098e+06 | 0.0245795 | 6.12326 | 27.8451 | 4.51125 | 0.0292371 | 0.111267 | 6.57372e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 798.027 | 0.12021 | 7453.79ms | 1834197 | 40 | 2.77713e+08 | 2.19194e+06 | 0.125982 | 6.34576 | 26.7016 | 5.35129 | 0.0313178 | 0.117838 | 7.77043e-05 | 3(Loss) | true |
| glaze | 721.257 | 0.0940744 | 8230.98ms | 1834197 | 80 | 4.16433e+08 | 2.42525e+06 | 0.0150069 | 7.09888 | 28.9171 | 5.66249 | 0.0314093 | 0.0591643 | 0.00144732 | 4(Loss) | true |
| simdjson (ondemand) | 685.389 | 0.0814571 | 8612.47ms | 1834197 | 80 | 3.45753e+08 | 2.55217e+06 | 0.00502441 | 7.5039 | 30.3095 | 5.40655 | 0.037567 | 0.11723 | 7.94762e-05 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1313.26 | 0.025264 | 8459.68ms | 1834197 | 40 | 4.52954e+06 | 1.33197e+06 | 0.0552112 | 3.91761 | 11.8454 | 0.765596 | 0.00373764 | 0.0594267 | 0.000132619 | 1(Win) | true |
| glaze | 1002.56 | 0.169327 | 5433.99ms | 1833577 | 160 | 1.39558e+09 | 1.74418e+06 | 0.106414 | 5.11434 | 15.8266 | 1.02014 | 0.000916883 | 0.0492324 | 0.000130408 | 2(Loss) | true |
| simdjson (reflection) | 894.633 | 0.0485347 | 6378.34ms | 1922245 | 160 | 1.58253e+08 | 2.0491e+06 | 0.0243614 | 5.7447 | 18.1209 | 2.02074 | 0.0273634 | 0.0501077 | 0.000304036 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1317.93 | 0.0110919 | 8442.71ms | 1834197 | 320 | 6.93543e+06 | 1.32726e+06 | 0.253456 | 3.90327 | 11.8452 | 0.765556 | 0.00378106 | 0.0593711 | 0.000160976 | 1(Win) | true |
| glaze | 1017.68 | 0.229699 | 5347.87ms | 1833577 | 160 | 2.49237e+09 | 1.71826e+06 | 0.278277 | 5.05441 | 15.8258 | 1.01998 | 0.00092293 | 0.0490528 | 8.45376e-05 | 2(Loss) | true |
| simdjson (reflection) | 895.655 | 0.0119599 | 6376.67ms | 1922245 | 160 | 9.58765e+06 | 2.04676e+06 | 0.0192973 | 5.74158 | 18.1207 | 2.0207 | 0.0273485 | 0.0500586 | 0.00010014 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3388.09 | 0.134569 | 8773.34ms | 9930848 | 40 | 5.6599e+08 | 2.79532e+06 | 0.00824334 | 1.51274 | 6.83221 | 1.01047 | 0.0059028 | 0.0517093 | 0.000873251 | 1(Win) | true |
| jsonifier | 3357.02 | 0.0799552 | 8828.68ms | 9930848 | 160 | 8.14102e+08 | 2.82119e+06 | 0.213683 | 1.50737 | 6.74504 | 1.53844 | 0.00737172 | 0.0298559 | 0.00143551 | 2(Loss) | true |
| jsonifier (two-stage) | 3334.12 | 0.0747551 | 8839.48ms | 9930848 | 160 | 7.21459e+08 | 2.84057e+06 | 0.114721 | 1.51474 | 6.43815 | 1.1549 | 0.00654189 | 0.0541928 | 0.00320453 | 3(Loss) | true |
| simdjson (ondemand) | 2816.98 | 0.265647 | 5071.38ms | 9930848 | 40 | 3.19061e+09 | 3.36204e+06 | 0.996276 | 1.79869 | 7.28607 | 1.17314 | 0.00735113 | 0.0535094 | 0.00494369 | 4(Loss) | true |
| glaze | 2640.4 | 0.141704 | 5418.54ms | 9930848 | 40 | 1.03336e+09 | 3.58687e+06 | 0.400871 | 1.92744 | 9.14585 | 1.80148 | 0.00672074 | 0.0290809 | 0.0013223 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3722.4 | 0.0586638 | 8494.81ms | 9930848 | 160 | 3.5644e+08 | 2.54427e+06 | 0.196282 | 1.37243 | 6.27239 | 0.878054 | 0.00505891 | 0.0467165 | 0.00078053 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 3608.76 | 0.107716 | 8828.99ms | 9930848 | 80 | 6.39309e+08 | 2.62439e+06 | 0.157524 | 1.40653 | 6.18958 | 1.4094 | 0.00731756 | 0.0249873 | 0.000722937 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3603.86 | 0.0775903 | 8861.14ms | 9930848 | 160 | 6.6523e+08 | 2.62796e+06 | 0.0968013 | 1.40351 | 5.88252 | 1.02567 | 0.00635534 | 0.0493442 | 0.00415234 | 2(Tie) | true |
| simdjson (ondemand) | 3077.54 | 0.225606 | 10182.7ms | 9930848 | 30 | 1.44606e+09 | 3.07739e+06 | 0.189135 | 1.64186 | 6.72747 | 1.04338 | 0.00658171 | 0.0477226 | 0.00350419 | 4(Loss) | true |
| glaze | 2798 | 0.20509 | 5449.49ms | 9930848 | 30 | 1.44573e+09 | 3.38485e+06 | 0.254578 | 1.82235 | 8.58947 | 1.67197 | 0.00654039 | 0.0247038 | 0.00171245 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6679.95 | 0.0458694 | 8997.2ms | 9930848 | 320 | 1.35339e+08 | 1.4178e+06 | 0.0374669 | 0.769544 | 2.26987 | 0.143472 | 0.000416086 | 0.0250113 | 0.000450983 | 1(Win) | true |
| glaze | 3753.7 | 0.107321 | 7888.47ms | 9930228 | 80 | 5.86483e+08 | 2.5229e+06 | 0.0437387 | 1.37032 | 4.43055 | 0.415402 | 0.000734978 | 0.0416762 | 0.00257258 | 2(Loss) | true |
| simdjson (reflection) | 196.428 | 0.0820504 | 14663.9ms | 10018896 | 30 | 4.77876e+10 | 4.86425e+07 | 0.415396 | 21.4698 | 69.8624 | 13.4285 | 0.0634374 | 0.270584 | 0.123138 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6686.9 | 0.0205273 | 8993.31ms | 9930848 | 160 | 1.3524e+07 | 1.41632e+06 | 0.0783588 | 0.769091 | 2.26984 | 0.143465 | 0.00041307 | 0.0249901 | 0.000316472 | 1(Win) | true |
| glaze | 4156.02 | 0.175613 | 7142.82ms | 9930228 | 30 | 4.80395e+08 | 2.27867e+06 | 0.209771 | 1.23698 | 4.43026 | 0.415337 | 0.000739036 | 0.0224035 | 0.000644443 | 2(Loss) | true |
| simdjson (reflection) | 196.956 | 0.0960781 | 14538.4ms | 10018896 | 30 | 6.51733e+10 | 4.85121e+07 | 0.0418265 | 21.4108 | 69.8367 | 13.4258 | 0.0629534 | 0.270944 | 0.127469 | 3(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 774.841 | 0.141752 | 7060.78ms | 1834197 | 40 | 4.09624e+08 | 2.25753e+06 | 0.024227 | 6.59795 | 25.446 | 5.31681 | 0.0407686 | 0.0839875 | 0.000597332 | 1(Win) | true |
| jsonifier (two-stage) | 734.176 | 0.170656 | 7415.3ms | 1834197 | 30 | 4.95974e+08 | 2.38257e+06 | 0.307302 | 6.8584 | 29.297 | 5.9373 | 0.03255 | 0.146278 | 0.00159383 | 2(Loss) | true |
| simdjson (reflection) | 726.845 | 0.0621182 | 7474.49ms | 1834197 | 160 | 3.57574e+08 | 2.4066e+06 | 0.271443 | 7.00746 | 30.7961 | 5.23332 | 0.0355184 | 0.136465 | 0.000298175 | 3(Loss) | true |
| glaze | 653.226 | 0.068001 | 8303.04ms | 1834197 | 160 | 5.30537e+08 | 2.67783e+06 | 0.0370396 | 7.81957 | 31.7439 | 6.35383 | 0.033026 | 0.0835981 | 0.000922519 | 4(Loss) | true |
| simdjson (ondemand) | 614.381 | 0.267967 | 8875.31ms | 1834197 | 30 | 1.74623e+09 | 2.84714e+06 | 0.33116 | 8.33681 | 33.2986 | 6.09768 | 0.0423748 | 0.14817 | 0.00294956 | 5(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 860.215 | 0.179876 | 7073.31ms | 1834197 | 40 | 5.35163e+08 | 2.03348e+06 | 0.0916857 | 5.90445 | 22.4701 | 4.62783 | 0.0399163 | 0.0575144 | 0.0001832 | 1(Win) | true |
| simdjson (reflection) | 821.25 | 0.123179 | 7262.53ms | 1834197 | 30 | 2.06507e+08 | 2.12996e+06 | 0.39077 | 6.18901 | 27.7876 | 4.53134 | 0.0303163 | 0.111491 | 0.000201396 | 2(Loss) | true |
| jsonifier (two-stage) | 813.485 | 0.137412 | 7408.18ms | 1834197 | 30 | 2.61915e+08 | 2.15029e+06 | 0.0314041 | 6.23757 | 26.3239 | 5.24922 | 0.0318651 | 0.119487 | 0.000207266 | 3(Loss) | true |
| glaze | 715.39 | 0.0534076 | 8334.08ms | 1834197 | 160 | 2.72855e+08 | 2.44514e+06 | 0.179974 | 7.16621 | 28.7669 | 5.66369 | 0.0317077 | 0.0596215 | 0.000761427 | 4(Loss) | true |
| simdjson (ondemand) | 679.001 | 0.0849312 | 8689.53ms | 1834197 | 160 | 7.65958e+08 | 2.57618e+06 | 0.156496 | 7.5198 | 30.31 | 5.40657 | 0.0374587 | 0.118084 | 0.00144254 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1332.57 | 0.0351764 | 8322.95ms | 1834197 | 160 | 3.41141e+07 | 1.31267e+06 | 0.00415011 | 3.8565 | 11.7858 | 0.76544 | 0.00288902 | 0.0611354 | 0.000364758 | 1(Win) | true |
| glaze | 970.131 | 0.260545 | 5601.89ms | 1833577 | 160 | 3.52878e+09 | 1.80247e+06 | 0.539923 | 5.25429 | 15.8114 | 1.02018 | 0.000942359 | 0.0819501 | 0.000569086 | 2(Loss) | true |
| simdjson (reflection) | 896.539 | 0.0679563 | 6365.03ms | 1922245 | 160 | 3.08929e+08 | 2.04475e+06 | 0.136949 | 5.6868 | 18.1187 | 2.02075 | 0.0256249 | 0.05162 | 0.000659827 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1333.93 | 0.0588932 | 8331.89ms | 1834197 | 30 | 1.78929e+07 | 1.31134e+06 | 0.111923 | 3.85407 | 11.7856 | 0.765401 | 0.00290772 | 0.0611012 | 9.31016e-05 | 1(Win) | true |
| glaze | 1022.34 | 0.26796 | 5331.29ms | 1833577 | 160 | 3.36102e+09 | 1.71043e+06 | 0.610706 | 5.03357 | 15.8105 | 1.01998 | 0.000936305 | 0.0494018 | 0.000112066 | 2(Loss) | true |
| simdjson (reflection) | 891.334 | 0.0603137 | 6374.17ms | 1922245 | 160 | 2.462e+08 | 2.05669e+06 | 0.526645 | 5.6905 | 18.1185 | 2.02071 | 0.0256069 | 0.0516921 | 0.000311732 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 3333.97 | 0.0999716 | 8843.42ms | 9930848 | 80 | 6.45196e+08 | 2.84069e+06 | 0.0999746 | 1.53195 | 6.8176 | 1.01146 | 0.00622721 | 0.0518745 | 0.000287255 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3332.03 | 0.146998 | 8900.23ms | 9930848 | 40 | 6.98293e+08 | 2.84235e+06 | 0.391019 | 1.5079 | 6.36231 | 1.13406 | 0.00666488 | 0.054732 | 0.00263105 | 1(Tie) | true |
| jsonifier | 3305.35 | 0.113136 | 8903.71ms | 9930848 | 80 | 8.40675e+08 | 2.86529e+06 | 0.0508637 | 1.52062 | 6.66568 | 1.51676 | 0.0075814 | 0.0301124 | 0.00274229 | 3(Loss) | true |
| simdjson (ondemand) | 2904.49 | 0.0864367 | 10230.2ms | 9930848 | 80 | 6.35504e+08 | 3.26074e+06 | 0.199036 | 1.77059 | 7.27969 | 1.17104 | 0.00747614 | 0.0538112 | 0.000480247 | 4(Loss) | true |
| glaze | 2602.89 | 0.0671983 | 5488.63ms | 9930848 | 80 | 4.78266e+08 | 3.63857e+06 | 0.272855 | 1.93939 | 9.13978 | 1.79947 | 0.00674157 | 0.0293147 | 0.00345933 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3695.74 | 0.0888611 | 8672.29ms | 9930848 | 160 | 8.29687e+08 | 2.56263e+06 | 0.458302 | 1.37732 | 5.81319 | 1.00695 | 0.00649608 | 0.0497537 | 0.000331251 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3692.66 | 0.0935355 | 8625.64ms | 9930848 | 160 | 9.20802e+08 | 2.56476e+06 | 0.517576 | 1.38111 | 6.26166 | 0.881739 | 0.00528805 | 0.0467242 | 0.000828497 | 1(Tie) | true |
| jsonifier | 3604.43 | 0.186567 | 8875.4ms | 9930848 | 30 | 7.20928e+08 | 2.62754e+06 | 0.261739 | 1.40897 | 6.11603 | 1.3895 | 0.00742782 | 0.0250579 | 0.00523453 | 3(Loss) | true |
| simdjson (ondemand) | 3142 | 0.0995682 | 10084.1ms | 9930848 | 80 | 7.20597e+08 | 3.01426e+06 | 0.265913 | 1.62125 | 6.7273 | 1.04329 | 0.00656124 | 0.0479123 | 0.0001149 | 4(Loss) | true |
| glaze | 2748.33 | 0.128506 | 5500.21ms | 9930848 | 40 | 7.84404e+08 | 3.44601e+06 | 0.0434579 | 1.8451 | 8.58976 | 1.67197 | 0.00655827 | 0.0248858 | 0.00745378 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6682.07 | 0.0276931 | 8995.05ms | 9930848 | 160 | 2.46498e+07 | 1.41734e+06 | 0.00950764 | 0.769758 | 2.27264 | 0.143459 | 0.000422185 | 0.0250152 | 5.19474e-05 | 1(Win) | true |
| glaze | 3158.97 | 0.231734 | 9386.88ms | 9930228 | 40 | 1.93049e+09 | 2.99788e+06 | 0.30965 | 1.621 | 4.42787 | 0.414461 | 0.000697106 | 0.0755429 | 0.0102948 | 2(Loss) | true |
| simdjson (reflection) | 196.249 | 0.137714 | 14518.9ms | 10018896 | 30 | 1.34866e+11 | 4.8687e+07 | 1.01234 | 21.1607 | 69.8186 | 13.4251 | 0.060323 | 0.265165 | 0.120165 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6673.76 | 0.0362116 | 8991.32ms | 9930848 | 80 | 2.1126e+07 | 1.41911e+06 | 0.0667808 | 0.77051 | 2.2726 | 0.143452 | 0.000424351 | 0.025009 | 0.000283604 | 1(Win) | true |
| glaze | 4179.78 | 0.15561 | 7065.81ms | 9930228 | 80 | 9.94433e+08 | 2.26572e+06 | 0.0460281 | 1.23053 | 4.42747 | 0.414372 | 0.00072402 | 0.0224069 | 1.88956e-05 | 2(Loss) | true |
| simdjson (reflection) | 203.101 | 1.11748 | 14032.6ms | 10018896 | 30 | 8.29124e+12 | 4.70445e+07 | 0.498135 | 21.1531 | 69.8316 | 13.4261 | 0.0602649 | 0.279553 | 0.14198 | 3(Loss) | true |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1221.14 | 0.073549 | 6519.87ms | 642697 | 160 | 2.18051e+07 | 501929 | 0.1274 | 4.19324 | 18.5677 | 3.36206 | 0.0138665 | 0.0249024 | 4.46167e-05 | 1(Win) | true |
| simdjson (ondemand) | 1190.4 | 0.0666165 | 6662.86ms | 642697 | 320 | 3.76477e+07 | 514887 | 0.0807074 | 4.2724 | 20.7504 | 3.19055 | 0.0124796 | 0.0663997 | 9.6804e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 1169.39 | 0.0778361 | 6809.77ms | 642697 | 640 | 1.0652e+08 | 524138 | 0.1793 | 4.34552 | 20.4744 | 3.82607 | 0.0170365 | 0.0529407 | 7.69973e-05 | 3(Loss) | true |
| simdjson (reflection) | 1161.11 | 0.102168 | 6782.81ms | 642697 | 80 | 2.32693e+07 | 527876 | 0.0868672 | 4.36478 | 21.3927 | 3.17821 | 0.0116201 | 0.0558455 | 1.85741e-05 | 4(Loss) | true |
| jsonifier | 1087.11 | 0.103546 | 7264.02ms | 642697 | 160 | 5.4532e+07 | 563810 | 0.124427 | 4.69136 | 18.1226 | 3.56496 | 0.0400746 | 0.0128765 | 4.44514e-05 | 5(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| glaze | 1344.98 | 0.0520251 | 6246.12ms | 642697 | 320 | 1.7987e+07 | 455713 | 0.245551 | 3.80562 | 17.3988 | 3.10144 | 0.0131449 | 0.00168514 | 1.00893e-05 | 1(Win) | true |
| simdjson (ondemand) | 1318.99 | 0.167913 | 6318.61ms | 642697 | 320 | 1.94828e+08 | 464693 | 0.166196 | 3.8601 | 19.5417 | 2.91955 | 0.0112838 | 0.0172565 | 4.7607e-05 | 2(Loss) | true |
| simdjson (reflection) | 1234.18 | 0.0445992 | 6737.36ms | 642697 | 640 | 3.1397e+07 | 496623 | 0.018284 | 4.12484 | 20.2461 | 2.91878 | 0.0109977 | 0.0473358 | 6.91131e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1227.22 | 0.121046 | 6795.81ms | 642697 | 320 | 1.16955e+08 | 499440 | 0.130396 | 4.13479 | 19.3648 | 3.57662 | 0.0167171 | 0.0463856 | 1.10715e-05 | 4(Loss) | true |
| jsonifier | 1142.24 | 0.133563 | 7205.78ms | 642697 | 80 | 4.10918e+07 | 536596 | 0.173125 | 4.44938 | 17.013 | 3.31552 | 0.0398744 | 0.0104368 | 4.64838e-06 | 5(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2423.19 | 0.0418818 | 6684.46ms | 642697 | 640 | 7.18238e+06 | 252941 | 0.0733021 | 2.11264 | 7.23638 | 0.690313 | 5.6031e-05 | 0.00233327 | 8.18086e-06 | 1(Win) | true |
| glaze | 1614.32 | 0.111084 | 9908.21ms | 642692 | 1280 | 2.27688e+08 | 379676 | 0.602483 | 3.12447 | 10.1214 | 0.666384 | 0.000138452 | 0.0421146 | 5.15775e-06 | 2(Loss) | true |
| simdjson (reflection) | 1281.74 | 0.0224992 | 6157.42ms | 643373 | 640 | 7.42406e+06 | 478700 | 0.196097 | 3.94389 | 14.5168 | 1.45439 | 0.00502153 | 0.00175013 | 5.25429e-05 | 3(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2402.39 | 0.0319255 | 6692.23ms | 642697 | 1280 | 8.49202e+06 | 255131 | 0.136038 | 2.11377 | 7.23552 | 0.690117 | 5.5659e-05 | 0.00236439 | 9.96898e-06 | 1(Win) | true |
| glaze | 1754.58 | 0.0783353 | 9120.92ms | 642692 | 160 | 1.1981e+07 | 349325 | 0.0232537 | 2.92789 | 10.1192 | 0.665886 | 0.000137362 | 0.00412026 | 1.56179e-05 | 2(Loss) | true |
| simdjson (reflection) | 1279.21 | 0.0321026 | 6162.2ms | 643373 | 30 | 711285 | 479646 | 0.0217127 | 3.94817 | 14.5159 | 1.45419 | 0.00538086 | 0.0025485 | 2.15531e-05 | 3(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2189.57 | 0.0606089 | 6924.77ms | 1225964 | 320 | 3.35167e+07 | 533972 | 0.241971 | 2.31766 | 11.5494 | 1.68893 | 0.00509725 | 0.0629137 | 3.16027e-05 | 1(Win) | true |
| simdjson (reflection) | 2156.44 | 0.154579 | 7015.83ms | 1225964 | 40 | 2.80959e+07 | 542176 | 0.123848 | 2.3718 | 11.8868 | 1.68263 | 0.00491742 | 0.0593386 | 2.45725e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2102.32 | 0.363204 | 7260.55ms | 1225964 | 30 | 1.22399e+08 | 556132 | 0.182399 | 2.40756 | 11.4403 | 2.04401 | 0.00728404 | 0.0612966 | 2.33286e-05 | 3(Loss) | true |
| jsonifier | 1841.33 | 0.0590452 | 8178.36ms | 1225964 | 320 | 4.49792e+07 | 634960 | 0.0341264 | 2.77588 | 12.5508 | 2.76666 | 0.0171557 | 0.0251027 | 3.48986e-05 | 4(Loss) | true |
| glaze | 1827.56 | 0.122073 | 8173.84ms | 1225964 | 30 | 1.82966e+07 | 639743 | 0.0148423 | 2.76533 | 12.5996 | 2.53139 | 0.0137857 | 0.0309088 | 4.4917e-05 | 5(Loss) | true |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2440.05 | 0.0499268 | 6538.76ms | 1225964 | 640 | 3.66273e+07 | 479159 | 0.0920341 | 2.08899 | 10.9163 | 1.54707 | 0.00449195 | 0.0355079 | 2.40895e-05 | 1(Win) | true |
| simdjson (reflection) | 2291.52 | 0.0489541 | 6926.31ms | 1225964 | 320 | 1.99635e+07 | 510217 | 0.181673 | 2.24238 | 11.2856 | 1.54668 | 0.00461934 | 0.0522821 | 2.96705e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 2159.54 | 0.382966 | 7283.96ms | 1225964 | 30 | 1.28966e+08 | 541397 | 0.0250464 | 2.32949 | 10.8589 | 1.91333 | 0.00706494 | 0.0558186 | 3.63523e-05 | 3(Loss) | true |
| glaze | 1999.73 | 0.0421632 | 7837.54ms | 1225964 | 640 | 3.88921e+07 | 584665 | 0.15568 | 2.55398 | 11.987 | 2.39487 | 0.0134629 | 0.00975122 | 1.36296e-05 | 4(Loss) | true |
| jsonifier | 1914.56 | 0.111552 | 8218.57ms | 1225964 | 80 | 3.7125e+07 | 610675 | 0.090633 | 2.67044 | 11.9692 | 2.6359 | 0.0169965 | 0.0224573 | 2.93137e-05 | 5(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4533.28 | 0.155693 | 6701.84ms | 1225964 | 30 | 4.83718e+06 | 257908 | 0.125082 | 1.11947 | 3.83172 | 0.361895 | 4.74457e-05 | 0.0134646 | 8.75502e-05 | 1(Win) | true |
| glaze | 2656.37 | 0.102551 | 5720.79ms | 1225970 | 320 | 6.51947e+07 | 440140 | 0.237808 | 1.91151 | 6.73862 | 0.654419 | 0.000122192 | 0.0350653 | 9.75248e-06 | 2(Loss) | true |
| simdjson (reflection) | 172.14 | 0.0969668 | 10245.1ms | 1226640 | 80 | 3.47382e+09 | 6.79572e+06 | 0.359302 | 29.6545 | 106.259 | 19.7455 | 0.120448 | 0.596357 | 0.0137706 | 3(Loss) | true |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4602.39 | 0.0294392 | 6680.14ms | 1225964 | 320 | 1.78975e+06 | 254036 | 0.0192505 | 1.11773 | 3.83126 | 0.361792 | 4.97823e-05 | 0.0131569 | 1.52686e-06 | 1(Win) | true |
| glaze | 2850.53 | 0.03365 | 5320ms | 1225970 | 320 | 6.09578e+06 | 410161 | 0.0526168 | 1.80194 | 6.73706 | 0.654078 | 0.000122729 | 0.012544 | 5.92133e-06 | 2(Loss) | true |
| simdjson (reflection) | 170.156 | 0.154221 | 10344.5ms | 1226640 | 40 | 4.49665e+09 | 6.87497e+06 | 0.0327477 | 29.9529 | 106.259 | 19.7455 | 0.120765 | 0.595901 | 0.0472337 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1455.66 | 0.0477546 | 7038.12ms | 409725 | 640 | 1.05167e+07 | 268432 | 0.000185103 | 3.51324 | 13.6013 | 2.44663 | 0.0218634 | 0.020464 | 0.000185445 | 1(Win) | true |
| jsonifier (two-stage) | 1402.34 | 0.0797866 | 7317.18ms | 409725 | 160 | 7.90781e+06 | 278637 | 0.00986372 | 3.6155 | 16.1156 | 2.7538 | 0.0133413 | 0.0597261 | 0.000374382 | 2(Loss) | true |
| glaze | 1198.49 | 0.073658 | 8532.8ms | 409725 | 1280 | 7.38187e+07 | 326031 | 0.0668327 | 4.23783 | 17.2023 | 3.36648 | 0.0249704 | 0.0289069 | 4.24427e-05 | 3(Loss) | true |
| simdjson (reflection) | 1191.04 | 0.116122 | 8653.56ms | 409725 | 80 | 1.16105e+07 | 328070 | 0.0810679 | 4.28077 | 16.98 | 2.95582 | 0.013293 | 0.0509818 | 0.000134023 | 4(Loss) | true |
| simdjson (ondemand) | 855.369 | 0.108167 | 5948.13ms | 409725 | 160 | 3.90651e+07 | 456813 | 0.0682471 | 5.93511 | 19.3551 | 3.51185 | 0.0154212 | 0.0673432 | 0.000390002 | 5(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2066.63 | 0.0326197 | 6269.28ms | 409725 | 1280 | 4.86888e+06 | 189073 | 0.139026 | 2.47142 | 10.2848 | 1.78306 | 0.0158463 | 0.00136798 | 1.79026e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1965.23 | 0.0377453 | 6472.23ms | 409725 | 1280 | 7.20933e+06 | 198829 | 0.340547 | 2.56571 | 12.7975 | 2.09 | 0.00792133 | 0.0119903 | 5.26954e-05 | 2(Loss) | true |
| glaze | 1502.66 | 0.156191 | 8048.92ms | 409725 | 320 | 5.27872e+07 | 260035 | 0.141214 | 3.38199 | 14.3265 | 2.75784 | 0.0204915 | 0.00841102 | 5.61962e-05 | 3(Loss) | true |
| simdjson (reflection) | 1463.29 | 0.113155 | 8177.86ms | 409725 | 160 | 1.46082e+07 | 267032 | 0.131181 | 3.45056 | 14.4759 | 2.37323 | 0.00617975 | 0.022279 | 2.08982e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1053.68 | 0.123945 | 5396.76ms | 409725 | 640 | 1.35211e+08 | 370839 | 0.338875 | 4.81654 | 16.3464 | 2.87034 | 0.00663591 | 0.0104631 | 3.33951e-05 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13810.1 | 0.0681623 | 3580.42ms | 409725 | 1280 | 476090 | 28294.1 | 0.119857 | 0.363899 | 1.91764 | 0.268597 | 5.96837e-05 | 0.00143131 | 8.82642e-06 | 1(Win) | true |
| simdjson (reflection) | 11632.9 | 0.0248924 | 4143.23ms | 409725 | 4890 | 341864 | 33589.7 | 0.066998 | 0.435897 | 2.3896 | 0.298898 | 0.000840927 | 0.000311419 | 1.68061e-05 | 2(Loss) | true |
| glaze | 3669.26 | 0.39272 | 5906ms | 409725 | 640 | 1.11937e+08 | 106491 | 0.283219 | 1.37491 | 5.57961 | 0.872012 | 0.010185 | 0.0244685 | 2.22787e-05 | 3(Loss) | true |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13939 | 0.0745805 | 3590.2ms | 409725 | 320 | 139869 | 28032.4 | 0.0890808 | 0.363188 | 1.91631 | 0.268292 | 6.59207e-05 | 0.00167471 | 9.85417e-06 | 1(Win) | true |
| simdjson (reflection) | 11638.1 | 0.0784586 | 4098.66ms | 409725 | 40 | 27756.4 | 33574.6 | 0.0636733 | 0.434862 | 2.38835 | 0.298615 | 0.000936482 | 0.000197083 | 6.58979e-06 | 2(Loss) | true |
| glaze | 4096.11 | 0.0822719 | 5293.59ms | 409725 | 2560 | 1.57683e+07 | 95394 | 0.0497536 | 1.2294 | 5.56313 | 0.868285 | 0.0101597 | 0.000566414 | 5.11299e-05 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2393.2 | 0.537556 | 8252.13ms | 785750 | 640 | 1.81317e+09 | 313116 | 0.0239585 | 2.09997 | 9.03474 | 1.45344 | 0.0076806 | 0.0555542 | 0.000155964 | 1(Win) | true |
| simdjson (reflection) | 2106.84 | 0.125451 | 9306.56ms | 785750 | 160 | 3.18549e+07 | 355675 | 0.000207352 | 2.39948 | 9.5181 | 1.57014 | 0.00770503 | 0.0488015 | 0.000209855 | 2(Loss) | true |
| jsonifier | 2090.26 | 0.0571708 | 9402.5ms | 785750 | 1280 | 5.37684e+07 | 358496 | 0.331038 | 2.41477 | 9.15717 | 1.83922 | 0.0123621 | 0.0274105 | 0.000229747 | 3(Loss) | true |
| glaze | 1837.06 | 0.0856688 | 5269.68ms | 785750 | 320 | 3.90766e+07 | 407906 | 0.152694 | 2.74384 | 11.6421 | 2.29981 | 0.013375 | 0.0210177 | 6.59481e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1547.47 | 0.0853634 | 6437.73ms | 785750 | 40 | 6.83481e+06 | 484241 | 0.0451104 | 3.26286 | 10.7571 | 1.86027 | 0.00893112 | 0.0580535 | 0.000384728 | 5(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3252.07 | 0.412394 | 7637.2ms | 785750 | 40 | 3.6119e+07 | 230423 | 0.381972 | 1.54532 | 7.30791 | 1.10814 | 0.00493131 | 0.0253667 | 0.000583169 | 1(Win) | true |
| jsonifier | 2706.92 | 0.0368327 | 8509.52ms | 785750 | 640 | 6.65373e+06 | 276827 | 0.0600702 | 1.87289 | 7.42902 | 1.4937 | 0.00925383 | 0.00386125 | 8.90491e-05 | 2(Loss) | true |
| simdjson (reflection) | 2588.05 | 0.0397118 | 8759.32ms | 785750 | 1280 | 1.69228e+07 | 289542 | 0.0571942 | 1.95332 | 8.21387 | 1.26677 | 0.00394232 | 0.0265925 | 5.34034e-05 | 3(Loss) | true |
| glaze | 2220.68 | 0.24567 | 5012.79ms | 785750 | 30 | 2.06168e+07 | 337441 | 0.249778 | 2.27469 | 10.143 | 1.98261 | 0.0108134 | 0.00564234 | 2.98229e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1904.8 | 0.0975842 | 5713.54ms | 785750 | 40 | 5.89506e+06 | 393400 | 0.154924 | 2.65091 | 9.18716 | 1.52554 | 0.00403805 | 0.0171823 | 5.15431e-05 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18493.4 | 0.0600044 | 4849.44ms | 785750 | 80 | 47292.7 | 40519.9 | 0.00438075 | 0.273615 | 1.09816 | 0.140078 | 0.00010062 | 0.00878291 | 1.28858e-05 | 1(Win) | true |
| glaze | 4846.11 | 0.13108 | 8436.22ms | 785750 | 640 | 2.62926e+07 | 154629 | 0.267027 | 1.04544 | 4.36993 | 0.633741 | 0.00593003 | 0.0573549 | 2.39222e-05 | 2(Loss) | true |
| simdjson (reflection) | 527.769 | 0.451352 | 9050.67ms | 785750 | 160 | 6.57102e+09 | 1.41984e+06 | 0.664307 | 9.5472 | 35.8082 | 6.58882 | 0.0321901 | 0.356251 | 0.00223435 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 18530.9 | 0.0909684 | 4845.51ms | 785750 | 80 | 108255 | 40437.9 | 0.0450488 | 0.272958 | 1.09747 | 0.13992 | 4.028e-05 | 0.00845377 | 1.35221e-05 | 1(Win) | true |
| glaze | 5801.45 | 0.0514942 | 7024.41ms | 785750 | 2560 | 1.13254e+07 | 129166 | 0.150298 | 0.872222 | 4.36041 | 0.631537 | 0.00584236 | 0.0121 | 6.19382e-05 | 2(Loss) | true |
| simdjson (reflection) | 518.663 | 0.341732 | 9085.23ms | 785750 | 320 | 7.80042e+09 | 1.44477e+06 | 0.0778669 | 9.6604 | 35.8085 | 6.58889 | 0.0319324 | 0.357683 | 0.0111877 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7384.57 | 0.0394865 | 4156.91ms | 264040 | 2560 | 464117 | 34099.2 | 0.124074 | 0.686471 | 3.03682 | 0.37603 | 0.000644744 | 5.61438e-06 | 3.70594e-06 | 1(Win) | true |
| jsonifier (two-stage) | 7363.98 | 0.13281 | 4163.79ms | 264040 | 160 | 329987 | 34194.6 | 0.138664 | 0.686508 | 3.03459 | 0.375477 | 0.000623083 | 1.27822e-06 | 4.73413e-07 | 2(Loss) | true |
| simdjson (ondemand) | 5493.71 | 0.0332629 | 5338.63ms | 264040 | 1280 | 297535 | 45835.8 | 0.285826 | 0.920774 | 4.4689 | 0.713297 | 0.0011791 | 8.29361e-06 | 5.6632e-06 | 3(Loss) | true |
| simdjson (reflection) | 5363.56 | 0.0269198 | 5445.4ms | 264040 | 2560 | 408899 | 46947.9 | 0.0830514 | 0.942017 | 4.44666 | 0.712975 | 0.000900958 | 5.33625e-06 | 3.00913e-06 | 4(Loss) | true |
| glaze | 2611.72 | 0.118502 | 5315ms | 264040 | 320 | 4.17722e+06 | 96414.7 | 0.0655234 | 1.94069 | 8.8941 | 1.36391 | 0.00279715 | 2.31972e-05 | 1.92916e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7617.3 | 0.0650664 | 4118.8ms | 264040 | 320 | 148048 | 33057.4 | 0.0580483 | 0.665807 | 2.98011 | 0.363225 | 0.000604063 | 3.21921e-06 | 1.94099e-06 | 1(Win) | true |
| jsonifier | 7556.36 | 0.0262517 | 4134.32ms | 264040 | 4890 | 374229 | 33324 | 0.0451771 | 0.668899 | 2.98218 | 0.363725 | 0.000686354 | 4.73297e-06 | 3.14137e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5591.66 | 0.0923064 | 5319.72ms | 264040 | 80 | 138233 | 45032.8 | 0.0382907 | 0.904123 | 4.40251 | 0.701405 | 0.00115631 | 1.56226e-06 | 8.52144e-07 | 3(Loss) | true |
| simdjson (reflection) | 5364.89 | 0.0453012 | 5520.5ms | 264040 | 640 | 289345 | 46936.3 | 0.107899 | 0.941178 | 4.42146 | 0.707995 | 0.000983859 | 2.26647e-06 | 1.13619e-06 | 4(Loss) | true |
| glaze | 2632.64 | 0.0831926 | 5308.78ms | 264040 | 640 | 4.05235e+06 | 95648.7 | 0.0201511 | 1.91915 | 8.81695 | 1.34816 | 0.00276342 | 2.20137e-05 | 1.78595e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 8831.73 | 0.0371411 | 5060.16ms | 399947 | 2560 | 658663 | 43187.4 | 0.0411274 | 0.572313 | 2.51414 | 0.261827 | 0.000442303 | 4.19782e-06 | 2.77381e-06 | 1(Win) | true |
| jsonifier | 8819.59 | 0.0339028 | 5076.94ms | 399947 | 2560 | 550323 | 43246.8 | 0.0581533 | 0.571401 | 2.51498 | 0.262052 | 0.000434953 | 4.9489e-06 | 3.49167e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7198.09 | 0.0321414 | 6053.08ms | 399947 | 4890 | 1.41844e+06 | 52989 | 0.0311156 | 0.701614 | 3.43194 | 0.490813 | 0.000721799 | 5.43784e-06 | 3.31435e-06 | 3(Loss) | true |
| simdjson (reflection) | 7041.72 | 0.025459 | 6163.54ms | 399947 | 4890 | 929904 | 54165.6 | 0.0892727 | 0.71827 | 3.42338 | 0.491985 | 0.000599507 | 7.48156e-06 | 5.12491e-06 | 4(Loss) | true |
| glaze | 3399.39 | 0.0501022 | 6115.87ms | 399947 | 2560 | 8.09014e+06 | 112202 | 0.0177066 | 1.48043 | 7.26236 | 1.20323 | 0.00225127 | 2.06834e-05 | 1.58527e-05 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 9064.19 | 0.0216334 | 5023.86ms | 399947 | 2560 | 212146 | 42079.8 | 0.122666 | 0.558516 | 2.47823 | 0.253756 | 0.000392666 | 3.34517e-06 | 2.29913e-06 | 1(Win) | true |
| jsonifier | 9048.92 | 0.036 | 5013.33ms | 399947 | 2560 | 589463 | 42150.8 | 0.149989 | 0.559993 | 2.47902 | 0.253964 | 0.000436802 | 4.54162e-06 | 3.35298e-06 | 2(Loss) | true |
| simdjson (ondemand) | 7281.43 | 0.0183809 | 6048.4ms | 399947 | 4890 | 453330 | 52382.5 | 0.0157507 | 0.693479 | 3.39344 | 0.484169 | 0.000788742 | 4.36408e-06 | 3.20134e-06 | 3(Loss) | true |
| simdjson (reflection) | 7041.57 | 0.0590494 | 6223.54ms | 399947 | 640 | 654752 | 54166.8 | 0.0183716 | 0.716764 | 3.40544 | 0.488382 | 0.000679895 | 1.12906e-06 | 3.8677e-07 | 4(Loss) | true |
| glaze | 3443.18 | 0.0913988 | 6071.12ms | 399947 | 1280 | 1.31213e+07 | 110775 | 0.0195013 | 1.46211 | 7.21157 | 1.19297 | 0.00223267 | 1.16871e-05 | 8.28625e-06 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2046.66 | 0.0932585 | 6730.21ms | 264040 | 320 | 4.21282e+06 | 123033 | 0.190727 | 2.4782 | 7.60108 | 1.29409 | 0.013529 | 0.000483284 | 0.000126697 | 1(Win) | true |
| simdjson (reflection) | 1811.7 | 0.0648485 | 7496.59ms | 264040 | 1280 | 1.03986e+07 | 138990 | 0.117381 | 2.78007 | 9.90953 | 1.57932 | 0.0112993 | 0.000934793 | 0.000195827 | 2(Loss) | true |
| glaze | 1783.55 | 0.10445 | 7619.47ms | 264040 | 640 | 1.39177e+07 | 141184 | 0.0551735 | 2.82023 | 10.3629 | 1.82373 | 0.0108592 | 0.000162108 | 5.43478e-05 | 3(Loss) | true |
| jsonifier (two-stage) | 1739.5 | 0.078168 | 7792.68ms | 264040 | 1280 | 1.63893e+07 | 144759 | 0.261577 | 2.89513 | 8.86689 | 1.41472 | 0.0142841 | 0.00178355 | 0.000200899 | 4(Loss) | true |
| simdjson (ondemand) | 1346.87 | 0.0495501 | 9927.77ms | 264040 | 2560 | 2.19692e+07 | 186957 | 0.161627 | 3.73732 | 11.1782 | 1.99132 | 0.0118347 | 0.00220302 | 0.000209858 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2651.56 | 0.268368 | 6103.12ms | 264040 | 30 | 1.94859e+06 | 94966.1 | 0.144789 | 1.91443 | 6.27451 | 1.00801 | 0.00968919 | 4.9235e-05 | 2.87835e-05 | 1(Win) | true |
| glaze | 2265.58 | 0.0903025 | 6758.28ms | 264040 | 640 | 6.44701e+06 | 111145 | 0.17691 | 2.21652 | 9.02428 | 1.53357 | 0.0060444 | 3.35354e-05 | 1.70902e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2163.08 | 0.0532082 | 7195.87ms | 264040 | 2560 | 9.82184e+06 | 116412 | 0.113104 | 2.33279 | 7.54035 | 1.12871 | 0.0105575 | 0.000160117 | 5.17781e-05 | 3(Loss) | true |
| simdjson (reflection) | 2105.98 | 0.15032 | 7104.63ms | 264040 | 320 | 1.03374e+07 | 119568 | 0.0406471 | 2.39422 | 8.96157 | 1.3607 | 0.00744771 | 0.000539253 | 6.71773e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1585.61 | 0.165973 | 9322.31ms | 264040 | 40 | 2.77895e+06 | 158808 | 0.00178415 | 3.19014 | 9.92488 | 1.72331 | 0.00869527 | 0.000119679 | 4.45955e-05 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17846.8 | 0.0443737 | 2151.31ms | 264040 | 2560 | 100349 | 14109.5 | 0.0105498 | 0.285704 | 1.14261 | 0.1631 | 1.84971e-05 | 1.49569e-05 | 8.27141e-06 | 1(Win) | true |
| simdjson (reflection) | 13010.1 | 0.164433 | 2698.92ms | 264040 | 30 | 30386 | 19354.8 | 0.225084 | 0.396887 | 1.41655 | 0.203855 | 0.000355249 | 5.21386e-05 | 4.59526e-05 | 2(Loss) | true |
| glaze | 6720.57 | 0.170628 | 4493.39ms | 263923 | 2560 | 1.0454e+07 | 37451.7 | 0.0239616 | 0.75079 | 2.34457 | 0.343328 | 0.000341731 | 0.000475776 | 7.67861e-05 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17841.4 | 0.0315369 | 2145.92ms | 264040 | 4890 | 96879.1 | 14113.7 | 0.013388 | 0.285032 | 1.14063 | 0.162646 | 2.11098e-05 | 1.70344e-05 | 1.03132e-05 | 1(Win) | true |
| simdjson (reflection) | 12858.6 | 0.112867 | 2694.22ms | 264040 | 640 | 312654 | 19582.8 | 0.189803 | 0.392514 | 1.41456 | 0.203405 | 0.000307606 | 9.09545e-06 | 5.82298e-06 | 2(Loss) | true |
| glaze | 7758.29 | 0.209631 | 3993.2ms | 263923 | 2560 | 1.18406e+07 | 32442.3 | 0.203498 | 0.649004 | 2.3215 | 0.338106 | 0.000333878 | 1.45654e-05 | 8.90559e-06 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2591.37 | 0.0879763 | 7904.9ms | 399947 | 1280 | 2.14629e+07 | 147188 | 0.0435154 | 1.9466 | 7.03479 | 1.06515 | 0.00756921 | 0.0024871 | 0.000115881 | 1(Win) | true |
| jsonifier (two-stage) | 2579.53 | 0.144088 | 7984.97ms | 399947 | 320 | 1.45255e+07 | 147864 | 0.0490878 | 1.94771 | 6.3664 | 0.946991 | 0.00898434 | 0.00288203 | 0.000136588 | 2(Loss) | true |
| glaze | 2216.49 | 0.0590124 | 9237.51ms | 399947 | 640 | 6.59991e+06 | 172082 | 0.104206 | 2.31364 | 8.68609 | 1.56694 | 0.00616506 | 0.000989604 | 0.000135299 | 3(Loss) | true |
| jsonifier | 2005.56 | 0.133063 | 5066.28ms | 399947 | 320 | 2.04927e+07 | 190181 | 0.0241654 | 2.54627 | 6.50397 | 1.24434 | 0.00973652 | 0.00218659 | 0.000104772 | 4(Loss) | true |
| simdjson (ondemand) | 1949.76 | 0.195082 | 5206.05ms | 399947 | 160 | 2.33022e+07 | 195624 | 0.0425157 | 2.57479 | 7.86687 | 1.33581 | 0.00794533 | 0.0034548 | 0.000124204 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3165.25 | 0.111184 | 7465.62ms | 399947 | 640 | 1.14882e+07 | 120502 | 0.0832734 | 1.59045 | 5.49233 | 0.758652 | 0.00681252 | 0.000454908 | 7.94637e-05 | 1(Win) | true |
| simdjson (reflection) | 2969.19 | 0.0553679 | 7760.73ms | 399947 | 2560 | 1.29505e+07 | 128459 | 0.107426 | 1.70087 | 6.40365 | 0.919397 | 0.00538499 | 0.00207748 | 3.52e-05 | 2(Loss) | true |
| glaze | 2531.51 | 0.0257754 | 8815.69ms | 399947 | 2560 | 3.86095e+06 | 150668 | 0.0462161 | 2.0016 | 7.81324 | 1.37845 | 0.00535565 | 7.58626e-05 | 1.08989e-05 | 3(Loss) | true |
| jsonifier | 2334.31 | 0.0333802 | 9552.83ms | 399947 | 2560 | 7.61563e+06 | 163397 | 0.0581823 | 2.16654 | 5.63019 | 1.05586 | 0.00730721 | 0.000486286 | 0.00011261 | 4(Loss) | true |
| simdjson (ondemand) | 2276.79 | 0.0338873 | 9730.21ms | 399947 | 2560 | 8.25041e+06 | 167525 | 0.0916487 | 2.2162 | 7.03861 | 1.15851 | 0.00595869 | 0.000152432 | 3.74034e-05 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21877 | 0.0569941 | 2502.77ms | 399947 | 640 | 63192.9 | 17434.7 | 0.0400404 | 0.234567 | 0.803311 | 0.108827 | 1.75375e-05 | 5.69607e-06 | 3.22699e-06 | 1(Win) | true |
| glaze | 4904.48 | 0.153163 | 8536.39ms | 399830 | 2560 | 3.63003e+07 | 77746.8 | 0.443983 | 1.02716 | 2.77561 | 0.355279 | 0.000401731 | 0.00139269 | 2.65308e-05 | 2(Loss) | true |
| simdjson (reflection) | 528.134 | 0.311068 | 9515.68ms | 399947 | 320 | 1.61502e+09 | 722202 | 0.0776784 | 9.51114 | 29.395 | 5.68791 | 0.0628098 | 0.249645 | 0.000709571 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21658.7 | 0.211514 | 2497.66ms | 399947 | 30 | 41623.8 | 17610.5 | 0.0697961 | 0.233631 | 0.802001 | 0.108529 | 2.65035e-05 | 1.72523e-05 | 1.16682e-05 | 1(Win) | true |
| glaze | 5600.61 | 0.108509 | 7525.63ms | 399830 | 4890 | 2.66883e+07 | 68083.2 | 0.353453 | 0.907983 | 2.76023 | 0.351722 | 0.000397983 | 3.5755e-05 | 2.26748e-05 | 2(Loss) | true |
| simdjson (reflection) | 528.158 | 0.202301 | 9314.03ms | 399947 | 640 | 1.36601e+09 | 722169 | 0.510592 | 9.52764 | 29.3887 | 5.68725 | 0.0634858 | 0.253994 | 0.00246337 | 3(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1071.11 | 0.0851415 | 1144.42ms | 4630 | 80 | 985.531 | 4122.39 | 0.0494008 | 4.85647 | 22.427 | 4.50972 | 0.00295356 | 4.31965e-05 | 1.34989e-05 | 1(Win) | true |
| jsonifier (two-stage) | 963.333 | 0.0509888 | 1189.32ms | 4630 | 2560 | 13982.9 | 4583.58 | 0.0825381 | 5.3295 | 25.0596 | 4.84212 | 0.00274264 | 7.83781e-05 | 3.12163e-05 | 2(Loss) | true |
| simdjson (reflection) | 955.977 | 0.0423792 | 1193.1ms | 4630 | 4890 | 18736.2 | 4618.85 | 0.162534 | 5.36056 | 26.2421 | 4.66415 | 0.00357436 | 0.000162186 | 9.68168e-05 | 3(Loss) | true |
| simdjson (ondemand) | 777.55 | 0.0921527 | 1288.81ms | 4630 | 40 | 1095.42 | 5678.75 | 0.247387 | 6.55022 | 29.943 | 5.4486 | 0.00340713 | 4.85961e-05 | 0 | 4(Loss) | true |
| glaze | 729.621 | 0.0556525 | 1333.97ms | 4630 | 2560 | 29038.7 | 6051.79 | 0.00207837 | 7.00855 | 30.1307 | 5.83823 | 0.0046335 | 0.000113475 | 5.65267e-05 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1338.27 | 0.0382884 | 1146.87ms | 4630 | 640 | 1021.39 | 3299.43 | 0.236109 | 3.82301 | 18.127 | 3.53305 | 0.00021632 | 2.63229e-05 | 3.37473e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1190.28 | 0.0556361 | 1189.87ms | 4630 | 2560 | 10904.8 | 3709.65 | 0.17392 | 4.346 | 20.7657 | 3.86739 | 0.0010805 | 7.69438e-05 | 2.80946e-05 | 2(Loss) | true |
| simdjson (reflection) | 1111 | 0.0977627 | 1219.09ms | 4630 | 4890 | 73822.1 | 3974.34 | 0.13115 | 4.59697 | 23.4449 | 4.02505 | 0.0018764 | 8.14904e-05 | 3.44071e-05 | 3(Loss) | true |
| simdjson (ondemand) | 895.018 | 0.120423 | 1309.81ms | 4630 | 320 | 11294.5 | 4933.43 | 0.0227984 | 5.69274 | 27.0058 | 4.78121 | 0.00186353 | 3.10475e-05 | 3.37473e-06 | 4(Loss) | true |
| glaze | 857.563 | 0.214859 | 1333.51ms | 4630 | 160 | 19582 | 5148.91 | 0.0161468 | 5.93012 | 25.7538 | 4.84363 | 0.00334503 | 2.69978e-05 | 4.04968e-06 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2020.38 | 0.0691217 | 947.235ms | 4630 | 4890 | 11159.2 | 2185.49 | 0.0329173 | 2.54845 | 7.64903 | 0.411232 | 0.000468625 | 4.12531e-05 | 1.76673e-05 | 1(Win) | true |
| glaze | 1550.51 | 0.202215 | 1006.71ms | 4630 | 320 | 10611.7 | 2847.77 | 0.0433265 | 3.3008 | 10.076 | 0.768251 | 0.000221382 | 3.44222e-05 | 1.48488e-05 | 2(Loss) | true |
| simdjson (reflection) | 1052.93 | 0.0320489 | 1144.55ms | 4630 | 30 | 54.1885 | 4193.53 | 0.00556381 | 4.84886 | 15.5717 | 1.48164 | 0.000647948 | 0 | 0 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2051.38 | 0.034275 | 943.714ms | 4630 | 1280 | 696.685 | 2152.46 | 0.0318051 | 2.51681 | 7.54492 | 0.386609 | 0.000457951 | 4.38715e-05 | 2.1767e-05 | 1(Win) | true |
| glaze | 1580.28 | 0.108662 | 1004.69ms | 4630 | 320 | 2949.87 | 2794.14 | 0.0956038 | 3.24669 | 9.58164 | 0.65594 | 0.000259854 | 6.07451e-06 | 2.02484e-06 | 2(Loss) | true |
| simdjson (reflection) | 1061.57 | 0.0681739 | 1138.28ms | 4630 | 40 | 321.631 | 4159.4 | 0.129995 | 4.80854 | 15.4646 | 1.45724 | 0.000647948 | 0.000134989 | 2.69978e-05 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2759.73 | 0.0392441 | 1249.37ms | 14795 | 1280 | 5152.96 | 5112.68 | 0.0144687 | 1.85189 | 8.68658 | 1.54694 | 0.000634927 | 4.31417e-05 | 2.07524e-05 | 1(Win) | true |
| simdjson (reflection) | 2735.27 | 0.0600884 | 1249.91ms | 14795 | 4890 | 46980.8 | 5158.4 | 0.106992 | 1.86409 | 9.09936 | 1.49388 | 0.001352 | 3.19154e-05 | 1.35872e-05 | 2(Loss) | true |
| jsonifier | 2611.92 | 0.0594164 | 1273.05ms | 14795 | 1280 | 13186.7 | 5402.02 | 0.109787 | 1.94941 | 9.05346 | 1.9512 | 0.00103107 | 2.77754e-05 | 9.55771e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2250.68 | 0.0731512 | 1359.22ms | 14795 | 1280 | 26918.7 | 6269.04 | 0.0105066 | 2.25399 | 10.5066 | 1.78919 | 0.000786214 | 6.2838e-05 | 3.30559e-05 | 4(Loss) | true |
| glaze | 1767.03 | 0.0356211 | 1532.81ms | 14795 | 4890 | 39560.9 | 7984.94 | 0.0867079 | 2.88175 | 13.3361 | 2.4707 | 0.00418031 | 9.1406e-05 | 5.06168e-05 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3338.54 | 0.0283043 | 1251.21ms | 14795 | 2560 | 3663.21 | 4226.28 | 0.0221043 | 1.5303 | 7.34471 | 1.24238 | 0.00018289 | 2.56368e-05 | 1.06666e-05 | 1(Win) | true |
| simdjson (reflection) | 3167.09 | 0.0567536 | 1277.01ms | 14795 | 160 | 1022.86 | 4455.07 | 0.169463 | 1.6124 | 8.26239 | 1.30206 | 0.000629436 | 2.06996e-05 | 5.49172e-06 | 2(Loss) | true |
| jsonifier | 3106.78 | 0.0856787 | 1276.27ms | 14795 | 40 | 605.638 | 4541.55 | 0.0700444 | 1.64354 | 7.71031 | 1.64637 | 0.000471443 | 1.68976e-05 | 1.68976e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2589.94 | 0.0953743 | 1376.66ms | 14795 | 40 | 1079.87 | 5447.85 | 0.0253987 | 1.96785 | 9.45137 | 1.55377 | 0.000664076 | 2.02771e-05 | 0 | 4(Loss) | true |
| glaze | 1950.44 | 0.0386353 | 1545.23ms | 14795 | 2560 | 19997.4 | 7234.07 | 0.13861 | 2.60926 | 11.9744 | 2.16181 | 0.003797 | 2.08316e-05 | 8.10557e-06 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5590.88 | 0.0974584 | 986.831ms | 14795 | 2560 | 15486.3 | 2523.68 | 0.31855 | 0.913236 | 2.49409 | 0.131058 | 7.01514e-05 | 4.35377e-05 | 2.20461e-05 | 1(Win) | true |
| glaze | 3464.31 | 0.161968 | 1141.32ms | 14795 | 80 | 3481.32 | 4072.85 | 0.0766688 | 1.47424 | 4.62474 | 0.416627 | 6.75904e-05 | 2.87259e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 198.319 | 0.0478504 | 7842.74ms | 14795 | 2560 | 2.96697e+06 | 71146.1 | 0.0282635 | 25.602 | 92.2671 | 16.7772 | 0.0740414 | 0.000265556 | 0.000155458 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5900.18 | 0.140842 | 966.812ms | 14795 | 1280 | 14520.3 | 2391.39 | 0.231474 | 0.869805 | 2.44995 | 0.120919 | 6.85937e-05 | 9.87454e-06 | 1.37293e-06 | 1(Win) | true |
| glaze | 3896.17 | 0.130914 | 1095.95ms | 14795 | 640 | 14385 | 3621.41 | 0.18669 | 1.31718 | 4.40399 | 0.366543 | 0.00014363 | 6.23099e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 199.796 | 0.0890774 | 7832.4ms | 14795 | 640 | 2.53262e+06 | 70620 | 0.133278 | 25.5563 | 92.2781 | 16.7818 | 0.072884 | 4.74189e-05 | 2.1122e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1937.89 | 0.0464613 | 976.464ms | 5092 | 320 | 433.763 | 2505.88 | 0.187786 | 2.70173 | 10.7767 | 1.99057 | 0.00207924 | 2.45483e-05 | 6.13708e-07 | 1(Win) | true |
| jsonifier (two-stage) | 1598.03 | 0.0405448 | 1035.05ms | 5092 | 4890 | 7423.14 | 3038.81 | 0.105164 | 3.23908 | 13.3213 | 2.30165 | 0.00107764 | 7.12052e-05 | 2.52612e-05 | 2(Loss) | true |
| glaze | 1506.34 | 0.155982 | 1054.01ms | 5092 | 320 | 8091.53 | 3223.78 | 0.142196 | 3.39553 | 13.8113 | 2.69874 | 0.00093345 | 2.33209e-05 | 1.84112e-06 | 3(Loss) | true |
| simdjson (reflection) | 1278.7 | 0.127949 | 1110.78ms | 5092 | 640 | 15111 | 3797.69 | 0.0421486 | 4.06587 | 15.1426 | 2.46013 | 0.00125749 | 0.000478385 | 0.000343063 | 4(Loss) | true |
| simdjson (ondemand) | 1227.99 | 0.0597849 | 1124.41ms | 5092 | 160 | 894.314 | 3954.52 | 0.213978 | 4.24565 | 15.5862 | 2.64513 | 0.00207924 | 6.13708e-05 | 3.31402e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2353.22 | 0.312386 | 999.886ms | 5092 | 40 | 1662.25 | 2063.6 | 0.0775946 | 2.23934 | 9.25 | 1.60782 | 0.00197859 | 7.36449e-05 | 2.9458e-05 | 1(Win) | true |
| jsonifier (two-stage) | 1911.67 | 0.123517 | 1023.63ms | 5092 | 80 | 787.582 | 2540.25 | 0.0935822 | 2.73892 | 11.7757 | 1.91555 | 0.00110958 | 6.62804e-05 | 2.9458e-05 | 2(Loss) | true |
| glaze | 1781.7 | 0.105952 | 1043.48ms | 5092 | 4890 | 40778.8 | 2725.55 | 0.187016 | 2.91413 | 12.3036 | 2.32149 | 0.000659602 | 2.48194e-05 | 8.43378e-06 | 3(Loss) | true |
| simdjson (reflection) | 1425.62 | 0.0530695 | 1105.47ms | 5092 | 4890 | 15979.7 | 3406.31 | 0.0833793 | 3.63438 | 13.8883 | 2.12824 | 0.00106025 | 0.000222933 | 0.000143414 | 4(Loss) | true |
| simdjson (ondemand) | 1385.96 | 0.067226 | 1114.76ms | 5092 | 4890 | 27130.5 | 3503.78 | 0.0688171 | 3.75436 | 14.0006 | 2.25717 | 0.00151069 | 0.000136627 | 8.59442e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8983.44 | 0.17093 | 779.592ms | 5092 | 80 | 68.2998 | 540.562 | 0.242215 | 0.619054 | 2.17184 | 0.356834 | 0.000267577 | 3.19128e-05 | 7.36449e-06 | 1(Win) | true |
| simdjson (reflection) | 6907.82 | 0.195265 | 796.888ms | 5092 | 160 | 301.484 | 702.987 | 0.333174 | 0.789542 | 2.58288 | 0.288885 | 0.000196386 | 8.59191e-06 | 2.45483e-06 | 2(Loss) | true |
| glaze | 3665.24 | 0.139052 | 859.128ms | 5092 | 2560 | 8688.92 | 1324.91 | 0.252679 | 1.43969 | 4.71131 | 0.720542 | 0.000198228 | 6.28283e-05 | 3.25265e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9597.97 | 0.0893363 | 775.963ms | 5092 | 640 | 130.754 | 505.952 | 0.0911862 | 0.581348 | 2.07306 | 0.334053 | 0.000196693 | 2.17866e-05 | 9.51247e-06 | 1(Win) | true |
| simdjson (reflection) | 7260.83 | 0.101071 | 791.246ms | 5092 | 640 | 292.442 | 668.809 | 0.608833 | 0.75287 | 2.48507 | 0.2663 | 0.000196386 | 2.36277e-05 | 1.19673e-05 | 2(Loss) | true |
| glaze | 4216.91 | 0.223464 | 837.449ms | 5092 | 4890 | 32382.6 | 1151.58 | 0.346799 | 1.2509 | 4.2176 | 0.614101 | 0.000197872 | 7.95185e-05 | 5.03215e-05 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3276.06 | 0.0463557 | 1071.37ms | 11724 | 4890 | 12239.5 | 3412.9 | 0.0247394 | 1.58082 | 6.51714 | 1.01288 | 0.000508038 | 4.57175e-05 | 2.0565e-05 | 1(Win) | true |
| jsonifier | 2789.11 | 0.0617433 | 1129.27ms | 11724 | 160 | 980.211 | 4008.76 | 0.00982321 | 1.86595 | 6.82813 | 1.4449 | 0.000978762 | 1.97245e-05 | 1.59928e-06 | 2(Loss) | true |
| simdjson (reflection) | 2731.64 | 0.105136 | 1141.86ms | 11724 | 320 | 5925.88 | 4093.09 | 0.0481225 | 1.90329 | 7.32873 | 1.09348 | 0.000615991 | 1.51932e-05 | 3.73166e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2589.59 | 0.0628585 | 1167.58ms | 11724 | 640 | 4714.08 | 4317.62 | 0.0772397 | 2.01085 | 7.56883 | 1.18373 | 0.000760459 | 1.10617e-05 | 5.33095e-07 | 4(Loss) | true |
| glaze | 2295.5 | 0.105656 | 1221.2ms | 11724 | 40 | 1059.36 | 4870.77 | 0.18735 | 2.26314 | 9.37146 | 1.76314 | 0.00152465 | 2.55885e-05 | 0 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3809.41 | 0.0550979 | 1067.37ms | 11724 | 640 | 1673.74 | 2935.07 | 0.0698405 | 1.37191 | 5.90959 | 0.857642 | 0.000504441 | 4.34472e-05 | 2.19901e-05 | 1(Win) | true |
| jsonifier | 3123.6 | 0.0560379 | 1127.12ms | 11724 | 1280 | 5150.08 | 3579.48 | 0.104284 | 1.66192 | 6.22049 | 1.28966 | 0.00095144 | 2.66547e-05 | 9.72897e-06 | 2(Loss) | true |
| simdjson (reflection) | 2942.75 | 0.109368 | 1151.14ms | 11724 | 320 | 5525.55 | 3799.47 | 0.158488 | 1.7368 | 6.85502 | 0.964411 | 0.000809504 | 2.31896e-05 | 7.99642e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2903.29 | 0.0374909 | 1148.94ms | 11724 | 4890 | 10193.7 | 3851.11 | 0.0262298 | 1.7873 | 6.8724 | 1.0139 | 0.000848817 | 2.25012e-05 | 8.70394e-06 | 4(Loss) | true |
| glaze | 2545.08 | 0.0729548 | 1204.77ms | 11724 | 160 | 1643.52 | 4393.13 | 0.126636 | 2.04323 | 8.74429 | 1.60474 | 0.00112696 | 3.83828e-05 | 1.91914e-05 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17179.1 | 0.100498 | 792.675ms | 11724 | 320 | 136.903 | 650.844 | 0.281531 | 0.313145 | 1.06039 | 0.158649 | 8.52951e-05 | 1.17281e-05 | 1.33274e-06 | 1(Win) | true |
| glaze | 4248.15 | 0.159043 | 999.668ms | 11746 | 2560 | 45024.7 | 2636.88 | 0.0313709 | 1.21541 | 3.76154 | 0.516516 | 0.000209513 | 1.89559e-05 | 6.51818e-06 | 2(Loss) | true |
| simdjson (reflection) | 549.005 | 0.664707 | 2771.84ms | 11724 | 80 | 1.46605e+06 | 20365.7 | 0.057544 | 9.22451 | 36.0943 | 6.20735 | 0.0049951 | 0.000198311 | 0.00013434 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20528.6 | 0.118064 | 785.523ms | 11724 | 4890 | 2021.98 | 544.648 | 0.123352 | 0.266622 | 1.00478 | 0.14594 | 8.5487e-05 | 3.72229e-05 | 2.16988e-05 | 1(Win) | true |
| glaze | 4289.23 | 0.0838501 | 993.586ms | 11746 | 4890 | 23449.7 | 2611.62 | 0.143323 | 1.21115 | 3.49268 | 0.456496 | 0.00021115 | 3.4089e-05 | 1.96386e-05 | 2(Loss) | true |
| simdjson (reflection) | 552.096 | 0.117755 | 2770.41ms | 11724 | 2560 | 1.45587e+06 | 20251.7 | 0.0944205 | 9.18714 | 36.0789 | 6.20526 | 0.00480635 | 0.000127476 | 8.42956e-05 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1916.25 | 0.181331 | 978.52ms | 4857 | 40 | 768.487 | 2417.22 | 0.0485858 | 2.69182 | 9.88964 | 1.84857 | 0.00141548 | 0.000118386 | 6.69137e-05 | 1(Win) | true |
| glaze | 1752.54 | 0.0793668 | 1000.57ms | 4857 | 320 | 1408.08 | 2643.01 | 0.309314 | 2.93098 | 11.6914 | 2.28382 | 0.00157762 | 2.2519e-05 | 7.72082e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1628.91 | 0.101459 | 1025.81ms | 4857 | 160 | 1331.81 | 2843.61 | 0.124116 | 3.14895 | 11.9822 | 1.99897 | 0.00157633 | 3.86041e-05 | 1.2868e-05 | 3(Loss) | true |
| simdjson (reflection) | 1349.96 | 0.051926 | 1083.95ms | 4857 | 4890 | 15522.9 | 3431.21 | 0.165913 | 3.78661 | 13.4917 | 2.26392 | 0.00251356 | 7.63766e-05 | 3.2378e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1308.24 | 0.041868 | 1095.38ms | 4857 | 4890 | 10745.7 | 3540.63 | 0.244589 | 3.92099 | 14.2059 | 2.75685 | 0.00107917 | 7.57871e-05 | 2.88412e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2556.64 | 0.120352 | 942.975ms | 4857 | 1280 | 6085.76 | 1811.75 | 0.0810883 | 2.02334 | 7.49413 | 1.28763 | 0.000321057 | 3.42611e-05 | 1.35114e-05 | 1(Win) | true |
| glaze | 2478.35 | 0.108664 | 947.495ms | 4857 | 2560 | 10558.9 | 1868.98 | 0.13621 | 2.09229 | 9.06136 | 1.69693 | 0.000862077 | 0.000108091 | 7.4715e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2040.12 | 0.0626379 | 986.13ms | 4857 | 2560 | 5177.72 | 2270.45 | 0.379058 | 2.52863 | 9.98188 | 1.52399 | 0.000702675 | 7.27848e-05 | 3.90866e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1598.14 | 0.14905 | 1047.48ms | 4857 | 320 | 5972.05 | 2898.37 | 0.167486 | 3.21279 | 12.1268 | 2.32036 | 0.00135179 | 3.21701e-05 | 6.43401e-07 | 4(Loss) | true |
| simdjson (reflection) | 1586.06 | 0.0584158 | 1062.22ms | 4857 | 2560 | 7450.74 | 2920.45 | 0.0852612 | 3.2293 | 11.9568 | 1.90756 | 0.00116625 | 0.000101818 | 4.37513e-05 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9591.07 | 0.0818523 | 782.531ms | 4857 | 4890 | 764.141 | 482.949 | 0.533024 | 0.571207 | 1.84867 | 0.304715 | 0.000206394 | 5.05669e-05 | 2.76623e-05 | 1(Win) | true |
| simdjson (reflection) | 6770.03 | 0.0861345 | 804.172ms | 4857 | 4890 | 1698.32 | 684.192 | 0.183979 | 0.791525 | 2.1435 | 0.329216 | 0.000250645 | 3.64199e-05 | 1.781e-05 | 2(Loss) | true |
| glaze | 4090.88 | 0.186807 | 853.866ms | 4857 | 640 | 2863.31 | 1132.28 | 0.0853546 | 1.2823 | 3.951 | 0.62343 | 0.000412099 | 2.44492e-05 | 4.18211e-06 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10447.5 | 0.0783435 | 777.805ms | 4857 | 320 | 38.6071 | 443.359 | 0.176604 | 0.523825 | 1.7379 | 0.278361 | 0.000205888 | 1.35114e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 7211.44 | 0.109697 | 801.453ms | 4857 | 1280 | 635.464 | 642.312 | 0.0639369 | 0.749274 | 2.04324 | 0.305744 | 0.000252052 | 3.24918e-05 | 1.80152e-05 | 2(Loss) | true |
| glaze | 4736.34 | 0.291045 | 837.732ms | 4857 | 640 | 5185.05 | 977.97 | 0.0506213 | 1.11068 | 3.44101 | 0.508133 | 0.000213288 | 1.35114e-05 | 3.86041e-06 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2358.47 | 0.046072 | 1034.61ms | 7376 | 4890 | 9233.42 | 2982.56 | 0.009109 | 2.18639 | 8.39181 | 1.32491 | 0.000597694 | 5.26773e-05 | 2.25958e-05 | 1(Win) | true |
| glaze | 2066.92 | 0.171864 | 1078.76ms | 7376 | 320 | 10947.5 | 3403.27 | 0.0149695 | 2.47196 | 9.86327 | 1.98407 | 0.00120407 | 3.43174e-05 | 1.14391e-05 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1992.9 | 0.063974 | 1093.61ms | 7376 | 2560 | 13053.2 | 3529.68 | 0.176906 | 2.57103 | 9.36481 | 1.50672 | 0.00121212 | 7.29774e-05 | 3.50058e-05 | 3(Tie) | true |
| jsonifier STATISTICAL TIE | 1991.08 | 0.0420593 | 1091.8ms | 7376 | 4890 | 10796.9 | 3532.92 | 0.0812974 | 2.5759 | 8.50854 | 1.78261 | 0.00131987 | 7.00331e-05 | 3.8399e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1911.09 | 0.130244 | 1109.18ms | 7376 | 640 | 14708.9 | 3680.78 | 0.120879 | 2.68949 | 9.88354 | 1.84124 | 0.000797773 | 8.96065e-05 | 4.2579e-05 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 2895.67 | 0.125572 | 1002.7ms | 7376 | 1280 | 11910.7 | 2429.25 | 0.138739 | 1.77945 | 7.02278 | 0.999322 | 0.00054982 | 2.97629e-05 | 8.8971e-06 | 1(Win) | true |
| glaze | 2729.4 | 0.0772929 | 1021.05ms | 7376 | 1280 | 5079.22 | 2577.24 | 0.075242 | 1.8822 | 8.01708 | 1.5728 | 0.000772882 | 2.81741e-05 | 9.63852e-06 | 2(Loss) | true |
| jsonifier | 2508.98 | 0.083351 | 1044.12ms | 7376 | 40 | 218.438 | 2803.65 | 0.0136745 | 2.0839 | 6.93872 | 1.41459 | 0.00080667 | 3.38937e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 2312.94 | 0.101171 | 1067.81ms | 7376 | 1280 | 12118.1 | 3041.28 | 0.0714643 | 2.20972 | 8.31901 | 1.26437 | 0.000569626 | 6.24915e-05 | 2.66913e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2289.12 | 0.100295 | 1070.54ms | 7376 | 1280 | 12158.3 | 3072.93 | 0.0646687 | 2.26374 | 8.50976 | 1.55301 | 0.0013138 | 0.000182814 | 0.000123182 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13685.6 | 0.0822582 | 781.077ms | 7376 | 320 | 57.2037 | 513.994 | 0.459943 | 0.398498 | 1.28254 | 0.199024 | 0.000135575 | 5.08406e-06 | 0 | 1(Win) | true |
| glaze | 3953.39 | 0.113935 | 917.099ms | 7376 | 2560 | 10521 | 1779.31 | 0.2645 | 1.31821 | 4.0282 | 0.590971 | 0.000137164 | 3.9931e-05 | 2.10247e-05 | 2(Loss) | true |
| simdjson (reflection) | 533.768 | 0.109508 | 2063.64ms | 7376 | 2560 | 533169 | 13178.6 | 0.117666 | 9.54716 | 34.9554 | 6.55342 | 0.0065023 | 0.000166609 | 0.000103058 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15343.1 | 0.196969 | 776.332ms | 7376 | 30 | 24.4644 | 458.467 | 0.0218071 | 0.357832 | 1.21434 | 0.183297 | 0.000135575 | 0 | 0 | 1(Win) | true |
| glaze | 4333.34 | 0.09791 | 896.701ms | 7376 | 4890 | 12352.6 | 1623.3 | 0.320484 | 1.20027 | 3.70445 | 0.518032 | 0.000309355 | 2.09046e-05 | 1.36961e-05 | 2(Loss) | true |
| simdjson (reflection) | 535.649 | 0.112947 | 2056.14ms | 7376 | 2560 | 563209 | 13132.3 | 0.125095 | 9.51156 | 34.9637 | 6.55505 | 0.00680988 | 0.000136051 | 8.2457e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2456.08 | 0.107206 | 903.348ms | 4390 | 40 | 133.579 | 1704.6 | 0.0840156 | 2.14669 | 9.75831 | 1.67745 | 0.000808656 | 2.2779e-05 | 0 | 1(Win) | true |
| glaze | 1957.41 | 0.045411 | 941.548ms | 4390 | 4890 | 4613.13 | 2138.86 | 0.17567 | 2.62647 | 12.7171 | 2.44032 | 0.000252479 | 2.10555e-05 | 8.89734e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 1809.78 | 0.183621 | 961.639ms | 4390 | 320 | 5773.91 | 2313.33 | 0.0695211 | 2.85118 | 13.2533 | 2.14693 | 0.00246441 | 8.2574e-05 | 3.63041e-05 | 3(Loss) | true |
| simdjson (reflection) | 1285.16 | 0.100861 | 1059.51ms | 4390 | 4890 | 52792.3 | 3257.68 | 0.454816 | 4.05028 | 14.8727 | 2.48314 | 0.00532652 | 0.000138211 | 7.4719e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1128.54 | 0.126999 | 1102.02ms | 4390 | 30 | 665.909 | 3709.77 | 0.0107812 | 4.52857 | 15.785 | 2.74374 | 0.00278664 | 1.5186e-05 | 0 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2821.68 | 0.087743 | 900.921ms | 4390 | 1280 | 2169.45 | 1483.74 | 0.0118458 | 1.84789 | 8.73394 | 1.43485 | 0.000271391 | 1.88639e-05 | 1.95757e-06 | 1(Win) | true |
| glaze | 2277.49 | 0.0841207 | 934.536ms | 4390 | 1280 | 3060.79 | 1838.27 | 0.274427 | 2.27864 | 11.4661 | 2.15034 | 0.000459496 | 7.06506e-05 | 4.87614e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2019.91 | 0.0459851 | 962.934ms | 4390 | 4890 | 4442.3 | 2072.68 | 0.267785 | 2.55143 | 12.1982 | 1.89977 | 0.00223677 | 3.94557e-05 | 1.50463e-05 | 3(Loss) | true |
| simdjson (reflection) | 1358.83 | 0.121532 | 1061.24ms | 4390 | 1280 | 17946.8 | 3081.06 | 0.180204 | 3.79707 | 14.0731 | 2.28816 | 0.00655147 | 3.2389e-05 | 1.3881e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1256.07 | 0.0756077 | 1085.71ms | 4390 | 1280 | 8129.13 | 3333.12 | 0.052789 | 4.1225 | 14.3569 | 2.4303 | 0.00306343 | 3.18551e-05 | 1.21014e-05 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10121.8 | 0.125885 | 762.838ms | 4390 | 4890 | 1325.77 | 413.624 | 0.0783447 | 0.555495 | 2.60706 | 0.338041 | 0.000228163 | 5.86013e-05 | 3.50303e-05 | 1(Win) | true |
| simdjson (reflection) | 8032.95 | 0.100958 | 777.945ms | 4390 | 1280 | 354.382 | 521.182 | 0.0280391 | 0.68684 | 2.6 | 0.383144 | 0.000253061 | 4.41344e-05 | 2.40248e-05 | 2(Loss) | true |
| glaze | 3834.77 | 0.143655 | 835.804ms | 4390 | 4890 | 12028.3 | 1091.75 | 0.0228963 | 1.38261 | 4.71731 | 0.758315 | 0.00022984 | 8.0076e-05 | 5.26387e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10792.5 | 0.229028 | 758.021ms | 4390 | 2560 | 2020.7 | 387.921 | 0.493287 | 0.519999 | 2.48451 | 0.309795 | 0.000228858 | 4.09311e-05 | 2.68722e-05 | 1(Win) | true |
| simdjson (reflection) | 8737.22 | 0.137237 | 772.11ms | 4390 | 320 | 138.381 | 479.172 | 0.100984 | 0.638215 | 2.48633 | 0.356948 | 0.000228502 | 1.63724e-05 | 6.40661e-06 | 2(Loss) | true |
| glaze | 4163.71 | 0.209036 | 825.889ms | 4390 | 2560 | 11309.7 | 1005.5 | 0.504771 | 1.2609 | 4.28497 | 0.659453 | 0.000228591 | 4.52911e-05 | 2.91856e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4022.51 | 0.0905408 | 1003.77ms | 11521 | 80 | 489.289 | 2731.45 | 0.0713397 | 1.29978 | 5.9895 | 0.868067 | 0.000835431 | 2.49544e-05 | 7.59483e-06 | 1(Win) | true |
| jsonifier | 3777.51 | 0.131463 | 1018.48ms | 11521 | 320 | 4678.72 | 2908.61 | 0.0412739 | 1.3798 | 5.96919 | 1.24217 | 0.00158569 | 1.89871e-05 | 6.7811e-06 | 2(Loss) | true |
| simdjson (reflection) | 3039.82 | 0.0398403 | 1090.01ms | 11521 | 4890 | 10140 | 3614.46 | 0.058102 | 1.6924 | 6.48998 | 0.975089 | 0.00214251 | 3.78787e-05 | 1.72354e-05 | 3(Loss) | true |
| glaze | 2876.88 | 0.0593573 | 1111.32ms | 11521 | 2560 | 13156 | 3819.16 | 0.0995256 | 1.80018 | 8.53797 | 1.56011 | 0.00390666 | 3.00063e-05 | 1.74613e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2698.09 | 0.0601406 | 1132.47ms | 11521 | 2560 | 15354.7 | 4072.24 | 0.128723 | 1.90314 | 6.90652 | 1.08793 | 0.00118957 | 2.30557e-05 | 8.34075e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4343.22 | 0.0363435 | 1008.29ms | 11521 | 4890 | 4133.51 | 2529.75 | 0.105065 | 1.18619 | 5.56662 | 0.769899 | 0.000772218 | 1.87441e-05 | 6.35454e-06 | 1(Win) | true |
| jsonifier | 4101.5 | 0.101612 | 1016.92ms | 11521 | 1280 | 9484.07 | 2678.85 | 0.0599381 | 1.2718 | 5.54752 | 1.144 | 0.00146316 | 3.03115e-05 | 1.7563e-05 | 2(Loss) | true |
| simdjson (reflection) | 3198.89 | 0.0886796 | 1094.3ms | 11521 | 640 | 5937.59 | 3434.72 | 0.0923417 | 1.62797 | 6.24382 | 0.912334 | 0.00273075 | 3.32274e-05 | 1.7224e-05 | 3(Loss) | true |
| glaze | 3133.5 | 0.0713213 | 1099.36ms | 11521 | 1280 | 8005.13 | 3506.39 | 0.193778 | 1.66105 | 8.02995 | 1.44363 | 0.00404953 | 7.86607e-06 | 1.35622e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2974.83 | 0.0651962 | 1123.86ms | 11521 | 160 | 927.729 | 3693.42 | 0.0069385 | 1.75135 | 6.39719 | 0.97561 | 0.00141481 | 1.73596e-05 | 4.3399e-06 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 19768.4 | 0.115829 | 775.153ms | 11521 | 2560 | 1060.99 | 555.8 | 0.164959 | 0.276848 | 1.1111 | 0.130805 | 8.70693e-05 | 2.52596e-05 | 1.32909e-05 | 1(Win) | true |
| glaze | 5603.32 | 0.102988 | 924.971ms | 11521 | 4890 | 19942 | 1960.85 | 0.261402 | 0.92886 | 3.76625 | 0.51289 | 8.82358e-05 | 2.13356e-05 | 8.0408e-06 | 2(Loss) | true |
| simdjson (reflection) | 537.107 | 0.192433 | 2777.26ms | 11521 | 1280 | 1.98349e+06 | 20456.4 | 0.364968 | 9.45864 | 35.9206 | 6.38345 | 0.00899526 | 7.33715e-05 | 3.29561e-05 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 23767.5 | 0.102918 | 764.858ms | 11521 | 320 | 72.4348 | 462.281 | 0.0635032 | 0.234092 | 1.05503 | 0.118045 | 8.6798e-05 | 4.3399e-06 | 2.16995e-06 | 1(Win) | true |
| glaze | 6797.52 | 0.217706 | 889.74ms | 11521 | 1280 | 15850 | 1616.37 | 0.248471 | 0.77232 | 3.50464 | 0.455516 | 0.000118534 | 1.30197e-05 | 6.1708e-06 | 2(Loss) | true |
| simdjson (reflection) | 541.071 | 0.138926 | 2758.89ms | 11521 | 2560 | 2.03742e+06 | 20306.5 | 0.133939 | 9.4401 | 35.777 | 6.34798 | 0.00864268 | 0.000170409 | 0.000101072 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3390.64 | 0.0433783 | 856.083ms | 4669 | 4890 | 1586.86 | 1313.23 | 0.170808 | 1.55563 | 6.45149 | 1.38081 | 0.000547491 | 2.14179e-05 | 8.58466e-06 | 1(Win) | true |
| jsonifier (two-stage) | 2173.75 | 0.151146 | 932.426ms | 4669 | 640 | 6134.83 | 2048.4 | 0.0690803 | 2.41117 | 9.28936 | 1.67488 | 0.00118869 | 3.6812e-05 | 1.53941e-05 | 2(Loss) | true |
| glaze | 1992.78 | 0.0722576 | 949.437ms | 4669 | 2560 | 6673.23 | 2234.42 | 0.229858 | 2.59241 | 9.62583 | 1.82202 | 0.000813879 | 3.84016e-05 | 2.02466e-05 | 3(Loss) | true |
| simdjson (reflection) | 1747.18 | 0.0668272 | 979.825ms | 4669 | 2560 | 7425.35 | 2548.5 | 0.0250238 | 2.95733 | 12.5123 | 1.91476 | 0.00120844 | 4.3756e-05 | 6.27476e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1255.84 | 0.0804932 | 1084.32ms | 4669 | 80 | 651.61 | 3545.6 | 0.014104 | 4.07408 | 14.5982 | 2.4909 | 0.00198918 | 2.67723e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3776.27 | 0.057042 | 843.938ms | 4669 | 320 | 144.764 | 1179.13 | 0.158499 | 1.41015 | 6.00171 | 1.26815 | 0.000546825 | 4.01585e-06 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 2381.93 | 0.166948 | 925.614ms | 4669 | 320 | 3116.74 | 1869.37 | 0.0103634 | 2.19934 | 8.83851 | 1.56286 | 0.00110637 | 1.33862e-05 | 1.33862e-06 | 2(Loss) | true |
| glaze | 2258.49 | 0.15043 | 928.235ms | 4669 | 80 | 703.669 | 1971.54 | 0.165754 | 2.30935 | 8.93596 | 1.66588 | 0.000736239 | 5.35447e-06 | 0 | 3(Loss) | true |
| simdjson (reflection) | 1790.22 | 0.0766322 | 984.062ms | 4669 | 1280 | 4650.16 | 2487.24 | 0.270901 | 2.86832 | 12.2405 | 1.84301 | 0.00132222 | 3.79832e-05 | 3.84852e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1358.58 | 0.0792149 | 1066.84ms | 4669 | 80 | 539.24 | 3277.47 | 0.0335512 | 3.83925 | 13.8698 | 2.33476 | 0.00160902 | 1.60634e-05 | 0 | 5(Loss) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14073.2 | 0.0977418 | 753.729ms | 4669 | 320 | 30.6038 | 316.397 | 0.572523 | 0.404763 | 1.35232 | 0.33519 | 0.000215517 | 1.20475e-05 | 3.34654e-06 | 1(Win) | true |
| simdjson (reflection) | 7744.64 | 0.0802445 | 781.183ms | 4669 | 320 | 68.1125 | 574.941 | 0.0777859 | 0.708638 | 1.66096 | 0.224888 | 0.000553518 | 9.37031e-06 | 0 | 2(Loss) | true |
| glaze | 3712.47 | 0.127829 | 851.263ms | 4669 | 2560 | 6017.57 | 1199.39 | 0.117142 | 1.41802 | 3.37717 | 0.4864 | 0.000267974 | 2.45971e-05 | 5.35447e-06 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16564.4 | 0.0824146 | 743.591ms | 4669 | 80 | 3.92642 | 268.812 | 0.393701 | 0.356005 | 1.24331 | 0.309916 | 0.000214179 | 5.35447e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8518.38 | 0.039635 | 776.915ms | 4669 | 640 | 27.4708 | 522.717 | 0.0128519 | 0.661171 | 1.55472 | 0.200257 | 0.000616433 | 5.01981e-06 | 1.33862e-06 | 2(Loss) | true |
| glaze | 4043.48 | 0.12521 | 834.86ms | 4669 | 4890 | 9296.63 | 1101.21 | 0.399189 | 1.29917 | 2.87471 | 0.373099 | 0.000214748 | 1.5724e-05 | 4.68653e-06 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3759.48 | 0.0489595 | 967.089ms | 9249 | 4890 | 6452.33 | 2346.21 | 0.0170776 | 1.3742 | 5.44599 | 0.887015 | 0.00056974 | 2.79475e-05 | 1.14311e-05 | 1(Win) | true |
| jsonifier | 3323.02 | 0.0995662 | 993.475ms | 9249 | 1280 | 8940.42 | 2654.37 | 0.192772 | 1.57824 | 5.53173 | 1.31279 | 0.000725501 | 5.31307e-05 | 3.48011e-05 | 2(Loss) | true |
| simdjson (reflection) | 3191.77 | 0.0491833 | 1010.06ms | 9249 | 2560 | 4729.36 | 2763.52 | 0.146158 | 1.6222 | 7.00778 | 0.995351 | 0.000559055 | 2.83392e-05 | 5.36376e-06 | 3(Loss) | true |
| glaze | 2648.76 | 0.0337708 | 1062.27ms | 9249 | 4890 | 6184.37 | 3330.06 | 0.140075 | 1.94981 | 7.7869 | 1.48524 | 0.00111607 | 1.4814e-05 | 3.00701e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2385.6 | 0.0364925 | 1103.16ms | 9249 | 320 | 582.574 | 3697.4 | 0.0897628 | 2.18421 | 8.04087 | 1.28176 | 0.000962942 | 2.1624e-05 | 3.37874e-07 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3997.52 | 0.185578 | 953.688ms | 9249 | 30 | 503.017 | 2206.5 | 0.0135943 | 1.28859 | 5.22002 | 0.831225 | 0.000544203 | 1.0812e-05 | 3.60399e-06 | 1(Win) | true |
| jsonifier | 3506.68 | 0.0692507 | 992.902ms | 9249 | 80 | 242.737 | 2515.35 | 0.046735 | 1.49409 | 5.30652 | 1.257 | 0.0007217 | 8.10898e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 3277.42 | 0.0500683 | 1005.9ms | 9249 | 320 | 581.033 | 2691.3 | 0.152458 | 1.56647 | 6.87058 | 0.959131 | 0.000556479 | 2.02725e-05 | 5.40599e-06 | 3(Loss) | true |
| glaze | 2801.52 | 0.0753836 | 1045.65ms | 9249 | 1280 | 7210.54 | 3148.49 | 0.118277 | 1.83834 | 7.45086 | 1.41086 | 0.00107495 | 9.88283e-06 | 4.22343e-07 | 4(Loss) | true |
| simdjson (ondemand) | 2482.81 | 0.0322559 | 1094.1ms | 9249 | 4890 | 6421.4 | 3552.64 | 0.0193831 | 2.07107 | 7.69305 | 1.20737 | 0.000723408 | 3.04681e-05 | 1.13426e-05 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 25960.8 | 0.132984 | 757.473ms | 9249 | 4890 | 998.294 | 339.764 | 0.000826176 | 0.220259 | 0.755355 | 0.169646 | 0.000109999 | 2.91857e-05 | 1.19838e-05 | 1(Win) | true |
| glaze | 3992.78 | 0.136923 | 959.229ms | 9249 | 4890 | 44740.9 | 2209.12 | 0.328199 | 1.29324 | 3.46697 | 0.452373 | 0.000375611 | 1.74009e-05 | 3.49344e-06 | 2(Loss) | true |
| simdjson (reflection) | 526.904 | 0.216333 | 2424.22ms | 9249 | 1280 | 1.67874e+06 | 16740.3 | 0.148969 | 9.73927 | 36.173 | 6.67164 | 0.00651194 | 6.00572e-05 | 2.25531e-05 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 29399.3 | 0.125746 | 755.149ms | 9249 | 4890 | 696.003 | 300.025 | 0.0346314 | 0.197147 | 0.700941 | 0.157098 | 0.000108164 | 5.7487e-06 | 8.40195e-07 | 1(Win) | true |
| glaze | 4767.5 | 0.176716 | 916.834ms | 9249 | 2560 | 27365.4 | 1850.14 | 0.168853 | 1.08633 | 3.20251 | 0.393773 | 0.000342478 | 7.55994e-06 | 8.44686e-07 | 2(Loss) | true |
| simdjson (reflection) | 521.101 | 0.153063 | 2434.9ms | 9249 | 2560 | 1.71841e+06 | 16926.7 | 0.19613 | 9.73951 | 36.187 | 6.67629 | 0.00661355 | 6.14509e-05 | 2.48338e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 811.312 | 0.0367917 | 1276.19ms | 4604 | 2560 | 10149.3 | 5411.87 | 0.141469 | 6.30751 | 23.6859 | 5.09057 | 0.00260456 | 6.40577e-05 | 2.0193e-05 | 1(Win) | true |
| simdjson (reflection) | 753.648 | 0.031386 | 1317.79ms | 4604 | 4890 | 16349.9 | 5825.95 | 0.191177 | 6.83689 | 28.4036 | 5.11555 | 0.00464094 | 0.0001106 | 5.48558e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 700.709 | 0.0557066 | 1363.54ms | 4604 | 2560 | 31192.3 | 6266.1 | 0.00179541 | 7.35398 | 27.0031 | 5.419 | 0.00627919 | 0.000593743 | 0.000429314 | 3(Loss) | true |
| glaze | 624.664 | 0.0324232 | 1438.32ms | 4604 | 4890 | 25398 | 7028.92 | 0.272266 | 8.19892 | 33.4844 | 6.95743 | 0.00697904 | 5.96529e-05 | 1.67455e-05 | 4(Loss) | true |
| simdjson (ondemand) | 570.544 | 0.0293449 | 1507.48ms | 4604 | 4890 | 24938.2 | 7695.66 | 0.173246 | 8.93191 | 34.4944 | 6.77389 | 0.00851482 | 0.000109045 | 3.74441e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1005.68 | 0.0541104 | 1258ms | 4604 | 2560 | 14287.3 | 4365.9 | 0.463463 | 5.09772 | 19.1727 | 4.06082 | 0.0018609 | 7.90753e-05 | 2.96108e-05 | 1(Win) | true |
| simdjson (reflection) | 870.744 | 0.0727579 | 1329.67ms | 4604 | 640 | 8614.48 | 5042.49 | 0.0102555 | 5.9607 | 26.1445 | 4.57377 | 0.00220291 | 5.1925e-05 | 9.50261e-06 | 2(Loss) | true |
| jsonifier (two-stage) | 847.679 | 0.102052 | 1349.13ms | 4604 | 640 | 17882.7 | 5179.69 | 0.0564688 | 6.06804 | 22.6751 | 4.43484 | 0.00501093 | 5.66763e-05 | 1.49327e-05 | 3(Loss) | true |
| glaze | 718.375 | 0.119592 | 1429.94ms | 4604 | 160 | 8548.52 | 6112.01 | 0.132702 | 7.08153 | 28.8883 | 5.90085 | 0.00683102 | 3.80104e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 640.399 | 0.0612046 | 1517.32ms | 4604 | 4890 | 86108.5 | 6856.22 | 0.0167489 | 7.94403 | 31.6524 | 6.11888 | 0.00603574 | 0.000110644 | 5.51223e-05 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1796.3 | 0.0822194 | 970.131ms | 4604 | 1280 | 5169.78 | 2444.31 | 0.0508576 | 2.91175 | 8.83818 | 0.572112 | 0.000490742 | 1.5272e-05 | 3.39379e-07 | 1(Win) | true |
| simdjson (reflection) | 1474.43 | 0.0385759 | 1041.43ms | 4918 | 4890 | 7363.21 | 3181 | 0.0189104 | 3.52008 | 11.5492 | 1.38837 | 0.000747764 | 3.04794e-05 | 6.1541e-06 | 2(Loss) | true |
| glaze | 1191.29 | 0.0759918 | 1092.95ms | 4604 | 2560 | 20082.3 | 3685.7 | 0.00557507 | 4.3683 | 12.7667 | 1.12837 | 0.00044255 | 2.30778e-05 | 4.15739e-06 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1823.06 | 0.042893 | 965.182ms | 4604 | 4890 | 5218.56 | 2408.43 | 0.130411 | 2.86054 | 8.76738 | 0.554736 | 0.000485396 | 5.24129e-05 | 1.71008e-05 | 1(Win) | true |
| simdjson (reflection) | 1502.77 | 0.0923561 | 1036.09ms | 4918 | 640 | 5317.43 | 3121.01 | 0.0670907 | 3.46372 | 11.4296 | 1.36092 | 0.000644952 | 3.20888e-05 | 1.71564e-05 | 2(Loss) | true |
| glaze | 1220.15 | 0.132918 | 1083.06ms | 4604 | 1280 | 29283.4 | 3598.52 | 0.0327068 | 4.27283 | 12.2129 | 1.00891 | 0.000718974 | 4.68343e-05 | 1.90052e-05 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 3443.6 | 0.0709816 | 1415.37ms | 24579 | 80 | 1867.6 | 6806.94 | 0.0622139 | 1.50685 | 6.40461 | 0.994914 | 0.000817263 | 3.05139e-05 | 1.9834e-05 | 1(Win) | true |
| jsonifier (two-stage) | 3337.33 | 0.0404277 | 1434.88ms | 24579 | 4890 | 39427.4 | 7023.7 | 0.111761 | 1.5475 | 5.98247 | 1.04569 | 0.00127112 | 3.65168e-05 | 2.01096e-05 | 2(Loss) | true |
| jsonifier | 3037.23 | 0.0546237 | 1505.61ms | 24579 | 80 | 1421.76 | 7717.69 | 0.0493751 | 1.70532 | 6.23589 | 1.42426 | 0.00130447 | 3.55995e-06 | 5.08564e-07 | 3(Loss) | true |
| simdjson (ondemand) | 2716.26 | 0.0388581 | 1613.68ms | 24579 | 2560 | 28786.4 | 8629.64 | 0.00379339 | 1.89522 | 7.61394 | 1.32076 | 0.0015561 | 2.2949e-05 | 6.94508e-06 | 4(Loss) | true |
| glaze | 2195.65 | 0.051739 | 1791.26ms | 24579 | 1280 | 39052.5 | 10675.8 | 0.0183714 | 2.32651 | 10.1868 | 1.96664 | 0.00380482 | 1.42398e-05 | 5.27635e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3901.67 | 0.0450115 | 1435.58ms | 24579 | 80 | 585.012 | 6007.77 | 0.107246 | 1.32996 | 5.19545 | 0.866756 | 0.00108324 | 1.11884e-05 | 4.57708e-06 | 1(Win) | true |
| simdjson (reflection) | 3849.38 | 0.0585616 | 1432.56ms | 24579 | 2560 | 32554.7 | 6089.39 | 0.172375 | 1.33238 | 6.01889 | 0.901244 | 0.000302643 | 1.77203e-05 | 5.68956e-06 | 2(Loss) | true |
| jsonifier | 3443.43 | 0.0559343 | 1502.41ms | 24579 | 1280 | 18557.3 | 6807.28 | 0.00960507 | 1.48288 | 5.43818 | 1.24277 | 0.00115377 | 1.11248e-05 | 5.02207e-06 | 3(Loss) | true |
| simdjson (ondemand) | 3007.39 | 0.0703389 | 1614.06ms | 24579 | 4890 | 146977 | 7794.26 | 0.0874332 | 1.70924 | 6.97865 | 1.17576 | 0.00109639 | 1.22055e-05 | 3.31139e-06 | 4(Loss) | true |
| glaze | 2431.32 | 0.0301231 | 1792.04ms | 24579 | 2560 | 21591.5 | 9641 | 0.0765469 | 2.11667 | 9.36604 | 1.77774 | 0.00392929 | 1.17288e-05 | 3.38513e-06 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8057.43 | 0.111834 | 1023.01ms | 24579 | 1280 | 13548.6 | 2909.16 | 0.0154123 | 0.635903 | 1.76801 | 0.110664 | 9.83436e-05 | 2.09147e-05 | 1.14427e-05 | 1(Win) | true |
| glaze | 3623.79 | 0.120965 | 1385.14ms | 24579 | 1280 | 78367.5 | 6468.47 | 0.00369595 | 1.40923 | 3.99333 | 0.453762 | 0.000316804 | 1.00441e-05 | 3.62352e-06 | 2(Loss) | true |
| simdjson (reflection) | 333.566 | 0.0591061 | 7875.15ms | 24893 | 4890 | 8.65296e+06 | 71169.8 | 0.232034 | 15.2403 | 60.3497 | 11.7233 | 0.0257607 | 0.000215778 | 0.000139862 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8332.24 | 0.0448384 | 1007.4ms | 24579 | 4890 | 7780.61 | 2813.21 | 0.0532156 | 0.616386 | 1.74617 | 0.105537 | 9.82267e-05 | 9.00231e-06 | 1.83042e-06 | 1(Win) | true |
| glaze | 4104.44 | 0.148425 | 1308.13ms | 24579 | 1280 | 91969.5 | 5710.98 | 0.105706 | 1.2428 | 3.83807 | 0.419057 | 0.000253742 | 1.49709e-05 | 4.19565e-06 | 2(Loss) | true |
| simdjson (reflection) | 332.537 | 0.079987 | 7892.35ms | 24893 | 2560 | 8.34746e+06 | 71390.1 | 0.0194913 | 15.3021 | 60.3651 | 11.7273 | 0.0274312 | 0.000314236 | 0.000222766 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 912.668 | 0.0462766 | 1213.33ms | 4604 | 2560 | 12688.4 | 4810.86 | 0.0626526 | 5.59978 | 21.7822 | 4.58559 | 0.00340414 | 0.000172489 | 9.37534e-05 | 1(Win) | true |
| jsonifier (two-stage) | 750.258 | 0.110561 | 1315.19ms | 4604 | 320 | 13396.7 | 5852.27 | 0.0427902 | 6.77869 | 26.0224 | 5.15465 | 0.00586107 | 0.000144575 | 7.26271e-05 | 2(Loss) | true |
| simdjson (reflection) | 741.386 | 0.0277212 | 1326.56ms | 4604 | 4890 | 13179.9 | 5922.31 | 0.172551 | 6.89506 | 28.2619 | 5.10708 | 0.0047486 | 0.000112332 | 4.76602e-05 | 3(Loss) | true |
| glaze | 629.528 | 0.0574228 | 1432.9ms | 4604 | 2560 | 41062.9 | 6974.62 | 0.0388703 | 8.15558 | 32.4329 | 6.76836 | 0.00998232 | 0.000247237 | 0.000140588 | 4(Loss) | true |
| simdjson (ondemand) | 572.68 | 0.129077 | 1498.12ms | 4604 | 160 | 15669.9 | 7666.97 | 0.0710531 | 8.86557 | 33.9145 | 6.6476 | 0.00953519 | 5.83732e-05 | 1.35752e-06 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1128.29 | 0.0605063 | 1209.02ms | 4604 | 2560 | 14192.7 | 3891.46 | 0.00417598 | 4.5363 | 17.712 | 3.65617 | 0.00284688 | 5.15856e-05 | 8.99354e-06 | 1(Win) | true |
| jsonifier (two-stage) | 908.586 | 0.113574 | 1309.12ms | 4604 | 1280 | 38557.2 | 4832.47 | 0.0164711 | 5.6537 | 21.8319 | 4.20243 | 0.00479491 | 5.05674e-05 | 1.64599e-05 | 2(Loss) | true |
| simdjson (reflection) | 855.598 | 0.0993504 | 1337.54ms | 4604 | 80 | 2079.51 | 5131.75 | 0.0175348 | 5.9617 | 25.8591 | 4.53749 | 0.00380919 | 7.33058e-05 | 1.35752e-05 | 3(Loss) | true |
| glaze | 717.979 | 0.0404403 | 1437.43ms | 4604 | 4890 | 29907.9 | 6115.39 | 0.159425 | 7.0958 | 28.175 | 5.7877 | 0.00924536 | 6.73816e-05 | 2.52737e-05 | 4(Loss) | true |
| simdjson (ondemand) | 639.761 | 0.0390781 | 1512.4ms | 4604 | 2560 | 18413.7 | 6863.05 | 0.0275384 | 8.01953 | 31.4934 | 6.08399 | 0.00874961 | 6.76212e-05 | 2.27384e-05 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1838.95 | 0.0976103 | 967.705ms | 4604 | 160 | 869.042 | 2387.62 | 0.100882 | 2.84256 | 8.82515 | 0.570156 | 0.000476488 | 4.2083e-05 | 1.08601e-05 | 1(Win) | true |
| simdjson (reflection) | 1474.18 | 0.0869464 | 1047.75ms | 4918 | 1280 | 9794.68 | 3181.55 | 0.0589683 | 3.49944 | 11.547 | 1.38979 | 0.000593642 | 2.36694e-05 | 6.35421e-06 | 2(Loss) | true |
| glaze | 1210.04 | 0.059213 | 1098.62ms | 4604 | 2560 | 11818 | 3628.57 | 0.320656 | 4.26063 | 12.7252 | 1.12446 | 0.000803055 | 4.08103e-05 | 1.56114e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1845.3 | 0.210152 | 964.548ms | 4604 | 30 | 750.11 | 2379.4 | 0.0825856 | 2.78883 | 8.75456 | 0.552997 | 0.000499566 | 2.89603e-05 | 7.24008e-06 | 1(Win) | true |
| simdjson (reflection) | 1506.54 | 0.0366884 | 1040.94ms | 4918 | 4890 | 6379.48 | 3113.22 | 0.162258 | 3.43512 | 11.4274 | 1.36235 | 0.000726807 | 2.80677e-05 | 1.11439e-05 | 2(Loss) | true |
| glaze | 1219.35 | 0.191134 | 1087.56ms | 4604 | 320 | 15157.9 | 3600.85 | 0.0188359 | 4.19196 | 12.2085 | 1.00804 | 0.000777177 | 2.64715e-05 | 8.82385e-06 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3479.24 | 0.132078 | 1416.22ms | 24579 | 30 | 2375.41 | 6737.2 | 0.0286882 | 1.48981 | 5.83982 | 1.00504 | 0.00112698 | 5.69592e-05 | 2.84796e-05 | 1(Win) | true |
| simdjson (reflection) | 3400.1 | 0.071543 | 1452.94ms | 24579 | 80 | 1946.11 | 6894.01 | 0.0455312 | 1.52432 | 6.40128 | 0.998535 | 0.00100136 | 1.27141e-05 | 2.54282e-06 | 2(Loss) | true |
| jsonifier | 3185.85 | 0.0732367 | 1470.78ms | 24579 | 640 | 18583 | 7357.66 | 0.0710277 | 1.60202 | 6.0688 | 1.37479 | 0.0014112 | 9.66272e-06 | 3.49638e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2691.33 | 0.0649162 | 1597.54ms | 24579 | 320 | 10229.4 | 8709.58 | 0.16213 | 1.88684 | 7.45327 | 1.28547 | 0.00179739 | 1.14427e-05 | 4.3228e-06 | 4(Loss) | true |
| glaze | 2228.45 | 0.072368 | 1776.43ms | 24579 | 30 | 1738.36 | 10518.7 | 0.0294626 | 2.27822 | 9.99811 | 1.92477 | 0.00410106 | 1.76302e-05 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 4080.51 | 0.0529337 | 1411.51ms | 24579 | 80 | 739.695 | 5744.46 | 0.0511624 | 1.27218 | 5.05578 | 0.826966 | 0.000941352 | 1.11884e-05 | 1.01713e-06 | 1(Win) | true |
| simdjson (reflection) | 3887.25 | 0.0408016 | 1427.14ms | 24579 | 2560 | 15496.7 | 6030.07 | 0.138165 | 1.33104 | 5.96391 | 0.894287 | 0.000457454 | 1.54635e-05 | 3.41692e-06 | 2(Loss) | true |
| jsonifier | 3734.82 | 0.137539 | 1465.13ms | 24579 | 160 | 11922.3 | 6276.16 | 0.119357 | 1.38613 | 5.28549 | 1.19659 | 0.00121242 | 8.13703e-06 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 2908.64 | 0.0344163 | 1641.83ms | 24579 | 4890 | 37616.9 | 8058.86 | 0.23495 | 1.76389 | 7.02032 | 1.18426 | 0.00168662 | 2.40949e-05 | 1.04167e-05 | 4(Loss) | true |
| glaze | 2447.17 | 0.0685024 | 1773.76ms | 24579 | 40 | 1722.15 | 9578.55 | 0.0224409 | 2.07561 | 9.23483 | 1.74946 | 0.0036759 | 1.11884e-05 | 0 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8254.67 | 0.0786675 | 1010.77ms | 24579 | 80 | 399.218 | 2839.65 | 0.115464 | 0.633067 | 1.76586 | 0.110501 | 9.61186e-05 | 7.62846e-06 | 0 | 1(Win) | true |
| glaze | 3897.65 | 0.0638168 | 1330.95ms | 24579 | 4890 | 72028.1 | 6013.98 | 0.0492185 | 1.32527 | 3.99451 | 0.453111 | 0.000323925 | 2.78722e-05 | 1.41608e-05 | 2(Loss) | true |
| simdjson (reflection) | 322.908 | 0.079502 | 8105.05ms | 24893 | 2560 | 8.7457e+06 | 73518.9 | 0.0114811 | 15.7925 | 60.4229 | 11.7446 | 0.024297 | 0.00012946 | 7.82568e-05 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 8454.54 | 0.103972 | 1004.07ms | 24579 | 640 | 5318.19 | 2772.52 | 0.199109 | 0.61762 | 1.74401 | 0.105375 | 9.88522e-05 | 7.37418e-06 | 3.17853e-07 | 1(Win) | true |
| glaze | 4119.21 | 0.0725452 | 1304.16ms | 24579 | 4890 | 83334.8 | 5690.5 | 0.251103 | 1.25464 | 3.84096 | 0.417918 | 0.000343819 | 8.73607e-06 | 2.1965e-06 | 2(Loss) | true |
| simdjson (reflection) | 317.376 | 0.154491 | 8197.17ms | 24893 | 640 | 8.54657e+06 | 74800.2 | 0.0250187 | 15.9301 | 60.4354 | 11.7474 | 0.0262637 | 7.46319e-05 | 3.55898e-05 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1006.01 | 0.0642997 | 839.032ms | 1181 | 4890 | 2534.08 | 1119.56 | 0.148481 | 5.24351 | 19.8925 | 4.09568 | 0.00254316 | 6.5973e-05 | 2.07789e-05 | 1(Win) | true |
| simdjson (reflection) | 887.646 | 0.232196 | 856.403ms | 1181 | 40 | 347.208 | 1268.85 | 0.0907155 | 5.98021 | 25.2599 | 4.12701 | 0.00262489 | 6.35055e-05 | 6.35055e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 874.693 | 0.0386033 | 856.106ms | 1181 | 4890 | 1208.22 | 1287.64 | 0.317767 | 5.99166 | 22.9704 | 4.41067 | 0.00259771 | 0.000103721 | 3.53241e-05 | 3(Loss) | true |
| glaze | 833.49 | 0.127018 | 853.824ms | 1181 | 160 | 471.353 | 1351.29 | 0.236711 | 6.28357 | 25.0246 | 4.95597 | 0.00392676 | 4.76291e-05 | 1.05843e-05 | 4(Loss) | true |
| simdjson (ondemand) | 738.345 | 0.181822 | 879.175ms | 1181 | 80 | 615.412 | 1525.42 | 0.0245894 | 7.15911 | 28.8865 | 5.03726 | 0.00358806 | 2.11685e-05 | 0 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1192.22 | 0.208838 | 834.696ms | 1181 | 30 | 116.769 | 944.7 | 0.0953592 | 4.42577 | 16.7273 | 3.37172 | 0.00254022 | 0 | 0 | 1(Win) | true |
| glaze | 1136.78 | 0.0818105 | 835.652ms | 1181 | 640 | 420.48 | 990.772 | 0.307205 | 4.648 | 18.652 | 3.4945 | 0.00269237 | 4.366e-05 | 1.05843e-05 | 2(Loss) | true |
| simdjson (reflection) | 1034.44 | 0.0401719 | 856.394ms | 1181 | 1280 | 244.874 | 1088.79 | 0.013348 | 5.07544 | 22.0085 | 3.37934 | 0.00169943 | 3.37373e-05 | 9.92273e-06 | 3(Loss) | true |
| jsonifier (two-stage) | 1014.82 | 0.185543 | 854.628ms | 1181 | 1280 | 5427.76 | 1109.84 | 0.0303486 | 5.19433 | 19.8188 | 3.69179 | 0.00228157 | 3.57218e-05 | 3.30758e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1000.99 | 0.0792373 | 857.541ms | 1181 | 2560 | 2034.87 | 1125.17 | 0.0293272 | 5.22688 | 22.0212 | 3.49534 | 0.00170076 | 6.01979e-05 | 1.48841e-05 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1734.25 | 0.228854 | 791.73ms | 1181 | 4890 | 10801.9 | 649.437 | 0.760978 | 3.10902 | 7.70195 | 0.773074 | 0.000935224 | 9.07345e-05 | 4.45015e-05 | 1(Win) | true |
| simdjson (reflection) | 1338.9 | 0.0481931 | 807.891ms | 1187 | 320 | 53.128 | 845.478 | 0.170683 | 3.95389 | 13.6639 | 1.44229 | 0.00084246 | 2.36942e-05 | 2.63269e-06 | 2(Loss) | true |
| glaze | 1300.37 | 0.125139 | 814.51ms | 1181 | 2560 | 3007.41 | 866.133 | 0.0251721 | 4.07831 | 10.7417 | 0.920407 | 0.00127408 | 2.94374e-05 | 4.96137e-06 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1998.97 | 0.157621 | 782.852ms | 1181 | 2560 | 2019.09 | 563.434 | 0.126408 | 2.75446 | 7.4276 | 0.706181 | 0.00136967 | 0.000116096 | 6.94591e-05 | 1(Win) | true |
| simdjson (reflection) | 1402.86 | 0.0362292 | 802.148ms | 1187 | 160 | 13.6745 | 806.931 | 0.0224566 | 3.85379 | 13.2595 | 1.34794 | 0.00084246 | 3.68576e-05 | 0 | 2(Loss) | true |
| glaze | 1336.75 | 0.066043 | 811.524ms | 1181 | 2560 | 792.666 | 842.555 | 0.128165 | 3.97071 | 10.1575 | 0.790855 | 0.00113251 | 3.73756e-05 | 1.0915e-05 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1777.97 | 0.100757 | 866.368ms | 2496 | 160 | 291.147 | 1338.81 | 0.270559 | 2.92847 | 12.6422 | 1.96675 | 0.0012495 | 2.25361e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 1695.3 | 0.120605 | 868.762ms | 2496 | 2560 | 7341.18 | 1404.1 | 0.251123 | 3.0907 | 11.7925 | 2.16587 | 0.00150303 | 0.000215971 | 0.000123635 | 2(Loss) | true |
| jsonifier | 1528.92 | 0.0603733 | 883.315ms | 2496 | 2560 | 2261.76 | 1556.89 | 0.0359167 | 3.40602 | 12.7452 | 2.8738 | 0.00193779 | 6.15047e-05 | 3.16131e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1511.98 | 0.0930728 | 887.173ms | 2496 | 4890 | 10499.1 | 1574.34 | 0.102227 | 3.43781 | 14.2568 | 2.3774 | 0.00166385 | 6.08745e-05 | 2.18755e-05 | 4(Loss) | true |
| glaze | 1364.41 | 0.0573963 | 898.857ms | 2496 | 4890 | 4903.16 | 1744.62 | 0.167195 | 3.7985 | 15.389 | 3.10577 | 0.00276508 | 6.48891e-05 | 2.46611e-05 | 5(Loss) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2108.54 | 0.0793992 | 860.163ms | 2496 | 320 | 257.103 | 1128.92 | 0.137111 | 2.48623 | 11.1038 | 1.61298 | 0.000803786 | 2.00321e-05 | 6.26002e-06 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2023.83 | 0.114296 | 863.917ms | 2496 | 160 | 289.147 | 1176.17 | 0.109876 | 2.63481 | 10.3013 | 1.82572 | 0.000803786 | 5.75921e-05 | 2.50401e-06 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2022.63 | 0.148887 | 861.293ms | 2496 | 160 | 491.234 | 1176.87 | 0.0100893 | 2.58542 | 11.1098 | 1.66787 | 0.000816306 | 5.25841e-05 | 2.50401e-05 | 2(Tie) | true |
| glaze | 1782.05 | 0.0617508 | 876.157ms | 2496 | 4890 | 3326.93 | 1335.75 | 0.135469 | 2.93974 | 12.3105 | 2.41426 | 0.00181706 | 3.85074e-05 | 1.08968e-05 | 4(Loss) | true |
| jsonifier | 1737.77 | 0.0787573 | 881.64ms | 2496 | 80 | 93.1062 | 1369.79 | 0.161261 | 2.99891 | 11.2448 | 2.53365 | 0.00142728 | 2.00321e-05 | 0 | 5(Loss) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4402.39 | 0.0705206 | 781.368ms | 2496 | 1280 | 186.104 | 540.7 | 0.64714 | 1.24349 | 3.80769 | 0.383013 | 0.00044853 | 1.3146e-05 | 1.252e-06 | 1(Win) | true |
| glaze | 2096.03 | 0.078851 | 841.794ms | 2507 | 2560 | 2070.94 | 1140.66 | 0.414597 | 2.51552 | 7.33706 | 0.85002 | 0.000640394 | 2.0879e-05 | 9.19301e-06 | 2(Loss) | true |
| simdjson (reflection) | 195.267 | 0.0393476 | 1964.03ms | 2502 | 2560 | 59182.4 | 12219.6 | 0.0663195 | 26.101 | 98.5632 | 18.4197 | 0.0281709 | 0.000409985 | 0.000205148 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4648.51 | 0.100982 | 773.564ms | 2496 | 320 | 85.5654 | 512.072 | 0.0286907 | 1.1712 | 3.60978 | 0.33734 | 0.000445713 | 1.0016e-05 | 0 | 1(Win) | true |
| glaze | 2297.82 | 0.0957124 | 830.478ms | 2507 | 4890 | 4849.8 | 1040.49 | 0.354612 | 2.30369 | 6.59234 | 0.686478 | 0.000729573 | 2.38188e-05 | 1.05227e-05 | 2(Loss) | true |
| simdjson (reflection) | 197.48 | 0.130918 | 1950.22ms | 2502 | 160 | 40035.5 | 12082.7 | 0.00801831 | 26.1164 | 98.5711 | 18.4215 | 0.0292366 | 0.000107414 | 2.2482e-05 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2179.82 | 0.0692664 | 944.127ms | 4926 | 1280 | 2852.36 | 2155.13 | 0.135972 | 2.36805 | 10.4657 | 1.84247 | 0.000568413 | 2.14106e-05 | 5.7095e-06 | 1(Win) | true |
| jsonifier (two-stage) | 1775.56 | 0.0304701 | 989.117ms | 4926 | 2560 | 1663.81 | 2645.81 | 0.341852 | 2.90856 | 13.0798 | 2.16768 | 0.00423811 | 2.59306e-05 | 4.44072e-06 | 2(Loss) | true |
| glaze | 1450.83 | 0.0971686 | 1047.36ms | 4926 | 640 | 6335.57 | 3238 | 0.232308 | 3.52668 | 15.3825 | 2.94052 | 0.00194028 | 3.80633e-05 | 7.29547e-06 | 3(Loss) | true |
| simdjson (reflection) | 1272.52 | 0.0653382 | 1107.68ms | 4926 | 1280 | 7447.36 | 3691.72 | 0.100166 | 4.02627 | 14.9251 | 2.48275 | 0.00487702 | 4.77378e-05 | 7.29547e-06 | 4(Loss) | true |
| simdjson (ondemand) | 894.885 | 0.0531793 | 1258.26ms | 4926 | 640 | 4987.92 | 5249.62 | 0.0418062 | 5.69244 | 17.7377 | 3.10881 | 0.00412067 | 7.51751e-05 | 3.61602e-05 | 5(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2696.84 | 0.185895 | 941.585ms | 4926 | 30 | 314.585 | 1741.97 | 0.0439922 | 1.92126 | 8.79963 | 1.45717 | 0.000236839 | 1.35336e-05 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 2108.88 | 0.0490122 | 989.077ms | 4926 | 4890 | 5829.13 | 2227.63 | 0.285578 | 2.47328 | 11.4134 | 1.78259 | 0.00389947 | 2.81051e-05 | 4.15142e-06 | 2(Loss) | true |
| glaze | 1848.4 | 0.0598574 | 1019.21ms | 4926 | 2560 | 5924.77 | 2541.55 | 0.0782154 | 2.78724 | 12.8053 | 2.41413 | 0.00161896 | 3.24331e-05 | 6.18529e-06 | 3(Loss) | true |
| simdjson (reflection) | 1414 | 0.0806013 | 1105.89ms | 4926 | 160 | 1147.35 | 3322.35 | 0.0582832 | 3.67922 | 14.2095 | 2.29212 | 0.00376573 | 5.45575e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1042.97 | 0.0935579 | 1213.77ms | 4926 | 640 | 11365.5 | 4504.26 | 0.249417 | 4.89835 | 15.2986 | 2.62383 | 0.00438268 | 3.90149e-05 | 3.48914e-06 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10756.6 | 0.071444 | 769.971ms | 4926 | 1280 | 124.617 | 436.735 | 0.345542 | 0.513667 | 2.12505 | 0.314454 | 0.000203004 | 1.60183e-05 | 5.5509e-06 | 1(Win) | true |
| simdjson (reflection) | 7623.24 | 0.0710057 | 789.007ms | 4926 | 4890 | 936.279 | 616.247 | 0.201045 | 0.712612 | 2.60272 | 0.344093 | 0.000203378 | 4.29672e-05 | 1.78511e-05 | 2(Loss) | true |
| glaze | 3961.14 | 0.180543 | 847.753ms | 4926 | 640 | 2934.19 | 1185.97 | 0.095477 | 1.34077 | 6.0877 | 0.981933 | 0.000203004 | 2.94991e-05 | 2.53756e-06 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12741.1 | 0.181372 | 758.41ms | 4926 | 80 | 35.7771 | 368.712 | 0.105206 | 0.442425 | 1.99391 | 0.284409 | 0.000203004 | 5.07511e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 8131.3 | 0.0922354 | 782.99ms | 4926 | 4890 | 1388.59 | 577.743 | 0.0694291 | 0.672277 | 2.47462 | 0.314454 | 0.00027993 | 3.03884e-05 | 1.44885e-05 | 2(Loss) | true |
| glaze | 4551.4 | 0.0920082 | 826.016ms | 4926 | 4890 | 4410.22 | 1032.17 | 0.0457001 | 1.16008 | 5.5745 | 0.871904 | 0.000216123 | 2.06741e-05 | 5.97805e-06 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3110.29 | 0.083002 | 1019.91ms | 9463 | 160 | 928.011 | 2901.54 | 0.0361746 | 1.67414 | 7.42841 | 1.14234 | 0.0021769 | 1.18884e-05 | 0 | 1(Win) | true |
| jsonifier | 2824.4 | 0.0927345 | 1049.48ms | 9463 | 640 | 5619.13 | 3195.24 | 0.0244564 | 1.84521 | 7.54972 | 1.53292 | 0.00104734 | 2.21256e-05 | 8.25584e-06 | 2(Loss) | true |
| simdjson (reflection) | 2338.68 | 0.0746366 | 1112.48ms | 9463 | 1280 | 10617.7 | 3858.86 | 0.0703626 | 2.20607 | 8.38275 | 1.30994 | 0.00245983 | 3.06292e-05 | 9.65933e-06 | 3(Loss) | true |
| glaze | 2144.48 | 0.0695857 | 1152.15ms | 9463 | 1280 | 10976.5 | 4208.31 | 0.0248517 | 2.41912 | 10.693 | 2.07704 | 0.00231593 | 1.39524e-05 | 1.56861e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1671.27 | 0.0683723 | 1275.21ms | 9463 | 4890 | 66655.3 | 5399.86 | 0.120399 | 3.10209 | 9.89466 | 1.64768 | 0.00216739 | 0.000114773 | 6.44854e-05 | 5(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3555.87 | 0.0618713 | 1023.57ms | 9463 | 1280 | 3156.12 | 2537.95 | 0.0513808 | 1.44637 | 6.56092 | 0.941879 | 0.00206132 | 1.64291e-05 | 1.73373e-06 | 1(Win) | true |
| jsonifier | 3165.61 | 0.104192 | 1052.66ms | 9463 | 640 | 5646.62 | 2850.83 | 0.125889 | 1.61908 | 6.68245 | 1.33245 | 0.000893612 | 2.19605e-05 | 2.31163e-06 | 2(Loss) | true |
| simdjson (reflection) | 2560.8 | 0.055336 | 1121.77ms | 9463 | 2560 | 9735.54 | 3524.14 | 0.0666386 | 2.01779 | 7.96545 | 1.20099 | 0.00183185 | 4.87507e-05 | 1.57687e-05 | 3(Loss) | true |
| glaze | 2489.3 | 0.0257057 | 1130.43ms | 9463 | 4890 | 4246.91 | 3625.37 | 0.107999 | 2.05627 | 9.35348 | 1.80313 | 0.00289732 | 1.68345e-05 | 2.46358e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1922.86 | 0.0795146 | 1226.05ms | 9463 | 160 | 2228.31 | 4693.33 | 0.0214446 | 2.65383 | 8.62242 | 1.3947 | 0.00231956 | 1.78326e-05 | 2.64187e-06 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 20195.2 | 0.158111 | 771.97ms | 9463 | 4890 | 2441.14 | 446.87 | 0.069892 | 0.271927 | 1.19645 | 0.16126 | 0.000105956 | 1.13238e-05 | 3.73859e-06 | 1(Win) | true |
| glaze | 4736.3 | 0.129017 | 922.184ms | 9463 | 640 | 3867.7 | 1905.42 | 0.0834095 | 1.10467 | 4.70823 | 0.710346 | 0.000147119 | 1.25489e-05 | 1.81628e-06 | 2(Loss) | true |
| simdjson (reflection) | 585.287 | 0.131395 | 2285.34ms | 9463 | 2560 | 1.05079e+06 | 15419.1 | 0.339038 | 8.78004 | 36.6651 | 6.75813 | 0.00897517 | 8.42096e-05 | 4.04949e-05 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 21982.8 | 0.150472 | 766.006ms | 9463 | 160 | 61.0556 | 410.531 | 0.196007 | 0.25218 | 1.14023 | 0.14805 | 0.000105675 | 7.9256e-06 | 6.60467e-07 | 1(Win) | true |
| glaze | 5771.71 | 0.0577236 | 883.698ms | 9463 | 4890 | 3983.49 | 1563.59 | 0.234512 | 0.905692 | 4.3724 | 0.634577 | 0.000147059 | 1.52785e-05 | 4.30046e-06 | 2(Loss) | true |
| simdjson (reflection) | 583.533 | 0.0942359 | 2285.29ms | 9463 | 4890 | 1.03865e+06 | 15465.5 | 0.0091815 | 8.77972 | 36.6544 | 6.75355 | 0.00914614 | 0.000103622 | 4.89475e-05 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 5926.28 | 0.126437 | 791.654ms | 2821 | 4890 | 1611.02 | 453.963 | 0.00401909 | 0.941588 | 3.50833 | 0.458703 | 0.000355644 | 2.04426e-05 | 8.11907e-06 | 1(Win) | true |
| jsonifier (two-stage) | 5861.69 | 0.101274 | 765.9ms | 2821 | 320 | 69.1367 | 458.966 | 0.222153 | 0.938175 | 3.50833 | 0.458703 | 0.000354484 | 9.96987e-06 | 2.21553e-06 | 2(Loss) | true |
| simdjson (ondemand) | 4701.49 | 0.0824594 | 782.21ms | 2821 | 4890 | 1088.74 | 572.226 | 0.364005 | 1.15289 | 4.53492 | 0.696208 | 0.000711506 | 1.86304e-05 | 2.17475e-06 | 3(Loss) | true |
| simdjson (reflection) | 4635.97 | 0.127522 | 783.601ms | 2821 | 2560 | 1401.97 | 580.314 | 0.0760539 | 1.16374 | 4.56895 | 0.70436 | 0.000705645 | 2.28476e-05 | 6.23117e-06 | 4(Loss) | true |
| glaze | 2577.05 | 0.0462672 | 823.705ms | 2821 | 4890 | 1140.81 | 1043.95 | 0.148824 | 2.06825 | 8.76604 | 1.35909 | 0.000576816 | 1.57307e-05 | 4.20452e-06 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 6186.41 | 0.248399 | 765.595ms | 2821 | 80 | 93.3513 | 434.875 | 0.427227 | 0.908627 | 3.35945 | 0.423609 | 0.000385502 | 8.86211e-06 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 6095.63 | 0.123653 | 769.55ms | 2821 | 2560 | 762.466 | 441.352 | 0.348154 | 0.907899 | 3.35945 | 0.423609 | 0.000355038 | 2.03551e-05 | 4.43105e-06 | 2(Loss) | true |
| simdjson (ondemand) | 4894.78 | 0.174451 | 780.856ms | 2821 | 2560 | 2353.58 | 549.63 | 0.0674715 | 1.11206 | 4.45977 | 0.677774 | 0.000709107 | 3.90487e-05 | 1.63395e-05 | 3(Loss) | true |
| simdjson (reflection) | 4688.56 | 0.170536 | 778.179ms | 2821 | 1280 | 1225.66 | 573.804 | 0.250466 | 1.15169 | 4.49841 | 0.686636 | 0.000707861 | 2.71402e-05 | 3.87717e-06 | 4(Loss) | true |
| glaze | 2653.79 | 0.093705 | 822.879ms | 2821 | 160 | 144.383 | 1013.76 | 0.0234331 | 2.01673 | 8.69231 | 1.3403 | 0.0003567 | 1.32932e-05 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7484.2 | 0.0950017 | 775.729ms | 4147 | 320 | 80.6473 | 528.431 | 0.427609 | 0.739303 | 2.85001 | 0.319267 | 0.000241138 | 9.04268e-06 | 0 | 1(Win) | true |
| jsonifier | 7443.95 | 0.0705338 | 778.78ms | 4147 | 1280 | 179.749 | 531.289 | 0.245879 | 0.740281 | 2.85001 | 0.319267 | 0.000241327 | 7.15879e-06 | 3.01423e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6273.67 | 0.113532 | 780.276ms | 4147 | 4890 | 2504.77 | 630.394 | 0.088169 | 0.866705 | 3.52592 | 0.492163 | 0.000474682 | 1.6569e-05 | 3.69844e-06 | 3(Loss) | true |
| simdjson (reflection) | 6081.78 | 0.133198 | 786.022ms | 4147 | 2560 | 1920.62 | 650.285 | 0.0634535 | 0.893357 | 3.5491 | 0.497715 | 0.000426042 | 1.99693e-05 | 4.99231e-06 | 4(Loss) | true |
| glaze | 3274.46 | 0.225835 | 845.771ms | 4147 | 30 | 223.2 | 1207.8 | 0.137802 | 1.59429 | 7.18736 | 1.20039 | 0.000329556 | 0 | 0 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 7776.25 | 0.156973 | 777.946ms | 4147 | 1280 | 815.802 | 508.585 | 0.113084 | 0.713308 | 2.74873 | 0.295394 | 0.000241703 | 5.84007e-06 | 1.50711e-06 | 1(Win) | true |
| jsonifier | 7579.14 | 0.139615 | 777.798ms | 4147 | 160 | 84.9206 | 521.812 | 0 | 0.718488 | 2.74873 | 0.295394 | 0.000241138 | 6.02845e-06 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 6428.41 | 0.259596 | 783.143ms | 4147 | 1280 | 3264.87 | 615.22 | 0.099657 | 0.849001 | 3.4748 | 0.479624 | 0.000475683 | 1.07382e-05 | 3.57939e-06 | 3(Loss) | true |
| simdjson (reflection) | 6135.42 | 0.0736139 | 788.588ms | 4147 | 4890 | 1101.06 | 644.6 | 0.246306 | 0.884102 | 3.50109 | 0.485652 | 0.000424433 | 1.91333e-05 | 3.64913e-06 | 4(Loss) | true |
| glaze | 3368.05 | 0.149533 | 841.399ms | 4147 | 640 | 1973.18 | 1174.24 | 0.205031 | 1.56177 | 7.136 | 1.18761 | 0.000253572 | 6.40523e-06 | 3.76778e-07 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 2935.2 | 0.0659157 | 816.103ms | 2821 | 320 | 116.804 | 916.569 | 0.0306945 | 1.83163 | 5.99078 | 1.01418 | 0.000354484 | 5.76037e-05 | 2.3263e-05 | 1(Win) | true |
| glaze | 2307.86 | 0.155975 | 845.337ms | 2821 | 1280 | 4231.61 | 1165.72 | 0.0563979 | 2.27784 | 8.92308 | 1.52889 | 0.000518156 | 4.62491e-05 | 1.44009e-05 | 2(Loss) | true |
| jsonifier (two-stage) | 2185.65 | 0.161703 | 849.812ms | 2821 | 30 | 118.852 | 1230.9 | 0.00270812 | 2.38804 | 7.97519 | 1.22722 | 0.0003663 | 0.000212691 | 7.08968e-05 | 3(Loss) | true |
| simdjson (reflection) | 2100.58 | 0.0567972 | 853.501ms | 2821 | 4890 | 2587.57 | 1280.75 | 0.0417127 | 2.53178 | 9.05388 | 1.38639 | 0.000440387 | 7.4159e-05 | 1.71805e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1633.55 | 0.0638167 | 887.873ms | 2821 | 320 | 353.475 | 1646.91 | 0.0616305 | 3.22905 | 9.88089 | 1.71783 | 0.000580468 | 2.54786e-05 | 0 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3363.03 | 0.058894 | 815.885ms | 2821 | 160 | 35.5147 | 799.969 | 0.141612 | 1.62642 | 5.43602 | 0.86955 | 0.00105016 | 1.32932e-05 | 0 | 1(Win) | true |
| glaze | 2523.1 | 0.0679531 | 841.596ms | 2821 | 320 | 167.998 | 1066.27 | 0.158219 | 2.08677 | 8.41014 | 1.39135 | 0.000516218 | 1.8832e-05 | 0 | 2(Loss) | true |
| jsonifier (two-stage) | 2487.75 | 0.0788596 | 841.363ms | 2821 | 640 | 465.459 | 1081.42 | 0.185176 | 2.14958 | 7.22297 | 1.04289 | 0.000384394 | 4.26489e-05 | 2.76941e-05 | 3(Loss) | true |
| simdjson (reflection) | 2256.48 | 0.114305 | 852.064ms | 2821 | 1280 | 2377.29 | 1192.26 | 0.0764768 | 2.36925 | 8.51471 | 1.24778 | 0.000714507 | 7.80973e-05 | 2.71402e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1719.55 | 0.0485816 | 889.027ms | 2821 | 4890 | 2825.06 | 1564.54 | 0.357763 | 3.07409 | 9.46154 | 1.60794 | 0.000976463 | 7.44489e-05 | 1.84854e-05 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 7833.07 | 0.124862 | 754.182ms | 2821 | 320 | 58.8507 | 343.456 | 0.164045 | 0.719765 | 1.71854 | 0.255583 | 0.000354484 | 6.64658e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 6036.91 | 0.18567 | 773.593ms | 2821 | 1280 | 876.334 | 445.645 | 0.146867 | 0.919155 | 2.08791 | 0.322935 | 0.000354761 | 3.43407e-05 | 1.08007e-05 | 2(Loss) | true |
| glaze | 5376.14 | 0.240662 | 776.54ms | 2819 | 320 | 463.463 | 500.062 | 0.103845 | 1.02723 | 3.02519 | 0.457254 | 0.000358061 | 1.66282e-05 | 2.2171e-06 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 9069.9 | 0.346523 | 755.523ms | 2821 | 1280 | 1352.31 | 296.62 | 0.0989344 | 0.635144 | 1.55441 | 0.216236 | 0.000374147 | 2.49247e-05 | 1.27393e-05 | 1(Win) | true |
| simdjson (reflection) | 6676.93 | 0.0608013 | 768.45ms | 2821 | 4890 | 293.486 | 402.927 | 0.019357 | 0.837617 | 1.91563 | 0.281815 | 0.000354702 | 3.29112e-05 | 1.06563e-05 | 2(Loss) | true |
| glaze | 6054.44 | 0.23456 | 770.496ms | 2819 | 640 | 694.275 | 444.039 | 0.0973768 | 0.918026 | 2.58815 | 0.365378 | 0.000387992 | 3.60278e-05 | 2.05082e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3092.23 | 0.119606 | 853.771ms | 4147 | 1280 | 2995.32 | 1278.98 | 0.174332 | 1.70995 | 5.89486 | 0.84302 | 0.000246601 | 3.33449e-05 | 1.13034e-05 | 1(Win) | true |
| simdjson (reflection) | 2914.03 | 0.165117 | 868.093ms | 4147 | 80 | 401.749 | 1357.19 | 0.0487904 | 1.78809 | 6.59995 | 0.961659 | 0.000409935 | 3.9185e-05 | 6.02845e-06 | 2(Loss) | true |
| glaze | 2568.81 | 0.0649772 | 886.813ms | 4147 | 1280 | 1280.97 | 1539.58 | 0.0511748 | 2.02395 | 7.97106 | 1.4191 | 0.00024566 | 2.33603e-05 | 3.76778e-06 | 3(Loss) | true |
| jsonifier | 2402.01 | 0.0763784 | 888.448ms | 4147 | 320 | 506.069 | 1646.49 | 0.0256161 | 2.18232 | 5.61177 | 1.09525 | 0.000367736 | 2.48674e-05 | 4.52134e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2297.84 | 0.0458448 | 903.223ms | 4147 | 4890 | 3044.51 | 1721.13 | 0.277381 | 2.25864 | 7.16253 | 1.18712 | 0.000289464 | 5.17288e-05 | 2.10071e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (two-stage) | 3444.82 | 0.082756 | 844.827ms | 4147 | 160 | 144.429 | 1148.07 | 0.025593 | 1.5305 | 5.38317 | 0.717627 | 0.000629973 | 2.86352e-05 | 2.26067e-05 | 1(Win) | true |
| simdjson (reflection) | 3177.3 | 0.372264 | 860.572ms | 4147 | 30 | 644.133 | 1244.73 | 0.0321457 | 1.65653 | 6.23415 | 0.867615 | 0.000482276 | 3.21518e-05 | 0 | 2(Loss) | true |
| glaze | 2738.46 | 0.161124 | 880.627ms | 4147 | 30 | 162.441 | 1444.2 | 0.0808482 | 1.90746 | 7.56113 | 1.31348 | 0.000723415 | 0.000120569 | 4.01897e-05 | 3(Loss) | true |
| jsonifier | 2601.95 | 0.104635 | 879.791ms | 4147 | 160 | 404.71 | 1519.97 | 0.181008 | 2.00833 | 5.23511 | 0.997106 | 0.00067368 | 6.32988e-05 | 2.56209e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2452.67 | 0.0908897 | 896.986ms | 4147 | 2560 | 5498.7 | 1612.48 | 0.20853 | 2.13579 | 6.87737 | 1.11239 | 0.000454206 | 5.84948e-05 | 2.19473e-05 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11128.6 | 0.0794034 | 767.031ms | 4147 | 1280 | 101.923 | 355.379 | 0.166139 | 0.505219 | 1.21075 | 0.173378 | 0.000382053 | 1.22453e-05 | 2.44906e-06 | 1(Win) | true |
| glaze | 3127.4 | 0.187048 | 860.278ms | 4145 | 2560 | 14309.7 | 1263.98 | 0.014218 | 1.69388 | 3.55738 | 0.510736 | 0.000521242 | 2.72354e-05 | 8.57584e-06 | 2(Loss) | true |
| simdjson (reflection) | 519.362 | 0.06663 | 1531.56ms | 4147 | 4890 | 125886 | 7614.9 | 0.745818 | 9.88808 | 34.3993 | 6.85291 | 0.00438709 | 0.000129347 | 5.11864e-05 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13015.3 | 0.125524 | 758.794ms | 4147 | 640 | 93.1098 | 303.864 | 0.479994 | 0.443444 | 1.09549 | 0.146371 | 0.000257716 | 1.09266e-05 | 2.26067e-06 | 1(Win) | true |
| glaze | 3500.85 | 0.209677 | 841.45ms | 4145 | 320 | 1793.73 | 1129.15 | 0.734611 | 1.49717 | 2.98239 | 0.379252 | 0.000431242 | 9.80097e-06 | 7.5392e-07 | 2(Loss) | true |
| simdjson (reflection) | 516.081 | 0.0971035 | 1507.47ms | 4147 | 2560 | 141756 | 7663.31 | 0.0159521 | 9.8867 | 34.4066 | 6.85437 | 0.00459802 | 0.000214669 | 0.000118968 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3217.18 | 0.101132 | 7451.9ms | 466906 | 320 | 6.26951e+06 | 138406 | 0.109553 | 1.56569 | 6.22386 | 1.20532 | 0.00244521 | 2.49716e-05 | 2.19396e-05 | 1(Win) | true |
| glaze | 2412.11 | 0.0583903 | 9903.97ms | 466906 | 320 | 3.71789e+06 | 184600 | 0.388355 | 2.11696 | 8.76994 | 1.98464 | 0.0027034 | 2.08821e-05 | 1.81514e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1341.56 | 0.418626 | 8845.55ms | 466906 | 30 | 5.79178e+07 | 331909 | 0.303726 | 3.75316 | 14.2926 | 2.49666 | 0.0134481 | 0.0908128 | 3.43395e-05 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3221.09 | 0.0583272 | 7490.86ms | 466906 | 1280 | 8.32158e+06 | 138238 | 0.0229107 | 1.5672 | 6.22313 | 1.20516 | 0.00252372 | 2.82729e-05 | 1.52266e-05 | 1(Win) | true |
| glaze | 2389.76 | 0.0830884 | 9901.64ms | 466906 | 40 | 958722 | 186327 | 0.10083 | 2.11379 | 8.76886 | 1.98439 | 0.00259619 | 1.62774e-05 | 1.25293e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1323.71 | 0.239044 | 8825.59ms | 466906 | 1280 | 8.27628e+08 | 336384 | 0.179689 | 3.79169 | 14.2924 | 2.49664 | 0.0137678 | 0.0924189 | 3.20745e-05 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4542.24 | 0.0478421 | 7915.21ms | 699405 | 2560 | 1.26351e+07 | 146845 | 0.176687 | 1.10918 | 4.55041 | 1.10249 | 0.00226295 | 0.000283123 | 2.14803e-05 | 1(Win) | true |
| glaze | 3667.89 | 0.0427876 | 9681.45ms | 699405 | 640 | 3.87471e+06 | 181849 | 0.0334883 | 1.377 | 6.02373 | 1.25783 | 0.00206996 | 4.51053e-06 | 3.25947e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1489.12 | 0.765219 | 6369.93ms | 767297 | 320 | 4.5247e+09 | 491398 | 0.0294207 | 3.37336 | 13.9345 | 2.26931 | 0.0108213 | 0.0907757 | 2.62651e-05 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4578.04 | 0.0777448 | 7885.11ms | 699405 | 640 | 8.21147e+06 | 145696 | 0.216294 | 1.11046 | 4.54991 | 1.10239 | 0.00226976 | 0.000223922 | 5.46893e-06 | 1(Win) | true |
| glaze | 3666.09 | 0.0419894 | 9695.22ms | 699405 | 640 | 3.73517e+06 | 181939 | 0.00201652 | 1.38105 | 6.02304 | 1.25768 | 0.00209849 | 8.74181e-06 | 7.31425e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1515.58 | 0.660889 | 6290.75ms | 767297 | 160 | 1.62909e+09 | 482819 | 0.238375 | 3.3136 | 13.9348 | 2.26938 | 0.0108068 | 0.0852492 | 6.16776e-05 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3019.08 | 0.311773 | 5293.05ms | 631514 | 80 | 3.09445e+07 | 199484 | 0.230682 | 1.68134 | 8.04056 | 1.32243 | 0.00559505 | 8.09562e-05 | 7.23064e-05 | 1(Win) | true |
| glaze | 2451.5 | 0.119531 | 6464.5ms | 631514 | 160 | 1.37969e+07 | 245670 | 0.0102944 | 2.07154 | 8.43595 | 1.51701 | 0.00876723 | 1.57063e-05 | 1.38655e-05 | 2(Loss) | true |
