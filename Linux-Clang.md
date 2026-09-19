# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 6.18.40.1-microsoft-standard-WSL2 using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1364.11 | 0.115818 | 1.50221ms | 1811 | 30 | 64.5069 | 1266.1 | 2.17775 | 1(Win) |
| glaze | 1094.91 | 0.0994832 | 14.0602ms | 1811 | 160 | 394 | 1577.39 | 2.72823 | 2(Loss) |
| simdjson (ondemand) | 262.007 | 0.539575 | 2.83954ms | 1811 | 30 | 37952.2 | 6591.83 | 11.5564 | 3(Loss) |

----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 801.417 | 0.29805 | 7.43063ms | 1811 | 80 | 3300.57 | 2155.06 | 3.74119 | 1(Win) |
| glaze | 672.717 | 1.07871 | 3.57995ms | 1798 | 40 | 30240.1 | 2548.93 | 4.45542 | 2(Loss) |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2248.89 | 0.0893416 | 1.30401ms | 3873 | 30 | 64.5931 | 1642.4 | 1.3305 | 1(Win) |
| glaze | 2100.22 | 0.0621889 | 1.33836ms | 3873 | 30 | 35.8851 | 1758.67 | 1.42742 | 2(Loss) |
| simdjson (ondemand) | 503.904 | 2.36716 | 3.02467ms | 3873 | 30 | 903182 | 7329.93 | 6.01342 | 3(Loss) |

----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5683.96 | 0.477445 | 5.31016ms | 3873 | 80 | 770.07 | 649.825 | 0.510357 | 1(Win) |
| glaze | 2838.45 | 0.230484 | 12.3242ms | 3873 | 160 | 1439.24 | 1301.27 | 1.05036 | 2(Loss) |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2377.06 | 0.159016 | 1.33098ms | 3862 | 30 | 182.116 | 1549.43 | 1.25634 | 1(Win) |
| glaze | 1898.33 | 0.275712 | 14.8016ms | 3862 | 160 | 4578.41 | 1940.17 | 1.57884 | 2(Loss) |
| simdjson (ondemand) | 506.493 | 0.109919 | 7.05992ms | 3862 | 40 | 2555.53 | 7271.75 | 5.97341 | 3(Loss) |

----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5817.86 | 0.546771 | 1.04468ms | 3862 | 30 | 359.444 | 633.067 | 0.501105 | 1(Win) |
| glaze | 2507.42 | 0.223086 | 27.2669ms | 3862 | 320 | 3436.1 | 1468.88 | 1.18756 | 2(Loss) |

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3172.68 | 0.359261 | 0.925942ms | 905 | 30 | 28.654 | 272.033 | 0.889355 | 1(Win) |
| glaze | 2476.01 | 0.783415 | 4.42511ms | 905 | 80 | 596.577 | 348.575 | 1.15794 | 2(Loss) |
| simdjson (ondemand) | 228.429 | 0.166038 | 20.4174ms | 905 | 160 | 6296.96 | 3778.31 | 13.2219 | 3(Loss) |

----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3571.96 | 1.35652 | 2.17462ms | 905 | 40 | 429.728 | 241.625 | 0.785994 | 1(Win) |
| glaze | 1005.02 | 2.543 | 1.04815ms | 905 | 30 | 14307.6 | 858.767 | 2.96088 | 2(Loss) |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3956.98 | 0.179452 | 1.56136ms | 9578 | 30 | 514.8 | 2308.4 | 0.757792 | 1(Win) |
| glaze | 3510.67 | 0.486249 | 1.60481ms | 9578 | 30 | 4801.84 | 2601.87 | 0.855189 | 2(Loss) |
| simdjson (ondemand) | 1568.83 | 0.2709 | 2.63057ms | 9578 | 30 | 7463.41 | 5822.37 | 1.93041 | 3(Loss) |

