# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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
| simdjson (reflection) | `haswell` |
| Glaze (utf8-validation) | `AVX2` |
| Glaze (string-escape) | `AVX2` |
| Glaze (float-write) | `SSE4.1` |
| Glaze (structural-skip) | `AVX2` |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. Glaze reports per-subsystem backends, which may differ from one another within a single build.

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5% AND mean shift < 2.5%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" performs fused scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through structural indexing/stage-1 + stage-2. The 'partial' tests require stage-1 + stage-2, so both jsonifier rows take the two-stage path there)

Each test is run twice. In the standard run, every iteration constructs a new object to parse into, or a new string to serialize into, and destroys it again inside the timed region, so allocation and deallocation are part of each measurement. In the run labelled "(Reused)", the object or string is created once and held across iterations; it is cleared (keeping its capacity) outside the timed region before each iteration, so only the parse or serialize work is measured. Parser instances are reused in both.

The "Small" tests use cut-down copies of the large documents, truncated by `GenerateSmallJson.py` so that each minified document is at most 5 KiB (arrays and numerically-keyed objects are shortened to as many leading entries as fit; the document structure is otherwise unchanged). They exercise per-call overhead (setup, dispatch, small allocations) rather than bulk throughput, which is where the standard and "(Reused)" runs differ most.

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

