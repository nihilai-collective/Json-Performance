# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 10, 2026)
#### Using the following commits:
----
| Jsonifier: [13785b6](https://github.com/nihilai-collective/jsonifier/commit/13785b6)  
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
| jsonifier | 1617.08 | 1.36132 | 55.8579ms | 905 | 4890 | 258146 | 533.726 | 1(Win) |
| glaze | 1509.85 | 1.27152 | 71.287ms | 905 | 4890 | 258333 | 571.629 | 2(Loss) |
| jsonifier (two-stage) | 248.41 | 0.425882 | 359.774ms | 905 | 1280 | 280252 | 3474.4 | 3(Loss) |
| simdjson (ondemand) | 178.846 | 0.261708 | 480.942ms | 905 | 1280 | 204166 | 4825.8 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1724.85 | 1.43651 | 52.578ms | 905 | 4890 | 252652 | 500.378 | 1(Win) |
| glaze | 1627.77 | 1.36296 | 55.5159ms | 905 | 4890 | 255378 | 530.218 | 2(Loss) |
| jsonifier (two-stage) | 246.805 | 0.217734 | 352.223ms | 905 | 4890 | 283499 | 3496.99 | 3(Loss) |
| simdjson (ondemand) | 196.047 | 0.357342 | 454.395ms | 905 | 2560 | 633560 | 4402.4 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1612.32 | 1.85326 | 56.906ms | 905 | 2560 | 251946 | 535.3 | 1(Win) |
| simdjson (reflection) | 213.908 | 0.206899 | 406.606ms | 905 | 1280 | 89201 | 4034.8 | 2(Loss) |
| glaze | 113.259 | 0.291743 | 760.467ms | 905 | 640 | 316328 | 7620.4 | 3(Loss) |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 2764.27 | 2.14447 | 41.314ms | 905 | 4890 | 219223 | 312.226 | 1(Win) |
| jsonifier | 2372.78 | 1.95378 | 46.528ms | 905 | 4890 | 246968 | 363.74 | 2(Loss) |
| glaze | 795.392 | 0.501685 | 123.356ms | 905 | 4890 | 144912 | 1085.09 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 840.969 | 0.20146 | 209.247ms | 1811 | 4890 | 83707.1 | 2053.71 | 1(Win) |
| glaze | 535.967 | 0.305187 | 326.228ms | 1811 | 4890 | 472935 | 3222.41 | 2(Loss) |
| jsonifier (two-stage) | 309.226 | 0.152623 | 563.976ms | 1811 | 4890 | 355333 | 5585.25 | 3(Loss) |
| simdjson (ondemand) | 142.972 | 0.184284 | 1229.99ms | 1811 | 160 | 79292.4 | 12080 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 983.995 | 0.379717 | 179.273ms | 1811 | 4890 | 217210 | 1755.2 | 1(Win) |
| glaze | 560.366 | 0.395845 | 308.923ms | 1811 | 2560 | 381052 | 3082.1 | 2(Loss) |
| jsonifier (two-stage) | 341.757 | 0.124794 | 511.303ms | 1811 | 2560 | 101820 | 5053.6 | 3(Loss) |
| simdjson (ondemand) | 140.58 | 0.17817 | 1235.46ms | 1811 | 640 | 306649 | 12285.6 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 291.505 | 0.231503 | 661.397ms | 1997 | 2560 | 585621 | 6533.3 | 1(Win) |
| jsonifier | 252.383 | 0.7496 | 692.363ms | 1811 | 160 | 421015 | 6843.2 | 2(Loss) |
| glaze | 200.438 | 0.142822 | 861.186ms | 1798 | 2560 | 382164 | 8554.8 | 3(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 814.019 | 0.336749 | 223.509ms | 1811 | 2560 | 130683 | 2121.7 | 1(Win) |
| simdjson (reflection) | 675.707 | 0.232488 | 295.431ms | 1997 | 4890 | 209966 | 2818.51 | 2(Loss) |
| glaze | 463.21 | 0.209397 | 387.084ms | 1798 | 4890 | 293816 | 3701.79 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2187.18 | 0.419324 | 170.839ms | 3862 | 4890 | 243817 | 1683.95 | 1(Win) |
| glaze | 1311.57 | 0.246543 | 283.552ms | 3862 | 4890 | 234388 | 2808.15 | 2(Loss) |
| jsonifier (two-stage) | 676.97 | 0.175992 | 547.354ms | 3862 | 4890 | 448311 | 5440.55 | 3(Loss) |
| simdjson (ondemand) | 470.31 | 0.166509 | 788.453ms | 3862 | 1280 | 217641 | 7831.2 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2702.24 | 0.522812 | 141.87ms | 3862 | 4890 | 248300 | 1362.98 | 1(Win) |
| glaze | 1488.24 | 0.664525 | 252.408ms | 3862 | 1280 | 346189 | 2474.8 | 2(Loss) |
| jsonifier (two-stage) | 711.901 | 0.348273 | 560.909ms | 3862 | 640 | 207781 | 5173.6 | 3(Loss) |
| simdjson (ondemand) | 487.749 | 0.220826 | 764.287ms | 3862 | 1280 | 355913 | 7551.2 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 748.565 | 0.195331 | 523.466ms | 3862 | 1280 | 118227 | 4920.2 | 1(Win) |
| jsonifier | 686.849 | 0.20882 | 539.561ms | 3862 | 2560 | 320987 | 5362.3 | 2(Loss) |
| glaze | 501.424 | 0.120355 | 742.421ms | 3862 | 4890 | 382163 | 7345.26 | 3(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3681.62 | 0.292853 | 113.063ms | 3862 | 640 | 5493.22 | 1000.4 | 1(Win) |
| simdjson (reflection) | 3013 | 0.708148 | 135.699ms | 3862 | 2560 | 191829 | 1222.4 | 2(Loss) |
| glaze | 2090.1 | 0.442493 | 195.612ms | 3862 | 4890 | 297312 | 1762.16 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1138.83 | 0.178358 | 786.901ms | 9578 | 160 | 32744.8 | 8020.8 | 1(Win) |
| glaze | 1060.14 | 0.13061 | 874.443ms | 9578 | 2560 | 324202 | 8616.1 | 2(Loss) |
| simdjson (ondemand) | 759.167 | 0.249881 | 1173.33ms | 9578 | 30 | 27118.3 | 12032 | 3(Loss) |
| jsonifier (two-stage) | 719.009 | 0.150798 | 1281.81ms | 9578 | 1280 | 469769 | 12704 | 4(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1982.25 | 0.16754 | 734.784ms | 9578 | 4890 | 291460 | 4608.05 | 1(Win) |
| glaze | 1578.36 | 0.35222 | 828.643ms | 9578 | 640 | 265916 | 5787.2 | 2(Loss) |
| simdjson (ondemand) | 1065.54 | 0.119888 | 1129.78ms | 9578 | 4890 | 516508 | 8572.49 | 3(Loss) |
| jsonifier (two-stage) | 954.921 | 0.0908898 | 1235.19ms | 9578 | 4890 | 369619 | 9565.5 | 4(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 1216.23 | 0.131913 | 759.626ms | 9578 | 4890 | 479957 | 7510.33 | 1(Win) |
| jsonifier | 1179.56 | 0.21137 | 758.54ms | 9578 | 2560 | 685861 | 7743.8 | 2(Loss) |
| glaze | 1011.08 | 0.14362 | 898.724ms | 9578 | 4890 | 823220 | 9034.18 | 3(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 10050.1 | 0.483554 | 102.842ms | 9578 | 4890 | 94451.8 | 908.879 | 1(Win) |
| jsonifier | 8485.96 | 1.20749 | 117.917ms | 9578 | 640 | 108118 | 1076.4 | 2(Loss) |
| glaze | 4727.67 | 0.22704 | 212.237ms | 9578 | 4890 | 94096.1 | 1932.09 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2230.08 | 0.426232 | 168.378ms | 3873 | 4890 | 243699 | 1656.25 | 1(Win) |
| glaze | 1491.58 | 0.305287 | 251.703ms | 3873 | 4890 | 279465 | 2476.29 | 2(Loss) |
| jsonifier (two-stage) | 672.881 | 0.364189 | 553.627ms | 3873 | 640 | 255771 | 5489.2 | 3(Loss) |
| simdjson (ondemand) | 441.985 | 0.405585 | 834.013ms | 3873 | 320 | 367615 | 8356.8 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2726.9 | 0.72622 | 140.053ms | 3873 | 2560 | 247705 | 1354.5 | 1(Win) |
| glaze | 1659.37 | 0.360036 | 223.599ms | 3873 | 4890 | 314058 | 2225.89 | 2(Loss) |
| jsonifier (two-stage) | 697.152 | 0.188065 | 530.234ms | 3873 | 2560 | 254152 | 5298.1 | 3(Loss) |
| simdjson (ondemand) | 452.091 | 0.253574 | 812.718ms | 3873 | 640 | 274684 | 8170 | 4(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (reflection) | 765.604 | 0.186574 | 492.839ms | 3873 | 2560 | 207409 | 4824.4 | 1(Win) |
| jsonifier | 702.455 | 0.257634 | 529.613ms | 3873 | 2560 | 469790 | 5258.1 | 2(Loss) |
| glaze | 510.156 | 0.138835 | 733.434ms | 3873 | 2560 | 258659 | 7240.1 | 3(Loss) |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3558.8 | 0.287352 | 117.057ms | 3873 | 4890 | 43493.7 | 1037.87 | 1(Win) |
| simdjson (reflection) | 3053.06 | 0.51809 | 133.379ms | 3873 | 4890 | 192107 | 1209.8 | 2(Loss) |
| glaze | 2362.83 | 0.898282 | 176.45ms | 3873 | 1280 | 252385 | 1563.2 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 653.71 | 0.091767 | 9639.03ms | 2090234 | 160 | 1.25289e+09 | 3.04937e+06 | 1(Win) |
| jsonifier (two-stage) | 607.98 | 0.0971974 | 10516.7ms | 2090234 | 40 | 4.06239e+08 | 3.27873e+06 | 2(Loss) |
| simdjson (reflection) | 536.028 | 0.226911 | 5600.75ms | 2090234 | 80 | 5.69659e+09 | 3.71884e+06 | 3(Loss) |
| glaze | 514.805 | 0.136253 | 5818.22ms | 2090234 | 40 | 1.11341e+09 | 3.87215e+06 | 4(Loss) |
| simdjson (ondemand) | 457.418 | 0.196659 | 6463.03ms | 2090234 | 40 | 2.93799e+09 | 4.35795e+06 | 5(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 800.683 | 0.120566 | 9508.82ms | 2090234 | 80 | 7.20785e+08 | 2.48963e+06 | 1(Win) |
| jsonifier (two-stage) | 730.346 | 0.36645 | 10301.5ms | 2090234 | 30 | 3.00112e+09 | 2.7294e+06 | 2(Loss) |
| simdjson (reflection) | 636.448 | 0.147107 | 5591.69ms | 2090234 | 40 | 8.4916e+08 | 3.13208e+06 | 3(Loss) |
| glaze | 601.306 | 0.174443 | 5845.81ms | 2090234 | 40 | 1.33772e+09 | 3.31512e+06 | 4(Loss) |
| simdjson (ondemand) | 552.832 | 0.102167 | 6255.25ms | 2090234 | 80 | 1.08572e+09 | 3.6058e+06 | 5(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2288.14 | 0.101141 | 5551.18ms | 2090234 | 80 | 6.21112e+07 | 871187 | 1(Win) |
| glaze | 1529.47 | 0.140249 | 8255.24ms | 2090234 | 160 | 5.34597e+08 | 1.30333e+06 | 2(Loss) |
| simdjson (reflection) | 769.768 | 0.0622204 | 8055.65ms | 2090326 | 40 | 1.03857e+08 | 2.58973e+06 | 3(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2286.35 | 0.185764 | 5508.24ms | 2090234 | 40 | 1.04927e+08 | 871872 | 1(Win) |
| glaze | 1615.72 | 0.101868 | 7826.25ms | 2090234 | 40 | 6.31819e+07 | 1.23375e+06 | 2(Loss) |
| simdjson (reflection) | 768.776 | 0.0838269 | 8101.75ms | 2090326 | 160 | 7.55987e+08 | 2.59307e+06 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1824.03 | 0.127978 | 5252.41ms | 6661897 | 40 | 7.94815e+08 | 3.4831e+06 | 1(Win) |
| jsonifier (two-stage) | 1649.35 | 0.195801 | 5917.04ms | 6661897 | 40 | 2.27543e+09 | 3.85199e+06 | 2(Loss) |
| simdjson (reflection) | 1513.62 | 0.121379 | 6304.45ms | 6661897 | 80 | 2.07651e+09 | 4.1974e+06 | 3(Loss) |
| simdjson (ondemand) | 1357.81 | 0.363129 | 7013.03ms | 6661897 | 40 | 1.15479e+10 | 4.67908e+06 | 4(Loss) |
| glaze | 1305.08 | 0.104299 | 7351.42ms | 6661897 | 80 | 2.06239e+09 | 4.86813e+06 | 5(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2175.34 | 0.131184 | 5265.52ms | 6661897 | 80 | 1.17433e+09 | 2.92059e+06 | 1(Win) |
| jsonifier (two-stage) | 1907.08 | 0.343037 | 5789.1ms | 6661897 | 80 | 1.0448e+10 | 3.33142e+06 | 2(Loss) |
| simdjson (reflection) | 1754.04 | 0.103017 | 6313.92ms | 6661897 | 40 | 5.56915e+08 | 3.62207e+06 | 3(Loss) |
| simdjson (ondemand) | 1552.54 | 0.169911 | 7004.13ms | 6661897 | 80 | 3.86762e+09 | 4.09218e+06 | 4(Loss) |
| glaze | 1469.26 | 0.106698 | 7373.8ms | 6661897 | 80 | 1.70295e+09 | 4.32414e+06 | 5(Loss) |
### Canada Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.10015679514090324%)

### Canada Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.07104977245952246%)


----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1942.83 | 0.124934 | 6281.78ms | 500299 | 160 | 1.50616e+07 | 245581 | 1(Win) |
| jsonifier (two-stage) | 1258.81 | 0.131749 | 9845.79ms | 500299 | 40 | 9.97454e+06 | 379027 | 2(Loss) |
| glaze | 1213.48 | 0.0898677 | 5046.02ms | 500299 | 320 | 3.99529e+07 | 393184 | 3(Loss) |
| simdjson (ondemand) | 1067.02 | 0.0782438 | 5728.83ms | 500299 | 640 | 7.83417e+07 | 447153 | 4(Loss) |
| simdjson (reflection) | 1044.97 | 0.0764558 | 5846.64ms | 500299 | 640 | 7.79922e+07 | 456589 | 5(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2438.69 | 0.0805884 | 6172.86ms | 500299 | 640 | 1.59101e+07 | 195647 | 1(Win) |
| jsonifier (two-stage) | 1451.07 | 0.142373 | 9607.61ms | 500299 | 30 | 6.57439e+06 | 328806 | 2(Loss) |
| glaze | 1392.32 | 0.0868907 | 9912.2ms | 500299 | 160 | 1.41856e+07 | 342682 | 3(Loss) |
| simdjson (ondemand) | 1191.72 | 0.17381 | 5688.75ms | 500299 | 40 | 1.93697e+07 | 400365 | 4(Loss) |
| simdjson (reflection) | 1152.53 | 0.309399 | 5811.32ms | 500299 | 30 | 4.92169e+07 | 413978 | 5(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8421.36 | 0.0591611 | 5679.57ms | 500299 | 2560 | 2.87613e+06 | 56656.2 | 1(Win) |
| simdjson (reflection) | 7225.1 | 0.193079 | 6671.01ms | 500299 | 160 | 2.60112e+06 | 66036.8 | 2(Loss) |
| glaze | 1949.33 | 0.126912 | 6269.81ms | 500299 | 80 | 7.71931e+06 | 244762 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8473.86 | 0.116714 | 5654.43ms | 500299 | 640 | 2.76388e+06 | 56305.2 | 1(Win) |
| simdjson (reflection) | 7223.57 | 0.106093 | 6672.36ms | 500299 | 640 | 3.14275e+06 | 66050.8 | 2(Loss) |
| glaze | 2063.51 | 0.0786937 | 5951.25ms | 500299 | 320 | 1.05944e+07 | 231218 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3275.52 | 0.271224 | 5319.79ms | 1439562 | 160 | 2.06764e+08 | 419131 | 1(Win) |
| jsonifier (two-stage) | 2825.42 | 0.148143 | 6192.53ms | 1439562 | 40 | 2.0726e+07 | 485901 | 2(Loss) |
| simdjson (ondemand) | 2436.33 | 0.151471 | 7233.71ms | 1439562 | 40 | 2.91413e+07 | 563501 | 3(Loss) |
| simdjson (reflection) | 2392.09 | 0.0583068 | 7316.9ms | 1439562 | 320 | 3.58339e+07 | 573922 | 4(Loss) |
| glaze | 1891.46 | 0.114118 | 9278.59ms | 1439562 | 30 | 2.05825e+07 | 725828 | 5(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3745.22 | 0.0909261 | 5280.81ms | 1439562 | 80 | 8.88735e+06 | 366566 | 1(Win) |
| jsonifier (two-stage) | 3173.29 | 0.225874 | 6152.15ms | 1439562 | 40 | 3.81974e+07 | 432634 | 2(Loss) |
| simdjson (ondemand) | 2655.63 | 0.108822 | 7142.57ms | 1439562 | 40 | 1.26595e+07 | 516966 | 3(Loss) |
| simdjson (reflection) | 2576.7 | 0.0765057 | 7342.85ms | 1439562 | 640 | 1.06341e+08 | 532802 | 4(Loss) |
| glaze | 2032.44 | 0.126317 | 9234.34ms | 1439562 | 160 | 1.16485e+08 | 675480 | 5(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 19179.4 | 0.0867533 | 7225.53ms | 1439562 | 640 | 2.468e+06 | 71580.8 | 1(Win) |
| glaze | 3834.47 | 0.0594778 | 9303.11ms | 1439584 | 320 | 1.45118e+07 | 358040 | 2(Loss) |
| simdjson (reflection) | 323.192 | 0.13672 | 6385.98ms | 1439562 | 80 | 2.69833e+09 | 4.24786e+06 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 19256.2 | 0.0558341 | 7183.79ms | 1439562 | 1280 | 2.02828e+06 | 71295.2 | 1(Win) |
| glaze | 4426.46 | 0.0659547 | 7954.52ms | 1439584 | 1280 | 5.35629e+07 | 310157 | 2(Loss) |
| simdjson (reflection) | 323.554 | 0.202286 | 6458.85ms | 1439562 | 30 | 2.21014e+09 | 4.2431e+06 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1683.31 | 0.140473 | 3205.67ms | 56369 | 640 | 1.288e+06 | 31935.6 | 1(Win) |
| glaze | 1311.13 | 0.0570901 | 4131.04ms | 56369 | 4890 | 2.67929e+06 | 41001 | 2(Loss) |
| jsonifier (two-stage) | 1135.68 | 0.082931 | 4750.17ms | 56369 | 1280 | 1.97249e+06 | 47335.4 | 3(Loss) |
| simdjson (reflection) | 1010.41 | 0.137642 | 5454.03ms | 56369 | 640 | 3.43219e+06 | 53204 | 4(Loss) |
| simdjson (ondemand) | 945.905 | 0.0798221 | 5712.89ms | 56369 | 640 | 1.31708e+06 | 56832 | 5(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2291.19 | 0.0900342 | 2902.88ms | 56369 | 2560 | 1.14239e+06 | 23462.8 | 1(Win) |
| glaze | 1758.68 | 0.0585508 | 3613.14ms | 56369 | 4890 | 1.56632e+06 | 30567.1 | 2(Loss) |
| jsonifier (two-stage) | 1442.31 | 0.0911989 | 4513.2ms | 56369 | 1280 | 1.47894e+06 | 37271.8 | 3(Loss) |
| simdjson (ondemand) | 1144.36 | 0.142516 | 5273.55ms | 56369 | 30 | 134462 | 46976 | 4(Loss) |
| simdjson (reflection) | 1139.42 | 0.0744284 | 5284.94ms | 56369 | 1280 | 1.57834e+06 | 47179.8 | 5(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11454 | 1.90991 | 478.124ms | 56369 | 30 | 241052 | 4693.33 | 1(Win) |
| simdjson (reflection) | 8830.54 | 0.127891 | 612.049ms | 56369 | 2560 | 155176 | 6087.7 | 2(Loss) |
| glaze | 2767.25 | 0.0852612 | 1954.51ms | 56369 | 4890 | 1.34152e+06 | 19426.4 | 3(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11955.3 | 0.173576 | 454.167ms | 56369 | 4890 | 297882 | 4496.54 | 1(Win) |
| simdjson (reflection) | 9041.44 | 0.627755 | 595.564ms | 56369 | 2560 | 3.56637e+06 | 5945.7 | 2(Loss) |
| glaze | 3104.22 | 0.162286 | 1777.91ms | 56369 | 1280 | 1.01099e+06 | 17317.6 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1981.26 | 0.143938 | 4597.34ms | 94370 | 320 | 1.36801e+06 | 45424.8 | 1(Win) |
| glaze | 1817.07 | 0.0553943 | 5010.72ms | 94370 | 2560 | 1.92706e+06 | 49529.3 | 2(Loss) |
| jsonifier (two-stage) | 1738.77 | 0.0569254 | 5223.43ms | 94370 | 4890 | 4.24525e+06 | 51759.6 | 3(Loss) |
| simdjson (reflection) | 1547.62 | 0.0736367 | 5823.92ms | 94370 | 2560 | 4.69427e+06 | 58152.7 | 4(Loss) |
| simdjson (ondemand) | 1449.05 | 0.0540033 | 6255.32ms | 94370 | 4890 | 5.50109e+06 | 62108.3 | 5(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2437.39 | 0.0454046 | 4219.6ms | 94370 | 4890 | 1.37445e+06 | 36924 | 1(Win) |
| glaze | 2275.94 | 0.0633119 | 4467.95ms | 94370 | 4890 | 3.06496e+06 | 39543.3 | 2(Loss) |
| jsonifier (two-stage) | 2153.42 | 0.188007 | 4883.87ms | 94370 | 1280 | 7.90259e+06 | 41793.2 | 3(Loss) |
| simdjson (ondemand) | 1736.36 | 0.12471 | 5783.28ms | 94370 | 30 | 125347 | 51831.5 | 4(Loss) |
| simdjson (reflection) | 1726.78 | 0.0517275 | 5803.35ms | 94370 | 2560 | 1.8607e+06 | 52119.1 | 5(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13110.9 | 0.237235 | 695.56ms | 94370 | 640 | 169724 | 6864.4 | 1(Win) |
| glaze | 2496.8 | 0.0482109 | 3618.84ms | 94370 | 4890 | 1.47673e+06 | 36045.5 | 2(Loss) |
| simdjson (reflection) | 345.963 | 0.242345 | 6702.24ms | 94370 | 30 | 1.19234e+07 | 260139 | 3(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13442.3 | 0.117847 | 670.636ms | 94370 | 4890 | 304417 | 6695.16 | 1(Win) |
| glaze | 2793.74 | 0.0854012 | 3266.56ms | 94370 | 4890 | 3.70111e+06 | 32214.2 | 2(Loss) |
| simdjson (reflection) | 346.098 | 0.128373 | 6660.02ms | 94370 | 160 | 1.78293e+07 | 260037 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1905.41 | 0.343719 | 601.773ms | 11812 | 320 | 132138 | 5912 | 1(Win) |
| jsonifier (two-stage) | 1140.03 | 0.0945389 | 992.738ms | 11812 | 4890 | 426720 | 9881.13 | 2(Loss) |
| glaze | 946.666 | 0.103905 | 1205.11ms | 11812 | 4890 | 747544 | 11899.4 | 3(Loss) |
| simdjson (reflection) | 938.733 | 0.112976 | 1293.16ms | 11812 | 40 | 7351.79 | 12000 | 4(Loss) |
| simdjson (ondemand) | 727.032 | 0.0754415 | 1555.65ms | 11812 | 4890 | 668143 | 15494.2 | 5(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2227.3 | 0.413156 | 588.154ms | 11812 | 160 | 69861.3 | 5057.6 | 1(Win) |
| jsonifier (two-stage) | 1285.94 | 0.30958 | 989.999ms | 11812 | 640 | 470687 | 8760 | 2(Loss) |
| glaze | 1040.5 | 0.0888808 | 1165.48ms | 11812 | 4890 | 452777 | 10826.3 | 3(Loss) |
| simdjson (reflection) | 1008.72 | 0.249369 | 1201.15ms | 11812 | 1280 | 992660 | 11167.4 | 4(Loss) |
| simdjson (ondemand) | 784.916 | 0.0938092 | 1527.93ms | 11812 | 2560 | 464015 | 14351.6 | 5(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10165.1 | 0.429685 | 113.587ms | 11812 | 4890 | 110874 | 1108.18 | 1(Win) |
| simdjson (reflection) | 8126.39 | 0.716376 | 142.713ms | 11812 | 2560 | 252449 | 1386.2 | 2(Loss) |
| glaze | 1757.35 | 0.152382 | 645.452ms | 11812 | 4890 | 466559 | 6410.1 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10697.8 | 0.330237 | 108.195ms | 11812 | 4890 | 59131.7 | 1053 | 1(Win) |
| simdjson (reflection) | 8398.72 | 0.519429 | 136.029ms | 11812 | 4890 | 237346 | 1341.25 | 2(Loss) |
| glaze | 1904.48 | 0.107197 | 596.703ms | 11812 | 4890 | 196594 | 5914.91 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2925 | 0.096468 | 1022.39ms | 31235 | 4890 | 471961 | 10183.9 | 1(Win) |
| jsonifier (two-stage) | 2111.65 | 0.0705605 | 1417.51ms | 31235 | 2560 | 253630 | 14106.5 | 2(Loss) |
| simdjson (reflection) | 2055.69 | 0.115991 | 1458.87ms | 31235 | 2560 | 723190 | 14490.5 | 3(Loss) |
| glaze | 1722.85 | 0.142668 | 1729.88ms | 31235 | 640 | 389424 | 17290 | 4(Loss) |
| simdjson (ondemand) | 1648.66 | 0.125236 | 1833.35ms | 31235 | 1280 | 655370 | 18068 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3202.87 | 0.280716 | 1013.91ms | 31235 | 640 | 436233 | 9300.4 | 1(Win) |
| jsonifier (two-stage) | 2563.87 | 0.215708 | 1412.84ms | 31235 | 640 | 401979 | 11618.4 | 2(Loss) |
| simdjson (reflection) | 2169.4 | 0.11159 | 1457.38ms | 31235 | 4890 | 1.14805e+06 | 13731 | 3(Loss) |
| glaze | 1794.37 | 0.157023 | 1739.55ms | 31235 | 1280 | 869748 | 16600.8 | 4(Loss) |
| simdjson (ondemand) | 1761.69 | 0.226229 | 1779.95ms | 31235 | 320 | 468243 | 16908.8 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15719 | 0.321087 | 192.884ms | 31235 | 4890 | 181045 | 1895.03 | 1(Win) |
| glaze | 2805.11 | 0.370207 | 1075.21ms | 31235 | 160 | 247282 | 10619.2 | 2(Loss) |
| simdjson (reflection) | 305.801 | 0.0819542 | 9792.26ms | 31235 | 1280 | 8.15751e+06 | 97409.8 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17430.4 | 0.412852 | 174.317ms | 31235 | 4890 | 243426 | 1708.97 | 1(Win) |
| glaze | 3076.64 | 0.243849 | 1018.11ms | 31235 | 640 | 356739 | 9682 | 2(Loss) |
| simdjson (reflection) | 305.885 | 0.069776 | 9812.18ms | 31235 | 2560 | 1.182e+07 | 97383.1 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2521.22 | 0.0677393 | 4129ms | 108313 | 2560 | 1.97179e+06 | 40970.3 | 1(Win) |
| jsonifier (two-stage) | 1496.88 | 0.180339 | 6970.66ms | 108313 | 320 | 4.95585e+06 | 69007.2 | 2(Loss) |
| glaze | 1345.96 | 0.0727797 | 7697.94ms | 108313 | 1280 | 3.99326e+06 | 76744.8 | 3(Loss) |
| simdjson (reflection) | 1198.72 | 0.0479773 | 8668.25ms | 108313 | 2560 | 4.37559e+06 | 86171.3 | 4(Loss) |
| simdjson (ondemand) | 1161.06 | 0.0469238 | 8939.55ms | 108313 | 4890 | 8.52216e+06 | 88966.6 | 5(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3004.94 | 0.112319 | 3686.59ms | 108313 | 640 | 954066 | 34375.2 | 1(Win) |
| jsonifier (two-stage) | 1645.89 | 0.0765607 | 6550.98ms | 108313 | 4890 | 1.12897e+07 | 62759.5 | 2(Loss) |
| glaze | 1464.76 | 0.111097 | 7383.24ms | 108313 | 640 | 3.92841e+06 | 70520.4 | 3(Loss) |
| simdjson (ondemand) | 1256.01 | 0.0649238 | 8537.91ms | 108313 | 4890 | 1.3941e+07 | 82241 | 4(Loss) |
| simdjson (reflection) | 1238.23 | 0.0489374 | 8639.77ms | 108313 | 4890 | 8.14979e+06 | 83421.5 | 5(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13781.5 | 0.145559 | 756.504ms | 108313 | 2560 | 304707 | 7495.2 | 1(Win) |
| simdjson (reflection) | 7687.38 | 0.185152 | 1349.95ms | 108313 | 1280 | 792264 | 13437 | 2(Loss) |
| glaze | 1865.67 | 0.115881 | 5682.67ms | 108313 | 320 | 1.31725e+06 | 55366.4 | 3(Loss) |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14168.6 | 0.123899 | 734.637ms | 108313 | 4890 | 398983 | 7290.45 | 1(Win) |
| simdjson (reflection) | 7821.02 | 0.0803544 | 1325.81ms | 108313 | 2560 | 288333 | 13207.4 | 2(Loss) |
| glaze | 1999.92 | 0.164244 | 5231.19ms | 108313 | 160 | 1.15141e+06 | 51649.6 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2479.29 | 0.0465241 | 8244.83ms | 213963 | 4890 | 7.1695e+06 | 82302.3 | 1(Win) |
| glaze | 2100.69 | 0.134171 | 5015.49ms | 213963 | 640 | 1.08705e+07 | 97135.2 | 2(Loss) |
| simdjson (reflection) | 2017.51 | 0.0642805 | 5200.03ms | 213963 | 2560 | 1.08204e+07 | 101140 | 3(Loss) |
| simdjson (ondemand) | 1981.6 | 0.179767 | 5456.07ms | 213963 | 80 | 2.7413e+06 | 102973 | 4(Loss) |
| jsonifier | 1385.2 | 0.0428706 | 7581.84ms | 213963 | 2560 | 1.02097e+07 | 147308 | 5(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3311.74 | 0.121293 | 6431.54ms | 213963 | 320 | 1.78724e+06 | 61614.4 | 1(Win) |
| jsonifier (two-stage) | 2699.81 | 0.0639783 | 7850.14ms | 213963 | 2560 | 5.98575e+06 | 75579.9 | 2(Loss) |
| glaze | 2263.79 | 0.0917765 | 9344.51ms | 213963 | 640 | 4.37973e+06 | 90136.8 | 3(Loss) |
| simdjson (ondemand) | 2121.33 | 0.0661152 | 5070.71ms | 213963 | 640 | 2.58846e+06 | 96190 | 4(Loss) |
| simdjson (reflection) | 2078.42 | 0.273005 | 5184.37ms | 213963 | 40 | 2.8735e+06 | 98176 | 5(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16997.7 | 0.0912016 | 1268.33ms | 213963 | 1280 | 153430 | 12004.6 | 1(Win) |
| glaze | 2212.17 | 0.0626632 | 9229.61ms | 213963 | 2560 | 8.55272e+06 | 92240 | 2(Loss) |
| simdjson (reflection) | 336.745 | 0.189596 | 7785.63ms | 213963 | 40 | 5.27951e+07 | 605952 | 3(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17179.2 | 0.079095 | 1195.76ms | 213963 | 4890 | 431599 | 11877.8 | 1(Win) |
| glaze | 2444.53 | 0.0464652 | 8357.13ms | 213963 | 4890 | 7.35612e+06 | 83472.3 | 2(Loss) |
| simdjson (reflection) | 334.859 | 0.0807738 | 7747.78ms | 213963 | 640 | 1.55051e+08 | 609364 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 620.614 | 0.217494 | 8796.72ms | 1834197 | 80 | 3.00632e+09 | 2.81854e+06 | 1(Win) |
| jsonifier (two-stage) | 512.359 | 0.518835 | 5098.92ms | 1834197 | 30 | 9.41291e+09 | 3.41407e+06 | 2(Loss) |
| glaze | 491.923 | 0.150795 | 5368.94ms | 1834197 | 80 | 2.30018e+09 | 3.5559e+06 | 3(Loss) |
| simdjson (reflection) | 474.74 | 0.0796649 | 5582.43ms | 1834197 | 30 | 2.58485e+08 | 3.6846e+06 | 4(Loss) |
| simdjson (ondemand) | 443.201 | 0.149629 | 5928.75ms | 1834197 | 80 | 2.79005e+09 | 3.9468e+06 | 5(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 713.154 | 0.217862 | 8750.06ms | 1834197 | 30 | 8.56664e+08 | 2.4528e+06 | 1(Win) |
| jsonifier (two-stage) | 576.327 | 0.27398 | 5137.55ms | 1834197 | 40 | 2.766e+09 | 3.03513e+06 | 2(Loss) |
| glaze | 546.021 | 0.266808 | 5460.69ms | 1834197 | 80 | 5.84468e+09 | 3.20359e+06 | 3(Loss) |
| simdjson (reflection) | 525.087 | 0.0997578 | 5548.19ms | 1834197 | 30 | 3.31318e+08 | 3.33131e+06 | 4(Loss) |
| simdjson (ondemand) | 489.021 | 0.178565 | 5946.37ms | 1834197 | 80 | 3.26377e+09 | 3.577e+06 | 5(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1296.73 | 0.189665 | 8509.39ms | 1834197 | 160 | 1.04734e+09 | 1.34896e+06 | 1(Win) |
| glaze | 817.701 | 0.100906 | 6704.04ms | 1833577 | 40 | 1.86253e+08 | 2.13848e+06 | 2(Loss) |
| simdjson (reflection) | 729.05 | 0.165482 | 7822.15ms | 1922245 | 160 | 2.77028e+09 | 2.5145e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1301.34 | 0.0886802 | 8479.08ms | 1834197 | 320 | 4.5469e+08 | 1.34418e+06 | 1(Win) |
| glaze | 815.448 | 0.124388 | 6782.22ms | 1833577 | 160 | 1.13837e+09 | 2.14439e+06 | 2(Loss) |
| simdjson (reflection) | 733.016 | 0.0672792 | 7836.85ms | 1922245 | 40 | 1.13243e+08 | 2.5009e+06 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2428.58 | 0.225993 | 5864.41ms | 9930848 | 80 | 6.21367e+09 | 3.89973e+06 | 1(Win) |
| jsonifier (two-stage) | 2248.27 | 0.134582 | 6474.82ms | 9930848 | 80 | 2.57123e+09 | 4.21247e+06 | 2(Loss) |
| simdjson (reflection) | 2028.04 | 0.135148 | 7064.29ms | 9930848 | 40 | 1.5933e+09 | 4.66993e+06 | 3(Loss) |
| simdjson (ondemand) | 1923.32 | 0.181673 | 7431.85ms | 9930848 | 80 | 6.40237e+09 | 4.9242e+06 | 4(Loss) |
| glaze | 1894.02 | 0.26123 | 7500.96ms | 9930848 | 80 | 1.36503e+10 | 5.00038e+06 | 5(Loss) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2683.35 | 0.212268 | 5880ms | 9930848 | 80 | 4.49035e+09 | 3.52947e+06 | 1(Win) |
| jsonifier (two-stage) | 2460.11 | 0.191544 | 6335.06ms | 9930848 | 40 | 2.175e+09 | 3.84974e+06 | 2(Loss) |
| simdjson (reflection) | 2195.09 | 0.15605 | 7027.09ms | 9930848 | 80 | 3.62648e+09 | 4.31454e+06 | 3(Loss) |
| simdjson (ondemand) | 2081.69 | 0.226821 | 7437.98ms | 9930848 | 30 | 3.19468e+09 | 4.54957e+06 | 4(Loss) |
| glaze | 2054.9 | 0.180994 | 7496.06ms | 9930848 | 80 | 5.56687e+09 | 4.60888e+06 | 5(Loss) |
### Marine IK Reverse Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.08006832624046056%)

### Marine IK Reverse Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.7751230417494483%)


----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 658.187 | 0.18434 | 8276.71ms | 1834197 | 160 | 3.84019e+09 | 2.65764e+06 | 1(Win) |
| jsonifier (two-stage) | 551.155 | 0.133466 | 9918.17ms | 1834197 | 80 | 1.4354e+09 | 3.17375e+06 | 2(Loss) |
| glaze | 486.029 | 0.240381 | 5389.33ms | 1834197 | 80 | 5.98765e+09 | 3.59901e+06 | 3(Loss) |
| simdjson (reflection) | 469.063 | 0.307057 | 5551.01ms | 1834197 | 80 | 1.04896e+10 | 3.7292e+06 | 4(Loss) |
| simdjson (ondemand) | 443.041 | 0.123127 | 5938.86ms | 1834197 | 30 | 7.08981e+08 | 3.94823e+06 | 5(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 760.856 | 0.147842 | 8241.41ms | 1834197 | 160 | 1.84843e+09 | 2.29902e+06 | 1(Win) |
| jsonifier (two-stage) | 620.793 | 0.154787 | 10013.5ms | 1834197 | 80 | 1.52179e+09 | 2.81773e+06 | 2(Loss) |
| glaze | 549.304 | 0.122679 | 5379.74ms | 1834197 | 40 | 6.10471e+08 | 3.18444e+06 | 3(Loss) |
| simdjson (reflection) | 524.276 | 0.144571 | 5557.23ms | 1834197 | 80 | 1.86133e+09 | 3.33646e+06 | 4(Loss) |
| simdjson (ondemand) | 487.28 | 0.360978 | 5971.64ms | 1834197 | 30 | 5.03753e+09 | 3.58978e+06 | 5(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1283.11 | 0.111829 | 8597.22ms | 1834197 | 320 | 7.43738e+08 | 1.36327e+06 | 1(Win) |
| glaze | 794.273 | 0.374701 | 6858.58ms | 1833577 | 40 | 2.72201e+09 | 2.20156e+06 | 2(Loss) |
| simdjson (reflection) | 741.245 | 0.141973 | 7825.06ms | 1922245 | 160 | 1.97255e+09 | 2.47313e+06 | 3(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1283.37 | 0.134056 | 8571.36ms | 1834197 | 320 | 1.06834e+09 | 1.363e+06 | 1(Win) |
| glaze | 821.255 | 0.0662926 | 6667.16ms | 1833577 | 40 | 7.96951e+07 | 2.12922e+06 | 2(Loss) |
| simdjson (reflection) | 740.213 | 0.167682 | 7710.44ms | 1922245 | 160 | 2.75928e+09 | 2.47658e+06 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2540.87 | 0.152962 | 5608.89ms | 9930848 | 80 | 2.60055e+09 | 3.72738e+06 | 1(Win) |
| jsonifier (two-stage) | 2353.19 | 0.138767 | 6112.61ms | 9930848 | 40 | 1.24765e+09 | 4.02467e+06 | 2(Loss) |
| simdjson (reflection) | 2024.23 | 0.310136 | 7064.72ms | 9930848 | 40 | 8.42205e+09 | 4.67872e+06 | 3(Loss) |
| simdjson (ondemand) | 1922.48 | 0.152894 | 7441.58ms | 9930848 | 80 | 4.53859e+09 | 4.92634e+06 | 4(Loss) |
| glaze | 1903.56 | 0.212637 | 7547.81ms | 9930848 | 40 | 4.4769e+09 | 4.9753e+06 | 5(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2817.87 | 0.186547 | 5630.03ms | 9930848 | 80 | 3.14482e+09 | 3.36098e+06 | 1(Win) |
| jsonifier (two-stage) | 2582.34 | 0.139542 | 6064.09ms | 9930848 | 80 | 2.09531e+09 | 3.66753e+06 | 2(Loss) |
| simdjson (reflection) | 2191.44 | 0.367286 | 7017.99ms | 9930848 | 30 | 7.55861e+09 | 4.32172e+06 | 3(Loss) |
| simdjson (ondemand) | 2077.06 | 0.263112 | 7534.22ms | 9930848 | 30 | 4.31794e+09 | 4.5597e+06 | 4(Loss) |
| glaze | 2055.18 | 0.155624 | 7558.3ms | 9930848 | 80 | 4.11447e+09 | 4.60826e+06 | 5(Loss) |
### Marine IK Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.5201008522600646%)

### Marine IK Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.2761322042045871%)


----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 997.908 | 0.0826907 | 7835.84ms | 642697 | 640 | 1.65092e+08 | 614209 | 1(Win) |
| glaze | 961.303 | 0.0899232 | 8153.95ms | 642697 | 80 | 2.62982e+07 | 637597 | 2(Loss) |
| jsonifier (two-stage) | 878.017 | 0.0985266 | 8951.99ms | 642697 | 80 | 3.78445e+07 | 698077 | 3(Loss) |
| simdjson (ondemand) | 842.039 | 0.0817202 | 9323.09ms | 642697 | 80 | 2.83072e+07 | 727904 | 4(Loss) |
| simdjson (reflection) | 639.477 | 0.103169 | 6069.32ms | 642697 | 40 | 3.91131e+07 | 958477 | 5(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1063.52 | 0.0819646 | 7818.34ms | 642697 | 160 | 3.57018e+07 | 576314 | 1(Win) |
| glaze | 1057.61 | 0.0937241 | 7832.5ms | 642697 | 640 | 1.88819e+08 | 579537 | 2(Loss) |
| jsonifier (two-stage) STATISTICAL TIE | 920.066 | 0.0789986 | 8941.13ms | 642697 | 640 | 1.77253e+08 | 666174 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 919.312 | 0.139799 | 9110.63ms | 642697 | 40 | 3.47498e+07 | 666720 | 3(Tie) |
| simdjson (reflection) | 661.379 | 0.103632 | 6099.81ms | 642697 | 320 | 2.95152e+08 | 926735 | 5(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2412.12 | 0.0608749 | 6519.83ms | 642697 | 1280 | 3.06268e+07 | 254102 | 1(Win) |
| glaze | 1055.06 | 0.085017 | 7416.55ms | 642692 | 640 | 1.56115e+08 | 580933 | 2(Loss) |
| simdjson (reflection) | 930.994 | 0.139616 | 8430.1ms | 643373 | 80 | 6.7732e+07 | 659046 | 3(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2425.03 | 0.0789765 | 6540.25ms | 642697 | 320 | 1.27504e+07 | 252749 | 1(Win) |
| glaze | 1090.62 | 0.190526 | 7194.89ms | 642692 | 80 | 9.17188e+07 | 561990 | 2(Loss) |
| simdjson (reflection) | 925.395 | 0.161236 | 8428.38ms | 643373 | 320 | 3.65717e+08 | 663034 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1525.08 | 0.0960157 | 9836.36ms | 1225964 | 80 | 4.33454e+07 | 766627 | 1(Win) |
| simdjson (ondemand) | 1497.78 | 0.0741973 | 9957.57ms | 1225964 | 640 | 2.14692e+08 | 780602 | 2(Loss) |
| glaze | 1484.82 | 0.151581 | 5061.97ms | 1225964 | 320 | 4.55875e+08 | 787414 | 3(Loss) |
| jsonifier | 1384.76 | 0.131669 | 5353.01ms | 1225964 | 320 | 3.9548e+08 | 844315 | 4(Loss) |
| simdjson (reflection) | 1158.2 | 0.109375 | 6451.39ms | 1225964 | 320 | 3.90103e+08 | 1.00947e+06 | 5(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| simdjson (ondemand) | 1636.63 | 0.0995466 | 9608.36ms | 1225964 | 30 | 1.51715e+07 | 714377 | 1(Win) |
| glaze | 1615.17 | 0.0699917 | 9680.56ms | 1225964 | 640 | 1.64283e+08 | 723868 | 2(Loss) |
| jsonifier (two-stage) | 1590.79 | 0.122131 | 9795.3ms | 1225964 | 320 | 2.57828e+08 | 734962 | 3(Loss) |
| jsonifier | 1432.52 | 0.327769 | 5342.61ms | 1225964 | 80 | 5.72507e+08 | 816163 | 4(Loss) |
| simdjson (reflection) | 1195.85 | 0.191224 | 6411.86ms | 1225964 | 160 | 5.59246e+08 | 977686 | 5(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3839.15 | 0.0674861 | 7849.41ms | 1225964 | 320 | 1.35165e+07 | 304539 | 1(Win) |
| glaze | 1506.62 | 0.191572 | 9944.99ms | 1225970 | 40 | 8.84049e+07 | 776026 | 2(Loss) |
| simdjson (reflection) | 88.8964 | 0.160271 | 9272.51ms | 1226640 | 40 | 1.77925e+10 | 1.31593e+07 | 3(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3833.31 | 0.071015 | 7831.91ms | 1225964 | 1280 | 6.00508e+07 | 305003 | 1(Win) |
| glaze | 1542.52 | 0.0748293 | 9666.26ms | 1225970 | 640 | 2.05883e+08 | 757964 | 2(Loss) |
| simdjson (reflection) | 88.3064 | 0.465311 | 9385.18ms | 1226640 | 40 | 1.51983e+11 | 1.32472e+07 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1166.98 | 0.0700541 | 8561.54ms | 409725 | 1280 | 7.04261e+07 | 334833 | 1(Win) |
| jsonifier (two-stage) | 860.303 | 0.0782947 | 5810.63ms | 409725 | 160 | 2.02333e+07 | 454194 | 2(Loss) |
| glaze | 761.953 | 0.0703836 | 6540.35ms | 409725 | 640 | 8.33781e+07 | 512820 | 3(Loss) |
| simdjson (reflection) | 715.698 | 0.176884 | 6995.78ms | 409725 | 30 | 2.79786e+07 | 545963 | 4(Loss) |
| simdjson (ondemand) | 637.617 | 0.148305 | 7821.92ms | 409725 | 160 | 1.32159e+08 | 612819 | 5(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1866.4 | 0.164358 | 7160.76ms | 409725 | 40 | 4.73607e+06 | 209357 | 1(Win) |
| jsonifier (two-stage) | 1232.5 | 0.19678 | 5172.49ms | 409725 | 320 | 1.24544e+08 | 317034 | 2(Loss) |
| glaze | 949.75 | 0.0740682 | 6203.67ms | 409725 | 640 | 5.94306e+07 | 411418 | 3(Loss) |
| simdjson (reflection) | 814.978 | 0.107148 | 7027.12ms | 409725 | 30 | 7.91735e+06 | 479454 | 4(Loss) |
| simdjson (ondemand) | 761.656 | 0.073633 | 7470.12ms | 409725 | 640 | 9.13257e+07 | 513020 | 5(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10890.2 | 0.0667755 | 3590.51ms | 409725 | 4890 | 2.80711e+06 | 35880.5 | 1(Win) |
| simdjson (reflection) | 8254.49 | 0.106848 | 4859.76ms | 409725 | 640 | 1.63726e+06 | 47337.2 | 2(Loss) |
| glaze | 1924.87 | 0.0700414 | 5247.77ms | 409725 | 320 | 6.46905e+06 | 202998 | 3(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11038 | 0.198893 | 3591.89ms | 409725 | 160 | 793169 | 35400 | 1(Win) |
| simdjson (reflection) | 7906.47 | 0.290508 | 4877.36ms | 409725 | 80 | 1.64902e+06 | 49420.8 | 2(Loss) |
| glaze | 2056.55 | 0.0648159 | 9808.37ms | 409725 | 320 | 4.85311e+06 | 190000 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1690.16 | 0.148814 | 5658.51ms | 785750 | 320 | 1.39301e+08 | 443360 | 1(Win) |
| jsonifier (two-stage) | 1291.65 | 0.0984454 | 7367.85ms | 785750 | 640 | 2.08762e+08 | 580150 | 2(Loss) |
| glaze | 1274.91 | 0.103222 | 7495.82ms | 785750 | 320 | 1.1779e+08 | 587766 | 3(Loss) |
| simdjson (reflection) | 1257.24 | 0.133235 | 7633.89ms | 785750 | 40 | 2.52246e+07 | 596026 | 4(Loss) |
| simdjson (ondemand) | 1138.82 | 0.0815547 | 8433.21ms | 785750 | 160 | 4.60761e+07 | 658005 | 5(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2352.63 | 0.061049 | 5031.93ms | 785750 | 160 | 6.04976e+06 | 318515 | 1(Win) |
| jsonifier (two-stage) | 1902.1 | 0.108901 | 6857.42ms | 785750 | 320 | 5.89001e+07 | 393960 | 2(Loss) |
| glaze | 1532.26 | 0.158488 | 7137.99ms | 785750 | 320 | 1.92241e+08 | 489048 | 3(Loss) |
| simdjson (reflection) | 1417 | 0.200201 | 7615.3ms | 785750 | 30 | 3.36264e+07 | 528828 | 4(Loss) |
| simdjson (ondemand) | 1337.13 | 0.0819022 | 8069.16ms | 785750 | 640 | 1.34833e+08 | 560418 | 5(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13697.4 | 0.0566718 | 5615.37ms | 785750 | 2560 | 2.46076e+06 | 54707.6 | 1(Win) |
| glaze | 2469.4 | 0.0796048 | 7793.17ms | 785750 | 640 | 3.73459e+07 | 303454 | 2(Loss) |
| simdjson (reflection) | 323.746 | 0.371663 | 7179.11ms | 785750 | 80 | 5.92037e+09 | 2.31462e+06 | 3(Loss) |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13661.4 | 0.0451424 | 5492.88ms | 785750 | 4890 | 2.99816e+06 | 54851.5 | 1(Win) |
| glaze | 2685.54 | 0.175652 | 7191.52ms | 785750 | 30 | 7.20662e+06 | 279031 | 2(Loss) |
| simdjson (reflection) | 325.365 | 0.19434 | 7198.26ms | 785750 | 160 | 3.20532e+09 | 2.3031e+06 | 3(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 4145.95 | 0.142649 | 6147.85ms | 264040 | 320 | 2.40203e+06 | 60736 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 4135.27 | 0.18692 | 6151.22ms | 264040 | 160 | 2.07282e+06 | 60892.8 | 1(Tie) |
| simdjson (ondemand) | 3092.8 | 0.0544565 | 8294.01ms | 264040 | 1280 | 2.5162e+06 | 81417.6 | 3(Loss) |
| simdjson (reflection) | 3067.12 | 0.296439 | 8289.41ms | 264040 | 30 | 1.77693e+06 | 82099.2 | 4(Loss) |
| glaze | 2300.78 | 0.167221 | 5642.28ms | 264040 | 160 | 5.35909e+06 | 109445 | 5(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 4264.19 | 0.0580894 | 6067.52ms | 264040 | 4890 | 5.75399e+06 | 59051.8 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 4262.89 | 0.0451875 | 6108.08ms | 264040 | 4890 | 3.48399e+06 | 59069.9 | 1(Tie) |
| simdjson (ondemand) | 3186.06 | 0.0855419 | 8093.87ms | 264040 | 640 | 2.92529e+06 | 79034.4 | 3(Loss) |
| simdjson (reflection) | 3109.63 | 0.0404303 | 8296.86ms | 264040 | 4890 | 5.24135e+06 | 80976.8 | 4(Loss) |
| glaze | 2329.34 | 0.113703 | 5617.17ms | 264040 | 640 | 9.66939e+06 | 108103 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4818.39 | 0.0606824 | 7981.15ms | 399947 | 4890 | 1.12833e+07 | 79159.1 | 1(Win) |
| jsonifier (two-stage) | 4784.74 | 0.135565 | 7974.8ms | 399947 | 2560 | 2.98967e+07 | 79715.8 | 2(Loss) |
| simdjson (ondemand) | 3898.46 | 0.130442 | 5034.58ms | 399947 | 320 | 5.21196e+06 | 97838.4 | 3(Loss) |
| simdjson (reflection) | 3873.84 | 0.0631626 | 5061.5ms | 399947 | 1280 | 4.95053e+06 | 98460.2 | 4(Loss) |
| glaze | 3019.86 | 0.0724161 | 6540.33ms | 399947 | 2560 | 2.14162e+07 | 126304 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 4970.74 | 0.111999 | 7931.25ms | 399947 | 160 | 1.1817e+06 | 76732.8 | 1(Win) |
| jsonifier | 4929.99 | 0.074999 | 7932.56ms | 399947 | 4890 | 1.64639e+07 | 77367.1 | 2(Loss) |
| simdjson (ondemand) | 4003.24 | 0.130089 | 9762.29ms | 399947 | 320 | 4.91599e+06 | 95277.6 | 3(Loss) |
| simdjson (reflection) | 3941.24 | 0.0826675 | 5538.76ms | 399947 | 30 | 192013 | 96776.5 | 4(Loss) |
| glaze | 3064.2 | 0.114096 | 6460.42ms | 399947 | 1280 | 2.5818e+07 | 124476 | 5(Loss) |
### Twitter Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.5095399010871243%)

### Twitter Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 5.436369283458934%)


----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11899.2 | 0.303015 | 2125.81ms | 264040 | 2560 | 1.05262e+07 | 21161.7 | 1(Win) |
| simdjson (reflection) | 8053.63 | 1.19855 | 3109.65ms | 264040 | 320 | 4.49386e+07 | 31266.4 | 2(Loss) |
| glaze | 3303.15 | 0.187743 | 8015.43ms | 263923 | 1280 | 2.61961e+07 | 76199 | 3(Loss) |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13504.4 | 0.192534 | 2338.6ms | 264040 | 320 | 412435 | 18646.4 | 1(Win) |
| simdjson (reflection) | 8897.06 | 0.326836 | 2923.48ms | 264040 | 640 | 5.4763e+06 | 28302.4 | 2(Loss) |
| glaze | 3868.54 | 0.175004 | 6994.25ms | 263923 | 4890 | 6.33963e+07 | 65062.5 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2040.43 | 0.433538 | 5670.92ms | 399947 | 30 | 1.97033e+07 | 186931 | 1(Win) |
| jsonifier | 1859.69 | 1.94591 | 5340.51ms | 399947 | 30 | 4.77853e+08 | 205099 | 2(Loss) |
| glaze | 1655.01 | 0.697576 | 6063.62ms | 399947 | 80 | 2.06766e+08 | 230464 | 3(Loss) |
| simdjson (reflection) | 1590.64 | 0.163121 | 6248.11ms | 399947 | 1280 | 1.95836e+08 | 239790 | 4(Loss) |
| simdjson (ondemand) | 1469.83 | 0.7681 | 6954.37ms | 399947 | 30 | 1.19187e+08 | 259499 | 5(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2430.56 | 0.663964 | 5239.75ms | 399947 | 160 | 1.737e+08 | 156926 | 1(Win) |
| jsonifier STATISTICAL TIE | 2178.49 | 1.50773 | 5812.03ms | 399947 | 1280 | 8.91968e+09 | 175084 | 2(Tie) |
| glaze STATISTICAL TIE | 2158.78 | 0.306308 | 5634.58ms | 399947 | 30 | 8.78672e+06 | 176683 | 2(Tie) |
| simdjson (ondemand) | 1796.44 | 0.161 | 6324.9ms | 399947 | 320 | 3.73923e+07 | 212320 | 4(Loss) |
| simdjson (reflection) | 1723.91 | 0.739999 | 6286.94ms | 399947 | 30 | 8.04192e+07 | 221252 | 5(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15211 | 0.299105 | 2638.99ms | 399947 | 40 | 225007 | 25075.2 | 1(Win) |
| glaze | 3404.07 | 0.29053 | 5611.32ms | 399830 | 320 | 3.38911e+07 | 112015 | 2(Loss) |
| simdjson (reflection) | 414.171 | 0.21034 | 5885.52ms | 399947 | 40 | 1.50089e+08 | 920922 | 3(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14930.7 | 0.271103 | 2619.98ms | 399947 | 640 | 3.06968e+06 | 25546 | 1(Win) |
| glaze | 4246.36 | 0.231843 | 9551.83ms | 399830 | 30 | 1.30025e+06 | 89796.3 | 2(Loss) |
| simdjson (reflection) | 405.997 | 0.409186 | 5901.57ms | 399947 | 320 | 4.7288e+09 | 939462 | 3(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 750.798 | 0.152691 | 613.415ms | 4630 | 4890 | 394321 | 5881.09 | 1(Win) |
| jsonifier (two-stage) | 643.773 | 0.2885 | 696.195ms | 4630 | 640 | 250592 | 6858.8 | 2(Loss) |
| simdjson (reflection) | 554.824 | 0.267356 | 870.8ms | 4630 | 640 | 289743 | 7958.4 | 3(Loss) |
| glaze | 457.481 | 0.123605 | 988.477ms | 4630 | 2560 | 364358 | 9651.8 | 4(Loss) |
| simdjson (ondemand) | 431.704 | 0.106197 | 1030.34ms | 4630 | 2560 | 302031 | 10228.1 | 5(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 937.271 | 0.164032 | 620.49ms | 4630 | 4890 | 292009 | 4711.03 | 1(Win) |
| jsonifier (two-stage) | 777.269 | 0.550507 | 714.241ms | 4630 | 320 | 312965 | 5680.8 | 2(Loss) |
| simdjson (reflection) | 652.526 | 0.269746 | 831.445ms | 4630 | 640 | 213234 | 6766.8 | 3(Loss) |
| glaze | 515.494 | 0.202826 | 974.993ms | 4630 | 1280 | 386344 | 8565.6 | 4(Loss) |
| simdjson (ondemand) | 487.254 | 0.0892381 | 1029.2ms | 4630 | 4890 | 319787 | 9062.03 | 5(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2299.43 | 0.240965 | 195.557ms | 4630 | 4890 | 104698 | 1920.26 | 1(Win) |
| glaze | 1533.27 | 0.262561 | 292.876ms | 4630 | 2560 | 146361 | 2879.8 | 2(Loss) |
| simdjson (reflection) | 845.624 | 0.455877 | 532.132ms | 4630 | 320 | 181322 | 5221.6 | 3(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2340.96 | 0.538551 | 192.284ms | 4630 | 1280 | 132081 | 1886.2 | 1(Win) |
| glaze | 1739.43 | 0.313128 | 259.327ms | 4630 | 4890 | 308960 | 2538.48 | 2(Loss) |
| simdjson (reflection) | 845.203 | 0.181285 | 528.043ms | 4630 | 2560 | 229616 | 5224.2 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1823.51 | 0.838516 | 871.495ms | 14795 | 80 | 336764 | 7737.6 | 1(Win) |
| jsonifier (two-stage) | 1770.87 | 0.135474 | 809.778ms | 14795 | 1280 | 149134 | 7967.6 | 2(Loss) |
| simdjson (reflection) | 1527.68 | 0.2428 | 931.303ms | 14795 | 640 | 321844 | 9236 | 3(Loss) |
| simdjson (ondemand) | 1232.32 | 0.448559 | 1355.77ms | 14795 | 160 | 422027 | 11449.6 | 4(Loss) |
| glaze | 1178.45 | 0.0977689 | 1372ms | 14795 | 1280 | 175395 | 11973 | 5(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2252.78 | 0.268842 | 748.83ms | 14795 | 1280 | 362907 | 6263.2 | 1(Win) |
| jsonifier (two-stage) | 2085.25 | 0.366611 | 804.624ms | 14795 | 320 | 196914 | 6766.4 | 2(Loss) |
| simdjson (reflection) | 1765.82 | 0.475672 | 979.13ms | 14795 | 160 | 231138 | 7990.4 | 3(Loss) |
| simdjson (ondemand) | 1328.09 | 0.854869 | 1235.81ms | 14795 | 30 | 247455 | 10624 | 4(Loss) |
| glaze | 1252.21 | 0.149311 | 1261.42ms | 14795 | 1280 | 362304 | 11267.8 | 5(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6745.85 | 0.576857 | 215.02ms | 14795 | 640 | 93169.4 | 2091.6 | 1(Win) |
| glaze | 2953.28 | 0.514067 | 491.429ms | 14795 | 320 | 193023 | 4777.6 | 2(Loss) |
| simdjson (reflection) | 122.653 | 0.276611 | 5942.19ms | 14795 | 80 | 8.10032e+06 | 115037 | 3(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6876.63 | 0.189275 | 209.554ms | 14795 | 4890 | 73751.9 | 2051.82 | 1(Win) |
| glaze | 3258.4 | 0.191103 | 443.124ms | 14795 | 4890 | 334860 | 4330.22 | 2(Loss) |
| simdjson (reflection) | 122.903 | 0.224834 | 6137.25ms | 14795 | 40 | 2.66496e+06 | 114803 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1300.59 | 0.219582 | 384.533ms | 5092 | 4890 | 328700 | 3733.78 | 1(Win) |
| jsonifier (two-stage) | 977.438 | 0.190981 | 516.48ms | 5092 | 1280 | 115236 | 4968.2 | 2(Loss) |
| glaze | 901.349 | 0.199765 | 549.416ms | 5092 | 2560 | 296532 | 5387.6 | 3(Loss) |
| simdjson (ondemand) | 840.653 | 0.203769 | 586.212ms | 5092 | 4890 | 677531 | 5776.6 | 4(Loss) |
| simdjson (reflection) | 820.954 | 0.140447 | 600.116ms | 5092 | 2560 | 176686 | 5915.2 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1799.61 | 0.258273 | 361.418ms | 5092 | 4890 | 237511 | 2698.42 | 1(Win) |
| jsonifier (two-stage) | 1250.67 | 0.200866 | 483.462ms | 5092 | 2560 | 155720 | 3882.8 | 2(Loss) |
| glaze | 1046.97 | 0.180114 | 550.261ms | 5092 | 4890 | 341282 | 4638.26 | 3(Loss) |
| simdjson (ondemand) | 1040.25 | 0.218463 | 551.973ms | 5092 | 2560 | 266253 | 4668.2 | 4(Loss) |
| simdjson (reflection) | 986.052 | 0.635594 | 640.005ms | 5092 | 80 | 78384 | 4924.8 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8558.53 | 2.45803 | 60.7222ms | 5092 | 1280 | 248978 | 567.4 | 1(Win) |
| simdjson (reflection) | 7009.4 | 2.10595 | 73.6141ms | 5092 | 1280 | 272471 | 692.8 | 2(Loss) |
| glaze | 1498.38 | 0.326152 | 327.743ms | 5092 | 2560 | 286029 | 3240.9 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8893.97 | 3.63325 | 59.6849ms | 5092 | 640 | 251858 | 546 | 1(Win) |
| simdjson (reflection) | 7601.92 | 2.11781 | 68.1989ms | 5092 | 1280 | 234268 | 638.8 | 2(Loss) |
| glaze | 1746.05 | 0.558463 | 269.53ms | 5092 | 1280 | 308790 | 2781.2 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2129.85 | 0.48937 | 535.231ms | 11724 | 320 | 211192 | 5249.6 | 1(Win) |
| jsonifier (two-stage) | 1883.06 | 0.359625 | 608.241ms | 11724 | 160 | 72952.6 | 5937.6 | 2(Loss) |
| simdjson (ondemand) | 1706.2 | 0.192914 | 670.384ms | 11724 | 2560 | 409130 | 6553.1 | 3(Loss) |
| simdjson (reflection) | 1668.44 | 0.119996 | 684.105ms | 11724 | 4890 | 316209 | 6701.39 | 4(Loss) |
| glaze | 1455.24 | 0.48453 | 779.315ms | 11724 | 160 | 221740 | 7683.2 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2656.8 | 0.430014 | 557.305ms | 11724 | 640 | 209595 | 4208.4 | 1(Win) |
| jsonifier (two-stage) | 2419.56 | 0.207983 | 592.546ms | 11724 | 4890 | 451692 | 4621.04 | 2(Loss) |
| simdjson (ondemand) | 2039.81 | 0.152628 | 631.311ms | 11724 | 4890 | 342253 | 5481.33 | 3(Loss) |
| simdjson (reflection) | 1978.36 | 0.375826 | 656.224ms | 11724 | 640 | 288733 | 5651.6 | 4(Loss) |
| glaze | 1694.48 | 0.428259 | 754.004ms | 11724 | 320 | 255529 | 6598.4 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15655.1 | 1.85371 | 81.7779ms | 11724 | 1280 | 224353 | 714.2 | 1(Win) |
| glaze | 2782.66 | 0.719599 | 416.665ms | 11746 | 40 | 33566.2 | 4025.6 | 2(Loss) |
| simdjson (reflection) | 324.973 | 0.18028 | 3468.58ms | 11724 | 320 | 1.23113e+06 | 34405.6 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17663.3 | 1.75554 | 65.463ms | 11724 | 2560 | 316132 | 633 | 1(Win) |
| glaze | 2881.73 | 0.788717 | 388.031ms | 11746 | 320 | 300792 | 3887.2 | 2(Loss) |
| simdjson (reflection) | 322.595 | 0.3449 | 4209.42ms | 11724 | 320 | 4.57272e+06 | 34659.2 | 3(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1439.58 | 0.43899 | 347.288ms | 4857 | 1280 | 255378 | 3217.6 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1121.51 | 1.62052 | 455.695ms | 4857 | 30 | 134386 | 4130.13 | 2(Tie) |
| glaze STATISTICAL TIE | 1083.46 | 1.84688 | 521.895ms | 4857 | 40 | 249373 | 4275.2 | 2(Tie) |
| simdjson (reflection) | 926.3 | 0.474272 | 500.678ms | 4857 | 30 | 16873.6 | 5000.53 | 4(Loss) |
| simdjson (ondemand) | 801.162 | 0.90302 | 616.579ms | 4857 | 320 | 872250 | 5781.6 | 5(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2101.22 | 0.360452 | 301.766ms | 4857 | 4890 | 308742 | 2204.43 | 1(Win) |
| glaze | 1626.75 | 0.57934 | 348.69ms | 4857 | 1280 | 348317 | 2847.4 | 2(Loss) |
| jsonifier (two-stage) | 1275.68 | 0.894103 | 431.675ms | 4857 | 2560 | 2.69816e+06 | 3631 | 3(Loss) |
| simdjson (reflection) | 1226.11 | 0.272131 | 430.927ms | 4857 | 4890 | 516827 | 3777.81 | 4(Loss) |
| simdjson (ondemand) | 1143.48 | 0.25021 | 493.114ms | 4857 | 640 | 65746.1 | 4050.8 | 5(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9998.69 | 1.57326 | 48.8998ms | 4857 | 4890 | 259755 | 463.261 | 1(Win) |
| simdjson (reflection) | 8070.63 | 1.25118 | 60.1452ms | 4857 | 4890 | 252155 | 573.932 | 2(Loss) |
| glaze | 2432.77 | 0.857004 | 188.292ms | 4857 | 640 | 170404 | 1904 | 3(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11649.9 | 4.89754 | 43.3649ms | 4857 | 640 | 242677 | 397.6 | 1(Win) |
| simdjson (reflection) | 8929.99 | 1.3959 | 54.5359ms | 4857 | 4890 | 256362 | 518.701 | 2(Loss) |
| glaze | 3036.78 | 0.662993 | 158.115ms | 4857 | 2560 | 261799 | 1525.3 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1714.35 | 0.361568 | 416.959ms | 7376 | 640 | 140866 | 4103.2 | 1(Win) |
| jsonifier (two-stage) | 1644.53 | 0.167956 | 434.924ms | 7376 | 4890 | 252382 | 4277.4 | 2(Loss) |
| glaze | 1507.92 | 0.17528 | 470.807ms | 7376 | 4890 | 326934 | 4664.91 | 3(Loss) |
| simdjson (reflection) | 1408.66 | 0.231763 | 503.556ms | 7376 | 160 | 21430.6 | 4993.6 | 4(Loss) |
| simdjson (ondemand) | 1277.74 | 0.146269 | 557.532ms | 7376 | 4890 | 317082 | 5505.26 | 5(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2294.82 | 0.26862 | 365.814ms | 7376 | 2560 | 173565 | 3065.3 | 1(Win) |
| jsonifier (two-stage) | 2114.69 | 0.418106 | 393.24ms | 7376 | 1280 | 247589 | 3326.4 | 2(Loss) |
| glaze | 1988.52 | 0.245458 | 424.734ms | 7376 | 4890 | 368677 | 3537.46 | 3(Loss) |
| simdjson (reflection) | 1721.22 | 0.344116 | 499.925ms | 7376 | 640 | 126577 | 4086.8 | 4(Loss) |
| simdjson (ondemand) | 1610.86 | 0.32918 | 483.067ms | 7376 | 1280 | 264487 | 4366.8 | 5(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11910.4 | 1.65694 | 64.0399ms | 7376 | 2560 | 245156 | 590.6 | 1(Win) |
| glaze | 2487.73 | 0.632452 | 300.873ms | 7376 | 640 | 204678 | 2827.6 | 2(Loss) |
| simdjson (reflection) | 317.754 | 1.21893 | 2049.19ms | 7376 | 80 | 5.8252e+06 | 22137.6 | 3(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12798.9 | 1.90041 | 61.2012ms | 7376 | 2560 | 279271 | 549.6 | 1(Win) |
| glaze | 2778.74 | 0.294217 | 258.395ms | 7376 | 4890 | 271263 | 2531.47 | 2(Loss) |
| simdjson (reflection) | 355.749 | 0.138475 | 2001.87ms | 7376 | 640 | 479820 | 19773.2 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1764.04 | 0.338915 | 243.152ms | 4390 | 4890 | 316373 | 2373.31 | 1(Win) |
| jsonifier (two-stage) | 1102.79 | 0.483722 | 385.967ms | 4390 | 640 | 215831 | 3796.4 | 2(Loss) |
| simdjson (reflection) | 813.38 | 0.677537 | 633.031ms | 4390 | 320 | 389187 | 5147.2 | 3(Loss) |
| glaze | 712.254 | 0.563646 | 503.553ms | 4390 | 2560 | 2.81003e+06 | 5878 | 4(Loss) |
| simdjson (ondemand) | 589.367 | 0.655849 | 701.64ms | 4390 | 2560 | 5.55655e+06 | 7103.6 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2211.87 | 0.93933 | 233.944ms | 4390 | 320 | 101157 | 1892.8 | 1(Win) |
| jsonifier (two-stage) | 1129.12 | 0.265921 | 418.23ms | 4390 | 4890 | 475404 | 3707.86 | 2(Loss) |
| glaze | 1096.44 | 0.329356 | 430.92ms | 4390 | 1280 | 202444 | 3818.4 | 3(Loss) |
| simdjson (reflection) | 852.674 | 0.400186 | 503.961ms | 4390 | 1280 | 494193 | 4910 | 4(Loss) |
| simdjson (ondemand) | 829.069 | 0.185617 | 577.658ms | 4390 | 1280 | 112459 | 5049.8 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7725.84 | 1.90941 | 69.3868ms | 4390 | 2560 | 274080 | 541.9 | 1(Win) |
| simdjson (reflection) | 6987.03 | 2.30264 | 66.1181ms | 4390 | 1280 | 243671 | 599.2 | 2(Loss) |
| glaze | 1503.82 | 1.19049 | 334.385ms | 4390 | 320 | 351511 | 2784 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10276.5 | 2.39525 | 44.9521ms | 4390 | 2560 | 243772 | 407.4 | 1(Win) |
| simdjson (reflection) | 7243.3 | 3.40175 | 73.4751ms | 4390 | 640 | 247423 | 578 | 2(Loss) |
| glaze | 1535.42 | 0.763518 | 294.666ms | 4390 | 2560 | 1.10957e+06 | 2726.7 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2250.08 | 0.392023 | 515.235ms | 11521 | 4890 | 1.79191e+06 | 4883.06 | 1(Win) |
| simdjson (reflection) | 1950.31 | 0.279194 | 643.535ms | 11521 | 1280 | 316661 | 5633.6 | 2(Loss) |
| jsonifier (two-stage) | 1739.21 | 0.570005 | 628.871ms | 11521 | 1280 | 1.65975e+06 | 6317.4 | 3(Loss) |
| simdjson (ondemand) | 1519.6 | 0.644703 | 751.31ms | 11521 | 160 | 347668 | 7230.4 | 4(Loss) |
| glaze | 1297.75 | 1.17335 | 868.339ms | 11521 | 2560 | 2.52636e+07 | 8466.4 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2956.68 | 0.277661 | 435.85ms | 11521 | 4890 | 520605 | 3716.08 | 1(Win) |
| jsonifier (two-stage) | 2476.4 | 0.917628 | 648.744ms | 11521 | 160 | 265212 | 4436.8 | 2(Loss) |
| simdjson (reflection) | 1980.83 | 0.591258 | 628.99ms | 11521 | 1280 | 1.37673e+06 | 5546.8 | 3(Loss) |
| glaze | 1640.18 | 0.435642 | 728.642ms | 11521 | 4890 | 4.16453e+06 | 6698.82 | 4(Loss) |
| simdjson (ondemand) | 1593.61 | 0.390624 | 745.913ms | 11521 | 1280 | 928423 | 6894.6 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13953.9 | 2.60767 | 78.711ms | 11521 | 1280 | 539642 | 787.4 | 1(Win) |
| glaze | 2493.48 | 0.885337 | 503.617ms | 11521 | 160 | 243503 | 4406.4 | 2(Loss) |
| simdjson (reflection) | 253.724 | 0.3853 | 4403.21ms | 11521 | 640 | 1.7817e+07 | 43304 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16453 | 1.98803 | 81.9881ms | 11521 | 1280 | 225605 | 667.8 | 1(Win) |
| glaze | 2937.78 | 0.301159 | 416.694ms | 11521 | 2560 | 324770 | 3740 | 2(Loss) |
| simdjson (reflection) | 256.284 | 0.448487 | 4194.93ms | 11521 | 4890 | 1.80778e+08 | 42871.5 | 3(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2397.28 | 0.566676 | 194.937ms | 4669 | 1280 | 141805 | 1857.4 | 1(Win) |
| jsonifier (two-stage) | 1422.04 | 0.637625 | 340.859ms | 4669 | 320 | 127556 | 3131.2 | 2(Loss) |
| glaze STATISTICAL TIE | 1099.65 | 0.657238 | 529.177ms | 4669 | 640 | 453276 | 4049.2 | 3(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1092.21 | 0.763983 | 598.142ms | 4669 | 80 | 77606.2 | 4076.8 | 3(Tie) |
| simdjson (ondemand) | 998.185 | 0.371838 | 466.523ms | 4669 | 1280 | 352162 | 4460.8 | 5(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2690.38 | 0.492818 | 184.907ms | 4669 | 4890 | 325314 | 1655.05 | 1(Win) |
| jsonifier (two-stage) | 1519.49 | 0.671485 | 336.842ms | 4669 | 320 | 123901 | 2930.4 | 2(Loss) |
| glaze | 1344.74 | 0.463914 | 356.733ms | 4669 | 1280 | 302034 | 3311.2 | 3(Loss) |
| simdjson (ondemand) | 1125.21 | 0.195233 | 417.711ms | 4669 | 4890 | 291873 | 3957.22 | 4(Loss) |
| simdjson (reflection) | 1118.91 | 0.201192 | 411.736ms | 4669 | 4890 | 313466 | 3979.52 | 5(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11573.5 | 1.81636 | 40.564ms | 4669 | 4890 | 238799 | 384.733 | 1(Win) |
| simdjson (reflection) | 6793.96 | 1.09672 | 69.5872ms | 4669 | 4890 | 252638 | 655.391 | 2(Loss) |
| glaze | 1575.62 | 0.654069 | 297.232ms | 4669 | 640 | 218661 | 2826 | 3(Loss) |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13240 | 2.13465 | 37.098ms | 4669 | 4890 | 252020 | 336.308 | 1(Win) |
| simdjson (reflection) | 6390.22 | 3.72655 | 67.575ms | 4669 | 320 | 215765 | 696.8 | 2(Loss) |
| glaze | 1800.5 | 0.416737 | 253.917ms | 4669 | 4890 | 519393 | 2473.04 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 2321.19 | 0.321821 | 387.599ms | 9249 | 2560 | 382857 | 3800 | 1(Win) |
| simdjson (reflection) | 1908.88 | 1.74012 | 642.72ms | 9249 | 40 | 258615 | 4620.8 | 2(Loss) |
| glaze | 1784.43 | 0.299041 | 502.991ms | 9249 | 4890 | 1.06846e+06 | 4943.05 | 3(Loss) |
| simdjson (ondemand) | 1732.78 | 0.265094 | 525.745ms | 9249 | 1280 | 233085 | 5090.4 | 4(Loss) |
| jsonifier | 1304.2 | 0.346865 | 697.049ms | 9249 | 1280 | 704425 | 6763.2 | 5(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2979.63 | 0.224631 | 322.036ms | 9249 | 4890 | 216229 | 2960.28 | 1(Win) |
| jsonifier (two-stage) | 2431.51 | 0.362438 | 457.834ms | 9249 | 2560 | 442534 | 3627.6 | 2(Loss) |
| glaze | 2020.65 | 0.537042 | 581.901ms | 9249 | 1280 | 703454 | 4365.2 | 3(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1963 | 0.436604 | 473.557ms | 9249 | 1280 | 492647 | 4493.4 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1950.43 | 0.206008 | 478.362ms | 9249 | 4890 | 424431 | 4522.35 | 4(Tie) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14979.2 | 1.23021 | 61.601ms | 9249 | 4890 | 256612 | 588.852 | 1(Win) |
| glaze | 2024.78 | 0.224112 | 451.148ms | 9249 | 4890 | 466093 | 4356.29 | 2(Loss) |
| simdjson (reflection) | 305.691 | 0.169874 | 3008.44ms | 9249 | 2560 | 6.15061e+06 | 28854.4 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15751 | 2.49357 | 58.3439ms | 9249 | 1280 | 249590 | 560 | 1(Win) |
| glaze | 2192.77 | 0.195414 | 416.776ms | 9249 | 4890 | 302150 | 4022.55 | 2(Loss) |
| simdjson (reflection) | 305.281 | 0.127235 | 3090.82ms | 9249 | 4890 | 6.60867e+06 | 28893.2 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 527.946 | 0.226489 | 855.829ms | 4604 | 4890 | 1.73498e+06 | 8316.6 | 1(Win) |
| simdjson (reflection) | 446.356 | 0.533276 | 1173.87ms | 4604 | 320 | 880566 | 9836.8 | 2(Loss) |
| jsonifier (two-stage) | 438.822 | 0.320412 | 1035.46ms | 4604 | 2560 | 2.63119e+06 | 10005.7 | 3(Loss) |
| glaze | 373.487 | 0.411944 | 1278.61ms | 4604 | 320 | 750489 | 11756 | 4(Loss) |
| simdjson (ondemand) | 345.791 | 0.652764 | 1352.02ms | 4604 | 30 | 206099 | 12697.6 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 660.417 | 0.651693 | 1018.72ms | 4604 | 640 | 1.20144e+06 | 6648.4 | 1(Win) |
| simdjson (reflection) | 532.015 | 0.300911 | 1016.12ms | 4604 | 1280 | 789421 | 8253 | 2(Loss) |
| jsonifier (two-stage) | 520.455 | 0.56912 | 1008.87ms | 4604 | 2560 | 5.90136e+06 | 8436.3 | 3(Loss) |
| glaze | 436.859 | 0.177941 | 1265.77ms | 4604 | 4890 | 1.56404e+06 | 10050.6 | 4(Loss) |
| simdjson (ondemand) | 384.34 | 0.252052 | 1372.55ms | 4604 | 4890 | 4.05441e+06 | 11424 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1635.71 | 0.312382 | 276.443ms | 4604 | 4890 | 343826 | 2684.28 | 1(Win) |
| simdjson (reflection) | 1402.14 | 0.444856 | 339.821ms | 4918 | 1280 | 283427 | 3345 | 2(Loss) |
| glaze | 853.565 | 0.328417 | 559.781ms | 4604 | 4890 | 1.39559e+06 | 5143.98 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1696.57 | 0.432184 | 263.207ms | 4604 | 2560 | 320263 | 2588 | 1(Win) |
| simdjson (reflection) | 1407.36 | 0.478812 | 368.726ms | 4918 | 1280 | 325917 | 3332.6 | 2(Loss) |
| glaze | 949.221 | 0.85576 | 476.896ms | 4604 | 160 | 250704 | 4625.6 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1969.12 | 0.599017 | 1298.05ms | 24579 | 30 | 152541 | 11904 | 1(Win) |
| jsonifier (two-stage) | 1924.69 | 0.367825 | 1547.82ms | 24579 | 640 | 1.28432e+06 | 12178.8 | 2(Loss) |
| simdjson (reflection) | 1889.86 | 0.268121 | 1261.62ms | 24579 | 1280 | 1.4156e+06 | 12403.2 | 3(Loss) |
| simdjson (ondemand) | 1530.13 | 0.237577 | 1768.59ms | 24579 | 640 | 847737 | 15319.2 | 4(Loss) |
| glaze | 1420.53 | 0.265914 | 1825.92ms | 24579 | 2560 | 4.92888e+06 | 16501.1 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2275.76 | 0.243091 | 1249.22ms | 24579 | 2560 | 1.60491e+06 | 10300 | 1(Win) |
| jsonifier (two-stage) | 2259.9 | 0.218249 | 1234.95ms | 24579 | 2560 | 1.31188e+06 | 10372.3 | 2(Loss) |
| simdjson (reflection) | 2186.45 | 0.133441 | 1369.69ms | 24579 | 4890 | 1.00078e+06 | 10720.7 | 3(Loss) |
| simdjson (ondemand) | 1705.65 | 0.312788 | 1553.11ms | 24579 | 640 | 1.18258e+06 | 13742.8 | 4(Loss) |
| glaze | 1603.46 | 0.227299 | 1638.97ms | 24579 | 2560 | 2.82648e+06 | 14618.6 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6937.48 | 0.483963 | 362.741ms | 24579 | 1280 | 342263 | 3378.8 | 1(Win) |
| glaze | 2802.98 | 1.18636 | 893.941ms | 24579 | 30 | 295289 | 8362.67 | 2(Loss) |
| simdjson (reflection) | 168.128 | 0.724982 | 7784.14ms | 24893 | 30 | 3.14378e+07 | 141201 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7381.4 | 0.492145 | 334.616ms | 24579 | 640 | 156321 | 3175.6 | 1(Win) |
| glaze | 3074.55 | 0.675784 | 780.321ms | 24579 | 320 | 849438 | 7624 | 2(Loss) |
| simdjson (reflection) | 167.222 | 0.182597 | 7585.93ms | 24893 | 1280 | 8.60133e+07 | 141966 | 3(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 590.872 | 0.172516 | 752.46ms | 4604 | 4890 | 803623 | 7430.91 | 1(Win) |
| jsonifier (two-stage) | 499.905 | 0.207529 | 911.172ms | 4604 | 4890 | 1.62466e+06 | 8783.1 | 2(Loss) |
| simdjson (reflection) | 445.198 | 0.48424 | 1032.59ms | 4604 | 80 | 182464 | 9862.4 | 3(Loss) |
| glaze | 378.824 | 0.477961 | 1241.79ms | 4604 | 80 | 245511 | 11590.4 | 4(Loss) |
| simdjson (ondemand) | 328.138 | 0.151626 | 1406.59ms | 4604 | 4890 | 2.01286e+06 | 13380.7 | 5(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 820.633 | 1.75238 | 977.822ms | 4604 | 30 | 263726 | 5350.4 | 1(Win) |
| jsonifier (two-stage) | 624.817 | 0.533251 | 885.166ms | 4604 | 320 | 449343 | 7027.2 | 2(Loss) |
| simdjson (reflection) | 530.44 | 0.334368 | 1040.35ms | 4604 | 2560 | 1.96105e+06 | 8277.5 | 3(Loss) |
| glaze | 435.794 | 0.450112 | 1246.99ms | 4604 | 320 | 658110 | 10075.2 | 4(Loss) |
| simdjson (ondemand) | 388.738 | 0.20803 | 1313.18ms | 4604 | 1280 | 706675 | 11294.8 | 5(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1675.85 | 0.769868 | 281.195ms | 4604 | 640 | 260384 | 2620 | 1(Win) |
| simdjson (reflection) | 1366.64 | 0.418289 | 353.419ms | 4918 | 2560 | 527548 | 3431.9 | 2(Loss) |
| glaze | 888.09 | 0.680596 | 577.608ms | 4604 | 80 | 90578.6 | 4944 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1668.78 | 0.365037 | 266.636ms | 4604 | 4890 | 451083 | 2631.09 | 1(Win) |
| simdjson (reflection) | 1384.43 | 0.338457 | 358.361ms | 4918 | 2560 | 336575 | 3387.8 | 2(Loss) |
| glaze | 933.401 | 0.567753 | 503.556ms | 4604 | 320 | 228246 | 4704 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2242.5 | 0.513977 | 1093.5ms | 24579 | 160 | 461820 | 10452.8 | 1(Win) |
| jsonifier (two-stage) | 2162.93 | 0.653901 | 1155.97ms | 24579 | 30 | 150657 | 10837.3 | 2(Loss) |
| simdjson (reflection) | 1905.84 | 0.375212 | 1264.78ms | 24579 | 160 | 340743 | 12299.2 | 3(Loss) |
| simdjson (ondemand) | 1522.58 | 0.389943 | 1615.13ms | 24579 | 160 | 576624 | 15395.2 | 4(Loss) |
| glaze | 1406.78 | 1.47271 | 1783.96ms | 24579 | 160 | 9.63452e+06 | 16662.4 | 5(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2698.02 | 0.481395 | 1130.16ms | 24579 | 640 | 1.1195e+06 | 8688 | 1(Win) |
| jsonifier (two-stage) | 2631.15 | 0.281847 | 1186.9ms | 24579 | 80 | 50437.8 | 8908.8 | 2(Loss) |
| simdjson (reflection) | 2110.53 | 0.601596 | 1491.14ms | 24579 | 320 | 1.42859e+06 | 11106.4 | 3(Loss) |
| simdjson (ondemand) | 1712.28 | 0.562561 | 1916.83ms | 24579 | 80 | 474472 | 13689.6 | 4(Loss) |
| glaze | 1606.26 | 0.161026 | 1692.68ms | 24579 | 2560 | 1.41359e+06 | 14593.1 | 5(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6887.74 | 0.873051 | 361.846ms | 24579 | 640 | 564981 | 3403.2 | 1(Win) |
| glaze | 2761.59 | 0.562299 | 893.69ms | 24579 | 320 | 728947 | 8488 | 2(Loss) |
| simdjson (reflection) | 163.16 | 0.203843 | 7762.16ms | 24893 | 320 | 2.81492e+07 | 145500 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7163.92 | 0.337493 | 347.048ms | 24579 | 2560 | 312173 | 3272 | 1(Win) |
| glaze | 3162.83 | 0.381497 | 763.261ms | 24579 | 640 | 511612 | 7411.2 | 2(Loss) |
| simdjson (reflection) | 162.769 | 0.428636 | 7845.37ms | 24893 | 80 | 3.12664e+07 | 145850 | 3(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 773.657 | 0.72302 | 152.789ms | 1181 | 2560 | 283624 | 1455.8 | 1(Win) |
| jsonifier (two-stage) | 636.298 | 0.396064 | 187.759ms | 1181 | 4890 | 240336 | 1770.06 | 2(Loss) |
| glaze | 517.05 | 0.395568 | 238.243ms | 1181 | 2560 | 190072 | 2178.3 | 3(Loss) |
| simdjson (reflection) | 507.018 | 0.536323 | 232.991ms | 1181 | 1280 | 181684 | 2221.4 | 4(Loss) |
| simdjson (ondemand) | 453.71 | 0.829072 | 350.828ms | 1181 | 640 | 271087 | 2482.4 | 5(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 957.973 | 0.697596 | 136.66ms | 1181 | 2560 | 172203 | 1175.7 | 1(Win) |
| glaze | 846.834 | 1.05746 | 156.483ms | 1181 | 1280 | 253186 | 1330 | 2(Loss) |
| jsonifier (two-stage) | 761.634 | 0.544472 | 166.022ms | 1181 | 4890 | 317006 | 1478.78 | 3(Loss) |
| simdjson (ondemand) | 697.529 | 0.537415 | 187.037ms | 1181 | 4890 | 368217 | 1614.68 | 4(Loss) |
| simdjson (reflection) | 581.991 | 0.308295 | 214.85ms | 1181 | 4890 | 174064 | 1935.23 | 5(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2034.48 | 3.57709 | 59.3308ms | 1181 | 640 | 250975 | 553.6 | 1(Win) |
| simdjson (reflection) | 966.184 | 0.525978 | 121.367ms | 1187 | 4890 | 185706 | 1171.63 | 2(Loss) |
| glaze | 900.671 | 1.0012 | 127.127ms | 1181 | 2560 | 401283 | 1250.5 | 3(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2218.38 | 1.4197 | 53.995ms | 1181 | 4890 | 254056 | 507.707 | 1(Win) |
| simdjson (reflection) | 1020.29 | 0.689351 | 115.525ms | 1187 | 2560 | 149753 | 1109.5 | 2(Loss) |
| glaze | 975.396 | 0.635206 | 118.653ms | 1181 | 2560 | 137723 | 1154.7 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1247.57 | 0.412444 | 215.041ms | 2496 | 2560 | 158536 | 1908 | 1(Win) |
| jsonifier | 1226.83 | 0.322732 | 203.586ms | 2496 | 4890 | 191740 | 1940.26 | 2(Loss) |
| simdjson (reflection) | 995.971 | 0.932388 | 268.502ms | 2496 | 640 | 317811 | 2390 | 3(Loss) |
| glaze STATISTICAL TIE | 907.154 | 2.13619 | 360.891ms | 2496 | 80 | 251360 | 2624 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 870.233 | 0.590053 | 274.565ms | 2496 | 4890 | 1.27382e+06 | 2735.33 | 4(Tie) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 1473.18 | 1.00174 | 193.515ms | 2496 | 1280 | 335347 | 1615.8 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1449.77 | 0.651126 | 194.823ms | 2496 | 2560 | 292592 | 1641.9 | 1(Tie) |
| glaze | 1369.87 | 0.419865 | 204.404ms | 2496 | 4890 | 260290 | 1737.66 | 3(Loss) |
| simdjson (ondemand) | 1265.62 | 0.642963 | 205.663ms | 2496 | 2560 | 374366 | 1880.8 | 4(Loss) |
| simdjson (reflection) | 1171.9 | 0.30176 | 272.943ms | 2496 | 1280 | 48088.1 | 2031.2 | 5(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3462.97 | 1.00101 | 73.6722ms | 2496 | 4890 | 231514 | 687.378 | 1(Win) |
| glaze | 1257.82 | 2.59186 | 217.891ms | 2507 | 40 | 97085.7 | 1900.8 | 2(Loss) |
| simdjson (reflection) | 89.3855 | 0.445333 | 2741.13ms | 2502 | 160 | 2.26116e+06 | 26694.4 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3772.72 | 1.1349 | 66.092ms | 2496 | 4890 | 250728 | 630.943 | 1(Win) |
| glaze | 1417.56 | 0.875281 | 172.702ms | 2507 | 1280 | 278952 | 1686.6 | 2(Loss) |
| simdjson (reflection) | 89.7068 | 0.215381 | 3359.79ms | 2502 | 1280 | 4.20094e+06 | 26598.8 | 3(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1428.16 | 0.452806 | 345.542ms | 4926 | 1280 | 283967 | 3289.4 | 1(Win) |
| jsonifier (two-stage) | 916.394 | 0.901467 | 585.935ms | 4926 | 80 | 170850 | 5126.4 | 2(Loss) |
| simdjson (reflection) | 770.232 | 0.887676 | 696.689ms | 4926 | 40 | 117251 | 6099.2 | 3(Loss) |
| glaze | 720.102 | 0.36991 | 740.723ms | 4926 | 1280 | 745422 | 6523.8 | 4(Loss) |
| simdjson (ondemand) | 617.092 | 0.317867 | 905.486ms | 4926 | 1280 | 749529 | 7612.8 | 5(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1906.73 | 0.497665 | 340.368ms | 4926 | 2560 | 384880 | 2463.8 | 1(Win) |
| jsonifier (two-stage) | 1163.28 | 0.851195 | 574.012ms | 4926 | 80 | 94529.5 | 4038.4 | 2(Loss) |
| glaze | 939.46 | 0.474272 | 657.073ms | 4926 | 30 | 16873.6 | 5000.53 | 3(Loss) |
| simdjson (reflection) | 851.544 | 0.546796 | 647.45ms | 4926 | 640 | 582378 | 5516.8 | 4(Loss) |
| simdjson (ondemand) | 760.063 | 0.449705 | 757.644ms | 4926 | 320 | 247226 | 6180.8 | 5(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9573.81 | 1.51699 | 51.2079ms | 4926 | 4890 | 270953 | 490.693 | 1(Win) |
| simdjson (reflection) | 7958.33 | 1.65717 | 62.7958ms | 4926 | 2560 | 244973 | 590.3 | 2(Loss) |
| glaze | 1609.54 | 0.32732 | 330.85ms | 4926 | 4890 | 446310 | 2918.71 | 3(Loss) |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10618.9 | 3.15589 | 53.5112ms | 4926 | 1280 | 249508 | 442.4 | 1(Win) |
| simdjson (reflection) | 8342.81 | 1.2915 | 59.936ms | 4926 | 4890 | 258621 | 563.095 | 2(Loss) |
| glaze | 1930.71 | 0.892667 | 250.211ms | 4926 | 640 | 301936 | 2433.2 | 3(Loss) |
### Random Small Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.15711318328282578%)


----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2393.8 | 0.481137 | 471.472ms | 9463 | 640 | 210571 | 3770 | 1(Win) |
| jsonifier (two-stage) | 1793.48 | 0.202099 | 669.361ms | 9463 | 4890 | 505706 | 5031.89 | 2(Loss) |
| simdjson (reflection) | 1530.92 | 0.184647 | 675.282ms | 9463 | 4890 | 579361 | 5894.91 | 3(Loss) |
| glaze | 1441.86 | 0.171425 | 756.846ms | 9463 | 4890 | 562946 | 6259.02 | 4(Loss) |
| simdjson (ondemand) | 1340.4 | 1.06605 | 803.108ms | 9463 | 80 | 412130 | 6732.8 | 5(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13224.8 | 1.36032 | 72.031ms | 9463 | 2560 | 220599 | 682.4 | 1(Win) |
| glaze | 2219.53 | 0.368671 | 424.427ms | 9463 | 640 | 143811 | 4066 | 2(Loss) |
| simdjson (reflection) | 295.172 | 0.153427 | 3201.45ms | 9463 | 2560 | 5.63316e+06 | 30574.1 | 3(Loss) |
### Random Small Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 3.296019680398727%)


----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 3324.25 | 1.04037 | 84.342ms | 2821 | 2560 | 181482 | 809.3 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3301.8 | 0.739339 | 102.555ms | 2821 | 4890 | 177460 | 814.802 | 1(Tie) |
| simdjson (reflection) | 2786.16 | 1.23176 | 129.839ms | 2821 | 320 | 45268.5 | 965.6 | 3(Loss) |
| simdjson (ondemand) | 2686.02 | 0.812555 | 102.656ms | 2821 | 80 | 5298.88 | 1001.6 | 4(Loss) |
| glaze | 2046.18 | 1.43429 | 156.12ms | 2821 | 640 | 227599 | 1314.8 | 5(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3566.17 | 3.21819 | 110.034ms | 2821 | 320 | 188616 | 754.4 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3426.28 | 2.09965 | 83.703ms | 2821 | 640 | 173954 | 785.2 | 1(Tie) |
| simdjson (ondemand) | 2825.07 | 0.691616 | 100.055ms | 2821 | 2560 | 111050 | 952.3 | 3(Loss) |
| simdjson (reflection) | 2705.19 | 0.605528 | 111.931ms | 2821 | 2560 | 92836.4 | 994.5 | 4(Loss) |
| glaze | 2219.73 | 1.36696 | 132.958ms | 2821 | 640 | 175670 | 1212 | 5(Loss) |
### Twitter Partial Small Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 1.2030863541651085%)


----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4157.35 | 1.01036 | 124.911ms | 4147 | 2560 | 236497 | 951.3 | 1(Win) |
| jsonifier (two-stage) | 3961.23 | 1.42843 | 118.587ms | 4147 | 30 | 6101.63 | 998.4 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 3510.76 | 0.463518 | 119.313ms | 4147 | 4890 | 133324 | 1126.5 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3470.28 | 0.494232 | 138.733ms | 4147 | 4890 | 155135 | 1139.64 | 3(Tie) |
| glaze | 2877.96 | 1.18941 | 153.925ms | 4147 | 1280 | 341960 | 1374.2 | 5(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2030.73 | 5.65868 | 165.757ms | 2821 | 40 | 224797 | 1324.8 | 1(Win) |
| glaze | 1593.79 | 0.944136 | 182.536ms | 2821 | 1280 | 325105 | 1688 | 2(Loss) |
| jsonifier (two-stage) | 1508.87 | 0.573961 | 182.571ms | 2821 | 2560 | 268107 | 1783 | 3(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1170.94 | 0.322191 | 280.071ms | 2821 | 4890 | 267960 | 2297.56 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1167.09 | 0.317365 | 246.284ms | 2821 | 4890 | 261714 | 2305.15 | 4(Tie) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2545.16 | 0.420631 | 126.072ms | 2821 | 4890 | 96669.6 | 1057.03 | 1(Win) |
| jsonifier (two-stage) | 1848 | 0.532762 | 183.787ms | 2821 | 4890 | 294155 | 1455.8 | 2(Loss) |
| glaze | 1738.83 | 1.83928 | 199.382ms | 2821 | 320 | 259142 | 1547.2 | 3(Loss) |
| simdjson (reflection) | 1338.73 | 1.26377 | 238.217ms | 2821 | 80 | 51599.2 | 2009.6 | 4(Loss) |
| simdjson (ondemand) | 1238.18 | 1.99932 | 306.948ms | 2821 | 80 | 150971 | 2172.8 | 5(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9843.82 | 3.23491 | 30.9791ms | 2821 | 2560 | 200099 | 273.3 | 1(Win) |
| simdjson (reflection) | 6944.49 | 1.80623 | 40.9129ms | 2821 | 4890 | 239431 | 387.403 | 2(Loss) |
| glaze | 2992.24 | 0.545978 | 93.462ms | 2819 | 4890 | 117668 | 898.461 | 3(Loss) |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11247.1 | 3.53645 | 26.9952ms | 2821 | 2560 | 183188 | 239.2 | 1(Win) |
| simdjson (reflection) | 7693.21 | 2.70584 | 36.8709ms | 2821 | 2560 | 229211 | 349.7 | 2(Loss) |
| glaze | 3459.73 | 0.777133 | 81.61ms | 2819 | 4890 | 178322 | 777.057 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2157.96 | 0.658082 | 209.603ms | 4147 | 2560 | 372377 | 1832.7 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 1906.52 | 2.14211 | 223.249ms | 4147 | 320 | 631857 | 2074.4 | 2(Tie) |
| glaze STATISTICAL TIE | 1886.15 | 0.933489 | 301.397ms | 4147 | 640 | 245195 | 2096.8 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 1643.49 | 1.65863 | 249.382ms | 4147 | 160 | 254890 | 2406.4 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1604.94 | 0.598182 | 276.716ms | 4147 | 1280 | 278118 | 2464.2 | 4(Tie) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2587.14 | 0.610171 | 231.894ms | 4147 | 4890 | 425441 | 1528.67 | 1(Win) |
| jsonifier (two-stage) | 2465.33 | 0.876265 | 184.984ms | 4147 | 1280 | 252929 | 1604.2 | 2(Loss) |
| glaze | 2198.81 | 0.365615 | 203.019ms | 4147 | 4890 | 211470 | 1798.65 | 3(Loss) |
| simdjson (ondemand) | 1697.44 | 0.339827 | 261.872ms | 4147 | 4890 | 306553 | 2329.91 | 4(Loss) |
| simdjson (reflection) | 594.184 | 1.49815 | 381.293ms | 4147 | 30 | 298302 | 6656 | 5(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11839 | 2.02738 | 45.8222ms | 4147 | 4890 | 224294 | 334.056 | 1(Win) |
| glaze | 2597.23 | 1.00513 | 160.908ms | 4145 | 1280 | 299558 | 1522 | 2(Loss) |
| simdjson (reflection) | 333.757 | 0.565086 | 1223.18ms | 4147 | 80 | 358696 | 11849.6 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13572 | 4.37739 | 33.2078ms | 4147 | 1280 | 208266 | 291.4 | 1(Win) |
| glaze | 3657.63 | 0.441933 | 117.881ms | 4145 | 4890 | 111551 | 1080.75 | 2(Loss) |
| simdjson (reflection) | 323.948 | 0.386722 | 1217.38ms | 4147 | 1280 | 2.85316e+06 | 12208.4 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2064.46 | 0.407136 | 6351.6ms | 466906 | 80 | 6.16901e+07 | 215686 | 1(Win) |
| glaze | 1440.9 | 0.801813 | 8905.36ms | 466906 | 30 | 1.84187e+08 | 309026 | 2(Loss) |
| simdjson (ondemand) | 791.743 | 0.267872 | 7812.3ms | 466906 | 40 | 9.07831e+07 | 562400 | 3(Loss) |
### Minify Test Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 0.18343077596581073%)


----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2900.46 | 0.45663 | 6801.02ms | 699405 | 30 | 3.30805e+07 | 229965 | 1(Win) |
| glaze | 1977.49 | 0.293494 | 9608.77ms | 699405 | 40 | 3.92002e+07 | 337299 | 2(Loss) |
| simdjson (ondemand) | 577.987 | 1.23193 | 8638.62ms | 767297 | 40 | 9.73023e+09 | 1.26604e+06 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2661.83 | 0.891427 | 6419.21ms | 699405 | 1280 | 6.38673e+09 | 250581 | 1(Win) |
| glaze | 1853.34 | 1.12785 | 9491.77ms | 699405 | 160 | 2.63615e+09 | 359893 | 2(Loss) |
| simdjson (ondemand) | 585.076 | 1.19779 | 8599.89ms | 767297 | 40 | 8.97683e+09 | 1.25069e+06 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1918.86 | 0.278268 | 8441.04ms | 631514 | 80 | 6.10231e+07 | 313862 | 1(Win) |
| glaze | 1733.85 | 0.283217 | 9383.55ms | 631514 | 40 | 3.87118e+07 | 347354 | 2(Loss) |
