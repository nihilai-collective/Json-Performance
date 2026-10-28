# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

Latest Results: (Oct 28, 2026)
#### Using the following commits:
----
| Jsonifier: [9f4382a](https://github.com/nihilai-collective/jsonifier/commit/9f4382a)  
| simdjson(On Demand): [41ad75c](https://github.com/simdjson/simdjson/commit/41ad75c)  

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
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 949.294 | 0.064438 | 814.599ms | 905 | 4890 | 1678.37 | 909.176 | 0.135532 | 5.55854 | 28.6166 | 2.56575 | 0.00454779 | 0.00015569 | 3.23131e-05 | 1(Win) | true |
| simdjson (ondemand) | 310.116 | 0.0787692 | 1020.89ms | 905 | 1280 | 6151.39 | 2783.08 | 0.0812569 | 16.6878 | 84.9204 | 7.56575 | 0.00375345 | 0.000139848 | 2.6761e-05 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 1922.08 | 0.154602 | 816.523ms | 1811 | 1280 | 2470.2 | 898.558 | 0.0013911 | 2.74713 | 14.2827 | 1.26891 | 0.000555632 | 5.9532e-05 | 1.42359e-05 | 1(Win) | true |
| simdjson (ondemand) | 590.699 | 0.0962225 | 1017.5ms | 1811 | 30 | 237.454 | 2923.83 | 0.122975 | 8.6783 | 42.4092 | 3.76698 | 0.0132339 | 0 | 0 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 3885.37 | 0.110008 | 818.632ms | 3862 | 80 | 86.996 | 947.938 | 0.0646557 | 1.35656 | 6.6362 | 0.544795 | 0.0007768 | 1.29467e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1343.13 | 0.0617323 | 999.344ms | 3862 | 1280 | 3667.93 | 2742.16 | 0.062176 | 3.88658 | 19.8998 | 1.77292 | 0.000517866 | 2.75117e-05 | 3.03437e-06 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4819.18 | 0.0486074 | 904.759ms | 9578 | 640 | 543.236 | 1895.4 | 0.060307 | 1.09165 | 4.55346 | 0.44456 | 0.000902785 | 8.97238e-06 | 6.52537e-07 | 1(Win) | true |
| simdjson (ondemand) | 3150.33 | 0.0647573 | 1011.64ms | 9578 | 640 | 2256.29 | 2899.47 | 0.0310844 | 1.62665 | 8.10597 | 0.714868 | 0.000940469 | 1.07669e-05 | 6.52537e-07 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 4238.57 | 0.0509412 | 810.843ms | 3873 | 1280 | 252.235 | 871.422 | 0.0611055 | 1.247 | 6.61735 | 0.543248 | 0.000774593 | 2.96524e-05 | 6.85838e-06 | 1(Win) | true |
| simdjson (ondemand) | 1325.34 | 0.0309913 | 1002.4ms | 3873 | 4890 | 3647.8 | 2786.9 | 0.0137142 | 3.86657 | 19.8433 | 1.76788 | 0.00051666 | 4.36666e-05 | 9.45141e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15236.5 | 0.0669706 | 1326.43ms | 94653 | 40 | 629.692 | 5924.48 | 0.0125203 | 0.334513 | 1.65882 | 0.164876 | 3.16947e-05 | 1.84886e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 13181 | 0.0334034 | 1416.93ms | 94653 | 4890 | 25589.6 | 6848.37 | 0.0124308 | 0.385746 | 2.00761 | 0.0771767 | 2.17391e-05 | 3.74633e-06 | 1.55989e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15159.1 | 0.0486775 | 1525.55ms | 124597 | 4890 | 71192.5 | 7838.52 | 0.021835 | 0.333201 | 1.62954 | 0.133133 | 1.74354e-05 | 2.34539e-06 | 1.21291e-06 | 1(Win) | true |
| simdjson (ondemand) | 13963.9 | 0.0261765 | 1585.7ms | 124597 | 80 | 396.929 | 8509.41 | 0.0171839 | 0.363877 | 1.83581 | 0.0692553 | 1.72556e-05 | 2.30744e-06 | 1.10356e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13414.7 | 0.0843848 | 8631.01ms | 2251027 | 1280 | 2.33419e+07 | 160029 | 8.00636e-05 | 0.37535 | 1.66497 | 0.181782 | 0.00207962 | 0.0249851 | 1.46565e-06 | 1(Win) | true |
| simdjson (ondemand) | 11591.9 | 0.013271 | 9932.34ms | 2251027 | 2560 | 1.54632e+06 | 185194 | 0.0780689 | 0.436538 | 2.09409 | 0.0806477 | 0.00142935 | 0.0249287 | 1.08839e-06 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17748.9 | 0.0253298 | 7586.63ms | 5373214 | 1280 | 6.84542e+06 | 288710 | 0.0942408 | 0.28435 | 1.30904 | 0.0954467 | 0.000858242 | 0.0196113 | 5.72719e-07 | 1(Win) | true |
| simdjson (ondemand) | 14554.7 | 0.0149636 | 9221.03ms | 5373214 | 1280 | 3.55262e+06 | 352072 | 0.0241367 | 0.347002 | 1.59198 | 0.057812 | 0.000928002 | 0.0195855 | 1.42707e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10349.1 | 0.0109799 | 5342.52ms | 500299 | 4890 | 125300 | 46102.6 | 0.179088 | 0.488887 | 2.49916 | 0.305178 | 1.30801e-05 | 3.9972e-06 | 3.37303e-06 | 1(Win) | true |
| simdjson (ondemand) | 9670.1 | 0.0527392 | 5635.28ms | 500299 | 80 | 54169.5 | 49340 | 0.0164954 | 0.522938 | 2.7946 | 0.112563 | 8.73728e-05 | 2.22367e-06 | 5.99641e-07 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14166.3 | 0.0398987 | 8533.95ms | 1151920 | 1280 | 1.22535e+06 | 77547.2 | 0.00857817 | 0.356338 | 1.73759 | 0.151327 | 3.59929e-05 | 5.6555e-05 | 3.31451e-05 | 1(Win) | true |
| simdjson (ondemand) | 12860.1 | 0.0121514 | 9311.67ms | 1151920 | 4890 | 526890 | 85423.7 | 0.0515966 | 0.39277 | 1.9283 | 0.0731319 | 0.000401375 | 2.78104e-05 | 1.02026e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 11025 | 0.0308387 | 1220.43ms | 56369 | 4890 | 11056.7 | 4875.99 | 0.0210401 | 0.46257 | 2.27668 | 0.265447 | 6.28273e-05 | 2.75355e-06 | 1.77765e-07 | 1(Win) | true |
| simdjson (ondemand) | 10071.6 | 0.023652 | 1263.22ms | 56369 | 4890 | 7793.52 | 5337.57 | 0.0254463 | 0.505737 | 2.58399 | 0.103053 | 3.56256e-05 | 3.18526e-06 | 4.89761e-07 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12664.3 | 0.184825 | 1361.9ms | 83958 | 30 | 4096.38 | 6322.37 | 0.102704 | 0.407155 | 1.97776 | 0.189261 | 3.45411e-05 | 2.30274e-05 | 2.06452e-05 | 1(Win) | true |
| simdjson (ondemand) | 12322.1 | 0.0563682 | 1379.2ms | 83958 | 320 | 4293.11 | 6497.95 | 0.0176529 | 0.412812 | 2.17624 | 0.0844589 | 3.73327e-05 | 8.56083e-06 | 6.25313e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 17204.4 | 0.052765 | 1026.65ms | 53331 | 160 | 389.308 | 2956.25 | 0.0109924 | 0.298347 | 1.4158 | 0.125293 | 0.000139694 | 5.27367e-06 | 2.34385e-07 | 1(Win) | true |
| simdjson (ondemand) | 14437.1 | 0.0253439 | 1085.18ms | 53331 | 4890 | 3898.15 | 3522.9 | 0.0145144 | 0.35406 | 1.73991 | 0.0652154 | 3.78352e-05 | 5.47953e-06 | 2.60748e-07 | 2(Loss) | true |

----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16871.4 | 0.0507941 | 1103.76ms | 65103 | 640 | 2236.17 | 3680.01 | 0.0578383 | 0.303227 | 1.47838 | 0.108597 | 7.70414e-05 | 2.23204e-06 | 1.44003e-07 | 1(Win) | true |
| simdjson (ondemand) | 15532.3 | 0.0467009 | 1130.33ms | 65103 | 640 | 2230.28 | 3997.28 | 0.00836436 | 0.32883 | 1.67746 | 0.0622552 | 3.05765e-05 | 4.32008e-06 | 7.20013e-08 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10182.8 | 0.161492 | 833.442ms | 11812 | 80 | 255.335 | 1106.26 | 0.00791014 | 0.514927 | 2.49111 | 0.303336 | 8.46597e-05 | 3.28056e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (ondemand) | 9417.52 | 0.0328588 | 844.767ms | 11812 | 320 | 49.4342 | 1196.15 | 0.0698036 | 0.555636 | 2.80867 | 0.117169 | 8.46597e-05 | 1.82547e-05 | 2.11649e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 13739.1 | 0.178926 | 910.791ms | 25388 | 30 | 298.271 | 1762.27 | 0.00378315 | 0.37683 | 1.78833 | 0.158933 | 4.46405e-05 | 1.83814e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 13297.6 | 0.0503704 | 910.506ms | 25388 | 80 | 67.2905 | 1820.78 | 0.00823757 | 0.389076 | 1.97101 | 0.0769261 | 4.57893e-05 | 1.13242e-05 | 1.96943e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 10832.3 | 0.0246923 | 1688.62ms | 108313 | 2560 | 14193.3 | 9535.86 | 0.0510149 | 0.468311 | 2.378 | 0.284841 | 1.84722e-05 | 2.85991e-06 | 1.46782e-06 | 1(Win) | true |
| simdjson (ondemand) | 10121.9 | 0.0167229 | 1753.45ms | 108313 | 4890 | 14241.9 | 10205.1 | 0.00829595 | 0.501467 | 2.66337 | 0.109027 | 4.51751e-05 | 2.91324e-06 | 1.07996e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12832.2 | 0.043276 | 2106.5ms | 183677 | 2560 | 89339.6 | 13650.7 | 0.0491717 | 0.394087 | 1.92011 | 0.181569 | 2.246e-05 | 2.7647e-06 | 1.49719e-06 | 1(Win) | true |
| simdjson (ondemand) | 12263.6 | 0.057535 | 2161.54ms | 183677 | 160 | 10805.9 | 14283.6 | 0.0072193 | 0.413228 | 2.1263 | 0.0823512 | 7.09466e-05 | 3.47077e-06 | 2.34787e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6998.07 | 0.0418134 | 6597.13ms | 1834197 | 1280 | 1.39822e+07 | 249958 | 0.0565517 | 0.721343 | 3.29421 | 0.160354 | 0.00377936 | 0.0376907 | 1.76849e-06 | 1(Win) | true |
| jsonifier | 6503.31 | 0.0566776 | 7093.91ms | 1834197 | 1280 | 2.97479e+07 | 268975 | 0.0473997 | 0.774347 | 2.92613 | 0.383817 | 0.00787624 | 0.0378292 | 1.27397e-06 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 13193.8 | 0.061771 | 6881.03ms | 7351818 | 40 | 4.31003e+06 | 531405 | 0.080957 | 0.382695 | 1.77309 | 0.066042 | 0.00103374 | 0.0211887 | 1.19358e-06 | 1(Win) | true |
| jsonifier | 11156.2 | 0.119184 | 8078.4ms | 7351818 | 320 | 1.79533e+08 | 628462 | 0.241981 | 0.451392 | 1.48947 | 0.120675 | 0.00533505 | 0.0211963 | 5.07485e-06 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 12760.1 | 0.0284929 | 4222.17ms | 461466 | 2560 | 247220 | 34489.3 | 0.0921525 | 0.39785 | 2.01274 | 0.224097 | 1.52215e-05 | 1.47289e-06 | 7.50834e-07 | 1(Win) | true |
| simdjson (ondemand) | 11525.9 | 0.0239067 | 4545.11ms | 461466 | 640 | 53327.7 | 38182.7 | 0.0251237 | 0.438745 | 2.34289 | 0.0920394 | 1.69196e-05 | 6.37574e-06 | 5.95588e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 14176.2 | 0.0304682 | 5647.08ms | 728486 | 1280 | 285383 | 49007.4 | 0.0391548 | 0.357645 | 1.7551 | 0.154135 | 2.13113e-05 | 1.93359e-06 | 8.19336e-07 | 1(Win) | true |
| simdjson (ondemand) | 13379.7 | 0.0157138 | 5939.56ms | 728486 | 4890 | 325549 | 51924.7 | 0.0612689 | 0.378619 | 1.96646 | 0.074891 | 0.000114648 | 7.16532e-06 | 5.29939e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 16104 | 0.0539212 | 3508.1ms | 466906 | 1280 | 284526 | 27650.1 | 0.0166761 | 0.313662 | 1.59509 | 0.154483 | 8.7193e-06 | 1.96439e-06 | 1.48585e-06 | 1(Win) | true |
| simdjson (ondemand) | 13721 | 0.0183817 | 3978.22ms | 466906 | 2560 | 91095.6 | 32452.1 | 0.0701887 | 0.368515 | 1.92744 | 0.0728798 | 2.39534e-05 | 2.27144e-06 | 1.526e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier | 15973.5 | 0.0875845 | 4623.83ms | 631514 | 80 | 87238.8 | 37703.6 | 0.018503 | 0.316659 | 1.56616 | 0.122868 | 2.94728e-05 | 2.85029e-06 | 2.5138e-06 | 1(Win) | true |
| simdjson (ondemand) | 14744.6 | 0.0833314 | 4816.8ms | 631514 | 160 | 185369 | 40846 | 0.0300915 | 0.34268 | 1.77518 | 0.0659464 | 4.37936e-05 | 3.58266e-06 | 2.23669e-06 | 2(Loss) | true |
