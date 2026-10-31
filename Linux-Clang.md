# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the Clang 24.0.0 compiler).  

Latest Results: (Oct 30, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [b6f72f8](https://github.com/nihilai-collective/jsonifier/commit/b6f72f8)  
| Simdjson (On Demand): [6d17180cd](https://github.com/simdjson/simdjson/commit/6d17180cd)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `AVX2` |
| **simdjson (ondemand)** | `haswell` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Intel(R) Core(TM) i9-14900KF-AVX2):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 4s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 5% and mean shift ≤ 2.5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **UTF-8 Validation:** Both libraries perform full UTF-8 validation in every test.
* **Schema-Free Traversal:** Neither library is given a schema. `jsonifier (generic)` walks its stage-1 structural tape through the re-accessible `jsonifier::generic` API; `simdjson (ondemand)` walks its On Demand API. Both fill the exact same structs through the exact same field-by-field traversal.
* **Streaming:** `jsonifier (generic)` uses `jsonifier::jsonifier_core::iterateMany`; `simdjson (ondemand)` uses `ondemand::parser::iterate_many` (unthreaded). Both use a 1 MiB batch size.

##### Test Variants
* **Amazon Cellphones:** Aggregates ratings per brand over `amazon_cellphones.ndjson` (from the simdjson repository; repeated to 10 MiB for the Large variant).
* **Stream Formats:** Reads and sums `"id"` over generated `{"id","name","payload","flag"}` documents, following simdjson's stream benchmarks, with 16- and 4096-byte payloads, repeated to 16 MB to fit the sampling window.
* **Stream:** Splits each corpus document's main record array into one document per record, repeated to 4 MiB.
* **(NDJSON) vs. (Comma-Separated):** Documents separated by newlines, or by commas (simdjson's `stream_format::comma_delimited`, Jsonifier's `allowCommaSeparated`).
* **Key Traversal Order:** Standard tests request keys in document order. Tests labeled `Reverse` request each object's keys backwards, forcing forward-only iterative parsers (e.g., simdjson On Demand) into sequential rescans or rewinds, degrading from $O(N)$ toward $O(N^2)$ as object size grows.
* **Sparse:** Reads the same document as its full counterpart but requests only a small subset of fields (a few per record of the main arrays, in the spirit of Twitter Partial); all other fields are skipped by each library. `Sparse Reverse` requests that subset in reverse document order.

---
*Environment generated via BenchmarkSuite commit: [35ec835](https://github.com/nihilai-collective/benchmarksuite/commit/35ec835)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 550.131 | 0.0967266 | 879.884ms | 905 | 320 | 736.897 | 1568.85 | 0.139827 | 9.42568 | 48.9569 | 6.15912 | 0.00121202 | 4.83425e-05 | 3.45304e-06 | 1(Win) | true |
| simdjson (ondemand) | 280.651 | 0.057028 | 1036.39ms | 905 | 2560 | 7873.73 | 3075.26 | 0.100346 | 18.2082 | 88.0608 | 9.69835 | 0.024997 | 0.000172652 | 4.44579e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 576.381 | 0.0710335 | 874.49ms | 905 | 2560 | 2896.3 | 1497.4 | 0.300294 | 9.06426 | 48.3392 | 6.04089 | 0.00113346 | 0.0001351 | 3.62569e-05 | 1(Win) | true |
| simdjson (ondemand) | 283.676 | 0.0887799 | 1032.02ms | 905 | 30 | 218.878 | 3042.47 | 0.221803 | 18.1082 | 87.4431 | 9.58011 | 0.0267035 | 7.36648e-05 | 0 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 658.602 | 0.100546 | 1001.41ms | 1811 | 1280 | 8898.83 | 2622.38 | 0.0118883 | 7.80958 | 38.5936 | 6.14246 | 0.00061085 | 0.000135457 | 4.74531e-05 | 1(Win) | true |
| simdjson (ondemand) | 356.463 | 0.0770533 | 1220.47ms | 1811 | 80 | 1115.01 | 4845.11 | 0.262031 | 14.3084 | 70.1121 | 9.3291 | 0.00171176 | 7.59249e-05 | 6.90226e-06 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 685.144 | 0.0411958 | 982.531ms | 1811 | 4890 | 5273.36 | 2520.79 | 0.053772 | 7.50591 | 37.5566 | 5.91773 | 0.00117437 | 9.5192e-05 | 1.86319e-05 | 1(Win) | true |
| simdjson (ondemand) | 369.873 | 0.0534783 | 1212.42ms | 1811 | 2560 | 15963.4 | 4669.45 | 0.0165694 | 13.9047 | 69.0834 | 9.10547 | 0.000584967 | 0.000147105 | 5.50024e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1497.91 | 0.0882237 | 985.792ms | 3862 | 640 | 3011.65 | 2458.82 | 0.0539803 | 3.43546 | 16.9801 | 2.0971 | 0.00160336 | 3.35804e-05 | 4.04583e-07 | 1(Win) | true |
| simdjson (ondemand) | 779.011 | 0.0361171 | 1206.01ms | 3862 | 2560 | 7464.55 | 4727.91 | 0.244079 | 6.53965 | 28.0163 | 3.60099 | 0.0138638 | 5.98783e-05 | 1.88131e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1560.13 | 0.0433468 | 966.161ms | 3862 | 320 | 335.094 | 2360.76 | 0.0293954 | 3.29577 | 16.506 | 1.99016 | 0.00167336 | 3.15575e-05 | 4.04583e-06 | 1(Win) | true |
| simdjson (ondemand) | 789.511 | 0.0555959 | 1203.29ms | 3862 | 80 | 538.126 | 4665.02 | 0.0654229 | 6.4598 | 27.537 | 3.4956 | 0.0171964 | 3.56033e-05 | 1.942e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1399.84 | 0.0662475 | 1384.03ms | 9578 | 30 | 560.599 | 6525.23 | 0.03935 | 3.63477 | 17.7129 | 3.01827 | 0.00364029 | 3.4802e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 1351.83 | 0.0263592 | 1417.09ms | 9578 | 4890 | 15512.4 | 6756.98 | 0.0285278 | 3.76672 | 19.2012 | 3.37482 | 0.00155072 | 3.4802e-05 | 1.53086e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1966.74 | 0.117185 | 1343.44ms | 9578 | 320 | 9478.7 | 4644.39 | 0.0100918 | 2.59166 | 13.427 | 2.05732 | 0.0024108 | 4.50251e-05 | 1.63134e-05 | 1(Win) | true |
| jsonifier (generic) | 1826.49 | 0.0263595 | 1370.42ms | 9578 | 4890 | 8497.61 | 5001 | 0.335473 | 2.78327 | 14.9424 | 2.41407 | 0.00111599 | 2.32511e-05 | 5.61529e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1383.5 | 0.0655088 | 1003.04ms | 3873 | 2560 | 7830.25 | 2669.73 | 0.0662519 | 3.74828 | 17.1015 | 2.10973 | 0.00134515 | 9.5513e-05 | 5.12361e-05 | 1(Win) | true |
| simdjson (ondemand) | 780.716 | 0.0354604 | 1205.97ms | 3873 | 2560 | 7205.02 | 4731.02 | 0.0291376 | 6.5236 | 27.5332 | 3.61296 | 0.0148448 | 4.35709e-05 | 9.27898e-06 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1427.15 | 0.0400689 | 988.725ms | 3873 | 4890 | 5258.74 | 2588.09 | 0.0849067 | 3.60368 | 16.6396 | 2.00697 | 0.00107244 | 5.41212e-05 | 1.89556e-05 | 1(Win) | true |
| simdjson (ondemand) | 795.741 | 0.0478658 | 1201.82ms | 3873 | 4890 | 24138.6 | 4641.68 | 0.0557416 | 6.4114 | 27.0599 | 3.50788 | 0.0167536 | 5.4438e-05 | 1.62628e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1488.27 | 0.0148341 | 6819.34ms | 94653 | 2560 | 207238 | 60653 | 0.0239014 | 3.3987 | 15.039 | 2.96697 | 0.00894809 | 1.41925e-05 | 9.42588e-06 | 1(Win) | true |
| simdjson (ondemand) | 1294.95 | 0.0359969 | 7741.01ms | 94653 | 640 | 402968 | 69707.6 | 0.0474436 | 3.91254 | 16.0343 | 3.13286 | 0.0121458 | 9.01319e-06 | 4.20945e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2158.05 | 0.038883 | 6210.55ms | 94653 | 640 | 169295 | 41828.5 | 0.0114666 | 2.34483 | 11.1324 | 2.08638 | 0.00608162 | 7.18083e-06 | 3.48312e-06 | 1(Win) | true |
| simdjson (ondemand) | 1772.75 | 0.0188166 | 7096.51ms | 94653 | 2560 | 235016 | 50920 | 0.0226295 | 2.85495 | 12.1615 | 2.25788 | 0.00869195 | 1.15347e-05 | 6.82179e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1879.8 | 0.0150286 | 7089.77ms | 124597 | 4890 | 441303 | 63211.6 | 0.0107976 | 2.6917 | 11.8013 | 2.25484 | 0.00734098 | 1.27643e-05 | 9.28802e-06 | 1(Win) | true |
| simdjson (ondemand) | 1664.21 | 0.0249343 | 4049.49ms | 124597 | 1280 | 405697 | 71400.1 | 0.0594282 | 3.04582 | 12.4729 | 2.39121 | 0.00926939 | 1.9375e-05 | 1.37819e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2669.92 | 0.022708 | 6498.59ms | 124597 | 4890 | 499445 | 44505.1 | 0.028954 | 1.89447 | 8.84678 | 1.58961 | 0.00457948 | 7.76327e-06 | 4.57754e-06 | 1(Win) | true |
| simdjson (ondemand) | 2234.51 | 0.0299256 | 7326.2ms | 124597 | 1280 | 324149 | 53177.1 | 0.0331066 | 2.25301 | 9.53787 | 1.73015 | 0.00694782 | 5.02244e-06 | 2.2949e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1130.62 | 0.0918662 | 4463.57ms | 94653 | 160 | 860735 | 79839.8 | 0.0352862 | 4.47643 | 20.8372 | 4.24049 | 0.0111585 | 5.57299e-05 | 4.72119e-05 | 1(Win) | true |
| simdjson (ondemand) | 703.735 | 0.0963151 | 7005.51ms | 94653 | 160 | 2.44208e+06 | 128270 | 0.129782 | 7.1837 | 34.8374 | 7.16431 | 0.0144708 | 2.07997e-05 | 1.16214e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1480.72 | 0.0234126 | 4140.71ms | 94653 | 1280 | 260756 | 60962.4 | 0.0140027 | 3.41538 | 16.9621 | 3.38108 | 0.0077387 | 1.52448e-05 | 8.7243e-06 | 1(Win) | true |
| simdjson (ondemand) | 823.682 | 0.0339917 | 6657.81ms | 94653 | 2560 | 3.55252e+06 | 109591 | 0.0696375 | 6.15122 | 31.0037 | 6.31504 | 0.0105938 | 1.69245e-05 | 8.77795e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1419.47 | 0.0323306 | 4666.13ms | 124597 | 640 | 468784 | 83710.9 | 0.158418 | 3.5688 | 16.2975 | 3.26386 | 0.00820189 | 3.17273e-05 | 2.65356e-05 | 1(Win) | true |
| simdjson (ondemand) | 929.949 | 0.0432712 | 7097.59ms | 124597 | 640 | 1.95648e+06 | 127776 | 0.0577815 | 5.43817 | 26.5056 | 5.39921 | 0.0105468 | 2.0629e-05 | 1.34183e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1821.63 | 0.0402548 | 4348.26ms | 124597 | 2560 | 1.76511e+06 | 65230.1 | 0.0319255 | 2.77954 | 13.3568 | 2.61329 | 0.00578376 | 2.10428e-05 | 1.52554e-05 | 1(Win) | true |
| simdjson (ondemand) | 1066.24 | 0.104519 | 6707.14ms | 124597 | 160 | 2.1708e+06 | 111443 | 0.0788525 | 4.74258 | 23.5938 | 4.75422 | 0.0083732 | 3.18025e-05 | 2.43284e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2408.25 | 0.0509157 | 4490.11ms | 94653 | 640 | 233104 | 37482.9 | 0.0489067 | 2.10773 | 9.43444 | 1.80148 | 0.00595813 | 3.30153e-06 | 1.20506e-06 | 1(Win) | true |
| simdjson (ondemand) | 1898.59 | 0.0197491 | 5501.06ms | 94653 | 2560 | 225706 | 47544.9 | 0.0166837 | 2.67309 | 10.6606 | 2.01224 | 0.00742563 | 1.00779e-05 | 5.50531e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3249.48 | 0.0165377 | 4018.82ms | 94653 | 4890 | 103205 | 27779.3 | 0.125023 | 1.55719 | 7.53005 | 1.35517 | 0.00362836 | 4.58245e-06 | 1.64631e-06 | 1(Win) | true |
| simdjson (ondemand) | 2352.98 | 0.028223 | 5070.56ms | 94653 | 1280 | 150055 | 38363.4 | 0.0951966 | 2.15482 | 8.77607 | 1.57222 | 0.00644619 | 5.95927e-06 | 2.62472e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2942.36 | 0.0139851 | 4797.3ms | 124597 | 4890 | 155978 | 40384.2 | 0.0164412 | 1.72163 | 7.58576 | 1.38369 | 0.0048966 | 1.62405e-05 | 1.17368e-05 | 1(Win) | true |
| simdjson (ondemand) | 2486.01 | 0.128478 | 5458.41ms | 124597 | 80 | 301686 | 47797.4 | 0.165555 | 2.02503 | 8.11352 | 1.48405 | 0.00584404 | 1.7356e-05 | 1.31424e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3896.09 | 0.0763582 | 4280.59ms | 124597 | 160 | 86773.8 | 30498.5 | 0.00801333 | 1.3009 | 6.13752 | 1.04471 | 0.00297424 | 5.71844e-06 | 1.90615e-06 | 1(Win) | true |
| simdjson (ondemand) | 3130.15 | 0.0646999 | 5047.66ms | 124597 | 320 | 193038 | 37961.5 | 0.0485536 | 1.62758 | 6.68864 | 1.15307 | 0.00465905 | 1.35186e-05 | 9.73137e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1821.26 | 0.0165087 | 5722.5ms | 94653 | 4890 | 327386 | 49563.5 | 0.0506124 | 2.77775 | 12.9023 | 2.54484 | 0.00751722 | 2.86786e-05 | 2.23807e-05 | 1(Win) | true |
| simdjson (ondemand) | 1610.52 | 0.0278698 | 6358.14ms | 94653 | 1280 | 312330 | 56049.1 | 0.0910103 | 3.15321 | 13.2119 | 2.4837 | 0.0083059 | 2.35482e-05 | 1.81007e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2238.61 | 0.022225 | 5271.85ms | 94653 | 2560 | 205606 | 40323.3 | 0.0872814 | 2.2576 | 11.018 | 2.11605 | 0.00619328 | 9.57032e-06 | 5.38975e-06 | 1(Win) | true |
| simdjson (ondemand) | 1924.84 | 0.0245202 | 5913.94ms | 94653 | 640 | 84626.6 | 46896.4 | 0.00731053 | 2.62758 | 11.3523 | 2.06478 | 0.00729403 | 6.81767e-06 | 3.35106e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2265.6 | 0.0228585 | 5996.42ms | 124597 | 1280 | 183973 | 52447.5 | 0.367759 | 2.23266 | 10.1781 | 1.95242 | 0.00544776 | 4.75282e-06 | 1.95631e-06 | 1(Win) | true |
| simdjson (ondemand) | 2136.56 | 0.0277381 | 6300.58ms | 124597 | 1280 | 304614 | 55615.1 | 0.0284584 | 2.36598 | 10.0823 | 1.84395 | 0.00616186 | 1.14808e-05 | 7.61831e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2753.41 | 0.0183376 | 5537.46ms | 124597 | 2560 | 160324 | 43155.6 | 0.020314 | 1.83844 | 8.75198 | 1.63018 | 0.00463757 | 6.43324e-06 | 3.59597e-06 | 1(Win) | true |
| simdjson (ondemand) | 2562.07 | 0.0230838 | 5868.46ms | 124597 | 2560 | 293420 | 46378.5 | 0.0127215 | 1.97584 | 8.66965 | 1.52635 | 0.00518124 | 8.80652e-06 | 5.32341e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 699.947 | 0.0835844 | 4295.23ms | 2090234 | 80 | 4.53316e+08 | 2.84793e+06 | 0.205973 | 7.23369 | 31.8961 | 6.22393 | 0.02328 | 0.103942 | 0.00165353 | 1(Win) | true |
| simdjson (ondemand) | 661.729 | 0.135129 | 4539.05ms | 2090234 | 40 | 6.62802e+08 | 3.01241e+06 | 0.15184 | 7.66293 | 31.8252 | 5.67656 | 0.0227554 | 0.104975 | 0.00267478 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 806.763 | 0.113771 | 4288.53ms | 2090234 | 30 | 2.37074e+08 | 2.47087e+06 | 0.00227996 | 6.26301 | 26.551 | 4.93272 | 0.0222839 | 0.0795811 | 0.000564068 | 1(Win) | true |
| simdjson (ondemand) | 756.716 | 0.129708 | 4540.12ms | 2090234 | 80 | 9.33997e+08 | 2.63428e+06 | 0.100245 | 6.67526 | 26.4971 | 4.38794 | 0.0216962 | 0.078534 | 0.00022211 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1633.19 | 0.259155 | 4625.11ms | 5212421 | 30 | 1.86658e+09 | 3.04371e+06 | 0.0139224 | 3.09801 | 13.5567 | 2.54184 | 0.0101809 | 0.060746 | 0.000416473 | 1(Win) | true |
| simdjson (ondemand) | 1552.89 | 0.115675 | 4824.84ms | 5212421 | 80 | 1.09689e+09 | 3.2011e+06 | 0.163977 | 3.25502 | 13.4997 | 2.31289 | 0.0101113 | 0.0607653 | 0.000536788 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1868.61 | 0.0898372 | 4574.58ms | 5212421 | 80 | 4.56926e+08 | 2.66024e+06 | 0.154659 | 2.69445 | 11.4088 | 2.02273 | 0.00982279 | 0.0505423 | 0.00035632 | 1(Win) | true |
| simdjson (ondemand) | 1758.87 | 0.311782 | 4837.47ms | 5212421 | 30 | 2.32936e+09 | 2.82622e+06 | 0.382713 | 2.86847 | 11.3558 | 1.79459 | 0.00971993 | 0.0508821 | 0.000165054 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 650.857 | 0.145154 | 4610.1ms | 2090234 | 30 | 5.92926e+08 | 3.06274e+06 | 0.317986 | 7.7457 | 35.407 | 6.86321 | 0.0232492 | 0.156214 | 0.000613695 | 1(Win) | true |
| simdjson (ondemand) | 609.996 | 0.109587 | 4967.73ms | 2090234 | 80 | 1.02599e+09 | 3.26789e+06 | 0.47959 | 8.26844 | 36.1293 | 6.63324 | 0.0227512 | 0.1804 | 0.000411993 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 735.695 | 0.543614 | 4649.42ms | 2090234 | 80 | 1.73566e+10 | 2.70955e+06 | 0.221303 | 6.84723 | 30.07 | 5.57245 | 0.0224073 | 0.130838 | 0.000242156 | 1(Win) | true |
| simdjson (ondemand) | 688.311 | 0.599399 | 4956.78ms | 2090234 | 40 | 1.20535e+10 | 2.89608e+06 | 0.41503 | 7.35864 | 30.8156 | 5.34739 | 0.021812 | 0.154626 | 0.000301928 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1482.5 | 0.791963 | 5054.74ms | 5212421 | 30 | 2.11553e+10 | 3.35308e+06 | 0.0555927 | 3.39873 | 14.8873 | 2.79503 | 0.0102607 | 0.101518 | 0.00124645 | 1(Win) | true |
| simdjson (ondemand) | 1372.75 | 0.592383 | 5457.07ms | 5212421 | 40 | 1.84061e+10 | 3.62116e+06 | 0.0184914 | 3.6733 | 15.2208 | 2.6955 | 0.0101424 | 0.120983 | 0.000368773 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1688.19 | 0.49194 | 5023.15ms | 5212421 | 80 | 1.67861e+10 | 2.94454e+06 | 0.0175875 | 2.98846 | 12.7558 | 2.27922 | 0.00989513 | 0.0907368 | 0.000209051 | 1(Win) | true |
| simdjson (ondemand) | 1533.1 | 1.15132 | 5450.23ms | 5212421 | 30 | 4.18075e+10 | 3.24242e+06 | 0.0189719 | 3.29859 | 13.0876 | 2.17935 | 0.00980279 | 0.110628 | 0.000186823 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7623.27 | 0.0438593 | 6906.04ms | 2090234 | 40 | 526127 | 261489 | 0.00200777 | 0.662787 | 3.24754 | 0.398848 | 0.00278321 | 0.0508068 | 4.13829e-06 | 1(Win) | true |
| simdjson (ondemand) | 7065.77 | 0.192523 | 7418.09ms | 2090234 | 320 | 9.44032e+07 | 282121 | 0.122649 | 0.713762 | 3.49769 | 0.418376 | 0.00275945 | 0.0500773 | 7.80415e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7684.23 | 0.0547426 | 6875.07ms | 2090234 | 80 | 1.61336e+06 | 259415 | 0.0427828 | 0.656933 | 3.24746 | 0.398831 | 0.00261203 | 0.0507492 | 3.37283e-06 | 1(Win) | true |
| simdjson (ondemand) | 7092.29 | 0.0825609 | 7446.95ms | 2090234 | 30 | 1.61542e+06 | 281066 | 0.028052 | 0.712318 | 3.4976 | 0.418359 | 0.00277551 | 0.0500248 | 1.62661e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10414.5 | 0.191917 | 6182.29ms | 5212421 | 30 | 2.5174e+07 | 477311 | 0.302505 | 0.482307 | 1.92457 | 0.183242 | 0.00200247 | 0.0394102 | 1.45806e-06 | 1(Win) | true |
| simdjson (ondemand) | 9896.28 | 0.695616 | 6595.97ms | 5212421 | 320 | 3.90682e+09 | 502305 | 0.25081 | 0.51234 | 2.13283 | 0.202773 | 0.00180383 | 0.039454 | 1.67089e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10467.5 | 0.11216 | 6156.97ms | 5212421 | 640 | 1.81573e+08 | 474896 | 0.148342 | 0.483329 | 1.92453 | 0.183235 | 0.00197096 | 0.0393761 | 1.95447e-06 | 1(Win) | true |
| simdjson (ondemand) | 9798.21 | 0.687358 | 6569.45ms | 5212421 | 640 | 7.78274e+09 | 507333 | 0.40573 | 0.516496 | 2.1328 | 0.202766 | 0.00185558 | 0.0394334 | 6.56785e-07 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5625.3 | 1.04188 | 4673.28ms | 2090234 | 640 | 8.7239e+09 | 354364 | 0.28271 | 0.901851 | 4.84726 | 0.718796 | 0.0026103 | 0.0761882 | 3.67632e-06 | 1(Win) | true |
| simdjson (ondemand) | 5423.18 | 0.253349 | 4806.54ms | 2090234 | 320 | 2.77504e+08 | 367571 | 0.169276 | 0.927909 | 4.93737 | 0.738305 | 0.00287149 | 0.0735334 | 1.70435e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5763.35 | 0.0466631 | 4626.26ms | 2090234 | 40 | 1.04195e+06 | 345876 | 0.0495679 | 0.876483 | 4.84718 | 0.718779 | 0.0026265 | 0.0761249 | 2.12895e-06 | 1(Win) | true |
| simdjson (ondemand) | 5480.92 | 0.0673865 | 4758.43ms | 2090234 | 30 | 1.80198e+06 | 363699 | 0.038068 | 0.921661 | 4.93729 | 0.738287 | 0.00279387 | 0.0734834 | 2.20071e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8372.32 | 0.177016 | 7705.1ms | 5212421 | 320 | 3.53479e+08 | 593737 | 0.887215 | 0.604915 | 2.63021 | 0.311545 | 0.00196963 | 0.0590598 | 2.78961e-06 | 1(Win) | true |
| simdjson (ondemand) | 7928.18 | 0.211866 | 8037ms | 5212421 | 640 | 1.12936e+09 | 626998 | 0.105391 | 0.636575 | 2.71016 | 0.331067 | 0.00185809 | 0.0591527 | 3.65053e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8376.05 | 0.0992392 | 7742.81ms | 5212421 | 640 | 2.21997e+08 | 593472 | 0.0944152 | 0.602973 | 2.63018 | 0.311538 | 0.00197786 | 0.0590378 | 2.89633e-06 | 1(Win) | true |
| simdjson (ondemand) | 7956.27 | 0.227727 | 8081.01ms | 5212421 | 160 | 3.23899e+08 | 624785 | 0.0118905 | 0.632253 | 2.71012 | 0.33106 | 0.00182989 | 0.0591235 | 3.25784e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1162.99 | 0.158271 | 5347.27ms | 500299 | 30 | 1.26484e+07 | 410256 | 0.0218366 | 4.33404 | 17.5537 | 3.2439 | 0.0158549 | 0.017097 | 2.56513e-05 | 1(Win) | true |
| simdjson (ondemand) | 1053.51 | 0.624315 | 5917.43ms | 500299 | 160 | 1.27911e+09 | 452887 | 0.0591114 | 4.78119 | 17.9179 | 3.03442 | 0.0235485 | 0.0194264 | 5.11319e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1278.05 | 0.192795 | 5351.63ms | 500299 | 80 | 4.14422e+07 | 373320 | 0.258988 | 3.94574 | 16.415 | 2.97036 | 0.0114486 | 0.0136914 | 1.20928e-05 | 1(Win) | true |
| simdjson (ondemand) | 1169.86 | 0.232787 | 5789.5ms | 500299 | 80 | 7.21103e+07 | 407846 | 0.0905482 | 4.31862 | 16.7751 | 2.759 | 0.0181826 | 0.016409 | 0.000166126 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2383.41 | 0.0899996 | 5988.15ms | 1151920 | 320 | 5.50651e+07 | 460917 | 0.166695 | 2.11537 | 8.40899 | 1.45675 | 0.00691125 | 0.0342374 | 3.22831e-05 | 1(Win) | true |
| simdjson (ondemand) | 2253.34 | 0.114641 | 6334.41ms | 1151920 | 320 | 9.99599e+07 | 487524 | 0.102545 | 2.24454 | 8.46757 | 1.35112 | 0.0103722 | 0.036772 | 2.36589e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2645.08 | 0.100941 | 5840.15ms | 1151920 | 320 | 5.62404e+07 | 415321 | 0.0213103 | 1.90956 | 7.91292 | 1.33726 | 0.00494944 | 0.0301931 | 2.56393e-05 | 1(Win) | true |
| simdjson (ondemand) | 2455.68 | 0.427656 | 6258.83ms | 1151920 | 40 | 1.46403e+08 | 447353 | 0.461695 | 2.05725 | 7.97234 | 1.23183 | 0.00837044 | 0.0316343 | 1.40852e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 648.073 | 0.242213 | 4715.82ms | 500299 | 30 | 9.53958e+07 | 736217 | 0.0160803 | 7.80882 | 36.5932 | 7.48707 | 0.0227294 | 0.0185321 | 4.81046e-05 | 1(Win) | true |
| simdjson (ondemand) | 400.237 | 0.059059 | 7612.97ms | 500299 | 160 | 7.93081e+07 | 1.1921e+06 | 0.6124 | 12.6297 | 66.1317 | 13.2269 | 0.0376237 | 0.0199497 | 0.000204003 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 687.522 | 0.0470899 | 4648.64ms | 500299 | 160 | 1.70869e+07 | 693973 | 0.0128579 | 7.34747 | 35.4543 | 7.21336 | 0.0163011 | 0.011797 | 3.52164e-05 | 1(Win) | true |
| simdjson (ondemand) | 415.361 | 0.281428 | 7510.78ms | 500299 | 160 | 1.67211e+09 | 1.14869e+06 | 0.0110045 | 12.1388 | 64.9837 | 12.9511 | 0.0315205 | 0.0124312 | 8.25756e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1405.29 | 0.0990226 | 5018.92ms | 1151920 | 320 | 1.91747e+08 | 781727 | 1.93182 | 3.59234 | 16.7846 | 3.32516 | 0.00956031 | 0.0381412 | 7.08572e-05 | 1(Win) | true |
| simdjson (ondemand) | 883.352 | 0.242092 | 7907.08ms | 1151920 | 40 | 3.62574e+08 | 1.24362e+06 | 0.52956 | 5.72349 | 29.381 | 5.77194 | 0.0160752 | 0.0779757 | 0.000150379 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1500.26 | 0.0790889 | 4881.5ms | 1151920 | 320 | 1.07322e+08 | 732242 | 0.0767531 | 3.37176 | 16.2841 | 3.20389 | 0.0068407 | 0.0324901 | 2.06991e-05 | 1(Win) | true |
| simdjson (ondemand) | 920.618 | 0.134626 | 7836.19ms | 1151920 | 80 | 2.0646e+08 | 1.19328e+06 | 0.222574 | 5.4867 | 28.885 | 5.65287 | 0.0137681 | 0.06824 | 4.20602e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5070.45 | 0.0158379 | 5188.73ms | 500299 | 2560 | 568592 | 94098.7 | 0.00418883 | 0.998263 | 5.38757 | 0.737625 | 0.000970648 | 4.23575e-06 | 2.56409e-06 | 1(Win) | true |
| simdjson (ondemand) | 4616.95 | 0.203687 | 5661.1ms | 500299 | 640 | 2.83566e+07 | 103342 | 0.0953948 | 1.09582 | 5.47303 | 0.733436 | 0.00118369 | 1.48848e-05 | 1.0578e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5124.72 | 0.0484881 | 5247.67ms | 500299 | 80 | 163034 | 93102.1 | 0.0486531 | 0.986562 | 5.35883 | 0.730875 | 0.00090286 | 2.79833e-06 | 1.82391e-06 | 1(Win) | true |
| simdjson (ondemand) | 4654.45 | 0.307451 | 5600.84ms | 500299 | 320 | 3.17851e+07 | 102509 | 0.358073 | 1.0872 | 5.44405 | 0.726668 | 0.00114745 | 1.57031e-05 | 1.26987e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8190.13 | 0.0819739 | 7281.99ms | 1151920 | 1280 | 1.54748e+07 | 134132 | 0.104077 | 0.617049 | 2.99955 | 0.353482 | 0.000933408 | 0.00550401 | 4.27818e-06 | 1(Win) | true |
| simdjson (ondemand) | 8105.22 | 0.417797 | 7487.72ms | 1151920 | 80 | 2.56528e+07 | 135537 | 0.476682 | 0.632096 | 3.06196 | 0.351604 | 0.00106315 | 0.00546564 | 1.54742e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8247.44 | 0.105861 | 7247.43ms | 1151920 | 1280 | 2.545e+07 | 133200 | 0.203467 | 0.614125 | 2.98706 | 0.350551 | 0.000887924 | 0.00480868 | 2.89395e-06 | 1(Win) | true |
| simdjson (ondemand) | 7938.41 | 0.503618 | 7529.75ms | 1151920 | 160 | 7.7714e+07 | 138385 | 0.311851 | 0.630698 | 3.04938 | 0.348664 | 0.0010539 | 0.00494783 | 6.3481e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2917.16 | 0.0733815 | 4356.71ms | 500299 | 160 | 2.30479e+06 | 163557 | 0.0514841 | 1.73779 | 9.81948 | 1.76877 | 0.00213868 | 2.87328e-06 | 7.87029e-07 | 1(Win) | true |
| simdjson (ondemand) | 2869.88 | 0.0374242 | 4441ms | 500299 | 160 | 619378 | 166251 | 0.0229374 | 1.76156 | 10.1008 | 1.75847 | 0.00253802 | 1.29423e-05 | 9.59426e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2958.37 | 0.0440751 | 4337.61ms | 500299 | 640 | 3.23385e+06 | 161279 | 0.152552 | 1.72681 | 9.79074 | 1.76202 | 0.00204972 | 7.16447e-06 | 4.42236e-06 | 1(Win) | true |
| simdjson (ondemand) | 2888.42 | 0.0247483 | 4416.25ms | 500299 | 640 | 1.06957e+06 | 165184 | 0.0409416 | 1.74912 | 10.0718 | 1.75169 | 0.00252034 | 2.88765e-05 | 2.40731e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5456.65 | 0.0622285 | 5418.62ms | 1151920 | 30 | 470862 | 201324 | 0.492337 | 0.926086 | 5.07187 | 0.796796 | 0.00172283 | 0.00555805 | 1.26456e-05 | 1(Win) | true |
| jsonifier (generic) | 5222.49 | 0.12882 | 5590.17ms | 1151920 | 320 | 2.34967e+07 | 210351 | 0.0705287 | 0.965194 | 4.93811 | 0.804701 | 0.00146177 | 0.00566389 | 1.72538e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5496.77 | 0.0938365 | 5361.33ms | 1151920 | 160 | 5.62721e+06 | 199855 | 0.209341 | 0.920735 | 5.05928 | 0.793849 | 0.00167272 | 0.00468788 | 1.1611e-06 | 1(Win) | true |
| jsonifier (generic) | 5280.28 | 0.215064 | 5560.93ms | 1151920 | 80 | 1.6016e+07 | 208049 | 0.0546088 | 0.958425 | 4.92565 | 0.801769 | 0.0014338 | 0.00498196 | 4.37964e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1404.73 | 0.0275295 | 4594.99ms | 56369 | 2560 | 284140 | 38269 | 0.00603086 | 3.59831 | 15.1847 | 3.02432 | 0.00812108 | 1.96182e-05 | 8.45434e-06 | 1(Win) | true |
| simdjson (ondemand) | 1291.14 | 0.218835 | 4888.2ms | 56369 | 320 | 2.65655e+06 | 41635.8 | 0.036971 | 3.89624 | 15.8725 | 2.86053 | 0.00934085 | 5.566e-05 | 2.62223e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1772.26 | 0.0516365 | 4108.19ms | 56369 | 4890 | 1.19963e+06 | 30332.8 | 0.0696929 | 2.8378 | 12.9525 | 2.53781 | 0.00461162 | 2.12448e-05 | 8.99347e-06 | 1(Win) | true |
| simdjson (ondemand) | 1563.31 | 0.024844 | 4548.04ms | 56369 | 4890 | 356897 | 34387.2 | 0.088194 | 3.23677 | 13.6889 | 2.38723 | 0.00937256 | 1.43301e-05 | 6.99815e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1987.64 | 0.0628903 | 4777.07ms | 83958 | 320 | 205383 | 40283.2 | 0.0310827 | 2.55904 | 10.7216 | 2.0443 | 0.00444199 | 3.43178e-05 | 2.51986e-05 | 1(Win) | true |
| simdjson (ondemand) | 1819.05 | 0.0313206 | 5173.67ms | 83958 | 1280 | 243280 | 44016.7 | 0.202368 | 2.7798 | 11.0734 | 1.9407 | 0.00925419 | 2.43984e-05 | 1.54653e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2427.55 | 0.0410192 | 4375.29ms | 83958 | 320 | 58575.1 | 32983.3 | 0.0710902 | 2.08418 | 9.22677 | 1.71892 | 0.00373408 | 1.64145e-05 | 1.10174e-05 | 1(Win) | true |
| simdjson (ondemand) | 2203.57 | 0.0195319 | 4756.95ms | 83958 | 4890 | 246301 | 36335.8 | 0.0416701 | 2.29759 | 9.60799 | 1.62281 | 0.00740608 | 7.9283e-06 | 3.38566e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 669.345 | 0.0524952 | 4472.24ms | 56369 | 30 | 53326.3 | 80313.8 | 0.0786286 | 7.55539 | 34.5481 | 7.15578 | 0.0137191 | 3.54805e-05 | 1.89229e-05 | 1(Win) | true |
| simdjson (ondemand) | 197.838 | 0.0310765 | 7120.75ms | 56369 | 1280 | 9.12717e+06 | 271726 | 0.186001 | 25.4886 | 138.941 | 30.5012 | 0.0330546 | 0.000147604 | 0.000107384 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 738.222 | 0.0192601 | 4275.94ms | 56369 | 2560 | 503573 | 72820.4 | 0.0593807 | 6.83941 | 32.3852 | 6.69081 | 0.0125749 | 2.63886e-05 | 1.54881e-05 | 1(Win) | true |
| simdjson (ondemand) | 203.961 | 0.0465555 | 7028.02ms | 56369 | 640 | 9.63627e+06 | 263569 | 0.0733349 | 24.8159 | 136.793 | 30.0417 | 0.0320684 | 8.507e-05 | 5.2306e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 921.304 | 0.0508338 | 4813.14ms | 83958 | 320 | 624559 | 86907.9 | 0.0249412 | 5.49027 | 24.6731 | 5.15893 | 0.00841619 | 1.68239e-05 | 5.73203e-06 | 1(Win) | true |
| simdjson (ondemand) | 290.201 | 0.0304193 | 7229.55ms | 83958 | 1280 | 9.0164e+06 | 275907 | 0.0183828 | 17.4045 | 93.5013 | 20.4466 | 0.0237359 | 5.45194e-05 | 3.9324e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1010.32 | 0.0672758 | 4600.57ms | 83958 | 320 | 909658 | 79251.1 | 0.0689978 | 5.00554 | 23.219 | 4.84585 | 0.00710746 | 1.84616e-05 | 7.36976e-06 | 1(Win) | true |
| simdjson (ondemand) | 299.752 | 0.0271992 | 7109.26ms | 83958 | 1280 | 6.75653e+06 | 267116 | 0.15633 | 16.8658 | 92.0689 | 20.1398 | 0.0206865 | 4.16782e-05 | 2.43891e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2339.86 | 0.0162039 | 3047.43ms | 56369 | 4890 | 67771.7 | 22974.7 | 0.0431416 | 2.16459 | 9.78864 | 1.76304 | 0.00355396 | 2.47239e-05 | 1.38439e-05 | 1(Win) | true |
| simdjson (ondemand) | 2186.85 | 0.0156113 | 3206.76ms | 56369 | 4890 | 72016.7 | 24582.3 | 0.035708 | 2.31363 | 10.1572 | 1.73138 | 0.00505596 | 1.21679e-05 | 5.53975e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2957.7 | 0.022831 | 2841.9ms | 56369 | 1280 | 22041 | 18175.5 | 0.0140236 | 1.7124 | 8.17293 | 1.41388 | 0.00234562 | 9.82643e-06 | 5.26664e-06 | 1(Win) | true |
| simdjson (ondemand) | 2780.07 | 0.0272377 | 2954.68ms | 56369 | 2560 | 71015.2 | 19336.8 | 0.240984 | 1.80823 | 8.54121 | 1.38325 | 0.00261761 | 8.28109e-06 | 3.40252e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3159.18 | 0.0349068 | 3284.89ms | 83958 | 640 | 50093 | 25344.8 | 0.042508 | 1.60188 | 7.08886 | 1.21547 | 0.00289496 | 3.9082e-06 | 1.2469e-06 | 1(Win) | true |
| simdjson (ondemand) | 3039.57 | 0.0364981 | 3383.64ms | 83958 | 2560 | 236636 | 26342.1 | 0.0691833 | 1.65828 | 7.24136 | 1.18346 | 0.00404212 | 6.00654e-06 | 2.27513e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3939.3 | 0.0202246 | 3075.16ms | 83958 | 2560 | 43260 | 20325.6 | 0.0766514 | 1.28617 | 5.99444 | 0.978192 | 0.00184645 | 5.98327e-06 | 2.6613e-06 | 1(Win) | true |
| simdjson (ondemand) | 3841.92 | 0.0466292 | 3156.58ms | 83958 | 40 | 3777.5 | 20840.8 | 0.0773524 | 1.31836 | 6.15547 | 0.949319 | 0.00224904 | 1.19107e-06 | 0 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1830.95 | 0.0378393 | 3688.93ms | 56369 | 2560 | 315977 | 29360.6 | 0.0186469 | 2.75839 | 13.3383 | 2.51 | 0.00416251 | 1.15797e-05 | 4.51822e-06 | 1(Win) | true |
| simdjson (ondemand) | 1386.83 | 0.0323842 | 4637.16ms | 56369 | 2560 | 403405 | 38763.1 | 0.0257941 | 3.65641 | 16.7575 | 3.21449 | 0.00788634 | 1.60286e-05 | 7.12382e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2174.72 | 0.0247203 | 3515.82ms | 56369 | 4890 | 182596 | 24719.4 | 0.0435573 | 2.32702 | 11.754 | 2.16967 | 0.00358191 | 9.07328e-06 | 3.84553e-06 | 1(Win) | true |
| simdjson (ondemand) | 1548.6 | 0.0343315 | 4515.31ms | 56369 | 2560 | 363602 | 34713.7 | 0.245467 | 3.25832 | 15.2073 | 2.8832 | 0.0075714 | 6.58329e-06 | 2.07201e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2372.85 | 0.0239598 | 4125.93ms | 83958 | 2560 | 167337 | 33743.7 | 0.0536931 | 2.13243 | 9.52743 | 1.72959 | 0.00526426 | 1.27668e-05 | 6.73235e-06 | 1(Win) | true |
| simdjson (ondemand) | 1987.23 | 0.0369443 | 4782.78ms | 83958 | 1280 | 283619 | 40291.6 | 0.0339595 | 2.54435 | 11.5481 | 2.15249 | 0.00552937 | 1.33996e-05 | 7.28601e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2766.98 | 0.0276428 | 3931.98ms | 83958 | 2560 | 163801 | 28937.2 | 0.0823305 | 1.82331 | 8.46845 | 1.50182 | 0.00413906 | 6.08563e-06 | 2.50776e-06 | 1(Win) | true |
| simdjson (ondemand) | 2239.08 | 0.0712079 | 4595.01ms | 83958 | 320 | 207487 | 35759.5 | 0.0576175 | 2.25885 | 10.5088 | 1.93035 | 0.0050287 | 4.13153e-06 | 1.07941e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1314.5 | 0.0757518 | 4622.05ms | 53331 | 320 | 274902 | 38692 | 0.00984636 | 3.84757 | 13.4904 | 2.69983 | 0.0123685 | 1.34186e-05 | 5.85963e-06 | 1(Win) | true |
| simdjson (ondemand) | 1008.92 | 0.0824178 | 5810.94ms | 53331 | 4890 | 8.44109e+06 | 50410.8 | 0.0297968 | 5.00938 | 18.244 | 3.64468 | 0.0204905 | 5.24946e-05 | 2.95527e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1631.03 | 0.185872 | 4401.36ms | 53331 | 80 | 268755 | 31183 | 0.00256543 | 3.10189 | 11.2656 | 2.19674 | 0.0100083 | 1.14849e-05 | 4.68771e-06 | 1(Win) | true |
| simdjson (ondemand) | 1195.89 | 0.0370402 | 5565.84ms | 53331 | 2560 | 635273 | 42529.2 | 0.219362 | 4.21641 | 16.0613 | 3.15131 | 0.0166402 | 1.9681e-05 | 1.02983e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1522.15 | 0.0399524 | 4842.93ms | 65103 | 2560 | 679849 | 40789.1 | 0.0258897 | 3.32752 | 11.4995 | 2.27297 | 0.00975371 | 8.84236e-05 | 6.73452e-05 | 1(Win) | true |
| simdjson (ondemand) | 1214.57 | 0.0312124 | 5870.33ms | 65103 | 2560 | 651704 | 51118.5 | 0.0155252 | 4.1656 | 15.1345 | 2.98558 | 0.0169453 | 4.09807e-05 | 2.36884e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1865.94 | 0.0926798 | 4615.87ms | 65103 | 160 | 152160 | 33273.9 | 0.0897044 | 2.71196 | 9.67366 | 1.85918 | 0.00775329 | 7.68014e-06 | 4.32008e-06 | 1(Win) | true |
| simdjson (ondemand) | 1438.19 | 0.097945 | 5646.91ms | 65103 | 4890 | 8.7426e+06 | 43170.2 | 0.0543664 | 3.51004 | 13.353 | 2.58351 | 0.0141388 | 2.40016e-05 | 1.24359e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 976.189 | 0.0602201 | 5979.85ms | 53331 | 640 | 630020 | 52101 | 0.19225 | 5.17589 | 19.1153 | 3.86458 | 0.0154931 | 6.33719e-05 | 4.08416e-05 | 1(Win) | true |
| simdjson (ondemand) | 416.189 | 0.0804064 | 6672.2ms | 53331 | 1280 | 1.23586e+07 | 122205 | 0.0047395 | 12.1512 | 40.6901 | 8.5817 | 0.0948867 | 0.000269499 | 0.000200927 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1154.26 | 0.0314274 | 5721.5ms | 53331 | 2560 | 490918 | 44063.3 | 0.0217907 | 4.38944 | 16.8173 | 3.34384 | 0.012879 | 2.69104e-05 | 1.4986e-05 | 1(Win) | true |
| simdjson (ondemand) | 454.042 | 0.21391 | 6551.78ms | 53331 | 160 | 9.1865e+06 | 112017 | 0.0812869 | 11.1304 | 38.4283 | 8.07005 | 0.0875377 | 2.95325e-05 | 1.6407e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1093.06 | 0.0876122 | 6584ms | 65103 | 160 | 396244 | 56801.1 | 0.140114 | 4.62241 | 16.3924 | 3.33404 | 0.0141006 | 2.65925e-05 | 1.72803e-05 | 1(Win) | true |
| simdjson (ondemand) | 523.458 | 0.152991 | 6506.36ms | 65103 | 320 | 1.05371e+07 | 118609 | 0.252432 | 9.63914 | 33.2391 | 6.96871 | 0.0695821 | 0.000200308 | 0.000119138 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1281.73 | 0.0197184 | 6195.97ms | 65103 | 4890 | 446128 | 48440.1 | 0.00733988 | 3.93546 | 14.5105 | 2.9081 | 0.0109052 | 2.87228e-05 | 1.66921e-05 | 1(Win) | true |
| simdjson (ondemand) | 570.618 | 0.0717229 | 6267.31ms | 65103 | 1280 | 7.79537e+06 | 108807 | 0.202497 | 8.84602 | 31.3897 | 6.55158 | 0.0639485 | 7.45093e-05 | 5.7241e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7973.09 | 0.0371662 | 1382.72ms | 53331 | 2560 | 14389.4 | 6379 | 0.152197 | 0.63961 | 2.91318 | 0.40123 | 0.00076767 | 1.53742e-05 | 8.10826e-06 | 1(Win) | true |
| simdjson (ondemand) | 6941.6 | 0.0260777 | 1479.04ms | 53331 | 4890 | 17852 | 7326.9 | 0.00726058 | 0.729064 | 3.15633 | 0.404793 | 0.000952223 | 4.43271e-06 | 1.39577e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8607.7 | 0.0273192 | 1367.54ms | 53331 | 4890 | 12741.8 | 5908.71 | 0.0139895 | 0.590711 | 2.75701 | 0.366916 | 0.000728648 | 7.28176e-06 | 2.96792e-06 | 1(Win) | true |
| simdjson (ondemand) | 7459.2 | 0.0490113 | 1436.95ms | 53331 | 1280 | 14294.8 | 6818.48 | 0.0731963 | 0.683005 | 3.00801 | 0.371548 | 0.000930319 | 6.76787e-06 | 2.40245e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8456.14 | 0.0225926 | 1478.7ms | 65103 | 4890 | 13455.4 | 7342.25 | 0.0330582 | 0.601199 | 2.72613 | 0.343932 | 0.000587202 | 4.77142e-06 | 1.99778e-06 | 1(Win) | true |
| simdjson (ondemand) | 7827.46 | 0.0379737 | 1540.95ms | 65103 | 2560 | 23225.6 | 7931.96 | 0.102417 | 0.647791 | 2.83068 | 0.343732 | 0.000721357 | 6.72012e-06 | 3.42006e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9065.12 | 0.0599869 | 1448.33ms | 65103 | 640 | 10803.1 | 6849 | 0.0370127 | 0.561542 | 2.59819 | 0.315823 | 0.000594971 | 1.81203e-05 | 9.67217e-06 | 1(Win) | true |
| simdjson (ondemand) | 8380.4 | 0.0319884 | 1496.78ms | 65103 | 2560 | 14378 | 7408.6 | 0.0176821 | 0.608697 | 2.70734 | 0.316146 | 0.000698281 | 3.39006e-06 | 9.18016e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5691.57 | 0.0367556 | 1633.66ms | 53331 | 2560 | 27617.4 | 8936.1 | 0.0510962 | 0.892696 | 4.24127 | 0.689918 | 0.00166608 | 7.15607e-06 | 2.68811e-06 | 1(Win) | true |
| simdjson (ondemand) | 4308.26 | 0.0249684 | 1925.07ms | 53331 | 4890 | 42486.3 | 11805.3 | 0.0170777 | 1.1806 | 5.62046 | 0.945098 | 0.00233231 | 1.05756e-05 | 5.376e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5997.88 | 0.201301 | 1642.7ms | 53331 | 30 | 8741.31 | 8479.73 | 0.0479805 | 0.847131 | 4.08543 | 0.655679 | 0.00147194 | 3.12514e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4485.72 | 0.0675006 | 1894.44ms | 53331 | 1280 | 74975.7 | 11338.3 | 0.0111887 | 1.13192 | 5.46999 | 0.911496 | 0.00222915 | 5.02463e-06 | 1.59675e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6086.8 | 0.0316362 | 1761.13ms | 65103 | 1280 | 13329.2 | 10200.3 | 0.0383344 | 0.833601 | 3.85392 | 0.589835 | 0.00134326 | 3.78007e-06 | 1.24802e-06 | 1(Win) | true |
| simdjson (ondemand) | 5000.2 | 0.0693241 | 1989.08ms | 65103 | 320 | 23710.8 | 12416.9 | 0.18368 | 1.01162 | 4.83336 | 0.782545 | 0.0017431 | 2.92805e-06 | 7.20013e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6447.07 | 0.0426049 | 1723.56ms | 65103 | 1280 | 21548 | 9630.28 | 0.0278422 | 0.792694 | 3.72573 | 0.56194 | 0.00128137 | 6.69612e-06 | 3.74407e-06 | 1(Win) | true |
| simdjson (ondemand) | 5207.67 | 0.0559925 | 1991.88ms | 65103 | 320 | 14260.2 | 11922.2 | 0.0787753 | 0.973916 | 4.71009 | 0.755019 | 0.00163947 | 2.11204e-06 | 9.60017e-08 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1307.13 | 0.124043 | 1664.09ms | 11812 | 320 | 36568.1 | 8617.97 | 0.554632 | 3.91592 | 17.9975 | 3.46969 | 0.00476449 | 2.7779e-05 | 1.45509e-05 | 1(Win) | true |
| simdjson (ondemand) | 1079.5 | 0.109431 | 1794.52ms | 11812 | 30 | 3912.03 | 10435.2 | 0.0332099 | 4.70251 | 19.6578 | 3.65361 | 0.00619709 | 8.46597e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1408.44 | 0.0403955 | 1630.77ms | 11812 | 1280 | 13361.2 | 7998.05 | 0.0573906 | 3.60903 | 16.9654 | 3.23544 | 0.00431209 | 2.89033e-05 | 1.0384e-05 | 1(Win) | true |
| simdjson (ondemand) | 1161.51 | 0.053018 | 1778.12ms | 11812 | 640 | 16921.1 | 9698.44 | 0.886622 | 4.37436 | 18.6189 | 3.42118 | 0.00464821 | 4.03456e-05 | 2.31491e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2422.58 | 0.0247824 | 1758.51ms | 25388 | 4890 | 29998.3 | 9994.26 | 0.00730609 | 2.09605 | 9.23436 | 1.67636 | 0.00321259 | 2.28197e-05 | 1.14702e-05 | 1(Win) | true |
| simdjson (ondemand) | 2178.68 | 0.0219079 | 1848.46ms | 25388 | 2560 | 15174.4 | 11113.1 | 0.117474 | 2.32824 | 9.77881 | 1.73068 | 0.00268315 | 1.46169e-05 | 5.26208e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2604.75 | 0.0971882 | 1727.71ms | 25388 | 80 | 6528.94 | 9295.29 | 0.123163 | 1.94915 | 8.7667 | 1.57055 | 0.00281235 | 1.28013e-05 | 4.92359e-06 | 1(Win) | true |
| simdjson (ondemand) | 2351.72 | 0.021641 | 1822.15ms | 25388 | 4890 | 24274.3 | 10295.4 | 0.0309459 | 2.1568 | 9.2565 | 1.61435 | 0.00201477 | 2.13537e-05 | 1.19052e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 756.346 | 0.0731522 | 2242ms | 11812 | 1280 | 151940 | 14893.7 | 0.0874718 | 6.69321 | 29.7414 | 5.99411 | 0.0151489 | 6.09814e-05 | 2.77128e-05 | 1(Win) | true |
| simdjson (ondemand) | 724.443 | 0.0276597 | 2313.22ms | 11812 | 2560 | 47356 | 15549.6 | 0.0798142 | 6.99767 | 32.3072 | 6.17347 | 0.0110017 | 0.000131884 | 8.28077e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 795.428 | 0.0748333 | 2216.96ms | 11812 | 160 | 17970.3 | 14161.9 | 0.0237376 | 6.371 | 28.7076 | 5.76109 | 0.0140911 | 1.69319e-05 | 4.23298e-06 | 1(Win) | true |
| simdjson (ondemand) | 755.166 | 0.0249592 | 2281.96ms | 11812 | 4890 | 67784.6 | 14917 | 0.0489388 | 6.70357 | 31.2367 | 5.9349 | 0.0111299 | 8.56984e-05 | 5.44488e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1499.03 | 0.0353815 | 2372.3ms | 25388 | 1280 | 41802.1 | 16151.7 | 0.226388 | 3.37873 | 15.5254 | 2.86988 | 0.00607395 | 1.50785e-05 | 5.60058e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1497.49 | 0.0461369 | 2369.04ms | 25388 | 1280 | 71226 | 16168.3 | 0.471333 | 3.37768 | 14.7938 | 2.8852 | 0.00687179 | 1.80019e-05 | 6.92379e-06 | 1(Tie) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1592.73 | 0.0279046 | 2318.87ms | 25388 | 4890 | 87990.5 | 15201.5 | 0.0508115 | 3.17783 | 14.2558 | 2.76457 | 0.00649405 | 2.77412e-05 | 1.57716e-05 | 1(Win) | true |
| simdjson (ondemand) | 1560.71 | 0.0306522 | 2348.31ms | 25388 | 4890 | 110571 | 15513.3 | 0.0762846 | 3.24448 | 15.0337 | 2.75997 | 0.00619434 | 1.68912e-05 | 5.87206e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2490.48 | 0.0770468 | 1195.38ms | 11812 | 320 | 3886.34 | 4523.15 | 0.00290182 | 2.04773 | 9.82941 | 1.74272 | 0.00340861 | 1.19053e-05 | 2.64561e-07 | 1(Win) | true |
| simdjson (ondemand) | 2226.85 | 0.0409192 | 1254.73ms | 11812 | 1280 | 5484.39 | 5058.62 | 0.105361 | 2.30548 | 10.5593 | 1.78496 | 0.00288835 | 2.83742e-05 | 1.66012e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2549.91 | 0.0966536 | 1196.97ms | 11812 | 30 | 546.961 | 4417.73 | 0.0452926 | 2.00176 | 9.63783 | 1.69683 | 0.00315498 | 1.97539e-05 | 1.41099e-05 | 1(Win) | true |
| simdjson (ondemand) | 2260.58 | 0.0880218 | 1254.35ms | 11812 | 320 | 6156.54 | 4983.14 | 0.00125421 | 2.23622 | 10.3512 | 1.73527 | 0.00258847 | 1.16407e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4456.25 | 0.0465186 | 1290.2ms | 25388 | 4890 | 31237.7 | 5433.24 | 0.00598098 | 1.14339 | 5.35698 | 0.879077 | 0.00166914 | 1.08742e-05 | 2.83534e-06 | 1(Win) | true |
| simdjson (ondemand) | 4233.46 | 0.132758 | 1321.19ms | 25388 | 30 | 1729.45 | 5719.17 | 0.0705729 | 1.20306 | 5.54719 | 0.861115 | 0.00133134 | 7.87774e-06 | 1.31296e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4563.69 | 0.0436916 | 1310.82ms | 25388 | 1280 | 6877.51 | 5305.33 | 0.039523 | 1.11566 | 5.26784 | 0.857728 | 0.00154419 | 5.87753e-06 | 7.38538e-07 | 1(Win) | true |
| simdjson (ondemand) | 4342.84 | 0.0488321 | 1310.07ms | 25388 | 640 | 4743.51 | 5575.12 | 0.0419169 | 1.17225 | 5.45037 | 0.837995 | 0.00120129 | 4.73895e-06 | 1.84634e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1863.57 | 0.036861 | 1342.06ms | 11812 | 2560 | 12709.5 | 6044.75 | 0.0637905 | 2.73715 | 13.003 | 2.26405 | 0.00570113 | 1.44847e-05 | 2.81097e-06 | 1(Win) | true |
| jsonifier (generic) | 1845.89 | 0.056932 | 1351.45ms | 11812 | 4890 | 59027.7 | 6102.63 | 0.0233485 | 2.75255 | 13.2628 | 2.47926 | 0.00656325 | 2.02906e-05 | 5.24578e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 1892.71 | 0.0367812 | 1340.44ms | 11812 | 1280 | 6133.95 | 5951.68 | 0.104889 | 2.68859 | 13.0501 | 2.42914 | 0.00637401 | 1.38233e-05 | 2.11649e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1891.25 | 0.123544 | 1335.68ms | 11812 | 30 | 1624.48 | 5956.27 | 0.0375096 | 2.69254 | 12.8164 | 2.21859 | 0.00560165 | 2.82199e-05 | 0 | 1(Tie) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3624.88 | 0.0723824 | 1406.52ms | 25388 | 2560 | 59838 | 6679.37 | 0.00857277 | 1.40392 | 6.68419 | 1.08402 | 0.00264637 | 1.01549e-05 | 3.35419e-06 | 1(Win) | true |
| jsonifier (generic) | 3293.92 | 0.1059 | 1478.41ms | 25388 | 30 | 1817.77 | 7350.47 | 0.074427 | 1.54359 | 6.97499 | 1.21798 | 0.00334673 | 7.87774e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3676.1 | 0.0206846 | 1409.86ms | 25388 | 4890 | 9075.86 | 6586.3 | 0.0642596 | 1.38336 | 6.59733 | 1.06286 | 0.00268465 | 7.62803e-06 | 1.41767e-06 | 1(Win) | true |
| jsonifier (generic) | 3353.56 | 0.0679293 | 1472.81ms | 25388 | 320 | 7696.79 | 7219.76 | 0.202289 | 1.52106 | 6.88601 | 1.19663 | 0.00315565 | 8.00083e-06 | 2.70797e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1537.48 | 0.0821629 | 7434.73ms | 108313 | 160 | 487541 | 67184.6 | 0.0421515 | 3.28245 | 14.5017 | 2.84728 | 0.00362855 | 2.94286e-06 | 4.61625e-07 | 1(Win) | true |
| simdjson (ondemand) | 1490.42 | 0.0444416 | 7696.46ms | 108313 | 1280 | 1.21432e+06 | 69306.2 | 0.121869 | 3.38392 | 15.5615 | 2.53254 | 0.00617308 | 1.99004e-05 | 1.19662e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1686.47 | 0.0584001 | 7071.16ms | 108313 | 320 | 409431 | 61249.4 | 0.00856057 | 2.99783 | 13.7775 | 2.68395 | 0.00353645 | 2.80437e-05 | 2.10039e-05 | 1(Win) | true |
| simdjson (ondemand) | 1622.22 | 0.118342 | 7310.21ms | 108313 | 160 | 908528 | 63675.4 | 0.00967706 | 3.11664 | 14.8458 | 2.36988 | 0.00553737 | 3.13905e-05 | 2.22734e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2409.78 | 0.0575488 | 4109.51ms | 183677 | 640 | 1.11997e+06 | 72690.5 | 0.0744806 | 2.09852 | 9.70492 | 1.51764 | 0.00385846 | 8.60886e-06 | 4.50009e-06 | 1(Win) | true |
| jsonifier (generic) | 2287.91 | 0.0344541 | 4325.78ms | 183677 | 1280 | 890682 | 76562.3 | 0.11003 | 2.21073 | 9.42917 | 1.77139 | 0.00224387 | 2.538e-05 | 1.87319e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2596.56 | 0.0312071 | 7686.65ms | 183677 | 2560 | 1.13464e+06 | 67461.5 | 0.13264 | 1.94603 | 9.28219 | 1.4215 | 0.00365393 | 1.04867e-05 | 7.28818e-06 | 1(Win) | true |
| jsonifier (generic) | 2453.44 | 0.0278767 | 4131.75ms | 183677 | 2560 | 1.0141e+06 | 71396.9 | 0.039339 | 2.05894 | 9.00131 | 1.67498 | 0.00203513 | 5.88457e-06 | 3.66217e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 629.329 | 0.0354883 | 4380.39ms | 108313 | 640 | 2.17148e+06 | 164136 | 0.0762221 | 8.04632 | 38.2569 | 7.54036 | 0.00993895 | 4.88024e-05 | 3.56028e-05 | 1(Win) | true |
| simdjson (ondemand) | 247.714 | 0.0583815 | 5394.04ms | 108313 | 160 | 9.48264e+06 | 416994 | 0.0140615 | 20.3954 | 99.2144 | 21.7689 | 0.0687244 | 6.02998e-05 | 4.13732e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 651.681 | 0.0380647 | 4281.21ms | 108313 | 640 | 2.32979e+06 | 158506 | 0.00902388 | 7.7783 | 37.5339 | 7.37694 | 0.00979603 | 6.84503e-05 | 5.64481e-05 | 1(Win) | true |
| simdjson (ondemand) | 252.108 | 0.0329731 | 5338.83ms | 108313 | 320 | 5.8406e+06 | 409726 | 0.180107 | 20.0481 | 98.4871 | 21.6044 | 0.0659324 | 2.31967e-05 | 1.06174e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 961.629 | 0.0782486 | 4838.18ms | 183677 | 640 | 1.30025e+07 | 182158 | 0.207844 | 5.26462 | 23.9855 | 4.71422 | 0.00606242 | 4.86077e-05 | 2.26621e-05 | 1(Win) | true |
| simdjson (ondemand) | 425.331 | 0.0314961 | 5335.46ms | 183677 | 640 | 1.07683e+07 | 411839 | 0.0336937 | 11.9 | 58.3025 | 12.7031 | 0.0358659 | 0.000166758 | 0.000140124 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 989.243 | 0.109898 | 4758.47ms | 183677 | 40 | 1.51477e+06 | 177073 | 0.165997 | 5.1223 | 23.5552 | 4.61708 | 0.00587961 | 5.29462e-05 | 4.57325e-05 | 1(Win) | true |
| simdjson (ondemand) | 432.142 | 0.0311339 | 5279.47ms | 183677 | 320 | 5.0965e+06 | 405348 | 0.0114112 | 11.7042 | 57.8736 | 12.606 | 0.0349221 | 6.11127e-05 | 5.0122e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4846.41 | 0.0696354 | 2880.05ms | 108313 | 320 | 70490.5 | 21313.8 | 0.0189321 | 1.04421 | 5.40909 | 0.846408 | 0.00102703 | 1.93306e-06 | 4.61625e-07 | 1(Win) | true |
| simdjson (ondemand) | 4391.89 | 0.0664973 | 3094.69ms | 108313 | 320 | 78273.8 | 23519.5 | 0.163625 | 1.15454 | 5.82512 | 0.809092 | 0.00111578 | 2.56779e-06 | 6.63586e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5142.86 | 0.0237666 | 2767.06ms | 108313 | 2560 | 58334.8 | 20085.2 | 0.0238572 | 0.988708 | 5.2248 | 0.797827 | 0.000744785 | 8.71317e-06 | 6.56013e-06 | 1(Win) | true |
| simdjson (ondemand) | 4601.6 | 0.016928 | 2996.92ms | 108313 | 4890 | 70609.8 | 22447.7 | 0.189022 | 1.10131 | 5.64105 | 0.760214 | 0.00104663 | 3.70244e-06 | 1.80496e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6691.05 | 0.0583984 | 3351.66ms | 183677 | 320 | 74795.2 | 26179.5 | 0.0125472 | 0.756751 | 3.77317 | 0.532892 | 0.000551597 | 2.79022e-06 | 1.66733e-06 | 1(Win) | true |
| simdjson (ondemand) | 6503.73 | 0.0228448 | 3431.86ms | 183677 | 2560 | 96917.2 | 26933.5 | 0.0723586 | 0.779761 | 3.94849 | 0.4988 | 0.000722087 | 4.44479e-06 | 2.82425e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7035.74 | 0.0184768 | 3249.02ms | 183677 | 4890 | 103479 | 24896.9 | 0.161268 | 0.723166 | 3.66449 | 0.504244 | 0.000437359 | 2.21336e-06 | 9.70852e-07 | 1(Win) | true |
| simdjson (ondemand) | 6823.66 | 0.0158713 | 3317.08ms | 183677 | 4890 | 81172.9 | 25670.7 | 0.00151842 | 0.743874 | 3.83995 | 0.469977 | 0.000623639 | 6.541e-06 | 5.07136e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3154.16 | 0.137245 | 4021.61ms | 108313 | 640 | 1.2929e+06 | 32748.9 | 0.187265 | 1.60536 | 8.20675 | 1.44035 | 0.00122657 | 7.34272e-06 | 4.15463e-06 | 1(Win) | true |
| simdjson (ondemand) | 2638.8 | 0.107175 | 4717.89ms | 108313 | 80 | 140808 | 39144.8 | 0.273234 | 1.95297 | 9.9661 | 1.72898 | 0.00194056 | 1.31563e-05 | 9.46331e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3233.22 | 0.0759174 | 3935.35ms | 108313 | 2560 | 1.50596e+06 | 31948.1 | 0.000562432 | 1.56653 | 8.02556 | 1.39412 | 0.0010224 | 5.35918e-06 | 2.95007e-06 | 1(Win) | true |
| simdjson (ondemand) | 2698.27 | 0.0312479 | 4589.02ms | 108313 | 2560 | 366331 | 38282.1 | 0.0460115 | 1.88145 | 9.78064 | 1.68008 | 0.0016588 | 9.31906e-06 | 6.65389e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4890.39 | 0.0232998 | 4335.34ms | 183677 | 2560 | 178307 | 35818.9 | 0.261356 | 1.03272 | 5.46342 | 0.895436 | 0.000826255 | 2.55841e-06 | 1.25262e-06 | 1(Win) | true |
| simdjson (ondemand) | 4052.98 | 0.0146853 | 5059.98ms | 183677 | 4890 | 196986 | 43219.5 | 0.0180164 | 1.25023 | 6.37891 | 1.03853 | 0.0011373 | 4.39333e-06 | 2.55294e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5084.38 | 0.0196181 | 4200.35ms | 183677 | 4890 | 223386 | 34452.2 | 0.0117858 | 0.998996 | 5.355 | 0.866772 | 0.000728707 | 3.02612e-06 | 1.72126e-06 | 1(Win) | true |
| simdjson (ondemand) | 4172.86 | 0.0974776 | 4969.12ms | 183677 | 160 | 267899 | 41977.9 | 0.240285 | 1.21666 | 6.26954 | 1.00969 | 0.000988352 | 4.11728e-06 | 2.48398e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 604.809 | 0.18311 | 4350.45ms | 1834197 | 80 | 2.24373e+09 | 2.8922e+06 | 0.0176431 | 8.34526 | 36.4657 | 7.3845 | 0.0382497 | 0.138996 | 0.00187708 | 1(Win) | true |
| simdjson (ondemand) | 565.788 | 0.506684 | 4637.44ms | 1834197 | 80 | 1.96313e+10 | 3.09166e+06 | 0.00018841 | 8.8823 | 37.0901 | 6.42301 | 0.0449259 | 0.139448 | 0.00554319 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 659.581 | 0.0697065 | 4349.53ms | 1834197 | 80 | 2.73396e+08 | 2.65203e+06 | 0.762145 | 7.67606 | 33.4721 | 6.68504 | 0.0371716 | 0.1184 | 0.00010279 | 1(Win) | true |
| simdjson (ondemand) | 613.727 | 0.463845 | 4643.53ms | 1834197 | 80 | 1.39823e+10 | 2.85017e+06 | 0.0256559 | 8.18109 | 34.0961 | 5.72318 | 0.0437094 | 0.118512 | 0.00125541 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2119.97 | 0.150167 | 4991.93ms | 7351818 | 30 | 7.39945e+08 | 3.30723e+06 | 0.0790763 | 2.37455 | 9.93068 | 1.8829 | 0.0102987 | 0.0587774 | 0.00229425 | 1(Win) | true |
| simdjson (ondemand) | 2047.55 | 1.45927 | 5155.77ms | 7351818 | 40 | 9.98739e+10 | 3.42421e+06 | 0.0517547 | 2.45748 | 10.167 | 1.64254 | 0.0109169 | 0.0587245 | 0.000237003 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2221.99 | 1.13327 | 5122.29ms | 7351818 | 80 | 1.02297e+11 | 3.15539e+06 | 0.0743794 | 2.27998 | 9.42027 | 1.46794 | 0.0106684 | 0.0535354 | 0.00115398 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2219.51 | 1.1182 | 5105.02ms | 7351818 | 80 | 9.98165e+10 | 3.15891e+06 | 1.25986 | 2.27835 | 9.1842 | 1.70847 | 0.0100242 | 0.0536036 | 0.00234406 | 1(Tie) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 381.993 | 1.32419 | 6849.68ms | 1834197 | 40 | 1.47076e+11 | 4.57921e+06 | 0.0668126 | 13.3581 | 63.7379 | 13.5147 | 0.0384508 | 0.343521 | 0.010095 | 1(Win) | true |
| simdjson (ondemand) | 259.856 | 0.722948 | 4798.77ms | 1834197 | 30 | 7.10496e+10 | 6.73152e+06 | 1.38122 | 19.481 | 107.022 | 21.2813 | 0.0481448 | 0.788649 | 0.00960958 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 413.069 | 0.133274 | 6805.12ms | 1834197 | 30 | 9.55558e+08 | 4.23471e+06 | 0.224007 | 12.2115 | 60.7439 | 12.8146 | 0.0372236 | 0.322416 | 0.000250591 | 1(Win) | true |
| simdjson (ondemand) | 264.717 | 1.07565 | 4798.81ms | 1834197 | 40 | 2.02082e+11 | 6.6079e+06 | 0.132533 | 19.0605 | 104.03 | 20.5819 | 0.0468239 | 0.767314 | 0.000225385 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1321.87 | 0.8103 | 8011.82ms | 7351818 | 80 | 1.47773e+11 | 5.30404e+06 | 0.323875 | 3.80878 | 16.7555 | 3.41522 | 0.0102886 | 0.186485 | 0.000840818 | 1(Win) | true |
| simdjson (ondemand) | 883.691 | 1.10373 | 5613.47ms | 7351818 | 40 | 3.06744e+11 | 7.93404e+06 | 0.204771 | 5.72473 | 27.6143 | 5.34953 | 0.0116392 | 0.43542 | 0.000484261 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1368.07 | 0.87655 | 8011.92ms | 7351818 | 80 | 1.61442e+11 | 5.12491e+06 | 0.939396 | 3.68544 | 16.0093 | 3.2409 | 0.00999268 | 0.181151 | 0.00303924 | 1(Win) | true |
| simdjson (ondemand) | 930.92 | 0.152622 | 5547.66ms | 7351818 | 40 | 5.2852e+09 | 7.53152e+06 | 1.19762 | 5.42531 | 26.8678 | 5.17501 | 0.0113658 | 0.430122 | 0.000828353 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4704.37 | 0.103547 | 4995.38ms | 1834197 | 80 | 1.18592e+07 | 371830 | 1.13668 | 1.08255 | 6.27608 | 0.838067 | 0.00107201 | 0.0754723 | 9.20703e-06 | 1(Win) | true |
| simdjson (ondemand) | 4323.33 | 0.0651331 | 5274.64ms | 1834197 | 80 | 5.55583e+06 | 404601 | 0.0921569 | 1.16775 | 6.33658 | 0.867798 | 0.00333639 | 0.0753331 | 2.15217e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4522.66 | 1.54641 | 4972.36ms | 1834197 | 320 | 1.14473e+10 | 386769 | 0.425929 | 1.11918 | 6.27588 | 0.83802 | 0.00110394 | 0.0754414 | 4.46892e-06 | 1(Win) | true |
| simdjson (ondemand) | 4370.34 | 0.113075 | 5277.28ms | 1834197 | 80 | 1.63864e+07 | 400249 | 0.457331 | 1.16536 | 6.33636 | 0.867749 | 0.00328113 | 0.0752921 | 6.81497e-07 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10152.6 | 0.119588 | 4431.56ms | 7351818 | 30 | 2.04613e+07 | 690586 | 0.49153 | 0.49809 | 2.34524 | 0.241959 | 0.00103184 | 0.0423799 | 2.74762e-06 | 1(Win) | true |
| simdjson (ondemand) | 9722.91 | 0.0791932 | 4611.83ms | 7351818 | 40 | 1.30446e+07 | 721105 | 0.0431237 | 0.51908 | 2.49471 | 0.256645 | 0.000809137 | 0.0424087 | 1.56764e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10063.2 | 0.190235 | 4475.36ms | 7351818 | 30 | 5.27009e+07 | 696718 | 0.921865 | 0.50214 | 2.34519 | 0.241947 | 0.0011123 | 0.0423749 | 4.92395e-06 | 1(Win) | true |
| simdjson (ondemand) | 9767.88 | 0.16863 | 4639.2ms | 7351818 | 320 | 4.68825e+08 | 717785 | 0.562085 | 0.518495 | 2.49465 | 0.256633 | 0.00075592 | 0.0424084 | 3.36184e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3209.36 | 0.695734 | 7280.84ms | 1834197 | 80 | 1.15035e+09 | 545039 | 0.204736 | 1.58012 | 8.73077 | 1.53929 | 0.00112716 | 0.1131 | 3.71416e-06 | 1(Win) | true |
| simdjson (ondemand) | 2188.02 | 0.779207 | 4981.64ms | 1834197 | 160 | 6.20893e+09 | 799457 | 2.48633 | 2.31385 | 12.647 | 2.2701 | 0.00332933 | 0.150493 | 3.08718e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3306.7 | 1.80165 | 7325.57ms | 1834197 | 30 | 2.72497e+09 | 528995 | 0.534441 | 1.55119 | 8.73057 | 1.53924 | 0.000915787 | 0.113052 | 3.18032e-06 | 1(Win) | true |
| simdjson (ondemand) | 2302.08 | 0.423299 | 4875.55ms | 1834197 | 80 | 8.27627e+08 | 759845 | 0.0264022 | 2.19058 | 12.6468 | 2.27005 | 0.00326255 | 0.150394 | 5.69732e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7523.76 | 1.51327 | 5848.47ms | 7351818 | 160 | 3.18182e+10 | 931880 | 0.411866 | 0.676094 | 2.95765 | 0.416912 | 0.00104471 | 0.0635412 | 2.68871e-05 | 1(Win) | true |
| simdjson (ondemand) | 6075.25 | 0.202962 | 7366.9ms | 7351818 | 160 | 8.77829e+08 | 1.15407e+06 | 0.240725 | 0.833182 | 4.06909 | 0.606504 | 0.000759642 | 0.0847875 | 3.69381e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7712.19 | 0.584785 | 5810.82ms | 7351818 | 320 | 9.04434e+09 | 909111 | 0.335918 | 0.660057 | 2.9576 | 0.4169 | 0.00102504 | 0.0634727 | 8.03798e-06 | 1(Win) | true |
| simdjson (ondemand) | 6099.06 | 0.146531 | 7305.31ms | 7351818 | 320 | 9.07969e+08 | 1.14956e+06 | 0.0718606 | 0.830537 | 4.06903 | 0.606492 | 0.000746532 | 0.0847701 | 6.11201e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1249.34 | 0.138118 | 4080.87ms | 409725 | 80 | 1.49284e+07 | 312760 | 0.0764309 | 4.04649 | 18.2113 | 3.60286 | 0.00972597 | 0.021907 | 4.26506e-05 | 1(Win) | true |
| simdjson (ondemand) | 971.422 | 0.377186 | 5213.42ms | 409725 | 40 | 9.20746e+07 | 402239 | 0.0768416 | 5.1897 | 20.1053 | 3.82434 | 0.0213803 | 0.0366057 | 0.000191958 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1563.05 | 0.192805 | 7699.23ms | 409725 | 1280 | 2.97361e+08 | 249988 | 0.052922 | 3.23303 | 15.2259 | 2.93458 | 0.00622116 | 0.0100467 | 3.79618e-05 | 1(Win) | true |
| simdjson (ondemand) | 1165.98 | 0.033172 | 4941.81ms | 409725 | 640 | 7.90907e+06 | 335120 | 0.0173979 | 4.33165 | 17.1235 | 3.15675 | 0.0167222 | 0.0150604 | 2.51503e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1921.7 | 0.202829 | 4406.99ms | 676745 | 160 | 7.42438e+07 | 335846 | 0.0153293 | 2.62975 | 11.6546 | 2.20932 | 0.00690371 | 0.0258483 | 8.05325e-06 | 1(Win) | true |
| simdjson (ondemand) | 1537.68 | 0.114703 | 5504.55ms | 676745 | 80 | 1.8542e+07 | 419720 | 0.144872 | 3.29097 | 12.6943 | 2.34103 | 0.0146477 | 0.0366585 | 2.35687e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2381.42 | 0.0439865 | 4192.66ms | 676745 | 640 | 9.0949e+06 | 271012 | 1.68444 | 2.12169 | 9.84477 | 1.80418 | 0.00458251 | 0.0117709 | 1.25994e-05 | 1(Win) | true |
| simdjson (ondemand) | 1827.24 | 0.0804688 | 5226.94ms | 676745 | 160 | 1.29251e+07 | 353207 | 0.471066 | 2.77224 | 10.8892 | 1.93696 | 0.0118986 | 0.0196018 | 4.5946e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 827.212 | 0.21921 | 6112.58ms | 409725 | 640 | 6.86204e+08 | 472363 | 0.00747859 | 6.1386 | 28.373 | 5.76457 | 0.0126213 | 0.0243834 | 0.00022991 | 1(Win) | true |
| simdjson (ondemand) | 447.844 | 0.107725 | 5587.36ms | 409725 | 30 | 2.65023e+07 | 872501 | 0.195715 | 11.2712 | 50.1934 | 10.408 | 0.0349202 | 0.0385548 | 7.89147e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 960.508 | 0.0452671 | 5836.79ms | 409725 | 320 | 1.08517e+07 | 406810 | 0.128018 | 5.26597 | 25.3965 | 5.09836 | 0.00921758 | 0.0102821 | 4.73183e-05 | 1(Win) | true |
| simdjson (ondemand) | 484.274 | 0.117163 | 5443.34ms | 409725 | 40 | 3.57474e+07 | 806866 | 0.0988636 | 10.4106 | 47.2296 | 9.74472 | 0.0300249 | 0.0150217 | 0.000158338 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1202.36 | 0.644084 | 6940.17ms | 676745 | 640 | 7.64978e+09 | 536774 | 0.0561255 | 4.19587 | 18.1128 | 3.65573 | 0.00997525 | 0.0262254 | 4.71489e-05 | 1(Win) | true |
| simdjson (ondemand) | 708.043 | 1.01444 | 5762.26ms | 676745 | 160 | 1.36805e+10 | 911519 | 0.5293 | 7.11502 | 30.7859 | 6.30046 | 0.0231729 | 0.0435673 | 9.02944e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1422.68 | 0.201531 | 6582.2ms | 676745 | 30 | 2.50751e+07 | 453648 | 0.200239 | 3.58862 | 16.3117 | 3.25251 | 0.00773019 | 0.0122386 | 0.000140427 | 1(Win) | true |
| simdjson (ondemand) | 783.024 | 0.121663 | 5553.3ms | 676745 | 40 | 4.02235e+07 | 824233 | 0.074307 | 6.46021 | 28.9925 | 5.89914 | 0.0206084 | 0.0209898 | 3.32474e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2463.92 | 0.059814 | 4244.13ms | 409725 | 160 | 1.43965e+06 | 158587 | 0.0896222 | 2.05058 | 9.49689 | 1.78309 | 0.00598806 | 0.00114781 | 0.000128821 | 1(Win) | true |
| simdjson (ondemand) | 2123.61 | 0.0344823 | 4896.32ms | 409725 | 640 | 2.57635e+06 | 184000 | 0.132987 | 2.38036 | 10.1973 | 1.77103 | 0.00691586 | 0.00152295 | 1.57728e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2863.99 | 0.0670516 | 4170.15ms | 409725 | 320 | 2.67801e+06 | 136434 | 0.169177 | 1.76786 | 8.4744 | 1.54825 | 0.00472009 | 0.000200371 | 4.56327e-05 | 1(Win) | true |
| simdjson (ondemand) | 2411.7 | 0.101606 | 4820.77ms | 409725 | 1280 | 3.46884e+07 | 162020 | 0.075386 | 2.09037 | 9.18345 | 1.53576 | 0.00588315 | 0.000637127 | 5.67835e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3504.01 | 0.0386005 | 4902.82ms | 676745 | 1280 | 6.47016e+06 | 184187 | 0.0234137 | 1.4488 | 6.34534 | 1.11756 | 0.00438253 | 0.00152027 | 0.000101745 | 1(Win) | true |
| simdjson (ondemand) | 3181.84 | 0.0972959 | 5383.21ms | 676745 | 80 | 3.11582e+06 | 202837 | 0.00507772 | 1.59325 | 6.67179 | 1.09501 | 0.00535283 | 0.00148084 | 5.6225e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4007.35 | 0.122546 | 4790.79ms | 676745 | 80 | 3.11619e+06 | 161053 | 0.149195 | 1.25489 | 5.72911 | 0.975932 | 0.00327356 | 0.00055211 | 2.45661e-05 | 1(Win) | true |
| simdjson (ondemand) | 3592.01 | 0.0430293 | 5261.56ms | 676745 | 640 | 3.82545e+06 | 179675 | 0.11346 | 1.41032 | 6.05591 | 0.95206 | 0.00436263 | 0.000543038 | 4.46069e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1937.27 | 0.043445 | 5349.86ms | 409725 | 640 | 4.91434e+06 | 201699 | 0.0852003 | 2.61072 | 12.4004 | 2.3875 | 0.0082636 | 0.000987145 | 2.01049e-05 | 1(Win) | true |
| simdjson (ondemand) | 1560.68 | 0.104125 | 6612.04ms | 409725 | 160 | 1.08741e+07 | 250368 | 0.046938 | 3.23845 | 14.3774 | 2.68371 | 0.00828804 | 0.00204476 | 0.000161816 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2191.88 | 0.0475415 | 5238.62ms | 409725 | 1280 | 9.19401e+06 | 178269 | 0.0229928 | 2.30125 | 11.3726 | 2.15094 | 0.00677547 | 0.000259244 | 1.9142e-05 | 1(Win) | true |
| simdjson (ondemand) | 1723.93 | 0.105469 | 6473.04ms | 409725 | 160 | 9.14358e+06 | 226659 | 0.107333 | 2.92017 | 13.36 | 2.44635 | 0.00683718 | 0.00056213 | 1.36067e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2670.81 | 0.0628529 | 6365.42ms | 676745 | 1280 | 2.95274e+07 | 241648 | 0.0835449 | 1.88875 | 8.21766 | 1.52238 | 0.00637284 | 0.00344522 | 8.45003e-05 | 1(Win) | true |
| simdjson (ondemand) | 2418.5 | 0.0613883 | 7020.45ms | 676745 | 640 | 1.71755e+07 | 266857 | 0.0641177 | 2.08863 | 9.21296 | 1.64881 | 0.00566702 | 0.00552562 | 9.42448e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2990.71 | 0.060484 | 6196.29ms | 676745 | 160 | 2.72586e+06 | 215800 | 0.303158 | 1.68433 | 7.60003 | 1.37949 | 0.0049985 | 0.0016073 | 1.58849e-05 | 1(Win) | true |
| simdjson (ondemand) | 2679.01 | 0.105708 | 6837.42ms | 676745 | 160 | 1.03762e+07 | 240908 | 0.0128489 | 1.88269 | 8.59656 | 1.50505 | 0.00458935 | 0.00353987 | 3.15296e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1881.57 | 0.026735 | 7326.49ms | 264040 | 2560 | 3.27718e+06 | 133829 | 0.196116 | 2.67762 | 10.004 | 1.88265 | 0.00788585 | 0.00079107 | 8.80149e-05 | 1(Win) | true |
| simdjson (ondemand) | 1776.93 | 0.0981548 | 7653.8ms | 264040 | 640 | 1.23824e+07 | 141710 | 0.0360284 | 2.81652 | 10.4016 | 1.80725 | 0.00898215 | 0.000727772 | 6.74969e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2373.32 | 0.0233606 | 6486.77ms | 264040 | 1280 | 786329 | 106099 | 0.005534 | 2.12929 | 8.58786 | 1.55811 | 0.00411224 | 6.25201e-05 | 3.2056e-05 | 1(Win) | true |
| simdjson (ondemand) | 2016.62 | 0.0737963 | 7571.04ms | 264040 | 1280 | 1.08685e+07 | 124866 | 0.48138 | 2.49138 | 8.9915 | 1.48503 | 0.011424 | 4.82408e-05 | 1.60635e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2356.04 | 0.0664644 | 7876.32ms | 360584 | 2560 | 2.40916e+07 | 145957 | 0.0875544 | 2.13414 | 7.96736 | 1.33966 | 0.00637475 | 0.00283438 | 1.80577e-05 | 1(Win) | true |
| jsonifier (generic) | 2333.6 | 0.0399345 | 7973.43ms | 360584 | 1280 | 4.43268e+06 | 147360 | 0.0853464 | 2.16588 | 7.80095 | 1.39884 | 0.00812823 | 0.000805778 | 2.57005e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2817.98 | 0.241276 | 7368.32ms | 360584 | 40 | 3.46757e+06 | 122030 | 0.0227249 | 1.79276 | 6.76673 | 1.16207 | 0.0061277 | 0.000164663 | 4.90177e-05 | 1(Win) | true |
| simdjson (ondemand) | 2728.28 | 0.0530258 | 7638.31ms | 360584 | 2560 | 1.14354e+07 | 126043 | 0.07628 | 1.83955 | 6.94119 | 1.10569 | 0.00650965 | 0.000172853 | 4.65662e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 687.471 | 0.0825298 | 4762.68ms | 264040 | 320 | 2.92416e+07 | 366282 | 0.0311316 | 7.31268 | 28.4715 | 5.24974 | 0.0239724 | 0.000901674 | 2.78367e-05 | 1(Win) | true |
| simdjson (ondemand) | 277.678 | 0.191521 | 5785.94ms | 264040 | 80 | 2.41313e+08 | 906836 | 0.028335 | 18.1023 | 72.7823 | 16.121 | 0.0855489 | 0.00253735 | 0.000401596 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 734.626 | 0.0502178 | 4641.66ms | 264040 | 640 | 1.89628e+07 | 342771 | 0.0660343 | 6.84806 | 27.0558 | 4.92549 | 0.0226017 | 6.67986e-05 | 1.45989e-05 | 1(Win) | true |
| simdjson (ondemand) | 286.875 | 0.139667 | 5691.56ms | 264040 | 160 | 2.40469e+08 | 877763 | 0.138879 | 17.5006 | 71.3718 | 15.7996 | 0.0809932 | 0.000756277 | 4.43115e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 883.083 | 0.0708678 | 5042.13ms | 360584 | 640 | 4.87403e+07 | 389408 | 0.160216 | 5.69747 | 21.5239 | 4.03221 | 0.0162476 | 0.00641298 | 3.99872e-05 | 1(Win) | true |
| simdjson (ondemand) | 394.253 | 0.119412 | 5566.82ms | 360584 | 320 | 3.47142e+08 | 872231 | 0.11444 | 12.7164 | 53.1082 | 11.7034 | 0.049001 | 0.00469139 | 0.000203368 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 958.361 | 0.0574961 | 4855.16ms | 360584 | 640 | 2.72403e+07 | 358821 | 0.246783 | 5.24445 | 20.4834 | 3.79413 | 0.0125229 | 0.00137115 | 3.43757e-05 | 1(Win) | true |
| simdjson (ondemand) | 407.696 | 0.110901 | 5467.07ms | 360584 | 320 | 2.80001e+08 | 843470 | 0.108054 | 12.3194 | 52.0739 | 11.4678 | 0.046018 | 0.000751602 | 0.000173755 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6907.84 | 0.0300111 | 4392.31ms | 264040 | 640 | 76594.9 | 36452.5 | 0.043064 | 0.733433 | 3.41513 | 0.472307 | 0.00125576 | 1.04624e-05 | 8.12495e-06 | 1(Win) | true |
| simdjson (ondemand) | 6210.01 | 0.0226591 | 4806.08ms | 264040 | 4890 | 412809 | 40548.8 | 0.283002 | 0.812768 | 3.78814 | 0.448836 | 0.00125479 | 1.38659e-05 | 1.08236e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7143.21 | 0.0363063 | 4334.51ms | 264040 | 640 | 104833 | 35251.4 | 0.0736461 | 0.710156 | 3.33132 | 0.453708 | 0.00124508 | 1.43267e-05 | 1.19596e-05 | 1(Win) | true |
| simdjson (ondemand) | 6368.69 | 0.168409 | 4738.02ms | 264040 | 30 | 133011 | 39538.4 | 0.152025 | 0.79385 | 3.70531 | 0.430244 | 0.00123454 | 6.56466e-05 | 5.54209e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7955.62 | 0.0231794 | 5077.05ms | 360584 | 1280 | 128493 | 43224.8 | 0.0679631 | 0.636702 | 2.92353 | 0.371032 | 0.000904113 | 5.77622e-06 | 4.02559e-06 | 1(Win) | true |
| simdjson (ondemand) | 7596.99 | 0.0271165 | 5287.24ms | 360584 | 320 | 48211.1 | 45265.3 | 0.18159 | 0.665725 | 3.12496 | 0.345433 | 0.00091292 | 2.40929e-06 | 1.34331e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8204.76 | 0.0323309 | 5000.95ms | 360584 | 640 | 117516 | 41912.2 | 0.0260335 | 0.61705 | 2.86217 | 0.357412 | 0.00088085 | 1.59897e-06 | 8.2765e-07 | 1(Win) | true |
| simdjson (ondemand) | 7794.89 | 0.0218856 | 5217.65ms | 360584 | 4890 | 455847 | 44116.1 | 0.085609 | 0.648836 | 3.06431 | 0.331819 | 0.000889807 | 9.89873e-06 | 7.80942e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4603.82 | 0.0125945 | 6230.8ms | 264040 | 4890 | 232046 | 54695.5 | 0.0751538 | 1.09798 | 5.26804 | 0.857571 | 0.00146159 | 9.20029e-06 | 6.41131e-06 | 1(Win) | true |
| simdjson (ondemand) | 4000.68 | 0.0435191 | 7055.15ms | 264040 | 2560 | 1.92076e+06 | 62941.4 | 0.038985 | 1.25463 | 6.18479 | 0.988803 | 0.00196203 | 1.04728e-05 | 7.35566e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4723.07 | 0.0137147 | 6146.7ms | 264040 | 4890 | 261441 | 53314.6 | 0.0253799 | 1.07197 | 5.18895 | 0.840312 | 0.00150737 | 8.24842e-06 | 5.33088e-06 | 1(Win) | true |
| simdjson (ondemand) | 4098.53 | 0.0599981 | 6951.79ms | 264040 | 1280 | 1.73928e+06 | 61438.7 | 0.0428558 | 1.22912 | 6.10617 | 0.971552 | 0.00192208 | 9.77302e-06 | 7.14262e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5682.99 | 0.0228327 | 6802.97ms | 360584 | 1280 | 244333 | 60510.4 | 0.0214872 | 0.888184 | 4.32699 | 0.662198 | 0.00138421 | 4.32025e-06 | 2.52412e-06 | 1(Win) | true |
| simdjson (ondemand) | 5017.83 | 0.0549093 | 7570.76ms | 360584 | 1280 | 1.81252e+06 | 68531.6 | 0.39388 | 0.997823 | 4.88982 | 0.743085 | 0.00140344 | 1.84531e-05 | 1.45684e-05 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5830.02 | 0.0318345 | 6717.22ms | 360584 | 640 | 225658 | 58984.3 | 0.00202645 | 0.868649 | 4.26879 | 0.649228 | 0.00135429 | 4.67991e-06 | 2.85128e-06 | 1(Win) | true |
| simdjson (ondemand) | 5124.48 | 0.0689138 | 7507.31ms | 360584 | 4890 | 1.04577e+07 | 67105.3 | 0.109548 | 0.980877 | 4.83225 | 0.730453 | 0.00137158 | 1.3369e-05 | 1.01539e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1834.63 | 0.0798469 | 879.925ms | 2632 | 2560 | 3055.15 | 1368.16 | 0.247894 | 2.84317 | 11 | 2.09688 | 0.000734648 | 0.000114279 | 4.57114e-05 | 1(Win) | true |
| simdjson (ondemand) | 1641.86 | 0.0587598 | 902.495ms | 2632 | 2560 | 2065.84 | 1528.79 | 0.0175312 | 3.15517 | 11.5255 | 2.13602 | 0.00214799 | 0.000111756 | 4.31884e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2366.43 | 0.0688179 | 849.881ms | 2632 | 320 | 170.505 | 1060.7 | 0.303123 | 2.22051 | 9.00798 | 1.63412 | 0.000759878 | 4.15559e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 2008.63 | 0.0448159 | 868.276ms | 2632 | 1280 | 401.465 | 1249.64 | 0.0128145 | 2.57454 | 9.72264 | 1.72264 | 0.000379939 | 5.72877e-05 | 2.10748e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2210.91 | 0.033122 | 905.237ms | 3370 | 4890 | 1133.6 | 1453.65 | 0.271121 | 2.33307 | 8.87217 | 1.62583 | 0.001736 | 4.20528e-05 | 6.25027e-06 | 1(Win) | true |
| simdjson (ondemand) | 2033.25 | 0.053984 | 916.902ms | 3370 | 2560 | 1864.02 | 1580.67 | 0.148426 | 2.53593 | 9.27804 | 1.67953 | 0.00267178 | 3.66283e-05 | 8.46161e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2798.45 | 0.189797 | 861.149ms | 3370 | 40 | 190.049 | 1148.45 | 0.260447 | 1.83533 | 7.39347 | 1.28071 | 0.00111276 | 2.22552e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2469.03 | 0.0504571 | 875.151ms | 3370 | 640 | 276.078 | 1301.68 | 0.167292 | 2.10355 | 7.87003 | 1.35668 | 0.001926 | 2.22552e-05 | 7.4184e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1250.95 | 0.0574647 | 937.145ms | 2632 | 2560 | 3403.58 | 2006.53 | 0.115135 | 4.10511 | 16.2435 | 3.25 | 0.00575682 | 7.01997e-05 | 1.30604e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.311 | 0.0279904 | 1085.05ms | 2632 | 4890 | 4691.2 | 3499.28 | 0.0113544 | 7.12833 | 30.1334 | 6.15464 | 0.0103466 | 0.000147392 | 7.63763e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1489.44 | 0.0724306 | 917.496ms | 2632 | 640 | 953.561 | 1685.24 | 0.0635513 | 3.47344 | 14.3552 | 2.81193 | 0.00477477 | 2.84954e-05 | 4.15559e-06 | 1(Win) | true |
| simdjson (ondemand) | 774.863 | 0.0413342 | 1068.45ms | 2632 | 640 | 1147.41 | 3239.37 | 0.00791111 | 6.6039 | 28.3393 | 5.74012 | 0.00995738 | 3.4432e-05 | 1.42477e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1502.94 | 0.035885 | 950.745ms | 3370 | 4890 | 2879.46 | 2138.4 | 0.0536957 | 3.42029 | 13.246 | 2.63472 | 0.00399131 | 5.64344e-05 | 1.32894e-05 | 1(Win) | true |
| simdjson (ondemand) | 924.014 | 0.0274937 | 1082.5ms | 3370 | 4890 | 4471.77 | 3478.17 | 0.0045646 | 5.53264 | 23.5804 | 4.76677 | 0.00837614 | 6.04395e-05 | 2.36661e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1748.37 | 0.0317503 | 924.178ms | 3370 | 2560 | 872.025 | 1838.21 | 0.0634935 | 2.95585 | 11.7674 | 2.28872 | 0.00352675 | 3.0485e-05 | 2.66599e-06 | 1(Win) | true |
| simdjson (ondemand) | 1001.66 | 0.120769 | 1068.97ms | 3370 | 320 | 4804.81 | 3208.55 | 0.112852 | 5.12337 | 22.1792 | 4.44303 | 0.00885942 | 2.04006e-05 | 2.7819e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3119.61 | 0.0332223 | 812.535ms | 2632 | 4890 | 349.415 | 804.611 | 0.0845351 | 1.69815 | 6.82371 | 1.21923 | 0.000406745 | 5.38441e-05 | 1.39855e-05 | 1(Win) | true |
| simdjson (ondemand) | 2394.05 | 0.0911647 | 833.967ms | 2632 | 1280 | 1169.42 | 1048.46 | 0.0333934 | 2.18919 | 7.84233 | 1.38374 | 0.00237996 | 1.39509e-05 | 8.90483e-07 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3831.84 | 0.0751685 | 798.367ms | 2632 | 1280 | 310.342 | 655.057 | 0.0120472 | 1.39308 | 5.80737 | 0.972264 | 0.00076255 | 6.26306e-05 | 1.81065e-05 | 1(Win) | true |
| simdjson (ondemand) | 2967.16 | 0.0541891 | 817.36ms | 2632 | 4890 | 1027.6 | 845.949 | 0.0524911 | 1.78473 | 6.77546 | 1.1326 | 0.000382192 | 2.29207e-05 | 4.04025e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3705.1 | 0.0527338 | 819.32ms | 3370 | 4890 | 1023.17 | 867.42 | 0.22545 | 1.42383 | 5.70238 | 0.972999 | 0.000347345 | 3.21009e-05 | 7.52459e-06 | 1(Win) | true |
| simdjson (ondemand) | 3087.4 | 0.128598 | 835.133ms | 3370 | 640 | 1146.88 | 1040.97 | 0.131465 | 1.69888 | 6.20742 | 1.05223 | 0.0019056 | 2.7819e-05 | 1.11276e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4539.72 | 0.0724161 | 806.63ms | 3370 | 2560 | 672.842 | 707.948 | 0.00215195 | 1.17626 | 4.90861 | 0.780119 | 0.000596949 | 2.57326e-05 | 7.18657e-06 | 1(Win) | true |
| simdjson (ondemand) | 3807.64 | 0.0867137 | 816.953ms | 3370 | 640 | 342.851 | 844.062 | 0.0222091 | 1.39008 | 5.37418 | 0.856083 | 0.000626855 | 3.01372e-05 | 9.73665e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2322.2 | 0.218723 | 842.221ms | 2632 | 30 | 167.679 | 1080.9 | 0.0493173 | 2.25993 | 9.27166 | 1.75152 | 0.00130446 | 5.06586e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2090.33 | 0.106326 | 851.376ms | 2632 | 2560 | 4173.15 | 1200.8 | 0.0638164 | 2.52339 | 9.64552 | 1.73138 | 0.00238991 | 0.000131791 | 0.000101812 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2790.89 | 0.0622386 | 826.013ms | 2632 | 640 | 200.534 | 899.381 | 0.239277 | 1.89608 | 8.26368 | 1.51216 | 0.00123658 | 4.39305e-05 | 7.12386e-06 | 1(Win) | true |
| simdjson (ondemand) | 2409.4 | 0.10875 | 839.698ms | 2632 | 640 | 821.471 | 1041.78 | 0.0179947 | 2.17511 | 8.58169 | 1.481 | 0.00228795 | 2.07779e-05 | 1.48414e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2793.15 | 0.0884583 | 848.973ms | 3370 | 160 | 165.756 | 1150.63 | 0.00814704 | 1.87458 | 7.60208 | 1.40297 | 0.00206231 | 3.7092e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2647.81 | 0.0504722 | 853.446ms | 3370 | 4890 | 1835.28 | 1213.79 | 0.00258735 | 1.97529 | 7.63472 | 1.32374 | 0.00239161 | 4.8121e-05 | 2.68822e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3354.29 | 0.051531 | 831.717ms | 3370 | 2560 | 624.073 | 958.14 | 0.152546 | 1.57511 | 6.81098 | 1.21217 | 0.000897047 | 4.06853e-05 | 1.12435e-05 | 1(Win) | true |
| simdjson (ondemand) | 3160.99 | 0.111152 | 835.621ms | 3370 | 1280 | 1634.78 | 1016.73 | 0.221956 | 1.66123 | 6.80386 | 1.12819 | 0.000899017 | 4.91469e-05 | 2.08642e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 747.973 | 0.0326709 | 1331.82ms | 4630 | 2560 | 9522.52 | 5903.31 | 0.0730527 | 6.80028 | 31.4238 | 6.01663 | 0.00293635 | 0.000167387 | 8.79117e-05 | 1(Win) | true |
| simdjson (ondemand) | 699.08 | 0.0350541 | 1368.4ms | 4630 | 2560 | 12549.5 | 6316.18 | 0.070003 | 7.27355 | 31.9713 | 5.61015 | 0.00319351 | 0.000173039 | 9.11177e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 872.805 | 0.06725 | 1336.73ms | 4630 | 640 | 7407.86 | 5058.99 | 0.0642215 | 5.84845 | 27.1447 | 5.02138 | 0.0022415 | 0.000133639 | 7.45815e-05 | 1(Win) | true |
| simdjson (ondemand) | 815.256 | 0.0951258 | 1362.9ms | 4630 | 320 | 8494.18 | 5416.11 | 0.01523 | 6.25094 | 27.5706 | 4.59179 | 0.0022037 | 7.69438e-05 | 2.22732e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1723.05 | 0.0662336 | 1378.59ms | 11579 | 640 | 11531.5 | 6408.76 | 0.0946378 | 2.95868 | 13.5431 | 2.49357 | 0.0012439 | 3.14416e-05 | 1.59232e-05 | 1(Win) | true |
| simdjson (ondemand) | 1666.6 | 0.0258853 | 1402.34ms | 11579 | 4890 | 14384.5 | 6625.82 | 0.00646962 | 3.0489 | 13.5132 | 2.27801 | 0.00118607 | 3.451e-05 | 1.52946e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1970.24 | 0.025855 | 1389.51ms | 11579 | 4890 | 10268.4 | 5604.68 | 0.0710938 | 2.5858 | 11.8185 | 2.09258 | 0.000785164 | 2.34894e-05 | 8.33608e-06 | 1(Win) | true |
| simdjson (ondemand) | 1916.91 | 0.0351206 | 1404.94ms | 11579 | 2560 | 10478.6 | 5760.62 | 0.0548134 | 2.6655 | 11.7723 | 1.87477 | 0.000905296 | 2.4762e-05 | 8.06282e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 669.625 | 0.0414205 | 1393.13ms | 4630 | 640 | 4774.3 | 6594.01 | 0.0237251 | 7.59482 | 35.6814 | 6.80367 | 0.00405913 | 6.41199e-05 | 3.47597e-05 | 1(Win) | true |
| simdjson (ondemand) | 633.986 | 0.0257982 | 1435.1ms | 4630 | 4890 | 15786.7 | 6964.69 | 0.119235 | 8.02179 | 36.3581 | 6.57992 | 0.00389816 | 0.000119873 | 5.74187e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 776.71 | 0.0384693 | 1402.13ms | 4630 | 1280 | 6121.84 | 5684.89 | 0.0690362 | 6.55517 | 31.2568 | 5.78013 | 0.00309075 | 7.69438e-05 | 2.39606e-05 | 1(Win) | true |
| simdjson (ondemand) | 728.868 | 0.0484786 | 1435.99ms | 4630 | 1280 | 11040.1 | 6058.04 | 0.038815 | 6.98508 | 31.9646 | 5.56393 | 0.00325273 | 5.58518e-05 | 1.48488e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1578.05 | 0.0803056 | 1439.84ms | 11579 | 640 | 20210.3 | 6997.63 | 0.0233169 | 3.22169 | 14.954 | 2.76414 | 0.00182658 | 4.41262e-05 | 1.83522e-05 | 1(Win) | true |
| simdjson (ondemand) | 1515.52 | 0.0892568 | 1467.14ms | 11579 | 2560 | 108278 | 7286.32 | 0.103656 | 3.34924 | 15.2321 | 2.65904 | 0.00160922 | 5.58662e-05 | 2.7562e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1819.07 | 0.0349722 | 1435.23ms | 11579 | 1280 | 5768.96 | 6070.45 | 0.0793662 | 2.79787 | 13.1851 | 2.35487 | 0.0010981 | 1.45063e-05 | 1.68678e-06 | 1(Win) | true |
| simdjson (ondemand) | 1723.33 | 0.0706274 | 1473.63ms | 11579 | 640 | 13107.9 | 6407.71 | 0.137244 | 2.9585 | 13.5261 | 2.26315 | 0.00130435 | 1.43039e-05 | 2.42897e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7385.03 | 0.110392 | 787.444ms | 4630 | 40 | 17.4256 | 597.9 | 0.00557476 | 0.730146 | 3.59158 | 0.459827 | 0.000431965 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6802.95 | 0.0602964 | 790.539ms | 4630 | 4890 | 748.96 | 649.058 | 0.0943798 | 0.788731 | 3.85443 | 0.478618 | 0.000431965 | 1.95224e-05 | 5.38853e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7542.02 | 0.112684 | 786.531ms | 4630 | 1280 | 557.088 | 585.455 | 0.0418836 | 0.715408 | 3.55616 | 0.452268 | 0.000432472 | 1.07991e-05 | 5.0621e-07 | 1(Win) | true |
| simdjson (ondemand) | 6959.24 | 0.0483417 | 788.866ms | 4630 | 4890 | 460.035 | 634.482 | 0.0292425 | 0.771851 | 3.81577 | 0.470627 | 0.000432363 | 1.16162e-05 | 6.18355e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12118.6 | 0.0312492 | 820.128ms | 11579 | 4890 | 396.483 | 911.213 | 0.0445644 | 0.434996 | 2.05743 | 0.207013 | 0.000177566 | 6.39335e-06 | 8.47737e-07 | 1(Win) | true |
| simdjson (ondemand) | 11168 | 0.0633731 | 833.162ms | 11579 | 1280 | 502.589 | 988.773 | 0.0924505 | 0.468269 | 2.26911 | 0.226358 | 0.000173199 | 5.87e-06 | 5.3977e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12339.2 | 0.0255784 | 819.419ms | 11579 | 1280 | 67.07 | 894.923 | 0.22907 | 0.428024 | 2.04327 | 0.20399 | 0.000172726 | 3.44104e-06 | 6.74713e-08 | 1(Win) | true |
| simdjson (ondemand) | 11182.4 | 0.0436772 | 825.476ms | 11579 | 320 | 59.5298 | 987.5 | 0.00253158 | 0.470242 | 2.25365 | 0.223163 | 0.00025909 | 9.71586e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4988.24 | 0.135241 | 814.993ms | 4630 | 1280 | 1834.4 | 885.184 | 0.0620954 | 1.055 | 5.25551 | 0.794601 | 0.000647948 | 1.51863e-05 | 1.8561e-06 | 1(Win) | true |
| simdjson (ondemand) | 4774.2 | 0.0941438 | 821.013ms | 4630 | 2560 | 1940.81 | 924.869 | 0.0382802 | 1.10319 | 5.32484 | 0.804752 | 0.000654529 | 1.06304e-05 | 1.68737e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5455.46 | 0.153341 | 806.499ms | 4630 | 1280 | 1971.64 | 809.374 | 0.15923 | 0.976744 | 5.2216 | 0.787042 | 0.000648623 | 2.73353e-05 | 9.11177e-06 | 1(Win) | true |
| simdjson (ondemand) | 4871.39 | 0.120591 | 817.64ms | 4630 | 1280 | 1529.31 | 906.418 | 0.0016376 | 1.08476 | 5.28596 | 0.79676 | 0.000653685 | 2.00796e-05 | 4.89336e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9094.73 | 0.113781 | 851.727ms | 11579 | 160 | 305.365 | 1214.17 | 0.112342 | 0.574357 | 2.78556 | 0.341221 | 0.000294175 | 9.71586e-06 | 5.93747e-06 | 1(Win) | true |
| simdjson (ondemand) | 8719.7 | 0.0560611 | 855.834ms | 11579 | 2560 | 1290.33 | 1266.4 | 0.202446 | 0.597653 | 2.85707 | 0.356767 | 0.000263475 | 7.25316e-06 | 7.42184e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9328.53 | 0.055666 | 850.111ms | 11579 | 1280 | 555.783 | 1183.74 | 0.303591 | 0.561142 | 2.77226 | 0.338199 | 0.000259292 | 9.98575e-06 | 3.64345e-06 | 1(Win) | true |
| simdjson (ondemand) | 8886.2 | 0.0875639 | 855.91ms | 11579 | 2560 | 3031.1 | 1242.67 | 0.379695 | 0.588301 | 2.84152 | 0.353571 | 0.000265634 | 1.20436e-05 | 4.48684e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1118.34 | 0.0952609 | 1175.83ms | 5092 | 320 | 5475.27 | 4342.23 | 0.057247 | 4.56316 | 17.6243 | 3.10212 | 0.00249656 | 2.57757e-05 | 1.22742e-06 | 1(Win) | true |
| jsonifier (generic) | 1106.37 | 0.140904 | 1172.07ms | 5092 | 160 | 6119.84 | 4389.23 | 0.011108 | 4.61042 | 17.9729 | 3.38895 | 0.00358774 | 3.19128e-05 | 3.68225e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1288.01 | 0.117528 | 1161.05ms | 5092 | 320 | 6283.09 | 3770.24 | 0.0660993 | 3.95137 | 15.9865 | 2.70679 | 0.00193748 | 2.70031e-05 | 1.22742e-06 | 1(Win) | true |
| jsonifier (generic) | 1260.41 | 0.0382149 | 1173.46ms | 5092 | 4890 | 10600.4 | 3852.79 | 0.0654946 | 4.06355 | 16.0695 | 2.94232 | 0.00390171 | 0.000109478 | 5.56629e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2059.34 | 0.168569 | 1201.66ms | 9739 | 40 | 2311.99 | 4510.1 | 0.023645 | 2.47745 | 9.80635 | 1.65099 | 0.00168909 | 6.1608e-05 | 3.3371e-05 | 1(Win) | true |
| jsonifier (generic) | 1951.24 | 0.10596 | 1222.64ms | 9739 | 80 | 2035.07 | 4759.96 | 0.18759 | 2.61421 | 10.1409 | 1.82204 | 0.00186878 | 1.92525e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2282.21 | 0.0308806 | 1187.11ms | 9739 | 4890 | 7723.21 | 4069.66 | 0.125165 | 2.22586 | 8.94979 | 1.44471 | 0.00155389 | 6.66685e-05 | 3.90142e-05 | 1(Win) | true |
| jsonifier (generic) | 2220.16 | 0.0922427 | 1210.97ms | 9739 | 320 | 4765.11 | 4183.4 | 0.160273 | 2.29975 | 9.15753 | 1.58858 | 0.00168459 | 5.6474e-05 | 2.8237e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 665.982 | 0.0288021 | 1471.38ms | 5092 | 4890 | 21567.9 | 7291.65 | 0.0346979 | 7.58871 | 32.0602 | 6.50944 | 0.00686393 | 0.0002198 | 0.000130603 | 1(Win) | true |
| simdjson (ondemand) | 416.998 | 0.0897944 | 1902.13ms | 5092 | 320 | 34991 | 11645.4 | 0.0602264 | 12.1192 | 55.882 | 11.1974 | 0.0140361 | 0.000122128 | 6.9349e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 722.525 | 0.0351933 | 1459.6ms | 5092 | 4890 | 27359 | 6721.03 | 0.408831 | 7.01527 | 30.1995 | 6.07699 | 0.00662357 | 0.000148796 | 8.37755e-05 | 1(Win) | true |
| simdjson (ondemand) | 440.395 | 0.0798141 | 1880.65ms | 5092 | 1280 | 99142.5 | 11026.7 | 0.0859662 | 11.5544 | 54.2176 | 10.7965 | 0.014797 | 0.000138851 | 6.44393e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1208.19 | 0.0426834 | 1513.06ms | 9739 | 640 | 6890.53 | 7687.37 | 0.0427629 | 4.20636 | 17.666 | 3.50692 | 0.00409629 | 2.32634e-05 | 8.34275e-06 | 1(Win) | true |
| simdjson (ondemand) | 790.052 | 0.0459828 | 1915.71ms | 9739 | 640 | 18702 | 11756 | 0.0187635 | 6.3996 | 29.7478 | 5.87001 | 0.0074005 | 1.26746e-05 | 6.4175e-07 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1318.98 | 0.0429419 | 1492.96ms | 9739 | 1280 | 11703.7 | 7041.65 | 0.102853 | 3.85795 | 16.7063 | 3.27475 | 0.00355233 | 7.50847e-05 | 4.57247e-05 | 1(Win) | true |
| simdjson (ondemand) | 829.608 | 0.0479184 | 1906.24ms | 9739 | 640 | 18419.1 | 11195.5 | 0.0536499 | 6.12431 | 28.8921 | 5.66403 | 0.00727327 | 3.80237e-05 | 1.84503e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4707.42 | 0.0986001 | 833.103ms | 5092 | 2560 | 2648.54 | 1031.59 | 0.0707845 | 1.11768 | 4.91163 | 0.683622 | 0.0013075 | 2.8921e-05 | 9.58918e-06 | 1(Win) | true |
| simdjson (ondemand) | 4455.45 | 0.0826753 | 838.633ms | 5092 | 2560 | 2078.67 | 1089.93 | 0.0747055 | 1.17924 | 5.18401 | 0.671446 | 0.00130681 | 3.42142e-05 | 1.56495e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4919.91 | 0.102808 | 829.51ms | 5092 | 1280 | 1318.02 | 987.032 | 0.00403656 | 1.07166 | 4.79694 | 0.65868 | 0.000997582 | 2.71566e-05 | 1.65701e-05 | 1(Win) | true |
| simdjson (ondemand) | 4583.14 | 0.039087 | 835.771ms | 5092 | 4890 | 838.735 | 1059.56 | 0.0185232 | 1.13979 | 5.06127 | 0.645915 | 0.00151876 | 1.249e-05 | 3.37351e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7225.24 | 0.0598472 | 856.661ms | 9739 | 4890 | 2894.15 | 1285.47 | 0.0195487 | 0.724237 | 3.29623 | 0.3793 | 0.000687263 | 1.81842e-05 | 9.47007e-06 | 1(Win) | true |
| jsonifier (generic) | 7188 | 0.0514982 | 861.345ms | 9739 | 4890 | 2165.24 | 1292.13 | 0.250515 | 0.722402 | 3.17117 | 0.393059 | 0.000754729 | 1.20318e-05 | 1.82682e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7584.31 | 0.0889512 | 850.517ms | 9739 | 2560 | 3037.67 | 1224.61 | 6.37958e-05 | 0.687294 | 3.08522 | 0.374885 | 0.000816586 | 1.17119e-05 | 4.61258e-06 | 1(Win) | true |
| simdjson (ondemand) | 7402.43 | 0.218862 | 851.234ms | 9739 | 640 | 4826.14 | 1254.7 | 0.336618 | 0.702144 | 3.23206 | 0.365951 | 0.00053554 | 9.14493e-06 | 1.44394e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 3088.89 | 0.0952374 | 886.096ms | 5092 | 1280 | 2869.44 | 1572.12 | 0.254783 | 1.68774 | 7.91359 | 1.37078 | 0.00242798 | 2.25538e-05 | 9.51247e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3076.41 | 0.20164 | 887.656ms | 5092 | 40 | 405.231 | 1578.5 | 0.362411 | 1.71598 | 8.24568 | 1.34701 | 0.00256284 | 9.81932e-06 | 0 | 1(Tie) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3159.59 | 0.0609422 | 882.583ms | 5092 | 4890 | 4290.04 | 1536.94 | 0.099073 | 1.64669 | 7.79851 | 1.34584 | 0.00246957 | 1.63455e-05 | 2.36949e-06 | 1(Win) | true |
| simdjson (ondemand) | 3101.3 | 0.0599461 | 884.084ms | 5092 | 2560 | 2255.54 | 1565.83 | 0.0264756 | 1.68291 | 8.12294 | 1.3209 | 0.00254512 | 2.89977e-05 | 1.41153e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5158.13 | 0.110116 | 907.32ms | 9739 | 1280 | 5032.13 | 1800.62 | 0.0876334 | 1.00167 | 4.89701 | 0.732519 | 0.00105897 | 9.94712e-06 | 2.16591e-06 | 1(Win) | true |
| jsonifier (generic) | 5066.41 | 0.0770767 | 910.202ms | 9739 | 2560 | 5111.1 | 1833.22 | 0.0808843 | 1.03218 | 4.74299 | 0.753876 | 0.00125274 | 1.40784e-05 | 6.37739e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5280.45 | 0.0798072 | 902.752ms | 9739 | 2560 | 5044.43 | 1758.91 | 0.175493 | 0.979251 | 4.83284 | 0.718863 | 0.00111492 | 8.34275e-06 | 1.04284e-06 | 1(Win) | true |
| jsonifier (generic) | 5126.52 | 0.0748646 | 909.182ms | 9739 | 2560 | 4709.52 | 1811.72 | 0.00360055 | 1.01338 | 4.68344 | 0.740836 | 0.00152127 | 1.04284e-05 | 3.0082e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1418.13 | 0.0464141 | 1062.13ms | 4857 | 4890 | 11238.6 | 3266.27 | 0.150228 | 3.61865 | 14.1874 | 2.78588 | 0.00138295 | 4.76617e-05 | 1.52416e-05 | 1(Win) | true |
| simdjson (ondemand) | 1342.79 | 0.213364 | 1077.82ms | 4857 | 40 | 2166.82 | 3449.53 | 0.122631 | 3.80925 | 14.7066 | 2.65987 | 0.000993412 | 4.11777e-05 | 5.14721e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1818.03 | 0.0494497 | 1011.65ms | 4857 | 4890 | 7761.9 | 2547.8 | 0.0649794 | 2.83493 | 11.294 | 2.15462 | 0.00223997 | 5.3051e-05 | 1.91994e-05 | 1(Win) | true |
| simdjson (ondemand) | 1700.01 | 0.0566772 | 1028.51ms | 4857 | 2560 | 6105.03 | 2724.68 | 0.248106 | 3.01884 | 12.0935 | 2.1048 | 0.000870602 | 7.23022e-05 | 2.83097e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1864.64 | 0.063307 | 1079.66ms | 6701 | 320 | 1506.41 | 3427.24 | 0.0888227 | 2.74427 | 10.7776 | 2.03522 | 0.00104975 | 2.09857e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1833.46 | 0.236919 | 1085.94ms | 6701 | 30 | 2045.77 | 3485.53 | 0.115583 | 2.84088 | 11.034 | 1.94464 | 0.00110431 | 3.48207e-05 | 1.49231e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2444.13 | 0.11632 | 1026.77ms | 6701 | 80 | 739.999 | 2614.66 | 0.0387389 | 2.13602 | 8.6805 | 1.57767 | 0.00167326 | 2.61155e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2272.08 | 0.0647282 | 1037.53ms | 6701 | 4890 | 16208 | 2812.66 | 0.0519712 | 2.26373 | 9.13998 | 1.54231 | 0.00120008 | 3.15553e-05 | 9.70462e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 699.293 | 0.0353906 | 1401.15ms | 4857 | 4890 | 26872.2 | 6623.83 | 0.0110446 | 7.29156 | 30.5545 | 6.08544 | 0.0078734 | 0.000101428 | 4.01672e-05 | 1(Win) | true |
| simdjson (ondemand) | 219.385 | 0.115527 | 2848.58ms | 4857 | 80 | 47596.9 | 21113.6 | 0.0186457 | 23.0645 | 115.446 | 25.3294 | 0.0337554 | 2.57361e-05 | 0 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 811.842 | 0.154282 | 1332.2ms | 4857 | 320 | 24795.6 | 5705.54 | 0.00454623 | 6.31487 | 27.6426 | 5.45378 | 0.0069616 | 2.38058e-05 | 1.9302e-06 | 1(Win) | true |
| simdjson (ondemand) | 227.634 | 0.0389987 | 2793.03ms | 4857 | 1280 | 80606.6 | 20348.4 | 0.0393188 | 22.2701 | 112.873 | 24.7855 | 0.0343718 | 8.54115e-05 | 3.58696e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 909.106 | 0.0490962 | 1435.87ms | 6701 | 1280 | 15246 | 7029.51 | 0.000300075 | 5.64539 | 23.2609 | 4.66393 | 0.00569831 | 6.87864e-05 | 3.38103e-05 | 1(Win) | true |
| simdjson (ondemand) | 304.223 | 0.0305668 | 2842.9ms | 6701 | 4890 | 201606 | 21006.2 | 0.163262 | 16.7272 | 83.8473 | 18.3311 | 0.024956 | 0.000106598 | 5.38332e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1039.56 | 0.104616 | 1374.28ms | 6701 | 30 | 1240.8 | 6147.4 | 0.0667394 | 4.98877 | 21.1542 | 4.20609 | 0.00491966 | 6.96413e-05 | 5.47182e-05 | 1(Win) | true |
| simdjson (ondemand) | 315.231 | 0.0449759 | 2782.27ms | 6701 | 1280 | 106412 | 20272.7 | 0.0635459 | 16.127 | 81.9821 | 17.9369 | 0.0248929 | 6.91361e-05 | 3.33439e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4053.91 | 0.248239 | 839.952ms | 4857 | 30 | 241.352 | 1142.6 | 0.331472 | 1.31419 | 5.45172 | 0.878526 | 0.000212751 | 0.000123533 | 0.00011667 | 1(Win) | true |
| simdjson (ondemand) | 3816.74 | 0.185752 | 845.157ms | 4857 | 40 | 203.272 | 1213.6 | 0.0164826 | 1.36802 | 5.76014 | 0.850937 | 0.000205888 | 5.66193e-05 | 4.63249e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4577.52 | 0.200659 | 829.862ms | 4857 | 40 | 164.913 | 1011.9 | 0.0263461 | 1.14834 | 4.89026 | 0.748198 | 0.000499279 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4398.79 | 0.0913485 | 832.244ms | 4857 | 2560 | 2368.71 | 1053.01 | 0.0845759 | 1.21015 | 5.18551 | 0.721227 | 0.000773368 | 2.51731e-05 | 9.40974e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4998.63 | 0.0540367 | 851.833ms | 6701 | 4890 | 2333.8 | 1278.46 | 0.145002 | 1.0583 | 4.54977 | 0.633488 | 0.000151612 | 2.34376e-05 | 1.02539e-05 | 1(Win) | true |
| jsonifier (generic) | 4931.12 | 0.163655 | 853.894ms | 6701 | 1280 | 5757.83 | 1295.97 | 0.0588619 | 1.06007 | 4.40472 | 0.671393 | 0.000152612 | 1.42236e-05 | 2.6815e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5700.84 | 0.124929 | 839.931ms | 6701 | 80 | 156.899 | 1120.99 | 0.108281 | 0.936011 | 4.13326 | 0.539472 | 0.000419713 | 1.67885e-05 | 3.73079e-06 | 1(Win) | true |
| jsonifier (generic) | 5596.22 | 0.0854251 | 842.439ms | 6701 | 1280 | 1218.07 | 1141.94 | 0.225053 | 0.950599 | 3.99776 | 0.576929 | 0.000659766 | 6.64546e-06 | 1.28246e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3098.83 | 0.0620053 | 877.627ms | 4857 | 4890 | 4200.57 | 1494.76 | 0.0580559 | 1.6891 | 7.39963 | 1.31089 | 0.000527479 | 2.90517e-05 | 1.06944e-05 | 1(Win) | true |
| simdjson (ondemand) | 2318.78 | 0.0453803 | 923.498ms | 4857 | 4890 | 4018.48 | 1997.6 | 0.053862 | 2.24055 | 10.0859 | 1.81739 | 0.00117116 | 2.94307e-05 | 1.67153e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3441.85 | 0.113937 | 868.576ms | 4857 | 80 | 188.094 | 1345.79 | 0.0677582 | 1.54329 | 6.85732 | 1.18756 | 0.00136401 | 3.34569e-05 | 7.72082e-06 | 1(Win) | true |
| simdjson (ondemand) | 2474.85 | 0.103972 | 915.606ms | 4857 | 40 | 151.471 | 1871.62 | 0.0191492 | 2.12557 | 9.53181 | 1.69549 | 0.00217727 | 0 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3720.73 | 0.105527 | 900.817ms | 6701 | 160 | 525.619 | 1717.56 | 0.0272842 | 1.41611 | 5.90434 | 1.00403 | 0.00107726 | 2.23847e-05 | 1.30578e-05 | 1(Win) | true |
| simdjson (ondemand) | 3057.38 | 0.047256 | 932.63ms | 6701 | 2560 | 2497.66 | 2090.21 | 0.0873694 | 1.70684 | 7.61603 | 1.31846 | 0.00147465 | 1.0318e-05 | 3.14785e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4029.34 | 0.0669631 | 891.943ms | 6701 | 4890 | 5515.59 | 1586.01 | 0.0393765 | 1.293 | 5.51157 | 0.91464 | 0.00120353 | 1.81885e-05 | 8.23977e-06 | 1(Win) | true |
| simdjson (ondemand) | 3302.06 | 0.325927 | 922.725ms | 6701 | 160 | 6366.08 | 1935.33 | 0.086796 | 1.58847 | 7.21445 | 1.23012 | 0.00177959 | 1.86539e-05 | 4.66348e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1339.79 | 0.105068 | 846.487ms | 1691 | 1280 | 2047.23 | 1203.67 | 0.0543613 | 3.96623 | 14.0225 | 2.79598 | 0.000601992 | 0.000146918 | 5.59026e-05 | 1(Win) | true |
| simdjson (ondemand) | 1214.11 | 0.0618399 | 860.91ms | 1691 | 2560 | 1727.21 | 1328.26 | 0.239547 | 4.32688 | 15.7215 | 3.07865 | 0.0005946 | 5.68266e-05 | 1.27051e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1563.78 | 0.0551135 | 842.163ms | 1691 | 640 | 206.743 | 1031.26 | 0.10268 | 3.4268 | 12.4228 | 2.40863 | 0.000591366 | 7.39208e-05 | 1.01641e-05 | 1(Win) | true |
| simdjson (ondemand) | 1391.73 | 0.114081 | 850.635ms | 1691 | 2560 | 4473.51 | 1158.75 | 0.214245 | 3.78374 | 14.1206 | 2.69012 | 0.000598989 | 8.59329e-05 | 3.28023e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1548.86 | 0.0672616 | 860.537ms | 2158 | 320 | 255.6 | 1328.73 | 0.0134038 | 3.36215 | 11.4588 | 2.27989 | 0.00139018 | 6.66126e-05 | 4.3443e-06 | 1(Win) | true |
| simdjson (ondemand) | 1503 | 0.0968584 | 863.408ms | 2158 | 160 | 281.436 | 1369.28 | 0.304431 | 3.48817 | 12.5922 | 2.43003 | 0.00125116 | 6.66126e-05 | 5.7924e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1809.28 | 0.0947487 | 847.998ms | 2158 | 160 | 185.849 | 1137.49 | 0.121027 | 2.89475 | 10.2053 | 1.97637 | 0.000463392 | 6.37164e-05 | 2.8962e-06 | 1(Win) | true |
| simdjson (ondemand) | 1732.33 | 0.0904919 | 848.56ms | 2158 | 320 | 369.84 | 1188.02 | 0.000789137 | 3.03714 | 11.3378 | 2.12558 | 0.000477873 | 6.80607e-05 | 2.60658e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 976.432 | 0.162587 | 895.216ms | 1691 | 1280 | 9229.69 | 1651.59 | 0.072085 | 5.35973 | 19.783 | 4.02484 | 0.000869493 | 0.000288291 | 0.000140449 | 1(Win) | true |
| simdjson (ondemand) | 722.43 | 0.222616 | 948.902ms | 1691 | 40 | 987.794 | 2232.28 | 0.0294829 | 7.12983 | 28.2637 | 5.6783 | 0.00133057 | 0.000162626 | 0.000103489 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1102.99 | 0.0848745 | 885.749ms | 1691 | 2560 | 3942.21 | 1462.09 | 0.20196 | 4.76303 | 18.1839 | 3.63572 | 0.00078818 | 0.000129361 | 4.45835e-05 | 1(Win) | true |
| simdjson (ondemand) | 801.974 | 0.17868 | 939.528ms | 1691 | 30 | 387.292 | 2010.87 | 0.205973 | 6.55577 | 26.6635 | 5.28918 | 0.00128129 | 7.88488e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1135.09 | 0.138847 | 910.662ms | 2158 | 1280 | 8112 | 1813.1 | 0.0668761 | 4.59882 | 16.3577 | 3.39991 | 0.00152666 | 9.01442e-05 | 2.9324e-05 | 1(Win) | true |
| simdjson (ondemand) | 929.232 | 0.111201 | 952.441ms | 2158 | 80 | 485.247 | 2214.76 | 0.269943 | 5.64355 | 22.2827 | 4.43513 | 0.0029715 | 5.7924e-05 | 2.31696e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1279.5 | 0.0487521 | 894.534ms | 2158 | 4890 | 3006.89 | 1608.46 | 0.0231456 | 4.11526 | 15.1038 | 3.095 | 0.00134441 | 9.53318e-05 | 3.15561e-05 | 1(Win) | true |
| simdjson (ondemand) | 1008.11 | 0.0930776 | 939.86ms | 2158 | 1280 | 4621.59 | 2041.48 | 0.00635302 | 5.17863 | 21.0287 | 4.13021 | 0.00257653 | 4.99595e-05 | 1.04987e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4546.9 | 0.184186 | 759.525ms | 1691 | 4890 | 2086.78 | 354.673 | 0.0413481 | 1.25457 | 4.43111 | 0.697221 | 0.000598622 | 5.80482e-05 | 2.66054e-05 | 1(Win) | true |
| simdjson (ondemand) | 4394.7 | 0.146763 | 758.183ms | 1691 | 160 | 46.4069 | 366.956 | 0.00510986 | 1.297 | 4.71437 | 0.69249 | 0.00118273 | 7.02247e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4952.9 | 0.253119 | 756.091ms | 1691 | 40 | 27.1692 | 325.6 | 0.0922226 | 1.14571 | 4.1094 | 0.623891 | 0.000665287 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4807.46 | 0.144346 | 756.163ms | 1691 | 4890 | 1146.5 | 335.45 | 0.196441 | 1.18656 | 4.37611 | 0.616795 | 0.00118068 | 3.43452e-05 | 1.59633e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5367.31 | 0.200508 | 760.006ms | 2158 | 80 | 47.2872 | 383.438 | 0.237414 | 1.0565 | 3.82994 | 0.564411 | 0.000781974 | 1.15848e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5289.88 | 0.335254 | 761.162ms | 2158 | 40 | 68.0487 | 389.05 | 0.490238 | 1.07254 | 3.9481 | 0.556534 | 0.000915199 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5897.99 | 0.220362 | 759.465ms | 2158 | 80 | 47.2998 | 348.938 | 0.0250824 | 0.971235 | 3.57785 | 0.506951 | 0.000822521 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5803.29 | 0.147188 | 757.564ms | 2158 | 320 | 87.1865 | 354.631 | 0.286447 | 0.985125 | 3.68304 | 0.49722 | 0.00092244 | 3.33063e-05 | 1.4481e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3290.56 | 0.0976354 | 775.627ms | 1691 | 160 | 36.6338 | 490.087 | 0.160428 | 1.68818 | 6.61798 | 1.1715 | 0.000927705 | 5.17445e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2776.74 | 0.372796 | 783.058ms | 1691 | 640 | 3000.11 | 580.775 | 0.215839 | 1.96149 | 8.09107 | 1.42815 | 0.00117349 | 2.77203e-05 | 1.47842e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3583.8 | 0.121559 | 770.041ms | 1691 | 80 | 23.9366 | 449.988 | 0.058369 | 1.55676 | 6.29923 | 1.09817 | 0.000591366 | 0.000110881 | 1.47842e-05 | 1(Win) | true |
| simdjson (ondemand) | 2994.59 | 0.319144 | 779.308ms | 1691 | 40 | 118.153 | 538.525 | 0.125185 | 1.81097 | 7.75281 | 1.35245 | 0.000665287 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3663.6 | 0.21709 | 782.502ms | 2158 | 80 | 118.975 | 561.75 | 0.532415 | 1.47723 | 5.62141 | 0.954588 | 0.000463392 | 5.21316e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3494.65 | 0.27939 | 785.095ms | 2158 | 4890 | 13238.1 | 588.909 | 0.0542264 | 1.55662 | 6.56719 | 1.12651 | 0.000562799 | 3.61048e-05 | 1.64888e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3942.49 | 0.101437 | 779.58ms | 2158 | 2560 | 717.788 | 522.013 | 0.003592 | 1.38856 | 5.37303 | 0.897591 | 0.00097783 | 3.51164e-05 | 1.19468e-05 | 1(Win) | true |
| simdjson (ondemand) | 3767.47 | 0.232329 | 781.624ms | 2158 | 80 | 128.854 | 546.263 | 0.0709869 | 1.46439 | 6.30213 | 1.06719 | 0.000503939 | 1.15848e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1285.6 | 0.0476706 | 1058.43ms | 4390 | 4890 | 11785 | 3256.57 | 0.182258 | 4.00706 | 17.8328 | 3.42096 | 0.00163925 | 0.000142124 | 6.3772e-05 | 1(Win) | true |
| simdjson (ondemand) | 1087.11 | 0.110835 | 1116.04ms | 4390 | 1280 | 23320.9 | 3851.15 | 0.106921 | 4.74113 | 19.6476 | 3.63781 | 0.00174829 | 0.00012137 | 6.35322e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1439.05 | 0.135701 | 1050.63ms | 4390 | 320 | 4987.57 | 2909.29 | 0.327825 | 3.62582 | 16.3879 | 3.09818 | 0.0018992 | 3.13212e-05 | 6.40661e-06 | 1(Win) | true |
| simdjson (ondemand) | 1194.95 | 0.168236 | 1104.75ms | 4390 | 2560 | 88942.6 | 3503.6 | 0.123876 | 4.31377 | 18.0986 | 3.2959 | 0.00168672 | 5.93501e-05 | 2.58044e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2396.31 | 0.101128 | 1103.92ms | 9378 | 40 | 569.82 | 3732.22 | 0.0104953 | 2.1349 | 9.22958 | 1.66827 | 0.00151152 | 2.66581e-05 | 2.66581e-06 | 1(Win) | true |
| simdjson (ondemand) | 2218.44 | 0.108756 | 1132.3ms | 9378 | 640 | 12303 | 4031.46 | 0.164681 | 2.33101 | 9.82459 | 1.73321 | 0.000374214 | 1.48286e-05 | 6.33131e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2622.74 | 0.0530486 | 1094.69ms | 9378 | 160 | 523.572 | 3410 | 0.0835079 | 1.95178 | 8.55321 | 1.51717 | 0.00143687 | 1.93271e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 2419.3 | 0.0473676 | 1118ms | 9378 | 2560 | 7849.54 | 3696.76 | 0.0267409 | 2.13345 | 9.09949 | 1.57315 | 0.000484553 | 2.67831e-05 | 8.66389e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 740.557 | 0.121073 | 1293.74ms | 4390 | 40 | 1873.98 | 5653.35 | 0.71169 | 6.87775 | 29.4697 | 5.92437 | 0.0110877 | 3.98633e-05 | 1.13895e-05 | 1(Win) | true |
| simdjson (ondemand) | 731.724 | 0.0321447 | 1309.59ms | 4390 | 4890 | 16541 | 5721.6 | 0.460326 | 7.01762 | 32.1169 | 6.12483 | 0.00736662 | 0.000141752 | 8.09611e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 792.545 | 0.0545765 | 1279.74ms | 4390 | 4890 | 40644.5 | 5282.51 | 0.0337387 | 6.44602 | 28.0253 | 5.60137 | 0.0106567 | 4.77475e-05 | 1.36022e-05 | 1(Win) | true |
| simdjson (ondemand) | 789.253 | 0.122328 | 1286.82ms | 4390 | 40 | 1684.25 | 5304.55 | 0.0436923 | 6.57837 | 30.5686 | 5.78269 | 0.00666287 | 5.69476e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1542.18 | 0.11658 | 1322.17ms | 9378 | 30 | 1371.25 | 5799.3 | 0.137184 | 3.36379 | 15.5279 | 2.86628 | 0.00353665 | 1.77721e-05 | 3.55442e-06 | 1(Win) | true |
| jsonifier (generic) | 1531.5 | 0.26582 | 1326.11ms | 9378 | 80 | 19277.5 | 5839.73 | 0.0825555 | 3.3874 | 14.7348 | 2.86564 | 0.00581814 | 2.53252e-05 | 3.99872e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1637.7 | 0.0740125 | 1304.83ms | 9378 | 80 | 1306.92 | 5461.04 | 0.127657 | 3.16939 | 14.8032 | 2.70612 | 0.00342824 | 1.59949e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 1597.92 | 0.0439417 | 1313.53ms | 9378 | 4890 | 29578.2 | 5596.99 | 0.233013 | 3.20314 | 14.0586 | 2.71444 | 0.00539798 | 5.21823e-05 | 2.63856e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2400.34 | 0.0581341 | 898.022ms | 4390 | 2560 | 2632 | 1744.18 | 0.159196 | 2.17531 | 9.94396 | 1.76014 | 0.00155004 | 1.8508e-05 | 2.3135e-06 | 1(Win) | true |
| simdjson (ondemand) | 2158.09 | 0.0472528 | 915.605ms | 4390 | 4890 | 4109.16 | 1939.97 | 0.12756 | 2.42087 | 10.6875 | 1.8 | 0.00108617 | 3.28875e-05 | 9.45633e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2470.53 | 0.0920203 | 898.3ms | 4390 | 1280 | 3112.63 | 1694.63 | 0.274595 | 2.11839 | 9.65034 | 1.69066 | 0.00214354 | 2.58044e-05 | 5.69476e-06 | 1(Win) | true |
| simdjson (ondemand) | 2240.95 | 0.0597502 | 917.143ms | 4390 | 4890 | 6093.27 | 1868.24 | 0.0793299 | 2.33967 | 10.3467 | 1.72005 | 0.0014736 | 3.34465e-05 | 1.05743e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4245.24 | 0.0711403 | 936.509ms | 9378 | 80 | 179.696 | 2106.72 | 0.103348 | 1.23878 | 5.43367 | 0.891022 | 0.00133824 | 2.66581e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4132.51 | 0.0645274 | 939.913ms | 9378 | 4890 | 9536.5 | 2164.19 | 0.363802 | 1.25724 | 5.65611 | 0.878013 | 0.000503702 | 1.61802e-05 | 6.14936e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4432.92 | 0.1243 | 932.451ms | 9378 | 30 | 188.671 | 2017.53 | 0.0231359 | 1.1859 | 5.29623 | 0.858499 | 0.000963247 | 1.06633e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4382.09 | 0.114895 | 929.695ms | 9378 | 30 | 164.961 | 2040.93 | 0.0702787 | 1.19838 | 5.46961 | 0.835253 | 0.000366105 | 1.42177e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1826.96 | 0.0434148 | 951.73ms | 4390 | 4890 | 4840.13 | 2291.59 | 0.108661 | 2.85748 | 13.2581 | 2.46765 | 0.00347262 | 2.16611e-05 | 5.49678e-06 | 1(Win) | true |
| simdjson (ondemand) | 1807.58 | 0.119197 | 953.272ms | 4390 | 1280 | 9756.08 | 2316.15 | 0.019905 | 2.87541 | 13.0749 | 2.26857 | 0.00442803 | 2.13554e-05 | 8.18622e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1895 | 0.161955 | 947.166ms | 4390 | 30 | 384.079 | 2209.3 | 0.0105603 | 2.76822 | 12.9651 | 2.39818 | 0.00335611 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1869.86 | 0.0742572 | 959.247ms | 4390 | 2560 | 7076.67 | 2239.01 | 0.122449 | 2.76929 | 12.7342 | 2.18861 | 0.00445811 | 6.96718e-05 | 3.40796e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3625.64 | 0.039416 | 971.509ms | 9378 | 4890 | 4622.8 | 2466.75 | 0.0591057 | 1.43414 | 6.71977 | 1.08669 | 0.00165952 | 1.13392e-05 | 3.24913e-06 | 1(Win) | true |
| jsonifier (generic) | 3223.59 | 0.0411102 | 1008.58ms | 9378 | 4890 | 6361.34 | 2774.41 | 0.110078 | 1.61143 | 7.04297 | 1.22734 | 0.00192983 | 1.77285e-05 | 2.85662e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3701.87 | 0.0917752 | 968.912ms | 9378 | 640 | 3146.36 | 2415.96 | 0.171681 | 1.40105 | 6.58723 | 1.0546 | 0.0017676 | 7.4976e-06 | 8.33067e-07 | 1(Win) | true |
| jsonifier (generic) | 3352.53 | 0.043263 | 996.533ms | 9378 | 4890 | 6513.53 | 2667.7 | 0.119244 | 1.54719 | 6.87887 | 1.18949 | 0.00160252 | 1.6878e-05 | 5.16808e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1498.95 | 0.0545397 | 1025.48ms | 4669 | 2560 | 6719.55 | 2970.56 | 0.0471202 | 3.44968 | 14.3727 | 2.82844 | 0.00171627 | 5.61382e-05 | 1.7402e-05 | 1(Win) | true |
| simdjson (ondemand) | 1480.82 | 0.0807399 | 1030.85ms | 4669 | 1280 | 7544.45 | 3006.91 | 0.19891 | 3.49461 | 15.4553 | 2.51767 | 0.00178789 | 2.35931e-05 | 3.01189e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1638.67 | 0.0411401 | 1002.91ms | 4669 | 4890 | 6110.9 | 2717.27 | 0.167037 | 3.1541 | 13.5719 | 2.64746 | 0.00156022 | 4.58579e-05 | 1.39282e-05 | 1(Win) | true |
| simdjson (ondemand) | 1607.67 | 0.0872484 | 1009.14ms | 4669 | 1280 | 7474.44 | 2769.66 | 0.0115382 | 3.21408 | 14.643 | 2.33476 | 0.00174472 | 5.00308e-05 | 2.02466e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2418.71 | 0.135254 | 1045ms | 7932 | 1280 | 22903.8 | 3127.51 | 0.043359 | 2.14914 | 9.6088 | 1.50555 | 0.000914413 | 4.09733e-05 | 1.71379e-05 | 1(Win) | true |
| jsonifier (generic) | 2179.27 | 0.0810938 | 1079.22ms | 7932 | 1280 | 10142.1 | 3471.13 | 0.0545724 | 2.35866 | 9.29526 | 1.74937 | 0.00141348 | 2.71842e-05 | 1.23117e-05 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2629.21 | 0.0726099 | 1022.94ms | 7932 | 320 | 1396.55 | 2877.12 | 0.0122721 | 1.97793 | 9.13742 | 1.39914 | 0.000651633 | 1.4577e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 2355.92 | 0.0579912 | 1055.2ms | 7932 | 2560 | 8875.81 | 3210.87 | 0.0313655 | 2.20598 | 8.8327 | 1.64435 | 0.0013012 | 6.61876e-05 | 2.24565e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 570.775 | 0.0386559 | 1511.16ms | 4669 | 2560 | 23280.3 | 7801.16 | 0.16347 | 8.95271 | 38.8981 | 7.64147 | 0.00822956 | 5.35447e-05 | 1.60634e-05 | 1(Win) | true |
| simdjson (ondemand) | 236.278 | 0.0730697 | 2608.31ms | 4669 | 320 | 60677.2 | 18845.2 | 0.292656 | 21.4293 | 103.868 | 22.8835 | 0.040366 | 0.000167327 | 0.000113782 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 600.096 | 0.0496786 | 1477.83ms | 4669 | 2560 | 34784.4 | 7419.99 | 0.204984 | 8.57027 | 38.0906 | 7.45599 | 0.00895342 | 3.4804e-05 | 8.19903e-06 | 1(Win) | true |
| simdjson (ondemand) | 241.514 | 0.0212361 | 2584.15ms | 4669 | 4890 | 74958.4 | 18436.6 | 0.0239853 | 21.1239 | 103.046 | 22.6974 | 0.0403437 | 6.07496e-05 | 2.42648e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 895.486 | 0.0987834 | 1569.55ms | 7932 | 320 | 22282.6 | 8447.42 | 0.00351426 | 5.6672 | 24.3227 | 4.77723 | 0.00537459 | 7.4461e-05 | 4.68829e-05 | 1(Win) | true |
| simdjson (ondemand) | 404.745 | 0.0304571 | 2603.84ms | 7932 | 2560 | 82950.7 | 18689.7 | 0.0447407 | 12.5879 | 60.8928 | 13.3297 | 0.027403 | 3.91511e-05 | 1.33951e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 936.834 | 0.130127 | 1554.22ms | 7932 | 160 | 17664.2 | 8074.58 | 0.117249 | 5.48732 | 23.8525 | 4.67007 | 0.0055377 | 6.53996e-05 | 3.073e-05 | 1(Win) | true |
| simdjson (ondemand) | 414.536 | 0.120557 | 2578.66ms | 7932 | 80 | 38718 | 18248.2 | 0.0145883 | 12.4467 | 60.4189 | 13.2225 | 0.027657 | 1.41831e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4641.5 | 0.0998213 | 820.343ms | 4669 | 80 | 73.3614 | 959.325 | 0.0260668 | 1.15434 | 4.99572 | 0.751767 | 0.00146177 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4481.95 | 0.0692117 | 819.104ms | 4669 | 160 | 75.6472 | 993.475 | 0.0327242 | 1.19458 | 5.34633 | 0.725637 | 0.00101467 | 8.0317e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5055.32 | 0.0374848 | 807.86ms | 4669 | 640 | 69.7655 | 880.795 | 0.0161457 | 1.06469 | 4.73849 | 0.692654 | 0.00121446 | 1.27169e-05 | 1.00396e-06 | 1(Win) | true |
| simdjson (ondemand) | 4804.08 | 0.107831 | 811.188ms | 4669 | 2560 | 2557.13 | 926.86 | 0.0194251 | 1.11557 | 5.07132 | 0.663954 | 0.000925402 | 9.11932e-06 | 3.51387e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6575.35 | 0.0400796 | 834.73ms | 7932 | 4890 | 1039.64 | 1150.44 | 0.061597 | 0.808838 | 3.64637 | 0.447554 | 0.000545073 | 7.91493e-06 | 1.21173e-06 | 1(Win) | true |
| jsonifier (generic) | 6519.82 | 0.0860014 | 836.01ms | 7932 | 80 | 79.6517 | 1160.24 | 0.0183186 | 0.822964 | 3.5232 | 0.477559 | 0.000505862 | 3.15179e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7135.86 | 0.103402 | 828.919ms | 7932 | 80 | 96.1209 | 1060.08 | 0.0424679 | 0.749828 | 3.37179 | 0.442763 | 0.000512166 | 2.04866e-05 | 7.87948e-06 | 1(Win) | true |
| simdjson (ondemand) | 7030.54 | 0.0781801 | 828.702ms | 7932 | 2560 | 1811.43 | 1075.96 | 0.0579091 | 0.758533 | 3.48449 | 0.411246 | 0.000515022 | 9.99708e-06 | 2.75782e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2908.11 | 0.142704 | 875.956ms | 4669 | 1280 | 6110.91 | 1531.13 | 0.579866 | 1.78996 | 7.5982 | 1.30221 | 0.0016132 | 1.72347e-05 | 4.3505e-06 | 1(Win) | true |
| simdjson (ondemand) | 2609.31 | 0.0364839 | 891.994ms | 4669 | 4890 | 1895.43 | 1706.47 | 0.279399 | 2.01022 | 9.37053 | 1.62969 | 0.00227625 | 1.27894e-05 | 4.64273e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3288.12 | 0.23782 | 861.617ms | 4669 | 640 | 6637.86 | 1354.18 | 0.118819 | 1.60652 | 7.34269 | 1.24374 | 0.00165988 | 1.60634e-05 | 3.34654e-07 | 1(Win) | true |
| simdjson (ondemand) | 2709.81 | 0.0688415 | 888.586ms | 4669 | 1280 | 1637.88 | 1643.18 | 0.200475 | 1.93206 | 9.09617 | 1.568 | 0.0022221 | 9.8723e-06 | 1.33862e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4683.93 | 0.0832742 | 887.42ms | 7932 | 320 | 578.784 | 1615 | 0.0846806 | 1.12682 | 5.09594 | 0.81291 | 0.000888805 | 1.61529e-05 | 4.72769e-06 | 1(Win) | true |
| simdjson (ondemand) | 4101.39 | 0.0655556 | 907.809ms | 7932 | 1280 | 1871.26 | 1844.39 | 0.00897914 | 1.26314 | 6.00076 | 0.975921 | 0.00117138 | 6.59906e-06 | 1.96987e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4943.19 | 0.103775 | 877.675ms | 7932 | 320 | 807.024 | 1530.3 | 0.0140884 | 1.05866 | 4.94516 | 0.778114 | 0.000816314 | 7.09153e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4235.23 | 0.0816221 | 901.259ms | 7932 | 2560 | 5440.86 | 1786.1 | 0.00299632 | 1.22847 | 5.83926 | 0.939612 | 0.00131666 | 1.06373e-05 | 3.25028e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 585.784 | 0.0428022 | 1489.11ms | 4604 | 2560 | 26349.2 | 7495.45 | 0.0126864 | 8.71723 | 36.1268 | 7.44092 | 0.00984199 | 0.000122855 | 6.77061e-05 | 1(Win) | true |
| simdjson (ondemand) | 575.455 | 0.0340865 | 1502.05ms | 4604 | 2560 | 17316.2 | 7629.99 | 0.0516066 | 8.84864 | 37.1649 | 6.79931 | 0.00886144 | 8.90869e-05 | 3.8774e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 658.381 | 0.0359943 | 1493.74ms | 4604 | 2560 | 14751 | 6668.96 | 0.372877 | 7.73702 | 32.0361 | 6.50978 | 0.0104312 | 3.9877e-05 | 7.63602e-06 | 1(Win) | true |
| simdjson (ondemand) | 655.015 | 0.0642884 | 1497.09ms | 4604 | 640 | 11885.4 | 6703.23 | 0.0106281 | 7.77397 | 32.9581 | 5.84405 | 0.0082727 | 4.34405e-05 | 1.15389e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2095.33 | 0.0365298 | 1570.94ms | 18245 | 2560 | 23556.8 | 8304.07 | 0.0462521 | 2.42227 | 10.3177 | 1.75922 | 0.00239907 | 2.19666e-05 | 9.12065e-06 | 1(Win) | true |
| jsonifier (generic) | 2067.92 | 0.0540438 | 1578.85ms | 18245 | 1280 | 26468.2 | 8414.17 | 0.0245341 | 2.47558 | 10.0144 | 1.92754 | 0.00264413 | 2.04251e-05 | 7.06529e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2347.37 | 0.0310011 | 1573.13ms | 18245 | 4890 | 25821.9 | 7412.47 | 0.171405 | 2.17219 | 9.28572 | 1.52458 | 0.00212414 | 1.92786e-05 | 9.00042e-06 | 1(Win) | true |
| jsonifier (generic) | 2295.64 | 0.0271728 | 1591.07ms | 18245 | 4890 | 20742.4 | 7579.49 | 0.0154992 | 2.21765 | 8.95648 | 1.68715 | 0.00240747 | 2.1341e-05 | 9.09009e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 320.857 | 0.0350691 | 2109.34ms | 4604 | 2560 | 58957.1 | 13684.3 | 0.0954728 | 15.8382 | 68.2194 | 14.6156 | 0.0198581 | 0.000225432 | 0.000133206 | 1(Win) | true |
| simdjson (ondemand) | 230.162 | 0.0403941 | 2648.52ms | 4604 | 1280 | 76006.3 | 19076.6 | 0.110464 | 21.9687 | 110.201 | 22.1649 | 0.0223618 | 0.000133546 | 7.02514e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 345.725 | 0.116432 | 2101.99ms | 4604 | 320 | 69968.4 | 12700 | 0.0383758 | 14.6839 | 63.9993 | 13.6565 | 0.0175459 | 0.00012014 | 4.95493e-05 | 1(Win) | true |
| simdjson (ondemand) | 243.302 | 0.027351 | 2630.86ms | 4604 | 2560 | 62368.3 | 18046.4 | 0.0322135 | 20.8927 | 105.976 | 21.2053 | 0.0215909 | 9.69775e-05 | 4.48828e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1181.62 | 0.0281431 | 2211.21ms | 18245 | 4890 | 83982.2 | 14725.4 | 0.0620694 | 4.29502 | 18.2389 | 3.77495 | 0.00551478 | 2.9243e-05 | 1.39546e-05 | 1(Win) | true |
| simdjson (ondemand) | 878.796 | 0.0228072 | 2717.65ms | 18245 | 4890 | 99716 | 19799.6 | 0.028647 | 5.79009 | 28.714 | 5.62971 | 0.00627314 | 4.05075e-05 | 2.30671e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1276.48 | 0.0333894 | 2197.65ms | 18245 | 4890 | 101293 | 13631 | 0.0329496 | 3.99398 | 17.17 | 3.53198 | 0.00509997 | 2.98931e-05 | 1.49633e-05 | 1(Win) | true |
| simdjson (ondemand) | 923.31 | 0.0819405 | 2708.81ms | 18245 | 2560 | 610421 | 18845 | 0.0207969 | 5.50341 | 27.6248 | 5.38279 | 0.00593448 | 2.93103e-05 | 1.35525e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4060.43 | 0.0629068 | 835.352ms | 4604 | 4890 | 2262.72 | 1081.34 | 0.506304 | 1.30519 | 6.66985 | 0.928106 | 0.000640725 | 1.86998e-05 | 3.46458e-06 | 1(Win) | true |
| simdjson (ondemand) | 4009.42 | 0.0885643 | 831.081ms | 4604 | 4890 | 4599.74 | 1095.1 | 0.0202615 | 1.32427 | 6.71829 | 0.946134 | 0.000436004 | 3.40684e-05 | 1.61236e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4194.13 | 0.0752161 | 829.754ms | 4604 | 4890 | 3031.92 | 1046.87 | 0.0169749 | 1.26299 | 6.58992 | 0.909427 | 0.000436004 | 1.91884e-05 | 3.24249e-06 | 1(Win) | true |
| simdjson (ondemand) | 4114.82 | 0.108472 | 828.322ms | 4604 | 40 | 53.5872 | 1067.05 | 0.0046856 | 1.29746 | 6.62945 | 0.926803 | 0.000434405 | 1.08601e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10211.2 | 0.120205 | 899.051ms | 18245 | 80 | 335.633 | 1703.99 | 0.0844322 | 0.515767 | 2.49444 | 0.271033 | 0.000232941 | 7.53631e-06 | 1.37024e-06 | 1(Win) | true |
| simdjson (ondemand) | 10153.3 | 0.0902362 | 898.106ms | 18245 | 40 | 95.6513 | 1713.7 | 0.0311121 | 0.519401 | 2.62269 | 0.279638 | 0.000153467 | 1.09619e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10329.6 | 0.0405063 | 895.154ms | 18245 | 1280 | 595.908 | 1684.46 | 0.289783 | 0.507411 | 2.47405 | 0.26632 | 0.00022078 | 9.89141e-06 | 2.7833e-06 | 1(Win) | true |
| simdjson (ondemand) | 10181.1 | 0.127758 | 898.305ms | 18245 | 40 | 190.692 | 1709.03 | 0.0862321 | 0.517738 | 2.60027 | 0.27476 | 0.000200055 | 1.37024e-05 | 1.37024e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2320.02 | 0.168475 | 911.852ms | 4604 | 640 | 6506.38 | 1892.54 | 0.31472 | 2.24351 | 9.35817 | 1.65769 | 0.00132765 | 1.01814e-05 | 1.01814e-06 | 1(Win) | true |
| simdjson (ondemand) | 2072.99 | 0.0973265 | 934.181ms | 4604 | 1280 | 5439.34 | 2118.05 | 0.052276 | 2.52106 | 13.0447 | 2.34774 | 0.00109212 | 1.56114e-05 | 3.56348e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2356.61 | 0.142564 | 906.525ms | 4604 | 1280 | 9030.82 | 1863.15 | 0.0157688 | 2.22081 | 9.27867 | 1.63901 | 0.001366 | 4.17436e-05 | 2.79988e-05 | 1(Win) | true |
| simdjson (ondemand) | 2102.13 | 0.0425325 | 932.81ms | 4604 | 160 | 126.274 | 2088.7 | 0.0388847 | 2.49668 | 12.9568 | 2.32841 | 0.00109687 | 1.90052e-05 | 4.07255e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7030.45 | 0.146411 | 974.166ms | 18245 | 1280 | 16806.5 | 2474.92 | 1.04451 | 0.740464 | 3.17227 | 0.457331 | 0.000393815 | 7.70759e-06 | 1.54152e-06 | 1(Win) | true |
| simdjson (ondemand) | 6251 | 0.0521205 | 1006.6ms | 18245 | 4890 | 10292.3 | 2783.52 | 0.0902067 | 0.827363 | 4.21902 | 0.633324 | 0.000336916 | 7.1286e-06 | 1.17689e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7248.21 | 0.300565 | 966.363ms | 18245 | 160 | 8329.58 | 2400.56 | 0.216666 | 0.710491 | 3.15221 | 0.452617 | 0.000344958 | 9.93423e-06 | 1.7128e-06 | 1(Win) | true |
| simdjson (ondemand) | 6341.17 | 0.0777155 | 1002.81ms | 18245 | 1280 | 5820.69 | 2743.94 | 0.101177 | 0.823253 | 4.19682 | 0.628446 | 0.000333653 | 1.8798e-05 | 8.43553e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1267.92 | 0.04675 | 1100.26ms | 4926 | 4890 | 14671.5 | 3705.11 | 0.0685343 | 4.07726 | 16.7286 | 3.26756 | 0.00432192 | 5.96559e-05 | 2.20025e-05 | 1(Win) | true |
| simdjson (ondemand) | 1079.16 | 0.0426446 | 1167.62ms | 4926 | 4890 | 16852.2 | 4353.21 | 0.0649265 | 4.75639 | 18.6159 | 3.47726 | 0.00359297 | 7.23593e-05 | 3.29623e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1575.01 | 0.0776636 | 1068.06ms | 4926 | 2560 | 13737.2 | 2982.72 | 0.0617371 | 3.28214 | 14.0126 | 2.67215 | 0.00437879 | 3.4257e-05 | 6.18529e-06 | 1(Win) | true |
| simdjson (ondemand) | 1289.85 | 0.12427 | 1133.02ms | 4926 | 640 | 13110.7 | 3642.12 | 0.0225607 | 3.99735 | 15.9062 | 2.88226 | 0.00344759 | 1.68113e-05 | 3.80633e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1972.2 | 0.21294 | 1128.45ms | 8150 | 160 | 11268.1 | 3941.01 | 0.022366 | 2.63311 | 10.7163 | 1.99865 | 0.0025161 | 2.3773e-05 | 3.06748e-06 | 1(Win) | true |
| simdjson (ondemand) | 1721.91 | 0.111818 | 1182.93ms | 8150 | 640 | 16304.1 | 4513.86 | 0.00879159 | 2.9839 | 11.7442 | 2.12442 | 0.00211541 | 1.39954e-05 | 1.15031e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2413.96 | 0.0772353 | 1094.28ms | 8150 | 1280 | 7915.84 | 3219.79 | 0.150737 | 2.14123 | 9.08368 | 1.64098 | 0.00245399 | 2.08972e-05 | 5.55982e-06 | 1(Win) | true |
| simdjson (ondemand) | 2043.49 | 0.040024 | 1149.87ms | 8150 | 4890 | 11332.4 | 3803.52 | 0.0829715 | 2.51967 | 10.1128 | 1.76736 | 0.00241053 | 1.78403e-05 | 3.66342e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 824.337 | 0.0557491 | 1304.46ms | 4926 | 2560 | 25840.1 | 5698.88 | 0.0183458 | 6.20872 | 26.9434 | 5.44011 | 0.00778268 | 0.000111415 | 3.63188e-05 | 1(Win) | true |
| simdjson (ondemand) | 457.942 | 0.0654537 | 1762.48ms | 4926 | 640 | 28854.6 | 10258.5 | 0.111946 | 11.091 | 48.8402 | 10.0867 | 0.0209038 | 3.48914e-05 | 8.24706e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 945.209 | 0.0338187 | 1269.32ms | 4926 | 4890 | 13815.2 | 4970.12 | 0.133402 | 5.41503 | 24.2416 | 4.84998 | 0.00750465 | 6.65888e-05 | 2.22516e-05 | 1(Win) | true |
| simdjson (ondemand) | 499.438 | 0.0299965 | 1723.8ms | 4926 | 4890 | 38929.3 | 9406.17 | 0.148946 | 10.208 | 46.1417 | 9.49797 | 0.0188186 | 4.92358e-05 | 1.7519e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1244.31 | 0.144414 | 1359.83ms | 8150 | 160 | 13019.5 | 6246.38 | 0.0192075 | 4.15979 | 17.2321 | 3.45693 | 0.00582975 | 1.91718e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 747.161 | 0.063395 | 1784.24ms | 8150 | 1280 | 55668.1 | 10402.6 | 0.0243869 | 6.82773 | 29.862 | 6.08945 | 0.0140696 | 4.45744e-05 | 1.6967e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1415.99 | 0.0669375 | 1326.6ms | 8150 | 80 | 1080 | 5489.05 | 0.0191253 | 3.66537 | 15.5836 | 3.09669 | 0.00599233 | 1.07362e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 806.049 | 0.033131 | 1742.42ms | 8150 | 4890 | 49907.9 | 9642.64 | 0.0184094 | 6.32322 | 28.2134 | 5.72957 | 0.0132825 | 2.16292e-05 | 5.14384e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2651.28 | 0.0969413 | 906.966ms | 4926 | 1280 | 3776.65 | 1771.9 | 0.0104066 | 1.97177 | 8.63337 | 1.59988 | 0.00139312 | 2.2838e-05 | 6.18529e-06 | 1(Win) | true |
| simdjson (ondemand) | 2268.2 | 0.0975142 | 928.975ms | 4926 | 640 | 2610.62 | 2071.16 | 0.0646864 | 2.31061 | 9.36419 | 1.5812 | 0.00292453 | 1.07846e-05 | 9.51583e-07 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2889.95 | 0.0924959 | 902.45ms | 4926 | 4890 | 11055.1 | 1625.56 | 0.254268 | 1.80514 | 8.04202 | 1.45412 | 0.00172865 | 1.95117e-05 | 4.60808e-06 | 1(Win) | true |
| simdjson (ondemand) | 2479.12 | 0.0516545 | 923.402ms | 4926 | 4890 | 4685.09 | 1894.94 | 0.0776936 | 2.1141 | 8.75741 | 1.43341 | 0.00270901 | 1.54433e-05 | 5.02322e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3819.5 | 0.0452373 | 928.517ms | 8150 | 4890 | 4143.85 | 2034.94 | 0.156516 | 1.37148 | 5.80896 | 1.00503 | 0.00128428 | 1.87938e-05 | 5.67077e-06 | 1(Win) | true |
| simdjson (ondemand) | 3483.09 | 0.0406359 | 946.656ms | 8150 | 4890 | 4020.82 | 2231.48 | 0.215281 | 1.49778 | 6.13018 | 0.976687 | 0.00189303 | 2.21561e-05 | 8.15487e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4105.78 | 0.0651443 | 922.535ms | 8150 | 160 | 243.331 | 1893.05 | 0.0528527 | 1.28179 | 5.45153 | 0.916933 | 0.00172086 | 1.07362e-05 | 3.83436e-06 | 1(Win) | true |
| simdjson (ondemand) | 3797.21 | 0.0747715 | 938.233ms | 8150 | 2560 | 5996.53 | 2046.89 | 0.0206148 | 1.37511 | 5.76344 | 0.887362 | 0.00178993 | 1.38516e-05 | 5.32017e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2041.7 | 0.163691 | 955.777ms | 4926 | 640 | 9078.87 | 2300.92 | 0.00835193 | 2.54754 | 11.5873 | 2.21519 | 0.00246872 | 3.14023e-05 | 1.11018e-05 | 1(Win) | true |
| simdjson (ondemand) | 1615.08 | 0.055726 | 1019.37ms | 4926 | 4890 | 12847.7 | 2908.71 | 0.356913 | 3.21226 | 13.5706 | 2.49959 | 0.00558308 | 2.71918e-05 | 8.63495e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2171.04 | 0.0661218 | 954.755ms | 4926 | 4890 | 10010.4 | 2163.84 | 0.231092 | 2.39496 | 10.9844 | 2.0676 | 0.00364291 | 3.73628e-05 | 1.58584e-05 | 1(Win) | true |
| simdjson (ondemand) | 1706.72 | 0.0780216 | 1011.32ms | 4926 | 1280 | 5903.4 | 2752.52 | 0.0326796 | 3.03246 | 12.9592 | 2.34998 | 0.00604319 | 1.63355e-05 | 3.01335e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2864.26 | 0.105703 | 1002.08ms | 8150 | 80 | 658.192 | 2713.6 | 0.0636091 | 1.82189 | 7.71092 | 1.41583 | 0.00230061 | 5.21472e-05 | 1.84049e-05 | 1(Win) | true |
| simdjson (ondemand) | 2533.12 | 0.042458 | 1031.16ms | 8150 | 4890 | 8299.13 | 3068.33 | 0.0972438 | 2.04346 | 8.68074 | 1.53276 | 0.00349367 | 1.58079e-05 | 5.21912e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2988.91 | 0.088304 | 995.286ms | 8150 | 2560 | 13498.6 | 2600.43 | 0.392955 | 1.73401 | 7.34896 | 1.32663 | 0.00301083 | 1.72546e-05 | 4.36158e-06 | 1(Win) | true |
| simdjson (ondemand) | 2701.46 | 0.134409 | 1025.25ms | 8150 | 80 | 1196.36 | 2877.12 | 0.129637 | 1.93339 | 8.31117 | 1.44233 | 0.00389877 | 7.66871e-06 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2181.09 | 0.129581 | 845.458ms | 2821 | 80 | 204.379 | 1233.47 | 0.016217 | 2.43546 | 9.10812 | 1.51613 | 0.000412088 | 1.77242e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 2162.56 | 0.0972731 | 850.635ms | 2821 | 2560 | 3748.81 | 1244.04 | 0.372765 | 2.43864 | 8.83375 | 1.63205 | 0.000358777 | 6.43887e-05 | 2.0909e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2447.24 | 0.0728137 | 840.444ms | 2821 | 320 | 205.036 | 1099.33 | 0.11386 | 2.18697 | 8.19709 | 1.46934 | 0.000355592 | 6.20347e-05 | 1.10776e-06 | 1(Win) | true |
| simdjson (ondemand) | 2328.17 | 0.123732 | 845.735ms | 2821 | 80 | 163.542 | 1155.55 | 0.0411229 | 2.28781 | 8.64835 | 1.4034 | 0.000407657 | 3.98795e-05 | 1.32932e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2781.31 | 0.0640218 | 853.904ms | 3770 | 2560 | 1753.4 | 1292.68 | 0.0712143 | 1.90448 | 7.15729 | 1.15385 | 0.000287943 | 3.49179e-05 | 1.11903e-05 | 1(Win) | true |
| jsonifier (generic) | 2696.04 | 0.168969 | 858.101ms | 3770 | 30 | 152.323 | 1333.57 | 0.241871 | 1.93456 | 7.08621 | 1.23846 | 0.000344828 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3027.94 | 0.0846806 | 850.893ms | 3770 | 160 | 161.762 | 1187.39 | 0.0121078 | 1.75975 | 6.61088 | 1.11671 | 0.000265252 | 2.98408e-05 | 3.31565e-06 | 1(Win) | true |
| simdjson (ondemand) | 2959.64 | 0.164612 | 850.448ms | 3770 | 2560 | 10236.9 | 1214.79 | 0.134172 | 1.7926 | 6.79443 | 1.06207 | 0.000517759 | 2.27951e-05 | 5.906e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 854.678 | 0.0335438 | 1042.82ms | 2821 | 4890 | 5451.73 | 3147.75 | 0.0424233 | 6.08472 | 26.0496 | 4.76781 | 0.00159184 | 7.20567e-05 | 2.48646e-05 | 1(Win) | true |
| simdjson (ondemand) | 346.427 | 0.0456874 | 1509.64ms | 2821 | 2560 | 32226.7 | 7765.89 | 0.209505 | 14.7885 | 67.0376 | 14.815 | 0.00692767 | 0.000199813 | 0.000119915 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 886.38 | 0.1184 | 1033.61ms | 2821 | 2560 | 33060.5 | 3035.17 | 0.00437597 | 5.8736 | 25.4452 | 4.61716 | 0.00163492 | 0.000191782 | 9.09751e-05 | 1(Win) | true |
| simdjson (ondemand) | 349.887 | 0.047918 | 1508.9ms | 2821 | 2560 | 34752.7 | 7689.1 | 0.407173 | 14.6745 | 66.5778 | 14.7015 | 0.00722525 | 0.000144286 | 9.1252e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1070.61 | 0.0390145 | 1067.52ms | 3770 | 4890 | 8394.2 | 3358.22 | 0.0164502 | 4.83907 | 20.1663 | 3.75199 | 0.00193992 | 6.66656e-05 | 2.24569e-05 | 1(Win) | true |
| simdjson (ondemand) | 462.17 | 0.0383813 | 1510.62ms | 3770 | 80 | 713.195 | 7779.29 | 0.0525158 | 10.9993 | 49.8966 | 10.9716 | 0.0068435 | 6.96286e-05 | 3.31565e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1102.64 | 0.0665319 | 1063.3ms | 3770 | 160 | 753.001 | 3260.68 | 0.0145654 | 4.73088 | 19.7626 | 3.6504 | 0.00164125 | 3.14987e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 469.948 | 0.0735061 | 1502.64ms | 3770 | 640 | 20240 | 7650.53 | 0.248064 | 10.8673 | 49.5363 | 10.8804 | 0.00643485 | 8.04045e-05 | 3.56432e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5892.87 | 0.0981856 | 772.556ms | 2821 | 80 | 16.0745 | 456.538 | 0.123362 | 0.948476 | 3.64552 | 0.50195 | 0.0007134 | 8.86211e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5855.83 | 0.108361 | 773.858ms | 2821 | 160 | 39.6547 | 459.425 | 0.349755 | 0.954287 | 3.85856 | 0.454449 | 0.000762141 | 2.88018e-05 | 1.55087e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6061.09 | 0.170361 | 774.103ms | 2821 | 30 | 17.154 | 443.867 | 0.339085 | 0.925121 | 3.57285 | 0.48458 | 0.000756233 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5999.49 | 0.0510542 | 770.769ms | 2821 | 1280 | 67.0889 | 448.424 | 0.397554 | 0.927367 | 3.77987 | 0.436371 | 0.00071423 | 8.03128e-06 | 1.10776e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6978.5 | 0.257692 | 774.354ms | 3770 | 4890 | 8619.23 | 515.204 | 0.0578209 | 0.792576 | 3.21671 | 0.356764 | 0.000533053 | 1.92023e-05 | 8.35354e-06 | 1(Win) | true |
| jsonifier (generic) | 6520.01 | 0.31646 | 782.019ms | 3770 | 30 | 91.3575 | 551.433 | 0.0181378 | 0.86137 | 3.15809 | 0.4 | 0.00106101 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7108.51 | 0.316166 | 777.19ms | 3770 | 4890 | 12504.4 | 505.781 | 0.0349093 | 0.775021 | 3.15783 | 0.343236 | 0.000545638 | 1.52425e-05 | 6.18379e-06 | 1(Win) | true |
| jsonifier (generic) | 6949.55 | 0.168667 | 776.807ms | 3770 | 80 | 60.9139 | 517.35 | 0.00966557 | 0.798624 | 3.10371 | 0.387003 | 0.000530504 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3987.35 | 0.113225 | 793.15ms | 2821 | 80 | 46.6884 | 674.712 | 0.0536977 | 1.36825 | 5.36406 | 0.857852 | 0.000828607 | 3.98795e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3691.56 | 0.050866 | 799.186ms | 2821 | 160 | 21.9868 | 728.775 | 0.0068613 | 1.47047 | 6.02127 | 0.94151 | 0.00114321 | 4.43105e-06 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4116.62 | 0.108197 | 790.551ms | 2821 | 40 | 19.9994 | 653.525 | 0.0855072 | 1.32952 | 5.29245 | 0.840837 | 0.001028 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3804.9 | 0.0870862 | 818.825ms | 2821 | 30 | 11.3747 | 707.067 | 0.0235771 | 1.42934 | 5.94293 | 0.923786 | 0.00108708 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4969.35 | 0.0703266 | 799.167ms | 3770 | 320 | 82.8464 | 723.506 | 0.260696 | 1.09015 | 4.48912 | 0.674801 | 0.00105852 | 1.40915e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 4603.82 | 0.121711 | 804.004ms | 3770 | 80 | 72.2759 | 780.95 | 0.207648 | 1.17491 | 4.84456 | 0.723342 | 0.000789125 | 1.65782e-05 | 6.6313e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5022.49 | 0.135066 | 797.916ms | 3770 | 80 | 74.7873 | 715.85 | 0.0384011 | 1.08112 | 4.43554 | 0.662069 | 0.0010809 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4653.73 | 0.158181 | 800.626ms | 3770 | 40 | 59.7378 | 772.575 | 0.0463602 | 1.14269 | 4.78594 | 0.71008 | 0.000795756 | 1.98939e-05 | 0 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4430.72 | 0.0241023 | 6712.74ms | 277673 | 4890 | 1.01472e+06 | 59766.8 | 0.0919149 | 1.14592 | 4.21805 | 0.670243 | 0.00318721 | 3.42902e-06 | 2.32431e-06 | 1(Win) | true |
| simdjson (ondemand) | 3640.81 | 0.12022 | 4106.22ms | 277673 | 640 | 4.89332e+06 | 72733.6 | 0.127356 | 1.39648 | 4.71545 | 0.783459 | 0.00367297 | 1.01682e-05 | 8.77268e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3641.1 | 0.179601 | 4157.96ms | 10548466 | 30 | 7.38674e+08 | 2.76285e+06 | 0.0838768 | 1.39149 | 4.21853 | 0.670527 | 0.00969791 | 0.0172015 | 0.000268279 | 1(Win) | true |
| simdjson (ondemand) | 3237.9 | 0.321295 | 4659.7ms | 10548466 | 30 | 2.98937e+09 | 3.10689e+06 | 0.470273 | 1.57127 | 4.71549 | 0.783856 | 0.00985804 | 0.0174374 | 0.000374832 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4115.51 | 0.289656 | 5582.35ms | 16002592 | 40 | 4.61487e+09 | 3.70823e+06 | 0.230976 | 1.23444 | 6.9708 | 0.963336 | 0.000751991 | 0.0357879 | 0.00101431 | 1(Win) | true |
| jsonifier (generic) | 4055.54 | 0.218575 | 5648.81ms | 16002592 | 40 | 2.70609e+09 | 3.76306e+06 | 0.0413621 | 1.24675 | 6.8554 | 1.03205 | 0.000831131 | 0.0334392 | 0.000228768 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3906.22 | 0.115025 | 5892.76ms | 16002591 | 30 | 6.0586e+08 | 3.90692e+06 | 0.289225 | 1.29427 | 7.15316 | 1.13613 | 0.000843353 | 0.0365117 | 0.000695939 | 1(Win) | true |
| simdjson (ondemand) | 2253.86 | 0.180123 | 4679.17ms | 16002591 | 30 | 4.46259e+09 | 6.77115e+06 | 1.21189 | 2.24443 | 11.1333 | 1.82311 | 0.000680063 | 0.0543751 | 0.011366 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 18411.6 | 0.478775 | 5287.52ms | 16197086 | 80 | 1.29075e+09 | 838967 | 0.0980737 | 0.275411 | 1.23503 | 0.0700954 | 9.17681e-05 | 0.0157247 | 0.000347853 | 1(Win) | true |
| jsonifier (generic) | 18003.9 | 0.161224 | 5480.86ms | 16197086 | 40 | 7.65348e+07 | 857967 | 0.0792548 | 0.281558 | 1.2923 | 0.0673779 | 7.93862e-05 | 0.0157194 | 0.000214191 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 17952 | 0.23441 | 5500.12ms | 16197085 | 160 | 6.50909e+08 | 860448 | 0.19391 | 0.282446 | 1.29667 | 0.0690485 | 9.22299e-05 | 0.0157199 | 0.000254257 | 1(Win) | true |
| simdjson (ondemand) | 17272.3 | 0.565402 | 5615.4ms | 16197085 | 40 | 1.0227e+09 | 894307 | 0.917352 | 0.293095 | 1.30398 | 0.0844263 | 0.000106865 | 0.0157227 | 0.000381556 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1929.82 | 0.16144 | 4017.93ms | 4212000 | 40 | 4.51675e+08 | 2.08148e+06 | 0.22834 | 2.61354 | 11.3738 | 2.07988 | 0.0112026 | 0.0666447 | 0.00290415 | 1(Win) | true |
| simdjson (ondemand) | 1647.15 | 0.0670825 | 4546.98ms | 4212000 | 30 | 8.02878e+07 | 2.43868e+06 | 0.0133948 | 3.0659 | 12.7555 | 2.34851 | 0.012314 | 0.0667061 | 0.000639134 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1528.56 | 0.131333 | 4817.24ms | 4212000 | 30 | 3.57341e+08 | 2.62788e+06 | 0.146877 | 3.30031 | 14.9824 | 2.90259 | 0.0116999 | 0.066836 | 0.000443447 | 1(Win) | true |
| simdjson (ondemand) | 1309.82 | 0.0746951 | 5483.76ms | 4212000 | 80 | 4.19787e+08 | 3.06674e+06 | 0.117529 | 3.85199 | 16.2723 | 3.01412 | 0.0132647 | 0.0667342 | 0.00191189 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1805.26 | 0.0816769 | 4229.75ms | 4211999 | 80 | 2.64231e+08 | 2.22509e+06 | 0.224954 | 2.8023 | 12.2764 | 2.305 | 0.0117901 | 0.067872 | 0.00170983 | 1(Win) | true |
| simdjson (ondemand) | 1398.26 | 0.0971907 | 5185.87ms | 4211999 | 40 | 3.11824e+08 | 2.87276e+06 | 0.0521294 | 3.61115 | 14.8273 | 2.77948 | 0.0124438 | 0.0687377 | 0.00152174 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1531.43 | 0.140615 | 4820.71ms | 4211999 | 80 | 1.08827e+09 | 2.62295e+06 | 0.0425122 | 3.30203 | 15.1839 | 2.97814 | 0.0120204 | 0.068114 | 0.000765833 | 1(Win) | true |
| simdjson (ondemand) | 1159.38 | 0.116005 | 6051.29ms | 4211999 | 40 | 6.46153e+08 | 3.46467e+06 | 0.26315 | 4.35834 | 18.3434 | 3.44495 | 0.0132829 | 0.0687202 | 0.00409716 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1302.32 | 0.0888446 | 5275.89ms | 4525120 | 40 | 3.46694e+08 | 3.31369e+06 | 0.00262087 | 3.87967 | 16.3044 | 2.87994 | 0.00985376 | 0.0776838 | 0.000790979 | 1(Win) | true |
| simdjson (ondemand) | 1204.31 | 0.161693 | 5686.87ms | 4525120 | 40 | 1.34284e+09 | 3.58336e+06 | 0.2628 | 4.20065 | 16.484 | 2.6639 | 0.0162099 | 0.077431 | 0.000535174 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 770.316 | 0.182413 | 4074.17ms | 4525120 | 30 | 3.13296e+09 | 5.60224e+06 | 0.0119306 | 6.57866 | 31.4815 | 6.2666 | 0.0151617 | 0.0779979 | 0.00697109 | 1(Win) | true |
| simdjson (ondemand) | 594.515 | 0.0669054 | 5257.43ms | 4525120 | 30 | 7.07586e+08 | 7.25885e+06 | 0.23616 | 8.50449 | 41.8087 | 8.18575 | 0.0277025 | 0.078121 | 0.00283833 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1164.71 | 0.0503599 | 5932.24ms | 4525119 | 80 | 2.78538e+08 | 3.70521e+06 | 0.193062 | 4.33641 | 18.5256 | 3.43548 | 0.010267 | 0.0782142 | 0.00120794 | 1(Win) | true |
| simdjson (ondemand) | 932.236 | 0.190913 | 7237.69ms | 4525119 | 40 | 3.12419e+09 | 4.62918e+06 | 0.0955905 | 5.41088 | 21.0294 | 3.60532 | 0.018935 | 0.0929008 | 0.00128549 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 761.2 | 0.10497 | 4102.3ms | 4525119 | 40 | 1.41662e+09 | 5.66932e+06 | 0.144164 | 6.64778 | 31.2132 | 6.26883 | 0.0149112 | 0.0785186 | 0.00113023 | 1(Win) | true |
| simdjson (ondemand) | 518.858 | 0.0670052 | 5978.72ms | 4525119 | 40 | 1.24234e+09 | 8.31729e+06 | 0.4124 | 9.74064 | 46.3548 | 9.12729 | 0.0305154 | 0.0934413 | 0.00236041 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1238.69 | 0.124113 | 5098.7ms | 4203059 | 80 | 1.29043e+09 | 3.23596e+06 | 0.231929 | 4.07338 | 17.7637 | 3.37939 | 0.0147144 | 0.0888994 | 0.000702366 | 1(Win) | true |
| simdjson (ondemand) | 967.833 | 0.0726233 | 6488.29ms | 4203059 | 80 | 7.23723e+08 | 4.14157e+06 | 0.0235936 | 5.23514 | 19.3513 | 3.60131 | 0.0319586 | 0.0880857 | 0.0016161 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 810.512 | 0.0597358 | 7661.55ms | 4203059 | 80 | 6.98187e+08 | 4.94546e+06 | 0.133385 | 6.23358 | 27.6551 | 5.53911 | 0.0209484 | 0.0895256 | 0.00194032 | 1(Win) | true |
| simdjson (ondemand) | 728.099 | 0.145512 | 8508.76ms | 4203059 | 30 | 1.92518e+09 | 5.50523e+06 | 0.0275026 | 6.94554 | 27.5845 | 5.13199 | 0.0380196 | 0.0872391 | 0.00275714 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1123.79 | 0.110103 | 5616.82ms | 4203058 | 40 | 6.16901e+08 | 3.5668e+06 | 0.453186 | 4.51346 | 19.9062 | 3.91513 | 0.015787 | 0.0885667 | 0.000779385 | 1(Win) | true |
| simdjson (ondemand) | 819.849 | 0.0859887 | 7638.36ms | 4203058 | 80 | 1.41396e+09 | 4.88913e+06 | 0.0566344 | 6.20097 | 23.6403 | 4.48543 | 0.0333438 | 0.102468 | 0.00138078 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 756.256 | 0.107726 | 8197.63ms | 4203058 | 30 | 9.78038e+08 | 5.30026e+06 | 0.15671 | 6.67765 | 29.7987 | 6.07526 | 0.022005 | 0.0883139 | 0.00143757 | 1(Win) | true |
| simdjson (ondemand) | 634.639 | 0.0944437 | 4534.46ms | 4203058 | 40 | 1.42326e+09 | 6.31595e+06 | 0.21119 | 7.92597 | 31.8731 | 6.01594 | 0.0395766 | 0.10147 | 0.00270268 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1763.71 | 0.07915 | 7368.08ms | 4197496 | 160 | 5.16352e+08 | 2.26967e+06 | 0.3512 | 2.86454 | 15.2062 | 2.88064 | 0.00047889 | 0.0815304 | 0.000526047 | 1(Win) | true |
| simdjson (ondemand) | 1552.47 | 0.112174 | 4010.84ms | 4197496 | 40 | 3.34642e+08 | 2.57849e+06 | 0.115832 | 3.25115 | 16.3114 | 2.56896 | 0.00502981 | 0.0808961 | 0.000549643 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1031.51 | 0.132699 | 5968.69ms | 4197496 | 80 | 2.12157e+09 | 3.88076e+06 | 0.154055 | 4.89097 | 26.6178 | 5.36546 | 0.000999641 | 0.0819876 | 0.00145863 | 1(Win) | true |
| simdjson (ondemand) | 787.905 | 0.11655 | 7817.88ms | 4197496 | 30 | 1.05191e+09 | 5.08061e+06 | 0.243384 | 6.42566 | 31.8513 | 5.99558 | 0.00944955 | 0.0810106 | 0.000786485 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1489.62 | 0.304465 | 4178.22ms | 4197495 | 80 | 5.35546e+09 | 2.6873e+06 | 0.505034 | 3.38236 | 17.441 | 3.42885 | 0.00079113 | 0.0842714 | 0.000541975 | 1(Win) | true |
| simdjson (ondemand) | 1172.23 | 0.0865008 | 5345.97ms | 4197495 | 80 | 6.9805e+08 | 3.4149e+06 | 0.603323 | 4.32016 | 21.0458 | 3.55398 | 0.00524879 | 0.101913 | 0.000681299 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 920.94 | 0.287644 | 6643.57ms | 4197495 | 80 | 1.2506e+10 | 4.34669e+06 | 0.182531 | 5.50034 | 26.8556 | 5.46839 | 0.00949421 | 0.0844442 | 0.000683613 | 1(Win) | true |
| simdjson (ondemand) | 677.756 | 0.197247 | 4223.79ms | 4197495 | 30 | 4.07168e+09 | 5.90632e+06 | 0.0430027 | 7.47222 | 36.5858 | 6.98061 | 0.00975316 | 0.102233 | 0.00123871 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1505.05 | 0.21229 | 5042.89ms | 4506447 | 80 | 2.93977e+09 | 2.8555e+06 | 0.162013 | 3.36518 | 15.5336 | 2.93682 | 0.00853115 | 0.0804907 | 0.000727929 | 1(Win) | true |
| simdjson (ondemand) | 1167.67 | 0.253381 | 6335.37ms | 4506447 | 30 | 2.60914e+09 | 3.68056e+06 | 0.0399084 | 4.33617 | 17.222 | 3.1657 | 0.0174006 | 0.0790715 | 0.000723896 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 886.898 | 0.0928601 | 8065.29ms | 4506447 | 80 | 1.61983e+09 | 4.84575e+06 | 0.506953 | 5.71317 | 26.0129 | 5.32847 | 0.0129935 | 0.0806759 | 0.00189473 | 1(Win) | true |
| simdjson (ondemand) | 514.616 | 0.0942174 | 6207.88ms | 4506447 | 30 | 1.85731e+09 | 8.35124e+06 | 0.12939 | 9.85364 | 43.2772 | 8.8987 | 0.03154 | 0.0792934 | 0.00357344 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1360.93 | 0.131918 | 5496.89ms | 4506446 | 40 | 6.94168e+08 | 3.1579e+06 | 0.175111 | 3.72596 | 17.2028 | 3.35667 | 0.0112759 | 0.0808466 | 0.00151264 | 1(Win) | true |
| simdjson (ondemand) | 983.127 | 0.166982 | 7309.13ms | 4506446 | 80 | 4.26261e+09 | 4.37144e+06 | 0.0439513 | 5.16225 | 20.6079 | 3.87008 | 0.0174806 | 0.0882783 | 0.00104487 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 884.38 | 0.337657 | 8000.94ms | 4506446 | 30 | 8.07727e+09 | 4.85954e+06 | 0.177774 | 5.74066 | 25.8741 | 5.34819 | 0.0131701 | 0.0807697 | 0.0017072 | 1(Win) | true |
| simdjson (ondemand) | 477.262 | 0.115797 | 6658.63ms | 4506446 | 30 | 3.2619e+09 | 9.00487e+06 | 0.279068 | 10.6434 | 46.6634 | 9.60313 | 0.0308321 | 0.0884695 | 0.0122307 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2076.07 | 0.108827 | 6752.46ms | 4219120 | 80 | 3.55896e+08 | 1.93812e+06 | 0.0396998 | 2.44682 | 8.91761 | 1.58005 | 0.0121391 | 0.0561054 | 0.000570071 | 1(Win) | true |
| simdjson (ondemand) | 1930.61 | 0.160502 | 7178.56ms | 4219120 | 80 | 8.95169e+08 | 2.08414e+06 | 0.156953 | 2.60481 | 9.07888 | 1.49826 | 0.0155065 | 0.0544615 | 0.000477274 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 760.186 | 0.149614 | 8311.4ms | 4219120 | 40 | 2.50849e+09 | 5.29301e+06 | 0.0760094 | 6.68945 | 26.3617 | 4.91918 | 0.0172001 | 0.0570775 | 0.00114156 | 1(Win) | true |
| simdjson (ondemand) | 291.685 | 0.0657443 | 4196.74ms | 4219120 | 30 | 2.46748e+09 | 1.37946e+07 | 0.265731 | 17.2563 | 70.2362 | 15.5697 | 0.0784346 | 0.0552178 | 0.00522386 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1915.14 | 0.0738157 | 7242.77ms | 4219119 | 160 | 3.84823e+08 | 2.10098e+06 | 0.388335 | 2.65714 | 9.94065 | 1.83566 | 0.0121337 | 0.0560995 | 0.00100859 | 1(Win) | true |
| simdjson (ondemand) | 1610.34 | 0.217374 | 4079.17ms | 4219119 | 80 | 2.36e+09 | 2.49864e+06 | 0.138654 | 3.12192 | 11.1173 | 1.92068 | 0.0167425 | 0.0552712 | 0.00131405 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 758.312 | 0.10231 | 8340.22ms | 4219119 | 30 | 8.84106e+08 | 5.30608e+06 | 0.137347 | 6.67994 | 26.2563 | 4.92431 | 0.0168872 | 0.0570068 | 0.00197806 | 1(Win) | true |
| simdjson (ondemand) | 283.83 | 0.115193 | 4348.52ms | 4219119 | 30 | 8.00023e+09 | 1.41763e+07 | 0.261575 | 17.7753 | 72.2743 | 15.9921 | 0.0799118 | 0.0560975 | 0.00539882 | 2(Loss) | true |
