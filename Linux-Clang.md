# Json-Performance: Stage-1 Parsing
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 892.295 | 0.0673418 | 818.676ms | 905 | 2560 | 1086.15 | 967.253 | 0.171445 | 5.89993 | 27.0707 | 2.72597 | 0.00633633 | 0.000149344 | 9.49586e-06 | 1(Win) | true |
| simdjson (ondemand) | 378.372 | 0.0468543 | 951.615ms | 905 | 4890 | 5585.56 | 2281.02 | 0.0149329 | 13.5416 | 70.789 | 6.90608 | 0.00293394 | 0.000148911 | 1.35579e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1878.63 | 0.0952423 | 816.452ms | 1811 | 2560 | 1962.7 | 919.343 | 0.0521076 | 2.80495 | 13.5229 | 1.36002 | 0.00302772 | 6.51401e-05 | 5.60809e-06 | 1(Win) | true |
| simdjson (ondemand) | 739.829 | 0.0656252 | 956.308ms | 1811 | 1280 | 3004.18 | 2334.46 | 0.19956 | 6.99973 | 35.2921 | 3.43733 | 0.0109375 | 9.05922e-05 | 1.85498e-05 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4061.3 | 0.087285 | 821.343ms | 3862 | 320 | 200.505 | 906.875 | 0.13421 | 1.29912 | 6.33946 | 0.637235 | 0.00106972 | 1.69925e-05 | 8.09166e-07 | 1(Win) | true |
| simdjson (ondemand) | 1652.96 | 0.102558 | 951.399ms | 3862 | 1280 | 6684.19 | 2228.18 | 0.0999924 | 3.09261 | 16.5883 | 1.61833 | 0.000733307 | 3.43896e-05 | 5.46187e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6576.9 | 0.0862463 | 875.865ms | 9578 | 1280 | 1836.53 | 1388.84 | 0.284542 | 0.788565 | 4.05346 | 0.379829 | 0.00108713 | 1.64766e-05 | 2.61015e-06 | 1(Win) | true |
| simdjson (ondemand) | 3752.44 | 0.0502931 | 972.957ms | 9578 | 4890 | 7329.05 | 2434.23 | 0.119978 | 1.36009 | 6.85258 | 0.673106 | 0.000907947 | 2.32298e-05 | 4.29153e-06 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4124.1 | 0.0517384 | 810.533ms | 3873 | 4890 | 1049.96 | 895.609 | 0.0860835 | 1.28051 | 6.31604 | 0.633618 | 0.000872645 | 4.76795e-05 | 8.34259e-06 | 1(Win) | true |
| simdjson (ondemand) | 1662.41 | 0.0729861 | 954.834ms | 3873 | 2560 | 6731.95 | 2221.83 | 0.0342952 | 3.08538 | 16.5412 | 1.61374 | 0.000956946 | 5.71868e-05 | 1.04893e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15832.2 | 0.0332952 | 1297.91ms | 94653 | 2560 | 9225.52 | 5701.56 | 0.0404194 | 0.321588 | 1.76926 | 0.088946 | 2.16168e-05 | 3.9412e-06 | 2.19552e-06 | 1(Win) | true |
| simdjson (ondemand) | 13283 | 0.0332925 | 1403.19ms | 94653 | 30 | 153.564 | 6795.77 | 0.00539522 | 0.382913 | 1.81558 | 0.0772612 | 5.91635e-05 | 1.40865e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16040.4 | 0.0654802 | 1461.89ms | 124597 | 30 | 705.868 | 7407.83 | 0.0647543 | 0.317202 | 1.76725 | 0.0810052 | 8.45392e-05 | 1.07012e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 14439.5 | 0.0281238 | 1542.4ms | 124597 | 40 | 214.251 | 8229.17 | 0.0146857 | 0.352149 | 1.6499 | 0.0693195 | 9.16956e-05 | 8.02588e-07 | 0 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14036.5 | 0.112227 | 8199.72ms | 2251027 | 40 | 1.17841e+06 | 152940 | 0.00973787 | 0.359558 | 1.7439 | 0.0767384 | 0.00175428 | 0.0244582 | 2.84315e-06 | 1(Win) | true |
| simdjson (ondemand) | 11264.4 | 0.0467517 | 5101.14ms | 2251027 | 30 | 238156 | 190578 | 0.106947 | 0.448599 | 1.89629 | 0.0806477 | 0.00180004 | 0.024634 | 7.99635e-07 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17755.4 | 0.309077 | 7615.38ms | 5373214 | 1280 | 1.01848e+09 | 288605 | 0.143348 | 0.283459 | 1.42556 | 0.0539043 | 0.000783775 | 0.0195616 | 8.82459e-06 | 1(Win) | true |
| simdjson (ondemand) | 15114.6 | 0.0433385 | 8917.35ms | 5373214 | 80 | 1.72708e+06 | 339029 | 0.0339383 | 0.334017 | 1.41699 | 0.057812 | 0.000945384 | 0.0195984 | 1.41675e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10576.2 | 0.0142686 | 5234.02ms | 500299 | 4890 | 202614 | 45112.9 | 0.2141 | 0.470588 | 2.53347 | 0.124274 | 2.02934e-05 | 3.35178e-06 | 2.43944e-06 | 1(Win) | true |
| simdjson (ondemand) | 9373.9 | 0.0352833 | 5830.49ms | 500299 | 640 | 206414 | 50899 | 0.0427991 | 0.537184 | 2.57789 | 0.112569 | 1.38511e-05 | 1.09622e-06 | 1.40541e-07 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14384.6 | 0.157453 | 8392.21ms | 1151920 | 4890 | 7.07061e+07 | 76370.2 | 0.0709883 | 0.346049 | 1.8545 | 0.0847481 | 0.000529816 | 0.00421824 | 3.80444e-07 | 1(Win) | true |
| simdjson (ondemand) | 13301.1 | 0.0269267 | 9002.61ms | 1151920 | 640 | 316530 | 82591.5 | 0.127957 | 0.373384 | 1.73803 | 0.0731328 | 0.000278581 | 0.00530624 | 5.37418e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11524.7 | 0.127588 | 1207.44ms | 56369 | 320 | 11334.3 | 4664.56 | 0.084275 | 0.44217 | 2.32839 | 0.115844 | 3.60349e-05 | 3.10454e-06 | 6.09821e-07 | 1(Win) | true |
| simdjson (ondemand) | 10246.1 | 0.0359095 | 1272.18ms | 56369 | 40 | 141.984 | 5246.62 | 0.0427076 | 0.497367 | 2.37274 | 0.103763 | 5.32207e-05 | 2.61669e-05 | 2.21753e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13144.8 | 0.0260865 | 1343.18ms | 83958 | 4890 | 12346.8 | 6091.27 | 0.101145 | 0.385759 | 2.09314 | 0.0970248 | 3.80169e-05 | 2.24331e-06 | 5.06632e-07 | 1(Win) | true |
| simdjson (ondemand) | 12347.6 | 0.0267515 | 1386.7ms | 83958 | 4890 | 14715.1 | 6484.53 | 0.0622776 | 0.409324 | 1.9733 | 0.0849116 | 4.30174e-05 | 1.96563e-06 | 2.77673e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17315.4 | 0.0295935 | 1030.79ms | 53331 | 4890 | 3694.86 | 2937.3 | 0.0673992 | 0.295092 | 1.56633 | 0.0780785 | 3.77509e-05 | 3.58528e-06 | 9.47127e-07 | 1(Win) | true |
| simdjson (ondemand) | 15122.1 | 0.0261132 | 1072.4ms | 53331 | 4890 | 3771.96 | 3363.32 | 0.0224181 | 0.337444 | 1.56436 | 0.0663967 | 3.5013e-05 | 4.27933e-06 | 1.48013e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16813.6 | 0.0655818 | 1113.02ms | 65103 | 1280 | 7506.81 | 3692.66 | 0.0171975 | 0.303778 | 1.65959 | 0.0748968 | 3.12606e-05 | 3.56406e-06 | 1.23602e-06 | 1(Win) | true |
| simdjson (ondemand) | 15782.4 | 0.0260646 | 1127.58ms | 65103 | 80 | 84.11 | 3933.94 | 0.149884 | 0.323701 | 1.50285 | 0.0631922 | 6.95052e-05 | 2.49604e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10080.7 | 0.0814832 | 851.619ms | 11812 | 1280 | 1061.24 | 1117.46 | 0.0161525 | 0.510968 | 2.54004 | 0.128175 | 8.49904e-05 | 7.2093e-06 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 9120.06 | 0.0156745 | 858ms | 11812 | 640 | 23.9892 | 1235.17 | 0.0319945 | 0.562121 | 2.59329 | 0.117254 | 0.000169319 | 1.23021e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14440 | 0.0553679 | 909.686ms | 25388 | 160 | 137.899 | 1676.72 | 0.0708728 | 0.352035 | 1.89085 | 0.0881913 | 4.77588e-05 | 5.41594e-06 | 4.92359e-07 | 1(Win) | true |
| simdjson (ondemand) | 13323.8 | 0.160561 | 922.683ms | 25388 | 640 | 5448.25 | 1817.18 | 0.0101472 | 0.38102 | 1.77864 | 0.0769656 | 4.01888e-05 | 6.03139e-06 | 9.23172e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11055.7 | 0.0732506 | 1679.79ms | 108313 | 30 | 1405.18 | 9343.17 | 0.00392428 | 0.450778 | 2.40346 | 0.118518 | 1.87728e-05 | 2.15425e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9707.76 | 0.0472366 | 1800.37ms | 108313 | 320 | 8084.09 | 10640.5 | 0.0182348 | 0.512749 | 2.45309 | 0.108953 | 3.86611e-05 | 1.55798e-06 | 3.46219e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13127.5 | 0.0396844 | 2073.25ms | 183677 | 1280 | 35892 | 13343.6 | 0.0360203 | 0.379704 | 2.04479 | 0.0940402 | 3.92333e-05 | 7.44343e-07 | 2.1267e-08 | 1(Win) | true |
| simdjson (ondemand) | 12435.6 | 0.0554391 | 2263.18ms | 183677 | 160 | 9757.34 | 14086.1 | 0.0560081 | 0.400045 | 1.92787 | 0.0823784 | 3.57965e-05 | 1.73538e-06 | 0 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8540.2 | 0.130117 | 5475.78ms | 1834197 | 80 | 5.68213e+06 | 204823 | 0.0273455 | 0.582006 | 2.90983 | 0.136897 | 0.00223783 | 0.0376917 | 3.08718e-06 | 1(Win) | true |
| simdjson (ondemand) | 6803.85 | 0.124877 | 6961.44ms | 1834197 | 80 | 8.24583e+06 | 257094 | 0.169935 | 0.732967 | 3.04777 | 0.152982 | 0.00440316 | 0.0376761 | 1.36299e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14786 | 0.149776 | 6277.99ms | 7351818 | 80 | 4.0352e+07 | 474181 | 0.0594988 | 0.334813 | 1.63303 | 0.0669813 | 0.00120233 | 0.021157 | 8.18624e-05 | 1(Win) | true |
| simdjson (ondemand) | 13576.7 | 0.022013 | 6698.59ms | 7351818 | 30 | 387690 | 516418 | 0.10952 | 0.36511 | 1.58987 | 0.066042 | 0.000860345 | 0.0211825 | 9.72095e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12759.7 | 0.105589 | 4164.71ms | 461466 | 40 | 53051.1 | 34490.4 | 0.0111371 | 0.38894 | 2.09417 | 0.103752 | 0.000153857 | 3.35886e-06 | 2.70876e-06 | 1(Win) | true |
| simdjson (ondemand) | 11274.6 | 0.0175512 | 4650.64ms | 461466 | 1280 | 60076.2 | 39033.6 | 0.00262602 | 0.440091 | 2.14095 | 0.0920394 | 1.12227e-05 | 6.44515e-06 | 3.99542e-07 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14538.4 | 0.0335707 | 5490.31ms | 728486 | 640 | 164705 | 47786.3 | 0.0246274 | 0.342146 | 1.89131 | 0.0866017 | 0.000344765 | 7.89308e-07 | 1.97327e-07 | 1(Win) | true |
| simdjson (ondemand) | 13222.7 | 0.035999 | 6039.45ms | 728486 | 160 | 57240.3 | 52541.3 | 0.233022 | 0.375234 | 1.77445 | 0.0748924 | 0.000172009 | 9.69476e-07 | 7.72149e-08 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15784.3 | 0.0117799 | 3560.15ms | 466906 | 4890 | 54000.6 | 28210 | 0.173057 | 0.314892 | 1.73857 | 0.0858482 | 2.04378e-05 | 6.48221e-07 | 1.21761e-07 | 1(Win) | true |
| simdjson (ondemand) | 13573.9 | 0.0328948 | 4009.21ms | 466906 | 1280 | 149045 | 32804 | 0.0127017 | 0.366929 | 1.74365 | 0.0739421 | 7.07617e-06 | 6.77666e-07 | 2.82779e-07 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15866 | 0.129522 | 4479.03ms | 631514 | 30 | 72516.9 | 37959 | 0.0253718 | 0.312707 | 1.74107 | 0.0785035 | 0.000141565 | 5.27832e-07 | 1.5835e-07 | 1(Win) | true |
| simdjson (ondemand) | 14748.7 | 0.0302009 | 4816.39ms | 631514 | 320 | 48668.8 | 40834.8 | 0.0112483 | 0.336499 | 1.59426 | 0.0666716 | 3.20163e-05 | 8.21439e-07 | 3.41441e-07 | 2(Loss) | true |
