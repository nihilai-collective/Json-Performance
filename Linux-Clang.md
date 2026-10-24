# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-1017-azure using the Clang 24.0.0 compiler).  

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

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 217.879 | 0.0524649 | 402.894ms | 905 | 80 | 345.538 | 3961.26 | 0.077371 | 10.6026 | 1(Win) | true |
| simdjson (ondemand) | 134.075 | 0.211783 | 649.746ms | 905 | 2560 | 475802 | 6437.27 | 0.0174126 | 17.2954 | 2(Loss) | true |

----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 427.705 | 0.0681574 | 411.483ms | 1811 | 40 | 302.994 | 4038.07 | 0.000619103 | 5.40469 | 1(Win) | true |
| simdjson (ondemand) | 279.9 | 0.036806 | 626.517ms | 1811 | 80 | 412.627 | 6170.43 | 0.29006 | 8.28319 | 2(Loss) | true |

----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 886.754 | 0.0715154 | 423.351ms | 3862 | 40 | 352.921 | 4153.45 | 0.0653647 | 2.60621 | 1(Win) | true |
| simdjson (ondemand) | 573.625 | 0.0585913 | 653.833ms | 3862 | 40 | 566.102 | 6420.73 | 0.0556481 | 4.04244 | 2(Loss) | true |

----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 1743.39 | 0.0360196 | 533.136ms | 9578 | 80 | 284.924 | 5239.39 | 0.0407801 | 1.32879 | 1(Win) | true |
| simdjson (ondemand) | 1462.51 | 0.0428095 | 633.933ms | 9578 | 80 | 571.905 | 6245.64 | 0.147721 | 1.58532 | 2(Loss) | true |

----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 896.209 | 0.0438402 | 420.358ms | 3873 | 80 | 261.163 | 4121.34 | 0.00151652 | 2.57906 | 1(Win) | true |
| simdjson (ondemand) | 591.501 | 0.136852 | 688.785ms | 3873 | 4890 | 357106 | 6244.42 | 0.0330084 | 3.91959 | 2(Loss) | true |

----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5734.11 | 0.0677679 | 8896.25ms | 2090234 | 1280 | 7.10421e+07 | 347639 | 0.201244 | 0.406648 | 1(Win) | true |
| simdjson (ondemand) | 4470.97 | 0.0726188 | 5659.4ms | 2090234 | 640 | 6.70911e+07 | 445855 | 0.138147 | 0.52154 | 2(Loss) | true |

----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 9090.12 | 0.0800775 | 8875.73ms | 6661897 | 320 | 1.00237e+08 | 698921 | 0.017463 | 0.256529 | 1(Win) | true |
| simdjson (ondemand) | 7939.28 | 0.131961 | 5034.05ms | 6661897 | 80 | 8.92107e+07 | 800234 | 0.129265 | 0.293696 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3728.73 | 0.0616563 | 6583.86ms | 500299 | 2560 | 1.59343e+07 | 127958 | 0.00249385 | 0.625224 | 1(Win) | true |
| simdjson (ondemand) | 3255.01 | 0.0856117 | 7489.16ms | 500299 | 1280 | 2.01573e+07 | 146581 | 0.0185832 | 0.716207 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6216.19 | 0.14391 | 5642.12ms | 1439562 | 320 | 3.23254e+07 | 220854 | 0.0921364 | 0.37509 | 1(Win) | true |
| simdjson (ondemand) | 5915.38 | 0.0973859 | 5939.18ms | 1439562 | 1280 | 6.5388e+07 | 232086 | 0.0437544 | 0.394155 | 2(Loss) | true |

----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4320.52 | 0.139404 | 1251.66ms | 56369 | 2560 | 770197 | 12442.4 | 0.145894 | 0.53819 | 1(Win) | true |
| simdjson (ondemand) | 3723.21 | 0.112292 | 1456.22ms | 56369 | 4890 | 1.28544e+06 | 14438.5 | 0.0182071 | 0.624707 | 2(Loss) | true |

----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5551.9 | 0.155533 | 1626.52ms | 94370 | 2560 | 1.62732e+06 | 16210.4 | 0.0248167 | 0.419012 | 1(Win) | true |
| simdjson (ondemand) | 5085.27 | 0.114178 | 1773.28ms | 94370 | 4890 | 1.9967e+06 | 17697.8 | 0.0574969 | 0.457658 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3815.91 | 0.0602522 | 301.853ms | 11812 | 80 | 253.097 | 2952.06 | 0.0165112 | 0.603682 | 1(Win) | true |
| simdjson (ondemand) | 3303.45 | 0.209757 | 344.649ms | 11812 | 4890 | 250180 | 3410.01 | 0.062524 | 0.698605 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6398.55 | 0.0838132 | 473.529ms | 31235 | 30 | 456.737 | 4655.43 | 0.0508108 | 0.36155 | 1(Win) | true |
| simdjson (ondemand) | 6035.86 | 0.175376 | 497.712ms | 31235 | 4890 | 366313 | 4935.17 | 0.0277083 | 0.383616 | 2(Loss) | true |