`simdjson (reflection)` is simdjson 5's C++26 static-reflection API (`document.get<T>()` for reads, `simdjson::to_json` into a `std::string` for writes). Its single-pass writer emits minified JSON only (pretty output is a second FracturedJson reformatting pass), so it is absent from the prettified write tests.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [6196208](https://github.com/nihilai-collective/benchmarksuite/commit/6196208).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1579.5 | 0.0649142 | 784.085ms | 905 | 4890 | 615.244 | 546.424 | 3.44909 | 15.5083 | 3.05857 | 0.00372075 | 0.000150945 | 1.44618e-05 | 1(Win) |
| glaze | 776.745 | 0.0472634 | 846.289ms | 905 | 320 | 88.2551 | 1111.14 | 6.75519 | 18.6685 | 3.27735 | 0.00224793 | 0.00015884 | 1.38122e-05 | 2(Loss) |
| jsonifier (two-stage) | 260.235 | 0.100598 | 1062.49ms | 905 | 2560 | 28496.3 | 3316.53 | 19.3921 | 58.2431 | 8.36244 | 0.00510661 | 0.000222721 | 5.26588e-05 | 3(Loss) |
| simdjson (ondemand) | 179.54 | 0.0866737 | 1213.3ms | 905 | 320 | 5555.2 | 4807.15 | 28.3941 | 103.857 | 10.5691 | 0.0258909 | 0.000124309 | 1.03591e-05 | 4(Loss) |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1736.76 | 0.10032 | 777.636ms | 905 | 2560 | 636.256 | 496.946 | 3.15716 | 14.9293 | 2.94586 | 0.00229541 | 0.000154092 | 2.54662e-05 | 1(Win) |
| glaze | 720.693 | 0.0482698 | 847.153ms | 905 | 4890 | 1634.02 | 1197.56 | 7.24509 | 18.3127 | 3.16464 | 0.00119649 | 0.000167215 | 3.66064e-05 | 2(Loss) |
| jsonifier (two-stage) | 264.331 | 0.0464474 | 1057.16ms | 905 | 640 | 1471.99 | 3265.13 | 19.3635 | 57.6641 | 8.24973 | 0.00682838 | 0.000138122 | 1.72652e-05 | 3(Loss) |
| simdjson (ondemand) | 188.058 | 0.0842564 | 1186.16ms | 905 | 640 | 9569.69 | 4589.4 | 27.1713 | 103.506 | 10.4564 | 0.0346789 | 0.000189917 | 3.45304e-05 | 4(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1768.96 | 0.108092 | 774.956ms | 905 | 2560 | 712.012 | 487.899 | 3.09399 | 12.7635 | 1.41215 | 0.00388596 | 0.000113087 | 9.06423e-06 | 1(Win) |
| simdjson (reflection) | 252.459 | 0.0518629 | 1072.53ms | 905 | 4890 | 15372.2 | 3418.67 | 20.2674 | 95.1227 | 20.7646 | 0.0464744 | 0.000213538 | 1.78513e-05 | 2(Loss) |
| glaze | 203.275 | 0.0638558 | 1156.42ms | 905 | 4890 | 35945.2 | 4245.86 | 25.107 | 110.474 | 23.1426 | 0.0840602 | 0.000338949 | 9.80691e-05 | 3(Loss) |

----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 3105.49 | 0.338616 | 762.549ms | 905 | 4890 | 4330.72 | 277.919 | 1.86381 | 8.46961 | 1.05414 | 0.00111333 | 0.000106204 | 1.60436e-05 | 1(Win) |
| jsonifier | 2715.58 | 0.0864075 | 761.518ms | 905 | 4890 | 368.794 | 317.824 | 2.10587 | 10.0088 | 0.938122 | 0.00223006 | 6.34964e-05 | 4.97125e-06 | 2(Loss) |
| glaze | 669.628 | 0.0905246 | 865.294ms | 905 | 4890 | 6656.9 | 1288.89 | 7.79179 | 21.8309 | 3.36906 | 0.0023801 | 0.00015569 | 2.44043e-05 | 3(Loss) |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1138.46 | 0.122753 | 884.004ms | 1811 | 40 | 138.715 | 1517.05 | 4.56133 | 20.0624 | 4.06461 | 0.00073164 | 0 | 0 | 1(Win) |
| glaze | 971.234 | 0.105483 | 909.633ms | 1811 | 4890 | 17205.2 | 1778.26 | 5.32905 | 26.4429 | 4.12258 | 0.000626709 | 0.000155717 | 4.09901e-05 | 2(Loss) |
| jsonifier (two-stage) | 324.409 | 0.0569915 | 1269.67ms | 1811 | 4890 | 45017.4 | 5323.85 | 15.7094 | 44.0381 | 6.3534 | 0.000973487 | 0.000174236 | 5.93962e-05 | 3(Loss) |
| simdjson (ondemand) | 226.749 | 0.115428 | 1498.34ms | 1811 | 1280 | 98941.7 | 7616.8 | 22.1169 | 84.2258 | 11.1585 | 0.000602654 | 0.00012726 | 2.71777e-05 | 4(Loss) |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1239.31 | 0.0509573 | 869.422ms | 1811 | 4890 | 2466.04 | 1393.6 | 4.19882 | 18.9691 | 3.81336 | 0.000986925 | 8.84167e-05 | 1.8406e-05 | 1(Win) |
| glaze | 1049.38 | 0.0537808 | 896.064ms | 1811 | 4890 | 3831.24 | 1645.84 | 4.94851 | 25.7156 | 3.88625 | 0.00153899 | 0.000101516 | 2.38262e-05 | 2(Loss) |
| jsonifier (two-stage) | 330.752 | 0.125284 | 1257.43ms | 1811 | 640 | 27390.9 | 5221.75 | 15.4337 | 42.9542 | 6.10216 | 0.00097667 | 8.28272e-05 | 1.03534e-05 | 3(Loss) |
| simdjson (ondemand) | 231.769 | 0.0888875 | 1483.07ms | 1811 | 2560 | 112317 | 7451.83 | 21.7045 | 83.1552 | 10.9299 | 0.000988102 | 0.000143869 | 3.79625e-05 | 4(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 338.659 | 0.11444 | 1303.32ms | 1997 | 640 | 26507.2 | 5623.61 | 15.0355 | 64.6249 | 11.667 | 0.00401462 | 0.000268371 | 9.70205e-05 | 1(Win) |
| jsonifier | 326.354 | 0.108828 | 1250.51ms | 1811 | 40 | 1326.78 | 5292.12 | 15.3164 | 63.8609 | 11.3026 | 0.0100773 | 0.000207068 | 0.000165654 | 2(Loss) |
| glaze | 292.613 | 0.0954209 | 1328.05ms | 1798 | 1280 | 40021.2 | 5859.99 | 17.3943 | 70.8337 | 12.4633 | 0.0215761 | 0.00020422 | 5.77899e-05 | 3(Loss) |

----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 843.293 | 0.088758 | 942.094ms | 1811 | 640 | 2114.83 | 2048.05 | 6.11616 | 20.8962 | 1.47819 | 0.000707482 | 6.03948e-05 | 3.45113e-06 | 1(Win) |
| glaze | 731.041 | 0.109235 | 988.617ms | 1798 | 30 | 196.944 | 2345.57 | 7.0622 | 26.4833 | 2.36374 | 0.00124212 | 0.000333704 | 0 | 2(Loss) |
| simdjson (reflection) | 635.55 | 0.0539082 | 1052.08ms | 1997 | 2560 | 6680.46 | 2996.6 | 8.0079 | 25.3025 | 2.57887 | 0.00104199 | 9.60425e-05 | 1.8387e-05 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3363.36 | 0.0936422 | 842.885ms | 3862 | 2560 | 2691.91 | 1095.06 | 1.55749 | 7.56111 | 0.992233 | 0.000264496 | 8.16246e-05 | 1.81051e-05 | 1(Win) |
| glaze | 1747.17 | 0.0640619 | 945.526ms | 3862 | 4890 | 8917.88 | 2108.03 | 2.93472 | 14.4259 | 1.82315 | 0.000268041 | 8.01687e-05 | 2.24515e-05 | 2(Loss) |
| jsonifier (two-stage) | 820.383 | 0.0725111 | 1182.52ms | 3862 | 40 | 423.897 | 4489.48 | 6.22196 | 16.7592 | 2.1564 | 0.00091274 | 0.000258933 | 0.00013594 | 3(Loss) |
| simdjson (ondemand) | 516.392 | 0.0408204 | 1448.41ms | 3862 | 4890 | 41450.4 | 7132.35 | 9.82548 | 31.5319 | 3.3449 | 0.00512301 | 8.31869e-05 | 2.25044e-05 | 4(Loss) |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3651.37 | 0.0557224 | 832.096ms | 3862 | 320 | 101.093 | 1008.69 | 1.44472 | 7.11031 | 0.893061 | 0.000258933 | 4.77408e-05 | 1.4565e-05 | 1(Win) |
| glaze | 1845.51 | 0.0721677 | 931.828ms | 3862 | 4890 | 10143.5 | 1995.7 | 2.8041 | 14.1373 | 1.71182 | 0.00062557 | 5.63934e-05 | 1.12257e-05 | 2(Loss) |
| jsonifier (two-stage) | 838.62 | 0.0627995 | 1172.27ms | 3862 | 2560 | 19473.6 | 4391.85 | 6.08651 | 16.312 | 2.05515 | 0.000440793 | 8.55693e-05 | 1.99257e-05 | 3(Loss) |
| simdjson (ondemand) | 522.637 | 0.0598117 | 1441.55ms | 3862 | 160 | 2842.6 | 7047.12 | 9.73153 | 31.0678 | 3.24573 | 0.00627104 | 2.58933e-05 | 0 | 4(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 947.304 | 0.167401 | 1125.48ms | 3862 | 640 | 27110.9 | 3887.97 | 5.37942 | 26.8133 | 5.21595 | 0.00736058 | 0.000105596 | 2.22521e-05 | 1(Win) |
| jsonifier | 908.601 | 0.0697484 | 1143.38ms | 3862 | 1280 | 10231.9 | 4053.58 | 5.62576 | 25.9345 | 5.355 | 0.00889516 | 9.40656e-05 | 2.12406e-05 | 2(Loss) |
| glaze | 832.106 | 0.0664128 | 1183.81ms | 3862 | 80 | 691.291 | 4426.23 | 6.13371 | 29.1732 | 5.83195 | 0.00838296 | 4.855e-05 | 0 | 3(Loss) |

----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5250.29 | 0.0875591 | 829.123ms | 3862 | 2560 | 965.832 | 701.503 | 1.02305 | 5.50777 | 0.748576 | 0.000320632 | 4.0964e-05 | 4.14698e-06 | 1(Win) |
| simdjson (reflection) | 4113 | 0.0717495 | 829.096ms | 3862 | 40 | 16.5122 | 895.475 | 1.26365 | 6.49197 | 0.534179 | 0.000517866 | 3.23666e-05 | 0 | 2(Loss) |
| glaze | 2438.51 | 0.0515144 | 919.4ms | 3862 | 4890 | 2960.35 | 1510.39 | 2.11684 | 8.67452 | 1.15174 | 0.00555308 | 8.0963e-05 | 3.02883e-05 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1725.64 | 0.126347 | 1272.55ms | 9578 | 1280 | 57252 | 5293.29 | 2.94031 | 14.6956 | 2.72346 | 0.00133305 | 4.95928e-05 | 1.25613e-05 | 1(Win) |
| glaze | 1447.81 | 0.0742442 | 1375.76ms | 9578 | 4890 | 107291 | 6309.05 | 3.50456 | 17.7596 | 3.48591 | 0.00125402 | 3.73214e-05 | 1.20633e-05 | 2(Loss) |
| jsonifier (two-stage) | 1031.86 | 0.181493 | 1624.75ms | 9578 | 160 | 41299.8 | 8852.28 | 4.91823 | 19.0375 | 3.27615 | 0.00124047 | 4.04573e-05 | 1.30507e-05 | 3(Loss) |
| simdjson (ondemand) | 998.68 | 0.169555 | 1657.04ms | 9578 | 30 | 7215.07 | 9146.37 | 5.0855 | 19.1594 | 2.9195 | 0.0049906 | 5.2203e-05 | 2.08812e-05 | 4(Loss) |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2617.47 | 0.0864956 | 1235.87ms | 9578 | 4890 | 44553.6 | 3489.74 | 1.94965 | 10.7088 | 1.84496 | 0.000196941 | 3.66168e-05 | 1.11665e-05 | 1(Win) |
| glaze | 2019.77 | 0.0581656 | 1338.6ms | 9578 | 4890 | 33836.8 | 4522.45 | 2.52903 | 13.5916 | 2.54803 | 0.0001669 | 2.88878e-05 | 8.49766e-06 | 2(Loss) |
| jsonifier (two-stage) | 1293.58 | 0.0534826 | 1587.54ms | 9578 | 4890 | 69742.2 | 7061.24 | 3.92465 | 15.0793 | 2.41261 | 0.000160922 | 3.43109e-05 | 9.22359e-06 | 3(Loss) |
| simdjson (ondemand) | 1248.49 | 0.145317 | 1619.89ms | 9578 | 1280 | 144686 | 7316.28 | 4.03831 | 15.1109 | 2.03435 | 0.00354116 | 3.3361e-05 | 9.95119e-06 | 4(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3757.41 | 0.233021 | 981.35ms | 9578 | 160 | 5134.3 | 2431.01 | 1.3689 | 5.4739 | 1.11234 | 0.00200525 | 2.28388e-05 | 1.95761e-06 | 1(Win) |
| simdjson (reflection) | 3721.62 | 0.233072 | 984.416ms | 9578 | 320 | 10471.7 | 2454.39 | 1.37889 | 6.09846 | 1.12195 | 0.00046167 | 3.65421e-05 | 2.186e-05 | 2(Loss) |
| glaze | 1997.85 | 0.0716434 | 1192.72ms | 9578 | 1280 | 13733.7 | 4572.07 | 2.54506 | 12.7134 | 2.58561 | 0.0011284 | 7.41445e-05 | 3.7113e-05 | 3(Loss) |

----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11182.8 | 0.0737347 | 845.891ms | 9578 | 4890 | 1773.78 | 816.814 | 0.473491 | 2.36323 | 0.337544 | 0.00097279 | 7.33831e-05 | 4.53066e-05 | 1(Win) |
| simdjson (reflection) | 9445.77 | 0.165529 | 856.509ms | 9578 | 1280 | 3279.71 | 967.025 | 0.558914 | 3.02558 | 0.331698 | 0.00012439 | 4.82877e-05 | 2.77328e-05 | 2(Loss) |
| glaze | 6085.94 | 0.0662065 | 908.625ms | 9578 | 2560 | 2527.76 | 1500.88 | 0.854652 | 4.38192 | 0.677908 | 0.000170802 | 4.96336e-05 | 2.63054e-05 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3409.15 | 0.109452 | 839.707ms | 3873 | 1280 | 1799.96 | 1083.43 | 1.53902 | 7.37413 | 0.934676 | 0.000426228 | 4.37726e-05 | 2.21889e-06 | 1(Win) |
| glaze | 1916.06 | 0.126805 | 923.685ms | 3873 | 2560 | 15296.3 | 1927.69 | 2.68184 | 12.7152 | 1.79112 | 0.000268284 | 9.91439e-05 | 2.47103e-05 | 2(Loss) |
| jsonifier (two-stage) | 849.215 | 0.0362324 | 1166.75ms | 3873 | 4890 | 12144.1 | 4349.41 | 6.0103 | 16.5967 | 2.07256 | 0.00108575 | 0.000103543 | 2.80374e-05 | 3(Loss) |
| simdjson (ondemand) | 516.781 | 0.0448365 | 1450.58ms | 3873 | 1280 | 13144.8 | 7147.28 | 9.83553 | 31.1696 | 3.45753 | 0.0098797 | 0.00013979 | 5.12361e-05 | 4(Loss) |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3786.35 | 0.0497411 | 827.794ms | 3873 | 320 | 75.3417 | 975.5 | 1.39227 | 6.92667 | 0.835786 | 0.000472825 | 2.98541e-05 | 7.26181e-06 | 1(Win) |
| glaze | 2004.91 | 0.0813389 | 912.557ms | 3873 | 2560 | 5748.35 | 1842.27 | 2.57666 | 12.4772 | 1.69223 | 0.000522951 | 6.70709e-05 | 2.12811e-05 | 2(Loss) |
| jsonifier (two-stage) | 875.973 | 0.0621044 | 1155.66ms | 3873 | 2560 | 17554.9 | 4216.54 | 5.83641 | 16.1508 | 1.9716 | 0.00115907 | 8.85538e-05 | 2.44078e-05 | 3(Loss) |
| simdjson (ondemand) | 522.675 | 0.0611033 | 1437.83ms | 3873 | 320 | 5966.37 | 7066.68 | 9.73451 | 30.7069 | 3.35864 | 0.0145728 | 7.58456e-05 | 1.69442e-05 | 4(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 884.887 | 0.0491798 | 1149.19ms | 3873 | 4890 | 20606.4 | 4174.07 | 5.77528 | 27.1856 | 5.28841 | 0.0108881 | 8.80196e-05 | 2.65062e-05 | 1(Win) |
| glaze STATISTICAL TIE | 869.586 | 0.0698263 | 1158.79ms | 3873 | 4890 | 43014.7 | 4247.52 | 5.86392 | 28.7155 | 5.78182 | 0.00628788 | 0.000276361 | 0.000158509 | 2(Tie) |
| jsonifier STATISTICAL TIE | 869.371 | 0.146064 | 1165.42ms | 3873 | 30 | 1155.29 | 4248.57 | 5.87117 | 25.6096 | 5.23419 | 0.0105517 | 3.44264e-05 | 0 | 2(Tie) |

----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4456.24 | 0.129414 | 838.868ms | 3873 | 2560 | 2945.51 | 828.857 | 1.19586 | 5.38136 | 0.735347 | 0.000458704 | 5.92039e-05 | 1.67425e-05 | 1(Win) |
| simdjson (reflection) | 4348.27 | 0.163576 | 821.996ms | 3873 | 80 | 154.452 | 849.438 | 1.21972 | 6.42628 | 0.530855 | 0.000329202 | 6.1322e-05 | 0 | 2(Loss) |
| glaze | 2755.25 | 0.0764972 | 897.396ms | 3873 | 2560 | 2692.17 | 1340.56 | 1.89349 | 7.79123 | 0.993568 | 0.00473188 | 0.00015623 | 9.37984e-05 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 915.697 | 0.11921 | 6860.47ms | 2090234 | 30 | 2.02039e+08 | 2.17692e+06 | 5.50384 | 27.2941 | 5.44706 | 0.021221 | 0.107588 | 8.05014e-05 | 1(Win) |
| jsonifier | 905.824 | 0.0509466 | 6864.8ms | 2090234 | 80 | 1.00559e+08 | 2.20065e+06 | 5.57593 | 24.7428 | 5.13406 | 0.0332065 | 0.0687985 | 7.78561e-05 | 2(Loss) |
| simdjson (reflection) | 871.512 | 0.107108 | 7126.17ms | 2090234 | 160 | 9.60306e+08 | 2.28729e+06 | 5.77876 | 28.1747 | 5.14253 | 0.0191267 | 0.10811 | 0.000163591 | 3(Loss) |
| simdjson (ondemand) | 770.647 | 0.296205 | 8088.99ms | 2090234 | 30 | 1.76111e+09 | 2.58666e+06 | 6.54029 | 30.2821 | 5.60877 | 0.0256042 | 0.114347 | 0.000443874 | 4(Loss) |
| glaze | 722.37 | 0.0689984 | 8556.93ms | 2090234 | 80 | 2.90027e+08 | 2.75953e+06 | 6.97662 | 30.8338 | 6.02083 | 0.028727 | 0.0669449 | 0.00152997 | 5(Loss) |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 1082.85 | 0.103625 | 6879.79ms | 2090234 | 160 | 5.82241e+08 | 1.84089e+06 | 4.59893 | 22.0441 | 4.19573 | 0.020456 | 0.0820837 | 0.000136522 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1081.85 | 0.340753 | 6883.59ms | 2090234 | 30 | 1.18265e+09 | 1.84259e+06 | 4.66443 | 19.4469 | 3.86872 | 0.0327016 | 0.0439421 | 4.62628e-05 | 1(Tie) |
| simdjson (reflection) | 1043.83 | 0.12209 | 7076.45ms | 2090234 | 160 | 8.69776e+08 | 1.90969e+06 | 4.80854 | 22.9342 | 3.89138 | 0.0178053 | 0.0805878 | 6.22986e-05 | 3(Loss) |
| simdjson (ondemand) | 923.764 | 0.258912 | 7876.73ms | 2090234 | 80 | 2.49725e+09 | 2.15791e+06 | 5.45844 | 24.9985 | 4.35347 | 0.0219213 | 0.0788208 | 0.000676713 | 4(Loss) |
| glaze | 843.455 | 0.0492297 | 8547.11ms | 2090234 | 160 | 2.16591e+08 | 2.36338e+06 | 5.98008 | 25.4867 | 4.74987 | 0.0277459 | 0.0404951 | 0.00037485 | 5(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2054.6 | 0.0331992 | 6176.9ms | 2090234 | 320 | 3.32e+07 | 970213 | 2.45573 | 7.84439 | 0.446084 | 0.000377781 | 0.0508704 | 3.14304e-05 | 1(Win) |
| glaze | 1438.04 | 0.0927292 | 8788.88ms | 2090234 | 160 | 2.64364e+08 | 1.3862e+06 | 3.47142 | 9.69974 | 0.651387 | 0.0117381 | 0.0693367 | 6.63203e-05 | 2(Loss) |
| simdjson (reflection) | 1032.68 | 0.0386985 | 6015.37ms | 2090326 | 30 | 1.6742e+07 | 1.93041e+06 | 4.88901 | 15.3147 | 1.4617 | 0.0160885 | 0.0508579 | 4.37731e-05 | 3(Loss) |

----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2058.06 | 0.0347614 | 6169.32ms | 2090234 | 160 | 1.8138e+07 | 968586 | 2.45553 | 7.84422 | 0.44605 | 0.000373968 | 0.0507726 | 1.84339e-05 | 1(Win) |
| glaze | 1515.89 | 0.131184 | 8364.24ms | 2090234 | 40 | 1.19034e+08 | 1.315e+06 | 3.32111 | 9.69575 | 0.650459 | 0.0117593 | 0.0434681 | 8.54928e-05 | 2(Loss) |
| simdjson (reflection) | 1033.16 | 0.0348851 | 6017.87ms | 2090326 | 80 | 3.62462e+07 | 1.92951e+06 | 4.89026 | 15.3145 | 1.46167 | 0.0160993 | 0.0507455 | 4.1112e-05 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2642.13 | 0.344682 | 7540.28ms | 6661897 | 40 | 2.7478e+09 | 2.40461e+06 | 1.89436 | 9.41651 | 1.74065 | 0.0056371 | 0.0567077 | 0.000227176 | 1(Win) |
| simdjson (reflection) | 2502.9 | 0.399674 | 7923.05ms | 6661897 | 160 | 1.6468e+10 | 2.53837e+06 | 2.00354 | 9.75959 | 1.6534 | 0.00521972 | 0.0565307 | 0.000103568 | 2(Loss) |
| jsonifier | 2417.43 | 0.300951 | 8187.23ms | 6661897 | 80 | 5.00459e+09 | 2.62811e+06 | 2.07486 | 9.72955 | 2.12321 | 0.00994394 | 0.0342679 | 0.000143574 | 3(Loss) |
| simdjson (ondemand) | 2280.39 | 0.135942 | 8704.18ms | 6661897 | 40 | 5.73776e+08 | 2.78605e+06 | 2.20785 | 10.4194 | 1.79929 | 0.00727497 | 0.0582335 | 0.000463618 | 4(Loss) |
| glaze | 1855.24 | 0.232095 | 5137.55ms | 6661897 | 80 | 5.0538e+09 | 3.42451e+06 | 2.72336 | 13.3202 | 2.49509 | 0.00882787 | 0.0359305 | 0.00238137 | 5(Loss) |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3087.55 | 0.346451 | 7580.88ms | 6661897 | 80 | 4.06575e+09 | 2.05771e+06 | 1.61382 | 7.77755 | 1.34978 | 0.00538843 | 0.0484458 | 0.00011881 | 1(Win) |
| simdjson (reflection) | 2951.99 | 0.71896 | 7787.97ms | 6661897 | 30 | 7.18286e+09 | 2.1522e+06 | 1.70172 | 8.11591 | 1.26103 | 0.00485866 | 0.0476357 | 0.000124999 | 2(Loss) |
| jsonifier | 2804.17 | 0.34157 | 8190.03ms | 6661897 | 80 | 4.79111e+09 | 2.26565e+06 | 1.7989 | 8.09074 | 1.7324 | 0.00970519 | 0.026052 | 0.000645711 | 3(Loss) |
| simdjson (ondemand) | 2692.33 | 0.146192 | 8598.38ms | 6661897 | 30 | 3.57033e+08 | 2.35977e+06 | 1.87198 | 8.7626 | 1.40565 | 0.00616259 | 0.0475606 | 0.000240267 | 4(Loss) |
| glaze | 2092.87 | 0.210798 | 5152.6ms | 6661897 | 80 | 3.27591e+09 | 3.03568e+06 | 2.41272 | 11.671 | 2.1037 | 0.00848362 | 0.0271159 | 0.000358774 | 5(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5789.71 | 0.475831 | 6954.71ms | 6661897 | 320 | 8.72446e+09 | 1.09734e+06 | 0.870495 | 2.53653 | 0.139963 | 0.000120264 | 0.0279245 | 2.27638e-05 | 1(Win) |
| glaze | 3165.74 | 0.956531 | 6205.97ms | 6661897 | 80 | 2.94805e+10 | 2.00689e+06 | 1.57836 | 4.40917 | 0.355584 | 0.00377952 | 0.0632975 | 0.00107189 | 2(Loss) |
| simdjson (reflection) | 177.647 | 0.180567 | 10771.3ms | 6661989 | 30 | 1.25109e+11 | 3.5764e+07 | 28.43 | 93.958 | 17.0909 | 0.113584 | 0.254629 | 0.1278 | 3(Loss) |

----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5895.4 | 0.119208 | 6947.85ms | 6661897 | 160 | 2.6406e+08 | 1.07767e+06 | 0.856154 | 2.53647 | 0.139952 | 0.000119721 | 0.0278887 | 1.273e-05 | 1(Win) |
| glaze | 3800.47 | 0.441948 | 5216.57ms | 6661897 | 160 | 8.73339e+09 | 1.67171e+06 | 1.32579 | 4.40771 | 0.355242 | 0.00376722 | 0.0246948 | 0.000185448 | 2(Loss) |
| simdjson (reflection) | 177.947 | 0.15233 | 10732.5ms | 6661989 | 30 | 8.87399e+10 | 3.57037e+07 | 28.3952 | 93.9604 | 17.0923 | 0.113571 | 0.256406 | 0.125519 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2446.77 | 0.23487 | 5219.86ms | 500299 | 40 | 8.39054e+06 | 195001 | 2.06386 | 8.93435 | 1.68541 | 0.0115172 | 0.00488113 | 0.000138417 | 1(Win) |
| jsonifier (two-stage) | 1873.49 | 0.188892 | 6757.62ms | 500299 | 30 | 6.94232e+06 | 254670 | 2.69465 | 11.8533 | 2.05037 | 0.0133256 | 0.0342598 | 0.000193951 | 2(Loss) |
| glaze | 1848.45 | 0.139356 | 6866.86ms | 500299 | 80 | 1.03511e+07 | 258120 | 2.74348 | 11.5954 | 2.25497 | 0.0128397 | 0.00389952 | 0.000139042 | 3(Loss) |
| simdjson (reflection) | 1439.18 | 0.224124 | 8665.56ms | 500299 | 320 | 1.76668e+08 | 331524 | 3.50842 | 14.6428 | 2.32226 | 0.0182576 | 0.0222002 | 0.000574544 | 4(Loss) |
| simdjson (ondemand) | 1374.59 | 0.271101 | 9117.64ms | 500299 | 320 | 2.83351e+08 | 347102 | 3.68312 | 14.2417 | 2.32379 | 0.0169067 | 0.0309957 | 0.000294955 | 5(Loss) |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3037.44 | 0.148432 | 5020.31ms | 500299 | 1280 | 6.95838e+07 | 157081 | 1.66212 | 7.8177 | 1.41469 | 0.00847196 | 0.00178508 | 2.61437e-05 | 1(Win) |
| jsonifier (two-stage) | 2240.82 | 0.170374 | 6581.44ms | 500299 | 80 | 1.05279e+07 | 212923 | 2.25603 | 10.7349 | 1.77982 | 0.00950669 | 0.024357 | 5.58166e-05 | 2(Loss) |
| glaze | 2182.15 | 0.125366 | 6704.25ms | 500299 | 160 | 1.20219e+07 | 218648 | 2.31354 | 10.4944 | 1.98983 | 0.0092414 | 0.00138648 | 5.57042e-05 | 3(Loss) |
| simdjson (reflection) | 1697.5 | 0.082827 | 8236.54ms | 500299 | 160 | 8.67165e+06 | 281073 | 2.97483 | 13.5342 | 2.0508 | 0.0113651 | 0.0178696 | 6.92961e-05 | 4(Loss) |
| simdjson (ondemand) | 1623.58 | 0.0340269 | 8580.38ms | 500299 | 1280 | 1.27988e+07 | 293871 | 3.10803 | 13.1115 | 2.04763 | 0.00953953 | 0.0196754 | 0.00010066 | 5(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12423 | 0.0941045 | 4697.51ms | 500299 | 320 | 417998 | 38406.3 | 0.408386 | 1.88545 | 0.301516 | 0.000741263 | 0.00293602 | 1.1337e-05 | 1(Win) |
| simdjson (reflection) | 11194.3 | 0.0880901 | 5097.28ms | 500299 | 640 | 902200 | 42622 | 0.452029 | 2.1699 | 0.197426 | 0.0012114 | 0.000790543 | 1.48318e-05 | 2(Loss) |
| glaze | 6082.13 | 0.551081 | 8691.45ms | 500299 | 2560 | 4.78431e+08 | 78446.6 | 0.826907 | 3.61292 | 0.526275 | 0.00133208 | 0.0218576 | 2.5883e-05 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12434.4 | 0.113012 | 4705.61ms | 500299 | 40 | 75216.9 | 38371.2 | 0.406914 | 1.88435 | 0.301268 | 0.000729814 | 0.00274451 | 2.40356e-05 | 1(Win) |
| simdjson (reflection) | 11181.2 | 0.0820757 | 5083.12ms | 500299 | 640 | 785033 | 42671.7 | 0.45304 | 2.16881 | 0.197178 | 0.00121746 | 0.000805215 | 1.63527e-05 | 2(Loss) |
| glaze | 7146.05 | 0.27356 | 7426.59ms | 500299 | 4890 | 1.63132e+08 | 66767.2 | 0.707861 | 3.59896 | 0.523037 | 0.0013417 | 0.00231368 | 3.63043e-05 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4378.65 | 0.128741 | 8211.69ms | 1439562 | 640 | 1.04278e+08 | 313538 | 1.1452 | 5.00055 | 0.744859 | 0.00448125 | 0.0574561 | 0.000109477 | 1(Win) |
| jsonifier | 4013.97 | 0.169525 | 9131.64ms | 1439562 | 40 | 1.34476e+07 | 342024 | 1.25841 | 5.38057 | 1.17244 | 0.00424801 | 0.0218041 | 0.000112673 | 2(Loss) |
| simdjson (reflection) | 3578.91 | 0.0624849 | 10041ms | 1439562 | 320 | 1.83848e+07 | 383601 | 1.41212 | 6.02924 | 0.848279 | 0.00607029 | 0.0485774 | 0.000153792 | 3(Loss) |
| simdjson (ondemand) | 3417.63 | 0.0614732 | 5219.63ms | 1439562 | 320 | 1.95134e+07 | 401703 | 1.47493 | 5.89282 | 0.849943 | 0.00566781 | 0.0524636 | 0.000123688 | 4(Loss) |
| glaze | 2935.01 | 0.448657 | 6078.37ms | 1439562 | 640 | 2.81871e+09 | 467757 | 1.72988 | 7.72451 | 1.43099 | 0.00633282 | 0.0179442 | 0.000141576 | 5(Loss) |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 5059.18 | 0.146506 | 8036.86ms | 1439562 | 320 | 5.05782e+07 | 271363 | 0.986111 | 4.61071 | 0.650602 | 0.00328541 | 0.0495482 | 8.5879e-05 | 1(Win) |
| jsonifier | 4451.28 | 0.679597 | 8976.05ms | 1439562 | 640 | 2.81173e+09 | 308422 | 1.13253 | 4.9935 | 1.07859 | 0.00317698 | 0.0156918 | 5.16042e-05 | 2(Loss) |
| simdjson (reflection) | 4119.52 | 0.122853 | 9617.03ms | 1439562 | 80 | 1.34101e+07 | 333261 | 1.22359 | 5.64172 | 0.753561 | 0.00389715 | 0.0388231 | 2.75778e-05 | 3(Loss) |
| simdjson (ondemand) | 3960.92 | 0.0899151 | 9879.56ms | 1439562 | 160 | 1.55401e+07 | 346605 | 1.27186 | 5.49635 | 0.752753 | 0.00325442 | 0.0398243 | 2.38137e-05 | 4(Loss) |
| glaze | 3237.46 | 0.457069 | 5991.91ms | 1439562 | 640 | 2.40433e+09 | 424059 | 1.56555 | 7.33963 | 1.33823 | 0.00486084 | 0.0128367 | 4.33042e-05 | 5(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18556.8 | 0.0670473 | 8327.23ms | 1439562 | 640 | 1.57469e+06 | 73982.2 | 0.27258 | 0.747908 | 0.104976 | 0.000251202 | 0.0168084 | 9.01424e-06 | 1(Win) |
| glaze | 5931.41 | 0.093163 | 6120.75ms | 1439584 | 1280 | 5.95188e+07 | 231462 | 0.844829 | 2.99221 | 0.365998 | 0.000652877 | 0.0599326 | 2.17766e-05 | 2(Loss) |
| simdjson (reflection) | 545.46 | 0.701305 | 7803.66ms | 1439562 | 160 | 4.98505e+10 | 2.51691e+06 | 9.16757 | 35.1845 | 5.83466 | 0.0145299 | 0.306917 | 0.00637925 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18598.8 | 0.113062 | 8353.44ms | 1439562 | 160 | 1.1144e+06 | 73815.2 | 0.271675 | 0.747668 | 0.104926 | 0.000239361 | 0.0167316 | 6.65133e-06 | 1(Win) |
| glaze | 8290.59 | 0.253687 | 8916.41ms | 1439584 | 320 | 5.64742e+07 | 165597 | 0.608098 | 2.98647 | 0.364672 | 0.000649445 | 0.0164804 | 1.81997e-05 | 2(Loss) |
| simdjson (reflection) | 552.744 | 0.463251 | 7779.05ms | 1439562 | 160 | 2.11819e+10 | 2.48374e+06 | 9.05994 | 35.1849 | 5.83472 | 0.014431 | 0.307699 | 0.0209217 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2231.53 | 0.0616675 | 3150.2ms | 56369 | 2560 | 564974 | 24090 | 2.27174 | 9.42193 | 1.8071 | 0.00478928 | 5.83696e-05 | 3.46281e-05 | 1(Win) |
| glaze | 1859.22 | 0.0732767 | 3645.12ms | 56369 | 4890 | 2.19514e+06 | 28914.2 | 2.72727 | 11.2289 | 2.23877 | 0.0075069 | 8.29583e-05 | 5.34965e-05 | 2(Loss) |
| jsonifier (two-stage) | 1811.99 | 0.0873428 | 3731.14ms | 56369 | 1280 | 859472 | 29667.7 | 2.81565 | 12.0598 | 2.07886 | 0.00552088 | 0.000118056 | 8.43216e-05 | 3(Loss) |
| simdjson (reflection) | 1549.04 | 0.0989039 | 4204.83ms | 56369 | 640 | 753980 | 34703.8 | 3.26809 | 13.7263 | 2.33736 | 0.00528798 | 0.000148575 | 9.69893e-05 | 4(Loss) |
| simdjson (ondemand) | 1444.53 | 0.0457269 | 4478.98ms | 56369 | 2560 | 741334 | 37214.8 | 3.50465 | 14.21 | 2.61877 | 0.00802822 | 0.000214699 | 0.000160868 | 5(Loss) |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3277.4 | 0.070138 | 2728.4ms | 56369 | 2560 | 338820 | 16402.5 | 1.55418 | 7.43958 | 1.37463 | 0.000882231 | 3.98601e-05 | 2.70469e-05 | 1(Win) |
| glaze | 2847.85 | 0.243691 | 2991.76ms | 56369 | 640 | 1.35428e+06 | 18876.6 | 1.78962 | 8.99656 | 1.7551 | 0.00171143 | 2.75251e-05 | 1.82115e-05 | 2(Loss) |
| jsonifier (two-stage) | 2405.46 | 0.044681 | 3333.09ms | 56369 | 4890 | 487573 | 22348.2 | 2.10315 | 10.0574 | 1.64188 | 0.00231665 | 4.23408e-05 | 2.85331e-05 | 3(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1814.96 | 0.0497616 | 4091.51ms | 56369 | 2560 | 556130 | 29619.3 | 2.80255 | 12.1347 | 1.97583 | 0.0037849 | 8.8923e-05 | 6.39966e-05 | 4(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1812.96 | 0.147866 | 4106.22ms | 56369 | 160 | 307581 | 29651.8 | 2.79089 | 12.0278 | 2.15723 | 0.00789253 | 3.33738e-05 | 2.05122e-05 | 4(Tie) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13348.7 | 0.0808608 | 1151.41ms | 56369 | 640 | 6786.73 | 4027.19 | 0.382432 | 1.57681 | 0.249534 | 0.000202239 | 9.14732e-06 | 3.65893e-06 | 1(Win) |
| simdjson (reflection) | 11074.7 | 0.078131 | 1232.61ms | 56369 | 4890 | 70334.7 | 4854.08 | 0.460848 | 1.85536 | 0.281875 | 0.000148713 | 2.17273e-05 | 1.18268e-05 | 2(Loss) |
| glaze | 6132.14 | 0.128215 | 1630.66ms | 56369 | 1280 | 161711 | 8766.54 | 0.828019 | 3.29016 | 0.477 | 0.000119483 | 2.30207e-05 | 1.41922e-05 | 3(Loss) |

----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13511.8 | 0.0538092 | 1143.74ms | 56369 | 4890 | 22411.8 | 3978.57 | 0.377688 | 1.56723 | 0.24737 | 0.000209095 | 1.93329e-05 | 1.14205e-05 | 1(Win) |
| simdjson (reflection) | 11316.2 | 0.0688006 | 1221.64ms | 56369 | 4890 | 52236.3 | 4750.51 | 0.450561 | 1.8458 | 0.279711 | 0.000144458 | 1.65612e-05 | 8.05023e-06 | 2(Loss) |
| glaze | 6569.77 | 0.090103 | 1568.7ms | 56369 | 4890 | 265808 | 8182.58 | 0.772851 | 3.21152 | 0.459455 | 6.75617e-05 | 2.43393e-05 | 1.46783e-05 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2836.27 | 0.0461262 | 3931.03ms | 94370 | 2560 | 548412 | 31731.2 | 1.7851 | 7.7775 | 1.25533 | 0.00282598 | 2.53201e-05 | 1.40115e-05 | 1(Win) |
| simdjson (reflection) | 2490.29 | 0.0300385 | 4370.02ms | 94370 | 4890 | 576281 | 36139.7 | 2.02952 | 8.78105 | 1.4202 | 0.00264374 | 4.93706e-05 | 3.22167e-05 | 2(Loss) |
| jsonifier | 2478.5 | 0.0789073 | 4379.49ms | 94370 | 1280 | 1.05083e+06 | 36311.5 | 2.04516 | 7.78978 | 1.70648 | 0.00516604 | 4.00683e-05 | 2.50676e-05 | 3(Loss) |
| glaze | 2469.32 | 0.0359591 | 4402.76ms | 94370 | 4890 | 839922 | 36446.6 | 2.05303 | 9.04498 | 1.86669 | 0.0047981 | 3.37292e-05 | 2.0062e-05 | 4(Loss) |
| simdjson (ondemand) | 2264.29 | 0.0317021 | 4718.55ms | 94370 | 4890 | 776406 | 39746.8 | 2.23774 | 9.06795 | 1.58797 | 0.00619104 | 8.8177e-05 | 6.07039e-05 | 5(Loss) |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3635.48 | 0.0452024 | 3578.5ms | 94370 | 4890 | 612315 | 24755.5 | 1.39445 | 6.59792 | 0.998093 | 0.00175012 | 2.55467e-05 | 1.52123e-05 | 1(Win) |
| glaze | 3220.38 | 0.123598 | 3902.45ms | 94370 | 80 | 95447.5 | 27946.4 | 1.57154 | 7.71525 | 1.57891 | 0.00338587 | 4.23864e-06 | 9.27201e-07 | 2(Loss) |
| jsonifier | 3134.64 | 0.0528462 | 3970ms | 94370 | 2560 | 589333 | 28710.9 | 1.62262 | 6.61382 | 1.45049 | 0.00337366 | 3.01713e-05 | 1.98065e-05 | 3(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 2848.91 | 0.0706782 | 4292.59ms | 94370 | 1280 | 638105 | 31590.4 | 1.77882 | 7.77413 | 1.31452 | 0.00485541 | 1.9612e-05 | 1.10022e-05 | 4(Tie) |
| simdjson (reflection) STATISTICAL TIE | 2845.36 | 0.0318681 | 4291.75ms | 94370 | 4890 | 496837 | 31629.8 | 1.77757 | 7.82967 | 1.20393 | 0.00234527 | 2.46257e-05 | 1.44322e-05 | 4(Tie) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18381.1 | 0.125938 | 1231.91ms | 94370 | 30 | 1140.67 | 4896.23 | 0.277403 | 0.991396 | 0.149168 | 0.000132811 | 2.54318e-05 | 1.20095e-05 | 1(Win) |
| glaze | 6216.06 | 0.0490337 | 2203.03ms | 94370 | 4890 | 246455 | 14478.4 | 0.815718 | 3.47904 | 0.47282 | 0.000262921 | 2.41923e-05 | 1.67638e-05 | 2(Loss) |
| simdjson (reflection) | 523.288 | 0.19859 | 9200.22ms | 94370 | 2560 | 2.98634e+08 | 171986 | 9.62985 | 36.2712 | 6.32937 | 0.0229602 | 0.0137724 | 0.00061639 | 3(Loss) |

----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18576.4 | 0.0884192 | 1224.64ms | 94370 | 80 | 1468.01 | 4844.76 | 0.274675 | 0.98579 | 0.147907 | 0.000134179 | 4.90092e-06 | 3.57635e-06 | 1(Win) |
| glaze | 7345.8 | 0.0687261 | 1976.69ms | 94370 | 2560 | 181498 | 12251.7 | 0.694043 | 3.42514 | 0.460687 | 0.00024765 | 1.56134e-05 | 9.08989e-06 | 2(Loss) |
| simdjson (reflection) | 528.638 | 0.258508 | 9171.72ms | 94370 | 1280 | 2.47918e+08 | 170245 | 9.54763 | 36.271 | 6.3296 | 0.0234097 | 0.020383 | 0.000421314 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2705.32 | 0.137936 | 1149.65ms | 11812 | 1280 | 42225.8 | 4163.95 | 1.90472 | 9.34897 | 1.55833 | 0.000145641 | 5.36398e-05 | 2.36783e-05 | 1(Win) |
| glaze | 1973.4 | 0.147617 | 1306.83ms | 11812 | 160 | 11360.8 | 5708.32 | 2.5779 | 12.8943 | 2.45555 | 0.0017043 | 2.85726e-05 | 2.11649e-06 | 2(Loss) |
| jsonifier (two-stage) | 1915.6 | 0.0465562 | 1330.02ms | 11812 | 4890 | 36652.2 | 5880.55 | 2.66577 | 12.7111 | 2.0199 | 0.00446352 | 5.37217e-05 | 2.45323e-05 | 3(Loss) |
| simdjson (reflection) | 1316.06 | 0.0629616 | 1596.22ms | 11812 | 2560 | 74351.5 | 8559.51 | 3.86031 | 14.5266 | 2.4073 | 0.00783155 | 6.85545e-05 | 3.37316e-05 | 4(Loss) |
| simdjson (ondemand) | 1108.21 | 0.120628 | 1758.98ms | 11812 | 160 | 24055.6 | 10164.8 | 4.57624 | 15.728 | 2.72256 | 0.00728073 | 7.40772e-05 | 3.70386e-05 | 5(Loss) |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3014.24 | 0.11494 | 1150.93ms | 11812 | 40 | 738.062 | 3737.2 | 1.69661 | 8.55054 | 1.37284 | 0.000338639 | 2.32814e-05 | 1.05825e-05 | 1(Win) |
| glaze | 2276.53 | 0.0610186 | 1286.95ms | 11812 | 4890 | 44579.5 | 4948.24 | 2.24643 | 11.8672 | 2.22257 | 0.00053346 | 3.76381e-05 | 1.572e-05 | 2(Loss) |
| jsonifier (two-stage) | 2083.03 | 0.0593451 | 1331.77ms | 11812 | 2560 | 26367.3 | 5407.89 | 2.45113 | 11.9114 | 1.83466 | 0.0043481 | 4.64636e-05 | 2.02059e-05 | 3(Loss) |
| simdjson (reflection) | 1383.6 | 0.231355 | 1606.03ms | 11812 | 320 | 113536 | 8141.69 | 3.71262 | 14.1789 | 2.32001 | 0.00779954 | 3.016e-05 | 9.78877e-06 | 4(Loss) |
| simdjson (ondemand) | 1186.28 | 0.164037 | 1741.13ms | 11812 | 80 | 19410.9 | 9495.88 | 4.277 | 14.9005 | 2.54089 | 0.00621825 | 7.93684e-05 | 3.80969e-05 | 5(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 10916.2 | 0.170013 | 836.597ms | 11812 | 30 | 92.3402 | 1031.93 | 0.481728 | 2.48078 | 0.317728 | 8.46597e-05 | 1.41099e-05 | 0 | 1(Win) |
| simdjson (reflection) | 9887.77 | 0.24224 | 847.624ms | 11812 | 2560 | 19497.6 | 1139.27 | 0.531453 | 2.45039 | 0.348798 | 0.00011816 | 3.3434e-05 | 1.45178e-05 | 2(Loss) |
| glaze | 4174.3 | 0.183782 | 1008.59ms | 11812 | 4890 | 120280 | 2698.61 | 1.24012 | 4.53954 | 0.718676 | 9.12212e-05 | 7.2835e-05 | 3.97675e-05 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11312.5 | 0.160479 | 828.737ms | 11812 | 80 | 204.296 | 995.788 | 0.467068 | 2.43735 | 0.307738 | 8.46597e-05 | 4.76211e-05 | 1.16407e-05 | 1(Win) |
| simdjson (reflection) | 10340.6 | 0.11538 | 841.141ms | 11812 | 1280 | 2022.21 | 1089.38 | 0.507429 | 2.4034 | 0.338131 | 0.000102782 | 1.73949e-05 | 3.17474e-06 | 2(Loss) |
| glaze | 4696.39 | 0.202167 | 974.898ms | 11812 | 4890 | 114986 | 2398.61 | 1.10601 | 4.26532 | 0.658737 | 0.000103825 | 5.53318e-05 | 2.99512e-05 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4167.95 | 0.102205 | 1450.6ms | 31235 | 640 | 34148 | 7146.92 | 1.2189 | 5.70693 | 0.804483 | 0.00154959 | 2.67628e-05 | 1.48071e-05 | 1(Win) |
| jsonifier | 4139.08 | 0.0750749 | 1456.57ms | 31235 | 4890 | 142749 | 7196.77 | 1.22915 | 5.69256 | 1.17861 | 0.00244129 | 1.93729e-05 | 9.1725e-06 | 2(Loss) |
| simdjson (reflection) | 3036.46 | 0.0652549 | 1724.49ms | 31235 | 2560 | 104909 | 9810.11 | 1.68222 | 6.46677 | 0.971363 | 0.00367445 | 2.27109e-05 | 1.07176e-05 | 3(Loss) |
| glaze | 2885.62 | 0.0620798 | 1772.53ms | 31235 | 4890 | 200823 | 10322.9 | 1.76075 | 8.485 | 1.54452 | 0.00574747 | 2.69217e-05 | 1.02135e-05 | 4(Loss) |
| simdjson (ondemand) | 2624.62 | 0.138007 | 1875.2ms | 31235 | 640 | 157012 | 11349.5 | 1.94371 | 6.79736 | 1.06221 | 0.00309103 | 3.02145e-05 | 1.65079e-05 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4516.53 | 0.105209 | 1445.39ms | 31235 | 30 | 1444.44 | 6595.33 | 1.1282 | 5.40522 | 0.734657 | 0.00152286 | 1.49405e-05 | 8.53743e-06 | 1(Win) |
| jsonifier | 4429.45 | 0.0576814 | 1457.15ms | 31235 | 160 | 2407.55 | 6724.99 | 1.1492 | 5.39129 | 1.10879 | 0.00245118 | 8.00384e-06 | 1.60077e-06 | 2(Loss) |
| simdjson (reflection) | 3182.85 | 0.132989 | 1722.67ms | 31235 | 640 | 99143.1 | 9358.91 | 1.59492 | 6.27536 | 0.924956 | 0.0032315 | 1.72083e-05 | 5.90283e-06 | 3(Loss) |
| glaze | 3078.42 | 0.0902459 | 1758.57ms | 31235 | 2560 | 195219 | 9676.4 | 1.65931 | 8.10527 | 1.45843 | 0.00557141 | 1.41068e-05 | 4.97739e-06 | 4(Loss) |
| simdjson (ondemand) | 2793.73 | 0.049309 | 1862.56ms | 31235 | 4890 | 135169 | 10662.5 | 1.82779 | 6.49227 | 0.995167 | 0.00272006 | 2.68759e-05 | 1.22365e-05 | 5(Loss) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18419.4 | 0.0576803 | 896.193ms | 31235 | 160 | 139.221 | 1617.21 | 0.281666 | 1.04722 | 0.120602 | 6.42308e-05 | 6.00288e-06 | 6.00288e-07 | 1(Win) |
| glaze | 6922.58 | 0.106494 | 1170.75ms | 31235 | 2560 | 53757 | 4303.02 | 0.738128 | 3.60864 | 0.477829 | 0.000148909 | 2.16854e-05 | 1.15555e-05 | 2(Loss) |
| simdjson (reflection) | 527.246 | 0.157855 | 6420.84ms | 31235 | 2560 | 2.03618e+07 | 56497.4 | 9.63112 | 37.4353 | 6.54926 | 0.0140676 | 0.000352019 | 0.000242404 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19100.8 | 0.0656226 | 887.781ms | 31235 | 4890 | 5121.51 | 1559.52 | 0.271648 | 1.02897 | 0.116376 | 5.823e-05 | 1.80962e-05 | 9.76174e-06 | 1(Win) |
| glaze | 7831.94 | 0.150631 | 1117.44ms | 31235 | 1280 | 42012.8 | 3803.4 | 0.660998 | 3.48407 | 0.450488 | 0.000167956 | 1.55325e-05 | 8.77921e-06 | 2(Loss) |
| simdjson (reflection) | 525.783 | 0.153287 | 6412.51ms | 31235 | 2560 | 1.93072e+07 | 56654.6 | 9.65291 | 37.4378 | 6.54998 | 0.0140743 | 0.000237727 | 0.000155875 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3301.3 | 0.0363976 | 3877.04ms | 108313 | 4890 | 634227 | 31289.3 | 1.53818 | 7.02592 | 1.47823 | 0.00218331 | 4.89153e-05 | 3.84461e-05 | 1(Win) |
| jsonifier (two-stage) | 2289.04 | 0.0563209 | 5265.63ms | 108313 | 1280 | 826805 | 45126 | 2.21158 | 9.92175 | 1.78183 | 0.00270791 | 3.98801e-05 | 2.7748e-05 | 2(Loss) |
| glaze | 2106.14 | 0.0390092 | 5647.47ms | 108313 | 4890 | 1.78991e+06 | 49045 | 2.40943 | 10.1682 | 1.91063 | 0.00310545 | 5.65014e-05 | 4.09496e-05 | 3(Loss) |
| simdjson (reflection) | 1856.1 | 0.167693 | 6299.13ms | 108313 | 160 | 1.3935e+06 | 55651.8 | 2.72452 | 12.8838 | 1.96485 | 0.00243375 | 1.61569e-05 | 9.2325e-06 | 4(Loss) |
| simdjson (ondemand) | 1398.09 | 0.072936 | 8124.58ms | 108313 | 640 | 1.85846e+06 | 73883.1 | 3.62848 | 14.494 | 2.45092 | 0.00316758 | 2.14367e-05 | 1.21032e-05 | 5(Loss) |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3936.38 | 0.0788073 | 3547.01ms | 108313 | 640 | 273704 | 26241.2 | 1.28557 | 6.33288 | 1.33094 | 0.00175008 | 1.65608e-05 | 1.09347e-05 | 1(Win) |
| jsonifier (two-stage) | 2586.28 | 0.104306 | 4947.37ms | 108313 | 640 | 1.11072e+06 | 39939.7 | 1.96421 | 9.22754 | 1.63455 | 0.00242407 | 1.62579e-05 | 1.10213e-05 | 2(Loss) |
| glaze | 2330.74 | 0.0482519 | 5366.32ms | 108313 | 4890 | 2.23621e+06 | 44318.8 | 2.18605 | 9.525 | 1.77341 | 0.00277571 | 2.80034e-05 | 2.08345e-05 | 3(Loss) |
| simdjson (reflection) | 1922.54 | 0.0334367 | 6287.22ms | 108313 | 4890 | 1.57822e+06 | 53728.7 | 2.63395 | 12.578 | 1.89385 | 0.00228063 | 2.39686e-05 | 1.70716e-05 | 4(Loss) |
| simdjson (ondemand) | 1505.74 | 0.0536999 | 5368.03ms | 108313 | 1280 | 1.73708e+06 | 68601 | 3.38776 | 13.8424 | 2.31591 | 0.00270176 | 2.46609e-05 | 1.75922e-05 | 5(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19236 | 0.0607788 | 1269.09ms | 108313 | 2560 | 27269.6 | 5369.91 | 0.266843 | 1.17906 | 0.304811 | 0.000120661 | 1.435e-05 | 9.54626e-06 | 1(Win) |
| simdjson (reflection) | 15950.3 | 0.139361 | 1396.26ms | 108313 | 80 | 6516.21 | 6476.09 | 0.324809 | 1.49061 | 0.1938 | 0.000177264 | 6.92438e-06 | 3.92381e-06 | 2(Loss) |
| glaze | 5498.77 | 0.100831 | 2638.55ms | 108313 | 4890 | 1.75439e+06 | 18785.2 | 0.924007 | 2.96029 | 0.382697 | 0.000162607 | 1.74606e-05 | 1.13792e-05 | 3(Loss) |

----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19649 | 0.124768 | 1266ms | 108313 | 640 | 27534.1 | 5257.03 | 0.26409 | 1.17418 | 0.303712 | 0.000114252 | 4.45757e-06 | 2.14944e-06 | 1(Win) |
| simdjson (reflection) | 15451.9 | 0.0679022 | 1409.86ms | 108313 | 4890 | 100757 | 6684.96 | 0.333827 | 1.4856 | 0.192682 | 0.000190847 | 4.34249e-06 | 2.09761e-06 | 2(Loss) |
| glaze | 6428.4 | 0.0537925 | 2348.55ms | 108313 | 4890 | 365350 | 16068.6 | 0.794731 | 2.91384 | 0.372172 | 0.000184724 | 6.80071e-06 | 3.54007e-06 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3847.45 | 0.0302446 | 6045.03ms | 213963 | 4890 | 1.25816e+06 | 53035.4 | 1.32251 | 5.79407 | 0.94643 | 0.00138213 | 2.45279e-05 | 1.82571e-05 | 1(Win) |
| jsonifier | 3493.38 | 0.0424343 | 6579.43ms | 213963 | 2560 | 1.57275e+06 | 58410.8 | 1.4513 | 5.86678 | 1.37735 | 0.00201529 | 2.18204e-05 | 1.5111e-05 | 2(Loss) |
| simdjson (reflection) | 3358.23 | 0.0246449 | 6825.01ms | 213963 | 4890 | 1.09653e+06 | 60761.4 | 1.50655 | 7.20482 | 1.02092 | 0.00120282 | 1.41683e-05 | 9.3216e-06 | 3(Loss) |
| glaze | 2892.26 | 0.0308767 | 7792.21ms | 213963 | 4890 | 2.32047e+06 | 70550.8 | 1.75098 | 8.06224 | 1.54244 | 0.00199206 | 2.57589e-05 | 1.78471e-05 | 4(Loss) |
| simdjson (ondemand) | 2581.61 | 0.0870546 | 8645.09ms | 213963 | 320 | 1.51506e+06 | 79040.2 | 1.96646 | 8.02873 | 1.2698 | 0.00157556 | 1.94397e-05 | 1.24437e-05 | 5(Loss) |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4274.76 | 0.0728434 | 5708.86ms | 213963 | 640 | 773776 | 47734 | 1.19199 | 5.44194 | 0.871726 | 0.00132141 | 2.19007e-05 | 1.73584e-05 | 1(Win) |
| jsonifier | 3817.82 | 0.110219 | 6306.58ms | 213963 | 320 | 1.11049e+06 | 53447 | 1.33665 | 5.51381 | 1.30212 | 0.0019578 | 1.7541e-05 | 1.33347e-05 | 2(Loss) |
| simdjson (reflection) | 3465.87 | 0.0498742 | 6810.25ms | 213963 | 1280 | 1.10361e+06 | 58874.4 | 1.46314 | 7.04384 | 0.983675 | 0.00112409 | 1.35209e-05 | 9.62856e-06 | 3(Loss) |
| glaze | 3125.52 | 0.0374722 | 7488.53ms | 213963 | 4890 | 2.92658e+06 | 65285.4 | 1.63153 | 7.74101 | 1.47422 | 0.00183644 | 1.40794e-05 | 9.82625e-06 | 4(Loss) |
| simdjson (ondemand) | 2752.1 | 0.105186 | 8350.82ms | 213963 | 80 | 486583 | 74143.9 | 1.84157 | 7.69457 | 1.20076 | 0.00140287 | 1.06327e-05 | 7.24424e-06 | 5(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 24699.8 | 0.0399962 | 1553.72ms | 213963 | 2560 | 27949 | 8261.23 | 0.208205 | 0.656151 | 0.154611 | 5.34117e-05 | 2.65634e-06 | 1.59928e-06 | 1(Win) |
| glaze | 6140.03 | 0.0641093 | 4073.26ms | 213963 | 4890 | 2.21966e+06 | 33232.9 | 0.822304 | 3.21268 | 0.397424 | 0.000378588 | 1.72984e-05 | 1.0566e-05 | 2(Loss) |
| simdjson (reflection) | 495.737 | 0.493792 | 5329.68ms | 213963 | 160 | 6.60972e+08 | 411611 | 10.146 | 38.0955 | 6.69639 | 0.0245039 | 0.195478 | 0.000553746 | 3(Loss) |

----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 24990.4 | 0.106567 | 1550.86ms | 213963 | 80 | 6057.05 | 8165.16 | 0.207204 | 0.65373 | 0.154064 | 5.79539e-05 | 3.21317e-06 | 2.57054e-06 | 1(Win) |
| glaze | 7459.27 | 0.155209 | 3476.78ms | 213963 | 640 | 1.15372e+06 | 27355.3 | 0.679434 | 3.18462 | 0.3911 | 0.000376379 | 8.96767e-06 | 6.43365e-06 | 2(Loss) |
| simdjson (reflection) | 493.272 | 0.521948 | 5359.24ms | 213963 | 160 | 7.45896e+08 | 413668 | 10.2168 | 38.1208 | 6.70325 | 0.0261733 | 0.189267 | 0.000244289 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 763.801 | 0.11161 | 7142.08ms | 1834197 | 80 | 5.22668e+08 | 2.29016e+06 | 6.63028 | 25.9531 | 5.46638 | 0.0393084 | 0.0815763 | 0.000614131 | 1(Win) |
| simdjson (reflection) | 734.666 | 0.0819268 | 7410.08ms | 1834197 | 30 | 1.14153e+08 | 2.38098e+06 | 6.88167 | 30.9317 | 5.22863 | 0.0336615 | 0.135517 | 0.000650439 | 2(Loss) |
| jsonifier (two-stage) | 731.774 | 0.133869 | 7483.2ms | 1834197 | 40 | 4.09601e+08 | 2.39039e+06 | 6.95565 | 29.7691 | 6.05198 | 0.0322257 | 0.144065 | 0.000454177 | 3(Loss) |
| glaze | 652.612 | 0.097264 | 8380.43ms | 1834197 | 80 | 5.43721e+08 | 2.68035e+06 | 7.75806 | 32.1185 | 6.36429 | 0.0326628 | 0.0816841 | 0.00402342 | 4(Loss) |
| simdjson (ondemand) | 614.004 | 0.143549 | 8865.1ms | 1834197 | 30 | 5.01734e+08 | 2.84889e+06 | 8.21926 | 33.5211 | 6.10914 | 0.0417014 | 0.147311 | 0.000867555 | 5(Loss) |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 836.693 | 0.0924188 | 7138.69ms | 1834197 | 160 | 5.97311e+08 | 2.09064e+06 | 6.06661 | 22.9466 | 4.76531 | 0.0386191 | 0.055514 | 0.000748526 | 1(Win) |
| simdjson (reflection) | 823.658 | 0.0569333 | 7198.15ms | 1834197 | 160 | 2.33911e+08 | 2.12373e+06 | 6.13959 | 27.9072 | 4.51131 | 0.0290095 | 0.111984 | 0.00096241 | 2(Loss) |
| jsonifier (two-stage) | 795.837 | 0.124635 | 7479.03ms | 1834197 | 80 | 6.00368e+08 | 2.19797e+06 | 6.37168 | 26.7618 | 5.35067 | 0.0314435 | 0.118168 | 0.000276756 | 3(Loss) |
| glaze | 712.629 | 0.0795811 | 8323.36ms | 1834197 | 80 | 3.05264e+08 | 2.45461e+06 | 7.11165 | 29.106 | 5.66255 | 0.0311242 | 0.0583229 | 0.000333102 | 4(Loss) |
| simdjson (ondemand) | 672.299 | 0.0671708 | 8732.48ms | 1834197 | 160 | 4.88707e+08 | 2.60186e+06 | 7.50958 | 30.4968 | 5.40606 | 0.0376141 | 0.117833 | 0.00123911 | 5(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1246.49 | 0.0649355 | 8933.27ms | 1834197 | 40 | 3.32152e+07 | 1.40332e+06 | 4.12723 | 12.0961 | 0.887773 | 0.0131057 | 0.0603373 | 0.000242667 | 1(Win) |
| glaze | 1003.15 | 0.150718 | 5451.3ms | 1833577 | 160 | 1.10438e+09 | 1.74315e+06 | 5.12869 | 15.8266 | 1.02016 | 0.000920366 | 0.0494081 | 0.00032803 | 2(Loss) |
| simdjson (reflection) | 884.484 | 0.090146 | 6433.09ms | 1922245 | 80 | 2.79268e+08 | 2.07262e+06 | 5.75499 | 18.1209 | 2.02074 | 0.0273988 | 0.0505999 | 0.00019355 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1241.8 | 0.0600169 | 8945.23ms | 1834197 | 160 | 1.14355e+08 | 1.40862e+06 | 4.13314 | 12.096 | 0.887733 | 0.0130152 | 0.0602578 | 0.00154708 | 1(Win) |
| glaze | 1015.46 | 0.263024 | 5377.23ms | 1833577 | 160 | 3.28236e+09 | 1.72202e+06 | 5.02804 | 15.8258 | 1.01999 | 0.000927685 | 0.0493014 | 0.000340809 | 2(Loss) |
| simdjson (reflection) | 889.858 | 0.0824791 | 6428.04ms | 1922245 | 80 | 2.30969e+08 | 2.0601e+06 | 5.74365 | 18.1208 | 2.02071 | 0.0273739 | 0.0503236 | 7.31306e-05 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3361.77 | 0.0808072 | 8759.52ms | 9930848 | 160 | 8.29196e+08 | 2.81721e+06 | 1.50239 | 6.44969 | 1.15527 | 0.00655776 | 0.0542992 | 0.00310572 | 1(Win) |
| simdjson (reflection) | 3307.68 | 0.130913 | 9198.41ms | 9930848 | 40 | 5.62021e+08 | 2.86327e+06 | 1.5277 | 6.84356 | 1.01044 | 0.00595899 | 0.0517262 | 0.00506316 | 2(Loss) |
| jsonifier | 3288.19 | 0.119978 | 8931.65ms | 9930848 | 80 | 9.5532e+08 | 2.88025e+06 | 1.52579 | 6.74503 | 1.53958 | 0.00732955 | 0.0299705 | 0.00157205 | 3(Loss) |
| simdjson (ondemand) | 2911.88 | 0.182977 | 10273.8ms | 9930848 | 30 | 1.06253e+09 | 3.25247e+06 | 1.74958 | 7.32095 | 1.17306 | 0.0073747 | 0.0537562 | 0.00125713 | 4(Loss) |
| glaze | 2634.83 | 0.112168 | 5461.76ms | 9930848 | 40 | 6.50227e+08 | 3.59447e+06 | 1.91611 | 9.18123 | 1.80157 | 0.00663817 | 0.0289371 | 0.000838561 | 5(Loss) |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3639.25 | 0.0857377 | 8772.77ms | 9930848 | 160 | 7.9655e+08 | 2.6024e+06 | 1.38887 | 5.89462 | 1.02582 | 0.00638698 | 0.0493951 | 0.00241959 | 1(Win) |
| simdjson (reflection) | 3587.05 | 0.13832 | 8813.47ms | 9930848 | 80 | 1.06699e+09 | 2.64028e+06 | 1.40618 | 6.28378 | 0.878034 | 0.00510752 | 0.0468256 | 0.00897094 | 2(Loss) |
| jsonifier | 3566.27 | 0.190236 | 8915.23ms | 9930848 | 30 | 7.65681e+08 | 2.65566e+06 | 1.41707 | 6.19039 | 1.41048 | 0.00721463 | 0.0250892 | 0.00166729 | 3(Loss) |
| simdjson (ondemand) | 3161.08 | 0.146227 | 10165.5ms | 9930848 | 30 | 5.7581e+08 | 2.99606e+06 | 1.60929 | 6.76195 | 1.04326 | 0.006598 | 0.0478321 | 0.00103726 | 4(Loss) |
| glaze | 2761.32 | 0.128905 | 5484.49ms | 9930848 | 40 | 7.81878e+08 | 3.4298e+06 | 1.82747 | 8.62484 | 1.67212 | 0.00645781 | 0.0245498 | 0.00502096 | 5(Loss) |
### Marine IK Reverse Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.11324953219104354%)

### Marine IK Reverse Test (Prettified) Write (Reused) Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.09606281201688949%)


----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 770.945 | 0.0890068 | 7068.76ms | 1834197 | 160 | 6.52547e+08 | 2.26894e+06 | 6.54949 | 25.5085 | 5.31713 | 0.0410111 | 0.0844216 | 0.00172268 | 1(Win) |
| simdjson (reflection) | 722.794 | 0.0751318 | 7553.72ms | 1834197 | 30 | 9.91817e+07 | 2.42009e+06 | 6.98498 | 30.8548 | 5.23246 | 0.035374 | 0.136569 | 0.00646085 | 2(Loss) |
| jsonifier (two-stage) | 720.765 | 0.0868554 | 7557.01ms | 1834197 | 160 | 7.10917e+08 | 2.4269e+06 | 6.97331 | 29.3611 | 5.93817 | 0.0328755 | 0.14785 | 0.0116128 | 3(Loss) |
| glaze | 628.269 | 0.136476 | 8631.28ms | 1834197 | 30 | 4.33145e+08 | 2.7842e+06 | 7.99573 | 31.9325 | 6.35393 | 0.0330566 | 0.0835689 | 0.0206071 | 4(Loss) |
| simdjson (ondemand) | 599.401 | 0.137463 | 9137.58ms | 1834197 | 40 | 6.4371e+08 | 2.91829e+06 | 8.39532 | 33.4868 | 6.09747 | 0.0423268 | 0.148991 | 0.0116291 | 5(Loss) |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 852.795 | 0.0729786 | 7089.59ms | 1834197 | 80 | 1.7926e+08 | 2.05117e+06 | 5.92859 | 22.5344 | 4.62848 | 0.0402192 | 0.0573226 | 0.00142012 | 1(Win) |
| simdjson (reflection) | 816.467 | 0.0709025 | 7333.68ms | 1834197 | 40 | 9.22991e+07 | 2.14243e+06 | 6.18291 | 27.8493 | 4.5312 | 0.0306476 | 0.11203 | 0.00368927 | 2(Loss) |
| jsonifier (two-stage) | 795.751 | 0.116593 | 7558.37ms | 1834197 | 80 | 5.25499e+08 | 2.19821e+06 | 6.32056 | 26.3872 | 5.24962 | 0.0319844 | 0.120685 | 0.00850868 | 3(Loss) |
| glaze | 696.079 | 0.132742 | 8530.19ms | 1834197 | 30 | 3.33823e+08 | 2.51297e+06 | 7.2436 | 28.9536 | 5.66319 | 0.0319498 | 0.0596895 | 0.0104331 | 4(Loss) |
| simdjson (ondemand) | 662.783 | 0.0870451 | 9000.77ms | 1834197 | 80 | 4.2221e+08 | 2.63922e+06 | 7.61172 | 30.4952 | 5.40543 | 0.0377797 | 0.11863 | 0.00918987 | 5(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1256.81 | 0.0432911 | 8862.14ms | 1834197 | 320 | 1.16171e+08 | 1.3918e+06 | 4.01109 | 12.0529 | 0.887663 | 0.0100307 | 0.0614693 | 0.00211789 | 1(Win) |
| glaze | 941.309 | 0.264323 | 5771.07ms | 1833577 | 160 | 3.85768e+09 | 1.85766e+06 | 5.3149 | 15.8114 | 1.02018 | 0.000942349 | 0.0821534 | 0.00819269 | 2(Loss) |
| simdjson (reflection) | 883.752 | 0.096249 | 6454.66ms | 1922245 | 160 | 6.37777e+08 | 2.07433e+06 | 5.7128 | 18.1187 | 2.02075 | 0.0255959 | 0.0516856 | 0.00134918 | 3(Loss) |

----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1255.51 | 0.170065 | 8811.49ms | 1834197 | 30 | 1.68423e+08 | 1.39324e+06 | 4.00763 | 12.0527 | 0.887623 | 0.0101166 | 0.0615245 | 0.00203052 | 1(Win) |
| glaze | 1006.89 | 0.619696 | 5450.34ms | 1833577 | 30 | 3.47464e+09 | 1.73666e+06 | 5.00007 | 15.8105 | 1.01999 | 0.000943838 | 0.0494495 | 0.00178549 | 2(Loss) |
| simdjson (reflection) | 881.68 | 0.245128 | 6480.62ms | 1922245 | 40 | 1.03906e+09 | 2.07921e+06 | 5.72789 | 18.1185 | 2.02071 | 0.0255104 | 0.0517479 | 0.00208545 | 3(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 3283.21 | 0.231883 | 8956.94ms | 9930848 | 80 | 3.57935e+09 | 2.88461e+06 | 1.52914 | 6.37424 | 1.13425 | 0.0066824 | 0.0548086 | 0.00778472 | 1(Tie) |
| jsonifier STATISTICAL TIE | 3279.68 | 0.257202 | 9014.24ms | 9930848 | 80 | 4.41316e+09 | 2.88772e+06 | 1.53961 | 6.67443 | 1.51687 | 0.0074757 | 0.0304723 | 0.00697658 | 1(Tie) |
| simdjson (reflection) STATISTICAL TIE | 3264.37 | 0.186975 | 9140.12ms | 9930848 | 30 | 8.82801e+08 | 2.90126e+06 | 1.54366 | 6.82894 | 1.01142 | 0.00621693 | 0.0519576 | 0.00548723 | 1(Tie) |
| simdjson (ondemand) | 2812.69 | 0.351456 | 5111.88ms | 9930848 | 40 | 5.60184e+09 | 3.36716e+06 | 1.7895 | 7.31412 | 1.17092 | 0.00746405 | 0.0539039 | 0.00428781 | 4(Loss) |
| glaze | 2540.54 | 0.230946 | 5592.53ms | 9930848 | 80 | 5.92971e+09 | 3.72787e+06 | 1.97428 | 9.17448 | 1.79947 | 0.00679014 | 0.0293916 | 0.0071493 | 5(Loss) |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 3653.1 | 0.14847 | 8817.05ms | 9930848 | 40 | 5.92637e+08 | 2.59254e+06 | 1.38159 | 6.27314 | 0.88172 | 0.00536145 | 0.0469091 | 0.00386701 | 1(Win) |
| jsonifier (two-stage) | 3612.19 | 0.0891818 | 8900.7ms | 9930848 | 160 | 8.7479e+08 | 2.6219e+06 | 1.39205 | 5.82448 | 1.0069 | 0.00649823 | 0.0497637 | 0.00392346 | 2(Loss) |
| jsonifier | 3581.5 | 0.297909 | 8934.26ms | 9930848 | 80 | 4.9648e+09 | 2.64437e+06 | 1.40926 | 6.12508 | 1.38962 | 0.00738453 | 0.0254119 | 0.00320514 | 3(Loss) |
| simdjson (ondemand) | 3035.71 | 0.180474 | 5064.93ms | 9930848 | 80 | 2.53613e+09 | 3.11979e+06 | 1.66047 | 6.7616 | 1.04309 | 0.00660383 | 0.0479752 | 0.00836639 | 4(Loss) |
| glaze | 2713.38 | 0.253905 | 5626.95ms | 9930848 | 80 | 6.28323e+09 | 3.49041e+06 | 1.8475 | 8.62457 | 1.67199 | 0.00657991 | 0.0249394 | 0.00751558 | 5(Loss) |
### Marine IK Test (Prettified) Write Did Not Converge

Excluded from rankings. Libraries that missed the RSE / mean-shift thresholds:

- simdjson (reflection) (RSE 0.12520975642423027%)


----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6115.31 | 0.171644 | 9889.05ms | 9930848 | 30 | 2.1199e+08 | 1.5487e+06 | 0.82604 | 2.32212 | 0.166026 | 0.00187029 | 0.0251285 | 0.000430705 | 1(Win) |
| glaze | 4013.41 | 0.316176 | 7339.51ms | 9930228 | 160 | 8.9057e+09 | 2.35964e+06 | 1.25281 | 4.42747 | 0.414372 | 0.000734462 | 0.0223981 | 0.0028923 | 2(Loss) |
| simdjson (reflection) | 200.321 | 1.08254 | 14399.5ms | 10018896 | 30 | 7.99822e+12 | 4.76972e+07 | 21.478 | 70.2579 | 13.4377 | 0.0604284 | 0.280136 | 0.152098 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 1198.5 | 0.208771 | 6587.67ms | 642697 | 30 | 3.41975e+07 | 511407 | 4.20266 | 18.6111 | 3.36144 | 0.014101 | 0.0275562 | 0.00017883 | 1(Win) |
| simdjson (ondemand) | 1172.05 | 0.432998 | 6738.7ms | 642697 | 160 | 8.2037e+08 | 522949 | 4.28653 | 20.7936 | 3.18988 | 0.0123273 | 0.0685286 | 6.43285e-05 | 2(Loss) |
| simdjson (reflection) STATISTICAL TIE | 1148.53 | 0.110179 | 6863.87ms | 642697 | 40 | 1.38288e+07 | 533658 | 4.39813 | 21.4169 | 3.17852 | 0.0120847 | 0.0604293 | 6.62054e-05 | 3(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1146.5 | 0.110434 | 6907.41ms | 642697 | 320 | 1.11537e+08 | 534603 | 4.3808 | 20.4987 | 3.82634 | 0.0170913 | 0.0552612 | 8.03013e-05 | 3(Tie) |
| jsonifier | 1074.2 | 0.112656 | 7345.56ms | 642697 | 320 | 1.3222e+08 | 570585 | 4.7118 | 18.1462 | 3.56504 | 0.0401681 | 0.0164423 | 0.000182867 | 5(Loss) |

----
### Mesh Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| glaze | 1329.68 | 0.0603803 | 6287.71ms | 642697 | 640 | 4.95777e+07 | 460954 | 3.81374 | 17.4437 | 3.10126 | 0.0131628 | 0.00421568 | 6.0356e-05 | 1(Win) |
| simdjson (ondemand) | 1317.31 | 0.104432 | 6366.85ms | 642697 | 320 | 7.55533e+07 | 465284 | 3.83233 | 19.5866 | 2.9196 | 0.0105728 | 0.0265559 | 4.84093e-05 | 2(Loss) |
| simdjson (reflection) | 1224.38 | 0.152085 | 6883.82ms | 642697 | 80 | 4.6371e+07 | 500599 | 4.14481 | 20.2682 | 2.91873 | 0.0111521 | 0.0498203 | 0.000115159 | 3(Loss) |
| jsonifier (two-stage) | 1199.18 | 0.180268 | 6922.28ms | 642697 | 160 | 1.35832e+08 | 511118 | 4.18938 | 19.3888 | 3.57686 | 0.0169882 | 0.0485073 | 7.89349e-05 | 4(Loss) |
| jsonifier | 1139.95 | 0.163006 | 7257.71ms | 642697 | 40 | 3.07262e+07 | 537677 | 4.43137 | 17.0365 | 3.31558 | 0.0398743 | 0.0135458 | 3.39585e-05 | 5(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2369.39 | 0.110823 | 6904.29ms | 642697 | 80 | 6.57489e+06 | 258684 | 2.15563 | 7.38722 | 0.752028 | 0.000697452 | 0.00730914 | 1.03665e-05 | 1(Win) |
| glaze | 1592.37 | 0.757358 | 5071.9ms | 642692 | 320 | 2.71939e+09 | 384910 | 3.21626 | 10.1215 | 0.666387 | 0.000141874 | 0.0408476 | 8.66132e-05 | 2(Loss) |
| simdjson (reflection) | 1279.19 | 0.292655 | 6167.87ms | 643373 | 160 | 3.15274e+08 | 479654 | 3.96513 | 14.5168 | 1.45439 | 0.00527006 | 0.0042643 | 7.39559e-05 | 3(Loss) |

----
### Mesh Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2396.05 | 0.0349177 | 6885.77ms | 642697 | 40 | 319132 | 255806 | 2.1486 | 7.38636 | 0.751832 | 0.000603006 | 0.00712478 | 9.64685e-06 | 1(Win) |
| glaze | 1706.87 | 0.288664 | 9366.51ms | 642692 | 1280 | 1.37531e+09 | 359089 | 2.97746 | 10.1192 | 0.665889 | 0.00014024 | 0.0079821 | 2.03842e-05 | 2(Loss) |
| simdjson (reflection) | 1279.98 | 0.0321413 | 6169.84ms | 643373 | 40 | 949526 | 479358 | 3.94817 | 14.516 | 1.45419 | 0.00520173 | 0.00354973 | 4.56189e-05 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2202.69 | 0.0342894 | 6895.92ms | 1225964 | 640 | 2.12007e+07 | 530792 | 2.29482 | 11.5722 | 1.68862 | 0.00491538 | 0.0623949 | 4.84313e-05 | 1(Win) |
| simdjson (reflection) | 2144.69 | 0.0492026 | 7051.93ms | 1225964 | 320 | 2.30225e+07 | 545147 | 2.36083 | 11.8994 | 1.68275 | 0.00487798 | 0.0581428 | 4.55432e-05 | 2(Loss) |
| jsonifier (two-stage) | 2061.6 | 0.198979 | 7331.11ms | 1225964 | 640 | 8.14973e+08 | 567119 | 2.43997 | 11.4529 | 2.04415 | 0.00738208 | 0.0591822 | 9.35629e-05 | 3(Loss) |
| glaze | 1826.52 | 0.0469431 | 8239.72ms | 1225964 | 320 | 2.88936e+07 | 640110 | 2.77297 | 12.6228 | 2.53116 | 0.0137975 | 0.0294329 | 9.25598e-05 | 4(Loss) |
| jsonifier | 1786.1 | 0.172022 | 8415.45ms | 1225964 | 30 | 3.80392e+07 | 654593 | 2.81815 | 12.5637 | 2.76686 | 0.0171196 | 0.0238374 | 4.49986e-05 | 5(Loss) |

----
### Mesh Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (ondemand) | 2428.07 | 0.128944 | 6546.2ms | 1225964 | 640 | 2.46728e+08 | 481522 | 2.0852 | 10.9398 | 1.54704 | 0.0043834 | 0.0379316 | 2.80443e-05 | 1(Win) |
| simdjson (reflection) | 2266.51 | 0.135982 | 7052.98ms | 1225964 | 40 | 1.96818e+07 | 515845 | 2.23666 | 11.2972 | 1.5466 | 0.00473334 | 0.0518752 | 0.000108425 | 2(Loss) |
| jsonifier (two-stage) | 2167.27 | 0.158979 | 7305.09ms | 1225964 | 160 | 1.17686e+08 | 539466 | 2.31731 | 10.8713 | 1.91341 | 0.00713992 | 0.0539128 | 1.91839e-05 | 3(Loss) |
| glaze | 1950.9 | 0.0314982 | 8027.59ms | 1225964 | 320 | 1.14027e+07 | 599297 | 2.58894 | 12.0109 | 2.39492 | 0.0134438 | 0.0127756 | 3.34278e-05 | 4(Loss) |
| jsonifier | 1875.54 | 0.0828202 | 8366.87ms | 1225964 | 160 | 4.26478e+07 | 623378 | 2.71173 | 11.9821 | 2.63611 | 0.01694 | 0.0211525 | 1.99792e-05 | 5(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4406.14 | 0.164327 | 7016.26ms | 1225964 | 40 | 7.60533e+06 | 265350 | 1.15581 | 3.91092 | 0.394248 | 0.000415082 | 0.0149036 | 8.97253e-06 | 1(Win) |
| glaze | 2702.52 | 0.0328012 | 5692.97ms | 1225970 | 30 | 604123 | 432625 | 1.90453 | 6.73879 | 0.654452 | 0.000117839 | 0.0339283 | 1.20993e-05 | 2(Loss) |
| simdjson (reflection) | 169.497 | 0.357621 | 10485.8ms | 1226640 | 40 | 2.43679e+10 | 6.9017e+06 | 29.981 | 106.997 | 19.7451 | 0.120281 | 0.597089 | 0.0470857 | 3(Loss) |

----
### Mesh Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4365.82 | 0.131309 | 7028.99ms | 1225964 | 40 | 4.94621e+06 | 267801 | 1.16205 | 3.91047 | 0.394146 | 0.000441632 | 0.0147448 | 1.66196e-05 | 1(Win) |
| glaze | 2768.54 | 0.469698 | 5441.41ms | 1225970 | 640 | 2.51812e+09 | 422308 | 1.83425 | 6.73707 | 0.654079 | 0.000116226 | 0.0145552 | 2.72985e-05 | 2(Loss) |
| simdjson (reflection) | 163.399 | 0.355433 | 10598.1ms | 1226640 | 40 | 2.59007e+10 | 7.15926e+06 | 30.9122 | 106.997 | 19.7451 | 0.120648 | 0.596057 | 0.150476 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1448.8 | 0.0615711 | 7113.24ms | 409725 | 40 | 1.10302e+06 | 269702 | 3.48722 | 13.7265 | 2.44404 | 0.0216838 | 0.0287921 | 0.000125816 | 1(Win) |
| jsonifier (two-stage) | 1409.06 | 0.320654 | 7309.75ms | 409725 | 640 | 5.06033e+08 | 277308 | 3.5934 | 16.0548 | 2.74799 | 0.0131468 | 0.0608452 | 0.000439083 | 2(Loss) |
| glaze | 1205.89 | 0.130843 | 8456.3ms | 409725 | 320 | 5.75198e+07 | 324029 | 4.19405 | 17.272 | 3.36758 | 0.0249849 | 0.0158804 | 0.000189533 | 3(Loss) |
| simdjson (reflection) | 1183.75 | 0.0317737 | 8647.65ms | 409725 | 640 | 7.04017e+06 | 330091 | 4.27092 | 17.058 | 2.96441 | 0.0129837 | 0.0564254 | 0.00018377 | 4(Loss) |
| simdjson (ondemand) | 855.367 | 0.191396 | 5917.89ms | 409725 | 640 | 4.89244e+08 | 456815 | 5.92553 | 19.4316 | 3.51442 | 0.0154128 | 0.0630655 | 0.000199032 | 5(Loss) |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2072.48 | 0.068037 | 6250.19ms | 409725 | 640 | 1.05311e+07 | 188540 | 2.45453 | 10.4102 | 1.78059 | 0.0156243 | 0.00212775 | 8.08431e-05 | 1(Win) |
| jsonifier (two-stage) | 1989.65 | 0.0442469 | 6468ms | 409725 | 160 | 1.20814e+06 | 196388 | 2.53952 | 12.7382 | 2.08478 | 0.00778806 | 0.0118024 | 2.32778e-05 | 2(Loss) |
| glaze | 1538.81 | 0.106334 | 7895.93ms | 409725 | 1280 | 9.33194e+07 | 253926 | 3.28979 | 14.3854 | 2.75641 | 0.0201064 | 0.00323572 | 6.04273e-05 | 3(Loss) |
| simdjson (reflection) | 1461.15 | 0.0292432 | 8167.72ms | 409725 | 1280 | 7.82804e+06 | 267422 | 3.45501 | 14.552 | 2.38076 | 0.00561987 | 0.0292014 | 5.48901e-05 | 4(Loss) |
| simdjson (ondemand) | 1066.82 | 0.176344 | 5307ms | 409725 | 30 | 1.25154e+07 | 366270 | 4.76066 | 16.408 | 2.86936 | 0.00641089 | 0.0170745 | 1.9688e-05 | 5(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13799.6 | 0.141546 | 3647.12ms | 409725 | 30 | 48191.3 | 28315.6 | 0.366655 | 1.92482 | 0.268578 | 0.000114223 | 0.00599272 | 0.00014587 | 1(Win) |
| simdjson (reflection) | 11598.2 | 0.0400002 | 4123.63ms | 409725 | 1280 | 232456 | 33690.2 | 0.436068 | 2.38964 | 0.298903 | 0.00085671 | 0.00389404 | 2.05073e-05 | 2(Loss) |
| glaze | 3653.57 | 0.195845 | 5897.29ms | 409725 | 640 | 2.80772e+07 | 106948 | 1.37184 | 5.57974 | 0.872036 | 0.0101186 | 0.032883 | 4.59149e-05 | 3(Loss) |

----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13872.1 | 0.0399873 | 3578.04ms | 409725 | 2560 | 324777 | 28167.7 | 0.364479 | 1.92348 | 0.268273 | 1.79951e-05 | 0.00488588 | 1.15331e-05 | 1(Win) |
| simdjson (reflection) | 11747.6 | 0.0188227 | 4080.1ms | 409725 | 2560 | 100344 | 33261.7 | 0.430617 | 2.38839 | 0.29862 | 0.00074745 | 9.59599e-05 | 9.6797e-06 | 2(Loss) |
| glaze | 4123.9 | 0.121694 | 5240.99ms | 409725 | 1280 | 1.70183e+07 | 94751.1 | 1.22617 | 5.56317 | 0.86829 | 0.0100663 | 0.00291584 | 2.95339e-05 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2442.33 | 0.218577 | 8040.41ms | 785750 | 160 | 7.19595e+07 | 306817 | 2.05251 | 9.00653 | 1.45118 | 0.00751148 | 0.0563827 | 9.67945e-05 | 1(Win) |
| simdjson (reflection) STATISTICAL TIE | 2110.83 | 0.0265463 | 9324.68ms | 785750 | 1280 | 1.13679e+07 | 355002 | 2.40006 | 9.53754 | 1.56935 | 0.00766562 | 0.0518076 | 0.000183304 | 2(Tie) |
| jsonifier STATISTICAL TIE | 2108.86 | 0.057348 | 9264.48ms | 785750 | 640 | 2.6576e+07 | 355334 | 2.39426 | 9.21438 | 1.84104 | 0.0130083 | 0.0293265 | 0.000174211 | 2(Tie) |
| glaze | 1841.12 | 0.129518 | 5265.3ms | 785750 | 160 | 4.44617e+07 | 407008 | 2.75346 | 11.6756 | 2.29973 | 0.0135073 | 0.0220012 | 0.000358328 | 4(Loss) |
| simdjson (ondemand) | 1569.52 | 0.229402 | 6180.9ms | 785750 | 40 | 4.79831e+07 | 477437 | 3.2502 | 10.7939 | 1.86093 | 0.00877986 | 0.0576614 | 0.000126885 | 5(Loss) |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3338.06 | 0.0748132 | 7154.7ms | 785750 | 1280 | 3.61033e+07 | 224486 | 1.51197 | 7.27865 | 1.1056 | 0.00481493 | 0.026187 | 4.17684e-05 | 1(Win) |
| jsonifier | 2718.91 | 0.031628 | 8446.86ms | 785750 | 160 | 1.21575e+06 | 275607 | 1.85898 | 7.48646 | 1.4954 | 0.00995206 | 0.00600954 | 3.75835e-05 | 2(Loss) |
| simdjson (reflection) | 2567.27 | 0.0781223 | 8859.3ms | 785750 | 160 | 8.31945e+06 | 291885 | 1.96916 | 8.23477 | 1.26595 | 0.00388362 | 0.0330396 | 2.73624e-05 | 3(Loss) |
| glaze | 2208.4 | 0.128182 | 5040.95ms | 785750 | 160 | 3.02683e+07 | 339317 | 2.29525 | 10.1755 | 1.98228 | 0.011004 | 0.0065742 | 7.35444e-05 | 4(Loss) |
| simdjson (ondemand) | 1920.68 | 0.0310148 | 5622.98ms | 785750 | 640 | 9.37083e+06 | 390148 | 2.63524 | 9.21871 | 1.52484 | 0.00380626 | 0.0239337 | 3.93891e-05 | 5(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18436.3 | 0.0771643 | 4862.84ms | 785750 | 640 | 629556 | 40645.3 | 0.274147 | 1.10215 | 0.140093 | 5.16604e-05 | 0.0105517 | 1.04856e-05 | 1(Win) |
| glaze | 4837.51 | 0.164167 | 8372.56ms | 785750 | 1280 | 8.27765e+07 | 154904 | 1.04219 | 4.36978 | 0.633689 | 0.0059445 | 0.0548937 | 2.37969e-05 | 2(Loss) |
| simdjson (reflection) | 523.445 | 0.604141 | 8965.63ms | 785750 | 160 | 1.1968e+10 | 1.43157e+06 | 9.61684 | 37.3872 | 6.59771 | 0.0285243 | 0.359952 | 0.000185921 | 3(Loss) |

----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 18653.9 | 0.094409 | 4844.06ms | 785750 | 640 | 920530 | 40171.3 | 0.272942 | 1.10145 | 0.139935 | 2.72471e-05 | 0.0102651 | 1.99053e-06 | 1(Win) |
| glaze | 5763.84 | 0.114643 | 7057.66ms | 785750 | 320 | 7.10869e+06 | 130009 | 0.878222 | 4.36043 | 0.631539 | 0.00591733 | 0.017331 | 5.82445e-05 | 2(Loss) |
| simdjson (reflection) | 530.938 | 0.459028 | 9004.53ms | 785750 | 320 | 1.34311e+10 | 1.41137e+06 | 9.54151 | 37.3876 | 6.59784 | 0.0286392 | 0.359775 | 0.0104704 | 3(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 7323.66 | 0.0688623 | 4173.08ms | 264040 | 640 | 358778 | 34382.8 | 0.69078 | 3.02809 | 0.373421 | 0.000638877 | 2.03568e-06 | 9.70497e-07 | 1(Tie) |
| jsonifier STATISTICAL TIE | 7316.36 | 0.0232818 | 4176.53ms | 264040 | 4890 | 313973 | 34417.1 | 0.692077 | 3.0301 | 0.373887 | 0.000666208 | 3.41632e-06 | 1.68764e-06 | 1(Tie) |
| simdjson (ondemand) | 5426.59 | 0.0154446 | 5385.24ms | 264040 | 4890 | 251158 | 46402.7 | 0.931048 | 4.47144 | 0.713494 | 0.00113472 | 4.30002e-06 | 2.24373e-06 | 3(Loss) |
| simdjson (reflection) | 5313.27 | 0.0253378 | 5504.12ms | 264040 | 2560 | 369143 | 47392.3 | 0.952752 | 4.4555 | 0.714657 | 0.000874002 | 3.9456e-06 | 1.79453e-06 | 4(Loss) |
| glaze | 2608.08 | 0.0416968 | 5324.75ms | 264040 | 2560 | 4.149e+06 | 96549.2 | 1.93795 | 8.89772 | 1.36436 | 0.00266749 | 6.31267e-06 | 3.5861e-06 | 5(Loss) |

----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 7498.06 | 0.025051 | 4157.54ms | 264040 | 4890 | 346099 | 33583.1 | 0.674044 | 2.97404 | 0.361294 | 0.000611136 | 6.00547e-06 | 4.16371e-06 | 1(Win) |
| jsonifier | 7484.82 | 0.0235476 | 4160.22ms | 264040 | 4890 | 306888 | 33642.5 | 0.675471 | 2.97591 | 0.361718 | 0.000649836 | 2.38391e-06 | 1.13774e-06 | 2(Loss) |
| simdjson (ondemand) | 5527.63 | 0.0252449 | 5346.88ms | 264040 | 1280 | 169285 | 45554.4 | 0.914643 | 4.40748 | 0.702326 | 0.00118907 | 3.03576e-06 | 1.48829e-06 | 3(Loss) |
| simdjson (reflection) | 5315.77 | 0.0216016 | 5551.73ms | 264040 | 4890 | 512023 | 47370 | 0.951593 | 4.42746 | 0.709124 | 0.000993821 | 7.72641e-06 | 5.43234e-06 | 4(Loss) |
| glaze | 2646.39 | 0.0931083 | 5274.08ms | 264040 | 320 | 2.51164e+06 | 95151.5 | 1.91314 | 8.81993 | 1.34846 | 0.00263604 | 1.71612e-06 | 2.84048e-07 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 8844.65 | 0.0511288 | 5040.31ms | 399947 | 160 | 77784.7 | 43124.3 | 0.571808 | 2.50773 | 0.259803 | 0.000409648 | 9.68878e-07 | 3.28168e-07 | 1(Win) |
| jsonifier | 8820.44 | 0.0171207 | 5064.88ms | 399947 | 4890 | 268027 | 43242.7 | 0.573138 | 2.50967 | 0.26026 | 0.000424157 | 5.07685e-06 | 3.50455e-06 | 2(Loss) |
| simdjson (ondemand) | 7138.65 | 0.0311142 | 6090.04ms | 399947 | 2560 | 707504 | 53430.2 | 0.707667 | 3.4331 | 0.490763 | 0.000628884 | 3.18988e-06 | 1.69651e-06 | 3(Loss) |
| simdjson (reflection) | 6966.05 | 0.043112 | 6224.96ms | 399947 | 1280 | 713242 | 54754 | 0.725351 | 3.42338 | 0.491723 | 0.000523333 | 3.66064e-06 | 2.17998e-06 | 4(Loss) |
| glaze | 3416.38 | 0.061173 | 6085.68ms | 399947 | 1280 | 5.97039e+06 | 111644 | 1.47391 | 7.26606 | 1.20377 | 0.0022491 | 7.60452e-06 | 4.57678e-06 | 5(Loss) |

----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 9010.13 | 0.128117 | 5028.65ms | 399947 | 30 | 88242.1 | 42332.3 | 0.561419 | 2.47378 | 0.252236 | 0.000438391 | 6.0008e-06 | 3.58381e-06 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 9000.45 | 0.0791143 | 5027.87ms | 399947 | 640 | 719394 | 42377.8 | 0.560875 | 2.47258 | 0.251938 | 0.000419095 | 2.07059e-06 | 1.22282e-06 | 1(Tie) |
| simdjson (ondemand) | 7204.64 | 0.0526643 | 6094.99ms | 399947 | 1280 | 995002 | 52940.8 | 0.702414 | 3.39606 | 0.484564 | 0.000788147 | 3.00821e-06 | 1.83227e-06 | 3(Loss) |
| simdjson (reflection) | 6963.7 | 0.0232935 | 6307.27ms | 399947 | 2560 | 416711 | 54772.5 | 0.725372 | 3.40943 | 0.489132 | 0.000664624 | 1.35272e-06 | 6.15316e-07 | 4(Loss) |
| glaze | 3452.88 | 0.0672286 | 6063.59ms | 399947 | 1280 | 7.05928e+06 | 110464 | 1.45735 | 7.21492 | 1.19343 | 0.00223547 | 5.79764e-06 | 3.73096e-06 | 5(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1988.43 | 0.277706 | 6879.98ms | 264040 | 30 | 3.71033e+06 | 126637 | 2.54176 | 7.65632 | 1.28522 | 0.0156674 | 0.000705449 | 0.000129147 | 1(Win) |
| glaze | 1856.54 | 0.13082 | 7314.37ms | 264040 | 320 | 1.00747e+07 | 135633 | 2.68142 | 10.3881 | 1.82375 | 0.00710977 | 0.000274911 | 0.000156652 | 2(Loss) |
| jsonifier (two-stage) | 1796.53 | 0.100337 | 7560.14ms | 264040 | 640 | 1.26583e+07 | 140163 | 2.80083 | 8.8738 | 1.41235 | 0.0143351 | 0.00276832 | 8.49895e-05 | 3(Loss) |
| simdjson (reflection) | 1626.47 | 0.0621233 | 8313.08ms | 264040 | 2560 | 2.36808e+07 | 154819 | 3.09425 | 9.92624 | 1.57839 | 0.0117474 | 0.000869803 | 0.000178466 | 4(Loss) |
| simdjson (ondemand) | 1329.93 | 0.0721687 | 5035.01ms | 264040 | 1280 | 2.38995e+07 | 189339 | 3.7812 | 11.2058 | 1.99288 | 0.0124353 | 0.0025894 | 0.000147859 | 5(Loss) |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2554.17 | 0.0394578 | 6257.38ms | 264040 | 2560 | 3.87389e+06 | 98587.1 | 1.9805 | 6.328 | 0.998997 | 0.0116593 | 2.70718e-05 | 1.42039e-05 | 1(Win) |
| glaze | 2275.75 | 0.0937538 | 6732.94ms | 264040 | 640 | 6.8873e+06 | 110649 | 2.21002 | 9.04149 | 1.53206 | 0.00634638 | 2.01615e-05 | 1.10956e-05 | 2(Loss) |
| jsonifier (two-stage) | 2251.06 | 0.147236 | 6627.43ms | 264040 | 320 | 8.6805e+06 | 111862 | 2.23704 | 7.54802 | 1.12652 | 0.0107208 | 7.20653e-05 | 2.57892e-05 | 3(Loss) |
| simdjson (reflection) | 1952.46 | 0.0598628 | 7659.44ms | 264040 | 1280 | 7.62959e+06 | 128970 | 2.57968 | 8.98855 | 1.36184 | 0.00382388 | 0.00045524 | 1.57854e-05 | 4(Loss) |
| simdjson (ondemand) | 1572.16 | 0.0293116 | 9380.4ms | 264040 | 2560 | 5.64243e+06 | 160167 | 3.21266 | 9.9487 | 1.7239 | 0.00893691 | 0.000240313 | 7.62669e-05 | 5(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 16717 | 0.0956104 | 2270.22ms | 264040 | 30 | 6222.38 | 15063 | 0.303387 | 1.17964 | 0.164536 | 4.83513e-05 | 2.04514e-05 | 1.07307e-05 | 1(Win) |
| simdjson (reflection) | 13016 | 0.0526524 | 2704.12ms | 264040 | 320 | 33202.5 | 19346 | 0.389109 | 1.41671 | 0.203886 | 0.000275834 | 8.17821e-06 | 3.85832e-06 | 2(Loss) |
| glaze | 6769.97 | 0.147708 | 4482.43ms | 263923 | 4890 | 1.47467e+07 | 37178.4 | 0.746247 | 2.34508 | 0.343354 | 0.00033819 | 0.00300961 | 3.90281e-05 | 3(Loss) |

----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 16635.8 | 0.0295004 | 2264.41ms | 264040 | 4890 | 97502.6 | 15136.5 | 0.302532 | 1.17764 | 0.164081 | 2.80354e-05 | 1.16802e-05 | 5.71968e-06 | 1(Win) |
| simdjson (reflection) | 12769.1 | 0.0978129 | 2708ms | 264040 | 160 | 59529.7 | 19720.2 | 0.389578 | 1.41462 | 0.203412 | 0.000282722 | 4.87616e-06 | 3.31389e-06 | 2(Loss) |
| glaze | 7941.29 | 0.364622 | 3934.79ms | 263923 | 640 | 8.54747e+06 | 31694.7 | 0.635091 | 2.32155 | 0.338114 | 0.00033745 | 1.13433e-05 | 5.99133e-06 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2567.45 | 0.153534 | 8097.92ms | 399947 | 40 | 2.081e+06 | 148560 | 1.96848 | 6.37077 | 0.94524 | 0.00905389 | 0.00667388 | 6.15081e-05 | 1(Win) |
| simdjson (reflection) | 2335.16 | 0.0498024 | 8736.16ms | 399947 | 2560 | 1.69399e+07 | 163337 | 2.14474 | 7.03625 | 1.06255 | 0.00774662 | 0.00197286 | 0.000113032 | 2(Loss) |
| glaze | 2130.75 | 0.0974754 | 9695.97ms | 399947 | 80 | 2.43569e+06 | 179007 | 2.36961 | 8.70393 | 1.56699 | 0.00568085 | 0.00260666 | 2.94414e-05 | 3(Loss) |
| jsonifier | 1980.99 | 0.034808 | 5132.64ms | 399947 | 1280 | 5.74921e+06 | 192540 | 2.54999 | 6.51029 | 1.23822 | 0.0102074 | 0.00418393 | 6.47508e-05 | 4(Loss) |
| simdjson (ondemand) | 1922.94 | 0.113158 | 5264.2ms | 399947 | 640 | 3.22422e+07 | 198352 | 2.60774 | 7.88758 | 1.33844 | 0.00820192 | 0.00501792 | 6.50516e-05 | 5(Loss) |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3130.14 | 0.0811636 | 7456.45ms | 399947 | 1280 | 1.25202e+07 | 121854 | 1.60369 | 5.49871 | 0.757046 | 0.0069947 | 0.000569308 | 1.98015e-05 | 1(Win) |
| simdjson (reflection) | 2614.35 | 0.0625069 | 8466.08ms | 399947 | 1280 | 1.06449e+07 | 145894 | 1.91849 | 6.42236 | 0.920556 | 0.00577698 | 0.00176678 | 3.59364e-05 | 2(Loss) |
| glaze | 2456.59 | 0.043664 | 9021.54ms | 399947 | 1280 | 5.883e+06 | 155264 | 2.05188 | 7.8321 | 1.37927 | 0.00475107 | 4.89733e-05 | 1.06987e-05 | 3(Loss) |
| jsonifier | 2294.78 | 0.068757 | 9054.55ms | 399947 | 320 | 4.17935e+06 | 166212 | 2.20306 | 5.63521 | 1.04932 | 0.00824233 | 0.000223686 | 1.40175e-05 | 4(Loss) |
| simdjson (ondemand) | 2251.27 | 0.265651 | 9862.91ms | 399947 | 40 | 8.1028e+06 | 169424 | 2.23436 | 7.04977 | 1.15768 | 0.00606493 | 0.000280725 | 3.10666e-05 | 5(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 20525.8 | 0.0532294 | 2619.59ms | 399947 | 1280 | 125233 | 18582.5 | 0.246965 | 0.830453 | 0.109782 | 2.30773e-05 | 2.44642e-05 | 1.61428e-05 | 1(Win) |
| glaze | 4863.73 | 0.212207 | 8657.72ms | 399830 | 1280 | 3.54275e+07 | 78398.2 | 1.0331 | 2.77597 | 0.355369 | 0.000412689 | 0.008356 | 1.62804e-05 | 2(Loss) |
| simdjson (reflection) | 525.988 | 0.547746 | 9323.36ms | 399947 | 640 | 1.0097e+10 | 725149 | 9.51235 | 28.6679 | 4.83543 | 0.0581211 | 0.253172 | 0.000669393 | 3(Loss) |

----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 20418.1 | 0.0340444 | 2624.69ms | 399947 | 4890 | 197777 | 18680.5 | 0.245179 | 0.829132 | 0.109485 | 1.53752e-05 | 1.11549e-05 | 5.47005e-06 | 1(Win) |
| glaze | 5673.42 | 0.195399 | 7493.14ms | 399830 | 1280 | 2.20757e+07 | 67209.5 | 0.894092 | 2.76027 | 0.351727 | 0.000399891 | 5.71493e-05 | 4.35771e-05 | 2(Loss) |
| simdjson (reflection) | 528.599 | 0.85871 | 9270.18ms | 399947 | 320 | 1.22856e+10 | 721567 | 9.45791 | 28.6828 | 4.83863 | 0.0584884 | 0.249245 | 0.00123938 | 3(Loss) |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1034.49 | 0.0337755 | 1164.3ms | 4630 | 4890 | 10163 | 4268.3 | 4.94219 | 22.2803 | 4.44968 | 0.00241446 | 0.000179853 | 9.6861e-05 | 1(Win) |
| simdjson (reflection) | 950.34 | 0.032626 | 1202.13ms | 4630 | 4890 | 11236.7 | 4646.24 | 5.36327 | 26.2181 | 4.63261 | 0.00363743 | 8.01654e-05 | 3.10944e-05 | 2(Loss) |
| jsonifier (two-stage) | 943.334 | 0.0868682 | 1202.65ms | 4630 | 160 | 2645.28 | 4680.75 | 5.40687 | 25.1922 | 4.84557 | 0.00382289 | 0.000105292 | 4.18467e-05 | 3(Loss) |
| simdjson (ondemand) | 795.764 | 0.0323738 | 1297.89ms | 4630 | 4890 | 15779.3 | 5548.77 | 6.39661 | 30.1397 | 5.43067 | 0.00353607 | 0.000105253 | 4.80992e-05 | 4(Loss) |
| glaze | 744.409 | 0.0487618 | 1329.8ms | 4630 | 1280 | 10708 | 5931.57 | 6.83448 | 30.0972 | 5.77344 | 0.00446595 | 7.96436e-05 | 2.51417e-05 | 5(Loss) |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1309.95 | 0.0256237 | 1160.4ms | 4630 | 4890 | 3647.94 | 3370.76 | 3.90621 | 18.0242 | 3.4851 | 0.000718617 | 3.60413e-05 | 6.97858e-06 | 1(Win) |
| jsonifier (two-stage) | 1179.1 | 0.10442 | 1201.41ms | 4630 | 30 | 458.717 | 3744.8 | 4.33852 | 20.8965 | 3.87084 | 0.0013031 | 5.75954e-05 | 7.19942e-06 | 2(Loss) |
| simdjson (reflection) | 1109.53 | 0.0781223 | 1233.1ms | 4630 | 80 | 773.253 | 3979.61 | 4.60695 | 23.5713 | 4.0216 | 0.00197624 | 9.9892e-05 | 6.47948e-05 | 3(Loss) |
| simdjson (ondemand) | 908.676 | 0.0451359 | 1323.39ms | 4630 | 2560 | 12314.8 | 4859.28 | 5.61377 | 27.3218 | 4.78985 | 0.00125962 | 7.50034e-05 | 2.44668e-05 | 4(Loss) |
| glaze | 866.511 | 0.0531952 | 1341.95ms | 4630 | 640 | 4702.6 | 5095.73 | 5.88954 | 25.7475 | 4.78639 | 0.00437298 | 4.9946e-05 | 1.41739e-05 | 5(Loss) |

----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1924.4 | 0.192245 | 961.975ms | 4630 | 640 | 12452.6 | 2294.48 | 2.67138 | 7.88315 | 0.504536 | 0.000219695 | 6.34449e-05 | 3.10475e-05 | 1(Win) |
| glaze | 1576.1 | 0.0339387 | 1015.46ms | 4630 | 4890 | 4420.75 | 2801.55 | 3.25263 | 10.116 | 0.776027 | 0.000220665 | 3.88681e-05 | 7.64111e-06 | 2(Loss) |
| simdjson (reflection) | 1053.76 | 0.0336968 | 1152.85ms | 4630 | 80 | 159.493 | 4190.23 | 4.84883 | 15.5756 | 1.48207 | 0.00147678 | 2.96976e-05 | 2.69978e-06 | 3(Loss) |

----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1951.88 | 0.104229 | 962.662ms | 4630 | 160 | 889.52 | 2262.18 | 2.64701 | 7.77279 | 0.478834 | 0.000863931 | 3.91469e-05 | 0 | 1(Win) |
| glaze | 1701.54 | 0.0685691 | 988.45ms | 4630 | 2560 | 8105.41 | 2595.01 | 3.01299 | 9.58467 | 0.656372 | 0.000231844 | 3.17225e-05 | 8.7743e-06 | 2(Loss) |
| simdjson (reflection) | 1062.38 | 0.0264077 | 1145.91ms | 4630 | 80 | 96.3733 | 4156.26 | 4.80528 | 15.4676 | 1.45767 | 0.00062905 | 3.50972e-05 | 0 | 3(Loss) |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 2736.9 | 0.0418361 | 1254.64ms | 14795 | 2560 | 11908.4 | 5155.32 | 1.86072 | 9.09395 | 1.48435 | 0.00134827 | 3.00724e-05 | 1.07458e-05 | 1(Win) |
| jsonifier (two-stage) | 2665.67 | 0.0437333 | 1266.75ms | 14795 | 160 | 857.353 | 5293.07 | 1.91472 | 8.70585 | 1.54262 | 0.000845725 | 1.90098e-05 | 2.95708e-06 | 2(Loss) |
| jsonifier | 2535.1 | 0.0674641 | 1299.28ms | 14795 | 640 | 9023.32 | 5565.71 | 2.00836 | 9.07178 | 1.94674 | 0.00160189 | 1.299e-05 | 2.21781e-06 | 3(Loss) |
| simdjson (ondemand) | 2253.04 | 0.153185 | 1363.26ms | 14795 | 320 | 29449.3 | 6262.48 | 2.25863 | 10.6071 | 1.7927 | 0.00109877 | 1.9221e-05 | 2.95708e-06 | 4(Loss) |
| glaze | 1754.19 | 0.0624591 | 1545.67ms | 14795 | 2560 | 64611.3 | 8043.38 | 2.87762 | 13.3797 | 2.46144 | 0.00445175 | 2.84883e-05 | 9.92734e-06 | 5(Loss) |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3258.03 | 0.187783 | 1266.05ms | 14795 | 2560 | 169306 | 4330.72 | 1.56406 | 7.36812 | 1.23948 | 0.000205834 | 2.02243e-05 | 7.07587e-06 | 1(Win) |
| simdjson (reflection) | 3134.49 | 0.138221 | 1284.88ms | 14795 | 320 | 12387.9 | 4501.41 | 1.62799 | 8.32565 | 1.30673 | 0.000687732 | 1.58415e-05 | 1.47854e-06 | 2(Loss) |
| jsonifier | 3007.9 | 0.0322418 | 1300.08ms | 14795 | 2560 | 5855.73 | 4690.85 | 1.69568 | 7.73119 | 1.64258 | 0.00103889 | 1.85874e-05 | 3.30031e-06 | 3(Loss) |
| simdjson (ondemand) | 2565.47 | 0.0503762 | 1380.91ms | 14795 | 1280 | 9825.58 | 5499.82 | 1.98478 | 9.65373 | 1.57614 | 0.000618347 | 1.45742e-05 | 3.32672e-06 | 4(Loss) |
| glaze | 1964.15 | 0.0281713 | 1551.32ms | 14795 | 4890 | 20026.5 | 7183.59 | 2.57606 | 12.0273 | 2.15492 | 0.00417135 | 1.98072e-05 | 3.63523e-06 | 5(Loss) |

----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5070.44 | 0.0978393 | 1015.15ms | 14795 | 2560 | 18976.1 | 2782.72 | 1.01058 | 2.54559 | 0.159243 | 7.24221e-05 | 2.61385e-05 | 6.01977e-06 | 1(Win) |
| glaze | 3174.55 | 0.03595 | 1183.75ms | 14795 | 4890 | 12484.6 | 4444.6 | 1.60452 | 4.61095 | 0.41291 | 9.58844e-05 | 1.83973e-05 | 4.35398e-06 | 2(Loss) |
| simdjson (reflection) | 195.875 | 0.263521 | 7923.02ms | 14795 | 80 | 2.88266e+06 | 72033.8 | 25.6618 | 92.6667 | 16.7887 | 0.0769855 | 0.000148699 | 7.09699e-05 | 3(Loss) |

----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 5077.75 | 0.227056 | 1007.98ms | 14795 | 320 | 12738.1 | 2778.72 | 1.01069 | 2.50517 | 0.149848 | 6.90689e-05 | 1.41517e-05 | 0 | 1(Win) |
| glaze | 3723.18 | 0.0379872 | 1117.63ms | 14795 | 4890 | 10134.1 | 3789.67 | 1.37053 | 4.40493 | 0.366678 | 0.000171049 | 1.0491e-05 | 2.84737e-06 | 2(Loss) |
| simdjson (reflection) | 196.354 | 0.0783532 | 7957.43ms | 14795 | 4890 | 1.55016e+07 | 71858.2 | 25.6982 | 92.6673 | 16.7889 | 0.078053 | 0.000209903 | 0.000114199 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1831.72 | 0.11492 | 1002.21ms | 5092 | 40 | 371.292 | 2651.12 | 2.80383 | 10.9643 | 2.00727 | 0.00210625 | 9.81932e-06 | 0 | 1(Win) |
| jsonifier (two-stage) | 1553.01 | 0.0380718 | 1055.1ms | 5092 | 4890 | 6930.2 | 3126.9 | 3.28715 | 13.4258 | 2.31304 | 0.0010535 | 4.20886e-05 | 7.30927e-06 | 2(Loss) |
| glaze | 1488.73 | 0.0766752 | 1068.51ms | 5092 | 160 | 1000.87 | 3261.92 | 3.43954 | 14.0628 | 2.72643 | 0.000826051 | 4.54144e-05 | 1.4729e-05 | 3(Loss) |
| simdjson (reflection) | 1255.63 | 0.0797064 | 1135.71ms | 5092 | 640 | 6081.58 | 3867.45 | 4.06741 | 15.27 | 2.46936 | 0.0013388 | 9.0215e-05 | 2.33209e-05 | 4(Loss) |
| simdjson (ondemand) | 1186.57 | 0.0377001 | 1155.47ms | 5092 | 640 | 1523.54 | 4092.55 | 4.30528 | 15.6954 | 2.64395 | 0.00160116 | 4.08116e-05 | 9.81932e-06 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2224.12 | 0.0435212 | 994.982ms | 5092 | 2560 | 2311.54 | 2183.38 | 2.31103 | 9.36037 | 1.61076 | 0.00176686 | 6.20612e-05 | 2.38579e-05 | 1(Win) |
| jsonifier (two-stage) | 1830.59 | 0.0445866 | 1047.58ms | 5092 | 4890 | 6840.91 | 2652.76 | 2.79291 | 11.8219 | 1.91673 | 0.00113225 | 6.57031e-05 | 2.12049e-05 | 2(Loss) |
| glaze | 1752.76 | 0.0641428 | 1056.54ms | 5092 | 2560 | 8084.72 | 2770.54 | 2.93651 | 12.4244 | 2.32561 | 0.000654136 | 7.51792e-05 | 3.85102e-05 | 3(Loss) |
| simdjson (reflection) | 1379.8 | 0.0459213 | 1138.41ms | 5092 | 2560 | 6686.75 | 3519.44 | 3.67841 | 14.1868 | 2.17788 | 0.00131986 | 6.01434e-05 | 1.53427e-05 | 4(Loss) |
| simdjson (ondemand) | 1328.43 | 0.0875772 | 1161.61ms | 5092 | 640 | 6559.39 | 3655.53 | 3.82253 | 14.0723 | 2.25383 | 0.00170611 | 4.29595e-05 | 8.89876e-06 | 5(Loss) |

----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 8218.53 | 0.0850968 | 793.568ms | 5092 | 4890 | 1236.3 | 590.874 | 0.657921 | 2.24902 | 0.36253 | 0.000196748 | 3.8956e-05 | 1.10041e-05 | 1(Win) |
| simdjson (reflection) | 6882.86 | 0.084466 | 806.236ms | 5092 | 4890 | 1736.65 | 705.537 | 0.777034 | 2.58072 | 0.288492 | 0.000196949 | 4.48998e-05 | 8.03217e-06 | 2(Loss) |
| glaze | 3583.98 | 0.121885 | 878.75ms | 5092 | 2560 | 6982.08 | 1354.95 | 1.43996 | 4.69737 | 0.7174 | 0.000202984 | 4.57979e-05 | 8.59191e-06 | 3(Loss) |

----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9209.22 | 0.151143 | 792.272ms | 5092 | 320 | 203.261 | 527.309 | 0.59273 | 2.13315 | 0.336606 | 0.000197 | 1.22742e-05 | 0 | 1(Win) |
| simdjson (reflection) | 7198.6 | 0.0810595 | 802.326ms | 5092 | 4890 | 1462.17 | 674.59 | 0.744839 | 2.48782 | 0.266693 | 0.000196627 | 4.14861e-05 | 6.02413e-06 | 2(Loss) |
| glaze | 4153.77 | 0.126043 | 872.166ms | 5092 | 2560 | 5558.68 | 1169.08 | 1.25992 | 4.22035 | 0.614493 | 0.000197154 | 3.59019e-05 | 4.98638e-06 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3231.37 | 0.0660979 | 1087.56ms | 11724 | 1280 | 6695.19 | 3460.1 | 1.59218 | 6.60218 | 1.02593 | 0.000547155 | 1.79253e-05 | 5.19767e-06 | 1(Win) |
| jsonifier | 2697.75 | 0.0935549 | 1155.47ms | 11724 | 640 | 9621.92 | 4144.52 | 1.89036 | 6.96452 | 1.46477 | 0.000983826 | 1.62594e-05 | 2.13238e-06 | 2(Loss) |
| simdjson (reflection) | 2655.32 | 0.0287522 | 1162.88ms | 11724 | 4890 | 7167.5 | 4210.74 | 1.9218 | 7.44541 | 1.1096 | 0.000504131 | 2.85712e-05 | 7.88413e-06 | 3(Loss) |
| simdjson (ondemand) | 2535.04 | 0.0547612 | 1182.94ms | 11724 | 1280 | 7466.88 | 4410.54 | 2.01131 | 7.61558 | 1.18304 | 0.000730873 | 2.81874e-05 | 1.03287e-05 | 4(Loss) |
| glaze | 2218.29 | 0.0354769 | 1245.71ms | 11724 | 2560 | 8185.5 | 5040.31 | 2.29637 | 9.45641 | 1.77047 | 0.00144689 | 1.98911e-05 | 4.29807e-06 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3710.48 | 0.0328633 | 1079.82ms | 11724 | 4890 | 4795.37 | 3013.32 | 1.38101 | 5.93628 | 0.85969 | 0.000544528 | 1.12855e-05 | 1.44775e-06 | 1(Win) |
| jsonifier | 3034.97 | 0.0558665 | 1150.33ms | 11724 | 1280 | 5421.96 | 3684.02 | 1.68542 | 6.27806 | 1.29461 | 0.00109271 | 1.59928e-05 | 4.5313e-06 | 2(Loss) |
| simdjson (reflection) | 2916.39 | 0.022336 | 1163.36ms | 11724 | 4890 | 3585.76 | 3833.81 | 1.75257 | 6.93955 | 0.976096 | 0.000672017 | 2.25361e-05 | 7.06432e-06 | 3(Loss) |
| simdjson (ondemand) | 2866.63 | 0.0253572 | 1190.2ms | 11724 | 4890 | 4783.21 | 3900.35 | 1.78416 | 6.89494 | 1.00975 | 0.000878627 | 5.68634e-05 | 2.8484e-05 | 4(Loss) |
| glaze | 2471.16 | 0.0403777 | 1232.64ms | 11724 | 2560 | 8544.26 | 4524.55 | 2.06337 | 8.79495 | 1.60619 | 0.00136819 | 1.27943e-05 | 2.56552e-06 | 5(Loss) |

----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 17192.2 | 0.085515 | 800.31ms | 11724 | 2560 | 791.796 | 650.346 | 0.313579 | 1.07702 | 0.158393 | 8.55283e-05 | 1.87583e-05 | 3.76498e-06 | 1(Win) |
| glaze | 4006.04 | 0.163682 | 1021.32ms | 11746 | 2560 | 53627.7 | 2796.24 | 1.28159 | 3.75719 | 0.51575 | 0.000231528 | 2.08515e-05 | 5.78654e-06 | 2(Loss) |
| simdjson (reflection) | 547.722 | 0.0827087 | 2788.22ms | 11724 | 4890 | 1.39394e+06 | 20413.4 | 9.23521 | 36.9757 | 6.16863 | 0.00516834 | 0.000110744 | 5.44738e-05 | 3(Loss) |

----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19251.2 | 0.125159 | 792.554ms | 11724 | 640 | 338.174 | 580.788 | 0.281624 | 1.02619 | 0.146537 | 8.54284e-05 | 9.99552e-06 | 5.33095e-07 | 1(Win) |
| glaze | 4912.15 | 0.132047 | 963.894ms | 11746 | 4890 | 44341 | 2280.44 | 1.04916 | 3.49387 | 0.456666 | 0.000300202 | 1.53905e-05 | 2.68115e-06 | 2(Loss) |
| simdjson (reflection) | 544.801 | 0.0825942 | 2797.25ms | 11724 | 4890 | 1.40503e+06 | 20522.9 | 9.25263 | 36.9711 | 6.16731 | 0.00556412 | 8.52777e-05 | 3.47634e-05 | 3(Loss) |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1988.51 | 0.0691887 | 975.22ms | 4857 | 640 | 1662.38 | 2329.38 | 2.58738 | 9.8252 | 1.80502 | 0.000411133 | 3.92475e-05 | 4.82551e-06 | 1(Win) |
| glaze | 1767.67 | 0.0434367 | 1002.35ms | 4857 | 4890 | 6335.13 | 2620.39 | 2.90159 | 11.6541 | 2.26086 | 0.000933066 | 4.65249e-05 | 8.505e-06 | 2(Loss) |
| jsonifier (two-stage) | 1653.42 | 0.0588688 | 1023.37ms | 4857 | 320 | 870.343 | 2801.46 | 3.10512 | 11.9034 | 1.97262 | 0.000820337 | 2.50926e-05 | 1.9302e-06 | 3(Loss) |
| simdjson (reflection) | 1366.41 | 0.039942 | 1086.34ms | 4857 | 2560 | 4693.22 | 3389.89 | 3.74473 | 13.4329 | 2.23708 | 0.00187447 | 0.000135919 | 6.30533e-05 | 4(Loss) |
| simdjson (ondemand) | 1284.54 | 0.0353085 | 1109.9ms | 4857 | 4890 | 7927.02 | 3605.96 | 3.9652 | 14.2176 | 2.74923 | 0.0011387 | 8.22712e-05 | 1.77258e-05 | 5(Loss) |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2592.06 | 0.0462047 | 943.386ms | 4857 | 640 | 436.313 | 1786.99 | 1.99786 | 7.70517 | 1.30883 | 0.00020621 | 1.22246e-05 | 0 | 1(Win) |
| glaze | 2469.85 | 0.16287 | 956.015ms | 4857 | 640 | 5971.16 | 1875.41 | 2.09011 | 8.99424 | 1.67593 | 0.000651122 | 2.86314e-05 | 9.97272e-06 | 2(Loss) |
| jsonifier (two-stage) | 2001.27 | 0.0340739 | 1001.6ms | 4857 | 4890 | 3041.42 | 2314.53 | 2.56362 | 9.97962 | 1.51863 | 0.000906751 | 4.07145e-05 | 4.67354e-06 | 3(Loss) |
| simdjson (reflection) | 1584.42 | 0.0413073 | 1064.84ms | 4857 | 2560 | 3733.28 | 2923.47 | 3.23658 | 12.0082 | 1.9125 | 0.00118957 | 4.16602e-05 | 8.20337e-06 | 4(Loss) |
| simdjson (ondemand) | 1568.77 | 0.0807558 | 1061.04ms | 4857 | 160 | 909.679 | 2952.64 | 3.27013 | 12.211 | 2.32983 | 0.00186329 | 4.50381e-05 | 9.00762e-06 | 5(Loss) |

----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9215.44 | 0.0474315 | 786.768ms | 4857 | 2560 | 145.505 | 502.634 | 0.594006 | 1.85547 | 0.313568 | 0.000205969 | 3.99713e-05 | 7.72082e-06 | 1(Win) |
| simdjson (reflection) | 6770.8 | 0.106448 | 804.91ms | 4857 | 640 | 339.403 | 684.114 | 0.790545 | 2.14721 | 0.329627 | 0.000207175 | 2.7988e-05 | 0 | 2(Loss) |
| glaze | 3946.78 | 0.0866862 | 858.618ms | 4857 | 4890 | 5061.28 | 1173.61 | 1.32405 | 3.93597 | 0.618901 | 0.000208836 | 3.62094e-05 | 6.3156e-06 | 3(Loss) |

----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 10345.7 | 0.0649041 | 781.303ms | 4857 | 4890 | 412.927 | 447.724 | 0.532683 | 1.73276 | 0.283303 | 0.000206099 | 3.63778e-05 | 7.32609e-06 | 1(Win) |
| simdjson (reflection) | 7206.23 | 0.0728082 | 798.447ms | 4857 | 4890 | 1071 | 642.777 | 0.747405 | 2.04612 | 0.306156 | 0.000207446 | 5.15353e-05 | 2.22309e-05 | 2(Loss) |
| glaze | 4754.62 | 0.0890399 | 836.373ms | 4857 | 2560 | 1926.26 | 974.21 | 1.10716 | 3.44328 | 0.508956 | 0.000206854 | 1.95433e-05 | 3.45828e-06 | 3(Loss) |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2365.61 | 0.0861153 | 1038.73ms | 7376 | 640 | 4196.58 | 2973.57 | 2.1588 | 8.34097 | 1.30559 | 0.000299536 | 2.64795e-05 | 2.11836e-06 | 1(Win) |
| glaze | 2089.65 | 0.086745 | 1080.09ms | 7376 | 160 | 1364.28 | 3366.26 | 2.44959 | 9.79013 | 1.95853 | 0.00179128 | 3.64357e-05 | 7.62608e-06 | 2(Loss) |
| jsonifier | 1982.69 | 0.0427445 | 1099.64ms | 7376 | 2560 | 5887.55 | 3547.86 | 2.56865 | 8.47031 | 1.76241 | 0.000755141 | 7.29244e-05 | 3.33641e-05 | 3(Loss) |
| simdjson (reflection) | 1962.87 | 0.0366488 | 1105.37ms | 7376 | 2560 | 4415.91 | 3583.69 | 2.60376 | 9.34084 | 1.49166 | 0.00161202 | 6.09028e-05 | 2.40963e-05 | 4(Loss) |
| simdjson (ondemand) | 1903.72 | 0.0421136 | 1114.98ms | 7376 | 1280 | 3099.49 | 3695.03 | 2.6862 | 9.85222 | 1.82863 | 0.000480337 | 3.74949e-05 | 4.55447e-06 | 5(Loss) |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 2899.07 | 0.0364242 | 1010.71ms | 7376 | 4890 | 3819.56 | 2426.4 | 1.77242 | 7.09043 | 1.00976 | 0.000451667 | 2.78635e-05 | 5.65588e-06 | 1(Win) |
| glaze | 2747.27 | 0.082791 | 1019.48ms | 7376 | 4890 | 21974.3 | 2560.47 | 1.8678 | 8.01559 | 1.56806 | 0.000769256 | 3.62919e-05 | 1.14781e-05 | 2(Loss) |
| jsonifier | 2444.5 | 0.069688 | 1056.11ms | 7376 | 80 | 321.711 | 2877.6 | 2.10108 | 7.03281 | 1.42611 | 0.000318601 | 1.35575e-05 | 0 | 3(Loss) |
| simdjson (reflection) | 2315.73 | 0.110663 | 1077.41ms | 7376 | 640 | 7231.94 | 3037.62 | 2.21516 | 8.24959 | 1.24539 | 0.000543994 | 1.9277e-05 | 0 | 4(Loss) |
| simdjson (ondemand) | 2239.43 | 0.0362355 | 1079.52ms | 7376 | 4890 | 6334.95 | 3141.11 | 2.28025 | 8.59206 | 1.56467 | 0.00142539 | 4.06725e-05 | 5.37863e-06 | 5(Loss) |

----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 13473.3 | 0.180056 | 790.431ms | 7376 | 160 | 141.394 | 522.094 | 0.405254 | 1.29379 | 0.204718 | 0.000135575 | 2.20309e-05 | 0 | 1(Win) |
| glaze | 3521.85 | 0.180355 | 947.487ms | 7376 | 2560 | 33219.8 | 1997.33 | 1.45916 | 4.05735 | 0.596936 | 0.000273533 | 2.15543e-05 | 3.54825e-06 | 2(Loss) |
| simdjson (reflection) | 540.812 | 0.114929 | 2055.19ms | 7376 | 2560 | 572068 | 13006.9 | 9.37046 | 35.8072 | 6.18316 | 0.00641629 | 0.000115345 | 5.26941e-05 | 3(Loss) |

----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 15009.3 | 0.0925541 | 779.774ms | 7376 | 640 | 120.418 | 468.663 | 0.366549 | 1.21299 | 0.186551 | 0.0001396 | 6.77874e-06 | 8.47343e-07 | 1(Win) |
| glaze | 4104.68 | 0.212285 | 914.308ms | 7376 | 1280 | 16940.8 | 1713.73 | 1.25608 | 3.70635 | 0.518303 | 0.000178048 | 1.35575e-05 | 1.69469e-06 | 2(Loss) |
| simdjson (reflection) | 540.953 | 0.0819174 | 2052.14ms | 7376 | 4890 | 554860 | 13003.5 | 9.37218 | 35.8145 | 6.18506 | 0.00638272 | 9.45974e-05 | 3.93694e-05 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2325.4 | 0.039587 | 912.775ms | 4390 | 2560 | 1300.41 | 1800.39 | 2.22296 | 10.1806 | 1.74556 | 0.000229748 | 5.01851e-05 | 1.45038e-05 | 1(Win) |
| glaze | 1885.07 | 0.0366129 | 955.726ms | 4390 | 1280 | 846.358 | 2220.95 | 2.73227 | 12.9071 | 2.46629 | 0.000230994 | 2.93636e-05 | 3.91515e-06 | 2(Loss) |
| jsonifier (two-stage) | 1742.27 | 0.0370029 | 976.327ms | 4390 | 2560 | 2024 | 2402.98 | 2.9511 | 13.5797 | 2.21458 | 0.00211916 | 4.32446e-05 | 1.01438e-05 | 3(Loss) |
| simdjson (reflection) | 1271.65 | 0.036735 | 1067.98ms | 4390 | 2560 | 3744.47 | 3292.27 | 4.02436 | 14.9718 | 2.49613 | 0.00522023 | 5.5079e-05 | 1.41479e-05 | 4(Loss) |
| simdjson (ondemand) | 1132.59 | 0.116866 | 1113.78ms | 4390 | 80 | 1492.96 | 3696.51 | 4.51518 | 15.8437 | 2.74419 | 0.00281891 | 3.41686e-05 | 1.99317e-05 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2702.24 | 0.0443689 | 912.861ms | 4390 | 4890 | 2310.72 | 1549.32 | 1.90039 | 8.99185 | 1.4688 | 0.000229933 | 4.88655e-05 | 2.10555e-05 | 1(Win) |
| glaze | 2217.56 | 0.0571188 | 943.647ms | 4390 | 2560 | 2976.98 | 1887.94 | 2.32949 | 11.5358 | 2.15535 | 0.000237044 | 2.54485e-05 | 7.47437e-06 | 2(Loss) |
| jsonifier (two-stage) | 1959.59 | 0.0566935 | 980.369ms | 4390 | 320 | 469.479 | 2136.48 | 2.6308 | 12.3875 | 1.9385 | 0.00208001 | 5.90831e-05 | 7.11845e-06 | 3(Loss) |
| simdjson (reflection) | 1361.91 | 0.0441154 | 1067.43ms | 4390 | 2560 | 4708.2 | 3074.09 | 3.74606 | 14.0743 | 2.28246 | 0.00596241 | 4.18209e-05 | 9.16501e-06 | 4(Loss) |
| simdjson (ondemand) | 1215.66 | 0.0401074 | 1107.37ms | 4390 | 2560 | 4884.18 | 3443.91 | 4.1984 | 14.7339 | 2.49727 | 0.00380481 | 4.38675e-05 | 9.07603e-06 | 5(Loss) |

----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 9344.11 | 0.200974 | 778.77ms | 4390 | 160 | 129.733 | 448.05 | 0.591091 | 2.65649 | 0.358314 | 0.00022779 | 5.69476e-06 | 0 | 1(Win) |
| simdjson (reflection) | 7947.99 | 0.0782953 | 785.322ms | 4390 | 4890 | 831.755 | 526.753 | 0.68421 | 2.6041 | 0.383599 | 0.00024102 | 3.41919e-05 | 5.35703e-06 | 2(Loss) |
| glaze | 3835.21 | 0.125462 | 847.217ms | 4390 | 4890 | 9172.49 | 1091.63 | 1.36341 | 4.72506 | 0.757176 | 0.000228489 | 5.82286e-05 | 2.5574e-05 | 3(Loss) |

----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 10001.5 | 0.214876 | 770.403ms | 4390 | 80 | 64.7241 | 418.6 | 0.553451 | 2.52073 | 0.326424 | 0.00022779 | 2.56264e-05 | 5.69476e-06 | 1(Win) |
| simdjson (reflection) | 8525.78 | 0.0963667 | 780.289ms | 4390 | 4890 | 1095.03 | 491.055 | 0.642046 | 2.48952 | 0.357403 | 0.00022821 | 3.31204e-05 | 1.04346e-05 | 2(Loss) |
| glaze | 4253.39 | 0.216873 | 834.391ms | 4390 | 2560 | 11665.7 | 984.304 | 1.2322 | 4.28816 | 0.659909 | 0.000230371 | 2.40248e-05 | 8.18622e-06 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3770.42 | 0.105769 | 1028.03ms | 11521 | 160 | 1519.97 | 2914.07 | 1.33458 | 6.08871 | 0.888899 | 0.000782267 | 3.20068e-05 | 1.57321e-05 | 1(Win) |
| jsonifier | 3637.79 | 0.0442925 | 1039.45ms | 11521 | 2560 | 4581.47 | 3020.31 | 1.41139 | 6.09591 | 1.26925 | 0.00192268 | 3.69909e-05 | 1.92922e-05 | 2(Loss) |
| simdjson (reflection) | 2996.59 | 0.0893994 | 1108.17ms | 11521 | 320 | 3438.32 | 3666.6 | 1.70319 | 6.57469 | 0.989237 | 0.00219301 | 1.79021e-05 | 4.88239e-06 | 3(Loss) |
| glaze | 2814.35 | 0.0805508 | 1126.6ms | 11521 | 640 | 6329.12 | 3904.02 | 1.81415 | 8.60707 | 1.5694 | 0.00381518 | 9.9004e-06 | 2.57682e-06 | 4(Loss) |
| simdjson (ondemand) | 2677.42 | 0.0520494 | 1150.89ms | 11521 | 160 | 729.957 | 4103.68 | 1.90816 | 6.92891 | 1.0881 | 0.00134049 | 1.19347e-05 | 2.16995e-06 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 4261.99 | 0.226644 | 1023.16ms | 11521 | 320 | 10924.3 | 2577.97 | 1.19719 | 5.63441 | 0.7837 | 0.000686789 | 1.95296e-05 | 4.88239e-06 | 1(Win) |
| jsonifier | 3979.49 | 0.0351087 | 1041.73ms | 11521 | 4890 | 4594.78 | 2760.98 | 1.28246 | 5.64283 | 1.16405 | 0.00182681 | 2.07144e-05 | 7.56155e-06 | 2(Loss) |
| simdjson (reflection) | 3209.23 | 0.0557477 | 1103.69ms | 11521 | 1280 | 4662.75 | 3423.65 | 1.59382 | 6.23271 | 0.907821 | 0.00246188 | 1.52575e-05 | 2.78025e-06 | 3(Loss) |
| glaze | 3021.5 | 0.0505422 | 1122.39ms | 11521 | 1280 | 4323.67 | 3636.36 | 1.69166 | 8.05208 | 1.44458 | 0.00410372 | 1.48506e-05 | 5.5605e-06 | 4(Loss) |
| simdjson (ondemand) | 2889.4 | 0.0813037 | 1144.32ms | 11521 | 80 | 764.671 | 3802.61 | 1.76997 | 6.48407 | 0.989671 | 0.00168171 | 7.59483e-06 | 1.08498e-06 | 5(Loss) |

----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 20677.2 | 0.0813417 | 784.719ms | 11521 | 2560 | 478.261 | 531.373 | 0.263375 | 1.12091 | 0.136273 | 0.000103717 | 1.17313e-05 | 3.49226e-06 | 1(Win) |
| glaze | 5618.14 | 0.27997 | 937.281ms | 11521 | 640 | 19186.6 | 1955.68 | 0.915452 | 3.76426 | 0.511588 | 0.000173054 | 1.30197e-05 | 1.35622e-06 | 2(Loss) |
| simdjson (reflection) | 507.842 | 0.101397 | 2910.02ms | 11521 | 4890 | 2.35332e+06 | 21635.2 | 9.95235 | 36.8964 | 6.37184 | 0.0100451 | 7.51185e-05 | 3.73107e-05 | 3(Loss) |

----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 23446.1 | 0.0851445 | 775.389ms | 11521 | 320 | 50.9451 | 468.619 | 0.233826 | 1.0697 | 0.124382 | 8.6798e-05 | 5.42488e-06 | 5.42488e-07 | 1(Win) |
| glaze | 7122 | 0.0955307 | 890.176ms | 11521 | 4890 | 10621.1 | 1542.72 | 0.726034 | 3.50586 | 0.45569 | 0.000116352 | 9.47856e-06 | 1.43776e-06 | 2(Loss) |
| simdjson (reflection) | 509.36 | 0.138276 | 2905.5ms | 11521 | 2560 | 2.27752e+06 | 21570.8 | 9.93214 | 36.9037 | 6.37341 | 0.0100415 | 6.92011e-05 | 3.06506e-05 | 3(Loss) |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3248.99 | 0.100569 | 872.964ms | 4669 | 80 | 151.975 | 1370.49 | 1.60379 | 6.50953 | 1.38681 | 0.000519383 | 2.14179e-05 | 1.87406e-05 | 1(Win) |
| jsonifier (two-stage) | 2183.46 | 0.127117 | 943.479ms | 4669 | 640 | 4300.72 | 2039.29 | 2.36107 | 9.33712 | 1.68344 | 0.00135736 | 0.000104412 | 3.88199e-05 | 2(Loss) |
| glaze | 2020.46 | 0.0327194 | 957.771ms | 4669 | 4890 | 2542.54 | 2203.81 | 2.54781 | 9.65068 | 1.82073 | 0.000829822 | 3.87186e-05 | 9.41685e-06 | 3(Loss) |
| simdjson (reflection) | 1690.79 | 0.163986 | 1004.25ms | 4669 | 30 | 559.5 | 2633.5 | 2.9809 | 12.5273 | 1.91519 | 0.00124224 | 9.995e-05 | 0 | 4(Loss) |
| simdjson (ondemand) | 1262.89 | 0.050325 | 1096.63ms | 4669 | 1280 | 4029.92 | 3525.81 | 4.049 | 14.623 | 2.48961 | 0.00177367 | 7.74724e-05 | 2.89476e-05 | 5(Loss) |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3645.05 | 0.0594543 | 861.775ms | 4669 | 160 | 84.3969 | 1221.58 | 1.43457 | 6.0212 | 1.26794 | 0.000579621 | 1.07089e-05 | 1.33862e-06 | 1(Win) |
| jsonifier (two-stage) | 2379.02 | 0.048025 | 933.401ms | 4669 | 4890 | 3950.92 | 1871.66 | 2.16828 | 8.85093 | 1.56522 | 0.00128109 | 3.78864e-05 | 1.0468e-05 | 2(Loss) |
| glaze | 2215.82 | 0.0390879 | 941.198ms | 4669 | 4890 | 3016.97 | 2009.5 | 2.32118 | 8.95866 | 1.66631 | 0.000769641 | 3.09661e-05 | 5.43111e-06 | 3(Loss) |
| simdjson (reflection) | 1794.21 | 0.0271935 | 995.217ms | 4669 | 4890 | 2227.1 | 2481.71 | 2.86641 | 12.2529 | 1.84344 | 0.0011842 | 3.56088e-05 | 6.6575e-06 | 4(Loss) |
| simdjson (ondemand) | 1331.83 | 0.0387364 | 1082ms | 4669 | 4890 | 8201.55 | 3343.29 | 3.81101 | 13.8925 | 2.3352 | 0.00141354 | 5.27782e-05 | 1.82643e-05 | 5(Loss) |

----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 14775 | 0.121668 | 765.422ms | 4669 | 30 | 4.03333 | 301.367 | 0.392654 | 1.36517 | 0.337974 | 0.000314129 | 2.85571e-05 | 0 | 1(Win) |
| simdjson (reflection) | 8078.16 | 0.0458355 | 791.978ms | 4669 | 320 | 20.4257 | 551.203 | 0.671255 | 1.62712 | 0.217177 | 0.000214179 | 1.94099e-05 | 0 | 2(Loss) |
| glaze | 3543.33 | 0.0976069 | 865.121ms | 4669 | 4890 | 7356.91 | 1256.65 | 1.46779 | 3.40865 | 0.493682 | 0.000215449 | 4.81354e-05 | 8.27807e-06 | 3(Loss) |

----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 16500.3 | 0.040902 | 759.616ms | 4669 | 2560 | 31.1884 | 269.856 | 0.354726 | 1.24652 | 0.310345 | 0.000398991 | 2.22545e-05 | 4.26684e-06 | 1(Win) |
| simdjson (reflection) | 8442.99 | 0.0731651 | 791.062ms | 4669 | 4890 | 728.069 | 527.385 | 0.645082 | 1.55772 | 0.200686 | 0.000229946 | 2.79002e-05 | 6.6575e-06 | 2(Loss) |
| glaze | 4114.58 | 0.130985 | 844.093ms | 4669 | 1280 | 2571.87 | 1082.18 | 1.26898 | 2.8777 | 0.373528 | 0.000323611 | 1.58961e-05 | 3.34654e-06 | 3(Loss) |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3646.46 | 0.0436026 | 982.818ms | 9249 | 2560 | 2847.82 | 2418.93 | 1.40053 | 5.47173 | 0.892097 | 0.000587901 | 2.44114e-05 | 7.05313e-06 | 1(Win) |
| jsonifier | 3176.56 | 0.032987 | 1021.03ms | 9249 | 320 | 268.48 | 2776.76 | 1.61585 | 5.56622 | 1.31722 | 0.000785558 | 1.85831e-05 | 0 | 2(Loss) |
| simdjson (reflection) | 3142.25 | 0.136421 | 1024.93ms | 9249 | 40 | 586.584 | 2807.07 | 1.63819 | 7.01535 | 0.995567 | 0.000756839 | 2.4327e-05 | 2.70299e-06 | 3(Loss) |
| glaze | 2625.13 | 0.0647031 | 1080.78ms | 9249 | 160 | 756.238 | 3360.04 | 1.95007 | 7.81933 | 1.48903 | 0.00130555 | 2.02725e-05 | 2.02725e-06 | 4(Loss) |
| simdjson (ondemand) | 2342.29 | 0.0334176 | 1121.81ms | 9249 | 4890 | 7744.07 | 3765.78 | 2.17742 | 8.07331 | 1.28554 | 0.000980176 | 3.7853e-05 | 1.0016e-05 | 5(Loss) |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3884.41 | 0.0692956 | 972.48ms | 9249 | 4890 | 12107.6 | 2270.75 | 1.32119 | 5.2263 | 0.832415 | 0.000607085 | 2.21767e-05 | 6.67734e-06 | 1(Win) |
| jsonifier | 3372.67 | 0.0634898 | 1007.52ms | 9249 | 320 | 882.266 | 2615.3 | 1.50823 | 5.32156 | 1.25754 | 0.000718321 | 2.39891e-05 | 2.70299e-06 | 2(Loss) |
| simdjson (reflection) | 3262.82 | 0.0718566 | 1018.07ms | 9249 | 160 | 603.751 | 2703.35 | 1.57602 | 6.87685 | 0.959347 | 0.000575738 | 2.50027e-05 | 5.40599e-06 | 3(Loss) |
| glaze | 2816.55 | 0.0398261 | 1059.82ms | 9249 | 2560 | 3982.27 | 3131.68 | 1.81543 | 7.46232 | 1.41107 | 0.00108589 | 3.60681e-05 | 1.03474e-05 | 4(Loss) |
| simdjson (ondemand) | 2484.51 | 0.0713524 | 1101.8ms | 9249 | 640 | 4106.82 | 3550.21 | 2.0575 | 7.70451 | 1.20759 | 0.000826272 | 1.79073e-05 | 3.37874e-07 | 5(Loss) |

----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 25645.5 | 0.0610737 | 768.285ms | 9249 | 1280 | 56.479 | 343.941 | 0.220427 | 0.757487 | 0.169856 | 0.00010812 | 1.56267e-05 | 2.87193e-06 | 1(Win) |
| glaze | 3539.72 | 0.124815 | 991.769ms | 9249 | 4890 | 47303.6 | 2491.87 | 1.45018 | 3.46913 | 0.45313 | 0.000331413 | 2.71737e-05 | 8.07029e-06 | 2(Loss) |
| simdjson (reflection) | 514.007 | 0.110338 | 2468.23ms | 9249 | 4890 | 1.75312e+06 | 17160.3 | 9.86117 | 37.3264 | 6.55087 | 0.00620566 | 0.000202354 | 0.000123597 | 3(Loss) |

----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 29328.5 | 0.0668136 | 761.314ms | 9249 | 4890 | 197.446 | 300.749 | 0.196144 | 0.702671 | 0.157314 | 0.000136598 | 2.22652e-05 | 5.06328e-06 | 1(Win) |
| glaze | 4089.79 | 0.13513 | 953.526ms | 9249 | 4890 | 41533.6 | 2156.72 | 1.25739 | 3.20402 | 0.393989 | 0.000362787 | 2.01868e-05 | 4.82006e-06 | 2(Loss) |
| simdjson (reflection) | 508.318 | 0.107326 | 2489.94ms | 9249 | 4890 | 1.69604e+06 | 17352.4 | 9.96288 | 37.5566 | 6.59888 | 0.00627192 | 7.71653e-05 | 3.50892e-05 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 813.776 | 0.04419 | 1281.38ms | 4604 | 1280 | 7276.45 | 5395.49 | 6.25744 | 23.7031 | 5.05691 | 0.00310396 | 8.78991e-05 | 2.4605e-05 | 1(Win) |
| simdjson (reflection) | 739.076 | 0.0237446 | 1340.69ms | 4604 | 4890 | 9730.43 | 5940.82 | 6.87607 | 28.523 | 5.11577 | 0.0047717 | 8.31499e-05 | 2.90936e-05 | 2(Loss) |
| jsonifier (two-stage) | 724.178 | 0.0448605 | 1351.24ms | 4604 | 1280 | 9469.31 | 6063.04 | 7.02943 | 26.8595 | 5.36295 | 0.00583511 | 7.75481e-05 | 2.49443e-05 | 3(Loss) |
| glaze | 618.416 | 0.0343895 | 1451.05ms | 4604 | 2560 | 15261.6 | 7099.94 | 8.21735 | 33.4985 | 6.88945 | 0.0063821 | 0.00020227 | 0.000119037 | 4(Loss) |
| simdjson (ondemand) | 574.696 | 0.0494887 | 1506.33ms | 4604 | 640 | 9149.28 | 7640.07 | 8.8401 | 34.5995 | 6.72524 | 0.00754303 | 4.95493e-05 | 3.39379e-06 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1001.55 | 0.0531447 | 1276.78ms | 4604 | 4890 | 26543.4 | 4383.93 | 5.09391 | 19.2706 | 4.04757 | 0.00252861 | 5.8276e-05 | 8.92795e-06 | 1(Win) |
| jsonifier (two-stage) | 861.618 | 0.0690156 | 1349.18ms | 4604 | 640 | 7916.18 | 5095.9 | 5.91372 | 22.6412 | 4.40422 | 0.00518605 | 5.97307e-05 | 1.05207e-05 | 2(Loss) |
| simdjson (reflection) | 841.345 | 0.0350075 | 1357.57ms | 4604 | 2560 | 8544.44 | 5218.69 | 6.06763 | 26.2541 | 4.57689 | 0.00380291 | 0.000182925 | 0.000102492 | 3(Loss) |
| glaze | 721.605 | 0.0219614 | 1437.3ms | 4604 | 4890 | 8731.78 | 6084.66 | 7.05184 | 29.043 | 5.87055 | 0.0063388 | 6.24068e-05 | 1.89663e-05 | 4(Loss) |
| simdjson (ondemand) | 640.488 | 0.0577425 | 1526.94ms | 4604 | 640 | 10028.1 | 6855.27 | 7.93782 | 32.0237 | 6.13662 | 0.00759632 | 3.83498e-05 | 3.39379e-06 | 5(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1691.81 | 0.0342737 | 998.407ms | 4604 | 2560 | 2025.49 | 2595.28 | 3.03626 | 9.05213 | 0.667246 | 0.000568544 | 6.99969e-05 | 2.1296e-05 | 1(Win) |
| simdjson (reflection) | 1463.05 | 0.0344024 | 1062.86ms | 4918 | 4890 | 5947.67 | 3205.75 | 3.49404 | 11.5492 | 1.38796 | 0.00050027 | 5.44305e-05 | 1.59674e-05 | 2(Loss) |
| glaze | 1236.58 | 0.0490337 | 1096.23ms | 4604 | 4890 | 14822.6 | 3550.69 | 4.13503 | 12.7691 | 1.12837 | 0.000441867 | 5.45893e-05 | 1.11488e-05 | 3(Loss) |

----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1717.81 | 0.071848 | 996.924ms | 4604 | 1280 | 4316.78 | 2556 | 2.99068 | 8.92572 | 0.637055 | 0.000591028 | 5.61672e-05 | 1.73083e-05 | 1(Win) |
| simdjson (reflection) | 1455.27 | 0.045998 | 1063.61ms | 4918 | 2560 | 5626.12 | 3222.89 | 3.52023 | 11.4325 | 1.36133 | 0.000533118 | 3.9555e-05 | 1.08022e-05 | 2(Loss) |
| glaze | 1237.55 | 0.110621 | 1095.55ms | 4604 | 1280 | 19716.3 | 3547.9 | 4.13023 | 12.2161 | 1.00956 | 0.000534182 | 5.07371e-05 | 1.57811e-05 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 3363.44 | 0.049001 | 1443.28ms | 24579 | 640 | 7463.67 | 6969.17 | 1.51133 | 6.44469 | 0.998739 | 0.000956355 | 1.1697e-05 | 2.60639e-06 | 1(Win) |
| jsonifier (two-stage) | 3278.72 | 0.0282078 | 1456.55ms | 24579 | 2560 | 10411.2 | 7149.25 | 1.55012 | 6.00972 | 1.04679 | 0.00120884 | 1.79269e-05 | 5.76903e-06 | 2(Loss) |
| jsonifier | 2945.33 | 0.0905291 | 1542.26ms | 24579 | 320 | 16610.7 | 7958.49 | 1.72626 | 6.25091 | 1.42691 | 0.00152086 | 3.58538e-05 | 2.04697e-05 | 3(Loss) |
| simdjson (ondemand) | 2713.12 | 0.0265329 | 1610.6ms | 24579 | 2560 | 13452.4 | 8639.64 | 1.87115 | 7.59478 | 1.3027 | 0.00138906 | 1.93254e-05 | 5.37171e-06 | 4(Loss) |
| glaze | 2227.55 | 0.0634509 | 1798.26ms | 24579 | 320 | 14265.9 | 10522.9 | 2.2769 | 10.1942 | 1.95496 | 0.00375651 | 1.1697e-05 | 3.55995e-06 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3835.07 | 0.0200118 | 1457.65ms | 24579 | 4890 | 7315.81 | 6112.1 | 1.32713 | 5.22047 | 0.867489 | 0.000956217 | 1.91195e-05 | 8.76935e-06 | 1(Win) |
| simdjson (reflection) | 3799.74 | 0.05103 | 1457.79ms | 24579 | 640 | 6342.37 | 6168.94 | 1.33916 | 6.02022 | 0.897657 | 0.000560183 | 6.42062e-06 | 5.08564e-07 | 2(Loss) |
| jsonifier | 3409.19 | 0.0322524 | 1527.43ms | 24579 | 2560 | 12589 | 6875.64 | 1.48729 | 5.45071 | 1.24509 | 0.00119387 | 1.49232e-05 | 4.72011e-06 | 3(Loss) |
| simdjson (ondemand) | 2941.41 | 0.0487411 | 1641.84ms | 24579 | 1280 | 19311.6 | 7969.09 | 1.72746 | 7.13034 | 1.19651 | 0.00178061 | 3.04185e-05 | 1.47484e-05 | 4(Loss) |
| glaze | 2464.81 | 0.0913693 | 1786.87ms | 24579 | 320 | 24160.8 | 9510.01 | 2.06193 | 9.38744 | 1.77037 | 0.00375905 | 1.24598e-05 | 4.44994e-06 | 5(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6962.5 | 0.0634822 | 1080.18ms | 24579 | 4890 | 22336.3 | 3366.66 | 0.735388 | 1.80593 | 0.126327 | 0.00013164 | 2.76975e-05 | 1.4452e-05 | 1(Win) |
| glaze | 3917.29 | 0.067876 | 1350.41ms | 24579 | 4890 | 80667.7 | 5983.82 | 1.29598 | 3.99337 | 0.453762 | 0.000282699 | 2.5318e-05 | 1.12487e-05 | 2(Loss) |
| simdjson (reflection) | 328.63 | 0.111405 | 7949.08ms | 24893 | 1280 | 8.29016e+06 | 72238.7 | 15.3287 | 60.851 | 11.7179 | 0.0248975 | 0.000183975 | 0.000119951 | 3(Loss) |

----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 6956.41 | 0.133139 | 1078.8ms | 24579 | 1280 | 25761.8 | 3369.6 | 0.73615 | 1.78412 | 0.121201 | 0.000153332 | 6.42062e-06 | 7.94632e-07 | 1(Win) |
| glaze | 3982.28 | 0.0839882 | 1333.62ms | 24579 | 4890 | 119512 | 5886.17 | 1.271 | 3.83864 | 0.419139 | 0.000300554 | 1.03668e-05 | 3.21155e-06 | 2(Loss) |
| simdjson (reflection) | 329.989 | 0.0776885 | 7939.99ms | 24893 | 2560 | 7.99668e+06 | 71941.3 | 15.2954 | 60.8622 | 11.7207 | 0.0252687 | 9.34939e-05 | 5.77942e-05 | 3(Loss) |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 900.337 | 0.0281115 | 1225.94ms | 4604 | 4890 | 9190.44 | 4876.75 | 5.65237 | 21.9438 | 4.59206 | 0.00452412 | 0.000157505 | 8.24392e-05 | 1(Win) |
| jsonifier (two-stage) | 760.437 | 0.0439696 | 1320.76ms | 4604 | 1280 | 8250.13 | 5773.94 | 6.68592 | 26.157 | 5.16138 | 0.00602822 | 9.55351e-05 | 3.93679e-05 | 2(Loss) |
| simdjson (reflection) | 745.39 | 0.0409496 | 1327.65ms | 4604 | 1280 | 7447.55 | 5890.5 | 6.80222 | 28.2593 | 5.08449 | 0.00415468 | 7.07605e-05 | 1.45933e-05 | 3(Loss) |
| glaze | 629.168 | 0.0486186 | 1442.29ms | 4604 | 640 | 7367.53 | 6978.61 | 8.07984 | 32.4255 | 6.69288 | 0.00843085 | 3.83498e-05 | 7.46633e-06 | 4(Loss) |
| simdjson (ondemand) | 563.164 | 0.0402752 | 1515.69ms | 4604 | 1280 | 12620.8 | 7796.52 | 9.02248 | 34.1463 | 6.62402 | 0.0102603 | 8.36569e-05 | 3.75014e-05 | 5(Loss) |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1126.02 | 0.0305278 | 1222.78ms | 4604 | 320 | 453.437 | 3899.31 | 4.54162 | 17.7793 | 3.64314 | 0.00258539 | 4.00467e-05 | 3.39379e-06 | 1(Win) |
| jsonifier (two-stage) | 916.834 | 0.0969643 | 1323.18ms | 4604 | 30 | 646.897 | 4789 | 5.57682 | 21.9453 | 4.2046 | 0.00529974 | 9.41211e-05 | 4.34405e-05 | 2(Loss) |
| simdjson (reflection) | 864.292 | 0.0231644 | 1334.33ms | 4604 | 640 | 886.285 | 5080.13 | 5.90097 | 25.8461 | 4.51399 | 0.00208514 | 5.66763e-05 | 8.48447e-06 | 3(Loss) |
| glaze | 719.873 | 0.0234465 | 1437.72ms | 4604 | 4890 | 10000.6 | 6099.3 | 7.04308 | 28.2648 | 5.7411 | 0.00816757 | 6.46277e-05 | 2.05654e-05 | 4(Loss) |
| simdjson (ondemand) | 629.952 | 0.0929994 | 1533.03ms | 4604 | 320 | 13445.2 | 6969.92 | 8.06851 | 32.0892 | 6.14603 | 0.00946867 | 3.80104e-05 | 8.82385e-06 | 5(Loss) |

----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1667.74 | 0.0652316 | 998.469ms | 4604 | 2560 | 7550.43 | 2632.74 | 3.08664 | 9.0328 | 0.666812 | 0.000307392 | 7.19483e-05 | 1.86658e-05 | 1(Win) |
| simdjson (reflection) | 1487.67 | 0.0368309 | 1053.22ms | 4918 | 2560 | 3451.65 | 3152.69 | 3.44164 | 11.497 | 1.37861 | 0.000555993 | 3.77281e-05 | 1.05639e-05 | 2(Loss) |
| glaze | 1198.88 | 0.0462559 | 1106.66ms | 4604 | 4890 | 14033.3 | 3662.34 | 4.26072 | 12.7441 | 1.12837 | 0.000656182 | 8.87465e-05 | 4.13529e-05 | 3(Loss) |

----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1696.89 | 0.0703047 | 995.472ms | 4604 | 2560 | 8471.77 | 2587.52 | 3.02764 | 8.9066 | 0.636838 | 0.000355245 | 5.65066e-05 | 1.54417e-05 | 1(Win) |
| simdjson (reflection) | 1492.58 | 0.0328555 | 1051.2ms | 4918 | 4890 | 5212.28 | 3142.33 | 3.44981 | 11.4303 | 1.36275 | 0.000624225 | 4.25381e-05 | 1.16013e-05 | 2(Loss) |
| glaze | 1284.74 | 0.0591664 | 1077.69ms | 4604 | 2560 | 10467.1 | 3417.58 | 3.98249 | 12.2087 | 1.00869 | 0.000757409 | 8.41659e-05 | 3.15622e-05 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3392.59 | 0.0859779 | 1429.07ms | 24579 | 320 | 11292.5 | 6909.28 | 1.49865 | 5.89292 | 1.01196 | 0.00119691 | 9.78986e-06 | 2.66996e-06 | 1(Win) |
| simdjson (reflection) | 3352.05 | 0.0591032 | 1442.57ms | 24579 | 1280 | 21864.5 | 6992.85 | 1.50282 | 6.43714 | 1.00131 | 0.000911601 | 1.52251e-05 | 4.76779e-06 | 2(Loss) |
| jsonifier | 3136.37 | 0.0330613 | 1488.84ms | 24579 | 2560 | 15629.9 | 7473.73 | 1.6216 | 6.10664 | 1.37992 | 0.00142878 | 5.69592e-05 | 3.82059e-05 | 3(Loss) |
| simdjson (ondemand) | 2714.91 | 0.0370835 | 1604.59ms | 24579 | 1280 | 13121.7 | 8633.94 | 1.8689 | 7.42733 | 1.26588 | 0.00204958 | 8.70916e-06 | 9.21773e-07 | 4(Loss) |
| glaze | 2248.26 | 0.0771885 | 1788.02ms | 24579 | 320 | 20724.8 | 10426 | 2.25515 | 10.0244 | 1.91648 | 0.00379465 | 5.84849e-06 | 3.81423e-07 | 5(Loss) |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3993.66 | 0.0619821 | 1436.81ms | 24579 | 160 | 2117.57 | 5869.39 | 1.27436 | 5.10399 | 0.832743 | 0.000921773 | 7.62846e-06 | 1.77997e-06 | 1(Win) |
| simdjson (reflection) | 3837.97 | 0.0238177 | 1444.63ms | 24579 | 4890 | 10347.5 | 6107.48 | 1.32566 | 5.94608 | 0.886475 | 0.000644123 | 1.82376e-05 | 6.42309e-06 | 2(Loss) |
| jsonifier | 3629.01 | 0.0228899 | 1485.79ms | 24579 | 4890 | 10689.3 | 6459.16 | 1.40143 | 5.32548 | 1.202 | 0.00102503 | 1.90779e-05 | 9.05224e-06 | 3(Loss) |
| simdjson (ondemand) | 2934.25 | 0.0812139 | 1645.93ms | 24579 | 80 | 3367.32 | 7988.52 | 1.73272 | 7.12823 | 1.19506 | 0.00187406 | 1.57655e-05 | 2.03426e-06 | 4(Loss) |
| glaze | 2454.77 | 0.0481309 | 1784.24ms | 24579 | 1280 | 27037.5 | 9548.91 | 2.06346 | 9.26041 | 1.74246 | 0.0035713 | 3.52499e-05 | 2.11054e-05 | 5(Loss) |

----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 7618.22 | 0.0399361 | 1049.02ms | 24579 | 4890 | 7383.5 | 3076.88 | 0.673034 | 1.80439 | 0.126205 | 6.20844e-05 | 1.89282e-05 | 7.7959e-06 | 1(Win) |
| glaze | 3748.31 | 0.0603155 | 1374.24ms | 24579 | 4890 | 69570.4 | 6253.58 | 1.35639 | 3.99105 | 0.451768 | 0.000346057 | 2.4669e-05 | 1.20391e-05 | 2(Loss) |
| simdjson (reflection) | 316.558 | 0.0835627 | 8245.35ms | 24893 | 4890 | 1.92036e+07 | 74993.7 | 15.9599 | 60.8927 | 11.7331 | 0.0247982 | 0.000142154 | 9.30773e-05 | 3(Loss) |

----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 7778.22 | 0.0383139 | 1043.32ms | 24579 | 4890 | 6519.11 | 3013.59 | 0.659569 | 1.78258 | 0.121079 | 6.11275e-05 | 1.64821e-05 | 6.24005e-06 | 1(Win) |
| glaze | 4054.39 | 0.0850527 | 1321.48ms | 24579 | 2560 | 61900.5 | 5781.48 | 1.25507 | 3.84153 | 0.417999 | 0.000341485 | 2.73035e-05 | 1.29684e-05 | 2(Loss) |
| simdjson (reflection) | 315.806 | 0.080971 | 8289.48ms | 24893 | 2560 | 9.48449e+06 | 75172.2 | 16.0609 | 60.9111 | 11.7372 | 0.0258762 | 0.000304145 | 0.000225261 | 3(Loss) |

----
### Mesh Small Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 969.476 | 0.0706987 | 850.765ms | 1181 | 2560 | 1726.98 | 1161.75 | 5.36011 | 19.9915 | 4.09738 | 0.00319016 | 0.00016141 | 4.69676e-05 | 1(Win) |
| jsonifier (two-stage) STATISTICAL TIE | 869.296 | 0.0697817 | 866.698ms | 1181 | 640 | 523.152 | 1295.63 | 6.00056 | 23.0694 | 4.41406 | 0.00338431 | 0.000185224 | 6.48285e-05 | 2(Tie) |
| simdjson (reflection) STATISTICAL TIE | 868.498 | 0.0418807 | 869.09ms | 1181 | 4890 | 1442.45 | 1296.82 | 6.00207 | 25.3599 | 4.12871 | 0.00255303 | 9.80071e-05 | 2.58005e-05 | 2(Tie) |
| glaze | 822.66 | 0.0417272 | 873.97ms | 1181 | 1280 | 417.741 | 1369.08 | 6.32169 | 25.2667 | 4.95766 | 0.00346965 | 0.000105181 | 2.183e-05 | 4(Loss) |
| simdjson (ondemand) | 723.058 | 0.0914003 | 892.785ms | 1181 | 1280 | 2594.53 | 1557.67 | 7.11756 | 29.1287 | 5.03895 | 0.0034895 | 0.000121719 | 2.64606e-05 | 5(Loss) |

----
### Mesh Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1163.91 | 0.0587745 | 846.959ms | 1181 | 4890 | 1581.78 | 967.676 | 4.52305 | 16.8053 | 3.37426 | 0.00249347 | 0.000102336 | 2.77052e-05 | 1(Win) |
| glaze | 1124.06 | 0.0495528 | 848.038ms | 1181 | 4890 | 1205.5 | 1001.99 | 4.7132 | 18.7892 | 3.49619 | 0.00235667 | 0.000188222 | 7.72282e-05 | 2(Loss) |
| simdjson (reflection) | 1036.42 | 0.0649424 | 864.09ms | 1181 | 1280 | 637.518 | 1086.71 | 5.06449 | 22.0466 | 3.37342 | 0.00169745 | 8.73201e-05 | 2.51376e-05 | 3(Loss) |
| simdjson (ondemand) STATISTICAL TIE | 1016.19 | 0.124021 | 863.186ms | 1181 | 160 | 302.317 | 1108.35 | 5.16532 | 22.0186 | 3.46994 | 0.00169348 | 0.000158764 | 1.58764e-05 | 4(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 1015.04 | 0.0659629 | 865.265ms | 1181 | 4890 | 2619.67 | 1109.61 | 5.16329 | 19.8967 | 3.69602 | 0.00193729 | 0.000188742 | 7.61893e-05 | 4(Tie) |

----
### Mesh Small Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 1778.63 | 0.380384 | 795.832ms | 1181 | 1280 | 7426.48 | 633.234 | 3.01193 | 8.00508 | 0.861984 | 0.000941337 | 7.21052e-05 | 5.29213e-06 | 1(Win) |
| simdjson (reflection) | 1334.88 | 0.03749 | 817.334ms | 1187 | 4890 | 494.266 | 848.028 | 3.96518 | 13.706 | 1.45156 | 0.000893283 | 0.000110433 | 3.32505e-05 | 2(Loss) |
| glaze | 1322.75 | 0.102449 | 819.622ms | 1181 | 1280 | 974.023 | 851.474 | 4.00558 | 10.7604 | 0.925487 | 0.00207319 | 9.92273e-05 | 1.32303e-05 | 3(Loss) |

----
### Mesh Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2028.15 | 0.275257 | 784.155ms | 1181 | 2560 | 5981.63 | 555.33 | 2.67494 | 7.5834 | 0.762066 | 0.000991612 | 5.4575e-05 | 5.62288e-06 | 1(Win) |
| simdjson (reflection) | 1377.81 | 0.0310061 | 813.141ms | 1187 | 320 | 20.7668 | 821.603 | 3.87978 | 13.2713 | 1.34962 | 0.00189027 | 4.2123e-05 | 0 | 2(Loss) |
| glaze | 1327.51 | 0.0581943 | 815.853ms | 1181 | 4890 | 1192.05 | 848.424 | 3.98578 | 10.1693 | 0.79255 | 0.00132587 | 7.32456e-05 | 1.35063e-05 | 3(Loss) |

----
### Mesh Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 1772.53 | 0.04325 | 870.715ms | 2496 | 4890 | 1649.61 | 1342.92 | 2.93987 | 12.6895 | 1.96755 | 0.00120651 | 5.38285e-05 | 1.49114e-05 | 1(Win) |
| jsonifier (two-stage) | 1685.9 | 0.0422443 | 878.352ms | 2496 | 1280 | 455.38 | 1411.93 | 3.08574 | 11.8397 | 2.16667 | 0.00120286 | 5.79051e-05 | 1.7215e-05 | 2(Loss) |
| jsonifier STATISTICAL TIE | 1522.25 | 0.0386025 | 891.674ms | 2496 | 4890 | 1781.79 | 1563.72 | 3.40697 | 12.7933 | 2.875 | 0.00187875 | 5.21898e-05 | 1.16342e-05 | 3(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1519.94 | 0.123424 | 895.369ms | 2496 | 80 | 298.901 | 1566.1 | 3.41611 | 14.3714 | 2.37821 | 0.00158253 | 3.50561e-05 | 5.00801e-06 | 3(Tie) |
| glaze | 1343.95 | 0.0537243 | 915.632ms | 2496 | 160 | 144.871 | 1771.17 | 3.84957 | 15.5036 | 3.10657 | 0.00321765 | 3.75601e-05 | 7.51202e-06 | 5(Loss) |

----
### Mesh Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| simdjson (reflection) | 2109.65 | 0.0487799 | 863.477ms | 2496 | 640 | 193.878 | 1128.32 | 2.48769 | 11.1218 | 1.61018 | 0.000803786 | 1.4398e-05 | 1.878e-06 | 1(Win) |
| simdjson (ondemand) | 2061.92 | 0.0532837 | 865.848ms | 2496 | 2560 | 968.67 | 1154.45 | 2.54001 | 11.1086 | 1.65585 | 0.000825227 | 5.63401e-05 | 1.23635e-05 | 2(Loss) |
| jsonifier (two-stage) | 1930.33 | 0.137167 | 875.203ms | 2496 | 1280 | 3662.15 | 1233.14 | 2.70704 | 10.3385 | 1.82692 | 0.000813802 | 9.73432e-05 | 3.16131e-05 | 3(Loss) |
| glaze | 1724.68 | 0.065391 | 889.332ms | 2496 | 640 | 521.302 | 1380.18 | 3.01944 | 12.3754 | 2.41506 | 0.00160256 | 6.19742e-05 | 2.00321e-05 | 4(Loss) |
| jsonifier | 1716 | 0.16067 | 891.785ms | 2496 | 320 | 1589.56 | 1387.16 | 3.03214 | 11.2829 | 2.53526 | 0.00142728 | 6.63562e-05 | 1.6276e-05 | 5(Loss) |

----
### Mesh Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4266.07 | 0.108045 | 786.479ms | 2496 | 640 | 232.607 | 557.978 | 1.2728 | 3.88301 | 0.410657 | 0.000465745 | 3.19261e-05 | 1.252e-06 | 1(Win) |
| glaze | 1796.25 | 0.281098 | 876.218ms | 2507 | 640 | 8959.2 | 1331.03 | 2.90171 | 7.3574 | 0.854009 | 0.000520418 | 0.000122781 | 1.93209e-05 | 2(Loss) |
| simdjson (reflection) | 194.001 | 0.0409967 | 1978ms | 2502 | 1280 | 32544.5 | 12299.4 | 26.1389 | 99.3797 | 18.4073 | 0.0306367 | 0.000156437 | 7.494e-05 | 3(Loss) |

----
### Mesh Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Mesh%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4518.66 | 0.0855444 | 783.793ms | 2496 | 640 | 129.967 | 526.788 | 1.20618 | 3.68149 | 0.363782 | 0.000496419 | 1.6902e-05 | 2.50401e-06 | 1(Win) |
| glaze | 1937.52 | 0.098646 | 861.247ms | 2507 | 4890 | 7245.78 | 1233.98 | 2.69867 | 6.59793 | 0.687276 | 0.000732672 | 5.77524e-05 | 1.63142e-05 | 2(Loss) |
| simdjson (reflection) | 193.715 | 0.0504545 | 1983.72ms | 2502 | 1280 | 49437.9 | 12317.6 | 26.1638 | 99.6017 | 18.4626 | 0.0297378 | 0.000143323 | 5.71418e-05 | 3(Loss) |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2183.28 | 0.0795276 | 949.304ms | 4926 | 1280 | 3748.15 | 2151.72 | 2.35765 | 10.6102 | 1.84267 | 0.000557945 | 3.82219e-05 | 9.83303e-06 | 1(Win) |
| jsonifier (two-stage) | 1730.88 | 0.0554101 | 1010.72ms | 4926 | 320 | 723.735 | 2714.1 | 2.96449 | 13.0424 | 2.16545 | 0.00434683 | 2.41068e-05 | 6.34389e-07 | 2(Loss) |
| glaze | 1459.68 | 0.13113 | 1060.65ms | 4926 | 320 | 5699.4 | 3218.38 | 3.50584 | 15.4499 | 2.94032 | 0.0017027 | 6.0267e-05 | 1.52253e-05 | 3(Loss) |
| simdjson (reflection) | 1274.08 | 0.0271743 | 1111.34ms | 4926 | 4890 | 4909.34 | 3687.22 | 4.00917 | 14.932 | 2.47117 | 0.0045933 | 6.04447e-05 | 1.65227e-05 | 4(Loss) |
| simdjson (ondemand) | 914.456 | 0.0204253 | 1257.15ms | 4926 | 4890 | 5384.04 | 5137.26 | 5.57182 | 17.6305 | 3.07329 | 0.00383928 | 5.14776e-05 | 1.51112e-05 | 5(Loss) |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2705.49 | 0.034565 | 949.205ms | 4926 | 2560 | 922.167 | 1736.4 | 1.9136 | 8.94336 | 1.45737 | 0.000208 | 2.66443e-05 | 1.11018e-06 | 1(Win) |
| jsonifier (two-stage) | 2044.26 | 0.175898 | 1009.85ms | 4926 | 320 | 5228.62 | 2298.04 | 2.51666 | 11.3752 | 1.78035 | 0.00400807 | 2.09348e-05 | 6.34389e-07 | 2(Loss) |
| glaze | 1859.91 | 0.0349381 | 1026.84ms | 4926 | 4890 | 3808.15 | 2525.83 | 2.76402 | 12.8772 | 2.41454 | 0.00146857 | 4.11406e-05 | 2.94751e-06 | 3(Loss) |
| simdjson (reflection) | 1381.69 | 0.161227 | 1120.78ms | 4926 | 320 | 9616 | 3400.04 | 3.69876 | 14.0924 | 2.25112 | 0.00415271 | 2.79131e-05 | 3.80633e-06 | 4(Loss) |
| simdjson (ondemand) | 1026.83 | 0.0405122 | 1234.05ms | 4926 | 1280 | 4397.16 | 4575.04 | 4.96691 | 15.6638 | 2.68352 | 0.00628901 | 5.50332e-05 | 5.07511e-06 | 5(Loss) |

----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11374.9 | 0.0806285 | 774.181ms | 4926 | 1280 | 141.931 | 412.995 | 0.491402 | 2.12282 | 0.312627 | 0.000203322 | 3.94907e-05 | 1.45909e-05 | 1(Win) |
| simdjson (reflection) | 7495.87 | 0.043813 | 797.293ms | 4926 | 4890 | 368.689 | 626.718 | 0.717169 | 2.58567 | 0.340845 | 0.000203212 | 1.93871e-05 | 2.49085e-06 | 2(Loss) |
| glaze | 3918.13 | 0.0799675 | 855.019ms | 4926 | 4890 | 4495.4 | 1198.99 | 1.33286 | 6.11795 | 0.986196 | 0.000204707 | 4.72847e-05 | 9.0501e-06 | 3(Loss) |

----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12470.3 | 0.116478 | 767.996ms | 4926 | 320 | 61.6134 | 376.719 | 0.449855 | 2.00406 | 0.284815 | 0.000203004 | 8.88145e-06 | 6.34389e-07 | 1(Win) |
| simdjson (reflection) | 8084.22 | 0.0396373 | 792.235ms | 4926 | 1280 | 67.9096 | 581.107 | 0.669652 | 2.47747 | 0.31486 | 0.000203322 | 3.80633e-05 | 6.18529e-06 | 2(Loss) |
| glaze | 4520.72 | 0.13995 | 837.935ms | 4926 | 2560 | 5414.51 | 1039.17 | 1.16156 | 5.57734 | 0.87231 | 0.000213313 | 2.57721e-05 | 6.0267e-06 | 3(Loss) |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3040.31 | 0.0907397 | 1037.85ms | 9463 | 1280 | 9285.94 | 2968.32 | 1.68276 | 7.41044 | 1.14171 | 0.00222908 | 2.50152e-05 | 8.25584e-06 | 1(Win) |
| jsonifier | 2851.29 | 0.0519448 | 1064.62ms | 9463 | 320 | 864.987 | 3165.1 | 1.83074 | 7.61408 | 1.53556 | 0.00105807 | 3.73164e-05 | 1.9814e-05 | 2(Loss) |
| simdjson (reflection) | 2301.12 | 0.0621575 | 1134.26ms | 9463 | 640 | 3803.18 | 3921.84 | 2.21912 | 8.43158 | 1.31523 | 0.00241269 | 1.68419e-05 | 1.65117e-06 | 3(Loss) |
| glaze | 2077.34 | 0.0371851 | 1172.87ms | 9463 | 2560 | 6680.64 | 4344.31 | 2.45637 | 10.7257 | 2.07566 | 0.00248476 | 5.86577e-05 | 2.24146e-05 | 4(Loss) |
| simdjson (ondemand) | 1638.29 | 0.0586692 | 1292.59ms | 9463 | 160 | 1671.15 | 5508.56 | 3.10975 | 9.86674 | 1.63458 | 0.00209302 | 3.17024e-05 | 1.32093e-06 | 5(Loss) |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3536.95 | 0.0562657 | 1041.2ms | 9463 | 2560 | 5276.26 | 2551.52 | 1.45364 | 6.54253 | 0.941245 | 0.00204609 | 1.92361e-05 | 5.69653e-06 | 1(Win) |
| jsonifier | 3218.1 | 0.118482 | 1059.65ms | 9463 | 30 | 331.195 | 2804.33 | 1.59511 | 6.74638 | 1.33509 | 0.000880623 | 1.05675e-05 | 0 | 2(Loss) |
| simdjson (reflection) | 2517.64 | 0.0661822 | 1144.73ms | 9463 | 1280 | 7203.81 | 3584.55 | 2.04689 | 7.99451 | 1.20068 | 0.00218103 | 1.05675e-05 | 0 | 3(Loss) |
| glaze | 2474.76 | 0.0382032 | 1144.34ms | 9463 | 4890 | 9490.79 | 3646.67 | 2.05738 | 9.39089 | 1.80334 | 0.00296244 | 3.29342e-05 | 1.2534e-05 | 4(Loss) |
| simdjson (ondemand) | 1874.29 | 0.0227265 | 1261.83ms | 9463 | 4890 | 5855.46 | 4814.96 | 2.72017 | 8.77037 | 1.4172 | 0.00328121 | 2.91524e-05 | 5.74836e-06 | 5(Loss) |

----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 19456.8 | 0.061991 | 786.067ms | 9463 | 1280 | 105.824 | 463.83 | 0.282962 | 1.2085 | 0.162845 | 0.00010584 | 9.41166e-06 | 1.65117e-06 | 1(Win) |
| glaze | 4595.33 | 0.0979338 | 939.275ms | 9463 | 1280 | 4734.78 | 1963.87 | 1.12601 | 4.70453 | 0.708972 | 0.0001065 | 1.02372e-05 | 3.71513e-06 | 2(Loss) |
| simdjson (reflection) | 542.592 | 0.100794 | 2413.55ms | 9463 | 4890 | 1.37433e+06 | 16632.4 | 9.34991 | 38.1562 | 6.73332 | 0.00913194 | 7.7149e-05 | 4.71971e-05 | 3(Loss) |

----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 22226.8 | 0.140883 | 771.497ms | 9463 | 80 | 26.1766 | 406.025 | 0.250107 | 1.14551 | 0.148262 | 0.000105675 | 1.32093e-06 | 0 | 1(Win) |
| glaze | 5617.37 | 0.0752321 | 900.43ms | 9463 | 2560 | 3739.72 | 1606.56 | 0.922494 | 4.37388 | 0.634788 | 0.000151247 | 1.72134e-05 | 2.60059e-06 | 2(Loss) |
| simdjson (reflection) | 540.483 | 0.0983537 | 2424.12ms | 9463 | 4890 | 1.31882e+06 | 16697.3 | 9.37138 | 38.1209 | 6.72492 | 0.00962414 | 4.56411e-05 | 2.58676e-05 | 3(Loss) |

----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 5379.51 | 0.0750708 | 784.586ms | 2821 | 4890 | 689.241 | 500.104 | 1.01863 | 3.57745 | 0.472528 | 0.000355137 | 3.16789e-05 | 7.97408e-06 | 1(Win) |
| jsonifier | 5330.13 | 0.182719 | 787.011ms | 2821 | 80 | 68.0441 | 504.738 | 1.02208 | 3.57745 | 0.472527 | 0.000354484 | 1.32932e-05 | 0 | 2(Loss) |
| simdjson (ondemand) | 4855.84 | 0.0915764 | 794.005ms | 2821 | 1280 | 329.499 | 554.037 | 1.12051 | 4.54272 | 0.696916 | 0.000708968 | 6.20347e-05 | 2.52016e-05 | 3(Loss) |
| simdjson (reflection) | 4625.11 | 0.0269299 | 792.464ms | 2821 | 4890 | 119.989 | 581.675 | 1.17361 | 4.57675 | 0.705069 | 0.000727526 | 2.44297e-05 | 1.52232e-06 | 4(Loss) |
| glaze | 2575.79 | 0.0625948 | 862.002ms | 2821 | 2560 | 1094.21 | 1044.46 | 2.04056 | 8.77384 | 1.3598 | 0.00044906 | 1.95243e-05 | 3.7387e-06 | 5(Loss) |

----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 6065.07 | 0.0933062 | 787.086ms | 2821 | 320 | 54.8157 | 443.575 | 0.921309 | 3.36476 | 0.423963 | 0.000581576 | 2.54786e-05 | 3.32329e-06 | 1(Win) |
| jsonifier | 6025.15 | 0.0453363 | 786.718ms | 2821 | 1280 | 52.4533 | 446.514 | 0.925958 | 3.36476 | 0.423963 | 0.000557482 | 1.77242e-05 | 2.76941e-07 | 2(Loss) |
| simdjson (ondemand) | 5015.81 | 0.0481404 | 788.747ms | 2821 | 2560 | 170.68 | 536.367 | 1.087 | 4.46615 | 0.678483 | 0.000708138 | 1.98013e-05 | 4.15411e-06 | 3(Loss) |
| simdjson (reflection) | 4697.64 | 0.191461 | 797.588ms | 2821 | 640 | 769.464 | 572.695 | 1.15338 | 4.50479 | 0.687345 | 0.000710076 | 8.86211e-06 | 1.66164e-06 | 4(Loss) |
| glaze | 2615.15 | 0.114174 | 838.037ms | 2821 | 160 | 220.733 | 1028.74 | 2.01676 | 8.69869 | 1.34101 | 0.000354484 | 3.98795e-05 | 1.10776e-05 | 5(Loss) |

----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 6967.2 | 0.0974739 | 798.584ms | 4147 | 320 | 97.9667 | 567.644 | 0.77679 | 2.89703 | 0.328671 | 0.00025847 | 2.93887e-05 | 7.53557e-07 | 1(Win) |
| jsonifier | 6749.75 | 0.098885 | 799.595ms | 4147 | 320 | 107.425 | 585.931 | 0.805586 | 2.89703 | 0.328671 | 0.00106779 | 9.04268e-06 | 1.50711e-06 | 2(Loss) |
| simdjson (ondemand) | 6354.06 | 0.0668246 | 795.784ms | 4147 | 4890 | 845.955 | 622.419 | 0.852068 | 3.53123 | 0.492646 | 0.000459198 | 1.90839e-05 | 2.51494e-06 | 3(Loss) |
| simdjson (reflection) | 6090.24 | 0.0588725 | 801.072ms | 4147 | 4890 | 714.716 | 649.381 | 0.883865 | 3.55438 | 0.498192 | 0.000357072 | 2.19441e-05 | 5.523e-06 | 4(Loss) |
| glaze | 3288.89 | 0.100582 | 863.162ms | 4147 | 160 | 234.063 | 1202.5 | 1.59056 | 7.19267 | 1.20087 | 0.000299916 | 1.65782e-05 | 0 | 5(Loss) |

----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 7454.25 | 0.0770208 | 795.704ms | 4147 | 640 | 106.87 | 530.555 | 0.730784 | 2.75235 | 0.295635 | 0.000241138 | 1.43176e-05 | 3.01423e-06 | 1(Tie) |
| jsonifier (two-stage) STATISTICAL TIE | 7446.92 | 0.0640326 | 795.453ms | 4147 | 4890 | 565.492 | 531.077 | 0.728975 | 2.75235 | 0.295635 | 0.000346815 | 1.96757e-05 | 2.07113e-06 | 1(Tie) |
| simdjson (ondemand) | 6445.99 | 0.0906287 | 795.271ms | 4147 | 4890 | 1511.92 | 613.543 | 0.837513 | 3.47914 | 0.480106 | 0.000442777 | 1.56321e-05 | 8.38313e-07 | 3(Loss) |
| simdjson (reflection) | 6143.4 | 0.094408 | 800.161ms | 4147 | 320 | 118.2 | 643.763 | 0.874761 | 3.50543 | 0.486135 | 0.000437816 | 1.95925e-05 | 0 | 4(Loss) |
| glaze | 3396.59 | 0.072732 | 854.488ms | 4147 | 160 | 114.75 | 1164.37 | 1.57009 | 7.14034 | 1.18809 | 0.000293887 | 2.10996e-05 | 4.52134e-06 | 5(Loss) |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2967.17 | 0.0572303 | 834.152ms | 2821 | 160 | 43.0817 | 906.694 | 1.7822 | 5.99397 | 0.996455 | 0.000354484 | 4.43105e-05 | 2.21553e-06 | 1(Win) |
| glaze | 2326.7 | 0.0627885 | 859.817ms | 2821 | 2560 | 1349.36 | 1156.28 | 2.25315 | 8.90429 | 1.51897 | 0.000524941 | 4.27874e-05 | 5.53882e-06 | 2(Loss) |
| jsonifier (two-stage) | 2307.85 | 0.0970911 | 855.338ms | 2821 | 80 | 102.48 | 1165.72 | 2.2698 | 7.82276 | 1.19 | 0.000354484 | 1.77242e-05 | 0 | 3(Loss) |
| simdjson (reflection) | 1866.14 | 0.0589064 | 886.651ms | 2821 | 2560 | 1846.22 | 1441.65 | 2.79372 | 9.03509 | 1.37646 | 0.00119791 | 6.12039e-05 | 6.0927e-06 | 4(Loss) |
| simdjson (ondemand) | 1628.38 | 0.0525603 | 903.688ms | 2821 | 320 | 241.302 | 1652.14 | 3.1834 | 9.86033 | 1.7079 | 0.000907258 | 4.09872e-05 | 3.32329e-06 | 5(Loss) |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3304.91 | 0.0700116 | 829.963ms | 2821 | 4890 | 1588.31 | 814.035 | 1.60666 | 5.48529 | 0.862461 | 0.000366373 | 4.67571e-05 | 8.48152e-06 | 1(Win) |
| glaze | 2575.51 | 0.048466 | 854.421ms | 2821 | 4890 | 1253.33 | 1044.58 | 2.05567 | 8.38356 | 1.38249 | 0.000386381 | 7.59713e-05 | 3.35636e-05 | 2(Loss) |
| jsonifier (two-stage) | 2462.84 | 0.0632192 | 853.93ms | 2821 | 2560 | 1220.88 | 1092.36 | 2.13031 | 7.22971 | 1.04041 | 0.000381071 | 2.93557e-05 | 6.23117e-06 | 3(Loss) |
| simdjson (reflection) | 2023.29 | 0.0957804 | 879.532ms | 2821 | 160 | 259.516 | 1329.67 | 2.5791 | 8.53527 | 1.24849 | 0.000726693 | 9.52676e-05 | 1.77242e-05 | 4(Loss) |
| simdjson (ondemand) | 1723 | 0.0395896 | 906.911ms | 2821 | 4890 | 1868.57 | 1561.42 | 3.00812 | 9.48458 | 1.60865 | 0.000715203 | 0.000105983 | 2.55896e-05 | 5(Loss) |

----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 7622.77 | 0.0433049 | 773.068ms | 2821 | 320 | 7.47488 | 352.931 | 0.741928 | 1.77033 | 0.264804 | 0.000363346 | 4.32028e-05 | 0 | 1(Win) |
| simdjson (reflection) | 5958.49 | 0.208573 | 785.788ms | 2821 | 320 | 283.793 | 451.509 | 0.926981 | 2.09855 | 0.323999 | 0.000358915 | 5.20649e-05 | 8.86211e-06 | 2(Loss) |
| glaze | 5232.65 | 0.100562 | 791.849ms | 2819 | 4890 | 1305.34 | 513.775 | 1.04251 | 3.04931 | 0.460093 | 0.000356404 | 8.71968e-05 | 3.85204e-05 | 3(Loss) |

----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 8713.84 | 0.0545689 | 762.872ms | 2821 | 320 | 9.08298 | 308.741 | 0.659014 | 1.59199 | 0.222971 | 0.000354484 | 1.21854e-05 | 0 | 1(Win) |
| simdjson (reflection) | 6618.25 | 0.150149 | 776.715ms | 2821 | 2560 | 953.685 | 406.5 | 0.84087 | 1.9206 | 0.282524 | 0.000363346 | 9.29136e-05 | 3.18482e-05 | 2(Loss) |
| glaze | 5589.64 | 0.0778479 | 790.187ms | 2819 | 4890 | 685.527 | 480.962 | 0.980712 | 2.59312 | 0.366087 | 0.000355244 | 5.94853e-05 | 9.57569e-06 | 3(Loss) |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3165.72 | 0.0403353 | 858.655ms | 4147 | 640 | 162.508 | 1249.29 | 1.65001 | 5.85218 | 0.829756 | 0.000241138 | 1.92157e-05 | 2.26067e-06 | 1(Win) |
| simdjson (reflection) | 2589.08 | 0.0799238 | 894.312ms | 4147 | 640 | 953.915 | 1527.53 | 2.00505 | 6.58717 | 0.954908 | 0.00115859 | 2.59977e-05 | 3.01423e-06 | 2(Loss) |
| glaze | 2480.04 | 0.0548608 | 901.905ms | 4147 | 4890 | 3742.69 | 1594.69 | 2.09142 | 7.89728 | 1.40029 | 0.000286506 | 6.22324e-05 | 2.39659e-05 | 3(Loss) |
| jsonifier | 2393.25 | 0.0340396 | 900.936ms | 4147 | 320 | 101.254 | 1652.52 | 2.16836 | 5.58934 | 1.08271 | 0.000657855 | 4.5967e-05 | 6.78201e-06 | 4(Loss) |
| simdjson (ondemand) | 2304.36 | 0.0485903 | 913.804ms | 4147 | 1280 | 890.177 | 1716.26 | 2.24797 | 7.14854 | 1.18037 | 0.000490377 | 4.37063e-05 | 7.34718e-06 | 5(Loss) |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier (two-stage) | 3535.11 | 0.0481047 | 855.374ms | 4147 | 320 | 92.6802 | 1118.74 | 1.48392 | 5.38775 | 0.715939 | 0.000241138 | 2.0346e-05 | 1.50711e-06 | 1(Win) |
| simdjson (reflection) | 2797.46 | 0.103491 | 885.917ms | 4147 | 1280 | 2740.01 | 1413.74 | 1.86548 | 6.24813 | 0.868098 | 0.000587963 | 6.21684e-05 | 1.46944e-05 | 2(Loss) |
| glaze | 2646.48 | 0.0683424 | 892.114ms | 4147 | 1280 | 1335.13 | 1494.4 | 1.96382 | 7.57511 | 1.31396 | 0.000265817 | 4.95464e-05 | 1.84621e-05 | 3(Loss) |
| jsonifier | 2559.09 | 0.0934028 | 896.865ms | 4147 | 1280 | 2667.01 | 1545.42 | 2.03015 | 5.24403 | 0.991801 | 0.000462119 | 8.10074e-05 | 5.25606e-05 | 4(Loss) |
| simdjson (ondemand) | 2408.36 | 0.0953494 | 909.05ms | 4147 | 160 | 392.267 | 1642.15 | 2.15337 | 6.89293 | 1.11285 | 0.000739993 | 4.37063e-05 | 1.50711e-06 | 5(Loss) |

----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 11315.9 | 0.0378381 | 771.041ms | 4147 | 640 | 11.1925 | 349.497 | 0.500194 | 1.20304 | 0.169761 | 0.000241515 | 2.67513e-05 | 0 | 1(Win) |
| glaze | 3293.8 | 0.300692 | 860.039ms | 4145 | 1280 | 16668.9 | 1200.13 | 1.60599 | 3.55103 | 0.506152 | 0.000243893 | 7.85962e-05 | 2.95914e-05 | 2(Loss) |
| simdjson (reflection) | 519.137 | 0.0886363 | 1514.02ms | 4147 | 2560 | 116726 | 7618.19 | 9.7896 | 33.8773 | 6.05233 | 0.00310776 | 8.06306e-05 | 4.70973e-05 | 3(Loss) |

----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 12454.6 | 0.0517201 | 768.115ms | 4147 | 320 | 8.63131 | 317.544 | 0.4596 | 1.12443 | 0.150952 | 0.000241138 | 1.65782e-05 | 0 | 1(Win) |
| glaze | 3925.92 | 0.373975 | 839.208ms | 4145 | 1280 | 18149.3 | 1006.89 | 1.33977 | 2.98577 | 0.379735 | 0.000241255 | 2.20522e-05 | 4.14656e-06 | 2(Loss) |
| simdjson (reflection) | 519.06 | 0.0883295 | 1517.26ms | 4147 | 2560 | 115954 | 7619.32 | 9.78935 | 33.8917 | 6.05546 | 0.00297928 | 0.000299539 | 0.000196302 | 3(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3168.02 | 0.0557587 | 7545.87ms | 466906 | 80 | 491359 | 140554 | 1.59448 | 6.18952 | 1.19682 | 0.00282418 | 0.000746751 | 4.73864e-06 | 1(Win) |
| glaze | 2412.31 | 0.0149173 | 9825.13ms | 466906 | 640 | 485237 | 184585 | 2.09554 | 8.77 | 1.98464 | 0.00255251 | 0.000669751 | 2.63537e-05 | 2(Loss) |
| simdjson (ondemand) | 1346.81 | 0.0775076 | 8651.11ms | 466906 | 1280 | 8.40517e+07 | 330616 | 3.73559 | 14.2928 | 2.49673 | 0.0135361 | 0.0910164 | 2.16987e-05 | 3(Loss) |

----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 3179.49 | 0.128539 | 7535.97ms | 466906 | 320 | 1.03696e+07 | 140046 | 1.58177 | 6.1884 | 1.19656 | 0.00278153 | 0.000774132 | 3.89934e-05 | 1(Win) |
| glaze | 2414.27 | 0.0605773 | 9838.09ms | 466906 | 40 | 499305 | 184435 | 2.09299 | 8.76889 | 1.9844 | 0.00251849 | 0.000590751 | 1.1512e-05 | 2(Loss) |
| simdjson (ondemand) | 1346.41 | 0.0744907 | 8677.63ms | 466906 | 1280 | 7.76823e+07 | 330715 | 3.7476 | 14.2933 | 2.49685 | 0.0136511 | 0.0953545 | 5.76167e-05 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4175.17 | 0.0341454 | 8541.98ms | 699405 | 2560 | 7.6175e+06 | 159755 | 1.21004 | 4.52635 | 1.0973 | 0.00244079 | 0.00258095 | 1.84778e-05 | 1(Win) |
| glaze | 3672.8 | 0.0232783 | 9673ms | 699405 | 2560 | 4.57517e+06 | 181607 | 1.37575 | 6.02381 | 1.25785 | 0.00209338 | 0.00124084 | 3.93806e-06 | 2(Loss) |
| simdjson (ondemand) | 1509.26 | 0.321669 | 6268.07ms | 767297 | 640 | 1.55666e+09 | 484840 | 3.32535 | 13.9345 | 2.26931 | 0.0112554 | 0.0922946 | 3.26206e-05 | 3(Loss) |

----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 4151.73 | 0.0311669 | 8587ms | 699405 | 2560 | 6.41838e+06 | 160657 | 1.21492 | 4.52585 | 1.0972 | 0.00232257 | 0.00243217 | 5.48457e-06 | 1(Win) |
| glaze | 3657.41 | 0.0329847 | 9690.01ms | 699405 | 1280 | 4.63175e+06 | 182371 | 1.37718 | 6.02306 | 1.25768 | 0.00206904 | 0.00110398 | 9.27239e-06 | 2(Loss) |
| simdjson (ondemand) | 1502.67 | 0.302934 | 6279.94ms | 767297 | 640 | 1.39275e+09 | 486967 | 3.32017 | 13.9345 | 2.26931 | 0.0113738 | 0.0919022 | 0.000170471 | 3(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- |
| jsonifier | 2980.43 | 0.082295 | 5356.8ms | 631514 | 640 | 1.76985e+07 | 202071 | 1.69097 | 8.04061 | 1.32244 | 0.00608885 | 1.18243e-05 | 1.01047e-05 | 1(Win) |
| glaze | 2474.94 | 0.130571 | 6414.05ms | 631514 | 80 | 8.07646e+06 | 243343 | 2.04161 | 8.43597 | 1.51701 | 0.00807152 | 2.06448e-05 | 1.80717e-05 | 2(Loss) |
