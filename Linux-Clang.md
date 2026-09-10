# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

Latest Results: (Oct 01, 2026)
#### Using the following commits:
----
| Jsonifier: [e2e111b](https://github.com/nihilai-collective/jsonifier/commit/e2e111b)  
| Simdjson (On Demand): [610f14d](https://github.com/simdjson/simdjson/commit/610f14d)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | `AVX2` |
| simdjson (ondemand) | `haswell` |
> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below. 

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 5 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 5.000000% AND mean shift < 2.500000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. "jsonifier" is performing scalar structural iteration; "jsonifier (two-stage)" is the same parse call routed through stage-1 + stage-2)

In all non-reverse lookup tests, all libraries, including simdjson, receive all of the documents in the defined parsing order.

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [ced5b69](https://github.com/nihilai-collective/benchmarksuite/commit/ced5b69).
  
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2145.34 | 0.367694 | 341.688ms | 905 | 320 | 700.212 | 402.303 | 1.34347 | 1(Win) |
| jsonifier (two-stage) | 337.078 | 0.373001 | 558.522ms | 905 | 640 | 58376.3 | 2560.46 | 8.93919 | 2(Loss) |
| simdjson (ondemand) | 215.056 | 0.186579 | 708.889ms | 905 | 30 | 1682.06 | 4013.27 | 14.0451 | 3(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3361.33 | 0.346337 | 409.83ms | 3862 | 40 | 576.051 | 1095.72 | 0.886186 | 1(Win) |
| jsonifier (two-stage) | 1028.54 | 0.216902 | 662.226ms | 3862 | 80 | 4826.09 | 3580.88 | 2.93065 | 2(Loss) |
| simdjson (ondemand) | 599.127 | 0.0842883 | 926.204ms | 3862 | 40 | 1073.94 | 6147.43 | 5.05085 | 3(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2556.56 | 0.142885 | 819.054ms | 9578 | 80 | 2084.99 | 3572.89 | 1.18113 | 1(Win) |
| simdjson (ondemand) | 1461.56 | 0.181233 | 1088.6ms | 9578 | 30 | 3848.64 | 6249.67 | 2.07153 | 2(Loss) |
| jsonifier (two-stage) | 1444.09 | 0.4124 | 1113.23ms | 9578 | 80 | 54435.9 | 6325.27 | 2.09619 | 3(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3923.08 | 0.451347 | 398.738ms | 3873 | 40 | 722.308 | 941.5 | 0.757888 | 1(Win) |
| jsonifier (two-stage) | 999.795 | 0.434617 | 679.991ms | 3873 | 1280 | 329987 | 3694.34 | 3.02403 | 2(Loss) |
| simdjson (ondemand) | 591.899 | 0.0856552 | 939.124ms | 3873 | 40 | 1142.79 | 6240.23 | 5.1181 | 3(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1233.48 | 0.154913 | 6283.73ms | 2090234 | 30 | 1.88029e+08 | 1.61608e+06 | 2.46298 | 1(Win) |
| jsonifier (two-stage) | 1033.16 | 0.170755 | 7258.39ms | 2090234 | 40 | 4.34171e+08 | 1.92942e+06 | 2.94057 | 2(Loss) |
| simdjson (ondemand) | 732.231 | 0.118684 | 9812.15ms | 2090234 | 160 | 1.67032e+09 | 2.72237e+06 | 4.14978 | 3(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3114.99 | 0.184584 | 7611.11ms | 6661897 | 40 | 5.66937e+08 | 2.03959e+06 | 0.975386 | 1(Win) |
| jsonifier | 2852.87 | 0.115837 | 8123.23ms | 6661897 | 80 | 5.32372e+08 | 2.22698e+06 | 1.06505 | 2(Loss) |
| simdjson (ondemand) | 2159.27 | 0.292925 | 5069.21ms | 6661897 | 30 | 2.22852e+09 | 2.94233e+06 | 1.40725 | 3(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2063 | 0.123713 | 6815.83ms | 500299 | 640 | 5.23927e+07 | 231276 | 1.47297 | 1(Win) |
| jsonifier (two-stage) | 1869.25 | 0.172791 | 7474.6ms | 500299 | 1280 | 2.48988e+08 | 255248 | 1.62549 | 2(Loss) |
| simdjson (ondemand) | 1185.62 | 0.259669 | 5663.78ms | 500299 | 160 | 1.74715e+08 | 402425 | 2.56299 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 4503.44 | 0.196658 | 8749.53ms | 1439562 | 320 | 1.15012e+08 | 304850 | 0.674678 | 1(Win) |
| jsonifier | 3975.52 | 0.160247 | 9756.59ms | 1439562 | 640 | 1.95989e+08 | 345331 | 0.764277 | 2(Loss) |
| simdjson (ondemand) | 3000.7 | 0.157858 | 6359.02ms | 1439562 | 640 | 3.33832e+08 | 457518 | 1.01263 | 3(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2310.73 | 0.301066 | 2965.65ms | 56369 | 320 | 1.56984e+06 | 23264.4 | 1.31368 | 1(Win) |
| jsonifier (two-stage) | 1944.83 | 0.376777 | 3441.59ms | 56369 | 160 | 1.73542e+06 | 27641.3 | 1.56122 | 2(Loss) |
| simdjson (ondemand) | 1480.22 | 0.633827 | 4266.41ms | 56369 | 1280 | 6.78233e+07 | 36317.3 | 2.0516 | 3(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2955.63 | 0.369587 | 3646.15ms | 94370 | 4890 | 6.19314e+07 | 30449.8 | 1.02724 | 1(Win) |
| simdjson (ondemand) | 2359.54 | 0.390181 | 4438.98ms | 94370 | 2560 | 5.67002e+07 | 38142.2 | 1.28698 | 2(Loss) |
| jsonifier | 2254.8 | 0.397702 | 4603.68ms | 94370 | 2560 | 6.45071e+07 | 39914 | 1.34692 | 3(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1915.35 | 0.11605 | 941.045ms | 11812 | 30 | 1397.54 | 5881.33 | 1.58002 | 1(Win) |
| jsonifier (two-stage) | 1709.03 | 1.29535 | 1030.78ms | 11812 | 30 | 218697 | 6591.33 | 1.77118 | 2(Loss) |
| simdjson (ondemand) | 1138.12 | 0.419611 | 1350.7ms | 11812 | 640 | 1.10395e+06 | 9897.75 | 2.66271 | 3(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3760.39 | 0.348838 | 1154.76ms | 31235 | 640 | 488703 | 7921.52 | 0.805809 | 1(Win) |
| jsonifier | 3265.98 | 0.498938 | 1285.96ms | 31235 | 320 | 662670 | 9120.68 | 0.927786 | 2(Loss) |
| simdjson (ondemand) | 2766.45 | 0.0839147 | 1468.44ms | 31235 | 40 | 3265.68 | 10767.6 | 1.09595 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2952.05 | 0.063668 | 4034.05ms | 108313 | 30 | 14889.4 | 34991 | 1.02879 | 1(Win) |
| jsonifier (two-stage) | 2174.06 | 0.379311 | 5194.86ms | 108313 | 4890 | 1.58824e+08 | 47512.5 | 1.39707 | 2(Loss) |
| simdjson (ondemand) | 1607.79 | 0.210689 | 6971.1ms | 108313 | 2560 | 4.69061e+07 | 64246.9 | 1.88923 | 3(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3855.52 | 0.251393 | 5754.43ms | 213963 | 2560 | 4.53165e+07 | 52924.4 | 0.787816 | 1(Win) |
| simdjson (ondemand) | 2954.02 | 0.560392 | 7423.46ms | 213963 | 160 | 2.39749e+07 | 69075.8 | 1.02841 | 2(Loss) |
| jsonifier | 2906.47 | 0.59555 | 7172.06ms | 213963 | 2560 | 4.47531e+08 | 70205.9 | 1.04511 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 949.215 | 0.199965 | 6359.17ms | 1834197 | 160 | 2.17265e+09 | 1.84281e+06 | 3.20135 | 1(Win) |
| jsonifier (two-stage) | 793.004 | 0.140258 | 7518.83ms | 1834197 | 80 | 7.65752e+08 | 2.20582e+06 | 3.83182 | 2(Loss) |
| simdjson (ondemand) | 197.773 | 0.204145 | 6430.76ms | 1834197 | 30 | 9.78046e+09 | 8.84463e+06 | 15.3665 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 3560.55 | 0.214122 | 8962.47ms | 9930848 | 30 | 9.73157e+08 | 2.65992e+06 | 0.853426 | 1(Win) |
| jsonifier | 3374.7 | 0.15041 | 9494.08ms | 9930848 | 160 | 2.85088e+09 | 2.80641e+06 | 0.900381 | 2(Loss) |
| simdjson (ondemand) | 905.853 | 0.246104 | 7640.45ms | 9930848 | 30 | 1.98617e+10 | 1.04551e+07 | 3.35488 | 3(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 976.115 | 0.145018 | 6274.23ms | 1834197 | 160 | 1.08057e+09 | 1.79203e+06 | 3.1129 | 1(Win) |
| jsonifier (two-stage) | 815.496 | 0.19856 | 7369.83ms | 1834197 | 80 | 1.45118e+09 | 2.14499e+06 | 3.72585 | 2(Loss) |
| simdjson (ondemand) | 615.217 | 0.176977 | 9665.08ms | 1834197 | 80 | 2.02563e+09 | 2.84327e+06 | 4.93938 | 3(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1463.28 | 0.183716 | 5864.84ms | 642697 | 320 | 1.89497e+08 | 418869 | 2.0764 | 1(Win) |
| simdjson (ondemand) | 1264.58 | 0.31143 | 6650.52ms | 642697 | 80 | 1.82277e+08 | 484686 | 2.40283 | 2(Loss) |
| jsonifier (two-stage) | 1228.91 | 0.232583 | 6912.85ms | 642697 | 160 | 2.15301e+08 | 498753 | 2.47233 | 3(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) STATISTICAL TIE | 2323.8 | 0.234539 | 6951.56ms | 1225964 | 320 | 4.45595e+08 | 503129 | 1.30745 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2312.15 | 0.20108 | 6868.66ms | 1225964 | 160 | 1.65416e+08 | 505663 | 1.3141 | 1(Tie) |
| jsonifier | 1863.97 | 0.276799 | 8458.51ms | 1225964 | 160 | 4.82311e+08 | 627247 | 1.63 | 3(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1866.33 | 0.435544 | 6788.47ms | 409725 | 80 | 6.65216e+07 | 209365 | 1.62812 | 1(Win) |
| jsonifier (two-stage) | 1553.42 | 0.193707 | 7995.31ms | 409725 | 320 | 7.59717e+07 | 251538 | 1.95599 | 2(Loss) |
| simdjson (ondemand) | 1098.31 | 0.16041 | 5299.59ms | 409725 | 640 | 2.0844e+08 | 355769 | 2.76665 | 3(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2696.92 | 0.438961 | 8482.5ms | 785750 | 40 | 5.95038e+07 | 277854 | 1.1266 | 1(Win) |
| jsonifier | 2074.62 | 0.194704 | 5234.74ms | 785750 | 640 | 3.16535e+08 | 361199 | 1.46464 | 2(Loss) |
| simdjson (ondemand) | 1917.84 | 0.420125 | 5664.21ms | 785750 | 80 | 2.15572e+08 | 390727 | 1.58438 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2506.47 | 0.173899 | 6115.45ms | 264040 | 2560 | 7.81352e+07 | 100463 | 1.21213 | 1(Win) |
| jsonifier (two-stage) | 1948.83 | 0.18462 | 7638.03ms | 264040 | 2560 | 1.45677e+08 | 129210 | 1.559 | 2(Loss) |
| simdjson (ondemand) | 1840.24 | 0.687438 | 8033.04ms | 264040 | 160 | 1.41572e+08 | 136834 | 1.65101 | 3(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier (two-stage) | 2738.61 | 0.256472 | 8014.74ms | 399947 | 2560 | 3.26636e+08 | 139275 | 1.10938 | 1(Win) |
| simdjson (ondemand) | 2609.92 | 0.161414 | 8517.01ms | 399947 | 2560 | 1.42453e+08 | 146142 | 1.16424 | 2(Loss) |
| jsonifier | 2421.37 | 0.405081 | 8841.69ms | 399947 | 640 | 2.60583e+08 | 157522 | 1.25485 | 3(Loss) |