----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6056.15 | 0.318318 | 1.3235ms | 9578 | 30 | 691.513 | 1508.27 | 0.492163 | 1(Win) |
| glaze | 4750.21 | 0.172773 | 6.9704ms | 9578 | 80 | 883.007 | 1922.92 | 0.629266 | 2(Loss) |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 847.063 | 0.338493 | 716.011ms | 2090234 | 30 | 1.90361e+09 | 2.35331e+06 | 3.58731 | 1(Win) |
| glaze | 776.898 | 0.566127 | 772.097ms | 2090234 | 30 | 6.33011e+09 | 2.56585e+06 | 3.91128 | 2(Loss) |
| simdjson (ondemand) | 577.876 | 0.788843 | 1025.59ms | 2090234 | 30 | 2.22138e+10 | 3.44953e+06 | 5.25852 | 3(Loss) |

----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1679.42 | 0.91526 | 357.437ms | 2090234 | 30 | 3.54066e+09 | 1.18696e+06 | 1.80918 | 1(Win) |
| glaze | 936.649 | 0.659062 | 634.811ms | 2090234 | 30 | 5.90215e+09 | 2.12823e+06 | 3.24382 | 2(Loss) |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2142.84 | 0.733692 | 896.375ms | 6661897 | 30 | 1.41959e+10 | 2.96488e+06 | 1.41802 | 1(Win) |
| glaze | 1925.33 | 0.337993 | 988.042ms | 6661897 | 30 | 3.73185e+09 | 3.29984e+06 | 1.57821 | 2(Loss) |
| simdjson (ondemand) | 1743.33 | 0.824135 | 1126.85ms | 6661897 | 30 | 2.70618e+10 | 3.64435e+06 | 1.743 | 3(Loss) |

----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3898.81 | 0.78579 | 491.597ms | 6661897 | 30 | 4.91889e+09 | 1.62954e+06 | 0.779251 | 1(Win) |
| glaze | 3062.82 | 0.522641 | 626.599ms | 6661897 | 30 | 3.52598e+09 | 2.07432e+06 | 0.991906 | 2(Loss) |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1813.36 | 0.490659 | 188.576ms | 500299 | 40 | 6.66668e+07 | 263114 | 1.67569 | 1(Win) |
| glaze | 1748.06 | 0.807547 | 848.715ms | 500299 | 160 | 7.77328e+08 | 272944 | 1.73806 | 2(Loss) |
| simdjson (ondemand) | 940.499 | 1.56701 | 148.873ms | 500299 | 30 | 1.89587e+09 | 507308 | 3.23027 | 3(Loss) |

----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6171.64 | 1.26076 | 24.2119ms | 500299 | 30 | 2.85001e+07 | 77308.9 | 0.492183 | 1(Win) |
| glaze | 5486.82 | 2.06893 | 61.5809ms | 500299 | 40 | 1.2947e+08 | 86957.9 | 0.553393 | 2(Loss) |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3443.78 | 1.61742 | 119.7ms | 1439562 | 30 | 1.24726e+09 | 398653 | 0.882295 | 1(Win) |
| glaze | 2802.56 | 0.572767 | 149.621ms | 1439562 | 30 | 2.36172e+08 | 489863 | 1.08418 | 2(Loss) |
| simdjson (ondemand) | 2492.06 | 1.03554 | 166.976ms | 1439562 | 30 | 9.76345e+08 | 550899 | 1.21916 | 3(Loss) |

----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9954.55 | 2.60652 | 42.3689ms | 1439562 | 30 | 3.8767e+08 | 137914 | 0.304917 | 1(Win) |
| glaze | 5628.01 | 0.610475 | 802.371ms | 1439584 | 160 | 3.5483e+08 | 243940 | 0.539667 | 2(Loss) |

