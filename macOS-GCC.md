# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on macOS 25.6.0 using the GCC 16.2.0 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `NEON` |
| **simdjson (ondemand)** | `arm64` |

> Each library selects its own instruction-set implementation at build or run time; the values above produced the results below.

> **Adaptive Sampling & Convergence (Apple M2 Pro (Virtual)-NEON):**  
> Iterations double each epoch (100 → 200 → 400 ...) up to a maximum of 100000.  
> Each epoch scores a trailing window of `max(iterations/10, 30)` (cap: 100000). No early stopping: epochs run until 5s elapse or the cap is hit.  
> The first epoch is an initial fallback only; the canonical epoch is the later one with minimum (RSE + epoch-over-epoch mean shift), converged or not.  
> Converged: RSE ≤ 10% and mean shift ≤ 5%. Non-converged results still count in rankings and win/tie/loss tallies; read them with reduced confidence.  
> Tie detection: Welch's t-test with Bessel-corrected variance.

---

##### Implementation Details
* **UTF-8 Validation:** Both libraries perform full UTF-8 validation in every test.
* **Schema-Free Traversal:** Neither library is given a schema. `Jsonifier (generic)` walks its stage-1 structural tape through the re-accessible `jsonifier::generic` API; `simdjson (ondemand)` walks its On Demand API. Both fill the exact same structs through the exact same field-by-field traversal.
* **Streaming:** `Jsonifier (generic)` uses `jsonifier::jsonifier_core::iterateMany`; `simdjson (ondemand)` uses `ondemand::parser::iterate_many` (unthreaded). Both use a 1 MiB batch size.

##### Test Variants
* **Amazon Cellphones:** Aggregates ratings per brand over `amazon_cellphones.ndjson` (from the simdjson repository; repeated to 10 MiB for the Large variant).
* **Stream Formats:** Reads and sums `"id"` over generated `{"id","name","payload","flag"}` documents, following simdjson's stream benchmarks, with 16- and 4096-byte payloads, repeated to 16 MB to fit the sampling window.
* **Stream:** Splits each corpus document's main record array into one document per record, repeated to 4 MiB.
* **(NDJSON) vs. (Comma-Separated):** Documents separated by newlines, or by commas (simdjson's `stream_format::comma_delimited`, Jsonifier's `allowCommaSeparated`).
* **Key Traversal Order:** Standard tests request keys in document order. Tests labeled `Reverse` request each object's keys backwards, forcing forward-only iterative parsers (e.g., simdjson On Demand) into sequential rescans or rewinds, degrading from $O(N)$ toward $O(N^2)$ as object size grows.
* **Sparse:** Reads the same document as its full counterpart but requests only a small subset of fields (a few per record of the main arrays, in the spirit of Twitter Partial); all other fields are skipped by each library. `Sparse Reverse` requests that subset in reverse document order.