----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4093.04 | 0.119443 | 2527.49ms | 108313 | 2560 | 2.32613e+06 | 25236.8 | 0.033402 | 0.568862 | 1(Win) | true |
| simdjson (ondemand) | 3549.96 | 0.0828135 | 2915.11ms | 108313 | 4890 | 2.8394e+06 | 29097.6 | 0.0271774 | 0.656117 | 2(Loss) | true |

----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 5836.68 | 0.113206 | 3500.9ms | 213963 | 2560 | 4.00981e+06 | 34960.1 | 0.0385946 | 0.399118 | 1(Win) | true |
| simdjson (ondemand) | 5486.04 | 0.0760318 | 3727.37ms | 213963 | 4890 | 3.91074e+06 | 37194.6 | 0.13141 | 0.424663 | 2(Loss) | true |

----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 3032.08 | 0.0604151 | 7329.4ms | 1834197 | 640 | 7.7747e+07 | 576907 | 0.0263356 | 0.769083 | 1(Win) | true |
| simdjson (ondemand) | 2599.04 | 0.0622482 | 8549.42ms | 1834197 | 320 | 5.61654e+07 | 673027 | 0.0183115 | 0.897222 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 7561.64 | 0.0637803 | 7917.77ms | 9930848 | 320 | 2.04204e+08 | 1.25248e+06 | 0.0533452 | 0.308402 | 1(Win) | true |
| simdjson (ondemand) | 6821.35 | 0.154066 | 8755.06ms | 9930848 | 30 | 1.37267e+08 | 1.38841e+06 | 0.0662205 | 0.341866 | 2(Loss) | true |

----
### Mesh Test (Minified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4381.98 | 0.0667261 | 7151.38ms | 642697 | 2560 | 2.23e+07 | 139874 | 0.0555128 | 0.532027 | 1(Win) | true |
| simdjson (ondemand) | 3700.84 | 0.0808312 | 8480.96ms | 642697 | 1280 | 2.29394e+07 | 165618 | 0.00493254 | 0.629948 | 2(Loss) | true |

----
### Mesh Test (Prettified) Results [(View the data used in the following test)](./json/Mesh%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Mesh%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6157.03 | 0.0620616 | 9715.83ms | 1225964 | 2560 | 3.55548e+07 | 189892 | 0.131765 | 0.378677 | 1(Win) | true |
| simdjson (ondemand) | 5317.53 | 0.0963098 | 5606.07ms | 1225964 | 1280 | 5.73966e+07 | 219871 | 0.0637531 | 0.438463 | 2(Loss) | true |

----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 4536.44 | 0.188475 | 8593.67ms | 409725 | 640 | 1.68672e+07 | 86134.5 | 0.0639053 | 0.513804 | 1(Win) | true |
| simdjson (ondemand) | 3915.51 | 0.1388 | 5129.07ms | 409725 | 640 | 1.22791e+07 | 99794.1 | 0.00621631 | 0.595339 | 2(Loss) | true |

----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6083.09 | 0.179939 | 6366.71ms | 785750 | 640 | 3.1445e+07 | 123186 | 0.0699993 | 0.383219 | 1(Win) | true |
| simdjson (ondemand) | 5685.65 | 0.149593 | 6761ms | 785750 | 320 | 1.2439e+07 | 131797 | 0.0165244 | 0.41001 | 2(Loss) | true |

----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6020.62 | 0.147785 | 4212.47ms | 264040 | 1280 | 4.89021e+06 | 41824.3 | 0.0760696 | 0.386995 | 1(Win) | true |
| simdjson (ondemand) | 5267.39 | 0.0689687 | 4825.62ms | 264040 | 4890 | 5.31573e+06 | 47805.2 | 0.171765 | 0.442309 | 2(Loss) | true |

----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| jsonifier | 6668.65 | 0.0769604 | 5727.67ms | 399947 | 4890 | 9.47486e+06 | 57195.8 | 0.151909 | 0.349459 | 1(Win) | true |
| simdjson (ondemand) | 6426.8 | 0.0684119 | 5944.16ms | 399947 | 4890 | 8.06099e+06 | 59348.2 | 0.00315751 | 0.362621 | 2(Loss) | true |