----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 5787.58 | 1.08814 | 37.1287ms | 56369 | 160 | 1.63446e+06 | 9288.45 | 0.523439 | 1(Tie) |
| jsonifier STATISTICAL TIE | 5772.64 | 0.966361 | 3.69751ms | 56369 | 30 | 242959 | 9312.5 | 0.524755 | 1(Tie) |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2466.54 | 0.696954 | 28.6253ms | 94370 | 40 | 2.58677e+06 | 36487.6 | 1.23123 | 1(Win) |
| jsonifier | 2252.09 | 1.237 | 14.5605ms | 94370 | 30 | 7.3309e+06 | 39962 | 1.34846 | 2(Loss) |
| simdjson (ondemand) | 1981.71 | 0.773216 | 34.9082ms | 94370 | 40 | 4.9323e+06 | 45414.4 | 1.53261 | 3(Loss) |

----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 8494.25 | 1.39295 | 9.62205ms | 94370 | 40 | 871259 | 10595.2 | 0.356547 | 1(Win) |
| glaze | 5200.13 | 1.38481 | 6.15777ms | 94370 | 30 | 1.72323e+06 | 17306.9 | 0.583239 | 2(Loss) |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 1385.29 | 0.179887 | 3.34636ms | 11812 | 30 | 6419.31 | 8131.73 | 2.18706 | 1(Win) |
| jsonifier | 1206.17 | 4.46523 | 316.724ms | 11812 | 1280 | 2.22602e+08 | 9339.33 | 2.51076 | 2(Loss) |
| simdjson (ondemand) | 1054.05 | 0.108968 | 4.11059ms | 11812 | 30 | 4068.56 | 10687.2 | 2.87678 | 3(Loss) |

----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4923.28 | 1.28315 | 1.57218ms | 11812 | 30 | 25859.2 | 2288.07 | 0.609956 | 1(Win) |
| glaze | 3803.54 | 1.40652 | 18.775ms | 11812 | 160 | 277642 | 2961.66 | 0.791564 | 2(Loss) |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2578.86 | 1.02473 | 22.453ms | 31235 | 80 | 1.12082e+06 | 11550.9 | 1.17578 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2564.26 | 0.511317 | 10.2299ms | 31235 | 40 | 141124 | 11616.6 | 1.18264 | 1(Tie) |
| glaze | 2353.22 | 0.113566 | 4.75044ms | 31235 | 30 | 6199.77 | 12658.4 | 1.289 | 3(Loss) |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3154 | 2.27321 | 53.2052ms | 108313 | 80 | 4.4341e+07 | 32750.6 | 0.962512 | 1(Win) |
| glaze | 2273.11 | 1.60697 | 14.4358ms | 108313 | 30 | 1.59976e+07 | 45442.3 | 1.33601 | 2(Loss) |
| simdjson (ondemand) | 1536.19 | 0.900271 | 109.02ms | 108313 | 80 | 2.93164e+07 | 67241.4 | 1.97751 | 3(Loss) |

----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze STATISTICAL TIE | 6426.93 | 0.722027 | 13.4889ms | 108313 | 40 | 538669 | 16072.3 | 0.47202 | 1(Tie) |
| jsonifier STATISTICAL TIE | 6186.48 | 2.53134 | 5.8273ms | 108313 | 30 | 5.35913e+06 | 16696.9 | 0.490253 | 1(Tie) |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3275 | 2.01752 | 19.3118ms | 213963 | 30 | 4.74035e+07 | 62305.7 | 0.927353 | 1(Win) |
| glaze STATISTICAL TIE | 2909.77 | 1.44064 | 22.1118ms | 213963 | 30 | 3.06193e+07 | 70126.2 | 1.04403 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2814.57 | 2.1011 | 22.9189ms | 213963 | 30 | 6.96099e+07 | 72498.2 | 1.07934 | 2(Tie) |