---
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 222.881 | 0.333538 | 417.366ms | 905 | 4890 | 815733 | 3872.35 | 0.979279 | 1(Win) | true |
| simdjson (ondemand) | 154.327 | 0.496883 | 546.445ms | 905 | 2560 | 1.97679e+06 | 5592.5 | 0.616648 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 228.535 | 0.315136 | 382.037ms | 905 | 4890 | 692620 | 3776.55 | 0.785933 | 1(Win) | true |
| simdjson (ondemand) | 153.054 | 0.326854 | 539.056ms | 905 | 4890 | 1.66121e+06 | 5639.02 | 1.88291 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 356.9 | 0.324737 | 501.794ms | 1811 | 4890 | 1.20758e+06 | 4839.19 | 7.80096 | -(Win) | false |
| simdjson (ondemand) | 180.372 | 0.324813 | 1028.11ms | 1811 | 4890 | 4.73016e+06 | 9575.24 | 1.52377 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 357.105 | 0.776263 | 516.579ms | 1811 | 640 | 902075 | 4836.4 | 1.51973 | 1(Win) | true |
| simdjson (ondemand) | 178.686 | 0.218183 | 962.48ms | 1811 | 2560 | 1.13852e+06 | 9665.6 | 1.49103 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 713.874 | 0.204896 | 538.662ms | 3862 | 2560 | 286081 | 5159.3 | 0.0950644 | 1(Win) | true |
| simdjson (ondemand) | 410.57 | 0.309674 | 898.884ms | 3862 | 4890 | 3.77371e+06 | 8970.68 | 3.04138 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 752.265 | 1.02864 | 575.704ms | 3862 | 40 | 101455 | 4896 | 1.41753 | 1(Win) | true |
| simdjson (ondemand) | 411.284 | 0.472685 | 878.414ms | 3862 | 2560 | 4.58696e+06 | 8955.1 | 1.15784 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 773.215 | 0.396234 | 1245.2ms | 9578 | 1280 | 2.80456e+06 | 11813.4 | 3.19107 | 1(Win) | true |
| simdjson (ondemand) | 657.417 | 0.239068 | 1401.7ms | 9578 | 4890 | 5.39536e+06 | 13894.2 | 0.098005 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 989.416 | 0.484731 | 1214.45ms | 9578 | 160 | 320415 | 9232 | 0.65427 | 1(Win) | true |
| simdjson (ondemand) | 889.565 | 0.241066 | 1285.27ms | 9578 | 4890 | 2.99624e+06 | 10268.3 | 2.19019 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 702.095 | 1.09463 | 546.385ms | 3873 | 80 | 265296 | 5260.8 | 1.20192 | 1(Win) | true |
| simdjson (ondemand) | 461.451 | 0.262636 | 967.495ms | 3873 | 30 | 13257.9 | 8004.27 | 0 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 672.171 | 0.455128 | 528.104ms | 3873 | 1280 | 800596 | 5495 | 1.53363 | 1(Win) | true |
| simdjson (ondemand) | 446.365 | 0.198055 | 860.686ms | 3873 | 2560 | 687582 | 8274.8 | 0.622103 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1030.02 | 0.414848 | 9293.58ms | 94653 | 30 | 3.9653e+06 | 87637.3 | 0.735655 | 1(Win) | true |
| simdjson (ondemand) | 723.055 | 1.88438 | 6445.29ms | 94653 | 30 | 1.66029e+08 | 124843 | 0.439379 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1602.25 | 0.229314 | 8338.55ms | 94653 | 320 | 5.34095e+06 | 56338.4 | 0.449307 | 1(Win) | true |
| simdjson (ondemand) | 893.286 | 1.17683 | 6163.98ms | 94653 | 30 | 4.24263e+07 | 101052 | 0.21156 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1346.8 | 0.0973323 | 9232.6ms | 124597 | 640 | 4.71958e+06 | 88227.6 | 0.0575452 | 1(Win) | true |
| simdjson (ondemand) | 982.947 | 0.275024 | 6255.43ms | 124597 | 80 | 8.8427e+06 | 120886 | 0.135185 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1973.23 | 0.156083 | 8115.86ms | 124597 | 320 | 2.82695e+06 | 60218.4 | 0.0651388 | 1(Win) | true |
| simdjson (ondemand) | 1266.86 | 0.112963 | 6073.61ms | 124597 | 640 | 7.18472e+06 | 93794.8 | 0.148614 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 861.492 | 0.129623 | 5371.11ms | 94653 | 640 | 1.18062e+07 | 104781 | 0.0752609 | 1(Win) | true |
| simdjson (ondemand) | 484.196 | 0.149115 | 5233.77ms | 94653 | 160 | 1.23649e+07 | 186429 | 0.106308 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1161.14 | 0.296952 | 5056.62ms | 94653 | 320 | 1.70538e+07 | 77740.8 | 0.113325 | 1(Win) | true |
| simdjson (ondemand) | 440.102 | 0.8314 | 5028.58ms | 94653 | 80 | 2.32634e+08 | 205107 | 0.501756 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1040.32 | 0.304424 | 6670.35ms | 124597 | 160 | 1.93444e+07 | 114219 | 0.169786 | 1(Win) | true |
| simdjson (ondemand) | 555.704 | 0.246199 | 5493.57ms | 124597 | 1280 | 3.54741e+08 | 213828 | 0.254137 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1227.02 | 0.682333 | 6604.5ms | 124597 | 160 | 6.9859e+07 | 96840 | 0.179767 | 1(Win) | true |
| simdjson (ondemand) | 651.341 | 0.208299 | 5212.29ms | 124597 | 1280 | 1.84834e+08 | 182431 | 2.01648 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1464.88 | 0.275021 | 6121.56ms | 94653 | 320 | 9.19065e+06 | 61621.6 | 0.587233 | 1(Win) | true |
| simdjson (ondemand) | 1087.95 | 0.062033 | 8582.68ms | 94653 | 2560 | 6.78162e+06 | 82970.5 | 0.0519732 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2243.68 | 0.181829 | 4844.48ms | 94653 | 2560 | 1.36997e+07 | 40232.1 | 0.944154 | 1(Win) | true |
| simdjson (ondemand) | 1340.98 | 0.334719 | 8011.67ms | 94653 | 80 | 4.06141e+06 | 67315.2 | 0.0380156 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1853.4 | 0.148791 | 6798.47ms | 124597 | 2560 | 2.32955e+07 | 64112 | 0.487138 | 1(Win) | true |
| simdjson (ondemand) | 1417.43 | 0.182323 | 8573.4ms | 124597 | 320 | 7.47555e+06 | 83831.2 | 0.305351 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2556.61 | 0.324814 | 5818.65ms | 124597 | 320 | 7.29301e+06 | 46477.6 | 0.845339 | 1(Win) | true |
| simdjson (ondemand) | 1730.58 | 0.125964 | 7886.21ms | 124597 | 2560 | 1.91499e+07 | 68662 | 0.212765 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1366.67 | 0.213082 | 6723.4ms | 94653 | 160 | 3.16922e+06 | 66049.6 | 0.245265 | 1(Win) | true |
| simdjson (ondemand) | 947.311 | 0.171312 | 5153.06ms | 94653 | 1280 | 3.41089e+07 | 95288.8 | 0.186729 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1783.62 | 0.216631 | 6201.63ms | 94653 | 160 | 1.92321e+06 | 50609.6 | 0.205918 | 1(Win) | true |
| simdjson (ondemand) | 1017.82 | 0.224999 | 9623.81ms | 94653 | 2560 | 1.01936e+08 | 88687.6 | 1.19738 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1361.3 | 0.449031 | 8200.78ms | 124597 | 640 | 9.83201e+07 | 87288 | 0.13307 | 1(Win) | true |
| simdjson (ondemand) | 1018.83 | 0.42646 | 5667.46ms | 124597 | 640 | 1.58324e+08 | 116629 | 0.752258 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2060.8 | 0.89323 | 7472ms | 124597 | 30 | 7.9578e+06 | 57659.7 | 0.103704 | 1(Win) | true |
| simdjson (ondemand) | 1312.48 | 0.974862 | 5409.16ms | 124597 | 160 | 1.24633e+08 | 90534.4 | 1.29247 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 476.121 | 1.08957 | 6416.01ms | 2090234 | 40 | 8.32391e+10 | 4.18675e+06 | 0.43084 | 1(Win) | true |
| simdjson (ondemand) | 456.434 | 0.76671 | 6660.37ms | 2090234 | 30 | 3.3637e+10 | 4.36734e+06 | 0.0322497 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 571.195 | 0.694935 | 6205.8ms | 2090234 | 40 | 2.35271e+10 | 3.48988e+06 | 1.53522 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 444.614 | 1.88474 | 6959.32ms | 2090234 | 80 | 5.71236e+11 | 4.48344e+06 | 6.0056 | -(Loss) | false |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1051.39 | 1.06391 | 7520.9ms | 5212421 | 40 | 1.01209e+11 | 4.72798e+06 | 5.59144 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 924.568 | 2.04961 | 7984.33ms | 5212421 | 30 | 3.64306e+11 | 5.37651e+06 | 5.06271 | -(Loss) | false |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1166.06 | 1.09183 | 7461ms | 5212421 | 80 | 1.73315e+11 | 4.26302e+06 | 4.78833 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1119.32 | 0.873404 | 7908.6ms | 5212421 | 40 | 6.0181e+10 | 4.44104e+06 | 7.70958 | -(Loss) | false |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 401.936 | 0.709598 | 7674.24ms | 2090234 | 80 | 9.90811e+10 | 4.9595e+06 | 0.510645 | 1(Win) | true |
| simdjson (ondemand) | 367.334 | 2.6382 | 7755.2ms | 2090234 | 40 | 8.19869e+11 | 5.42668e+06 | 2.90737 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 506.653 | 0.714246 | 7062.29ms | 2090234 | 30 | 2.36912e+10 | 3.93446e+06 | 1.1892 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 493.414 | 1.51203 | 7569.84ms | 2090234 | 30 | 1.11946e+11 | 4.04002e+06 | 3.43123 | 1(Tie) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 980.143 | 0.576728 | 7791.09ms | 5212421 | 80 | 6.84436e+10 | 5.07166e+06 | 4.61429 | 1(Win) | true |
| Jsonifier (generic) | 932.998 | 1.13797 | 7862.84ms | 5212421 | 30 | 1.10281e+11 | 5.32793e+06 | 0.718488 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.13 | 0.78327 | 7577.42ms | 5212421 | 30 | 3.87667e+10 | 4.58941e+06 | 0.241741 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1055.85 | 0.682546 | 7823.62ms | 5212421 | 80 | 8.26096e+10 | 4.70802e+06 | 5.85649 | -(Loss) | false |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3953.01 | 0.362067 | 6486.46ms | 2090234 | 320 | 1.06675e+09 | 504274 | 2.51313 | 1(Win) | true |
| simdjson (ondemand) | 3017.88 | 0.784736 | 7776.38ms | 2090234 | 160 | 4.29887e+09 | 660531 | 2.98863 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3623.48 | 1.37577 | 7050.13ms | 2090234 | 30 | 1.71851e+09 | 550135 | 1.44916 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 3328.82 | 0.384546 | 7757.63ms | 2090234 | 160 | 8.48449e+08 | 598832 | 7.27204 | -(Loss) | false |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5831.65 | 0.386544 | 5878.09ms | 5212421 | 320 | 3.47412e+09 | 852409 | 1.55524 | 1(Win) | true |
| simdjson (ondemand) | 5714.14 | 0.110715 | 5889.07ms | 5212421 | 30 | 2.78297e+07 | 869939 | 1.18064 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5619.75 | 0.448677 | 5799.08ms | 5212421 | 320 | 5.04037e+09 | 884550 | 0.183891 | 1(Win) | true |
| simdjson (ondemand) | 5096.35 | 0.298624 | 5782.59ms | 5212421 | 160 | 1.35746e+09 | 975394 | 0.710605 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3538.2 | 0.145833 | 7581.16ms | 2090234 | 320 | 2.16017e+08 | 563394 | 0.00781041 | 1(Win) | true |
| simdjson (ondemand) | 2584.15 | 1.15286 | 8765.07ms | 2090234 | 30 | 2.37265e+09 | 771396 | 1.21596 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3034.7 | 0.789036 | 7439.95ms | 2090234 | 30 | 8.05886e+08 | 656870 | 1.4778 | 1(Win) | true |
| simdjson (ondemand) | 2566.3 | 0.329754 | 9034.16ms | 2090234 | 320 | 2.09945e+09 | 776762 | 1.51782 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5458.11 | 0.132814 | 5971.62ms | 5212421 | 40 | 5.85247e+07 | 910746 | 0.454227 | 1(Win) | true |
| simdjson (ondemand) | 4953.61 | 0.110862 | 6909.91ms | 5212421 | 40 | 4.95062e+07 | 1.0035e+06 | 0.145412 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5474.73 | 0.119035 | 5813.83ms | 5212421 | 40 | 4.67262e+07 | 907981 | 0.00187959 | 1(Win) | true |
| simdjson (ondemand) | 4632.2 | 0.466526 | 6943.72ms | 5212421 | 160 | 4.01029e+09 | 1.07313e+06 | 3.69065 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 705.745 | 0.390363 | 8618.14ms | 500299 | 640 | 4.45738e+09 | 676054 | 5.57351 | -(Win) | false |
| simdjson (ondemand) | 686.822 | 0.999834 | 8863.81ms | 500299 | 30 | 1.44727e+09 | 694682 | 2.07852 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 850.672 | 1.40225 | 7635.05ms | 500299 | 40 | 2.47426e+09 | 560877 | 0.536076 | 1(Win) | true |
| simdjson (ondemand) | 731.22 | 1.34379 | 9039.55ms | 500299 | 30 | 2.30647e+09 | 652501 | 0.958487 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1331.8 | 1.10907 | 5252.7ms | 1151920 | 30 | 2.51075e+09 | 824866 | 0.738322 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1288.61 | 1.61983 | 5107.27ms | 1151920 | 320 | 6.10224e+10 | 852510 | 1.12208 | 1(Tie) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1643.86 | 0.861952 | 9618.32ms | 1151920 | 320 | 1.06178e+10 | 668280 | 1.04903 | 1(Win) | true |
| simdjson (ondemand) | 1524.5 | 1.77322 | 5112.84ms | 1151920 | 40 | 6.53095e+09 | 720602 | 3.55809 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 386.656 | 2.02997 | 7489.32ms | 500299 | 30 | 1.88238e+10 | 1.23397e+06 | 1.58438 | 1(Win) | true |
| simdjson (ondemand) | 271.853 | 2.06829 | 5395.21ms | 500299 | 40 | 5.27073e+10 | 1.75507e+06 | 4.86165 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 447.858 | 0.817275 | 6817.88ms | 500299 | 320 | 2.42586e+10 | 1.06534e+06 | 0.304698 | 1(Win) | true |
| simdjson (ondemand) | 256.094 | 0.983703 | 5138.56ms | 500299 | 40 | 1.34354e+10 | 1.86308e+06 | 3.40068 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 884.578 | 1.10024 | 6845.92ms | 1151920 | 30 | 5.60104e+09 | 1.2419e+06 | 3.17607 | 1(Win) | true |
| simdjson (ondemand) | 629.88 | 0.618823 | 5866.48ms | 1151920 | 80 | 9.31863e+09 | 1.74407e+06 | 1.88781 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1145.12 | 0.21405 | 7334.37ms | 1151920 | 30 | 1.26501e+08 | 959334 | 0.185562 | 1(Win) | true |
| simdjson (ondemand) | 585.842 | 0.653415 | 5694.75ms | 1151920 | 80 | 1.20102e+10 | 1.87517e+06 | 1.98011 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 3148.02 | 0.256884 | 7926.04ms | 500299 | 2560 | 3.88059e+08 | 151563 | 2.88537 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3130.77 | 0.136609 | 7819.92ms | 500299 | 320 | 1.38697e+07 | 152398 | 0.0173201 | 1(Tie) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3346.15 | 0.180177 | 7452.4ms | 500299 | 1280 | 8.44848e+07 | 142588 | 1.11953 | 1(Win) | true |
| simdjson (ondemand) | 3160.75 | 0.0637145 | 7831.56ms | 500299 | 1280 | 1.18404e+07 | 150952 | 0.107832 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5450.14 | 0.184966 | 5187.69ms | 1151920 | 80 | 1.112e+07 | 201565 | 0.65678 | 1(Win) | true |
| simdjson (ondemand) | 4729.84 | 0.142779 | 6288.48ms | 1151920 | 160 | 1.75956e+07 | 232261 | 0.00482193 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5552.08 | 0.0881162 | 5063.2ms | 1151920 | 1280 | 3.89094e+07 | 197864 | 0.117897 | 1(Win) | true |
| simdjson (ondemand) | 4434.61 | 0.320544 | 6129.48ms | 1151920 | 160 | 1.00886e+08 | 247723 | 0.00968729 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2006.94 | 0.131142 | 6230.72ms | 500299 | 160 | 1.55523e+07 | 237736 | 0.0949853 | 1(Win) | true |
| simdjson (ondemand) | 1902.04 | 0.156334 | 6570ms | 500299 | 80 | 1.23031e+07 | 250848 | 0.0791543 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2020.49 | 0.0874276 | 6240.67ms | 500299 | 320 | 1.36394e+07 | 236142 | 0.0094867 | 1(Win) | true |
| simdjson (ondemand) | 1910.28 | 0.0716016 | 6444.56ms | 500299 | 640 | 2.04688e+07 | 249766 | 0.0139311 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3629.43 | 0.106881 | 7836.09ms | 1151920 | 320 | 3.349e+07 | 302680 | 0.161494 | 1(Win) | true |
| simdjson (ondemand) | 3326.13 | 0.0613248 | 8596.1ms | 1151920 | 640 | 2.62553e+07 | 330280 | 0.0505281 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3636.41 | 0.0774143 | 7802.55ms | 1151920 | 640 | 3.50042e+07 | 302099 | 0.338115 | 1(Win) | true |
| simdjson (ondemand) | 3344.87 | 0.0471299 | 8720.9ms | 1151920 | 1280 | 3.06683e+07 | 328430 | 0.0229021 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1185.37 | 0.0739356 | 4604.97ms | 56369 | 4890 | 5.4978e+06 | 45350.9 | 0.000109575 | 1(Win) | true |
| simdjson (ondemand) | 919.727 | 0.18299 | 5948.43ms | 56369 | 160 | 1.83037e+06 | 58449.6 | 0.101181 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1462.2 | 0.20391 | 4207.58ms | 56369 | 320 | 1.79843e+06 | 36764.8 | 0.11328 | 1(Win) | true |
| simdjson (ondemand) | 543.532 | 0.0702464 | 5372.68ms | 56369 | 1280 | 6.17859e+06 | 98904.4 | 0.0315556 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1656.05 | 0.139642 | 4967.32ms | 83958 | 640 | 2.91734e+06 | 48349.2 | 0.0272939 | 1(Win) | true |
| simdjson (ondemand) | 1294.03 | 0.313161 | 6768.37ms | 83958 | 80 | 3.00371e+06 | 61875.2 | 0.165221 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2028.33 | 0.214333 | 4504.34ms | 83958 | 40 | 286342 | 39475.2 | 0.0865426 | 1(Win) | true |
| simdjson (ondemand) | 756.806 | 0.368949 | 5983.81ms | 83958 | 640 | 9.75142e+07 | 105798 | 0.388277 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 604.13 | 0.122938 | 9773.85ms | 56369 | 640 | 7.65905e+06 | 88983.6 | 0.0283118 | 1(Win) | true |
| simdjson (ondemand) | 141.759 | 0.591842 | 5005.04ms | 56369 | 160 | 8.05959e+08 | 379219 | 0.119682 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 606.751 | 0.46766 | 10064.3ms | 56369 | 320 | 5.49377e+07 | 88599.2 | 0.455706 | 1(Win) | true |
| simdjson (ondemand) | 136.075 | 0.645708 | 9956.98ms | 56369 | 160 | 1.04116e+09 | 395059 | 1.04684 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 632.068 | 0.444647 | 6274.26ms | 83958 | 640 | 2.03052e+08 | 126677 | 0.200278 | 1(Win) | true |
| simdjson (ondemand) | 241.989 | 0.0684307 | 8740.98ms | 83958 | 1280 | 6.56213e+07 | 330877 | 0.0776725 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 793.9 | 0.193145 | 5586.81ms | 83958 | 2560 | 9.71399e+07 | 100855 | 0.493612 | 1(Win) | true |
| simdjson (ondemand) | 241.246 | 0.172899 | 8695.87ms | 83958 | 30 | 9.87891e+06 | 331895 | 0.161717 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1815.46 | 0.0859876 | 3129.07ms | 56369 | 2560 | 1.65967e+06 | 29611.1 | 0.114615 | 1(Win) | true |
| simdjson (ondemand) | 1180.45 | 0.37691 | 4325.91ms | 56369 | 1280 | 3.77113e+07 | 45540 | 0.479029 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2282.92 | 0.0923004 | 2989.3ms | 56369 | 2560 | 1.20934e+06 | 23547.8 | 0.054328 | 1(Win) | true |
| simdjson (ondemand) | 1560.26 | 0.571348 | 4129.45ms | 56369 | 160 | 6.20027e+06 | 34454.4 | 0.0649712 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2302.3 | 0.688589 | 3867.42ms | 83958 | 40 | 2.29393e+06 | 34777.6 | 0.232558 | 1(Win) | true |
| simdjson (ondemand) | 1752.57 | 0.240998 | 4758.32ms | 83958 | 4890 | 5.92801e+07 | 45686.3 | 0.633321 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2855.76 | 0.29536 | 3684.48ms | 83958 | 320 | 2.1945e+06 | 28037.6 | 0.0826776 | 1(Win) | true |
| simdjson (ondemand) | 2068.49 | 0.297629 | 4558.64ms | 83958 | 640 | 8.49473e+06 | 38708.8 | 2.0113 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1412.18 | 0.264221 | 3950.36ms | 56369 | 30 | 303499 | 38067.2 | 0.359955 | 1(Win) | true |
| simdjson (ondemand) | 1031.07 | 0.261174 | 5329.96ms | 56369 | 160 | 2.96675e+06 | 52137.6 | 0 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1744.94 | 0.0604989 | 3567.9ms | 56369 | 4890 | 1.69873e+06 | 30807.8 | 0.103633 | 1(Win) | true |
| simdjson (ondemand) | 1164.06 | 0.052252 | 5026.23ms | 56369 | 4890 | 2.84737e+06 | 46181.1 | 0.00680748 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1901.81 | 0.0533186 | 4304.53ms | 83958 | 4890 | 2.46409e+06 | 42101.3 | 0.0221426 | 1(Win) | true |
| simdjson (ondemand) | 1445.62 | 0.0460593 | 5645.07ms | 83958 | 4890 | 3.18245e+06 | 55387.2 | 0.0263588 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2215.23 | 0.0489999 | 4106.1ms | 83958 | 4890 | 1.53386e+06 | 36144.6 | 0.184696 | 1(Win) | true |
| simdjson (ondemand) | 1621.86 | 0.0518709 | 5351.08ms | 83958 | 4890 | 3.20666e+06 | 49368.4 | 0.179322 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1204.4 | 0.0560988 | 4293.37ms | 53331 | 4890 | 2.7443e+06 | 42228.7 | 0.154029 | 1(Win) | true |
| simdjson (ondemand) | 797.565 | 0.730746 | 6471.36ms | 53331 | 30 | 6.5145e+06 | 63769.6 | 1.17694 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1508.91 | 0.158201 | 4326.85ms | 53331 | 640 | 1.81984e+06 | 33706.8 | 0.00118672 | 1(Win) | true |
| simdjson (ondemand) | 985.135 | 0.0463861 | 5787.85ms | 53331 | 4890 | 2.80448e+06 | 51627.9 | 0.0152475 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1350.51 | 0.0547153 | 4716.07ms | 65103 | 4890 | 3.09409e+06 | 45973 | 0.175029 | 1(Win) | true |
| simdjson (ondemand) | 1008.92 | 0.0742863 | 6204.45ms | 65103 | 4890 | 1.02192e+07 | 61538.3 | 0.0102655 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1668.13 | 0.0735513 | 4339.84ms | 65103 | 2560 | 1.91851e+06 | 37219.6 | 0.0687337 | 1(Win) | true |
| simdjson (ondemand) | 1181.3 | 0.174247 | 5990.19ms | 65103 | 320 | 2.68389e+06 | 52558.4 | 0.0699684 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 901.176 | 0.0679872 | 5670.39ms | 53331 | 2560 | 3.76907e+06 | 56437.8 | 0.00956714 | 1(Win) | true |
| simdjson (ondemand) | 438.955 | 0.0477138 | 6052.75ms | 53331 | 2560 | 7.82431e+06 | 115867 | 0.0494289 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1073.77 | 0.0887721 | 5489.87ms | 53331 | 1280 | 2.26308e+06 | 47366.2 | 0.0654904 | 1(Win) | true |
| simdjson (ondemand) | 479.579 | 0.335027 | 5828.96ms | 53331 | 30 | 3.78723e+06 | 106052 | 0.104493 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 981.471 | 0.123093 | 6480.28ms | 65103 | 640 | 3.88055e+06 | 63259.2 | 0.0341336 | 1(Win) | true |
| simdjson (ondemand) | 538.076 | 0.19829 | 6121.67ms | 65103 | 160 | 8.37601e+06 | 115387 | 0.184083 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1154.89 | 0.174361 | 6109.18ms | 65103 | 320 | 2.81168e+06 | 53760 | 0.0595593 | 1(Win) | true |
| simdjson (ondemand) | 588.669 | 0.0519247 | 5748.06ms | 65103 | 2560 | 7.67798e+06 | 105470 | 0.417703 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5543.07 | 0.130093 | 928.822ms | 53331 | 2560 | 364761 | 9175.5 | 0.179504 | 1(Win) | true |
| simdjson (ondemand) | 4105.95 | 0.181565 | 1249.67ms | 53331 | 1280 | 647447 | 12387 | 0.130611 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6202.64 | 0.184119 | 867.355ms | 53331 | 1280 | 291751 | 8199.8 | 0.138835 | 1(Win) | true |
| simdjson (ondemand) | 4436.15 | 0.0960279 | 1181.15ms | 53331 | 4890 | 592721 | 11465 | 0.0751436 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5425.67 | 0.274884 | 1152.32ms | 65103 | 640 | 633248 | 11443.2 | 0.00699056 | 1(Win) | true |
| simdjson (ondemand) | 4513.45 | 0.318823 | 1384.49ms | 65103 | 640 | 1.23101e+06 | 13756 | 0.00581598 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5939.98 | 0.188125 | 1080.7ms | 65103 | 1280 | 494921 | 10452.4 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4846.88 | 0.118594 | 1314.47ms | 65103 | 2560 | 590805 | 12809.7 | 0.191628 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4055.95 | 0.089654 | 1289.33ms | 53331 | 4890 | 618049 | 12539.7 | 0.100323 | 1(Win) | true |
| simdjson (ondemand) | 2726.21 | 0.0977351 | 1920.19ms | 53331 | 2560 | 851104 | 18656.1 | 0.122598 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4382.44 | 0.117055 | 1229.79ms | 53331 | 2560 | 472439 | 11605.5 | 0.0784726 | 1(Win) | true |
| simdjson (ondemand) | 2730.33 | 0.10963 | 1969.86ms | 53331 | 4890 | 2.03936e+06 | 18627.9 | 1.70388 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4032.05 | 0.527582 | 1553.57ms | 65103 | 40 | 263992 | 15398.4 | 0.468836 | 1(Win) | true |
| simdjson (ondemand) | 3108.71 | 0.201831 | 2059.31ms | 65103 | 320 | 519958 | 19972 | 0.163961 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4432.07 | 0.176292 | 1509.83ms | 65103 | 1280 | 780664 | 14008.6 | 0.00999286 | 1(Win) | true |
| simdjson (ondemand) | 3228.3 | 0.12845 | 1944.73ms | 65103 | 2560 | 1.56228e+06 | 19232.1 | 0.213119 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 868.848 | 0.0940537 | 1304.13ms | 11812 | 4890 | 727144 | 12965.2 | 0.0171418 | 1(Win) | true |
| simdjson (ondemand) | 668.106 | 0.247169 | 1703.9ms | 11812 | 80 | 138943 | 16860.8 | 0.0948047 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 949.829 | 0.0843106 | 1263.82ms | 11812 | 4890 | 488910 | 11859.8 | 0.0546494 | 1(Win) | true |
| simdjson (ondemand) | 710.516 | 0.198893 | 1723.51ms | 11812 | 640 | 636384 | 15854.4 | 0.0605144 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1676.17 | 0.563618 | 1593.53ms | 25388 | 40 | 265127 | 14444.8 | 0.132743 | 1(Win) | true |
| simdjson (ondemand) | 1293.18 | 0.173926 | 1889.03ms | 25388 | 640 | 678659 | 18722.8 | 0.125891 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1790.9 | 0.157812 | 1433.04ms | 25388 | 1280 | 582644 | 13519.4 | 0.137391 | 1(Win) | true |
| simdjson (ondemand) | 1366.07 | 0.0962434 | 1849.32ms | 25388 | 2560 | 744887 | 17723.7 | 0.0457224 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 623.764 | 0.0868286 | 1844.46ms | 11812 | 2560 | 629466 | 18059.4 | 0.0166091 | 1(Win) | true |
| simdjson (ondemand) | 482.205 | 0.147442 | 2336ms | 11812 | 1280 | 1.51857e+06 | 23361 | 0.108847 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 663.322 | 0.197687 | 1833.02ms | 11812 | 320 | 360664 | 16982.4 | 0.0282566 | 1(Win) | true |
| simdjson (ondemand) | 501.532 | 0.622922 | 2344.49ms | 11812 | 160 | 3.13212e+06 | 22460.8 | 0.128059 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1194.52 | 0.0817414 | 2040.25ms | 25388 | 2560 | 702743 | 20269.2 | 0.138934 | 1(Win) | true |
| simdjson (ondemand) | 973.522 | 0.112436 | 2503.94ms | 25388 | 1280 | 1.00088e+06 | 24870.4 | 0.0899859 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1267.8 | 0.229182 | 2044.54ms | 25388 | 40 | 76626.7 | 19097.6 | 0.0447027 | 1(Win) | true |
| simdjson (ondemand) | 1017.08 | 0.0803529 | 2463.77ms | 25388 | 2560 | 936679 | 23805.3 | 0.0163856 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1561.63 | 0.11316 | 724.015ms | 11812 | 4890 | 325824 | 7213.49 | 0.134377 | 1(Win) | true |
| simdjson (ondemand) | 1307.63 | 0.111681 | 869.219ms | 11812 | 4890 | 452637 | 8614.69 | 0.0893219 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1641.26 | 0.12876 | 708.84ms | 11812 | 4890 | 381911 | 6863.52 | 0.335092 | 1(Win) | true |
| simdjson (ondemand) | 1357.07 | 0.310388 | 855.408ms | 11812 | 640 | 424846 | 8300.8 | 0.0771605 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2782.98 | 0.276761 | 987.351ms | 25388 | 640 | 371047 | 8700 | 0.211048 | 1(Win) | true |
| simdjson (ondemand) | 2003.78 | 0.35185 | 1162.94ms | 25388 | 2560 | 4.62714e+06 | 12083.1 | 0.213147 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2727.73 | 0.24585 | 939.874ms | 25388 | 1280 | 609543 | 8876.2 | 0.424052 | 1(Win) | true |
| simdjson (ondemand) | 2388 | 0.168207 | 1036.09ms | 25388 | 1280 | 372298 | 10139 | 0.267009 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1227.18 | 0.162918 | 924.271ms | 11812 | 1280 | 286270 | 9179.4 | 0.293274 | 1(Win) | true |
| simdjson (ondemand) | 1136.38 | 0.112887 | 996.802ms | 11812 | 2560 | 320574 | 9912.9 | 0.0292463 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1276.53 | 0.0984402 | 914.22ms | 11812 | 4890 | 369012 | 8824.57 | 0.0166161 | 1(Win) | true |
| simdjson (ondemand) | 1180.6 | 0.388953 | 1017.39ms | 11812 | 320 | 440744 | 9541.6 | 0.125923 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2256.97 | 0.122904 | 1079.88ms | 25388 | 2560 | 445018 | 10727.6 | 0.0782414 | 1(Win) | true |
| simdjson (ondemand) | 2060.38 | 0.213502 | 1194.92ms | 25388 | 640 | 402856 | 11751.2 | 0.0817606 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2328.64 | 0.101452 | 1107.46ms | 25388 | 4890 | 544099 | 10397.4 | 0.308929 | 1(Win) | true |
| simdjson (ondemand) | 2043.27 | 0.352641 | 1282.03ms | 25388 | 80 | 139689 | 11849.6 | 0.134844 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1171.66 | 0.26957 | 8871.77ms | 108313 | 1280 | 7.22955e+07 | 88161.6 | 0.36932 | 1(Win) | true |
| simdjson (ondemand) | 1123.75 | 0.0916164 | 9354.92ms | 108313 | 640 | 4.53886e+06 | 91920 | 0.0383088 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1411.42 | 0.112132 | 8119ms | 108313 | 640 | 4.31009e+06 | 73185.6 | 0.0360597 | 1(Win) | true |
| simdjson (ondemand) | 1230.46 | 0.174757 | 8947.57ms | 108313 | 80 | 1.72181e+06 | 83948.8 | 0.252216 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1957.29 | 0.0551566 | 9040.82ms | 183677 | 2560 | 6.23785e+06 | 89495.3 | 0.117076 | 1(Win) | true |
| simdjson (ondemand) | 1725.71 | 0.139757 | 5383.58ms | 183677 | 320 | 6.43978e+06 | 101505 | 0.0291697 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2106.96 | 0.0542009 | 8625.87ms | 183677 | 2560 | 5.19817e+06 | 83137.9 | 0.0465275 | 1(Win) | true |
| simdjson (ondemand) | 1878.45 | 0.131186 | 9735.58ms | 183677 | 320 | 4.78884e+06 | 93251.2 | 0.0360447 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 533.065 | 0.0508408 | 10014.1ms | 108313 | 1280 | 1.24233e+07 | 193776 | 0.026739 | 1(Win) | true |
| simdjson (ondemand) | 221.204 | 0.11164 | 5951.51ms | 108313 | 160 | 4.34844e+07 | 466968 | 0.15958 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 552.149 | 0.0613876 | 9857.01ms | 108313 | 1280 | 1.68819e+07 | 187079 | 0.231238 | 1(Win) | true |
| simdjson (ondemand) | 221.196 | 0.177936 | 6079.86ms | 108313 | 320 | 2.20945e+08 | 466986 | 0.358805 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 788.318 | 0.158314 | 5718.47ms | 183677 | 160 | 1.98001e+07 | 222205 | 0.0158387 | 1(Win) | true |
| simdjson (ondemand) | 375.002 | 0.10309 | 5982.73ms | 183677 | 160 | 3.71017e+07 | 467112 | 0.0476344 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 822.284 | 0.319549 | 5610.09ms | 183677 | 30 | 1.39015e+07 | 213026 | 0.0400416 | 1(Win) | true |
| simdjson (ondemand) | 380.102 | 0.112852 | 5994.4ms | 183677 | 320 | 8.65519e+07 | 460845 | 0.075049 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3368.42 | 0.113952 | 3143.35ms | 108313 | 1280 | 1.56301e+06 | 30665.8 | 0.143927 | 1(Win) | true |
| simdjson (ondemand) | 2806.38 | 0.0564108 | 3689.6ms | 108313 | 4890 | 2.10815e+06 | 36807.4 | 0.00908589 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3571.56 | 0.172103 | 2991.43ms | 108313 | 40 | 99102.2 | 28921.6 | 0.0664305 | 1(Win) | true |
| simdjson (ondemand) | 3206.97 | 0.0914879 | 3296.28ms | 108313 | 1280 | 1.1115e+06 | 32209.6 | 0.0794163 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4525.65 | 0.146389 | 3981.8ms | 183677 | 640 | 2.05469e+06 | 38705.6 | 0.0124028 | 1(Win) | true |
| simdjson (ondemand) | 3811.07 | 0.0752272 | 4682.24ms | 183677 | 2560 | 3.06058e+06 | 45962.9 | 0.136164 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4733.78 | 0.0539962 | 3807.43ms | 183677 | 4890 | 1.95222e+06 | 37003.8 | 0.00748112 | 1(Win) | true |
| simdjson (ondemand) | 4232.63 | 0.120152 | 4168.88ms | 183677 | 640 | 1.58245e+06 | 41385.2 | 0.00676525 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2469.48 | 0.186256 | 4297.27ms | 108313 | 320 | 1.94233e+06 | 41828.8 | 0.110805 | 1(Win) | true |
| simdjson (ondemand) | 1983.95 | 0.143966 | 5354.56ms | 108313 | 320 | 1.79792e+06 | 52065.6 | 0.0338149 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2572.22 | 0.0777908 | 4097.48ms | 108313 | 2560 | 2.49828e+06 | 40158 | 0.0313662 | 1(Win) | true |
| simdjson (ondemand) | 2045.97 | 0.0644414 | 5230.52ms | 108313 | 2560 | 2.70977e+06 | 50487.2 | 0.0902384 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3421.54 | 0.049653 | 5193.8ms | 183677 | 4890 | 3.15985e+06 | 51195.7 | 0.10002 | 1(Win) | true |
| simdjson (ondemand) | 2853.12 | 0.112388 | 6687.26ms | 183677 | 640 | 3.04711e+06 | 61395.2 | 0.0273712 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3554.66 | 0.289603 | 5028.79ms | 183677 | 160 | 3.25866e+06 | 49278.4 | 0.107261 | 1(Win) | true |
| simdjson (ondemand) | 2925.71 | 0.548635 | 6969.35ms | 183677 | 40 | 4.31592e+06 | 59872 | 0.117723 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 452.792 | 0.144491 | 5777.18ms | 1834197 | 40 | 1.24635e+09 | 3.8632e+06 | 0.982965 | 1(Win) | true |
| Jsonifier (generic) | 349.597 | 1.38553 | 6653.81ms | 1834197 | 40 | 1.92242e+11 | 5.00355e+06 | 0.881536 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 505.098 | 0.0579649 | 6080.19ms | 1834197 | 30 | 1.20891e+08 | 3.46314e+06 | 0.519419 | 1(Win) | true |
| simdjson (ondemand) | 488.595 | 0.567742 | 5882.39ms | 1834197 | 30 | 1.23942e+10 | 3.58012e+06 | 2.28713 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1467.01 | 0.17159 | 7123.27ms | 7351818 | 80 | 5.3802e+09 | 4.77928e+06 | 2.86042 | 1(Win) | true |
| simdjson (ondemand) | 1206.37 | 1.26292 | 8163.25ms | 7351818 | 30 | 1.61623e+11 | 5.81186e+06 | 3.75202 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1586.76 | 0.504594 | 7277.67ms | 7351818 | 30 | 1.49134e+10 | 4.4186e+06 | 0.638037 | 1(Win) | true |
| simdjson (ondemand) | 1456.14 | 0.808897 | 7628.72ms | 7351818 | 30 | 4.55084e+10 | 4.81495e+06 | 1.41705 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 241.37 | 0.813649 | 10279.5ms | 1834197 | 30 | 1.04309e+11 | 7.24707e+06 | 0.179299 | 1(Win) | true |
| simdjson (ondemand) | 200.12 | 0.459357 | 6107.31ms | 1834197 | 30 | 4.83653e+10 | 8.7409e+06 | 0.657506 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 320.093 | 0.212595 | 8843.23ms | 1834197 | 80 | 1.07979e+10 | 5.46475e+06 | 0.378132 | 1(Win) | true |
| simdjson (ondemand) | 210.897 | 0.0481429 | 6231ms | 1834197 | 30 | 4.7834e+08 | 8.29421e+06 | 0.247539 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 972.29 | 0.567416 | 5088.95ms | 7351818 | 40 | 6.69671e+10 | 7.21106e+06 | 4.95565 | 1(Win) | true |
| simdjson (ondemand) | 597.283 | 0.758623 | 8284.24ms | 7351818 | 40 | 3.17206e+11 | 1.17385e+07 | 2.25099 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1011.69 | 0.307222 | 5094.75ms | 7351818 | 30 | 1.35993e+10 | 6.93019e+06 | 0.860278 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 688.63 | 0.901432 | 7715.01ms | 7351818 | 40 | 3.36933e+11 | 1.01814e+07 | 6.74014 | -(Loss) | false |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2731.68 | 0.0959368 | 8208.85ms | 1834197 | 160 | 6.03842e+07 | 640349 | 0.0760163 | 1(Win) | true |
| Jsonifier (generic) | 2337.92 | 1.15442 | 9893.04ms | 1834197 | 80 | 5.96835e+09 | 748198 | 3.5281 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2739.93 | 0.158065 | 8212.02ms | 1834197 | 40 | 4.07328e+07 | 638419 | 0.0491455 | 1(Win) | true |
| Jsonifier (generic) | 2576.6 | 0.243485 | 8941.37ms | 1834197 | 320 | 8.74366e+08 | 678889 | 1.96563 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5807.02 | 0.583201 | 8310.8ms | 7351818 | 40 | 1.98326e+09 | 1.20737e+06 | 0.92588 | 1(Win) | true |
| simdjson (ondemand) | 5158.7 | 0.506065 | 9014.3ms | 7351818 | 80 | 3.78453e+09 | 1.35911e+06 | 0.000941801 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5794.24 | 0.318813 | 7972.11ms | 7351818 | 160 | 2.38116e+09 | 1.21004e+06 | 0.952789 | 1(Win) | true |
| simdjson (ondemand) | 4881.12 | 0.304538 | 9423.31ms | 7351818 | 160 | 3.06162e+09 | 1.4364e+06 | 0.47622 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1773.09 | 0.58438 | 6661.22ms | 1834197 | 30 | 9.97102e+08 | 986539 | 1.35581 | 1(Win) | true |
| simdjson (ondemand) | 1555.42 | 0.259966 | 7593.92ms | 1834197 | 30 | 2.5642e+08 | 1.1246e+06 | 4.41048 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1551.07 | 0.870788 | 6318.12ms | 1834197 | 40 | 3.85758e+09 | 1.12776e+06 | 0.0121052 | 1(Win) | true |
| simdjson (ondemand) | 1456.56 | 0.161352 | 7719.77ms | 1834197 | 320 | 1.20153e+09 | 1.20093e+06 | 0.450003 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4413.22 | 0.652066 | 10448.1ms | 7351818 | 80 | 8.58523e+09 | 1.58869e+06 | 1.37255 | 1(Win) | true |
| simdjson (ondemand) | 3801.45 | 1.2607 | 6053.93ms | 7351818 | 30 | 1.62194e+10 | 1.84436e+06 | 1.49994 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4341.11 | 0.760309 | 5012.85ms | 7351818 | 80 | 1.20631e+10 | 1.61508e+06 | 1.28056 | 1(Win) | true |
| simdjson (ondemand) | 3486.08 | 0.629373 | 6243.2ms | 7351818 | 160 | 2.56361e+10 | 2.01121e+06 | 1.13105 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 799.496 | 2.19983 | 6020.34ms | 409725 | 30 | 3.46778e+09 | 488738 | 1.17472 | 1(Win) | true |
| simdjson (ondemand) | 607.201 | 0.0822116 | 8292.89ms | 409725 | 320 | 8.95645e+07 | 643517 | 0.0407926 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1207.14 | 0.24974 | 5193.12ms | 409725 | 30 | 1.96051e+07 | 323695 | 0.351852 | 1(Win) | true |
| simdjson (ondemand) | 706.767 | 0.0825783 | 8063.32ms | 409725 | 320 | 6.66983e+07 | 552862 | 0.0482089 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1426.2 | 0.137957 | 6371.12ms | 676745 | 80 | 3.11795e+07 | 452528 | 0.526856 | 1(Win) | true |
| simdjson (ondemand) | 893.573 | 0.467604 | 5036.99ms | 676745 | 80 | 9.12507e+08 | 722262 | 1.2923 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1480.38 | 0.294159 | 6253.82ms | 676745 | 640 | 1.05256e+09 | 435965 | 0.954997 | 1(Win) | true |
| simdjson (ondemand) | 948.756 | 0.355704 | 9513.92ms | 676745 | 640 | 3.74712e+09 | 680253 | 0.0576511 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 529.097 | 0.754647 | 8681.2ms | 409725 | 80 | 2.48481e+09 | 738512 | 2.932 | 1(Win) | true |
| simdjson (ondemand) | 349.488 | 0.103909 | 7135.64ms | 409725 | 40 | 5.39872e+07 | 1.11805e+06 | 0.0410071 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 718.13 | 0.310835 | 7622.43ms | 409725 | 160 | 4.57677e+08 | 544114 | 1.84465 | 1(Win) | true |
| simdjson (ondemand) | 379.191 | 0.0713388 | 6990.32ms | 409725 | 160 | 8.64652e+07 | 1.03047e+06 | 0.0427173 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 931.361 | 0.0833488 | 8937.62ms | 676745 | 160 | 5.33744e+07 | 692958 | 0.204384 | 1(Win) | true |
| simdjson (ondemand) | 560.949 | 0.160397 | 7587.88ms | 676745 | 30 | 1.02169e+08 | 1.15054e+06 | 0.01928 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1065.77 | 0.139459 | 8773.63ms | 676745 | 320 | 2.28227e+08 | 605568 | 0.122746 | 1(Win) | true |
| simdjson (ondemand) | 580.883 | 0.569943 | 7503.74ms | 676745 | 30 | 1.20297e+09 | 1.11106e+06 | 1.15244 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1484.98 | 0.253717 | 6564.76ms | 409725 | 640 | 2.85249e+08 | 263131 | 0.229919 | 1(Win) | true |
| simdjson (ondemand) | 1105.81 | 0.455145 | 9521.56ms | 409725 | 40 | 1.03464e+08 | 353357 | 0.554755 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1714.1 | 0.178824 | 6473.44ms | 409725 | 1280 | 2.12704e+08 | 227959 | 1.64133 | 1(Win) | true |
| simdjson (ondemand) | 1204.74 | 0.503409 | 9318.51ms | 409725 | 40 | 1.06635e+08 | 324339 | 0.347176 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2141.58 | 0.818943 | 7757.73ms | 676745 | 30 | 1.8273e+08 | 301363 | 0.0992035 | 1(Win) | true |
| simdjson (ondemand) | 1621.2 | 0.595303 | 5118.1ms | 676745 | 30 | 1.6849e+08 | 398097 | 0.435376 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2422.82 | 0.142513 | 7516.16ms | 676745 | 320 | 4.61178e+07 | 266382 | 0.0477283 | 1(Win) | true |
| simdjson (ondemand) | 1794.42 | 0.610066 | 9713.24ms | 676745 | 40 | 1.92582e+08 | 359667 | 0.0486612 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1291.14 | 0.486551 | 7815.7ms | 409725 | 320 | 6.93819e+08 | 302635 | 0.121217 | 1(Win) | true |
| simdjson (ondemand) | 969.227 | 0.087431 | 5349.57ms | 409725 | 320 | 3.97571e+07 | 403150 | 0.0341428 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1479.41 | 0.4386 | 7245.6ms | 409725 | 40 | 5.3679e+07 | 264122 | 0.639733 | 1(Win) | true |
| simdjson (ondemand) | 1055.58 | 0.118975 | 5074.01ms | 409725 | 160 | 3.10335e+07 | 370170 | 0.0337029 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1970.75 | 0.0909846 | 8828.51ms | 676745 | 160 | 1.4205e+07 | 327486 | 0.164377 | 1(Win) | true |
| simdjson (ondemand) | 1487.38 | 0.0803659 | 5620.3ms | 676745 | 320 | 3.89133e+07 | 433913 | 0.00755969 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2196.81 | 0.0927095 | 8306.07ms | 676745 | 320 | 2.37389e+07 | 293786 | 0.0857031 | 1(Win) | true |
| simdjson (ondemand) | 1611.27 | 0.115169 | 5446.69ms | 676745 | 160 | 3.40492e+07 | 400550 | 0.0183713 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1617.46 | 0.0830865 | 8060.97ms | 264040 | 640 | 1.07081e+07 | 155681 | 0.0523875 | 1(Win) | true |
| simdjson (ondemand) | 1291.74 | 0.211445 | 10037.9ms | 264040 | 320 | 5.43669e+07 | 194937 | 0.0619304 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1967.71 | 0.0932995 | 7877.83ms | 264040 | 640 | 9.12337e+06 | 127970 | 0.102316 | 1(Win) | true |
| simdjson (ondemand) | 1510.92 | 0.244016 | 5123.81ms | 264040 | 80 | 1.32308e+07 | 166659 | 0.0594873 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1693.34 | 0.561383 | 5133.3ms | 360584 | 320 | 4.15904e+08 | 203078 | 0.372869 | 1(Win) | true |
| simdjson (ondemand) | 1671.1 | 0.169855 | 5264.5ms | 360584 | 160 | 1.95472e+07 | 205781 | 0.112614 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2408.79 | 0.0930803 | 8559.18ms | 360584 | 1280 | 2.26017e+07 | 142760 | 0.0655214 | 1(Win) | true |
| simdjson (ondemand) | 1940.86 | 0.133404 | 5105.01ms | 360584 | 160 | 8.93894e+06 | 177179 | 0.0261813 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 631.711 | 0.144265 | 5082.61ms | 264040 | 160 | 5.2911e+07 | 398613 | 0.0349333 | 1(Win) | true |
| simdjson (ondemand) | 283.668 | 0.0987232 | 5648.65ms | 264040 | 80 | 6.14395e+07 | 887686 | 0.0475617 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 682.981 | 0.0740468 | 5054.84ms | 264040 | 320 | 2.38498e+07 | 368690 | 0.166922 | 1(Win) | true |
| simdjson (ondemand) | 293.268 | 0.0868639 | 5657.4ms | 264040 | 160 | 8.90036e+07 | 858627 | 0.115293 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 778.685 | 0.342178 | 5661.65ms | 360584 | 320 | 7.30708e+08 | 441616 | 0.354163 | 1(Win) | true |
| simdjson (ondemand) | 390.125 | 0.103506 | 5791.13ms | 360584 | 160 | 1.33187e+08 | 881461 | 0.0948433 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 849.613 | 0.191763 | 5595.11ms | 360584 | 40 | 2.40969e+07 | 404749 | 0.387475 | 1(Win) | true |
| simdjson (ondemand) | 403.412 | 0.122554 | 5858.76ms | 360584 | 160 | 1.7462e+08 | 852429 | 2.72524 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4559.63 | 0.382716 | 6301.17ms | 264040 | 80 | 3.57374e+06 | 55225.6 | 0.185078 | 1(Win) | true |
| simdjson (ondemand) | 3531.45 | 0.721081 | 7919.88ms | 264040 | 30 | 7.93091e+06 | 71304.5 | 0.131469 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4743.01 | 0.174456 | 6515.49ms | 264040 | 320 | 2.74506e+06 | 53090.4 | 0.188713 | 1(Win) | true |
| simdjson (ondemand) | 3336.73 | 0.983484 | 7528.53ms | 264040 | 80 | 4.40679e+07 | 75465.6 | 0.370276 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4950.06 | 0.640097 | 7677.75ms | 360584 | 30 | 5.93206e+06 | 69469.9 | 0.0981716 | 1(Win) | true |
| simdjson (ondemand) | 3630.03 | 0.253649 | 9556.44ms | 360584 | 2560 | 1.47808e+08 | 94731.8 | 0.617736 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4665.18 | 0.663492 | 7840.09ms | 360584 | 80 | 1.91354e+07 | 73712 | 0.169021 | 1(Win) | true |
| simdjson (ondemand) | 4178.65 | 0.69691 | 8962.43ms | 360584 | 80 | 2.63139e+07 | 82294.4 | 0.62983 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2975.79 | 0.112913 | 8893.46ms | 264040 | 4890 | 4.46409e+07 | 84618.9 | 0.945503 | 1(Win) | true |
| simdjson (ondemand) | 2591.15 | 0.0943312 | 5082.42ms | 264040 | 640 | 5.37829e+06 | 97180 | 0.0575918 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3127 | 0.172787 | 8073.44ms | 264040 | 2560 | 4.95618e+07 | 80527.1 | 1.42463 | 1(Win) | true |
| simdjson (ondemand) | 2653.16 | 0.213905 | 5018.09ms | 264040 | 160 | 6.5944e+06 | 94908.8 | 0.0707547 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3684.97 | 0.0704316 | 9900.25ms | 360584 | 1280 | 5.52956e+06 | 93319.6 | 0.142509 | 1(Win) | true |
| simdjson (ondemand) | 2861.7 | 0.906759 | 6603.41ms | 360584 | 30 | 3.56181e+07 | 120166 | 0.0567779 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3216.76 | 0.771244 | 5529.53ms | 360584 | 80 | 5.43811e+07 | 106902 | 0.321321 | 1(Win) | true |
| simdjson (ondemand) | 2836.23 | 0.268897 | 6333.88ms | 360584 | 1280 | 1.36054e+08 | 121245 | 0.209767 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 941.088 | 0.808477 | 260.671ms | 2632 | 2560 | 1.19038e+06 | 2667.2 | 1.63741 | 1(Win) | true |
| simdjson (ondemand) | 775.911 | 0.435142 | 330.979ms | 2632 | 1280 | 253642 | 3235 | 0.53499 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1436.33 | 0.459707 | 207.42ms | 2632 | 4890 | 315597 | 1747.55 | 0.656394 | 1(Win) | true |
| simdjson (ondemand) | 1010.84 | 0.502589 | 298.092ms | 2632 | 4890 | 761624 | 2483.15 | 0.407185 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1142.43 | 0.883271 | 274.716ms | 3370 | 640 | 395157 | 2813.2 | 7.4118 | -(Win) | false |
| simdjson (ondemand) | 886.859 | 0.285895 | 359.707ms | 3370 | 4890 | 524895 | 3623.89 | 0.196086 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1671.98 | 0.78529 | 224.798ms | 3370 | 1280 | 291653 | 1922.2 | 0.617672 | 1(Win) | true |
| simdjson (ondemand) | 1172.75 | 0.504969 | 296.631ms | 3370 | 4890 | 936447 | 2740.46 | 1.50392 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 804.009 | 0.217475 | 315.499ms | 2632 | 4890 | 225413 | 3121.94 | 0.284076 | 1(Win) | true |
| simdjson (ondemand) | 487.467 | 0.124176 | 526.043ms | 2632 | 4890 | 199923 | 5149.21 | 0.0235484 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1157.4 | 0.272136 | 256.606ms | 2632 | 4890 | 170329 | 2168.72 | 0.735852 | 1(Win) | true |
| simdjson (ondemand) | 454.888 | 0.672618 | 572.137ms | 2632 | 640 | 881617 | 5518 | 0.555075 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 843.982 | 0.834265 | 381.396ms | 3370 | 640 | 645924 | 3808 | 3.38949 | 1(Win) | true |
| simdjson (ondemand) | 579.776 | 0.181575 | 559.17ms | 3370 | 4890 | 495403 | 5543.32 | 0.511214 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1295.15 | 0.333313 | 281.745ms | 3370 | 4890 | 334528 | 2481.47 | 0.9669 | 1(Win) | true |
| simdjson (ondemand) | 676.297 | 0.202839 | 507.405ms | 3370 | 4890 | 454355 | 4752.18 | 0.233631 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2126.41 | 0.502404 | 122.811ms | 2632 | 4890 | 171986 | 1180.43 | 0.74607 | 1(Win) | true |
| simdjson (ondemand) | 1385.25 | 0.503256 | 183.571ms | 2632 | 2560 | 212880 | 1812 | 0.454596 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3138.67 | 0.746543 | 89.5939ms | 2632 | 4890 | 174301 | 799.725 | 0.370605 | 1(Win) | true |
| simdjson (ondemand) | 1919.77 | 0.52206 | 143.433ms | 2632 | 4890 | 227836 | 1307.48 | 0.654611 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2378.73 | 0.522168 | 137.391ms | 3370 | 4890 | 243389 | 1351.09 | 0.0143357 | 1(Win) | true |
| simdjson (ondemand) | 1812.68 | 0.513692 | 183.39ms | 3370 | 2560 | 212356 | 1773 | 1.03716 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3472.3 | 0.507503 | 102.183ms | 3370 | 4890 | 107898 | 925.579 | 0.203392 | 1(Win) | true |
| simdjson (ondemand) | 2135.75 | 2.14726 | 156.663ms | 3370 | 320 | 334099 | 1504.8 | 0.373533 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1533.71 | 0.940258 | 166.7ms | 2632 | 1280 | 303102 | 1636.6 | 1.52605 | 1(Win) | true |
| simdjson (ondemand) | 1251.97 | 0.657919 | 203.497ms | 2632 | 2560 | 445420 | 2004.9 | 0.0648832 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2322.42 | 1.48501 | 120.373ms | 2632 | 320 | 82433 | 1080.8 | 0.0739645 | 1(Win) | true |
| simdjson (ondemand) | 1595.28 | 0.463435 | 166.039ms | 2632 | 4890 | 260005 | 1573.43 | 0.00200158 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1960.64 | 0.869617 | 165.518ms | 3370 | 1280 | 260094 | 1639.2 | 0.342801 | 1(Win) | true |
| simdjson (ondemand) | 1624.49 | 0.294041 | 199.775ms | 3370 | 2560 | 86632.9 | 1978.4 | 0.0910655 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2668.45 | 0.962705 | 128.573ms | 3370 | 1280 | 172083 | 1204.4 | 0.066379 | 1(Win) | true |
| simdjson (ondemand) | 2080.25 | 0.482453 | 165.977ms | 3370 | 4890 | 271675 | 1544.95 | 0.197947 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 517.783 | 0.11112 | 858.619ms | 4630 | 4890 | 439096 | 8527.73 | 0.101545 | 1(Win) | true |
| simdjson (ondemand) | 499.922 | 0.267676 | 888.864ms | 4630 | 640 | 357730 | 8832.4 | 0.0226388 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 593.577 | 0.127398 | 863.716ms | 4630 | 4890 | 439176 | 7438.82 | 0.173926 | 1(Win) | true |
| simdjson (ondemand) | 572.098 | 0.177148 | 886.964ms | 4630 | 2560 | 478556 | 7718.1 | 0.112595 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1186.25 | 0.175482 | 937.08ms | 11579 | 1280 | 341556 | 9308.8 | 0.0300881 | 1(Win) | true |
| simdjson (ondemand) | 1153.03 | 0.21781 | 1011.92ms | 11579 | 1280 | 556962 | 9577 | 0.285286 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1345.72 | 0.132293 | 932.42ms | 11579 | 2560 | 301677 | 8205.7 | 0.295261 | 1(Win) | true |
| simdjson (ondemand) | 1302.33 | 0.117221 | 957.344ms | 11579 | 4890 | 483080 | 8479.1 | 0.023618 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 479.52 | 0.172515 | 927.743ms | 4630 | 1280 | 323008 | 9208.2 | 0.023886 | 1(Win) | true |
| simdjson (ondemand) | 458.402 | 0.260987 | 976.412ms | 4630 | 640 | 404472 | 9632.4 | 0.335237 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 541.462 | 0.13535 | 926.595ms | 4630 | 2560 | 311877 | 8154.8 | 0.12003 | 1(Win) | true |
| simdjson (ondemand) | 516.138 | 0.141243 | 966.197ms | 4630 | 2560 | 373768 | 8554.9 | 0.00350689 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1104.64 | 0.154514 | 1006.27ms | 11579 | 1280 | 305385 | 9996.6 | 0.0220123 | 1(Win) | true |
| simdjson (ondemand) | 1055.21 | 0.282867 | 1047.36ms | 11579 | 1280 | 1.12159e+06 | 10464.8 | 0.137415 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1234.42 | 0.125614 | 1006.64ms | 11579 | 2560 | 323247 | 8945.6 | 0.228566 | 1(Win) | true |
| simdjson (ondemand) | 1177.75 | 0.330867 | 1165.91ms | 11579 | 320 | 307958 | 9376 | 0.0170678 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4909.95 | 0.511597 | 92.2532ms | 4630 | 4890 | 103508 | 899.298 | 0.332688 | 1(Win) | true |
| simdjson (ondemand) | 4184.53 | 0.64048 | 108.714ms | 4630 | 1280 | 58464.2 | 1055.2 | 0.15186 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4932.43 | 0.981368 | 93.5501ms | 4630 | 1280 | 98790.1 | 895.2 | 0.400534 | 1(Win) | true |
| simdjson (ondemand) | 4228.58 | 0.307273 | 107.108ms | 4630 | 4890 | 50342.1 | 1044.21 | 0.171341 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6956.36 | 0.471235 | 160.829ms | 11579 | 4890 | 273629 | 1587.41 | 0.0825551 | 1(Win) | true |
| simdjson (ondemand) | 6121.17 | 0.488605 | 183.111ms | 11579 | 2560 | 198897 | 1804 | 0.022168 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 7046.97 | 0.898346 | 161.793ms | 11579 | 1280 | 253650 | 1567 | 0.603493 | 1(Win) | true |
| simdjson (ondemand) | 5496.14 | 0.332267 | 198.335ms | 11579 | 4890 | 217927 | 2009.16 | 0.111613 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3761.96 | 0.48676 | 120.805ms | 4630 | 4890 | 159615 | 1173.73 | 0.201856 | 1(Win) | true |
| simdjson (ondemand) | 3183.04 | 1.41484 | 138.66ms | 4630 | 640 | 246532 | 1387.2 | 0.231214 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3837.97 | 0.462185 | 119.196ms | 4630 | 4890 | 138261 | 1150.48 | 0.172555 | 1(Win) | true |
| simdjson (ondemand) | 3351.18 | 1.18525 | 134.848ms | 4630 | 1280 | 312174 | 1317.6 | 0.396221 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5940.71 | 0.308646 | 189.993ms | 11579 | 4890 | 160952 | 1858.8 | 0.166453 | 1(Win) | true |
| simdjson (ondemand) | 5344.66 | 0.26701 | 210.091ms | 11579 | 2560 | 77910.8 | 2066.1 | 0.207689 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5934.96 | 0.429857 | 186.665ms | 11579 | 2560 | 163755 | 1860.6 | 0.703616 | 1(Win) | true |
| simdjson (ondemand) | 5357.52 | 0.201111 | 208.227ms | 11579 | 4890 | 84022.8 | 2061.14 | 0.00680671 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 851.77 | 0.26037 | 576.885ms | 5092 | 1280 | 282049 | 5701.2 | 0.196065 | 1(Win) | true |
| simdjson (ondemand) | 771.868 | 0.127386 | 631.956ms | 5092 | 4890 | 314081 | 6291.37 | 0.0386072 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1042.05 | 0.185155 | 546.168ms | 5092 | 4890 | 364062 | 4660.14 | 0.129828 | 1(Win) | true |
| simdjson (ondemand) | 923.566 | 0.298801 | 604.933ms | 5092 | 1280 | 315948 | 5258 | 0.235276 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1487.82 | 0.260519 | 672.249ms | 9739 | 1280 | 338549 | 6242.6 | 0.04808 | 1(Win) | true |
| simdjson (ondemand) | 1364.17 | 0.283824 | 699.542ms | 9739 | 640 | 238984 | 6808.4 | 0.395187 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1808.1 | 0.117978 | 589.837ms | 9739 | 4890 | 179596 | 5136.8 | 0.101033 | 1(Win) | true |
| simdjson (ondemand) | 1595.41 | 0.190898 | 657.773ms | 9739 | 2560 | 316175 | 5821.6 | 0.260417 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 551.179 | 0.130082 | 893.324ms | 5092 | 2560 | 336254 | 8810.4 | 0.298263 | 1(Win) | true |
| simdjson (ondemand) | 332.911 | 0.163619 | 1536.7ms | 5092 | 1280 | 729119 | 14586.8 | 0.00548471 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 589.634 | 0.157312 | 897.826ms | 5092 | 2560 | 429712 | 8235.8 | 0.387616 | 1(Win) | true |
| simdjson (ondemand) | 320.781 | 0.445402 | 1494.08ms | 5092 | 640 | 2.90968e+06 | 15138.4 | 0.100508 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 960.1 | 0.100356 | 972.019ms | 9739 | 4890 | 460882 | 9673.82 | 0.0498082 | 1(Win) | true |
| simdjson (ondemand) | 625.561 | 0.248656 | 1493.72ms | 9739 | 320 | 436153 | 14847.2 | 0.0593056 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1036.63 | 0.150127 | 1022.96ms | 9739 | 640 | 115790 | 8959.6 | 0.0669225 | 1(Win) | true |
| simdjson (ondemand) | 673.031 | 0.239374 | 1502.17ms | 9739 | 160 | 174595 | 13800 | 0.0580046 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3668.26 | 0.521127 | 135.853ms | 5092 | 4890 | 232730 | 1323.82 | 1.0673 | 1(Win) | true |
| simdjson (ondemand) | 3176.04 | 0.490457 | 155.913ms | 5092 | 4890 | 274990 | 1528.98 | 1.35582 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3878.99 | 0.712276 | 129.866ms | 5092 | 2560 | 203552 | 1251.9 | 0.0718391 | 1(Win) | true |
| simdjson (ondemand) | 3344.48 | 0.510288 | 151.092ms | 5092 | 4890 | 268447 | 1451.98 | 0.617696 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5213.2 | 1.32384 | 193.952ms | 9739 | 320 | 178010 | 1781.6 | 0.315315 | 1(Win) | true |
| simdjson (ondemand) | 3892.24 | 0.315574 | 239.656ms | 9739 | 4890 | 277295 | 2386.24 | 1.80468 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4504.28 | 0.961148 | 198.139ms | 9739 | 640 | 251384 | 2062 | 0.903499 | 1(Win) | true |
| simdjson (ondemand) | 3943.88 | 0.635558 | 227.536ms | 9739 | 1280 | 286749 | 2355 | 4.31432 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2393.59 | 0.972629 | 217.089ms | 5092 | 80 | 31150.3 | 2028.8 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2184.52 | 0.301237 | 224.611ms | 5092 | 4890 | 219275 | 2222.96 | 0.159016 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2431.95 | 0.952284 | 207.568ms | 5092 | 30 | 10847.3 | 1996.8 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2033.72 | 0.89496 | 232.78ms | 5092 | 1280 | 584538 | 2387.8 | 0.479717 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3630.44 | 0.302277 | 261.48ms | 9739 | 4890 | 292436 | 2558.32 | 0.201882 | 1(Win) | true |
| simdjson (ondemand) | 2894.13 | 0.524676 | 312.883ms | 9739 | 1280 | 362900 | 3209.2 | 0.273462 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3729.89 | 0.313665 | 251.68ms | 9739 | 4890 | 298317 | 2490.11 | 0.0606939 | 1(Win) | true |
| simdjson (ondemand) | 3492.09 | 0.283435 | 268.755ms | 9739 | 4890 | 277890 | 2659.68 | 0.19128 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1060.42 | 0.188942 | 436.625ms | 4857 | 4890 | 333078 | 4368.07 | 1.09874 | 1(Win) | true |
| simdjson (ondemand) | 885.32 | 0.666035 | 543.322ms | 4857 | 160 | 194290 | 5232 | 0.304878 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1538.87 | 0.210926 | 345.975ms | 4857 | 1280 | 51594.7 | 3010 | 0.620708 | 1(Win) | true |
| simdjson (ondemand) | 732 | 0.128255 | 680.347ms | 4857 | 4890 | 322086 | 6327.86 | 0.202512 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1424.43 | 0.255072 | 453.692ms | 6701 | 2560 | 335245 | 4486.4 | 0.00445772 | 1(Win) | true |
| simdjson (ondemand) | 1179.16 | 0.213919 | 546.294ms | 6701 | 2560 | 344089 | 5419.6 | 0.11823 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2019.27 | 1.36697 | 369.588ms | 6701 | 80 | 149727 | 3164.8 | 0.101215 | 1(Win) | true |
| simdjson (ondemand) | 976.403 | 0.134061 | 698.834ms | 6701 | 4890 | 376472 | 6545.01 | 0.0827928 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 579 | 0.155624 | 848.233ms | 4857 | 1280 | 198401 | 8000 | 0.0749438 | 1(Win) | true |
| simdjson (ondemand) | 154.706 | 0.120974 | 2975.39ms | 4857 | 4890 | 6.41528e+06 | 29940.6 | 0.0857084 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 623.764 | 0.208042 | 784.892ms | 4857 | 4890 | 1.1671e+06 | 7425.88 | 0.303707 | 1(Win) | true |
| simdjson (ondemand) | 160.156 | 0.195714 | 2924.02ms | 4857 | 2560 | 8.2022e+06 | 28921.7 | 1.3699 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 631.744 | 0.180233 | 997.416ms | 6701 | 4890 | 1.62546e+06 | 10115.8 | 0.158115 | 1(Win) | true |
| simdjson (ondemand) | 239.646 | 0.335356 | 2940.91ms | 6701 | 30 | 239922 | 26666.7 | 0.128164 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 759.184 | 0.186771 | 876.547ms | 6701 | 4890 | 1.20869e+06 | 8417.69 | 0.0511952 | 1(Win) | true |
| simdjson (ondemand) | 221.178 | 0.150452 | 2917.61ms | 6701 | 4890 | 9.24067e+06 | 28893.4 | 0.588334 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2434.07 | 0.37721 | 189.013ms | 4857 | 4890 | 251968 | 1902.99 | 0.852493 | 1(Win) | true |
| simdjson (ondemand) | 2178.41 | 0.249102 | 223.576ms | 4857 | 4890 | 137189 | 2126.32 | 0.217665 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3179.35 | 0.697238 | 164.802ms | 4857 | 2560 | 264157 | 1456.9 | 0.62854 | 1(Win) | true |
| simdjson (ondemand) | 2514.09 | 0.384777 | 198.248ms | 4857 | 4890 | 245755 | 1842.41 | 0.185684 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2903.62 | 0.45367 | 219.823ms | 6701 | 2560 | 255224 | 2200.9 | 0.0227231 | 1(Win) | true |
| simdjson (ondemand) | 2562.48 | 0.426373 | 247.302ms | 6701 | 2560 | 289453 | 2493.9 | 0.479452 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3784.54 | 0.58626 | 191.015ms | 6701 | 2560 | 250885 | 1688.6 | 2.0919 | 1(Win) | true |
| simdjson (ondemand) | 3140.18 | 0.441081 | 218.794ms | 6701 | 2560 | 206276 | 2035.1 | 1.05504 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1994.32 | 0.604621 | 236.19ms | 4857 | 1280 | 252421 | 2322.6 | 0.709644 | 1(Win) | true |
| simdjson (ondemand) | 1365.22 | 0.235517 | 337.139ms | 4857 | 4890 | 312239 | 3392.86 | 0.786116 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2439.18 | 0.520624 | 203.422ms | 4857 | 2560 | 250230 | 1899 | 1.20443 | 1(Win) | true |
| simdjson (ondemand) | 1598.12 | 0.785157 | 324.454ms | 4857 | 640 | 331443 | 2898.4 | 0.521691 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1935.36 | 0.568051 | 323.786ms | 6701 | 1280 | 450338 | 3302 | 1.20871 | 1(Win) | true |
| simdjson (ondemand) | 1560.2 | 1.23286 | 405.087ms | 6701 | 320 | 816016 | 4096 | 4.87505 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2381.34 | 0.56405 | 281.293ms | 6701 | 1280 | 293279 | 2683.6 | 0.059657 | 1(Win) | true |
| simdjson (ondemand) | 1805.14 | 0.38164 | 381.197ms | 6701 | 2560 | 467307 | 3540.2 | 0.589689 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 891.762 | 0.718446 | 204.406ms | 1691 | 1280 | 216066 | 1808.4 | 1.61045 | 1(Win) | true |
| simdjson (ondemand) | 807.624 | 0.576968 | 229.645ms | 1691 | 80 | 10618.5 | 1996.8 | 1.26582 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 947.652 | 0.544928 | 184.41ms | 1691 | 4890 | 420511 | 1701.75 | 1.19198 | 1(Win) | true |
| simdjson (ondemand) | 822.02 | 0.390847 | 218.143ms | 1691 | 4890 | 287505 | 1961.83 | 2.05103 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1070.44 | 0.474059 | 192.523ms | 2158 | 2560 | 212659 | 1922.6 | 1.68746 | 1(Win) | true |
| simdjson (ondemand) | 1019.63 | 0.659453 | 223.287ms | 2158 | 2560 | 453547 | 2018.4 | 2.49848 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1339.86 | 2.23763 | 191.016ms | 2158 | 320 | 378013 | 1536 | 1.63934 | 1(Win) | true |
| simdjson (ondemand) | 1108.37 | 0.72748 | 219.385ms | 2158 | 1280 | 233551 | 1856.8 | 1.00087 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 647.032 | 0.908052 | 244.655ms | 1691 | 640 | 327821 | 2492.4 | 0.906489 | 1(Win) | true |
| simdjson (ondemand) | 561.2 | 2.05459 | 332.8ms | 1691 | 40 | 139432 | 2873.6 | 0.223214 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 889.059 | 0.629624 | 212.064ms | 1691 | 2560 | 333910 | 1813.9 | 2.21563 | 1(Win) | true |
| simdjson (ondemand) | 616.085 | 1.52171 | 306.852ms | 1691 | 160 | 253859 | 2617.6 | 0.4914 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 800.509 | 0.448843 | 250.641ms | 2158 | 2560 | 340878 | 2570.9 | 2.87715 | 1(Win) | true |
| simdjson (ondemand) | 647.138 | 0.393215 | 352.941ms | 2158 | 1280 | 200161 | 3180.2 | 0.119347 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1003.72 | 0.292999 | 228.652ms | 2158 | 2560 | 92395.1 | 2050.4 | 0.332746 | 1(Win) | true |
| simdjson (ondemand) | 669.281 | 0.30584 | 335.776ms | 2158 | 4890 | 432497 | 3074.98 | 0.537455 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2676.18 | 2.29041 | 54.7709ms | 1691 | 1280 | 243835 | 602.6 | 1.27785 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2671.74 | 2.42637 | 63.391ms | 1691 | 1280 | 274550 | 603.6 | 0.39604 | 1(Tie) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3177.04 | 2.76861 | 61.7449ms | 1691 | 1280 | 252799 | 507.6 | 0.626468 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 3137.48 | 2.73422 | 49.087ms | 1691 | 1280 | 252814 | 514 | 0.312256 | 1(Tie) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2927.15 | 0.95102 | 75.7199ms | 2158 | 4890 | 218626 | 703.084 | 0.610144 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 2818.45 | 1.81653 | 69.9139ms | 2158 | 1280 | 225205 | 730.2 | 0.191361 | 1(Tie) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3526.65 | 1.51769 | 63.3459ms | 2158 | 4890 | 383576 | 583.565 | 0.415559 | 1(Win) | true |
| simdjson (ondemand) | 2864.74 | 5.01068 | 73.0061ms | 2158 | 160 | 207322 | 718.4 | 2.3913 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2216.62 | 1.22241 | 72.9889ms | 1691 | 4890 | 386766 | 727.532 | 0.732418 | 1(Win) | true |
| simdjson (ondemand) | 1602.41 | 2.95038 | 103.699ms | 1691 | 160 | 141065 | 1006.4 | 0.801282 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2239.81 | 2.85104 | 73.9932ms | 1691 | 640 | 269682 | 720 | 0.446429 | 1(Win) | true |
| simdjson (ondemand) | 1658.65 | 0.456182 | 104.595ms | 1691 | 4890 | 96197.8 | 972.276 | 0.639321 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2322.56 | 0.771239 | 87.9529ms | 2158 | 4890 | 228380 | 886.106 | 3.13146 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1784.16 | 0.692696 | 108.29ms | 2158 | 2560 | 163441 | 1153.5 | 6.94419 | -(Loss) | false |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2559.74 | 1.62931 | 88.585ms | 2158 | 1280 | 219650 | 804 | 0.199402 | 1(Win) | true |
| simdjson (ondemand) | 2410.43 | 1.20524 | 92.4339ms | 2158 | 1280 | 135541 | 853.8 | 1.83683 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 620.646 | 1.20433 | 606.449ms | 4390 | 40 | 263992 | 6745.6 | 0.700637 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 614.236 | 0.645628 | 728.603ms | 4390 | 80 | 154922 | 6816 | 0.0938086 | 1(Tie) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 880.84 | 0.408832 | 507.973ms | 4390 | 2560 | 966642 | 4753 | 0.929631 | 1(Win) | true |
| simdjson (ondemand) | 699.924 | 0.188669 | 670.631ms | 4390 | 4890 | 622786 | 5981.55 | 0.570944 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1293.64 | 0.217611 | 699.127ms | 9378 | 4890 | 1.10678e+06 | 6913.47 | 0.00384552 | 1(Win) | true |
| simdjson (ondemand) | 991.229 | 0.354272 | 933.847ms | 9378 | 2560 | 2.61569e+06 | 9022.7 | 1.80187 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1465.63 | 0.561534 | 666.558ms | 9378 | 1280 | 1.50291e+06 | 6102.2 | 0.0360656 | 1(Win) | true |
| simdjson (ondemand) | 1006.16 | 0.881007 | 889.372ms | 9378 | 320 | 1.96243e+06 | 8888.8 | 3.60056 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 471.382 | 0.758663 | 885.695ms | 4390 | 320 | 1.45288e+06 | 8881.6 | 0.234742 | 1(Win) | true |
| simdjson (ondemand) | 416.703 | 0.242082 | 1048.87ms | 4390 | 4890 | 2.89275e+06 | 10047 | 0.94577 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 521.289 | 0.845212 | 811.432ms | 4390 | 2560 | 1.17962e+07 | 8031.3 | 1.62302 | 1(Win) | true |
| simdjson (ondemand) | 414.091 | 1.31867 | 1058.97ms | 4390 | 160 | 2.84401e+06 | 10110.4 | 0.397204 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1027.52 | 2.42618 | 917.817ms | 9378 | 30 | 1.33784e+06 | 8704 | 0.681597 | 1(Win) | true |
| simdjson (ondemand) | 735.49 | 2.2086 | 1107.39ms | 9378 | 30 | 2.16382e+06 | 12160 | 0.835073 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 973.819 | 0.792033 | 878.104ms | 9378 | 640 | 3.38633e+06 | 9184 | 0.226995 | 1(Win) | true |
| simdjson (ondemand) | 784.137 | 0.49161 | 1095.57ms | 9378 | 320 | 1.00607e+06 | 11405.6 | 0.359003 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1391.82 | 0.453549 | 311.469ms | 4390 | 4890 | 910167 | 3008.03 | 2.14704 | 1(Win) | true |
| simdjson (ondemand) | 1031.85 | 0.535662 | 404.639ms | 4390 | 1280 | 604627 | 4057.4 | 2.35368 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1635.4 | 1.55608 | 310.523ms | 4390 | 160 | 253900 | 2560 | 2.5641 | 1(Win) | true |
| simdjson (ondemand) | 1050.65 | 0.924654 | 390.582ms | 4390 | 320 | 434432 | 3984.8 | 0.459632 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 2228.43 | 0.314382 | 387.047ms | 9378 | 4890 | 778480 | 4013.39 | 7.25824 | -(Win) | false |
| simdjson (ondemand) | 2029.77 | 0.641683 | 459.688ms | 9378 | 1280 | 1.02324e+06 | 4406.2 | 0.717747 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2463.32 | 0.346322 | 383.153ms | 9378 | 4890 | 773125 | 3630.7 | 3.86332 | 1(Win) | true |
| simdjson (ondemand) | 1909.71 | 0.796334 | 467.122ms | 9378 | 320 | 445067 | 4683.2 | 0.0341763 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 857.881 | 0.555002 | 434.158ms | 4390 | 1280 | 939018 | 4880.2 | 0.423903 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 847.359 | 1.08713 | 419.862ms | 4390 | 30 | 86552.7 | 4940.8 | 2.29682 | 1(Tie) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 975.995 | 0.638096 | 450.13ms | 4390 | 320 | 239748 | 4289.6 | 0.666914 | 1(Win) | true |
| simdjson (ondemand) | 937.232 | 0.289383 | 442.04ms | 4390 | 4890 | 817128 | 4467.02 | 0.337304 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1687.5 | 0.299314 | 522.2ms | 9378 | 2560 | 644214 | 5299.9 | 1.03515 | 1(Win) | true |
| simdjson (ondemand) | 1543.22 | 0.432712 | 557.35ms | 9378 | 2560 | 1.60992e+06 | 5795.4 | 0.89836 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1735.13 | 0.522286 | 499.604ms | 9378 | 640 | 463823 | 5154.4 | 1.753 | 1(Win) | true |
| simdjson (ondemand) | 1610.64 | 1.04617 | 543.05ms | 9378 | 320 | 1.07988e+06 | 5552.8 | 2.07353 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1160.53 | 0.842873 | 415.964ms | 4669 | 160 | 167333 | 3836.8 | 0.415282 | 1(Win) | true |
| simdjson (ondemand) | 949.161 | 0.928337 | 488.46ms | 4669 | 320 | 606917 | 4691.2 | 0.652249 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1326.47 | 1.1355 | 377.017ms | 4669 | 160 | 232457 | 3356.8 | 0.0952381 | 1(Win) | true |
| simdjson (ondemand) | 1163.07 | 0.267641 | 433.134ms | 4669 | 2560 | 268770 | 3828.4 | 2.75845 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1385.96 | 0.501072 | 543.42ms | 7932 | 640 | 478683 | 5458 | 0.626844 | 1(Win) | true |
| simdjson (ondemand) | 1212.36 | 0.29646 | 587.765ms | 7932 | 2560 | 875932 | 6239.5 | 1.60066 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1596.3 | 0.625685 | 472.06ms | 7932 | 640 | 562638 | 4738.8 | 1.06637 | 1(Win) | true |
| simdjson (ondemand) | 1342.18 | 0.577646 | 564.197ms | 7932 | 320 | 339169 | 5636 | 0.729196 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 407.101 | 1.06102 | 1227.01ms | 4669 | 160 | 2.15482e+06 | 10937.6 | 0.117165 | 1(Win) | true |
| simdjson (ondemand) | 143.406 | 0.441521 | 2961.75ms | 4669 | 80 | 1.5035e+06 | 31049.6 | 0.154831 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 405.054 | 0.328177 | 1130.3ms | 4669 | 4890 | 6.36427e+06 | 10992.9 | 0.771589 | 1(Win) | true |
| simdjson (ondemand) | 153.448 | 0.742262 | 2666.83ms | 4669 | 160 | 7.42263e+06 | 29017.6 | 1.49902 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 743.371 | 0.609272 | 1198.69ms | 7932 | 40 | 153758 | 10176 | 0.209205 | 1(Win) | true |
| simdjson (ondemand) | 354.022 | 0.428844 | 2627.97ms | 7932 | 30 | 251899 | 21367.5 | 0.0399202 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 683.51 | 0.798274 | 1063.58ms | 7932 | 640 | 4.99528e+06 | 11067.2 | 0.640186 | 1(Win) | true |
| simdjson (ondemand) | 359.477 | 0.0870515 | 2238.26ms | 7932 | 4890 | 1.64091e+06 | 21043.2 | 0.245813 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 3077.62 | 0.975764 | 154.813ms | 4669 | 1280 | 255103 | 1446.8 | 1.14785 | 1(Win) | true |
| Jsonifier (generic) | 2706.15 | 0.880833 | 156.576ms | 4669 | 1280 | 268869 | 1645.4 | 0.280351 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3723.93 | 0.725747 | 123.252ms | 4669 | 2560 | 192777 | 1195.7 | 0.0585089 | 1(Win) | true |
| simdjson (ondemand) | 3375.31 | 2.00112 | 147.07ms | 4669 | 320 | 223007 | 1319.2 | 0.54878 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3889.6 | 0.31649 | 196.535ms | 7932 | 4890 | 185262 | 1944.81 | 0.408914 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 3882.49 | 0.575607 | 194.327ms | 7932 | 4890 | 615044 | 1948.37 | 1.27214 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4611.96 | 0.626817 | 170.101ms | 7932 | 2560 | 270592 | 1640.2 | 0.0365943 | 1(Win) | true |
| simdjson (ondemand) | 3746.31 | 2.115 | 188.32ms | 7932 | 160 | 291810 | 2019.2 | 0.317965 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2453.01 | 0.667695 | 187.072ms | 4669 | 1280 | 188025 | 1815.2 | 0.591457 | 1(Win) | true |
| simdjson (ondemand) | 1985.43 | 0.329798 | 232.863ms | 4669 | 4890 | 267514 | 2242.7 | 0.306894 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2718.88 | 0.630179 | 175.628ms | 4669 | 2560 | 272669 | 1637.7 | 0.176765 | 1(Win) | true |
| simdjson (ondemand) | 2037.11 | 0.631536 | 222.881ms | 4669 | 1280 | 243909 | 2185.8 | 0.35558 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3398.27 | 0.766694 | 232.464ms | 7932 | 640 | 186412 | 2226 | 0.125945 | 1(Win) | true |
| simdjson (ondemand) | 2943.52 | 0.298589 | 259.188ms | 7932 | 4890 | 287931 | 2569.89 | 0.898717 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3545.88 | 3.11614 | 219.972ms | 7932 | 30 | 132579 | 2133.33 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3132.27 | 0.312254 | 246.827ms | 7932 | 4890 | 278083 | 2415.04 | 0.0678726 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 403.677 | 0.342699 | 1205.28ms | 4604 | 80 | 111152 | 10876.8 | 0.265487 | 1(Win) | true |
| simdjson (ondemand) | 345.559 | 0.71304 | 1402.32ms | 4604 | 30 | 246250 | 12706.1 | 0.0672043 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 413.144 | 0.151147 | 1286.74ms | 4604 | 4890 | 1.26176e+06 | 10627.6 | 1.96454 | 1(Win) | true |
| Jsonifier (generic) | 382.293 | 1.17985 | 1262.64ms | 4604 | 640 | 1.17519e+07 | 11485.2 | 0.317937 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1403.8 | 0.374833 | 1307.31ms | 18245 | 640 | 1.38145e+06 | 12394.8 | 0.145012 | 1(Win) | true |
| simdjson (ondemand) | 1195.35 | 0.262134 | 1497.68ms | 18245 | 1280 | 1.8636e+06 | 14556.2 | 0.172044 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1501.03 | 0.170919 | 1315.92ms | 18245 | 2560 | 1.00491e+06 | 11591.9 | 0.0629354 | 1(Win) | true |
| simdjson (ondemand) | 1365.16 | 0.276497 | 1504.2ms | 18245 | 1280 | 1.58968e+06 | 12745.6 | 0.86417 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 235.579 | 0.205997 | 1850.53ms | 4604 | 1280 | 1.88682e+06 | 18638 | 0.0816204 | 1(Win) | true |
| simdjson (ondemand) | 166.571 | 0.478245 | 2942.73ms | 4604 | 30 | 476756 | 26359.5 | 1.152 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 264.269 | 0.168468 | 1810.98ms | 4604 | 2560 | 2.00564e+06 | 16614.6 | 0.119314 | 1(Win) | true |
| simdjson (ondemand) | 159.651 | 0.465495 | 2997.19ms | 4604 | 640 | 1.04891e+07 | 27502 | 0.489623 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 796.504 | 0.500229 | 2255.88ms | 18245 | 640 | 7.64239e+06 | 21845.2 | 1.31154 | 1(Win) | true |
| simdjson (ondemand) | 554.769 | 0.391588 | 3111.42ms | 18245 | 1280 | 1.93077e+07 | 31364 | 0.577219 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 841.981 | 0.336133 | 2172.03ms | 18245 | 2560 | 1.23523e+07 | 20665.3 | 1.01725 | 1(Win) | true |
| simdjson (ondemand) | 694.414 | 0.1731 | 3250.52ms | 18245 | 320 | 601996 | 25056.8 | 1.16441 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2876.89 | 0.930236 | 160.921ms | 4604 | 1280 | 258000 | 1526.2 | 0.326541 | 1(Win) | true |
| simdjson (ondemand) | 2371.57 | 0.613244 | 186.392ms | 4604 | 1280 | 164997 | 1851.4 | 1.60502 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2873.51 | 2.11169 | 159.038ms | 4604 | 320 | 333163 | 1528 | 0.951374 | 1(Win) | true |
| simdjson (ondemand) | 2629.39 | 0.48719 | 180.612ms | 4604 | 4890 | 323644 | 1669.86 | 0.79823 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6440.4 | 0.311177 | 278.222ms | 18245 | 4890 | 345610 | 2701.66 | 0.823619 | 1(Win) | true |
| simdjson (ondemand) | 5523.39 | 0.351655 | 334.524ms | 18245 | 1280 | 157079 | 3150.2 | 0.26098 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6665.13 | 0.283739 | 270.665ms | 18245 | 4890 | 268299 | 2610.57 | 0.083261 | 1(Win) | true |
| simdjson (ondemand) | 4741.95 | 3.40039 | 339.989ms | 18245 | 30 | 467038 | 3669.33 | 3.86473 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2017.79 | 1.84835 | 239.464ms | 4604 | 80 | 129413 | 2176 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1434.3 | 0.278251 | 340.098ms | 4604 | 4890 | 354789 | 3061.22 | 2.23135 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1729.51 | 0.537306 | 241.135ms | 4604 | 2560 | 476328 | 2538.7 | 0.715682 | 1(Win) | true |
| simdjson (ondemand) | 1383.56 | 0.349976 | 314.904ms | 4604 | 2560 | 315786 | 3173.5 | 1.83432 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4878.81 | 0.845356 | 361.737ms | 18245 | 1280 | 1.16345e+06 | 3566.4 | 0.0224266 | 1(Win) | true |
| simdjson (ondemand) | 3881.11 | 0.524007 | 458.181ms | 18245 | 640 | 353207 | 4483.2 | 0.160342 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 5076.52 | 0.339413 | 354.079ms | 18245 | 2560 | 346459 | 3427.5 | 0.137314 | 1(Win) | true |
| simdjson (ondemand) | 3835.48 | 0.41176 | 458.522ms | 18245 | 4890 | 1.70627e+06 | 4536.54 | 0.523202 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 705.705 | 0.336016 | 650.114ms | 4926 | 4890 | 2.44665e+06 | 6656.89 | 4.39069 | 1(Win) | true |
| simdjson (ondemand) | 579.117 | 0.471685 | 841.722ms | 4926 | 80 | 117125 | 8112 | 0.821596 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1114.32 | 0.210348 | 516.448ms | 4926 | 4890 | 384550 | 4215.83 | 1.57971 | 1(Win) | true |
| simdjson (ondemand) | 691.667 | 0.184655 | 775.862ms | 4926 | 2560 | 402679 | 6792 | 0.632022 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1294.8 | 0.473187 | 609.463ms | 8150 | 1280 | 1.03272e+06 | 6002.8 | 0.576369 | 1(Win) | true |
| simdjson (ondemand) | 882.952 | 0.544391 | 873.192ms | 8150 | 1280 | 2.9395e+06 | 8802.8 | 0.617228 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1702.69 | 0.907698 | 552.094ms | 8150 | 160 | 274692 | 4564.8 | 0.105263 | 1(Win) | true |
| simdjson (ondemand) | 1087.85 | 0.448912 | 912.885ms | 8150 | 320 | 329194 | 7144.8 | 0.678381 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 502.987 | 0.560957 | 943.662ms | 4926 | 2560 | 7.02706e+06 | 9339.8 | 1.29148 | 1(Win) | true |
| simdjson (ondemand) | 291.109 | 1.40093 | 1735.66ms | 4926 | 80 | 4.08886e+06 | 16137.6 | 4.93134 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 591.208 | 0.58674 | 891.811ms | 4926 | 2560 | 5.56467e+06 | 7946.1 | 3.04622 | 1(Win) | true |
| simdjson (ondemand) | 319.739 | 0.478444 | 1591.09ms | 4926 | 1280 | 6.32514e+06 | 14692.6 | 2.90665 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 741.249 | 0.471526 | 1073.79ms | 8150 | 1280 | 3.12902e+06 | 10485.6 | 0.148997 | 1(Win) | true |
| simdjson (ondemand) | 493.855 | 0.591367 | 1610.11ms | 8150 | 2560 | 2.21753e+07 | 15738.3 | 0.435877 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 959.727 | 0.256467 | 900.177ms | 8150 | 4890 | 2.10955e+06 | 8098.6 | 3.88687 | 1(Win) | true |
| simdjson (ondemand) | 584.605 | 0.269076 | 1460.54ms | 8150 | 2560 | 3.27626e+06 | 13295.2 | 0.518652 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1486.13 | 0.436028 | 326.773ms | 4926 | 4890 | 929000 | 3161.1 | 1.66114 | 1(Win) | true |
| simdjson (ondemand) | 1154.14 | 1.10179 | 460.955ms | 4926 | 30 | 60338.3 | 4070.4 | 1.44628 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1670.49 | 0.432166 | 317.377ms | 4926 | 4890 | 722289 | 2812.23 | 2.32247 | 1(Win) | true |
| simdjson (ondemand) | 1158.23 | 0.45305 | 464.735ms | 4926 | 2560 | 864427 | 4056 | 0.257069 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2113.92 | 1.69031 | 399.714ms | 8150 | 80 | 309004 | 3676.8 | 0.087108 | 1(Win) | true |
| simdjson (ondemand) | 1721.17 | 0.823512 | 481.217ms | 8150 | 1280 | 1.77019e+06 | 4515.8 | 0.0398442 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2127.34 | 1.24061 | 376.276ms | 8150 | 640 | 1.31489e+06 | 3653.6 | 0.484048 | 1(Win) | true |
| simdjson (ondemand) | 1771.71 | 0.28627 | 461.597ms | 8150 | 4890 | 771241 | 4386.97 | 0.390649 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1111.55 | 0.286214 | 416.944ms | 4926 | 4890 | 715522 | 4226.36 | 1.07272 | 1(Win) | true |
| simdjson (ondemand) | 939.259 | 1.18697 | 566.341ms | 4926 | 80 | 281960 | 5001.6 | 0.0640205 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1533.49 | 1.62669 | 367.556ms | 4926 | 30 | 74500.1 | 3063.47 | 0.828729 | 1(Win) | true |
| simdjson (ondemand) | 896.51 | 0.353952 | 543.35ms | 4926 | 4890 | 1.68219e+06 | 5240.09 | 0.21793 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1777.03 | 0.210543 | 455.593ms | 8150 | 4890 | 414683 | 4373.83 | 0.540507 | 1(Win) | true |
| simdjson (ondemand) | 1438.06 | 0.929628 | 554.292ms | 8150 | 160 | 403922 | 5404.8 | 0.353982 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1993.96 | 0.318676 | 428.332ms | 8150 | 2560 | 395024 | 3898 | 0.758694 | 1(Win) | true |
| simdjson (ondemand) | 1354.65 | 1.88613 | 577.838ms | 8150 | 80 | 936906 | 5737.6 | 0.843645 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1516.18 | 0.882829 | 185.752ms | 2821 | 1280 | 314099 | 1774.4 | 1.02633 | 1(Win) | true |
| simdjson (ondemand) | 1182.61 | 0.887492 | 235.275ms | 2821 | 2560 | 1.0435e+06 | 2274.9 | 0.321926 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1739.3 | 0.735165 | 176.635ms | 2821 | 4890 | 632321 | 1546.78 | 3.01076 | 1(Win) | true |
| simdjson (ondemand) | 1314.66 | 1.11244 | 218.414ms | 2821 | 1280 | 663351 | 2046.4 | 0.078125 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1931.32 | 0.714972 | 192.426ms | 3770 | 1280 | 226757 | 1861.6 | 0.767591 | 1(Win) | true |
| simdjson (ondemand) | 1638.12 | 0.526294 | 224.932ms | 3770 | 1280 | 170788 | 2194.8 | 0.0910415 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2207.9 | 1.08295 | 178.398ms | 3770 | 2560 | 796125 | 1628.4 | 0.258589 | 1(Win) | true |
| simdjson (ondemand) | 1785.89 | 0.489969 | 216.478ms | 3770 | 640 | 62271.9 | 2013.2 | 0.139276 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 664.079 | 0.873011 | 426.418ms | 2821 | 40 | 50034.2 | 4051.2 | 0.582627 | 1(Win) | true |
| simdjson (ondemand) | 289.936 | 0.298774 | 923.402ms | 2821 | 1280 | 983782 | 9279 | 1.44088 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 727.584 | 1.46912 | 400.188ms | 2821 | 160 | 472145 | 3697.6 | 0.303819 | 1(Win) | true |
| simdjson (ondemand) | 329.308 | 0.532327 | 980.343ms | 2821 | 80 | 151303 | 8169.6 | 0.274941 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 831.026 | 1.93949 | 489.264ms | 3770 | 40 | 281637 | 4326.4 | 2.21774 | 1(Win) | true |
| simdjson (ondemand) | 334.389 | 1.4307 | 1034.51ms | 3770 | 80 | 1.89308e+06 | 10752 | 1.35056 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 815.273 | 0.389338 | 498.026ms | 3770 | 1280 | 377347 | 4410 | 3.37553 | 1(Win) | true |
| simdjson (ondemand) | 330.516 | 0.464237 | 1065.98ms | 3770 | 640 | 1.63214e+06 | 10878 | 0.661163 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 3505.75 | 1.20403 | 88.3489ms | 2821 | 2560 | 218555 | 767.4 | 5.49261 | -(Win) | false |
| simdjson (ondemand) | 2595.33 | 0.721264 | 101.841ms | 2821 | 2560 | 143104 | 1036.6 | 0.499136 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2991.9 | 3.85683 | 90.304ms | 2821 | 80 | 96219.7 | 899.2 | 0.357143 | 1(Win) | true |
| simdjson (ondemand) | 2694.63 | 0.865452 | 94.1192ms | 2821 | 80 | 5972.9 | 998.4 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4453.55 | 1.00901 | 83.424ms | 3770 | 2560 | 169863 | 807.3 | 0.480769 | 1(Win) | true |
| simdjson (ondemand) | 4110.38 | 0.764869 | 99.626ms | 3770 | 2560 | 114586 | 874.7 | 1.5421 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4431.34 | 0.854441 | 89.407ms | 3770 | 4890 | 235010 | 811.347 | 0.533623 | 1(Win) | true |
| simdjson (ondemand) | 4019.85 | 2.20895 | 96.574ms | 3770 | 320 | 124906 | 894.4 | 2.44328 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2526.59 | 1.24788 | 114.241ms | 2821 | 640 | 112995 | 1064.8 | 3.01858 | 1(Win) | true |
| simdjson (ondemand) | 2445.3 | 0.837643 | 128.318ms | 2821 | 1280 | 108710 | 1100.2 | 3.11729 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2656.58 | 0.306652 | 109.777ms | 2821 | 2560 | 24688.4 | 1012.7 | 0.307052 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 2586.34 | 0.962859 | 105.832ms | 2821 | 1280 | 128401 | 1040.2 | 6.59124 | -(Loss) | false |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3549.91 | 1.0829 | 121.263ms | 3770 | 160 | 19246 | 1012.8 | 1.09375 | 1(Win) | true |
| simdjson (ondemand) | 3187.09 | 0.620614 | 115.621ms | 3770 | 2560 | 125481 | 1128.1 | 0.379724 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3650.1 | 0.491417 | 104.623ms | 3770 | 1280 | 29990.4 | 985 | 0.384304 | 1(Win) | true |
| simdjson (ondemand) | 3335.82 | 0.592534 | 117.349ms | 3770 | 2560 | 104410 | 1077.8 | 0.406579 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3576.11 | 0.672651 | 7739.39ms | 277673 | 320 | 7.93916e+07 | 74049.6 | 0.357793 | 1(Win) | true |
| simdjson (ondemand) | 2895.99 | 0.308701 | 5057.94ms | 277673 | 160 | 1.27488e+07 | 91440 | 0.104877 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 3041.11 | 0.297812 | 5417.74ms | 10548466 | 30 | 2.91152e+09 | 3.30794e+06 | 7.67646 | -(Win) | false |
| simdjson (ondemand) | 2714.7 | 0.407321 | 5979.28ms | 10548466 | 80 | 1.82262e+10 | 3.70567e+06 | 0.121648 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2081.88 | 1.53897 | 10868.6ms | 16002592 | 30 | 3.81814e+11 | 7.33051e+06 | 1.26331 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 1855.34 | 1.25565 | 5248.17ms | 16002592 | 40 | 4.26709e+11 | 8.22557e+06 | 7.5586 | -(Loss) | false |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2292 | 0.444175 | 10152.2ms | 16002591 | 80 | 6.99759e+10 | 6.65848e+06 | 0.510917 | 1(Win) | true |
| simdjson (ondemand) | 1263.68 | 0.704739 | 8860.49ms | 16002591 | 30 | 2.1731e+11 | 1.20768e+07 | 2.05327 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 8421.26 | 0.612888 | 5692.45ms | 16197086 | 80 | 1.01105e+10 | 1.83426e+06 | 0.0693077 | 1(Win) | true |
| simdjson (ondemand) | 7231.75 | 0.806462 | 6298.56ms | 16197086 | 30 | 8.90177e+09 | 2.13596e+06 | 0.401089 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 8612.67 | 0.441803 | 5640.62ms | 16197085 | 80 | 5.0228e+09 | 1.79349e+06 | 0.528535 | 1(Win) | true |
| simdjson (ondemand) | 7695.02 | 0.504442 | 6670.27ms | 16197085 | 160 | 1.64058e+10 | 2.00737e+06 | 2.25355 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1343.42 | 1.01785 | 5902.51ms | 4212000 | 40 | 3.70494e+10 | 2.99003e+06 | 1.11476 | 1(Win) | true |
| simdjson (ondemand) | 883.254 | 0.369902 | 8331.93ms | 4212000 | 80 | 2.26397e+10 | 4.54782e+06 | 0.479138 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1049.96 | 0.5888 | 7717.46ms | 4212000 | 40 | 2.02968e+10 | 3.82575e+06 | 0.995117 | 1(Win) | true |
| simdjson (ondemand) | 754.354 | 0.810064 | 9552.83ms | 4212000 | 40 | 7.44261e+10 | 5.32492e+06 | 3.63771 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1247.02 | 0.877986 | 6586.44ms | 4211999 | 80 | 6.39875e+10 | 3.22118e+06 | 1.10107 | 1(Win) | true |
| simdjson (ondemand) | 751.521 | 0.815793 | 9541.38ms | 4211999 | 80 | 1.52105e+11 | 5.345e+06 | 2.65425 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1102.75 | 0.456487 | 6614.25ms | 4211999 | 30 | 8.29467e+09 | 3.64259e+06 | 0.505321 | 1(Win) | true |
| simdjson (ondemand) | 774.034 | 0.0660703 | 9203.5ms | 4211999 | 80 | 9.405e+08 | 5.18953e+06 | 0.569034 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1066.16 | 0.0461277 | 6785.08ms | 4525120 | 30 | 1.04583e+08 | 4.04769e+06 | 2.83483 | 1(Win) | true |
| simdjson (ondemand) | 789.32 | 0.620819 | 8263.59ms | 4525120 | 80 | 9.21665e+10 | 5.46735e+06 | 4.89781 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 524.501 | 0.956868 | 6027.4ms | 4525120 | 40 | 2.47931e+11 | 8.2278e+06 | 3.16315 | 1(Win) | true |
| simdjson (ondemand) | 406.298 | 0.586755 | 8070.83ms | 4525120 | 40 | 1.55362e+11 | 1.06215e+07 | 4.63366 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 755.21 | 0.886411 | 8649.83ms | 4525119 | 40 | 1.02625e+11 | 5.71429e+06 | 0.33569 | 1(Win) | true |
| simdjson (ondemand) | 668.944 | 0.418269 | 10083.8ms | 4525119 | 30 | 2.18431e+10 | 6.4512e+06 | 0.125554 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 613.135 | 0.292162 | 5103.85ms | 4525119 | 30 | 1.26857e+10 | 7.0384e+06 | 0.183651 | 1(Win) | true |
| simdjson (ondemand) | 369.339 | 1.19688 | 8033.12ms | 4525119 | 30 | 5.86725e+11 | 1.16844e+07 | 3.04345 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 869.411 | 0.275505 | 7429.74ms | 4203059 | 80 | 1.29071e+10 | 4.61042e+06 | 1.24896 | 1(Win) | true |
| simdjson (ondemand) | 677.957 | 0.0664655 | 10129.9ms | 4203059 | 30 | 4.63277e+08 | 5.9124e+06 | 0.119938 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 557.409 | 0.523529 | 5307.19ms | 4203059 | 40 | 5.66924e+10 | 7.19103e+06 | 0.745996 | 1(Win) | true |
| simdjson (ondemand) | 481.69 | 0.628771 | 6082.68ms | 4203059 | 30 | 8.213e+10 | 8.32143e+06 | 0.184204 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 691.685 | 0.866075 | 9797.86ms | 4203058 | 30 | 7.55694e+10 | 5.79505e+06 | 0.00559527 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 447.415 | 0.449261 | 6266.57ms | 4203058 | 40 | 6.47988e+10 | 8.95891e+06 | 5.27866 | -(Loss) | false |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 458.891 | 0.93978 | 6164.49ms | 4203058 | 30 | 2.02156e+11 | 8.73487e+06 | 0.413381 | 1(Win) | true |
| simdjson (ondemand) | 392.179 | 0.849422 | 7480.41ms | 4203058 | 30 | 2.26116e+11 | 1.02207e+07 | 0.697977 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1212.73 | 0.975063 | 5149.56ms | 4197496 | 40 | 4.14362e+10 | 3.30086e+06 | 0.411437 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 895.053 | 1.54412 | 7067.87ms | 4197496 | 40 | 1.90767e+11 | 4.47241e+06 | 8.75942 | -(Loss) | false |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 651.541 | 0.822377 | 9377.43ms | 4197496 | 30 | 7.6588e+10 | 6.14397e+06 | 0.845299 | 1(Win) | true |
| simdjson (ondemand) | 509.676 | 0.94459 | 5381.73ms | 4197496 | 30 | 1.6512e+11 | 7.8541e+06 | 2.72997 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1083.71 | 1.83103 | 6006.26ms | 4197495 | 40 | 1.82982e+11 | 3.69384e+06 | 2.61981 | 1(Win) | true |
| simdjson (ondemand) | 625.457 | 0.701723 | 9458.13ms | 4197495 | 40 | 8.06819e+10 | 6.40019e+06 | 2.03989 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 709.235 | 0.805543 | 8831.68ms | 4197495 | 40 | 8.26869e+10 | 5.64417e+06 | 2.94645 | 1(Win) | true |
| simdjson (ondemand) | 439.758 | 1.08042 | 6374.81ms | 4197495 | 40 | 3.86901e+11 | 9.10284e+06 | 1.87014 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 964.718 | 0.707892 | 7822.08ms | 4506447 | 80 | 7.95593e+10 | 4.45486e+06 | 2.32884 | 1(Win) | true |
| simdjson (ondemand) | 603.838 | 1.5907 | 5464.29ms | 4506447 | 30 | 3.84528e+11 | 7.11728e+06 | 1.95798 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 610.834 | 0.714297 | 5398.36ms | 4506447 | 40 | 1.01028e+11 | 7.03576e+06 | 1.52346 | 1(Win) | true |
| simdjson (ondemand) | 346.713 | 0.54627 | 8878.53ms | 4506447 | 30 | 1.37552e+11 | 1.23955e+07 | 0.569981 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 977.523 | 0.169292 | 8226.87ms | 4506446 | 30 | 1.66191e+09 | 4.3965e+06 | 1.9887 | 1(Win) | true |
| simdjson (ondemand) | 548.557 | 1.00166 | 6057.58ms | 4506446 | 30 | 1.84753e+11 | 7.83452e+06 | 1.72739 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 597.678 | 1.08178 | 5791.62ms | 4506446 | 30 | 1.81524e+11 | 7.19063e+06 | 4.47595 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 275.101 | 1.65467 | 10473.2ms | 4506446 | 30 | 2.0046e+12 | 1.56222e+07 | 5.67607 | -(Loss) | false |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1569.85 | 0.872196 | 9589.45ms | 4219120 | 30 | 1.49927e+10 | 2.5631e+06 | 0.734667 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1183.23 | 1.23346 | 5567.45ms | 4219120 | 80 | 1.4075e+11 | 3.40059e+06 | 5.16429 | -(Loss) | false |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 561.95 | 1.24022 | 5530.68ms | 4219120 | 30 | 2.36574e+11 | 7.16019e+06 | 5.75107 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 210.831 | 2.14374 | 5145.73ms | 4219120 | 30 | 5.02159e+12 | 1.90848e+07 | 13.2826 | -(Loss) | false |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1335.14 | 0.883704 | 5268.9ms | 4219119 | 80 | 5.67409e+10 | 3.01368e+06 | 7.17488 | -(Win) | false |
| simdjson (ondemand) | 1035.8 | 0.896233 | 6349.87ms | 4219119 | 30 | 3.63627e+10 | 3.8846e+06 | 0.193905 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 533.102 | 0.56225 | 5336.4ms | 4219119 | 40 | 7.20348e+10 | 7.54765e+06 | 0.738492 | 1(Win) | true |
| simdjson (ondemand) | 257.262 | 0.878837 | 5143.64ms | 4219119 | 30 | 5.66801e+11 | 1.56403e+07 | 3.72685 | 2(Loss) | true |
