# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.17.0-1022-azure using the Clang 24.0.0 compiler).  

Latest Results: (Sep 27, 2026)
#### Using the following commits:
----
| Jsonifier: [13fff52](https://github.com/nihilai-collective/jsonifier/commit/13fff52)  
| Simdjson (On Demand): [645e5c8](https://github.com/simdjson/simdjson/commit/645e5c8)  

#### Active Implementations:
| Library | Active Implementation |
| ------- | --------------------- |
| Jsonifier | AVX512 |
| simdjson (ondemand) | icelake |

> Each library selects its own instruction-set implementation at build or run time; the values above are the implementations that produced the results below.

> Both libraries are executing only 'stage-1' parsing, where they identify the structural indices, and neither of them are performing utf-8 validation in these tests. Adaptive sampling on (AMD EPYC 9V45 96-Core Processor-AVX512): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Sampling does not stop early: epochs continue until 20 seconds have elapsed or the iteration cap is reached. Every epoch after the first is scored by its RSE plus its epoch-over-epoch mean shift (%), and the lowest-scoring epoch is retained as the canonical result. A result counts as converged only if that retained epoch has RSE < 10.000000% AND mean shift < 10.000000%; non-converged results are excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

#### Note:
 This is the commit of BenchmarkSuite that was used to generate these results: [343f572](https://github.com/nihilai-collective/benchmarksuite/commit/343f572).
 
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 222.896 | 0.0444324 | 1033.1ms | 905 | 40 | 118.4 | 3872.1 | 11.0311 | 1(Win) |
| simdjson (ondemand) | 211.207 | 0.046031 | 1061.05ms | 905 | 40 | 141.528 | 4086.4 | 11.6489 | 2(Loss) |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 445.703 | 0.0737462 | 1057.23ms | 1811 | 80 | 653.304 | 3875.01 | 5.51755 | 1(Win) |
| simdjson (ondemand) | 418.112 | 0.0550137 | 1067.94ms | 1811 | 40 | 206.563 | 4130.73 | 5.8844 | 2(Loss) |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 935.471 | 0.0508433 | 1096.52ms | 3862 | 40 | 160.285 | 3937.15 | 2.62859 | 1(Win) |
| simdjson (ondemand) | 892.603 | 0.0875177 | 1065.52ms | 3862 | 30 | 391.22 | 4126.23 | 2.75615 | 2(Loss) |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2341.51 | 0.00971539 | 1042.09ms | 9578 | 320 | 45.965 | 3901.02 | 1.05026 | 1(Win) |
| simdjson (ondemand) | 2098.7 | 0.0215936 | 1103.3ms | 9578 | 320 | 282.65 | 4352.36 | 1.17214 | 2(Loss) |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 935.697 | 0.045678 | 1043.67ms | 3873 | 80 | 260.094 | 3947.41 | 2.62808 | 1(Win) |
| simdjson (ondemand) | 898.922 | 0.0794608 | 1062.44ms | 3873 | 40 | 426.4 | 4108.9 | 2.73675 | 2(Loss) |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 28691.7 | 0.117422 | 7792.37ms | 2090234 | 2560 | 1.70379e+07 | 69476.7 | 0.0862518 | 1(Win) |
| simdjson (ondemand) | 20555.2 | 0.251617 | 10359.6ms | 2090234 | 320 | 1.90537e+07 | 96978.1 | 0.120412 | 2(Loss) |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 25465.7 | 0.0282037 | 25608.9ms | 6661897 | 4890 | 2.42107e+07 | 249484 | 0.0972111 | 1(Win) |
| simdjson (ondemand) | 20580.6 | 0.0361863 | 31519.3ms | 6661897 | 2560 | 3.19453e+07 | 308702 | 0.120287 | 2(Loss) |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 21381.5 | 0.233594 | 2871.64ms | 500299 | 4890 | 1.32866e+07 | 22314.7 | 0.115651 | 1(Win) |
| simdjson (ondemand) | 17398.3 | 0.200096 | 3379.15ms | 500299 | 4890 | 1.47242e+07 | 27423.4 | 0.142161 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 21205.5 | 0.0893041 | 7100.76ms | 1439562 | 4890 | 1.63462e+07 | 64741.4 | 0.116705 | 1(Win) |
| simdjson (ondemand) | 20426.3 | 0.247362 | 7347.73ms | 1439562 | 640 | 1.769e+07 | 67211.2 | 0.12116 | 2(Loss) |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 21854.3 | 0.0285411 | 906.121ms | 56369 | 160 | 78.8623 | 2459.82 | 0.112069 | 1(Win) |
| simdjson (ondemand) | 19859.4 | 0.0184113 | 929.378ms | 56369 | 160 | 39.7407 | 2706.91 | 0.123446 | 2(Loss) |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22287.1 | 0.0423522 | 1068.14ms | 94370 | 80 | 233.994 | 4038.14 | 0.110381 | 1(Win) |
| simdjson (ondemand) | 20269.9 | 0.0241467 | 1098.46ms | 94370 | 30 | 34.4828 | 4440 | 0.121471 | 2(Loss) |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 20370.6 | 0.0887307 | 723.651ms | 11812 | 160 | 38.522 | 552.994 | 0.115865 | 1(Win) |
| simdjson (ondemand) | 18155.1 | 0.199485 | 733.305ms | 11812 | 40 | 61.2814 | 620.475 | 0.130461 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 21438.9 | 0.067609 | 800.27ms | 31235 | 160 | 141.191 | 1389.44 | 0.113343 | 1(Win) |
| simdjson (ondemand) | 20219.6 | 0.0513575 | 806.622ms | 31235 | 80 | 45.7968 | 1473.22 | 0.120246 | 2(Loss) |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22614.4 | 0.0371204 | 1116.49ms | 108313 | 40 | 114.994 | 4567.68 | 0.108824 | 1(Win) |
| simdjson (ondemand) | 19359.4 | 0.0220039 | 1193.9ms | 108313 | 80 | 110.273 | 5335.68 | 0.127286 | 2(Loss) |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22736.7 | 0.105297 | 1563.04ms | 213963 | 40 | 3572 | 8974.52 | 0.108565 | 1(Win) |
| simdjson (ondemand) | 20743.4 | 0.025067 | 1642.61ms | 213963 | 30 | 182.409 | 9836.93 | 0.119037 | 2(Loss) |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22494.6 | 0.0786612 | 8400.85ms | 1834197 | 4890 | 1.82964e+07 | 77762 | 0.110025 | 1(Win) |
| simdjson (ondemand) | 18368.3 | 0.0634821 | 10144.2ms | 1834197 | 4890 | 1.78718e+07 | 95231 | 0.13475 | 2(Loss) |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 23075.6 | 0.0331789 | 21316.5ms | 9930848 | 1280 | 2.37357e+07 | 410425 | 0.107284 | 1(Win) |
| simdjson (ondemand) | 20575.2 | 0.0706548 | 23887.2ms | 9930848 | 320 | 3.38469e+07 | 460302 | 0.120322 | 2(Loss) |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 26523.4 | 0.237936 | 2954.87ms | 642697 | 4890 | 1.47837e+07 | 23108.8 | 0.0932337 | 1(Win) |
| simdjson (ondemand) | 19571.8 | 0.180836 | 3765.13ms | 642697 | 4890 | 1.56829e+07 | 31316.6 | 0.126389 | 2(Loss) |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 25689.8 | 0.163632 | 5174.32ms | 1225964 | 4890 | 2.71193e+07 | 45511.1 | 0.0963156 | 1(Win) |
| simdjson (ondemand) | 20397.2 | 0.106822 | 6355.39ms | 1225964 | 4890 | 1.83336e+07 | 57320.2 | 0.121316 | 2(Loss) |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 23749.4 | 0.0511854 | 2314.58ms | 409725 | 30 | 2127.61 | 16452.8 | 0.104008 | 1(Win) |
| simdjson (ondemand) | 17778.1 | 0.258634 | 2816.68ms | 409725 | 4890 | 1.58013e+07 | 21978.9 | 0.139088 | 2(Loss) |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22193.6 | 0.16382 | 4044.97ms | 785750 | 4890 | 1.49609e+07 | 33764.3 | 0.111466 | 1(Win) |
| simdjson (ondemand) | 20342.7 | 0.159217 | 4355.28ms | 785750 | 4890 | 1.68205e+07 | 36836.3 | 0.121607 | 2(Loss) |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 23877.2 | 0.826429 | 1691.42ms | 264040 | 4890 | 3.71442e+07 | 10546 | 0.103435 | 1(Win) |
| simdjson (ondemand) | 21301.2 | 0.227863 | 1832.65ms | 264040 | 320 | 232182 | 11821.3 | 0.115971 | 2(Loss) |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 22665.9 | 0.414027 | 2300.51ms | 399947 | 2560 | 1.24267e+07 | 16827.9 | 0.109062 | 1(Win) |
| simdjson (ondemand) | 19377.7 | 0.339806 | 2576.69ms | 399947 | 2560 | 1.14525e+07 | 19683.4 | 0.127596 | 2(Loss) |