----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9812.42 | 0.765523 | 76.1615ms | 213963 | 160 | 4.05473e+06 | 20795.2 | 0.309283 | 1(Win) |
| glaze | 5705.34 | 1.39883 | 11.632ms | 213963 | 30 | 7.50869e+06 | 35764.9 | 0.532241 | 2(Loss) |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 783.935 | 0.385712 | 676.507ms | 1834197 | 30 | 2.22218e+09 | 2.23134e+06 | 3.87618 | 1(Win) |
| glaze | 672.863 | 0.420971 | 783.175ms | 1834197 | 30 | 3.59306e+09 | 2.59968e+06 | 4.51613 | 2(Loss) |
| simdjson (ondemand) | 184.304 | 0.374975 | 2871.84ms | 1834197 | 30 | 3.7997e+10 | 9.49099e+06 | 16.4882 | 3(Loss) |

----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1109.47 | 0.468001 | 477.336ms | 1834197 | 30 | 1.63334e+09 | 1.57664e+06 | 2.73878 | 1(Win) |
| glaze | 627.709 | 0.33599 | 847.223ms | 1833577 | 30 | 2.62819e+09 | 2.78574e+06 | 4.84117 | 2(Loss) |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

These tests parse keys in reverse order relative to their appearance in the JSON document.

This highlights a key limitation of simdjson's On Demand API and similar iterative forward-only parsers: because they lack hash-based key lookup, out-of-order access forces sequential rescans (or rewinds), degrading performance from O(N) to O(N^2) as document size grows.

In contrast, DOM- or hash-based parsers decouple access order from layout, maintaining consistent lookup time regardless of key ordering.

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2927.49 | 1.33442 | 964.658ms | 9930848 | 30 | 5.59097e+10 | 3.23513e+06 | 1.03795 | 1(Win) |
| glaze | 2577.2 | 0.583741 | 1100.48ms | 9930848 | 30 | 1.3805e+10 | 3.67484e+06 | 1.17907 | 2(Loss) |
| simdjson (ondemand) | 881.839 | 0.610453 | 3227.19ms | 9930848 | 30 | 1.2895e+11 | 1.07398e+07 | 3.44602 | 3(Loss) |

----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 3523.8 | 0.529141 | 4076.9ms | 9930228 | 80 | 1.61781e+10 | 2.6875e+06 | 0.862249 | 1(Win) |
| jsonifier | 3313.33 | 0.462958 | 866.064ms | 9930848 | 30 | 5.25348e+09 | 2.85839e+06 | 0.917123 | 2(Loss) |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 767.856 | 0.477847 | 3477.65ms | 1834197 | 80 | 9.47985e+09 | 2.27807e+06 | 3.95663 | 1(Win) |
| glaze | 667.944 | 0.575196 | 788.902ms | 1834197 | 30 | 6.80715e+09 | 2.61882e+06 | 4.5492 | 2(Loss) |
| simdjson (ondemand) | 540.715 | 0.427745 | 984.633ms | 1834197 | 30 | 5.74441e+09 | 3.23502e+06 | 5.61956 | 3(Loss) |

----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1096.77 | 0.756875 | 480.634ms | 1834197 | 30 | 4.37148e+09 | 1.59489e+06 | 2.77042 | 1(Win) |
| glaze | 599.919 | 0.0931847 | 37568.4ms | 1833577 | 640 | 4.72153e+09 | 2.91479e+06 | 5.06521 | 2(Loss) |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3035.95 | 0.352991 | 2195ms | 9930848 | 40 | 4.85034e+09 | 3.11955e+06 | 1.00087 | 1(Win) |
| glaze STATISTICAL TIE | 2576.02 | 0.999729 | 1088.42ms | 9930848 | 30 | 4.05284e+10 | 3.67652e+06 | 1.17949 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2563.21 | 0.267132 | 1116.5ms | 9930848 | 30 | 2.92266e+09 | 3.69489e+06 | 1.1855 | 2(Tie) |

