# Json-Performance
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Oct 24, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [1ed6e0c](https://github.com/nihilai-collective/jsonifier/commit/1ed6e0c)  
| Simdjson (On Demand): [50f0739](https://github.com/simdjson/simdjson/commit/50f0739)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `NEON` |
| **simdjson (ondemand)** | `arm64` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 4s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **UTF-8 Validation:** Both libraries perform full UTF-8 validation in every test.
* **Schema-Free Traversal:** Neither library is given a schema. `jsonifier (generic)` walks its stage-1 structural tape through the re-accessible `jsonifier::generic` API; `simdjson (ondemand)` walks its On Demand API. Both fill the exact same structs through the exact same field-by-field traversal.

##### Test Variants
* **Key Traversal Order:** Standard tests request keys in document order. Tests labeled `Reverse` request each object's keys backwards, forcing forward-only iterative parsers (e.g., simdjson On Demand) into sequential rescans or rewinds, degrading from $O(N)$ toward $O(N^2)$ as object size grows.
* **Sparse:** Reads the same document as its full counterpart but requests only a small subset of fields (a few per record of the main arrays, in the spirit of Twitter Partial); all other fields are skipped by each library. `Sparse Reverse` requests that subset in reverse document order.

---
*Environment generated via BenchmarkSuite commit: [ab75024](https://github.com/nihilai-collective/benchmarksuite/commit/ab75024)*

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1012.96 | 0.0676463 | 4673.71ms | 94653 | 2560 | 9.30276e+06 | 89113.2 | 0.164463 | 1(Win) | true |
| simdjson (ondemand) | 763.699 | 0.114501 | 6109.51ms | 94653 | 1280 | 2.34451e+07 | 118199 | 0.147162 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1456.99 | 0.106122 | 4168.39ms | 94653 | 2560 | 1.10664e+07 | 61955.2 | 0.258549 | 1(Win) | true |
| simdjson (ondemand) | 984.631 | 0.0776165 | 5757.7ms | 94653 | 2560 | 1.29619e+07 | 91677.1 | 0.283643 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1248 | 0.117404 | 4898.96ms | 124611 | 640 | 7.9989e+06 | 95222.8 | 0.102181 | 1(Win) | true |
| simdjson (ondemand) | 976.466 | 0.273412 | 6313.5ms | 124611 | 40 | 4.42889e+06 | 121702 | 0.0560617 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1763.83 | 0.0947812 | 4491.54ms | 124611 | 2560 | 1.04396e+07 | 67375 | 0.107343 | 1(Win) | true |
| simdjson (ondemand) | 1247.25 | 0.0964565 | 5893.32ms | 124611 | 1280 | 1.08114e+07 | 95280.4 | 0.231201 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 698.976 | 0.33071 | 7011.57ms | 94653 | 30 | 5.47218e+06 | 129143 | 0.30303 | 1(Win) | true |
| simdjson (ondemand) | 364.844 | 0.151634 | 6459.69ms | 94653 | 320 | 4.50398e+07 | 247416 | 0.0090544 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 877.101 | 0.0934023 | 6253.33ms | 94653 | 2560 | 2.36551e+07 | 102916 | 0.108847 | 1(Win) | true |
| simdjson (ondemand) | 407.759 | 0.0869855 | 6238.85ms | 94653 | 1280 | 4.74642e+07 | 221376 | 0.632001 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 885.702 | 0.0921925 | 6970.33ms | 124611 | 2560 | 3.91713e+07 | 134174 | 0.598233 | 1(Win) | true |
| simdjson (ondemand) | 481.08 | 0.1732 | 6382.62ms | 124611 | 80 | 1.46441e+07 | 247024 | 0.131009 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1122.87 | 0.0623977 | 6480.07ms | 124611 | 2560 | 1.11643e+07 | 105835 | 0.0627001 | 1(Win) | true |
| simdjson (ondemand) | 535.639 | 0.134226 | 6168.27ms | 124611 | 640 | 5.67576e+07 | 221863 | 0.0611562 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1489.24 | 0.174765 | 6134.8ms | 94653 | 640 | 7.18175e+06 | 60613.6 | 0.388213 | 1(Win) | true |
| simdjson (ondemand) | 1082.81 | 0.0886267 | 4342.93ms | 94653 | 1280 | 6.98718e+06 | 83364.6 | 0.141507 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1980.64 | 0.0823611 | 5337.96ms | 94653 | 2560 | 3.60696e+06 | 45575.2 | 0.0473717 | 1(Win) | true |
| simdjson (ondemand) | 1322.4 | 0.165101 | 7693.48ms | 94653 | 320 | 4.06434e+06 | 68260.8 | 0.138102 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1890.75 | 0.070529 | 6353.45ms | 124611 | 2560 | 5.0306e+06 | 62852.5 | 0.162498 | 1(Win) | true |
| simdjson (ondemand) | 1419.14 | 0.069605 | 4343.56ms | 124611 | 2560 | 8.69731e+06 | 83739.8 | 0.181662 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2454.37 | 0.102553 | 5714.59ms | 124611 | 2560 | 6.31205e+06 | 48419 | 0.290362 | 1(Win) | true |
| simdjson (ondemand) | 1730.54 | 0.0539081 | 7840.44ms | 124611 | 4890 | 6.70144e+06 | 68671.3 | 0.0491294 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1265.9 | 0.0943544 | 7211.95ms | 94653 | 2560 | 1.15887e+07 | 71307.5 | 0.0447558 | 1(Win) | true |
| simdjson (ondemand) | 927.108 | 0.130605 | 5113.64ms | 94653 | 30 | 485117 | 97365.3 | 0 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1606.82 | 0.0801366 | 6455.5ms | 94653 | 2560 | 5.18845e+06 | 56178.2 | 0.140822 | 1(Win) | true |
| simdjson (ondemand) | 1089.56 | 0.150335 | 4638.63ms | 94653 | 640 | 9.92804e+06 | 82848 | 0.133079 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1596.59 | 0.0574063 | 7561.06ms | 124611 | 4890 | 8.92795e+06 | 74432.4 | 0.065596 | 1(Win) | true |
| simdjson (ondemand) | 1198.54 | 0.0751236 | 5116.02ms | 124611 | 2560 | 1.42037e+07 | 99152.6 | 0.112681 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1987.34 | 0.247371 | 6755.32ms | 124611 | 640 | 1.40037e+07 | 59797.6 | 0.689702 | 1(Win) | true |
| simdjson (ondemand) | 1422.46 | 0.0638697 | 4743.71ms | 124611 | 2560 | 7.28893e+06 | 83544.4 | 0.205217 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1124.38 | 0.826221 | 224.654ms | 2632 | 640 | 217729 | 2232.4 | 0.08967 | 1(Win) | true |
| simdjson (ondemand) | 741.221 | 0.472862 | 324.626ms | 2632 | 1280 | 328212 | 3386.4 | 1.88898 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1664.8 | 0.634925 | 178.949ms | 2632 | 4890 | 448127 | 1507.73 | 0.236216 | 1(Win) | true |
| simdjson (ondemand) | 1144.77 | 0.273675 | 248.798ms | 2632 | 4890 | 176083 | 2192.65 | 0.143553 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1506.51 | 0.304771 | 235.85ms | 3643 | 4890 | 241563 | 2306.15 | 0.0716517 | 1(Win) | true |
| simdjson (ondemand) | 1178.19 | 0.67093 | 304.199ms | 3643 | 160 | 62627.6 | 2948.8 | 0.0542888 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2117.53 | 0.604128 | 195.038ms | 3643 | 2560 | 251511 | 1640.7 | 0.164294 | 1(Win) | true |
| simdjson (ondemand) | 1517.88 | 0.305099 | 266.243ms | 3643 | 4890 | 238470 | 2288.87 | 0.336242 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 750.051 | 0.286304 | 335.944ms | 2632 | 4890 | 448904 | 3346.53 | 0.525162 | 1(Win) | true |
| simdjson (ondemand) | 386.813 | 0.210341 | 653.838ms | 2632 | 2560 | 476932 | 6489.1 | 0.171349 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 978.356 | 0.300083 | 286.111ms | 2632 | 4890 | 289847 | 2565.6 | 0.190561 | 1(Win) | true |
| simdjson (ondemand) | 440.526 | 0.194438 | 603.076ms | 2632 | 2560 | 314218 | 5697.9 | 0.0684932 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1012.66 | 0.454718 | 349.075ms | 3643 | 1280 | 311519 | 3430.8 | 0.209424 | 1(Win) | true |
| simdjson (ondemand) | 498.942 | 1.70722 | 686.036ms | 3643 | 80 | 1.13054e+06 | 6963.2 | 0.183486 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1153.23 | 0.534459 | 337.349ms | 3643 | 1280 | 331835 | 3012.6 | 0.992507 | 1(Win) | true |
| simdjson (ondemand) | 603.018 | 0.145436 | 606.28ms | 3643 | 4890 | 343328 | 5761.41 | 0.555553 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1974.4 | 0.536152 | 130.09ms | 2632 | 4890 | 227189 | 1271.31 | 0.686695 | 1(Win) | true |
| simdjson (ondemand) | 1456.3 | 1.04574 | 177.381ms | 2632 | 640 | 207922 | 1723.6 | 0.396086 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2823.48 | 1.0944 | 95.5791ms | 2632 | 2560 | 242324 | 889 | 1.30995 | 1(Win) | true |
| simdjson (ondemand) | 1891.68 | 0.718078 | 141.356ms | 2632 | 2560 | 232413 | 1326.9 | 0.721117 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2644.82 | 1.40612 | 134.97ms | 3643 | 640 | 218348 | 1313.6 | 0.428135 | 1(Win) | true |
| simdjson (ondemand) | 1971.17 | 0.497464 | 178.299ms | 3643 | 4890 | 375926 | 1762.53 | 0.698507 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) DID NOT CONVERGE | 3270.42 | 0.593158 | 115.083ms | 3643 | 4890 | 194161 | 1062.32 | 5.03475 | -(Win) | false |
| simdjson (ondemand) | 2619.3 | 1.9994 | 142.134ms | 3643 | 320 | 225059 | 1326.4 | 0.974421 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 1671.37 | 0.677104 | 155.76ms | 2632 | 2560 | 264713 | 1501.8 | 0.43755 | 1(Win) | true |
| simdjson (ondemand) | 1191.41 | 0.606616 | 214.464ms | 2632 | 640 | 104533 | 2106.8 | 0.246212 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2284.46 | 0.423506 | 118.932ms | 2632 | 4890 | 105884 | 1098.76 | 0.49282 | 1(Win) | true |
| simdjson (ondemand) | 1498.79 | 0.424047 | 177.085ms | 2632 | 4890 | 246620 | 1674.73 | 1.57319 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2031.63 | 0.4255 | 172.631ms | 3643 | 4890 | 258902 | 1710.07 | 0.127029 | 1(Win) | true |
| simdjson (ondemand) | 1590.91 | 0.543636 | 219.829ms | 3643 | 1280 | 180407 | 2183.8 | 0.728782 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](../../json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| jsonifier (generic) | 2795.49 | 1.03158 | 131.297ms | 3643 | 2560 | 420771 | 1242.8 | 0.19274 | 1(Win) | true |
| simdjson (ondemand) | 1968.18 | 0.621938 | 184.104ms | 3643 | 2560 | 308548 | 1765.2 | 0.329658 | 2(Loss) | true |
