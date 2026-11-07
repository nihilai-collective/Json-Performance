# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the GCC 16.2.1 compiler).  

Latest Results: (Nov 07, 2026)
#### Using the following commits:
----
| Jsonifier: [3e5ab01](https://github.com/nihilai-collective/Jsonifier/commit/3e5ab01)  
| simdjson: [54be8dc25](https://github.com/simdjson/simdjson/commit/54be8dc25)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **Stage-1 Only:** Both libraries execute only stage-1 parsing, identifying structural indices and nothing more.
* **No UTF-8 Validation:** Neither library performs UTF-8 validation in these tests.

---
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 794.044 | 0.074658 | 830.762ms | 905 | 4890 | 3220.1 | 1086.94 | 0.0383829 | 6.59241 | 32.558 | 2.71934 | 0.00590697 | 0.000214216 | 5.12942e-05 | 1(Win) | true |
| simdjson (ondemand) | 305.416 | 0.100608 | 1003.39ms | 905 | 40 | 323.323 | 2825.9 | 0.0920908 | 16.816 | 85.3624 | 7.56685 | 0.00325967 | 8.28729e-05 | 0 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1625.78 | 0.0852848 | 828.633ms | 1811 | 2560 | 2101.33 | 1062.32 | 0.155341 | 3.2296 | 16.249 | 1.34235 | 0.0048236 | 7.76505e-05 | 5.82379e-06 | 1(Win) | true |
| simdjson (ondemand) | 602.417 | 0.0596802 | 1011.77ms | 1811 | 160 | 468.407 | 2866.96 | 0.106924 | 8.67495 | 42.63 | 3.76753 | 0.0104914 | 4.14136e-05 | 3.45113e-06 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2979.34 | 0.155262 | 850.393ms | 3862 | 1280 | 4715.44 | 1236.21 | 0.396564 | 1.72778 | 7.57509 | 0.583895 | 0.000971404 | 2.93323e-05 | 8.09166e-07 | 1(Win) | true |
| simdjson (ondemand) | 1298.9 | 0.0478081 | 1011.77ms | 3862 | 2560 | 4704.5 | 2835.53 | 0.0991306 | 3.95518 | 20.0034 | 1.77318 | 0.000752929 | 5.81588e-05 | 1.05192e-05 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5615.64 | 0.094282 | 898.569ms | 9578 | 160 | 376.295 | 1626.58 | 0.00192117 | 0.908815 | 4.45437 | 0.459595 | 0.00133379 | 1.04406e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3102.04 | 0.0597702 | 1030.9ms | 9578 | 1280 | 3964.93 | 2944.61 | 0.0271344 | 1.65202 | 8.14773 | 0.714972 | 0.000940143 | 1.32139e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3466.26 | 0.0800799 | 831.817ms | 3873 | 2560 | 1864.06 | 1065.58 | 0.0822305 | 1.51446 | 7.55358 | 0.582236 | 0.000998298 | 3.89314e-05 | 9.78328e-06 | 1(Win) | true |
| simdjson (ondemand) | 1302.54 | 0.0433175 | 1013.64ms | 3873 | 2560 | 3862.62 | 2835.68 | 0.0355806 | 3.94381 | 19.9466 | 1.76814 | 0.000912467 | 4.91181e-05 | 1.53305e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14633.9 | 0.0921589 | 1340.25ms | 94653 | 30 | 969.495 | 6168.43 | 0.0172953 | 0.347842 | 1.80334 | 0.164929 | 0.000139809 | 2.32428e-05 | 2.18341e-05 | 1(Win) | true |
| simdjson (ondemand) | 12865.2 | 0.0614941 | 1433.85ms | 94653 | 640 | 11914.7 | 7016.45 | 0.0159199 | 0.39744 | 2.00761 | 0.0771767 | 2.08822e-05 | 2.5917e-06 | 9.40937e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15297.5 | 0.0398308 | 1507.03ms | 124597 | 80 | 765.782 | 7767.62 | 0.0263846 | 0.332347 | 1.731 | 0.133157 | 1.65534e-05 | 1.10356e-06 | 3.0097e-07 | 1(Win) | true |
| simdjson (ondemand) | 14271.2 | 0.0129634 | 1560.19ms | 124597 | 4890 | 5696.9 | 8326.2 | 0.0261931 | 0.355913 | 1.83581 | 0.0692553 | 1.68904e-05 | 1.66919e-06 | 9.51944e-08 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13287.6 | 0.342863 | 8803.18ms | 2251027 | 40 | 1.22736e+07 | 161561 | 0.0882892 | 0.378636 | 1.82718 | 0.181783 | 0.00203915 | 0.0247967 | 2.199e-06 | 1(Win) | true |
| simdjson (ondemand) | 11285.4 | 0.120922 | 5012.44ms | 2251027 | 30 | 1.58731e+06 | 190223 | 0.061369 | 0.446634 | 2.09409 | 0.0806477 | 0.0017824 | 0.0247214 | 1.34753e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17319.9 | 0.107267 | 7734.22ms | 5373214 | 30 | 3.02153e+06 | 295861 | 0.00278291 | 0.286644 | 1.37322 | 0.095448 | 0.000877972 | 0.0195902 | 2.4008e-06 | 1(Win) | true |
| simdjson (ondemand) | 14502.7 | 0.0400124 | 9265.95ms | 5373214 | 160 | 3.19802e+06 | 353334 | 0.065619 | 0.348407 | 1.59198 | 0.057812 | 0.000977504 | 0.019599 | 1.29473e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10031.7 | 0.0457258 | 5506.81ms | 500299 | 1280 | 605395 | 47561.3 | 0.0217255 | 0.497795 | 2.78461 | 0.305168 | 1.9746e-05 | 1.76801e-05 | 3.34175e-07 | 1(Win) | true |
| simdjson (ondemand) | 9657.82 | 0.0529538 | 5709.73ms | 500299 | 80 | 54750.1 | 49402.7 | 0.0269144 | 0.523602 | 2.7946 | 0.112563 | 0.000116505 | 0.000693011 | 6.49612e-07 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14024.5 | 0.167916 | 8783.87ms | 1151920 | 160 | 2.76806e+06 | 78331.3 | 0.0593519 | 0.357544 | 1.85763 | 0.151335 | 6.01876e-05 | 0.00451356 | 2.57179e-06 | 1(Win) | true |
| simdjson (ondemand) | 12552 | 0.0368379 | 9467.22ms | 1151920 | 80 | 83157.3 | 87520.5 | 0.133519 | 0.395179 | 1.9283 | 0.0731319 | 0.000501869 | 0.0047944 | 1.81219e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10945.3 | 0.0333809 | 1236.77ms | 56369 | 4890 | 13144 | 4911.46 | 0.0418984 | 0.46509 | 2.52186 | 0.26543 | 3.60392e-05 | 2.39076e-06 | 1.5237e-07 | 1(Win) | true |
| simdjson (ondemand) | 10355.7 | 0.0242434 | 1259.45ms | 56369 | 160 | 253.413 | 5191.12 | 0.0239535 | 0.492246 | 2.58399 | 0.103053 | 5.26664e-05 | 3.7698e-06 | 0 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12283.6 | 0.102027 | 1402.85ms | 83958 | 30 | 1326.85 | 6518.33 | 0.00664836 | 0.414935 | 2.1361 | 0.189368 | 5.91566e-05 | 1.90571e-05 | 1.7072e-05 | 1(Win) | true |
| simdjson (ondemand) | 11899.9 | 0.0288193 | 1410.79ms | 83958 | 80 | 300.81 | 6728.5 | 0.00148624 | 0.427614 | 2.17624 | 0.0844589 | 3.76676e-05 | 2.38214e-06 | 0 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17525.2 | 0.0337959 | 1030.64ms | 53331 | 2560 | 2462.65 | 2902.13 | 0.173024 | 0.292482 | 1.52049 | 0.125237 | 3.80217e-05 | 2.25596e-06 | 1.46491e-08 | 1(Win) | true |
| simdjson (ondemand) | 14954.7 | 0.0366254 | 1077.21ms | 53331 | 80 | 124.126 | 3400.97 | 0.0161744 | 0.342313 | 1.73991 | 0.0652154 | 3.49234e-05 | 5.15648e-06 | 0 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16238.8 | 0.0600387 | 1135.44ms | 65103 | 4890 | 25767 | 3823.37 | 0.065884 | 0.30952 | 1.55564 | 0.108582 | 3.12765e-05 | 4.74001e-06 | 1.82816e-06 | 1(Win) | true |
| simdjson (ondemand) | 14627.5 | 0.0340997 | 1165.56ms | 65103 | 80 | 167.592 | 4244.55 | 0.0931472 | 0.34268 | 1.67746 | 0.0622552 | 5.87531e-05 | 3.64807e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9529.21 | 0.214992 | 864.494ms | 11812 | 30 | 193.775 | 1182.13 | 0.0282056 | 0.539141 | 2.76685 | 0.302912 | 8.46597e-05 | 1.69319e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9203.32 | 0.0293871 | 862.283ms | 11812 | 4890 | 632.674 | 1223.99 | 0.0727532 | 0.557471 | 2.80867 | 0.117169 | 0.000163779 | 7.87733e-06 | 1.38503e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13065.2 | 0.0494733 | 929.796ms | 25388 | 320 | 268.976 | 1853.15 | 0.00354114 | 0.388555 | 1.91386 | 0.15917 | 5.16977e-05 | 7.38538e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 12825.9 | 0.0857164 | 930.691ms | 25388 | 30 | 78.5471 | 1887.73 | 0.163949 | 0.39556 | 1.97101 | 0.0769261 | 4.72664e-05 | 5.25183e-06 | 0 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10231 | 0.0703491 | 1872.68ms | 108313 | 40 | 2017.9 | 10096.3 | 0.0225381 | 0.486924 | 2.64252 | 0.28486 | 4.24695e-05 | 1.61569e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9668.71 | 0.01885 | 1814.55ms | 108313 | 4890 | 19831.5 | 10683.5 | 0.00702019 | 0.516495 | 2.66337 | 0.109027 | 4.03039e-05 | 1.69923e-06 | 1.90692e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12719.2 | 0.0171682 | 2122.7ms | 183677 | 4890 | 27336.8 | 13771.9 | 0.0121649 | 0.392451 | 2.07013 | 0.181601 | 2.30588e-05 | 1.46407e-06 | 4.89879e-07 | 1(Win) | true |
| simdjson (ondemand) | 12335.7 | 0.0299605 | 2183.34ms | 183677 | 40 | 723.997 | 14200 | 0.016552 | 0.403428 | 2.1263 | 0.0823511 | 6.41071e-05 | 1.08887e-06 | 0 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6107.04 | 0.321949 | 7530.98ms | 1834197 | 1280 | 1.08846e+09 | 286428 | 0.229838 | 0.810176 | 3.29036 | 0.383816 | 0.00805263 | 0.0378071 | 4.50214e-06 | 1(Win) | true |
| simdjson (ondemand) | 6017.18 | 0.281227 | 7015.72ms | 1834197 | 40 | 2.67349e+07 | 290705 | 0.29186 | 0.741217 | 3.29421 | 0.160354 | 0.00501444 | 0.0376676 | 2.22168e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 12936.8 | 0.0391844 | 7166.39ms | 7351818 | 80 | 3.6079e+06 | 541963 | 0.0218928 | 0.383158 | 1.77309 | 0.066042 | 0.00104549 | 0.021183 | 8.51796e-05 | 1(Win) | true |
| Jsonifier | 11148.2 | 0.278717 | 8149.54ms | 7351818 | 40 | 1.22904e+08 | 628913 | 0.121353 | 0.4436 | 1.57889 | 0.120675 | 0.00499082 | 0.0211698 | 0.000299752 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12188.8 | 0.0693953 | 4481.8ms | 461466 | 80 | 50223.6 | 36106 | 0.125618 | 0.407103 | 2.21714 | 0.224103 | 1.77153e-05 | 9.20978e-07 | 0 | 1(Win) | true |
| simdjson (ondemand) | 10787.7 | 0.093323 | 4738.98ms | 461466 | 30 | 43482.8 | 40795.3 | 0.0128299 | 0.459877 | 2.34289 | 0.0920394 | 0.000357123 | 8.66803e-07 | 2.88934e-07 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14135.3 | 0.0585369 | 5735.82ms | 728486 | 80 | 66218.9 | 49149.2 | 0.0414981 | 0.35773 | 1.87792 | 0.154147 | 2.905e-05 | 1.00379e-05 | 1.47566e-06 | 1(Win) | true |
| simdjson (ondemand) | 13143.6 | 0.0226803 | 6044.67ms | 728486 | 2560 | 367920 | 52857.7 | 0.000407936 | 0.379534 | 1.96646 | 0.074891 | 0.000164147 | 7.74562e-06 | 8.84754e-08 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15536.7 | 0.0493981 | 3606.08ms | 466906 | 640 | 128275 | 28659.7 | 0.0272888 | 0.319437 | 1.73055 | 0.1545 | 9.33004e-06 | 7.9312e-07 | 2.47641e-07 | 1(Win) | true |
| simdjson (ondemand) | 13148.3 | 0.0496026 | 4130ms | 466906 | 640 | 180596 | 33865.7 | 0.0050611 | 0.377768 | 1.92744 | 0.0728798 | 3.05067e-05 | 3.12563e-06 | 1.17797e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15670.4 | 0.0471184 | 4582.95ms | 631514 | 1280 | 419754 | 38432.8 | 0.264868 | 0.316594 | 1.65874 | 0.122873 | 5.07746e-05 | 2.06349e-06 | 5.12162e-07 | 1(Win) | true |
| simdjson (ondemand) | 14545 | 0.0276065 | 4858.71ms | 631514 | 640 | 83625.9 | 41406.6 | 0.0674714 | 0.341505 | 1.77518 | 0.0659463 | 4.0582e-05 | 1.4103e-06 | 2.25153e-07 | 2(Loss) | true |