----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3290.46 | 0.609276 | 871.507ms | 9930848 | 30 | 9.22593e+09 | 2.87826e+06 | 0.923513 | 1(Win) |
| glaze | 2897.63 | 0.862284 | 984.76ms | 9930228 | 30 | 2.38261e+10 | 3.26826e+06 | 1.04858 | 2(Loss) |

----
### Mesh Test (Minified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1493.39 | 0.424249 | 124.325ms | 642697 | 30 | 9.0956e+07 | 410425 | 2.03474 | 1(Win) |
| glaze | 1390.82 | 0.665902 | 133.521ms | 642697 | 30 | 2.58352e+08 | 440692 | 2.1848 | 2(Loss) |
| simdjson (ondemand) | 1059.09 | 0.652157 | 174.088ms | 642697 | 30 | 4.27341e+08 | 578728 | 2.86919 | 3(Loss) |

----
### Mesh Test (Minified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1956.89 | 0.652242 | 94.9469ms | 642697 | 30 | 1.25204e+08 | 313213 | 1.55277 | 1(Win) |
| glaze | 1562.7 | 0.59966 | 118.769ms | 642692 | 30 | 1.65954e+08 | 392218 | 1.94441 | 2(Loss) |

----
### Mesh Test (Prettified) Read Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| glaze | 2129.29 | 0.509081 | 164.834ms | 1225964 | 30 | 2.34411e+08 | 549088 | 1.42707 | 1(Win) |
| simdjson (ondemand) STATISTICAL TIE | 1977.58 | 0.542207 | 178.828ms | 1225964 | 30 | 3.08277e+08 | 591214 | 1.53655 | 2(Tie) |
| jsonifier STATISTICAL TIE | 1975.14 | 0.656551 | 178.843ms | 1225964 | 30 | 4.53125e+08 | 591944 | 1.53847 | 2(Tie) |

----
### Mesh Test (Prettified) Write Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2037.82 | 0.735773 | 172.121ms | 1225964 | 30 | 5.34604e+08 | 573735 | 1.49105 | 1(Win) |
| glaze | 1746.46 | 0.350849 | 202.382ms | 1225970 | 30 | 1.65503e+08 | 669456 | 1.73992 | 2(Loss) |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 1159.37 | 0.328948 | 102.369ms | 409725 | 30 | 3.68737e+07 | 337032 | 2.62103 | 1(Win) |
| glaze | 984.085 | 0.725957 | 119.091ms | 409725 | 30 | 2.49266e+08 | 397063 | 3.08778 | 2(Loss) |
| simdjson (ondemand) | 947.048 | 0.569783 | 124.832ms | 409725 | 30 | 1.65799e+08 | 412592 | 3.20848 | 3(Loss) |

----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 3845.89 | 0.839744 | 31.7043ms | 409725 | 30 | 2.18376e+07 | 101600 | 0.789933 | 1(Win) |
| glaze | 3335.04 | 0.955521 | 377.285ms | 409725 | 160 | 2.00532e+08 | 117163 | 0.910608 | 2(Loss) |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 1753.39 | 0.957896 | 128.949ms | 785750 | 30 | 5.02771e+08 | 427372 | 1.73286 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1722.7 | 0.536872 | 133.82ms | 785750 | 30 | 1.6361e+08 | 434984 | 1.76385 | 1(Tie) |
| glaze | 1489.43 | 0.827826 | 151.725ms | 785750 | 30 | 5.20388e+08 | 503111 | 2.03995 | 3(Loss) |

----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 5848.01 | 1.98665 | 39.1769ms | 785750 | 30 | 1.94409e+08 | 128138 | 0.519421 | 1(Win) |
| glaze | 4051.33 | 0.966714 | 57.0561ms | 785750 | 30 | 9.59161e+07 | 184964 | 0.749848 | 2(Loss) |

