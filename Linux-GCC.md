# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the GCC 16.1.0 compiler).  

Latest Results: (Sep 19, 2026)
#### Using the following commits:
----
| Jsonifier: [3240669](https://github.com/nihilai-collective/jsonifier/commit/3240669)  
| Glaze: [a5fcd46](https://github.com/stephenberry/glaze/commit/a5fcd46)  
| Simdjson: [a683f0a](https://github.com/simdjson/simdjson/commit/a683f0a)  

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

> Adaptive sampling on (Intel(R) Core(TM) i9-14900KF-AVX2): iterations begin at 100 and double each epoch (e.g. 100 → 200 → 400 → ...) up to a maximum of 100000 iterations. Each epoch runs all iterations and evaluates a trailing window of max(iterations/10, 30) samples, capped at 100000. Convergence requires RSE < 5.000000% AND mean shift < 2.500000% epoch-over-epoch simultaneously. The first epoch satisfying both conditions is retained as the canonical result. If convergence is never reached before 20 seconds elapse or the iteration cap is hit, the result is marked non-converged and excluded from all rankings — only converged results participate in win/tie/loss tallying. All results use Bessel-corrected variance and Welch's t-test for statistical tie detection.

##### (All of the libraries are performing UTF8-validation in these tests. Jsonifier is only performing "structural indexing/stage-1 + stage-2" parsing for the 'partial' tests here, for the rest of them - we perform scalar structural iteration)

#### Note:
  This is the commit of BenchmarkSuite that was used to generate these results: [4972187](https://github.com/realtimechris/benchmarksuite/commit/4972187).
  
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1227.94 | 0.325185 | 1.48954ms | 1811 | 30 | 627.569 | 1406.5 | 2.43004 | 1(Win) |
| glaze | 1085.09 | 0.232289 | 1.2901ms | 1811 | 30 | 410.092 | 1591.67 | 2.75719 | 2(Loss) |
| simdjson (ondemand) | 240.205 | 2.38924 | 7.36579ms | 1811 | 40 | 1.18046e+06 | 7190.12 | 12.6062 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 803.815 | 0.151256 | 1.48968ms | 1811 | 30 | 316.861 | 2148.63 | 3.72507 | 1(Win) |
| glaze | 604.65 | 0.93061 | 1.65826ms | 1798 | 30 | 20894.3 | 2835.87 | 4.96937 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2102.97 | 0.110769 | 1.33872ms | 3873 | 30 | 113.551 | 1756.37 | 1.42415 | 1(Win) |
| glaze | 1997.93 | 0.0974261 | 1.37634ms | 3873 | 30 | 97.3207 | 1848.7 | 1.49991 | 2(Loss) |
| simdjson (ondemand) | 441.443 | 0.353148 | 3.42224ms | 3873 | 30 | 26192.7 | 8367.07 | 6.86752 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5664.71 | 0.399084 | 1.01697ms | 3873 | 30 | 203.137 | 652.033 | 0.515741 | 1(Win) |
| glaze | 3015.41 | 0.25633 | 1.22831ms | 3873 | 30 | 295.748 | 1224.9 | 0.989087 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2160.82 | 0.143761 | 6.44209ms | 3862 | 80 | 480.354 | 1704.49 | 1.38501 | 1(Win) |
| glaze | 1822.17 | 0.121879 | 1.43952ms | 3862 | 30 | 182.064 | 2021.27 | 1.64447 | 2(Loss) |
| simdjson (ondemand) | 449.609 | 0.505778 | 33.4409ms | 3862 | 160 | 274660 | 8191.76 | 6.73647 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5446.21 | 0.413706 | 1.04243ms | 3862 | 30 | 234.823 | 676.267 | 0.533687 | 1(Win) |
| glaze | 2908.93 | 0.349739 | 1.20629ms | 3862 | 30 | 588.257 | 1266.13 | 1.02025 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2725.86 | 0.334565 | 9.3085ms | 905 | 160 | 179.544 | 316.625 | 1.03909 | 1(Win) |
| glaze | 852.111 | 0.102158 | 1.1239ms | 905 | 30 | 32.1195 | 1012.87 | 3.4389 | 2(Loss) |
| simdjson (ondemand) | 193.327 | 0.148685 | 2.16848ms | 905 | 30 | 1321.82 | 4464.33 | 15.6392 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3166.09 | 0.657769 | 1.99335ms | 905 | 40 | 128.605 | 272.6 | 0.88989 | 1(Win) |
| glaze | 899.349 | 0.202472 | 1.12667ms | 905 | 30 | 113.264 | 959.667 | 3.24884 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3358.77 | 0.133138 | 1.68965ms | 9578 | 30 | 393.292 | 2719.53 | 0.89399 | 1(Win) |
| glaze | 3237.7 | 0.787126 | 35.7575ms | 9578 | 320 | 157803 | 2821.23 | 0.928258 | 2(Loss) |
| simdjson (ondemand) | 1249.84 | 3.87938 | 985.389ms | 9578 | 4890 | 3.93074e+08 | 7308.36 | 2.42356 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7384.23 | 0.363582 | 1.22028ms | 9578 | 30 | 606.828 | 1237 | 0.402276 | 1(Win) |
| glaze | 5432.23 | 0.251986 | 1.3494ms | 9578 | 30 | 538.603 | 1681.5 | 0.547031 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 783.737 | 1.29301 | 759.276ms | 2090234 | 30 | 3.2447e+10 | 2.54346e+06 | 3.87708 | 1(Win) |
| simdjson (ondemand) | 741.405 | 0.262787 | 813.739ms | 2090234 | 30 | 1.49764e+09 | 2.68868e+06 | 4.09832 | 2(Loss) |
| glaze | 689.972 | 0.542241 | 869.354ms | 2090234 | 30 | 7.36262e+09 | 2.88911e+06 | 4.4041 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1767.69 | 0.299733 | 340.986ms | 2090234 | 30 | 3.4274e+08 | 1.12768e+06 | 1.71889 | 1(Win) |
| glaze | 1399.65 | 0.386848 | 2160.26ms | 2090234 | 80 | 2.42842e+09 | 1.42422e+06 | 2.17065 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2180.04 | 0.227766 | 899.263ms | 6661897 | 30 | 1.32181e+09 | 2.9143e+06 | 1.39362 | 1(Win) |
| jsonifier | 1931.58 | 0.197796 | 1000.53ms | 6661897 | 30 | 1.26977e+09 | 3.28917e+06 | 1.57308 | 2(Loss) |
| glaze | 1656.12 | 1.03066 | 5625.76ms | 6661897 | 80 | 1.25064e+11 | 3.83625e+06 | 1.83425 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4300.21 | 0.477035 | 449.175ms | 6661897 | 30 | 1.49018e+09 | 1.47744e+06 | 0.706362 | 1(Win) |
| glaze | 3090.14 | 0.732213 | 1483.44ms | 6661897 | 40 | 9.06517e+09 | 2.05599e+06 | 0.983174 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 1758.27 | 0.905094 | 82.1144ms | 500299 | 30 | 1.80966e+08 | 271359 | 1.72814 | 1(Tie) |
| jsonifier STATISTICAL TIE | 1743.6 | 0.714076 | 197.825ms | 500299 | 40 | 1.52727e+08 | 273643 | 1.74259 | 1(Tie) |
| simdjson (ondemand) | 1081 | 0.975917 | 307.783ms | 500299 | 40 | 7.42153e+08 | 441371 | 2.81051 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6574.1 | 0.409836 | 23.6686ms | 500299 | 30 | 2.65416e+06 | 72576 | 0.462063 | 1(Win) |
| glaze | 5727.26 | 1.12631 | 132.23ms | 500299 | 80 | 7.04323e+07 | 83307.3 | 0.53033 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2788.88 | 0.830508 | 745.572ms | 1439562 | 80 | 1.33715e+09 | 492267 | 1.08939 | 1(Win) |
| glaze STATISTICAL TIE | 2642.7 | 2.3482 | 153.516ms | 1439562 | 30 | 4.46432e+09 | 519496 | 1.14964 | 2(Tie) |
| jsonifier STATISTICAL TIE | 2559.17 | 0.863793 | 162.47ms | 1439562 | 30 | 6.44175e+08 | 536453 | 1.18725 | 2(Tie) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10591.8 | 0.857206 | 40.9132ms | 1439562 | 30 | 3.70349e+07 | 129616 | 0.286639 | 1(Win) |
| glaze | 6387.89 | 0.709986 | 335.652ms | 1439584 | 80 | 1.86272e+08 | 214921 | 0.475382 | 2(Loss) |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1863.01 | 1.27321 | 9.71349ms | 56369 | 30 | 4.04922e+06 | 28855.3 | 1.62966 | 1(Win) |
| jsonifier | 1769.54 | 0.319429 | 10.3343ms | 56369 | 30 | 282509 | 30379.5 | 1.71601 | 2(Loss) |
| simdjson (ondemand) | 1269.71 | 1.52898 | 14.2097ms | 56369 | 30 | 1.25718e+07 | 42338.5 | 2.39156 | 3(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 6382.76 | 0.369255 | 8.06487ms | 56369 | 40 | 38688 | 8422.33 | 0.474457 | 1(Win) |
| jsonifier | 5912.97 | 0.291826 | 18.5778ms | 56369 | 80 | 56312.7 | 9091.49 | 0.511894 | 2(Loss) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2296.51 | 0.851695 | 1070.24ms | 94370 | 1280 | 1.42597e+08 | 39189.1 | 1.32222 | 1(Win) |
| simdjson (ondemand) | 2063.29 | 0.792944 | 13.8962ms | 94370 | 30 | 3.58882e+06 | 43618.7 | 1.47177 | 2(Loss) |
| jsonifier | 1809.2 | 4.85793 | 34.4564ms | 94370 | 40 | 2.33592e+08 | 49744.8 | 1.67788 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8477.6 | 0.436154 | 4.1184ms | 94370 | 30 | 64316.5 | 10616 | 0.357081 | 1(Win) |
| glaze | 6144.47 | 0.793166 | 113.156ms | 94370 | 320 | 4.31895e+06 | 14647 | 0.493492 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1425.98 | 1.09465 | 32.9554ms | 11812 | 160 | 1.19644e+06 | 7899.68 | 2.12373 | 1(Win) |
| jsonifier | 1285.12 | 0.808898 | 3.65313ms | 11812 | 30 | 150824 | 8765.57 | 2.35776 | 2(Loss) |
| simdjson (ondemand) | 1039.46 | 2.81301 | 4.14107ms | 11812 | 30 | 2.78803e+06 | 10837.2 | 2.91579 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5029.98 | 1.30312 | 1.54934ms | 11812 | 30 | 25550.7 | 2239.53 | 0.597079 | 1(Win) |
| glaze | 4022.28 | 1.45052 | 1.88004ms | 11812 | 30 | 49507.5 | 2800.6 | 0.74847 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2470.85 | 1.65169 | 4.49161ms | 31235 | 30 | 1.18952e+06 | 12055.8 | 1.227 | 1(Win) |
| jsonifier STATISTICAL TIE | 2295.44 | 0.760969 | 5.07542ms | 31235 | 30 | 292556 | 12977.1 | 1.32131 | 2(Tie) |
| glaze STATISTICAL TIE | 2283.12 | 0.819455 | 4.86194ms | 31235 | 30 | 342923 | 13047.1 | 1.32839 | 2(Tie) |

----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7897.95 | 0.644827 | 9.8569ms | 31235 | 80 | 47318.5 | 3771.61 | 0.381809 | 1(Win) |
| glaze | 6333.47 | 0.76876 | 2.31434ms | 31235 | 30 | 39219.5 | 4703.27 | 0.477115 | 2(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3359.49 | 0.495426 | 10.521ms | 108313 | 30 | 696135 | 30747.3 | 0.903671 | 1(Win) |
| glaze | 2109.71 | 0.899841 | 15.5252ms | 108313 | 30 | 5.82331e+06 | 48961.9 | 1.4396 | 2(Loss) |
| simdjson (ondemand) | 1655.83 | 0.540801 | 46.7055ms | 108313 | 40 | 4.55264e+06 | 62382.7 | 1.83447 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6560.65 | 0.503661 | 27.9985ms | 108313 | 80 | 503077 | 15744.7 | 0.462451 | 1(Win) |
| glaze | 5929.94 | 0.462003 | 14.6873ms | 108313 | 40 | 259066 | 17419.3 | 0.511576 | 2(Loss) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) STATISTICAL TIE | 2926.19 | 0.926349 | 109.7ms | 213963 | 80 | 3.3382e+07 | 69732.7 | 1.03801 | 1(Tie) |
| jsonifier STATISTICAL TIE | 2888.45 | 0.728231 | 23.1788ms | 213963 | 30 | 7.93974e+06 | 70643.7 | 1.05174 | 1(Tie) |
| glaze | 2573.04 | 3.97975 | 24.7007ms | 213963 | 30 | 2.98824e+08 | 79303.4 | 1.18034 | 3(Loss) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 10470 | 0.919569 | 16.1126ms | 213963 | 40 | 1.28474e+06 | 19489.2 | 0.289763 | 1(Win) |
| glaze | 5902.93 | 1.3322 | 56.1909ms | 213963 | 80 | 1.69657e+07 | 34567.8 | 0.514314 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 712.949 | 0.524885 | 734.768ms | 1834197 | 30 | 4.97537e+09 | 2.45351e+06 | 4.26212 | 1(Win) |
| glaze | 598.565 | 0.400467 | 880.363ms | 1834197 | 30 | 4.10889e+09 | 2.92237e+06 | 5.07643 | 2(Loss) |
| simdjson (ondemand) | 158.533 | 0.29028 | 3336.38ms | 1834197 | 30 | 3.07757e+10 | 1.10338e+07 | 19.1693 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1070.23 | 0.288347 | 490.213ms | 1834197 | 30 | 6.66328e+08 | 1.63444e+06 | 2.83913 | 1(Win) |
| glaze | 953.056 | 0.815358 | 568.165ms | 1833577 | 30 | 6.71398e+09 | 1.83477e+06 | 3.18812 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2669.44 | 0.549292 | 1073.17ms | 9930848 | 30 | 1.13936e+10 | 3.54786e+06 | 1.13824 | 1(Win) |
| glaze | 2378.03 | 0.284136 | 1200.85ms | 9930848 | 30 | 3.84159e+09 | 3.98262e+06 | 1.27766 | 2(Loss) |
| simdjson (ondemand) | 736.416 | 0.849757 | 3834.31ms | 9930848 | 30 | 3.58292e+11 | 1.28607e+07 | 4.12649 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4118.05 | 0.405502 | 1610.17ms | 9930848 | 40 | 3.47885e+09 | 2.29983e+06 | 0.737857 | 1(Win) |
| glaze | 3468.33 | 0.505314 | 828.446ms | 9930228 | 30 | 5.71113e+09 | 2.73048e+06 | 0.876078 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 725.014 | 0.647755 | 722.272ms | 1834197 | 30 | 7.32726e+09 | 2.41268e+06 | 4.19109 | 1(Win) |
| glaze STATISTICAL TIE | 589.438 | 0.642943 | 884.965ms | 1834197 | 30 | 1.09215e+10 | 2.96762e+06 | 5.15509 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 586.599 | 0.461159 | 921.613ms | 1834197 | 30 | 5.67325e+09 | 2.98198e+06 | 5.18002 | 2(Tie) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1071.16 | 0.200004 | 501.833ms | 1834197 | 30 | 3.20023e+08 | 1.63302e+06 | 2.83684 | 1(Win) |
| glaze | 925.62 | 0.639744 | 572.763ms | 1833577 | 30 | 4.38194e+09 | 1.88915e+06 | 3.28261 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2717.59 | 0.28114 | 1083.67ms | 9930848 | 30 | 2.87985e+09 | 3.48499e+06 | 1.11809 | 1(Win) |
| jsonifier | 2596.87 | 0.36247 | 1073.87ms | 9930848 | 30 | 5.24247e+09 | 3.647e+06 | 1.16989 | 2(Loss) |
| glaze | 2376.75 | 0.368025 | 1201.85ms | 9930848 | 30 | 6.45182e+09 | 3.98477e+06 | 1.27853 | 3(Loss) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4138.69 | 0.801883 | 690.974ms | 9930848 | 30 | 1.01016e+10 | 2.28836e+06 | 0.734203 | 1(Win) |
| glaze | 2668.48 | 0.866734 | 1065.68ms | 9930228 | 30 | 2.83847e+10 | 3.54891e+06 | 1.1385 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1184.53 | 0.67555 | 158.18ms | 642697 | 30 | 3.6657e+08 | 517441 | 2.56485 | 1(Win) |
| jsonifier | 1096.92 | 1.47933 | 169.093ms | 642697 | 30 | 2.04979e+09 | 558766 | 2.77007 | 2(Loss) |
| glaze | 1044.03 | 0.492712 | 177.532ms | 642697 | 30 | 2.51013e+08 | 587077 | 2.91014 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1859.99 | 0.676201 | 100.684ms | 642697 | 30 | 1.48959e+08 | 329531 | 1.63349 | 1(Win) |
| glaze | 1557.76 | 0.68239 | 120.596ms | 642692 | 30 | 2.16269e+08 | 393463 | 1.95042 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2164.81 | 0.964183 | 162.981ms | 1225964 | 30 | 8.13494e+08 | 540079 | 1.40346 | 1(Win) |
| glaze | 1740.1 | 0.3824 | 203.488ms | 1225964 | 30 | 1.98046e+08 | 671900 | 1.74629 | 2(Loss) |
| jsonifier | 1559.79 | 0.377369 | 228.148ms | 1225964 | 30 | 2.40036e+08 | 749570 | 1.94804 | 3(Loss) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3029 | 0.53786 | 583.6ms | 1225964 | 80 | 3.44814e+08 | 385992 | 1.003 | 1(Win) |
| glaze | 2551.23 | 1.17271 | 137.188ms | 1225970 | 30 | 8.66489e+08 | 458280 | 1.19073 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1013.94 | 1.50822 | 116.049ms | 409725 | 30 | 1.01348e+09 | 385373 | 2.99653 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 952.71 | 0.608463 | 125.842ms | 409725 | 30 | 1.86833e+08 | 410140 | 3.18923 | 2(Tie) |
| glaze STATISTICAL TIE | 943.653 | 0.712944 | 128.228ms | 409725 | 30 | 2.61453e+08 | 414076 | 3.21975 | 2(Tie) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5315.36 | 1.59683 | 22.5432ms | 409725 | 30 | 4.13386e+07 | 73512.2 | 0.571405 | 1(Win) |
| glaze | 3612.69 | 2.71658 | 32.8672ms | 409725 | 30 | 2.58995e+08 | 108159 | 0.840614 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 1710.64 | 0.808988 | 133.579ms | 785750 | 30 | 3.76754e+08 | 438052 | 1.77605 | 1(Win) |
| glaze | 1453.47 | 0.626194 | 363.99ms | 785750 | 40 | 4.169e+08 | 515558 | 2.09031 | 2(Loss) |
| jsonifier | 1372.46 | 2.02682 | 163.913ms | 785750 | 30 | 3.67385e+09 | 545989 | 2.21383 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6536.58 | 3.11301 | 33.9358ms | 785750 | 30 | 3.82075e+08 | 114639 | 0.464631 | 1(Win) |
| glaze | 4384.7 | 1.37924 | 123.873ms | 785750 | 40 | 2.22243e+08 | 170901 | 0.692763 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5556.51 | 0.978296 | 14.5695ms | 264040 | 30 | 5.89655e+06 | 45317.7 | 0.54664 | 1(Win) |
| simdjson (ondemand) | 4718.22 | 2.80456 | 39.0314ms | 264040 | 40 | 8.96135e+07 | 53369.3 | 0.643523 | 2(Loss) |
| glaze | 3129.61 | 0.378755 | 25.3452ms | 264040 | 30 | 2.78609e+06 | 80459.8 | 0.970768 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7203.52 | 0.581727 | 17.1611ms | 399947 | 30 | 2.84626e+06 | 52949 | 0.421676 | 1(Win) |
| simdjson (ondemand) | 6657.72 | 0.649913 | 18.8386ms | 399947 | 30 | 4.15896e+06 | 57289.7 | 0.456235 | 2(Loss) |
| glaze | 3716.22 | 0.78162 | 330.144ms | 399947 | 160 | 1.02971e+08 | 102636 | 0.817461 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1925.5 | 1.36341 | 199.266ms | 264040 | 80 | 2.54328e+08 | 130776 | 1.5778 | 1(Win) |
| glaze | 1614.7 | 0.401224 | 3982.38ms | 264040 | 1280 | 5.01119e+08 | 155948 | 1.88136 | 2(Loss) |
| simdjson (ondemand) | 1525.62 | 1.69076 | 50.5909ms | 264040 | 30 | 2.33632e+08 | 165053 | 1.99132 | 3(Loss) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6926.05 | 0.998379 | 27.1559ms | 264040 | 40 | 5.2701e+06 | 36356.7 | 0.438336 | 1(Win) |
| glaze | 6025.89 | 1.89619 | 68.5186ms | 263923 | 80 | 5.0184e+07 | 41769.2 | 0.503898 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| simdjson (ondemand) | 2184.76 | 0.889239 | 543.371ms | 399947 | 160 | 3.85615e+08 | 174581 | 1.39049 | 1(Win) |
| glaze | 1956.26 | 0.8143 | 145.528ms | 399947 | 40 | 1.00827e+08 | 194973 | 1.55319 | 2(Loss) |
| jsonifier | 1811.07 | 0.572979 | 696.961ms | 399947 | 160 | 2.32988e+08 | 210605 | 1.67776 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8505.32 | 2.379 | 35.9091ms | 399947 | 40 | 4.55274e+07 | 44844.8 | 0.356961 | 1(Win) |
| glaze | 5318.86 | 1.7186 | 232.123ms | 399830 | 160 | 2.42874e+08 | 71689.7 | 0.570971 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2361.17 | 0.332719 | 290.432ms | 466906 | 80 | 3.14957e+07 | 188583 | 1.2869 | 1(Win) |
| jsonifier | 2196.9 | 1.24794 | 61.5786ms | 466906 | 30 | 1.91931e+08 | 202684 | 1.38279 | 2(Loss) |
| simdjson (ondemand) | 1284.31 | 1.14634 | 107.563ms | 466906 | 30 | 4.73883e+08 | 346706 | 2.36558 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3644.63 | 0.65258 | 1186.07ms | 699405 | 320 | 4.56423e+08 | 183010 | 0.833525 | 1(Win) |
| glaze | 3288.96 | 0.514994 | 63.4898ms | 699405 | 30 | 3.27239e+07 | 202801 | 0.923891 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3320.07 | 1.79431 | 279.154ms | 631514 | 80 | 8.47536e+08 | 181399 | 0.915025 | 1(Win) |
| glaze | 2361.34 | 0.898856 | 79.1522ms | 631514 | 30 | 1.57671e+08 | 255050 | 1.28682 | 2(Loss) |
