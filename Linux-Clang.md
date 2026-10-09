# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 10, 2026)
#### Using the following commits:
----
| Jsonifier: [5aa6104](https://github.com/nihilai-collective/jsonifier/commit/5aa6104)  
| Glaze: [e194d23](https://github.com/stephenberry/glaze/commit/e194d23)  
| Simdjson: [7f6f8dc](https://github.com/simdjson/simdjson/commit/7f6f8dc)  

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

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1778.76 | 0.333544 | 777.094ms | 905 | 80 | 209.537 | 485.212 | 3.11742 | 15.053 | 2.9547 | 0.00131215 | 0.000110497 | 0 | 1(Win) |
| glaze | 1570.23 | 0.0330785 | 783.624ms | 905 | 4890 | 161.648 | 549.649 | 3.49181 | 17.589 | 2.29171 | 0.00264832 | 0.000115017 | 1.83032e-05 | 2(Loss) |
| jsonifier (two-stage) | 363.009 | 0.0469964 | 965.25ms | 905 | 2560 | 3196.18 | 2377.56 | 14.1879 | 45.2597 | 7.03757 | 0.00571176 | 0.00015366 | 4.48895e-05 | 3(Loss) |
| simdjson (ondemand) | 232.414 | 0.0353463 | 1102.39ms | 905 | 320 | 551.328 | 3713.53 | 22.0351 | 90.9072 | 10.6895 | 0.0265331 | 0.000224448 | 8.28729e-05 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1926.73 | 0.057986 | 771.221ms | 905 | 4890 | 329.922 | 447.948 | 2.86196 | 14.389 | 2.83425 | 0.00138653 | 0.000109593 | 1.17502e-05 | 1(Win) |
| glaze | 1692.24 | 0.231364 | 778.167ms | 905 | 1280 | 1782.27 | 510.02 | 3.21513 | 16.9249 | 2.17127 | 0.00111792 | 0.00011395 | 3.10773e-05 | 2(Loss) |
| jsonifier (two-stage) | 371.541 | 0.0464279 | 958.556ms | 905 | 1280 | 1488.85 | 2322.96 | 13.8382 | 44.642 | 6.91713 | 0.00448463 | 8.11464e-05 | 1.03591e-05 | 3(Loss) |
| simdjson (ondemand) | 231.738 | 0.128346 | 1113.7ms | 905 | 320 | 7311.61 | 3724.35 | 21.7589 | 90.2928 | 10.5691 | 0.023674 | 0.000169199 | 6.56077e-05 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1905.09 | 0.284796 | 774.7ms | 905 | 80 | 133.176 | 453.038 | 2.89461 | 10.8331 | 1.58564 | 0.00343923 | 2.76243e-05 | 0 | 1(Win) |
| glaze | 209.181 | 0.0765687 | 1152.65ms | 905 | 640 | 6387.55 | 4125.97 | 24.3309 | 112.314 | 22.8751 | 0.0751519 | 0.000359116 | 0.000167472 | 2(Loss) |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3181.29 | 0.084046 | 763.48ms | 905 | 4890 | 254.234 | 271.297 | 1.82165 | 7.58785 | 0.939227 | 0.00222328 | 4.74528e-05 | 4.51931e-06 | 1(Win) |
| glaze | 930.715 | 0.295852 | 834.089ms | 905 | 80 | 602.146 | 927.325 | 5.69698 | 24.5017 | 3.14917 | 0.00117403 | 0.000220994 | 0.000151934 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1230.1 | 0.173172 | 869.512ms | 1811 | 160 | 945.873 | 1404.04 | 4.2288 | 20.2192 | 4.28824 | 0.000697129 | 0.000224324 | 4.48647e-05 | 1(Win) |
| glaze | 972.028 | 0.0339536 | 911.66ms | 1811 | 4890 | 1779.75 | 1776.81 | 5.30331 | 26.5058 | 4.27885 | 0.000807381 | 8.32224e-05 | 1.71639e-05 | 2(Loss) |
| jsonifier (two-stage) | 449.318 | 0.0242399 | 1116.29ms | 1811 | 4890 | 4245.21 | 3843.83 | 11.3668 | 35.55 | 6.4434 | 0.000577362 | 0.000113824 | 3.07144e-05 | 3(Loss) |
| simdjson (ondemand) | 271.218 | 0.057094 | 1367.8ms | 1811 | 80 | 1057.48 | 6367.96 | 18.7654 | 69.5345 | 9.53065 | 0.00635699 | 0.000193263 | 6.90226e-06 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1352.55 | 0.0457121 | 856.999ms | 1811 | 4890 | 1666.1 | 1276.92 | 3.8474 | 19.1872 | 4.05467 | 0.000914995 | 9.33852e-05 | 2.21324e-05 | 1(Win) |
| glaze | 1040.59 | 0.0290847 | 894.607ms | 1811 | 4890 | 1139.51 | 1659.74 | 4.9682 | 25.4859 | 4.04583 | 0.00110933 | 9.44015e-05 | 1.56959e-05 | 2(Loss) |
| jsonifier (two-stage) | 460.512 | 0.0336449 | 1107.95ms | 1811 | 320 | 509.502 | 3750.4 | 11.0994 | 34.4942 | 6.21204 | 0.000555632 | 6.55715e-05 | 0 | 3(Loss) |
| simdjson (ondemand) | 275.832 | 0.0265295 | 1356.36ms | 1811 | 2560 | 7063.92 | 6261.43 | 18.4449 | 68.5947 | 9.32413 | 0.0011557 | 7.18267e-05 | 2.86875e-05 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 330.125 | 0.0350507 | 1259.12ms | 1811 | 1280 | 4304.12 | 5231.67 | 15.4273 | 64.1496 | 11.545 | 0.017826 | 0.000116907 | 3.1923e-05 | 1(Win) |
| glaze | 298.62 | 0.0233589 | 1310.23ms | 1798 | 4890 | 8797.41 | 5742.1 | 17.0462 | 70.6352 | 12.1196 | 0.0203189 | 0.000233161 | 0.000117376 | 2(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 837.819 | 0.0356584 | 948.45ms | 1811 | 4890 | 2642.22 | 2061.43 | 6.15235 | 20.709 | 1.69354 | 0.000580185 | 8.76263e-05 | 1.35505e-05 | 1(Win) |
| glaze | 682.337 | 0.0471714 | 995.23ms | 1798 | 4890 | 6871.45 | 2512.99 | 7.53362 | 27.3231 | 2.17242 | 0.000863718 | 0.000130684 | 6.01668e-05 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2958.1 | 0.038507 | 854.826ms | 3862 | 4890 | 1124.05 | 1245.08 | 1.76325 | 8.558 | 1.145 | 0.00029314 | 5.00922e-05 | 1.51442e-05 | 1(Win) |
| glaze | 1775.09 | 0.0848769 | 935.247ms | 3862 | 320 | 992.461 | 2074.88 | 2.94228 | 14.0277 | 1.72683 | 0.000258933 | 4.53133e-05 | 1.29467e-05 | 2(Loss) |
| jsonifier (two-stage) | 1044.23 | 0.0221894 | 1082.1ms | 3862 | 4890 | 2995.23 | 3527.08 | 4.89735 | 15.4868 | 2.23071 | 0.00026534 | 3.606e-05 | 4.76564e-06 | 3(Loss) |
| simdjson (ondemand) | 557.123 | 0.0435626 | 1394.44ms | 3862 | 80 | 663.499 | 6610.91 | 9.13032 | 27.731 | 3.61108 | 0.0133868 | 8.739e-05 | 6.47333e-05 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3283.55 | 0.0851158 | 839.617ms | 3862 | 2560 | 2333.44 | 1121.68 | 1.59268 | 8.03599 | 1.02952 | 0.000262777 | 2.61968e-05 | 2.62979e-06 | 1(Win) |
| glaze | 1821.95 | 0.0338665 | 926.132ms | 3862 | 4890 | 2291.93 | 2021.51 | 2.82968 | 13.5342 | 1.62118 | 0.000287845 | 2.92293e-05 | 7.67798e-06 | 2(Loss) |
| jsonifier (two-stage) | 1064.67 | 0.0684909 | 1074.32ms | 3862 | 640 | 3592.85 | 3459.37 | 4.80473 | 14.9834 | 2.11704 | 0.000560752 | 3.60079e-05 | 6.06875e-06 | 3(Loss) |
| simdjson (ondemand) | 561.385 | 0.0423393 | 1385.12ms | 3862 | 320 | 2469.11 | 6560.73 | 9.05832 | 27.2266 | 3.4956 | 0.0169067 | 3.3985e-05 | 0 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 925.274 | 0.0223418 | 1131.79ms | 3862 | 4890 | 3867.48 | 3980.54 | 5.51935 | 26.0492 | 5.44925 | 0.00598999 | 8.98588e-05 | 4.38439e-05 | 1(Win) |
| glaze | 875.683 | 0.0673106 | 1149.67ms | 3862 | 640 | 5129.53 | 4205.96 | 5.82789 | 28.7885 | 5.61678 | 0.00839308 | 4.16721e-05 | 5.66416e-06 | 2(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4920.49 | 0.079011 | 825.975ms | 3862 | 2560 | 895.414 | 748.521 | 1.08371 | 5.69161 | 0.787416 | 0.000273802 | 2.62979e-05 | 5.15843e-06 | 1(Win) |
| glaze | 2410 | 0.0299851 | 912.301ms | 3862 | 4890 | 1026.86 | 1528.25 | 2.15581 | 8.50388 | 0.951321 | 0.00402877 | 4.71269e-05 | 1.61502e-05 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1775.06 | 0.0268458 | 1254.58ms | 9578 | 4890 | 9332.16 | 5145.9 | 2.865 | 14.3205 | 2.74776 | 0.00190779 | 2.98272e-05 | 1.04833e-05 | 1(Win) |
| glaze | 1424.57 | 0.033445 | 1380.11ms | 9578 | 2560 | 11773 | 6411.97 | 3.56745 | 17.6227 | 3.50501 | 0.00203881 | 2.9405e-05 | 7.42261e-06 | 2(Loss) |
| jsonifier (two-stage) | 1149.89 | 0.0688848 | 1544.62ms | 9578 | 40 | 1197.68 | 7943.6 | 4.42096 | 18.848 | 3.3412 | 0.00152694 | 2.08812e-05 | 5.2203e-06 | 3(Loss) |
| simdjson (ondemand) | 1120.4 | 0.171753 | 1544.05ms | 9578 | 640 | 125485 | 8152.69 | 4.43086 | 17.6735 | 3.00251 | 0.0044521 | 5.41606e-05 | 2.39807e-05 | 4(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2731.85 | 0.0789823 | 1203.59ms | 9578 | 2560 | 17853.9 | 3343.62 | 1.87256 | 10.1448 | 1.82766 | 0.00119043 | 4.07428e-05 | 1.87604e-05 | 1(Win) |
| glaze | 2130.85 | 0.0504899 | 1311.74ms | 9578 | 320 | 1499.01 | 4286.69 | 2.39599 | 13.1864 | 2.50386 | 0.000375861 | 1.72922e-05 | 1.63134e-06 | 2(Loss) |
| simdjson (ondemand) | 1501.49 | 0.0740735 | 1521.09ms | 9578 | 40 | 812.256 | 6083.5 | 3.39067 | 13.5304 | 2.09668 | 0.0036255 | 2.08812e-05 | 5.2203e-06 | 3(Loss) |
| jsonifier (two-stage) | 1496.56 | 0.0707127 | 1484.81ms | 9578 | 320 | 5960.79 | 6103.51 | 3.39081 | 14.7226 | 2.44373 | 0.000701477 | 1.8271e-05 | 1.30507e-06 | 4(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4409.64 | 0.0818634 | 944.104ms | 9578 | 2560 | 7361.45 | 2071.44 | 1.16857 | 5.25287 | 1.08801 | 0.00141515 | 3.9193e-05 | 1.56201e-05 | 1(Win) |
| glaze | 1916.8 | 0.146314 | 1213.91ms | 9578 | 320 | 15556.8 | 4765.38 | 2.66075 | 12.6824 | 2.60305 | 0.0010023 | 3.58895e-05 | 9.78806e-06 | 2(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11195.5 | 0.111183 | 840.673ms | 9578 | 4890 | 4023.95 | 815.891 | 0.468683 | 2.07538 | 0.299123 | 0.000979473 | 2.54716e-05 | 7.66498e-06 | 1(Win) |
| glaze | 5576.01 | 0.0672769 | 922.987ms | 9578 | 640 | 777.345 | 1638.14 | 0.927553 | 4.37941 | 0.710482 | 0.000196903 | 1.22351e-05 | 1.46821e-06 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3200.14 | 0.0654258 | 843.232ms | 3873 | 1280 | 729.905 | 1154.19 | 1.63324 | 8.67157 | 1.11593 | 0.000516194 | 3.89314e-05 | 8.06868e-06 | 1(Win) |
| glaze | 1917.64 | 0.0553619 | 924.029ms | 3873 | 4890 | 5560.23 | 1926.11 | 2.67973 | 13.0669 | 1.62097 | 0.000262211 | 0.000124611 | 7.15456e-05 | 2(Loss) |
| jsonifier (two-stage) | 1032.84 | 0.0387124 | 1091.86ms | 3873 | 2560 | 4906.51 | 3576.15 | 4.94547 | 15.8033 | 2.14872 | 0.000657799 | 5.00258e-05 | 2.08777e-05 | 3(Loss) |
| simdjson (ondemand) | 575.851 | 0.0172105 | 1373.54ms | 3873 | 4890 | 5958.96 | 6414.13 | 8.81853 | 27.2301 | 3.65841 | 0.0139523 | 7.50305e-05 | 3.59048e-05 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3600.4 | 0.0478952 | 825.789ms | 3873 | 640 | 154.51 | 1025.88 | 1.46814 | 8.24167 | 1.01936 | 0.000489365 | 3.42919e-05 | 7.26181e-06 | 1(Win) |
| glaze | 2019.34 | 0.0450491 | 906.115ms | 3873 | 30 | 20.369 | 1829.1 | 2.57766 | 12.63 | 1.52672 | 0.000516396 | 1.72132e-05 | 0 | 2(Loss) |
| jsonifier (two-stage) | 1055.86 | 0.0519991 | 1079.47ms | 3873 | 40 | 132.353 | 3498.18 | 4.84338 | 15.3594 | 2.05216 | 0.00139427 | 6.45494e-06 | 0 | 3(Loss) |
| simdjson (ondemand) | 581.691 | 0.0435214 | 1366.05ms | 3873 | 640 | 4887.61 | 6349.73 | 8.74157 | 26.802 | 3.55952 | 0.0160163 | 1.8558e-05 | 4.43777e-06 | 4(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 894.339 | 0.0776646 | 1146.59ms | 3873 | 160 | 1646.1 | 4129.96 | 5.71002 | 29.2148 | 5.73096 | 0.00560773 | 5.97082e-05 | 8.06868e-06 | 1(Win) |
| jsonifier | 889.881 | 0.0257595 | 1148.04ms | 3873 | 4890 | 5590.04 | 4150.65 | 5.73345 | 25.8996 | 5.38859 | 0.00731275 | 6.27806e-05 | 1.68436e-05 | 2(Loss) |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5152.4 | 0.0653306 | 825.111ms | 3873 | 4890 | 1072.55 | 716.866 | 1.03964 | 5.49522 | 0.764782 | 0.000434607 | 6.01405e-05 | 2.6559e-05 | 1(Win) |
| glaze | 2617.19 | 0.0352981 | 898.766ms | 3873 | 4890 | 1213.49 | 1411.28 | 1.98673 | 8.46424 | 0.946037 | 0.00388363 | 4.91579e-05 | 9.60982e-06 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 969.054 | 0.262202 | 6423.01ms | 2090234 | 80 | 2.32732e+09 | 2.05706e+06 | 5.16807 | 25.2036 | 5.22961 | 0.0159103 | 0.0679182 | 5.31639e-05 | 1(Win) |
| jsonifier (two-stage) | 934.179 | 0.68576 | 6651.47ms | 2090234 | 40 | 8.56513e+09 | 2.13386e+06 | 5.36968 | 27.6767 | 5.53792 | 0.0199464 | 0.107383 | 6.29834e-05 | 2(Loss) |
| glaze | 803.997 | 0.122855 | 7705.48ms | 2090234 | 40 | 3.71128e+08 | 2.47937e+06 | 6.26804 | 30.0296 | 5.97931 | 0.0183433 | 0.0670914 | 0.00035331 | 3(Loss) |
| simdjson (ondemand) | 651.353 | 0.10814 | 9531.88ms | 2090234 | 40 | 4.38115e+08 | 3.0604e+06 | 7.75492 | 31.2727 | 5.64418 | 0.0255919 | 0.113366 | 0.000116961 | 4(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1189.52 | 0.187574 | 6389.75ms | 2090234 | 160 | 1.58092e+09 | 1.6758e+06 | 4.22492 | 19.8848 | 3.93776 | 0.0153029 | 0.043314 | 1.80243e-05 | 1(Win) |
| jsonifier (two-stage) | 1142.91 | 0.280268 | 6614.46ms | 2090234 | 160 | 3.82324e+09 | 1.74414e+06 | 4.41948 | 22.4081 | 4.26373 | 0.0195205 | 0.0818676 | 0.000155757 | 2(Loss) |
| glaze | 953.468 | 0.0523838 | 7676.65ms | 2090234 | 160 | 1.91907e+08 | 2.09069e+06 | 5.28082 | 24.6753 | 4.68504 | 0.0175021 | 0.0417578 | 6.13e-05 | 3(Loss) |
| simdjson (ondemand) | 751.146 | 0.324928 | 9440.17ms | 2090234 | 160 | 1.18969e+10 | 2.65381e+06 | 6.71938 | 25.9501 | 4.3588 | 0.0214276 | 0.0783951 | 0.000384712 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1540.28 | 0.0703482 | 8216.22ms | 2090234 | 320 | 2.65246e+08 | 1.29419e+06 | 3.24405 | 7.82858 | 0.405714 | 0.000241885 | 0.0502609 | 2.44515e-05 | 1(Win) |
| glaze | 949.925 | 0.577872 | 6513.84ms | 2090234 | 40 | 5.88215e+09 | 2.09848e+06 | 5.27519 | 9.34203 | 0.534063 | 0.000239076 | 0.0692359 | 5.37858e-05 | 2(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1543.1 | 0.142706 | 8229.15ms | 2090234 | 80 | 2.71878e+08 | 1.29181e+06 | 3.24116 | 7.82831 | 0.405653 | 0.000239154 | 0.0502317 | 1.83831e-05 | 1(Win) |
| glaze | 996.245 | 0.0127084 | 6242.78ms | 2090234 | 40 | 2.58642e+06 | 2.00092e+06 | 5.07066 | 9.33804 | 0.533131 | 0.000231948 | 0.0435013 | 3.25681e-05 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2648.29 | 0.564938 | 7505.55ms | 6661897 | 40 | 7.3473e+09 | 2.39901e+06 | 1.87548 | 9.57185 | 1.77969 | 0.00589475 | 0.0565712 | 0.000500368 | 1(Win) |
| jsonifier | 2531.32 | 0.566496 | 7857.97ms | 6661897 | 30 | 6.06482e+09 | 2.50987e+06 | 1.98728 | 9.99592 | 2.13063 | 0.0050621 | 0.0341255 | 0.000145764 | 2(Loss) |
| glaze | 1983.94 | 0.128336 | 9961.62ms | 6661897 | 30 | 5.06706e+08 | 3.20236e+06 | 2.54556 | 12.3603 | 2.44198 | 0.0065298 | 0.0357876 | 0.00371798 | 3(Loss) |
| simdjson (ondemand) | 1955.46 | 0.125623 | 10180.3ms | 6661897 | 80 | 1.33269e+09 | 3.24899e+06 | 2.58587 | 10.6585 | 1.81055 | 0.00721769 | 0.058282 | 0.000214451 | 4(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3116.7 | 0.739275 | 7496.53ms | 6661897 | 80 | 1.81681e+10 | 2.03846e+06 | 1.60359 | 7.92376 | 1.38087 | 0.00570652 | 0.0483657 | 0.000344065 | 1(Win) |
| jsonifier | 2985.04 | 0.0891903 | 7860.92ms | 6661897 | 160 | 5.76567e+08 | 2.12837e+06 | 1.67955 | 8.34808 | 1.73181 | 0.00486917 | 0.0259352 | 0.000436715 | 2(Loss) |
| glaze | 2282.35 | 0.0775227 | 9874.89ms | 6661897 | 80 | 3.72544e+08 | 2.78365e+06 | 2.20584 | 10.7038 | 2.04277 | 0.00617307 | 0.0269164 | 0.000193909 | 3(Loss) |
| simdjson (ondemand) | 2236.86 | 0.372611 | 10051ms | 6661897 | 40 | 4.48011e+09 | 2.84027e+06 | 2.26093 | 8.9902 | 1.40792 | 0.00600114 | 0.0469216 | 0.0004591 | 4(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4443.08 | 0.32403 | 9023.69ms | 6661897 | 160 | 3.43492e+09 | 1.42993e+06 | 1.13564 | 2.57027 | 0.127289 | 7.47385e-05 | 0.0278743 | 0.000109916 | 1(Win) |
| glaze | 3228.85 | 0.619119 | 6108.75ms | 6661897 | 80 | 1.18724e+10 | 1.96766e+06 | 1.55511 | 4.23028 | 0.469308 | 7.55322e-05 | 0.0633825 | 0.00115634 | 2(Loss) |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4487.57 | 0.103363 | 8985.84ms | 6661897 | 80 | 1.71314e+08 | 1.41575e+06 | 1.1238 | 2.57022 | 0.127277 | 7.44326e-05 | 0.0278419 | 2.27938e-05 | 1(Win) |
| glaze | 3857.53 | 0.210899 | 5132.63ms | 6661897 | 40 | 4.82602e+08 | 1.64698e+06 | 1.30442 | 4.22889 | 0.468987 | 7.42656e-05 | 0.0247889 | 2.65803e-05 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2463.69 | 0.0346067 | 5149.83ms | 500299 | 1280 | 5.74936e+06 | 193662 | 2.04722 | 9.03721 | 1.72711 | 0.0108959 | 0.00539591 | 2.22398e-05 | 1(Win) |
| glaze STATISTICAL TIE | 1821.92 | 0.126314 | 6966.43ms | 500299 | 40 | 4.37689e+06 | 261879 | 2.77378 | 12.4267 | 2.34786 | 0.0135291 | 0.00390836 | 2.29363e-05 | 2(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1820.58 | 0.0953341 | 6957.57ms | 500299 | 80 | 4.99372e+06 | 262071 | 2.77489 | 12.44 | 2.15051 | 0.0143017 | 0.0365054 | 4.81712e-05 | 2(Tie) |
| simdjson (ondemand) | 1226.86 | 0.3416 | 5089.84ms | 500299 | 80 | 1.41187e+08 | 388897 | 4.11802 | 14.7367 | 2.4084 | 0.0165961 | 0.0320784 | 2.62843e-05 | 4(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3065.07 | 0.23093 | 10029.7ms | 500299 | 30 | 3.87667e+06 | 155664 | 1.6486 | 7.87997 | 1.44836 | 0.00807824 | 0.00332188 | 2.68506e-05 | 1(Win) |
| jsonifier (two-stage) | 2169.42 | 0.161294 | 6731.71ms | 500299 | 30 | 3.77513e+06 | 219931 | 2.32936 | 11.2809 | 1.87161 | 0.0102418 | 0.0251294 | 3.29137e-05 | 2(Loss) |
| glaze | 2138.73 | 0.17912 | 6774.31ms | 500299 | 30 | 4.79024e+06 | 223087 | 2.3536 | 11.2854 | 2.07375 | 0.00971692 | 0.00137051 | 1.05937e-05 | 3(Loss) |
| simdjson (ondemand) | 1409.19 | 0.297801 | 9690.74ms | 500299 | 320 | 3.25329e+08 | 338579 | 3.58623 | 13.5845 | 2.12672 | 0.00928878 | 0.0138447 | 1.03875e-05 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 10326.4 | 0.0878543 | 5440.15ms | 500299 | 80 | 131819 | 46204.1 | 0.489677 | 2.16048 | 0.353079 | 0.00248109 | 0.00415764 | 1.15681e-05 | 1(Win) |
| glaze | 5658.23 | 0.36099 | 9261.83ms | 500299 | 4890 | 4.53104e+08 | 84323.6 | 0.887119 | 3.6437 | 0.515398 | 0.00131233 | 0.0205801 | 1.6895e-05 | 2(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 10276.7 | 0.101893 | 5430.72ms | 500299 | 160 | 358066 | 46427.7 | 0.487475 | 2.15938 | 0.352831 | 0.00247097 | 0.00411075 | 2.59845e-06 | 1(Win) |
| glaze | 6542.73 | 0.196949 | 8082.33ms | 500299 | 4890 | 1.0087e+08 | 72924.1 | 0.769019 | 3.63048 | 0.512286 | 0.00135945 | 0.00314139 | 4.50855e-06 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4327.46 | 0.176507 | 8375.8ms | 1439562 | 80 | 2.50848e+07 | 317247 | 1.16434 | 5.27196 | 0.790862 | 0.00477871 | 0.0566793 | 5.3749e-05 | 1(Win) |
| jsonifier | 3887.54 | 0.033363 | 9238.44ms | 1439562 | 1280 | 1.77685e+07 | 353147 | 1.29431 | 5.71824 | 1.19383 | 0.00384049 | 0.0219767 | 7.64007e-05 | 2(Loss) |
| simdjson (ondemand) | 3125.45 | 0.119855 | 5738.44ms | 1439562 | 640 | 1.77389e+08 | 439256 | 1.62249 | 5.98254 | 0.877644 | 0.00542257 | 0.0519728 | 6.81598e-05 | 3(Loss) |
| glaze | 2985.21 | 0.0704459 | 6041.77ms | 1439562 | 40 | 4.19839e+06 | 459891 | 1.69207 | 7.46376 | 1.44327 | 0.00642999 | 0.017943 | 1.80437e-05 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 5009.89 | 0.222883 | 8247.46ms | 1439562 | 30 | 1.11912e+07 | 274032 | 1.00777 | 4.86985 | 0.694074 | 0.00362541 | 0.0487991 | 7.87508e-05 | 1(Win) |
| jsonifier | 4415.67 | 0.108243 | 9039.07ms | 1439562 | 30 | 3.39772e+06 | 310910 | 1.14404 | 5.31618 | 1.09697 | 0.00274854 | 0.0159845 | 1.66717e-05 | 2(Loss) |
| simdjson (ondemand) | 3579.95 | 0.531289 | 5486.5ms | 1439562 | 30 | 1.24535e+08 | 383490 | 1.41824 | 5.58148 | 0.779499 | 0.00305482 | 0.0407438 | 1.03041e-05 | 3(Loss) |
| glaze | 3260.28 | 0.522846 | 5923.85ms | 1439562 | 320 | 1.55113e+09 | 421091 | 1.54754 | 7.06414 | 1.34738 | 0.00491592 | 0.013091 | 5.66362e-05 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 17943.9 | 0.0932064 | 8602.91ms | 1439562 | 30 | 152561 | 76509.4 | 0.28163 | 0.872076 | 0.124255 | 0.000551997 | 0.0172179 | 1.02809e-05 | 1(Win) |
| glaze | 5726.67 | 0.143601 | 6428.86ms | 1439584 | 80 | 9.48151e+06 | 239737 | 0.875718 | 2.78631 | 0.504919 | 0.000938552 | 0.0597063 | 3.54269e-06 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18023 | 0.0517385 | 8555.31ms | 1439562 | 80 | 124259 | 76173.6 | 0.280522 | 0.871687 | 0.124168 | 0.00050399 | 0.0171319 | 3.73377e-06 | 1(Win) |
| glaze | 7712.22 | 0.455402 | 9654.69ms | 1439584 | 30 | 1.97164e+07 | 178015 | 0.655286 | 2.78084 | 0.503639 | 0.000936822 | 0.0164608 | 1.82923e-05 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2232.57 | 0.0199728 | 3156.31ms | 56369 | 2560 | 59209.3 | 24078.8 | 2.26726 | 9.40601 | 1.85241 | 0.00371678 | 1.28755e-05 | 5.64084e-06 | 1(Win) |
| glaze | 2007.41 | 0.0313381 | 3424.2ms | 56369 | 1280 | 90149.1 | 26779.6 | 2.5205 | 11.6842 | 2.31705 | 0.00423643 | 1.34438e-05 | 5.57155e-06 | 2(Loss) |
| jsonifier (two-stage) | 1779.91 | 0.0342861 | 3769.47ms | 56369 | 1280 | 137256 | 30202.5 | 2.84263 | 12.2335 | 2.18322 | 0.00705367 | 7.00185e-05 | 4.15371e-05 | 3(Loss) |
| simdjson (ondemand) | 1471.07 | 0.0392982 | 4399.68ms | 56369 | 640 | 131990 | 36543.2 | 3.43765 | 14.2779 | 2.35039 | 0.00704238 | 4.19668e-05 | 2.13992e-05 | 4(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3198.5 | 0.0686488 | 2789.47ms | 56369 | 320 | 42599.5 | 16807.2 | 1.58438 | 7.23075 | 1.36601 | 0.00285102 | 3.99156e-06 | 9.42451e-07 | 1(Win) |
| glaze | 3005.12 | 0.0424139 | 2895.43ms | 56369 | 2560 | 147371 | 17888.7 | 1.68491 | 9.15443 | 1.75132 | 0.0022623 | 6.65259e-06 | 2.16902e-06 | 2(Loss) |
| jsonifier (two-stage) | 2474.86 | 0.0394345 | 3273.99ms | 56369 | 640 | 46958.3 | 21721.5 | 2.04606 | 10.0517 | 1.69562 | 0.00272704 | 2.04013e-05 | 1.10599e-05 | 3(Loss) |
| simdjson (ondemand) | 1915.19 | 0.0288909 | 3949.01ms | 56369 | 1280 | 84175.8 | 28069.1 | 2.64108 | 11.8722 | 1.81922 | 0.00669201 | 1.19054e-05 | 5.19734e-06 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13809.2 | 0.0402938 | 1132.65ms | 56369 | 2560 | 6298.88 | 3892.9 | 0.369026 | 1.48637 | 0.250439 | 0.000179842 | 6.34075e-06 | 2.59867e-06 | 1(Win) |
| glaze | 6039.13 | 0.0775681 | 1631.46ms | 56369 | 4890 | 233135 | 8901.56 | 0.839454 | 3.10759 | 0.487413 | 0.000149631 | 2.77749e-05 | 1.72432e-05 | 2(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14047.3 | 0.0242218 | 1119.28ms | 56369 | 4890 | 4201.63 | 3826.9 | 0.363631 | 1.47652 | 0.248239 | 0.000183047 | 5.91342e-06 | 1.92639e-06 | 1(Win) |
| glaze | 6216.89 | 0.111988 | 1608.12ms | 56369 | 4890 | 458547 | 8647.04 | 0.81604 | 3.02993 | 0.469833 | 0.000109873 | 3.05466e-05 | 2.01165e-05 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2886.27 | 0.0351818 | 3869.41ms | 94370 | 1280 | 154043 | 31181.5 | 1.7549 | 7.92328 | 1.32344 | 0.00244013 | 3.55317e-05 | 2.23191e-05 | 1(Win) |
| glaze | 2512.32 | 0.0184286 | 4319.96ms | 94370 | 4890 | 213114 | 35822.7 | 2.00935 | 9.45335 | 1.92583 | 0.00385627 | 1.10278e-05 | 5.94406e-06 | 2(Loss) |
| simdjson (ondemand) | 2355.6 | 0.0307878 | 4566.71ms | 94370 | 1280 | 177106 | 38206.1 | 2.14553 | 9.06139 | 1.42859 | 0.00401029 | 1.58535e-05 | 6.70565e-06 | 3(Loss) |
| jsonifier | 2137.31 | 0.124072 | 5005.52ms | 94370 | 40 | 109178 | 42108.1 | 2.36703 | 8.47715 | 1.82671 | 0.00529882 | 1.05966e-05 | 8.21236e-06 | 4(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3731.78 | 0.030241 | 3515.54ms | 94370 | 1280 | 68082.8 | 24116.7 | 1.35689 | 6.62797 | 1.03438 | 0.00183472 | 5.67083e-06 | 2.64915e-06 | 1(Win) |
| glaze | 3326 | 0.0638133 | 3816ms | 94370 | 640 | 190821 | 27059 | 1.51931 | 7.97285 | 1.59556 | 0.0026813 | 3.79159e-06 | 8.94087e-07 | 2(Loss) |
| simdjson (ondemand) | 2987.32 | 0.0520697 | 4145.1ms | 94370 | 640 | 157490 | 30126.7 | 1.68334 | 7.63055 | 1.11293 | 0.00395067 | 9.83496e-06 | 5.57977e-06 | 3(Loss) |
| jsonifier | 2599.22 | 0.0197636 | 4573.34ms | 94370 | 2560 | 119882 | 34625.1 | 1.93995 | 7.18542 | 1.53847 | 0.00395955 | 5.96886e-06 | 2.42976e-06 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 17587.3 | 0.0258581 | 1251.93ms | 94370 | 2560 | 4482.29 | 5117.21 | 0.289909 | 0.980958 | 0.156639 | 0.000109389 | 7.46728e-06 | 3.63844e-06 | 1(Win) |
| glaze | 5089.06 | 0.0482631 | 2518.24ms | 94370 | 4890 | 356231 | 17684.7 | 0.989037 | 3.42164 | 0.637343 | 0.00132662 | 1.50411e-05 | 8.36459e-06 | 2(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 17762.6 | 0.0287844 | 1248.5ms | 94370 | 2560 | 5445.18 | 5066.74 | 0.286918 | 0.975331 | 0.155378 | 0.000101951 | 2.84369e-06 | 1.05966e-06 | 1(Win) |
| glaze | 5865.74 | 0.0553655 | 2278.54ms | 94370 | 1280 | 92365.8 | 15343 | 0.859343 | 3.36923 | 0.625209 | 0.00132818 | 1.08284e-05 | 6.2255e-06 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2643.97 | 0.0814564 | 1161.57ms | 11812 | 640 | 7708.41 | 4260.57 | 1.9294 | 9.40946 | 1.64312 | 0.00316587 | 1.15084e-05 | 1.32281e-07 | 1(Win) |
| jsonifier (two-stage) | 1946.48 | 0.0355603 | 1316.04ms | 11812 | 320 | 1355.28 | 5787.27 | 2.61714 | 12.7655 | 2.15336 | 0.00440283 | 2.03712e-05 | 3.96842e-06 | 2(Loss) |
| glaze | 1792.78 | 0.0542952 | 1367.8ms | 11812 | 1280 | 14898 | 6283.43 | 2.82484 | 13.6791 | 2.68875 | 0.00228217 | 2.79112e-05 | 1.04502e-05 | 3(Loss) |
| simdjson (ondemand) | 1381.13 | 0.0478061 | 1558.18ms | 11812 | 1280 | 19460.6 | 8156.25 | 3.67644 | 16.5638 | 2.87572 | 0.00268768 | 5.67484e-05 | 2.62577e-05 | 4(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3092.74 | 0.0886846 | 1147.42ms | 11812 | 1280 | 13355.7 | 3642.34 | 1.65113 | 8.43414 | 1.41526 | 0.00227119 | 4.70258e-05 | 2.38105e-05 | 1(Win) |
| jsonifier (two-stage) | 2182.55 | 0.076166 | 1301.53ms | 11812 | 320 | 4945.3 | 5161.31 | 2.33496 | 11.7899 | 1.9255 | 0.00345623 | 1.21698e-05 | 3.17474e-06 | 2(Loss) |
| glaze | 2060.6 | 0.0394284 | 1332.06ms | 11812 | 320 | 1486.72 | 5466.76 | 2.47303 | 12.4977 | 2.42567 | 0.0013236 | 1.56091e-05 | 5.02667e-06 | 3(Loss) |
| simdjson (ondemand) | 1502.58 | 0.0564047 | 1543.45ms | 11812 | 640 | 11444.1 | 7496.97 | 3.38385 | 15.7101 | 2.68727 | 0.00160536 | 2.50011e-05 | 8.86281e-06 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11457.5 | 0.0468676 | 831.206ms | 11812 | 4890 | 1038.29 | 983.181 | 0.460104 | 2.08026 | 0.339909 | 9.00959e-05 | 1.55123e-05 | 4.24164e-06 | 1(Win) |
| glaze | 4004.86 | 0.14364 | 1022.58ms | 11812 | 4890 | 79823.9 | 2812.79 | 1.27804 | 5.23596 | 0.80808 | 0.000399112 | 4.03389e-05 | 1.93211e-05 | 2(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11987.8 | 0.0997897 | 824.187ms | 11812 | 2560 | 2251.03 | 939.692 | 0.439989 | 2.03505 | 0.329495 | 8.48581e-05 | 2.05366e-05 | 8.06912e-06 | 1(Win) |
| glaze | 4575.66 | 0.223282 | 983.72ms | 11812 | 1280 | 38677.5 | 2461.9 | 1.12342 | 4.9647 | 0.74763 | 0.000406102 | 2.6853e-05 | 1.14423e-05 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4347.5 | 0.0406422 | 1434.63ms | 31235 | 2560 | 19851.8 | 6851.76 | 1.1694 | 5.76072 | 0.861054 | 0.0017668 | 1.40567e-05 | 5.60269e-06 | 1(Win) |
| jsonifier | 3754.45 | 0.0402562 | 1533.67ms | 31235 | 2560 | 26115.4 | 7934.05 | 1.35399 | 6.14016 | 1.2332 | 0.0033624 | 2.5087e-05 | 1.42193e-05 | 2(Loss) |
| simdjson (ondemand) | 3246.46 | 0.0917928 | 1657.58ms | 31235 | 40 | 2837.54 | 9175.55 | 1.56482 | 7.05411 | 1.12329 | 0.00119017 | 8.00384e-06 | 0 | 3(Loss) |
| glaze | 2752.51 | 0.0458709 | 1821.92ms | 31235 | 160 | 3942.94 | 10822.1 | 1.84418 | 8.26678 | 1.63915 | 0.00530475 | 2.02097e-05 | 1.10053e-05 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4686.32 | 0.0362724 | 1429.48ms | 31235 | 4890 | 25994.5 | 6356.37 | 1.0852 | 5.43061 | 0.783608 | 0.00177292 | 7.47025e-06 | 1.68261e-06 | 1(Win) |
| jsonifier | 4008.84 | 0.100885 | 1537.68ms | 31235 | 640 | 35964.6 | 7430.58 | 1.2667 | 5.81002 | 1.15579 | 0.00334681 | 5.40259e-06 | 5.50264e-07 | 2(Loss) |
| simdjson (ondemand) | 3483.21 | 0.0294903 | 1648.44ms | 31235 | 2560 | 16282.5 | 8551.89 | 1.45815 | 6.72505 | 1.05023 | 0.000986586 | 1.08052e-05 | 3.93939e-06 | 3(Loss) |
| glaze | 2906.24 | 0.0729385 | 1819.54ms | 31235 | 320 | 17884.8 | 10249.7 | 1.74585 | 7.85782 | 1.54804 | 0.00547933 | 3.70178e-06 | 2.00096e-07 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18231.9 | 0.0473958 | 900.416ms | 31235 | 2560 | 1535.11 | 1633.84 | 0.284291 | 0.914455 | 0.129022 | 3.82058e-05 | 2.9264e-06 | 7.25348e-07 | 1(Win) |
| glaze | 5135.61 | 0.0584177 | 1315.04ms | 31235 | 2560 | 29391.9 | 5800.29 | 0.990667 | 3.63512 | 0.652345 | 0.00222784 | 1.79711e-05 | 8.52909e-06 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19429 | 0.0991636 | 884.126ms | 31235 | 640 | 1479.34 | 1533.18 | 0.267353 | 0.894509 | 0.124316 | 3.36161e-05 | 7.55363e-06 | 5.10245e-06 | 1(Win) |
| glaze | 5641.66 | 0.0468631 | 1263.09ms | 31235 | 4890 | 29939.1 | 5280.01 | 0.903003 | 3.51404 | 0.625004 | 0.002182 | 1.55625e-05 | 7.73214e-06 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2656.32 | 0.105425 | 4636.85ms | 108313 | 40 | 67227.6 | 38886.7 | 1.90399 | 8.35156 | 1.68483 | 0.00299295 | 1.50028e-05 | 1.22331e-05 | 1(Win) |
| glaze | 2424.74 | 0.0736274 | 5054.24ms | 108313 | 640 | 629636 | 42600.5 | 2.08465 | 10.059 | 1.80969 | 0.00252044 | 8.16499e-06 | 4.86149e-06 | 2(Loss) |
| jsonifier (two-stage) | 1982.9 | 0.0512558 | 5965.44ms | 108313 | 320 | 228137 | 52093.1 | 2.5471 | 11.5501 | 2.018 | 0.00296424 | 4.58163e-05 | 3.36698e-05 | 3(Loss) |
| simdjson (ondemand) | 1734.19 | 0.0449085 | 6726.07ms | 108313 | 160 | 114484 | 59563.9 | 2.91503 | 14.2359 | 2.03132 | 0.00285821 | 2.89093e-05 | 1.90997e-05 | 4(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3159.76 | 0.026136 | 4199.8ms | 108313 | 2560 | 186885 | 32690.9 | 1.59696 | 7.54059 | 1.49995 | 0.00239122 | 6.67193e-06 | 3.28187e-06 | 1(Win) |
| glaze | 2743.51 | 0.0312887 | 4698.49ms | 108313 | 4890 | 678629 | 37650.9 | 1.84299 | 9.32375 | 1.64264 | 0.00225673 | 9.22495e-06 | 4.69177e-06 | 2(Loss) |
| jsonifier (two-stage) | 2260.99 | 0.055974 | 5531.18ms | 108313 | 320 | 209261 | 45685.9 | 2.22717 | 10.744 | 1.8345 | 0.00248894 | 6.89553e-06 | 3.46219e-06 | 3(Loss) |
| simdjson (ondemand) | 1916.43 | 0.0382235 | 6321.86ms | 108313 | 4890 | 2.0756e+06 | 53899.8 | 2.63876 | 13.4894 | 1.86516 | 0.00250421 | 3.49325e-05 | 2.31587e-05 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18290.6 | 0.0561762 | 1307.19ms | 108313 | 640 | 6441.51 | 5647.44 | 0.278349 | 1.23804 | 0.320451 | 0.000167397 | 1.74552e-06 | 4.90477e-07 | 1(Win) |
| glaze | 5667.67 | 0.0737534 | 2563.33ms | 108313 | 4890 | 883536 | 18225.3 | 0.892791 | 2.7371 | 0.384589 | 0.000285096 | 6.52506e-06 | 3.03785e-06 | 2(Loss) |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18411.8 | 0.0242582 | 1303.36ms | 108313 | 4890 | 9057.21 | 5610.29 | 0.276351 | 1.23322 | 0.319371 | 0.000166255 | 3.11526e-06 | 1.00255e-06 | 1(Win) |
| glaze | 6474.44 | 0.0845564 | 2344.21ms | 108313 | 4890 | 889936 | 15954.3 | 0.784414 | 2.69244 | 0.374221 | 0.000295383 | 1.11338e-05 | 6.69498e-06 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3377.36 | 0.0689202 | 6738.59ms | 213963 | 30 | 52015.9 | 60417.2 | 1.49691 | 6.68811 | 1.07625 | 0.00174594 | 6.07582e-06 | 3.89475e-06 | 1(Win) |
| simdjson (ondemand) | 3165.7 | 0.0196078 | 7179.88ms | 213963 | 640 | 102229 | 64456.9 | 1.59702 | 7.81993 | 1.05341 | 0.00161755 | 6.50667e-06 | 2.83343e-06 | 2(Loss) |
| glaze | 3028.89 | 0.0680262 | 7492.46ms | 213963 | 160 | 336033 | 67368.2 | 1.66865 | 7.93422 | 1.46019 | 0.00289282 | 2.40988e-05 | 1.88993e-05 | 3(Loss) |
| jsonifier | 2821.3 | 0.0175041 | 7991.98ms | 213963 | 1280 | 205150 | 72325.3 | 1.79081 | 6.84496 | 1.51072 | 0.00197212 | 3.10363e-06 | 1.01872e-06 | 4(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3809.07 | 0.00933844 | 6319.23ms | 213963 | 4890 | 122376 | 53569.7 | 1.32771 | 6.27896 | 0.983058 | 0.00132114 | 3.69595e-06 | 1.71274e-06 | 1(Win) |
| simdjson (ondemand) | 3493.71 | 0.0207422 | 6765.26ms | 213963 | 2560 | 375710 | 58405.3 | 1.44405 | 7.45645 | 0.97265 | 0.00113066 | 7.61303e-06 | 4.48018e-06 | 2(Loss) |
| glaze | 3333.99 | 0.0254365 | 7038.64ms | 213963 | 1280 | 310221 | 61203.2 | 1.51607 | 7.57528 | 1.37872 | 0.00238238 | 1.87715e-05 | 1.374e-05 | 3(Loss) |
| jsonifier | 3091.5 | 0.0105908 | 7529.77ms | 213963 | 4890 | 238951 | 66003.8 | 1.63828 | 6.43804 | 1.41815 | 0.00176023 | 5.34657e-06 | 2.85201e-06 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22858.3 | 0.0143803 | 1630.71ms | 213963 | 4890 | 8058.11 | 8926.76 | 0.221997 | 0.727261 | 0.163706 | 8.30257e-05 | 1.25397e-06 | 3.80396e-07 | 1(Win) |
| glaze | 5677.26 | 0.0520526 | 4332.67ms | 213963 | 2560 | 896035 | 35941.8 | 0.891188 | 3.04141 | 0.571225 | 0.000658691 | 3.55822e-06 | 1.29257e-06 | 2(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22954.6 | 0.0697032 | 1625.54ms | 213963 | 640 | 24571.1 | 8889.35 | 0.221148 | 0.724822 | 0.163159 | 8.19578e-05 | 2.43909e-06 | 1.3583e-06 | 1(Win) |
| glaze | 6700.63 | 0.0460296 | 3784.92ms | 213963 | 1280 | 251496 | 30452.5 | 0.755294 | 3.01408 | 0.564888 | 0.000658532 | 1.71613e-06 | 5.40397e-07 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 864.98 | 0.0465801 | 6295.74ms | 1834197 | 160 | 1.41972e+08 | 2.02227e+06 | 5.84639 | 26.383 | 5.71663 | 0.0287784 | 0.0812124 | 0.000792312 | 1(Win) |
| jsonifier (two-stage) | 769.728 | 0.0665301 | 7078.88ms | 1834197 | 160 | 3.65741e+08 | 2.27253e+06 | 6.53144 | 30.4989 | 6.30908 | 0.0318824 | 0.145081 | 0.00129234 | 2(Loss) |
| glaze | 707.111 | 0.0740796 | 7682.58ms | 1834197 | 160 | 5.37322e+08 | 2.47377e+06 | 7.13069 | 30.8954 | 6.4503 | 0.0341631 | 0.0814814 | 0.000845823 | 3(Loss) |
| simdjson (ondemand) | 602.889 | 0.0561138 | 9035.46ms | 1834197 | 160 | 4.24109e+08 | 2.90141e+06 | 8.36523 | 34.9145 | 6.13834 | 0.0446768 | 0.146441 | 0.00330612 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 959.893 | 0.0484431 | 6289.98ms | 1834197 | 160 | 1.2469e+08 | 1.82231e+06 | 5.26631 | 23.3731 | 5.01025 | 0.0282051 | 0.0552175 | 1.71465e-05 | 1(Win) |
| jsonifier (two-stage) | 848.819 | 0.0673213 | 7076.57ms | 1834197 | 160 | 3.07955e+08 | 2.06078e+06 | 5.95115 | 27.4887 | 5.60251 | 0.0312929 | 0.118869 | 0.00112085 | 2(Loss) |
| glaze | 783.539 | 0.086689 | 7647.81ms | 1834197 | 40 | 1.49816e+08 | 2.23247e+06 | 6.44741 | 27.8785 | 5.74305 | 0.0329478 | 0.0580784 | 0.000230319 | 3(Loss) |
| simdjson (ondemand) | 660.109 | 0.0605763 | 8932.97ms | 1834197 | 160 | 4.12275e+08 | 2.64991e+06 | 7.62928 | 31.8836 | 5.42958 | 0.0404488 | 0.118334 | 0.000248729 | 4(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 892.943 | 0.0807526 | 6107.06ms | 1834197 | 160 | 4.00385e+08 | 1.95894e+06 | 5.65957 | 12.611 | 0.907968 | 0.00128116 | 0.0590981 | 0.000845929 | 1(Win) |
| glaze | 616.344 | 0.296282 | 8821.26ms | 1833577 | 30 | 2.11974e+09 | 2.83711e+06 | 8.19485 | 15.5349 | 0.949926 | 0.0010161 | 0.0488914 | 0.000233842 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 889.825 | 0.11922 | 6104.1ms | 1834197 | 40 | 2.19706e+08 | 1.96581e+06 | 5.65619 | 12.6107 | 0.907901 | 0.00128574 | 0.0592454 | 5.407e-05 | 1(Win) |
| glaze | 614.479 | 0.0976028 | 8870.07ms | 1833577 | 160 | 1.23432e+09 | 2.84572e+06 | 8.24927 | 15.534 | 0.94973 | 0.00099295 | 0.0487196 | 0.000391595 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3430.66 | 0.186559 | 8586.85ms | 9930848 | 30 | 7.95738e+08 | 2.76063e+06 | 1.45757 | 6.65832 | 1.20675 | 0.00688864 | 0.0540899 | 0.00126999 | 1(Win) |
| jsonifier | 3349.17 | 0.0531553 | 8743.98ms | 9930848 | 160 | 3.61503e+08 | 2.82781e+06 | 1.5038 | 7.00783 | 1.56661 | 0.00491565 | 0.0293773 | 0.000291521 | 2(Loss) |
| simdjson (ondemand) | 2794.12 | 0.210893 | 5028.55ms | 9930848 | 40 | 2.04393e+09 | 3.38954e+06 | 1.80657 | 7.48988 | 1.17975 | 0.00779952 | 0.0533278 | 0.00573497 | 3(Loss) |
| glaze | 2716.53 | 0.0826767 | 5255.74ms | 9930848 | 40 | 3.32331e+08 | 3.48636e+06 | 1.84634 | 8.55415 | 1.76047 | 0.0072184 | 0.0287976 | 0.000652872 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3726.4 | 0.116883 | 8579.33ms | 9930848 | 160 | 1.41193e+09 | 2.54154e+06 | 1.34904 | 6.10203 | 1.07628 | 0.00672698 | 0.0492085 | 0.00157737 | 1(Win) |
| jsonifier | 3602.44 | 0.103033 | 8790.79ms | 9930848 | 30 | 2.20119e+08 | 2.62899e+06 | 1.39806 | 6.45088 | 1.43592 | 0.00481106 | 0.0246079 | 0.000263603 | 2(Loss) |
| simdjson (ondemand) | 3050.56 | 0.115506 | 10263.4ms | 9930848 | 80 | 1.02875e+09 | 3.10461e+06 | 1.65835 | 6.93019 | 1.04884 | 0.00700812 | 0.047814 | 0.00450031 | 3(Loss) |
| glaze | 2901.48 | 0.0659136 | 5244.99ms | 9930848 | 30 | 1.38869e+08 | 3.26412e+06 | 1.73953 | 7.99717 | 1.63009 | 0.0071418 | 0.0244418 | 0.000778611 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5513.48 | 0.0328574 | 5333.9ms | 9930848 | 80 | 2.54846e+07 | 1.71775e+06 | 0.915944 | 2.47977 | 0.167991 | 0.000254159 | 0.0246815 | 0.000149464 | 1(Win) |
| glaze | 3692.29 | 0.142003 | 8024.71ms | 9930228 | 40 | 5.3062e+08 | 2.56486e+06 | 1.37083 | 4.13202 | 0.480827 | 0.00110777 | 0.0416028 | 0.00227597 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5570.02 | 0.0953967 | 5317.67ms | 9930848 | 80 | 2.10482e+08 | 1.70032e+06 | 0.919048 | 2.47974 | 0.167984 | 0.000253489 | 0.024671 | 0.000500241 | 1(Win) |
| glaze | 4072.79 | 0.116878 | 7244.37ms | 9930228 | 80 | 5.90864e+08 | 2.32524e+06 | 1.24317 | 4.13176 | 0.480769 | 0.00110884 | 0.022305 | 3.9945e-05 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 869.564 | 0.0626371 | 6267.35ms | 1834197 | 160 | 2.54023e+08 | 2.01161e+06 | 5.78946 | 26.0023 | 5.60218 | 0.0300079 | 0.0828232 | 0.000536018 | 1(Win) |
| jsonifier (two-stage) | 777.917 | 0.0947963 | 6997.88ms | 1834197 | 80 | 3.63495e+08 | 2.2486e+06 | 6.45506 | 30.1252 | 6.20513 | 0.0328629 | 0.145954 | 0.000110832 | 2(Loss) |
| glaze | 705.449 | 0.0805609 | 7720.82ms | 1834197 | 80 | 3.19227e+08 | 2.47959e+06 | 7.12847 | 30.8629 | 6.43914 | 0.0344657 | 0.0820391 | 0.000148655 | 3(Loss) |
| simdjson (ondemand) | 605.383 | 0.0594057 | 8995.71ms | 1834197 | 160 | 4.7142e+08 | 2.88946e+06 | 8.31176 | 34.9036 | 6.13186 | 0.0448683 | 0.147365 | 0.000123927 | 4(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 981.718 | 0.126898 | 6251.24ms | 1834197 | 30 | 1.53372e+08 | 1.7818e+06 | 5.14618 | 23.0214 | 4.90715 | 0.0291528 | 0.0561829 | 9.35923e-06 | 1(Win) |
| jsonifier (two-stage) | 869.419 | 0.115261 | 7006.4ms | 1834197 | 40 | 2.15107e+08 | 2.01195e+06 | 5.80851 | 27.1443 | 5.51016 | 0.0319714 | 0.119707 | 0.000123964 | 2(Loss) |
| glaze | 779.653 | 0.0981396 | 7723.61ms | 1834197 | 40 | 1.93927e+08 | 2.2436e+06 | 6.47231 | 27.8798 | 5.74304 | 0.0333821 | 0.0583233 | 1.64377e-05 | 3(Loss) |
| simdjson (ondemand) | 669.264 | 0.118702 | 8824.04ms | 1834197 | 30 | 2.88758e+08 | 2.61366e+06 | 7.53444 | 31.909 | 5.43444 | 0.0402297 | 0.118788 | 3.14034e-05 | 4(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 841.535 | 0.091212 | 6457.86ms | 1834197 | 160 | 5.75138e+08 | 2.07862e+06 | 6.03939 | 12.6365 | 0.908002 | 0.00137742 | 0.059981 | 0.000204459 | 1(Win) |
| glaze | 607.792 | 0.245479 | 8949.57ms | 1833577 | 80 | 3.99033e+09 | 2.87703e+06 | 8.38192 | 15.5346 | 0.950156 | 0.000973589 | 0.0814355 | 0.00250897 | 2(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 845.449 | 0.098851 | 6459.11ms | 1834197 | 160 | 6.69268e+08 | 2.06899e+06 | 6.03758 | 12.6362 | 0.907939 | 0.00141103 | 0.05982 | 0.000236023 | 1(Win) |
| glaze | 633.307 | 0.162621 | 8595.73ms | 1833577 | 160 | 3.22585e+09 | 2.76112e+06 | 8.08631 | 15.5335 | 0.949903 | 0.000975337 | 0.0487926 | 3.30365e-05 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3492.94 | 0.147037 | 8449.66ms | 9930848 | 40 | 6.35775e+08 | 2.71141e+06 | 1.43614 | 6.58871 | 1.18762 | 0.00706548 | 0.0543918 | 0.000321639 | 1(Win) |
| jsonifier | 3386.1 | 0.0998719 | 8713.23ms | 9930848 | 30 | 2.34089e+08 | 2.79696e+06 | 1.49206 | 6.90932 | 1.54716 | 0.00505751 | 0.0298828 | 0.000460189 | 2(Loss) |
| simdjson (ondemand) | 2857.23 | 0.105186 | 5017.91ms | 9930848 | 30 | 3.64686e+08 | 3.31468e+06 | 1.76291 | 7.48828 | 1.17862 | 0.00781938 | 0.0534751 | 0.000331925 | 3(Loss) |
| glaze | 2716.69 | 0.0806905 | 5279.51ms | 9930848 | 40 | 3.16517e+08 | 3.48615e+06 | 1.85149 | 8.54924 | 1.75858 | 0.00791478 | 0.028992 | 0.000307285 | 4(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3809.59 | 0.150756 | 8432.48ms | 9930848 | 40 | 5.61855e+08 | 2.48604e+06 | 1.3239 | 6.03879 | 1.0594 | 0.00692469 | 0.0493721 | 0.00220692 | 1(Win) |
| jsonifier | 3649.65 | 0.0402014 | 8756.85ms | 9930848 | 160 | 1.7413e+08 | 2.59499e+06 | 1.38389 | 6.35885 | 1.4188 | 0.00493507 | 0.0249034 | 0.000224007 | 2(Loss) |
| simdjson (ondemand) | 3097.51 | 0.0892674 | 10191.6ms | 9930848 | 80 | 5.9597e+08 | 3.05756e+06 | 1.63141 | 6.93486 | 1.04973 | 0.00698691 | 0.0478878 | 0.00129697 | 3(Loss) |
| glaze | 2887.44 | 0.160252 | 5279.37ms | 9930848 | 40 | 1.10513e+09 | 3.28e+06 | 1.75819 | 7.99835 | 1.63007 | 0.00766796 | 0.0245697 | 0.000381498 | 4(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5978.08 | 0.0831017 | 9981.45ms | 9930848 | 160 | 2.77325e+08 | 1.58425e+06 | 0.842608 | 2.47707 | 0.167991 | 0.000272238 | 0.0248564 | 0.000180116 | 1(Win) |
| glaze | 3149.79 | 0.160657 | 9602.66ms | 9930228 | 160 | 3.73315e+09 | 3.00661e+06 | 1.61072 | 4.16781 | 0.480846 | 0.000978009 | 0.075475 | 0.0101468 | 2(Loss) |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6067.18 | 0.0508088 | 9967.16ms | 9930848 | 320 | 2.01292e+08 | 1.56099e+06 | 0.843527 | 2.47704 | 0.167984 | 0.000255832 | 0.0248457 | 0.00039364 | 1(Win) |
| glaze | 4101.61 | 0.108579 | 7183.29ms | 9930228 | 160 | 1.00559e+09 | 2.3089e+06 | 1.23226 | 4.16747 | 0.480771 | 0.00101223 | 0.0223303 | 0.000820878 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 1455.68 | 0.0411399 | 5450.91ms | 642697 | 640 | 1.92038e+07 | 421057 | 3.46733 | 17.3782 | 3.43983 | 0.0091013 | 0.0256385 | 1.64055e-05 | 1(Win) |
| jsonifier | 1414.14 | 0.0561744 | 5607.21ms | 642697 | 160 | 9.4847e+06 | 433424 | 3.57139 | 18.4295 | 3.61742 | 0.00911658 | 0.018811 | 1.52191e-05 | 2(Loss) |
| jsonifier (two-stage) | 1215.13 | 0.14784 | 6591.53ms | 642697 | 80 | 4.44875e+07 | 504408 | 4.15723 | 21.4492 | 3.98228 | 0.010556 | 0.0522543 | 5.74143e-05 | 3(Loss) |
| simdjson (ondemand) | 1155 | 0.0257512 | 6862.74ms | 642697 | 640 | 1.19515e+07 | 530670 | 4.37349 | 21.8772 | 3.45254 | 0.0113293 | 0.0656286 | 0.000108525 | 4(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 1652.98 | 0.046653 | 5151.44ms | 642697 | 320 | 9.57611e+06 | 370800 | 3.05555 | 16.1523 | 3.16686 | 0.00844654 | 0.00723705 | 7.69706e-06 | 1(Win) |
| jsonifier | 1510.83 | 0.036636 | 5607.9ms | 642697 | 320 | 7.06883e+06 | 405687 | 3.34333 | 17.3084 | 3.36127 | 0.008784 | 0.0163341 | 2.40247e-05 | 2(Loss) |
| simdjson (ondemand) | 1291 | 0.0318234 | 6466.12ms | 642697 | 320 | 7.30477e+06 | 474768 | 3.9135 | 20.6212 | 3.17221 | 0.0095979 | 0.0201812 | 2.66261e-05 | 3(Loss) |
| jsonifier (two-stage) | 1282.34 | 0.0493147 | 6564.74ms | 642697 | 640 | 3.55581e+07 | 477972 | 3.93604 | 20.3286 | 3.72619 | 0.0102163 | 0.047448 | 2.578e-05 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1267.47 | 0.0619955 | 6213.4ms | 642697 | 160 | 1.43807e+07 | 483581 | 3.96907 | 7.65295 | 0.792682 | 5.85618e-05 | 0.00478401 | 2.64802e-05 | 1(Win) |
| glaze | 1018.41 | 0.0452317 | 7795.16ms | 642692 | 640 | 4.74273e+07 | 601840 | 4.94573 | 10.1803 | 0.702843 | 0.000139735 | 0.0414771 | 0.000141555 | 2(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1272.98 | 0.0328376 | 6193.85ms | 642697 | 40 | 999929 | 481486 | 3.96895 | 7.65241 | 0.792569 | 5.74921e-05 | 0.0045437 | 4.41888e-05 | 1(Win) |
| glaze | 1055.65 | 0.0271381 | 7477.89ms | 642692 | 160 | 3.97234e+06 | 580609 | 4.78434 | 10.1783 | 0.702395 | 0.000143138 | 0.00384123 | 5.68021e-05 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 2246.64 | 0.0548381 | 6714.91ms | 1225964 | 640 | 5.21234e+07 | 520408 | 2.24689 | 12.1959 | 2.54055 | 0.00504581 | 0.0288718 | 2.58725e-05 | 1(Win) |
| jsonifier (two-stage) | 2217.17 | 0.185962 | 6839.68ms | 1225964 | 160 | 1.53861e+08 | 527326 | 2.2625 | 12.0236 | 2.12988 | 0.00497607 | 0.0564653 | 1.38411e-05 | 2(Loss) |
| simdjson (ondemand) | 2079.75 | 0.528543 | 7257.35ms | 1225964 | 640 | 5.65033e+09 | 562169 | 2.42399 | 12.104 | 1.83257 | 0.00459738 | 0.0624759 | 4.38813e-05 | 3(Loss) |
| jsonifier | 1933.92 | 0.0767547 | 7793.25ms | 1225964 | 80 | 1.72257e+07 | 604559 | 2.61437 | 13.0939 | 2.69642 | 0.00557037 | 0.0232252 | 0.000103419 | 4(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 2503.2 | 0.112671 | 6411.14ms | 1225964 | 80 | 2.21551e+07 | 467070 | 2.0259 | 11.5531 | 2.3976 | 0.00465635 | 0.0112267 | 4.19058e-06 | 1(Win) |
| simdjson (ondemand) | 2362.39 | 0.107066 | 6750.38ms | 1225964 | 80 | 2.24618e+07 | 494910 | 2.13919 | 11.4458 | 1.68566 | 0.00380642 | 0.0375974 | 1.00125e-05 | 2(Loss) |
| jsonifier (two-stage) | 2344.84 | 0.26585 | 6773.01ms | 1225964 | 640 | 1.12456e+09 | 498614 | 2.15326 | 11.4356 | 1.99563 | 0.00483434 | 0.0520512 | 6.50254e-06 | 3(Loss) |
| jsonifier | 2007.05 | 0.366826 | 7892.68ms | 1225964 | 160 | 7.30598e+08 | 582531 | 2.51755 | 12.506 | 2.56215 | 0.00533602 | 0.020585 | 1.09812e-05 | 4(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4017.28 | 0.0881182 | 7633.08ms | 1225964 | 160 | 1.05231e+07 | 291036 | 1.24854 | 4.14363 | 0.402621 | 6.2716e-05 | 0.0125194 | 5.9443e-06 | 1(Win) |
| glaze | 1727.22 | 0.449432 | 8723.79ms | 1225970 | 640 | 5.92344e+09 | 676913 | 2.93169 | 6.40403 | 0.609083 | 0.00010195 | 0.0335619 | 3.02643e-05 | 2(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4068.25 | 0.0524128 | 7602.74ms | 1225964 | 640 | 1.4521e+07 | 287389 | 1.25 | 4.14318 | 0.402519 | 6.33201e-05 | 0.0124317 | 2.69176e-05 | 1(Win) |
| glaze | 1803.53 | 0.431478 | 8341.59ms | 1225970 | 640 | 5.00736e+09 | 648270 | 2.81433 | 6.40233 | 0.608707 | 0.000102104 | 0.0125069 | 1.63493e-05 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1667.56 | 0.0833625 | 6187.59ms | 409725 | 30 | 1.14468e+06 | 234320 | 3.03043 | 13.4764 | 2.48498 | 0.01282 | 0.0225323 | 0.00025928 | 1(Win) |
| jsonifier (two-stage) | 1403.15 | 0.0915093 | 7451.13ms | 409725 | 40 | 2.59755e+06 | 278476 | 3.60067 | 15.9796 | 2.88178 | 0.0139786 | 0.0526168 | 3.52065e-05 | 2(Loss) |
| glaze | 1207.97 | 0.283191 | 8518.59ms | 409725 | 160 | 1.34262e+08 | 323472 | 4.20391 | 17.186 | 3.42748 | 0.0249708 | 0.01455 | 0.000181875 | 3(Loss) |
| simdjson (ondemand) | 1098.4 | 0.243645 | 9398.91ms | 409725 | 30 | 2.25373e+07 | 355741 | 4.59639 | 18.5882 | 3.3385 | 0.0135196 | 0.0568451 | 7.0047e-05 | 4(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2593.2 | 0.0264389 | 5228.89ms | 409725 | 640 | 1.01573e+06 | 150680 | 1.94795 | 9.99041 | 1.71712 | 0.00706301 | 0.000366969 | 4.41989e-06 | 1(Win) |
| jsonifier (two-stage) | 2013.04 | 0.0179649 | 6403.49ms | 409725 | 640 | 778229 | 194106 | 2.51059 | 12.4952 | 2.11404 | 0.00816413 | 0.00629891 | 4.72497e-06 | 2(Loss) |
| glaze | 1519.32 | 0.247088 | 8052.7ms | 409725 | 640 | 2.58448e+08 | 257184 | 3.33668 | 14.2103 | 2.76016 | 0.0195953 | 0.00327309 | 6.02424e-05 | 3(Loss) |
| simdjson (ondemand) | 1431.1 | 0.326555 | 8469.76ms | 409725 | 30 | 2.38494e+07 | 273037 | 3.5411 | 15.5101 | 2.64142 | 0.00630683 | 0.0156235 | 1.9688e-05 | 4(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14781.4 | 0.0635042 | 3409.82ms | 409725 | 80 | 22545 | 26434.9 | 0.3425 | 1.70938 | 0.290409 | 0.000642657 | 0.000113826 | 7.68808e-06 | 1(Win) |
| glaze | 3426.38 | 0.576468 | 6196.66ms | 409725 | 1280 | 5.5319e+08 | 114040 | 1.46488 | 5.49038 | 0.863145 | 0.0108574 | 0.0316588 | 2.38918e-05 | 2(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14738.6 | 0.0462149 | 3402.44ms | 409725 | 640 | 96076.9 | 26511.7 | 0.340583 | 1.70853 | 0.290231 | 0.000431109 | 4.45955e-05 | 2.65041e-06 | 1(Win) |
| glaze | 3771.3 | 0.321736 | 5673.3ms | 409725 | 2560 | 2.84474e+08 | 103610 | 1.33665 | 5.47384 | 0.859369 | 0.0108877 | 0.00155571 | 5.89763e-06 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2411.83 | 0.247922 | 8144.53ms | 785750 | 1280 | 7.59479e+08 | 310698 | 2.07447 | 9.02798 | 1.52919 | 0.00839397 | 0.0514887 | 6.88216e-05 | 1(Win) |
| jsonifier | 2155.22 | 0.164881 | 9225.09ms | 785750 | 30 | 9.85935e+06 | 347691 | 2.33256 | 9.62173 | 1.93478 | 0.00687895 | 0.0269618 | 4.78948e-05 | 2(Loss) |
| simdjson (ondemand) | 1961.32 | 0.20413 | 9973.39ms | 785750 | 1280 | 7.78566e+08 | 382063 | 2.56976 | 10.2987 | 1.76941 | 0.00781092 | 0.0545196 | 0.000271359 | 3(Loss) |
| glaze | 1813.16 | 0.32217 | 5445.62ms | 785750 | 30 | 5.31847e+07 | 413283 | 2.78603 | 11.7907 | 2.33128 | 0.0132362 | 0.0181551 | 4.73009e-05 | 4(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3271.39 | 0.802742 | 7299.6ms | 785750 | 640 | 2.1639e+09 | 229062 | 1.52177 | 7.2106 | 1.12893 | 0.00519878 | 0.0212139 | 1.20605e-05 | 1(Win) |
| jsonifier | 2809.77 | 0.229835 | 8264.89ms | 785750 | 1280 | 4.80913e+08 | 266694 | 1.79614 | 7.80602 | 1.53481 | 0.00412213 | 0.00473135 | 9.32529e-06 | 2(Loss) |
| simdjson (ondemand) | 2533.96 | 0.342301 | 8972.07ms | 785750 | 30 | 3.07402e+07 | 295722 | 1.99396 | 8.6963 | 1.40651 | 0.00371882 | 0.0203036 | 2.5114e-05 | 3(Loss) |
| glaze | 2149.17 | 0.394901 | 5173.6ms | 785750 | 640 | 1.21334e+09 | 348669 | 2.34488 | 10.2392 | 1.98351 | 0.0106486 | 0.00460434 | 1.61311e-05 | 4(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18817.8 | 0.105194 | 4780.58ms | 785750 | 4890 | 8.58067e+06 | 39821.3 | 0.269037 | 1.01387 | 0.151462 | 0.000175403 | 0.00750542 | 4.96133e-06 | 1(Win) |
| glaze | 3949.35 | 0.188372 | 5066.4ms | 785750 | 320 | 4.08787e+07 | 189740 | 1.26924 | 4.43462 | 0.800408 | 0.00651471 | 0.0551934 | 6.35897e-05 | 2(Loss) |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18826.1 | 0.106944 | 4780.81ms | 785750 | 80 | 144960 | 39803.7 | 0.268458 | 1.01343 | 0.151369 | 0.000217038 | 0.00756115 | 6.93605e-06 | 1(Win) |
| glaze | 4604.59 | 0.570608 | 8830.3ms | 785750 | 40 | 3.44923e+07 | 162740 | 1.10176 | 4.42505 | 0.798136 | 0.00650115 | 0.0105865 | 4.17754e-05 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 6973.47 | 0.0599752 | 4338.11ms | 264040 | 1280 | 600337 | 36109.4 | 0.724679 | 3.4166 | 0.444376 | 0.00130626 | 3.61273e-06 | 2.05639e-06 | 1(Win) |
| jsonifier | 6943.78 | 0.03358 | 4350.8ms | 264040 | 4890 | 725132 | 36263.8 | 0.730109 | 3.43304 | 0.448853 | 0.00134141 | 5.06058e-06 | 2.9462e-06 | 2(Loss) |
| simdjson (ondemand) | 5737.31 | 0.109093 | 5165.72ms | 264040 | 40 | 91701.3 | 43889.6 | 0.897938 | 4.13673 | 0.457789 | 0.000770054 | 1.23087e-06 | 4.73413e-07 | 3(Loss) |
| glaze | 3483.15 | 0.0180827 | 7969.11ms | 264040 | 4890 | 835658 | 72293.2 | 1.46896 | 6.49119 | 1.20323 | 0.00256016 | 2.98415e-06 | 1.44986e-06 | 4(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 7152.47 | 0.0805397 | 4333.53ms | 264040 | 1280 | 1.0291e+06 | 35205.8 | 0.706977 | 3.3564 | 0.430336 | 0.00129844 | 1.65695e-06 | 6.98284e-07 | 1(Win) |
| jsonifier | 7102.72 | 0.0508211 | 4432.93ms | 264040 | 1280 | 415516 | 35452.4 | 0.713552 | 3.37194 | 0.434533 | 0.00135752 | 4.68383e-06 | 3.16003e-06 | 2(Loss) |
| simdjson (ondemand) | 5796.37 | 0.0290958 | 5124.8ms | 264040 | 4890 | 781261 | 43442.4 | 0.874421 | 4.06425 | 0.443122 | 0.000699145 | 1.47929e-06 | 6.5755e-07 | 3(Loss) |
| glaze | 3563.61 | 0.0693718 | 7981.01ms | 264040 | 320 | 768909 | 70661 | 1.44089 | 6.40728 | 1.18437 | 0.00254914 | 3.50326e-06 | 2.34339e-06 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 8960.35 | 0.144921 | 5060.15ms | 399947 | 30 | 114167 | 42567.4 | 0.574092 | 2.82924 | 0.312479 | 0.000785937 | 1.5002e-06 | 1.00013e-06 | 1(Win) |
| jsonifier | 8896.98 | 0.0517468 | 5040.22ms | 399947 | 2560 | 1.25987e+06 | 42870.6 | 0.57501 | 2.82954 | 0.312539 | 0.000789204 | 2.9125e-06 | 1.71605e-06 | 2(Loss) |
| simdjson (ondemand) | 7572.71 | 0.0856695 | 5831.17ms | 399947 | 40 | 74475.8 | 50367.6 | 0.680061 | 3.17164 | 0.321827 | 0.000463999 | 8.75116e-07 | 2.50033e-07 | 3(Loss) |
| glaze | 4367.36 | 0.0420333 | 9485.29ms | 399947 | 4890 | 6.58966e+06 | 87334 | 1.16882 | 5.60327 | 1.05177 | 0.00193596 | 4.28278e-06 | 2.53357e-06 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 9024.3 | 0.0519272 | 5089.91ms | 399947 | 2560 | 1.23312e+06 | 42265.8 | 0.562409 | 2.7899 | 0.303318 | 0.00079596 | 2.90273e-06 | 1.9192e-06 | 1(Tie) |
| jsonifier STATISTICAL TIE | 9021.62 | 0.0328778 | 5125.02ms | 399947 | 4890 | 944824 | 42278.3 | 0.563046 | 2.79018 | 0.303378 | 0.000807241 | 3.26628e-06 | 2.39551e-06 | 1(Tie) |
| simdjson (ondemand) | 7631.58 | 0.0597048 | 5792.2ms | 399947 | 1280 | 1.13974e+06 | 49979.1 | 0.667374 | 3.13026 | 0.313527 | 0.000454334 | 5.48315e-06 | 3.64501e-06 | 3(Loss) |
| glaze | 4434.52 | 0.0327223 | 9453.74ms | 399947 | 2560 | 2.02786e+06 | 86011.3 | 1.14799 | 5.5483 | 1.03946 | 0.00188675 | 2.75329e-06 | 1.6594e-06 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 2092.13 | 0.0310719 | 6569.41ms | 264040 | 2560 | 3.58045e+06 | 120360 | 2.45612 | 10.0075 | 1.79741 | 0.00620495 | 7.11747e-05 | 2.26469e-05 | 1(Win) |
| jsonifier | 1987.02 | 0.179214 | 6922.66ms | 264040 | 30 | 1.54738e+06 | 126726 | 2.59078 | 8.12088 | 1.45553 | 0.0103804 | 0.000767813 | 0.000324825 | 2(Loss) |
| jsonifier (two-stage) | 1838.91 | 0.0556719 | 7379.71ms | 264040 | 1280 | 7.43879e+06 | 136933 | 2.77425 | 9.25801 | 1.52889 | 0.0129733 | 0.000806953 | 0.00011185 | 3(Loss) |
| simdjson (ondemand) | 1714.19 | 0.185056 | 7896.13ms | 264040 | 2560 | 1.89176e+08 | 146896 | 2.95887 | 10.1516 | 1.54256 | 0.0115745 | 0.00306806 | 5.38019e-05 | 4(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 2584.27 | 0.0533734 | 6007.94ms | 264040 | 640 | 1.73098e+06 | 97438.7 | 1.97937 | 8.57963 | 1.47084 | 0.00466341 | 5.55669e-06 | 2.7458e-06 | 1(Win) |
| jsonifier (two-stage) | 2520.01 | 0.0995016 | 6187.81ms | 264040 | 2560 | 2.53068e+07 | 99923.7 | 2.03202 | 7.84298 | 1.20695 | 0.00396626 | 8.15646e-05 | 4.21219e-05 | 2(Loss) |
| jsonifier | 2499.35 | 0.085526 | 6335.33ms | 264040 | 160 | 1.18796e+06 | 100750 | 2.06141 | 6.69438 | 1.13077 | 0.00768316 | 3.18844e-05 | 1.75873e-05 | 3(Loss) |
| simdjson (ondemand) | 2150.17 | 0.168088 | 7207.53ms | 264040 | 80 | 3.09998e+06 | 117111 | 2.36993 | 8.77946 | 1.2314 | 0.00777595 | 0.000399135 | 2.04041e-05 | 4(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19630 | 0.0808007 | 2029.29ms | 264040 | 160 | 17188.9 | 12827.7 | 0.263199 | 1.07317 | 0.16257 | 1.20247e-05 | 1.74216e-05 | 8.94751e-06 | 1(Win) |
| glaze | 6136.11 | 0.130095 | 4861.7ms | 263923 | 4890 | 1.39251e+07 | 41018.9 | 0.832669 | 2.25639 | 0.339777 | 0.000469263 | 0.000172606 | 8.80687e-06 | 2(Loss) |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19645.5 | 0.103897 | 2026.64ms | 264040 | 640 | 113501 | 12817.6 | 0.262267 | 1.07108 | 0.1621 | 6.98876e-06 | 1.8759e-05 | 6.45025e-06 | 1(Win) |
| glaze | 7511.55 | 0.291538 | 4086.37ms | 263923 | 1280 | 1.2215e+07 | 33507.9 | 0.675956 | 2.23443 | 0.33478 | 0.000467842 | 5.72196e-06 | 2.85654e-06 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2635.81 | 0.0759518 | 7792.43ms | 399947 | 2560 | 3.09239e+07 | 144707 | 1.94294 | 6.66719 | 1.02737 | 0.00871029 | 0.00153368 | 0.000123448 | 1(Win) |
| simdjson (ondemand) | 2501.13 | 0.0530859 | 8209.9ms | 399947 | 2560 | 1.67776e+07 | 152499 | 2.03103 | 7.1476 | 1.03912 | 0.00761291 | 0.006762 | 9.69904e-05 | 2(Loss) |
| glaze | 2402.06 | 0.156841 | 8558.84ms | 399947 | 160 | 9.9238e+06 | 158789 | 2.12727 | 8.4602 | 1.53055 | 0.00580971 | 0.000178742 | 2.25967e-05 | 3(Loss) |
| jsonifier | 2043.88 | 0.139035 | 9944.9ms | 399947 | 1280 | 8.61692e+07 | 186616 | 2.5103 | 7.02697 | 1.35516 | 0.00796353 | 0.00164475 | 5.08896e-05 | 4(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3479.85 | 0.029976 | 6697.19ms | 399947 | 2560 | 2.76359e+06 | 109608 | 1.46577 | 5.73868 | 0.816126 | 0.0033521 | 0.000174464 | 2.03181e-05 | 1(Win) |
| simdjson (ondemand) | 3056.03 | 0.0628769 | 7533.48ms | 399947 | 2560 | 1.57656e+07 | 124809 | 1.66788 | 6.24246 | 0.834035 | 0.0051856 | 0.00129386 | 4.42461e-05 | 2(Loss) |
| glaze | 2788.14 | 0.155631 | 8052.36ms | 399947 | 320 | 1.4505e+07 | 136801 | 1.82947 | 7.52213 | 1.31745 | 0.00522757 | 1.94088e-05 | 5.08661e-06 | 3(Loss) |
| jsonifier | 2362.45 | 0.111844 | 9315.93ms | 399947 | 160 | 5.21708e+06 | 161450 | 2.14237 | 6.08671 | 1.14118 | 0.00584887 | 0.000159271 | 2.42376e-05 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22884.6 | 0.0569225 | 2414.66ms | 399947 | 640 | 57605.5 | 16667 | 0.224875 | 0.780681 | 0.110842 | 1.2236e-05 | 1.28064e-05 | 4.40293e-06 | 1(Win) |
| glaze | 5660.18 | 0.248292 | 7498.41ms | 399830 | 4890 | 1.36812e+08 | 67366.7 | 0.9016 | 2.54849 | 0.458615 | 0.000718219 | 0.00255776 | 1.64548e-05 | 2(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22820.1 | 0.080239 | 2404.84ms | 399947 | 1280 | 230224 | 16714.2 | 0.223937 | 0.779278 | 0.110527 | 9.37624e-06 | 6.89935e-06 | 1.78539e-06 | 1(Win) |
| glaze | 6526.22 | 0.141405 | 6622.27ms | 399830 | 2560 | 1.74741e+07 | 58427 | 0.780869 | 2.53274 | 0.454951 | 0.000715973 | 4.11992e-06 | 2.36136e-06 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1038.24 | 0.0927392 | 1156.74ms | 4630 | 30 | 466.671 | 4252.87 | 5.10033 | 23.2125 | 4.71037 | 0.00729302 | 3.59971e-05 | 2.87977e-05 | 1(Win) |
| jsonifier (two-stage) | 954.96 | 0.152279 | 1180.86ms | 4630 | 30 | 1487.29 | 4623.77 | 5.3423 | 25.9276 | 5.0581 | 0.00696904 | 0.000151188 | 0.000115191 | 2(Loss) |
| glaze | 809.02 | 0.128552 | 1281.22ms | 4630 | 40 | 1969.05 | 5457.85 | 6.53278 | 29.4121 | 5.7676 | 0.00444924 | 7.01944e-05 | 4.85961e-05 | 3(Loss) |
| simdjson (ondemand) | 725.416 | 0.0603234 | 1337.2ms | 4630 | 4890 | 65927.8 | 6086.87 | 7.12881 | 30.9244 | 5.47214 | 0.00266608 | 6.08197e-05 | 1.9964e-05 | 4(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1285.37 | 0.0367246 | 1156.78ms | 4630 | 320 | 509.3 | 3435.22 | 4.05679 | 18.8726 | 3.70454 | 0.00458086 | 3.17225e-05 | 1.34989e-06 | 1(Win) |
| jsonifier (two-stage) | 1221.89 | 0.0569821 | 1176.44ms | 4630 | 1280 | 5427.29 | 3613.66 | 4.24979 | 21.5786 | 4.04989 | 0.00486417 | 3.69533e-05 | 8.94303e-06 | 2(Loss) |
| glaze | 947.851 | 0.0850473 | 1279.78ms | 4630 | 640 | 10045.8 | 4658.45 | 5.47629 | 24.994 | 4.74363 | 0.00312702 | 2.76728e-05 | 2.36231e-06 | 3(Loss) |
| simdjson (ondemand) | 844.339 | 0.0609308 | 1341.55ms | 4630 | 1280 | 12996.1 | 5229.55 | 6.14245 | 27.3041 | 4.63888 | 0.000914214 | 4.16779e-05 | 1.26552e-05 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1555.9 | 0.2992 | 1010.65ms | 4630 | 1280 | 92285.6 | 2837.92 | 3.33462 | 7.93218 | 0.459396 | 0.000221214 | 1.46801e-05 | 2.53105e-06 | 1(Win) |
| glaze | 990.212 | 0.0637634 | 1169.57ms | 4630 | 640 | 5174.03 | 4459.16 | 5.24606 | 9.73931 | 0.674515 | 0.000220032 | 3.88094e-05 | 1.41739e-05 | 2(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1554.04 | 0.224162 | 1002.14ms | 4630 | 2560 | 103849 | 2841.32 | 3.36571 | 7.82009 | 0.433262 | 0.000220117 | 3.12163e-05 | 1.64518e-05 | 1(Win) |
| glaze | 1003.22 | 0.104447 | 1165.45ms | 4630 | 4890 | 103340 | 4401.33 | 5.16589 | 9.2527 | 0.565876 | 0.000222122 | 2.42925e-05 | 9.62868e-06 | 2(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2721.68 | 0.0397745 | 1244.18ms | 14795 | 4890 | 20791 | 5184.16 | 1.91151 | 8.93322 | 1.61365 | 0.00211442 | 2.15764e-05 | 8.83237e-06 | 1(Win) |
| jsonifier | 2446.76 | 0.0510889 | 1304.49ms | 14795 | 1280 | 11109.9 | 5766.66 | 2.11815 | 9.36708 | 1.96898 | 0.00365305 | 2.49768e-05 | 1.20923e-05 | 2(Loss) |
| simdjson (ondemand) | 2070.97 | 0.0735649 | 1410.15ms | 14795 | 640 | 16077 | 6813.06 | 2.50065 | 10.645 | 1.77655 | 0.00108821 | 1.37293e-05 | 3.06269e-06 | 3(Loss) |
| glaze | 1933.22 | 0.0634562 | 1456.43ms | 14795 | 2560 | 54910.3 | 7298.48 | 2.66811 | 12.1384 | 2.36587 | 0.00452766 | 2.75906e-05 | 1.08514e-05 | 4(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3277.56 | 0.0756251 | 1243.6ms | 14795 | 320 | 3391.65 | 4304.91 | 1.58623 | 7.57601 | 1.29909 | 0.00130407 | 7.60392e-06 | 8.4488e-07 | 1(Win) |
| jsonifier | 2893.23 | 0.0889076 | 1301.39ms | 14795 | 80 | 1503.95 | 4876.77 | 1.79635 | 8.0146 | 1.65563 | 0.00302552 | 1.26732e-05 | 1.68976e-06 | 2(Loss) |
| simdjson (ondemand) | 2345.76 | 0.159804 | 1421.88ms | 14795 | 80 | 7391.45 | 6014.94 | 2.2117 | 9.65421 | 1.54572 | 0.000400473 | 1.09834e-05 | 0 | 3(Loss) |
| glaze | 2216.14 | 0.075565 | 1451.66ms | 14795 | 160 | 3703.37 | 6366.75 | 2.33984 | 10.7663 | 2.04826 | 0.00425524 | 1.68976e-05 | 2.95708e-06 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4326.16 | 0.0497877 | 1051.12ms | 14795 | 4890 | 12893.7 | 3261.46 | 1.19879 | 2.59757 | 0.145117 | 6.82953e-05 | 8.14126e-06 | 1.83835e-06 | 1(Win) |
| glaze | 3356.08 | 0.106116 | 1148.39ms | 14795 | 4890 | 97327.2 | 4204.19 | 1.55279 | 4.44481 | 0.533627 | 0.00094809 | 1.7955e-05 | 6.96637e-06 | 2(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4486.79 | 0.450131 | 1041.54ms | 14795 | 40 | 8014.88 | 3144.7 | 1.16349 | 2.55613 | 0.135519 | 6.75904e-05 | 1.68976e-05 | 6.75904e-06 | 1(Win) |
| glaze | 3857.54 | 0.052364 | 1088.24ms | 14795 | 4890 | 17938.4 | 3657.67 | 1.34571 | 4.23853 | 0.486313 | 0.000947648 | 9.91049e-06 | 2.34977e-06 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1969.1 | 0.0476557 | 968.914ms | 5092 | 2560 | 3536 | 2466.16 | 2.64711 | 10.8386 | 2.02396 | 0.00104514 | 3.65923e-05 | 1.53427e-05 | 1(Win) |
| jsonifier (two-stage) | 1619.47 | 0.104964 | 1028.01ms | 5092 | 40 | 396.251 | 2998.57 | 3.22404 | 13.4711 | 2.34701 | 0.00108013 | 2.9458e-05 | 0 | 2(Loss) |
| glaze | 1553.04 | 0.251709 | 1047.56ms | 5092 | 40 | 2477.82 | 3126.85 | 3.36015 | 14.0685 | 2.69364 | 0.00197859 | 9.81932e-06 | 0 | 3(Loss) |
| simdjson (ondemand) | 1233.08 | 0.089589 | 1124.78ms | 5092 | 320 | 3983.42 | 3938.21 | 4.22169 | 15.6129 | 2.64336 | 0.00162142 | 3.86636e-05 | 1.59564e-05 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2395.39 | 0.0570287 | 958.565ms | 5092 | 2560 | 3421.78 | 2027.28 | 2.18637 | 9.35978 | 1.65515 | 0.00105857 | 2.14798e-05 | 2.3014e-06 | 1(Win) |
| jsonifier (two-stage) | 1875.52 | 0.0568146 | 1016.59ms | 5092 | 1280 | 2769.88 | 2589.2 | 2.78974 | 12.1807 | 2.01434 | 0.00100341 | 2.6236e-05 | 5.21652e-06 | 2(Loss) |
| glaze | 1865.69 | 0.0347318 | 1021.29ms | 5092 | 4890 | 3996.31 | 2602.84 | 2.79479 | 12.5481 | 2.31775 | 0.000597071 | 1.81929e-05 | 3.41367e-06 | 3(Loss) |
| simdjson (ondemand) | 1427.12 | 0.0728026 | 1108.59ms | 5092 | 1280 | 7855.2 | 3402.72 | 3.6505 | 13.9548 | 2.24215 | 0.00166898 | 0.000106171 | 6.25982e-05 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 8860.44 | 0.210674 | 780.377ms | 5092 | 30 | 39.9954 | 548.067 | 0.624345 | 2.28456 | 0.399254 | 0.000196386 | 5.23697e-05 | 2.61849e-05 | 1(Win) |
| glaze | 3529.8 | 0.160736 | 859.345ms | 5092 | 2560 | 12518.2 | 1375.75 | 1.50076 | 4.5762 | 0.695208 | 0.00020237 | 0.00019723 | 0.00012512 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9553.75 | 0.0472145 | 773.324ms | 5092 | 2560 | 147.442 | 508.294 | 0.582752 | 2.18009 | 0.374902 | 0.000196386 | 2.60059e-05 | 1.44221e-05 | 1(Win) |
| glaze | 3973.29 | 0.157025 | 845.81ms | 5092 | 2560 | 9428.69 | 1222.19 | 1.33751 | 4.10134 | 0.593087 | 0.000360323 | 4.56445e-05 | 2.01756e-05 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3284.65 | 0.125966 | 1075.31ms | 11724 | 640 | 11766.9 | 3403.98 | 1.58569 | 6.8057 | 1.07898 | 0.000453797 | 8.26296e-06 | 6.66368e-07 | 1(Win) |
| jsonifier | 2736.48 | 0.0605776 | 1131.9ms | 11724 | 2560 | 15683.1 | 4085.86 | 1.88529 | 7.33828 | 1.49531 | 0.000982893 | 2.15903e-05 | 8.76274e-06 | 2(Loss) |
| simdjson (ondemand) | 2579.9 | 0.051895 | 1165.63ms | 11724 | 4890 | 24734.6 | 4333.84 | 1.99968 | 7.51322 | 1.18219 | 0.000795408 | 3.43971e-05 | 1.69195e-05 | 3(Loss) |
| glaze | 2424.86 | 0.0818703 | 1189.57ms | 11724 | 1280 | 18240.6 | 4610.93 | 2.13883 | 9.03779 | 1.75085 | 0.001489 | 1.61261e-05 | 5.99731e-06 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3737.05 | 0.158233 | 1066.25ms | 11724 | 30 | 672.369 | 2991.9 | 1.39868 | 6.1531 | 0.916837 | 0.000503241 | 9.9511e-05 | 1.7059e-05 | 1(Win) |
| jsonifier | 3101.92 | 0.0898869 | 1124.92ms | 11724 | 40 | 419.897 | 3604.5 | 1.68064 | 6.6856 | 1.33308 | 0.00115362 | 2.13238e-05 | 0 | 2(Loss) |
| simdjson (ondemand) | 3008.7 | 0.115874 | 1148.01ms | 11724 | 640 | 11867.1 | 3716.18 | 1.72927 | 6.78079 | 1.00614 | 0.000737536 | 7.99642e-06 | 1.06619e-06 | 3(Loss) |
| glaze | 2689.52 | 0.0382202 | 1177.25ms | 11724 | 4890 | 12345.2 | 4157.21 | 1.92138 | 8.3979 | 1.59152 | 0.0014308 | 1.9658e-05 | 7.86669e-06 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 17333.8 | 0.0400608 | 783.576ms | 11724 | 2560 | 170.939 | 645.032 | 0.315971 | 1.12547 | 0.177585 | 8.53284e-05 | 6.16391e-06 | 4.66458e-07 | 1(Win) |
| glaze | 4042.47 | 0.103583 | 1007.83ms | 11746 | 4890 | 40287.7 | 2771.04 | 1.29232 | 3.58616 | 0.652393 | 0.000502925 | 2.31206e-05 | 6.33727e-06 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19120.8 | 0.217677 | 781.003ms | 11724 | 40 | 64.8077 | 584.75 | 0.287472 | 1.07369 | 0.165473 | 8.52951e-05 | 8.10304e-05 | 2.55885e-05 | 1(Win) |
| glaze | 4511.44 | 0.279079 | 970.084ms | 11746 | 640 | 30731.5 | 2482.99 | 1.16126 | 3.33441 | 0.594585 | 0.000590627 | 1.92885e-05 | 7.1833e-06 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2033.02 | 0.0473641 | 957.446ms | 4857 | 4890 | 5694.54 | 2278.38 | 2.56172 | 9.61756 | 1.78958 | 0.00116893 | 3.0357e-05 | 7.99975e-06 | 1(Win) |
| jsonifier (two-stage) | 1758.61 | 0.0730472 | 992.766ms | 4857 | 1280 | 4738.22 | 2633.9 | 2.92807 | 11.6928 | 2.01513 | 0.00100821 | 0.000122085 | 4.11777e-05 | 2(Loss) |
| glaze | 1727.96 | 0.119329 | 1000.54ms | 4857 | 640 | 6548.51 | 2680.62 | 3.02479 | 12.1473 | 2.30719 | 0.000956738 | 9.55451e-05 | 3.86041e-05 | 3(Loss) |
| simdjson (ondemand) | 1494.63 | 0.129474 | 1039.72ms | 4857 | 640 | 10304.3 | 3099.09 | 3.45624 | 13.2796 | 2.19045 | 0.000267333 | 5.46891e-05 | 1.31897e-05 | 4(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2753.79 | 0.0723551 | 925.419ms | 4857 | 1280 | 1895.93 | 1682.04 | 1.91984 | 7.40395 | 1.27939 | 0.000620078 | 2.87922e-05 | 4.66466e-06 | 1(Win) |
| glaze | 2450.57 | 0.121872 | 950.491ms | 4857 | 640 | 3396.18 | 1890.17 | 2.10965 | 9.32263 | 1.67943 | 0.00137044 | 1.86586e-05 | 2.57361e-06 | 2(Loss) |
| jsonifier (two-stage) | 2263.04 | 0.167227 | 963.885ms | 4857 | 40 | 468.626 | 2046.8 | 2.32337 | 9.61705 | 1.53366 | 0.000828701 | 1.02944e-05 | 0 | 3(Loss) |
| simdjson (ondemand) | 1975.32 | 0.107431 | 987.348ms | 4857 | 80 | 507.705 | 2344.94 | 2.6558 | 10.8518 | 1.6609 | 0.00127908 | 9.00762e-05 | 3.86041e-05 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9668.56 | 0.106282 | 772.369ms | 4857 | 320 | 82.9625 | 479.078 | 0.583737 | 1.77579 | 0.315421 | 0.000205888 | 1.9302e-05 | 0 | 1(Win) |
| glaze | 3679.31 | 0.351101 | 851.318ms | 4857 | 2560 | 50015.9 | 1258.93 | 1.43726 | 3.79411 | 0.630842 | 0.000355881 | 3.29743e-05 | 6.91656e-06 | 2(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11320.2 | 0.0738936 | 768.409ms | 4857 | 160 | 14.6273 | 409.181 | 0.500111 | 1.65205 | 0.284332 | 0.000205888 | 4.11777e-05 | 5.14721e-06 | 1(Win) |
| glaze | 4015.34 | 0.55211 | 840.34ms | 4857 | 1280 | 51922.3 | 1153.58 | 1.32437 | 3.32839 | 0.524398 | 0.000207979 | 2.76663e-05 | 1.01336e-05 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2545.57 | 0.0381125 | 1009.59ms | 7376 | 4890 | 5423.95 | 2763.35 | 2.05971 | 8.24871 | 1.34131 | 0.000833494 | 1.35575e-05 | 1.77439e-06 | 1(Win) |
| simdjson (ondemand) | 2173.05 | 0.0523694 | 1059.95ms | 7376 | 2560 | 7356.96 | 3237.06 | 2.39959 | 9.28891 | 1.47994 | 0.000265165 | 3.79715e-05 | 1.43519e-05 | 2(Loss) |
| glaze | 2140.82 | 0.0492455 | 1059.87ms | 7376 | 2560 | 6702.8 | 3285.8 | 2.43931 | 10.1629 | 2.00842 | 0.00108746 | 2.18191e-05 | 6.35507e-06 | 3(Loss) |
| jsonifier | 1951.57 | 0.0770548 | 1093.5ms | 7376 | 640 | 4936.86 | 3604.42 | 2.67582 | 8.93093 | 1.81908 | 0.00221622 | 3.49529e-05 | 1.58877e-05 | 4(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3201.8 | 0.0426524 | 978.665ms | 7376 | 4890 | 4293.88 | 2196.98 | 1.63812 | 6.8788 | 1.024 | 0.000329483 | 1.77994e-05 | 2.66159e-06 | 1(Win) |
| simdjson (ondemand) | 2886 | 0.0732503 | 999.052ms | 7376 | 2560 | 8160.33 | 2437.39 | 1.81668 | 7.56114 | 1.10588 | 0.000618719 | 2.8386e-05 | 8.6323e-06 | 2(Loss) |
| glaze | 2867.89 | 0.0574426 | 1001.64ms | 7376 | 4890 | 9707.19 | 2452.78 | 1.82455 | 8.21285 | 1.57565 | 0.00109122 | 2.03224e-05 | 2.55069e-06 | 3(Loss) |
| jsonifier | 2440.67 | 0.046792 | 1048.12ms | 7376 | 2560 | 4655.94 | 2882.12 | 2.14205 | 7.32402 | 1.45201 | 0.00138032 | 2.9657e-05 | 9.63852e-06 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14827.1 | 0.112927 | 776.367ms | 7376 | 320 | 91.8497 | 474.422 | 0.376928 | 1.22533 | 0.199566 | 0.000135575 | 2.03362e-05 | 5.9314e-06 | 1(Win) |
| glaze | 3246.28 | 0.183345 | 948.522ms | 7376 | 2560 | 40406.2 | 2166.88 | 1.61763 | 3.94536 | 0.707972 | 0.000365628 | 1.95948e-05 | 4.97814e-06 | 2(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 15939.5 | 0.368254 | 772.815ms | 7376 | 4890 | 12915.1 | 441.314 | 0.352238 | 1.18004 | 0.188856 | 0.000135908 | 2.57842e-05 | 7.15303e-06 | 1(Win) |
| glaze | 3487.62 | 0.260474 | 932.405ms | 7376 | 2560 | 70656.5 | 2016.94 | 1.50302 | 3.6128 | 0.632592 | 0.000356519 | 2.5844e-05 | 5.61365e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2449.45 | 0.177781 | 897.312ms | 4390 | 320 | 2954.69 | 1709.21 | 2.16189 | 9.9639 | 1.77153 | 0.00205438 | 2.06435e-05 | 2.84738e-06 | 1(Win) |
| jsonifier (two-stage) | 1826.74 | 0.0560418 | 954.615ms | 4390 | 4890 | 8066.94 | 2291.86 | 2.86002 | 13.3436 | 2.2836 | 0.00271532 | 6.54024e-05 | 1.9658e-05 | 2(Loss) |
| glaze | 1781.79 | 0.0371989 | 960.803ms | 4390 | 4890 | 3735.83 | 2349.68 | 2.94738 | 13.5054 | 2.63326 | 0.00108846 | 1.95182e-05 | 3.21422e-06 | 3(Loss) |
| simdjson (ondemand) | 1402.71 | 0.0393148 | 1027.09ms | 4390 | 4890 | 6733.13 | 2984.68 | 3.71125 | 16.5051 | 2.85331 | 0.000946658 | 4.40674e-05 | 1.87263e-05 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2920.62 | 0.122572 | 890.291ms | 4390 | 40 | 123.487 | 1433.47 | 1.81393 | 8.81344 | 1.49932 | 0.00114465 | 9.68109e-05 | 4.55581e-05 | 1(Win) |
| jsonifier (two-stage) | 2096.26 | 0.0906875 | 949.495ms | 4390 | 2560 | 8397.92 | 1997.19 | 2.51169 | 12.1925 | 2.01139 | 0.00187393 | 5.0541e-05 | 1.26353e-05 | 2(Loss) |
| glaze | 2054.64 | 0.0503072 | 950.368ms | 4390 | 2560 | 2690.02 | 2037.64 | 2.55053 | 12.2021 | 2.34032 | 0.000553815 | 1.98427e-05 | 3.73719e-06 | 3(Loss) |
| simdjson (ondemand) | 1579.55 | 0.0813126 | 1014.67ms | 4390 | 80 | 371.594 | 2650.53 | 3.31291 | 15.056 | 2.53508 | 0.000654897 | 2.56264e-05 | 0 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11287.1 | 0.362198 | 755.463ms | 4390 | 4890 | 8826.05 | 370.922 | 0.508747 | 2.25148 | 0.37631 | 0.000228536 | 4.78872e-05 | 2.79963e-05 | 1(Win) |
| glaze | 3942.99 | 0.250608 | 824.756ms | 4390 | 1280 | 9063.13 | 1061.79 | 1.34158 | 5.38838 | 0.84647 | 0.000471597 | 2.7584e-05 | 3.91515e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12512.1 | 0.073703 | 749.188ms | 4390 | 320 | 19.462 | 334.606 | 0.467832 | 2.12984 | 0.347836 | 0.00022779 | 1.21014e-05 | 0 | 1(Win) |
| glaze | 4178.42 | 0.282681 | 815.606ms | 4390 | 2560 | 20537.1 | 1001.96 | 1.29153 | 4.95558 | 0.749886 | 0.000514397 | 2.7673e-05 | 9.60991e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4066.6 | 0.0620848 | 995.479ms | 11521 | 2560 | 7203.25 | 2701.84 | 1.28275 | 6.0845 | 0.93169 | 0.00120524 | 1.60034e-05 | 5.28925e-06 | 1(Win) |
| jsonifier | 3453.41 | 0.0455727 | 1043.7ms | 11521 | 4890 | 10280.2 | 3181.57 | 1.5074 | 6.48967 | 1.31013 | 0.00279561 | 1.60638e-05 | 5.41378e-06 | 2(Loss) |
| simdjson (ondemand) | 3277.7 | 0.039785 | 1060.9ms | 11521 | 4890 | 8697.4 | 3352.13 | 1.5875 | 7.08638 | 1.12534 | 0.00035305 | 1.33126e-05 | 3.40802e-06 | 3(Loss) |
| glaze | 2782.5 | 0.103606 | 1117.51ms | 11521 | 320 | 5355.88 | 3948.7 | 1.86893 | 8.29242 | 1.63684 | 0.0039919 | 8.6798e-06 | 0 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4540.13 | 0.116002 | 993.949ms | 11521 | 1280 | 10087.6 | 2420.04 | 1.14634 | 5.62503 | 0.823974 | 0.000903988 | 1.02395e-05 | 2.57682e-06 | 1(Win) |
| jsonifier | 3784.25 | 0.0621526 | 1042.52ms | 11521 | 2560 | 8336.43 | 2903.43 | 1.37948 | 6.03012 | 1.2025 | 0.00279205 | 1.5427e-05 | 5.05192e-06 | 2(Loss) |
| simdjson (ondemand) | 3610.31 | 0.0983073 | 1053.3ms | 11521 | 640 | 5728.53 | 3043.31 | 1.44481 | 6.53424 | 1.00408 | 0.000275991 | 6.91672e-06 | 6.7811e-07 | 3(Loss) |
| glaze | 3015.68 | 0.0493664 | 1105.94ms | 11521 | 1280 | 4140.79 | 3643.39 | 1.73056 | 7.76556 | 1.51957 | 0.00426945 | 8.34075e-06 | 1.15279e-06 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 21678.5 | 0.198868 | 769.766ms | 11521 | 1280 | 1300.36 | 506.829 | 0.256713 | 0.969187 | 0.138964 | 8.69336e-05 | 6.1708e-06 | 4.06866e-07 | 1(Win) |
| glaze | 4758.33 | 0.174857 | 955.341ms | 11521 | 640 | 10433.1 | 2309.06 | 1.10166 | 3.79767 | 0.686225 | 0.00125016 | 1.35622e-05 | 3.1193e-06 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 23027.9 | 0.0644155 | 764.671ms | 11521 | 1280 | 120.91 | 477.13 | 0.24265 | 0.940023 | 0.132107 | 8.68658e-05 | 1.17991e-05 | 4.81458e-06 | 1(Win) |
| glaze | 5387.48 | 0.0721761 | 922.217ms | 11521 | 4890 | 10595.1 | 2039.41 | 0.973314 | 3.54362 | 0.629807 | 0.00120926 | 1.08986e-05 | 3.12402e-06 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2757.35 | 0.0991998 | 883.811ms | 4669 | 80 | 205.294 | 1614.85 | 1.91547 | 7.76633 | 1.55686 | 0.00108428 | 2.67723e-05 | 0 | 1(Win) |
| glaze | 2187.77 | 0.0829341 | 922.871ms | 4669 | 160 | 455.861 | 2035.28 | 2.3582 | 9.68923 | 1.72864 | 0.000856714 | 5.35447e-06 | 0 | 2(Loss) |
| jsonifier (two-stage) | 1980.87 | 0.164619 | 946.202ms | 4669 | 320 | 4381.73 | 2247.85 | 2.64442 | 10.9197 | 1.87728 | 0.00124023 | 2.00792e-05 | 3.34654e-06 | 3(Loss) |
| simdjson (ondemand) | 1657.62 | 0.0477346 | 994.444ms | 4669 | 2560 | 4209.05 | 2686.2 | 3.14963 | 13.7289 | 1.97815 | 0.00108763 | 5.04491e-05 | 2.37604e-05 | 4(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3007.22 | 0.054704 | 873.926ms | 4669 | 320 | 209.945 | 1480.67 | 1.75985 | 7.31163 | 1.44656 | 0.00116058 | 1.27169e-05 | 1.33862e-06 | 1(Win) |
| glaze | 2475.68 | 0.178609 | 908.895ms | 4669 | 640 | 6604.56 | 1798.58 | 2.12565 | 8.95074 | 1.5635 | 0.000787106 | 3.34654e-05 | 2.47644e-05 | 2(Loss) |
| jsonifier (two-stage) | 2108.66 | 0.0328432 | 935.736ms | 4669 | 640 | 307.827 | 2111.63 | 2.48963 | 10.4641 | 1.76676 | 0.00122952 | 1.57287e-05 | 3.01189e-06 | 3(Loss) |
| simdjson (ondemand) | 1800.42 | 0.0626571 | 979.072ms | 4669 | 160 | 384.204 | 2473.15 | 2.90901 | 12.9728 | 1.81174 | 0.00122483 | 1.60634e-05 | 0 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12966.6 | 0.16072 | 757.68ms | 4669 | 2560 | 779.789 | 343.399 | 0.443901 | 1.41058 | 0.360463 | 0.000214597 | 4.06605e-05 | 1.99956e-05 | 1(Win) |
| glaze | 3433.01 | 0.215462 | 853.762ms | 4669 | 4890 | 38189.7 | 1297.03 | 1.55752 | 3.22596 | 0.493039 | 0.000225566 | 3.00463e-05 | 1.43662e-05 | 2(Loss) |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14763.6 | 0.148185 | 749.426ms | 4669 | 40 | 7.98974 | 301.6 | 0.401248 | 1.29621 | 0.333904 | 0.000214179 | 2.67723e-05 | 0 | 1(Win) |
| glaze | 3902.6 | 0.421852 | 835.353ms | 4669 | 1280 | 29653.2 | 1140.96 | 1.37439 | 2.7085 | 0.37567 | 0.000221206 | 1.77367e-05 | 1.27169e-05 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3443.81 | 0.12007 | 983.45ms | 9249 | 40 | 378.307 | 2561.28 | 1.51895 | 6.34371 | 1.00011 | 0.000616283 | 1.0812e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 3036.66 | 0.0391337 | 1019.98ms | 9249 | 2560 | 3307.78 | 2904.68 | 1.72271 | 7.56114 | 1.02681 | 0.00064648 | 1.77806e-05 | 6.92642e-06 | 2(Loss) |
| glaze | 2875.08 | 0.0609129 | 1031.52ms | 9249 | 640 | 2235.06 | 3067.93 | 1.81477 | 7.67132 | 1.41226 | 0.00141857 | 8.6158e-06 | 1.85831e-06 | 3(Loss) |
| jsonifier | 2830.46 | 0.0630825 | 1039.99ms | 9249 | 640 | 2473.27 | 3116.28 | 1.85289 | 6.47378 | 1.43248 | 0.00118476 | 1.6049e-05 | 0 | 4(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3638.27 | 0.0546016 | 971.717ms | 9249 | 1280 | 2242.96 | 2424.38 | 1.43885 | 6.11374 | 0.944318 | 0.000651675 | 1.46975e-05 | 3.37874e-07 | 1(Win) |
| simdjson (ondemand) | 3283.31 | 0.0437413 | 1002.29ms | 9249 | 320 | 441.874 | 2686.47 | 1.59258 | 7.17948 | 0.942805 | 0.000653449 | 6.1831e-05 | 3.88556e-05 | 2(Loss) |
| glaze | 3106.23 | 0.121438 | 1014.88ms | 9249 | 160 | 1902.61 | 2839.63 | 1.68305 | 7.29819 | 1.3289 | 0.00143124 | 2.1624e-05 | 9.46048e-06 | 3(Loss) |
| jsonifier | 2941.04 | 0.0979062 | 1032.48ms | 9249 | 40 | 344.881 | 2999.12 | 1.78132 | 6.24403 | 1.37669 | 0.00131095 | 5.40599e-06 | 2.70299e-06 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 23345.6 | 0.1742 | 759.614ms | 9249 | 40 | 17.3276 | 377.825 | 0.247851 | 0.818251 | 0.183047 | 0.00010812 | 5.40599e-06 | 0 | 1(Win) |
| glaze | 4220.49 | 0.241865 | 933.359ms | 9249 | 2560 | 65411 | 2089.93 | 1.2287 | 3.26349 | 0.619202 | 0.000379644 | 1.49087e-05 | 5.40599e-06 | 2(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 25801.4 | 0.0874987 | 755.572ms | 9249 | 80 | 7.15807 | 341.863 | 0.222531 | 0.763001 | 0.170505 | 0.00010812 | 1.8921e-05 | 1.21635e-05 | 1(Win) |
| glaze | 4744.61 | 0.245932 | 913.408ms | 9249 | 1280 | 26756.5 | 1859.06 | 1.11608 | 3.00551 | 0.560709 | 0.000382051 | 4.91607e-05 | 2.99863e-05 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 845.95 | 0.0355886 | 1247ms | 4604 | 4890 | 16684.4 | 5190.28 | 6.13449 | 24.2076 | 5.30148 | 0.00534123 | 0.000136718 | 7.91079e-05 | 1(Win) |
| jsonifier (two-stage) | 748.29 | 0.0621541 | 1316.44ms | 4604 | 4890 | 65039.7 | 5867.66 | 6.90372 | 27.8506 | 5.75369 | 0.00667389 | 5.94753e-05 | 2.47851e-05 | 2(Loss) |
| glaze | 661.177 | 0.0491175 | 1393.32ms | 4604 | 4890 | 52025.4 | 6640.75 | 7.81185 | 33.2111 | 6.91464 | 0.0085094 | 0.000110911 | 5.33456e-05 | 3(Loss) |
| simdjson (ondemand) | 594.28 | 0.0226463 | 1467.56ms | 4604 | 4890 | 13689.7 | 7388.3 | 8.7327 | 36.2439 | 6.70135 | 0.00828265 | 0.000131876 | 6.50719e-05 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1052 | 0.0330455 | 1237.45ms | 4604 | 320 | 608.717 | 4173.69 | 4.94834 | 19.7856 | 4.28997 | 0.00443432 | 3.66529e-05 | 6.78758e-07 | 1(Win) |
| jsonifier (two-stage) | 907.568 | 0.0617831 | 1301.46ms | 4604 | 2560 | 22871.4 | 4837.89 | 5.69704 | 23.6086 | 4.78302 | 0.00518961 | 9.92683e-05 | 5.77792e-05 | 2(Loss) |
| glaze | 782.459 | 0.120439 | 1379.28ms | 4604 | 30 | 1370.25 | 5611.43 | 6.63366 | 28.8158 | 5.8977 | 0.00676948 | 5.79206e-05 | 0 | 3(Loss) |
| simdjson (ondemand) | 678.041 | 0.0443005 | 1474.47ms | 4604 | 4890 | 40242.5 | 6475.6 | 7.61214 | 32.4948 | 5.84854 | 0.00577279 | 9.46096e-05 | 4.1264e-05 | 4(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1370.15 | 0.0462888 | 1043.5ms | 4604 | 4890 | 10759.6 | 3204.56 | 3.79742 | 9.53714 | 0.661165 | 0.000517777 | 3.74885e-05 | 1.18595e-05 | 1(Win) |
| glaze | 859.739 | 0.0551354 | 1241.99ms | 4604 | 1280 | 10148.6 | 5107.03 | 6.13659 | 12.2604 | 1.00239 | 0.000476997 | 4.00467e-05 | 1.23873e-05 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1442.14 | 0.132577 | 1027.98ms | 4604 | 80 | 1303.41 | 3044.57 | 3.68634 | 9.40682 | 0.629887 | 0.000494136 | 2.71503e-05 | 1.35752e-05 | 1(Win) |
| glaze | 863.951 | 0.143094 | 1230.76ms | 4604 | 1280 | 67693 | 5082.14 | 5.97386 | 11.72 | 0.886187 | 0.000572362 | 5.02281e-05 | 1.83265e-05 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3437.09 | 0.0342736 | 1410.64ms | 24579 | 2560 | 13986.4 | 6819.82 | 1.50717 | 6.24871 | 1.11994 | 0.00125108 | 1.44464e-05 | 5.35582e-06 | 1(Win) |
| jsonifier | 2867.32 | 0.0708652 | 1546.92ms | 24579 | 2560 | 85917.6 | 8175 | 1.78797 | 6.60942 | 1.49506 | 0.00203184 | 3.21667e-05 | 2.02472e-05 | 2(Loss) |
| simdjson (ondemand) | 2755.3 | 0.126034 | 1583.13ms | 24579 | 30 | 3448.93 | 8507.37 | 1.87941 | 7.82607 | 1.30172 | 0.00162198 | 9.76443e-05 | 4.06851e-05 | 3(Loss) |
| glaze | 2334.97 | 0.14138 | 1727.92ms | 24579 | 160 | 32230.4 | 10038.8 | 2.21276 | 9.53411 | 1.93755 | 0.00412496 | 1.52569e-05 | 4.83136e-06 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3992.82 | 0.045915 | 1413.91ms | 24579 | 4890 | 35529.2 | 5870.62 | 1.29122 | 5.45502 | 0.938403 | 0.00104199 | 1.28212e-05 | 4.2682e-06 | 1(Win) |
| jsonifier | 3318.82 | 0.0462619 | 1534.25ms | 24579 | 160 | 1708.17 | 7062.87 | 1.56276 | 5.79104 | 1.30803 | 0.00185448 | 9.66272e-06 | 7.1199e-06 | 2(Loss) |
| simdjson (ondemand) | 3140.79 | 0.0556974 | 1586.67ms | 24579 | 160 | 2764.65 | 7463.19 | 1.64979 | 7.10964 | 1.13877 | 0.0015023 | 9.66272e-06 | 1.01713e-06 | 3(Loss) |
| glaze | 2672.1 | 0.117772 | 1716.22ms | 24579 | 30 | 3202.06 | 8772.27 | 1.97369 | 8.70369 | 1.74536 | 0.00381084 | 1.49179e-05 | 8.13703e-06 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6631.38 | 0.0509256 | 1089.58ms | 24579 | 2560 | 8295.32 | 3534.76 | 0.794217 | 1.92689 | 0.123317 | 0.000105448 | 7.94632e-06 | 1.38266e-06 | 1(Win) |
| glaze | 3929.92 | 0.0903818 | 1329.91ms | 24579 | 4890 | 142113 | 5964.59 | 1.31552 | 3.54815 | 0.470687 | 0.000263006 | 1.70645e-05 | 7.63782e-06 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6755.38 | 0.0452579 | 1076.13ms | 24579 | 4890 | 12059.4 | 3469.88 | 0.770735 | 1.90537 | 0.118353 | 9.68872e-05 | 1.19559e-05 | 2.88706e-06 | 1(Win) |
| glaze | 4416.2 | 0.103142 | 1263.13ms | 24579 | 2560 | 76725.6 | 5307.81 | 1.17606 | 3.40327 | 0.43765 | 0.000262308 | 1.63217e-05 | 5.95974e-06 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 947.789 | 0.168372 | 1202.29ms | 4604 | 320 | 19468.8 | 4632.59 | 5.44775 | 22.3273 | 4.91594 | 0.00645431 | 9.02748e-05 | 5.09068e-05 | 1(Win) |
| jsonifier (two-stage) | 802.316 | 0.191881 | 1280.19ms | 4604 | 2560 | 282281 | 5472.55 | 6.36705 | 26.9144 | 5.57776 | 0.0061526 | 0.000115049 | 5.81186e-05 | 2(Loss) |
| glaze | 674.858 | 0.0568029 | 1384.49ms | 4604 | 4890 | 66787.6 | 6506.14 | 7.66712 | 32.8071 | 6.82646 | 0.00891387 | 7.76421e-05 | 2.4563e-05 | 3(Loss) |
| simdjson (ondemand) | 596.776 | 0.0371964 | 1469.71ms | 4604 | 4890 | 36623.4 | 7357.39 | 8.6578 | 35.6171 | 6.55669 | 0.00836278 | 0.000309813 | 0.000160748 | 4(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1201.12 | 0.126078 | 1196.88ms | 4604 | 40 | 849.64 | 3655.53 | 4.33974 | 18.0709 | 3.9407 | 0.00529431 | 0.000195482 | 0.000103171 | 1(Win) |
| jsonifier (two-stage) | 988.648 | 0.14845 | 1262.62ms | 4604 | 320 | 13909.1 | 4441.13 | 5.25823 | 22.6807 | 4.60904 | 0.00512937 | 4.88705e-05 | 1.42539e-05 | 2(Loss) |
| glaze | 790.319 | 0.130482 | 1383.57ms | 4604 | 40 | 2101.98 | 5555.62 | 6.56794 | 28.4726 | 5.82255 | 0.00814509 | 5.97307e-05 | 1.62902e-05 | 3(Loss) |
| simdjson (ondemand) | 669.393 | 0.144849 | 1483.15ms | 4604 | 80 | 7221.53 | 6559.25 | 7.74693 | 32.8389 | 5.91268 | 0.00789802 | 4.61555e-05 | 2.71503e-06 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1358.07 | 0.0455737 | 1052.52ms | 4604 | 2560 | 5557.72 | 3233.06 | 3.8396 | 9.53758 | 0.662902 | 0.000503044 | 3.86043e-05 | 6.10882e-06 | 1(Win) |
| glaze | 830.16 | 0.047106 | 1257.97ms | 4604 | 2560 | 15890.6 | 5289 | 6.29061 | 12.2005 | 0.99696 | 0.000770729 | 2.99502e-05 | 1.12843e-05 | 2(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1386.02 | 0.0442901 | 1043.19ms | 4604 | 4890 | 9626.19 | 3167.86 | 3.74618 | 9.40682 | 0.631625 | 0.000539719 | 4.82376e-05 | 1.04382e-05 | 1(Win) |
| glaze | 795.429 | 0.399535 | 1275.11ms | 4604 | 640 | 311284 | 5519.93 | 6.52517 | 11.7163 | 0.887056 | 0.000784644 | 5.7355e-05 | 1.11995e-05 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3713.42 | 0.0299898 | 1358.56ms | 24579 | 4890 | 17524.2 | 6312.33 | 1.40331 | 6.06778 | 1.08593 | 0.00110478 | 6.90566e-06 | 1.13985e-06 | 1(Win) |
| jsonifier | 3102.99 | 0.0699296 | 1502.37ms | 24579 | 320 | 8929.77 | 7554.12 | 1.69752 | 6.31256 | 1.44699 | 0.00206032 | 9.15416e-06 | 1.52569e-06 | 2(Loss) |
| simdjson (ondemand) | 2803.21 | 0.0598992 | 1574.75ms | 24579 | 4890 | 122679 | 8361.98 | 1.83617 | 7.66525 | 1.26527 | 0.00164618 | 2.4253e-05 | 6.7975e-06 | 3(Loss) |
| glaze | 2332.78 | 0.135818 | 1734.1ms | 24579 | 30 | 5587.51 | 10048.3 | 2.21769 | 9.34155 | 1.89277 | 0.00456352 | 2.98358e-05 | 8.13703e-06 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4354.23 | 0.0926705 | 1368.92ms | 24579 | 40 | 995.515 | 5383.35 | 1.19284 | 5.27475 | 0.904471 | 0.000978478 | 6.10277e-06 | 0 | 1(Win) |
| jsonifier | 3520.96 | 0.0625405 | 1488.79ms | 24579 | 640 | 11094.6 | 6657.38 | 1.47228 | 5.50446 | 1.2621 | 0.00176421 | 1.31591e-05 | 6.86562e-06 | 2(Loss) |
| simdjson (ondemand) | 3091.65 | 0.124987 | 1598.48ms | 24579 | 30 | 2694.01 | 7581.83 | 1.67573 | 7.18852 | 1.15459 | 0.0016803 | 1.89864e-05 | 9.4932e-06 | 3(Loss) |
| glaze | 2528.78 | 0.12627 | 1730.32ms | 24579 | 320 | 43838.8 | 9269.43 | 1.99094 | 8.54543 | 1.71032 | 0.00407068 | 6.86562e-06 | 1.01713e-06 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6896.43 | 0.191662 | 1068.68ms | 24579 | 320 | 13580.1 | 3398.91 | 0.754754 | 1.92445 | 0.123358 | 0.000123581 | 1.36041e-05 | 4.57708e-06 | 1(Win) |
| glaze | 3824.34 | 0.0701835 | 1352.71ms | 24579 | 4890 | 90488.7 | 6129.25 | 1.35563 | 3.55364 | 0.470605 | 0.000322636 | 1.39028e-05 | 3.18659e-06 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 7046.08 | 0.299809 | 1063.03ms | 24579 | 40 | 3979.08 | 3326.72 | 0.740334 | 1.90297 | 0.118394 | 0.000104764 | 1.11884e-05 | 2.03426e-06 | 1(Win) |
| glaze | 3927.1 | 0.0599222 | 1329.57ms | 24579 | 4890 | 62555.8 | 5968.87 | 1.31511 | 3.41031 | 0.437813 | 0.000372514 | 9.56808e-06 | 2.24642e-06 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1023.57 | 0.155409 | 825.988ms | 1181 | 1280 | 3743.05 | 1100.35 | 5.21909 | 20.8611 | 4.28197 | 0.00503678 | 5.22597e-05 | 1.65379e-05 | 1(Win) |
| glaze | 914.245 | 0.0756942 | 836.149ms | 1181 | 2560 | 2226.07 | 1231.93 | 5.82529 | 24.2227 | 4.93988 | 0.00382588 | 7.27667e-05 | 2.48068e-05 | 2(Loss) |
| jsonifier (two-stage) | 892.921 | 0.0622643 | 846.754ms | 1181 | 4890 | 3016.2 | 1261.35 | 5.97172 | 24.3124 | 4.69094 | 0.00254819 | 0.000122249 | 2.83978e-05 | 3(Loss) |
| simdjson (ondemand) | 767.132 | 0.0675217 | 870.68ms | 1181 | 2560 | 2515.86 | 1468.18 | 6.85636 | 29.1109 | 5.07621 | 0.00403293 | 0.00015711 | 4.66369e-05 | 4(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1246.71 | 0.095663 | 823.637ms | 1181 | 4890 | 3652.32 | 903.413 | 4.3106 | 17.6207 | 3.53175 | 0.0040505 | 8.93493e-05 | 3.80946e-05 | 1(Win) |
| glaze | 1234.11 | 0.118114 | 818.881ms | 1181 | 1280 | 1487.32 | 912.63 | 4.37988 | 17.9822 | 3.52752 | 0.00238146 | 3.90294e-05 | 1.52149e-05 | 2(Loss) |
| jsonifier (two-stage) | 1070.21 | 0.173143 | 843.759ms | 1181 | 40 | 132.81 | 1052.4 | 5.02798 | 21.0711 | 3.94073 | 0.00169348 | 6.35055e-05 | 4.2337e-05 | 3(Loss) |
| simdjson (ondemand) | 1002.64 | 0.116625 | 848.984ms | 1181 | 160 | 274.611 | 1123.33 | 5.32897 | 22.8146 | 3.663 | 0.00261431 | 4.76291e-05 | 2.11685e-05 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1317.1 | 0.146102 | 806.753ms | 1181 | 80 | 124.87 | 855.125 | 4.16574 | 8.2718 | 0.890771 | 0.00105843 | 0 | 0 | 1(Win) |
| glaze | 968.664 | 0.208771 | 842.165ms | 1181 | 4890 | 28814 | 1162.72 | 5.47875 | 10.4259 | 0.886538 | 0.00162439 | 2.99562e-05 | 5.7142e-06 | 2(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1347.02 | 0.170177 | 805.801ms | 1181 | 30 | 60.7402 | 836.133 | 4.00751 | 7.82218 | 0.784928 | 0.00084674 | 0.000366921 | 5.64493e-05 | 1(Win) |
| glaze | 983.32 | 0.192596 | 837.377ms | 1181 | 4890 | 23796.5 | 1145.39 | 5.40932 | 9.98984 | 0.788316 | 0.00136188 | 2.7532e-05 | 1.07358e-05 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 1679.3 | 0.142446 | 864.221ms | 2496 | 160 | 652.314 | 1417.48 | 3.15431 | 12.4808 | 2.30008 | 0.003125 | 3.25521e-05 | 0 | 1(Win) |
| simdjson (ondemand) | 1573.87 | 0.0847526 | 872.367ms | 2496 | 1280 | 2103.14 | 1512.43 | 3.3571 | 14.4419 | 2.42628 | 0.00143793 | 2.44141e-05 | 6.88602e-06 | 2(Loss) |
| glaze | 1550.69 | 0.0681341 | 878.758ms | 2496 | 2560 | 2800.32 | 1535.04 | 3.40661 | 14.8429 | 3.09055 | 0.00212308 | 4.22551e-05 | 1.45545e-05 | 3(Loss) |
| jsonifier | 1540.19 | 0.0849222 | 874.626ms | 2496 | 1280 | 2204.91 | 1545.5 | 3.44167 | 13.6326 | 2.92428 | 0.00228115 | 3.06741e-05 | 1.0016e-05 | 4(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2012.54 | 0.137188 | 856.656ms | 2496 | 1280 | 3370.12 | 1182.77 | 2.63466 | 11.4631 | 1.75769 | 0.000873898 | 1.5963e-05 | 7.82502e-06 | 1(Win) |
| glaze | 1974.95 | 0.0506745 | 862.577ms | 2496 | 4890 | 1824.17 | 1205.28 | 2.69559 | 11.8978 | 2.42228 | 0.00201877 | 2.25309e-05 | 8.60272e-06 | 2(Loss) |
| jsonifier (two-stage) | 1963.5 | 0.187386 | 857.951ms | 2496 | 80 | 412.85 | 1212.31 | 2.71399 | 10.9471 | 1.94511 | 0.00213341 | 9.01442e-05 | 2.50401e-05 | 3(Loss) |
| jsonifier | 1777.66 | 0.0990487 | 871.023ms | 2496 | 160 | 281.457 | 1339.05 | 2.99302 | 12.0994 | 2.56931 | 0.00178786 | 2.50401e-05 | 7.51202e-06 | 4(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4096.32 | 0.245298 | 782.698ms | 2496 | 80 | 162.547 | 581.1 | 1.3222 | 3.98518 | 0.403045 | 0.000470753 | 4.00641e-05 | 2.00321e-05 | 1(Win) |
| glaze | 1594.49 | 0.179875 | 876.325ms | 2507 | 4890 | 35572.7 | 1499.45 | 3.32426 | 7.02673 | 0.888712 | 0.000804618 | 3.53203e-05 | 1.23172e-05 | 2(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4378.7 | 0.150566 | 774.995ms | 2496 | 640 | 428.776 | 543.625 | 1.26668 | 3.85216 | 0.371795 | 0.000408779 | 7.51202e-06 | 2.50401e-06 | 1(Win) |
| glaze | 1764.48 | 0.207588 | 858.979ms | 2507 | 640 | 5063.64 | 1355 | 3.01921 | 6.29318 | 0.724772 | 0.000820827 | 1.62046e-05 | 0 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2270.16 | 0.174119 | 927.176ms | 4926 | 30 | 389.482 | 2069.37 | 2.31218 | 10.2136 | 1.78664 | 0.00412099 | 3.38341e-05 | 6.76682e-06 | 1(Win) |
| jsonifier (two-stage) | 1783.39 | 0.13522 | 983.511ms | 4926 | 640 | 8120.06 | 2634.2 | 2.89215 | 12.8691 | 2.20219 | 0.00401949 | 2.37896e-05 | 6.0267e-06 | 2(Loss) |
| glaze | 1413.93 | 0.176841 | 1056.67ms | 4926 | 80 | 2761.77 | 3322.51 | 3.68862 | 15.5278 | 3.0406 | 0.00251726 | 3.29882e-05 | 1.01502e-05 | 3(Loss) |
| simdjson (ondemand) | 1169.73 | 0.069063 | 1126.89ms | 4926 | 1280 | 9847.29 | 4016.13 | 4.44509 | 16.9762 | 2.95615 | 0.00410101 | 0.000117679 | 5.7888e-05 | 4(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2862.38 | 0.0662487 | 924.728ms | 4926 | 4890 | 5780.93 | 1641.22 | 1.84348 | 8.55461 | 1.40236 | 0.00323682 | 4.28427e-05 | 1.33261e-05 | 1(Win) |
| jsonifier (two-stage) | 2181.56 | 0.0775946 | 985.969ms | 4926 | 160 | 446.722 | 2153.41 | 2.40813 | 11.2099 | 1.8179 | 0.00351451 | 2.79131e-05 | 2.53756e-06 | 2(Loss) |
| glaze | 1816.9 | 0.0595265 | 1021.53ms | 4926 | 2560 | 6064.4 | 2585.62 | 2.86587 | 12.8534 | 2.44864 | 0.00201228 | 2.48205e-05 | 6.34389e-06 | 3(Loss) |
| simdjson (ondemand) | 1450.67 | 0.131034 | 1076.17ms | 4926 | 320 | 5761.9 | 3238.36 | 3.59429 | 14.3747 | 2.38429 | 0.0038463 | 3.67946e-05 | 1.96661e-05 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11935.4 | 0.149658 | 758.665ms | 4926 | 320 | 111.036 | 393.603 | 0.475889 | 1.9052 | 0.333536 | 0.000203639 | 1.52253e-05 | 5.7095e-06 | 1(Win) |
| glaze | 3575.88 | 0.162262 | 849.704ms | 4926 | 2560 | 11633.2 | 1313.75 | 1.48856 | 6.01056 | 0.977873 | 0.000253993 | 3.06093e-05 | 1.04674e-05 | 2(Loss) |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13707.2 | 0.241901 | 747.943ms | 4926 | 80 | 54.9867 | 342.725 | 0.421823 | 1.7838 | 0.305116 | 0.000220767 | 0.000109115 | 5.07511e-05 | 1(Win) |
| glaze | 3959.43 | 0.156497 | 836.671ms | 4926 | 4890 | 16859.4 | 1186.48 | 1.34395 | 5.49858 | 0.867235 | 0.00031858 | 1.1707e-05 | 2.36631e-06 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3225.56 | 0.0297164 | 1007.46ms | 9463 | 2560 | 1769.62 | 2797.84 | 1.62001 | 7.36426 | 1.1713 | 0.00200782 | 2.84414e-05 | 1.02372e-05 | 1(Win) |
| jsonifier | 2574.09 | 0.0554092 | 1074.54ms | 9463 | 2560 | 9660.79 | 3505.94 | 2.01421 | 7.95551 | 1.57836 | 0.00264311 | 1.7007e-05 | 5.07734e-06 | 2(Loss) |
| simdjson (ondemand) | 2122.7 | 0.11391 | 1153.24ms | 9463 | 80 | 1876.28 | 4251.49 | 2.45032 | 9.43908 | 1.56768 | 0.0020633 | 6.20839e-05 | 3.43443e-05 | 3(Loss) |
| glaze | 2073.11 | 0.0813558 | 1163.9ms | 9463 | 160 | 2006.83 | 4353.18 | 2.5087 | 10.9729 | 2.13886 | 0.00225682 | 1.58512e-05 | 0 | 4(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3803.43 | 0.0494287 | 1006.7ms | 9463 | 4890 | 6726.25 | 2372.76 | 1.38055 | 6.5006 | 0.971261 | 0.00177065 | 1.57324e-05 | 3.78182e-06 | 1(Win) |
| jsonifier | 2967.49 | 0.0453977 | 1067.85ms | 9463 | 4890 | 9320.86 | 3041.16 | 1.76354 | 7.09173 | 1.37821 | 0.00238855 | 1.4587e-05 | 3.34961e-06 | 2(Loss) |
| simdjson (ondemand) | 2608 | 0.178964 | 1106.45ms | 9463 | 320 | 12272.2 | 3460.36 | 2.002 | 8.06182 | 1.26535 | 0.00206132 | 1.91535e-05 | 9.24654e-06 | 3(Loss) |
| glaze | 2464.74 | 0.108296 | 1129.22ms | 9463 | 640 | 10062.8 | 3661.49 | 2.1123 | 9.57963 | 1.8306 | 0.00264963 | 1.15582e-05 | 2.80699e-06 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 20441.6 | 0.146611 | 763.851ms | 9463 | 2560 | 1072.51 | 441.484 | 0.275974 | 1.11223 | 0.172778 | 0.000105799 | 1.03611e-05 | 6.02676e-06 | 1(Win) |
| glaze | 4010 | 0.111146 | 950.24ms | 9463 | 2560 | 16017.7 | 2250.53 | 1.30741 | 4.76699 | 0.876783 | 0.000382328 | 2.80286e-05 | 1.08151e-05 | 2(Loss) |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22810.9 | 0.0458513 | 756.387ms | 9463 | 2560 | 84.2399 | 395.628 | 0.248757 | 1.05205 | 0.15884 | 0.000106088 | 1.04024e-05 | 4.04536e-06 | 1(Win) |
| glaze | 4743.84 | 0.127225 | 914.882ms | 9463 | 4890 | 28645.1 | 1902.39 | 1.11102 | 4.44933 | 0.803339 | 0.000266002 | 9.96238e-06 | 3.43605e-06 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 5430.96 | 0.27606 | 772.708ms | 2821 | 30 | 56.1023 | 495.367 | 1.04605 | 4.20489 | 0.470755 | 0.000354484 | 2.36323e-05 | 0 | 1(Win) |
| jsonifier (two-stage) | 5359.43 | 0.0865688 | 769.994ms | 2821 | 640 | 120.857 | 501.978 | 1.05529 | 3.93158 | 0.531372 | 0.00090615 | 1.82781e-05 | 5.53882e-06 | 2(Loss) |
| jsonifier | 5239.85 | 0.195325 | 770.23ms | 2821 | 4890 | 4918.06 | 513.433 | 1.06233 | 3.93158 | 0.531372 | 0.000874539 | 1.98627e-05 | 6.59674e-06 | 3(Loss) |
| glaze | 3305.6 | 0.336609 | 801.2ms | 2821 | 30 | 225.154 | 813.867 | 1.66183 | 6.52038 | 1.20489 | 0.000389933 | 0 | 0 | 4(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 5840.81 | 0.16108 | 764.659ms | 2821 | 160 | 88.0767 | 460.606 | 0.960907 | 3.77951 | 0.496278 | 0.000409872 | 1.10776e-05 | 2.21553e-06 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 5839.13 | 0.0652498 | 768.715ms | 2821 | 640 | 57.8426 | 460.739 | 0.957968 | 3.77951 | 0.496278 | 0.000356146 | 4.43105e-06 | 0 | 1(Tie) |
| simdjson (ondemand) | 5599.72 | 0.0770572 | 769.605ms | 2821 | 320 | 43.8582 | 480.438 | 0.998929 | 4.12159 | 0.451967 | 0.000360023 | 2.43708e-05 | 2.21553e-06 | 3(Loss) |
| glaze | 3281.86 | 0.175377 | 801.521ms | 2821 | 4890 | 10106.9 | 819.753 | 1.65132 | 6.43885 | 1.18646 | 0.000432413 | 1.98627e-05 | 8.84398e-06 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 6872.61 | 0.128689 | 782.469ms | 4147 | 160 | 87.7465 | 575.456 | 0.801139 | 3.26405 | 0.338799 | 0.000566675 | 3.9185e-05 | 9.04268e-06 | 1(Win) |
| jsonifier | 6686.77 | 0.189818 | 784.153ms | 4147 | 80 | 100.833 | 591.45 | 0.820747 | 3.22932 | 0.379069 | 0.000247167 | 1.50711e-05 | 6.02845e-06 | 2(Loss) |
| jsonifier (two-stage) | 6631.6 | 0.374706 | 782.721ms | 4147 | 4890 | 24418.7 | 596.37 | 0.83373 | 3.22932 | 0.379069 | 0.000249225 | 2.06126e-05 | 4.53675e-06 | 3(Loss) |
| glaze | 4023.88 | 0.178794 | 814.868ms | 4147 | 4890 | 15100.5 | 982.854 | 1.3415 | 5.59151 | 1.05329 | 0.00035219 | 1.17857e-05 | 2.367e-06 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 7088.94 | 0.340525 | 781.944ms | 4147 | 2560 | 9239.42 | 557.895 | 0.776103 | 3.20738 | 0.326019 | 0.000242457 | 1.36582e-05 | 2.63745e-06 | 1(Win) |
| jsonifier (two-stage) | 7026.83 | 0.26058 | 781.365ms | 4147 | 1280 | 2753.22 | 562.827 | 0.790848 | 3.12587 | 0.355197 | 0.000279193 | 8.85429e-06 | 2.82584e-06 | 2(Loss) |
| jsonifier | 6987.09 | 0.123866 | 777.923ms | 4147 | 640 | 314.6 | 566.028 | 0.790673 | 3.12587 | 0.355197 | 0.000369996 | 1.20569e-05 | 5.65168e-06 | 3(Loss) |
| glaze | 4050.31 | 0.0495983 | 815.993ms | 4147 | 4890 | 1146.92 | 976.441 | 1.322 | 5.53581 | 1.04075 | 0.000326252 | 1.09967e-05 | 2.95875e-06 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 2563.09 | 0.100019 | 826.809ms | 2821 | 4890 | 5389.6 | 1049.64 | 2.08363 | 8.49061 | 1.46118 | 0.000670113 | 4.53073e-05 | 8.55402e-06 | 1(Win) |
| jsonifier | 2517.53 | 0.226185 | 838.323ms | 2821 | 4890 | 28569 | 1068.63 | 2.11759 | 6.45941 | 1.12301 | 0.00213227 | 5.50937e-05 | 1.49333e-05 | 2(Loss) |
| simdjson (ondemand) | 2264.29 | 0.107414 | 844.203ms | 2821 | 1280 | 2084.86 | 1188.15 | 2.33633 | 8.8458 | 1.23999 | 0.000361685 | 6.84044e-05 | 1.66164e-05 | 3(Loss) |
| jsonifier (two-stage) | 2241.39 | 0.0592338 | 848.422ms | 2821 | 4890 | 2471.83 | 1200.29 | 2.35946 | 8.20773 | 1.28217 | 0.000714188 | 7.32891e-05 | 1.89928e-05 | 4(Loss) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2842.61 | 0.407788 | 831.453ms | 2821 | 1280 | 19065.6 | 946.425 | 1.88537 | 5.87699 | 0.978023 | 0.00178045 | 4.18181e-05 | 1.60626e-05 | 1(Win) |
| glaze | 2767.92 | 0.103774 | 830.774ms | 2821 | 2560 | 2604.45 | 971.962 | 1.9315 | 7.99504 | 1.33676 | 0.000377886 | 2.28476e-05 | 1.3847e-06 | 2(Loss) |
| jsonifier (two-stage) | 2591.15 | 0.0448614 | 836.266ms | 2821 | 1280 | 277.7 | 1038.27 | 2.0807 | 7.50585 | 1.11273 | 0.000354484 | 3.68331e-05 | 1.66164e-06 | 3(Loss) |
| simdjson (ondemand) | 2466.22 | 0.223153 | 843.085ms | 2821 | 30 | 177.775 | 1090.87 | 2.1724 | 8.44559 | 1.14002 | 0.000531726 | 7.08968e-05 | 1.18161e-05 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 8301.52 | 0.148084 | 758.682ms | 2821 | 80 | 18.4247 | 324.075 | 0.710869 | 1.61468 | 0.257356 | 0.000354484 | 2.65863e-05 | 0 | 1(Win) |
| glaze | 4640.69 | 0.643559 | 781.862ms | 2819 | 2560 | 35583 | 579.312 | 1.18982 | 3.06279 | 0.479603 | 0.000362911 | 4.03235e-05 | 1.71825e-05 | 2(Loss) |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9289.56 | 0.15296 | 751.261ms | 2821 | 160 | 31.3974 | 289.606 | 0.631398 | 1.43495 | 0.215881 | 0.000354484 | 2.65863e-05 | 0 | 1(Win) |
| glaze | 5424.41 | 1.18682 | 770.622ms | 2819 | 1280 | 44286 | 495.613 | 1.02188 | 2.53601 | 0.367152 | 0.00035529 | 5.48732e-05 | 3.21479e-05 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 3134.87 | 0.0979243 | 852.499ms | 4147 | 1280 | 1953.53 | 1261.58 | 1.69196 | 6.42151 | 0.86207 | 0.000385633 | 1.92157e-05 | 6.9704e-06 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3127.57 | 0.10339 | 850.684ms | 4147 | 160 | 273.484 | 1264.53 | 1.70169 | 6.18037 | 0.902821 | 0.000482276 | 4.67205e-05 | 2.10996e-05 | 1(Tie) |
| glaze | 2957.23 | 0.150481 | 855.283ms | 4147 | 80 | 324.006 | 1337.36 | 1.83568 | 7.60912 | 1.33349 | 0.000696286 | 2.10996e-05 | 3.01423e-06 | 3(Loss) |
| jsonifier | 2438.09 | 0.0727969 | 891.439ms | 4147 | 80 | 111.554 | 1622.12 | 2.16596 | 6.13118 | 1.17796 | 0.000723415 | 3.9185e-05 | 3.01423e-06 | 4(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3529.39 | 0.0743117 | 843.28ms | 4147 | 1280 | 887.548 | 1120.56 | 1.51323 | 5.64191 | 0.775501 | 0.000242834 | 3.99385e-05 | 1.24337e-05 | 1(Win) |
| simdjson (ondemand) | 3378.8 | 0.184279 | 852.07ms | 4147 | 40 | 186.103 | 1170.5 | 1.5771 | 6.14878 | 0.794068 | 0.000446106 | 1.20569e-05 | 0 | 2(Loss) |
| glaze | 3084.64 | 0.0738765 | 856.367ms | 4147 | 4890 | 4387.13 | 1282.12 | 1.72671 | 7.272 | 1.24885 | 0.000657434 | 3.48146e-05 | 1.50403e-05 | 3(Loss) |
| jsonifier | 2689.16 | 0.105827 | 883.004ms | 4147 | 40 | 96.8917 | 1470.67 | 2.00887 | 5.73427 | 1.07933 | 0.000482276 | 1.20569e-05 | 0 | 4(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11150.9 | 0.123026 | 761.637ms | 4147 | 160 | 30.4619 | 354.669 | 0.51337 | 1.15312 | 0.175307 | 0.000241138 | 1.05498e-05 | 0 | 1(Win) |
| glaze | 4108.02 | 0.249515 | 827.341ms | 4145 | 2560 | 14757.7 | 962.259 | 1.30156 | 3.34065 | 0.606514 | 0.000243328 | 3.19474e-05 | 7.35072e-06 | 2(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12826.9 | 1.08754 | 754.828ms | 4147 | 1280 | 14392.1 | 308.327 | 0.453349 | 1.03641 | 0.1483 | 0.000241327 | 1.13034e-05 | 3.95617e-06 | 1(Win) |
| glaze | 4912.29 | 0.316461 | 810.02ms | 4145 | 4890 | 31712.5 | 804.712 | 1.09799 | 2.78191 | 0.479855 | 0.000243277 | 1.52449e-05 | 4.14425e-06 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3683.54 | 0.188387 | 6580.06ms | 466906 | 2560 | 1.32761e+08 | 120883 | 1.3878 | 6.16682 | 0.824173 | 0.00360098 | 0.00140947 | 1.50843e-05 | 1(Win) |
| glaze | 2895.13 | 0.252268 | 8250.13ms | 466906 | 1280 | 1.92689e+08 | 153802 | 1.77025 | 7.42684 | 1.5035 | 0.00246125 | 0.00139319 | 2.31912e-05 | 2(Loss) |
| simdjson (ondemand) | 1354.02 | 0.211358 | 8723.79ms | 466906 | 80 | 3.86489e+07 | 328855 | 3.77007 | 15.024 | 2.43166 | 0.00838193 | 0.0720383 | 0.000177364 | 3(Loss) |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3738.87 | 0.074045 | 6573ms | 466906 | 80 | 622101 | 119094 | 1.37665 | 6.16566 | 0.823916 | 0.00362303 | 0.00120584 | 1.33324e-05 | 1(Win) |
| glaze | 2940.07 | 0.0552761 | 8212.65ms | 466906 | 320 | 2.24269e+06 | 151451 | 1.74786 | 7.42571 | 1.50325 | 0.00239058 | 0.00126957 | 1.26966e-05 | 2(Loss) |
| simdjson (ondemand) | 1311.06 | 0.508694 | 8888.57ms | 466906 | 1280 | 3.82062e+09 | 339630 | 3.88394 | 15.0239 | 2.43166 | 0.00839404 | 0.0933628 | 0.000348851 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4761.63 | 0.138525 | 7686.98ms | 699405 | 40 | 1.50613e+06 | 140079 | 1.08113 | 4.01735 | 0.644058 | 0.00547912 | 0.000860088 | 5.54042e-06 | 1(Win) |
| glaze | 3997.18 | 0.0710025 | 8974.21ms | 699405 | 40 | 561511 | 166869 | 1.28764 | 4.84003 | 1.13546 | 0.00190998 | 0.00197679 | 3.864e-05 | 2(Loss) |
| simdjson (ondemand) | 1438.52 | 0.659494 | 6560.86ms | 767297 | 640 | 7.20267e+09 | 508682 | 3.53522 | 13.9013 | 2.23378 | 0.0115941 | 0.0709623 | 0.000123701 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4679.95 | 0.253596 | 7703.78ms | 699405 | 1280 | 1.67214e+08 | 142524 | 1.09111 | 4.01683 | 0.64395 | 0.00544691 | 0.000882008 | 1.8089e-05 | 1(Win) |
| glaze | 4016.61 | 0.129469 | 8980.79ms | 699405 | 80 | 3.69794e+06 | 166061 | 1.28147 | 4.83925 | 1.13529 | 0.00190657 | 0.0019221 | 4.89523e-05 | 2(Loss) |
| simdjson (ondemand) | 1479.17 | 0.63251 | 6568ms | 767297 | 40 | 3.91639e+08 | 494704 | 3.44882 | 13.9011 | 2.23373 | 0.011507 | 0.0784838 | 0.000120227 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3764.28 | 0.160183 | 8593.72ms | 631514 | 320 | 2.10176e+07 | 159993 | 1.34735 | 7.02621 | 1.20741 | 0.00305454 | 1.09855e-06 | 2.96906e-07 | 1(Win) |
| glaze | 2678.24 | 0.0961096 | 5982.86ms | 631514 | 80 | 3.73672e+06 | 224871 | 1.92236 | 8.57774 | 1.52634 | 0.00206706 | 2.27628e-06 | 1.34597e-06 | 2(Loss) |
