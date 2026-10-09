# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 15, 2026)
#### Using the following commits:
----
| Jsonifier: [3b56371](https://github.com/nihilai-collective/jsonifier/commit/3b56371)  
| Glaze: [5520fb0](https://github.com/stephenberry/glaze/commit/5520fb0)  
| Simdjson: [9c00353](https://github.com/simdjson/simdjson/commit/9c00353)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `NEON` |
| simdjson (ondemand) | `arm64` |
| simdjson (reflection) | `arm64` |
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

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

`simdjson (ondemand)` results include this harness's field-mapping layer (per-field lookups, string copies and `unescaped_key()` for maps, in `include/common.hpp`), since materializing into the shared test structs is what these tests measure; hand-tuned glue written by a simdjson specialist could perform differently.

`Results.csv` additionally carries `jsonifier (combined)` and `simdjson (combined)` summary rows. Each is a best-of-variants tally: per test, only the better-ranked of that library's two variants counts, and a test counts as a win when that position is 1 and no other library shares it, so two variants of the same library tying for first count as one win. These rows are not independent results and should not be summed with the per-variant rows.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ae63a25](https://github.com/nihilai-collective/benchmarksuite/commit/ae63a25).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1502.57 | 3.43264 | 58.2541ms | 905 | 640 | 248809 | 574.4 | 0.27933 | 1(Win) | true |
| glaze | 1231.56 | 5.23755 | 82.27ms | 905 | 160 | 215558 | 700.8 | 1.86047 | 2(Loss) | true |
| jsonifier (two-stage) | 227.484 | 0.337534 | 384.26ms | 905 | 1280 | 209914 | 3794 | 0.126356 | 3(Loss) | true |
| simdjson (ondemand) | 201.653 | 0.333707 | 433.951ms | 905 | 2560 | 522226 | 4280 | 0.116686 | 4(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| glaze STATISTICAL TIE | 1633.07 | 1.87697 | 55.7491ms | 905 | 2560 | 251909 | 528.5 | 0.28463 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 1611.07 | 1.34989 | 55.9209ms | 905 | 4890 | 255724 | 535.715 | 1.40362 | 1(Tie) | true |
| jsonifier (two-stage) | 235.35 | 0.380538 | 373.193ms | 905 | 1280 | 249273 | 3667.2 | 0.108956 | 3(Loss) | true |
| simdjson (ondemand) | 197.112 | 0.583839 | 440.284ms | 905 | 1280 | 836503 | 4378.6 | 0.16929 | 4(Loss) | true |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1932.98 | 2.43205 | 45.9149ms | 905 | 2560 | 301876 | 446.5 | 1.33908 | 1(Win) | true |
| simdjson (reflection) | 214.343 | 0.136095 | 411.469ms | 905 | 2560 | 76877.7 | 4026.6 | 0.597413 | 2(Loss) | true |
| glaze | 117.94 | 0.145389 | 744.801ms | 905 | 2560 | 289784 | 7317.9 | 0.0205019 | 3(Loss) | true |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3205.54 | 2.37812 | 37.25ms | 905 | 4890 | 200481 | 269.245 | 0.992119 | 1(Win) | true |
| simdjson (reflection) | 2335.16 | 2.59338 | 47.6749ms | 905 | 2560 | 235200 | 369.6 | 0.269833 | 2(Loss) | true |
| glaze | 812.383 | 0.669341 | 127.561ms | 905 | 1280 | 64726.4 | 1062.4 | 0.598802 | 3(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 947.813 | 0.651551 | 185.959ms | 1811 | 1280 | 180426 | 1822.2 | 0.0767712 | 1(Win) | true |
| glaze | 818.173 | 0.240505 | 212.101ms | 1811 | 4890 | 126039 | 2110.93 | 1.98207 | 2(Loss) | true |
| jsonifier (two-stage) | 314.156 | 1.78791 | 579.95ms | 1811 | 40 | 386452 | 5497.6 | 0.116279 | 3(Loss) | true |
| simdjson (ondemand) | 155.472 | 0.087623 | 1132.58ms | 1811 | 2560 | 242555 | 11108.8 | 0.217372 | 4(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1131.32 | 0.482396 | 156.935ms | 1811 | 4890 | 265206 | 1526.63 | 0.558296 | 1(Win) | true |
| glaze | 993.159 | 0.721097 | 177.644ms | 1811 | 1280 | 201278 | 1739 | 0.195898 | 2(Loss) | true |
| jsonifier (two-stage) | 355.914 | 0.124057 | 507.527ms | 1811 | 4890 | 177215 | 4852.59 | 0.512807 | 3(Loss) | true |
| simdjson (ondemand) | 158.881 | 0.388381 | 1144.97ms | 1811 | 80 | 142593 | 10870.4 | 0.0294291 | 4(Loss) | true |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 282.934 | 0.787662 | 675.31ms | 1997 | 160 | 449764 | 6731.2 | 0.262154 | 1(Win) | true |
| jsonifier | 262.364 | 0.194918 | 662.454ms | 1811 | 4890 | 805090 | 6582.86 | 0.119614 | 2(Loss) | true |
| glaze | 200.569 | 0.138951 | 863.853ms | 1798 | 2560 | 361253 | 8549.2 | 0.0888182 | 3(Loss) | true |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 815.095 | 0.336923 | 225.99ms | 1811 | 2560 | 130474 | 2118.9 | 0.474401 | 1(Win) | true |
| simdjson (reflection) | 668.758 | 0.512407 | 297.021ms | 1997 | 1280 | 272558 | 2847.8 | 0.6432 | 2(Loss) | true |
| glaze | 465.497 | 0.385308 | 388.301ms | 1798 | 1280 | 257852 | 3683.6 | 0.108472 | 3(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2230.45 | 0.428578 | 168.806ms | 3862 | 4890 | 244911 | 1651.28 | 0.585278 | 1(Win) | true |
| glaze | 1315.11 | 0.432108 | 287.721ms | 3862 | 1280 | 187455 | 2800.6 | 0.107235 | 2(Loss) | true |
| jsonifier (two-stage) | 648.705 | 0.191905 | 572.304ms | 3862 | 2560 | 303908 | 5677.6 | 0.378346 | 3(Loss) | true |
| simdjson (ondemand) | 470.975 | 0.0913625 | 804.049ms | 3862 | 4890 | 249617 | 7820.15 | 0.322586 | 4(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2739.91 | 0.517119 | 141.222ms | 3862 | 4890 | 236288 | 1344.24 | 0.361026 | 1(Win) | true |
| glaze | 1495.85 | 0.591926 | 250.735ms | 3862 | 1280 | 271889 | 2462.2 | 0.252443 | 2(Loss) | true |
| jsonifier (two-stage) | 656.153 | 0.138242 | 570.436ms | 3862 | 4890 | 294443 | 5613.15 | 0.0168616 | 3(Loss) | true |
| simdjson (ondemand) | 482.775 | 0.221609 | 771.251ms | 3862 | 1280 | 365864 | 7629 | 0.0445867 | 4(Loss) | true |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 745.879 | 0.133852 | 500.975ms | 3862 | 4890 | 213622 | 4937.92 | 0.157295 | 1(Win) | true |
| jsonifier | 691.115 | 0.394461 | 541.859ms | 3862 | 640 | 282821 | 5329.2 | 0.444813 | 2(Loss) | true |
| glaze | 502.459 | 1.38572 | 807.87ms | 3862 | 30 | 309526 | 7330.13 | 0.116279 | 3(Loss) | true |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3686.04 | 0.190971 | 113.132ms | 3862 | 2560 | 9321.4 | 999.2 | 0 | 1(Win) | true |
| simdjson (reflection) | 3018.01 | 0.506391 | 138.311ms | 3862 | 4890 | 186751 | 1220.37 | 0.255711 | 2(Loss) | true |
| glaze | 2096.2 | 0.413598 | 194.836ms | 3862 | 4890 | 258240 | 1757.03 | 0.252712 | 3(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1187.3 | 0.146557 | 779.596ms | 9578 | 4890 | 621656 | 7693.35 | 0.415711 | 1(Win) | true |
| glaze | 1036.32 | 0.271027 | 893.109ms | 9578 | 1280 | 730468 | 8814.2 | 0.0976651 | 2(Loss) | true |
| simdjson (ondemand) | 770.644 | 0.490326 | 1236.6ms | 9578 | 40 | 135105 | 11852.8 | 0.144196 | 3(Loss) | true |
| jsonifier (two-stage) | 707.997 | 0.209462 | 1303.8ms | 9578 | 640 | 467387 | 12901.6 | 0.0310135 | 4(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1985.38 | 0.177259 | 737.743ms | 9578 | 4890 | 325228 | 4600.78 | 0.841082 | 1(Win) | true |
| glaze | 1543.16 | 0.306392 | 847.195ms | 9578 | 640 | 210504 | 5919.2 | 0.242686 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 932.527 | 0.229587 | 1329.67ms | 9578 | 640 | 323670 | 9795.2 | 0.382394 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 931.31 | 1.01259 | 1352.03ms | 9578 | 80 | 789076 | 9808 | 0.55159 | 3(Tie) | true |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1208.56 | 0.224271 | 763.82ms | 9578 | 1280 | 367765 | 7558 | 0.221788 | 1(Win) | true |
| simdjson (reflection) | 1167.66 | 0.144606 | 779.595ms | 9578 | 4890 | 625740 | 7822.71 | 0.426277 | 2(Loss) | true |
| glaze | 1014.62 | 0.19679 | 909.793ms | 9578 | 30 | 9416.09 | 9002.67 | 0 | 3(Loss) | true |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 9684.36 | 1.43444 | 105.243ms | 9578 | 320 | 58576 | 943.2 | 1.63793 | 1(Win) | true |
| jsonifier | 8602.67 | 0.375643 | 121.561ms | 9578 | 4890 | 77793.3 | 1061.8 | 3.27066 | 2(Loss) | true |
| glaze | 4737.7 | 0.80122 | 212.512ms | 9578 | 320 | 76360.2 | 1928 | 0.249584 | 3(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1922.54 | 0.931838 | 176.591ms | 3873 | 640 | 205119 | 1921.2 | 0.805452 | 1(Win) | true |
| glaze | 1346.06 | 2.10539 | 264.653ms | 3873 | 320 | 1.06803e+06 | 2744 | 1.54994 | 2(Loss) | true |
| jsonifier (two-stage) | 529.956 | 0.704927 | 692.096ms | 3873 | 320 | 772421 | 6969.6 | 0.368664 | 3(Loss) | true |
| simdjson (ondemand) | 413.104 | 0.160487 | 876.115ms | 3873 | 4890 | 1.00685e+06 | 8941.05 | 0.444843 | 4(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 2491.29 | 0.95951 | 149.881ms | 3873 | 1280 | 259034 | 1482.6 | 5.2046 | -(Win) | false |
| glaze | 1616.02 | 0.597151 | 230.906ms | 3873 | 1280 | 238440 | 2285.6 | 0.298403 | 2(Loss) | true |
| jsonifier (two-stage) | 593.671 | 1.56312 | 575.525ms | 3873 | 320 | 3.02649e+06 | 6221.6 | 0.322497 | 3(Loss) | true |
| simdjson (ondemand) | 436.717 | 0.435747 | 854.698ms | 3873 | 320 | 434623 | 8457.6 | 0.207665 | 4(Loss) | true |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 684.706 | 0.400364 | 547.362ms | 3873 | 640 | 298521 | 5394.4 | 0.17828 | 1(Win) | true |
| simdjson (reflection) | 668.824 | 1.01912 | 600.259ms | 3873 | 2560 | 8.10886e+06 | 5522.5 | 0.276283 | 2(Loss) | true |
| glaze | 492.005 | 0.382165 | 746.032ms | 3873 | 640 | 526790 | 7507.2 | 0.180832 | 3(Loss) | true |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2958.2 | 0.87215 | 139.555ms | 3873 | 4890 | 579869 | 1248.59 | 2.56193 | 1(Win) | true |
| simdjson (reflection) | 2792.24 | 1.5288 | 156.352ms | 3873 | 1280 | 523480 | 1322.8 | 1.3174 | 2(Loss) | true |
| glaze | 2299.35 | 0.474487 | 180.34ms | 3873 | 4890 | 284082 | 1606.36 | 0.0708718 | 3(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 625.661 | 0.772732 | 10071.5ms | 2090234 | 40 | 2.42454e+10 | 3.18607e+06 | 2.50829 | 1(Win) | true |
| jsonifier (two-stage) | 567.815 | 0.643496 | 6025.42ms | 2090234 | 40 | 2.0414e+10 | 3.51066e+06 | 3.62785 | 2(Loss) | true |
| simdjson (reflection) | 524.902 | 0.341258 | 6263.63ms | 2090234 | 30 | 5.03872e+09 | 3.79767e+06 | 2.26055 | 3(Loss) | true |
| glaze | 467.359 | 0.345949 | 6477.91ms | 2090234 | 40 | 8.70908e+09 | 4.26525e+06 | 0.125549 | 4(Loss) | true |
| simdjson (ondemand) | 412.917 | 0.305837 | 7611.51ms | 2090234 | 80 | 1.74396e+10 | 4.82761e+06 | 2.74413 | 5(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 808.25 | 0.350491 | 9752.94ms | 2090234 | 80 | 5.97781e+09 | 2.46632e+06 | 0.0356934 | 1(Win) | true |
| jsonifier (two-stage) | 681.029 | 1.03132 | 5815.41ms | 2090234 | 30 | 2.7338e+10 | 2.92704e+06 | 4.11023 | 2(Loss) | true |
| simdjson (reflection) | 569.809 | 0.213691 | 6218.66ms | 2090234 | 80 | 4.47087e+09 | 3.49837e+06 | 0.129994 | 3(Loss) | true |
| glaze | 529.375 | 0.504194 | 6988.66ms | 2090234 | 30 | 1.08139e+10 | 3.76558e+06 | 0.895827 | 4(Loss) | true |
| simdjson (ondemand) | 464.218 | 0.614615 | 7680.16ms | 2090234 | 40 | 2.78619e+10 | 4.29411e+06 | 0.41371 | 5(Loss) | true |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2057.05 | 0.529262 | 5927.65ms | 2090234 | 80 | 2.10442e+09 | 969059 | 0.794491 | 1(Win) | true |
| glaze | 1394.94 | 0.542341 | 9134.88ms | 2090234 | 160 | 9.61048e+09 | 1.42903e+06 | 0.921027 | 2(Loss) | true |
| simdjson (reflection) | 658.192 | 0.57215 | 8969.1ms | 2090326 | 160 | 4.80466e+10 | 3.02873e+06 | 1.34753 | 3(Loss) | true |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1989.06 | 0.46729 | 6379.66ms | 2090234 | 40 | 8.77256e+08 | 1.00218e+06 | 1.1622 | 1(Win) | true |
| glaze | 1462.8 | 0.451121 | 8495.31ms | 2090234 | 40 | 1.51169e+09 | 1.36273e+06 | 1.28915 | 2(Loss) | true |
| simdjson (reflection) | 683.624 | 0.472469 | 8918.93ms | 2090326 | 30 | 5.69458e+09 | 2.91606e+06 | 0.25307 | 3(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1624.93 | 0.877622 | 5962.97ms | 6661897 | 30 | 3.53234e+10 | 3.90988e+06 | 0.1212 | 1(Win) | true |
| jsonifier (two-stage) | 1560.57 | 0.272119 | 5999.36ms | 6661897 | 80 | 9.81829e+09 | 4.07112e+06 | 0.616723 | 2(Loss) | true |
| simdjson (reflection) | 1438.49 | 0.894193 | 6735.26ms | 6661897 | 40 | 6.23888e+10 | 4.41664e+06 | 0.74293 | 3(Loss) | true |
| simdjson (ondemand) | 1205.12 | 0.120399 | 8167.96ms | 6661897 | 80 | 3.22308e+09 | 5.27189e+06 | 0.00115327 | 4(Loss) | true |
| glaze | 1170.26 | 0.713724 | 8423.89ms | 6661897 | 30 | 4.50418e+10 | 5.42897e+06 | 0.150807 | 5(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2011.32 | 0.332526 | 5896.03ms | 6661897 | 80 | 8.82628e+09 | 3.15877e+06 | 1.59727 | 1(Win) | true |
| jsonifier (two-stage) | 1853.22 | 0.36336 | 6361.58ms | 6661897 | 30 | 4.65519e+09 | 3.42824e+06 | 0.37527 | 2(Loss) | true |
| simdjson (reflection) | 1681.04 | 0.182208 | 6618.91ms | 6661897 | 30 | 1.42264e+09 | 3.77938e+06 | 0.436787 | 3(Loss) | true |
| simdjson (ondemand) | 1361.29 | 1.00514 | 8125.23ms | 6661897 | 30 | 6.60189e+10 | 4.66712e+06 | 2.37803 | 4(Loss) | true |
| glaze | 1256.12 | 0.470176 | 8532.68ms | 6661897 | 80 | 4.52421e+10 | 5.05785e+06 | 1.76786 | 5(Loss) | true |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6251.11 | 0.088439 | 6456.92ms | 6661897 | 320 | 2.58535e+08 | 1.01634e+06 | 0.310971 | 1(Win) | true |
| glaze | 2800.96 | 0.449554 | 6548.3ms | 6661897 | 30 | 3.11938e+09 | 2.26825e+06 | 0.0270796 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 99.3592 | 1.13887 | 6023.32ms | 6661989 | 30 | 1.59097e+13 | 6.39434e+07 | inf | -(Loss) | false |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5727.06 | 0.436635 | 6544.9ms | 6661897 | 40 | 9.38488e+08 | 1.10934e+06 | 0.170481 | 1(Win) | true |
| glaze | 3436.96 | 0.0957663 | 5883.11ms | 6661897 | 160 | 5.0141e+08 | 1.84852e+06 | 0.448159 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 106.255 | 0.291451 | 6109.82ms | 6661989 | 30 | 9.1109e+11 | 5.97936e+07 | inf | -(Loss) | false |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1806.06 | 0.339411 | 6998.57ms | 500299 | 40 | 3.21595e+07 | 264179 | 0.156907 | 1(Win) | true |
| jsonifier (two-stage) | 1147.87 | 0.226145 | 5352.66ms | 500299 | 320 | 2.82747e+08 | 415658 | 0.608128 | 2(Loss) | true |
| glaze | 1104.54 | 0.210945 | 5667.81ms | 500299 | 640 | 5.31391e+08 | 431964 | 0.621901 | 3(Loss) | true |
| simdjson (ondemand) | 989.573 | 0.117289 | 6138.27ms | 500299 | 320 | 1.02336e+08 | 482150 | 0.514508 | 4(Loss) | true |
| simdjson (reflection) | 918.252 | 0.408395 | 6708.92ms | 500299 | 160 | 7.20469e+08 | 519598 | 0.284026 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2367.24 | 0.197774 | 6710.97ms | 500299 | 80 | 1.27117e+07 | 201552 | 0.18225 | 1(Win) | true |
| jsonifier (two-stage) | 1404.83 | 0.0800191 | 10230.7ms | 500299 | 320 | 2.36345e+07 | 339629 | 0.0315539 | 2(Loss) | true |
| glaze | 1278.69 | 0.232913 | 5412.68ms | 500299 | 160 | 1.20847e+08 | 373134 | 0.137834 | 3(Loss) | true |
| simdjson (ondemand) | 1118.07 | 0.238753 | 6192.08ms | 500299 | 80 | 8.30438e+07 | 426736 | 0.750945 | 4(Loss) | true |
| simdjson (reflection) | 1066.36 | 0.305245 | 6111.51ms | 500299 | 40 | 7.46119e+07 | 447430 | 0.653159 | 5(Loss) | true |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8071.51 | 0.0545829 | 5993.09ms | 500299 | 4890 | 5.09062e+06 | 59111.9 | 0.0937506 | 1(Win) | true |
| simdjson (reflection) | 6937.13 | 0.0526535 | 7000.78ms | 500299 | 4890 | 6.41302e+06 | 68778 | 0.0499351 | 2(Loss) | true |
| glaze | 1863.27 | 0.0642599 | 6619.22ms | 500299 | 1280 | 3.46575e+07 | 256067 | 0.0629127 | 3(Loss) | true |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8089.38 | 0.0722878 | 5949.35ms | 500299 | 2560 | 4.6537e+06 | 58981.3 | 0.00966501 | 1(Win) | true |
| simdjson (reflection) | 7133.1 | 0.0670876 | 6886.27ms | 500299 | 4890 | 9.84682e+06 | 66888.5 | 0.488705 | 2(Loss) | true |
| glaze | 1987.43 | 0.167368 | 6279.98ms | 500299 | 40 | 6.45777e+06 | 240070 | 0.0133276 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2951.72 | 0.316658 | 6033.27ms | 1439562 | 320 | 6.94133e+08 | 465110 | 1.73286 | 1(Win) | true |
| jsonifier (two-stage) | 2800.68 | 0.276711 | 6355.46ms | 1439562 | 320 | 5.88761e+08 | 490194 | 0.558599 | 2(Loss) | true |
| simdjson (ondemand) | 2405.12 | 0.114965 | 7419.89ms | 1439562 | 640 | 2.75615e+08 | 570814 | 0.275452 | 3(Loss) | true |
| simdjson (reflection) | 2349.86 | 0.157927 | 7553.9ms | 1439562 | 640 | 5.44839e+08 | 584237 | 0.244883 | 4(Loss) | true |
| glaze | 1874.58 | 0.188588 | 9362.23ms | 1439562 | 320 | 6.10423e+08 | 732362 | 0.00950439 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3344.27 | 0.668657 | 5607.23ms | 1439562 | 40 | 3.01388e+08 | 410515 | 1.03222 | 1(Win) | true |
| jsonifier (two-stage) | 3002.9 | 0.261103 | 6526.43ms | 1439562 | 160 | 2.27993e+08 | 457182 | 0.237066 | 2(Loss) | true |
| simdjson (ondemand) | 2345.23 | 0.724619 | 7769.28ms | 1439562 | 40 | 7.19728e+08 | 585389 | 1.33425 | 3(Loss) | true |
| simdjson (reflection) | 2272.07 | 0.548998 | 7913.3ms | 1439562 | 320 | 3.52134e+09 | 604238 | 1.86907 | 4(Loss) | true |
| glaze | 1756.38 | 0.515747 | 5213.13ms | 1439562 | 40 | 6.50068e+08 | 781651 | 0.0417403 | 5(Loss) | true |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18806.1 | 0.114534 | 7418.31ms | 1439562 | 160 | 1.11855e+06 | 73001.6 | 0.288474 | 1(Win) | true |
| glaze | 3596.51 | 0.165759 | 10046.9ms | 1439584 | 1280 | 5.12479e+08 | 381730 | 0.166152 | 2(Loss) | true |
| simdjson (reflection) | 310.863 | 0.743175 | 6661.09ms | 1439562 | 80 | 8.6178e+10 | 4.41634e+06 | 0.582093 | 3(Loss) | true |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 18915.4 | 0.078211 | 7459.18ms | 1439562 | 640 | 2.06227e+06 | 72579.6 | 0.246842 | 1(Win) | true |
| glaze | 4254.13 | 0.0644196 | 8396.23ms | 1439584 | 1280 | 5.53219e+07 | 322720 | 0.143488 | 2(Loss) | true |
| simdjson (reflection) | 321.704 | 0.382958 | 6600.28ms | 1439562 | 80 | 2.13668e+10 | 4.2675e+06 | 0.118785 | 3(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1619.47 | 0.206981 | 3345.5ms | 56369 | 30 | 141618 | 33194.7 | 0 | 1(Win) | true |
| glaze | 1325.39 | 0.219805 | 4174.47ms | 56369 | 160 | 1.27172e+06 | 40560 | 0.0552573 | 2(Loss) | true |
| jsonifier (two-stage) | 1038.95 | 0.209592 | 5166.24ms | 56369 | 2560 | 3.01078e+07 | 51742.2 | 0.113897 | 3(Loss) | true |
| simdjson (reflection) | 1002.66 | 0.117475 | 5413.36ms | 56369 | 640 | 2.5389e+06 | 53615.2 | 0.524982 | 4(Loss) | true |
| simdjson (ondemand) | 929.869 | 0.10055 | 6012.97ms | 56369 | 4890 | 1.65238e+07 | 57812.1 | 0.0128384 | 5(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2160.82 | 0.449467 | 3148.66ms | 56369 | 160 | 2.0006e+06 | 24878.4 | 0.0064317 | 1(Win) | true |
| glaze | 1753.58 | 0.101559 | 3679.39ms | 56369 | 1280 | 1.24073e+06 | 30656 | 0.228863 | 2(Loss) | true |
| jsonifier (two-stage) | 1360.93 | 0.24299 | 4860.4ms | 56369 | 30 | 276381 | 39500.8 | 0.322997 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1141.8 | 0.197567 | 5480.24ms | 56369 | 80 | 692183 | 47081.6 | 0.183849 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1133.25 | 0.411814 | 5574.45ms | 56369 | 40 | 1.52648e+06 | 47436.8 | 0.0719036 | 4(Tie) | true |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11500.1 | 0.190107 | 479.332ms | 56369 | 4890 | 386174 | 4674.54 | 0.440044 | 1(Win) | true |
| simdjson (reflection) | 8804.65 | 0.304052 | 623.893ms | 56369 | 320 | 110281 | 6105.6 | 0.0261986 | 2(Loss) | true |
| glaze | 2551.05 | 0.26531 | 2092.36ms | 56369 | 1280 | 4.00095e+06 | 21072.8 | 0.211143 | 3(Loss) | true |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12064.1 | 0.722216 | 454.821ms | 56369 | 320 | 331416 | 4456 | 0.322119 | 1(Win) | true |
| simdjson (reflection) | 9012.48 | 0.201616 | 610.531ms | 56369 | 1280 | 185120 | 5964.8 | 0.242001 | 2(Loss) | true |
| glaze | 2789.77 | 0.407795 | 1799.94ms | 56369 | 640 | 3.95192e+06 | 19269.6 | 1.92989 | 3(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1823.13 | 0.479603 | 5065.86ms | 94370 | 320 | 1.79369e+07 | 49364.8 | 0.91254 | 1(Win) | true |
| glaze | 1799.09 | 0.0561575 | 5273.33ms | 94370 | 4890 | 3.85911e+06 | 50024.3 | 0.955636 | 2(Loss) | true |
| jsonifier (two-stage) | 1761.41 | 0.173931 | 5623.44ms | 94370 | 320 | 2.52726e+06 | 51094.4 | 0.0969811 | 3(Loss) | true |
| simdjson (reflection) | 1549.39 | 0.248124 | 6130.4ms | 94370 | 80 | 1.66179e+06 | 58086.4 | 0.077067 | 4(Loss) | true |
| simdjson (ondemand) | 1433.46 | 0.10673 | 6467.84ms | 94370 | 2560 | 1.14949e+07 | 62784 | 0.138379 | 5(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2468.14 | 0.166298 | 4507.14ms | 94370 | 160 | 588330 | 36464 | 0.0702556 | 1(Win) | true |
| glaze | 2280.33 | 0.21962 | 4847.87ms | 94370 | 160 | 1.20209e+06 | 39467.2 | 0.174626 | 2(Loss) | true |
| jsonifier (two-stage) | 2005.77 | 0.303926 | 5422.86ms | 94370 | 640 | 1.1902e+07 | 44869.6 | 0.262782 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1717.21 | 0.283628 | 6106.23ms | 94370 | 40 | 883854 | 52409.6 | 0.117905 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1716.27 | 0.218878 | 5954.08ms | 94370 | 160 | 2.10778e+06 | 52438.4 | 0.0610612 | 4(Tie) | true |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12670.8 | 0.369812 | 700.927ms | 94370 | 640 | 441572 | 7102.8 | 0.469616 | 1(Win) | true |
| glaze | 2502.23 | 0.105153 | 3672.35ms | 94370 | 640 | 915452 | 35967.2 | 0.133277 | 2(Loss) | true |
| simdjson (reflection) | 339.688 | 0.197558 | 7492.91ms | 94370 | 160 | 4.38347e+07 | 264944 | 0.30408 | 3(Loss) | true |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13717.6 | 0.343075 | 706.046ms | 94370 | 640 | 324244 | 6560.8 | 0.305773 | 1(Win) | true |
| glaze | 2784.74 | 0.237422 | 3377.72ms | 94370 | 160 | 942026 | 32318.4 | 0.133849 | 2(Loss) | true |
| simdjson (reflection) | 341.06 | 0.336794 | 6987.9ms | 94370 | 40 | 3.15934e+07 | 263878 | 0.00727661 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1727.94 | 0.447154 | 732.045ms | 11812 | 320 | 271928 | 6519.2 | 0.30773 | 1(Win) | true |
| jsonifier (two-stage) | 1043.02 | 0.598265 | 1189.99ms | 11812 | 2560 | 1.06879e+07 | 10800.2 | 0.00185185 | 2(Loss) | true |
| glaze | 846.952 | 0.216321 | 1353.09ms | 11812 | 640 | 529794 | 13300.4 | 0.0450911 | 3(Loss) | true |
| simdjson (reflection) | 755.175 | 1.16552 | 1763.32ms | 11812 | 160 | 4.83625e+06 | 14916.8 | 0.501601 | 4(Loss) | true |
| simdjson (ondemand) | 591.601 | 0.742531 | 2329.61ms | 11812 | 2560 | 5.1175e+07 | 19041.2 | 0.689497 | 5(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2049.84 | 1.66743 | 702.325ms | 11812 | 30 | 251899 | 5495.47 | 0.311526 | 1(Win) | true |
| jsonifier (two-stage) | 1165.36 | 1.55989 | 1192.58ms | 11812 | 320 | 7.27562e+06 | 9666.4 | 1.49193 | 2(Loss) | true |
| simdjson (reflection) | 862.41 | 0.361225 | 1544.45ms | 11812 | 2560 | 5.69921e+06 | 13062 | 1.08186 | 3(Loss) | true |
| glaze | 835.965 | 0.861629 | 1334.03ms | 11812 | 160 | 2.15691e+06 | 13475.2 | 0.307765 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 621.733 | 1.07395 | 2190.54ms | 11812 | 1280 | 4.84635e+07 | 18118.4 | 7.25635 | -(Loss) | false |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8417.88 | 1.44532 | 160.581ms | 11812 | 1280 | 478830 | 1338.2 | 3.782 | 1(Win) | true |
| simdjson (reflection) | 7111.62 | 2.51564 | 186.228ms | 11812 | 160 | 254055 | 1584 | 0.201613 | 2(Loss) | true |
| glaze | 1529.13 | 0.42798 | 858.734ms | 11812 | 640 | 636186 | 7366.8 | 1.35512 | 3(Loss) | true |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8762.29 | 1.82993 | 164.915ms | 11812 | 640 | 354212 | 1285.6 | 1.96701 | 1(Win) | true |
| simdjson (reflection) | 6728.47 | 1.564 | 179.586ms | 11812 | 2560 | 1.75521e+06 | 1674.2 | 0.958353 | 2(Loss) | true |
| glaze | 1632.96 | 0.814719 | 856.913ms | 11812 | 320 | 1.01079e+06 | 6898.4 | 1.69859 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2694.19 | 0.14129 | 1202.16ms | 31235 | 4890 | 1.19331e+06 | 11056.4 | 0.218643 | 1(Win) | true |
| jsonifier (two-stage) | 1833.24 | 1.03277 | 1675.49ms | 31235 | 640 | 1.80231e+07 | 16248.8 | 1.46987 | 2(Loss) | true |
| glaze | 1642.72 | 0.395174 | 2148.21ms | 31235 | 30 | 154047 | 18133.3 | 0.520341 | 3(Loss) | true |
| simdjson (reflection) | 1490.77 | 1.20675 | 1980.32ms | 31235 | 2560 | 1.48845e+08 | 19981.6 | 1.00474 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1376.2 | 1.32132 | 2257.24ms | 31235 | 1280 | 1.047e+08 | 21645.2 | 6.01629 | -(Loss) | false |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2636.95 | 0.473703 | 1275.99ms | 31235 | 640 | 1.83262e+06 | 11296.4 | 0.401735 | 1(Win) | true |
| jsonifier (two-stage) | 2591.93 | 0.291606 | 1646.17ms | 31235 | 1280 | 1.43761e+06 | 11492.6 | 0.730989 | 2(Loss) | true |
| simdjson (reflection) | 2059.94 | 0.288046 | 1770.67ms | 31235 | 4890 | 8.48413e+06 | 14460.6 | 4.53946 | 3(Loss) | true |
| glaze STATISTICAL TIE | 1654.01 | 0.524856 | 2113.42ms | 31235 | 1280 | 1.14366e+07 | 18009.6 | 1.06397 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1651.07 | 1.03249 | 2151.04ms | 31235 | 40 | 1.38798e+06 | 18041.6 | 0.271226 | 4(Tie) | true |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15780.9 | 0.544537 | 190.967ms | 31235 | 2560 | 270467 | 1887.6 | 1.91124 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2531.49 | 0.176503 | 1182.31ms | 31235 | 2560 | 1.10427e+06 | 11767 | 5.1079 | -(Loss) | false |
| simdjson (reflection) | 297.29 | 0.264612 | 5275.77ms | 31235 | 80 | 5.62382e+06 | 100198 | 0.12791 | 3(Loss) | true |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16461.1 | 1.78769 | 182.544ms | 31235 | 160 | 167444 | 1809.6 | 2.81818 | 1(Win) | true |
| glaze | 3102.79 | 0.352288 | 1088.67ms | 31235 | 640 | 732075 | 9600.4 | 0.00416667 | 2(Loss) | true |
| simdjson (reflection) | 291.847 | 1.14668 | 5798ms | 31235 | 30 | 4.1094e+07 | 102067 | 0.724211 | 3(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1400.23 | 2.54795 | 6696.26ms | 108313 | 1280 | 4.52224e+09 | 73770.2 | 1.52366 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1395.42 | 0.135912 | 7825.58ms | 108313 | 4890 | 4.94968e+07 | 74024.6 | 2.08202 | 1(Tie) | true |
| glaze | 1067.17 | 0.798617 | 5020.12ms | 108313 | 2560 | 1.52971e+09 | 96793.4 | 0.429581 | 3(Loss) | true |
| simdjson (ondemand) | 1021.18 | 0.386459 | 5361.87ms | 108313 | 1280 | 1.95602e+08 | 101153 | 0.83467 | 4(Loss) | true |
| simdjson (reflection) | 1004.15 | 0.347166 | 5651.64ms | 108313 | 160 | 2.04062e+07 | 102869 | 0.116518 | 5(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2777.47 | 0.687019 | 4091.34ms | 108313 | 40 | 2.61132e+06 | 37190.4 | 0.13176 | 1(Win) | true |
| jsonifier (two-stage) | 1516.73 | 0.367712 | 7297.87ms | 108313 | 320 | 2.00683e+07 | 68104 | 0.101124 | 2(Loss) | true |
| glaze | 1358.35 | 0.338709 | 10265.6ms | 108313 | 80 | 5.30742e+06 | 76044.8 | 0.0926628 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1152.96 | 0.614298 | 5625.54ms | 108313 | 30 | 9.08683e+06 | 89591.5 | 0.0951565 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1150.83 | 0.251315 | 5057.64ms | 108313 | 640 | 3.25657e+07 | 89757.6 | 0.177053 | 4(Tie) | true |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12661.2 | 0.200228 | 843.658ms | 108313 | 1280 | 341563 | 8158.4 | 0.332291 | 1(Win) | true |
| simdjson (reflection) | 7186.06 | 0.557925 | 1561.25ms | 108313 | 40 | 257271 | 14374.4 | 0.0891266 | 2(Loss) | true |
| glaze | 1681.55 | 0.497678 | 6364ms | 108313 | 640 | 5.98165e+07 | 61428.8 | 0.564469 | 3(Loss) | true |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13040.8 | 0.264205 | 800.001ms | 108313 | 4890 | 2.14162e+06 | 7920.92 | 0.589532 | 1(Win) | true |
| simdjson (reflection) | 7091.78 | 0.300074 | 1523.76ms | 108313 | 2560 | 4.89042e+06 | 14565.5 | 0.274687 | 2(Loss) | true |
| glaze | 1851.17 | 0.176519 | 5850.17ms | 108313 | 640 | 6.20914e+06 | 55800 | 0.0401273 | 3(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2715.35 | 0.531659 | 7897.23ms | 213963 | 320 | 5.10789e+07 | 75147.2 | 2.69378 | 1(Win) | true |
| jsonifier (two-stage) | 2295.72 | 0.903832 | 5067.16ms | 213963 | 40 | 2.58151e+07 | 88883.2 | 0.922667 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1832.51 | 2.60426 | 6046.03ms | 213963 | 160 | 1.34546e+09 | 111350 | 3.31651 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1807.58 | 0.371636 | 6143.29ms | 213963 | 80 | 1.40802e+07 | 112886 | 0.122041 | 3(Tie) | true |
| simdjson (reflection) | 1710.37 | 0.26317 | 6358.31ms | 213963 | 2560 | 2.52353e+08 | 119302 | 0.164139 | 5(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3170.38 | 0.40503 | 7598.01ms | 213963 | 80 | 5.43649e+06 | 64361.6 | 0.0547209 | 1(Win) | true |
| jsonifier (two-stage) | 2513.64 | 0.66254 | 9523.99ms | 213963 | 40 | 1.15706e+07 | 81177.6 | 0.146951 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1959.38 | 0.596851 | 5841ms | 213963 | 40 | 1.54537e+07 | 104141 | 0.304101 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1946.22 | 1.75835 | 5570.83ms | 213963 | 40 | 1.35945e+08 | 104845 | 0.175296 | 3(Tie) | true |
| simdjson (reflection) | 1887.35 | 0.683673 | 5848.86ms | 213963 | 80 | 4.3708e+07 | 108115 | 0.377425 | 5(Loss) | true |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14561.8 | 0.632737 | 1370.38ms | 213963 | 1280 | 1.00625e+07 | 14012.8 | 0.0256974 | 1(Win) | true |
| glaze | 2030.21 | 0.432239 | 5366.09ms | 213963 | 160 | 3.01969e+07 | 100507 | 0.183407 | 2(Loss) | true |
| simdjson (reflection) | 287.604 | 1.01903 | 9108.8ms | 213963 | 320 | 1.6727e+10 | 709487 | 0.147832 | 3(Loss) | true |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 15715.5 | 0.135443 | 1469.66ms | 213963 | 2560 | 791735 | 12984.1 | 0.319096 | 1(Win) | true |
| glaze | 2271.68 | 0.384962 | 9280.96ms | 213963 | 80 | 9.56556e+06 | 89824 | 0.369135 | 2(Loss) | true |
| simdjson (reflection) | 273.015 | 0.463492 | 9552.02ms | 213963 | 640 | 7.68016e+09 | 747400 | 4.67387 | 3(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 444.244 | 3.62812 | 5260.13ms | 1834197 | 80 | 1.63268e+12 | 3.93754e+06 | 26.4121 | -(Tie) | false |
| glaze STATISTICAL TIE | 443.83 | 0.331807 | 6712.46ms | 1834197 | 80 | 1.3681e+10 | 3.94121e+06 | 1.01936 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 429.57 | 0.403309 | 6731.74ms | 1834197 | 30 | 8.09136e+09 | 4.07204e+06 | 0.89927 | 1(Tie) | true |
| jsonifier (two-stage) | 403.059 | 3.07778 | 6365.45ms | 1834197 | 80 | 1.42732e+12 | 4.33988e+06 | 3.73447 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 343.495 | 3.49281 | 7820.44ms | 1834197 | 80 | 2.53099e+12 | 5.09243e+06 | 7.60192 | -(Loss) | false |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 582.408 | 3.56306 | 5945.1ms | 1834197 | 40 | 4.58083e+11 | 3.00344e+06 | 8.20373 | -(Win) | false |
| jsonifier (two-stage) DID NOT CONVERGE | 523.876 | 0.9446 | 6137.16ms | 1834197 | 30 | 2.98437e+10 | 3.33901e+06 | 12.2729 | -(Loss) | false |
| glaze | 472.589 | 0.743401 | 6225.28ms | 1834197 | 80 | 6.05705e+10 | 3.70137e+06 | 0.96013 | 3(Loss) | true |
| simdjson (reflection) | 456.016 | 1.34928 | 6814.92ms | 1834197 | 80 | 2.14303e+11 | 3.83589e+06 | 3.12842 | 4(Loss) | true |
| simdjson (ondemand) | 419.378 | 0.652213 | 6906.46ms | 1834197 | 80 | 5.92038e+10 | 4.171e+06 | 2.70724 | 5(Loss) | true |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1016.79 | 2.72116 | 10231.8ms | 1834197 | 40 | 8.76587e+10 | 1.72034e+06 | 1.09785 | 1(Win) | true |
| glaze DID NOT CONVERGE | 703.851 | 0.558105 | 8153.16ms | 1833577 | 80 | 1.53801e+10 | 2.48438e+06 | 7.7355 | -(Loss) | false |
| simdjson (reflection) DID NOT CONVERGE | 655.691 | 0.747654 | 9305.74ms | 1922245 | 40 | 1.74775e+10 | 2.79582e+06 | 5.96087 | -(Loss) | false |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1133.38 | 1.87891 | 5011.64ms | 1834197 | 40 | 3.36365e+10 | 1.54337e+06 | 1.18224 | 1(Win) | true |
| glaze DID NOT CONVERGE | 688.377 | 0.642986 | 7870.78ms | 1833577 | 30 | 8.00332e+09 | 2.54023e+06 | 10.426 | -(Loss) | false |
| simdjson (reflection) | 636.003 | 0.648143 | 9514.82ms | 1922245 | 40 | 1.39605e+10 | 2.88237e+06 | 3.799 | 3(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2211.89 | 0.42111 | 6899.82ms | 9930848 | 40 | 1.30046e+10 | 4.28177e+06 | 3.46581 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1794.06 | 4.01846 | 7521.19ms | 9930848 | 30 | 1.35002e+12 | 5.27898e+06 | 0.0624349 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1754.64 | 0.453937 | 9132.84ms | 9930848 | 80 | 4.80261e+10 | 5.39757e+06 | 0.351335 | 2(Tie) | true |
| glaze STATISTICAL TIE | 1680.39 | 0.313724 | 9538.38ms | 9930848 | 30 | 9.37929e+09 | 5.63607e+06 | 2.51881 | 2(Tie) | true |
| simdjson (ondemand) | 1626.12 | 1.16558 | 9095.18ms | 9930848 | 30 | 1.38252e+11 | 5.82415e+06 | 0.381678 | 5(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2375.44 | 0.837286 | 7151.74ms | 9930848 | 40 | 4.4575e+10 | 3.98696e+06 | 0.116622 | 1(Win) | true |
| jsonifier (two-stage) | 2129.65 | 0.559132 | 7428.56ms | 9930848 | 30 | 1.85484e+10 | 4.44711e+06 | 0.347443 | 2(Loss) | true |
| simdjson (reflection) | 1945.99 | 0.618625 | 8183.2ms | 9930848 | 40 | 3.62584e+10 | 4.86684e+06 | 3.72059 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 1828.31 | 0.454956 | 8926.25ms | 9930848 | 30 | 1.66623e+10 | 5.18009e+06 | 8.29031 | -(Tie) | false |
| glaze STATISTICAL TIE | 1755.23 | 2.00115 | 9065.83ms | 9930848 | 40 | 4.66361e+11 | 5.39575e+06 | 2.05979 | 4(Tie) | true |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5168.93 | 1.09869 | 6248.99ms | 9930848 | 40 | 1.621e+10 | 1.83226e+06 | 4.79595 | 1(Win) | true |
| glaze DID NOT CONVERGE | 2406.63 | 1.31737 | 6411.21ms | 9930228 | 80 | 2.14983e+11 | 3.93504e+06 | 6.60743 | -(Loss) | false |
| simdjson (reflection) DID NOT CONVERGE | 107.509 | 1.04874 | 8480.81ms | 10018896 | 30 | 2.60622e+13 | 8.88744e+07 | inf | -(Loss) | false |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5412.76 | 0.916938 | 5894.38ms | 9930848 | 30 | 7.72213e+09 | 1.74972e+06 | 1.30965 | 1(Win) | true |
| glaze | 2659.45 | 0.883367 | 5622.37ms | 9930228 | 30 | 2.96852e+10 | 3.56097e+06 | 1.7012 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 131.911 | 0.752876 | 7955.25ms | 10018896 | 30 | 8.92163e+12 | 7.24333e+07 | inf | -(Loss) | false |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 458.014 | 3.09114 | 5744.5ms | 1834197 | 80 | 1.11496e+12 | 3.81915e+06 | 6.64112 | -(Win) | false |
| glaze STATISTICAL TIE | 427.542 | 0.784223 | 6649.77ms | 1834197 | 30 | 3.08842e+10 | 4.09136e+06 | 1.72557 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 420.189 | 2.2627 | 6558.65ms | 1834197 | 30 | 2.66181e+11 | 4.16295e+06 | 2.05351 | 2(Tie) | true |
| simdjson (reflection) | 405.465 | 1.26258 | 6759.49ms | 1834197 | 30 | 8.9007e+10 | 4.31413e+06 | 4.00254 | 4(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 380.417 | 1.53018 | 7402.53ms | 1834197 | 80 | 3.96047e+11 | 4.59819e+06 | 10.6671 | -(Loss) | false |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 568.108 | 2.93354 | 5888.74ms | 1834197 | 40 | 3.26344e+11 | 3.07904e+06 | 0.982967 | 1(Win) | true |
| jsonifier | 478.939 | 5.16068 | 6684.64ms | 1834197 | 40 | 1.42104e+12 | 3.65229e+06 | 4.27684 | 2(Loss) | true |
| glaze STATISTICAL TIE | 432.272 | 0.95189 | 7799.24ms | 1834197 | 80 | 1.18698e+11 | 4.04659e+06 | 1.09367 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 426.475 | 0.436661 | 7222.25ms | 1834197 | 80 | 2.56616e+10 | 4.1016e+06 | 0.613726 | 3(Tie) | true |
| simdjson (reflection) | 357.062 | 2.97556 | 7476.78ms | 1834197 | 80 | 1.69994e+12 | 4.89895e+06 | 0.41684 | 5(Loss) | true |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1244.41 | 1.27108 | 5369.42ms | 1834197 | 30 | 9.57703e+09 | 1.40566e+06 | 1.91495 | 1(Win) | true |
| glaze DID NOT CONVERGE | 691.34 | 1.48212 | 8437.74ms | 1833577 | 160 | 2.24854e+11 | 2.52934e+06 | 7.97889 | -(Loss) | false |
| simdjson (reflection) | 660.158 | 1.18075 | 9965.99ms | 1922245 | 40 | 4.30026e+10 | 2.7769e+06 | 1.69643 | 3(Loss) | true |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1145.25 | 0.614397 | 5266.88ms | 1834197 | 80 | 7.04494e+09 | 1.52737e+06 | 0.222006 | 1(Win) | true |
| glaze | 746.535 | 0.588466 | 7444.01ms | 1833577 | 160 | 3.03991e+10 | 2.34233e+06 | 1.38064 | 2(Loss) | true |
| simdjson (reflection) | 542.967 | 4.79171 | 9561.22ms | 1922245 | 30 | 7.85187e+11 | 3.37626e+06 | 1.22601 | 3(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2145.62 | 0.189504 | 7119.41ms | 9930848 | 40 | 2.79875e+09 | 4.414e+06 | 1.63764 | 1(Win) | true |
| jsonifier | 1892.55 | 3.04792 | 7442.63ms | 9930848 | 40 | 9.30561e+11 | 5.00425e+06 | 2.8432 | 2(Loss) | true |
| simdjson (reflection) | 1708.95 | 1.18135 | 9174ms | 9930848 | 30 | 1.28586e+11 | 5.54187e+06 | 2.33266 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1528.36 | 1.16537 | 9556.2ms | 9930848 | 80 | 4.17197e+11 | 6.1967e+06 | 8.58135 | -(Loss) | false |
| glaze | 1355.02 | 3.64584 | 10289.5ms | 9930848 | 30 | 1.94804e+12 | 6.98941e+06 | 0.00756897 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2164.04 | 3.8642 | 7293.43ms | 9930848 | 40 | 1.14399e+12 | 4.37644e+06 | 2.53264 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1994.72 | 1.76144 | 8552.58ms | 9930848 | 80 | 5.5955e+11 | 4.74794e+06 | 1.61838 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1986.52 | 0.480303 | 8484.74ms | 9930848 | 40 | 2.09738e+10 | 4.76752e+06 | 7.61086 | -(Loss) | false |
| glaze DID NOT CONVERGE | 1700.66 | 1.04474 | 10406.1ms | 9930848 | 40 | 1.35398e+11 | 5.5689e+06 | 5.51257 | -(Loss) | false |
| simdjson (reflection) | 1423.61 | 4.43078 | 10323ms | 9930848 | 30 | 2.60657e+12 | 6.65265e+06 | 1.96846 | 5(Loss) | true |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 4986.67 | 0.815424 | 5962.19ms | 9930848 | 160 | 3.83742e+10 | 1.89922e+06 | 10.4757 | -(Win) | false |
| glaze | 1735.44 | 2.35479 | 8095.46ms | 9930228 | 80 | 1.32097e+12 | 5.45694e+06 | 0.523457 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 123.436 | 0.79832 | 8441.54ms | 10018896 | 30 | 1.14559e+13 | 7.74065e+07 | inf | -(Loss) | false |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5221.29 | 1.75884 | 5714.82ms | 9930848 | 40 | 4.07129e+10 | 1.81388e+06 | 0.573808 | 1(Win) | true |
| glaze | 2399.81 | 1.54247 | 5946.9ms | 9930228 | 80 | 2.96408e+11 | 3.94622e+06 | 1.13163 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 120.278 | 1.93998 | 8247.01ms | 10018896 | 30 | 7.12501e+13 | 7.9439e+07 | inf | -(Loss) | false |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 916.558 | 0.585468 | 9348.64ms | 642697 | 40 | 6.13139e+08 | 668723 | 0.90163 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 751.469 | 1.37096 | 5115.65ms | 642697 | 320 | 4.00121e+10 | 815634 | 0.507099 | 2(Tie) | true |
| glaze STATISTICAL TIE | 739.979 | 1.62063 | 5445.31ms | 642697 | 160 | 2.88313e+10 | 828299 | 1.97921 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 729.676 | 1.14386 | 5423.86ms | 642697 | 320 | 2.95425e+10 | 839994 | 0.0463598 | 2(Tie) | true |
| simdjson (reflection) | 560.248 | 0.367378 | 6985.48ms | 642697 | 320 | 5.16925e+09 | 1.09402e+06 | 3.39062 | 5(Loss) | true |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 972.021 | 0.26202 | 9044.98ms | 642697 | 40 | 1.09192e+08 | 630566 | 0.0358748 | 1(Win) | true |
| glaze | 936.145 | 0.265174 | 10017ms | 642697 | 320 | 9.64583e+08 | 654731 | 0.0875629 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 822.752 | 0.838039 | 5406.03ms | 642697 | 320 | 1.24725e+10 | 744968 | 0.322834 | 3(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 821.465 | 2.53702 | 5207.74ms | 642697 | 80 | 2.86662e+10 | 746134 | 0.303275 | 3(Tie) | true |
| simdjson (reflection) | 603.026 | 0.469343 | 6803.62ms | 642697 | 30 | 6.8272e+08 | 1.01641e+06 | 0.153032 | 5(Loss) | true |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2255.88 | 0.297459 | 7664.21ms | 642697 | 160 | 1.04509e+08 | 271701 | 0.59882 | 1(Win) | true |
| glaze | 995.166 | 0.244031 | 8177.49ms | 642692 | 320 | 7.22863e+08 | 615896 | 0.653706 | 2(Loss) | true |
| simdjson (reflection) | 836.573 | 0.342234 | 9484.14ms | 643373 | 640 | 4.03221e+09 | 733431 | 0.316063 | 3(Loss) | true |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2180.9 | 0.365305 | 7365.19ms | 642697 | 160 | 1.68645e+08 | 281042 | 0.00967922 | 1(Win) | true |
| glaze | 996.759 | 0.204603 | 7893.46ms | 642692 | 320 | 5.06522e+08 | 614912 | 0.632167 | 2(Loss) | true |
| simdjson (reflection) | 799.85 | 1.27503 | 9419.48ms | 643373 | 30 | 2.86992e+09 | 767104 | 1.17519 | 3(Loss) | true |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 1294.83 | 0.537708 | 6544.77ms | 1225964 | 40 | 9.42934e+08 | 902950 | 3.38394 | 1(Win) | true |
| glaze STATISTICAL TIE | 1251.87 | 0.507116 | 6607.6ms | 1225964 | 80 | 1.7945e+09 | 933939 | 0.043838 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1230.17 | 1.35741 | 6377.99ms | 1225964 | 160 | 2.66299e+10 | 950416 | 1.52485 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 970.249 | 0.66674 | 7519.76ms | 1225964 | 80 | 5.16407e+09 | 1.20502e+06 | 2.17767 | 4(Tie) | true |
| jsonifier STATISTICAL TIE DID NOT CONVERGE | 968.652 | 3.41115 | 8881.54ms | 1225964 | 80 | 1.35616e+11 | 1.20701e+06 | 5.54618 | -(Tie) | false |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 1498.48 | 1.36914 | 6244.3ms | 1225964 | 30 | 3.42351e+09 | 780237 | 2.58055 | 1(Win) | true |
| jsonifier (two-stage) | 1323.2 | 0.422885 | 5871.82ms | 1225964 | 40 | 5.58478e+08 | 883590 | 2.46677 | 2(Loss) | true |
| glaze STATISTICAL TIE | 1088.15 | 3.09576 | 7266.45ms | 1225964 | 160 | 1.77024e+11 | 1.07446e+06 | 0.4785 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1078.88 | 0.522945 | 7331.94ms | 1225964 | 80 | 2.56927e+09 | 1.08369e+06 | 1.77309 | 3(Tie) | true |
| jsonifier | 819.074 | 3.26151 | 8492.01ms | 1225964 | 160 | 3.46789e+11 | 1.42743e+06 | 3.73708 | 5(Loss) | true |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3506.56 | 0.483557 | 10035ms | 1225964 | 80 | 2.0796e+08 | 333424 | 0.343363 | 1(Win) | true |
| glaze | 1251.73 | 1.32027 | 5707.86ms | 1225970 | 160 | 2.43323e+10 | 934046 | 0.125719 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 68.4589 | 2.63738 | 10905.3ms | 1226640 | 30 | 6.09313e+12 | 1.70878e+07 | 8.55497 | -(Loss) | false |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3037.17 | 2.0109 | 5040.4ms | 1225964 | 160 | 9.58782e+09 | 384954 | 0.616422 | 1(Win) | true |
| glaze | 1170.43 | 2.17882 | 5857.87ms | 1225970 | 160 | 7.57928e+10 | 998925 | 2.00338 | 2(Loss) | true |
| simdjson (reflection) | 80.0872 | 0.496252 | 10421.8ms | 1226640 | 40 | 2.10171e+11 | 1.46068e+07 | 0.543945 | 3(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1030.88 | 1.22499 | 5535.88ms | 409725 | 80 | 1.72476e+09 | 379040 | 1.24064 | 1(Win) | true |
| jsonifier (two-stage) | 737.712 | 1.39838 | 6891.74ms | 409725 | 40 | 2.19442e+09 | 529670 | 0.694744 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 649.186 | 0.593298 | 8284.97ms | 409725 | 30 | 3.82572e+08 | 601899 | 5.1537 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE DID NOT CONVERGE | 554.496 | 1.19139 | 9261.65ms | 409725 | 160 | 1.12776e+10 | 704683 | 6.70738 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 549.52 | 2.22448 | 8493.24ms | 409725 | 320 | 8.00621e+10 | 711065 | 4.56941 | 4(Tie) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1573.75 | 0.83437 | 5068.86ms | 409725 | 40 | 1.71668e+08 | 248288 | 2.3975 | 1(Win) | true |
| jsonifier (two-stage) | 1123.61 | 0.810829 | 6260.93ms | 409725 | 80 | 6.36062e+08 | 347757 | 0.870216 | 2(Loss) | true |
| glaze | 798.888 | 1.67645 | 7566.82ms | 409725 | 80 | 5.37881e+09 | 489110 | 0.949375 | 3(Loss) | true |
| simdjson (ondemand) | 692.084 | 0.301159 | 8803.97ms | 409725 | 30 | 8.67321e+07 | 564591 | 0.11172 | 4(Loss) | true |
| simdjson (reflection) | 679.987 | 0.594565 | 8730.34ms | 409725 | 30 | 3.5019e+08 | 574635 | 1.51045 | 5(Loss) | true |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 7559.67 | 3.59018 | 6031.75ms | 409725 | 160 | 5.50976e+08 | 51688 | 9.37781 | -(Win) | false |
| simdjson (reflection) | 6962.95 | 1.02609 | 5898.21ms | 409725 | 640 | 2.12202e+08 | 56117.6 | 0.413129 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 1323.78 | 1.19266 | 7292.5ms | 409725 | 640 | 7.93166e+09 | 295172 | 9.56551 | -(Loss) | false |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8728.54 | 0.410585 | 5051.49ms | 409725 | 4890 | 1.65203e+08 | 44766.3 | 2.31418 | 1(Win) | true |
| simdjson (reflection) | 6947.21 | 0.622559 | 6150.65ms | 409725 | 160 | 1.96176e+07 | 56244.8 | 4.88907 | 2(Loss) | true |
| glaze | 1581.75 | 1.22654 | 7386.57ms | 409725 | 40 | 3.67228e+08 | 247034 | 0.709116 | 3(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1590.21 | 0.34475 | 6282.66ms | 785750 | 40 | 1.05567e+08 | 471226 | 1.23806 | 1(Win) | true |
| simdjson (reflection) | 1142.45 | 0.319443 | 9148.61ms | 785750 | 80 | 3.51212e+08 | 655914 | 0.39625 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 1084.38 | 0.4479 | 9273.99ms | 785750 | 640 | 6.13121e+09 | 691038 | 9.68877 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE | 932.064 | 1.01689 | 9842.6ms | 785750 | 30 | 2.00515e+09 | 803968 | 1.15852 | 4(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 878.865 | 2.76933 | 8751.56ms | 785750 | 40 | 2.23015e+10 | 852634 | 0.427166 | 4(Tie) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2153.94 | 0.368532 | 5731.6ms | 785750 | 80 | 1.31505e+08 | 347898 | 0.4379 | 1(Win) | true |
| jsonifier (two-stage) | 1691.16 | 0.562951 | 8210.92ms | 785750 | 640 | 3.9822e+09 | 443099 | 1.07255 | 2(Loss) | true |
| glaze | 1301.15 | 0.58634 | 8391.53ms | 785750 | 640 | 7.29779e+09 | 575912 | 2.5071 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1148.81 | 0.461861 | 9230.66ms | 785750 | 640 | 5.80864e+09 | 652282 | 5.07384 | -(Loss) | false |
| simdjson (reflection) | 1109.48 | 1.12502 | 8960.4ms | 785750 | 30 | 1.7321e+09 | 675405 | 0.188608 | 5(Loss) | true |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11633.6 | 0.49624 | 6430.9ms | 785750 | 2560 | 2.61557e+08 | 64412.6 | 0.05927 | 1(Win) | true |
| glaze | 2269.48 | 0.708399 | 9015.84ms | 785750 | 80 | 4.37685e+08 | 330186 | 0.020348 | 2(Loss) | true |
| simdjson (reflection) | 268.771 | 1.0973 | 8892.49ms | 785750 | 160 | 1.49752e+11 | 2.78806e+06 | 1.04581 | 3(Loss) | true |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12461.2 | 0.28915 | 6271.15ms | 785750 | 320 | 9.67484e+06 | 60134.4 | 0.0266 | 1(Win) | true |
| glaze | 2397.34 | 0.427027 | 8392.04ms | 785750 | 80 | 1.42532e+08 | 312576 | 0.340768 | 2(Loss) | true |
| simdjson (reflection) | 271.887 | 0.487711 | 8788.55ms | 785750 | 160 | 2.89094e+10 | 2.75611e+06 | 0.229073 | 3(Loss) | true |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3738.13 | 0.892236 | 7264.33ms | 264040 | 30 | 1.08371e+07 | 67362.1 | 0.202276 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3710.11 | 0.184103 | 7088.88ms | 264040 | 4890 | 7.63473e+07 | 67870.7 | 3.48894 | 1(Tie) | true |
| simdjson (reflection) | 2828.14 | 0.710112 | 9360.85ms | 264040 | 30 | 1.19926e+07 | 89036.8 | 0.324799 | 3(Loss) | true |
| simdjson (ondemand) | 2695.59 | 0.477687 | 9352.93ms | 264040 | 1280 | 2.54875e+08 | 93414.8 | 0.09326 | 4(Loss) | true |
| glaze | 2016.32 | 0.354279 | 6653.48ms | 264040 | 320 | 6.26411e+07 | 124885 | 0.728767 | 5(Loss) | true |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3772.05 | 0.182304 | 6957.37ms | 264040 | 2560 | 3.79158e+07 | 66756.4 | 0.198126 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3768.49 | 0.269718 | 7051.54ms | 264040 | 1280 | 4.15754e+07 | 66819.4 | 0.14718 | 1(Tie) | true |
| simdjson (ondemand) | 2902.41 | 0.521865 | 5126.33ms | 264040 | 40 | 8.19973e+06 | 86758.4 | 3.10683 | 3(Loss) | true |
| simdjson (reflection) | 2788.35 | 1.2374 | 9320.34ms | 264040 | 80 | 9.98972e+07 | 90307.2 | 0.394877 | 4(Loss) | true |
| glaze | 2192.14 | 0.534094 | 6414.35ms | 264040 | 160 | 6.02227e+07 | 114869 | 1.94973 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 4440.83 | 0.428787 | 9087.59ms | 399947 | 640 | 8.68041e+07 | 85889.2 | 0.157629 | 1(Win) | true |
| jsonifier (two-stage) | 4170.33 | 1.60371 | 5128.58ms | 399947 | 30 | 6.45414e+07 | 91460.3 | 0.0373343 | 2(Loss) | true |
| simdjson (ondemand) | 3563.64 | 0.188096 | 5638.77ms | 399947 | 2560 | 1.03757e+08 | 107031 | 1.25262 | 3(Loss) | true |
| simdjson (reflection) | 3514.17 | 0.544324 | 5696.42ms | 399947 | 160 | 5.58465e+07 | 108538 | 0.00884408 | 4(Loss) | true |
| glaze | 2718.95 | 0.409111 | 7461.67ms | 399947 | 640 | 2.10798e+08 | 140282 | 1.03367 | 5(Loss) | true |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4506.03 | 0.887477 | 5162.33ms | 399947 | 40 | 2.25731e+07 | 84646.4 | 1.37701 | 1(Win) | true |
| jsonifier | 4265.28 | 0.338618 | 9771.38ms | 399947 | 4890 | 4.48373e+08 | 89424.2 | 0.117837 | 2(Loss) | true |
| simdjson (reflection) | 3590.45 | 0.842311 | 5836.14ms | 399947 | 30 | 2.402e+07 | 106231 | 1.20625 | 3(Loss) | true |
| simdjson (ondemand) | 3264.81 | 0.834935 | 5821.96ms | 399947 | 320 | 3.04469e+08 | 116827 | 1.58638 | 4(Loss) | true |
| glaze | 2735.76 | 0.303173 | 7256.82ms | 399947 | 1280 | 2.28685e+08 | 139420 | 0.23014 | 5(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1666.88 | 0.602604 | 7759.53ms | 264040 | 320 | 2.65183e+08 | 151066 | 1.11161 | 1(Win) | true |
| jsonifier (two-stage) | 1399.85 | 0.313804 | 9452.24ms | 264040 | 2560 | 8.15706e+08 | 179882 | 0.250568 | 2(Loss) | true |
| glaze | 1293.06 | 0.43248 | 5195ms | 264040 | 320 | 2.26976e+08 | 194738 | 0.461404 | 3(Loss) | true |
| simdjson (reflection) | 1060.5 | 0.702121 | 6119.18ms | 264040 | 80 | 2.22348e+08 | 237443 | 0.32642 | 4(Loss) | true |
| simdjson (ondemand) | 987.246 | 1.24158 | 6809.6ms | 264040 | 30 | 3.00857e+08 | 255061 | 0.588928 | 5(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2200.14 | 0.700998 | 7575.56ms | 264040 | 640 | 4.11959e+08 | 114451 | 3.27828 | 1(Win) | true |
| jsonifier (two-stage) | 1756.52 | 0.6306 | 9169.4ms | 264040 | 640 | 5.23025e+08 | 143356 | 0.247548 | 2(Loss) | true |
| glaze | 1612.3 | 0.458969 | 9792.45ms | 264040 | 160 | 8.22114e+07 | 156179 | 0.41767 | 3(Loss) | true |
| simdjson (reflection) | 1239.16 | 0.302335 | 6350.76ms | 264040 | 320 | 1.20784e+08 | 203209 | 0.538401 | 4(Loss) | true |
| simdjson (ondemand) | 1186.97 | 0.501473 | 5941.21ms | 264040 | 160 | 1.81082e+08 | 212144 | 0.545992 | 5(Loss) | true |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12391.3 | 0.41597 | 2169.7ms | 264040 | 4890 | 3.49412e+07 | 20321.3 | 0.0872844 | 1(Win) | true |
| simdjson (reflection) | 8743.18 | 0.338593 | 2884.17ms | 264040 | 4890 | 4.65015e+07 | 28800.5 | 1.13822 | 2(Loss) | true |
| glaze | 3185.87 | 0.0942466 | 8284.19ms | 263923 | 4890 | 2.71106e+07 | 79004.1 | 1.68249 | 3(Loss) | true |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12991.1 | 0.425819 | 1997.58ms | 264040 | 320 | 2.17997e+06 | 19383.2 | 0.302202 | 1(Win) | true |
| simdjson (reflection) | 8938.31 | 0.449776 | 2965.02ms | 264040 | 1280 | 2.0551e+07 | 28171.8 | 0.304062 | 2(Loss) | true |
| glaze | 3726.11 | 0.185941 | 6835.68ms | 263923 | 2560 | 4.03863e+07 | 67549.5 | 0.491286 | 3(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1945.84 | 0.408762 | 10132.3ms | 399947 | 2560 | 1.64352e+09 | 196018 | 0.223744 | 1(Win) | true |
| jsonifier (two-stage) | 1806.98 | 0.736044 | 5908.31ms | 399947 | 1280 | 3.08971e+09 | 211081 | 0.311273 | 2(Loss) | true |
| glaze | 1671.38 | 0.396342 | 5963.85ms | 399947 | 1280 | 1.04714e+09 | 228206 | 0.294635 | 3(Loss) | true |
| simdjson (reflection) | 1483.95 | 0.585818 | 6634.66ms | 399947 | 640 | 1.45101e+09 | 257030 | 1.16918 | 4(Loss) | true |
| simdjson (ondemand) | 1353.36 | 0.685585 | 7191.09ms | 399947 | 30 | 1.12e+08 | 281830 | 0.0909174 | 5(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2412.53 | 0.570536 | 10071.7ms | 399947 | 160 | 1.30181e+08 | 158099 | 0.360996 | 1(Win) | true |
| jsonifier (two-stage) | 2352.23 | 0.604017 | 5013.57ms | 399947 | 640 | 6.13936e+08 | 162152 | 0.378854 | 2(Loss) | true |
| glaze | 1947.16 | 1.65223 | 5765.37ms | 399947 | 80 | 8.37976e+08 | 195885 | 0.83682 | 3(Loss) | true |
| simdjson (ondemand) | 1677.21 | 0.413614 | 6733.16ms | 399947 | 320 | 2.83119e+08 | 227413 | 1.42866 | 4(Loss) | true |
| simdjson (reflection) | 1602.69 | 0.905551 | 6793.52ms | 399947 | 30 | 1.39332e+08 | 237986 | 0.842637 | 5(Loss) | true |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12308.9 | 0.552622 | 2983.46ms | 399947 | 320 | 9.38364e+06 | 30987.2 | 1.72278 | 1(Win) | true |
| glaze | 1442.67 | 0.827923 | 6612.63ms | 399830 | 320 | 1.53231e+09 | 264306 | 1.82487 | 2(Loss) | true |
| simdjson (reflection) | 374.511 | 0.503992 | 7671.86ms | 399947 | 40 | 1.05386e+09 | 1.01844e+06 | 0.481575 | 3(Loss) | true |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 14481 | 0.523001 | 2803.4ms | 399947 | 80 | 1.5181e+06 | 26339.2 | 0.13382 | 1(Win) | true |
| glaze | 2812.8 | 0.225632 | 7584.2ms | 399830 | 320 | 2.99381e+07 | 135562 | 0.341079 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 281.738 | 1.39454 | 7723.83ms | 399947 | 320 | 1.14058e+11 | 1.35381e+06 | 5.33832 | -(Loss) | false |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 724.27 | 0.33139 | 615.929ms | 4630 | 2560 | 1.04491e+06 | 6096.5 | 0.0738674 | 1(Win) | true |
| jsonifier (two-stage) | 563.894 | 0.95236 | 810.694ms | 4630 | 160 | 889795 | 7830.4 | 0.447518 | 2(Loss) | true |
| simdjson (reflection) | 431.438 | 2.90823 | 1279ms | 4630 | 320 | 2.83487e+07 | 10234.4 | 0.779896 | 3(Loss) | true |
| glaze | 373.563 | 0.558234 | 1225.79ms | 4630 | 320 | 1.39321e+06 | 11820 | 1.407 | 4(Loss) | true |
| simdjson (ondemand) | 348.227 | 2.94197 | 1294.98ms | 4630 | 160 | 2.22657e+07 | 12680 | 0.339537 | 5(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 886.115 | 0.67709 | 637.962ms | 4630 | 1280 | 1.45708e+06 | 4983 | 1.85185 | 1(Win) | true |
| jsonifier (two-stage) | 735.919 | 0.792742 | 781.57ms | 4630 | 2560 | 5.7917e+06 | 6000 | 0.294196 | 2(Loss) | true |
| simdjson (reflection) | 502.619 | 0.946727 | 1166.7ms | 4630 | 2560 | 1.77081e+07 | 8785 | 0.20901 | 3(Loss) | true |
| glaze | 493.133 | 0.163399 | 1014.23ms | 4630 | 1280 | 273996 | 8954 | 0.744912 | 4(Loss) | true |
| simdjson (ondemand) | 425.179 | 2.71759 | 1283.17ms | 4630 | 30 | 2.3895e+06 | 10385.1 | 0.409165 | 5(Loss) | true |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2078.08 | 1.24946 | 249.996ms | 4630 | 160 | 112771 | 2124.8 | 0.449775 | 1(Win) | true |
| glaze | 1413.78 | 1.25772 | 391.862ms | 4630 | 80 | 123440 | 3123.2 | 1.6129 | 2(Loss) | true |
| simdjson (reflection) | 697.362 | 2.30133 | 909.822ms | 4630 | 30 | 636980 | 6331.73 | 1.64384 | 3(Loss) | true |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2114.71 | 0.803284 | 256.594ms | 4630 | 320 | 90022.1 | 2088 | 2.10053 | 1(Win) | true |
| glaze | 1231.97 | 1.18852 | 364.593ms | 4630 | 4890 | 8.87322e+06 | 3584.1 | 0.239243 | 2(Loss) | true |
| simdjson (reflection) | 709.989 | 0.411716 | 630.653ms | 4630 | 4890 | 3.20599e+06 | 6219.12 | 1.99929 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1573.22 | 0.425797 | 1041.61ms | 14795 | 4890 | 7.13129e+06 | 8968.64 | 0.861876 | 1(Win) | true |
| jsonifier STATISTICAL TIE | 1210.63 | 4.24642 | 1288.81ms | 14795 | 2560 | 6.27039e+08 | 11654.8 | 0.837515 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1196.05 | 0.291657 | 1268.76ms | 14795 | 320 | 378812 | 11796.8 | 0.0271334 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1167.7 | 0.734174 | 1211.13ms | 14795 | 2560 | 2.01469e+07 | 12083.3 | 3.18964 | 2(Tie) | true |
| glaze | 930.615 | 2.08457 | 1665.59ms | 14795 | 160 | 1.59825e+07 | 15161.6 | 4.8462 | 5(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2054 | 0.963613 | 885.515ms | 14795 | 30 | 131449 | 6869.33 | 0.124378 | 1(Win) | true |
| jsonifier | 1892.94 | 0.75482 | 914.75ms | 14795 | 1280 | 4.05184e+06 | 7453.8 | 0.115511 | 2(Loss) | true |
| simdjson (reflection) | 1596 | 0.290239 | 1089.46ms | 14795 | 1280 | 842722 | 8840.6 | 0.703969 | 3(Loss) | true |
| simdjson (ondemand) | 1250.5 | 0.854809 | 1484.58ms | 14795 | 160 | 1.48841e+06 | 11283.2 | 1.23249 | 4(Loss) | true |
| glaze DID NOT CONVERGE | 966.101 | 0.912846 | 1832.79ms | 14795 | 2560 | 4.55009e+07 | 14604.7 | 10.4555 | -(Loss) | false |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 5033.39 | 2.5944 | 308.159ms | 14795 | 40 | 211564 | 2803.2 | 2.33645 | 1(Win) | true |
| glaze | 2400.41 | 0.900059 | 616.019ms | 14795 | 1280 | 3.58271e+06 | 5878 | 1.14254 | 2(Loss) | true |
| simdjson (reflection) | 95.4526 | 1.75014 | 7234.35ms | 14795 | 640 | 4.28329e+09 | 147818 | 3.52263 | 3(Loss) | true |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6015.87 | 0.577667 | 249.732ms | 14795 | 1280 | 234962 | 2345.4 | 2.68827 | 1(Win) | true |
| glaze | 2932.66 | 1.05081 | 533.256ms | 14795 | 160 | 408959 | 4811.2 | 0.562169 | 2(Loss) | true |
| simdjson (reflection) | 100.602 | 0.652315 | 7195.22ms | 14795 | 160 | 1.33921e+08 | 140251 | 0.423719 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1099.26 | 1.0318 | 430.663ms | 5092 | 160 | 332417 | 4417.6 | 1.20968 | 1(Win) | true |
| jsonifier (two-stage) | 955.814 | 0.220908 | 544.744ms | 5092 | 1280 | 161236 | 5080.6 | 0.0590133 | 2(Loss) | true |
| glaze | 809.1 | 0.314942 | 611.95ms | 5092 | 4890 | 1.7472e+06 | 6001.87 | 0.612962 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 652.466 | 0.519915 | 768.831ms | 5092 | 2560 | 3.83324e+06 | 7442.7 | 1.38813 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 649.108 | 0.493128 | 676.242ms | 5092 | 640 | 871049 | 7481.2 | 2.4361 | 4(Tie) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1604.05 | 0.713951 | 416.094ms | 5092 | 1280 | 597979 | 3027.4 | 0.636734 | 1(Win) | true |
| jsonifier (two-stage) | 1208.23 | 1.53153 | 536.591ms | 5092 | 30 | 113671 | 4019.2 | 1.25786 | 2(Loss) | true |
| glaze | 1076.27 | 1.80209 | 552.157ms | 5092 | 40 | 264455 | 4512 | 0.142045 | 3(Loss) | true |
| simdjson (ondemand) | 949.052 | 0.874274 | 649.898ms | 5092 | 80 | 160097 | 5116.8 | 0.313676 | 4(Loss) | true |
| simdjson (reflection) | 884.795 | 0.516864 | 655.874ms | 5092 | 640 | 515019 | 5488.4 | 0.00728757 | 5(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7528.85 | 2.31499 | 81.206ms | 5092 | 1280 | 285382 | 645 | 1.79659 | 1(Win) | true |
| simdjson (reflection) | 6590.81 | 3.37687 | 94.271ms | 5092 | 320 | 198097 | 736.8 | 0.324675 | 2(Loss) | true |
| glaze | 1570.95 | 1.00757 | 323.74ms | 5092 | 80 | 77606.2 | 3091.2 | 0.206612 | 3(Loss) | true |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8025.3 | 2.31922 | 64.0579ms | 5092 | 2560 | 504169 | 605.1 | 0.770745 | 1(Win) | true |
| simdjson (reflection) | 6917.69 | 0.98885 | 74.3949ms | 5092 | 4890 | 235627 | 701.984 | 1.7379 | 2(Loss) | true |
| glaze | 1821.77 | 2.16571 | 337.714ms | 5092 | 80 | 266613 | 2665.6 | 0.358852 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1970.31 | 1.51538 | 609.673ms | 11724 | 30 | 221843 | 5674.67 | 1.37195 | 1(Win) | true |
| jsonifier (two-stage) | 1833.17 | 0.658481 | 673.146ms | 11724 | 80 | 129040 | 6099.2 | 0.421496 | 2(Loss) | true |
| simdjson (ondemand) | 1585.27 | 0.172431 | 736.578ms | 11724 | 1280 | 189317 | 7053 | 0.178329 | 3(Loss) | true |
| simdjson (reflection) | 1509.3 | 0.422705 | 753.611ms | 11724 | 1280 | 1.25512e+06 | 7408 | 1.78621 | 4(Loss) | true |
| glaze | 1308.3 | 0.2232 | 894.802ms | 11724 | 2560 | 931463 | 8546.1 | 0.36288 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2490.4 | 1.25855 | 568.904ms | 11724 | 80 | 255414 | 4489.6 | 0.355114 | 1(Win) | true |
| jsonifier (two-stage) | 2301.73 | 0.626831 | 661.19ms | 11724 | 160 | 148342 | 4857.6 | 0.463269 | 2(Loss) | true |
| simdjson (reflection) | 1922.33 | 0.134122 | 681.661ms | 11724 | 4890 | 297583 | 5816.33 | 1.26981 | 3(Loss) | true |
| simdjson (ondemand) | 1880.28 | 0.264196 | 703.587ms | 11724 | 1280 | 315915 | 5946.4 | 0.425589 | 4(Loss) | true |
| glaze | 1559.83 | 1.10974 | 941.403ms | 11724 | 30 | 189828 | 7168 | 1.52403 | 5(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16273.4 | 0.983512 | 72.681ms | 11724 | 4890 | 223287 | 687.064 | 0.713019 | 1(Win) | true |
| glaze | 2708.9 | 0.503599 | 427.126ms | 11746 | 320 | 138775 | 4135.2 | 0.212355 | 2(Loss) | true |
| simdjson (reflection) | 324.001 | 0.180482 | 3773.25ms | 11724 | 640 | 2.48261e+06 | 34508.8 | 0.0115926 | 3(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17668.1 | 1.1941 | 66.5321ms | 11724 | 4890 | 279231 | 632.828 | 1.05842 | 1(Win) | true |
| glaze | 3120.21 | 0.297534 | 372.276ms | 11746 | 2560 | 292096 | 3590.1 | 0.298933 | 2(Loss) | true |
| simdjson (reflection) | 264.498 | 1.41449 | 4532.9ms | 11724 | 40 | 1.43009e+07 | 42272 | 1.53548 | 3(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1192.34 | 1.98863 | 391.333ms | 4857 | 80 | 477459 | 3884.8 | 1.50502 | 1(Win) | true |
| jsonifier (two-stage) | 1128.65 | 0.442498 | 410.456ms | 4857 | 320 | 105533 | 4104 | 0.430697 | 2(Loss) | true |
| glaze STATISTICAL TIE | 961.596 | 0.581908 | 479.857ms | 4857 | 4890 | 3.84209e+06 | 4816.99 | 0.584426 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 940.749 | 2.03568 | 556.763ms | 4857 | 30 | 301390 | 4923.73 | 1.53584 | 3(Tie) | true |
| simdjson (ondemand) | 867.285 | 0.528707 | 606.431ms | 4857 | 320 | 255149 | 5340.8 | 1.18413 | 5(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2123.99 | 0.523797 | 281.462ms | 4857 | 1280 | 167019 | 2180.8 | 0.274374 | 1(Win) | true |
| glaze | 1569.74 | 0.654626 | 366.667ms | 4857 | 1280 | 477613 | 2950.8 | 1.77097 | 2(Loss) | true |
| jsonifier (two-stage) | 1351.3 | 0.479214 | 403.78ms | 4857 | 1280 | 345382 | 3427.8 | 0.0408592 | 3(Loss) | true |
| simdjson (reflection) | 1030.17 | 0.761336 | 579.246ms | 4857 | 4890 | 5.73031e+06 | 4496.33 | 1.87452 | 4(Loss) | true |
| simdjson (ondemand) | 914.98 | 1.56065 | 554.77ms | 4857 | 80 | 499359 | 5062.4 | 0.628141 | 5(Loss) | true |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8888.72 | 2.2265 | 57.7321ms | 4857 | 4890 | 658280 | 521.109 | 2.39914 | 1(Win) | true |
| simdjson (reflection) | 6934.13 | 4.1727 | 81.8189ms | 4857 | 320 | 248620 | 668 | 2.90698 | 2(Loss) | true |
| glaze | 2212.88 | 1.59934 | 223.303ms | 4857 | 2560 | 2.86909e+06 | 2093.2 | 0.124058 | 3(Loss) | true |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 10945.2 | 4.63886 | 53.8309ms | 4857 | 640 | 246657 | 423.2 | 5.36673 | -(Win) | false |
| simdjson (reflection) | 8434.08 | 3.60161 | 93.282ms | 4857 | 640 | 250399 | 549.2 | 1.78827 | 2(Loss) | true |
| glaze | 2746.68 | 3.08719 | 197.214ms | 4857 | 80 | 216839 | 1686.4 | 2.13178 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1521.26 | 1.80353 | 643.356ms | 7376 | 80 | 556382 | 4624 | 0.618982 | 1(Win) | true |
| glaze | 1399.55 | 0.752042 | 653.567ms | 7376 | 30 | 42862.1 | 5026.13 | 0.169492 | 2(Loss) | true |
| jsonifier (two-stage) STATISTICAL TIE | 993.882 | 4.26022 | 633.759ms | 7376 | 320 | 2.90929e+07 | 7077.6 | 1.01621 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 965.434 | 1.51316 | 736.445ms | 7376 | 4890 | 5.94395e+07 | 7286.16 | 1.22741 | 3(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 767.133 | 1.21513 | 968.835ms | 7376 | 1280 | 1.58912e+07 | 9169.6 | 5.14149 | -(Loss) | false |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1886.48 | 1.11999 | 444.587ms | 7376 | 320 | 558108 | 3728.8 | 1.04034 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1876.01 | 0.916404 | 545.933ms | 7376 | 320 | 377828 | 3749.6 | 1.61629 | 1(Tie) | true |
| glaze | 1708.68 | 1.5913 | 499.875ms | 7376 | 160 | 686662 | 4116.8 | 1.56848 | 3(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 1599.29 | 0.90255 | 623.459ms | 7376 | 160 | 252146 | 4398.4 | 5.85616 | -(Loss) | false |
| simdjson (ondemand) | 1117.03 | 0.743309 | 728.753ms | 7376 | 2560 | 5.60903e+06 | 6297.3 | 0.175956 | 5(Loss) | true |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 10420 | 1.66665 | 78.4151ms | 7376 | 4890 | 619016 | 675.076 | 6.47331 | -(Win) | false |
| glaze | 2111.83 | 0.498666 | 367.626ms | 7376 | 2560 | 706290 | 3330.9 | 2.55968 | 2(Loss) | true |
| simdjson (reflection) | 326.598 | 0.440449 | 2359.69ms | 7376 | 30 | 269978 | 21538.1 | 0.158228 | 3(Loss) | true |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11668.8 | 1.16891 | 68.226ms | 7376 | 4890 | 242806 | 602.83 | 2.05845 | 1(Win) | true |
| glaze | 2652.05 | 0.553456 | 305.299ms | 7376 | 1280 | 275838 | 2652.4 | 0.0301523 | 2(Loss) | true |
| simdjson (reflection) | 284.963 | 0.637014 | 2484.4ms | 7376 | 1280 | 3.165e+07 | 24685 | 1.07855 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1283.26 | 1.65125 | 366.556ms | 4390 | 2560 | 7.4296e+06 | 3262.5 | 1.80882 | 1(Win) | true |
| jsonifier (two-stage) | 903.537 | 2.25318 | 553.534ms | 4390 | 30 | 327002 | 4633.6 | 0.549451 | 2(Loss) | true |
| glaze STATISTICAL TIE | 768.697 | 1.97698 | 544.601ms | 4390 | 40 | 463751 | 5446.4 | 0.273438 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 761.538 | 1.44382 | 823.935ms | 4390 | 40 | 252020 | 5497.6 | 0.50702 | 3(Tie) | true |
| simdjson (ondemand) | 629.229 | 1.01599 | 816.68ms | 4390 | 4890 | 2.23459e+07 | 6653.59 | 0.629035 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1949.81 | 0.680398 | 285.183ms | 4390 | 640 | 136600 | 2147.2 | 2.44275 | 1(Win) | true |
| jsonifier (two-stage) | 1185.14 | 0.706392 | 434.68ms | 4390 | 1280 | 797059 | 3532.6 | 0.725045 | 2(Loss) | true |
| glaze | 1067.15 | 0.913976 | 526.185ms | 4390 | 160 | 205717 | 3923.2 | 1.74274 | 3(Loss) | true |
| simdjson (reflection) | 890.015 | 0.590453 | 577.46ms | 4390 | 640 | 493725 | 4704 | 1.34228 | 4(Loss) | true |
| simdjson (ondemand) | 747.613 | 1.42872 | 704.568ms | 4390 | 40 | 256053 | 5600 | 0.568182 | 5(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 8159.49 | 1.41137 | 55.7002ms | 4390 | 4890 | 256446 | 513.099 | 0.85036 | 1(Win) | true |
| simdjson (reflection) | 7249.58 | 1.70237 | 59.936ms | 4390 | 2560 | 247429 | 577.5 | 0.469729 | 2(Loss) | true |
| glaze | 1502.57 | 0.602295 | 345.026ms | 4390 | 4890 | 1.37717e+06 | 2786.32 | 0.0352827 | 3(Loss) | true |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 10110.2 | 2.36416 | 44.8858ms | 4390 | 2560 | 245359 | 414.1 | 0.314922 | 1(Win) | true |
| simdjson (reflection) | 8069.83 | 3.83217 | 54.0951ms | 4390 | 640 | 252970 | 518.8 | 1.17005 | 2(Loss) | true |
| glaze | 1684.35 | 1.20355 | 268.878ms | 4390 | 320 | 286380 | 2485.6 | 0.485123 | 3(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2531.4 | 0.450858 | 449.317ms | 11521 | 640 | 245087 | 4340.4 | 0.789523 | 1(Win) | true |
| jsonifier (two-stage) | 1971.03 | 1.42867 | 602.909ms | 11521 | 40 | 253700 | 5574.4 | 0.0382848 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1627.07 | 0.555742 | 754.863ms | 11521 | 640 | 901350 | 6752.8 | 0.9156 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1615.49 | 0.249486 | 695.802ms | 11521 | 1280 | 368530 | 6801.2 | 0.0176408 | 3(Tie) | true |
| simdjson (ondemand) | 1530.06 | 0.149556 | 734.753ms | 11521 | 4890 | 564000 | 7180.93 | 0.900736 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2947.63 | 0.238034 | 428.689ms | 11521 | 4890 | 384966 | 3727.5 | 4.52355 | 1(Win) | true |
| jsonifier (two-stage) | 2416.27 | 0.408985 | 584.284ms | 11521 | 1280 | 442704 | 4547.2 | 0.184388 | 2(Loss) | true |
| simdjson (reflection) | 2170.37 | 1.0478 | 616.684ms | 11521 | 40 | 112545 | 5062.4 | 0.461409 | 3(Loss) | true |
| glaze | 1530.52 | 0.557963 | 756.693ms | 11521 | 640 | 1.02682e+06 | 7178.8 | 0.416158 | 4(Loss) | true |
| simdjson (ondemand) | 1442.73 | 0.534781 | 977.624ms | 11521 | 640 | 1.06155e+06 | 7615.6 | 1.19592 | 5(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 16044.5 | 7.66286 | 97.281ms | 11521 | 80 | 220292 | 684.8 | 4.90196 | 1(Win) | true |
| glaze | 2500.52 | 0.511791 | 461.879ms | 11521 | 640 | 323657 | 4394 | 0.480159 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 264.193 | 0.195065 | 5022.52ms | 11521 | 4890 | 3.21813e+07 | 41588 | 6.59333 | -(Loss) | false |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 20301.7 | 1.83053 | 58.785ms | 11521 | 2560 | 251252 | 541.2 | 1.02414 | 1(Win) | true |
| glaze | 2639.14 | 0.79957 | 448.892ms | 11521 | 320 | 354583 | 4163.2 | 0.19253 | 2(Loss) | true |
| simdjson (reflection) | 292.813 | 1.34286 | 4773.36ms | 11521 | 40 | 1.0156e+07 | 37523.2 | 0.600549 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2296.16 | 2.6127 | 222.361ms | 4669 | 80 | 205360 | 1939.2 | 2.88462 | 1(Win) | true |
| glaze STATISTICAL TIE | 1249.08 | 1.59956 | 471.004ms | 4669 | 80 | 260112 | 3564.8 | 0.357782 | 2(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1212.87 | 2.19646 | 354.117ms | 4669 | 1280 | 8.32289e+06 | 3671.2 | 2.83473 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE DID NOT CONVERGE | 1019.14 | 2.11978 | 470.723ms | 4669 | 30 | 257323 | 4369.07 | 7.74775 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 988.26 | 1.91711 | 537.742ms | 4669 | 40 | 298441 | 4505.6 | 1.30841 | 4(Tie) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2728.37 | 1.66277 | 222.83ms | 4669 | 320 | 235642 | 1632 | 2.5788 | 1(Win) | true |
| jsonifier (two-stage) | 1350.9 | 1.38955 | 362.153ms | 4669 | 2560 | 5.37019e+06 | 3296.1 | 0.798165 | 2(Loss) | true |
| glaze | 1247.26 | 1.94759 | 396.636ms | 4669 | 640 | 3.09394e+06 | 3570 | 1.90152 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1005.96 | 0.71635 | 447.137ms | 4669 | 4890 | 4.91642e+06 | 4426.34 | 1.35417 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 984.531 | 2.12544 | 446.376ms | 4669 | 30 | 277210 | 4522.67 | 0.37594 | 4(Tie) | true |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11465.8 | 2.15068 | 42.431ms | 4669 | 4890 | 341113 | 388.345 | 3.25583 | 1(Win) | true |
| simdjson (reflection) | 6047.41 | 2.56375 | 74.335ms | 4669 | 2560 | 912222 | 736.3 | 0.284399 | 2(Loss) | true |
| glaze | 1474.02 | 0.386606 | 303.994ms | 4669 | 2560 | 349157 | 3020.8 | 2.04716 | 3(Loss) | true |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13383.5 | 2.81072 | 38.176ms | 4669 | 2560 | 223862 | 332.7 | 2.49538 | 1(Win) | true |
| simdjson (reflection) | 6972.18 | 1.15279 | 67.6841ms | 4669 | 4890 | 265044 | 638.639 | 2.97192 | 2(Loss) | true |
| glaze | 1759.68 | 1.1385 | 264.164ms | 4669 | 320 | 265579 | 2530.4 | 0.346566 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2656.07 | 0.480279 | 337.092ms | 9249 | 2560 | 651238 | 3320.9 | 0.279263 | 1(Win) | true |
| jsonifier (two-stage) | 2376.22 | 1.49252 | 407.001ms | 9249 | 80 | 245553 | 3712 | 3.20285 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1778.76 | 0.93251 | 494.339ms | 9249 | 640 | 1.36849e+06 | 4958.8 | 0.641338 | 3(Tie) | true |
| glaze STATISTICAL TIE | 1751.36 | 0.690859 | 545.36ms | 9249 | 640 | 774817 | 5036.4 | 2.95206 | 3(Tie) | true |
| simdjson (ondemand) | 1416.45 | 2.55542 | 652.622ms | 9249 | 40 | 1.01291e+06 | 6227.2 | 3.21782 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2771.88 | 1.11861 | 357.215ms | 9249 | 4890 | 6.19592e+06 | 3182.15 | 2.35814 | 1(Win) | true |
| jsonifier (two-stage) | 2410.77 | 0.577603 | 385.58ms | 9249 | 1280 | 571671 | 3658.8 | 0.439223 | 2(Loss) | true |
| simdjson (reflection) | 2069.38 | 0.962172 | 487.234ms | 9249 | 80 | 134556 | 4262.4 | 0.149925 | 3(Loss) | true |
| simdjson (ondemand) | 1923.53 | 1.12265 | 496.946ms | 9249 | 160 | 424036 | 4585.6 | 0.279916 | 4(Loss) | true |
| glaze | 1701.49 | 0.801941 | 492.929ms | 9249 | 320 | 553050 | 5184 | 2.9552 | 5(Loss) | true |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13487.1 | 1.44961 | 69.8519ms | 9249 | 2560 | 230089 | 654 | 2.53353 | 1(Win) | true |
| glaze | 1786.11 | 0.906661 | 489.941ms | 9249 | 1280 | 2.5661e+06 | 4938.4 | 0.306848 | 2(Loss) | true |
| simdjson (reflection) | 280.907 | 0.368278 | 3123.97ms | 9249 | 1280 | 1.7117e+07 | 31400.2 | 0.37249 | 3(Loss) | true |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 17094.1 | 5.45682 | 58.976ms | 9249 | 320 | 253705 | 516 | 0.462963 | 1(Win) | true |
| glaze | 2238.26 | 1.02243 | 445.935ms | 9249 | 160 | 259751 | 3940.8 | 0.765512 | 2(Loss) | true |
| simdjson (reflection) | 296.708 | 0.468971 | 3223.37ms | 9249 | 320 | 6.21976e+06 | 29728 | 1.35283 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 481.523 | 0.664553 | 1034.74ms | 4604 | 320 | 1.17502e+06 | 9118.4 | 0.54693 | 1(Win) | true |
| jsonifier (two-stage) | 469.656 | 0.675902 | 1135.54ms | 4604 | 160 | 638850 | 9348.8 | 1.75897 | 2(Loss) | true |
| glaze | 375.378 | 0.551625 | 1261.99ms | 4604 | 1280 | 5.32883e+06 | 11696.8 | 1.52551 | 3(Loss) | true |
| simdjson (reflection) | 355.967 | 1.40596 | 1301.7ms | 4604 | 1280 | 3.84949e+07 | 12334.6 | 0.476052 | 4(Loss) | true |
| simdjson (ondemand) | 285.23 | 0.671367 | 1474.07ms | 4604 | 320 | 3.41783e+06 | 15393.6 | 0.0728105 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 636.041 | 0.714053 | 1011.38ms | 4604 | 320 | 777520 | 6903.2 | 0.174135 | 1(Win) | true |
| jsonifier (two-stage) | 528.272 | 1.25077 | 1108.3ms | 4604 | 30 | 324215 | 8311.47 | 0.814664 | 2(Loss) | true |
| simdjson (reflection) | 413.615 | 0.851705 | 1274.78ms | 4604 | 4890 | 3.99729e+07 | 10615.5 | 2.17987 | 3(Loss) | true |
| glaze | 378.311 | 0.519403 | 1362.2ms | 4604 | 2560 | 9.30297e+06 | 11606.1 | 0.750894 | 4(Loss) | true |
| simdjson (ondemand) | 290.468 | 0.851663 | 1679.04ms | 4604 | 4890 | 8.10434e+07 | 15116 | 0.70035 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1578.71 | 0.701783 | 305.931ms | 4604 | 1280 | 487618 | 2781.2 | 3.14807 | 1(Win) | true |
| simdjson (reflection) | 1477.3 | 0.249042 | 361.468ms | 4918 | 4890 | 305699 | 3174.82 | 1.13787 | 2(Loss) | true |
| glaze | 761.114 | 0.685752 | 580.193ms | 4604 | 320 | 500790 | 5768.8 | 0.543781 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1474.78 | 0.534361 | 302.266ms | 4604 | 1280 | 323964 | 2977.2 | 0.839329 | 1(Win) | true |
| simdjson (reflection) | 1296.13 | 0.361183 | 363.199ms | 4918 | 2560 | 437297 | 3618.6 | 0.880959 | 2(Loss) | true |
| glaze | 806.643 | 0.818742 | 535.327ms | 4604 | 160 | 317777 | 5443.2 | 2.22356 | 3(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2068.46 | 0.788031 | 1325.12ms | 24579 | 30 | 239244 | 11332.3 | 0.3003 | 1(Win) | true |
| jsonifier (two-stage) | 2016.83 | 0.663611 | 1407.59ms | 24579 | 40 | 237946 | 11622.4 | 0.147059 | 2(Loss) | true |
| simdjson (reflection) | 1670.59 | 0.771446 | 1512.42ms | 24579 | 1280 | 1.49972e+07 | 14031.2 | 1.35268 | 3(Loss) | true |
| glaze | 1488.01 | 0.36313 | 1864.28ms | 24579 | 640 | 2.0942e+06 | 15752.8 | 0.213751 | 4(Loss) | true |
| simdjson (ondemand) | 1370.7 | 0.802086 | 1790.88ms | 24579 | 1280 | 2.40821e+07 | 17101 | 0.402762 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2388.75 | 0.262333 | 1297.95ms | 24579 | 1280 | 848204 | 9812.8 | 0.0815927 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2079.23 | 1.35035 | 1601.25ms | 24579 | 80 | 1.85399e+06 | 11273.6 | 3.37356 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1980.47 | 2.00203 | 1466.52ms | 24579 | 30 | 1.68443e+06 | 11835.7 | 2.51293 | 2(Tie) | true |
| simdjson (ondemand) | 1837.4 | 0.646016 | 1768.8ms | 24579 | 30 | 203764 | 12757.3 | 0.0669344 | 4(Loss) | true |
| glaze | 1572.36 | 0.574479 | 1860.47ms | 24579 | 30 | 220035 | 14907.7 | 0.807848 | 5(Loss) | true |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6953.74 | 0.793062 | 336.341ms | 24579 | 2560 | 1.82956e+06 | 3370.9 | 4.11594 | 1(Win) | true |
| glaze | 2303.16 | 0.647392 | 1043.06ms | 24579 | 4890 | 2.12288e+07 | 10177.5 | 2.54805 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 128.568 | 2.53374 | 8225.49ms | 24893 | 160 | 3.50213e+09 | 184648 | 5.27156 | -(Loss) | false |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6281.42 | 0.287662 | 369.194ms | 24579 | 2560 | 294998 | 3731.7 | 1.45452 | 1(Win) | true |
| glaze | 3004.4 | 0.405427 | 874.537ms | 24579 | 640 | 640350 | 7802 | 0.525296 | 2(Loss) | true |
| simdjson (reflection) | 166.742 | 0.542585 | 7723.39ms | 24893 | 40 | 2.38704e+07 | 142374 | 0.0269784 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 593.982 | 1.15648 | 767.499ms | 4604 | 80 | 584639 | 7392 | 0.0865052 | 1(Win) | true |
| jsonifier (two-stage) | 440.676 | 0.472645 | 958.976ms | 4604 | 640 | 1.41932e+06 | 9963.6 | 0.562874 | 2(Loss) | true |
| simdjson (reflection) | 424.981 | 0.180699 | 1050.09ms | 4604 | 4890 | 1.70433e+06 | 10331.6 | 0.571046 | 3(Loss) | true |
| glaze | 373.309 | 0.493373 | 1250.19ms | 4604 | 320 | 1.07754e+06 | 11761.6 | 0.149864 | 4(Loss) | true |
| simdjson (ondemand) | 316.301 | 0.273203 | 1402.72ms | 4604 | 4890 | 7.03313e+06 | 13881.4 | 2.9001 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 788.945 | 0.563664 | 811.359ms | 4604 | 4890 | 4.81202e+06 | 5565.3 | 0.692281 | 1(Win) | true |
| jsonifier (two-stage) | 606.587 | 0.906659 | 920.958ms | 4604 | 160 | 689117 | 7238.4 | 1.35194 | 2(Loss) | true |
| simdjson (reflection) | 529.768 | 0.723502 | 1019.95ms | 4604 | 80 | 287653 | 8288 | 0.699844 | 3(Loss) | true |
| glaze | 447.035 | 0.689974 | 1275.9ms | 4604 | 30 | 137776 | 9821.87 | 1.11684 | 4(Loss) | true |
| simdjson (ondemand) | 371.239 | 0.930554 | 1485.61ms | 4604 | 30 | 363386 | 11827.2 | 0.144509 | 5(Loss) | true |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1483.85 | 0.600976 | 290.784ms | 4604 | 1280 | 404776 | 2959 | 2.62902 | 1(Win) | true |
| simdjson (reflection) | 1299.94 | 0.896195 | 353.702ms | 4918 | 640 | 669142 | 3608 | 1.16644 | 2(Loss) | true |
| glaze | 829.094 | 0.6961 | 523.666ms | 4604 | 2560 | 3.47893e+06 | 5295.8 | 0.718905 | 3(Loss) | true |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1525.07 | 0.321488 | 310.76ms | 4604 | 4890 | 418920 | 2879.03 | 4.30518 | 1(Win) | true |
| simdjson (reflection) | 1500.95 | 0.624094 | 343.438ms | 4918 | 320 | 121701 | 3124.8 | 0.566426 | 2(Loss) | true |
| glaze | 953.659 | 0.195007 | 503.062ms | 4604 | 4890 | 394179 | 4604.07 | 0.128555 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 2181.39 | 0.688039 | 1179.42ms | 24579 | 160 | 874596 | 10745.6 | 1.14458 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2051.47 | 0.842315 | 1212.23ms | 24579 | 30 | 277888 | 11426.1 | 0.0746269 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 2012.32 | 0.98981 | 1153.32ms | 24579 | 640 | 8.50778e+06 | 11648.4 | 0.285832 | 2(Tie) | true |
| simdjson (ondemand) | 1574.62 | 0.0756995 | 1577.45ms | 24579 | 4890 | 620969 | 14886.3 | 0.347978 | 4(Loss) | true |
| glaze | 1506.76 | 0.355673 | 1657.66ms | 24579 | 160 | 489848 | 15556.8 | 0.0308452 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2757.3 | 0.604434 | 1142.68ms | 24579 | 1280 | 3.37962e+06 | 8501.2 | 1.64036 | 1(Win) | true |
| jsonifier (two-stage) | 2623.61 | 0.201323 | 1030.75ms | 24579 | 80 | 25882.6 | 8934.4 | 0.287356 | 2(Loss) | true |
| simdjson (reflection) | 2383.7 | 0.426196 | 1257.91ms | 24579 | 80 | 140519 | 9833.6 | 0.227273 | 3(Loss) | true |
| simdjson (ondemand) | 1792.79 | 0.128064 | 1646.94ms | 24579 | 640 | 179434 | 13074.8 | 0.00917712 | 4(Loss) | true |
| glaze | 1700.35 | 0.482007 | 1756.61ms | 24579 | 40 | 176611 | 13785.6 | 0.0929368 | 5(Loss) | true |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 6329.25 | 0.574966 | 346.576ms | 24579 | 2560 | 1.16078e+06 | 3703.5 | 0.885832 | 1(Win) | true |
| glaze | 3007.02 | 0.429732 | 832.938ms | 24579 | 160 | 179544 | 7795.2 | 0.123001 | 2(Loss) | true |
| simdjson (reflection) | 157.85 | 0.391139 | 7450.11ms | 24893 | 2560 | 8.8586e+08 | 150394 | 1.18221 | 3(Loss) | true |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 7927.08 | 0.265505 | 307.397ms | 24579 | 2560 | 157793 | 2957 | 0.878252 | 1(Win) | true |
| glaze | 3438.21 | 0.458468 | 784.435ms | 24579 | 160 | 156315 | 6817.6 | 0.257491 | 2(Loss) | true |
| simdjson (reflection) | 158.445 | 0.203355 | 7887.36ms | 24893 | 2560 | 2.37656e+08 | 149830 | 0.825012 | 3(Loss) | true |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 738.89 | 0.686805 | 169.069ms | 1181 | 2560 | 280574 | 1524.3 | 1.19912 | 1(Win) | true |
| jsonifier (two-stage) | 602.681 | 2.3007 | 224.827ms | 1181 | 160 | 295778 | 1868.8 | 1.74216 | 2(Loss) | true |
| simdjson (reflection) | 472.814 | 0.593929 | 264.922ms | 1181 | 2560 | 512424 | 2382.1 | 1.4684 | 3(Loss) | true |
| simdjson (ondemand) | 417.16 | 0.404332 | 295.742ms | 1181 | 2560 | 305078 | 2699.9 | 0.269651 | 4(Loss) | true |
| glaze | 386.457 | 2.16307 | 307.124ms | 1181 | 640 | 2.54344e+06 | 2914.4 | 3.02602 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 895.871 | 1.39011 | 188.166ms | 1181 | 640 | 195472 | 1257.2 | 2.87392 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 761.83 | 5.52777 | 218.857ms | 1181 | 40 | 267143 | 1478.4 | 0.726744 | 2(Tie) | true |
| glaze STATISTICAL TIE | 721.507 | 0.613165 | 174.902ms | 1181 | 4890 | 448005 | 1561.02 | 1.55645 | 2(Tie) | true |
| simdjson (ondemand) | 634.172 | 3.13362 | 200.85ms | 1181 | 80 | 247782 | 1776 | 3.15985 | 4(Loss) | true |
| simdjson (reflection) | 581.535 | 0.391132 | 211.091ms | 1181 | 4890 | 280610 | 1936.75 | 0.339476 | 5(Loss) | true |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 994.738 | 1.22064 | 126.97ms | 1187 | 640 | 123491 | 1138 | 0.815025 | 1(Win) | true |
| glaze STATISTICAL TIE | 699.472 | 5.03202 | 149.337ms | 1181 | 2560 | 1.68068e+07 | 1610.2 | 1.09337 | 2(Tie) | true |
| jsonifier STATISTICAL TIE | 637.619 | 2.97996 | 85.4031ms | 1181 | 80 | 221661 | 1766.4 | 1.77936 | 2(Tie) | true |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2184.59 | 1.39433 | 80.3228ms | 1181 | 4890 | 252694 | 515.56 | 3.14486 | 1(Win) | true |
| simdjson (reflection) | 1023.43 | 0.640663 | 116.429ms | 1187 | 2560 | 128555 | 1106.1 | 0.0271297 | 2(Loss) | true |
| glaze | 908.487 | 0.524464 | 126.628ms | 1181 | 4890 | 206730 | 1239.74 | 0.318283 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 1252.04 | 0.930406 | 199.988ms | 2496 | 640 | 200254 | 1901.2 | 0.272765 | 1(Win) | true |
| jsonifier | 1179.8 | 1.46845 | 233.8ms | 2496 | 160 | 140446 | 2017.6 | 0.238474 | 2(Loss) | true |
| simdjson (reflection) | 930.414 | 0.890639 | 302.389ms | 2496 | 640 | 332293 | 2558.4 | 0.497822 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 763.772 | 1.30988 | 352.309ms | 2496 | 1280 | 2.13323e+06 | 3116.6 | 0.858888 | 4(Tie) | true |
| glaze STATISTICAL TIE | 750.243 | 0.828536 | 353.937ms | 2496 | 320 | 221135 | 3172.8 | 0.202122 | 4(Tie) | true |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 1390.24 | 1.55801 | 217.53ms | 2496 | 1280 | 910875 | 1712.2 | 3.67912 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 1379.37 | 0.822143 | 198.824ms | 2496 | 2560 | 515306 | 1725.7 | 1.19661 | 1(Tie) | true |
| glaze STATISTICAL TIE | 1337.89 | 2.68331 | 239.239ms | 2496 | 80 | 182339 | 1779.2 | 0.361011 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1249.67 | 0.635276 | 241.128ms | 2496 | 640 | 93713.8 | 1904.8 | 0.0840689 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1194.01 | 2.33732 | 226.261ms | 2496 | 80 | 173702 | 1993.6 | 0.160256 | 4(Tie) | true |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3712.37 | 2.10711 | 74.6289ms | 2496 | 1280 | 233653 | 641.2 | 0.627746 | 1(Win) | true |
| glaze | 1277.17 | 0.579026 | 213.132ms | 2507 | 1280 | 150389 | 1872 | 0.106724 | 2(Loss) | true |
| simdjson (reflection) | 86.6033 | 0.953728 | 2889.1ms | 2502 | 80 | 5.5239e+06 | 27552 | 0 | 3(Loss) | true |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3434.98 | 1.04557 | 89.7101ms | 2496 | 4890 | 256716 | 692.98 | 0.811748 | 1(Win) | true |
| glaze | 1414.38 | 1.57108 | 188.927ms | 2507 | 320 | 225698 | 1690.4 | 0.141777 | 2(Loss) | true |
| simdjson (reflection) | 85.0168 | 2.26718 | 2879.84ms | 2502 | 30 | 1.21467e+07 | 28066.1 | 1.70068 | 3(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1371.28 | 0.248463 | 350.081ms | 4926 | 4890 | 354297 | 3425.85 | 0.211941 | 1(Win) | true |
| jsonifier (two-stage) | 907.893 | 0.663788 | 503.887ms | 4926 | 320 | 377510 | 5174.4 | 0.465983 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 633.331 | 2.71434 | 693.619ms | 4926 | 160 | 6.48596e+06 | 7417.6 | 1.57113 | 3(Tie) | true |
| glaze STATISTICAL TIE | 626.156 | 0.657742 | 863.066ms | 4926 | 2560 | 6.23411e+06 | 7502.6 | 0.0400021 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 606.888 | 0.719375 | 824.227ms | 4926 | 320 | 992275 | 7740.8 | 0.144479 | 3(Tie) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1770.35 | 0.861395 | 369.669ms | 4926 | 640 | 334392 | 2653.6 | 1.92194 | 1(Win) | true |
| jsonifier (two-stage) | 1324.07 | 0.413729 | 499.869ms | 4926 | 1280 | 275809 | 3548 | 0.471275 | 2(Loss) | true |
| glaze | 837.935 | 1.53799 | 742.238ms | 4926 | 30 | 223048 | 5606.4 | 4.36681 | 3(Loss) | true |
| simdjson (reflection) | 807.074 | 0.266343 | 703.089ms | 4926 | 4890 | 1.17532e+06 | 5820.78 | 0.784008 | 4(Loss) | true |
| simdjson (ondemand) | 754.497 | 0.669871 | 767.8ms | 4926 | 640 | 1.11336e+06 | 6226.4 | 2.51754 | 5(Loss) | true |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9072.42 | 1.47383 | 63.8039ms | 4926 | 4890 | 284805 | 517.811 | 0.783475 | 1(Win) | true |
| simdjson (reflection) | 7214.61 | 1.12665 | 73.7958ms | 4926 | 4890 | 263179 | 651.151 | 1.88561 | 2(Loss) | true |
| glaze | 1542.79 | 1.07909 | 313.011ms | 4926 | 1280 | 1.38198e+06 | 3045 | 1.32858 | 3(Loss) | true |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 9852.36 | 1.55968 | 53.023ms | 4926 | 4890 | 270450 | 476.82 | 0.298618 | 1(Win) | true |
| simdjson (reflection) | 6945.3 | 2.75887 | 68.1078ms | 4926 | 640 | 222870 | 676.4 | 0.177725 | 2(Loss) | true |
| glaze | 1795.52 | 0.888981 | 267.322ms | 4926 | 640 | 346237 | 2616.4 | 0.562481 | 3(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1880.13 | 0.887481 | 533.06ms | 9463 | 80 | 145175 | 4800 | 0 | 1(Win) | true |
| jsonifier (two-stage) | 1336.58 | 1.32749 | 696.729ms | 9463 | 80 | 642709 | 6752 | 0.38059 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 1166.1 | 0.294533 | 818.84ms | 9463 | 4890 | 2.54075e+06 | 7739.16 | 6.96451 | -(Loss) | false |
| glaze STATISTICAL TIE | 1002.44 | 1.95725 | 846.684ms | 9463 | 30 | 931440 | 9002.67 | 1.15053 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 998.652 | 2.24482 | 1008.74ms | 9463 | 30 | 1.23456e+06 | 9036.8 | 1.76252 | 4(Tie) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2258.87 | 0.639383 | 507.36ms | 9463 | 320 | 208809 | 3995.2 | 2.72692 | 1(Win) | true |
| jsonifier (two-stage) | 1758.95 | 0.40728 | 677.461ms | 9463 | 2560 | 1.11784e+06 | 5130.7 | 2.0101 | 2(Loss) | true |
| simdjson (reflection) | 1586.16 | 0.386627 | 731.835ms | 9463 | 640 | 309691 | 5689.6 | 3.68364 | 3(Loss) | true |
| simdjson (ondemand) | 1336.23 | 0.232004 | 804.322ms | 9463 | 2560 | 628530 | 6753.8 | 0.0681562 | 4(Loss) | true |
| glaze | 1313.68 | 0.554275 | 790.567ms | 9463 | 4890 | 7.08982e+06 | 6869.7 | 0.436247 | 5(Loss) | true |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 12485.6 | 1.74941 | 81.0701ms | 9463 | 1280 | 204658 | 722.8 | 0.0553097 | 1(Win) | true |
| glaze | 2201.56 | 0.939358 | 434.174ms | 9463 | 80 | 118618 | 4099.2 | 0.549451 | 2(Loss) | true |
| simdjson (reflection) | 278.923 | 0.807045 | 3428.4ms | 9463 | 160 | 1.09095e+07 | 32355.2 | 1.94596 | 3(Loss) | true |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13287.1 | 1.93662 | 77.824ms | 9463 | 1280 | 221459 | 679.2 | 0.771513 | 1(Win) | true |
| glaze | 2413.94 | 0.432865 | 381.194ms | 9463 | 4890 | 1.28061e+06 | 3738.54 | 1.36771 | 2(Loss) | true |
| simdjson (reflection) | 268.539 | 0.646217 | 3473.17ms | 9463 | 320 | 1.50921e+07 | 33606.4 | 0.938546 | 3(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) STATISTICAL TIE | 3197.43 | 1.28535 | 90.848ms | 2821 | 1280 | 149712 | 841.4 | 0.935701 | 1(Tie) | true |
| jsonifier STATISTICAL TIE | 3139.96 | 2.45381 | 99.4911ms | 2821 | 320 | 141446 | 856.8 | 3.33935 | 1(Tie) | true |
| simdjson (reflection) | 2765.54 | 1.35641 | 110.011ms | 2821 | 320 | 55715.9 | 972.8 | 0.164745 | 3(Loss) | true |
| simdjson (ondemand) | 2651.86 | 0.78076 | 108.688ms | 2821 | 2560 | 160612 | 1014.5 | 0.480675 | 4(Loss) | true |
| glaze | 2009.2 | 0.999577 | 177.829ms | 2821 | 1280 | 229300 | 1339 | 3.09516 | 5(Loss) | true |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 3284.08 | 0.959632 | 91.6032ms | 2821 | 2560 | 158208 | 819.2 | 0 | 1(Win) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2869.36 | 2.13655 | 125.302ms | 2821 | 160 | 64206.7 | 937.6 | 1.03448 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2840.28 | 1.39307 | 107.526ms | 2821 | 320 | 55715.9 | 947.2 | 1.71821 | 2(Tie) | true |
| simdjson (ondemand) | 2363.45 | 0.82748 | 112.441ms | 2821 | 2560 | 227127 | 1138.3 | 0.770184 | 4(Loss) | true |
| glaze | 1977.65 | 1.25518 | 140.032ms | 2821 | 4890 | 1.42569e+06 | 1360.36 | 2.18867 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 3664.99 | 0.863959 | 146.413ms | 4147 | 2560 | 222510 | 1079.1 | 0.41876 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3471.64 | 3.5733 | 129.804ms | 4147 | 80 | 132565 | 1139.2 | 0.558659 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 3467.09 | 1.0389 | 123.647ms | 4147 | 4890 | 686740 | 1140.69 | 4.24009 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3462.17 | 0.450098 | 126.285ms | 4147 | 4890 | 129269 | 1142.31 | 1.20092 | 3(Tie) | true |
| glaze | 2493.62 | 1.57934 | 173.876ms | 4147 | 1280 | 803094 | 1586 | 1.53649 | 5(Loss) | true |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (two-stage) | 4038.9 | 1.67784 | 111.847ms | 4147 | 640 | 172752 | 979.2 | 1.07349 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 3547.62 | 1.16938 | 148.807ms | 4147 | 640 | 108764 | 1114.8 | 1.17021 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3376.78 | 5.63758 | 156.624ms | 4147 | 40 | 174385 | 1171.2 | 0.182482 | 2(Tie) | true |
| glaze | 3025.46 | 2.8405 | 144.845ms | 4147 | 160 | 220594 | 1307.2 | 1.3285 | 4(Loss) | true |
| jsonifier | 1364.13 | 1.7993 | 125.128ms | 4147 | 40 | 108849 | 2899.2 | 0.947522 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1959.16 | 1.41984 | 152.534ms | 2821 | 640 | 243291 | 1373.2 | 0.0874636 | 1(Win) | true |
| jsonifier (two-stage) | 1474.33 | 0.836696 | 191.04ms | 2821 | 4890 | 1.13989e+06 | 1824.77 | 1.06418 | 2(Loss) | true |
| glaze | 1339.76 | 1.06054 | 221.807ms | 2821 | 4890 | 2.21774e+06 | 2008.06 | 3.68439 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1091.74 | 0.336576 | 260.119ms | 2821 | 4890 | 336392 | 2464.25 | 2.36733 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1081.66 | 0.629541 | 270.161ms | 2821 | 1280 | 313819 | 2487.2 | 0.971492 | 4(Tie) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2546.92 | 0.678082 | 129.066ms | 2821 | 2560 | 131334 | 1056.3 | 4.00763 | 1(Win) | true |
| jsonifier (two-stage) | 1818.7 | 0.53143 | 179.255ms | 2821 | 4890 | 302194 | 1479.25 | 3.01189 | 2(Loss) | true |
| glaze | 1749.23 | 1.01686 | 182.254ms | 2821 | 1280 | 313073 | 1538 | 0.697314 | 3(Loss) | true |
| simdjson (reflection) | 1388.86 | 2.5094 | 211.403ms | 2821 | 30 | 70884.3 | 1937.07 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1200.09 | 0.304463 | 259.177ms | 2821 | 4890 | 227800 | 2241.75 | 0.472661 | 5(Loss) | true |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier DID NOT CONVERGE | 8219.65 | 2.06067 | 32.7928ms | 2821 | 4890 | 222448 | 327.303 | 8.48627 | -(Win) | false |
| simdjson (reflection) DID NOT CONVERGE | 6398.06 | 2.30056 | 46.9299ms | 2821 | 4890 | 457601 | 420.489 | 6.56086 | -(Loss) | false |
| glaze | 2690.56 | 1.95767 | 103.636ms | 2819 | 320 | 122443 | 999.2 | 0.715421 | 3(Loss) | true |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11686.9 | 5.13755 | 28.0292ms | 2821 | 1280 | 179033 | 230.2 | 1.14236 | 1(Win) | true |
| simdjson (reflection) | 7586.9 | 5.55511 | 39.1511ms | 2821 | 1280 | 496676 | 354.6 | 0.838926 | 2(Loss) | true |
| glaze | 3288.17 | 1.91889 | 89.5009ms | 2819 | 640 | 157530 | 817.6 | 0 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier STATISTICAL TIE | 2205 | 1.83609 | 200.539ms | 4147 | 160 | 173524 | 1793.6 | 0.266904 | 1(Tie) | true |
| jsonifier (two-stage) STATISTICAL TIE | 2123.54 | 1.0814 | 206.228ms | 4147 | 320 | 129798 | 1862.4 | 0.692042 | 1(Tie) | true |
| glaze | 1942.67 | 0.589195 | 220.725ms | 4147 | 1280 | 184161 | 2035.8 | 0.226467 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1455.82 | 1.57753 | 319.965ms | 4147 | 1280 | 2.35079e+06 | 2716.6 | 0.242362 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1446.77 | 1.15522 | 286.319ms | 4147 | 1280 | 1.27646e+06 | 2733.6 | 2.10668 | 4(Tie) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2445.21 | 0.794374 | 203.895ms | 4147 | 2560 | 422595 | 1617.4 | 0.973904 | 1(Win) | true |
| jsonifier (two-stage) | 2384.24 | 0.796002 | 184.726ms | 4147 | 4890 | 852524 | 1658.76 | 0.366965 | 2(Loss) | true |
| glaze DID NOT CONVERGE | 2069.21 | 0.518814 | 262.362ms | 4147 | 2560 | 251722 | 1911.3 | 5.03957 | -(Loss) | false |
| simdjson (reflection) | 1716.02 | 0.66566 | 254.719ms | 4147 | 4890 | 1.15089e+06 | 2304.68 | 0.273258 | 4(Loss) | true |
| simdjson (ondemand) | 1519.24 | 1.64631 | 273.966ms | 4147 | 320 | 587746 | 2603.2 | 0.184729 | 5(Loss) | true |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 11874.3 | 2.03127 | 37.481ms | 4147 | 4890 | 223818 | 333.062 | 2.84079 | 1(Win) | true |
| glaze | 1373.71 | 0.80242 | 311.042ms | 4145 | 320 | 170614 | 2877.6 | 0.47486 | 2(Loss) | true |
| simdjson (reflection) | 304.32 | 0.562876 | 1344.24ms | 4147 | 2560 | 1.36984e+07 | 12995.8 | 2.42075 | 3(Loss) | true |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 13470.3 | 6.15856 | 34.4451ms | 4147 | 640 | 209243 | 293.6 | 3.08989 | 1(Win) | true |
| glaze | 2383.61 | 0.958154 | 166.856ms | 4145 | 1280 | 323191 | 1658.4 | 0.704396 | 2(Loss) | true |
| simdjson (reflection) | 301.184 | 0.3827 | 1346.11ms | 4147 | 4890 | 1.23489e+07 | 13131.1 | 2.9122 | 3(Loss) | true |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1862.87 | 0.876617 | 6255.28ms | 466906 | 40 | 1.7562e+08 | 239027 | 2.23366 | 1(Win) | true |
| glaze | 1425.42 | 0.235793 | 8657.83ms | 466906 | 1280 | 6.94453e+08 | 312382 | 1.94157 | 2(Loss) | true |
| simdjson (ondemand) | 854.249 | 0.196201 | 7171.26ms | 466906 | 320 | 3.3469e+08 | 521249 | 4.1323 | 3(Loss) | true |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1910.65 | 0.687887 | 6132.33ms | 466906 | 80 | 2.05599e+08 | 233050 | 0.189847 | 1(Win) | true |
| glaze | 1447.04 | 0.375758 | 8044.19ms | 466906 | 160 | 2.13912e+08 | 307715 | 0.624193 | 2(Loss) | true |
| simdjson (ondemand) | 530.108 | 2.62547 | 8277.87ms | 466906 | 320 | 1.5563e+11 | 839972 | 4.48959 | 3(Loss) | true |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2820 | 0.449284 | 6362.67ms | 699405 | 160 | 1.80685e+08 | 236526 | 1.32893 | 1(Win) | true |
| glaze | 1624.22 | 0.803051 | 9466.72ms | 699405 | 320 | 3.48021e+09 | 410662 | 2.07645 | 2(Loss) | true |
| simdjson (ondemand) | 591.794 | 1.16887 | 8196.75ms | 767297 | 30 | 6.26668e+09 | 1.2365e+06 | 3.0678 | 3(Loss) | true |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 2900.49 | 0.198955 | 6237.51ms | 699405 | 640 | 1.33969e+08 | 229962 | 0.761001 | 1(Win) | true |
| glaze | 1739.93 | 1.14928 | 5030.09ms | 699405 | 80 | 1.55286e+09 | 383350 | 0.956562 | 2(Loss) | true |
| simdjson (ondemand) | 579.275 | 0.475133 | 7679.58ms | 767297 | 40 | 1.44095e+09 | 1.26322e+06 | 0.775851 | 3(Loss) | true |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier | 1594.94 | 1.84792 | 9891.3ms | 631514 | 160 | 7.79044e+09 | 377605 | 0.0275496 | 1(Win) | true |
| glaze | 1321.75 | 1.45266 | 5716.92ms | 631514 | 320 | 1.40199e+10 | 455652 | 3.14432 | 2(Loss) | true |
