# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the Clang 23.1.0 compiler).  

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
| Glaze (utf8-validation) | `NEON64` |
| Glaze (string-escape) | `NEON` |
| Glaze (float-write) | `NEON` |
| Glaze (structural-skip) | `NEON64` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Apple M1 (Virtual)-NEON): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 5.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` (simdjson 5's C++26 static-reflection API) is absent from these results because this compiler does not provide P2996 reflection.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1124.39 | 0.159532 | 101.354ms | 905 | 320 | 479.853 | 767.594 | 1(Win) |
| jsonifier | 1066.84 | 0.0536148 | 84.4804ms | 905 | 2560 | 481.626 | 809.002 | 2(Loss) |
| jsonifier (two-stage) | 240.866 | 0.0981642 | 367.469ms | 905 | 2560 | 31673.3 | 3583.22 | 3(Loss) |
| simdjson (ondemand) | 182.745 | 0.0547724 | 518.962ms | 905 | 80 | 535.328 | 4722.84 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1239.07 | 0.0937318 | 71.302ms | 905 | 1280 | 545.616 | 696.549 | 1(Win) |
| jsonifier | 1131.71 | 0.148703 | 80.0778ms | 905 | 320 | 411.545 | 762.628 | 2(Loss) |
| jsonifier (two-stage) | 241.034 | 0.219467 | 366.71ms | 905 | 640 | 39524.1 | 3580.73 | 3(Loss) |
| simdjson (ondemand) | 182.218 | 0.0536352 | 478.848ms | 905 | 80 | 516.304 | 4736.5 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1449.22 | 0.0741067 | 64.334ms | 905 | 2560 | 498.633 | 595.543 | 1(Win) |
| glaze | 119.85 | 0.0837695 | 727.893ms | 905 | 30 | 1091.72 | 7201.27 | 2(Loss) |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1961.67 | 0.133467 | 54.9604ms | 905 | 1280 | 441.37 | 439.97 | 1(Win) |
| glaze | 668.445 | 0.142753 | 144.162ms | 905 | 2560 | 8697.18 | 1291.17 | 2(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 860.446 | 0.0369865 | 204.971ms | 1811 | 640 | 352.742 | 2007.22 | 1(Win) |
| glaze | 756.068 | 0.128535 | 220.715ms | 1811 | 40 | 344.84 | 2284.32 | 2(Loss) |
| jsonifier (two-stage) | 274.014 | 0.0964409 | 634.051ms | 1811 | 2560 | 94591.8 | 6302.98 | 3(Loss) |
| simdjson (ondemand) | 167.781 | 1.90894 | 1144.81ms | 1811 | 40 | 1.54454e+06 | 10293.8 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1030.46 | 0.166824 | 172.007ms | 1811 | 40 | 312.715 | 1676.05 | 1(Win) |
| glaze | 968.3 | 0.130308 | 181.959ms | 1811 | 4890 | 26416.1 | 1783.65 | 2(Loss) |
| jsonifier (two-stage) | 293.003 | 0.839904 | 642.25ms | 1811 | 640 | 1.56867e+06 | 5894.49 | 3(Loss) |
| simdjson (ondemand) | 191.735 | 0.0412221 | 909.563ms | 1811 | 80 | 1103.03 | 9007.79 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 265.761 | 0.564503 | 692.725ms | 1811 | 160 | 215332 | 6498.72 | 1(Win) |
| glaze | 198.184 | 0.0462314 | 875.624ms | 1798 | 80 | 1279.99 | 8652.1 | 2(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 827.911 | 0.164303 | 223.459ms | 1811 | 30 | 352.438 | 2086.1 | 1(Win) |
| glaze | 626.05 | 0.0526339 | 293.48ms | 1798 | 320 | 665.032 | 2738.93 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2077.05 | 0.0492536 | 185.5ms | 3862 | 640 | 488.186 | 1773.23 | 1(Win) |
| glaze | 1271.74 | 0.0722032 | 294.946ms | 3862 | 160 | 699.622 | 2896.11 | 2(Loss) |
| jsonifier (two-stage) | 612.588 | 0.216195 | 605.015ms | 3862 | 640 | 108133 | 6012.35 | 3(Loss) |
| simdjson (ondemand) | 453.165 | 0.189641 | 899.535ms | 3862 | 640 | 152039 | 8127.48 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2532.79 | 0.12084 | 150.117ms | 3862 | 80 | 247.024 | 1454.16 | 1(Win) |
| glaze | 1461.26 | 0.115725 | 256.658ms | 3862 | 2560 | 21780.3 | 2520.49 | 2(Loss) |
| jsonifier (two-stage) | 629.359 | 0.0716983 | 594.35ms | 3862 | 40 | 704.215 | 5852.12 | 3(Loss) |
| simdjson (ondemand) | 470.169 | 0.194885 | 795.988ms | 3862 | 320 | 74580 | 7833.55 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2614.74 | 0.302789 | 147.153ms | 3862 | 2560 | 46568.1 | 1408.59 | 1(Win) |
| glaze | 482.864 | 0.0849091 | 776.56ms | 3862 | 80 | 3355.64 | 7627.6 | 2(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3416.32 | 0.143207 | 119.642ms | 3862 | 80 | 190.688 | 1078.09 | 1(Win) |
| glaze | 2101.03 | 0.105278 | 194.596ms | 3862 | 640 | 2179.81 | 1752.99 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1161.03 | 0.0686404 | 808.676ms | 9578 | 2560 | 74655.5 | 7867.39 | 1(Win) |
| glaze | 922.656 | 0.111716 | 875.12ms | 9578 | 30 | 3669.66 | 9900 | 2(Loss) |
| simdjson (ondemand) | 821.863 | 0.0606951 | 1116.48ms | 9578 | 80 | 3640.39 | 11114.1 | 3(Loss) |
| jsonifier (two-stage) | 652.899 | 0.0617491 | 1404.5ms | 9578 | 30 | 2238.93 | 13990.4 | 4(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2078.65 | 0.168465 | 742.448ms | 9578 | 30 | 1644.09 | 4394.33 | 1(Win) |
| glaze | 1636.9 | 0.0511171 | 822.136ms | 9578 | 80 | 650.924 | 5580.25 | 2(Loss) |
| simdjson (ondemand) | 1182.07 | 0.187292 | 1118.69ms | 9578 | 160 | 33513.9 | 7727.38 | 3(Loss) |
| jsonifier (two-stage) | 866.364 | 0.0512508 | 1396.17ms | 9578 | 4890 | 142778 | 10543.3 | 4(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1088.37 | 0.0926109 | 844.749ms | 9578 | 80 | 4832.96 | 8392.66 | 1(Win) |
| glaze | 1043.77 | 0.130541 | 883.29ms | 9578 | 640 | 83524.6 | 8751.26 | 2(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6347.65 | 0.256348 | 159.89ms | 9578 | 4890 | 66541.3 | 1439 | 1(Win) |
| glaze | 4419.83 | 0.0916054 | 222.278ms | 9578 | 160 | 573.458 | 2066.66 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2011.9 | 0.0359754 | 186.589ms | 3873 | 640 | 279.173 | 1835.87 | 1(Win) |
| glaze | 1372.35 | 0.0767424 | 267.063ms | 3873 | 160 | 682.586 | 2691.43 | 2(Loss) |
| jsonifier (two-stage) | 593.697 | 0.0942808 | 628.233ms | 3873 | 2560 | 88075 | 6221.32 | 3(Loss) |
| simdjson (ondemand) | 448.387 | 0.0681571 | 833.994ms | 3873 | 40 | 1260.87 | 8237.48 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2450.55 | 0.11363 | 154.396ms | 3873 | 4890 | 14343.8 | 1507.24 | 1(Win) |
| glaze | 1645.83 | 0.0322247 | 229.088ms | 3873 | 1280 | 669.441 | 2244.2 | 2(Loss) |
| jsonifier (two-stage) | 616.206 | 0.0518875 | 608.557ms | 3873 | 4890 | 47301.9 | 5994.07 | 3(Loss) |
| simdjson (ondemand) | 462.661 | 0.0593917 | 828.748ms | 3873 | 30 | 674.437 | 7983.33 | 4(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2972.87 | 0.149979 | 128.298ms | 3873 | 2560 | 8888.84 | 1242.43 | 1(Win) |
| glaze | 493.48 | 0.0861098 | 761.403ms | 3873 | 30 | 1246.19 | 7484.77 | 2(Loss) |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3206.21 | 0.192141 | 127.733ms | 3873 | 4890 | 23958.6 | 1152.01 | 1(Win) |
| glaze | 2201.02 | 0.0658601 | 187.738ms | 3873 | 320 | 390.879 | 1678.12 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 726.971 | 0.0709471 | 8745.43ms | 2090234 | 40 | 1.51386e+08 | 2.74207e+06 | 1(Win) |
| jsonifier (two-stage) | 645.396 | 0.0769066 | 9736.86ms | 2090234 | 30 | 1.69272e+08 | 3.08865e+06 | 2(Loss) |
| glaze | 525.435 | 0.347267 | 5745.58ms | 2090234 | 30 | 5.20715e+09 | 3.79382e+06 | 3(Loss) |
| simdjson (ondemand) | 441.425 | 0.206347 | 6851.9ms | 2090234 | 80 | 6.94646e+09 | 4.51583e+06 | 4(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 907.024 | 0.520697 | 8672.58ms | 2090234 | 40 | 5.23819e+09 | 2.19774e+06 | 1(Win) |
| jsonifier (two-stage) | 787.192 | 0.0870045 | 9750.81ms | 2090234 | 160 | 7.76662e+08 | 2.5323e+06 | 2(Loss) |
| glaze | 619.782 | 0.116268 | 6223.03ms | 2090234 | 30 | 4.19519e+08 | 3.2163e+06 | 3(Loss) |
| simdjson (ondemand) | 505.239 | 0.0965938 | 6819.33ms | 2090234 | 80 | 1.16194e+09 | 3.94546e+06 | 4(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2467.84 | 0.114606 | 5275.36ms | 2090234 | 40 | 3.42791e+07 | 807752 | 1(Win) |
| glaze | 1447.38 | 0.421853 | 8083.32ms | 2090234 | 40 | 1.35022e+09 | 1.37725e+06 | 2(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2464.93 | 0.0785098 | 5159.75ms | 2090234 | 320 | 1.28996e+08 | 808705 | 1(Win) |
| glaze | 1662.82 | 0.127902 | 8279.05ms | 2090234 | 30 | 7.05297e+07 | 1.19881e+06 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1847.88 | 0.252925 | 5173.61ms | 6661897 | 40 | 3.02477e+09 | 3.43815e+06 | 1(Win) |
| jsonifier (two-stage) | 1721.76 | 0.10293 | 5553.86ms | 6661897 | 30 | 4.32769e+08 | 3.68999e+06 | 2(Loss) |
| glaze | 1332.54 | 0.0877608 | 7306.79ms | 6661897 | 30 | 5.25241e+08 | 4.7678e+06 | 3(Loss) |
| simdjson (ondemand) | 1315.47 | 0.0673084 | 7560.79ms | 6661897 | 30 | 3.17024e+08 | 4.82966e+06 | 4(Loss) |
### Canada Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 0.194742%)


----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6613.68 | 0.235509 | 6569.66ms | 6661897 | 80 | 4.09461e+08 | 960626 | 1(Win) |
| glaze | 3030.19 | 0.107394 | 6623.91ms | 6661897 | 160 | 8.11221e+08 | 2.09666e+06 | 2(Loss) |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6690.42 | 0.0825911 | 6013.05ms | 6661897 | 80 | 4.92091e+07 | 949609 | 1(Win) |
| glaze | 3349.02 | 0.261365 | 5997.38ms | 6661897 | 160 | 3.93349e+09 | 1.89706e+06 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2077.85 | 0.112481 | 6025.21ms | 500299 | 80 | 5.33684e+06 | 229623 | 1(Win) |
| jsonifier (two-stage) | 1391.05 | 0.0561945 | 8805.76ms | 500299 | 640 | 2.37763e+07 | 342995 | 2(Loss) |
| glaze | 1169.3 | 0.11716 | 5348.1ms | 500299 | 160 | 3.65671e+07 | 408041 | 3(Loss) |
| simdjson (ondemand) | 980.54 | 0.119708 | 6321.82ms | 500299 | 640 | 2.17148e+08 | 486592 | 4(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2587.16 | 0.178392 | 5866.44ms | 500299 | 80 | 8.65872e+06 | 184419 | 1(Win) |
| jsonifier (two-stage) | 1604.76 | 0.127686 | 9207.11ms | 500299 | 1280 | 1.84475e+08 | 297316 | 2(Loss) |
| glaze | 1319.74 | 0.105744 | 5123.74ms | 500299 | 160 | 2.33836e+07 | 361528 | 3(Loss) |
| simdjson (ondemand) | 1077.15 | 0.0828469 | 6211.87ms | 500299 | 320 | 4.30937e+07 | 442951 | 4(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7828.35 | 0.0501222 | 6184.02ms | 500299 | 4890 | 4.5634e+06 | 60948 | 1(Win) |
| glaze | 1855.01 | 0.0524772 | 6582.08ms | 500299 | 1280 | 2.33194e+07 | 257207 | 2(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7943.66 | 0.0491615 | 6064.07ms | 500299 | 2560 | 2.23207e+06 | 60063.3 | 1(Win) |
| glaze | 1952.73 | 0.0659933 | 6320.5ms | 500299 | 1280 | 3.32802e+07 | 244337 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3669.68 | 0.190587 | 5468.03ms | 1439562 | 30 | 1.52515e+07 | 374112 | 1(Win) |
| jsonifier (two-stage) | 3103.78 | 0.398549 | 5618.8ms | 1439562 | 30 | 9.32316e+07 | 442322 | 2(Loss) |
| simdjson (ondemand) | 2342.68 | 0.0763679 | 7602.23ms | 1439562 | 320 | 6.40926e+07 | 586028 | 3(Loss) |
| glaze | 2009.22 | 0.622287 | 8064.44ms | 1439562 | 30 | 5.42385e+08 | 683286 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4182.19 | 0.189751 | 9573.16ms | 1439562 | 30 | 1.16398e+07 | 328267 | 1(Win) |
| jsonifier (two-stage) | 3539.58 | 0.0804857 | 5627.64ms | 1439562 | 160 | 1.55925e+07 | 387863 | 2(Loss) |
| simdjson (ondemand) | 2517.18 | 0.0950602 | 7396.17ms | 1439562 | 320 | 8.60158e+07 | 545401 | 3(Loss) |
| glaze | 2379.06 | 0.0737387 | 7968.56ms | 1439562 | 640 | 1.15883e+08 | 577065 | 4(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 18464.3 | 0.110868 | 7484.21ms | 1439562 | 640 | 4.34898e+06 | 74352.8 | 1(Win) |
| glaze | 2927.54 | 0.172036 | 6083.26ms | 1439584 | 30 | 1.95267e+07 | 468959 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 18661.3 | 0.0369894 | 7938.99ms | 1439562 | 30 | 22215.3 | 73568 | 1(Win) |
| glaze | 3257.38 | 0.0732268 | 5465.79ms | 1439584 | 640 | 6.09617e+07 | 421472 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2357.14 | 0.0401508 | 2298.83ms | 56369 | 40 | 3353.95 | 22806.3 | 1(Win) |
| glaze | 1468.01 | 0.0516532 | 3748.77ms | 56369 | 4890 | 1.74954e+06 | 36619.3 | 2(Loss) |
| simdjson (ondemand) | 1274.67 | 0.124982 | 4241.52ms | 56369 | 160 | 444527 | 42173.7 | 3(Loss) |
| jsonifier (two-stage) | 1186.22 | 0.115712 | 4562.01ms | 56369 | 320 | 879944 | 45318.4 | 4(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2982.22 | 0.028015 | 2020.12ms | 56369 | 80 | 2040.2 | 18026.1 | 1(Win) |
| glaze | 1810.18 | 0.0705672 | 3125.48ms | 56369 | 2560 | 1.12431e+06 | 29697.5 | 2(Loss) |
| jsonifier (two-stage) | 1558 | 0.141845 | 4281.78ms | 56369 | 160 | 383259 | 34504.2 | 3(Loss) |
| simdjson (ondemand) | 1503.08 | 0.24788 | 3767.63ms | 56369 | 80 | 628772 | 35765.1 | 4(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11024.8 | 0.0889737 | 494.158ms | 56369 | 40 | 752.869 | 4876.05 | 1(Win) |
| glaze | 2565.65 | 0.106896 | 2120.23ms | 56369 | 1280 | 642131 | 20952.9 | 2(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 11533.7 | 0.0651146 | 474.047ms | 56369 | 80 | 736.866 | 4660.91 | 1(Win) |
| glaze | 2884.8 | 0.0657351 | 1873.14ms | 56369 | 30 | 4501.56 | 18634.8 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2530.13 | 0.0594214 | 3674.31ms | 94370 | 4890 | 2.18463e+06 | 35570.6 | 1(Win) |
| glaze | 2052.25 | 0.134072 | 4515.17ms | 94370 | 160 | 553102 | 43853.4 | 2(Loss) |
| simdjson (ondemand) | 1996 | 0.146566 | 4705.89ms | 94370 | 160 | 698773 | 45089.3 | 3(Loss) |
| jsonifier (two-stage) | 1776.48 | 0.100138 | 5385.18ms | 94370 | 30 | 77208.5 | 50661.1 | 4(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2937.52 | 0.0219512 | 3229.54ms | 94370 | 80 | 3618.38 | 30637.5 | 1(Win) |
| glaze | 2375.51 | 0.0656586 | 3945.33ms | 94370 | 80 | 49502.7 | 37885.9 | 2(Loss) |
| simdjson (ondemand) | 2337.53 | 0.043637 | 4059.77ms | 94370 | 30 | 8468.03 | 38501.4 | 3(Loss) |
| jsonifier (two-stage) | 2298.09 | 0.0602922 | 4794.78ms | 94370 | 4890 | 2.72626e+06 | 39162.2 | 4(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16543.3 | 0.0606283 | 554.147ms | 94370 | 80 | 870.29 | 5440.16 | 1(Win) |
| glaze | 2648.28 | 0.133406 | 3483.26ms | 94370 | 320 | 657725 | 33983.7 | 2(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16721.2 | 0.102648 | 542.014ms | 94370 | 4890 | 149261 | 5382.29 | 1(Win) |
| glaze | 2991.08 | 0.118332 | 3038.55ms | 94370 | 30 | 38031.2 | 30088.8 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2194.66 | 0.084282 | 523.57ms | 11812 | 80 | 1497.17 | 5132.81 | 1(Win) |
| jsonifier (two-stage) | 1149.03 | 0.0788179 | 990.406ms | 11812 | 4890 | 291972 | 9803.72 | 2(Loss) |
| glaze | 973.331 | 0.0644926 | 1201.22ms | 11812 | 4890 | 272430 | 11573.5 | 3(Loss) |
| simdjson (ondemand) | 871.793 | 0.333108 | 1222.83ms | 11812 | 1280 | 2.37138e+06 | 12921.4 | 4(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2339.19 | 0.0751637 | 512.595ms | 11812 | 40 | 524.071 | 4815.68 | 1(Win) |
| jsonifier (two-stage) | 1318.17 | 0.0364125 | 975.453ms | 11812 | 80 | 774.635 | 8545.81 | 2(Loss) |
| glaze | 1036.47 | 0.105885 | 1132.84ms | 11812 | 1280 | 169518 | 10868.4 | 3(Loss) |
| simdjson (ondemand) | 1022.4 | 0.0641088 | 1132.54ms | 11812 | 2560 | 127727 | 11018 | 4(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8186.35 | 0.0399314 | 142.671ms | 11812 | 320 | 96.6154 | 1376.05 | 1(Win) |
| glaze | 1599.31 | 0.0742309 | 712.319ms | 11812 | 2560 | 69983.1 | 7043.56 | 2(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8527.94 | 0.0425443 | 137.086ms | 11812 | 1280 | 404.251 | 1320.93 | 1(Win) |
| glaze | 1740.58 | 0.0657225 | 655.256ms | 11812 | 80 | 1447.36 | 6471.86 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3354.83 | 0.0470712 | 959.737ms | 31235 | 30 | 524.051 | 8879.13 | 1(Win) |
| simdjson (ondemand) | 2221.61 | 0.0324305 | 1360.7ms | 31235 | 80 | 1512.68 | 13408.3 | 2(Loss) |
| jsonifier (two-stage) | 2139.15 | 0.0391275 | 1403.76ms | 31235 | 30 | 890.602 | 13925.1 | 3(Loss) |
| glaze | 1966.51 | 0.0341014 | 1551.97ms | 31235 | 160 | 4269.29 | 15147.7 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3494.58 | 0.0814817 | 885.918ms | 31235 | 2560 | 123496 | 8524.07 | 1(Win) |
| jsonifier (two-stage) | 2632.7 | 0.0347722 | 1396.62ms | 31235 | 40 | 619.163 | 11314.6 | 2(Loss) |
| simdjson (ondemand) | 2340.65 | 0.0512841 | 1372.52ms | 31235 | 30 | 1277.9 | 12726.4 | 3(Loss) |
| glaze | 2066.82 | 0.0575223 | 1482.58ms | 31235 | 30 | 2061.91 | 14412.5 | 4(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17608.1 | 0.193068 | 173.252ms | 31235 | 40 | 426.717 | 1691.72 | 1(Win) |
| glaze | 2723.48 | 0.0717179 | 1102.06ms | 31235 | 80 | 4922.46 | 10937.5 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 19819 | 0.0452803 | 156.075ms | 31235 | 320 | 148.213 | 1503 | 1(Win) |
| glaze | 2989.89 | 0.0600436 | 1002.55ms | 31235 | 4890 | 174991 | 9962.92 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1431.48 | 1.35137 | 6581.02ms | 108313 | 4890 | 4.64995e+09 | 72159.9 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1419.86 | 0.857404 | 5383.53ms | 108313 | 160 | 6.22529e+07 | 72750.3 | 1(Tie) |
| glaze | 1285.08 | 1.02358 | 8779.57ms | 108313 | 30 | 2.03079e+07 | 80380.5 | 3(Loss) |
| simdjson (ondemand) | 1009.16 | 1.61727 | 6543.63ms | 108313 | 80 | 2.19228e+08 | 102358 | 4(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1521.86 | 0.928421 | 5045.29ms | 108313 | 160 | 6.35361e+07 | 67874.2 | 1(Win) |
| glaze STATISTICAL TIE | 1377.92 | 0.906536 | 8531.5ms | 108313 | 40 | 1.84732e+07 | 74964.6 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1339.87 | 1.35787 | 5909.89ms | 108313 | 1280 | 1.4027e+09 | 77093.8 | 2(Tie) |
| simdjson (ondemand) | 1075.2 | 1.28841 | 6262.4ms | 108313 | 30 | 4.59635e+07 | 96070.8 | 4(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10926 | 1.72258 | 1369.37ms | 108313 | 40 | 1.06087e+06 | 9454.12 | 1(Win) |
| glaze | 1422.56 | 0.67618 | 8154ms | 108313 | 1280 | 3.08573e+08 | 72612.5 | 2(Loss) |
### Instruments Test (Minified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 1.050792%)

### Instruments Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 1.647277%)


----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2573.07 | 0.841809 | 5040.35ms | 213963 | 30 | 1.33698e+07 | 79302.7 | 1(Win) |
| jsonifier (two-stage) | 2281.65 | 1.18428 | 5311.6ms | 213963 | 640 | 7.17907e+08 | 89431.2 | 2(Loss) |
| simdjson (ondemand) | 1917.58 | 0.841254 | 7981.09ms | 213963 | 80 | 6.41081e+07 | 106410 | 3(Loss) |
| glaze | 1624.4 | 1.18067 | 7221.15ms | 213963 | 1280 | 2.8155e+09 | 125616 | 4(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17323.5 | 0.72585 | 1193.61ms | 213963 | 2560 | 1.87128e+07 | 11778.9 | 1(Win) |
| glaze | 1738.36 | 0.575148 | 6846.25ms | 213963 | 640 | 2.91699e+08 | 117381 | 2(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 18218.3 | 0.388268 | 1233.09ms | 213963 | 640 | 1.21033e+06 | 11200.3 | 1(Win) |
| glaze | 1675.6 | 1.35401 | 6059.63ms | 213963 | 640 | 1.74005e+09 | 121778 | 2(Loss) |
### Marine IK Reverse Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 4.710660%)
- glaze (RSE 2.732343%)

### Marine IK Reverse Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 1.043126%)
- jsonifier (RSE 0.257848%)


----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1343.45 | 0.514533 | 8385.51ms | 1834197 | 160 | 7.18118e+09 | 1.30204e+06 | 1(Win) |
| glaze | 754.345 | 0.642792 | 7827.95ms | 1833577 | 30 | 6.6607e+09 | 2.31808e+06 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1475.65 | 0.199252 | 7692.47ms | 1834197 | 160 | 8.92581e+08 | 1.18539e+06 | 1(Win) |
| glaze | 691.515 | 0.450344 | 7506.44ms | 1833577 | 160 | 2.07493e+10 | 2.5287e+06 | 2(Loss) |
### Marine IK Reverse Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 0.329152%)
- glaze (RSE 0.210728%)


----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2486.2 | 0.64876 | 6713.04ms | 9930848 | 30 | 1.83228e+10 | 3.80935e+06 | 1(Win) |
| jsonifier (two-stage) | 2295.95 | 0.689095 | 7029.2ms | 9930848 | 40 | 3.23195e+10 | 4.125e+06 | 2(Loss) |
| glaze | 1868.51 | 1.04008 | 8847.52ms | 9930848 | 30 | 8.33749e+10 | 5.06864e+06 | 3(Loss) |
| simdjson (ondemand) | 1802.84 | 0.955636 | 8723.43ms | 9930848 | 30 | 7.56077e+10 | 5.25327e+06 | 4(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5549.25 | 1.38146 | 6172.49ms | 9930848 | 30 | 1.66765e+10 | 1.70668e+06 | 1(Win) |
| glaze | 2579.57 | 0.506482 | 5583.26ms | 9930228 | 30 | 1.03723e+10 | 3.67123e+06 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5514.08 | 0.361967 | 5224.21ms | 9930848 | 160 | 6.18422e+09 | 1.71757e+06 | 1(Win) |
| glaze | 2756.55 | 1.09556 | 5154.06ms | 9930228 | 80 | 1.13332e+11 | 3.43553e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 596.711 | 0.505256 | 9363.11ms | 1834197 | 40 | 8.77499e+09 | 2.93145e+06 | 1(Win) |
| jsonifier (two-stage) | 558.43 | 0.571256 | 5303.48ms | 1834197 | 30 | 9.60589e+09 | 3.1324e+06 | 2(Loss) |
| glaze | 413.806 | 1.21682 | 6438.14ms | 1834197 | 30 | 7.93729e+10 | 4.22717e+06 | 3(Loss) |
| simdjson (ondemand) | 363.225 | 0.582449 | 7640.74ms | 1834197 | 40 | 3.14714e+10 | 4.81582e+06 | 4(Loss) |
### Marine IK Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 4.724029%)


----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1334.79 | 0.411808 | 8504.85ms | 1834197 | 160 | 4.65989e+09 | 1.31049e+06 | 1(Win) |
| glaze | 730.822 | 0.839098 | 7588.96ms | 1833577 | 40 | 1.61236e+10 | 2.3927e+06 | 2(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1353.32 | 0.293385 | 8791.91ms | 1834197 | 320 | 4.60167e+09 | 1.29254e+06 | 1(Win) |
| glaze | 710.296 | 0.298804 | 7423.53ms | 1833577 | 80 | 4.32894e+09 | 2.46184e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2423.45 | 0.70636 | 6094.45ms | 9930848 | 30 | 2.28602e+10 | 3.90799e+06 | 1(Win) |
| jsonifier (two-stage) | 2031.61 | 0.354031 | 7179.21ms | 9930848 | 40 | 1.08952e+10 | 4.66171e+06 | 2(Loss) |
| glaze | 1658.72 | 0.816043 | 8803.74ms | 9930848 | 30 | 6.51289e+10 | 5.7097e+06 | 3(Loss) |
| simdjson (ondemand) | 1605.16 | 0.46374 | 8945.66ms | 9930848 | 40 | 2.99465e+10 | 5.90023e+06 | 4(Loss) |
### Marine IK Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 3.084779%)


----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4815.32 | 2.52684 | 6086.57ms | 9930848 | 160 | 3.95183e+11 | 1.96681e+06 | 1(Win) |
| glaze | 2655.48 | 0.36754 | 5524.57ms | 9930228 | 80 | 1.37446e+10 | 3.56629e+06 | 2(Loss) |

----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3705.56 | 3.65321 | 8512.31ms | 9930848 | 160 | 1.39487e+12 | 2.55583e+06 | 1(Win) |
| glaze | 3000.5 | 0.461731 | 11053.7ms | 9930228 | 30 | 6.37133e+09 | 3.15621e+06 | 2(Loss) |
### Mesh Test (Minified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 3.978336%)


----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1039.06 | 1.21029 | 8282.73ms | 642697 | 80 | 4.0776e+09 | 589883 | 1(Tie) |
| glaze STATISTICAL TIE | 1022.3 | 0.383762 | 9579.8ms | 642697 | 640 | 3.38809e+09 | 599551 | 1(Tie) |
| jsonifier (two-stage) | 936.043 | 0.216879 | 9224.8ms | 642697 | 320 | 6.45364e+08 | 654803 | 3(Loss) |
| simdjson (ondemand) | 776.814 | 1.55116 | 6581.48ms | 642697 | 40 | 5.99172e+09 | 789023 | 4(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2598.4 | 0.211798 | 6503.67ms | 642697 | 1280 | 3.1949e+08 | 235885 | 1(Win) |
| glaze | 1110.91 | 0.488011 | 8358.72ms | 642692 | 40 | 2.89977e+08 | 551725 | 2(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2257.27 | 1.0465 | 6662.73ms | 642697 | 30 | 2.42241e+08 | 271533 | 1(Win) |
| glaze | 1115.86 | 0.475317 | 7768.72ms | 642692 | 80 | 5.45308e+08 | 549279 | 2(Loss) |
### Mesh Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 0.770707%)


----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 1746.69 | 0.657635 | 9739.75ms | 1225964 | 40 | 7.75093e+08 | 669364 | 1(Win) |
| jsonifier (two-stage) | 1620.95 | 0.122321 | 5023.73ms | 1225964 | 80 | 6.22743e+07 | 721286 | 2(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1429.55 | 0.523653 | 5484.7ms | 1225964 | 30 | 5.50256e+08 | 817858 | 3(Tie) |
| jsonifier STATISTICAL TIE | 1428.7 | 0.589032 | 6108.92ms | 1225964 | 80 | 1.85884e+09 | 818346 | 3(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5034.95 | 0.0851959 | 6002.73ms | 1225964 | 320 | 1.25243e+07 | 232211 | 1(Win) |
| glaze | 1772.1 | 0.179786 | 8644.34ms | 1225970 | 640 | 9.00481e+08 | 659768 | 2(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5009.2 | 0.093608 | 6181.19ms | 1225964 | 1280 | 6.11018e+07 | 233405 | 1(Win) |
| glaze | 1836.91 | 0.06783 | 8286.56ms | 1225970 | 320 | 5.96452e+07 | 636489 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1629.73 | 1.4131 | 6736.34ms | 409725 | 160 | 1.83663e+09 | 239760 | 1(Win) |
| glaze | 998.618 | 0.152715 | 5222.52ms | 409725 | 80 | 2.85653e+07 | 391285 | 2(Loss) |
| jsonifier (two-stage) | 831.148 | 0.869555 | 6940.11ms | 409725 | 80 | 1.33694e+09 | 470126 | 3(Loss) |
| simdjson (ondemand) | 695.939 | 1.63193 | 8821.1ms | 409725 | 40 | 3.35822e+09 | 561464 | 4(Loss) |
### Random Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 1.432877%)


----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8434.27 | 0.851039 | 5278.88ms | 409725 | 80 | 1.2436e+07 | 46328.2 | 1(Win) |
| glaze | 1448.49 | 0.671758 | 6632.64ms | 409725 | 1280 | 4.20329e+09 | 269760 | 2(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8164.96 | 0.472467 | 5518.28ms | 409725 | 640 | 3.2719e+07 | 47856.2 | 1(Win) |
| glaze | 1785.71 | 0.233206 | 6097.9ms | 409725 | 1280 | 3.33316e+08 | 218818 | 2(Loss) |
### Random Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 1.199357%)

### Random Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (ondemand) (RSE 1.021342%)


----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14714.8 | 0.64989 | 5122.53ms | 785750 | 30 | 3.28596e+06 | 50925 | 1(Win) |
| glaze | 2323.55 | 0.295587 | 9393.56ms | 785750 | 80 | 7.26984e+07 | 322502 | 2(Loss) |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14818.9 | 0.16679 | 5154.24ms | 785750 | 4890 | 3.47843e+07 | 50567.1 | 1(Win) |
| glaze | 2564.97 | 0.197859 | 8306.37ms | 785750 | 160 | 5.34612e+07 | 292148 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 3972.51 | 0.0602319 | 6611.1ms | 264040 | 1280 | 1.86583e+06 | 63387.6 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 3950.92 | 0.501978 | 7553.77ms | 264040 | 320 | 3.27538e+07 | 63734.1 | 1(Tie) |
| simdjson (ondemand) | 3369.74 | 0.0115773 | 7573.53ms | 264040 | 30 | 2245.35 | 74726.4 | 3(Loss) |
| glaze | 2111.97 | 0.18957 | 6539.76ms | 264040 | 40 | 2.04344e+06 | 119229 | 4(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 4114.39 | 0.14403 | 6855.64ms | 264040 | 320 | 2.48649e+06 | 61201.9 | 1(Tie) |
| jsonifier STATISTICAL TIE | 4113.23 | 0.0748782 | 6366.69ms | 264040 | 640 | 1.34482e+06 | 61219.1 | 1(Tie) |
| simdjson (ondemand) | 3452.9 | 0.0496184 | 7560.4ms | 264040 | 2560 | 3.35195e+06 | 72926.6 | 3(Loss) |
| glaze | 2160.85 | 0.0393201 | 6348.19ms | 264040 | 2560 | 5.37476e+06 | 116532 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4766.98 | 0.0319281 | 8318.78ms | 399947 | 4890 | 3.19136e+06 | 80012.8 | 1(Win) |
| jsonifier (two-stage) | 4742.47 | 0.0541521 | 8500.21ms | 399947 | 4890 | 9.27547e+06 | 80426.3 | 2(Loss) |
| simdjson (ondemand) | 4283.56 | 0.0874218 | 10035ms | 399947 | 640 | 3.87807e+06 | 89042.6 | 3(Loss) |
| glaze | 2948.76 | 0.153406 | 7340.34ms | 399947 | 160 | 6.29989e+06 | 129349 | 4(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 4900.24 | 0.0436672 | 8245.77ms | 399947 | 2560 | 2.95748e+06 | 77836.9 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 4879.48 | 0.291314 | 8136.87ms | 399947 | 30 | 1.55561e+06 | 78168 | 1(Tie) |
| simdjson (ondemand) | 4003.33 | 0.387013 | 5238.62ms | 399947 | 1280 | 1.74029e+08 | 95275.4 | 3(Loss) |
| glaze | 3012.16 | 0.0705121 | 7024.53ms | 399947 | 640 | 5.10217e+06 | 126626 | 4(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1911.57 | 0.570372 | 7749.01ms | 264040 | 80 | 4.51613e+07 | 131729 | 1(Win) |
| glaze | 1427.22 | 0.228289 | 9854.26ms | 264040 | 2560 | 4.15307e+08 | 176433 | 2(Loss) |
| simdjson (ondemand) | 1289.28 | 1.40777 | 10365.2ms | 264040 | 80 | 6.04783e+08 | 195309 | 3(Loss) |
| jsonifier (two-stage) | 1177.48 | 3.10245 | 6071.66ms | 264040 | 80 | 3.5215e+09 | 213853 | 4(Loss) |
### Twitter Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 7.094630%)


----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9488.61 | 0.782283 | 2856.01ms | 264040 | 4890 | 2.10752e+08 | 26537.9 | 1(Win) |
| glaze | 2877.43 | 0.499048 | 9568.84ms | 263923 | 2560 | 4.8783e+08 | 87472.6 | 2(Loss) |
### Twitter Test (Minified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 1.191223%)

### Twitter Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 1.347404%)


----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 2556.34 | 1.03054 | 9473.12ms | 399947 | 320 | 7.56573e+08 | 149205 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 2540.57 | 0.616921 | 9313.99ms | 399947 | 80 | 6.86264e+07 | 150131 | 1(Tie) |
| simdjson (ondemand) | 2171.65 | 0.353719 | 5205.38ms | 399947 | 1280 | 4.94031e+08 | 175636 | 3(Loss) |
| glaze | 1642.23 | 3.28303 | 6770.5ms | 399947 | 640 | 3.72106e+10 | 232257 | 4(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17919.7 | 0.997917 | 2390.2ms | 399947 | 80 | 3.6093e+06 | 21284.9 | 1(Win) |
| glaze | 3193.42 | 1.43999 | 5894.21ms | 399830 | 40 | 1.18255e+08 | 119404 | 2(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16619.7 | 0.288845 | 2354.99ms | 399947 | 2560 | 1.12493e+07 | 22949.8 | 1(Win) |
| glaze | 4332.63 | 0.236892 | 10863ms | 399830 | 40 | 1.73863e+06 | 88008.3 | 2(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 715.357 | 0.0632268 | 717.392ms | 4630 | 80 | 1218.45 | 6172.46 | 1(Win) |
| jsonifier (two-stage) | 593.029 | 0.281619 | 732.307ms | 4630 | 640 | 281394 | 7445.7 | 2(Loss) |
| glaze | 402.651 | 0.334713 | 1102.81ms | 4630 | 80 | 107781 | 10966.1 | 3(Loss) |
| simdjson (ondemand) | 385.165 | 0.179536 | 1263.68ms | 4630 | 640 | 271113 | 11463.9 | 4(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 765.723 | 0.117792 | 733.612ms | 4630 | 1280 | 59055.3 | 5766.46 | 1(Win) |
| jsonifier | 746.146 | 0.389837 | 737.157ms | 4630 | 4890 | 2.60249e+06 | 5917.76 | 2(Loss) |
| glaze | 510.991 | 0.162879 | 1097.96ms | 4630 | 80 | 15847.3 | 8641.08 | 3(Loss) |
| simdjson (ondemand) | 457.192 | 0.146261 | 1211.26ms | 4630 | 640 | 127703 | 9657.89 | 4(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2245.14 | 0.436907 | 235.489ms | 4630 | 40 | 2953.34 | 1966.7 | 1(Win) |
| glaze | 1298.51 | 0.363286 | 362.34ms | 4630 | 2560 | 390672 | 3400.46 | 2(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2024.69 | 1.23854 | 239.381ms | 4630 | 4890 | 3.56759e+06 | 2180.83 | 1(Win) |
| glaze | 1312.75 | 1.00901 | 319.858ms | 4630 | 4890 | 5.63249e+06 | 3363.57 | 2(Loss) |
### Canada Small Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (RSE 2.674361%)


----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2138.65 | 0.092543 | 854.562ms | 14795 | 1280 | 47714.2 | 6597.43 | 1(Win) |
| jsonifier (two-stage) | 1828.77 | 0.247345 | 911.017ms | 14795 | 30 | 10925.5 | 7715.37 | 2(Loss) |
| simdjson (ondemand) | 1279.61 | 0.075866 | 1319.13ms | 14795 | 2560 | 179147 | 11026.5 | 3(Loss) |
| glaze | 1215.17 | 0.247718 | 1405.05ms | 14795 | 30 | 24819.4 | 11611.2 | 4(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6524.71 | 0.309807 | 214.654ms | 14795 | 80 | 3590.71 | 2162.49 | 1(Win) |
| glaze | 2980.44 | 0.153637 | 492.875ms | 14795 | 640 | 33856.6 | 4734.07 | 2(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5354.92 | 1.08688 | 243.598ms | 14795 | 80 | 65611.2 | 2634.89 | 1(Win) |
| glaze | 3334.84 | 0.126255 | 452.619ms | 14795 | 1280 | 36524.5 | 4230.97 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1285.65 | 0.150742 | 406.745ms | 5092 | 40 | 1296.75 | 3777.15 | 1(Win) |
| glaze | 889.863 | 0.0973563 | 555.942ms | 5092 | 1280 | 36130.1 | 5457.14 | 2(Loss) |
| jsonifier (two-stage) | 825.224 | 0.428681 | 591.06ms | 5092 | 2560 | 1.62908e+06 | 5884.6 | 3(Loss) |
| simdjson (ondemand) | 814.214 | 0.0673441 | 601.392ms | 5092 | 2560 | 41299 | 5964.17 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1811.15 | 0.131215 | 358.96ms | 5092 | 40 | 495.102 | 2681.22 | 1(Win) |
| jsonifier (two-stage) | 1254.36 | 0.249432 | 489.955ms | 5092 | 2560 | 238714 | 3871.39 | 2(Loss) |
| glaze | 1179.77 | 0.0736544 | 505.521ms | 5092 | 160 | 1470.63 | 4116.16 | 3(Loss) |
| simdjson (ondemand) | 963.385 | 0.100257 | 585.321ms | 5092 | 40 | 1021.56 | 5040.68 | 4(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7772.96 | 0.0928515 | 67.3611ms | 5092 | 160 | 53.8396 | 624.744 | 1(Win) |
| glaze | 1594.19 | 0.245391 | 315.125ms | 5092 | 640 | 35760 | 3046.14 | 2(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8354.6 | 0.251568 | 74.1835ms | 5092 | 40 | 85.5256 | 581.25 | 1(Win) |
| glaze | 1966.26 | 0.191091 | 257.59ms | 5092 | 40 | 890.922 | 2469.72 | 2(Loss) |
### CitmCatalog Small Test (Prettified) Read Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 1.496928%)


----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2837.55 | 0.13118 | 480.282ms | 11724 | 30 | 801.54 | 3940.33 | 1(Win) |
| jsonifier (two-stage) | 2637.74 | 0.0370113 | 529.373ms | 11724 | 320 | 787.601 | 4238.8 | 2(Loss) |
| simdjson (ondemand) | 2117.38 | 0.099538 | 601.753ms | 11724 | 30 | 828.809 | 5280.53 | 3(Loss) |
| glaze | 1747.96 | 0.579053 | 756.449ms | 11724 | 4890 | 6.70865e+06 | 6396.53 | 4(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 17308.9 | 0.136071 | 68.362ms | 11724 | 640 | 494.446 | 645.959 | 1(Win) |
| glaze | 2485.96 | 0.13601 | 459.82ms | 11746 | 1280 | 48077.8 | 4506.04 | 2(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 18854.7 | 0.171432 | 63.2994ms | 11724 | 320 | 330.712 | 593.003 | 1(Win) |
| glaze | 2870.32 | 0.0681957 | 436.168ms | 11746 | 160 | 1133.32 | 3902.65 | 2(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1985.13 | 0.084171 | 243.866ms | 4857 | 80 | 308.585 | 2333.35 | 1(Win) |
| glaze | 1308.99 | 0.369021 | 363.901ms | 4857 | 40 | 6820.66 | 3538.6 | 2(Loss) |
| jsonifier (two-stage) | 1159.63 | 0.0951096 | 404.2ms | 4857 | 1280 | 18473.9 | 3994.38 | 3(Loss) |
| simdjson (ondemand) | 1069.37 | 0.250109 | 446.423ms | 4857 | 4890 | 573917 | 4331.53 | 4(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2575.66 | 0.0502728 | 207.893ms | 4857 | 640 | 523.126 | 1798.37 | 1(Win) |
| glaze | 1808.99 | 0.0759437 | 272.132ms | 4857 | 1280 | 4840.11 | 2560.54 | 2(Loss) |
| simdjson (ondemand) | 1548.04 | 0.296402 | 317.187ms | 4857 | 80 | 6292.49 | 2992.16 | 3(Loss) |
| jsonifier (two-stage) | 1381.89 | 0.676231 | 490.903ms | 4857 | 640 | 328821 | 3351.93 | 4(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9737.44 | 0.119218 | 51.1328ms | 4857 | 4890 | 1572.67 | 475.689 | 1(Win) |
| glaze | 2320.23 | 0.175109 | 218.154ms | 4857 | 80 | 977.648 | 1996.35 | 2(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10888 | 0.117783 | 45.9618ms | 4857 | 1280 | 321.378 | 425.422 | 1(Win) |
| glaze | 2811.57 | 0.0439688 | 168.796ms | 4857 | 1280 | 671.64 | 1647.47 | 2(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2088.51 | 0.133391 | 342.937ms | 7376 | 30 | 605.541 | 3368.1 | 1(Win) |
| glaze | 1776.65 | 0.170505 | 442.365ms | 7376 | 40 | 1822.93 | 3959.3 | 2(Loss) |
| simdjson (ondemand) | 1753.54 | 0.14362 | 411.053ms | 7376 | 40 | 1327.69 | 4011.47 | 3(Loss) |
| jsonifier (two-stage) | 1612.78 | 0.122306 | 441.904ms | 7376 | 2560 | 72850.1 | 4361.61 | 4(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| glaze | 2280.23 | 0.0827563 | 332.834ms | 7376 | 4890 | 31871 | 3084.91 | 1(Win) |
| simdjson (ondemand) | 2260.43 | 0.110748 | 330.222ms | 7376 | 80 | 950.211 | 3111.94 | 2(Loss) |
| jsonifier (two-stage) | 2162.28 | 0.0628046 | 390.488ms | 7376 | 4890 | 20413.3 | 3253.19 | 3(Loss) |
| jsonifier | 1948.73 | 0.81226 | 380.815ms | 7376 | 4890 | 4.20374e+06 | 3609.68 | 4(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12886.5 | 0.562882 | 62.7434ms | 7376 | 30 | 283.223 | 545.867 | 1(Win) |
| glaze | 2592.05 | 0.0767376 | 281.015ms | 7376 | 4890 | 21207 | 2713.79 | 2(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15640.7 | 0.105869 | 48.4855ms | 7376 | 1280 | 290.189 | 449.744 | 1(Win) |
| glaze | 2899.05 | 0.048578 | 252.827ms | 7376 | 640 | 889.183 | 2426.42 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2091.85 | 0.120584 | 205.672ms | 4390 | 30 | 174.731 | 2001.4 | 1(Win) |
| jsonifier (two-stage) | 1125.83 | 0.06153 | 381.45ms | 4390 | 80 | 418.84 | 3718.71 | 2(Loss) |
| simdjson (ondemand) | 959.799 | 0.0648958 | 443.789ms | 4390 | 80 | 641.05 | 4361.99 | 3(Loss) |
| glaze | 929.309 | 0.471153 | 496.01ms | 4390 | 40 | 18021.6 | 4505.1 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2372.18 | 0.0464821 | 193.968ms | 4390 | 640 | 430.71 | 1764.89 | 1(Win) |
| jsonifier (two-stage) | 1271.8 | 0.0469583 | 372.714ms | 4390 | 160 | 382.327 | 3291.89 | 2(Loss) |
| simdjson (ondemand) | 1069.57 | 0.0544707 | 412.327ms | 4390 | 160 | 727.371 | 3914.31 | 3(Loss) |
| glaze | 895.852 | 0.508712 | 493.744ms | 4390 | 640 | 361727 | 4673.35 | 4(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6821.13 | 0.447519 | 66.1445ms | 4390 | 640 | 4828.57 | 613.773 | 1(Win) |
| glaze | 1572.45 | 0.0811762 | 276.721ms | 4390 | 160 | 747.396 | 2662.48 | 2(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8225.46 | 0.139162 | 54.6308ms | 4390 | 640 | 321.092 | 508.984 | 1(Win) |
| glaze | 1685.18 | 0.150419 | 256.444ms | 4390 | 80 | 1117.2 | 2484.38 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3201.63 | 0.0725603 | 356.129ms | 11521 | 80 | 496.05 | 3431.78 | 1(Win) |
| simdjson (ondemand) | 2208.48 | 0.0939456 | 533.887ms | 11521 | 40 | 873.792 | 4975.05 | 2(Loss) |
| jsonifier (two-stage) | 2072.31 | 0.0259631 | 539.804ms | 11521 | 320 | 606.365 | 5301.96 | 3(Loss) |
| glaze | 1887.89 | 0.0537453 | 592.335ms | 11521 | 80 | 782.702 | 5819.86 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3432.83 | 0.0704049 | 338.063ms | 11521 | 80 | 406.23 | 3200.65 | 1(Win) |
| jsonifier (two-stage) | 2597.4 | 0.0310693 | 536.366ms | 11521 | 320 | 552.733 | 4230.11 | 2(Loss) |
| simdjson (ondemand) | 2411.07 | 0.0893847 | 475.065ms | 11521 | 1280 | 21237.2 | 4557.01 | 3(Loss) |
| glaze | 2058.01 | 0.0899885 | 557.078ms | 11521 | 30 | 692.441 | 5338.8 | 4(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 16752.6 | 0.160935 | 81.3758ms | 11521 | 320 | 356.506 | 655.856 | 1(Win) |
| glaze | 2221.06 | 0.887384 | 496.334ms | 11521 | 160 | 308321 | 4946.86 | 2(Loss) |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 19205.2 | 0.0915056 | 60.7648ms | 11521 | 1280 | 350.793 | 572.101 | 1(Win) |
| glaze | 2762.26 | 0.355371 | 433.049ms | 11521 | 2560 | 511510 | 3977.64 | 2(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2630.56 | 0.209156 | 173.721ms | 4669 | 160 | 2005.44 | 1692.68 | 1(Win) |
| jsonifier (two-stage) | 1585.57 | 0.243095 | 322.234ms | 4669 | 30 | 1398.13 | 2808.27 | 2(Loss) |
| glaze | 1251.94 | 0.122389 | 377.963ms | 4669 | 1280 | 24253.5 | 3556.64 | 3(Loss) |
| simdjson (ondemand) | 1143.41 | 0.0757274 | 446.847ms | 4669 | 80 | 695.734 | 3894.25 | 4(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2978.74 | 0.0374231 | 163.052ms | 4669 | 1280 | 400.565 | 1494.83 | 1(Win) |
| jsonifier (two-stage) | 1751.88 | 0.208219 | 328.883ms | 4669 | 30 | 840.23 | 2541.67 | 2(Loss) |
| glaze | 1488.65 | 0.0918476 | 317.177ms | 4669 | 80 | 603.797 | 2991.11 | 3(Loss) |
| simdjson (ondemand) | 1407.35 | 0.17832 | 337.04ms | 4669 | 30 | 954.921 | 3163.9 | 4(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 12416.4 | 0.113459 | 39.5053ms | 4669 | 2560 | 423.812 | 358.615 | 1(Win) |
| glaze | 1694.91 | 0.143547 | 275.478ms | 4669 | 80 | 1137.71 | 2627.1 | 2(Loss) |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13521.7 | 0.105608 | 36.3618ms | 4669 | 1280 | 154.806 | 329.301 | 1(Win) |
| glaze | 1990.54 | 0.114942 | 227.924ms | 4669 | 2560 | 16924.2 | 2236.93 | 2(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3152.56 | 0.113902 | 288.786ms | 9249 | 40 | 406.246 | 2797.9 | 1(Win) |
| jsonifier (two-stage) | 2727.09 | 0.180098 | 328.026ms | 9249 | 1280 | 43433.1 | 3234.42 | 2(Loss) |
| simdjson (ondemand) | 2134.55 | 0.0777146 | 418.731ms | 9249 | 80 | 825.031 | 4132.26 | 3(Loss) |
| glaze | 2068.04 | 0.128048 | 434.074ms | 9249 | 30 | 894.833 | 4265.17 | 4(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3379.97 | 0.0485481 | 277.087ms | 9249 | 320 | 513.64 | 2609.65 | 1(Win) |
| jsonifier (two-stage) | 2936.87 | 0.0705433 | 328.909ms | 9249 | 160 | 718.212 | 3003.38 | 2(Loss) |
| simdjson (ondemand) | 2481.72 | 0.169971 | 380.925ms | 9249 | 30 | 1094.86 | 3554.2 | 3(Loss) |
| glaze | 2137.84 | 0.758782 | 424.435ms | 9249 | 320 | 313634 | 4125.91 | 4(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 22462 | 0.646691 | 47.5091ms | 9249 | 80 | 515.914 | 392.688 | 1(Win) |
| glaze | 2213.51 | 0.0712452 | 408.235ms | 9249 | 4890 | 39413.6 | 3984.86 | 2(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 25924.3 | 0.184213 | 37.4564ms | 9249 | 640 | 251.417 | 340.242 | 1(Win) |
| glaze | 2424.21 | 0.144166 | 373.366ms | 9249 | 40 | 1100.61 | 3638.53 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 606.675 | 0.15333 | 734.833ms | 4604 | 40 | 4925.77 | 7237.35 | 1(Win) |
| jsonifier (two-stage) | 518.589 | 0.111578 | 860.872ms | 4604 | 30 | 2677.33 | 8466.67 | 2(Loss) |
| glaze | 369.27 | 0.0592968 | 1221.93ms | 4604 | 30 | 1491.31 | 11890.3 | 3(Loss) |
| simdjson (ondemand) | 341.165 | 0.260241 | 1309.03ms | 4604 | 640 | 717920 | 12869.8 | 4(Loss) |
### Marine IK Reverse Small Test (Minified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- jsonifier (two-stage) (RSE 0.399910%)


----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1883.6 | 0.0554679 | 239.747ms | 4604 | 160 | 267.484 | 2331.03 | 1(Win) |
| glaze | 876.086 | 0.425441 | 512.81ms | 4604 | 320 | 145481 | 5011.74 | 2(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1934.72 | 0.170012 | 232.838ms | 4604 | 30 | 446.599 | 2269.43 | 1(Win) |
| glaze | 1022.77 | 0.0752299 | 435.111ms | 4604 | 160 | 1668.85 | 4292.97 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier STATISTICAL TIE | 1982.08 | 1.15835 | 1242.92ms | 24579 | 640 | 1.20101e+07 | 11826.1 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1978 | 0.379342 | 1521.91ms | 24579 | 160 | 323338 | 11850.5 | 1(Tie) |
| simdjson (ondemand) | 1595.5 | 0.0481696 | 1507.43ms | 24579 | 30 | 1502.46 | 14691.6 | 3(Loss) |
| glaze | 1266.31 | 0.531512 | 1994.7ms | 24579 | 1280 | 1.23904e+07 | 18510.8 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 2348.7 | 0.338337 | 1171.36ms | 24579 | 2560 | 2.91886e+06 | 9980.13 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2344.67 | 0.575683 | 1333.37ms | 24579 | 1280 | 4.23976e+06 | 9997.28 | 1(Tie) |
| simdjson (ondemand) | 1587.21 | 0.606344 | 1733.76ms | 24579 | 320 | 2.56594e+06 | 14768.3 | 3(Loss) |
| glaze | 1431.81 | 0.848922 | 1821.19ms | 24579 | 1280 | 2.47231e+07 | 16371.1 | 4(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 7422.63 | 0.114614 | 319.515ms | 24579 | 2560 | 33537.3 | 3157.96 | 1(Win) |
| glaze | 2638.01 | 0.884541 | 938.119ms | 24579 | 160 | 988399 | 8885.62 | 2(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8020.83 | 0.0752807 | 297.52ms | 24579 | 80 | 387.211 | 2922.44 | 1(Win) |
| glaze | 3498.3 | 0.0718087 | 783.349ms | 24579 | 80 | 1852.08 | 6700.5 | 2(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 656.76 | 0.124208 | 684.221ms | 4604 | 40 | 2758.15 | 6685.43 | 1(Win) |
| jsonifier (two-stage) | 544.407 | 0.144499 | 879.839ms | 4604 | 4890 | 664147 | 8065.13 | 2(Loss) |
| glaze | 376.097 | 0.138383 | 1337.2ms | 4604 | 80 | 20879.9 | 11674.4 | 3(Loss) |
| simdjson (ondemand) | 342.752 | 0.293579 | 1484.55ms | 4604 | 160 | 226299 | 12810.2 | 4(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 865.704 | 0.11677 | 664.902ms | 4604 | 4890 | 171514 | 5071.84 | 1(Win) |
| jsonifier (two-stage) | 700.49 | 0.11364 | 826.164ms | 4604 | 30 | 1522.13 | 6268.07 | 2(Loss) |
| glaze | 433.517 | 0.0888679 | 1169.71ms | 4604 | 40 | 3240.47 | 10128.1 | 3(Loss) |
| simdjson (ondemand) | 394.596 | 0.0441405 | 1411.05ms | 4604 | 80 | 1929.87 | 11127.1 | 4(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1659.45 | 0.447312 | 279.473ms | 4604 | 4890 | 684973 | 2645.89 | 1(Win) |
| glaze | 931.354 | 0.085851 | 516.427ms | 4604 | 320 | 5241.82 | 4714.34 | 2(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1790.08 | 0.389534 | 243.437ms | 4604 | 30 | 2738.65 | 2452.8 | 1(Win) |
| glaze | 1016.17 | 0.057786 | 439.199ms | 4604 | 4890 | 30485.5 | 4320.86 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2153.47 | 0.471152 | 1270ms | 24579 | 640 | 1.68327e+06 | 10884.9 | 1(Win) |
| jsonifier (two-stage) | 2034.6 | 0.769767 | 1230.39ms | 24579 | 80 | 629188 | 11520.9 | 2(Loss) |
| glaze STATISTICAL TIE | 1494.38 | 0.100988 | 1646.01ms | 24579 | 640 | 160594 | 15685.7 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1490.06 | 0.106821 | 1706.63ms | 24579 | 40 | 11295.3 | 15731.1 | 3(Tie) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2843.9 | 0.42415 | 1150.28ms | 24579 | 1280 | 1.56441e+06 | 8242.34 | 1(Win) |
| jsonifier (two-stage) | 2712.8 | 0.0589701 | 1143.2ms | 24579 | 80 | 2077.04 | 8640.64 | 2(Loss) |
| glaze | 1679.8 | 0.0350622 | 1622.29ms | 24579 | 80 | 1915.05 | 13954.2 | 3(Loss) |
| simdjson (ondemand) | 1569.23 | 0.454535 | 1906.37ms | 24579 | 640 | 2.95032e+06 | 14937.5 | 4(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6193.56 | 1.83385 | 398.405ms | 24579 | 30 | 144509 | 3784.63 | 1(Win) |
| glaze | 2471.75 | 1.99426 | 1253.64ms | 24579 | 30 | 1.07302e+06 | 9483.3 | 2(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 6703.41 | 0.358492 | 340.565ms | 24579 | 4890 | 768432 | 3496.78 | 1(Win) |
| glaze | 2969.75 | 0.896655 | 784.744ms | 24579 | 160 | 801419 | 7893.04 | 2(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 752.286 | 0.321508 | 165.078ms | 1181 | 2560 | 59314 | 1497.16 | 1(Win) |
| jsonifier (two-stage) | 627.191 | 0.203333 | 257.726ms | 1181 | 30 | 399.978 | 1795.77 | 2(Loss) |
| glaze | 482.681 | 0.225717 | 239.637ms | 1181 | 4890 | 135649 | 2333.4 | 3(Loss) |
| simdjson (ondemand) | 421.527 | 0.119694 | 315.231ms | 1181 | 2560 | 26183.9 | 2671.93 | 4(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 844.363 | 0.205285 | 160.898ms | 1181 | 4890 | 36666.2 | 1333.89 | 1(Win) |
| glaze | 829.98 | 0.179903 | 155.048ms | 1181 | 1280 | 7628.74 | 1357.01 | 2(Loss) |
| jsonifier (two-stage) | 702.365 | 1.12258 | 191.392ms | 1181 | 2560 | 829559 | 1603.57 | 3(Loss) |
| simdjson (ondemand) | 646.325 | 0.12456 | 202.258ms | 1181 | 320 | 1507.66 | 1742.61 | 4(Loss) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1846.26 | 0.679395 | 65.417ms | 1181 | 4890 | 83997.7 | 610.038 | 1(Win) |
| glaze | 914.168 | 0.157596 | 145.401ms | 1181 | 160 | 603.194 | 1232.04 | 2(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2329.77 | 1.34531 | 61.6884ms | 1181 | 30 | 1268.94 | 483.433 | 1(Win) |
| glaze | 869.505 | 0.618643 | 128.751ms | 1181 | 320 | 20548.8 | 1295.32 | 2(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 1182.79 | 0.198925 | 215.767ms | 2496 | 40 | 641.077 | 2012.5 | 1(Win) |
| jsonifier | 1053.9 | 0.895957 | 247.49ms | 2496 | 2560 | 1.04835e+06 | 2258.63 | 2(Loss) |
| simdjson (ondemand) | 936.564 | 0.157082 | 275.921ms | 2496 | 30 | 478.179 | 2541.6 | 3(Loss) |
| glaze | 839.633 | 1.13302 | 348.436ms | 2496 | 1280 | 1.32067e+06 | 2835.01 | 4(Loss) |
### Mesh Small Test (Prettified) Read (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- glaze (RSE 4.589161%)


----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 4377.74 | 0.302227 | 74.3459ms | 2496 | 160 | 432.091 | 543.744 | 1(Win) |
| glaze | 1384.13 | 0.161172 | 192.111ms | 2507 | 160 | 1240.09 | 1727.34 | 2(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 5092.25 | 0.600792 | 51.6911ms | 2496 | 40 | 315.485 | 467.45 | 1(Win) |
| glaze | 1634.06 | 0.589906 | 152.149ms | 2507 | 2560 | 190712 | 1463.14 | 2(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2007.49 | 0.284754 | 245.054ms | 4926 | 30 | 1332.12 | 2340.13 | 1(Win) |
| glaze STATISTICAL TIE | 859.797 | 0.386537 | 559.475ms | 4926 | 1280 | 570939 | 5463.85 | 2(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 848.164 | 1.19909 | 521.772ms | 4926 | 320 | 1.41151e+06 | 5538.78 | 2(Tie) |
| simdjson (ondemand) | 841.571 | 0.63687 | 668.832ms | 4926 | 1280 | 1.61778e+06 | 5582.18 | 4(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2257.21 | 0.271005 | 275.221ms | 4926 | 80 | 2544.99 | 2081.24 | 1(Win) |
| glaze | 1197.72 | 0.150743 | 485.979ms | 4926 | 30 | 1048.77 | 3922.3 | 2(Loss) |
| jsonifier (two-stage) | 1135.51 | 0.208594 | 519.673ms | 4926 | 4890 | 364183 | 4137.18 | 3(Loss) |
| simdjson (ondemand) | 995.519 | 0.306695 | 539.098ms | 4926 | 1280 | 268110 | 4718.95 | 4(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8763.27 | 0.152526 | 60.9978ms | 4926 | 320 | 213.941 | 536.078 | 1(Win) |
| glaze | 1470.61 | 0.232542 | 332.526ms | 4926 | 2560 | 141265 | 3194.45 | 2(Loss) |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 8947.98 | 0.593032 | 57.149ms | 4926 | 80 | 775.506 | 525.013 | 1(Win) |
| glaze | 1892.9 | 0.114986 | 295.579ms | 4926 | 80 | 651.504 | 2481.8 | 2(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2541.39 | 0.0889259 | 380.74ms | 9463 | 40 | 398.869 | 3551.05 | 1(Win) |
| glaze | 1599.66 | 0.179499 | 592.12ms | 9463 | 640 | 65630.9 | 5641.6 | 2(Loss) |
| simdjson (ondemand) | 1449.49 | 0.6908 | 812.526ms | 9463 | 160 | 295972 | 6226.06 | 3(Loss) |
| jsonifier (two-stage) | 1413.57 | 0.150229 | 642.783ms | 9463 | 2560 | 235489 | 6384.3 | 4(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2466.31 | 0.437216 | 424.276ms | 9463 | 1280 | 327616 | 3659.16 | 1(Win) |
| glaze | 1866.33 | 0.0752996 | 546.27ms | 9463 | 40 | 530.308 | 4835.5 | 2(Loss) |
| jsonifier (two-stage) | 1819.41 | 0.184293 | 659.173ms | 9463 | 2560 | 213921 | 4960.19 | 3(Loss) |
| simdjson (ondemand) | 1802.33 | 0.18307 | 630.879ms | 9463 | 40 | 3361.14 | 5007.2 | 4(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 14063.6 | 0.58426 | 82.701ms | 9463 | 80 | 1124.52 | 641.7 | 1(Win) |
| glaze | 2002.67 | 0.204375 | 453.922ms | 9463 | 4890 | 414766 | 4506.29 | 2(Loss) |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15811.3 | 0.33441 | 60.255ms | 9463 | 4890 | 17815.2 | 570.77 | 1(Win) |
| glaze | 2281.39 | 0.338053 | 415.259ms | 9463 | 4890 | 874459 | 3955.76 | 2(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 3373.88 | 0.0600006 | 93.4462ms | 2821 | 1280 | 293.001 | 797.395 | 1(Win) |
| jsonifier | 3149.51 | 0.452236 | 94.2139ms | 2821 | 30 | 447.683 | 854.2 | 2(Loss) |
| simdjson (ondemand) | 2838.03 | 0.472011 | 109.874ms | 2821 | 80 | 1601.64 | 947.95 | 3(Loss) |
| glaze | 1994.34 | 0.242655 | 148.351ms | 2821 | 80 | 857.189 | 1348.97 | 4(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 3504.5 | 0.428886 | 88.6342ms | 2821 | 40 | 433.61 | 767.675 | 1(Win) |
| jsonifier | 3344.14 | 0.141874 | 92.1657ms | 2821 | 1280 | 1667.46 | 804.487 | 2(Loss) |
| simdjson (ondemand) | 2702.88 | 0.893459 | 123.76ms | 2821 | 160 | 12653.8 | 995.35 | 3(Loss) |
| glaze | 1840.62 | 0.265808 | 149.175ms | 2821 | 2560 | 38641.3 | 1461.63 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) | 3825.49 | 0.344731 | 113.113ms | 4147 | 80 | 1016.12 | 1033.83 | 1(Win) |
| simdjson (ondemand) | 3628.05 | 0.405141 | 114.456ms | 4147 | 80 | 1560.36 | 1090.09 | 2(Loss) |
| jsonifier | 3332.15 | 0.527192 | 123.764ms | 4147 | 2560 | 100230 | 1186.89 | 3(Loss) |
| glaze | 2906.47 | 0.141126 | 152.526ms | 4147 | 160 | 590.027 | 1360.72 | 4(Loss) |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 3889.17 | 1.22645 | 108.91ms | 4147 | 4890 | 760615 | 1016.9 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 3877.96 | 0.341447 | 114.039ms | 4147 | 80 | 970.062 | 1019.84 | 1(Tie) |
| jsonifier | 3468.86 | 0.981937 | 106.333ms | 4147 | 160 | 20053.2 | 1140.11 | 3(Loss) |
| glaze | 2834.4 | 0.225759 | 150.094ms | 4147 | 160 | 1587.67 | 1395.32 | 4(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2068.63 | 0.264033 | 223.411ms | 2821 | 320 | 3773.16 | 1300.53 | 1(Win) |
| glaze | 1541 | 0.531957 | 181.771ms | 2821 | 320 | 27599.8 | 1745.83 | 2(Loss) |
| jsonifier (two-stage) STATISTICAL TIE | 1473.41 | 0.574925 | 193.308ms | 2821 | 2560 | 282113 | 1825.91 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1466 | 0.360386 | 189.337ms | 2821 | 640 | 27993.4 | 1835.14 | 3(Tie) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2666.78 | 0.23942 | 146.597ms | 2821 | 80 | 466.703 | 1008.83 | 1(Win) |
| jsonifier (two-stage) | 1934.83 | 0.14349 | 217.595ms | 2821 | 320 | 1273.84 | 1390.47 | 2(Loss) |
| simdjson (ondemand) | 1698.63 | 0.361161 | 174.017ms | 2821 | 80 | 2617.57 | 1583.81 | 3(Loss) |
| glaze | 642.279 | 0.296467 | 220.544ms | 2821 | 30 | 4626.29 | 4188.7 | 4(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 9268.43 | 0.479289 | 33.4535ms | 2821 | 30 | 58.0644 | 290.267 | 1(Win) |
| glaze | 2757.53 | 0.38988 | 115.841ms | 2819 | 30 | 433.444 | 974.933 | 2(Loss) |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 10781.2 | 0.518702 | 31.5787ms | 2821 | 640 | 1072.23 | 249.537 | 1(Win) |
| glaze | 3420.64 | 0.397756 | 85.9753ms | 2819 | 80 | 781.806 | 785.938 | 2(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 2176.96 | 0.208282 | 192.574ms | 4147 | 30 | 429.528 | 1816.7 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2167.41 | 0.273032 | 189.973ms | 4147 | 2560 | 63541.2 | 1824.71 | 1(Tie) |
| simdjson (ondemand) | 2048.63 | 0.734282 | 221.059ms | 4147 | 30 | 6028.19 | 1930.5 | 3(Loss) |
| glaze | 1973.43 | 0.514861 | 240.706ms | 4147 | 1280 | 136275 | 2004.07 | 4(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2579.41 | 0.324493 | 183.611ms | 4147 | 40 | 990.141 | 1533.25 | 1(Win) |
| jsonifier (two-stage) | 2554.18 | 0.103697 | 182.812ms | 4147 | 160 | 412.493 | 1548.4 | 2(Loss) |
| glaze STATISTICAL TIE | 2273.43 | 0.235191 | 206.218ms | 4147 | 80 | 1339.18 | 1739.61 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2256.85 | 0.573342 | 193.331ms | 4147 | 2560 | 258423 | 1752.39 | 3(Tie) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 13197.4 | 0.154844 | 34.6443ms | 4147 | 1280 | 275.605 | 299.671 | 1(Win) |
| glaze | 2923.72 | 0.181277 | 148.457ms | 4145 | 80 | 480.568 | 1352.04 | 2(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 15951.1 | 0.507205 | 29.3887ms | 4147 | 80 | 126.515 | 247.938 | 1(Win) |
| glaze | 3752.18 | 0.159059 | 120.466ms | 4145 | 2560 | 7188.52 | 1053.51 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2264.02 | 0.581415 | 5726.95ms | 466906 | 40 | 5.23035e+07 | 196675 | 1(Win) |
| glaze | 1537.19 | 0.327868 | 7485.63ms | 466906 | 320 | 2.88636e+08 | 289668 | 2(Loss) |
| simdjson (ondemand) | 687.356 | 1.38804 | 8365.15ms | 466906 | 320 | 2.58733e+10 | 647810 | 3(Loss) |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 2218.24 | 1.6689 | 5536.43ms | 466906 | 40 | 4.48914e+08 | 200734 | 1(Win) |
| glaze | 1496.92 | 0.467938 | 7986.68ms | 466906 | 640 | 1.23999e+09 | 297462 | 2(Loss) |
| simdjson (ondemand) | 783.875 | 0.300125 | 8685.47ms | 466906 | 40 | 1.1626e+08 | 568045 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3220.71 | 0.418083 | 5724.92ms | 699405 | 30 | 2.24905e+07 | 207099 | 1(Win) |
| glaze | 2198.11 | 0.289934 | 8309.13ms | 699405 | 40 | 3.09611e+07 | 303445 | 2(Loss) |
| simdjson (ondemand) | 589.758 | 1.01537 | 8311.2ms | 767297 | 30 | 4.76152e+09 | 1.24077e+06 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 3130.14 | 0.406337 | 5383.69ms | 699405 | 640 | 4.79826e+08 | 213091 | 1(Win) |
| glaze | 2184.98 | 0.303551 | 8253.69ms | 699405 | 80 | 6.86934e+07 | 305268 | 2(Loss) |
| simdjson (ondemand) | 513.676 | 0.783292 | 9229.8ms | 767297 | 80 | 9.96063e+09 | 1.42454e+06 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | -------- |
| jsonifier | 1715.89 | 0.747832 | 7718.05ms | 631514 | 160 | 1.10234e+09 | 350989 | 1(Win) |
| glaze | 1568.8 | 0.985969 | 5284.84ms | 631514 | 30 | 4.29812e+08 | 383897 | 2(Loss) |
