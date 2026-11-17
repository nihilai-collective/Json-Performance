# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the Clang 24.0.0 compiler).  

Latest Results: (Nov 17, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [79b3e67](https://github.com/nihilai-collective/Jsonifier/commit/79b3e67)  
| simdjson: [36c5b3cfc](https://github.com/simdjson/simdjson/commit/36c5b3cfc)  

#### Benchmark Methodology & Test Matrix

| Library | Active Implementation |
| :--- | :--- |
| **Jsonifier (generic)** | `AVX2` |
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
*Environment generated via BenchmarkSuite commit: [71afc62](https://github.com/nihilai-collective/benchmarksuite/commit/71afc62)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.593 | 0.507082 | 870.713ms | 905 | 80 | 4875.82 | 1539.58 | 0.0178653 | 9.56497 | 49.3702 | 6.37018 | 0.00312155 | 2.76243e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 288.89 | 0.0355395 | 1022.35ms | 905 | 320 | 360.749 | 2987.56 | 0.0244825 | 18.072 | 88.9459 | 9.47735 | 0.0219544 | 0.000107044 | 3.45304e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 564.316 | 0.107393 | 867.677ms | 905 | 160 | 431.641 | 1529.42 | 0.0535621 | 9.36285 | 48.7514 | 6.25193 | 0.00446823 | 5.52486e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 291.988 | 0.114625 | 1015.83ms | 905 | 160 | 1836.72 | 2955.86 | 0.269497 | 17.8671 | 88.3271 | 9.35912 | 0.0224931 | 6.90608e-05 | 0 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.052 | 0.0609191 | 975.498ms | 1811 | 160 | 373.044 | 2506.49 | 0.0626266 | 7.59893 | 39.3109 | 6.43457 | 0.000790309 | 7.9376e-05 | 3.45113e-06 | 1(Win) | true |
| simdjson (ondemand) | 365.038 | 0.106164 | 1194.91ms | 1811 | 4890 | 123374 | 4731.31 | 0.000676276 | 14.1032 | 71.1706 | 9.25014 | 0.000668941 | 0.000151201 | 4.56199e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 712.822 | 0.0493175 | 960.435ms | 1811 | 1280 | 1827.62 | 2422.91 | 0.104427 | 7.31097 | 38.2518 | 6.19879 | 0.00102542 | 5.26298e-05 | 3.45113e-06 | 1(Win) | true |
| simdjson (ondemand) | 369.901 | 0.14672 | 1182.49ms | 1811 | 40 | 1877.17 | 4669.1 | 0.198146 | 13.788 | 70.2253 | 9.04362 | 0.000648813 | 6.90226e-05 | 1.38045e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1546.04 | 0.102544 | 957.83ms | 3862 | 30 | 179.03 | 2382.27 | 0.0671178 | 3.38726 | 16.9443 | 2.10176 | 0.00133782 | 2.58933e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 794.342 | 0.0598263 | 1186.57ms | 3862 | 1280 | 9849.25 | 4636.65 | 0.0338114 | 6.53503 | 28.2372 | 3.48887 | 0.0130735 | 6.49356e-05 | 2.4275e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1612.8 | 0.131138 | 946.934ms | 3862 | 30 | 269.057 | 2283.67 | 0.0248077 | 3.25022 | 16.4606 | 1.99171 | 0.00159675 | 1.72622e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 803.045 | 0.071545 | 1179.67ms | 3862 | 320 | 3445.51 | 4586.41 | 0.0257621 | 6.46568 | 27.7962 | 3.39203 | 0.0165466 | 4.04583e-05 | 1.61833e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1356.22 | 0.0275276 | 1404.14ms | 9578 | 4890 | 16808.6 | 6735.09 | 0.136123 | 3.7955 | 19.2036 | 3.36281 | 0.00137799 | 2.513e-05 | 7.1739e-06 | 1(Win) | true |
| simdjson (ondemand) | 1299.88 | 0.0392288 | 1432.03ms | 9578 | 1280 | 9726.65 | 7027.02 | 0.00522509 | 3.9293 | 17.5663 | 2.97212 | 0.00271374 | 1.6395e-05 | 1.06037e-06 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1994.2 | 0.0452342 | 1324.57ms | 9578 | 2560 | 10989.8 | 4580.44 | 0.0357712 | 2.55286 | 13.4262 | 2.045 | 0.00195777 | 1.4315e-05 | 6.52537e-07 | 1(Win) | true |
| Jsonifier (generic) | 1794.85 | 0.0265037 | 1365.51ms | 9578 | 4890 | 8896.43 | 5089.17 | 0.0256442 | 2.85401 | 14.9756 | 2.40698 | 0.00169883 | 2.20982e-05 | 4.67585e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1542.8 | 0.0388889 | 956.131ms | 3873 | 4890 | 4238.74 | 2394.08 | 0.000496999 | 3.39026 | 17.071 | 2.11645 | 0.000778765 | 7.90962e-05 | 3.28423e-05 | 1(Win) | true |
| simdjson (ondemand) | 732.639 | 0.022525 | 1223.68ms | 3873 | 4890 | 6305.99 | 5041.47 | 0.0436563 | 7.05388 | 27.912 | 3.56649 | 0.0151832 | 8.88644e-05 | 4.07625e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1608.64 | 0.0342998 | 944.211ms | 3873 | 640 | 396.955 | 2296.09 | 0.205525 | 3.24943 | 16.5944 | 2.00852 | 0.00103642 | 3.10644e-05 | 1.2103e-06 | 1(Win) | true |
| simdjson (ondemand) | 734.692 | 0.0612383 | 1223.93ms | 3873 | 320 | 3033.06 | 5027.39 | 0.0854584 | 7.06594 | 27.4216 | 3.45624 | 0.0186846 | 3.46953e-05 | 1.2103e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1504.93 | 0.0199598 | 6747.6ms | 94653 | 2560 | 366938 | 59981.8 | 0.0590704 | 3.36986 | 15.0448 | 2.9685 | 0.00900091 | 9.90047e-06 | 4.02374e-06 | 1(Win) | true |
| simdjson (ondemand) | 1227.54 | 0.0419706 | 8082.74ms | 94653 | 640 | 609629 | 73535.7 | 0.167175 | 4.13578 | 16.629 | 3.11044 | 0.0129068 | 1.72175e-05 | 1.13078e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2191.7 | 0.021771 | 6088.46ms | 94653 | 2560 | 205827 | 41186.3 | 0.060645 | 2.31465 | 11.1468 | 2.08898 | 0.00608877 | 6.5783e-06 | 3.1282e-06 | 1(Win) | true |
| simdjson (ondemand) | 1647.19 | 0.0788334 | 7485.48ms | 94653 | 320 | 597244 | 54801.3 | 0.0224169 | 3.08468 | 12.7599 | 2.23621 | 0.00993986 | 5.77768e-06 | 2.146e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1824.56 | 0.0329378 | 7261.09ms | 124597 | 640 | 294489 | 65125.4 | 0.139823 | 2.77243 | 11.8363 | 2.25794 | 0.00720332 | 4.0631e-06 | 1.3042e-06 | 1(Win) | true |
| simdjson (ondemand) | 1572.38 | 0.0643845 | 8218.88ms | 124597 | 80 | 189389 | 75570.2 | 0.00868473 | 3.21559 | 12.931 | 2.3761 | 0.0103689 | 3.31067e-06 | 9.02911e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2569.59 | 0.0249159 | 6605.71ms | 124597 | 2560 | 339845 | 46242.8 | 0.062905 | 1.97224 | 8.87835 | 1.58957 | 0.00465028 | 1.71114e-05 | 1.28195e-05 | 1(Win) | true |
| simdjson (ondemand) | 2108.02 | 0.0354263 | 7664.66ms | 124597 | 1280 | 510422 | 56368.2 | 0.024264 | 2.42511 | 9.99071 | 1.71305 | 0.00787908 | 5.28579e-06 | 2.28863e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1132.97 | 0.0169548 | 8716.11ms | 94653 | 4890 | 892334 | 79674.2 | 0.0121462 | 4.48201 | 20.9675 | 4.21809 | 0.0105955 | 2.63496e-05 | 1.61153e-05 | 1(Win) | true |
| simdjson (ondemand) | 704.529 | 0.0435959 | 6928.8ms | 94653 | 640 | 1.99684e+06 | 128125 | 0.155978 | 7.2114 | 35.153 | 7.04403 | 0.0150085 | 3.03246e-05 | 1.69864e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1479.76 | 0.0912418 | 8077.71ms | 94653 | 160 | 495672 | 61001.9 | 0.0806189 | 3.42604 | 17.1041 | 3.3608 | 0.00769198 | 8.84811e-06 | 4.49008e-06 | 1(Win) | true |
| simdjson (ondemand) | 817.873 | 0.130442 | 6628.02ms | 94653 | 40 | 829072 | 110369 | 0.076593 | 6.17549 | 31.3209 | 6.1945 | 0.0116346 | 1.34703e-05 | 2.11298e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1419.75 | 0.0209346 | 9121.19ms | 124597 | 2560 | 785886 | 83694.1 | 0.145286 | 3.57946 | 16.5617 | 3.28644 | 0.00830874 | 2.57549e-05 | 1.57163e-05 | 1(Win) | true |
| simdjson (ondemand) | 912.162 | 0.0576406 | 6964.58ms | 124597 | 80 | 451044 | 130267 | 0.0916552 | 5.5408 | 26.6776 | 5.30834 | 0.0117229 | 1.60518e-05 | 1.06343e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1841.62 | 0.0234408 | 8382.44ms | 124597 | 1280 | 292800 | 64522 | 0.159653 | 2.74665 | 13.6215 | 2.63298 | 0.00555587 | 1.05089e-05 | 5.90654e-06 | 1(Win) | true |
| simdjson (ondemand) | 1078.95 | 0.0561709 | 6630.73ms | 124597 | 320 | 1.22457e+06 | 110130 | 0.0208971 | 4.69815 | 23.7634 | 4.66178 | 0.00858849 | 4.81553e-06 | 1.32929e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2490.12 | 0.0397636 | 4376.94ms | 94653 | 640 | 132978 | 36250.5 | 0.0420904 | 2.03568 | 9.3863 | 1.79966 | 0.00478536 | 4.07739e-06 | 8.25383e-07 | 1(Win) | true |
| simdjson (ondemand) | 1873.02 | 0.0474274 | 5572.81ms | 94653 | 640 | 334367 | 48194 | 0.253499 | 2.72712 | 11.0178 | 1.95328 | 0.00864785 | 4.20945e-06 | 1.15554e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3343.81 | 0.0188495 | 3949.1ms | 94653 | 4890 | 126618 | 26995.6 | 0.234997 | 1.52142 | 7.48156 | 1.35543 | 0.00351955 | 4.86547e-06 | 1.32223e-06 | 1(Win) | true |
| simdjson (ondemand) | 2323.93 | 0.0346191 | 5117.85ms | 94653 | 1280 | 231455 | 38842.9 | 0.0213345 | 2.18292 | 9.12156 | 1.51132 | 0.00656488 | 1.47826e-05 | 7.18083e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2914.44 | 0.0249611 | 4813.29ms | 124597 | 2560 | 265139 | 40771.1 | 0.219594 | 1.74487 | 7.5808 | 1.38444 | 0.00535958 | 1.29355e-05 | 8.35193e-06 | 1(Win) | true |
| simdjson (ondemand) | 2358.04 | 0.0342765 | 5764.1ms | 124597 | 1280 | 381871 | 50391.5 | 0.0506046 | 2.14894 | 8.34947 | 1.4377 | 0.00969062 | 1.09854e-05 | 7.14178e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3895.38 | 0.0558415 | 4285.74ms | 124597 | 640 | 185700 | 30504.1 | 0.0571113 | 1.31109 | 6.12951 | 1.04542 | 0.00306955 | 4.72774e-06 | 2.67111e-06 | 1(Win) | true |
| simdjson (ondemand) | 3118.57 | 0.0244018 | 5050.36ms | 124597 | 2560 | 221303 | 38102.3 | 0.103463 | 1.62773 | 6.91474 | 1.10383 | 0.00479834 | 8.76576e-06 | 5.00677e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1839.02 | 0.0669321 | 5737.39ms | 94653 | 80 | 86348.8 | 49085 | 0.0163009 | 2.80253 | 12.995 | 2.53951 | 0.00812811 | 1.34703e-05 | 6.86719e-06 | 1(Win) | true |
| simdjson (ondemand) | 1538.4 | 0.0454822 | 6601.55ms | 94653 | 640 | 455818 | 58676.5 | 0.118489 | 3.29804 | 13.6511 | 2.45551 | 0.00983774 | 6.40497e-06 | 2.54218e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2217.52 | 0.0168181 | 5327.2ms | 94653 | 4890 | 229192 | 40706.9 | 0.234859 | 2.29423 | 11.1172 | 2.11621 | 0.00642908 | 1.39159e-05 | 9.74391e-06 | 1(Win) | true |
| simdjson (ondemand) | 1823.61 | 0.0704013 | 6166.43ms | 94653 | 320 | 388612 | 49499.7 | 0.00729856 | 2.78356 | 11.8004 | 2.0392 | 0.00811131 | 1.84226e-05 | 9.31032e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2285.14 | 0.0163545 | 5939.69ms | 124597 | 4890 | 353649 | 51999 | 0.0738594 | 2.23085 | 10.4036 | 1.96387 | 0.00567363 | 1.80114e-05 | 1.35406e-05 | 1(Win) | true |
| simdjson (ondemand) | 2050.79 | 0.0243798 | 6510.17ms | 124597 | 2560 | 510828 | 57941.1 | 0.0663864 | 2.47723 | 10.3512 | 1.8235 | 0.00659977 | 8.94133e-06 | 5.08201e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2737.39 | 0.0441208 | 5539.35ms | 124597 | 320 | 117376 | 43408.2 | 0.153663 | 1.84724 | 8.97792 | 1.64285 | 0.00507311 | 6.01941e-06 | 1.58009e-06 | 1(Win) | true |
| simdjson (ondemand) | 2432.81 | 0.0187776 | 6128.84ms | 124597 | 4890 | 411325 | 48842.6 | 0.0960145 | 2.09795 | 8.93627 | 1.50539 | 0.00584346 | 1.8535e-05 | 1.46911e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 790.743 | 0.0813605 | 7889.95ms | 2090234 | 160 | 6.7308e+08 | 2.52092e+06 | 0.903193 | 6.40874 | 32.6323 | 6.38394 | 0.0230273 | 0.10413 | 0.000596094 | 1(Win) | true |
| simdjson (ondemand) | 760.007 | 0.228242 | 8225.31ms | 2090234 | 160 | 5.73411e+09 | 2.62288e+06 | 0.794331 | 6.70619 | 31.7593 | 5.65027 | 0.0232213 | 0.105009 | 0.000769274 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 920.843 | 0.48119 | 7984.7ms | 2090234 | 40 | 4.34022e+09 | 2.16476e+06 | 0.06331 | 5.48019 | 27.2873 | 5.09175 | 0.0221006 | 0.0787975 | 0.000158535 | 1(Win) | true |
| simdjson (ondemand) | 885.193 | 0.30906 | 8238.97ms | 2090234 | 80 | 3.87517e+09 | 2.25194e+06 | 0.240375 | 5.7171 | 26.429 | 4.36112 | 0.0219782 | 0.0783751 | 0.000431961 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1771.27 | 0.163003 | 8801.48ms | 5212421 | 30 | 6.27805e+08 | 2.80644e+06 | 0.112259 | 2.86458 | 13.4729 | 2.30229 | 0.0103707 | 0.0614223 | 0.000274268 | 1(Win) | true |
| Jsonifier (generic) | 1732.06 | 0.83306 | 8901.07ms | 5212421 | 40 | 2.28646e+10 | 2.86996e+06 | 0.807521 | 2.93371 | 13.8811 | 2.60521 | 0.0103597 | 0.0604341 | 7.05814e-05 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2046.27 | 0.187893 | 8849.55ms | 5212421 | 30 | 6.2502e+08 | 2.42927e+06 | 0.415357 | 2.47985 | 11.3277 | 1.7836 | 0.00997131 | 0.0512934 | 0.000284737 | 1(Win) | true |
| Jsonifier (generic) | 2017.23 | 0.3464 | 8855.63ms | 5212421 | 40 | 2.91461e+09 | 2.46424e+06 | 0.0683067 | 2.52309 | 11.7331 | 2.08631 | 0.00999507 | 0.0511405 | 0.000441134 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.945 | 0.479607 | 8538.18ms | 2090234 | 160 | 2.77507e+10 | 2.74594e+06 | 0.460488 | 6.96104 | 35.6642 | 7.02223 | 0.0230406 | 0.154874 | 0.000237067 | 1(Win) | true |
| simdjson (ondemand) | 691.528 | 0.180048 | 9066.8ms | 2090234 | 160 | 4.30991e+09 | 2.88261e+06 | 0.175511 | 7.32005 | 36.0929 | 6.61299 | 0.0229803 | 0.17814 | 0.000215697 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.407 | 0.652694 | 8489.12ms | 2090234 | 80 | 1.86382e+10 | 2.33856e+06 | 0.168369 | 5.96683 | 30.3269 | 5.7316 | 0.0220575 | 0.129408 | 0.00108002 | 1(Win) | true |
| simdjson (ondemand) | 802.358 | 0.109447 | 8964.42ms | 2090234 | 80 | 5.9149e+08 | 2.48443e+06 | 0.166248 | 6.30694 | 30.7483 | 5.32089 | 0.0220614 | 0.15228 | 0.000290888 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1582.91 | 0.150117 | 9723.62ms | 5212421 | 160 | 3.55588e+09 | 3.14038e+06 | 0.26722 | 3.19198 | 15.0921 | 2.86045 | 0.0103941 | 0.10066 | 0.000904411 | 1(Win) | true |
| simdjson (ondemand) | 1518.82 | 0.60816 | 10158.1ms | 5212421 | 160 | 6.33905e+10 | 3.27291e+06 | 0.169889 | 3.32728 | 15.2047 | 2.68705 | 0.0103677 | 0.120114 | 0.00117997 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1814.71 | 0.218459 | 9752.14ms | 5212421 | 80 | 2.86481e+09 | 2.73926e+06 | 0.293909 | 2.78639 | 12.9527 | 2.34309 | 0.0099929 | 0.090384 | 0.000632141 | 1(Win) | true |
| simdjson (ondemand) | 1769.41 | 0.0795822 | 10035.7ms | 5212421 | 160 | 7.99791e+08 | 2.80939e+06 | 0.402237 | 2.85536 | 13.0604 | 2.16865 | 0.0100516 | 0.110355 | 0.000389725 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7941.83 | 0.0958949 | 6651.63ms | 2090234 | 320 | 1.85391e+07 | 251000 | 0.031071 | 0.636528 | 3.25154 | 0.398873 | 0.00267546 | 0.0509243 | 3.2293e-06 | 1(Win) | true |
| simdjson (ondemand) | 7078.54 | 0.0363 | 7431.8ms | 2090234 | 1280 | 1.3376e+07 | 281612 | 0.258339 | 0.715518 | 3.65784 | 0.418405 | 0.00254726 | 0.0499222 | 9.77388e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8060.23 | 0.108494 | 6641.62ms | 2090234 | 80 | 5.75965e+06 | 247313 | 0.214515 | 0.632335 | 3.25146 | 0.398855 | 0.00258444 | 0.0508269 | 3.06186e-06 | 1(Win) | true |
| simdjson (ondemand) | 7062.8 | 0.0943638 | 7457.22ms | 2090234 | 160 | 1.13492e+07 | 282240 | 0.0134655 | 0.717482 | 3.65776 | 0.418387 | 0.00262242 | 0.0498835 | 9.68791e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10758.1 | 0.0858083 | 5966ms | 5212421 | 320 | 5.03059e+07 | 462067 | 0.0366378 | 0.469446 | 1.95585 | 0.18325 | 0.00198931 | 0.0394018 | 4.29563e-06 | 1(Win) | true |
| simdjson (ondemand) | 9837.1 | 0.0735097 | 6563.05ms | 5212421 | 640 | 8.83109e+07 | 505327 | 0.0957799 | 0.51652 | 2.19705 | 0.202785 | 0.00216707 | 0.0394067 | 6.84063e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10737.6 | 0.18782 | 6016.73ms | 5212421 | 80 | 6.04842e+07 | 462949 | 0.106567 | 0.471564 | 1.95582 | 0.183243 | 0.00198395 | 0.0394079 | 4.73628e-06 | 1(Win) | true |
| simdjson (ondemand) | 9878.86 | 0.100134 | 6548.61ms | 5212421 | 320 | 8.12414e+07 | 503191 | 0.358767 | 0.516599 | 2.19702 | 0.202778 | 0.002168 | 0.0394054 | 1.4017e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5961.27 | 0.157454 | 8698.61ms | 2090234 | 80 | 2.21772e+07 | 334392 | 0.0237166 | 0.846776 | 4.69133 | 0.718822 | 0.00266517 | 0.0763064 | 1.33956e-06 | 1(Win) | true |
| simdjson (ondemand) | 4945.86 | 0.147138 | 5298.29ms | 2090234 | 40 | 1.40674e+07 | 403044 | 0.706098 | 1.02894 | 5.09756 | 0.738336 | 0.00304328 | 0.0758865 | 4.78415e-07 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5984.36 | 0.0613858 | 8714.11ms | 2090234 | 30 | 1.25433e+06 | 333102 | 0.109666 | 0.844523 | 4.69125 | 0.718804 | 0.00260988 | 0.0762639 | 5.13499e-06 | 1(Win) | true |
| simdjson (ondemand) | 4905.19 | 0.833781 | 5286ms | 2090234 | 640 | 7.34787e+09 | 406386 | 0.37118 | 1.03949 | 5.09748 | 0.738318 | 0.00253841 | 0.0758111 | 1.1026e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8569.78 | 0.165241 | 7565.26ms | 5212421 | 40 | 3.67484e+07 | 580056 | 0.0342944 | 0.595212 | 2.53322 | 0.311554 | 0.00202233 | 0.0590989 | 5.16555e-06 | 1(Win) | true |
| simdjson (ondemand) | 7987.56 | 0.0656996 | 8103.55ms | 5212421 | 640 | 1.06993e+08 | 622337 | 0.406053 | 0.637081 | 2.7744 | 0.33108 | 0.00217864 | 0.0590752 | 5.63078e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8542.65 | 0.12587 | 7598.02ms | 5212421 | 40 | 2.14586e+07 | 581898 | 0.441553 | 0.592014 | 2.53319 | 0.311547 | 0.00199956 | 0.0590664 | 2.87295e-06 | 1(Win) | true |
| simdjson (ondemand) | 7971.38 | 0.0917325 | 8078.02ms | 5212421 | 80 | 2.61788e+07 | 623600 | 0.0347078 | 0.637322 | 2.77436 | 0.331073 | 0.00216674 | 0.0591834 | 1.29762e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1257.4 | 0.0431092 | 9898.7ms | 500299 | 640 | 1.71249e+07 | 379450 | 0.194799 | 4.02301 | 17.989 | 3.39912 | 0.0164763 | 0.0184542 | 5.24093e-05 | 1(Win) | true |
| simdjson (ondemand) | 1125.87 | 0.0999798 | 5523.71ms | 500299 | 160 | 2.8723e+07 | 423782 | 0.0244245 | 4.50599 | 18.6546 | 3.0036 | 0.0231247 | 0.0205571 | 2.72212e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.61 | 0.048541 | 9675.52ms | 500299 | 1280 | 3.37347e+07 | 334445 | 0.106274 | 3.5503 | 16.8353 | 3.1206 | 0.0111508 | 0.0157663 | 5.03964e-05 | 1(Win) | true |
| simdjson (ondemand) | 1266.03 | 0.273768 | 5332.99ms | 500299 | 320 | 3.40634e+08 | 376865 | 0.172975 | 4.01257 | 17.507 | 2.7262 | 0.016675 | 0.0167189 | 3.91141e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2513.9 | 0.680535 | 5654.12ms | 1151920 | 640 | 5.66016e+09 | 436993 | 0.243971 | 2.01221 | 8.58617 | 1.51224 | 0.00684247 | 0.0343918 | 2.58522e-05 | 1(Win) | true |
| simdjson (ondemand) | 2395.93 | 0.0450231 | 5991.73ms | 1151920 | 640 | 2.72738e+07 | 458509 | 0.290042 | 2.11532 | 8.78977 | 1.33834 | 0.0103086 | 0.0356868 | 3.58545e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2805.54 | 0.979316 | 5530.85ms | 1151920 | 320 | 4.70553e+09 | 391568 | 0.35622 | 1.80898 | 8.0862 | 1.39154 | 0.00486878 | 0.0303411 | 1.95923e-05 | 1(Win) | true |
| simdjson (ondemand) | 2653.99 | 0.0848593 | 5804.41ms | 1151920 | 160 | 1.97407e+07 | 413926 | 0.121976 | 1.90743 | 8.2934 | 1.21841 | 0.00800363 | 0.0321377 | 1.44704e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.158 | 0.180134 | 8924.07ms | 500299 | 30 | 4.57255e+07 | 685365 | 0.0440057 | 7.34177 | 36.6901 | 7.5749 | 0.0220754 | 0.0226535 | 9.33442e-05 | 1(Win) | true |
| simdjson (ondemand) | 414.218 | 0.0777065 | 7340.92ms | 500299 | 30 | 2.40346e+07 | 1.15186e+06 | 0.035177 | 12.2024 | 65.6047 | 13.0831 | 0.0363365 | 0.0330706 | 6.86256e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 745.678 | 0.083858 | 8675.94ms | 500299 | 160 | 4.60643e+07 | 639850 | 0.026918 | 6.83371 | 35.5328 | 7.29686 | 0.0162862 | 0.0178734 | 2.73711e-05 | 1(Win) | true |
| simdjson (ondemand) | 432.063 | 0.0509753 | 7246.71ms | 500299 | 160 | 5.06998e+07 | 1.10429e+06 | 0.0612604 | 11.7 | 64.4547 | 12.8063 | 0.0295968 | 0.0249884 | 3.86394e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.65 | 0.0385168 | 9742.86ms | 1151920 | 640 | 5.42255e+07 | 755722 | 0.115352 | 3.49817 | 17.0618 | 3.38721 | 0.00936624 | 0.0398866 | 2.89924e-05 | 1(Win) | true |
| simdjson (ondemand) | 920.4 | 0.171728 | 7624.74ms | 1151920 | 30 | 1.26037e+08 | 1.19356e+06 | 0.336716 | 5.52163 | 29.1359 | 5.70734 | 0.0154171 | 0.0800947 | 9.71711e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1539.53 | 0.0534846 | 9573.45ms | 1151920 | 320 | 4.661e+07 | 713568 | 0.0478591 | 3.29539 | 16.5617 | 3.26699 | 0.00713296 | 0.0345606 | 2.29264e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.411 | 0.579686 | 7597.92ms | 1151920 | 160 | 7.24421e+09 | 1.16076e+06 | 0.471241 | 5.36099 | 28.6368 | 5.5872 | 0.0126107 | 0.0718637 | 4.33027e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5235.87 | 0.20202 | 5088.53ms | 500299 | 30 | 1.01669e+06 | 91125.6 | 0.145615 | 0.975919 | 5.40884 | 0.739146 | 0.000981546 | 0.00272997 | 8.66149e-07 | 1(Win) | true |
| simdjson (ondemand) | 4871.98 | 0.120284 | 5446.39ms | 500299 | 30 | 416279 | 97932 | 0.10955 | 1.05714 | 5.51372 | 0.724669 | 0.00127904 | 0.00224153 | 3.7844e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5279.28 | 0.0589513 | 9866.11ms | 500299 | 640 | 1.81667e+06 | 90376.4 | 0.0912413 | 0.96423 | 5.37987 | 0.732364 | 0.000898828 | 0.00269606 | 1.40229e-06 | 1(Win) | true |
| simdjson (ondemand) | 4851.72 | 0.169683 | 5364.6ms | 500299 | 30 | 835350 | 98340.9 | 0.121842 | 1.04153 | 5.48477 | 0.717905 | 0.00125438 | 0.00204178 | 2.06543e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8459.16 | 0.181148 | 7166.61ms | 1151920 | 160 | 8.85479e+06 | 129866 | 0.375609 | 0.604053 | 3.03765 | 0.353911 | 0.000951108 | 0.0070189 | 1.6657e-06 | 1(Win) | true |
| simdjson (ondemand) | 8183.31 | 0.241708 | 7247.97ms | 1151920 | 1280 | 1.34765e+08 | 134244 | 0.06295 | 0.618892 | 3.07938 | 0.34772 | 0.00118811 | 0.00730709 | 6.63498e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8343.74 | 0.0680158 | 7138ms | 1151920 | 2560 | 2.05297e+07 | 131662 | 0.114611 | 0.609221 | 3.02512 | 0.350985 | 0.000888498 | 0.00737194 | 4.13271e-06 | 1(Win) | true |
| simdjson (ondemand) | 8295.36 | 0.0279878 | 7156.35ms | 1151920 | 2560 | 3.51683e+06 | 132430 | 0.328275 | 0.610838 | 3.06702 | 0.344856 | 0.00118782 | 0.00975455 | 4.78752e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2916.5 | 0.157254 | 8803.24ms | 500299 | 160 | 1.05892e+07 | 163594 | 0.012544 | 1.74305 | 9.81407 | 1.76932 | 0.00215915 | 0.00278167 | 6.39618e-06 | 1(Win) | true |
| simdjson (ondemand) | 2834.59 | 0.198225 | 8968.75ms | 500299 | 160 | 1.78123e+07 | 168322 | 0.017779 | 1.79205 | 10.1222 | 1.72956 | 0.00250043 | 0.00202709 | 1.87388e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2935.82 | 0.0878749 | 8736.83ms | 500299 | 640 | 1.3053e+07 | 162517 | 0.0539583 | 1.7372 | 9.78511 | 1.76254 | 0.00210328 | 0.00272172 | 1.04531e-05 | 1(Win) | true |
| simdjson (ondemand) | 2861.72 | 0.178995 | 8857.86ms | 500299 | 160 | 1.42498e+07 | 166726 | 0.276556 | 1.77169 | 10.0933 | 1.7228 | 0.00244837 | 0.00214397 | 1.36169e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5482.74 | 0.143621 | 5383.13ms | 1151920 | 160 | 1.32496e+07 | 200366 | 0.325793 | 0.93756 | 5.08132 | 0.784265 | 0.00176267 | 0.0107859 | 1.74274e-05 | 1(Win) | true |
| Jsonifier (generic) | 5320.91 | 0.208746 | 5460.16ms | 1151920 | 1280 | 2.37749e+08 | 206460 | 0.0592816 | 0.959237 | 4.97644 | 0.804975 | 0.00148886 | 0.010072 | 4.51081e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5471.73 | 0.246414 | 5358.81ms | 1151920 | 80 | 1.95801e+07 | 200769 | 0.079389 | 0.931063 | 5.06859 | 0.781291 | 0.00175745 | 0.0105796 | 8.03007e-07 | 1(Win) | true |
| Jsonifier (generic) | 5411.54 | 0.309169 | 5412.86ms | 1151920 | 40 | 1.57564e+07 | 203003 | 0.0866643 | 0.951041 | 4.96371 | 0.801993 | 0.00150573 | 0.00979996 | 4.03023e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1414.54 | 0.0455865 | 4567.92ms | 56369 | 640 | 192090 | 38003.7 | 0.217343 | 3.61803 | 15.6053 | 3.11138 | 0.00744458 | 1.47743e-05 | 5.23892e-06 | 1(Win) | true |
| simdjson (ondemand) | 1205.99 | 0.0343917 | 5210.6ms | 56369 | 1280 | 300824 | 44575.7 | 0.0470296 | 4.27043 | 17.053 | 2.86634 | 0.0142706 | 8.81469e-06 | 2.99367e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.16 | 0.0222115 | 4067.24ms | 56369 | 1280 | 57073.6 | 30063.1 | 0.00835552 | 2.87942 | 13.3082 | 2.60819 | 0.00534566 | 1.00898e-05 | 2.61946e-06 | 1(Win) | true |
| simdjson (ondemand) | 1422.84 | 0.0210268 | 4878.08ms | 56369 | 4890 | 308620 | 37781.9 | 0.100603 | 3.60017 | 14.7972 | 2.37353 | 0.0131823 | 1.43627e-05 | 4.70534e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1975.48 | 0.0134235 | 4795.49ms | 83958 | 4890 | 144750 | 40531.2 | 0.244385 | 2.60158 | 11.059 | 2.09798 | 0.00513471 | 1.2924e-05 | 5.5559e-06 | 1(Win) | true |
| simdjson (ondemand) | 1772.18 | 0.0117676 | 5258.12ms | 83958 | 4890 | 138228 | 45180.9 | 0.054988 | 2.90451 | 11.865 | 1.9435 | 0.00789461 | 8.48121e-06 | 2.72802e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2432.33 | 0.0222557 | 4393.96ms | 83958 | 1280 | 68702 | 32918.5 | 0.179953 | 2.11857 | 9.5185 | 1.76156 | 0.00413927 | 9.08192e-06 | 4.57818e-06 | 1(Win) | true |
| simdjson (ondemand) | 2045.84 | 0.0448333 | 5015.97ms | 83958 | 640 | 197043 | 39137.2 | 0.00293048 | 2.51944 | 10.3599 | 1.61508 | 0.00942272 | 3.88959e-06 | 7.4442e-07 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 683.114 | 0.126945 | 8576.19ms | 56369 | 2560 | 2.55484e+07 | 78695 | 0.0127017 | 7.43411 | 35.3914 | 7.26188 | 0.0114364 | 4.26112e-05 | 1.72274e-05 | 1(Win) | true |
| simdjson (ondemand) | 200.108 | 0.0447251 | 7045.81ms | 56369 | 1280 | 1.84785e+07 | 268644 | 0.0801534 | 25.4521 | 139.931 | 28.1377 | 0.0343825 | 6.68308e-05 | 3.4843e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.015 | 0.0219679 | 8148.41ms | 56369 | 2560 | 616466 | 70639.4 | 0.215898 | 6.7167 | 33.1011 | 6.7667 | 0.0097834 | 1.00828e-05 | 1.57999e-06 | 1(Win) | true |
| simdjson (ondemand) | 204.863 | 0.0608409 | 6998.7ms | 56369 | 640 | 1.63127e+07 | 262408 | 0.208623 | 24.9751 | 137.674 | 27.6535 | 0.0315694 | 3.14612e-05 | 1.25845e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 901.879 | 0.0647609 | 9642.95ms | 83958 | 640 | 2.1156e+06 | 88779.8 | 0.0638908 | 5.68366 | 25.0917 | 5.23911 | 0.00795234 | 2.14951e-05 | 9.06331e-06 | 1(Win) | true |
| simdjson (ondemand) | 297.28 | 0.0815909 | 7078.44ms | 83958 | 320 | 1.54535e+07 | 269337 | 0.0205868 | 17.2133 | 93.9956 | 18.8319 | 0.0235326 | 1.567e-05 | 5.65759e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 988.077 | 0.0268578 | 9157.44ms | 83958 | 1280 | 606308 | 81034.7 | 0.0141518 | 5.18864 | 23.564 | 4.90904 | 0.0067081 | 1.15292e-05 | 5.34121e-06 | 1(Win) | true |
| simdjson (ondemand) | 304.972 | 0.0569942 | 6981.14ms | 83958 | 640 | 1.433e+07 | 262544 | 0.00595888 | 16.7882 | 92.5015 | 18.5106 | 0.0229092 | 5.103e-05 | 3.26056e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2345 | 0.0464604 | 3040.31ms | 56369 | 320 | 36300.4 | 22924.4 | 0.0916034 | 2.19904 | 9.90158 | 1.76729 | 0.00380822 | 3.65893e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2031.89 | 0.0822825 | 3390.28ms | 56369 | 320 | 151651 | 26457 | 0.0902419 | 2.53807 | 10.4997 | 1.7176 | 0.00690883 | 1.31389e-05 | 7.15154e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2928.03 | 0.052857 | 2844.81ms | 56369 | 640 | 60272.1 | 18359.7 | 0.11127 | 1.75159 | 8.28239 | 1.41697 | 0.00265189 | 1.25845e-05 | 6.43084e-06 | 1(Win) | true |
| simdjson (ondemand) | 2443.84 | 0.0356246 | 3239.71ms | 56369 | 2560 | 157209 | 21997.2 | 0.0512649 | 2.10573 | 8.88338 | 1.36925 | 0.00598602 | 7.01987e-06 | 2.12744e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3277.36 | 0.0272349 | 3178.18ms | 83958 | 1280 | 56668.1 | 24430.8 | 0.0212123 | 1.57231 | 7.17244 | 1.21094 | 0.00273339 | 4.17806e-06 | 1.2376e-06 | 1(Win) | true |
| simdjson (ondemand) | 2730.58 | 0.122075 | 3666.46ms | 83958 | 160 | 205017 | 29322.9 | 0.0406631 | 1.88762 | 7.47084 | 1.17431 | 0.00755214 | 1.03474e-05 | 6.32757e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4071.49 | 0.0172496 | 2976.44ms | 83958 | 4890 | 56270.7 | 19665.7 | 0.137548 | 1.2625 | 6.0837 | 0.975035 | 0.00180849 | 3.85576e-06 | 5.45603e-07 | 1(Win) | true |
| simdjson (ondemand) | 3441.86 | 0.0546199 | 3353.7ms | 83958 | 640 | 103328 | 23263.1 | 0.0413037 | 1.49728 | 6.38432 | 0.939839 | 0.00423205 | 1.1706e-05 | 6.83005e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1783.76 | 0.0764214 | 3749.98ms | 56369 | 80 | 42435.3 | 30137.2 | 0.028528 | 2.89037 | 13.3859 | 2.50554 | 0.00722361 | 3.3263e-06 | 2.21753e-07 | 1(Win) | true |
| simdjson (ondemand) | 1336.24 | 0.25283 | 4761.34ms | 56369 | 40 | 413837 | 40230.6 | 0.110366 | 3.8567 | 17.5182 | 2.91568 | 0.0101177 | 5.32207e-06 | 8.87012e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2127.65 | 0.026413 | 3551.89ms | 56369 | 640 | 28503.3 | 25266.2 | 0.0177268 | 2.42386 | 11.7846 | 2.16137 | 0.00555683 | 3.13226e-06 | 2.49472e-07 | 1(Win) | true |
| simdjson (ondemand) | 1497.06 | 0.143349 | 4669.73ms | 56369 | 160 | 423950 | 35908.9 | 0.208722 | 3.44254 | 15.9767 | 2.58673 | 0.00935177 | 8.981e-06 | 4.32419e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2497.05 | 0.0220557 | 3934.51ms | 83958 | 4890 | 244580 | 32065.2 | 0.115618 | 2.05672 | 9.72625 | 1.73988 | 0.003309 | 7.99406e-06 | 3.0544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1945.33 | 0.099534 | 4833.37ms | 83958 | 320 | 537069 | 41159.4 | 0.0260109 | 2.63718 | 12.0444 | 1.95048 | 0.0067734 | 3.98265e-06 | 1.11663e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2910.9 | 0.0346428 | 3735.37ms | 83958 | 2560 | 232453 | 27506.5 | 0.279488 | 1.76101 | 8.65416 | 1.50905 | 0.00261584 | 4.46652e-06 | 1.11663e-06 | 1(Win) | true |
| simdjson (ondemand) | 2205.4 | 0.0470023 | 4667.26ms | 83958 | 1280 | 372733 | 36305.7 | 0.0808792 | 2.33714 | 10.9993 | 1.72752 | 0.00561146 | 4.19667e-06 | 8.00251e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.56 | 0.0516495 | 4681.91ms | 53331 | 640 | 261102 | 39106.5 | 0.0532644 | 3.96197 | 13.9699 | 2.74989 | 0.0130499 | 4.38007e-05 | 2.33799e-05 | 1(Win) | true |
| simdjson (ondemand) | 998.82 | 0.139633 | 5821.19ms | 53331 | 2560 | 1.2942e+07 | 50920.5 | 0.0626936 | 5.15083 | 18.8427 | 3.49552 | 0.0206926 | 5.62818e-05 | 2.31162e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1621.79 | 0.0294508 | 4418.16ms | 53331 | 2560 | 218376 | 31360.7 | 0.175335 | 3.1775 | 11.7509 | 2.24174 | 0.0104883 | 1.9117e-05 | 8.69423e-06 | 1(Win) | true |
| simdjson (ondemand) | 1186.35 | 0.0357983 | 5582.2ms | 53331 | 2560 | 602973 | 42871.3 | 0.0422854 | 4.341 | 16.6658 | 2.99762 | 0.017118 | 1.52643e-05 | 3.47183e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1464.01 | 0.0802337 | 4972.34ms | 65103 | 320 | 370492 | 42409 | 0.14524 | 3.51992 | 12.0289 | 2.32558 | 0.0115057 | 1.29602e-05 | 4.65608e-06 | 1(Win) | true |
| simdjson (ondemand) | 1196.93 | 0.0628371 | 5934.63ms | 65103 | 640 | 679951 | 51872 | 0.0608206 | 4.30311 | 15.6238 | 2.86542 | 0.0180642 | 2.23444e-05 | 7.94414e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1793.93 | 0.0411185 | 4733.23ms | 65103 | 1280 | 259225 | 34609.6 | 0.0271618 | 2.8706 | 10.2017 | 1.90724 | 0.00869648 | 8.88016e-06 | 2.70005e-06 | 1(Win) | true |
| simdjson (ondemand) | 1421.04 | 0.0305932 | 5708.22ms | 65103 | 2560 | 457383 | 43691.3 | 0.098186 | 3.62497 | 13.8407 | 2.45858 | 0.0148727 | 1.08542e-05 | 2.14804e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 970.788 | 0.0255941 | 5970.91ms | 53331 | 2560 | 460288 | 52390.9 | 0.011186 | 5.30546 | 19.4979 | 3.91727 | 0.0165437 | 1.82601e-05 | 5.30297e-06 | 1(Win) | true |
| simdjson (ondemand) | 439.577 | 0.105538 | 6324.24ms | 53331 | 640 | 9.54304e+06 | 115703 | 0.0973844 | 11.6173 | 40.8149 | 7.37027 | 0.068995 | 3.50113e-05 | 1.79012e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1136.86 | 0.0213504 | 5769.04ms | 53331 | 4890 | 446137 | 44737.7 | 0.0914339 | 4.49288 | 17.2077 | 3.39326 | 0.0137668 | 1.52882e-05 | 6.94049e-06 | 1(Win) | true |
| simdjson (ondemand) | 481.651 | 0.073828 | 6138.3ms | 53331 | 1280 | 7.77941e+06 | 105596 | 0.207927 | 10.6336 | 38.5623 | 6.85593 | 0.0625555 | 2.22373e-05 | 8.51111e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1050.13 | 0.0189759 | 6649.02ms | 65103 | 4890 | 615500 | 59123 | 0.1131 | 4.90384 | 16.9365 | 3.39101 | 0.0150111 | 3.75557e-05 | 2.08824e-05 | 1(Win) | true |
| simdjson (ondemand) | 552.387 | 0.0468231 | 6146.55ms | 65103 | 2560 | 7.09048e+06 | 112398 | 0.0294556 | 9.29031 | 33.2849 | 5.97369 | 0.0524147 | 3.52206e-05 | 1.42083e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1217.88 | 0.0355935 | 6422.18ms | 65103 | 1280 | 421451 | 50979.8 | 0.098116 | 4.22582 | 15.0573 | 2.96163 | 0.0121972 | 2.37484e-05 | 1.28762e-05 | 1(Win) | true |
| simdjson (ondemand) | 601.931 | 0.0483895 | 5992.68ms | 65103 | 2560 | 6.37752e+06 | 103147 | 0.151444 | 8.53761 | 31.4571 | 5.55668 | 0.0479903 | 4.92069e-05 | 3.35826e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7909.28 | 0.0327712 | 1369.47ms | 53331 | 2560 | 11368.7 | 6430.47 | 0.0503412 | 0.654809 | 3.0039 | 0.422006 | 0.000819074 | 3.69889e-06 | 6.07937e-07 | 1(Win) | true |
| simdjson (ondemand) | 6852.62 | 0.0310358 | 1466ms | 53331 | 2560 | 13583.5 | 7422.04 | 0.142016 | 0.750422 | 3.34655 | 0.4161 | 0.000879011 | 3.36196e-06 | 4.76095e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8711.05 | 0.0202482 | 1330.72ms | 53331 | 4890 | 6834.37 | 5838.61 | 0.142183 | 0.59511 | 2.83355 | 0.384186 | 0.000699613 | 4.82767e-06 | 1.56832e-06 | 1(Win) | true |
| simdjson (ondemand) | 7376.76 | 0.023315 | 1425.45ms | 53331 | 2560 | 6615.14 | 6894.68 | 0.0344293 | 0.702216 | 3.1867 | 0.380473 | 0.000934509 | 2.8346e-06 | 2.19736e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8198.93 | 0.0431372 | 1481.06ms | 65103 | 1280 | 13658.5 | 7572.58 | 0.0505367 | 0.631125 | 2.83288 | 0.360045 | 0.00078149 | 6.90012e-06 | 3.32406e-06 | 1(Win) | true |
| simdjson (ondemand) | 7732.02 | 0.0549452 | 1535.75ms | 65103 | 320 | 6229.12 | 8029.86 | 0.0417796 | 0.66941 | 2.98315 | 0.352196 | 0.000814431 | 4.65608e-06 | 1.63203e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8860.12 | 0.0419168 | 1444.32ms | 65103 | 1280 | 11043.5 | 7007.47 | 0.131094 | 0.584499 | 2.69333 | 0.329063 | 0.000685752 | 3.07206e-06 | 4.20008e-07 | 1(Win) | true |
| simdjson (ondemand) | 8284.01 | 0.0783751 | 1496ms | 65103 | 160 | 5520.74 | 7494.81 | 0.0194339 | 0.625118 | 2.8522 | 0.323011 | 0.000776942 | 2.59205e-06 | 4.80009e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5574.92 | 0.0208432 | 1634.78ms | 53331 | 4890 | 17681.5 | 9123.07 | 0.193337 | 0.925908 | 4.37635 | 0.713694 | 0.00181953 | 5.98569e-06 | 1.67185e-06 | 1(Win) | true |
| simdjson (ondemand) | 4143.06 | 0.0224469 | 1959.91ms | 53331 | 4890 | 37131.1 | 12276 | 0.000941709 | 1.24094 | 5.90201 | 0.948548 | 0.0022084 | 3.754e-06 | 3.87287e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5984.63 | 0.104549 | 1613.92ms | 53331 | 30 | 2368.33 | 8498.5 | 0.0709426 | 0.865382 | 4.20603 | 0.675911 | 0.00155819 | 3.12514e-06 | 1.25005e-06 | 1(Win) | true |
| simdjson (ondemand) | 4355.49 | 0.0348088 | 1909.45ms | 53331 | 1280 | 21148.2 | 11677.3 | 0.00741902 | 1.18545 | 5.7422 | 0.912959 | 0.00207137 | 1.40485e-05 | 1.01225e-05 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6016.28 | 0.0186478 | 1760.37ms | 65103 | 4890 | 18109.7 | 10319.8 | 0.0440432 | 0.856907 | 3.96635 | 0.608544 | 0.0015572 | 3.55265e-06 | 1.02402e-06 | 1(Win) | true |
| simdjson (ondemand) | 4805.66 | 0.0671316 | 2046.67ms | 65103 | 320 | 24071.3 | 12919.6 | 0.314902 | 1.06209 | 5.07588 | 0.78809 | 0.00171747 | 8.97616e-06 | 5.4721e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6389.1 | 0.0750153 | 1721.94ms | 65103 | 320 | 17004.9 | 9717.66 | 0.0528634 | 0.809144 | 3.82683 | 0.577593 | 0.00137354 | 3.98407e-06 | 1.24802e-06 | 1(Win) | true |
| simdjson (ondemand) | 5094.72 | 0.0269408 | 1988.01ms | 65103 | 2560 | 27594.6 | 12186.6 | 0.0314957 | 1.01301 | 4.94496 | 0.758936 | 0.00162467 | 3.21006e-06 | 6.00011e-07 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1289.82 | 0.0363236 | 1604.19ms | 11812 | 2560 | 25763.6 | 8733.62 | 0.0241224 | 3.9755 | 18.1438 | 3.54521 | 0.00612463 | 2.53318e-05 | 6.21719e-06 | 1(Win) | true |
| simdjson (ondemand) | 1037.17 | 0.0534917 | 1815.22ms | 11812 | 1280 | 43204.8 | 10861.1 | 0.10099 | 4.943 | 20.696 | 3.60307 | 0.00784127 | 3.80969e-05 | 1.60721e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.88 | 0.0507671 | 1569.31ms | 11812 | 160 | 2552.21 | 7867.12 | 0.0773191 | 3.617 | 17.1199 | 3.31349 | 0.00481131 | 2.27523e-05 | 5.29123e-06 | 1(Win) | true |
| simdjson (ondemand) | 1118.35 | 0.0322693 | 1785.56ms | 11812 | 2560 | 27046.4 | 10072.7 | 0.0907108 | 4.61029 | 19.6283 | 3.36421 | 0.00720583 | 3.6278e-05 | 1.36249e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2400.4 | 0.0326382 | 1740ms | 25388 | 2560 | 27744.7 | 10086.6 | 0.0108076 | 2.13837 | 9.30692 | 1.69281 | 0.00320693 | 1.17858e-05 | 3.49267e-06 | 1(Win) | true |
| simdjson (ondemand) | 2137.46 | 0.0459556 | 1875ms | 25388 | 640 | 17342.8 | 11327.4 | 0.0641146 | 2.41743 | 10.3023 | 1.71481 | 0.00314531 | 2.99723e-05 | 1.76634e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2592 | 0.060807 | 1742.88ms | 25388 | 160 | 5161.95 | 9341 | 0.175929 | 1.99596 | 8.78943 | 1.57712 | 0.00290861 | 5.66212e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2275.19 | 0.0289818 | 1845.84ms | 25388 | 2560 | 24350.8 | 10641.7 | 0.0140788 | 2.26228 | 9.78675 | 1.59938 | 0.00283072 | 8.78552e-06 | 1.80019e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 784.926 | 0.0301757 | 2167.82ms | 11812 | 2560 | 48011.3 | 14351.4 | 0.129404 | 6.55482 | 30.0242 | 6.03353 | 0.0159962 | 3.01269e-05 | 1.23021e-05 | 1(Win) | true |
| simdjson (ondemand) | 688.266 | 0.0431417 | 2365.28ms | 11812 | 640 | 31908.8 | 16366.9 | 0.0444392 | 7.48907 | 33.5745 | 6.19501 | 0.0124765 | 1.36249e-05 | 9.25965e-07 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.43 | 0.0703174 | 2145.78ms | 11812 | 640 | 59803.9 | 13747.1 | 0.14124 | 6.23547 | 28.9379 | 5.78945 | 0.0153917 | 2.05035e-05 | 6.61404e-06 | 1(Win) | true |
| simdjson (ondemand) | 718.685 | 0.0857545 | 2342.43ms | 11812 | 4890 | 883471 | 15674.2 | 0.164553 | 7.16257 | 32.488 | 5.95234 | 0.0122578 | 0.000101592 | 5.92445e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1541.92 | 0.0358502 | 2303.46ms | 25388 | 1280 | 40562.7 | 15702.4 | 0.0779198 | 3.34742 | 14.9805 | 2.93556 | 0.00738778 | 2.14791e-05 | 8.40087e-06 | 1(Win) | true |
| simdjson (ondemand) | 1401.88 | 0.023814 | 2460.16ms | 25388 | 2560 | 43305.1 | 17271 | 0.0499756 | 3.67765 | 16.0666 | 2.87835 | 0.00640912 | 1.96482e-05 | 7.12381e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1603.06 | 0.0790745 | 2305.67ms | 25388 | 320 | 45643.8 | 15103.6 | 0.0190937 | 3.22111 | 14.4705 | 2.8209 | 0.00699875 | 7.1392e-06 | 1.10781e-06 | 1(Win) | true |
| simdjson (ondemand) | 1456.43 | 0.0173721 | 2436.41ms | 25388 | 4890 | 40784.2 | 16624.1 | 0.0404405 | 3.5412 | 15.5604 | 2.76524 | 0.0064878 | 1.48936e-05 | 4.96185e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2350.27 | 0.0354731 | 1200.65ms | 11812 | 1280 | 3700.16 | 4792.98 | 0.110294 | 2.20961 | 10.5319 | 1.9415 | 0.00349916 | 1.29635e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 2061.1 | 0.0192324 | 1267.79ms | 11812 | 4890 | 5402.88 | 5465.44 | 0.0254538 | 2.51445 | 11.7105 | 1.87868 | 0.00363019 | 2.44111e-05 | 9.48742e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2402.26 | 0.0288884 | 1196.85ms | 11812 | 2560 | 4697.8 | 4689.25 | 0.0302379 | 2.16183 | 10.3452 | 1.89604 | 0.00302142 | 2.1661e-05 | 8.59825e-06 | 1(Win) | true |
| simdjson (ondemand) | 2093.92 | 0.0281 | 1265.66ms | 11812 | 640 | 1462.58 | 5379.76 | 0.148716 | 2.47922 | 11.5238 | 1.83322 | 0.00371934 | 2.19586e-05 | 1.00533e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4107.27 | 0.0659763 | 1313.74ms | 25388 | 320 | 4840.34 | 5894.88 | 0.0599926 | 1.26222 | 5.71057 | 0.959627 | 0.00205831 | 6.40066e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3985.73 | 0.0220398 | 1334.27ms | 25388 | 2560 | 4588.76 | 6074.65 | 0.0636759 | 1.30063 | 6.08343 | 0.904601 | 0.00173107 | 1.05549e-05 | 3.06186e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4185.76 | 0.0768672 | 1311.41ms | 25388 | 320 | 6326.17 | 5784.34 | 0.0231281 | 1.23874 | 5.62372 | 0.938475 | 0.00204612 | 6.76993e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 4036.01 | 0.0203631 | 1332.62ms | 25388 | 4890 | 7297.08 | 5998.97 | 0.193552 | 1.28249 | 5.99657 | 0.883449 | 0.00179126 | 6.39563e-06 | 1.07131e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1755.2 | 0.0422619 | 1367.84ms | 11812 | 1280 | 9416.77 | 6417.95 | 0.0345469 | 2.9486 | 14.0227 | 2.64265 | 0.00826397 | 1.06486e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 1581.71 | 0.0495934 | 1439.41ms | 11812 | 640 | 7984 | 7121.9 | 0.098429 | 3.27406 | 14.6178 | 2.41763 | 0.0069667 | 9.52421e-06 | 7.93684e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1775.85 | 0.0488726 | 1363.53ms | 11812 | 1280 | 12302 | 6343.34 | 0.284297 | 2.91473 | 13.836 | 2.59719 | 0.00774517 | 1.11116e-05 | 1.12439e-06 | 1(Win) | true |
| simdjson (ondemand) | 1594.04 | 0.0327217 | 1443.05ms | 11812 | 4890 | 26147.4 | 7066.81 | 0.222613 | 3.22607 | 14.4312 | 2.37216 | 0.00689893 | 2.32684e-05 | 6.71737e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3254.18 | 0.03432 | 1471.66ms | 25388 | 2560 | 16692 | 7440.23 | 0.0240558 | 1.57997 | 7.29057 | 1.30168 | 0.00323249 | 7.72388e-06 | 1.32321e-06 | 1(Win) | true |
| simdjson (ondemand) | 3134.96 | 0.0663488 | 1503ms | 25388 | 640 | 16805.1 | 7723.2 | 0.0163293 | 1.6504 | 7.43611 | 1.15535 | 0.00322507 | 6.09294e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3307.5 | 0.122608 | 1466.32ms | 25388 | 160 | 12888.9 | 7320.31 | 0.0439895 | 1.56439 | 7.20372 | 1.28053 | 0.00303145 | 1.18166e-05 | 3.44651e-06 | 1(Win) | true |
| simdjson (ondemand) | 3163.16 | 0.0404912 | 1496.62ms | 25388 | 2560 | 24591 | 7654.33 | 0.0207203 | 1.6247 | 7.34926 | 1.1342 | 0.00317087 | 9.75485e-06 | 1.93866e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.85 | 0.0170535 | 7598.25ms | 108313 | 4890 | 673632 | 68824.8 | 0.0891372 | 3.38143 | 14.88 | 3.01818 | 0.00414307 | 1.49249e-05 | 6.85735e-06 | 1(Win) | true |
| simdjson (ondemand) | 1396.9 | 0.0383465 | 8158.12ms | 108313 | 1280 | 1.02918e+06 | 73946.2 | 0.0190463 | 3.6635 | 16.6552 | 2.51372 | 0.00709797 | 3.98945e-05 | 2.66011e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1634.53 | 0.0349752 | 7247.3ms | 108313 | 1280 | 625327 | 63195.8 | 0.0940385 | 3.12971 | 14.1474 | 2.84873 | 0.00347974 | 1.01413e-05 | 5.81359e-06 | 1(Win) | true |
| simdjson (ondemand) | 1505.5 | 0.0364009 | 7805ms | 108313 | 1280 | 798430 | 68612.1 | 0.194758 | 3.40771 | 15.9279 | 2.34549 | 0.00607275 | 3.12967e-05 | 2.25403e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2259.8 | 0.0244795 | 8505.59ms | 183677 | 2560 | 921747 | 77514.7 | 0.0852181 | 2.23307 | 10.3442 | 1.50767 | 0.00371354 | 4.95095e-06 | 2.94122e-06 | 1(Win) | true |
| Jsonifier (generic) | 2227.13 | 0.0265404 | 8607.11ms | 183677 | 2560 | 1.11551e+06 | 78651.8 | 0.0169138 | 2.27179 | 9.6198 | 1.83769 | 0.00245403 | 2.11245e-05 | 1.60736e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2406.44 | 0.0192981 | 8206.82ms | 183677 | 4890 | 964938 | 72791.4 | 0.192906 | 2.11977 | 9.18002 | 1.73476 | 0.00182847 | 1.23628e-05 | 8.8657e-06 | 1(Win) | true |
| simdjson (ondemand) | 2399.19 | 0.108953 | 8207.81ms | 183677 | 80 | 506233 | 73011.4 | 0.0283255 | 2.10775 | 9.92847 | 1.4099 | 0.00367398 | 2.04163e-05 | 1.66052e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 630.247 | 0.0437915 | 8717.23ms | 108313 | 640 | 3.29686e+06 | 163897 | 0.106727 | 8.06347 | 38.0978 | 7.59829 | 0.0110979 | 2.08453e-05 | 5.84244e-06 | 1(Win) | true |
| simdjson (ondemand) | 241.524 | 0.17291 | 5502.12ms | 108313 | 320 | 1.74997e+08 | 427681 | 0.0828794 | 20.9796 | 100.159 | 18.1433 | 0.0704498 | 0.00024746 | 0.00015952 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 660.129 | 0.0639516 | 8550.41ms | 108313 | 80 | 801119 | 156477 | 0.219747 | 7.80112 | 37.3763 | 7.43234 | 0.010679 | 1.45412e-05 | 5.77031e-06 | 1(Win) | true |
| simdjson (ondemand) | 248.189 | 0.0675656 | 5432.53ms | 108313 | 640 | 5.06088e+07 | 416196 | 0.0235366 | 20.6262 | 99.4376 | 17.9773 | 0.0703087 | 3.90939e-05 | 1.82919e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 960.546 | 0.0209153 | 9680.88ms | 183677 | 2560 | 3.72426e+06 | 182363 | 0.158634 | 5.29922 | 24.168 | 4.79153 | 0.00569132 | 1.75474e-05 | 1.03017e-05 | 1(Win) | true |
| simdjson (ondemand) | 420.604 | 0.221783 | 5410.84ms | 183677 | 80 | 6.8251e+07 | 416468 | 0.286557 | 12.1911 | 58.7619 | 10.566 | 0.037072 | 3.33466e-05 | 1.89191e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 996.936 | 0.0173961 | 9457.35ms | 183677 | 2560 | 2.39177e+06 | 175706 | 0.00310186 | 5.15019 | 23.742 | 4.69358 | 0.00560066 | 1.80641e-05 | 1.128e-05 | 1(Win) | true |
| simdjson (ondemand) | 424.227 | 0.0730591 | 5372.34ms | 183677 | 640 | 5.82428e+07 | 412911 | 0.0185346 | 11.9926 | 58.3352 | 10.4679 | 0.0363959 | 0.000109542 | 8.75518e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4998.32 | 0.0303992 | 2805.38ms | 108313 | 2560 | 101036 | 20666 | 0.0890614 | 1.02245 | 5.53887 | 0.852871 | 0.0010264 | 8.79973e-06 | 4.68477e-06 | 1(Win) | true |
| simdjson (ondemand) | 4252.77 | 0.0245566 | 3167.67ms | 108313 | 4890 | 173965 | 24289 | 0.000476951 | 1.19846 | 6.10412 | 0.772659 | 0.00126631 | 1.11715e-05 | 7.4181e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5353.87 | 0.0583221 | 2699.46ms | 108313 | 80 | 10129.4 | 19293.6 | 0.0227355 | 0.964299 | 5.35389 | 0.803671 | 0.000803689 | 2.76975e-06 | 1.96191e-06 | 1(Win) | true |
| simdjson (ondemand) | 4483.7 | 0.0422139 | 3045.76ms | 108313 | 1280 | 121063 | 23038 | 0.0656162 | 1.14163 | 5.92018 | 0.723718 | 0.00110382 | 2.71205e-06 | 7.93418e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6770.64 | 0.0153085 | 3319.76ms | 183677 | 4890 | 76704.9 | 25871.7 | 0.0172068 | 0.761126 | 3.87652 | 0.534928 | 0.000527335 | 1.72237e-06 | 5.77835e-07 | 1(Win) | true |
| simdjson (ondemand) | 6318.33 | 0.0279803 | 3500.14ms | 183677 | 2560 | 154046 | 27723.8 | 0.00418593 | 0.813725 | 4.11406 | 0.477736 | 0.00105846 | 2.2309e-06 | 6.80542e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7065.1 | 0.0248265 | 3213.75ms | 183677 | 2560 | 96994 | 24793.4 | 0.000228451 | 0.728987 | 3.768 | 0.506046 | 0.000416624 | 1.07611e-06 | 4.67873e-08 | 1(Win) | true |
| simdjson (ondemand) | 6596.68 | 0.0907017 | 3399.41ms | 183677 | 160 | 92813.2 | 26554 | 0.0248018 | 0.78166 | 4.00559 | 0.448875 | 0.000989985 | 1.259e-06 | 0 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.37 | 0.212678 | 3858.97ms | 108313 | 320 | 1.42909e+06 | 31421.9 | 0.418021 | 1.56792 | 8.18969 | 1.44361 | 0.0014845 | 2.48123e-06 | 1.73109e-07 | 1(Win) | true |
| simdjson (ondemand) | 2585.35 | 0.0791023 | 4763.28ms | 108313 | 1280 | 1.27853e+06 | 39954.2 | 0.0509094 | 1.98633 | 10.3457 | 1.59747 | 0.00292903 | 4.02479e-06 | 1.3993e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3482.49 | 0.237787 | 3732.57ms | 108313 | 320 | 1.59187e+06 | 29661.4 | 0.0779447 | 1.46537 | 8.00572 | 1.39499 | 0.00124336 | 3.37563e-06 | 2.88516e-07 | 1(Win) | true |
| simdjson (ondemand) | 2658.99 | 0.169533 | 4642.57ms | 108313 | 160 | 693994 | 38847.6 | 0.0680524 | 1.93825 | 10.1619 | 1.54892 | 0.00272953 | 3.51989e-06 | 2.88516e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4674.23 | 0.169018 | 4431.03ms | 183677 | 160 | 641910 | 37475.2 | 0.0452003 | 1.09979 | 5.59955 | 0.900184 | 0.000956707 | 2.31384e-06 | 7.48597e-07 | 1(Win) | true |
| simdjson (ondemand) | 3958.4 | 0.119001 | 5127.37ms | 183677 | 640 | 1.77482e+06 | 44252.2 | 0.0750246 | 1.29463 | 6.6009 | 0.961454 | 0.00196982 | 1.36108e-06 | 1.02081e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4894.62 | 0.118032 | 4318.02ms | 183677 | 640 | 1.14196e+06 | 35787.9 | 0.0159909 | 1.04549 | 5.4911 | 0.87153 | 0.000759664 | 2.53502e-06 | 5.52941e-07 | 1(Win) | true |
| simdjson (ondemand) | 4100.07 | 0.0602397 | 5001.86ms | 183677 | 1280 | 847817 | 42723.2 | 0.0489472 | 1.25449 | 6.49251 | 0.932823 | 0.00194123 | 1.61629e-06 | 1.53122e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 612.995 | 0.119326 | 8918.78ms | 1834197 | 80 | 9.27544e+08 | 2.85357e+06 | 0.0375738 | 8.31565 | 35.2655 | 7.3955 | 0.0378327 | 0.139177 | 0.00354098 | 1(Win) | true |
| simdjson (ondemand) | 572.264 | 0.135269 | 9491.13ms | 1834197 | 80 | 1.36769e+09 | 3.05668e+06 | 0.232687 | 8.82623 | 37.2272 | 6.36161 | 0.0445514 | 0.138945 | 0.00981291 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 663.076 | 0.11668 | 8986.6ms | 1834197 | 80 | 7.57968e+08 | 2.63805e+06 | 0.114956 | 7.67816 | 32.2698 | 6.69537 | 0.0369107 | 0.118546 | 0.00500286 | 1(Win) | true |
| simdjson (ondemand) | 619.059 | 0.137231 | 9547.35ms | 1834197 | 40 | 6.0144e+08 | 2.82562e+06 | 0.0294948 | 8.1664 | 34.2314 | 5.66128 | 0.0436012 | 0.118117 | 0.0108664 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2205.64 | 0.0684776 | 9893.43ms | 7351818 | 160 | 7.5812e+08 | 3.17878e+06 | 0.105734 | 2.28272 | 9.65712 | 1.8855 | 0.0102851 | 0.0588955 | 0.00661619 | 1(Win) | true |
| simdjson (ondemand) | 2094.06 | 0.206371 | 5005.09ms | 7351818 | 30 | 1.43229e+09 | 3.34816e+06 | 0.440604 | 2.41444 | 10.2023 | 1.62706 | 0.0109843 | 0.0588178 | 0.00534768 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2384.94 | 0.182563 | 9868.85ms | 7351818 | 30 | 8.64131e+08 | 2.9398e+06 | 0.15545 | 2.12277 | 8.91025 | 1.71096 | 0.0100143 | 0.0536115 | 0.00575517 | 1(Win) | true |
| simdjson (ondemand) | 2269.33 | 0.0735162 | 10302.2ms | 7351818 | 80 | 4.12714e+08 | 3.08956e+06 | 0.0537118 | 2.23115 | 9.45533 | 1.45242 | 0.0107245 | 0.0536475 | 0.000923622 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 401.111 | 0.159028 | 6648.64ms | 1834197 | 30 | 1.44288e+09 | 4.36095e+06 | 0.546737 | 12.6876 | 62.6232 | 13.5019 | 0.0392354 | 0.344248 | 0.000179624 | 1(Win) | true |
| simdjson (ondemand) | 270.43 | 0.195416 | 9699.96ms | 1834197 | 40 | 6.39092e+09 | 6.46832e+06 | 0.0871948 | 18.7846 | 105.346 | 21.2147 | 0.047124 | 0.789032 | 0.0100976 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 418.293 | 0.143087 | 6662.3ms | 1834197 | 30 | 1.07412e+09 | 4.18182e+06 | 0.404756 | 12.0558 | 59.6326 | 12.8028 | 0.0380678 | 0.323043 | 0.000547342 | 1(Win) | true |
| simdjson (ondemand) | 278.651 | 0.0621641 | 9712.16ms | 1834197 | 80 | 1.21826e+09 | 6.27748e+06 | 0.0290427 | 18.2159 | 102.355 | 20.5158 | 0.045955 | 0.76803 | 0.0172433 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.13 | 0.325979 | 7813.79ms | 7351818 | 40 | 1.15478e+10 | 5.21231e+06 | 0.975846 | 3.77718 | 16.6536 | 3.41596 | 0.0107985 | 0.186635 | 0.00708071 | 1(Win) | true |
| simdjson (ondemand) | 930.148 | 0.0980337 | 5296.4ms | 7351818 | 40 | 2.18422e+09 | 7.53777e+06 | 0.153446 | 5.50779 | 27.1972 | 5.33287 | 0.0118159 | 0.435952 | 0.000820729 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1433.52 | 0.430798 | 7689.06ms | 7351818 | 30 | 1.33183e+10 | 4.89092e+06 | 0.275606 | 3.54698 | 15.9074 | 3.24153 | 0.010524 | 0.181295 | 0.00433258 | 1(Win) | true |
| simdjson (ondemand) | 961.294 | 0.0916392 | 5305.53ms | 7351818 | 40 | 1.7869e+09 | 7.29354e+06 | 0.960852 | 5.34073 | 26.4509 | 5.15844 | 0.0115483 | 0.430653 | 0.000820647 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4671.61 | 0.194915 | 9838.21ms | 1834197 | 160 | 8.52257e+07 | 374438 | 0.0735175 | 1.0979 | 6.28014 | 0.838105 | 0.00244447 | 0.0754577 | 1.21988e-06 | 1(Win) | true |
| simdjson (ondemand) | 4312.23 | 0.0832119 | 5247.47ms | 1834197 | 40 | 4.55743e+06 | 405644 | 0.0105747 | 1.17276 | 6.33085 | 0.867839 | 0.00351834 | 0.0749098 | 2.98496e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4598.74 | 0.152316 | 9923.44ms | 1834197 | 320 | 1.07412e+08 | 380371 | 0.141191 | 1.10705 | 6.27992 | 0.838056 | 0.00255981 | 0.0754279 | 3.3683e-06 | 1(Win) | true |
| simdjson (ondemand) | 4327.83 | 0.0588452 | 5234.54ms | 1834197 | 320 | 1.81019e+07 | 404181 | 0.133486 | 1.17345 | 6.33063 | 0.86779 | 0.00353133 | 0.0748776 | 3.81127e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10126.2 | 0.0584754 | 8898.38ms | 7351818 | 640 | 1.04912e+08 | 692387 | 0.157829 | 0.505731 | 2.37653 | 0.241967 | 0.00102663 | 0.042343 | 0.000210638 | 1(Win) | true |
| simdjson (ondemand) | 9680.14 | 0.047922 | 9447.37ms | 7351818 | 640 | 7.71038e+07 | 724291 | 0.291749 | 0.528893 | 2.4948 | 0.256654 | 0.000970091 | 0.0424171 | 7.29314e-05 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10038.9 | 0.109045 | 8993.95ms | 7351818 | 160 | 9.28006e+07 | 698410 | 0.00575649 | 0.505534 | 2.37647 | 0.241955 | 0.00104488 | 0.0423798 | 0.000183039 | 1(Win) | true |
| simdjson (ondemand) | 9814.47 | 0.0292216 | 9237.38ms | 7351818 | 320 | 1.39448e+07 | 714378 | 0.21071 | 0.52446 | 2.49475 | 0.256642 | 0.00095106 | 0.0424027 | 2.08966e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3349.76 | 0.14308 | 6751.49ms | 1834197 | 640 | 3.57274e+08 | 522194 | 0.0958524 | 1.53647 | 8.73484 | 1.53934 | 0.00252182 | 0.11316 | 1.93801e-06 | 1(Win) | true |
| simdjson (ondemand) | 2408.53 | 0.289345 | 9231.08ms | 1834197 | 320 | 1.41309e+09 | 726265 | 0.691648 | 2.13301 | 12.6415 | 2.27012 | 0.00357281 | 0.150702 | 2.20464e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3328.67 | 0.709223 | 6759.61ms | 1834197 | 40 | 5.55617e+08 | 525503 | 0.25958 | 1.54556 | 8.73462 | 1.53929 | 0.00258692 | 0.113125 | 8.17797e-07 | 1(Win) | true |
| simdjson (ondemand) | 2487.39 | 0.125746 | 9259.32ms | 1834197 | 30 | 2.34592e+07 | 703236 | 0.19612 | 2.06172 | 12.6413 | 2.27007 | 0.00339089 | 0.150648 | 2.83503e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7770.22 | 0.0959308 | 5773.31ms | 7351818 | 160 | 1.19883e+08 | 902322 | 0.136246 | 0.661236 | 3.0764 | 0.416921 | 0.00101202 | 0.0634845 | 0.000234639 | 1(Win) | true |
| simdjson (ondemand) | 6301.93 | 0.0550951 | 7214.97ms | 7351818 | 320 | 1.20232e+08 | 1.11255e+06 | 0.93694 | 0.808569 | 4.06923 | 0.606508 | 0.000981994 | 0.0848089 | 2.37654e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7706.94 | 0.116955 | 5815.64ms | 7351818 | 320 | 3.62251e+08 | 909730 | 0.56516 | 0.662884 | 3.07634 | 0.416909 | 0.00100953 | 0.0634913 | 0.00028141 | 1(Win) | true |
| simdjson (ondemand) | 6270.09 | 0.0854327 | 7098.08ms | 7351818 | 160 | 1.46019e+08 | 1.1182e+06 | 0.00199654 | 0.811175 | 4.06918 | 0.606495 | 0.000979991 | 0.0847872 | 8.99522e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1250.36 | 0.0529236 | 8155.87ms | 409725 | 640 | 1.75063e+07 | 312505 | 0.128062 | 4.05541 | 18.6337 | 3.68751 | 0.0101636 | 0.0171612 | 3.63048e-06 | 1(Win) | true |
| simdjson (ondemand) | 928.047 | 0.145719 | 5439.76ms | 409725 | 40 | 1.50569e+07 | 421039 | 0.168852 | 5.44255 | 21.1462 | 3.7874 | 0.0216492 | 0.0354222 | 0.000163768 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1602.21 | 0.135166 | 7561.89ms | 409725 | 80 | 8.69307e+06 | 243879 | 0.0219579 | 3.20571 | 15.648 | 3.01558 | 0.00652035 | 0.00580694 | 7.81012e-06 | 1(Win) | true |
| simdjson (ondemand) | 1101.91 | 0.134118 | 5166.74ms | 409725 | 80 | 1.80949e+07 | 354606 | 0.0643539 | 4.60132 | 18.1683 | 3.11728 | 0.0171538 | 0.012368 | 7.51419e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.1 | 0.0644094 | 9103.5ms | 676745 | 320 | 1.60854e+07 | 348090 | 0.0931005 | 2.72173 | 11.9153 | 2.25211 | 0.00697182 | 0.0252861 | 7.80344e-05 | 1(Win) | true |
| simdjson (ondemand) | 1483.35 | 0.0903708 | 5659.51ms | 676745 | 160 | 2.47365e+07 | 435092 | 0.137928 | 3.44102 | 13.323 | 2.31856 | 0.0143983 | 0.0346171 | 1.79905e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2261.97 | 0.0874896 | 8580.15ms | 676745 | 320 | 1.99407e+07 | 285325 | 0.0757127 | 2.23683 | 10.1066 | 1.8452 | 0.00467944 | 0.0133962 | 4.71882e-05 | 1(Win) | true |
| simdjson (ondemand) | 1730.03 | 0.0398909 | 5413.47ms | 676745 | 640 | 1.41733e+07 | 373054 | 0.0165511 | 2.92823 | 11.5218 | 1.9132 | 0.0116694 | 0.0217179 | 4.85527e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.026 | 0.0434918 | 6177.91ms | 409725 | 640 | 2.75539e+07 | 477084 | 0.0545796 | 6.23636 | 28.8171 | 5.82669 | 0.0151376 | 0.0186543 | 6.82394e-05 | 1(Win) | true |
| simdjson (ondemand) | 446.361 | 0.108411 | 5595.04ms | 409725 | 80 | 7.20525e+07 | 875399 | 0.0845783 | 11.4466 | 50.6039 | 9.29602 | 0.0396665 | 0.0356322 | 1.10135e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 953.014 | 0.140961 | 5911.26ms | 409725 | 30 | 1.00208e+07 | 410009 | 0.0735321 | 5.3872 | 25.8414 | 5.15295 | 0.0115654 | 0.00681172 | 4.40946e-05 | 1(Win) | true |
| simdjson (ondemand) | 484.161 | 0.209746 | 5442.83ms | 409725 | 30 | 8.59636e+07 | 807055 | 0.310745 | 10.5576 | 47.6373 | 8.62435 | 0.0350849 | 0.0135718 | 9.92536e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.75 | 0.0603554 | 6897.13ms | 676745 | 640 | 6.65744e+07 | 534377 | 0.0376757 | 4.22634 | 18.5633 | 3.71962 | 0.0100438 | 0.0251758 | 4.23027e-05 | 1(Win) | true |
| simdjson (ondemand) | 724.115 | 0.0531672 | 5671.79ms | 676745 | 320 | 7.18575e+07 | 891287 | 0.00573817 | 7.03765 | 30.9378 | 5.61399 | 0.0251598 | 0.0440987 | 0.000117936 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1387.19 | 0.0520272 | 6640.25ms | 676745 | 80 | 4.68739e+06 | 465253 | 0.170653 | 3.70717 | 16.7624 | 3.31189 | 0.00781555 | 0.0135819 | 0.000154157 | 1(Win) | true |
| simdjson (ondemand) | 784.035 | 0.0566548 | 5531.22ms | 676745 | 320 | 6.9599e+07 | 823171 | 0.0651328 | 6.50068 | 29.1422 | 5.20746 | 0.0226768 | 0.0233955 | 9.27694e-06 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2413.11 | 0.0175492 | 8636.06ms | 409725 | 1280 | 1.0336e+06 | 161925 | 0.0144727 | 2.09673 | 9.77072 | 1.84457 | 0.00590341 | 0.000167059 | 1.99638e-06 | 1(Win) | true |
| simdjson (ondemand) | 1917.69 | 0.0397368 | 5372.3ms | 409725 | 320 | 2.09779e+06 | 203757 | 0.000299068 | 2.63604 | 11.0923 | 1.81361 | 0.00946118 | 0.00290799 | 4.60675e-06 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2816.04 | 0.0811515 | 8458.92ms | 409725 | 160 | 2.02872e+06 | 138757 | 0.072549 | 1.81563 | 8.74816 | 1.60981 | 0.00470174 | 0.000274147 | 2.91354e-06 | 1(Win) | true |
| simdjson (ondemand) | 2185.75 | 0.171822 | 5271.89ms | 409725 | 1280 | 1.20768e+08 | 178769 | 0.0930927 | 2.31782 | 10.076 | 1.57788 | 0.00757586 | 0.00237251 | 4.27993e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3448.95 | 0.0278603 | 9996.51ms | 676745 | 2560 | 6.95804e+06 | 187128 | 0.030824 | 1.48683 | 6.55275 | 1.15171 | 0.00443681 | 0.000856873 | 3.61969e-06 | 1(Win) | true |
| simdjson (ondemand) | 2979.65 | 0.0562877 | 5708.61ms | 676745 | 320 | 4.75659e+06 | 216600 | 0.0830081 | 1.70274 | 7.10538 | 1.09952 | 0.00644037 | 0.00503417 | 3.50945e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3928.98 | 0.0251759 | 9808.55ms | 676745 | 1280 | 2.18912e+06 | 164265 | 0.180172 | 1.30434 | 5.93439 | 1.00977 | 0.00341981 | 0.000591315 | 3.63181e-06 | 1(Win) | true |
| simdjson (ondemand) | 3380.57 | 0.0909112 | 5585.37ms | 676745 | 160 | 4.81976e+06 | 190913 | 0.097538 | 1.51353 | 6.49019 | 0.956718 | 0.00550282 | 0.00329341 | 3.90657e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1879.65 | 0.0315313 | 5516.6ms | 409725 | 640 | 2.74977e+06 | 207881 | 0.181877 | 2.73195 | 12.84 | 2.46704 | 0.00846379 | 0.000283174 | 6.56309e-06 | 1(Win) | true |
| simdjson (ondemand) | 1465.87 | 0.0827954 | 6990.39ms | 409725 | 160 | 7.79339e+06 | 266561 | 0.114474 | 3.48083 | 15.3706 | 2.62642 | 0.0120128 | 0.00287974 | 1.87626e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2088.04 | 0.0788932 | 5477.34ms | 409725 | 160 | 3.48743e+06 | 187134 | 0.0117382 | 2.44696 | 11.8154 | 2.22986 | 0.00752157 | 0.000213741 | 4.11862e-07 | 1(Win) | true |
| simdjson (ondemand) | 1620.72 | 0.029603 | 6849.63ms | 409725 | 640 | 3.26004e+06 | 241093 | 0.0215852 | 3.16972 | 14.3514 | 2.38847 | 0.0104682 | 0.00257929 | 7.55461e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2703.6 | 0.0278421 | 6313.39ms | 676745 | 1280 | 5.65431e+06 | 238717 | 0.0682885 | 1.89266 | 8.49738 | 1.55396 | 0.00620246 | 0.00133876 | 2.10382e-05 | 1(Win) | true |
| simdjson (ondemand) | 2307.91 | 0.0535078 | 7333.22ms | 676745 | 320 | 7.16465e+06 | 279644 | 0.0194258 | 2.20248 | 9.75036 | 1.60194 | 0.007703 | 0.00499634 | 1.70762e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2991.3 | 0.0514205 | 6207.43ms | 676745 | 320 | 3.9387e+06 | 215757 | 0.0902885 | 1.69618 | 7.87829 | 1.41069 | 0.00512412 | 0.00095172 | 7.42525e-06 | 1(Win) | true |
| simdjson (ondemand) | 2507.09 | 0.0579461 | 7298.54ms | 676745 | 320 | 7.12047e+06 | 257428 | 0.0608137 | 2.0286 | 9.133 | 1.45794 | 0.00683308 | 0.00339553 | 7.24978e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1787.68 | 0.0476542 | 7607.64ms | 264040 | 1280 | 5.76731e+06 | 140858 | 0.00158458 | 2.86274 | 10.392 | 1.96386 | 0.0100046 | 4.86935e-05 | 1.06725e-05 | 1(Win) | true |
| simdjson (ondemand) | 1580.93 | 0.21126 | 8514.16ms | 264040 | 160 | 1.81164e+07 | 159279 | 0.111415 | 3.19021 | 11.2944 | 1.85093 | 0.0122709 | 0.000105287 | 2.06171e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2165.36 | 0.112971 | 7051.82ms | 264040 | 160 | 2.76145e+06 | 116289 | 0.0204058 | 2.33857 | 8.95821 | 1.63349 | 0.00729359 | 4.05715e-05 | 3.25235e-05 | 1(Win) | true |
| simdjson (ondemand) | 1783.25 | 0.276816 | 8416.88ms | 264040 | 30 | 4.58372e+06 | 141207 | 0.0765192 | 2.83727 | 9.86512 | 1.52286 | 0.0140727 | 6.96864e-05 | 3.76206e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2271.9 | 0.149274 | 8181.33ms | 360584 | 80 | 4.0841e+06 | 151362 | 0.309774 | 2.25707 | 8.10978 | 1.45249 | 0.00800618 | 9.92487e-05 | 4.78391e-06 | 1(Win) | true |
| simdjson (ondemand) | 1995.16 | 0.0529953 | 9226.89ms | 360584 | 2560 | 2.13586e+07 | 172357 | 0.15286 | 2.54734 | 8.62101 | 1.37215 | 0.0127421 | 0.00125551 | 1.37873e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2702.31 | 0.102224 | 7601.57ms | 360584 | 160 | 2.70749e+06 | 127254 | 0.0654805 | 1.87446 | 7.05969 | 1.2107 | 0.0057908 | 1.07465e-05 | 1.7853e-06 | 1(Win) | true |
| simdjson (ondemand) | 2361.69 | 0.0427085 | 8697.43ms | 360584 | 2560 | 9.90003e+06 | 145607 | 0.243628 | 2.16848 | 7.57831 | 1.1329 | 0.0106899 | 0.000186147 | 1.47233e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 676.829 | 0.0988893 | 9629.97ms | 264040 | 160 | 2.16571e+07 | 372041 | 0.0857411 | 7.47239 | 28.4742 | 5.30754 | 0.0254246 | 0.000622183 | 2.49962e-05 | 1(Win) | true |
| simdjson (ondemand) | 275.391 | 0.143657 | 5855ms | 264040 | 160 | 2.76064e+08 | 914365 | 0.0175105 | 18.3083 | 72.7168 | 12.735 | 0.0932338 | 0.000204728 | 0.000114542 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 743.923 | 0.12288 | 9247.24ms | 264040 | 80 | 1.384e+07 | 338487 | 0.218184 | 6.92036 | 27.0501 | 4.97757 | 0.0214448 | 8.39835e-05 | 5.96027e-05 | 1(Win) | true |
| simdjson (ondemand) | 284.645 | 0.154902 | 5746.54ms | 264040 | 80 | 1.50224e+08 | 884640 | 0.0925846 | 17.6789 | 71.2958 | 12.4072 | 0.0879522 | 7.15801e-05 | 1.23087e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 870.931 | 0.0712105 | 5115.99ms | 360584 | 320 | 2.52978e+07 | 394842 | 0.0349662 | 5.83843 | 21.7105 | 4.07989 | 0.0184244 | 0.000484388 | 6.35254e-05 | 1(Win) | true |
| simdjson (ondemand) | 387.672 | 0.140763 | 5655.39ms | 360584 | 160 | 2.49449e+08 | 887038 | 0.0806429 | 13.0186 | 52.9005 | 9.20678 | 0.0572644 | 0.000343696 | 7.81718e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 957.051 | 0.0484214 | 9771.03ms | 360584 | 1280 | 3.8746e+07 | 359312 | 0.0153012 | 5.32806 | 20.6653 | 3.83763 | 0.0126075 | 0.00010351 | 3.86092e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.633 | 0.122892 | 5578ms | 360584 | 320 | 3.57836e+08 | 860489 | 0.0428843 | 12.6119 | 51.8599 | 8.96679 | 0.054253 | 0.000342145 | 4.50484e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7008.88 | 0.0534368 | 4338.23ms | 264040 | 2560 | 943545 | 35927 | 0.0949408 | 0.725626 | 3.47071 | 0.476492 | 0.00122066 | 7.88529e-06 | 4.89983e-06 | 1(Win) | true |
| simdjson (ondemand) | 6004.41 | 0.0577133 | 4916.4ms | 264040 | 1280 | 749827 | 41937.2 | 0.0109806 | 0.841527 | 3.88472 | 0.435379 | 0.00144134 | 3.29022e-06 | 1.25159e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7194.57 | 0.0372909 | 4294.99ms | 264040 | 4890 | 833000 | 34999.8 | 0.0791991 | 0.701984 | 3.38811 | 0.457889 | 0.00119552 | 2.03384e-06 | 8.17872e-07 | 1(Win) | true |
| simdjson (ondemand) | 6195.73 | 0.0364567 | 4858.42ms | 264040 | 2560 | 562015 | 40642.2 | 0.0935373 | 0.817014 | 3.80213 | 0.416867 | 0.00144015 | 6.53162e-06 | 4.11869e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7969.13 | 0.0820575 | 5061.89ms | 360584 | 1280 | 1.60486e+06 | 43151.5 | 0.0680369 | 0.639412 | 2.99814 | 0.371775 | 0.000775118 | 1.8828e-06 | 8.3415e-07 | 1(Win) | true |
| simdjson (ondemand) | 7357.03 | 0.054515 | 5404.81ms | 360584 | 1280 | 831094 | 46741.6 | 0.178129 | 0.689234 | 3.19568 | 0.335546 | 0.00103855 | 3.4731e-06 | 1.54697e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8274.78 | 0.0863725 | 5014.8ms | 360584 | 80 | 103072 | 41557.6 | 0.0739991 | 0.622754 | 2.93767 | 0.358152 | 0.000752113 | 1.31731e-06 | 7.27986e-07 | 1(Win) | true |
| simdjson (ondemand) | 7529.62 | 0.0314951 | 5424.03ms | 360584 | 2560 | 529654 | 45670.3 | 0.0902102 | 0.671355 | 3.1352 | 0.32199 | 0.00104077 | 1.88496e-06 | 8.6015e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4979.97 | 0.0304921 | 5792.22ms | 264040 | 2560 | 608554 | 50564.2 | 0.0549759 | 1.02445 | 5.31374 | 0.863506 | 0.00133077 | 5.84369e-06 | 3.5506e-06 | 1(Win) | true |
| simdjson (ondemand) | 3917.58 | 0.0929437 | 7206.03ms | 264040 | 160 | 571037 | 64276.5 | 0.0192856 | 1.30187 | 6.37773 | 0.936307 | 0.00274904 | 3.29022e-06 | 1.91732e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5109.11 | 0.0853916 | 5727.28ms | 264040 | 4890 | 8.66142e+06 | 49286.1 | 0.0767114 | 0.996665 | 5.23537 | 0.846243 | 0.00129128 | 3.92362e-06 | 1.67757e-06 | 1(Win) | true |
| simdjson (ondemand) | 3947.82 | 0.0236048 | 7179.28ms | 264040 | 4890 | 1.1085e+06 | 63784.1 | 0.0322437 | 1.27981 | 6.29934 | 0.919136 | 0.00268416 | 1.06401e-05 | 7.30896e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5892.68 | 0.0663722 | 6566.21ms | 360584 | 4890 | 7.33615e+06 | 58357.1 | 0.244246 | 0.86103 | 4.37902 | 0.664142 | 0.00136016 | 7.47367e-06 | 4.77526e-06 | 1(Win) | true |
| simdjson (ondemand) | 4941.17 | 0.0989772 | 7661.83ms | 360584 | 320 | 1.51836e+06 | 69594.8 | 0.0447705 | 1.02845 | 5.03403 | 0.704717 | 0.00195629 | 8.31984e-07 | 1.38664e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5999.1 | 0.0463926 | 6471.73ms | 360584 | 320 | 226302 | 57321.9 | 0.0176549 | 0.844233 | 4.32163 | 0.651502 | 0.00134159 | 2.01063e-06 | 2.25329e-07 | 1(Win) | true |
| simdjson (ondemand) | 5031.22 | 0.0292387 | 7617.38ms | 360584 | 4890 | 1.95295e+06 | 68349.2 | 0.0479799 | 1.01352 | 4.97662 | 0.692143 | 0.00196254 | 5.15524e-06 | 3.03416e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1857.69 | 0.1177 | 858.132ms | 2632 | 1280 | 3237.36 | 1351.18 | 0.551091 | 2.86655 | 11.1736 | 2.10828 | 0.00111043 | 6.11465e-05 | 1.45445e-05 | 1(Win) | true |
| simdjson (ondemand) | 1585.41 | 0.0611947 | 878.72ms | 2632 | 4890 | 4590.14 | 1583.23 | 0.00997348 | 3.33826 | 12.3047 | 2.15464 | 0.00178742 | 9.23042e-05 | 4.12572e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2391.67 | 0.0901294 | 831.63ms | 2632 | 2560 | 2290.57 | 1049.51 | 0.00628976 | 2.23545 | 9.13564 | 1.64096 | 0.00076344 | 4.31884e-05 | 4.304e-06 | 1(Win) | true |
| simdjson (ondemand) | 1888.97 | 0.0911347 | 860.819ms | 2632 | 1280 | 1877.15 | 1328.8 | 0.0053505 | 2.8092 | 10.4069 | 1.7234 | 0.00283381 | 6.58957e-05 | 1.5435e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2266.97 | 0.0778993 | 863.399ms | 3370 | 320 | 390.287 | 1417.7 | 0.0742291 | 2.34281 | 9.11424 | 1.64955 | 0.000617582 | 4.08012e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1950.8 | 0.0518307 | 887.695ms | 3370 | 2560 | 1866.58 | 1647.47 | 0.0496018 | 2.70389 | 9.89021 | 1.69525 | 0.00314262 | 4.38149e-05 | 1.69232e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2880.89 | 0.0816602 | 840.285ms | 3370 | 160 | 132.785 | 1115.59 | 0 | 1.85357 | 7.52255 | 1.28457 | 0.000602745 | 5.93472e-05 | 1.8546e-06 | 1(Win) | true |
| simdjson (ondemand) | 2392.24 | 0.0482377 | 862.283ms | 3370 | 2560 | 1075.13 | 1343.46 | 0.0480687 | 2.21956 | 8.40861 | 1.35846 | 0.00124073 | 3.74397e-05 | 1.06639e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1267.33 | 0.030277 | 919.156ms | 2632 | 4890 | 1758.44 | 1980.6 | 0.00305431 | 4.14641 | 16.5935 | 3.2538 | 0.00559272 | 7.07044e-05 | 1.39078e-05 | 1(Win) | true |
| simdjson (ondemand) | 722.694 | 0.0714281 | 1068.19ms | 2632 | 320 | 1969.48 | 3473.21 | 0.00521824 | 7.20903 | 30.9183 | 5.91224 | 0.011505 | 4.51178e-05 | 2.37462e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1509.23 | 0.156412 | 896.478ms | 2632 | 640 | 4330.97 | 1663.15 | 0.00826676 | 3.4921 | 14.6516 | 2.80509 | 0.00449812 | 3.79939e-05 | 5.3429e-06 | 1(Win) | true |
| simdjson (ondemand) | 793.885 | 0.0445297 | 1044.32ms | 2632 | 2560 | 5074.53 | 3161.76 | 0.0586997 | 6.56705 | 29.117 | 5.49962 | 0.00925211 | 6.76767e-05 | 1.76612e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.74 | 0.0410737 | 933.699ms | 3370 | 2560 | 2018.18 | 2161.7 | 0.0373734 | 3.5317 | 13.6786 | 2.65697 | 0.00495479 | 4.55536e-05 | 5.21606e-06 | 1(Win) | true |
| simdjson (ondemand) | 920.007 | 0.0404828 | 1070.58ms | 3370 | 1280 | 2559.94 | 3493.32 | 0.00699947 | 5.6617 | 24.1282 | 4.57567 | 0.0102886 | 3.26873e-05 | 9.273e-07 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1759.26 | 0.038096 | 911.991ms | 3370 | 4890 | 2368.48 | 1826.84 | 0.027802 | 2.99207 | 12.162 | 2.30653 | 0.00354517 | 5.30969e-05 | 2.44549e-05 | 1(Win) | true |
| simdjson (ondemand) | 1027.58 | 0.075854 | 1044.54ms | 3370 | 1280 | 7204.37 | 3127.63 | 0.0183879 | 5.12583 | 22.7214 | 4.25341 | 0.00801906 | 6.56065e-05 | 3.176e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.73 | 0.0595776 | 798.609ms | 2632 | 1280 | 289.456 | 798.184 | 0.2332 | 1.72073 | 6.87462 | 1.23708 | 0.000919572 | 3.35415e-05 | 3.2651e-06 | 1(Win) | true |
| simdjson (ondemand) | 2410.81 | 0.0609275 | 822.783ms | 2632 | 4890 | 1967.81 | 1041.17 | 0.0632546 | 2.21769 | 8.24582 | 1.35372 | 0.00325341 | 4.62298e-05 | 1.52286e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3951.93 | 0.118243 | 782.732ms | 2632 | 320 | 180.492 | 635.15 | 0.0403285 | 1.38519 | 5.80775 | 0.984043 | 0.000769377 | 5.69909e-05 | 2.37462e-06 | 1(Win) | true |
| simdjson (ondemand) | 3003.69 | 0.105565 | 801.637ms | 2632 | 1280 | 996.127 | 835.663 | 0.0228995 | 1.795 | 7.17895 | 1.10068 | 0.000382611 | 3.56193e-05 | 5.63972e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3684.98 | 0.0653026 | 805.086ms | 3370 | 4890 | 1586.21 | 872.158 | 0.0664488 | 1.45944 | 5.77745 | 0.982196 | 0.000710892 | 4.8121e-05 | 1.45637e-05 | 1(Win) | true |
| simdjson (ondemand) | 3058.41 | 0.100697 | 823.441ms | 3370 | 320 | 358.302 | 1050.83 | 0.0811196 | 1.74713 | 6.50564 | 1.02967 | 0.00264188 | 2.96736e-05 | 7.4184e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4575 | 0.0761393 | 789.203ms | 3370 | 2560 | 732.378 | 702.488 | 0.21811 | 1.1879 | 4.94421 | 0.78457 | 0.000600658 | 5.55221e-05 | 2.02847e-05 | 1(Win) | true |
| simdjson (ondemand) | 3760.91 | 0.0472325 | 804.567ms | 3370 | 4890 | 796.646 | 854.55 | 0.213553 | 1.43333 | 5.6724 | 0.832048 | 0.000744631 | 5.00628e-05 | 1.34714e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2351.76 | 0.0694082 | 824.642ms | 2632 | 1280 | 702.452 | 1067.32 | 0.200377 | 2.27862 | 9.46392 | 1.7747 | 0.00187031 | 5.93655e-05 | 1.42477e-05 | 1(Win) | true |
| simdjson (ondemand) | 1995.13 | 0.225474 | 843.681ms | 2632 | 30 | 241.403 | 1258.1 | 0.0132492 | 2.66554 | 10.1505 | 1.7196 | 0.00398936 | 7.59878e-05 | 1.26646e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2843.19 | 0.0698569 | 805.586ms | 2632 | 2560 | 973.686 | 882.837 | 0.00805352 | 1.88934 | 8.40008 | 1.52432 | 0.00114071 | 6.53021e-05 | 1.70676e-05 | 1(Win) | true |
| simdjson (ondemand) | 2405.02 | 0.0224902 | 845.235ms | 2632 | 4890 | 269.42 | 1043.68 | 0.451947 | 2.22366 | 9.08663 | 1.46923 | 0.00129545 | 4.14903e-05 | 4.27334e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2765.47 | 0.0716848 | 833.331ms | 3370 | 2560 | 1776.71 | 1162.15 | 0.131218 | 1.92059 | 7.87389 | 1.42018 | 0.00130471 | 4.86832e-05 | 1.78505e-05 | 1(Win) | true |
| simdjson (ondemand) | 2534.81 | 0.0456766 | 840.976ms | 3370 | 4890 | 1640.08 | 1267.9 | 0.205384 | 2.09406 | 7.98368 | 1.31543 | 0.00339644 | 3.50136e-05 | 4.91526e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3249.22 | 0.0688955 | 818.326ms | 3370 | 320 | 148.605 | 989.125 | 0.17914 | 1.64854 | 7.04303 | 1.22463 | 0.00116469 | 1.57641e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3045.22 | 0.0898377 | 824.141ms | 3370 | 320 | 287.668 | 1055.39 | 0.0088822 | 1.75609 | 7.15282 | 1.11988 | 0.00104507 | 3.43101e-05 | 6.4911e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.903 | 0.122917 | 1298.07ms | 4630 | 160 | 8055.46 | 5772.64 | 0.111967 | 6.77624 | 33.1447 | 6.40151 | 0.00485016 | 4.58963e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 747.46 | 0.0382781 | 1315.38ms | 4630 | 2560 | 13089.7 | 5907.36 | 0.443282 | 6.86634 | 32.9512 | 5.79957 | 0.00349335 | 6.277e-05 | 2.36231e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.703 | 0.040148 | 1319.5ms | 4630 | 1280 | 5058.94 | 4951.78 | 0.0144855 | 5.82268 | 29.2235 | 5.47257 | 0.00374494 | 4.23529e-05 | 5.39957e-06 | 1(Win) | true |
| simdjson (ondemand) | 885.431 | 0.0965726 | 1320.86ms | 4630 | 640 | 14843.7 | 4986.85 | 0.00372842 | 5.85833 | 28.4724 | 4.76177 | 0.00237379 | 4.55589e-05 | 6.41199e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1805.19 | 0.0252962 | 1345.55ms | 11579 | 4890 | 11708.9 | 6117.14 | 0.0268917 | 2.83243 | 13.5809 | 2.31298 | 0.00196883 | 1.835e-05 | 5.45731e-06 | 1(Win) | true |
| Jsonifier (generic) | 1729.6 | 0.0783572 | 1375.46ms | 11579 | 640 | 16017.3 | 6384.49 | 0.0340064 | 2.9545 | 13.9007 | 2.59811 | 0.00261519 | 2.1051e-05 | 2.15908e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2124.52 | 0.0328662 | 1348.15ms | 11579 | 2560 | 7470.67 | 5197.69 | 0.1996 | 2.40769 | 11.6789 | 1.8683 | 0.00133209 | 2.44246e-05 | 7.21943e-06 | 1(Win) | true |
| Jsonifier (generic) | 2026.42 | 0.0237083 | 1375.01ms | 11579 | 4890 | 8161.95 | 5449.31 | 0.0139989 | 2.52146 | 11.9963 | 2.15235 | 0.00187693 | 2.21118e-05 | 6.04013e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 715.298 | 0.0508107 | 1340.76ms | 4630 | 320 | 3148.1 | 6172.97 | 0.0837514 | 7.24869 | 36.4618 | 7.09374 | 0.00552916 | 3.57721e-05 | 4.04968e-06 | 1(Win) | true |
| simdjson (ondemand) | 680.515 | 0.0229876 | 1373.84ms | 4630 | 4890 | 10878.8 | 6488.48 | 0.0730479 | 7.6105 | 37.4309 | 6.78726 | 0.00410323 | 9.65518e-05 | 3.74105e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.074 | 0.0901471 | 1362.08ms | 4630 | 80 | 1917.32 | 5430.64 | 0.0195688 | 6.39225 | 32.5683 | 6.17084 | 0.00394708 | 0.000156587 | 2.15983e-05 | 1(Win) | true |
| simdjson (ondemand) | 779.615 | 0.0344543 | 1383.78ms | 4630 | 4890 | 18620.8 | 5663.71 | 0.0704251 | 6.65241 | 33.0344 | 5.76653 | 0.00267766 | 5.9318e-05 | 1.24554e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1588.16 | 0.0260745 | 1420.35ms | 11579 | 4890 | 16072.9 | 6953.08 | 0.0336981 | 3.25936 | 15.5597 | 2.91951 | 0.00259915 | 9.33218e-05 | 5.54738e-05 | 1(Win) | true |
| simdjson (ondemand) | 1586.6 | 0.0312262 | 1422.15ms | 11579 | 4890 | 23096.9 | 6959.91 | 0.054133 | 3.24503 | 15.6882 | 2.7473 | 0.00168553 | 3.48985e-05 | 1.17447e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1899.13 | 0.0249313 | 1413.67ms | 11579 | 4890 | 10276.2 | 5814.56 | 0.113222 | 2.69007 | 13.5361 | 2.2774 | 0.000972266 | 1.32812e-05 | 1.23628e-06 | 1(Win) | true |
| Jsonifier (generic) | 1893.68 | 0.118143 | 1409.91ms | 11579 | 160 | 7593.91 | 5831.27 | 0.127278 | 2.7218 | 13.3912 | 2.44512 | 0.00106389 | 1.8892e-05 | 3.77839e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7480.43 | 0.0582516 | 772.891ms | 4630 | 4890 | 578.141 | 590.275 | 0.084261 | 0.735803 | 3.63391 | 0.469978 | 0.000432407 | 2.22166e-05 | 7.3761e-06 | 1(Win) | true |
| simdjson (ondemand) | 6612.35 | 0.0572147 | 780.25ms | 4630 | 4890 | 713.797 | 667.767 | 0.0375272 | 0.823917 | 4.10194 | 0.491577 | 0.00043254 | 1.38247e-05 | 9.27533e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7678.7 | 0.0779527 | 769.879ms | 4630 | 2560 | 514.386 | 575.034 | 0.0942408 | 0.718273 | 3.59698 | 0.461987 | 0.000432556 | 1.82235e-05 | 4.80899e-06 | 1(Win) | true |
| simdjson (ondemand) | 6751.57 | 0.0560572 | 774.604ms | 4630 | 4890 | 657.24 | 653.998 | 0.0263162 | 0.808052 | 4.06501 | 0.483586 | 0.000432628 | 1.16162e-05 | 2.65009e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12713.6 | 0.0433088 | 801.101ms | 11579 | 320 | 45.2805 | 868.569 | 0.0280713 | 0.424059 | 2.10459 | 0.210899 | 0.000172726 | 6.47724e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11108.3 | 0.129458 | 814.66ms | 11579 | 1280 | 2119.88 | 994.083 | 0.128879 | 0.483033 | 2.36808 | 0.23154 | 0.000173266 | 7.89414e-06 | 8.09655e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12908.2 | 0.0659777 | 800.848ms | 11579 | 2560 | 815.535 | 855.469 | 0.00620966 | 0.417676 | 2.08982 | 0.207704 | 0.000173367 | 3.64345e-06 | 3.03621e-07 | 1(Win) | true |
| simdjson (ondemand) | 11242.4 | 0.0708387 | 813.208ms | 11579 | 160 | 77.4619 | 982.231 | 0.0883684 | 0.477289 | 2.35331 | 0.228344 | 0.000172726 | 7.01701e-06 | 4.85793e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5058.09 | 0.123169 | 801.204ms | 4630 | 2560 | 2959.61 | 872.961 | 0.370532 | 1.06482 | 5.1527 | 0.805184 | 0.000648201 | 2.51417e-05 | 1.07148e-05 | 1(Win) | true |
| simdjson (ondemand) | 4516.78 | 0.197063 | 811.641ms | 4630 | 640 | 2375.18 | 977.58 | 0.0263795 | 1.18717 | 5.58726 | 0.818575 | 0.000647948 | 1.45113e-05 | 6.74946e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5484.8 | 0.170293 | 795.947ms | 4630 | 640 | 1202.86 | 805.045 | 0.186945 | 0.986199 | 5.11577 | 0.797192 | 0.000647948 | 8.7743e-06 | 2.02484e-06 | 1(Win) | true |
| simdjson (ondemand) | 4550.05 | 0.127988 | 810.283ms | 4630 | 160 | 246.825 | 970.431 | 0.119006 | 1.17871 | 5.55032 | 0.810583 | 0.000647948 | 1.61987e-05 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10241.3 | 0.0416136 | 821.653ms | 11579 | 4890 | 984.498 | 1078.25 | 0.0395354 | 0.521589 | 2.71137 | 0.345367 | 0.000259425 | 8.56568e-06 | 1.30693e-06 | 1(Win) | true |
| simdjson (ondemand) | 8491.68 | 0.0592805 | 845.916ms | 11579 | 2560 | 1521.31 | 1300.4 | 0.0184773 | 0.625172 | 2.962 | 0.362294 | 0.000295221 | 9.58092e-06 | 3.13741e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10408.6 | 0.0389028 | 820.159ms | 11579 | 320 | 54.509 | 1060.91 | 0.147356 | 0.516044 | 2.69661 | 0.342171 | 0.000309828 | 4.58805e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 8500.76 | 0.137807 | 847.521ms | 11579 | 80 | 256.367 | 1299.01 | 0.025988 | 0.624612 | 2.94723 | 0.359098 | 0.00025909 | 6.47724e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.82 | 0.0370675 | 1149.91ms | 5092 | 4890 | 11819.2 | 4194.17 | 0.095088 | 4.46363 | 18.4561 | 3.51458 | 0.00301564 | 5.06027e-05 | 2.06828e-05 | 1(Win) | true |
| simdjson (ondemand) | 1136.8 | 0.0387349 | 1154.74ms | 5092 | 4890 | 13388.2 | 4271.74 | 0.102847 | 4.53359 | 18.4456 | 3.09412 | 0.00350901 | 6.93176e-05 | 3.05624e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1296.04 | 0.0342711 | 1155.47ms | 5092 | 4890 | 8063.14 | 3746.88 | 0.105721 | 4.01644 | 16.9538 | 3.13537 | 0.00337773 | 4.63456e-05 | 1.41366e-05 | 1(Win) | true |
| simdjson (ondemand) | 1277.57 | 0.0543271 | 1141.16ms | 5092 | 640 | 2729.11 | 3801.06 | 0.0222027 | 4.08095 | 17.0939 | 2.74897 | 0.00338889 | 2.88443e-05 | 5.83022e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2068.31 | 0.152444 | 1180.38ms | 9739 | 320 | 14995.7 | 4490.54 | 0.331264 | 2.50877 | 10.279 | 1.65335 | 0.00181198 | 1.5402e-05 | 1.92525e-06 | 1(Win) | true |
| Jsonifier (generic) | 2040.84 | 0.140507 | 1183.03ms | 9739 | 320 | 13084.5 | 4550.98 | 0.145303 | 2.54302 | 10.2771 | 1.84824 | 0.00165732 | 4.20346e-05 | 2.21404e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2273.89 | 0.0443905 | 1175.45ms | 9739 | 4890 | 16076.1 | 4084.56 | 0.0156807 | 2.26606 | 9.52736 | 1.66188 | 0.00120289 | 4.31508e-05 | 1.82472e-05 | 1(Win) | true |
| simdjson (ondemand) | 2260.15 | 0.0429753 | 1176.12ms | 9739 | 4890 | 15251.1 | 4109.38 | 0.0512811 | 2.28288 | 9.54782 | 1.4721 | 0.0021756 | 4.01481e-05 | 1.92551e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 697.674 | 0.0327405 | 1423.36ms | 5092 | 2560 | 13294.9 | 6960.43 | 0.0319542 | 7.4187 | 32.7159 | 6.65278 | 0.00582884 | 4.27294e-05 | 1.21207e-05 | 1(Win) | true |
| simdjson (ondemand) | 438.032 | 0.02228 | 1860.01ms | 5092 | 2560 | 15618.3 | 11086.2 | 0.0384833 | 11.7938 | 56.1612 | 10.9546 | 0.0138356 | 5.50803e-05 | 1.98688e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 762.23 | 0.0280133 | 1409.55ms | 5092 | 2560 | 8154.06 | 6370.93 | 0.118131 | 6.79459 | 30.7901 | 6.19917 | 0.0058461 | 5.7842e-05 | 1.23509e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.818 | 0.0218087 | 1832.15ms | 5092 | 2560 | 13639.4 | 10583.9 | 0.00358014 | 11.2664 | 54.4747 | 10.5479 | 0.0138815 | 6.80448e-05 | 2.19401e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.81 | 0.0525345 | 1494.45ms | 9739 | 1280 | 20889.6 | 7689.81 | 0.0752474 | 4.28341 | 18.2647 | 3.59601 | 0.00350933 | 0.000110862 | 5.95223e-05 | 1(Win) | true |
| simdjson (ondemand) | 836.014 | 0.0720407 | 1839.53ms | 9739 | 320 | 20497.8 | 11109.7 | 0.0267151 | 6.17973 | 29.7724 | 5.72287 | 0.0072415 | 2.8237e-05 | 1.60437e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.97 | 0.0172713 | 1473.54ms | 9739 | 4890 | 7254.96 | 7052.41 | 0.00887759 | 3.93381 | 17.1964 | 3.34625 | 0.00317313 | 2.77383e-05 | 8.77714e-06 | 1(Win) | true |
| simdjson (ondemand) | 873.203 | 0.0399531 | 1829.96ms | 9739 | 1280 | 23115.9 | 10636.5 | 0.0645011 | 5.91773 | 28.9677 | 5.52511 | 0.00699283 | 2.00547e-05 | 2.80765e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4734.1 | 0.0400829 | 813.714ms | 5092 | 4890 | 826.665 | 1025.77 | 0.245894 | 1.13053 | 4.97604 | 0.690888 | 0.00115852 | 1.75904e-05 | 1.76708e-06 | 1(Win) | true |
| simdjson (ondemand) | 4641.05 | 0.049292 | 817.62ms | 5092 | 4890 | 1300.79 | 1046.34 | 0.0254368 | 1.15101 | 5.29478 | 0.663787 | 0.000940527 | 1.22491e-05 | 2.53013e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4917.13 | 0.066393 | 810.592ms | 5092 | 320 | 137.578 | 987.591 | 0.0611077 | 1.0903 | 4.8533 | 0.664768 | 0.00143546 | 1.35016e-05 | 6.13708e-07 | 1(Win) | true |
| simdjson (ondemand) | 4748.64 | 0.0695175 | 830.497ms | 5092 | 1280 | 646.899 | 1022.63 | 0.0324024 | 1.12619 | 5.17262 | 0.638256 | 0.00107322 | 9.35904e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7470.13 | 0.0304621 | 839.084ms | 9739 | 4890 | 701.457 | 1243.33 | 0.00779231 | 0.711996 | 3.2068 | 0.390492 | 0.000571501 | 7.70625e-06 | 3.14969e-07 | 1(Win) | true |
| simdjson (ondemand) | 7429.73 | 0.0327625 | 836.521ms | 9739 | 4890 | 820.251 | 1250.09 | 0.0889913 | 0.715532 | 3.3486 | 0.373961 | 0.00032003 | 1.39846e-05 | 3.92662e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7764.13 | 0.0420821 | 833.65ms | 9739 | 4890 | 1239.21 | 1196.25 | 0.0251866 | 0.685665 | 3.14262 | 0.376835 | 0.000453031 | 8.73514e-06 | 3.98961e-07 | 1(Win) | true |
| simdjson (ondemand) | 7531.57 | 0.127083 | 836.403ms | 9739 | 80 | 196.483 | 1233.19 | 0.118455 | 0.706478 | 3.28473 | 0.360612 | 0.000521101 | 7.701e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3106.47 | 0.0404789 | 871.039ms | 5092 | 320 | 128.129 | 1563.22 | 0.0633306 | 1.70166 | 7.92812 | 1.37667 | 0.00255609 | 2.39346e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2961.13 | 0.0355565 | 878.745ms | 5092 | 4890 | 1662.69 | 1639.95 | 0.0280844 | 1.78088 | 8.3315 | 1.30656 | 0.00246696 | 2.10443e-05 | 3.37351e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3196.01 | 0.066773 | 868.433ms | 5092 | 640 | 658.78 | 1519.43 | 0.0609439 | 1.65453 | 7.80538 | 1.35055 | 0.00225875 | 1.2581e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3034.97 | 0.0504326 | 873.604ms | 5092 | 160 | 104.186 | 1600.05 | 0.0781836 | 1.73961 | 8.20935 | 1.28103 | 0.00237014 | 1.71838e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5087.39 | 0.0712259 | 902.643ms | 9739 | 160 | 270.541 | 1825.66 | 0.00513488 | 1.0353 | 4.80593 | 0.756135 | 0.00156715 | 1.21932e-05 | 1.2835e-06 | 1(Win) | true |
| simdjson (ondemand) | 5051.27 | 0.0344103 | 916.759ms | 9739 | 4890 | 1957.54 | 1838.71 | 0.0199702 | 1.04114 | 4.93613 | 0.710032 | 0.00100127 | 1.55175e-05 | 3.00271e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5189.48 | 0.0494251 | 896.794ms | 9739 | 160 | 125.198 | 1789.74 | 0.0108244 | 1.01478 | 4.74176 | 0.742479 | 0.00139773 | 8.9845e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5139.01 | 0.0460201 | 897.433ms | 9739 | 160 | 110.684 | 1807.32 | 0.0197154 | 1.02518 | 4.87227 | 0.696683 | 0.00118082 | 1.0268e-05 | 0 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1419 | 0.0250049 | 1054.17ms | 4857 | 4890 | 3257.84 | 3264.27 | 0.094966 | 3.67286 | 14.5713 | 2.86236 | 0.00190049 | 5.34299e-05 | 1.39785e-05 | 1(Win) | true |
| simdjson (ondemand) | 1330.81 | 0.0334122 | 1072.09ms | 4857 | 2560 | 3462.2 | 3480.57 | 0.00415269 | 3.91177 | 15.5164 | 2.61952 | 0.00182742 | 3.30547e-05 | 2.89531e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1869.12 | 0.0315658 | 996.273ms | 4857 | 2560 | 1566.53 | 2478.17 | 0.0120254 | 2.80144 | 11.5985 | 2.21083 | 0.00218821 | 2.72641e-05 | 1.68893e-06 | 1(Win) | true |
| simdjson (ondemand) | 1601.42 | 0.0295162 | 1034.94ms | 4857 | 4890 | 3564.13 | 2892.42 | 0.0580448 | 3.26041 | 13.2351 | 2.12539 | 0.00143916 | 3.6041e-05 | 7.70503e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1855.02 | 0.0763514 | 1073.06ms | 6701 | 160 | 1106.97 | 3445.01 | 0.0595417 | 2.81096 | 11.1013 | 2.08566 | 0.00153895 | 3.54425e-05 | 1.02597e-05 | 1(Win) | true |
| simdjson (ondemand) | 1807.62 | 0.0433199 | 1079.16ms | 6701 | 2560 | 6004.52 | 3535.34 | 0.0331805 | 2.87822 | 11.6602 | 1.92344 | 0.000876268 | 3.27027e-05 | 3.90567e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.52 | 0.126243 | 1020.59ms | 6701 | 640 | 7271.11 | 2669.94 | 0.0984721 | 2.17376 | 8.96687 | 1.61752 | 0.00143099 | 2.96131e-05 | 1.0726e-05 | 1(Win) | true |
| simdjson (ondemand) | 2193.94 | 0.111552 | 1054.36ms | 6701 | 320 | 3378.58 | 2912.83 | 0.0716097 | 2.37675 | 9.97314 | 1.55798 | 0.000705119 | 2.70482e-05 | 0 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 717.385 | 0.0388405 | 1372.65ms | 4857 | 2560 | 16100.6 | 6456.77 | 0.0606805 | 7.20229 | 31.0804 | 6.14114 | 0.00752586 | 0.000122568 | 6.18469e-05 | 1(Win) | true |
| simdjson (ondemand) | 220.705 | 0.03803 | 2829.43ms | 4857 | 1280 | 81540.3 | 20987.2 | 0.0163184 | 23.3141 | 115.9 | 22.3562 | 0.0439289 | 6.03189e-05 | 1.49591e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 829.443 | 0.0474572 | 1307.1ms | 4857 | 320 | 2247.59 | 5584.47 | 0.0715201 | 6.25491 | 28.0819 | 5.48713 | 0.00624228 | 3.15267e-05 | 2.57361e-06 | 1(Win) | true |
| simdjson (ondemand) | 227.471 | 0.0281934 | 2790.99ms | 4857 | 2560 | 84376.3 | 20363 | 0.0324586 | 22.5438 | 113.57 | 21.8549 | 0.0436068 | 8.20337e-05 | 2.38058e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.911 | 0.0185483 | 1448.49ms | 6701 | 4890 | 8754.22 | 7213.56 | 0.0127678 | 5.83005 | 23.6004 | 4.72892 | 0.00619469 | 3.88185e-05 | 1.30921e-05 | 1(Win) | true |
| simdjson (ondemand) | 298.859 | 0.0218055 | 2888.91ms | 6701 | 2560 | 55657 | 21383.3 | 0.0460798 | 17.2592 | 84.0992 | 16.1588 | 0.0328394 | 9.85744e-05 | 5.33969e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1007.83 | 0.0402481 | 1388.47ms | 6701 | 1280 | 8336.87 | 6340.9 | 0.00576647 | 5.14076 | 21.4255 | 4.25474 | 0.00530669 | 3.49761e-05 | 6.64546e-06 | 1(Win) | true |
| simdjson (ondemand) | 314.702 | 0.0476071 | 2785.95ms | 6701 | 320 | 29907 | 20306.7 | 0.0716459 | 16.3992 | 82.391 | 15.7912 | 0.0320465 | 3.2178e-05 | 4.66348e-07 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4013.79 | 0.0934021 | 835.09ms | 4857 | 1280 | 1487.14 | 1154.02 | 0.0314697 | 1.32716 | 5.54561 | 0.890057 | 0.000848485 | 2.28407e-05 | 1.12595e-06 | 1(Win) | true |
| simdjson (ondemand) | 3587.58 | 0.0908685 | 853.506ms | 4857 | 320 | 440.462 | 1291.12 | 0.115561 | 1.48152 | 6.03212 | 0.836319 | 0.000314623 | 3.34569e-05 | 1.2868e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4681.31 | 0.0956046 | 830.025ms | 4857 | 4890 | 4375.9 | 989.465 | 0.00278246 | 1.12869 | 4.95882 | 0.756434 | 0.000574803 | 2.73255e-05 | 1.26733e-05 | 1(Win) | true |
| simdjson (ondemand) | 3939.57 | 0.0751818 | 866.034ms | 4857 | 4890 | 3820.97 | 1175.76 | 0.160375 | 1.34886 | 5.4616 | 0.707433 | 0.00104207 | 5.41878e-05 | 2.20204e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4936.9 | 0.162753 | 851.188ms | 6701 | 40 | 177.536 | 1294.45 | 0.109561 | 1.07578 | 4.51157 | 0.672885 | 0.000156693 | 1.11924e-05 | 1.11924e-05 | 1(Win) | true |
| simdjson (ondemand) | 4605.41 | 0.100029 | 854.256ms | 6701 | 320 | 616.518 | 1387.62 | 0.0250041 | 1.1514 | 4.74989 | 0.623787 | 0.000366083 | 4.0106e-05 | 2.1452e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5622.84 | 0.0435679 | 836.579ms | 6701 | 2560 | 627.685 | 1136.54 | 0.0932611 | 0.948548 | 4.08626 | 0.576034 | 0.000738929 | 2.40752e-05 | 6.58717e-06 | 1(Win) | true |
| simdjson (ondemand) | 5238.82 | 0.0453425 | 844.251ms | 6701 | 4890 | 1496 | 1219.85 | 0.0592802 | 1.01519 | 4.33637 | 0.530369 | 0.000294068 | 1.20545e-05 | 1.86158e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3043.36 | 0.117405 | 875.838ms | 4857 | 80 | 255.443 | 1522 | 0.0542344 | 1.73613 | 7.53675 | 1.3218 | 0.000509574 | 7.72082e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2186.49 | 0.0528314 | 949.54ms | 4857 | 2560 | 3206.76 | 2118.46 | 0.165339 | 2.39797 | 10.6848 | 1.65905 | 0.00143438 | 2.19561e-05 | 4.18211e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3340.54 | 0.0879858 | 865.017ms | 4857 | 320 | 476.297 | 1386.6 | 0.17429 | 1.58611 | 6.96644 | 1.19518 | 0.00146374 | 1.22246e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 2390.36 | 0.134629 | 910.893ms | 4857 | 320 | 2177.87 | 1937.78 | 0.160072 | 2.20728 | 10.1316 | 1.53799 | 0.00178673 | 8.36422e-06 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3848.43 | 0.0402097 | 878.53ms | 6701 | 4890 | 2180.13 | 1660.57 | 0.188834 | 1.38353 | 6.08685 | 1.01224 | 0.00037906 | 1.45875e-05 | 2.19727e-06 | 1(Win) | true |
| simdjson (ondemand) | 3010.91 | 0.139574 | 945.372ms | 6701 | 160 | 1404.15 | 2122.47 | 0.183998 | 1.77563 | 8.03701 | 1.20415 | 0.000935495 | 2.42501e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4247.27 | 0.0492256 | 870.632ms | 6701 | 1280 | 702.185 | 1504.63 | 0.0347486 | 1.26736 | 5.67348 | 0.92046 | 0.00076726 | 4.09221e-05 | 2.09857e-05 | 1(Win) | true |
| simdjson (ondemand) | 3156.7 | 0.0414574 | 922.494ms | 6701 | 4890 | 3444.49 | 2024.44 | 0.0116389 | 1.66754 | 7.63602 | 1.1164 | 0.00141138 | 2.03553e-05 | 1.95313e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1265.2 | 0.0564333 | 843.231ms | 1691 | 4890 | 2530.16 | 1274.63 | 0.155169 | 4.20596 | 14.9072 | 2.93081 | 0.00116387 | 0.000345991 | 0.000142702 | 1(Win) | true |
| simdjson (ondemand) | 1176.68 | 0.0376435 | 854.139ms | 1691 | 4890 | 1301.54 | 1370.52 | 0.0123555 | 4.51072 | 16.9119 | 2.93554 | 0.000982466 | 9.33609e-05 | 6.89322e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1470.15 | 0.0503886 | 835.509ms | 1691 | 2560 | 782.113 | 1096.94 | 0.0146337 | 3.63348 | 13.2448 | 2.52513 | 0.00111181 | 0.00010834 | 1.50152e-05 | 1(Win) | true |
| simdjson (ondemand) | 1362.97 | 0.292083 | 844.52ms | 1691 | 30 | 358.303 | 1183.2 | 0.152362 | 3.98894 | 15.2496 | 2.52986 | 0.00114331 | 0.000216834 | 5.91366e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1507.52 | 0.0534865 | 853.31ms | 2158 | 2560 | 1364.92 | 1365.18 | 0.05176 | 3.51602 | 12.3809 | 2.39296 | 0.000480588 | 8.16366e-05 | 1.21278e-05 | 1(Win) | true |
| simdjson (ondemand) | 1474 | 0.0398323 | 856.145ms | 2158 | 2560 | 791.804 | 1396.22 | 0.0302344 | 3.59536 | 13.4666 | 2.30538 | 0.000477692 | 0.000113857 | 4.07278e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1750.41 | 0.0320444 | 846.105ms | 2158 | 4890 | 694.127 | 1175.74 | 0.0223513 | 3.06959 | 11.0783 | 2.07507 | 0.000465572 | 0.000119212 | 4.86135e-05 | 1(Win) | true |
| simdjson (ondemand) | 1686.44 | 0.0466192 | 845.759ms | 2158 | 4890 | 1582.71 | 1220.34 | 0.211095 | 3.17884 | 12.164 | 1.98749 | 0.000483766 | 9.44789e-05 | 3.11771e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 940.853 | 0.0390196 | 890.148ms | 1691 | 320 | 143.139 | 1714.04 | 0.181918 | 5.60151 | 20.6487 | 4.16026 | 0.00119012 | 0.000112729 | 5.54406e-06 | 1(Win) | true |
| simdjson (ondemand) | 684.15 | 0.142565 | 962.338ms | 1691 | 320 | 3613.75 | 2357.18 | 0.200975 | 7.65328 | 30.2543 | 5.42697 | 0.00184432 | 0.000114577 | 3.14163e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1060.12 | 0.144421 | 880.502ms | 1691 | 640 | 3089 | 1521.21 | 0.0960483 | 4.98273 | 19.0278 | 3.7605 | 0.00124556 | 0.000114577 | 2.67963e-05 | 1(Win) | true |
| simdjson (ondemand) | 742.002 | 0.168515 | 944.164ms | 1691 | 320 | 4292.43 | 2173.39 | 0.241276 | 7.0649 | 28.6334 | 5.0272 | 0.00186465 | 0.000120121 | 4.80485e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1061.39 | 0.0291324 | 912.066ms | 2158 | 4890 | 1560.33 | 1939 | 0.0346491 | 4.95625 | 17.3916 | 3.51946 | 0.00252951 | 0.000111252 | 2.90923e-05 | 1(Win) | true |
| simdjson (ondemand) | 870.487 | 0.0483863 | 959.745ms | 2158 | 2560 | 3350.15 | 2364.23 | 0.0667551 | 6.01698 | 23.7845 | 4.22799 | 0.0017875 | 7.45772e-05 | 1.53861e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1171.56 | 0.0466594 | 904.26ms | 2158 | 2560 | 1719.86 | 1756.66 | 0.0377946 | 4.49509 | 16.1214 | 3.20621 | 0.00266975 | 0.000100824 | 1.82823e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.048 | 0.0454399 | 947.344ms | 2158 | 1280 | 1250.72 | 2175.4 | 0.144615 | 5.54755 | 22.5144 | 3.91474 | 0.00166604 | 8.07316e-05 | 1.23089e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4507.02 | 0.0670422 | 746.052ms | 1691 | 1280 | 73.6573 | 357.812 | 0.407991 | 1.27555 | 4.57363 | 0.735068 | 0.000638029 | 2.40242e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4148.26 | 0.111863 | 750.211ms | 1691 | 320 | 60.5172 | 388.756 | 0.0337729 | 1.3711 | 5.10171 | 0.713187 | 0.000591366 | 4.80485e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5113.83 | 0.0787693 | 741.238ms | 1691 | 640 | 39.4901 | 315.353 | 0.136939 | 1.14062 | 4.22413 | 0.656416 | 0.00061539 | 1.20121e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4553.4 | 0.0403511 | 751.062ms | 1691 | 2560 | 52.2839 | 354.167 | 0.13098 | 1.25824 | 4.7534 | 0.635719 | 0.000591597 | 3.85774e-05 | 1.38601e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5133.92 | 0.0470401 | 753.781ms | 2158 | 4890 | 173.88 | 400.869 | 0.0283549 | 1.10062 | 3.98424 | 0.592679 | 0.000465856 | 2.03741e-05 | 1.89526e-06 | 1(Win) | true |
| simdjson (ondemand) | 5015.9 | 0.0479757 | 754.303ms | 2158 | 2560 | 99.1945 | 410.301 | 0.0176159 | 1.12679 | 4.2507 | 0.57368 | 0.000472081 | 3.90987e-05 | 1.4843e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5596.18 | 0.0989187 | 750.624ms | 2158 | 640 | 84.6948 | 367.756 | 0.0722808 | 1.02125 | 3.71038 | 0.531047 | 0.00046484 | 3.98228e-05 | 5.7924e-06 | 1(Win) | true |
| simdjson (ondemand) | 5347.42 | 0.0653825 | 754.957ms | 2158 | 640 | 40.5245 | 384.864 | 0.0450849 | 1.06397 | 3.97776 | 0.512975 | 0.000480045 | 2.67899e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3322.94 | 0.157864 | 762.439ms | 1691 | 160 | 93.9143 | 485.312 | 0.0180264 | 1.7063 | 6.86339 | 1.21644 | 0.000683767 | 2.21762e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2592.6 | 0.280254 | 779.858ms | 1691 | 80 | 243.113 | 622.025 | 0.144898 | 2.15107 | 8.66588 | 1.4317 | 0.00100532 | 1.47842e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3395.8 | 0.203542 | 761.344ms | 1691 | 40 | 37.3744 | 474.9 | 0.0210615 | 1.6465 | 6.5139 | 1.13779 | 0.0017741 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2664.73 | 0.0940185 | 777.825ms | 1691 | 4890 | 1583.13 | 605.188 | 0.508461 | 2.05165 | 8.31756 | 1.35423 | 0.00152497 | 3.12009e-05 | 4.95828e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3644.4 | 0.0402175 | 770.693ms | 2158 | 2560 | 132.045 | 564.71 | 0.0388599 | 1.51434 | 5.79564 | 0.988415 | 0.000865783 | 4.01848e-05 | 9.59366e-06 | 1(Win) | true |
| simdjson (ondemand) | 3187.43 | 0.106543 | 792.339ms | 2158 | 640 | 302.869 | 645.67 | 0.293164 | 1.74692 | 7.04032 | 1.13531 | 0.000729842 | 4.19949e-05 | 2.31696e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3928.54 | 0.472101 | 770.893ms | 2158 | 30 | 183.499 | 523.867 | 0.00636335 | 1.40799 | 5.52178 | 0.926784 | 0.00105036 | 3.08928e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3284.37 | 0.112913 | 777.531ms | 2158 | 2560 | 1281.52 | 626.614 | 0.0186429 | 1.66856 | 6.76738 | 1.07461 | 0.00109386 | 2.24456e-05 | 3.25823e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1291.65 | 0.0250205 | 1046.07ms | 4390 | 4890 | 3216.21 | 3241.32 | 0.230669 | 4.03628 | 18.0189 | 3.50228 | 0.00231284 | 6.82905e-05 | 2.0776e-05 | 1(Win) | true |
| simdjson (ondemand) | 1059.33 | 0.039373 | 1137.38ms | 4390 | 2560 | 6198.8 | 3952.16 | 0.0640654 | 4.90895 | 20.5497 | 3.56173 | 0.00263374 | 4.27107e-05 | 1.27242e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1430.2 | 0.0510998 | 1038.74ms | 4390 | 320 | 716.018 | 2927.3 | 0.0573595 | 3.65229 | 16.5267 | 3.17084 | 0.00269433 | 4.1287e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1170.97 | 0.0244166 | 1097.29ms | 4390 | 4890 | 3726.6 | 3575.34 | 0.0352137 | 4.44696 | 19.1638 | 3.25034 | 0.00240419 | 3.40055e-05 | 5.40362e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2373.27 | 0.025696 | 1097.53ms | 9378 | 4890 | 4585.28 | 3768.46 | 0.131636 | 2.19258 | 9.36257 | 1.69727 | 0.00145079 | 1.97783e-05 | 3.40177e-06 | 1(Win) | true |
| simdjson (ondemand) | 2123.99 | 0.0730339 | 1140.16ms | 9378 | 160 | 1513.16 | 4210.74 | 0.0118758 | 2.44915 | 10.2488 | 1.69834 | 0.0019667 | 1.73278e-05 | 1.33291e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2603.45 | 0.0374974 | 1091.18ms | 9378 | 2560 | 4247.82 | 3435.27 | 0.0950848 | 2.00503 | 8.63702 | 1.53679 | 0.00159386 | 1.76194e-05 | 2.41589e-06 | 1(Win) | true |
| simdjson (ondemand) | 2291.42 | 0.0344015 | 1149.23ms | 9378 | 2560 | 4615.37 | 3903.07 | 0.176304 | 2.24491 | 9.60002 | 1.55257 | 0.00176306 | 1.99103e-05 | 4.20699e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.877 | 0.0547632 | 1269.96ms | 4390 | 1280 | 11470.9 | 5466.45 | 0.0234329 | 6.77173 | 29.7517 | 5.95923 | 0.0121396 | 7.31421e-05 | 2.24231e-05 | 1(Win) | true |
| simdjson (ondemand) | 675.658 | 0.03759 | 1343.17ms | 4390 | 2560 | 13888.6 | 6196.37 | 0.125596 | 7.61838 | 33.2314 | 6.11276 | 0.00803655 | 0.000107311 | 4.66259e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.625 | 0.0745737 | 1262.06ms | 4390 | 640 | 9423.92 | 5145.65 | 0.0384574 | 6.3773 | 28.2592 | 5.62756 | 0.0116828 | 3.16771e-05 | 7.47437e-06 | 1(Win) | true |
| simdjson (ondemand) | 717.946 | 0.234223 | 1333.87ms | 4390 | 80 | 14924.3 | 5831.4 | 0.0715439 | 7.2154 | 31.818 | 5.7959 | 0.00809226 | 0.000125285 | 2.2779e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1505.98 | 0.0769763 | 1319.09ms | 9378 | 80 | 1671.81 | 5938.7 | 0.000841928 | 3.44481 | 14.9292 | 2.91629 | 0.00597675 | 4.79846e-05 | 2.26594e-05 | 1(Win) | true |
| simdjson (ondemand) | 1372.3 | 0.0373762 | 1371.46ms | 9378 | 1280 | 7594.96 | 6517.21 | 0.037235 | 3.71207 | 16.0448 | 2.86778 | 0.00470166 | 2.51586e-05 | 9.91349e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1593.68 | 0.0248161 | 1306.59ms | 9378 | 4890 | 9483.97 | 5611.87 | 0.330273 | 3.23543 | 14.2305 | 2.76104 | 0.00625643 | 4.14101e-05 | 1.32146e-05 | 1(Win) | true |
| simdjson (ondemand) | 1491.85 | 0.0734406 | 1344.43ms | 9378 | 40 | 775.353 | 5994.93 | 0.0221069 | 3.4772 | 15.3575 | 2.71454 | 0.00424131 | 2.66581e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2095.77 | 0.113135 | 915.624ms | 4390 | 160 | 817.246 | 1997.66 | 0.067846 | 2.46905 | 10.7417 | 1.97585 | 0.00227648 | 4.98292e-05 | 2.98975e-05 | 1(Win) | true |
| simdjson (ondemand) | 1976.3 | 0.104355 | 928.2ms | 4390 | 640 | 3127.74 | 2118.42 | 0.0382212 | 2.65142 | 11.8565 | 1.89932 | 0.00134325 | 3.59482e-05 | 8.54214e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2257.16 | 0.0761532 | 907.299ms | 4390 | 80 | 159.615 | 1854.83 | 0.0794591 | 2.33207 | 10.4009 | 1.8959 | 0.00220387 | 1.70843e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2024.42 | 0.134866 | 931.959ms | 4390 | 30 | 233.375 | 2068.07 | 0.08227 | 2.59412 | 11.5733 | 1.83075 | 0.00220197 | 0 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3844.17 | 0.0298235 | 954.994ms | 9378 | 4890 | 2354.19 | 2326.52 | 0.0699806 | 1.3638 | 5.80657 | 0.975155 | 0.00118947 | 1.75104e-05 | 2.90023e-06 | 1(Win) | true |
| simdjson (ondemand) | 3835.58 | 0.021366 | 951.253ms | 9378 | 4890 | 1213.71 | 2331.74 | 0.0119571 | 1.36504 | 6.17936 | 0.920132 | 0.000757353 | 1.3956e-05 | 2.66036e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3979.28 | 0.100326 | 947.199ms | 9378 | 30 | 152.533 | 2247.53 | 0.0355819 | 1.3227 | 5.67402 | 0.943058 | 0.00110542 | 2.13265e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3949 | 0.041239 | 947.746ms | 9378 | 1280 | 1116.54 | 2264.77 | 0.0851045 | 1.32712 | 6.04681 | 0.888036 | 0.00075026 | 1.09965e-05 | 5.83147e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1704.36 | 0.0330244 | 966.57ms | 4390 | 4890 | 3217.99 | 2456.42 | 0.00259248 | 3.06515 | 14.0765 | 2.64374 | 0.00437726 | 3.20025e-05 | 3.77322e-06 | 1(Win) | true |
| simdjson (ondemand) | 1581.7 | 0.0929591 | 985.082ms | 4390 | 40 | 242.174 | 2646.93 | 0.0185785 | 3.30764 | 14.6797 | 2.42187 | 0.00299544 | 0 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1760.33 | 0.0324035 | 958.229ms | 4390 | 4890 | 2904.26 | 2378.33 | 0.0246889 | 2.97246 | 13.7934 | 2.57517 | 0.00377708 | 3.07447e-05 | 6.19553e-06 | 1(Win) | true |
| simdjson (ondemand) | 1623.53 | 0.0505547 | 980.682ms | 4390 | 160 | 271.927 | 2578.72 | 0.0230197 | 3.22188 | 14.3966 | 2.3533 | 0.00278616 | 2.2779e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3140.47 | 0.0373148 | 1005.55ms | 9378 | 2560 | 2890.91 | 2847.84 | 0.070278 | 1.66073 | 7.35114 | 1.3087 | 0.00202768 | 1.95354e-05 | 4.20699e-06 | 1(Win) | true |
| simdjson (ondemand) | 3118.23 | 0.0630508 | 1005.93ms | 9378 | 80 | 261.623 | 2868.15 | 0.00174325 | 1.6799 | 7.49712 | 1.16315 | 0.00147553 | 1.06633e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3240.9 | 0.0480562 | 1000.41ms | 9378 | 2560 | 4502.23 | 2759.59 | 0.0181012 | 1.61004 | 7.2186 | 1.27661 | 0.00173749 | 1.74527e-05 | 1.66613e-06 | 1(Win) | true |
| simdjson (ondemand) | 3196.53 | 0.091136 | 1002.09ms | 9378 | 30 | 195.059 | 2797.9 | 0.00119138 | 1.63997 | 7.36458 | 1.13105 | 0.00131869 | 1.06633e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.38 | 0.0503935 | 1032.74ms | 4669 | 2560 | 6256.11 | 3102.11 | 0.0387564 | 3.63561 | 14.7323 | 2.98672 | 0.00264879 | 8.46675e-05 | 3.84016e-05 | 1(Win) | true |
| simdjson (ondemand) | 1401.02 | 0.0516331 | 1042.02ms | 4669 | 2560 | 6893.73 | 3178.19 | 0.0653199 | 3.71834 | 16.4699 | 2.48704 | 0.00101609 | 4.50946e-05 | 1.28005e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1555.82 | 0.0291641 | 1013.78ms | 4669 | 2560 | 1783.48 | 2861.97 | 0.051075 | 3.35422 | 13.9163 | 2.8006 | 0.00219659 | 3.5055e-05 | 2.09159e-06 | 1(Win) | true |
| simdjson (ondemand) | 1504.09 | 0.16023 | 1024.51ms | 4669 | 30 | 675.007 | 2960.4 | 0.0461436 | 3.47315 | 15.6682 | 2.30478 | 0.00122082 | 3.56964e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2233.28 | 0.0457772 | 1064.57ms | 7932 | 4890 | 11756.7 | 3387.19 | 0.0556946 | 2.31167 | 10.2089 | 1.48512 | 0.000968457 | 2.83081e-05 | 8.7915e-06 | 1(Win) | true |
| Jsonifier (generic) | 2098.52 | 0.163312 | 1084.05ms | 7932 | 30 | 1039.67 | 3604.7 | 0.059147 | 2.44587 | 9.50895 | 1.81631 | 0.00165154 | 1.68095e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2432.04 | 0.0837663 | 1046.9ms | 7932 | 640 | 4344.54 | 3110.38 | 0.0170326 | 2.14563 | 9.73298 | 1.37771 | 0.000969175 | 1.61529e-05 | 2.36384e-06 | 1(Win) | true |
| Jsonifier (generic) | 2296.08 | 0.0338176 | 1060.38ms | 7932 | 4890 | 6069.95 | 3294.54 | 0.0347543 | 2.26001 | 9.01488 | 1.70222 | 0.00113212 | 2.68128e-05 | 7.34773e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 593.468 | 0.0309072 | 1470.6ms | 4669 | 1280 | 6883.09 | 7502.86 | 0.0246113 | 8.72402 | 38.6929 | 7.67959 | 0.0092654 | 3.81506e-05 | 2.34258e-06 | 1(Win) | true |
| simdjson (ondemand) | 244.425 | 0.0314529 | 2556.1ms | 4669 | 2560 | 84046.3 | 18217.1 | 0.301549 | 21.0934 | 104.744 | 18.9595 | 0.0354785 | 5.26244e-05 | 9.37031e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 622.075 | 0.026144 | 1442.11ms | 4669 | 2560 | 8964.92 | 7157.83 | 0.0141637 | 8.33004 | 37.8929 | 7.49754 | 0.00892447 | 4.14134e-05 | 6.35843e-06 | 1(Win) | true |
| simdjson (ondemand) | 247.29 | 0.160683 | 2536.5ms | 4669 | 80 | 66967.7 | 18006 | 0.0952248 | 20.8727 | 103.945 | 18.7781 | 0.0348736 | 4.5513e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.572 | 0.0534408 | 1559.23ms | 7932 | 80 | 1601.31 | 8371.83 | 0.00358332 | 5.73012 | 24.4981 | 4.84279 | 0.00500662 | 3.30938e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 415.722 | 0.0644349 | 2558.15ms | 7932 | 640 | 87979.9 | 18196.2 | 0.0685796 | 12.3972 | 61.3158 | 11.0202 | 0.0223917 | 3.95944e-05 | 1.69409e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 939.934 | 0.0180422 | 1529.36ms | 7932 | 4890 | 10310 | 8047.95 | 0.0244478 | 5.50458 | 24.0252 | 4.73512 | 0.004907 | 2.6194e-05 | 3.4805e-06 | 1(Win) | true |
| simdjson (ondemand) | 418.042 | 0.0378088 | 2565.51ms | 7932 | 2560 | 119826 | 18095.2 | 0.330761 | 12.2572 | 60.8433 | 10.9129 | 0.0220792 | 2.79229e-05 | 5.46639e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4507.77 | 0.0610897 | 816.196ms | 4669 | 4890 | 1780.62 | 987.785 | 0.0329806 | 1.18843 | 5.1722 | 0.762691 | 0.00128704 | 1.32712e-05 | 1.22638e-06 | 1(Win) | true |
| simdjson (ondemand) | 4190.89 | 0.138573 | 819.936ms | 4669 | 1280 | 2774.62 | 1062.47 | 0.0275083 | 1.27406 | 5.63911 | 0.70165 | 0.00139501 | 1.18802e-05 | 2.50991e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4880.6 | 0.0962696 | 805.578ms | 4669 | 2560 | 1974.78 | 912.327 | 0.245511 | 1.09996 | 4.89848 | 0.701007 | 0.00140663 | 2.09995e-05 | 3.93219e-06 | 1(Win) | true |
| simdjson (ondemand) | 4532.19 | 0.0768565 | 816.019ms | 4669 | 4890 | 2788.06 | 982.463 | 0.348185 | 1.18911 | 5.36539 | 0.639966 | 0.00126685 | 1.96659e-05 | 3.46015e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6419.35 | 0.0614777 | 833.182ms | 7932 | 320 | 167.945 | 1178.4 | 0.0618277 | 0.830548 | 3.65721 | 0.483737 | 0.000562201 | 2.00927e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 6230.83 | 0.0674947 | 836.522ms | 7932 | 1280 | 859.454 | 1214.05 | 0.0891748 | 0.853589 | 3.81934 | 0.433813 | 0.000892843 | 5.02317e-06 | 1.37891e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6898.02 | 0.0549939 | 827.81ms | 7932 | 40 | 14.5481 | 1096.62 | 0.0372216 | 0.774354 | 3.49609 | 0.447428 | 0.000504286 | 6.30358e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6628.12 | 0.0921866 | 828.146ms | 7932 | 160 | 177.109 | 1141.28 | 0.0487628 | 0.804595 | 3.65822 | 0.397504 | 0.00078716 | 9.45537e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3254.91 | 0.0531099 | 854.36ms | 4669 | 4890 | 2581.25 | 1368 | 0.388755 | 1.62808 | 7.65175 | 1.31292 | 0.00155457 | 1.76511e-05 | 2.89075e-06 | 1(Win) | true |
| simdjson (ondemand) | 2573.14 | 0.0462424 | 888.163ms | 4669 | 2560 | 1639.24 | 1730.46 | 0.036285 | 2.04696 | 9.78968 | 1.52924 | 0.00229531 | 1.20475e-05 | 1.75693e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3469.76 | 0.387689 | 845.592ms | 4669 | 80 | 1980.18 | 1283.29 | 0.155116 | 1.53073 | 7.37803 | 1.25123 | 0.00136539 | 2.94496e-05 | 8.0317e-06 | 1(Win) | true |
| simdjson (ondemand) | 2674.79 | 0.037433 | 888.376ms | 4669 | 4890 | 1898.84 | 1664.7 | 0.128834 | 1.96305 | 9.51596 | 1.46755 | 0.00231825 | 1.19134e-05 | 1.62057e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4624.82 | 0.0383408 | 888.051ms | 7932 | 4890 | 1923.12 | 1635.64 | 1.67839 | 1.13912 | 5.27408 | 0.820348 | 0.000896578 | 1.57267e-05 | 1.62424e-06 | 1(Win) | true |
| simdjson (ondemand) | 3945.09 | 0.244537 | 908.71ms | 7932 | 160 | 3517.7 | 1917.46 | 0.124684 | 1.33335 | 6.2408 | 0.916919 | 0.00139703 | 1.26072e-05 | 7.87948e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4684.12 | 0.070902 | 884.308ms | 7932 | 4890 | 6411.15 | 1614.94 | 0.699458 | 1.12069 | 5.11299 | 0.784045 | 0.000832511 | 1.3329e-05 | 2.16565e-06 | 1(Win) | true |
| simdjson (ondemand) | 4110.88 | 0.103994 | 901.541ms | 7932 | 1280 | 4687.32 | 1840.13 | 0.0413778 | 1.27925 | 6.07968 | 0.880611 | 0.00134325 | 9.45537e-06 | 4.92467e-07 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 562.854 | 0.0476707 | 1514.43ms | 4604 | 640 | 8850.4 | 7800.82 | 0.110487 | 9.19657 | 36.3228 | 7.71786 | 0.0125166 | 5.09068e-05 | 1.28964e-05 | 1(Win) | true |
| simdjson (ondemand) | 544.367 | 0.034479 | 1531.01ms | 4604 | 2560 | 19798.7 | 8065.72 | 0.0402148 | 9.50391 | 38.9056 | 7.06788 | 0.0104344 | 0.000129897 | 5.61672e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 645.137 | 0.0577481 | 1500.46ms | 4604 | 640 | 9886.06 | 6805.87 | 0.0234228 | 8.02877 | 31.7843 | 6.68549 | 0.0102672 | 4.07255e-05 | 3.73317e-06 | 1(Win) | true |
| simdjson (ondemand) | 618.927 | 0.0446836 | 1526.78ms | 4604 | 1280 | 12861.7 | 7094.07 | 0.00445995 | 8.3662 | 34.4881 | 6.06147 | 0.00898098 | 4.37799e-05 | 7.29664e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2072.68 | 0.0594188 | 1567.58ms | 18245 | 320 | 7962 | 8394.84 | 0.0986983 | 2.49663 | 10.0902 | 1.99477 | 0.00287836 | 1.04481e-05 | 1.7128e-07 | 1(Win) | true |
| simdjson (ondemand) | 1980.11 | 0.0707244 | 1611.91ms | 18245 | 80 | 3089.85 | 8787.29 | 0.0513262 | 2.61402 | 10.7303 | 1.82165 | 0.00310907 | 6.16607e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2341.46 | 0.0536979 | 1573.44ms | 18245 | 640 | 10190.8 | 7431.18 | 0.056719 | 2.21043 | 8.94541 | 1.7345 | 0.00244648 | 7.70759e-06 | 5.13839e-07 | 1(Win) | true |
| simdjson (ondemand) | 2208.1 | 0.0353073 | 1607.38ms | 18245 | 2560 | 19816.3 | 7879.99 | 0.0835088 | 2.32069 | 9.63015 | 1.57084 | 0.00271521 | 1.89264e-05 | 7.32221e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 326.981 | 0.0581731 | 2096.11ms | 4604 | 640 | 39052.6 | 13428.1 | 0.0472783 | 15.7719 | 68.8691 | 14.9241 | 0.0203044 | 5.1925e-05 | 1.90052e-05 | 1(Win) | true |
| simdjson (ondemand) | 241.472 | 0.0845992 | 2540.5ms | 4604 | 80 | 18930.4 | 18183.2 | 0.177539 | 21.3741 | 110.6 | 22.2106 | 0.021761 | 0.000244353 | 0.000152042 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 349.514 | 0.0301401 | 2086.02ms | 4604 | 1280 | 18350.2 | 12562.4 | 0.0622845 | 14.7809 | 64.4279 | 13.9067 | 0.0188208 | 5.88822e-05 | 1.01814e-05 | 1(Win) | true |
| simdjson (ondemand) | 256.173 | 0.0316366 | 2534.92ms | 4604 | 2560 | 75270.5 | 17139.7 | 0.0952258 | 20.144 | 106.184 | 21.1985 | 0.0210353 | 0.000179786 | 7.89904e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1221.21 | 0.0638586 | 2174.76ms | 18245 | 320 | 26490.7 | 14248 | 0.00399164 | 4.22888 | 18.5921 | 3.8578 | 0.00502141 | 2.9974e-05 | 1.5929e-05 | 1(Win) | true |
| simdjson (ondemand) | 923.935 | 0.014007 | 2621.5ms | 18245 | 4890 | 34025.5 | 18832.3 | 0.0303367 | 5.57945 | 28.7775 | 5.63445 | 0.00593204 | 5.97413e-05 | 3.79183e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1301.02 | 0.0472029 | 2157.03ms | 18245 | 640 | 25505.8 | 13374 | 0.118839 | 3.96999 | 17.4935 | 3.60565 | 0.00487976 | 1.85839e-05 | 4.11072e-06 | 1(Win) | true |
| simdjson (ondemand) | 980.752 | 0.120367 | 2609.21ms | 18245 | 40 | 18240.7 | 17741.3 | 0.00624759 | 5.26244 | 27.6597 | 5.37846 | 0.00526994 | 3.28857e-05 | 1.09619e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4086.62 | 0.157569 | 823.381ms | 4604 | 640 | 1834.27 | 1074.41 | 0.00552658 | 1.30452 | 6.73436 | 0.943093 | 0.000651947 | 1.32358e-05 | 3.39379e-07 | 1(Win) | true |
| simdjson (ondemand) | 3915.54 | 0.0572536 | 828.326ms | 4604 | 2560 | 1055.2 | 1121.36 | 0.0152949 | 1.36056 | 6.86924 | 0.962424 | 0.000452137 | 1.86658e-05 | 2.88472e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4200.29 | 0.0525806 | 822.121ms | 4604 | 1280 | 386.699 | 1045.34 | 0.0243582 | 1.27156 | 6.64705 | 0.923545 | 0.000651438 | 1.88355e-05 | 1.69689e-07 | 1(Win) | true |
| simdjson (ondemand) | 3984.39 | 0.0647521 | 826.675ms | 4604 | 4890 | 2489.8 | 1101.98 | 0.0712855 | 1.33736 | 6.78193 | 0.942876 | 0.00045768 | 2.47406e-05 | 4.61944e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10164.9 | 0.0245744 | 887.564ms | 18245 | 4890 | 865.279 | 1711.75 | 0.0492386 | 0.518437 | 2.5419 | 0.274431 | 0.000219451 | 8.86592e-06 | 9.07888e-07 | 1(Win) | true |
| simdjson (ondemand) | 9902.77 | 0.0983857 | 893.516ms | 18245 | 80 | 239.072 | 1757.06 | 0.00640232 | 0.532131 | 2.66117 | 0.28342 | 0.000210332 | 8.22143e-06 | 2.74048e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10385.1 | 0.0810497 | 885.779ms | 18245 | 640 | 1180.19 | 1675.46 | 0.00615464 | 0.5075 | 2.51987 | 0.269499 | 0.000164942 | 5.73787e-06 | 2.5692e-07 | 1(Win) | true |
| simdjson (ondemand) | 10059.1 | 0.0477238 | 894.1ms | 18245 | 2560 | 1744.53 | 1729.75 | 0.0156523 | 0.523675 | 2.63913 | 0.278488 | 0.000177232 | 6.55145e-06 | 1.19896e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.6 | 0.0655341 | 887.907ms | 4604 | 1280 | 1542 | 1674.83 | 0.0156291 | 2.00926 | 9.43419 | 1.6755 | 0.000946018 | 3.2241e-05 | 1.23873e-05 | 1(Win) | true |
| simdjson (ondemand) | 2054.12 | 0.0563287 | 927.915ms | 4604 | 4890 | 7089.05 | 2137.52 | 0.305212 | 2.55195 | 13.273 | 2.35491 | 0.00127075 | 2.35414e-05 | 5.7743e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2662.98 | 0.0547318 | 880.449ms | 4604 | 40 | 32.5744 | 1648.8 | 0.00202171 | 1.98102 | 9.34687 | 1.65595 | 0.00091768 | 8.6881e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2076.51 | 0.115106 | 930.895ms | 4604 | 640 | 3791.21 | 2114.47 | 0.0897027 | 2.52623 | 13.1857 | 2.33536 | 0.00111554 | 6.78758e-06 | 6.78758e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8170.3 | 0.0565544 | 935.161ms | 18245 | 160 | 232.094 | 2129.64 | 0.118117 | 0.642462 | 3.30825 | 0.461113 | 0.000164429 | 9.93423e-06 | 1.7128e-06 | 1(Win) | true |
| simdjson (ondemand) | 6316.29 | 0.187093 | 996.153ms | 18245 | 640 | 17000.5 | 2754.75 | 0.0473956 | 0.826204 | 4.27679 | 0.634475 | 0.000339905 | 8.39271e-06 | 8.56399e-08 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8290.52 | 0.0385946 | 937.404ms | 18245 | 4890 | 3208.38 | 2098.76 | 0.0295936 | 0.632879 | 3.28622 | 0.45618 | 0.000169786 | 1.03342e-05 | 9.52722e-07 | 1(Win) | true |
| simdjson (ondemand) | 6371.14 | 0.106443 | 993.901ms | 18245 | 640 | 5408.4 | 2731.03 | 0.151615 | 0.819898 | 4.25475 | 0.629543 | 0.000341532 | 4.71019e-06 | 8.56399e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1243.3 | 0.037769 | 1100.31ms | 4926 | 2560 | 5213.74 | 3778.49 | 0.160139 | 4.17118 | 17.1354 | 3.35018 | 0.00421314 | 3.94907e-05 | 1.03088e-05 | 1(Win) | true |
| simdjson (ondemand) | 1055.69 | 0.0589134 | 1164.38ms | 4926 | 2560 | 17594.8 | 4449.98 | 0.0707542 | 4.8977 | 19.6294 | 3.43383 | 0.00377771 | 0.000122278 | 6.74831e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1548.13 | 0.069532 | 1069.6ms | 4926 | 2560 | 11396.8 | 3034.5 | 0.0266152 | 3.36846 | 14.4533 | 2.75822 | 0.00430885 | 3.74289e-05 | 3.72704e-06 | 1(Win) | true |
| simdjson (ondemand) | 1272.75 | 0.035804 | 1128.97ms | 4926 | 2560 | 4471 | 3691.06 | 0.112157 | 4.09103 | 16.9959 | 2.8512 | 0.00368477 | 4.06802e-05 | 1.03088e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1864.34 | 0.051782 | 1142.15ms | 8150 | 1280 | 5965.28 | 4169 | 0.0440185 | 2.78877 | 10.975 | 2.04258 | 0.0027963 | 3.24962e-05 | 8.14801e-06 | 1(Win) | true |
| simdjson (ondemand) | 1706.76 | 0.0354426 | 1184.85ms | 8150 | 2560 | 6669.04 | 4553.92 | 0.0623649 | 3.03668 | 12.3243 | 2.0919 | 0.00212898 | 3.11541e-05 | 1.06883e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2308.84 | 0.0225726 | 1097.78ms | 8150 | 4890 | 2823.58 | 3366.39 | 0.0628004 | 2.2576 | 9.35387 | 1.68479 | 0.00259764 | 3.82651e-05 | 3.16158e-06 | 1(Win) | true |
| simdjson (ondemand) | 1994.76 | 0.22961 | 1152.38ms | 8150 | 320 | 25613.2 | 3896.43 | 0.00818125 | 2.60342 | 10.7474 | 1.74258 | 0.00285161 | 0.000116564 | 7.05521e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.514 | 0.0333347 | 1305.7ms | 4926 | 4890 | 18344.9 | 5810.41 | 0.0750309 | 6.40712 | 27.3792 | 5.4996 | 0.0101167 | 0.000139986 | 6.23128e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.085 | 0.0350367 | 1752.61ms | 4926 | 1280 | 16525.5 | 10255.3 | 0.0180514 | 11.2859 | 49.2385 | 8.96407 | 0.0248953 | 4.17111e-05 | 1.07846e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 935.652 | 0.0449992 | 1264.27ms | 4926 | 1280 | 6534 | 5020.88 | 0.0075783 | 5.54661 | 24.701 | 4.90723 | 0.00990725 | 3.86977e-05 | 4.75792e-06 | 1(Win) | true |
| simdjson (ondemand) | 496.96 | 0.0367184 | 1708.13ms | 4926 | 2560 | 30842.8 | 9453.07 | 0.073691 | 10.4061 | 46.609 | 8.38104 | 0.0229492 | 8.82594e-05 | 3.96493e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1210.77 | 0.0242476 | 1368.72ms | 8150 | 4890 | 11847.9 | 6419.44 | 0.0147075 | 4.27558 | 17.6528 | 3.51644 | 0.00645221 | 3.63833e-05 | 1.28972e-05 | 1(Win) | true |
| simdjson (ondemand) | 758.874 | 0.101548 | 1766.03ms | 8150 | 320 | 34615.6 | 10242.1 | 0.19394 | 6.82764 | 29.9443 | 5.38577 | 0.0144179 | 3.91104e-05 | 1.22699e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1376.97 | 0.0811574 | 1332.1ms | 8150 | 40 | 839.426 | 5644.6 | 0.00118106 | 3.76913 | 16.0353 | 3.15865 | 0.0065092 | 1.53374e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 818.911 | 0.03946 | 1716.96ms | 8150 | 1280 | 17954.2 | 9491.19 | 0.0193892 | 6.31913 | 28.3697 | 5.0362 | 0.014255 | 2.55943e-05 | 6.80598e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2510.44 | 0.0331975 | 904.937ms | 4926 | 4890 | 1887.17 | 1871.31 | 0.0213588 | 2.09494 | 8.92814 | 1.66565 | 0.00237764 | 4.47108e-05 | 8.59344e-06 | 1(Win) | true |
| simdjson (ondemand) | 2178.11 | 0.0273887 | 933.788ms | 4926 | 4890 | 1706.41 | 2156.83 | 0.146374 | 2.40819 | 10.2887 | 1.62789 | 0.00156463 | 2.23346e-05 | 3.03054e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2771.4 | 0.051064 | 898.266ms | 4926 | 320 | 239.755 | 1695.1 | 0.165461 | 1.90586 | 8.32318 | 1.51786 | 0.0027044 | 4.37728e-05 | 6.34389e-07 | 1(Win) | true |
| simdjson (ondemand) | 2372.79 | 0.0303246 | 926.313ms | 4926 | 640 | 230.698 | 1979.87 | 0.0401539 | 2.21551 | 9.68473 | 1.48112 | 0.00155425 | 2.09348e-05 | 6.34389e-07 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3656.7 | 0.0422331 | 928.68ms | 8150 | 1280 | 1031.46 | 2125.53 | 0.229854 | 1.44663 | 6.02994 | 1.04245 | 0.00167418 | 9.87347e-06 | 8.6273e-07 | 1(Win) | true |
| simdjson (ondemand) | 3437.55 | 0.0349148 | 946.175ms | 8150 | 4890 | 3047.51 | 2261.04 | 0.209004 | 1.52307 | 6.57546 | 0.982332 | 0.000950883 | 1.66359e-05 | 3.28704e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4011.62 | 0.0366498 | 923.779ms | 8150 | 2560 | 1290.8 | 1937.48 | 0.0947478 | 1.31033 | 5.66429 | 0.953129 | 0.00169613 | 1.8309e-05 | 1.38995e-06 | 1(Win) | true |
| simdjson (ondemand) | 3720.3 | 0.0989175 | 938.477ms | 8150 | 40 | 170.831 | 2089.2 | 0.0335169 | 1.41168 | 6.21043 | 0.89362 | 0.00111963 | 6.13497e-06 | 3.06748e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1925.13 | 0.0717897 | 967.975ms | 4926 | 640 | 1964.15 | 2440.25 | 0.0690081 | 2.72012 | 12.0481 | 2.29781 | 0.00407468 | 3.04507e-05 | 1.01502e-05 | 1(Win) | true |
| simdjson (ondemand) | 1576.59 | 0.0594957 | 1017.56ms | 4926 | 2560 | 8045.68 | 2979.72 | 0.0582507 | 3.31524 | 14.6186 | 2.44742 | 0.00487195 | 3.45742e-05 | 1.40359e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2031.57 | 0.0275868 | 965.121ms | 4926 | 4890 | 1989.93 | 2312.4 | 0.0258993 | 2.57672 | 11.4367 | 2.14819 | 0.0053445 | 4.99416e-05 | 1.62736e-05 | 1(Win) | true |
| simdjson (ondemand) | 1662.04 | 0.0366563 | 1015.39ms | 4926 | 4890 | 5249.44 | 2826.53 | 0.0090203 | 3.1341 | 14.0081 | 2.29882 | 0.00483321 | 5.58781e-05 | 2.68597e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2781.14 | 0.113884 | 1001.86ms | 8150 | 40 | 405.19 | 2794.7 | 0.174443 | 1.87979 | 7.99718 | 1.45031 | 0.00226074 | 5.82822e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2490.67 | 0.0875794 | 1030.66ms | 8150 | 80 | 597.554 | 3120.62 | 0.0480904 | 2.09479 | 9.23178 | 1.48552 | 0.00340491 | 1.53374e-05 | 1.53374e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2977.42 | 0.299253 | 991.607ms | 8150 | 160 | 9764.11 | 2610.46 | 0.0220219 | 1.75322 | 7.62761 | 1.35988 | 0.00316564 | 1.30368e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2626.89 | 0.0692437 | 1025.33ms | 8150 | 1280 | 5372.82 | 2958.8 | 0.0525457 | 1.98837 | 8.86282 | 1.39571 | 0.00357813 | 1.90759e-05 | 3.93021e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2128.56 | 0.0407172 | 847.854ms | 2821 | 2560 | 677.998 | 1263.91 | 0.00380159 | 2.49698 | 9.19 | 1.70188 | 0.000663135 | 5.70498e-05 | 8.72364e-06 | 1(Win) | true |
| simdjson (ondemand) | 1975.32 | 0.0557486 | 854.272ms | 2821 | 2560 | 1475.84 | 1361.96 | 0.0389353 | 2.68196 | 10.0411 | 1.56257 | 0.000709522 | 3.39252e-05 | 1.06622e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2346.26 | 0.166915 | 839.332ms | 2821 | 80 | 293.044 | 1146.64 | 0.0533885 | 2.27331 | 8.56966 | 1.5452 | 0.000438674 | 4.87416e-05 | 2.65863e-05 | 1(Win) | true |
| simdjson (ondemand) | 2114.98 | 0.0455006 | 850.094ms | 2821 | 2560 | 857.566 | 1272.03 | 0.0612573 | 2.51103 | 9.55973 | 1.44169 | 0.00069526 | 4.37566e-05 | 7.20046e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2699.81 | 0.0676198 | 852.099ms | 3770 | 160 | 129.743 | 1331.71 | 0.0933081 | 1.96671 | 7.37401 | 1.28515 | 0.000338196 | 3.31565e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2568.26 | 0.0607223 | 887.271ms | 3770 | 4890 | 3533.54 | 1399.92 | 0.077414 | 2.06113 | 7.84297 | 1.18462 | 0.000530395 | 5.89087e-05 | 2.95086e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2926.7 | 0.0493279 | 846.289ms | 3770 | 640 | 235.013 | 1228.47 | 0.0288807 | 1.81921 | 6.90981 | 1.1679 | 0.000625829 | 6.92142e-05 | 1.98939e-05 | 1(Win) | true |
| simdjson (ondemand) | 2723.81 | 0.127053 | 858.507ms | 3770 | 640 | 1800.03 | 1319.97 | 0.0102996 | 1.9493 | 7.48276 | 1.09416 | 0.000524702 | 3.48143e-05 | 6.21684e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 844.862 | 0.099291 | 1038.02ms | 2821 | 40 | 399.866 | 3184.32 | 0.0206785 | 6.17817 | 26.1195 | 4.82985 | 0.00130273 | 3.54484e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 355.063 | 0.0750908 | 1482.21ms | 2821 | 1280 | 41436.1 | 7577 | 0.0746647 | 14.581 | 67.0255 | 11.5573 | 0.011511 | 7.5051e-05 | 1.46779e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.216 | 0.13508 | 1042.68ms | 2821 | 30 | 549.379 | 3168 | 0.0630915 | 6.1478 | 25.5005 | 4.67246 | 0.00154791 | 0.000129978 | 8.2713e-05 | 1(Win) | true |
| simdjson (ondemand) | 357.424 | 0.0312115 | 1480.44ms | 2821 | 4890 | 26988.5 | 7526.97 | 0.253795 | 14.4706 | 66.5495 | 11.4364 | 0.0117423 | 0.000112797 | 4.66121e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1041.8 | 0.0667463 | 1066ms | 3770 | 160 | 848.956 | 3451.08 | 0.130746 | 5.003 | 20.4496 | 3.81379 | 0.00124668 | 5.13926e-05 | 9.94695e-06 | 1(Win) | true |
| simdjson (ondemand) | 469.773 | 0.0397064 | 1488.39ms | 3770 | 2560 | 23641.1 | 7653.38 | 0.0260387 | 11.0182 | 49.722 | 8.51326 | 0.0118975 | 5.09781e-05 | 1.23301e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1084.27 | 0.0822121 | 1061.97ms | 3770 | 80 | 594.526 | 3315.93 | 0.0263808 | 4.81079 | 19.9851 | 3.69549 | 0.00109748 | 3.31565e-05 | 9.94695e-06 | 1(Win) | true |
| simdjson (ondemand) | 476.982 | 0.108726 | 1489.45ms | 3770 | 320 | 21493.1 | 7537.71 | 0.0348957 | 10.8493 | 49.3645 | 8.42228 | 0.0111887 | 2.65252e-05 | 3.31565e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5717.46 | 0.181112 | 764.748ms | 2821 | 2560 | 1859.24 | 470.544 | 0.114194 | 0.96871 | 3.72847 | 0.511521 | 0.000485616 | 2.97711e-05 | 3.60023e-06 | 1(Win) | true |
| simdjson (ondemand) | 5216.34 | 0.053445 | 770.741ms | 2821 | 4890 | 371.533 | 515.748 | 0.0612734 | 1.05343 | 3.99832 | 0.449859 | 0.00108107 | 2.26899e-05 | 1.88478e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5673.6 | 0.186518 | 763ms | 2821 | 160 | 125.156 | 474.181 | 0.265634 | 0.972521 | 3.64977 | 0.493442 | 0.000943814 | 4.65261e-05 | 1.99397e-05 | 1(Win) | true |
| simdjson (ondemand) | 5443.23 | 0.128845 | 769.015ms | 2821 | 80 | 32.443 | 494.25 | 0.192581 | 1.03635 | 3.91989 | 0.432116 | 0.00106345 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6730.66 | 0.327 | 769.115ms | 3770 | 40 | 122.046 | 534.175 | 0.0452616 | 0.819854 | 3.25013 | 0.405305 | 0.000285146 | 3.97878e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6334.02 | 0.0533938 | 783.65ms | 3770 | 4890 | 449.174 | 567.626 | 0.332039 | 0.861193 | 3.32122 | 0.353316 | 0.000824451 | 1.291e-05 | 2.98341e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6811.55 | 0.0734631 | 777.467ms | 3770 | 2560 | 384.919 | 527.832 | 0.0383942 | 0.809088 | 3.19125 | 0.391777 | 0.000296336 | 1.41951e-05 | 1.96867e-06 | 1(Win) | true |
| simdjson (ondemand) | 6495.65 | 0.043465 | 780.777ms | 3770 | 1280 | 74.0844 | 553.502 | 0.168814 | 0.835913 | 3.2626 | 0.340053 | 0.000870151 | 8.0819e-06 | 6.21684e-07 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4214.24 | 0.0953701 | 787.054ms | 2821 | 160 | 59.308 | 638.388 | 0.0528955 | 1.29448 | 5.43283 | 0.868132 | 0.000759926 | 1.32932e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3608.65 | 0.0663458 | 789.276ms | 2821 | 640 | 156.576 | 745.519 | 0.183514 | 1.48558 | 6.25417 | 0.901453 | 0.000914459 | 1.27393e-05 | 1.10776e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4264.93 | 0.190235 | 781.435ms | 2821 | 30 | 43.2 | 630.8 | 0.0264145 | 1.26856 | 5.35448 | 0.850408 | 0.00141794 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3733.19 | 0.101401 | 790.037ms | 2821 | 320 | 170.875 | 720.647 | 0.0896826 | 1.45609 | 6.17618 | 0.884084 | 0.000886211 | 2.99096e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4989.46 | 0.0676538 | 792.544ms | 3770 | 1280 | 304.208 | 720.59 | 0.142991 | 1.08703 | 4.55438 | 0.680902 | 0.000782908 | 5.96817e-05 | 2.44529e-05 | 1(Win) | true |
| simdjson (ondemand) | 4525.62 | 0.116424 | 800.39ms | 3770 | 160 | 136.877 | 794.444 | 0.175746 | 1.19549 | 5.02149 | 0.693369 | 0.00103282 | 3.14987e-05 | 3.31565e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5168.26 | 0.0845135 | 790.332ms | 3770 | 1280 | 442.442 | 695.66 | 0.25163 | 1.05441 | 4.49576 | 0.667639 | 0.000573193 | 4.80769e-05 | 1.59566e-05 | 1(Win) | true |
| simdjson (ondemand) | 4685.34 | 0.0707849 | 794.95ms | 3770 | 640 | 188.826 | 767.362 | 0.0065154 | 1.15582 | 4.96313 | 0.680371 | 0.000707062 | 1.53349e-05 | 4.14456e-07 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4731.19 | 0.10035 | 6349.7ms | 277673 | 640 | 2.01902e+06 | 55971 | 0.303977 | 1.0786 | 4.29122 | 0.683817 | 0.0048865 | 2.17207e-06 | 8.77831e-07 | 1(Win) | true |
| simdjson (ondemand) | 3763.67 | 0.0832769 | 7773.14ms | 277673 | 640 | 2.19723e+06 | 70359.5 | 0.0410801 | 1.35833 | 4.69215 | 0.770977 | 0.00471658 | 8.94712e-06 | 6.41492e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4057.93 | 0.252556 | 7743.88ms | 10548466 | 40 | 1.568e+09 | 2.47905e+06 | 0.0934847 | 1.25844 | 4.28876 | 0.683731 | 0.0101408 | 0.0175175 | 0.000765905 | 1(Win) | true |
| simdjson (ondemand) | 3426.65 | 0.0901898 | 9173.69ms | 10548466 | 160 | 1.12169e+09 | 2.93575e+06 | 0.290681 | 1.48738 | 4.68845 | 0.770965 | 0.00968387 | 0.0180083 | 0.000720333 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3603.99 | 0.15305 | 6354.19ms | 16002592 | 80 | 3.36024e+09 | 4.23454e+06 | 0.0597614 | 1.40428 | 7.61292 | 1.20636 | 0.000871026 | 0.0327834 | 0.0054251 | 1(Win) | true |
| simdjson (ondemand) | 2922.45 | 0.0992361 | 7826.45ms | 16002592 | 30 | 8.05652e+08 | 5.22208e+06 | 0.0953326 | 1.72872 | 8.64356 | 1.26589 | 0.00287135 | 0.037025 | 0.00718846 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3581.12 | 0.0566585 | 6399.22ms | 16002591 | 80 | 4.66406e+08 | 4.26159e+06 | 0.209031 | 1.41211 | 7.89616 | 1.29591 | 0.000882413 | 0.0359179 | 0.00724997 | 1(Win) | true |
| simdjson (ondemand) | 1676.65 | 0.0768055 | 6384.58ms | 16002591 | 40 | 1.95497e+09 | 9.10223e+06 | 0.33334 | 3.02275 | 13.1392 | 2.15446 | 0.00283234 | 0.0539245 | 0.00569991 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 18283.6 | 0.0798789 | 5453.37ms | 16197086 | 320 | 1.45736e+08 | 844844 | 0.784728 | 0.275939 | 1.26283 | 0.0751262 | 9.68207e-05 | 0.0157225 | 0.000125728 | 1(Win) | true |
| Jsonifier (generic) | 17920 | 0.203171 | 5532.23ms | 16197086 | 40 | 1.22683e+08 | 861985 | 0.0991126 | 0.28236 | 1.33568 | 0.070273 | 7.86916e-05 | 0.0157177 | 0.000165786 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18076.6 | 0.0942275 | 5474.8ms | 16197085 | 80 | 5.18662e+07 | 854514 | 0.00179199 | 0.280145 | 1.33981 | 0.0717036 | 9.33833e-05 | 0.0157387 | 0.00023891 | 1(Win) | true |
| simdjson (ondemand) | 16793.7 | 0.0797945 | 5860.85ms | 16197085 | 320 | 1.72376e+08 | 919794 | 0.302928 | 0.302639 | 1.33731 | 0.0899315 | 0.000108757 | 0.0157564 | 0.000212362 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1861.41 | 0.0864693 | 8481.71ms | 4212000 | 40 | 1.39276e+08 | 2.15797e+06 | 0.173695 | 2.71797 | 11.4448 | 2.08984 | 0.0113275 | 0.0663459 | 0.00365432 | 1(Win) | true |
| simdjson (ondemand) | 1483.27 | 0.0651925 | 10244.6ms | 4212000 | 160 | 4.98716e+08 | 2.70813e+06 | 0.237651 | 3.41212 | 13.541 | 2.37315 | 0.0136181 | 0.0661918 | 0.00211212 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.61 | 0.045404 | 9763.52ms | 4212000 | 160 | 2.15749e+08 | 2.55753e+06 | 0.0880615 | 3.2238 | 15.2585 | 2.94046 | 0.0119481 | 0.0663017 | 0.00163708 | 1(Win) | true |
| simdjson (ondemand) | 1254.58 | 0.117807 | 5674.87ms | 4212000 | 40 | 5.69087e+08 | 3.20176e+06 | 0.247397 | 4.0315 | 16.6715 | 2.90954 | 0.0148345 | 0.0664491 | 0.00397717 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1754.64 | 0.155228 | 8902.92ms | 4211999 | 40 | 5.05124e+08 | 2.28928e+06 | 0.0080148 | 2.89171 | 12.3747 | 2.30546 | 0.0121183 | 0.0681227 | 0.00144559 | 1(Win) | true |
| simdjson (ondemand) | 1238.71 | 0.165661 | 5748.95ms | 4211999 | 40 | 1.15435e+09 | 3.24278e+06 | 0.135787 | 4.10907 | 15.7803 | 2.82266 | 0.0138292 | 0.0682594 | 0.00226285 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.49 | 0.0921564 | 9950.16ms | 4211999 | 80 | 4.7047e+08 | 2.63145e+06 | 0.0573698 | 3.33246 | 15.4783 | 2.99723 | 0.0125735 | 0.0681156 | 0.00154355 | 1(Win) | true |
| simdjson (ondemand) | 920.06 | 0.0763055 | 7399.23ms | 4211999 | 80 | 8.87862e+08 | 4.36588e+06 | 0.0140994 | 5.5443 | 18.9107 | 3.359 | 0.0242068 | 0.0685317 | 0.0138654 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1464.09 | 0.149531 | 9908.45ms | 4525120 | 40 | 7.77043e+08 | 2.94755e+06 | 0.277695 | 3.49552 | 16.6413 | 3.01451 | 0.00950586 | 0.0778435 | 0.0038786 | 1(Win) | true |
| simdjson (ondemand) | 1307.65 | 0.184272 | 5260.21ms | 4525120 | 30 | 1.10948e+09 | 3.30019e+06 | 0.622801 | 3.87162 | 17.208 | 2.6279 | 0.0154574 | 0.0776282 | 0.0131329 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.03 | 0.084767 | 8702.76ms | 4525120 | 40 | 8.81994e+08 | 5.53957e+06 | 0.171113 | 6.51604 | 32.0192 | 6.41872 | 0.0156584 | 0.0784765 | 0.0031436 | 1(Win) | true |
| simdjson (ondemand) | 601.384 | 0.0639922 | 5212.96ms | 4525120 | 40 | 8.43471e+08 | 7.17593e+06 | 0.276875 | 8.51054 | 42.9394 | 8.0928 | 0.0262953 | 0.0776657 | 0.00325617 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1305.94 | 0.161454 | 5333.35ms | 4525119 | 30 | 8.53948e+08 | 3.30451e+06 | 0.345319 | 3.90779 | 18.8618 | 3.56887 | 0.0100957 | 0.0781217 | 0.00119282 | 1(Win) | true |
| simdjson (ondemand) | 957.666 | 0.0786863 | 7159.41ms | 4525119 | 80 | 1.00582e+09 | 4.50626e+06 | 0.282627 | 5.30928 | 22.1232 | 3.61269 | 0.018246 | 0.0953383 | 0.00581679 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 802.682 | 0.146693 | 8497.69ms | 4525119 | 30 | 1.866e+09 | 5.37634e+06 | 0.0616657 | 6.36737 | 31.7503 | 6.41975 | 0.0156354 | 0.0783227 | 0.00793359 | 1(Win) | true |
| simdjson (ondemand) | 512.375 | 0.0987565 | 6176.12ms | 4525119 | 40 | 2.76742e+09 | 8.42252e+06 | 0.0253416 | 9.95981 | 47.8543 | 9.07752 | 0.0294476 | 0.0958454 | 0.00631938 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1199.61 | 0.20477 | 5361.45ms | 4203059 | 80 | 3.74519e+09 | 3.34138e+06 | 0.155488 | 4.23472 | 17.8451 | 3.41887 | 0.0146411 | 0.0899235 | 0.0134879 | 1(Win) | true |
| simdjson (ondemand) | 951.688 | 0.107562 | 6721.98ms | 4203059 | 30 | 6.15718e+08 | 4.21183e+06 | 0.344963 | 5.32496 | 20.4366 | 3.55463 | 0.0271071 | 0.0891833 | 0.00137799 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 796.355 | 0.111627 | 7942.71ms | 4203059 | 80 | 2.5255e+09 | 5.03337e+06 | 0.0356101 | 6.38066 | 28.0166 | 5.62766 | 0.0229145 | 0.089484 | 0.0153223 | 1(Win) | true |
| simdjson (ondemand) | 706.035 | 0.153947 | 8934.72ms | 4203059 | 40 | 3.05549e+09 | 5.67727e+06 | 0.119469 | 7.20683 | 28.8471 | 5.14704 | 0.0312362 | 0.0879426 | 0.00731048 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1080.28 | 0.163456 | 5900.48ms | 4203058 | 80 | 2.94274e+09 | 3.71048e+06 | 0.668353 | 4.70737 | 19.9816 | 3.95227 | 0.0167643 | 0.0891268 | 0.00521014 | 1(Win) | true |
| simdjson (ondemand) | 760.682 | 0.183008 | 8306.22ms | 4203058 | 30 | 2.78988e+09 | 5.26942e+06 | 0.0858352 | 6.67165 | 25.0667 | 4.46731 | 0.0288594 | 0.103106 | 0.00184777 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.482 | 0.0412416 | 8382.32ms | 4203058 | 30 | 1.43261e+08 | 5.29867e+06 | 0.202182 | 6.80294 | 30.1525 | 6.16082 | 0.024738 | 0.0889217 | 0.00835213 | 1(Win) | true |
| simdjson (ondemand) | 594.579 | 0.121395 | 10428.1ms | 4203058 | 30 | 2.00925e+09 | 6.74149e+06 | 0.264429 | 8.52398 | 33.4786 | 6.06033 | 0.0325685 | 0.101678 | 0.0100648 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1585.38 | 0.111887 | 8144.45ms | 4197496 | 40 | 3.19254e+08 | 2.52498e+06 | 0.00372657 | 3.21085 | 15.7568 | 3.07156 | 0.000503884 | 0.0819465 | 0.000678345 | 1(Win) | true |
| simdjson (ondemand) | 1360.29 | 0.0482855 | 9436.45ms | 4197496 | 160 | 3.23051e+08 | 2.94279e+06 | 0.0703152 | 3.71807 | 18.5659 | 2.76464 | 0.00881265 | 0.0817383 | 0.00165708 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1013.6 | 0.0656832 | 6104.25ms | 4197496 | 80 | 5.38323e+08 | 3.94932e+06 | 0.0727851 | 5.00113 | 27.5621 | 5.67743 | 0.000955856 | 0.0822121 | 0.00569998 | 1(Win) | true |
| simdjson (ondemand) | 750.999 | 0.112922 | 8175.03ms | 4197496 | 30 | 1.08688e+09 | 5.33029e+06 | 0.124672 | 6.74848 | 34.5093 | 5.39404 | 0.0142429 | 0.0823158 | 0.00221947 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1407.83 | 0.0810111 | 9115.92ms | 4197495 | 80 | 4.24484e+08 | 2.84342e+06 | 0.0829694 | 3.59812 | 18.0186 | 3.60626 | 0.000671984 | 0.0843626 | 0.00574805 | 1(Win) | true |
| simdjson (ondemand) | 994.508 | 0.248416 | 6227.25ms | 4197495 | 30 | 2.99948e+09 | 4.02515e+06 | 0.196531 | 5.11249 | 23.683 | 3.77693 | 0.00950842 | 0.103839 | 0.00349315 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.046 | 0.0424069 | 6276.49ms | 4197495 | 80 | 2.35673e+08 | 4.04738e+06 | 0.0191038 | 5.10691 | 27.8269 | 5.76686 | 0.00117435 | 0.0845791 | 0.00243011 | 1(Win) | true |
| simdjson (ondemand) | 626.147 | 0.133065 | 9832.31ms | 4197495 | 30 | 2.1711e+09 | 6.39313e+06 | 0.259785 | 8.08199 | 39.6264 | 6.40632 | 0.0151085 | 0.104148 | 0.00956223 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.47 | 0.0897098 | 5285.1ms | 4506447 | 80 | 5.84404e+08 | 3.01281e+06 | 0.055322 | 3.54292 | 15.8911 | 3.00069 | 0.00861423 | 0.0804471 | 0.00431197 | 1(Win) | true |
| simdjson (ondemand) | 1091.18 | 0.0859865 | 6671.25ms | 4506447 | 80 | 9.17548e+08 | 3.93857e+06 | 0.0571526 | 4.64347 | 18.3172 | 3.1405 | 0.0176421 | 0.0787664 | 0.00373431 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 853.181 | 0.144007 | 8357.3ms | 4506447 | 40 | 2.10482e+09 | 5.03725e+06 | 0.276418 | 5.94399 | 26.8781 | 5.42164 | 0.0130514 | 0.080836 | 0.0150133 | 1(Win) | true |
| simdjson (ondemand) | 499.833 | 0.126955 | 6390.02ms | 4506447 | 30 | 3.57468e+09 | 8.59824e+06 | 0.0123254 | 10.1483 | 43.7018 | 7.7793 | 0.0359104 | 0.0790057 | 0.0209321 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1289.45 | 0.455615 | 5749.86ms | 4506446 | 40 | 9.22392e+09 | 3.33296e+06 | 0.146241 | 3.93144 | 17.5602 | 3.41567 | 0.0111232 | 0.0808545 | 0.0032406 | 1(Win) | true |
| simdjson (ondemand) | 894.104 | 0.199756 | 7960.87ms | 4506446 | 80 | 7.37534e+09 | 4.80669e+06 | 0.132592 | 5.6785 | 21.9732 | 3.85896 | 0.0179059 | 0.0867825 | 0.00270331 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 846.743 | 0.348609 | 8363.23ms | 4506446 | 30 | 9.39211e+09 | 5.07554e+06 | 0.425482 | 5.96775 | 26.7363 | 5.43394 | 0.0132015 | 0.0810863 | 0.00426377 | 1(Win) | true |
| simdjson (ondemand) | 456.764 | 0.214983 | 6950.22ms | 4506446 | 30 | 1.22749e+10 | 9.40899e+06 | 0.168405 | 11.0807 | 47.3576 | 8.49768 | 0.0360704 | 0.0856905 | 0.00925377 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1982.7 | 0.384606 | 7011.17ms | 4219120 | 40 | 2.43681e+09 | 2.02939e+06 | 0.247398 | 2.55562 | 9.28939 | 1.64433 | 0.011529 | 0.0566562 | 0.000206074 | 1(Win) | true |
| simdjson (ondemand) | 1701.21 | 0.106256 | 8071.08ms | 4219120 | 80 | 5.05266e+08 | 2.36517e+06 | 0.268928 | 2.95002 | 9.95526 | 1.53735 | 0.0175347 | 0.0538274 | 0.000226137 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 746.141 | 0.302007 | 8455.44ms | 4219120 | 30 | 7.95716e+09 | 5.39263e+06 | 0.52273 | 6.75332 | 26.4403 | 4.97387 | 0.0167754 | 0.0576631 | 0.00113435 | 1(Win) | true |
| simdjson (ondemand) | 287.92 | 0.0861247 | 10007.2ms | 4219120 | 40 | 5.7945e+09 | 1.39749e+07 | 0.0603813 | 17.5269 | 70.159 | 12.1737 | 0.0850667 | 0.0540767 | 0.00847667 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.65 | 0.185804 | 7499.31ms | 4219119 | 30 | 4.87475e+08 | 2.16951e+06 | 0.231299 | 2.74581 | 10.3167 | 1.89967 | 0.0121528 | 0.0564935 | 0.000764939 | 1(Win) | true |
| simdjson (ondemand) | 1399.15 | 0.0631645 | 9654.74ms | 4219119 | 160 | 5.27939e+08 | 2.8758e+06 | 0.228199 | 3.58894 | 12.1567 | 1.96556 | 0.0192749 | 0.0532469 | 0.000345256 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 754.01 | 0.0986717 | 8383.41ms | 4219119 | 30 | 8.31756e+08 | 5.33635e+06 | 0.250041 | 6.72263 | 26.3382 | 4.97764 | 0.0169592 | 0.0578287 | 0.00277338 | 1(Win) | true |
| simdjson (ondemand) | 276.456 | 0.149014 | 10418.6ms | 4219119 | 40 | 1.8815e+10 | 1.45544e+07 | 0.188144 | 18.2638 | 72.3589 | 12.6015 | 0.0868096 | 0.0537844 | 0.0149669 | 2(Loss) | true |