----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 6293.82 | 0.819132 | 13.0672ms | 264040 | 30 | 3.2221e+06 | 40008.8 | 0.482531 | 1(Win) |
| simdjson (ondemand) | 5687.76 | 0.748913 | 14.3732ms | 264040 | 30 | 3.29793e+06 | 44272 | 0.533987 | 2(Loss) |
| glaze | 3339.87 | 1.57528 | 23.0712ms | 264040 | 30 | 4.23174e+07 | 75394.6 | 0.909547 | 3(Loss) |

----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7643.78 | 0.458829 | 37.6112ms | 399947 | 40 | 2.09676e+06 | 49899.3 | 0.397381 | 1(Win) |
| simdjson (ondemand) | 7164.81 | 1.67491 | 16.8493ms | 399947 | 30 | 2.38507e+07 | 53235.1 | 0.423905 | 2(Loss) |
| glaze | 4345.64 | 0.549502 | 27.4175ms | 399947 | 30 | 6.97842e+06 | 87770.5 | 0.699094 | 3(Loss) |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2156.85 | 0.555838 | 181.859ms | 264040 | 80 | 3.36889e+07 | 116748 | 1.40868 | 1(Win) |
| glaze STATISTICAL TIE | 1692.55 | 2.01786 | 44.8382ms | 264040 | 30 | 2.7037e+08 | 148774 | 1.79497 | 2(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 1651.49 | 0.951703 | 47.3344ms | 264040 | 30 | 6.31702e+07 | 152473 | 1.83971 | 2(Tie) |

----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 7742.83 | 1.20949 | 10.8429ms | 264040 | 30 | 4.64162e+06 | 32521.5 | 0.3921 | 1(Win) |
| glaze | 6149.79 | 1.00504 | 68.5696ms | 263923 | 80 | 1.35361e+07 | 40927.7 | 0.493747 | 2(Loss) |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier STATISTICAL TIE | 2310.85 | 1.00006 | 51.4075ms | 399947 | 30 | 8.17396e+07 | 165056 | 1.31485 | 1(Tie) |
| simdjson (ondemand) STATISTICAL TIE | 2266.9 | 0.766844 | 50.0639ms | 399947 | 30 | 4.9943e+07 | 168256 | 1.34028 | 1(Tie) |
| glaze | 2125.38 | 0.727811 | 127.426ms | 399947 | 40 | 6.82384e+07 | 179459 | 1.42963 | 3(Loss) |

----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 9005.61 | 2.28274 | 66.7659ms | 399947 | 80 | 7.47795e+07 | 42353.5 | 0.337111 | 1(Win) |
| glaze | 4928.93 | 1.97295 | 24.6094ms | 399830 | 30 | 6.98876e+07 | 77361.2 | 0.616313 | 2(Loss) |

----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 2933.15 | 1.19073 | 46.2098ms | 466906 | 30 | 9.80251e+07 | 151808 | 1.03576 | 1(Win) |
| glaze | 2529.27 | 0.435379 | 53.3278ms | 466906 | 30 | 1.76248e+07 | 176049 | 1.20134 | 2(Loss) |
| simdjson (ondemand) | 1314.46 | 0.672269 | 242.662ms | 466906 | 40 | 2.07449e+08 | 338753 | 2.31127 | 3(Loss) |

----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4415.31 | 1.05652 | 47.7461ms | 699405 | 30 | 7.64201e+07 | 151066 | 0.688037 | 1(Win) |
| glaze | 3676.73 | 1.65387 | 56.7432ms | 699405 | 30 | 2.70057e+08 | 181412 | 0.826193 | 2(Loss) |

----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Cycles/Byte | Position |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ----------- | -------- |
| jsonifier | 4429.29 | 0.6169 | 437.666ms | 631514 | 160 | 1.12576e+08 | 135972 | 0.685908 | 1(Win) |
| glaze | 2446.49 | 0.939751 | 175.512ms | 631514 | 40 | 2.14075e+08 | 246173 | 1.24196 | 2(Loss) |
