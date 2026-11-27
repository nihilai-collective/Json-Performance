# Json-Performance: Stage-1 Parsing
Just a bit of performance profiling of some JSON libraries (compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

Latest results: (Nov 27, 2026)
#### Here are the commits we used:
----
| Jsonifier: [a1328b5](https://github.com/nihilai-collective/Jsonifier/commit/a1328b5)  
| simdjson: [4ba1cb3ae](https://github.com/simdjson/simdjson/commit/4ba1cb3ae)  

#### How We Benchmarked & What We Tested

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (stage-1)** | `AVX2` |
| **simdjson (stage-1)** | `haswell` |

> Each library picks its own instruction-set implementation at build or run time, and these are the ones that produced the results below.

> **Sampling (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations: 100 → 200 → 400 ... (max 100000), doubling per epoch.  
> Window: last `max(iterations/10, 30)` samples (max 100000). Runs for 5s or until the cap.  
> Epoch used: lowest RSE + mean shift (1st epoch is just a fallback).  
> Converged = RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged ones still get ranked.  
> Ties: Welch's t-test (Bessel-corrected).

---

##### A Few Details
* **Stage-1 Only:** Just stage-1 on both sides, structural indexing with no tape or DOM built.
* **No UTF-8 Validation:** Off for both libraries.

---
*Generated with BenchmarkSuite commit: [ff0f871](https://github.com/nihilai-collective/benchmarksuite/commit/ff0f871)*

----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1879.25 | 0.146645 | 752.834ms | 905 | 4890 | 2218.04 | 459.266 | 0.0988498 | 2.98309 | 12.926 | 2.93923 | 0.00114067 | 0.000118406 | 9.26459e-06 | 1(Win) | true |
| simdjson (stage-1) | 1131.8 | 0.0789094 | 801.862ms | 905 | 320 | 115.869 | 762.572 | 0.231249 | 4.83553 | 23.9227 | 5.47182 | 0.0116609 | 0.000117403 | 4.14365e-05 | 2(Loss) | true |

----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2851.37 | 0.0959827 | 764.707ms | 1811 | 4890 | 1652.82 | 605.71 | 0.415337 | 1.9387 | 9.46107 | 2.46935 | 0.000557714 | 6.54939e-05 | 3.95222e-06 | 1(Win) | true |
| simdjson (stage-1) | 1336.14 | 0.094235 | 835.584ms | 1811 | 2560 | 3798.35 | 1292.6 | 0.00755557 | 3.98322 | 19.6405 | 4.73385 | 0.000855881 | 0.000120358 | 4.72374e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1911.84 | 0.17378 | 773.853ms | 1313 | 160 | 207.275 | 654.956 | 0.0696126 | 2.85668 | 10.7738 | 2.64737 | 0.000813976 | 0.000128522 | 5.2361e-05 | 1(Win) | true |
| simdjson (stage-1) | 1162.78 | 0.161344 | 812.597ms | 1313 | 320 | 966.034 | 1076.88 | 0.0159629 | 4.59812 | 23.1013 | 5.15918 | 0.00137329 | 8.33016e-05 | 1.19002e-05 | 2(Loss) | true |

----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3427.61 | 0.224869 | 829.915ms | 4215 | 1280 | 8901.87 | 1172.75 | 0.0899182 | 1.55909 | 7.30819 | 1.00261 | 0.00166111 | 5.06005e-05 | 1.42719e-05 | 1(Win) | true |
| simdjson (stage-1) | 3278.65 | 0.104166 | 833.802ms | 4215 | 30 | 48.9299 | 1226.03 | 0.0135958 | 1.62108 | 8.30558 | 0.879004 | 0.00127323 | 2.37248e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2217.7 | 0.173982 | 757.745ms | 1213 | 320 | 263.558 | 521.625 | 0.184861 | 2.49587 | 11.1674 | 2.70074 | 0.000896538 | 9.78978e-05 | 5.15251e-06 | 1(Win) | true |
| simdjson (stage-1) | 1112.36 | 0.136335 | 811.333ms | 1213 | 1280 | 2573.09 | 1039.96 | 0.250359 | 4.87994 | 24.676 | 5.50206 | 0.00247192 | 0.000103694 | 4.50845e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16692.3 | 0.0696278 | 1262.73ms | 94653 | 1280 | 18147.2 | 5407.76 | 0.0819229 | 0.311175 | 1.75871 | 0.117757 | 2.21615e-05 | 2.53393e-06 | 1.19681e-06 | 1(Win) | true |
| simdjson (stage-1) | 13612.3 | 0.0557099 | 1381.05ms | 94653 | 1280 | 17469.6 | 6631.39 | 0.0659189 | 0.381074 | 1.81521 | 0.0772084 | 2.71634e-05 | 2.65773e-06 | 1.51871e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16307.2 | 0.0434968 | 1450.67ms | 124597 | 2560 | 25716.3 | 7286.65 | 0.0202466 | 0.316758 | 1.74552 | 0.103695 | 1.64813e-05 | 2.72754e-06 | 1.62399e-06 | 1(Win) | true |
| simdjson (stage-1) | 14632 | 0.0231619 | 1526.82ms | 124597 | 4890 | 17300.7 | 8120.89 | 0.142137 | 0.350916 | 1.64961 | 0.0692794 | 1.63308e-05 | 3.0413e-06 | 1.61502e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13574.6 | 0.167191 | 8746.86ms | 2251027 | 40 | 2.79636e+06 | 158145 | 0.0678717 | 0.378089 | 1.74254 | 0.110614 | 0.00222758 | 0.0248748 | 8.66271e-07 | 1(Win) | true |
| simdjson (stage-1) | 11823.2 | 0.612982 | 9737.36ms | 2251027 | 2560 | 3.17122e+09 | 181570 | 0.066391 | 0.432842 | 1.89627 | 0.0806455 | 0.000911878 | 0.0246696 | 5.68664e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17392.9 | 0.466247 | 7781.27ms | 5373214 | 1280 | 2.41527e+09 | 294620 | 0.0874793 | 0.289991 | 1.42439 | 0.0692394 | 0.00101322 | 0.0195583 | 1.39421e-06 | 1(Win) | true |
| simdjson (stage-1) | 15414.8 | 0.202106 | 8811.83ms | 5373214 | 320 | 1.44445e+08 | 332428 | 0.294928 | 0.332152 | 1.41698 | 0.0578111 | 0.000945057 | 0.0195803 | 5.38202e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10753.1 | 0.0439153 | 5165.78ms | 500299 | 2560 | 971985 | 44370.5 | 0.00113126 | 0.477922 | 2.5935 | 0.189557 | 2.1762e-05 | 1.46163e-06 | 9.2679e-07 | 1(Win) | true |
| simdjson (stage-1) | 9358.24 | 0.073264 | 5814.34ms | 500299 | 30 | 41857.5 | 50984.2 | 0.183511 | 0.540448 | 2.57783 | 0.112559 | 4.73717e-05 | 1.39916e-06 | 6.66268e-08 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15194.9 | 0.152992 | 8113.02ms | 1151920 | 40 | 489380 | 72297.5 | 0.490784 | 0.337323 | 1.86187 | 0.113597 | 0.000392931 | 0.0029621 | 1.38899e-06 | 1(Win) | true |
| simdjson (stage-1) | 13928.4 | 0.15466 | 8750.73ms | 1151920 | 30 | 446392 | 78871.7 | 0.288598 | 0.368913 | 1.738 | 0.0731284 | 0.00017316 | 0.00348708 | 4.48527e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11429.6 | 0.0466273 | 1190.54ms | 56369 | 1280 | 6156.15 | 4703.37 | 0.0470296 | 0.45454 | 2.37219 | 0.170856 | 3.60349e-05 | 2.03736e-06 | 5.54383e-08 | 1(Win) | true |
| simdjson (stage-1) | 10414.7 | 0.0564417 | 1234.72ms | 56369 | 1280 | 10864.1 | 5161.69 | 0.127762 | 0.498646 | 2.3721 | 0.103674 | 3.62982e-05 | 2.23139e-06 | 2.49472e-07 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13778.1 | 0.0365499 | 1302.31ms | 83958 | 80 | 360.916 | 5811.29 | 0.0191401 | 0.376603 | 2.09171 | 0.133853 | 3.67743e-05 | 1.93549e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 12665 | 0.0250516 | 1352.01ms | 83958 | 40 | 100.333 | 6322.02 | 0.00303182 | 0.409419 | 1.9729 | 0.0848519 | 3.57322e-05 | 1.78661e-06 | 0 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17299 | 0.0522412 | 1016.91ms | 53331 | 1280 | 3019.64 | 2940.08 | 0.0248779 | 0.301552 | 1.538 | 0.0984231 | 3.82487e-05 | 2.46105e-06 | 2.05087e-07 | 1(Win) | true |
| simdjson (stage-1) | 15204.8 | 0.0510099 | 1045.36ms | 53331 | 30 | 87.3437 | 3345.03 | 0.193696 | 0.343195 | 1.56376 | 0.0663029 | 0.000226885 | 2.50011e-06 | 0 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17530 | 0.0338526 | 1071.7ms | 65103 | 1280 | 1840.06 | 3541.76 | 0.0291525 | 0.297126 | 1.60275 | 0.0909329 | 3.13326e-05 | 5.4961e-06 | 2.43604e-06 | 1(Win) | true |
| simdjson (stage-1) | 16135.4 | 0.0520813 | 1100.48ms | 65103 | 1280 | 5140.64 | 3847.88 | 0.0610692 | 0.322638 | 1.50234 | 0.0631154 | 4.25168e-05 | 1.81203e-06 | 1.08002e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10283.7 | 0.114334 | 819.698ms | 11812 | 2560 | 4015.45 | 1095.4 | 0.0586627 | 0.523607 | 2.58813 | 0.1915 | 8.53211e-05 | 1.16738e-05 | 5.22509e-06 | 1(Win) | true |
| simdjson (stage-1) | 9359 | 0.0935465 | 829.195ms | 11812 | 30 | 38.0333 | 1203.63 | 0.0776032 | 0.568732 | 2.59042 | 0.11683 | 0.000318885 | 2.25759e-05 | 5.64398e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15034.7 | 0.103591 | 876.45ms | 25388 | 30 | 83.4897 | 1610.4 | 0.0787173 | 0.351247 | 1.90941 | 0.118914 | 4.98923e-05 | 1.31296e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 13777.1 | 0.0464284 | 889.684ms | 25388 | 30 | 19.9724 | 1757.4 | 0.00758754 | 0.382622 | 1.77726 | 0.0767686 | 7.87774e-05 | 6.56478e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11141.3 | 0.0663704 | 1654.4ms | 108313 | 320 | 12116.8 | 9271.39 | 0.0271595 | 0.46396 | 2.47339 | 0.179369 | 4.0623e-05 | 1.15406e-06 | 5.77031e-08 | 1(Win) | true |
| simdjson (stage-1) | 10044.1 | 0.0376886 | 1752ms | 108313 | 2560 | 38459.3 | 10284.2 | 0.101573 | 0.514468 | 2.45756 | 0.108907 | 3.08784e-05 | 2.12059e-06 | 8.79973e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14259.8 | 0.0475759 | 1951.05ms | 183677 | 30 | 1024.65 | 12284 | 0.111923 | 0.362425 | 2.0355 | 0.128737 | 4.44621e-05 | 1.27035e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 12919.9 | 0.0207207 | 2082.12ms | 183677 | 4890 | 38592.9 | 13558 | 0.00381303 | 0.398928 | 1.9277 | 0.0823512 | 2.75824e-05 | 2.28907e-06 | 1.48077e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 7405.32 | 0.181356 | 6357.62ms | 1834197 | 80 | 1.4681e+07 | 236212 | 0.316297 | 0.694399 | 3.00091 | 0.221873 | 0.00679348 | 0.037707 | 1.30166e-06 | 1(Win) | true |
| simdjson (stage-1) | 7035.98 | 0.0566393 | 6575.29ms | 1834197 | 640 | 1.26899e+07 | 248612 | 0.243604 | 0.730844 | 3.08886 | 0.152979 | 0.00431101 | 0.0376926 | 2.08453e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13593.9 | 0.462943 | 6620.23ms | 7351818 | 320 | 1.82433e+09 | 515762 | 0.524279 | 0.372544 | 1.60714 | 0.0869614 | 0.00224619 | 0.0211738 | 0.000429202 | 1(Win) | true |
| simdjson (stage-1) | 13309.3 | 0.726802 | 6765.66ms | 7351818 | 640 | 9.38186e+09 | 526791 | 0.0265701 | 0.385076 | 1.58986 | 0.0660413 | 0.00111118 | 0.0211919 | 0.000196183 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13256.7 | 0.0765449 | 4058.33ms | 461466 | 640 | 413258 | 33197.4 | 0.0100639 | 0.387581 | 2.10669 | 0.147573 | 1.54061e-05 | 1.36454e-06 | 9.51451e-07 | 1(Win) | true |
| simdjson (stage-1) | 11599.8 | 0.0300657 | 4519.65ms | 461466 | 4890 | 636252 | 37939.2 | 0.0326572 | 0.441965 | 2.14087 | 0.0920285 | 1.39743e-05 | 5.27039e-06 | 4.5352e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15480.6 | 0.068916 | 5217.44ms | 728486 | 160 | 153048 | 44878 | 0.0823743 | 0.331625 | 1.87508 | 0.114693 | 0.000125732 | 5.38789e-06 | 3.98944e-06 | 1(Win) | true |
| simdjson (stage-1) | 13819.3 | 0.0276699 | 5756.95ms | 728486 | 2560 | 495364 | 50272.9 | 0.216182 | 0.370366 | 1.7744 | 0.0748855 | 1.27839e-05 | 4.02536e-06 | 2.72665e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15635.4 | 0.0851149 | 3551.66ms | 466906 | 160 | 94009.4 | 28478.7 | 0.324029 | 0.32343 | 1.71062 | 0.11295 | 1.39482e-05 | 1.36537e-06 | 1.04411e-06 | 1(Win) | true |
| simdjson (stage-1) | 13926 | 0.100779 | 3930.16ms | 466906 | 40 | 41534.5 | 31974.5 | 0.015635 | 0.369981 | 1.74384 | 0.0739315 | 6.7626e-05 | 1.12442e-06 | 5.88984e-07 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16973.7 | 0.0660779 | 4297.37ms | 631514 | 320 | 175905 | 35481.9 | 0.126067 | 0.300002 | 1.69236 | 0.0983938 | 1.62853e-05 | 7.2247e-07 | 4.05771e-07 | 1(Win) | true |
| simdjson (stage-1) | 15249 | 0.0296046 | 4681.02ms | 631514 | 1280 | 174989 | 39494.9 | 0.134417 | 0.336216 | 1.59421 | 0.0666637 | 2.087e-05 | 1.37443e-06 | 1.06639e-06 | 2(Loss) | true |
