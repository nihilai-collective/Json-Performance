# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 10, 2026)
#### Using the following commits:
----
| Jsonifier: [5aa6104](https://github.com/nihilai-collective/jsonifier/commit/5aa6104)  
| Glaze: [e194d23](https://github.com/stephenberry/glaze/commit/e194d23)  
| Simdjson: [7f6f8dc](https://github.com/simdjson/simdjson/commit/7f6f8dc)  

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

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10% AND mean shift < 5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1509.58 | 1.24573 | 59.5451ms | 905 | 4890 | 248052 | 571.733 | 1(Tie) |
| glaze STATISTICAL TIE | 1493.98 | 1.24143 | 78.86ms | 905 | 4890 | 251513 | 577.701 | 1(Tie) |
| jsonifier (two-stage) | 221.126 | 0.3081 | 378.029ms | 905 | 2560 | 370205 | 3903.1 | 3(Loss) |
| simdjson (ondemand) | 195.067 | 0.239661 | 447.326ms | 905 | 2560 | 287848 | 4424.5 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1708.4 | 1.43958 | 53.9661ms | 905 | 4890 | 258639 | 505.194 | 1(Win) |
| glaze | 1624.15 | 1.89376 | 56.2811ms | 905 | 2560 | 259258 | 531.4 | 2(Loss) |
| jsonifier (two-stage) | 245.785 | 0.32245 | 354.468ms | 905 | 2560 | 328210 | 3511.5 | 3(Loss) |
| simdjson (ondemand) | 199.279 | 0.232283 | 441.195ms | 905 | 2560 | 259091 | 4331 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1604.83 | 1.84335 | 58.2039ms | 905 | 2560 | 251593 | 537.8 | 1(Win) |
| simdjson (reflection) | 169.603 | 0.643736 | 565.969ms | 905 | 640 | 686794 | 5088.8 | 2(Loss) |
| glaze | 116.85 | 0.142151 | 754.17ms | 905 | 4890 | 539079 | 7386.2 | 3(Loss) |
### Bool Test Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 3.0976955255937493%)


----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 830.741 | 0.212148 | 213.057ms | 1811 | 4890 | 95124.8 | 2078.99 | 1(Win) |
| glaze | 529.852 | 0.359904 | 329.864ms | 1811 | 2560 | 352323 | 3259.6 | 2(Loss) |
| jsonifier (two-stage) | 307.832 | 0.135489 | 570.09ms | 1811 | 4890 | 282568 | 5610.54 | 3(Loss) |
| simdjson (ondemand) | 142.004 | 0.173039 | 1260.72ms | 1811 | 640 | 283471 | 12162.4 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 984.7 | 0.368718 | 179.394ms | 1811 | 4890 | 204516 | 1753.94 | 1(Win) |
| glaze | 528.037 | 0.546392 | 311.465ms | 1811 | 640 | 204408 | 3270.8 | 2(Loss) |
| jsonifier (two-stage) | 340.558 | 0.147268 | 519.716ms | 1811 | 2560 | 142795 | 5071.4 | 3(Loss) |
| simdjson (ondemand) | 140.397 | 0.244066 | 1256.11ms | 1811 | 320 | 288460 | 12301.6 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 282.297 | 0.479664 | 668.13ms | 1997 | 320 | 335096 | 6746.4 | 1(Win) |
| jsonifier | 265.48 | 0.44297 | 658.393ms | 1811 | 320 | 265750 | 6505.6 | 2(Loss) |
| glaze | 201.54 | 0.261499 | 914.503ms | 1798 | 640 | 316793 | 8508 | 3(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 815.262 | 0.239152 | 223.524ms | 1811 | 4890 | 125516 | 2118.47 | 1(Win) |
| simdjson (reflection) | 677.079 | 0.819658 | 339.792ms | 1997 | 320 | 170096 | 2812.8 | 2(Loss) |
| glaze | 465.852 | 0.382398 | 385.818ms | 1798 | 1280 | 253586 | 3680.8 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2202.45 | 0.443919 | 171.892ms | 3862 | 4890 | 269482 | 1672.27 | 1(Win) |
| glaze | 1318.21 | 0.509214 | 286.501ms | 3862 | 1280 | 259098 | 2794 | 2(Loss) |
| jsonifier (two-stage) | 674.114 | 0.423699 | 553.572ms | 3862 | 640 | 342968 | 5463.6 | 3(Loss) |
| simdjson (ondemand) | 468.444 | 0.51545 | 854.103ms | 3862 | 80 | 131393 | 7862.4 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2699.02 | 0.520195 | 143.071ms | 3862 | 4890 | 246406 | 1364.6 | 1(Win) |
| glaze | 1489.56 | 0.64042 | 252.532ms | 3862 | 1280 | 320958 | 2472.6 | 2(Loss) |
| jsonifier (two-stage) | 712.838 | 0.219848 | 553.767ms | 3862 | 1280 | 165158 | 5166.8 | 3(Loss) |
| simdjson (ondemand) | 438.354 | 0.207489 | 814.086ms | 3862 | 4890 | 1.48618e+06 | 8402.09 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 745.16 | 0.158245 | 500.161ms | 3862 | 4890 | 299155 | 4942.68 | 1(Win) |
| jsonifier | 686.094 | 0.205421 | 544.393ms | 3862 | 2560 | 311306 | 5368.2 | 2(Loss) |
| glaze | 501.811 | 0.284633 | 747.74ms | 3862 | 640 | 279316 | 7339.6 | 3(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3670.52 | 0.174108 | 113.665ms | 3862 | 4890 | 14925.1 | 1003.43 | 1(Win) |
| simdjson (reflection) | 3020.66 | 0.695715 | 135.998ms | 3862 | 2560 | 184215 | 1219.3 | 2(Loss) |
| glaze | 2090.76 | 0.501572 | 195.894ms | 3862 | 2560 | 199858 | 1761.6 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1172.88 | 0.0993994 | 785.637ms | 9578 | 4890 | 293033 | 7787.9 | 1(Win) |
| glaze | 1055.26 | 0.134584 | 878.03ms | 9578 | 2560 | 347425 | 8656 | 2(Loss) |
| simdjson (ondemand) | 782.059 | 0.142771 | 1184.98ms | 9578 | 1280 | 355926 | 11679.8 | 3(Loss) |
| jsonifier (two-stage) | 724.944 | 0.204654 | 1286.44ms | 9578 | 640 | 425561 | 12600 | 4(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1949.02 | 0.294566 | 739.439ms | 9578 | 2560 | 487888 | 4686.6 | 1(Win) |
| glaze | 1564.2 | 0.326475 | 906.194ms | 9578 | 640 | 232619 | 5839.6 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 958.377 | 0.315619 | 1182.53ms | 9578 | 1280 | 1.15828e+06 | 9531 | 3(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 954.192 | 0.25774 | 1235.95ms | 9578 | 640 | 389603 | 9572.8 | 3(Tie) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 1226.28 | 0.315754 | 756.749ms | 9578 | 640 | 354037 | 7448.8 | 1(Win) |
| jsonifier | 1209.87 | 0.215523 | 761.168ms | 9578 | 1280 | 338897 | 7549.8 | 2(Loss) |
| glaze | 1022.6 | 0.158783 | 901.681ms | 9578 | 1280 | 257487 | 8932.4 | 3(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 10011.4 | 0.473849 | 102.401ms | 9578 | 4890 | 91400.1 | 912.386 | 1(Win) |
| jsonifier | 8663.02 | 0.45373 | 120.213ms | 9578 | 2560 | 58593.1 | 1054.4 | 2(Loss) |
| glaze | 4605.84 | 0.343145 | 216.143ms | 9578 | 640 | 29639.3 | 1983.2 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2224.39 | 0.46825 | 170.195ms | 3873 | 4890 | 295624 | 1660.49 | 1(Win) |
| glaze | 1369.46 | 0.419539 | 273.902ms | 3873 | 2560 | 327776 | 2697.1 | 2(Loss) |
| jsonifier (two-stage) | 674.602 | 0.591909 | 564.359ms | 3873 | 320 | 336093 | 5475.2 | 3(Loss) |
| simdjson (ondemand) | 441.351 | 0.325227 | 895.871ms | 3873 | 640 | 474110 | 8368.8 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2714.67 | 0.998231 | 142.298ms | 3873 | 1280 | 236120 | 1360.6 | 1(Win) |
| glaze | 1651.49 | 0.304072 | 225.661ms | 3873 | 4890 | 226155 | 2236.52 | 2(Loss) |
| jsonifier (two-stage) | 719.828 | 0.390504 | 527.156ms | 3873 | 320 | 128481 | 5131.2 | 3(Loss) |
| simdjson (ondemand) | 454.539 | 0.221545 | 831.577ms | 3873 | 640 | 207424 | 8126 | 4(Loss) |
### Uint64 Test Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 0.16954387597716558%)


----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3590.18 | 1.02701 | 118.897ms | 3873 | 320 | 35723.8 | 1028.8 | 1(Win) |
| simdjson (reflection) | 3094.75 | 0.680345 | 133.475ms | 3873 | 2560 | 168788 | 1193.5 | 2(Loss) |
| glaze | 2358.14 | 0.465781 | 176.806ms | 3873 | 4890 | 260273 | 1566.31 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 688.051 | 0.496862 | 9111.89ms | 2090234 | 80 | 1.65772e+10 | 2.89717e+06 | 1(Win) |
| jsonifier (two-stage) | 651.205 | 0.221274 | 9696.19ms | 2090234 | 80 | 3.67034e+09 | 3.0611e+06 | 2(Loss) |
| simdjson (reflection) | 535.581 | 0.233135 | 5602.03ms | 2090234 | 80 | 6.02344e+09 | 3.72195e+06 | 3(Loss) |
| glaze | 511.943 | 0.253114 | 5956.66ms | 2090234 | 80 | 7.77087e+09 | 3.8938e+06 | 4(Loss) |
| simdjson (ondemand) | 474.144 | 0.406507 | 6467.35ms | 2090234 | 30 | 8.76248e+09 | 4.20421e+06 | 5(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 879.694 | 0.16921 | 8924.57ms | 2090234 | 160 | 2.35233e+09 | 2.26602e+06 | 1(Win) |
| jsonifier (two-stage) | 796.798 | 0.266304 | 9655.03ms | 2090234 | 160 | 7.10181e+09 | 2.50177e+06 | 2(Loss) |
| simdjson (reflection) | 635.935 | 0.265433 | 5690.13ms | 2090234 | 30 | 2.0768e+09 | 3.1346e+06 | 3(Loss) |
| glaze | 594.417 | 0.54566 | 5852.03ms | 2090234 | 30 | 1.00455e+10 | 3.35354e+06 | 4(Loss) |
| simdjson (ondemand) | 544.128 | 0.642806 | 6411.65ms | 2090234 | 40 | 2.21823e+10 | 3.66348e+06 | 5(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2288.18 | 0.128566 | 5555.65ms | 2090234 | 40 | 5.01787e+07 | 871174 | 1(Win) |
| glaze | 1552.09 | 0.114024 | 8448.91ms | 2090234 | 30 | 6.4338e+07 | 1.28433e+06 | 2(Loss) |
| simdjson (reflection) | 765.497 | 0.213647 | 8175.87ms | 2090326 | 80 | 2.47642e+09 | 2.60418e+06 | 3(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2286.36 | 0.233247 | 5669.19ms | 2090234 | 30 | 1.24066e+08 | 871868 | 1(Win) |
| glaze | 1603.23 | 0.119628 | 7902.7ms | 2090234 | 320 | 7.07968e+08 | 1.24337e+06 | 2(Loss) |
| simdjson (reflection) | 762.765 | 0.190675 | 8144.65ms | 2090326 | 160 | 3.97334e+09 | 2.6135e+06 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1725.89 | 0.239899 | 5661.42ms | 6661897 | 80 | 6.23906e+09 | 3.68117e+06 | 1(Win) |
| jsonifier | 1645.98 | 0.99097 | 5412.16ms | 6661897 | 80 | 1.17046e+11 | 3.85987e+06 | 2(Loss) |
| simdjson (reflection) | 1509.27 | 0.310514 | 6453.19ms | 6661897 | 40 | 6.83413e+09 | 4.2095e+06 | 3(Loss) |
| simdjson (ondemand) | 1363.32 | 0.214346 | 7084.52ms | 6661897 | 80 | 7.98219e+09 | 4.66015e+06 | 4(Loss) |
| glaze | 1298.65 | 0.214498 | 7577.18ms | 6661897 | 80 | 8.80943e+09 | 4.89221e+06 | 5(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2179.88 | 0.19709 | 5395.72ms | 6661897 | 30 | 9.89876e+08 | 2.91451e+06 | 1(Win) |
| jsonifier (two-stage) | 2038.31 | 0.277144 | 5608.38ms | 6661897 | 80 | 5.96978e+09 | 3.11694e+06 | 2(Loss) |
| simdjson (reflection) | 1741 | 0.364298 | 6397.83ms | 6661897 | 40 | 7.06921e+09 | 3.64921e+06 | 3(Loss) |
| simdjson (ondemand) | 1543.18 | 0.390311 | 7125.1ms | 6661897 | 30 | 7.74647e+09 | 4.117e+06 | 4(Loss) |
| glaze | 1461.5 | 0.228348 | 7497.18ms | 6661897 | 80 | 7.88281e+09 | 4.34709e+06 | 5(Loss) |
### Canada Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.2709428138283382%)

### Canada Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.5789975147788581%)


----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1950.64 | 0.0668275 | 6360.27ms | 500299 | 320 | 8.54998e+06 | 244598 | 1(Win) |
| jsonifier (two-stage) | 1267.58 | 0.106439 | 9955.62ms | 500299 | 40 | 6.42047e+06 | 376403 | 2(Loss) |
| glaze | 1204.44 | 0.114472 | 5167.81ms | 500299 | 640 | 1.31602e+08 | 396135 | 3(Loss) |
| simdjson (ondemand) | 1057.43 | 0.155005 | 5773.95ms | 500299 | 640 | 3.13061e+08 | 451210 | 4(Loss) |
| simdjson (reflection) | 1048.76 | 0.11967 | 6711.91ms | 500299 | 30 | 8.89188e+06 | 454938 | 5(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2461.18 | 0.125888 | 6252.87ms | 500299 | 80 | 4.76462e+06 | 193859 | 1(Win) |
| jsonifier (two-stage) | 1457.88 | 0.141485 | 9678.16ms | 500299 | 40 | 8.57614e+06 | 327270 | 2(Loss) |
| glaze | 1394.62 | 0.123406 | 5028.93ms | 500299 | 160 | 2.85194e+07 | 342117 | 3(Loss) |
| simdjson (ondemand) | 1194.1 | 0.125383 | 5700.7ms | 500299 | 40 | 1.00394e+07 | 399565 | 4(Loss) |
| simdjson (reflection) | 1069.08 | 0.45745 | 6695.4ms | 500299 | 160 | 6.66884e+08 | 446294 | 5(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7727.03 | 0.617299 | 7207.97ms | 500299 | 80 | 1.16229e+07 | 61747.2 | 1(Win) |
| simdjson (reflection) | 6531.39 | 0.195563 | 7597.15ms | 500299 | 1280 | 2.61234e+07 | 73050.6 | 2(Loss) |
| glaze | 1714.21 | 0.215343 | 7067.76ms | 500299 | 1280 | 4.59835e+08 | 278333 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7344.5 | 0.832006 | 6546.67ms | 500299 | 80 | 2.3371e+07 | 64963.2 | 1(Win) |
| simdjson (reflection) | 6499.79 | 0.192783 | 7550.69ms | 500299 | 2560 | 5.12668e+07 | 73405.8 | 2(Loss) |
| glaze | 1873.98 | 0.244906 | 6719.8ms | 500299 | 640 | 2.48834e+08 | 254604 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2991.13 | 0.467638 | 6212ms | 1439562 | 160 | 7.37103e+08 | 458981 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 2170.32 | 1.38305 | 8561.61ms | 1439562 | 320 | 2.44927e+10 | 632566 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2160.63 | 0.674513 | 8819.64ms | 1439562 | 80 | 1.46951e+09 | 635405 | 2(Tie) |
| simdjson (ondemand) | 2108.42 | 0.391988 | 8481.87ms | 1439562 | 640 | 4.16938e+09 | 651137 | 4(Loss) |
| glaze | 1591.43 | 1.21607 | 5626.21ms | 1439562 | 80 | 8.80419e+09 | 862666 | 5(Loss) |
### CitmCatalog Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 0.4958245550354688%)

### CitmCatalog Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.4249666572856685%)


----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17536.5 | 0.478724 | 8169ms | 1439562 | 160 | 2.24731e+07 | 78286.4 | 1(Win) |
| glaze | 4306.49 | 0.922102 | 9064.11ms | 1439584 | 30 | 2.59243e+08 | 318797 | 2(Loss) |
| simdjson (reflection) | 320.219 | 0.543748 | 7175.98ms | 1439562 | 40 | 2.17381e+10 | 4.2873e+06 | 3(Loss) |
### Discord Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 1.5633010969906596%)


----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2290.13 | 0.192003 | 3097.43ms | 56369 | 320 | 650016 | 23473.6 | 1(Win) |
| glaze | 1554.8 | 0.52715 | 4197.64ms | 56369 | 320 | 1.06304e+07 | 34575.2 | 2(Loss) |
| jsonifier (two-stage) | 1333.65 | 0.408331 | 4975.32ms | 56369 | 320 | 8.66912e+06 | 40308.8 | 3(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1136.54 | 0.323116 | 5591.14ms | 56369 | 80 | 1.8686e+06 | 47299.2 | 4(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1134.76 | 0.0521178 | 5362.63ms | 56369 | 4890 | 2.98093e+06 | 47373.5 | 4(Tie) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11298.8 | 0.155029 | 481.231ms | 56369 | 4890 | 266044 | 4757.83 | 1(Win) |
| simdjson (reflection) | 8877.93 | 0.251242 | 644.777ms | 56369 | 320 | 74061.2 | 6055.2 | 2(Loss) |
| glaze | 2782.32 | 0.133013 | 2048.45ms | 56369 | 640 | 422707 | 19321.2 | 3(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11655.6 | 0.212559 | 474.842ms | 56369 | 4890 | 469981 | 4612.19 | 1(Win) |
| simdjson (reflection) | 9082.47 | 0.101052 | 598.1ms | 56369 | 4890 | 174933 | 5918.84 | 2(Loss) |
| glaze | 3107.91 | 0.552787 | 1836.09ms | 56369 | 30 | 274272 | 17297.1 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2006.98 | 0.15504 | 4619.46ms | 94370 | 30 | 145008 | 44842.7 | 1(Win) |
| glaze | 1827.85 | 0.156344 | 5233.47ms | 94370 | 30 | 177776 | 49237.3 | 2(Loss) |
| jsonifier (two-stage) | 1676.59 | 0.141481 | 5404.67ms | 94370 | 640 | 3.69137e+06 | 53679.2 | 3(Loss) |
| simdjson (reflection) | 1551.4 | 0.0842635 | 5915.59ms | 94370 | 1280 | 3.05851e+06 | 58011 | 4(Loss) |
| simdjson (ondemand) | 1454.14 | 0.0782595 | 6565.23ms | 94370 | 1280 | 3.00289e+06 | 61891 | 5(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2469.22 | 0.226325 | 4410.32ms | 94370 | 160 | 1.08876e+06 | 36448 | 1(Win) |
| glaze | 2255.83 | 0.0850518 | 4579.98ms | 94370 | 2560 | 2.94756e+06 | 39895.9 | 2(Loss) |
| jsonifier (two-stage) | 2150.68 | 0.167703 | 4948.25ms | 94370 | 160 | 787988 | 41846.4 | 3(Loss) |
| simdjson (reflection) | 1729.46 | 0.116874 | 5884.25ms | 94370 | 160 | 591844 | 52038.4 | 4(Loss) |
| simdjson (ondemand) | 1720.65 | 0.182793 | 5818.7ms | 94370 | 1280 | 1.17007e+07 | 52304.8 | 5(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12928.4 | 0.179513 | 816.905ms | 94370 | 2560 | 399774 | 6961.3 | 1(Win) |
| glaze | 2507.36 | 0.193155 | 3641.46ms | 94370 | 320 | 1.53814e+06 | 35893.6 | 2(Loss) |
| simdjson (reflection) | 335.524 | 0.376806 | 7064.75ms | 94370 | 160 | 1.63447e+08 | 268232 | 3(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13100.9 | 0.360299 | 726.091ms | 94370 | 320 | 196037 | 6869.6 | 1(Win) |
| glaze | 2806.46 | 0.212879 | 3249.79ms | 94370 | 30 | 139810 | 32068.3 | 2(Loss) |
| simdjson (reflection) | 346.038 | 0.132882 | 6806.44ms | 94370 | 160 | 1.91103e+07 | 260082 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1881.58 | 0.0823604 | 604.352ms | 11812 | 4890 | 118891 | 5986.89 | 1(Win) |
| jsonifier (two-stage) | 1146.33 | 0.153142 | 1017.84ms | 11812 | 1280 | 289883 | 9826.8 | 2(Loss) |
| glaze STATISTICAL TIE | 916.732 | 0.323675 | 1205.83ms | 11812 | 320 | 506209 | 12288 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 910.567 | 0.630395 | 1429.65ms | 11812 | 40 | 243281 | 12371.2 | 3(Tie) |
| simdjson (ondemand) | 730.987 | 0.220752 | 1599.97ms | 11812 | 320 | 370329 | 15410.4 | 5(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2213.73 | 0.229258 | 595.452ms | 11812 | 1280 | 174203 | 5088.6 | 1(Win) |
| jsonifier (two-stage) | 1240.73 | 0.377488 | 1001.12ms | 11812 | 320 | 375881 | 9079.2 | 2(Loss) |
| glaze | 1044.16 | 0.171506 | 1167.83ms | 11812 | 1280 | 438211 | 10788.4 | 3(Loss) |
| simdjson (reflection) | 935.677 | 0.288474 | 1403.3ms | 11812 | 320 | 385974 | 12039.2 | 4(Loss) |
| simdjson (ondemand) | 779.873 | 0.35975 | 1552.42ms | 11812 | 2560 | 6.91258e+06 | 14444.4 | 5(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10240.7 | 1.57714 | 114.934ms | 11812 | 320 | 96310.6 | 1100 | 1(Win) |
| simdjson (reflection) | 8126.39 | 0.715503 | 141.573ms | 11812 | 2560 | 251834 | 1386.2 | 2(Loss) |
| glaze | 1762.63 | 0.189748 | 648.219ms | 11812 | 2560 | 376461 | 6390.9 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10684.6 | 0.464867 | 109.011ms | 11812 | 2560 | 61493.1 | 1054.3 | 1(Win) |
| simdjson (reflection) | 8505.96 | 0.518614 | 138.58ms | 11812 | 4890 | 230673 | 1324.34 | 2(Loss) |
| glaze | 1879.1 | 0.213477 | 628.86ms | 11812 | 1280 | 209634 | 5994.8 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2656.89 | 0.346068 | 1234.72ms | 31235 | 640 | 963470 | 11211.6 | 1(Win) |
| simdjson (reflection) | 2042.75 | 0.102947 | 1483.09ms | 31235 | 2560 | 576925 | 14582.3 | 2(Loss) |
| jsonifier (two-stage) | 1853.73 | 0.521118 | 1609.03ms | 31235 | 1280 | 8.97574e+06 | 16069.2 | 3(Loss) |
| glaze | 1720.56 | 0.113635 | 1742.3ms | 31235 | 1280 | 495426 | 17313 | 4(Loss) |
| simdjson (ondemand) | 1595.88 | 0.275854 | 1938.21ms | 31235 | 320 | 848383 | 18665.6 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2991.25 | 0.527988 | 1271.13ms | 31235 | 30 | 82936.9 | 9958.4 | 1(Win) |
| jsonifier (two-stage) | 2371.44 | 0.191138 | 1603.26ms | 31235 | 4890 | 2.81879e+06 | 12561.2 | 2(Loss) |
| simdjson (reflection) | 1921.82 | 0.185418 | 1837.29ms | 31235 | 4890 | 4.03897e+06 | 15499.9 | 3(Loss) |
| glaze | 1820.96 | 0.243992 | 1808.5ms | 31235 | 160 | 254890 | 16358.4 | 4(Loss) |
| simdjson (ondemand) | 1760.9 | 0.103081 | 1789.65ms | 31235 | 1280 | 389213 | 16916.4 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15663.2 | 0.262188 | 194.167ms | 31235 | 4890 | 121578 | 1901.78 | 1(Win) |
| glaze | 2252.06 | 0.587566 | 1398.43ms | 31235 | 1280 | 7.73119e+06 | 13227 | 2(Loss) |
| simdjson (reflection) | 305.807 | 0.424099 | 5096.71ms | 31235 | 30 | 5.11972e+06 | 97408 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17450.2 | 0.400404 | 174.776ms | 31235 | 4890 | 228449 | 1707.03 | 1(Win) |
| glaze | 3016.83 | 0.1098 | 1083.28ms | 31235 | 4890 | 574776 | 9873.96 | 2(Loss) |
| simdjson (reflection) | 306.759 | 0.0855415 | 5055.19ms | 31235 | 640 | 4.41593e+06 | 97105.6 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2514.95 | 0.137953 | 4249.6ms | 108313 | 2560 | 8.21873e+06 | 41072.5 | 1(Win) |
| jsonifier (two-stage) | 1483.27 | 0.0642048 | 7183.76ms | 108313 | 2560 | 5.11794e+06 | 69640.2 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1206.07 | 0.141526 | 8774.1ms | 108313 | 320 | 4.70154e+06 | 85646.4 | 3(Tie) |
| glaze STATISTICAL TIE | 1193.78 | 0.89312 | 7835.58ms | 108313 | 40 | 2.38887e+07 | 86528 | 3(Tie) |
| simdjson (ondemand) | 1149.12 | 0.0785551 | 9020.34ms | 108313 | 4890 | 2.4383e+07 | 89890.8 | 5(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3000.4 | 0.272161 | 3770.93ms | 108313 | 160 | 1.40467e+06 | 34427.2 | 1(Win) |
| jsonifier (two-stage) | 1636.91 | 0.0639883 | 6723.49ms | 108313 | 4890 | 7.97299e+06 | 63103.8 | 2(Loss) |
| glaze | 1474.84 | 0.154524 | 7474.82ms | 108313 | 160 | 1.87407e+06 | 70038.4 | 3(Loss) |
| simdjson (ondemand) | 1267.27 | 0.114286 | 8902.19ms | 108313 | 30 | 260336 | 81510.4 | 4(Loss) |
| simdjson (reflection) | 1245.89 | 0.152935 | 9630.15ms | 108313 | 160 | 2.57238e+06 | 82908.8 | 5(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13848 | 0.383401 | 768.475ms | 108313 | 320 | 261723 | 7459.2 | 1(Win) |
| simdjson (reflection) | 7565.43 | 0.135351 | 1387.85ms | 108313 | 4890 | 1.67003e+06 | 13653.6 | 2(Loss) |
| glaze | 1855.75 | 0.175331 | 5734.62ms | 108313 | 160 | 1.52392e+06 | 55662.4 | 3(Loss) |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14175.5 | 0.159851 | 740.55ms | 108313 | 2560 | 347342 | 7286.9 | 1(Win) |
| simdjson (reflection) | 7837.75 | 0.117358 | 1358.38ms | 108313 | 2560 | 612415 | 13179.2 | 2(Loss) |
| glaze | 2000.67 | 0.174937 | 5385.85ms | 108313 | 160 | 1.30526e+06 | 51630.4 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2460.6 | 0.101836 | 8481.26ms | 213963 | 2560 | 1.82571e+07 | 82927.2 | 1(Win) |
| glaze | 2110.62 | 0.259575 | 5287.18ms | 213963 | 40 | 2.5191e+06 | 96678.4 | 2(Loss) |
| simdjson (reflection) | 2038.5 | 0.0791584 | 5587.93ms | 213963 | 640 | 4.0182e+06 | 100099 | 3(Loss) |
| simdjson (ondemand) | 1988.93 | 0.1247 | 5398.98ms | 213963 | 160 | 2.61876e+06 | 102594 | 4(Loss) |
| jsonifier | 1378.45 | 0.0902021 | 7861.74ms | 213963 | 1280 | 2.28211e+07 | 148029 | 5(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3124.88 | 0.248167 | 6546.1ms | 213963 | 640 | 1.68065e+07 | 65298.8 | 1(Win) |
| jsonifier (two-stage) | 2709.35 | 0.158751 | 8076.34ms | 213963 | 160 | 2.28716e+06 | 75313.6 | 2(Loss) |
| glaze | 2264.79 | 0.13667 | 9467.74ms | 213963 | 640 | 9.70393e+06 | 90097.2 | 3(Loss) |
| simdjson (ondemand) | 2093.89 | 0.225859 | 5225.77ms | 213963 | 2560 | 1.24018e+08 | 97450.7 | 4(Loss) |
| simdjson (reflection) | 1825.12 | 0.40279 | 5664.65ms | 213963 | 320 | 6.48937e+07 | 111802 | 5(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16889.4 | 0.0660073 | 1247.9ms | 213963 | 4890 | 310986 | 12081.6 | 1(Win) |
| glaze | 1688.45 | 0.132455 | 5654.28ms | 213963 | 1280 | 3.2798e+07 | 120851 | 2(Loss) |
| simdjson (reflection) | 335.898 | 0.0942695 | 7905.21ms | 213963 | 160 | 5.24716e+07 | 607478 | 3(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16897 | 0.0949569 | 1204.08ms | 213963 | 1280 | 168315 | 12076.2 | 1(Win) |
| glaze | 2320.79 | 0.13973 | 9098.84ms | 213963 | 640 | 9.65978e+06 | 87923.2 | 2(Loss) |
| simdjson (reflection) | 333.129 | 0.106785 | 7960.82ms | 213963 | 640 | 2.7381e+08 | 612528 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 608.986 | 0.62907 | 8986.31ms | 1834197 | 80 | 2.61196e+10 | 2.87236e+06 | 1(Win) |
| glaze | 488.483 | 0.315496 | 5432.9ms | 1834197 | 80 | 1.0211e+10 | 3.58094e+06 | 2(Loss) |
| jsonifier (two-stage) | 438.556 | 1.28799 | 5786.07ms | 1834197 | 40 | 1.05566e+11 | 3.9886e+06 | 3(Loss) |
| simdjson (reflection) STATISTICAL TIE | 416.157 | 0.398108 | 5811.66ms | 1834197 | 30 | 8.40042e+09 | 4.20328e+06 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 401.985 | 2.30585 | 6234.76ms | 1834197 | 40 | 4.02713e+11 | 4.35147e+06 | 4(Tie) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 711.437 | 0.270971 | 8910.99ms | 1834197 | 80 | 3.55104e+09 | 2.45872e+06 | 1(Win) |
| jsonifier (two-stage) | 580.761 | 0.222118 | 5189.15ms | 1834197 | 80 | 3.58059e+09 | 3.01196e+06 | 2(Loss) |
| glaze | 544.193 | 0.293753 | 5411.8ms | 1834197 | 80 | 7.13248e+09 | 3.21435e+06 | 3(Loss) |
| simdjson (reflection) | 520.322 | 0.36379 | 5699.97ms | 1834197 | 40 | 5.98288e+09 | 3.36182e+06 | 4(Loss) |
| simdjson (ondemand) | 483.776 | 0.594563 | 6077.43ms | 1834197 | 30 | 1.3865e+10 | 3.61578e+06 | 5(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1292.86 | 0.139519 | 8690.61ms | 1834197 | 320 | 1.14028e+09 | 1.35299e+06 | 1(Win) |
| glaze | 817.769 | 0.124138 | 6762.46ms | 1833577 | 30 | 2.11383e+08 | 2.1383e+06 | 2(Loss) |
| simdjson (reflection) | 723.207 | 0.390246 | 8003.6ms | 1922245 | 80 | 7.82818e+09 | 2.53482e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1289.43 | 0.151303 | 9000.25ms | 1834197 | 320 | 1.34817e+09 | 1.35659e+06 | 1(Win) |
| glaze | 818.749 | 0.0917229 | 6810.78ms | 1833577 | 30 | 1.15126e+08 | 2.13574e+06 | 2(Loss) |
| simdjson (reflection) | 720.493 | 0.271065 | 8051.38ms | 1922245 | 80 | 3.80534e+09 | 2.54436e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2418.78 | 0.267237 | 6001.5ms | 9930848 | 80 | 8.75916e+09 | 3.91552e+06 | 1(Win) |
| jsonifier (two-stage) | 2246.82 | 0.511269 | 6580.85ms | 9930848 | 40 | 1.85778e+10 | 4.2152e+06 | 2(Loss) |
| glaze | 1885.5 | 0.359629 | 7628.73ms | 9930848 | 80 | 2.61047e+10 | 5.02297e+06 | 3(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1858.39 | 0.604462 | 7559.24ms | 9930848 | 30 | 2.84679e+10 | 5.09623e+06 | 4(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1855.04 | 0.372617 | 7313.02ms | 9930848 | 30 | 1.08571e+10 | 5.10545e+06 | 4(Tie) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2665.54 | 0.407525 | 5974.02ms | 9930848 | 40 | 8.38631e+09 | 3.55305e+06 | 1(Win) |
| jsonifier (two-stage) | 2455.63 | 0.514355 | 6437.96ms | 9930848 | 40 | 1.5741e+10 | 3.85677e+06 | 2(Loss) |
| simdjson (reflection) | 2173.3 | 0.428438 | 7127.53ms | 9930848 | 30 | 1.04576e+10 | 4.35779e+06 | 3(Loss) |
| glaze STATISTICAL TIE | 2047.71 | 0.229335 | 7558.37ms | 9930848 | 80 | 9.00054e+09 | 4.62507e+06 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2038.82 | 0.491732 | 7544.75ms | 9930848 | 40 | 2.08704e+10 | 4.64522e+06 | 4(Tie) |
### Marine IK Reverse Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 1.0407493325639101%)

### Marine IK Reverse Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.2587550592073793%)

### Marine IK Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 5.9200821348458%)
- glaze (RSE 1.56206166294316%)

### Marine IK Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 3.8922889551709487%)
- jsonifier (two-stage) (RSE 0.591591497496197%)


----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1161.49 | 0.955766 | 5086ms | 1834197 | 80 | 1.65752e+10 | 1.50603e+06 | 1(Win) |
| simdjson (reflection) | 720.376 | 0.481216 | 8045.02ms | 1922245 | 160 | 2.39938e+10 | 2.54478e+06 | 2(Loss) |
| glaze | 716.274 | 0.617324 | 8245.78ms | 1833577 | 160 | 3.63402e+10 | 2.44129e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1121.46 | 1.09717 | 9655.76ms | 1834197 | 40 | 1.17146e+10 | 1.55978e+06 | 1(Win) |
| glaze | 726.086 | 1.28553 | 7923.88ms | 1833577 | 30 | 2.87548e+10 | 2.4083e+06 | 2(Loss) |
| simdjson (reflection) | 557.762 | 1.22164 | 8689.56ms | 1922245 | 40 | 6.44864e+10 | 3.2867e+06 | 3(Loss) |
### Marine IK Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 0.09112979881989358%)
- jsonifier (RSE 0.33487833580214427%)

### Marine IK Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 1.0757057531620045%)

### Marine IK Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 1.1791344130741965%)

### Marine IK Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.8727075879533419%)


----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 994.438 | 0.0990444 | 8188.86ms | 642697 | 640 | 2.38505e+08 | 616352 | 1(Win) |
| glaze | 939.991 | 0.109879 | 8479.92ms | 642697 | 640 | 3.28529e+08 | 652052 | 2(Loss) |
| jsonifier (two-stage) | 872.723 | 0.190977 | 9292.17ms | 642697 | 160 | 2.87834e+08 | 702312 | 3(Loss) |
| simdjson (ondemand) | 829.319 | 0.192436 | 9572.77ms | 642697 | 320 | 6.4728e+08 | 739069 | 4(Loss) |
| simdjson (reflection) | 638.53 | 0.1762 | 6155.18ms | 642697 | 30 | 8.58187e+07 | 959898 | 5(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1061.05 | 0.175828 | 8103.93ms | 642697 | 80 | 8.25289e+07 | 577658 | 1(Win) |
| glaze | 1045.37 | 0.269628 | 8185.95ms | 642697 | 160 | 3.99876e+08 | 586323 | 2(Loss) |
| jsonifier (two-stage) | 931.173 | 0.11571 | 9036.05ms | 642697 | 30 | 1.74027e+07 | 658227 | 3(Loss) |
| simdjson (ondemand) | 906.442 | 0.133393 | 9244.09ms | 642697 | 640 | 5.20692e+08 | 676186 | 4(Loss) |
| simdjson (reflection) | 663.31 | 0.117238 | 6246.45ms | 642697 | 40 | 4.69439e+07 | 924038 | 5(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2412.49 | 0.195987 | 6598.93ms | 642697 | 30 | 7.43803e+06 | 254063 | 1(Win) |
| glaze | 1050.58 | 0.263009 | 8722.41ms | 642692 | 80 | 1.88357e+08 | 583411 | 2(Loss) |
| simdjson (reflection) | 813.934 | 0.84791 | 9267.9ms | 643373 | 40 | 1.6342e+09 | 753830 | 3(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2369.26 | 0.135728 | 6588.29ms | 642697 | 1280 | 1.5781e+08 | 258698 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 932.576 | 0.153041 | 8622.83ms | 643373 | 30 | 3.04154e+07 | 657929 | 2(Tie) |
| glaze STATISTICAL TIE | 918.568 | 0.990998 | 8672.94ms | 642692 | 320 | 1.3992e+10 | 667254 | 2(Tie) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1527.68 | 0.0802494 | 9931.6ms | 1225964 | 80 | 3.01763e+07 | 765325 | 1(Win) |
| simdjson (ondemand) | 1504.03 | 0.0723164 | 5009.94ms | 1225964 | 160 | 5.05631e+07 | 777357 | 2(Loss) |
| glaze | 1457.71 | 0.225246 | 5052.74ms | 1225964 | 320 | 1.04443e+09 | 802062 | 3(Loss) |
| jsonifier | 1369.36 | 0.219861 | 5418.81ms | 1225964 | 320 | 1.12763e+09 | 853809 | 4(Loss) |
| simdjson (reflection) | 1160.3 | 0.146321 | 6469.3ms | 1225964 | 80 | 1.73908e+08 | 1.00765e+06 | 5(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1632.12 | 0.147766 | 9801.57ms | 1225964 | 40 | 4.48191e+07 | 716352 | 1(Win) |
| glaze | 1600.44 | 0.112569 | 10006.1ms | 1225964 | 640 | 4.32809e+08 | 730531 | 2(Loss) |
| jsonifier (two-stage) | 1586.16 | 0.0975144 | 10120.3ms | 1225964 | 640 | 3.30656e+08 | 737105 | 3(Loss) |
| jsonifier | 1456.59 | 0.0957001 | 5430.26ms | 1225964 | 40 | 2.36029e+07 | 802675 | 4(Loss) |
| simdjson (reflection) | 1201.83 | 0.176567 | 6860.23ms | 1225964 | 80 | 2.36034e+08 | 972822 | 5(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3391.45 | 0.42129 | 9522.23ms | 1225964 | 1280 | 2.69995e+09 | 344740 | 1(Win) |
| glaze | 1515.92 | 0.0827777 | 5204.4ms | 1225970 | 80 | 3.26079e+07 | 771264 | 2(Loss) |
| simdjson (reflection) | 72.3174 | 0.764892 | 11602.3ms | 1226640 | 30 | 4.59273e+11 | 1.61761e+07 | 3(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3731.37 | 1.19809 | 9608.95ms | 1225964 | 30 | 4.22782e+08 | 313335 | 1(Win) |
| glaze | 1548.77 | 0.155182 | 9812.98ms | 1225970 | 40 | 5.48941e+07 | 754906 | 2(Loss) |
| simdjson (reflection) | 76.7473 | 0.703455 | 11006.3ms | 1226640 | 40 | 4.59877e+11 | 1.52424e+07 | 3(Loss) |
### Random Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 0.8932407120703404%)

### Random Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 0.3912652112233756%)


----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10260.1 | 0.423651 | 4141.73ms | 409725 | 320 | 8.33014e+06 | 38084 | 1(Win) |
| simdjson (reflection) | 7355.21 | 0.534442 | 5918.21ms | 409725 | 160 | 1.28978e+07 | 53124.8 | 2(Loss) |
| glaze | 1811.13 | 0.256063 | 5945.71ms | 409725 | 320 | 9.76631e+07 | 215746 | 3(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10099 | 0.237032 | 4041.19ms | 409725 | 2560 | 2.15321e+07 | 38691.5 | 1(Win) |
| simdjson (reflection) | 7990.29 | 0.113223 | 5551.7ms | 409725 | 40 | 122628 | 48902.4 | 2(Loss) |
| glaze | 1720.93 | 0.811041 | 5530.89ms | 409725 | 320 | 1.08516e+09 | 227054 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1456.74 | 0.550168 | 6824.81ms | 785750 | 80 | 6.4074e+08 | 514400 | 1(Win) |
| jsonifier (two-stage) | 1221.6 | 0.240955 | 8430.94ms | 785750 | 160 | 3.49546e+08 | 613418 | 2(Loss) |
| simdjson (reflection) | 1181.48 | 0.105714 | 8195.66ms | 785750 | 320 | 1.43859e+08 | 634249 | 3(Loss) |
| glaze STATISTICAL TIE | 1053.01 | 1.72484 | 9136.79ms | 785750 | 40 | 6.0265e+09 | 711629 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1032.82 | 0.586228 | 9338.48ms | 785750 | 30 | 5.42718e+08 | 725538 | 4(Tie) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1987.84 | 0.867846 | 6101.96ms | 785750 | 640 | 6.84969e+09 | 376967 | 1(Win) |
| jsonifier (two-stage) | 1849.54 | 0.174809 | 7564.35ms | 785750 | 30 | 1.50483e+07 | 405154 | 2(Loss) |
| glaze | 1482.7 | 0.448402 | 8178.8ms | 785750 | 30 | 1.5407e+08 | 505395 | 3(Loss) |
| simdjson (reflection) | 1317.82 | 0.156072 | 8063.74ms | 785750 | 640 | 5.04064e+08 | 568628 | 4(Loss) |
| simdjson (ondemand) | 1231.42 | 0.271916 | 8993.31ms | 785750 | 160 | 4.38074e+08 | 608525 | 5(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12782.3 | 0.138091 | 5709.65ms | 785750 | 40 | 262144 | 58624 | 1(Win) |
| glaze | 2345.85 | 0.296976 | 8536.96ms | 785750 | 30 | 2.69981e+07 | 319437 | 2(Loss) |
| simdjson (reflection) | 324.311 | 0.242972 | 7370.28ms | 785750 | 160 | 5.04286e+09 | 2.31059e+06 | 3(Loss) |
### Random Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.5807779638018574%)


----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4144.42 | 0.223851 | 6288.58ms | 264040 | 80 | 1.47986e+06 | 60758.4 | 1(Win) |
| jsonifier (two-stage) | 4018.49 | 0.157251 | 6708.06ms | 264040 | 320 | 3.10706e+06 | 62662.4 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 2713.82 | 0.941069 | 5024.41ms | 264040 | 160 | 1.21994e+08 | 92787.2 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2621.6 | 3.3058 | 5227.14ms | 264040 | 80 | 8.06585e+08 | 96051.2 | 3(Tie) |
| glaze | 2199.71 | 0.314968 | 5783.15ms | 264040 | 160 | 2.08e+07 | 114474 | 5(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4289.22 | 0.227588 | 6330.07ms | 264040 | 80 | 1.42815e+06 | 58707.2 | 1(Win) |
| jsonifier (two-stage) | 3906.38 | 0.992668 | 6408.94ms | 264040 | 40 | 1.6378e+07 | 64460.8 | 2(Loss) |
| simdjson (ondemand) | 2712.54 | 0.409418 | 9889.76ms | 264040 | 640 | 9.24491e+07 | 92831.2 | 3(Loss) |
| simdjson (reflection) | 2587.25 | 1.129 | 5555.32ms | 264040 | 640 | 7.72735e+08 | 97326.4 | 4(Loss) |
| glaze | 2337.94 | 0.0504882 | 5627.22ms | 264040 | 2560 | 7.56995e+06 | 107705 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4712.23 | 0.142902 | 9244.24ms | 399947 | 640 | 8.56265e+06 | 80942.4 | 1(Win) |
| jsonifier (two-stage) | 3495.35 | 0.976562 | 6287.77ms | 399947 | 2560 | 2.90712e+09 | 109122 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 3301.88 | 0.521156 | 5969.65ms | 399947 | 2560 | 9.27807e+08 | 115516 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 3257.67 | 0.51105 | 6178.94ms | 399947 | 1280 | 4.58276e+08 | 117083 | 3(Tie) |
| glaze | 2354.43 | 1.49553 | 9267.45ms | 399947 | 320 | 1.87835e+09 | 162001 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 4002.8 | 1.37275 | 5577.97ms | 399947 | 1280 | 2.19012e+09 | 95288 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3903.7 | 2.06399 | 6346.53ms | 399947 | 320 | 1.30143e+09 | 97707.2 | 1(Tie) |
| simdjson (reflection) | 3797.85 | 0.223666 | 5279.07ms | 399947 | 320 | 1.61465e+07 | 100430 | 3(Loss) |
| simdjson (ondemand) | 3469.18 | 0.500561 | 5665.37ms | 399947 | 2560 | 7.75367e+08 | 109945 | 4(Loss) |
| glaze | 2359.22 | 2.16628 | 7662.54ms | 399947 | 160 | 1.96255e+09 | 161672 | 5(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1797.78 | 0.582257 | 8518.29ms | 264040 | 30 | 1.99534e+07 | 140066 | 1(Win) |
| jsonifier (two-stage) | 1409.61 | 0.869086 | 5263.12ms | 264040 | 30 | 7.23084e+07 | 178637 | 2(Loss) |
| glaze | 1366.08 | 0.632052 | 5190.9ms | 264040 | 30 | 4.07204e+07 | 184329 | 3(Loss) |
| simdjson (reflection) | 1185.67 | 0.412845 | 5914.76ms | 264040 | 160 | 1.23e+08 | 212376 | 4(Loss) |
| simdjson (ondemand) | 1127.19 | 0.672019 | 6508.97ms | 264040 | 30 | 6.76127e+07 | 223394 | 5(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2159.15 | 0.443775 | 7057.64ms | 264040 | 2560 | 6.85705e+08 | 116624 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1677.93 | 1.06781 | 9509.15ms | 264040 | 80 | 2.05432e+08 | 150070 | 2(Tie) |
| glaze STATISTICAL TIE | 1676.34 | 0.313113 | 9399.6ms | 264040 | 160 | 3.53946e+07 | 150213 | 2(Tie) |
| simdjson (reflection) | 1244.38 | 0.143426 | 5647.44ms | 264040 | 1280 | 1.0782e+08 | 202357 | 4(Loss) |
| simdjson (ondemand) | 1105.03 | 0.344788 | 6173.96ms | 264040 | 1280 | 7.90143e+08 | 227875 | 5(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13586 | 0.519765 | 1992.67ms | 264040 | 30 | 278415 | 18534.4 | 1(Win) |
| simdjson (reflection) | 9795.85 | 0.177293 | 2688.5ms | 264040 | 640 | 1.32929e+06 | 25705.6 | 2(Loss) |
| glaze | 3514.69 | 0.168819 | 8319.7ms | 263923 | 80 | 1.16927e+06 | 71612.8 | 3(Loss) |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13274.3 | 0.36229 | 2045.11ms | 264040 | 30 | 141693 | 18969.6 | 1(Win) |
| simdjson (reflection) | 9813.1 | 0.0867899 | 2583.46ms | 264040 | 4890 | 2.42535e+06 | 25660.4 | 2(Loss) |
| glaze | 4144.98 | 0.573259 | 6678.83ms | 263923 | 40 | 4.84698e+06 | 60723.2 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2209.27 | 0.191501 | 8959.84ms | 399947 | 2560 | 2.79825e+08 | 172645 | 1(Win) |
| jsonifier (two-stage) | 2089.13 | 0.175354 | 5022.52ms | 399947 | 40 | 4.09982e+06 | 182573 | 2(Loss) |
| glaze | 1851.28 | 0.0765518 | 5381.14ms | 399947 | 1280 | 3.18405e+07 | 206030 | 3(Loss) |
| simdjson (reflection) | 1720.53 | 0.138651 | 5794.6ms | 399947 | 80 | 7.55812e+06 | 221686 | 4(Loss) |
| simdjson (ondemand) | 1619.62 | 0.114551 | 6095.37ms | 399947 | 160 | 1.1644e+07 | 235499 | 5(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2753.84 | 0.354422 | 8307.75ms | 399947 | 30 | 7.22922e+06 | 138505 | 1(Win) |
| jsonifier (two-stage) | 2590.39 | 0.0756403 | 8975.91ms | 399947 | 320 | 3.96946e+06 | 147244 | 2(Loss) |
| glaze | 2173.83 | 0.147597 | 5057.04ms | 399947 | 320 | 2.14613e+07 | 175459 | 3(Loss) |
| simdjson (reflection) | 1896.7 | 0.206691 | 5693.29ms | 399947 | 30 | 5.18292e+06 | 201097 | 4(Loss) |
| simdjson (ondemand) | 1683.45 | 0.694125 | 6216.01ms | 399947 | 80 | 1.97865e+08 | 226570 | 5(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14648.6 | 0.152053 | 2605.29ms | 399947 | 640 | 1.0032e+06 | 26038 | 1(Win) |
| glaze | 3695.99 | 0.341932 | 5530.17ms | 399830 | 30 | 3.73329e+06 | 103168 | 2(Loss) |
| simdjson (reflection) | 417.61 | 0.114715 | 5841.83ms | 399947 | 80 | 8.78199e+07 | 913338 | 3(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15226.6 | 0.355814 | 2649.83ms | 399947 | 40 | 317766 | 25049.6 | 1(Win) |
| glaze | 4208.77 | 0.309963 | 9697.06ms | 399830 | 160 | 1.26177e+07 | 90598.4 | 2(Loss) |
| simdjson (reflection) | 418.27 | 0.215368 | 6015.28ms | 399947 | 30 | 1.15711e+08 | 911898 | 3(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 809.055 | 0.228057 | 551.463ms | 4630 | 4890 | 757531 | 5457.62 | 1(Win) |
| jsonifier (two-stage) | 620.296 | 0.830592 | 740.189ms | 4630 | 160 | 559320 | 7118.4 | 2(Loss) |
| simdjson (reflection) | 512.038 | 0.611541 | 944.731ms | 4630 | 2560 | 7.11948e+06 | 8623.4 | 3(Loss) |
| glaze | 456.676 | 0.313692 | 986.618ms | 4630 | 320 | 294375 | 9668.8 | 4(Loss) |
| simdjson (ondemand) | 433.378 | 0.153089 | 1035.35ms | 4630 | 1280 | 311406 | 10188.6 | 5(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1037.48 | 1.17885 | 546.914ms | 4630 | 80 | 201378 | 4256 | 1(Win) |
| jsonifier (two-stage) | 834.217 | 0.19242 | 658.603ms | 4630 | 2560 | 265548 | 5293 | 2(Loss) |
| simdjson (reflection) | 652.841 | 0.114786 | 817.561ms | 4630 | 4890 | 294734 | 6763.53 | 3(Loss) |
| glaze | 522.41 | 0.197806 | 973.592ms | 4630 | 1280 | 357791 | 8452.2 | 4(Loss) |
| simdjson (ondemand) | 449.681 | 0.493819 | 1149.69ms | 4630 | 160 | 376191 | 9819.2 | 5(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2001.96 | 1.03381 | 255.721ms | 4630 | 2560 | 1.331e+06 | 2205.6 | 1(Win) |
| glaze | 1316.65 | 0.764105 | 398.073ms | 4630 | 640 | 420251 | 3353.6 | 2(Loss) |
| simdjson (reflection) | 736.704 | 1.95115 | 662.018ms | 4630 | 160 | 2.18815e+06 | 5993.6 | 3(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2208.86 | 0.471387 | 263.098ms | 4630 | 1280 | 113656 | 1999 | 1(Win) |
| glaze | 1681.59 | 0.560472 | 285.681ms | 4630 | 1280 | 277231 | 2625.8 | 2(Loss) |
| simdjson (reflection) | 787.584 | 0.544739 | 615.14ms | 4630 | 320 | 298466 | 5606.4 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 1848.45 | 0.305509 | 776.661ms | 14795 | 640 | 348050 | 7633.2 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1833.12 | 1.13808 | 816.94ms | 14795 | 30 | 230205 | 7697.07 | 1(Tie) |
| simdjson (reflection) | 1538.87 | 0.0994724 | 1001.84ms | 14795 | 2560 | 212947 | 9168.8 | 3(Loss) |
| simdjson (ondemand) | 1239.08 | 0.344086 | 1237.6ms | 14795 | 160 | 245634 | 11387.2 | 4(Loss) |
| glaze | 1031.22 | 0.56234 | 1487.14ms | 14795 | 320 | 1.8944e+06 | 13682.4 | 5(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2251.05 | 0.159471 | 754.238ms | 14795 | 2560 | 255777 | 6268 | 1(Win) |
| jsonifier (two-stage) | 2177.81 | 0.353672 | 777.288ms | 14795 | 640 | 336024 | 6478.8 | 2(Loss) |
| simdjson (reflection) | 1762.86 | 0.112219 | 926.146ms | 14795 | 1280 | 103260 | 8003.8 | 3(Loss) |
| simdjson (ondemand) | 1375.16 | 0.102685 | 1155.74ms | 14795 | 4890 | 542803 | 10260.3 | 4(Loss) |
| glaze | 1138.53 | 0.378623 | 1429.66ms | 14795 | 320 | 704537 | 12392.8 | 5(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6689.89 | 0.235329 | 218.237ms | 14795 | 4890 | 120462 | 2109.09 | 1(Win) |
| glaze | 2881.81 | 0.174023 | 502.026ms | 14795 | 2560 | 185845 | 4896.1 | 2(Loss) |
| simdjson (reflection) | 121.47 | 0.0830898 | 5978.26ms | 14795 | 2560 | 2.38467e+07 | 116157 | 3(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5394.82 | 0.858883 | 248.695ms | 14795 | 1280 | 645883 | 2615.4 | 1(Win) |
| glaze | 3211.11 | 0.346287 | 449.14ms | 14795 | 1280 | 296349 | 4394 | 2(Loss) |
| simdjson (reflection) | 122.86 | 0.171214 | 6111.74ms | 14795 | 160 | 6.18602e+06 | 114843 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1307.94 | 0.541679 | 377.572ms | 5092 | 640 | 258861 | 3712.8 | 1(Win) |
| jsonifier (two-stage) | 985.652 | 0.304287 | 501.607ms | 5092 | 640 | 143839 | 4926.8 | 2(Loss) |
| glaze | 903.967 | 0.517312 | 550.122ms | 5092 | 320 | 247131 | 5372 | 3(Loss) |
| simdjson (ondemand) | 842.103 | 0.147753 | 584.441ms | 5092 | 4890 | 355002 | 5766.65 | 4(Loss) |
| simdjson (reflection) | 819.846 | 0.274685 | 618.878ms | 5092 | 640 | 169419 | 5923.2 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1822.86 | 0.532805 | 357.276ms | 5092 | 1280 | 257878 | 2664 | 1(Win) |
| jsonifier (two-stage) | 1205.35 | 0.296728 | 494.346ms | 5092 | 2560 | 365854 | 4028.8 | 2(Loss) |
| glaze STATISTICAL TIE | 1043.7 | 0.742338 | 553.744ms | 5092 | 320 | 381752 | 4652.8 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1034.14 | 0.310378 | 557.662ms | 5092 | 1280 | 271902 | 4695.8 | 3(Tie) |
| simdjson (reflection) | 943.154 | 0.897627 | 682.373ms | 5092 | 80 | 170881 | 5148.8 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 7262.14 | 2.23337 | 76.0271ms | 5092 | 4890 | 1.09063e+06 | 668.689 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 7078.7 | 1.02202 | 70.9919ms | 5092 | 4890 | 240381 | 686.017 | 1(Tie) |
| glaze | 1431.3 | 0.850349 | 350.274ms | 5092 | 320 | 266355 | 3392.8 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9002.8 | 1.87609 | 58.124ms | 5092 | 2560 | 262161 | 539.4 | 1(Win) |
| simdjson (reflection) | 5998.16 | 2.75616 | 76.777ms | 5092 | 320 | 159331 | 809.6 | 2(Loss) |
| glaze | 1600.73 | 0.306584 | 304.93ms | 5092 | 4890 | 423007 | 3033.68 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2137.67 | 0.473282 | 539.872ms | 11724 | 320 | 196092 | 5230.4 | 1(Win) |
| jsonifier (two-stage) | 1959.49 | 0.357008 | 622.313ms | 11724 | 640 | 265582 | 5706 | 2(Loss) |
| simdjson (ondemand) | 1713.91 | 0.356534 | 670.239ms | 11724 | 640 | 346224 | 6523.6 | 3(Loss) |
| simdjson (reflection) | 1673.58 | 0.345463 | 679.274ms | 11724 | 640 | 340910 | 6680.8 | 4(Loss) |
| glaze | 1459.49 | 0.922075 | 919.672ms | 11724 | 40 | 199591 | 7660.8 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2537.88 | 0.564527 | 530.108ms | 11724 | 640 | 395877 | 4405.6 | 1(Win) |
| jsonifier (two-stage) | 2458.63 | 0.448108 | 561.995ms | 11724 | 640 | 265772 | 4547.6 | 2(Loss) |
| simdjson (ondemand) | 2047.7 | 0.210178 | 637.483ms | 11724 | 2560 | 337157 | 5460.2 | 3(Loss) |
| simdjson (reflection) | 1969.23 | 0.433193 | 659.218ms | 11724 | 1280 | 774341 | 5677.8 | 4(Loss) |
| glaze | 1704.61 | 0.233326 | 750.161ms | 11724 | 1280 | 299805 | 6559.2 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14316.4 | 0.855158 | 84.7319ms | 11724 | 4890 | 218115 | 780.983 | 1(Win) |
| glaze | 2780.31 | 0.216691 | 412.018ms | 11746 | 4890 | 372719 | 4028.99 | 2(Loss) |
| simdjson (reflection) | 325.393 | 0.0880766 | 3636.24ms | 11724 | 1280 | 1.17238e+06 | 34361.2 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17849.4 | 2.17489 | 66.5748ms | 11724 | 1280 | 237569 | 626.4 | 1(Win) |
| glaze | 3136.11 | 0.297284 | 363.745ms | 11746 | 2560 | 288658 | 3571.9 | 2(Loss) |
| simdjson (reflection) | 323.701 | 0.119257 | 3498.23ms | 11724 | 640 | 1.08595e+06 | 34540.8 | 3(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1529.42 | 0.240038 | 306.354ms | 4857 | 1280 | 67647.7 | 3028.6 | 1(Win) |
| glaze | 1165.09 | 0.122342 | 413.387ms | 4857 | 4890 | 115685 | 3975.64 | 2(Loss) |
| jsonifier (two-stage) | 1147.95 | 0.123627 | 408.601ms | 4857 | 4890 | 121681 | 4035.01 | 3(Loss) |
| simdjson (ondemand) | 891.008 | 0.182571 | 527.197ms | 4857 | 2560 | 230610 | 5198.6 | 4(Loss) |
| simdjson (reflection) | 788.398 | 2.05178 | 651.292ms | 4857 | 40 | 581254 | 5875.2 | 5(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2256.21 | 0.282275 | 259.274ms | 4857 | 2560 | 85973.4 | 2053 | 1(Win) |
| glaze | 1705.45 | 0.56357 | 303.389ms | 4857 | 1280 | 299892 | 2716 | 2(Loss) |
| jsonifier (two-stage) | 1533.42 | 0.147715 | 362.239ms | 4857 | 2560 | 50969 | 3020.7 | 3(Loss) |
| simdjson (reflection) | 1222.87 | 0.358168 | 429.648ms | 4857 | 1280 | 235590 | 3787.8 | 4(Loss) |
| simdjson (ondemand) | 1142.46 | 0.527825 | 470.424ms | 4857 | 160 | 73274.6 | 4054.4 | 5(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9923.55 | 1.56215 | 49.184ms | 4857 | 4890 | 259990 | 466.768 | 1(Win) |
| simdjson (reflection) | 8106.87 | 1.2632 | 59.9501ms | 4857 | 4890 | 254731 | 571.367 | 2(Loss) |
| glaze | 2568.24 | 0.345771 | 184.966ms | 4857 | 4890 | 190174 | 1803.57 | 3(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11661.6 | 2.44778 | 43.126ms | 4857 | 2560 | 241994 | 397.2 | 1(Win) |
| simdjson (reflection) | 8924.85 | 1.94252 | 55.3411ms | 4857 | 2560 | 260200 | 519 | 2(Loss) |
| glaze | 3057.42 | 0.669008 | 156.686ms | 4857 | 2560 | 262983 | 1515 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1620.28 | 0.26551 | 442.206ms | 7376 | 2560 | 340142 | 4341.4 | 1(Win) |
| glaze | 1508.36 | 0.201343 | 474.602ms | 7376 | 4890 | 431135 | 4663.55 | 2(Loss) |
| simdjson (reflection) | 1421.04 | 0.147921 | 505.642ms | 7376 | 2560 | 137255 | 4950.1 | 3(Loss) |
| jsonifier | 1336.15 | 1.74468 | 536.262ms | 7376 | 1280 | 1.07988e+07 | 5264.6 | 4(Loss) |
| simdjson (ondemand) | 1176.78 | 0.338255 | 600.176ms | 7376 | 320 | 130825 | 5977.6 | 5(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2317.42 | 0.164282 | 362.969ms | 7376 | 2560 | 63658.1 | 3035.4 | 1(Win) |
| glaze | 2254.01 | 0.171406 | 363.476ms | 7376 | 4890 | 139924 | 3120.79 | 2(Loss) |
| jsonifier (two-stage) | 2098.13 | 0.222774 | 394.231ms | 7376 | 4890 | 272782 | 3352.66 | 3(Loss) |
| simdjson (reflection) | 1731.56 | 0.539187 | 460.14ms | 7376 | 160 | 76765.2 | 4062.4 | 4(Loss) |
| simdjson (ondemand) | 1536.14 | 0.88946 | 489.665ms | 7376 | 160 | 265431 | 4579.2 | 5(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11199.3 | 1.5324 | 63.9398ms | 7376 | 2560 | 237161 | 628.1 | 1(Win) |
| glaze | 2326.16 | 0.601367 | 352.007ms | 7376 | 160 | 52913.1 | 3024 | 2(Loss) |
| simdjson (reflection) | 353.902 | 0.157554 | 2004.74ms | 7376 | 1280 | 1.25528e+06 | 19876.4 | 3(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12924.8 | 1.33363 | 57.0949ms | 7376 | 4890 | 257619 | 544.249 | 1(Win) |
| glaze | 2779.04 | 0.582995 | 266.87ms | 7376 | 1280 | 278736 | 2531.2 | 2(Loss) |
| simdjson (reflection) | 354.066 | 0.367046 | 2003.43ms | 7376 | 160 | 850811 | 19867.2 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1736.54 | 0.421992 | 243.542ms | 4390 | 2560 | 264977 | 2410.9 | 1(Win) |
| jsonifier (two-stage) | 1106.23 | 0.250525 | 386.578ms | 4390 | 2560 | 230134 | 3784.6 | 2(Loss) |
| simdjson (reflection) | 912.319 | 0.355595 | 464.637ms | 4390 | 1280 | 340846 | 4589 | 3(Loss) |
| glaze | 796.452 | 0.575667 | 467.145ms | 4390 | 1280 | 1.17209e+06 | 5256.6 | 4(Loss) |
| simdjson (ondemand) | 691.319 | 0.745906 | 591.012ms | 4390 | 160 | 326482 | 6056 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2233.64 | 0.282432 | 233.062ms | 4390 | 4890 | 137037 | 1874.35 | 1(Win) |
| jsonifier (two-stage) | 1294.41 | 0.393811 | 395.983ms | 4390 | 1280 | 207670 | 3234.4 | 2(Loss) |
| glaze STATISTICAL TIE | 963.891 | 2.45519 | 496.095ms | 4390 | 30 | 341164 | 4343.47 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 924.446 | 0.560213 | 474.589ms | 4390 | 640 | 411958 | 4528.8 | 3(Tie) |
| simdjson (ondemand) | 830.549 | 0.266157 | 621.47ms | 4390 | 320 | 57600.2 | 5040.8 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9362.11 | 1.59851 | 47.5292ms | 4390 | 4890 | 249873 | 447.189 | 1(Win) |
| simdjson (reflection) | 7570.16 | 1.30338 | 57.2659ms | 4390 | 4890 | 254078 | 553.044 | 2(Loss) |
| glaze | 1740.22 | 0.605826 | 245.666ms | 4390 | 1280 | 271910 | 2405.8 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10279.1 | 1.73316 | 44.3558ms | 4390 | 4890 | 243672 | 407.297 | 1(Win) |
| simdjson (reflection) | 8239.35 | 1.41449 | 54.793ms | 4390 | 4890 | 252612 | 508.126 | 2(Loss) |
| glaze | 1881.21 | 0.406035 | 228.092ms | 4390 | 2560 | 209036 | 2225.5 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2336.92 | 1.04726 | 491.852ms | 11521 | 320 | 775795 | 4701.6 | 1(Win) |
| jsonifier (two-stage) | 2061.95 | 0.268963 | 541.463ms | 11521 | 1280 | 262919 | 5328.6 | 2(Loss) |
| simdjson (reflection) | 2022.99 | 0.528249 | 560.902ms | 11521 | 320 | 263402 | 5431.2 | 3(Loss) |
| glaze | 1686.41 | 0.516408 | 666.597ms | 11521 | 320 | 362235 | 6515.2 | 4(Loss) |
| simdjson (ondemand) | 1657.88 | 0.205256 | 668.065ms | 11521 | 2560 | 473704 | 6627.3 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3144 | 0.22063 | 396.117ms | 11521 | 4890 | 290707 | 3494.69 | 1(Win) |
| jsonifier (two-stage) | 2546.83 | 0.233701 | 531.157ms | 11521 | 2560 | 260220 | 4314.1 | 2(Loss) |
| simdjson (reflection) | 2235.37 | 0.708046 | 542.57ms | 11521 | 80 | 96893.7 | 4915.2 | 3(Loss) |
| glaze | 1877.81 | 0.169291 | 641.323ms | 11521 | 2560 | 251178 | 5851.1 | 4(Loss) |
| simdjson (ondemand) | 1858.09 | 0.206415 | 642.474ms | 11521 | 1280 | 190695 | 5913.2 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16149.1 | 1.00869 | 70.622ms | 11521 | 4890 | 230307 | 680.363 | 1(Win) |
| glaze | 2739.15 | 0.308504 | 409.43ms | 11521 | 160 | 24501.3 | 4011.2 | 2(Loss) |
| simdjson (reflection) | 300.694 | 0.270685 | 3819.61ms | 11521 | 30 | 293481 | 36539.7 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17024 | 2.08914 | 70.9642ms | 11521 | 1280 | 232703 | 645.4 | 1(Win) |
| glaze | 3011.62 | 0.27785 | 372.436ms | 11521 | 2560 | 263053 | 3648.3 | 2(Loss) |
| simdjson (reflection) | 303.067 | 0.100206 | 3821.77ms | 11521 | 640 | 844629 | 36253.6 | 3(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2552.72 | 0.521206 | 179.802ms | 4669 | 2560 | 211593 | 1744.3 | 1(Win) |
| jsonifier (two-stage) | 1508.95 | 0.191665 | 301.909ms | 4669 | 4890 | 156420 | 2950.86 | 2(Loss) |
| glaze | 1268.53 | 0.219016 | 361.086ms | 4669 | 4890 | 289005 | 3510.13 | 3(Loss) |
| simdjson (reflection) | 1053.79 | 0.324139 | 423.255ms | 4669 | 1280 | 240109 | 4225.4 | 4(Loss) |
| simdjson (ondemand) | 925.18 | 1.7763 | 566.772ms | 4669 | 80 | 584681 | 4812.8 | 5(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2955.61 | 0.508664 | 166.394ms | 4669 | 4890 | 287160 | 1506.53 | 1(Win) |
| glaze | 1458.76 | 0.173668 | 324.139ms | 4669 | 2560 | 71938.3 | 3052.4 | 2(Loss) |
| jsonifier (two-stage) | 1359.29 | 1.21862 | 317.585ms | 4669 | 4890 | 7.79229e+06 | 3275.75 | 3(Loss) |
| simdjson (reflection) | 1243.63 | 0.614111 | 409.62ms | 4669 | 640 | 309411 | 3580.4 | 4(Loss) |
| simdjson (ondemand) | 1016.79 | 1.51879 | 437.402ms | 4669 | 640 | 2.83115e+06 | 4379.2 | 5(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11852.5 | 1.92637 | 41.5642ms | 4669 | 4890 | 256103 | 375.676 | 1(Win) |
| simdjson (reflection) | 6489.18 | 0.989747 | 71.9918ms | 4669 | 4890 | 225541 | 686.174 | 2(Loss) |
| glaze | 1540.3 | 0.684643 | 294.84ms | 4669 | 640 | 250694 | 2890.8 | 3(Loss) |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12157.5 | 2.06443 | 39.4181ms | 4669 | 4890 | 279557 | 366.253 | 1(Win) |
| simdjson (reflection) | 6730.21 | 4.03078 | 75.7932ms | 4669 | 320 | 227573 | 661.6 | 2(Loss) |
| glaze | 1887.86 | 0.604063 | 253.195ms | 4669 | 1280 | 259827 | 2358.6 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2282.1 | 0.319024 | 446.292ms | 9249 | 2560 | 389231 | 3865.1 | 1(Win) |
| simdjson (reflection) | 2044.63 | 0.435529 | 459.9ms | 9249 | 640 | 225930 | 4314 | 2(Loss) |
| glaze | 1764.49 | 0.279502 | 523.232ms | 9249 | 2560 | 499757 | 4998.9 | 3(Loss) |
| simdjson (ondemand) | 1586.75 | 0.884336 | 548.06ms | 9249 | 4890 | 1.18172e+07 | 5558.86 | 4(Loss) |
| jsonifier | 1356.46 | 0.256409 | 700.66ms | 9249 | 2560 | 711671 | 6502.6 | 5(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3246.18 | 0.750301 | 340.541ms | 9249 | 640 | 266008 | 2717.2 | 1(Win) |
| jsonifier (two-stage) | 2660.47 | 0.519692 | 349.79ms | 9249 | 1280 | 379991 | 3315.4 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 2144.13 | 0.275848 | 437.371ms | 9249 | 1280 | 164830 | 4113.8 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2126.86 | 0.702619 | 507.084ms | 9249 | 160 | 135853 | 4147.2 | 3(Tie) |
| glaze | 1713.12 | 0.861618 | 512.717ms | 9249 | 160 | 314892 | 5148.8 | 5(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16300.9 | 1.33628 | 58.6391ms | 9249 | 4890 | 255667 | 541.108 | 1(Win) |
| glaze | 2174.1 | 0.143875 | 475.64ms | 9249 | 2560 | 87224.9 | 4057.1 | 2(Loss) |
| simdjson (reflection) | 334.76 | 0.251794 | 2811.82ms | 9249 | 40 | 176065 | 26348.8 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15142.5 | 1.68491 | 58.6002ms | 9249 | 2560 | 246595 | 582.5 | 1(Win) |
| glaze | 2258.9 | 0.311593 | 408.374ms | 9249 | 2560 | 378976 | 3904.8 | 2(Loss) |
| simdjson (reflection) | 333.343 | 0.234242 | 2695.27ms | 9249 | 80 | 307345 | 26460.8 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 578.132 | 1.18028 | 910.799ms | 4604 | 30 | 241052 | 7594.67 | 1(Win) |
| jsonifier (two-stage) | 479.294 | 0.211396 | 942.199ms | 4604 | 640 | 240016 | 9160.8 | 2(Loss) |
| simdjson (reflection) | 411.733 | 0.791294 | 997.699ms | 4604 | 160 | 1.13929e+06 | 10664 | 3(Loss) |
| glaze | 400.883 | 0.153527 | 1127.81ms | 4604 | 2560 | 723844 | 10952.6 | 4(Loss) |
| simdjson (ondemand) | 367.436 | 0.203143 | 1246.22ms | 4604 | 320 | 188564 | 11949.6 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 731.986 | 0.0864053 | 761.355ms | 4604 | 4890 | 131357 | 5998.36 | 1(Win) |
| jsonifier (two-stage) | 582.385 | 0.528209 | 914.52ms | 4604 | 160 | 253736 | 7539.2 | 2(Loss) |
| simdjson (reflection) | 533.199 | 0.978372 | 916.295ms | 4604 | 30 | 194725 | 8234.67 | 3(Loss) |
| glaze | 478.271 | 0.185649 | 1080.65ms | 4604 | 640 | 185903 | 9180.4 | 4(Loss) |
| simdjson (ondemand) | 402.028 | 0.167693 | 1216.35ms | 4604 | 4890 | 1.64019e+06 | 10921.4 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1736.01 | 0.79639 | 251.689ms | 4604 | 640 | 259655 | 2529.2 | 1(Win) |
| simdjson (reflection) | 1530.33 | 0.496557 | 316.045ms | 4918 | 320 | 74112.6 | 3064.8 | 2(Loss) |
| glaze | 949.59 | 0.346282 | 474.539ms | 4604 | 1280 | 328148 | 4623.8 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1842.59 | 0.42162 | 245.251ms | 4604 | 2560 | 258401 | 2382.9 | 1(Win) |
| simdjson (reflection) | 1523.79 | 0.154291 | 313.757ms | 4918 | 4890 | 110286 | 3077.97 | 2(Loss) |
| glaze | 1011.16 | 0.187823 | 440.248ms | 4604 | 4890 | 325266 | 4342.26 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2101.5 | 0.155194 | 1127.58ms | 24579 | 4890 | 1.4653e+06 | 11154.1 | 1(Win) |
| jsonifier STATISTICAL TIE | 2070.38 | 0.145707 | 1117.06ms | 24579 | 4890 | 1.33075e+06 | 11321.7 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2058.77 | 0.486558 | 1162.99ms | 24579 | 80 | 245511 | 11385.6 | 2(Tie) |
| simdjson (ondemand) | 1652.48 | 0.107787 | 1440.38ms | 24579 | 1280 | 299225 | 14185 | 4(Loss) |
| glaze | 1548.72 | 0.0729999 | 1566.51ms | 24579 | 2560 | 312512 | 15135.3 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2531.79 | 0.408336 | 1095.68ms | 24579 | 320 | 457359 | 9258.4 | 1(Win) |
| jsonifier (two-stage) | 2495.93 | 0.161107 | 1136.77ms | 24579 | 4890 | 1.11944e+06 | 9391.43 | 2(Loss) |
| simdjson (reflection) | 2379.44 | 0.2887 | 1150.15ms | 24579 | 320 | 258834 | 9851.2 | 3(Loss) |
| simdjson (ondemand) | 1857.04 | 0.189863 | 1423.78ms | 24579 | 640 | 367573 | 12622.4 | 4(Loss) |
| glaze | 1739.8 | 0.158131 | 1514.25ms | 24579 | 1280 | 580997 | 13473 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6269.99 | 0.471967 | 377.747ms | 24579 | 2560 | 796998 | 3738.5 | 1(Win) |
| glaze | 3001.4 | 0.222553 | 803.968ms | 24579 | 2560 | 773368 | 7809.8 | 2(Loss) |
| simdjson (reflection) | 179.173 | 0.187498 | 6862.75ms | 24893 | 640 | 3.9499e+07 | 132497 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7968.03 | 0.320445 | 300.501ms | 24579 | 1280 | 113748 | 2941.8 | 1(Win) |
| glaze | 3429.96 | 0.276342 | 709.194ms | 24579 | 640 | 228257 | 6834 | 2(Loss) |
| simdjson (reflection) | 182.719 | 0.201603 | 6994.5ms | 24893 | 640 | 4.39099e+07 | 129925 | 3(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 560.67 | 0.656685 | 872.887ms | 4604 | 320 | 846292 | 7831.2 | 1(Win) |
| jsonifier (two-stage) | 549.132 | 0.251463 | 946.409ms | 4604 | 30 | 12127.9 | 7995.73 | 2(Loss) |
| glaze STATISTICAL TIE | 403.144 | 0.243488 | 1213.06ms | 4604 | 320 | 225039 | 10891.2 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 399.796 | 0.890454 | 1166.19ms | 4604 | 160 | 1.53016e+06 | 10982.4 | 3(Tie) |
| simdjson (ondemand) | 323.818 | 0.598113 | 1400.45ms | 4604 | 320 | 2.10468e+06 | 13559.2 | 5(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 824.408 | 0.250054 | 698.329ms | 4604 | 2560 | 454039 | 5325.9 | 1(Win) |
| jsonifier (two-stage) | 565.348 | 1.85886 | 988.253ms | 4604 | 80 | 1.66734e+06 | 7766.4 | 2(Loss) |
| simdjson (reflection) | 520.128 | 1.03907 | 1125.16ms | 4604 | 80 | 615499 | 8441.6 | 3(Loss) |
| glaze | 477.307 | 0.580592 | 1379.82ms | 4604 | 30 | 85573.4 | 9198.93 | 4(Loss) |
| simdjson (ondemand) | 413.281 | 0.126054 | 1335.57ms | 4604 | 4890 | 877001 | 10624.1 | 5(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1500.64 | 0.411905 | 319.217ms | 4604 | 2560 | 371837 | 2925.9 | 1(Win) |
| simdjson (reflection) | 1294.77 | 2.80126 | 530.885ms | 4918 | 40 | 411869 | 3622.4 | 2(Loss) |
| glaze | 759.167 | 0.499912 | 632.474ms | 4604 | 640 | 535012 | 5783.6 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1657.12 | 2.313 | 321.445ms | 4604 | 80 | 300470 | 2649.6 | 1(Win) |
| simdjson (reflection) | 1353.98 | 1.30713 | 350.554ms | 4918 | 160 | 328028 | 3464 | 2(Loss) |
| glaze | 845.409 | 0.767293 | 526.664ms | 4604 | 320 | 508171 | 5193.6 | 3(Loss) |
### Marine IK Small Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 1.40811882725697%)

### Marine IK Small Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 1.3920330133585215%)


----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6420.24 | 0.771703 | 372.027ms | 24579 | 4890 | 3.88182e+06 | 3651.01 | 1(Win) |
| glaze | 2473.03 | 1.91589 | 933.953ms | 24579 | 40 | 1.31908e+06 | 9478.4 | 2(Loss) |
| simdjson (reflection) | 153.679 | 0.194882 | 8288.63ms | 24893 | 2560 | 2.3201e+08 | 154476 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6490.6 | 0.929792 | 352.747ms | 24579 | 4890 | 5.51365e+06 | 3611.43 | 1(Win) |
| glaze | 3125.05 | 1.193 | 857.875ms | 24579 | 30 | 240223 | 7500.8 | 2(Loss) |
| simdjson (reflection) | 160.643 | 0.179526 | 8072.76ms | 24893 | 2560 | 1.80189e+08 | 147780 | 3(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 765.21 | 0.568973 | 149.313ms | 1181 | 4890 | 342950 | 1471.87 | 1(Win) |
| jsonifier (two-stage) | 592.534 | 2.64386 | 191.891ms | 1181 | 80 | 202042 | 1900.8 | 2(Loss) |
| glaze STATISTICAL TIE | 513.748 | 0.426317 | 237.987ms | 1181 | 2560 | 223617 | 2192.3 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 507.887 | 1.52468 | 236.878ms | 1181 | 160 | 182913 | 2217.6 | 3(Tie) |
| simdjson (ondemand) | 437.39 | 0.494046 | 275.263ms | 1181 | 4890 | 791421 | 2575.02 | 5(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 924.4 | 1.95579 | 136.179ms | 1181 | 320 | 181708 | 1218.4 | 1(Win) |
| glaze | 820.432 | 2.79861 | 162.516ms | 1181 | 160 | 236167 | 1372.8 | 2(Loss) |
| jsonifier (two-stage) | 741.663 | 1.03751 | 165.258ms | 1181 | 1280 | 317744 | 1518.6 | 3(Loss) |
| simdjson (ondemand) | 697.393 | 0.857164 | 184.159ms | 1181 | 1280 | 245291 | 1615 | 4(Loss) |
| simdjson (reflection) | 565.463 | 0.554891 | 213.458ms | 1181 | 2560 | 312714 | 1991.8 | 5(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2117.09 | 2.63802 | 57.227ms | 1181 | 1280 | 252111 | 532 | 1(Win) |
| simdjson (reflection) | 976.209 | 0.953648 | 125.306ms | 1187 | 1280 | 156532 | 1159.6 | 2(Loss) |
| glaze | 914.79 | 1.94299 | 128.239ms | 1181 | 320 | 183125 | 1231.2 | 3(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2169.39 | 1.53259 | 55.3541ms | 1181 | 4890 | 309586 | 519.172 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 999.922 | 0.652019 | 114.401ms | 1187 | 2560 | 139486 | 1132.1 | 2(Tie) |
| glaze STATISTICAL TIE | 956.428 | 5.09233 | 130.024ms | 1181 | 40 | 143843 | 1177.6 | 2(Tie) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1268.04 | 0.604452 | 197.516ms | 2496 | 1280 | 164799 | 1877.2 | 1(Win) |
| jsonifier (two-stage) | 1218.95 | 1.22183 | 192.928ms | 2496 | 320 | 182175 | 1952.8 | 2(Loss) |
| simdjson (reflection) | 977.485 | 0.615483 | 252.999ms | 2496 | 1280 | 287549 | 2435.2 | 3(Loss) |
| glaze | 941.602 | 0.429053 | 268.414ms | 2496 | 2560 | 301174 | 2528 | 4(Loss) |
| simdjson (ondemand) | 822.633 | 1.77468 | 311.66ms | 2496 | 1280 | 3.37541e+06 | 2893.6 | 5(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1422.23 | 0.514533 | 184.218ms | 2496 | 4890 | 362646 | 1673.69 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1404.18 | 1.27223 | 190.035ms | 2496 | 640 | 297680 | 1695.2 | 1(Tie) |
| glaze STATISTICAL TIE | 1356.18 | 1.0587 | 194.005ms | 2496 | 640 | 220994 | 1755.2 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1329.96 | 0.756938 | 190.269ms | 2496 | 1280 | 234931 | 1789.8 | 3(Tie) |
| simdjson (reflection) | 1106.53 | 0.415341 | 243.439ms | 2496 | 2560 | 204367 | 2151.2 | 5(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3458.84 | 1.34223 | 75.735ms | 2496 | 2560 | 218434 | 688.2 | 1(Win) |
| glaze | 1210.44 | 1.05246 | 199.797ms | 2507 | 320 | 138288 | 1975.2 | 2(Loss) |
| simdjson (reflection) | 83.6193 | 0.542336 | 2924.18ms | 2502 | 640 | 1.53278e+07 | 28535.2 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3679.09 | 2.08205 | 68.3712ms | 2496 | 1280 | 232273 | 647 | 1(Win) |
| glaze | 1399.56 | 0.595631 | 181.151ms | 2507 | 2560 | 265047 | 1708.3 | 2(Loss) |
| simdjson (reflection) | 83.4255 | 0.500711 | 2960.4ms | 2502 | 2560 | 5.2504e+07 | 28601.5 | 3(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1377.13 | 0.274562 | 347.66ms | 4926 | 4890 | 428971 | 3411.29 | 1(Win) |
| jsonifier (two-stage) | 856.512 | 1.30697 | 543.717ms | 4926 | 80 | 411093 | 5484.8 | 2(Loss) |
| simdjson (reflection) | 720.939 | 0.3627 | 664.447ms | 4926 | 4890 | 2.73147e+06 | 6516.22 | 3(Loss) |
| glaze | 682.245 | 0.51615 | 699.918ms | 4926 | 2560 | 3.2337e+06 | 6885.8 | 4(Loss) |
| simdjson (ondemand) | 607.351 | 0.399022 | 805.852ms | 4926 | 2560 | 2.43862e+06 | 7734.9 | 5(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1960.03 | 2.44246 | 351.654ms | 4926 | 80 | 274162 | 2396.8 | 1(Win) |
| jsonifier (two-stage) | 1176.57 | 0.588834 | 524.175ms | 4926 | 320 | 176885 | 3992.8 | 2(Loss) |
| glaze | 937.142 | 0.218722 | 606.87ms | 4926 | 2560 | 307754 | 5012.9 | 3(Loss) |
| simdjson (ondemand) | 745.254 | 0.228757 | 729.626ms | 4926 | 4890 | 1.01681e+06 | 6303.62 | 4(Loss) |
| simdjson (reflection) | 312.62 | 0.247074 | 814.103ms | 4926 | 30 | 41355.5 | 15027.2 | 5(Loss) |
### Random Small Test (Minified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 2.004938152311527%)


----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10239.3 | 3.39331 | 52.854ms | 4926 | 1280 | 310244 | 458.8 | 1(Win) |
| simdjson (reflection) | 8050.9 | 1.23695 | 59.6221ms | 4926 | 4890 | 254750 | 583.512 | 2(Loss) |
| glaze | 1901.02 | 1.68868 | 257.52ms | 4926 | 320 | 557261 | 2471.2 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1824.1 | 0.520553 | 515.962ms | 9463 | 4890 | 3.2434e+06 | 4947.45 | 1(Win) |
| simdjson (reflection) | 1255.28 | 0.324587 | 744.359ms | 9463 | 2560 | 1.39404e+06 | 7189.3 | 2(Loss) |
| jsonifier (two-stage) | 1229.38 | 0.750699 | 707.483ms | 9463 | 320 | 971782 | 7340.8 | 3(Loss) |
| glaze | 1193.16 | 0.35523 | 774.242ms | 9463 | 1280 | 924031 | 7563.6 | 4(Loss) |
| simdjson (ondemand) | 1085.37 | 0.460775 | 857.114ms | 9463 | 640 | 939425 | 8314.8 | 5(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2280.33 | 0.497486 | 496.857ms | 9463 | 640 | 248087 | 3957.6 | 1(Win) |
| jsonifier (two-stage) | 1714.01 | 0.364793 | 729.814ms | 9463 | 4890 | 1.80399e+06 | 5265.22 | 2(Loss) |
| simdjson (reflection) | 1532.87 | 0.288985 | 725.391ms | 9463 | 1280 | 370516 | 5887.4 | 3(Loss) |
| glaze | 1432.48 | 1.82764 | 818.151ms | 9463 | 320 | 4.24241e+06 | 6300 | 4(Loss) |
| simdjson (ondemand) | 1294.41 | 0.693883 | 821.828ms | 9463 | 320 | 748923 | 6972 | 5(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11103.1 | 1.36275 | 78.2039ms | 9463 | 1280 | 157040 | 812.8 | 1(Win) |
| glaze | 2085.99 | 0.576989 | 444.794ms | 9463 | 2560 | 1.59518e+06 | 4326.3 | 2(Loss) |
| simdjson (reflection) | 271.445 | 0.548638 | 3480.45ms | 9463 | 1280 | 4.2587e+07 | 33246.6 | 3(Loss) |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13974.3 | 1.48929 | 69.41ms | 9463 | 2560 | 236808 | 645.8 | 1(Win) |
| glaze | 2403.23 | 0.929793 | 395.318ms | 9463 | 320 | 390111 | 3755.2 | 2(Loss) |
| simdjson (reflection) | 298.813 | 0.595892 | 3297.61ms | 9463 | 40 | 1.29555e+06 | 30201.6 | 3(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 3221.16 | 1.55469 | 90.4671ms | 2821 | 1280 | 215813 | 835.2 | 1(Win) |
| jsonifier | 2995.93 | 0.81806 | 98.3741ms | 2821 | 4890 | 263889 | 897.989 | 2(Loss) |
| simdjson (ondemand) | 2769.71 | 0.349785 | 105.074ms | 2821 | 4890 | 56448.1 | 971.334 | 3(Loss) |
| simdjson (reflection) | 2666.32 | 0.692214 | 107.211ms | 2821 | 1280 | 62441.4 | 1009 | 4(Loss) |
| glaze | 1947.25 | 2.00278 | 140.289ms | 2821 | 320 | 245009 | 1381.6 | 5(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3744.87 | 1.76669 | 83.041ms | 2821 | 1280 | 206187 | 718.4 | 1(Win) |
| jsonifier (two-stage) | 3402.88 | 1.47196 | 87.2581ms | 2821 | 1280 | 173346 | 790.6 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 2873.04 | 1.08829 | 105.248ms | 2821 | 640 | 66465.3 | 936.4 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2827.47 | 0.41459 | 108.797ms | 2821 | 4890 | 76095.3 | 951.493 | 3(Tie) |
| glaze | 2199.77 | 0.700997 | 130.34ms | 2821 | 2560 | 188159 | 1223 | 5(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3911.08 | 1.55358 | 120.079ms | 4147 | 80 | 19743.8 | 1011.2 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3830.28 | 3.66076 | 112.461ms | 4147 | 30 | 42862.1 | 1032.53 | 1(Tie) |
| simdjson (reflection) | 3437.84 | 1.7675 | 130.377ms | 4147 | 320 | 132302 | 1150.4 | 3(Loss) |
| simdjson (ondemand) | 3271.21 | 0.717843 | 128.744ms | 4147 | 2560 | 192820 | 1209 | 4(Loss) |
| glaze | 2735.43 | 0.72173 | 150.558ms | 4147 | 2560 | 278744 | 1445.8 | 5(Loss) |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3896.44 | 0.788342 | 109.469ms | 4147 | 1280 | 81954.2 | 1015 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3859.18 | 1.94685 | 184.72ms | 4147 | 2560 | 1.01902e+06 | 1024.8 | 1(Tie) |
| simdjson (reflection) | 3705.85 | 1.88111 | 125.169ms | 4147 | 160 | 64482.4 | 1067.2 | 3(Loss) |
| simdjson (ondemand) | 3402.35 | 1.82566 | 122.429ms | 4147 | 320 | 144112 | 1162.4 | 4(Loss) |
| glaze | 2823.71 | 0.989596 | 150.556ms | 4147 | 1280 | 245897 | 1400.6 | 5(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1857.44 | 2.19164 | 202.464ms | 2821 | 640 | 644905 | 1448.4 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1495.61 | 0.595815 | 197.914ms | 2821 | 4890 | 561695 | 1798.81 | 2(Tie) |
| glaze STATISTICAL TIE | 1443.61 | 2.63109 | 176.687ms | 2821 | 640 | 1.5387e+06 | 1863.6 | 2(Tie) |
| simdjson (ondemand) | 1166.05 | 0.67573 | 247.519ms | 2821 | 1280 | 311119 | 2307.2 | 4(Loss) |
| simdjson (reflection) | 1117.61 | 0.803348 | 247.316ms | 2821 | 2560 | 957353 | 2407.2 | 5(Loss) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2718.59 | 0.830545 | 123.728ms | 2821 | 320 | 21617 | 989.6 | 1(Win) |
| jsonifier (two-stage) | 1876.88 | 1.01189 | 164.417ms | 2821 | 1280 | 269287 | 1433.4 | 2(Loss) |
| glaze | 1785.92 | 1.89458 | 180.687ms | 2821 | 320 | 260649 | 1506.4 | 3(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1285.76 | 2.48784 | 226.997ms | 2821 | 1280 | 3.46851e+06 | 2092.4 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1258.92 | 0.50906 | 235.41ms | 2821 | 1280 | 151481 | 2137 | 4(Tie) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9997.46 | 3.27002 | 31.134ms | 2821 | 2560 | 198229 | 269.1 | 1(Win) |
| simdjson (reflection) | 7399.11 | 3.71743 | 39.828ms | 2821 | 1280 | 233853 | 363.6 | 2(Loss) |
| glaze | 2987.12 | 0.778198 | 100.023ms | 2819 | 2560 | 125575 | 900 | 3(Loss) |
### Twitter Small Test (Minified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 5.269196713149693%)


----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2226.6 | 0.726542 | 186.956ms | 4147 | 1280 | 213165 | 1776.2 | 1(Win) |
| jsonifier (two-stage) | 2064.14 | 1.06118 | 203.819ms | 4147 | 320 | 132289 | 1916 | 2(Loss) |
| glaze | 1794.15 | 1.01266 | 227.228ms | 4147 | 4890 | 2.4366e+06 | 2204.32 | 3(Loss) |
| simdjson (reflection) | 1645.68 | 1.17024 | 260.871ms | 4147 | 320 | 253094 | 2403.2 | 4(Loss) |
| simdjson (ondemand) | 1581.95 | 0.635717 | 267.544ms | 4147 | 1280 | 323309 | 2500 | 5(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2337.03 | 1.21772 | 188.666ms | 4147 | 4890 | 2.07655e+06 | 1692.27 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 2229.86 | 1.20254 | 203.411ms | 4147 | 1280 | 582260 | 1773.6 | 2(Tie) |
| glaze STATISTICAL TIE | 2206.19 | 0.403964 | 196.758ms | 4147 | 4890 | 256433 | 1792.63 | 2(Tie) |
| simdjson (reflection) | 1785.34 | 0.848575 | 249.915ms | 4147 | 640 | 226145 | 2215.2 | 4(Loss) |
| simdjson (ondemand) | 1629.87 | 0.874351 | 264.967ms | 4147 | 2560 | 1.15232e+06 | 2426.5 | 5(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10853.1 | 2.62366 | 38.0498ms | 4147 | 2560 | 233998 | 364.4 | 1(Win) |
| glaze | 2612.68 | 1.10581 | 159.109ms | 4145 | 1280 | 358305 | 1513 | 2(Loss) |
| simdjson (reflection) | 315.906 | 0.318929 | 1255.52ms | 4147 | 4890 | 7.79561e+06 | 12519.2 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12072.3 | 4.50039 | 39.262ms | 4147 | 1280 | 278227 | 327.6 | 1(Win) |
| glaze | 3554.84 | 2.33671 | 125.119ms | 4145 | 160 | 108029 | 1112 | 2(Loss) |
| simdjson (reflection) | 316.235 | 0.320379 | 1265.04ms | 4147 | 4890 | 7.85025e+06 | 12506.1 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2034.88 | 0.623667 | 6153.41ms | 466906 | 80 | 1.48997e+08 | 218822 | 1(Win) |
| glaze | 1400.01 | 0.288831 | 8225.52ms | 466906 | 1280 | 1.08018e+09 | 318053 | 2(Loss) |
| simdjson (ondemand) | 736.84 | 0.674446 | 7847.96ms | 466906 | 30 | 4.98343e+08 | 604305 | 3(Loss) |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2123.67 | 0.785082 | 5889.75ms | 466906 | 30 | 8.12894e+07 | 209673 | 1(Win) |
| glaze | 1399.69 | 0.345548 | 8288.3ms | 466906 | 640 | 7.73377e+08 | 318124 | 2(Loss) |
| simdjson (ondemand) | 737.553 | 0.448198 | 7656.58ms | 466906 | 640 | 4.68588e+09 | 603721 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2794 | 0.344427 | 6254.59ms | 699405 | 320 | 2.16346e+08 | 238727 | 1(Win) |
| glaze | 1866.27 | 1.5937 | 9221.07ms | 699405 | 320 | 1.03818e+10 | 357399 | 2(Loss) |
| simdjson (ondemand) | 575.939 | 0.928415 | 8436.59ms | 767297 | 30 | 4.17426e+09 | 1.27054e+06 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2708.78 | 0.633013 | 6543.37ms | 699405 | 160 | 3.88737e+08 | 246238 | 1(Win) |
| glaze | 1942.65 | 0.237144 | 9295.88ms | 699405 | 640 | 4.24299e+08 | 343348 | 2(Loss) |
| simdjson (ondemand) | 569.988 | 0.340577 | 8064.41ms | 767297 | 320 | 6.11754e+09 | 1.2838e+06 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1832.67 | 0.45465 | 8666.13ms | 631514 | 1280 | 2.85735e+09 | 328624 | 1(Win) |
| glaze | 1634.73 | 0.289404 | 9715.82ms | 631514 | 640 | 7.27548e+08 | 368415 | 2(Loss) |
