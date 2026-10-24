# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1017-azure using the GCC 16.0.1 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier: [cb40a92](https://github.com/nihilai-collective/jsonifier/commit/cb40a92)  
| simdjson(On Demand): [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (AMD EPYC 7763 64-Core Processor-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 156.147 | 0.0750641 | 561.349ms | 905 | 30 | 516.437 | 5527.33 | 0.062077 | 14.8398 | 1(Win) | true |
| simdjson (ondemand) | 119.412 | 0.321723 | 729.925ms | 905 | 1280 | 692111 | 7227.71 | 0.17395 | 19.4309 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 321.601 | 0.0485865 | 554.103ms | 1811 | 40 | 272.328 | 5370.32 | 0.0200134 | 7.20453 | 1(Win) | true |
| simdjson (ondemand) | 230.352 | 0.184273 | 753.606ms | 1811 | 4890 | 933443 | 7497.68 | 0.147909 | 10.0742 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 648.094 | 0.175478 | 571.04ms | 3862 | 4890 | 486301 | 5682.96 | 0.120581 | 3.57583 | 1(Win) | true |
| simdjson (ondemand) | 486.647 | 0.0568041 | 773.716ms | 3862 | 40 | 739.292 | 7568.3 | 0.246036 | 4.76936 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1159.5 | 0.253673 | 792.529ms | 9578 | 2560 | 1.02235e+06 | 7877.8 | 0.0771798 | 2.00188 | 1(Win) | true |
| jsonifier | 1136.39 | 0.187231 | 808.005ms | 9578 | 2560 | 579819 | 8038.01 | 0.185147 | 2.0424 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 655.177 | 0.0464798 | 572.837ms | 3873 | 30 | 205.982 | 5637.53 | 0.0059131 | 3.53833 | 1(Win) | true |
| simdjson (ondemand) | 476.214 | 0.155711 | 781.502ms | 3873 | 4890 | 713246 | 7756.13 | 0.258919 | 4.87386 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5434.42 | 0.218071 | 9370.81ms | 2090234 | 80 | 5.11879e+07 | 366811 | 0.0504738 | 0.429078 | 1(Win) | true |
| simdjson (ondemand) | 4796.76 | 0.145728 | 5295.2ms | 2090234 | 160 | 5.86815e+07 | 415573 | 0.402513 | 0.486108 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 8513.13 | 0.0921189 | 9509.93ms | 6661897 | 160 | 7.56198e+07 | 746292 | 0.123519 | 0.273917 | 1(Win) | true |
| simdjson (ondemand) | 7629.18 | 0.174997 | 5230.68ms | 6661897 | 40 | 8.49496e+07 | 832761 | 0.030293 | 0.305629 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3887.01 | 0.134106 | 6255.14ms | 500299 | 2560 | 6.93685e+07 | 122748 | 0.443945 | 0.599709 | 1(Win) | true |
| simdjson (ondemand) | 3411.65 | 0.0855294 | 7185.98ms | 500299 | 2560 | 3.66271e+07 | 139851 | 0.0103995 | 0.683293 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6080.41 | 0.245736 | 5756.89ms | 1439562 | 160 | 4.92554e+07 | 225786 | 0.202545 | 0.38345 | 1(Win) | true |
| simdjson (ondemand) | 5926.02 | 0.128173 | 5906.27ms | 1439562 | 640 | 5.64296e+07 | 231669 | 0.0775211 | 0.393446 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4454.93 | 0.194757 | 1209.52ms | 56369 | 4890 | 2.70081e+06 | 12067 | 0.272989 | 0.521676 | 1(Win) | true |
| simdjson (ondemand) | 3928.48 | 0.188069 | 1372.8ms | 56369 | 2560 | 1.69553e+06 | 13684.1 | 0.0124017 | 0.592125 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5515.33 | 0.195954 | 1644.24ms | 94370 | 1280 | 1.30871e+06 | 16317.8 | 0.0193864 | 0.42189 | 1(Win) | true |
| simdjson (ondemand) | 5244.99 | 0.187251 | 1726.09ms | 94370 | 1280 | 1.32141e+06 | 17158.9 | 0.0970419 | 0.443571 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3983.94 | 0.0612947 | 289.836ms | 11812 | 80 | 240.301 | 2827.55 | 0.0274164 | 0.577964 | 1(Win) | true |
| simdjson (ondemand) | 3532.71 | 0.0688529 | 325.76ms | 11812 | 80 | 385.625 | 3188.71 | 0.0552426 | 0.652974 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6316.57 | 0.0644952 | 481.463ms | 31235 | 40 | 370.028 | 4715.85 | 0.0215539 | 0.366478 | 1(Win) | true |
| simdjson (ondemand) | 5955.64 | 0.0482254 | 509.568ms | 31235 | 80 | 465.446 | 5001.65 | 0.0850442 | 0.388826 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4244.51 | 0.119245 | 2438.67ms | 108313 | 4890 | 4.11812e+06 | 24336.2 | 0.176245 | 0.548608 | 1(Win) | true |
| simdjson (ondemand) | 3723.97 | 0.0922965 | 2782.82ms | 108313 | 4890 | 3.205e+06 | 27738 | 0.0186895 | 0.625427 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5807.81 | 0.103034 | 3524.76ms | 213963 | 4890 | 6.40803e+06 | 35133.9 | 0.250738 | 0.401124 | 1(Win) | true |
| simdjson (ondemand) | 5548.06 | 0.131055 | 3685.68ms | 213963 | 2560 | 5.94763e+06 | 36778.8 | 0.0257396 | 0.419922 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3148.26 | 0.182993 | 7202.06ms | 1834197 | 40 | 4.13503e+07 | 555616 | 0.126428 | 0.740683 | 1(Win) | true |
| simdjson (ondemand) | 2548.58 | 0.180425 | 8731.9ms | 1834197 | 30 | 4.60053e+07 | 686352 | 0.0352707 | 0.914974 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7104.29 | 0.0997754 | 8390.35ms | 9930848 | 160 | 2.83073e+08 | 1.33311e+06 | 0.0202315 | 0.328238 | 1(Win) | true |
| simdjson (ondemand) | 6868.83 | 0.0978878 | 8819.1ms | 9930848 | 30 | 5.46493e+07 | 1.37881e+06 | 0.844657 | 0.339502 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4423.92 | 0.126857 | 7067.17ms | 642697 | 1280 | 3.95399e+07 | 138548 | 0.0674964 | 0.526963 | 1(Win) | true |
| simdjson (ondemand) | 3422.25 | 0.0607506 | 9165.57ms | 642697 | 2560 | 3.03061e+07 | 179100 | 0.000773405 | 0.681218 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5937.82 | 0.116004 | 5028.78ms | 1225964 | 1280 | 6.67813e+07 | 196902 | 0.025757 | 0.39265 | 1(Win) | true |
| simdjson (ondemand) | 5396.66 | 0.236188 | 5530.12ms | 1225964 | 160 | 4.1893e+07 | 216647 | 0.161412 | 0.431821 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4732.85 | 0.0694759 | 8286.25ms | 409725 | 4890 | 1.60885e+07 | 82560 | 0.0528591 | 0.492463 | 1(Win) | true |
| simdjson (ondemand) | 4101.53 | 0.0865486 | 9590.42ms | 409725 | 4890 | 3.32448e+07 | 95268 | 0.0759255 | 0.568321 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6002.42 | 0.138126 | 6368.89ms | 785750 | 2560 | 7.61216e+07 | 124841 | 0.0311033 | 0.388342 | 1(Win) | true |
| simdjson (ondemand) | 5732.05 | 0.0990663 | 6708.15ms | 785750 | 1280 | 2.14689e+07 | 130730 | 0.0444703 | 0.406688 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6116.78 | 0.0973533 | 4131.46ms | 264040 | 4890 | 7.85425e+06 | 41166.8 | 0.193926 | 0.380881 | 1(Win) | true |
| simdjson (ondemand) | 5395.47 | 0.107534 | 4660.66ms | 264040 | 4890 | 1.23164e+07 | 46670.3 | 0.195942 | 0.431807 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6594.98 | 0.203007 | 5785.68ms | 399947 | 1280 | 1.76446e+07 | 57834.8 | 0.0502662 | 0.353362 | 1(Win) | true |
| simdjson (ondemand) | 6406.42 | 0.140212 | 5974.55ms | 399947 | 4890 | 3.40761e+07 | 59537 | 0.197849 | 0.363782 | 2(Loss) | true |
