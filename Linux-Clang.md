# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-42-generic using the Clang 24.0.0 compiler).  

Latest Results: (Nov 07, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [3e5ab01](https://github.com/nihilai-collective/Jsonifier/commit/3e5ab01)  
| simdjson: [dfe02cfe3](https://github.com/simdjson/simdjson/commit/dfe02cfe3)  

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
*Environment generated via BenchmarkSuite commit: [ed43ce8](https://github.com/nihilai-collective/benchmarksuite/commit/ed43ce8)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 538.377 | 0.0543549 | 880.152ms | 905 | 4890 | 3712.88 | 1603.1 | 0.200477 | 9.62157 | 49.3702 | 6.37017 | 0.00117525 | 0.000129704 | 1.12983e-05 | 1(Win) | true |
| simdjson (ondemand) | 286.191 | 0.0400834 | 1027.68ms | 905 | 1280 | 1870.35 | 3015.73 | 0.12658 | 18.2435 | 88.9459 | 9.47735 | 0.0243862 | 0.000284012 | 0.000101001 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 549.347 | 0.0612907 | 878.131ms | 905 | 4890 | 4534.22 | 1571.09 | 0.140882 | 9.44041 | 48.7514 | 6.25194 | 0.00118203 | 0.000147104 | 5.64914e-06 | 1(Win) | true |
| simdjson (ondemand) | 284.403 | 0.0448172 | 1026.98ms | 905 | 1280 | 2367.72 | 3034.7 | 0.0623901 | 18.0219 | 88.3271 | 9.35912 | 0.0239857 | 0.000262431 | 6.73343e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 659.107 | 0.0972655 | 991.032ms | 1811 | 640 | 4157.41 | 2620.37 | 0.0313747 | 7.7858 | 38.9547 | 6.35837 | 0.00258576 | 0.000119064 | 3.53741e-05 | 1(Win) | true |
| simdjson (ondemand) | 357.524 | 0.120106 | 1213.96ms | 1811 | 640 | 21544.4 | 4830.74 | 0.138077 | 14.0061 | 71.1706 | 9.25014 | 0.00142014 | 6.21204e-05 | 0 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 699.43 | 0.0633349 | 976.776ms | 1811 | 640 | 1565.36 | 2469.3 | 0.120334 | 7.34705 | 37.9117 | 6.13143 | 0.000785995 | 7.85133e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 367.484 | 0.03531 | 1207.48ms | 1811 | 4890 | 13466.8 | 4699.8 | 0.0220678 | 13.7989 | 70.2253 | 9.04363 | 0.00145611 | 9.27077e-05 | 1.37763e-05 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1518.34 | 0.0616149 | 972.681ms | 3862 | 640 | 1429.68 | 2425.73 | 0.0924123 | 3.38389 | 16.934 | 2.09917 | 0.00102966 | 2.71071e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 801.272 | 0.0814747 | 1196.04ms | 3862 | 1280 | 17952.3 | 4596.56 | 0.0320959 | 6.47257 | 28.2372 | 3.48887 | 0.0137734 | 5.21912e-05 | 1.53742e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1579.89 | 0.0614821 | 958.654ms | 3862 | 320 | 657.38 | 2331.23 | 0.0898664 | 3.25695 | 16.4544 | 1.99016 | 0.00102764 | 4.28858e-05 | 1.05192e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.403 | 0.0412096 | 1180.75ms | 3862 | 4890 | 17323.1 | 4567.31 | 0.234348 | 6.4058 | 27.7962 | 3.39203 | 0.0164284 | 6.72485e-05 | 2.02805e-05 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1409.14 | 0.0731071 | 1389.66ms | 9578 | 320 | 7186.36 | 6482.16 | 0.0804294 | 3.60904 | 17.6879 | 3.00512 | 0.00330445 | 3.23006e-05 | 8.48298e-06 | 1(Win) | true |
| Jsonifier (generic) | 1317.23 | 0.0750837 | 1423.75ms | 9578 | 1280 | 34699.7 | 6934.46 | 0.0169022 | 3.86935 | 19.3275 | 3.3933 | 0.00212181 | 4.6738e-05 | 2.07996e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1974.91 | 0.0438551 | 1346.47ms | 9578 | 2560 | 10532.6 | 4625.17 | 0.0534576 | 2.57185 | 13.3554 | 2.02631 | 0.00232736 | 2.73658e-05 | 7.70809e-06 | 1(Win) | true |
| Jsonifier (generic) | 1762.32 | 0.0523671 | 1380.56ms | 9578 | 160 | 1178.74 | 5183.11 | 0 | 2.8931 | 15.0177 | 2.4171 | 0.00201112 | 1.8271e-05 | 0 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1518.26 | 0.126126 | 985.16ms | 3873 | 80 | 753.189 | 2432.78 | 0.0483221 | 3.38861 | 17.072 | 2.11748 | 0.00104893 | 4.84121e-05 | 9.68242e-06 | 1(Win) | true |
| simdjson (ondemand) | 709.099 | 0.112631 | 1251.22ms | 3873 | 30 | 1032.56 | 5208.83 | 0.0358237 | 7.05397 | 27.8567 | 3.5528 | 0.0163956 | 0.000103279 | 0 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1580.57 | 0.0415183 | 965.213ms | 3873 | 1280 | 1204.92 | 2336.87 | 0.529874 | 3.21972 | 16.5944 | 2.00852 | 0.000789924 | 5.76911e-05 | 1.53305e-05 | 1(Win) | true |
| simdjson (ondemand) | 725.215 | 0.0667733 | 1241.93ms | 3873 | 640 | 7401.97 | 5093.08 | 0.0288464 | 6.97639 | 27.4216 | 3.45624 | 0.0175538 | 8.63349e-05 | 3.67125e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1459.93 | 0.0437745 | 6940.18ms | 94653 | 320 | 234422 | 61830.5 | 0.000692422 | 3.45952 | 15.1491 | 2.99554 | 0.00959653 | 1.05979e-05 | 7.03227e-06 | 1(Win) | true |
| simdjson (ondemand) | 1203.02 | 0.0763813 | 4223.85ms | 94653 | 80 | 262779 | 75034.9 | 0.0962144 | 4.20247 | 16.2851 | 3.13542 | 0.0149718 | 2.60161e-05 | 1.59794e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2124.02 | 0.0217209 | 6235.67ms | 94653 | 1280 | 109072 | 42498.6 | 0.0228295 | 2.38008 | 11.2472 | 2.11338 | 0.00599829 | 2.92186e-06 | 4.9523e-07 | 1(Win) | true |
| simdjson (ondemand) | 1666.43 | 0.0499956 | 7456.39ms | 94653 | 320 | 234698 | 54168.6 | 0.0904997 | 3.03127 | 12.4048 | 2.2584 | 0.00982847 | 1.76632e-05 | 1.10932e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1890.9 | 0.0237903 | 7059.89ms | 124597 | 2560 | 572161 | 62840.4 | 0.11731 | 2.66258 | 11.9057 | 2.28447 | 0.00720348 | 2.05914e-05 | 1.41299e-05 | 1(Win) | true |
| simdjson (ondemand) | 1576.28 | 0.0395087 | 4254.72ms | 124597 | 640 | 567696 | 75383.3 | 0.0264619 | 3.19535 | 12.6624 | 2.39316 | 0.00997739 | 2.10428e-05 | 1.46723e-05 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2670.03 | 0.025616 | 6436.91ms | 124597 | 1280 | 166347 | 44503.2 | 0.15023 | 1.85823 | 8.95663 | 1.61945 | 0.00448406 | 1.18883e-05 | 8.14501e-06 | 1(Win) | true |
| simdjson (ondemand) | 2104.53 | 0.0152218 | 7678.2ms | 124597 | 4890 | 361198 | 56461.5 | 0.106522 | 2.36742 | 9.73234 | 1.73255 | 0.00741978 | 4.21974e-06 | 1.67575e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1101.42 | 0.0526302 | 4513.59ms | 94653 | 320 | 595368 | 81956.3 | 0.183738 | 4.58633 | 21.0717 | 4.2273 | 0.0141855 | 3.54254e-05 | 2.1559e-05 | 1(Win) | true |
| simdjson (ondemand) | 699.464 | 0.139308 | 7056.22ms | 94653 | 30 | 969636 | 129053 | 0.0181546 | 7.22278 | 35.2286 | 7.22994 | 0.014881 | 6.19808e-05 | 5.07115e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1485.47 | 0.052165 | 4120.23ms | 94653 | 320 | 321553 | 60767.6 | 0.187803 | 3.40129 | 17.2007 | 3.36746 | 0.00755477 | 2.50586e-05 | 1.5154e-05 | 1(Win) | true |
| simdjson (ondemand) | 813.896 | 0.0292415 | 6847.7ms | 94653 | 2560 | 2.6926e+06 | 110909 | 0.00969418 | 6.11163 | 31.3916 | 6.37854 | 0.0110595 | 1.25169e-05 | 6.70211e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1359.17 | 0.021855 | 4990.79ms | 124597 | 2560 | 934569 | 87424.8 | 0.231287 | 3.67553 | 16.5996 | 3.27997 | 0.00871419 | 8.38328e-06 | 4.27629e-06 | 1(Win) | true |
| simdjson (ondemand) | 896.367 | 0.0892031 | 7140.06ms | 124597 | 160 | 2.23729e+06 | 132563 | 0.00975105 | 5.53967 | 26.7695 | 5.44654 | 0.010348 | 5.46763e-06 | 2.15695e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1767.54 | 0.0187137 | 4449.29ms | 124597 | 2560 | 405169 | 67226.2 | 0.058698 | 2.81195 | 13.656 | 2.62656 | 0.00540539 | 4.32645e-06 | 1.12237e-06 | 1(Win) | true |
| simdjson (ondemand) | 1056.85 | 0.0445661 | 6853.16ms | 124597 | 640 | 1.60687e+06 | 112434 | 0.141465 | 4.69484 | 23.8605 | 4.80231 | 0.00824472 | 6.98502e-06 | 2.3576e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2360.94 | 0.0100856 | 4585.03ms | 94653 | 4890 | 72712.7 | 38234 | 0.015364 | 2.1023 | 9.45755 | 1.81557 | 0.00556821 | 5.95221e-06 | 2.27934e-06 | 1(Win) | true |
| simdjson (ondemand) | 1699.85 | 0.0527398 | 5925.6ms | 94653 | 320 | 250999 | 53103.5 | 0.0768956 | 2.92113 | 10.9617 | 2.03268 | 0.0120892 | 7.56051e-06 | 4.25898e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3133.44 | 0.0118059 | 4116.09ms | 94653 | 4890 | 56563.5 | 28808 | 0.0159096 | 1.5844 | 7.55514 | 1.372 | 0.00376837 | 3.70528e-06 | 1.00032e-06 | 1(Win) | true |
| simdjson (ondemand) | 1980.67 | 0.0533558 | 5433.4ms | 94653 | 160 | 94608.2 | 45574.6 | 0.0527291 | 2.2642 | 9.07282 | 1.59309 | 0.00710503 | 3.69772e-06 | 9.24429e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2934.15 | 0.0590149 | 4775.75ms | 124597 | 320 | 182778 | 40497.2 | 0.329601 | 1.69709 | 7.62464 | 1.40276 | 0.00477647 | 2.45792e-06 | 5.26698e-07 | 1(Win) | true |
| simdjson (ondemand) | 2344.78 | 0.0167329 | 5811.49ms | 124597 | 2560 | 184075 | 50676.4 | 0.0532984 | 2.11942 | 8.34384 | 1.50153 | 0.00600981 | 3.66494e-06 | 1.17253e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3977.58 | 0.0156264 | 4239.91ms | 124597 | 4890 | 106562 | 29873.7 | 0.00745023 | 1.25332 | 6.17665 | 1.06426 | 0.00264494 | 2.47998e-06 | 4.52994e-07 | 1(Win) | true |
| simdjson (ondemand) | 2920.07 | 0.0360645 | 5305.83ms | 124597 | 640 | 137838 | 40692.5 | 0.141072 | 1.70255 | 6.91016 | 1.16823 | 0.0048386 | 1.0396e-05 | 6.5461e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1787.59 | 0.0680295 | 5819.14ms | 94653 | 320 | 377641 | 50497.2 | 0.0258992 | 2.81012 | 13.0719 | 2.53927 | 0.00741102 | 3.89581e-05 | 3.47321e-05 | 1(Win) | true |
| simdjson (ondemand) | 1536.6 | 0.0124193 | 6637.93ms | 94653 | 4890 | 260287 | 58745.5 | 0.0766075 | 3.22925 | 13.5859 | 2.55719 | 0.00832704 | 7.09512e-06 | 2.72657e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2153.96 | 0.0111118 | 5421.86ms | 94653 | 4890 | 106040 | 41908 | 0.0783173 | 2.30372 | 11.1921 | 2.11481 | 0.00648925 | 3.47194e-06 | 8.62044e-07 | 1(Win) | true |
| simdjson (ondemand) | 1814.44 | 0.0186344 | 6219.78ms | 94653 | 2560 | 220016 | 49749.9 | 0.0265492 | 2.73552 | 11.7349 | 2.14029 | 0.00771201 | 9.60746e-06 | 4.17231e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2166.65 | 0.0131835 | 6241.72ms | 124597 | 4890 | 255630 | 54842.7 | 0.0034669 | 2.29082 | 10.4326 | 1.96308 | 0.00580117 | 4.72197e-06 | 1.83167e-06 | 1(Win) | true |
| simdjson (ondemand) | 2015.86 | 0.0282809 | 6628.37ms | 124597 | 1280 | 355707 | 58945 | 0.044112 | 2.46526 | 10.3457 | 1.90176 | 0.00675418 | 3.3044e-06 | 6.64643e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2612.61 | 0.0228718 | 5784.58ms | 124597 | 2560 | 277016 | 45481.2 | 0.128888 | 1.90686 | 9.00717 | 1.64157 | 0.00499591 | 2.54257e-06 | 4.32645e-07 | 1(Win) | true |
| simdjson (ondemand) | 2417.1 | 0.0501629 | 6177.85ms | 124597 | 640 | 389199 | 49160.2 | 0.0788253 | 2.06841 | 8.92945 | 1.58321 | 0.00582049 | 2.60841e-06 | 4.76536e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 693.714 | 0.106402 | 4342.04ms | 2090234 | 40 | 3.73928e+08 | 2.87352e+06 | 0.307221 | 7.17039 | 32.616 | 6.35345 | 0.0228745 | 0.104864 | 0.000212763 | 1(Win) | true |
| simdjson (ondemand) | 654.162 | 0.406146 | 4579.19ms | 2090234 | 40 | 6.12695e+09 | 3.04726e+06 | 0.0275205 | 7.57358 | 31.4658 | 5.80658 | 0.0231709 | 0.105106 | 0.000412454 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 795.335 | 0.365327 | 4348.54ms | 2090234 | 80 | 6.70724e+09 | 2.50637e+06 | 0.0912615 | 6.23839 | 27.2941 | 5.06576 | 0.0220755 | 0.0795705 | 0.000211035 | 1(Win) | true |
| simdjson (ondemand) | 753.285 | 0.447175 | 4573.73ms | 2090234 | 40 | 5.60128e+09 | 2.64628e+06 | 0.186849 | 6.58764 | 26.1497 | 4.52004 | 0.022162 | 0.0802308 | 0.000377697 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1609.63 | 0.110121 | 4663.99ms | 5212421 | 30 | 3.46967e+08 | 3.08825e+06 | 0.509554 | 3.08623 | 13.874 | 2.5931 | 0.0100568 | 0.0614903 | 0.000673571 | 1(Win) | true |
| simdjson (ondemand) | 1541.48 | 0.35674 | 4840.95ms | 5212421 | 80 | 1.05876e+10 | 3.22479e+06 | 0.146629 | 3.21476 | 13.3546 | 2.36486 | 0.0101342 | 0.0614223 | 0.00249545 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1839.69 | 0.36748 | 4643.19ms | 5212421 | 80 | 7.88761e+09 | 2.70206e+06 | 0.280849 | 2.71826 | 11.7364 | 2.07604 | 0.00962769 | 0.0512512 | 0.00205439 | 1(Win) | true |
| simdjson (ondemand) | 1760.02 | 0.236597 | 4820.29ms | 5212421 | 30 | 1.33963e+09 | 2.82438e+06 | 0.996115 | 2.82284 | 11.2167 | 1.8477 | 0.00981799 | 0.0512066 | 0.00209074 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 644.96 | 0.336163 | 4649.12ms | 2090234 | 80 | 8.63604e+09 | 3.09074e+06 | 0.0830495 | 7.68394 | 35.6442 | 6.99095 | 0.0227557 | 0.156664 | 0.00155382 | 1(Win) | true |
| simdjson (ondemand) | 600.201 | 0.30512 | 4987.82ms | 2090234 | 80 | 8.2154e+09 | 3.32122e+06 | 0.0117147 | 8.25472 | 35.7851 | 6.76641 | 0.0229811 | 0.181456 | 0.00210451 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 738.501 | 0.442734 | 4645.63ms | 2090234 | 40 | 5.71262e+09 | 2.69926e+06 | 0.158854 | 6.71093 | 30.3328 | 5.70527 | 0.0218217 | 0.130853 | 0.000548683 | 1(Win) | true |
| simdjson (ondemand) | 682.473 | 0.482882 | 4965.36ms | 2090234 | 80 | 1.59144e+10 | 2.92085e+06 | 0.0810026 | 7.26102 | 30.469 | 5.47994 | 0.0219779 | 0.155594 | 0.00127003 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1464.18 | 0.49752 | 5175.06ms | 5212421 | 40 | 1.14122e+10 | 3.39504e+06 | 0.254101 | 3.38736 | 15.0917 | 2.84952 | 0.0100325 | 0.101016 | 0.00260613 | 1(Win) | true |
| simdjson (ondemand) | 1343.14 | 0.355778 | 5597.15ms | 5212421 | 80 | 1.38702e+10 | 3.70099e+06 | 0.243917 | 3.68878 | 15.0834 | 2.74905 | 0.0101643 | 0.120899 | 0.00469803 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1644.56 | 0.435567 | 5125.58ms | 5212421 | 80 | 1.38669e+10 | 3.02266e+06 | 0.104462 | 3.01364 | 12.9558 | 2.33279 | 0.0096588 | 0.0907803 | 0.00237626 | 1(Win) | true |
| simdjson (ondemand) | 1516.15 | 0.728614 | 5535.65ms | 5212421 | 30 | 1.71202e+10 | 3.27866e+06 | 0.0574143 | 3.26787 | 12.9486 | 2.23253 | 0.00978832 | 0.110707 | 0.00317868 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7717.15 | 0.0557904 | 6882.34ms | 2090234 | 80 | 1.66144e+06 | 258308 | 0.0502393 | 0.642246 | 3.25155 | 0.398874 | 0.00267437 | 0.0506733 | 3.82134e-06 | 1(Win) | true |
| simdjson (ondemand) | 6749.71 | 0.209654 | 7665.27ms | 2090234 | 40 | 1.53351e+07 | 295331 | 0.138423 | 0.736168 | 3.49786 | 0.418407 | 0.00320291 | 0.0493774 | 7.89385e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7724.06 | 0.094752 | 6817.82ms | 2090234 | 30 | 1.79389e+06 | 258077 | 0.11504 | 0.64178 | 3.25147 | 0.398856 | 0.0026716 | 0.0506137 | 2.34424e-06 | 1(Win) | true |
| simdjson (ondemand) | 6939.75 | 0.184125 | 7661.2ms | 2090234 | 40 | 1.11889e+07 | 287244 | 0.0325991 | 0.71424 | 3.49778 | 0.41839 | 0.0026894 | 0.0492309 | 7.05663e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10796.8 | 0.0840883 | 5980.16ms | 5212421 | 40 | 5.99541e+06 | 460409 | 0.0269398 | 0.459444 | 1.95585 | 0.183251 | 0.00197765 | 0.0394079 | 3.53962e-06 | 1(Win) | true |
| simdjson (ondemand) | 9637.38 | 0.044549 | 6599.21ms | 5212421 | 80 | 4.22403e+06 | 515799 | 0.360753 | 0.514237 | 2.1329 | 0.202785 | 0.00208106 | 0.0394838 | 1.22112e-05 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10781 | 0.0587507 | 6000.34ms | 5212421 | 40 | 2.93525e+06 | 461084 | 0.102003 | 0.459663 | 1.95582 | 0.183244 | 0.00195118 | 0.0393989 | 6.84423e-06 | 1(Win) | true |
| simdjson (ondemand) | 9905.18 | 0.158402 | 6500.57ms | 5212421 | 40 | 2.52776e+07 | 501854 | 0.0337563 | 0.505088 | 2.13287 | 0.202778 | 0.00180679 | 0.0394792 | 1.61729e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5941.13 | 0.0472409 | 4415.71ms | 2090234 | 80 | 2.00992e+06 | 335526 | 0.0281018 | 0.849811 | 4.69134 | 0.718823 | 0.00265916 | 0.0757429 | 3.54027e-06 | 1(Win) | true |
| simdjson (ondemand) | 5423.33 | 0.2149 | 4786.16ms | 2090234 | 30 | 1.87177e+07 | 367561 | 0.124424 | 0.931469 | 4.93758 | 0.73834 | 0.00283061 | 0.0757596 | 1.9934e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5888.93 | 0.515489 | 4409.74ms | 2090234 | 640 | 1.94866e+09 | 338500 | 0.00500902 | 0.857437 | 4.69126 | 0.718805 | 0.00262081 | 0.0756894 | 3.22183e-06 | 1(Win) | true |
| simdjson (ondemand) | 5454.08 | 0.113668 | 4762.56ms | 2090234 | 80 | 1.38074e+07 | 365488 | 0.204832 | 0.926167 | 4.9375 | 0.738322 | 0.00273112 | 0.0756723 | 1.51897e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8619.48 | 0.320866 | 7439.59ms | 5212421 | 640 | 2.19152e+09 | 576712 | 0.050809 | 0.585671 | 2.53322 | 0.311555 | 0.00193185 | 0.0590817 | 2.32872e-05 | 1(Win) | true |
| simdjson (ondemand) | 7859.88 | 0.056145 | 4059.41ms | 5212421 | 40 | 5.04347e+06 | 632446 | 0.0574409 | 0.630581 | 2.71024 | 0.331081 | 0.00187572 | 0.059208 | 1.13815e-05 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8677.82 | 0.0729264 | 7494.85ms | 5212421 | 30 | 5.23538e+06 | 572834 | 0.0545294 | 0.582113 | 2.53319 | 0.311548 | 0.00194378 | 0.0590726 | 7.0089e-06 | 1(Win) | true |
| simdjson (ondemand) | 7861.03 | 0.421092 | 4045.61ms | 5212421 | 320 | 2.26895e+09 | 632354 | 0.460149 | 0.630418 | 2.71021 | 0.331074 | 0.00180671 | 0.0591753 | 1.01195e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1108.37 | 0.202017 | 5591.87ms | 500299 | 640 | 4.84004e+08 | 430474 | 0.204519 | 4.48356 | 18.1145 | 3.40041 | 0.0163068 | 0.0148222 | 1.85139e-05 | 1(Win) | true |
| simdjson (ondemand) | 1011.08 | 0.402866 | 6176.41ms | 500299 | 30 | 1.08426e+08 | 471894 | 0.23048 | 4.92788 | 18.5257 | 3.10761 | 0.0228621 | 0.0202949 | 1.13266e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1234.01 | 0.197129 | 5501.39ms | 500299 | 640 | 3.71798e+08 | 386645 | 0.0534022 | 4.03659 | 16.9653 | 3.12307 | 0.0111925 | 0.0121259 | 7.78597e-06 | 1(Win) | true |
| simdjson (ondemand) | 1113.75 | 0.189619 | 6017.78ms | 500299 | 160 | 1.05576e+08 | 428392 | 0.203382 | 4.46466 | 17.3891 | 2.83401 | 0.0176309 | 0.0171338 | 4.40986e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2277.59 | 0.079436 | 6260.5ms | 1151920 | 80 | 1.17441e+07 | 482333 | 0.130588 | 2.17705 | 8.63965 | 1.51387 | 0.00739018 | 0.0364385 | 8.6486e-06 | 1(Win) | true |
| simdjson (ondemand) | 2154.17 | 0.138415 | 6600.67ms | 1151920 | 160 | 7.97207e+07 | 509967 | 0.192075 | 2.30005 | 8.73321 | 1.38343 | 0.0102965 | 0.0379897 | 1.02329e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2506.5 | 0.213321 | 6120.84ms | 1151920 | 40 | 3.49652e+07 | 438283 | 0.0472292 | 1.96746 | 8.13906 | 1.39241 | 0.00491482 | 0.0321658 | 6.0117e-06 | 1(Win) | true |
| simdjson (ondemand) | 2353.19 | 0.243658 | 6489.8ms | 1151920 | 640 | 8.28075e+08 | 466836 | 0.00591614 | 2.1091 | 8.23666 | 1.26385 | 0.00823636 | 0.0344727 | 6.10123e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 647.369 | 0.0758427 | 4706.39ms | 500299 | 40 | 1.24981e+07 | 737018 | 0.27424 | 7.65963 | 36.8218 | 7.59545 | 0.0221521 | 0.0169358 | 3.28803e-05 | 1(Win) | true |
| simdjson (ondemand) | 386.894 | 0.32703 | 7794.59ms | 500299 | 80 | 1.30118e+09 | 1.23321e+06 | 0.255937 | 12.8164 | 65.7803 | 13.4746 | 0.037382 | 0.0222658 | 1.89637e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 693.075 | 0.201513 | 4582.29ms | 500299 | 320 | 6.1582e+08 | 688414 | 0.00745499 | 7.16345 | 35.6637 | 7.31621 | 0.0149315 | 0.0113498 | 1.62215e-05 | 1(Win) | true |
| simdjson (ondemand) | 402.862 | 0.127626 | 7698.58ms | 500299 | 160 | 3.65547e+08 | 1.18433e+06 | 0.190736 | 12.3098 | 64.6322 | 13.1997 | 0.031488 | 0.0156553 | 1.28173e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1376.33 | 0.11436 | 5113.72ms | 1151920 | 40 | 3.33281e+07 | 798180 | 0.397457 | 3.66172 | 17.1194 | 3.38739 | 0.00967016 | 0.0447483 | 3.82622e-05 | 1(Win) | true |
| simdjson (ondemand) | 873.603 | 0.0546501 | 8003.22ms | 1151920 | 40 | 1.88911e+07 | 1.2575e+06 | 0.0897836 | 5.78181 | 29.216 | 5.87728 | 0.016646 | 0.100559 | 9.59268e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1460.69 | 0.153123 | 5005.75ms | 1151920 | 40 | 5.30481e+07 | 752083 | 0.295957 | 3.44768 | 16.6182 | 3.26636 | 0.00719531 | 0.0402836 | 1.02438e-05 | 1(Win) | true |
| simdjson (ondemand) | 905.669 | 0.0730485 | 7971.18ms | 1151920 | 30 | 2.35532e+07 | 1.21298e+06 | 0.0998045 | 5.57794 | 28.7175 | 5.75795 | 0.0144967 | 0.0928592 | 9.86758e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5178.32 | 0.0331683 | 5090.33ms | 500299 | 1280 | 1.19547e+06 | 92138.4 | 0.00629278 | 0.974512 | 5.41232 | 0.739652 | 0.000949562 | 7.56891e-06 | 6.33059e-06 | 1(Win) | true |
| simdjson (ondemand) | 4889.28 | 0.0749744 | 5385.2ms | 500299 | 40 | 214119 | 97585.3 | 0.0146133 | 1.03359 | 5.51545 | 0.737187 | 0.00107616 | 6.50111e-05 | 5.99641e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5234.09 | 0.0289903 | 5045.52ms | 500299 | 1280 | 893908 | 91156.8 | 0.00291385 | 0.965501 | 5.38328 | 0.73285 | 0.000916555 | 9.75979e-06 | 6.65227e-06 | 1(Win) | true |
| simdjson (ondemand) | 4942.68 | 0.0331703 | 5358.54ms | 500299 | 640 | 656166 | 96531.1 | 0.0120947 | 1.02136 | 5.48641 | 0.730385 | 0.00104529 | 4.90425e-05 | 9.88784e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8355.59 | 0.302317 | 7139.24ms | 1151920 | 2560 | 4.0444e+08 | 131476 | 0.152308 | 0.596334 | 3.03879 | 0.35415 | 0.000894996 | 0.0106415 | 1.55074e-06 | 1(Win) | true |
| simdjson (ondemand) | 8151.3 | 0.0395254 | 7320.42ms | 1151920 | 320 | 908018 | 134771 | 0.1222 | 0.609427 | 3.08041 | 0.353254 | 0.00111625 | 0.0143873 | 1.09057e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8350.98 | 0.203764 | 7176.27ms | 1151920 | 320 | 2.29919e+07 | 131548 | 0.206114 | 0.59611 | 3.02617 | 0.351196 | 0.000867839 | 0.00985186 | 3.79801e-07 | 1(Win) | true |
| simdjson (ondemand) | 8245.6 | 0.0904618 | 7221.78ms | 1151920 | 80 | 1.16204e+06 | 133229 | 0.00834018 | 0.603251 | 3.0678 | 0.3503 | 0.00108712 | 0.0136789 | 3.28799e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2875.31 | 0.0698012 | 4406.72ms | 500299 | 160 | 2.14652e+06 | 165938 | 0.0868247 | 1.72797 | 9.82389 | 1.77031 | 0.00220118 | 2.31112e-06 | 1.24925e-06 | 1(Win) | true |
| simdjson (ondemand) | 2661 | 0.212907 | 4730.01ms | 500299 | 160 | 2.33168e+07 | 179302 | 0.0160702 | 1.86776 | 10.1892 | 1.76464 | 0.0022348 | 7.16571e-05 | 4.37239e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2933.39 | 0.0562112 | 4375.32ms | 500299 | 320 | 2.67495e+06 | 162652 | 0.0526402 | 1.7133 | 9.79485 | 1.76351 | 0.00214321 | 2.16121e-06 | 4.80962e-07 | 1(Win) | true |
| simdjson (ondemand) | 2666.26 | 0.114445 | 4729.62ms | 500299 | 1280 | 5.36857e+07 | 178948 | 0.142535 | 1.85802 | 10.1601 | 1.75784 | 0.00218267 | 2.81894e-05 | 5.859e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5466.55 | 0.0561244 | 5306.22ms | 1151920 | 40 | 508841 | 200960 | 0.0636975 | 0.906758 | 4.97928 | 0.804948 | 0.00154054 | 0.0108321 | 1.34558e-05 | 1(Win) | true |
| simdjson (ondemand) | 5173.42 | 0.266157 | 5619.58ms | 1151920 | 80 | 2.55538e+07 | 212346 | 0.226087 | 0.961532 | 5.11029 | 0.799494 | 0.00170147 | 0.0144311 | 5.67531e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5570.83 | 0.0770813 | 5283.54ms | 1151920 | 160 | 3.69678e+06 | 197198 | 0.146113 | 0.899104 | 4.96666 | 0.801993 | 0.00143762 | 0.0101151 | 4.88315e-07 | 1(Win) | true |
| simdjson (ondemand) | 5163.99 | 0.276248 | 5627.99ms | 1151920 | 1280 | 4.4206e+08 | 212734 | 0.20677 | 0.962391 | 5.09767 | 0.79654 | 0.00157134 | 0.013858 | 1.15636e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1332.01 | 0.100474 | 4798.7ms | 56369 | 4890 | 8.04051e+06 | 40358.3 | 0.00890056 | 3.72115 | 15.8168 | 3.15864 | 0.00858699 | 2.11577e-05 | 8.98984e-06 | 1(Win) | true |
| simdjson (ondemand) | 1110.28 | 0.0168034 | 5605.15ms | 56369 | 4890 | 323683 | 48418.3 | 0.0336518 | 4.46698 | 16.7955 | 2.96269 | 0.0180575 | 1.83316e-05 | 7.47702e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1696.01 | 0.0230664 | 4275.7ms | 56369 | 2560 | 136843 | 31696.5 | 0.0301053 | 2.92785 | 13.515 | 2.6552 | 0.00502438 | 1.70473e-05 | 1.12678e-05 | 1(Win) | true |
| simdjson (ondemand) | 1339.62 | 0.047127 | 5074.78ms | 56369 | 640 | 228896 | 40129.1 | 0.361864 | 3.70485 | 14.5331 | 2.46981 | 0.014444 | 6.31996e-06 | 1.49683e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1882.17 | 0.0186114 | 5007.86ms | 83958 | 4890 | 306529 | 42540.6 | 0.0225019 | 2.64706 | 11.1428 | 2.13297 | 0.00607014 | 7.08797e-06 | 2.51367e-06 | 1(Win) | true |
| simdjson (ondemand) | 1709.66 | 0.028895 | 5424.03ms | 83958 | 1280 | 234403 | 46833.2 | 0.0065354 | 2.90652 | 11.6926 | 2.00891 | 0.00725718 | 5.8437e-06 | 2.09368e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2349.06 | 0.0277645 | 4510.32ms | 83958 | 1280 | 114637 | 34085.3 | 0.027025 | 2.11883 | 9.60347 | 1.79662 | 0.0039492 | 5.06205e-06 | 1.07941e-06 | 1(Win) | true |
| simdjson (ondemand) | 1941.9 | 0.0541818 | 5078.12ms | 83958 | 640 | 319417 | 41232.1 | 0.016146 | 2.57424 | 10.175 | 1.67842 | 0.0097671 | 3.10795e-06 | 2.97768e-07 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 683.879 | 0.0255647 | 4403.95ms | 56369 | 2560 | 1.03382e+06 | 78607 | 0.099047 | 7.2868 | 34.9316 | 7.2809 | 0.0118087 | 2.29861e-05 | 1.07273e-05 | 1(Win) | true |
| simdjson (ondemand) | 182.405 | 0.120884 | 7664.65ms | 56369 | 80 | 1.01538e+07 | 294715 | 0.0365304 | 27.1823 | 145.933 | 30.9533 | 0.0414346 | 2.0623e-05 | 8.42662e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 753.232 | 0.0517972 | 4202.97ms | 56369 | 1280 | 1.74923e+06 | 71369.3 | 0.0576465 | 6.6266 | 32.6469 | 6.78746 | 0.00981445 | 1.13233e-05 | 2.14823e-06 | 1(Win) | true |
| simdjson (ondemand) | 189.253 | 0.0474477 | 7541.73ms | 56369 | 1280 | 2.32508e+07 | 284053 | 0.055649 | 26.4034 | 143.687 | 30.4705 | 0.0370098 | 2.05953e-05 | 7.87223e-06 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 907.526 | 0.0306887 | 4889.87ms | 83958 | 2560 | 1.87673e+06 | 88227.3 | 0.0348879 | 5.51049 | 25.118 | 5.23281 | 0.0100199 | 1.07848e-05 | 2.87997e-06 | 1(Win) | true |
| simdjson (ondemand) | 271.531 | 0.0853989 | 7685.09ms | 83958 | 320 | 2.02928e+07 | 294879 | 0.0686866 | 18.3762 | 98.0778 | 20.7361 | 0.0285519 | 4.74195e-05 | 3.02979e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 995.937 | 0.181502 | 4675.48ms | 83958 | 80 | 1.70339e+06 | 80395.2 | 0.128219 | 5.06525 | 23.5958 | 4.90382 | 0.0085985 | 6.69978e-06 | 1.04219e-06 | 1(Win) | true |
| simdjson (ondemand) | 280.416 | 0.0895827 | 7567.42ms | 83958 | 320 | 2.09371e+07 | 285535 | 0.121758 | 17.8234 | 96.5655 | 20.4115 | 0.0251602 | 3.02979e-05 | 1.2469e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2260.44 | 0.0190161 | 3133.23ms | 56369 | 4890 | 100010 | 23781.9 | 0.0141035 | 2.20832 | 9.98566 | 1.78682 | 0.0036962 | 7.50242e-06 | 2.46332e-06 | 1(Win) | true |
| simdjson (ondemand) | 2092.99 | 0.0363158 | 3301.27ms | 56369 | 640 | 55682.4 | 25684.6 | 0.022461 | 2.37277 | 10.3254 | 1.74372 | 0.00441727 | 5.48839e-06 | 1.27508e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2830.76 | 0.0210279 | 2930.99ms | 56369 | 4890 | 77978.9 | 18990.6 | 0.166806 | 1.75728 | 8.35168 | 1.43185 | 0.00269381 | 5.05361e-06 | 1.32417e-06 | 1(Win) | true |
| simdjson (ondemand) | 2633.46 | 0.0303024 | 3077.96ms | 56369 | 2560 | 97953.7 | 20413.3 | 0.0686044 | 1.89621 | 8.71543 | 1.39692 | 0.00299505 | 3.9777e-06 | 8.87012e-07 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3108.31 | 0.0332701 | 3302.26ms | 83958 | 1280 | 94014 | 25759.5 | 0.0553131 | 1.60742 | 7.20966 | 1.22327 | 0.00249038 | 5.3133e-06 | 1.40509e-06 | 1(Win) | true |
| simdjson (ondemand) | 2940.36 | 0.105702 | 3446.55ms | 83958 | 80 | 66279.5 | 27230.9 | 0.0189159 | 1.68798 | 7.35568 | 1.19249 | 0.00341093 | 3.42433e-06 | 2.97768e-07 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3866.85 | 0.0648746 | 3158.77ms | 83958 | 320 | 57744.4 | 20706.4 | 0.112425 | 1.3032 | 6.11784 | 0.986803 | 0.00192511 | 2.8288e-06 | 1.11663e-07 | 1(Win) | true |
| simdjson (ondemand) | 3709.41 | 0.0262833 | 3219.92ms | 83958 | 4890 | 157393 | 21585.3 | 0.282305 | 1.35396 | 6.27176 | 0.958813 | 0.00197064 | 3.12261e-06 | 5.87011e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1853.94 | 0.0430456 | 3647.63ms | 56369 | 640 | 99707.1 | 28996.4 | 0.0392244 | 2.71623 | 13.416 | 2.50961 | 0.00382693 | 3.99156e-06 | 6.65259e-07 | 1(Win) | true |
| simdjson (ondemand) | 1254.84 | 0.0246808 | 5045.62ms | 56369 | 4890 | 546676 | 42840.1 | 0.0124817 | 3.97972 | 18.4623 | 3.35511 | 0.00846056 | 5.91704e-06 | 1.05571e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2209.01 | 0.0167708 | 3483.4ms | 56369 | 2560 | 42641.8 | 24335.6 | 0.0217564 | 2.2887 | 11.8297 | 2.16862 | 0.00329835 | 3.48568e-06 | 4.85085e-07 | 1(Win) | true |
| simdjson (ondemand) | 1421.55 | 0.0265515 | 4836.49ms | 56369 | 4890 | 492996 | 37816.3 | 0.247673 | 3.55191 | 16.9042 | 3.02276 | 0.0077587 | 6.66801e-06 | 1.46203e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2514.19 | 0.0500949 | 3918.43ms | 83958 | 640 | 162889 | 31846.6 | 0.0224319 | 2.00398 | 9.73895 | 1.73799 | 0.00315893 | 3.7221e-06 | 7.81641e-07 | 1(Win) | true |
| simdjson (ondemand) | 1878.24 | 0.113994 | 4994.25ms | 83958 | 320 | 755675 | 42629.6 | 0.209588 | 2.69302 | 12.6755 | 2.24527 | 0.00566433 | 6.40201e-06 | 8.56083e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2977.93 | 0.00980119 | 3725.27ms | 83958 | 4890 | 33959.6 | 26887.4 | 0.0163534 | 1.69952 | 8.67169 | 1.50854 | 0.00241756 | 3.13722e-06 | 5.96754e-07 | 1(Win) | true |
| simdjson (ondemand) | 2057.98 | 0.0331762 | 4923ms | 83958 | 2560 | 426514 | 38906.4 | 0.469372 | 2.43798 | 11.6395 | 2.02404 | 0.00505073 | 9.36108e-06 | 5.4017e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1279.72 | 0.0339499 | 4730.61ms | 53331 | 2560 | 466065 | 39743.4 | 0.0219424 | 3.91615 | 13.9135 | 2.77018 | 0.0125397 | 2.60461e-05 | 7.9398e-06 | 1(Win) | true |
| simdjson (ondemand) | 949.477 | 0.050602 | 6143.22ms | 53331 | 1280 | 940451 | 53566.8 | 0.0975055 | 5.30162 | 19.257 | 3.76693 | 0.0211583 | 3.90251e-05 | 1.01518e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1571.84 | 0.0320084 | 4520.45ms | 53331 | 2560 | 274606 | 32357.2 | 0.190844 | 3.17282 | 11.6908 | 2.26159 | 0.0101525 | 1.18658e-05 | 5.12718e-06 | 1(Win) | true |
| simdjson (ondemand) | 1122.36 | 0.0334446 | 5866.25ms | 53331 | 2560 | 588014 | 45315.7 | 0.250143 | 4.49813 | 17.0784 | 3.26916 | 0.0171826 | 1.46637e-05 | 5.35424e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1469.74 | 0.0315746 | 4965.87ms | 65103 | 2560 | 455450 | 42243.7 | 0.0124273 | 3.42341 | 12.06 | 2.33043 | 0.0105502 | 2.42584e-05 | 9.72017e-06 | 1(Win) | true |
| simdjson (ondemand) | 1134.41 | 0.0712009 | 6203.64ms | 65103 | 640 | 971879 | 54730.7 | 0.147449 | 4.39374 | 15.9686 | 3.08702 | 0.0178419 | 2.20084e-05 | 1.07522e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1790.84 | 0.0242588 | 4758.84ms | 65103 | 4890 | 345887 | 34669.2 | 0.0964049 | 2.79131 | 10.24 | 1.91397 | 0.00801903 | 1.12768e-05 | 3.26995e-06 | 1(Win) | true |
| simdjson (ondemand) | 1337.44 | 0.0265557 | 5980.69ms | 65103 | 4890 | 743158 | 46422.4 | 0.0173194 | 3.7449 | 14.1853 | 2.68067 | 0.0149156 | 1.06485e-05 | 2.90557e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 931.429 | 0.0611955 | 6209.65ms | 53331 | 640 | 714627 | 54604.7 | 0.0109067 | 5.37103 | 19.5594 | 3.92919 | 0.0168045 | 3.63297e-05 | 1.6905e-05 | 1(Win) | true |
| simdjson (ondemand) | 376.887 | 0.13329 | 7290.38ms | 53331 | 1280 | 4.14138e+07 | 134949 | 0.0335245 | 13.3267 | 44.8004 | 9.05859 | 0.09641 | 0.000128414 | 6.55107e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1109.07 | 0.0252494 | 5903.83ms | 53331 | 2560 | 343228 | 45858.6 | 0.024921 | 4.5478 | 17.2624 | 3.40326 | 0.0135995 | 1.59748e-05 | 6.19656e-06 | 1(Win) | true |
| simdjson (ondemand) | 410.276 | 0.0752387 | 7105.02ms | 53331 | 1280 | 1.11352e+07 | 123966 | 0.302458 | 12.3036 | 42.567 | 8.54954 | 0.0874866 | 1.88827e-05 | 8.21813e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1063.03 | 0.144298 | 6596.59ms | 65103 | 80 | 568227 | 58405.6 | 0.0720699 | 4.74671 | 16.9688 | 3.38599 | 0.0146178 | 3.01445e-05 | 1.80483e-05 | 1(Win) | true |
| simdjson (ondemand) | 477.998 | 0.13491 | 7115.17ms | 65103 | 320 | 9.82631e+06 | 129890 | 0.503994 | 10.5636 | 36.6075 | 7.36702 | 0.0709619 | 2.45764e-05 | 9.79218e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1228.83 | 0.0384015 | 6389.36ms | 65103 | 1280 | 481863 | 50525.3 | 0.233054 | 4.08457 | 15.0938 | 2.95796 | 0.011819 | 7.95614e-06 | 2.73605e-06 | 1(Win) | true |
| simdjson (ondemand) | 506.579 | 0.143797 | 6948.6ms | 65103 | 320 | 9.93932e+06 | 122561 | 0.294914 | 9.80885 | 34.7711 | 6.94898 | 0.0656714 | 1.43043e-05 | 5.4241e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7618.03 | 0.0554763 | 1410.9ms | 53331 | 320 | 4389.75 | 6676.32 | 0.000702113 | 0.655168 | 3.00544 | 0.421612 | 0.000786773 | 3.69157e-06 | 4.10174e-07 | 1(Win) | true |
| simdjson (ondemand) | 6492.5 | 0.0766264 | 1528.63ms | 53331 | 640 | 23060.7 | 7833.72 | 0.14408 | 0.777464 | 3.35805 | 0.437048 | 0.00110659 | 2.43175e-06 | 2.05087e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8497.1 | 0.0265953 | 1357.38ms | 53331 | 4890 | 12391.9 | 5985.62 | 0.0787459 | 0.593609 | 2.8394 | 0.384767 | 0.00073109 | 3.27085e-06 | 6.32696e-07 | 1(Win) | true |
| simdjson (ondemand) | 6945.39 | 0.0788468 | 1492.75ms | 53331 | 640 | 21336.1 | 7322.9 | 0.243558 | 0.724434 | 3.19615 | 0.401249 | 0.00102359 | 2.51964e-06 | 1.17193e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8307.13 | 0.0284341 | 1488.02ms | 65103 | 2560 | 11561.6 | 7473.95 | 0.0708471 | 0.610647 | 2.83141 | 0.360644 | 0.000725707 | 2.23204e-06 | 1.68003e-07 | 1(Win) | true |
| simdjson (ondemand) | 7294.46 | 0.0237532 | 1600.04ms | 65103 | 4890 | 19987.9 | 8511.53 | 0.0260352 | 0.684679 | 2.99269 | 0.369384 | 0.000798342 | 3.57778e-06 | 6.59644e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9010.26 | 0.0321245 | 1443.46ms | 65103 | 1280 | 6272.07 | 6890.7 | 0.00721132 | 0.564259 | 2.69539 | 0.330461 | 0.000590687 | 2.25604e-06 | 3.48006e-07 | 1(Win) | true |
| simdjson (ondemand) | 7776.3 | 0.044844 | 1561.14ms | 65103 | 1280 | 16408.7 | 7984.14 | 0.0935258 | 0.64275 | 2.86008 | 0.340061 | 0.000777938 | 2.29204e-06 | 9.60017e-08 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5487.19 | 0.0244124 | 1672.48ms | 53331 | 2560 | 13107.5 | 9268.93 | 0.0253555 | 0.908232 | 4.38214 | 0.711781 | 0.00176655 | 2.73938e-06 | 1.90438e-07 | 1(Win) | true |
| simdjson (ondemand) | 3793.89 | 0.0521459 | 2086.07ms | 53331 | 1280 | 62551.9 | 13405.9 | 0.16409 | 1.31492 | 6.01826 | 0.993119 | 0.00251066 | 5.42016e-06 | 1.75789e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5857.31 | 0.0551845 | 1631.27ms | 53331 | 640 | 14695.2 | 8683.23 | 0.0371268 | 0.852147 | 4.21794 | 0.67548 | 0.00160073 | 4.21893e-06 | 2.05087e-06 | 1(Win) | true |
| simdjson (ondemand) | 3928.45 | 0.116214 | 2056.97ms | 53331 | 320 | 72440.6 | 12946.7 | 0.0318995 | 1.2662 | 5.85643 | 0.957361 | 0.00255087 | 4.39472e-06 | 5.85963e-08 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6061.38 | 0.0198185 | 1772.13ms | 65103 | 4890 | 20151.6 | 10243.1 | 0.115228 | 0.823559 | 3.95209 | 0.606209 | 0.00144153 | 2.12342e-06 | 9.42348e-08 | 1(Win) | true |
| simdjson (ondemand) | 4428.57 | 0.0454761 | 2150.46ms | 65103 | 1280 | 52029.7 | 14019.7 | 0.193982 | 1.12489 | 5.17265 | 0.825231 | 0.00201769 | 6.10811e-06 | 3.10806e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6397.79 | 0.068973 | 1735.63ms | 65103 | 640 | 28673.5 | 9704.46 | 0.0448771 | 0.780646 | 3.81979 | 0.576901 | 0.0013105 | 2.37604e-06 | 1.20002e-07 | 1(Win) | true |
| simdjson (ondemand) | 4678.54 | 0.0830402 | 2090.76ms | 65103 | 320 | 38860.6 | 13270.6 | 0.0601313 | 1.0829 | 5.04008 | 0.795939 | 0.00199525 | 3.26406e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1265.95 | 0.0385025 | 1632.45ms | 11812 | 1280 | 15024.5 | 8898.27 | 0.0801392 | 4.00928 | 18.3068 | 3.56015 | 0.00591923 | 2.65884e-05 | 1.04502e-05 | 1(Win) | true |
| simdjson (ondemand) | 1026.99 | 0.0361944 | 1841.84ms | 11812 | 1280 | 20174.8 | 10968.8 | 0.0014815 | 4.93818 | 20.2335 | 3.67288 | 0.00798539 | 4.39833e-05 | 1.81225e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.03 | 0.0362052 | 1617.5ms | 11812 | 4890 | 43716.9 | 8258.45 | 0.0716241 | 3.70039 | 17.2085 | 3.3135 | 0.00537279 | 1.91307e-05 | 2.21604e-06 | 1(Win) | true |
| simdjson (ondemand) | 1097.35 | 0.0175445 | 1818.12ms | 11812 | 4890 | 15861.6 | 10265.5 | 0.0422364 | 4.62154 | 19.1473 | 3.42923 | 0.00738049 | 1.88537e-05 | 2.04291e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2397.76 | 0.0315352 | 1749.97ms | 25388 | 1280 | 12979.2 | 10097.7 | 0.00478164 | 2.11599 | 9.39334 | 1.71613 | 0.00292938 | 1.38784e-05 | 5.0159e-06 | 1(Win) | true |
| simdjson (ondemand) | 2121.76 | 0.0465455 | 1882.46ms | 25388 | 640 | 18055.1 | 11411.2 | 0.0314011 | 2.39022 | 10.0314 | 1.73499 | 0.00370168 | 7.6931e-06 | 1.10781e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2569.67 | 0.0637497 | 1732.69ms | 25388 | 320 | 11545.4 | 9422.18 | 0.0968846 | 1.97529 | 8.89869 | 1.60481 | 0.00267597 | 8.00083e-06 | 8.61628e-07 | 1(Win) | true |
| simdjson (ondemand) | 2274.8 | 0.0991073 | 1863.43ms | 25388 | 320 | 35606.9 | 10643.5 | 0.0135627 | 2.24884 | 9.51706 | 1.61994 | 0.00328686 | 1.28013e-05 | 4.43123e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.63 | 0.0195431 | 2229.66ms | 11812 | 2560 | 21672.4 | 14888.1 | 0.00945946 | 6.69678 | 30.1959 | 6.02299 | 0.0153417 | 7.83433e-05 | 3.69725e-05 | 1(Win) | true |
| simdjson (ondemand) | 663.411 | 0.0492472 | 2434.65ms | 11812 | 640 | 44753.2 | 16980.1 | 0.0913561 | 7.616 | 33.2773 | 6.31739 | 0.0147895 | 1.6006e-05 | 1.71965e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.899 | 0.0298738 | 2223.6ms | 11812 | 1280 | 23232.4 | 14261.1 | 0.0883674 | 6.40909 | 29.1183 | 5.78149 | 0.0154507 | 1.9776e-05 | 4.23298e-06 | 1(Win) | true |
| simdjson (ondemand) | 693.66 | 0.0288696 | 2417.33ms | 11812 | 2560 | 56269.7 | 16239.7 | 0.0750299 | 7.29463 | 32.1985 | 6.07603 | 0.0152429 | 1.80563e-05 | 1.85193e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1525.36 | 0.0174117 | 2332.01ms | 25388 | 2560 | 19553.8 | 15872.9 | 0.0708009 | 3.32112 | 15.0043 | 2.92949 | 0.00713192 | 8.01621e-06 | 8.77014e-07 | 1(Win) | true |
| simdjson (ondemand) | 1401.87 | 0.0322192 | 2468.45ms | 25388 | 1280 | 39635.1 | 17271.1 | 0.0178708 | 3.61061 | 15.9437 | 2.93353 | 0.00652135 | 3.72346e-05 | 1.76941e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1598.65 | 0.0351282 | 2307.87ms | 25388 | 640 | 18115.2 | 15145.2 | 0.0365967 | 3.1696 | 14.4617 | 2.80849 | 0.00669897 | 7.63156e-06 | 1.10781e-06 | 1(Win) | true |
| simdjson (ondemand) | 1458.86 | 0.056229 | 2448.87ms | 25388 | 320 | 27867.5 | 16596.4 | 0.125844 | 3.47212 | 15.4468 | 2.82224 | 0.00648215 | 5.53903e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2234.09 | 0.0244687 | 1240.62ms | 11812 | 4890 | 7443.49 | 5042.24 | 0.0538004 | 2.2778 | 10.63 | 1.94988 | 0.00331838 | 1.32962e-05 | 2.89124e-06 | 1(Win) | true |
| simdjson (ondemand) | 1926.45 | 0.0317013 | 1320.83ms | 11812 | 2560 | 8796.81 | 5847.44 | 0.0426487 | 2.64072 | 11.7376 | 1.97968 | 0.00490996 | 1.08139e-05 | 9.25965e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2290.45 | 0.0397764 | 1232.11ms | 11812 | 2560 | 9797.04 | 4918.16 | 0.0396412 | 2.22369 | 10.4434 | 1.90442 | 0.00304342 | 8.89588e-06 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 1964.96 | 0.0586078 | 1319.46ms | 11812 | 640 | 7224.87 | 5732.84 | 0.0463554 | 2.59056 | 11.5295 | 1.92999 | 0.00523594 | 9.12737e-06 | 3.96842e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4171.01 | 0.0434943 | 1315.75ms | 25388 | 1280 | 8159.22 | 5804.8 | 0.0294967 | 1.21976 | 5.74382 | 0.963566 | 0.0019053 | 5.72367e-06 | 5.23131e-07 | 1(Win) | true |
| simdjson (ondemand) | 3797.59 | 0.0341919 | 1370.83ms | 25388 | 2560 | 12165.4 | 6375.59 | 0.0311956 | 1.33876 | 6.08496 | 0.94974 | 0.0021853 | 6.10832e-06 | 1.2309e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4274.57 | 0.0208255 | 1310.4ms | 25388 | 4890 | 6804.14 | 5664.17 | 0.0650943 | 1.19061 | 5.65696 | 0.942414 | 0.00185299 | 8.82822e-06 | 2.71452e-06 | 1(Win) | true |
| simdjson (ondemand) | 3863.09 | 0.0277979 | 1371.82ms | 25388 | 4890 | 14843 | 6267.5 | 0.0571145 | 1.31663 | 5.99811 | 0.928589 | 0.00218732 | 7.52332e-06 | 8.53824e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1733.6 | 0.0413455 | 1387.45ms | 11812 | 1280 | 9238.77 | 6497.91 | 0.0225003 | 2.93257 | 14.1546 | 2.63419 | 0.00766236 | 1.19714e-05 | 1.12439e-06 | 1(Win) | true |
| simdjson (ondemand) | 1603.24 | 0.025618 | 1433.71ms | 11812 | 4890 | 15843.4 | 7026.26 | 0.052354 | 3.16821 | 14.3958 | 2.47587 | 0.00809812 | 1.10629e-05 | 8.82954e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1769.89 | 0.0343272 | 1381.31ms | 11812 | 4890 | 23342 | 6364.67 | 0.0292204 | 2.87214 | 13.9679 | 2.58872 | 0.00718073 | 1.62221e-05 | 1.38503e-06 | 1(Win) | true |
| simdjson (ondemand) | 1625.93 | 0.0406002 | 1436.37ms | 11812 | 2560 | 20255.4 | 6928.24 | 0.0403924 | 3.12535 | 14.2091 | 2.43041 | 0.00799488 | 1.31619e-05 | 1.28974e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3241.23 | 0.0760088 | 1485.19ms | 25388 | 640 | 20632.2 | 7469.97 | 0.0487967 | 1.56716 | 7.312 | 1.30168 | 0.00296603 | 4.86204e-06 | 6.15448e-08 | 1(Win) | true |
| simdjson (ondemand) | 3187.62 | 0.13042 | 1493.59ms | 25388 | 30 | 2943.97 | 7595.6 | 0.13936 | 1.59579 | 7.33169 | 1.18257 | 0.00348721 | 1.18166e-05 | 2.62591e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3302.18 | 0.0425493 | 1478.52ms | 25388 | 2560 | 24916 | 7332.09 | 0.0143653 | 1.53879 | 7.22515 | 1.28053 | 0.00280494 | 7.12381e-06 | 5.53903e-07 | 1(Win) | true |
| simdjson (ondemand) | 3240.51 | 0.0955067 | 1491.32ms | 25388 | 320 | 16294.7 | 7471.62 | 0.0135113 | 1.56734 | 7.24484 | 1.16142 | 0.00338693 | 7.38538e-06 | 2.46179e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1484.1 | 0.0195677 | 7698.5ms | 108313 | 4890 | 907029 | 69601.2 | 0.0284294 | 3.39984 | 15.0237 | 3.02583 | 0.00415542 | 1.12225e-05 | 2.9982e-06 | 1(Win) | true |
| simdjson (ondemand) | 1369.06 | 0.06572 | 4229.02ms | 108313 | 320 | 786798 | 75449.9 | 0.0331815 | 3.69117 | 16.4878 | 2.64599 | 0.00767885 | 4.96824e-05 | 2.49278e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1611.23 | 0.0502289 | 7342.21ms | 108313 | 4890 | 5.07064e+06 | 64109.6 | 0.0228808 | 3.13427 | 14.2949 | 2.85736 | 0.00356588 | 8.38666e-06 | 3.59482e-06 | 1(Win) | true |
| simdjson (ondemand) | 1477.51 | 0.0387375 | 4052.6ms | 108313 | 1280 | 938805 | 69911.9 | 0.0505993 | 3.4168 | 15.762 | 2.47789 | 0.00722136 | 7.94861e-06 | 1.9042e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2265.43 | 0.0318552 | 4332.38ms | 183677 | 1280 | 776569 | 77322.3 | 0.177651 | 2.22851 | 9.65157 | 1.84231 | 0.00228902 | 4.50434e-06 | 1.46317e-06 | 1(Win) | true |
| simdjson (ondemand) | 2226.92 | 0.0632203 | 4399.73ms | 183677 | 320 | 791339 | 78659.2 | 0.0954158 | 2.2701 | 10.2445 | 1.58327 | 0.00484985 | 3.41973e-06 | 7.6561e-07 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2444.58 | 0.0359675 | 4133.35ms | 183677 | 1280 | 850225 | 71655.8 | 0.159305 | 2.06419 | 9.22469 | 1.74354 | 0.00192815 | 7.34561e-06 | 4.41502e-06 | 1(Win) | true |
| simdjson (ondemand) | 2383.99 | 0.140695 | 4263.69ms | 183677 | 80 | 854968 | 73476.8 | 0.185828 | 2.11989 | 9.81877 | 1.4847 | 0.00452758 | 2.17774e-06 | 4.08325e-07 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 621.392 | 0.0990888 | 4429.97ms | 108313 | 160 | 4.3411e+06 | 166232 | 0.089247 | 8.0753 | 38.1172 | 7.6572 | 0.0116859 | 2.19272e-05 | 1.09059e-05 | 1(Win) | true |
| simdjson (ondemand) | 215.148 | 0.110847 | 6218.28ms | 108313 | 160 | 4.53162e+07 | 480112 | 0.143556 | 23.478 | 107.583 | 22.8261 | 0.0890764 | 0.000224811 | 0.000144546 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 645.942 | 0.155554 | 4348.29ms | 108313 | 30 | 1.85635e+06 | 159914 | 0.000625339 | 7.79791 | 37.3866 | 7.48946 | 0.0110433 | 2.3389e-05 | 8.617e-06 | 1(Win) | true |
| simdjson (ondemand) | 218.548 | 0.0945201 | 6121.4ms | 108313 | 320 | 6.38657e+07 | 472644 | 0.052497 | 22.9538 | 106.863 | 22.6606 | 0.0835527 | 4.18925e-05 | 1.47143e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 969.73 | 0.0442172 | 4803.56ms | 183677 | 640 | 4.08291e+06 | 180636 | 0.0185646 | 5.20172 | 24.1755 | 4.79112 | 0.00543006 | 1.45891e-05 | 5.12108e-06 | 1(Win) | true |
| simdjson (ondemand) | 370.548 | 0.123712 | 6115.94ms | 183677 | 80 | 2.7361e+07 | 472726 | 0.178352 | 13.6425 | 63.1956 | 13.3243 | 0.0478758 | 4.23297e-05 | 3.33466e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1006 | 0.0438853 | 4679.49ms | 183677 | 160 | 934267 | 174123 | 0.0332341 | 5.0233 | 23.7488 | 4.69301 | 0.00511108 | 2.44655e-05 | 2.14711e-05 | 1(Win) | true |
| simdjson (ondemand) | 375.183 | 0.0802233 | 6046.01ms | 183677 | 640 | 8.9785e+07 | 466886 | 0.0129237 | 13.46 | 62.7716 | 13.2268 | 0.0470445 | 2.27216e-05 | 8.73646e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4707.43 | 0.166957 | 2953.63ms | 108313 | 160 | 214745 | 21943 | 0.239401 | 1.07046 | 5.56097 | 0.855549 | 0.00117299 | 2.48123e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4187 | 0.0182371 | 3213.12ms | 108313 | 4890 | 98986.3 | 24670.5 | 0.156073 | 1.20573 | 6.00632 | 0.842854 | 0.00126055 | 2.50543e-06 | 6.41933e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4819.01 | 0.0206683 | 2892.31ms | 108313 | 4890 | 95976.2 | 21434.9 | 0.0394237 | 1.03658 | 5.37634 | 0.806468 | 0.0007157 | 3.16813e-06 | 4.39913e-07 | 1(Win) | true |
| simdjson (ondemand) | 4406.59 | 0.0221376 | 3110.56ms | 108313 | 2560 | 68937.6 | 23441.1 | 0.0764748 | 1.14787 | 5.82216 | 0.793885 | 0.0010398 | 1.96551e-06 | 4.43593e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6708.59 | 0.0423088 | 3359.87ms | 183677 | 1280 | 156214 | 26111 | 0.0147559 | 0.745265 | 3.88658 | 0.538244 | 0.000525264 | 2.90081e-06 | 5.52941e-07 | 1(Win) | true |
| simdjson (ondemand) | 6150.48 | 0.0742149 | 3573.2ms | 183677 | 320 | 142963 | 28480.4 | 0.0247148 | 0.806749 | 4.05667 | 0.518813 | 0.000775903 | 6.19294e-06 | 3.16452e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7034.16 | 0.192806 | 3255.24ms | 183677 | 30 | 69158.5 | 24902.5 | 0.00803069 | 0.713028 | 3.77793 | 0.509345 | 0.000417581 | 1.6333e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6494.39 | 0.147596 | 3450.78ms | 183677 | 4890 | 7.74978e+06 | 26972.2 | 0.0947625 | 0.770076 | 3.94808 | 0.489936 | 0.000627677 | 2.45719e-06 | 7.04758e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3272.36 | 0.0804451 | 3912.28ms | 108313 | 1280 | 825367 | 31566 | 0.0466453 | 1.52628 | 8.21896 | 1.4444 | 0.00202722 | 1.81765e-06 | 1.29832e-07 | 1(Win) | true |
| simdjson (ondemand) | 2542.89 | 0.0511574 | 4807.04ms | 108313 | 1280 | 552755 | 40621.2 | 0.103656 | 1.96611 | 10.4327 | 1.80158 | 0.00215514 | 4.15463e-06 | 1.21177e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3361.89 | 0.0860487 | 3818.18ms | 108313 | 1280 | 894734 | 30725.4 | 0.0697461 | 1.47908 | 8.03371 | 1.39557 | 0.00177721 | 5.10673e-06 | 2.66877e-06 | 1(Win) | true |
| simdjson (ondemand) | 2633.79 | 0.0670201 | 4685.41ms | 108313 | 1280 | 884343 | 39219.3 | 0.140786 | 1.90388 | 10.2474 | 1.75274 | 0.0018352 | 4.85428e-06 | 2.09174e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4528.86 | 0.0402956 | 4601.72ms | 183677 | 4890 | 1.18784e+06 | 38678.2 | 0.0780401 | 1.11113 | 5.61138 | 0.89903 | 0.000888851 | 2.55183e-06 | 7.28139e-07 | 1(Win) | true |
| simdjson (ondemand) | 3906.94 | 0.102848 | 5178.66ms | 183677 | 320 | 680416 | 44835 | 0.140091 | 1.27201 | 6.6529 | 1.08137 | 0.00129543 | 3.3857e-06 | 4.59366e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4661.16 | 0.0413161 | 4518.7ms | 183677 | 4890 | 1.17888e+06 | 37580.4 | 0.352589 | 1.07227 | 5.50209 | 0.870213 | 0.000743938 | 2.06751e-06 | 8.03847e-07 | 1(Win) | true |
| simdjson (ondemand) | 4029.38 | 0.114397 | 5086.68ms | 183677 | 640 | 1.58286e+06 | 43472.7 | 0.107197 | 1.24273 | 6.5436 | 1.05255 | 0.00112517 | 3.45375e-06 | 1.87149e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 585.537 | 0.371901 | 4473.81ms | 1834197 | 80 | 9.87483e+09 | 2.98739e+06 | 0.0285301 | 8.43162 | 36.4996 | 7.32558 | 0.0375989 | 0.13875 | 0.00179914 | 1(Win) | true |
| simdjson (ondemand) | 544.458 | 0.512114 | 4854.03ms | 1834197 | 30 | 8.12114e+09 | 3.21278e+06 | 0.297148 | 9.25846 | 36.888 | 6.54753 | 0.044247 | 0.139268 | 0.0262505 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 632.484 | 0.334725 | 4524.35ms | 1834197 | 80 | 6.85584e+09 | 2.76565e+06 | 0.0917297 | 7.80932 | 33.5071 | 6.6264 | 0.0364075 | 0.117991 | 0.00725497 | 1(Win) | true |
| simdjson (ondemand) | 590.097 | 0.257909 | 4796.27ms | 1834197 | 40 | 2.33796e+09 | 2.9643e+06 | 0.426368 | 8.38266 | 33.8959 | 5.84808 | 0.0431792 | 0.118355 | 0.00179067 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2095.7 | 0.691479 | 5002.52ms | 7351818 | 30 | 1.60551e+10 | 3.34554e+06 | 0.0328887 | 2.39961 | 9.96471 | 1.86807 | 0.0102281 | 0.0588386 | 0.00703205 | 1(Win) | true |
| simdjson (ondemand) | 1986.45 | 0.343597 | 5305.21ms | 7351818 | 80 | 1.17658e+10 | 3.52953e+06 | 0.320074 | 2.49262 | 10.1182 | 1.67354 | 0.0107327 | 0.058822 | 0.00706648 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2309.93 | 0.0960294 | 5013.89ms | 7351818 | 30 | 2.54871e+08 | 3.03526e+06 | 0.363376 | 2.18197 | 9.21794 | 1.69355 | 0.00995075 | 0.0536036 | 0.00272483 | 1(Win) | true |
| simdjson (ondemand) | 2128.66 | 0.445666 | 5337.52ms | 7351818 | 80 | 1.72379e+10 | 3.29373e+06 | 0.0539587 | 2.32555 | 9.37173 | 1.49906 | 0.0104786 | 0.053601 | 0.00626496 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 380.826 | 0.371217 | 6908.06ms | 1834197 | 30 | 8.72199e+09 | 4.59324e+06 | 0.139799 | 13.016 | 63.8659 | 13.4327 | 0.0378287 | 0.3449 | 0.00970367 | 1(Win) | true |
| simdjson (ondemand) | 252.169 | 0.348772 | 4862.48ms | 1834197 | 40 | 2.34127e+10 | 6.93672e+06 | 0.0666974 | 19.6706 | 104.899 | 21.4608 | 0.0489559 | 0.789525 | 0.00697123 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 404.136 | 0.478929 | 6855.34ms | 1834197 | 30 | 1.28914e+10 | 4.32831e+06 | 0.0525023 | 12.2809 | 60.8743 | 12.7332 | 0.0366484 | 0.323241 | 0.00375485 | 1(Win) | true |
| simdjson (ondemand) | 261.617 | 0.43136 | 4858.21ms | 1834197 | 40 | 3.32736e+10 | 6.68621e+06 | 0.0142968 | 19.0581 | 101.909 | 20.762 | 0.0478613 | 0.768159 | 0.010021 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1303.66 | 0.422641 | 8124.7ms | 7351818 | 40 | 2.06662e+10 | 5.3781e+06 | 0.0287986 | 3.7934 | 16.9626 | 3.39987 | 0.0103188 | 0.186846 | 0.00420908 | 1(Win) | true |
| simdjson (ondemand) | 845.172 | 0.549541 | 5798.56ms | 7351818 | 30 | 6.23478e+10 | 8.29564e+06 | 0.378729 | 5.87014 | 27.0855 | 5.39411 | 0.0120969 | 0.436499 | 0.00943199 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1308.12 | 0.699607 | 8378.66ms | 7351818 | 30 | 4.21816e+10 | 5.35978e+06 | 0.388526 | 3.77044 | 16.2167 | 3.22557 | 0.0100444 | 0.181512 | 0.00763692 | 1(Win) | true |
| simdjson (ondemand) | 885.024 | 0.53902 | 5713.79ms | 7351818 | 30 | 5.47029e+10 | 7.92209e+06 | 0.958516 | 5.63518 | 26.3399 | 5.2199 | 0.0118121 | 0.431146 | 0.00627675 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4654.49 | 0.202373 | 4926.52ms | 1834197 | 40 | 2.31374e+07 | 375815 | 0.390163 | 1.07147 | 6.28016 | 0.838107 | 0.0018879 | 0.0755249 | 1.44477e-06 | 1(Win) | true |
| simdjson (ondemand) | 4141.46 | 0.117512 | 5461.58ms | 1834197 | 30 | 7.39042e+06 | 422369 | 0.0714498 | 1.19968 | 6.33081 | 0.867858 | 0.00370338 | 0.075125 | 4.76139e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4599.56 | 0.405901 | 4932.56ms | 1834197 | 640 | 1.52503e+09 | 380303 | 0.0343067 | 1.08052 | 6.27994 | 0.838058 | 0.00193894 | 0.0754931 | 1.46011e-06 | 1(Win) | true |
| simdjson (ondemand) | 4248.46 | 0.0263981 | 5410.29ms | 1834197 | 160 | 1.89015e+06 | 411732 | 0.0984955 | 1.18889 | 6.33059 | 0.867809 | 0.0031323 | 0.0751126 | 1.23692e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9981.94 | 0.130402 | 4537.64ms | 7351818 | 40 | 3.35573e+07 | 702392 | 0.0168797 | 0.49687 | 2.37653 | 0.241968 | 0.00127427 | 0.0423905 | 3.02748e-05 | 1(Win) | true |
| simdjson (ondemand) | 9332.51 | 0.469502 | 4782.2ms | 7351818 | 320 | 3.98124e+09 | 751271 | 0.353579 | 0.534575 | 2.49479 | 0.256659 | 0.000758014 | 0.0424339 | 0.000280282 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9855.96 | 0.144383 | 4555.01ms | 7351818 | 40 | 4.21974e+07 | 711371 | 0.117328 | 0.502496 | 2.37647 | 0.241956 | 0.00128123 | 0.0423851 | 0.000114948 | 1(Win) | true |
| simdjson (ondemand) | 9415.18 | 0.193934 | 4828.53ms | 7351818 | 30 | 6.25691e+07 | 744674 | 0.195366 | 0.530686 | 2.49474 | 0.256647 | 0.00077379 | 0.0424265 | 0.000262221 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3278.78 | 0.342283 | 6916.53ms | 1834197 | 640 | 2.13411e+09 | 533499 | 0.0438205 | 1.52863 | 8.73487 | 1.53934 | 0.00194086 | 0.113177 | 5.72884e-06 | 1(Win) | true |
| simdjson (ondemand) | 2375.62 | 0.132472 | 4720.06ms | 1834197 | 40 | 3.80581e+07 | 736326 | 0.45985 | 2.11329 | 12.6416 | 2.2702 | 0.00338054 | 0.150575 | 1.50202e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3318.45 | 0.0835054 | 6881.39ms | 1834197 | 40 | 7.75017e+06 | 527122 | 0.280003 | 1.52089 | 8.73465 | 1.53929 | 0.00194671 | 0.113144 | 4.22528e-06 | 1(Win) | true |
| simdjson (ondemand) | 2372.98 | 0.166183 | 4742.36ms | 1834197 | 30 | 4.50193e+07 | 737144 | 0.165919 | 2.10812 | 12.6414 | 2.27015 | 0.00314953 | 0.150483 | 1.24123e-05 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7529.74 | 0.538851 | 5951.87ms | 7351818 | 160 | 4.02798e+09 | 931140 | 0.162007 | 0.661674 | 3.0764 | 0.41692 | 0.00123291 | 0.063562 | 0.000150216 | 1(Win) | true |
| simdjson (ondemand) | 5605.33 | 2.30605 | 8151.51ms | 7351818 | 30 | 2.49602e+10 | 1.25082e+06 | 0.233724 | 0.884921 | 4.06926 | 0.606527 | 0.000830244 | 0.0847969 | 0.000911575 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7192.04 | 0.388425 | 6202.34ms | 7351818 | 80 | 1.14707e+09 | 974862 | 0.357191 | 0.692622 | 3.07634 | 0.416908 | 0.00127457 | 0.0635558 | 0.000649307 | 1(Win) | true |
| simdjson (ondemand) | 5647.54 | 0.391564 | 7746.67ms | 7351818 | 320 | 7.56185e+09 | 1.24147e+06 | 0.882648 | 0.877135 | 4.06921 | 0.606515 | 0.000758025 | 0.0847778 | 0.00111081 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1158.44 | 0.180169 | 4376.48ms | 409725 | 30 | 1.10795e+07 | 337301 | 0.0966044 | 4.27721 | 18.8038 | 3.72271 | 0.0102075 | 0.0200827 | 0.00012187 | 1(Win) | true |
| simdjson (ondemand) | 952.108 | 0.150578 | 5307.1ms | 409725 | 30 | 1.14566e+07 | 410399 | 0.0995193 | 5.20612 | 20.7351 | 3.86175 | 0.0164442 | 0.0377911 | 3.01828e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1443.75 | 0.0732538 | 4126.9ms | 409725 | 80 | 3.1445e+06 | 270646 | 0.0529425 | 3.43142 | 15.824 | 3.05218 | 0.0067801 | 0.00416706 | 3.44133e-05 | 1(Win) | true |
| simdjson (ondemand) | 1149.03 | 0.101738 | 5056.93ms | 409725 | 160 | 1.91517e+07 | 340064 | 0.104355 | 4.33 | 17.7599 | 3.19224 | 0.0123667 | 0.0126563 | 8.08469e-07 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1880.85 | 0.075815 | 4472.12ms | 676745 | 30 | 2.03037e+06 | 343140 | 0.107217 | 2.68441 | 11.9869 | 2.27908 | 0.00695146 | 0.0313535 | 5.32451e-05 | 1(Win) | true |
| simdjson (ondemand) | 1522.68 | 0.0910826 | 5517.31ms | 676745 | 160 | 2.38465e+07 | 423855 | 0.132721 | 3.31797 | 13.0773 | 2.36426 | 0.012008 | 0.0389566 | 4.46993e-06 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2333.99 | 0.0467243 | 4228.9ms | 676745 | 80 | 1.33546e+06 | 276520 | 0.00277112 | 2.16514 | 10.1822 | 1.87298 | 0.00475388 | 0.0177828 | 4.0451e-06 | 1(Win) | true |
| simdjson (ondemand) | 1806.61 | 0.151475 | 5273.9ms | 676745 | 80 | 2.34259e+07 | 357241 | 0.247377 | 2.79608 | 11.2766 | 1.95905 | 0.00958799 | 0.0241824 | 1.11748e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 802.317 | 0.052047 | 6311.62ms | 409725 | 40 | 2.57007e+06 | 487020 | 0.0215352 | 6.29641 | 28.9839 | 5.85129 | 0.0131049 | 0.0218242 | 1.30575e-05 | 1(Win) | true |
| simdjson (ondemand) | 406.404 | 0.0921478 | 6124.93ms | 409725 | 80 | 6.27957e+07 | 961468 | 0.127185 | 12.4309 | 53.4607 | 10.7301 | 0.0414235 | 0.0483314 | 0.00015846 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 928.325 | 0.0614764 | 6064.66ms | 409725 | 30 | 2.00873e+06 | 420913 | 0.0185515 | 5.44256 | 26.0123 | 5.17868 | 0.0090996 | 0.00501475 | 2.13151e-05 | 1(Win) | true |
| simdjson (ondemand) | 439.56 | 0.193846 | 6012.93ms | 409725 | 160 | 4.75097e+08 | 888943 | 0.136047 | 11.4929 | 50.4952 | 10.0589 | 0.0361891 | 0.0134059 | 9.31722e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.65 | 0.298469 | 6884.96ms | 676745 | 640 | 1.62834e+09 | 534421 | 0.0683648 | 4.11014 | 18.5438 | 3.7147 | 0.00854526 | 0.0314484 | 7.82237e-06 | 1(Win) | true |
| simdjson (ondemand) | 646.965 | 0.217135 | 6334.87ms | 676745 | 320 | 1.50141e+09 | 997572 | 0.0608082 | 7.68072 | 32.6982 | 6.48382 | 0.0263667 | 0.0476931 | 2.42567e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1382.15 | 0.333396 | 6605.64ms | 676745 | 320 | 7.75558e+08 | 466951 | 0.0419187 | 3.59909 | 16.7465 | 3.30765 | 0.00638998 | 0.0170788 | 1.23477e-05 | 1(Win) | true |
| simdjson (ondemand) | 698.297 | 0.192914 | 6191.98ms | 676745 | 320 | 1.0173e+09 | 924241 | 0.0518247 | 7.10524 | 30.9036 | 6.07765 | 0.0237127 | 0.0265685 | 1.12256e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2322.14 | 0.0381178 | 4475.88ms | 409725 | 320 | 1.31648e+06 | 168269 | 0.0544439 | 2.13507 | 9.83406 | 1.85346 | 0.0057161 | 6.20309e-05 | 7.32198e-06 | 1(Win) | true |
| simdjson (ondemand) | 1863.9 | 0.0820466 | 5557.55ms | 409725 | 160 | 4.7335e+06 | 209638 | 0.000286208 | 2.6782 | 11.1123 | 1.95253 | 0.00694225 | 0.000841967 | 4.94234e-06 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2709.3 | 0.0530571 | 4355.94ms | 409725 | 320 | 1.87374e+06 | 144223 | 0.287105 | 1.8378 | 8.81337 | 1.61922 | 0.00444084 | 8.38977e-06 | 4.01184e-06 | 1(Win) | true |
| simdjson (ondemand) | 2085.57 | 0.0774586 | 5448.95ms | 409725 | 640 | 1.34789e+07 | 187356 | 0.0704536 | 2.37785 | 10.0943 | 1.71644 | 0.00575884 | 0.000334016 | 4.83937e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3338.01 | 0.0461048 | 5134.59ms | 676745 | 80 | 635710 | 193347 | 0.0361718 | 1.48552 | 6.59088 | 1.16369 | 0.00451817 | 0.00276005 | 3.26933e-06 | 1(Win) | true |
| simdjson (ondemand) | 2857.26 | 0.147224 | 5978.75ms | 676745 | 40 | 4.42351e+06 | 225878 | 0.0185348 | 1.74867 | 7.12803 | 1.18313 | 0.00549287 | 0.00389279 | 4.95017e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3834 | 0.189447 | 5013.63ms | 676745 | 640 | 6.5088e+07 | 168335 | 0.0279564 | 1.29695 | 5.97303 | 1.02184 | 0.00323541 | 0.00179909 | 5.19029e-06 | 1(Win) | true |
| simdjson (ondemand) | 3179.47 | 0.072519 | 5916.65ms | 676745 | 30 | 650079 | 202988 | 0.0485321 | 1.55889 | 6.51282 | 1.04048 | 0.00460144 | 0.00219053 | 1.00481e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1820.48 | 0.0606573 | 5680.91ms | 409725 | 80 | 1.35603e+06 | 214638 | 0.046545 | 2.72056 | 12.8595 | 2.47521 | 0.00922973 | 3.73116e-05 | 5.67454e-06 | 1(Win) | true |
| simdjson (ondemand) | 1388.51 | 0.0695007 | 7304.87ms | 409725 | 30 | 1.14759e+06 | 281412 | 0.180653 | 3.57035 | 15.7787 | 2.92774 | 0.00831468 | 0.00389749 | 1.31796e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2046.54 | 0.0237441 | 5552.26ms | 409725 | 1280 | 2.63067e+06 | 190929 | 0.0312697 | 2.41512 | 11.8394 | 2.23932 | 0.00742666 | 1.49414e-05 | 3.47413e-06 | 1(Win) | true |
| simdjson (ondemand) | 1546.53 | 0.199971 | 7161.83ms | 409725 | 30 | 7.65812e+06 | 252658 | 0.00658291 | 3.24654 | 14.7587 | 2.68987 | 0.00664535 | 0.002293 | 1.56202e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2604.68 | 0.128465 | 6535.29ms | 676745 | 640 | 6.48471e+07 | 247782 | 0.121809 | 1.9381 | 8.53503 | 1.55745 | 0.00603416 | 0.00165019 | 1.25324e-05 | 1(Win) | true |
| simdjson (ondemand) | 2204.78 | 0.0678029 | 7671.33ms | 676745 | 160 | 6.30285e+06 | 292725 | 0.225638 | 2.28148 | 10.0086 | 1.78477 | 0.00591829 | 0.0036024 | 5.56894e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2892.07 | 0.0321429 | 6403.53ms | 676745 | 80 | 411619 | 223160 | 0.133168 | 1.74712 | 7.9123 | 1.41342 | 0.00522311 | 0.000671745 | 5.67053e-06 | 1(Win) | true |
| simdjson (ondemand) | 2440.8 | 0.0257202 | 7458.57ms | 676745 | 320 | 1.48007e+06 | 264419 | 0.04501 | 2.06925 | 9.39125 | 1.64084 | 0.00450865 | 0.00247764 | 1.86185e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1732.89 | 0.0752498 | 7828ms | 264040 | 320 | 3.82612e+06 | 145311 | 0.0804418 | 2.91498 | 10.4773 | 1.98708 | 0.00976205 | 0.000123028 | 5.6135e-05 | 1(Win) | true |
| simdjson (ondemand) | 1560.59 | 0.0725512 | 4328.69ms | 264040 | 640 | 8.77062e+06 | 161354 | 0.149874 | 3.17126 | 11.1373 | 1.9015 | 0.0114815 | 0.000148237 | 4.20746e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2101.86 | 0.0654892 | 7019.75ms | 264040 | 640 | 3.93959e+06 | 119802 | 0.0484378 | 2.3892 | 9.04337 | 1.6567 | 0.00658503 | 1.58712e-05 | 1.10719e-05 | 1(Win) | true |
| simdjson (ondemand) | 1752.16 | 0.0608572 | 4274.72ms | 264040 | 1280 | 9.79096e+06 | 143713 | 0.0532447 | 2.82307 | 9.70901 | 1.57334 | 0.0135333 | 2.14722e-05 | 2.34635e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2187.65 | 0.0394784 | 4206.01ms | 360584 | 1280 | 4.9293e+06 | 157191 | 0.045724 | 2.26752 | 8.14136 | 1.46938 | 0.00791216 | 0.000114443 | 1.0441e-05 | 1(Win) | true |
| simdjson (ondemand) | 2055.96 | 0.103159 | 4465.25ms | 360584 | 1280 | 3.81077e+07 | 167260 | 0.154273 | 2.40848 | 8.50713 | 1.40909 | 0.00870342 | 0.00195914 | 1.80826e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2627.83 | 0.0269461 | 7830.49ms | 360584 | 2560 | 3.1831e+06 | 130861 | 0.0669471 | 1.8879 | 7.09351 | 1.22842 | 0.00591463 | 7.49544e-06 | 1.96404e-06 | 1(Win) | true |
| simdjson (ondemand) | 2297.14 | 0.135747 | 4423.79ms | 360584 | 1280 | 5.28577e+07 | 149699 | 0.168091 | 2.15251 | 7.46227 | 1.16972 | 0.0099958 | 0.000447302 | 3.27594e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 673.648 | 0.194064 | 4841.92ms | 264040 | 160 | 8.41944e+07 | 373798 | 0.191912 | 7.36139 | 28.3531 | 5.30146 | 0.0214049 | 0.00191744 | 1.29952e-05 | 1(Win) | true |
| simdjson (ondemand) | 246.775 | 0.0960835 | 6471.16ms | 264040 | 320 | 3.07599e+08 | 1.0204e+06 | 0.250196 | 19.9791 | 82.4398 | 16.6618 | 0.0942107 | 0.00208892 | 3.13399e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 715.801 | 0.0714091 | 4783.3ms | 264040 | 320 | 2.01935e+07 | 351785 | 0.0540929 | 6.92898 | 26.9347 | 4.97295 | 0.0206892 | 0.00024679 | 5.49159e-06 | 1(Win) | true |
| simdjson (ondemand) | 254.709 | 0.0923157 | 6378.16ms | 264040 | 320 | 2.66533e+08 | 988609 | 0.0586163 | 19.3715 | 81.0216 | 16.3348 | 0.0879143 | 0.000348207 | 1.24863e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 846.436 | 0.0741781 | 5278.36ms | 360584 | 640 | 5.81241e+07 | 406268 | 0.122376 | 5.85875 | 21.8181 | 4.06547 | 0.0175723 | 0.00246125 | 2.76375e-05 | 1(Win) | true |
| simdjson (ondemand) | 355.323 | 0.133779 | 6137.82ms | 360584 | 160 | 2.68202e+08 | 967796 | 0.115103 | 13.8854 | 60.0624 | 12.0822 | 0.0497609 | 0.00303782 | 2.01929e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 905.485 | 0.0860806 | 5124.49ms | 360584 | 320 | 3.41988e+07 | 379774 | 0.0302632 | 5.49041 | 20.7752 | 3.82399 | 0.0152929 | 0.000390894 | 2.16749e-05 | 1(Win) | true |
| simdjson (ondemand) | 366.499 | 0.238294 | 6054.59ms | 360584 | 40 | 1.99965e+08 | 938283 | 0.0988809 | 13.4759 | 59.0221 | 11.8423 | 0.0459327 | 0.000733879 | 7.69585e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7027.81 | 0.038711 | 4356.55ms | 264040 | 4890 | 940758 | 35830.2 | 0.116814 | 0.715897 | 3.48296 | 0.478712 | 0.000958854 | 5.42615e-06 | 3.1739e-06 | 1(Win) | true |
| simdjson (ondemand) | 5943.47 | 0.044126 | 4993.58ms | 264040 | 2560 | 894723 | 42367.2 | 0.0769114 | 0.847653 | 3.92811 | 0.470223 | 0.0011964 | 4.10094e-06 | 1.29449e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7252.31 | 0.069119 | 4269.48ms | 264040 | 1280 | 737211 | 34721.1 | 0.0440826 | 0.692548 | 3.39977 | 0.460002 | 0.000937098 | 1.74867e-06 | 6.00643e-07 | 1(Win) | true |
| simdjson (ondemand) | 6078.94 | 0.0445211 | 4953.65ms | 264040 | 2560 | 870673 | 41423.1 | 0.044262 | 0.82748 | 3.84482 | 0.451528 | 0.00119083 | 2.65407e-06 | 7.76693e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7701.55 | 0.0826407 | 5223.07ms | 360584 | 40 | 54463.4 | 44650.7 | 0.0111059 | 0.656634 | 3.00514 | 0.3735 | 0.00078151 | 5.54656e-07 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7270.65 | 0.172079 | 5532.06ms | 360584 | 40 | 264962 | 47297 | 0.0600998 | 0.695435 | 3.22755 | 0.36111 | 0.000875593 | 3.2586e-06 | 2.14929e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7883.95 | 0.0411781 | 5163.11ms | 360584 | 4890 | 1.57749e+06 | 43617.7 | 0.265631 | 0.63623 | 2.94422 | 0.3598 | 0.00070239 | 3.76179e-06 | 2.50446e-06 | 1(Win) | true |
| simdjson (ondemand) | 7434.72 | 0.0260888 | 5450.5ms | 360584 | 4890 | 712035 | 46253.2 | 0.0230755 | 0.678702 | 3.16656 | 0.347421 | 0.000865558 | 1.72352e-06 | 7.21393e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4852.93 | 0.0560379 | 5988.05ms | 264040 | 160 | 135274 | 51887.9 | 0.0664976 | 1.04174 | 5.318 | 0.865104 | 0.00163858 | 4.66312e-06 | 3.00617e-06 | 1(Win) | true |
| simdjson (ondemand) | 3664.65 | 0.0212785 | 7631.91ms | 264040 | 4890 | 1.04536e+06 | 68712.7 | 0.0479696 | 1.35177 | 6.58468 | 1.03005 | 0.00221311 | 3.4504e-06 | 1.34298e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4864.96 | 0.017836 | 5984.21ms | 264040 | 1280 | 109090 | 51759.5 | 0.0297241 | 1.01985 | 5.23901 | 0.847735 | 0.00160843 | 2.23984e-06 | 8.19596e-07 | 1(Win) | true |
| simdjson (ondemand) | 3739.24 | 0.0295489 | 7557.82ms | 264040 | 2560 | 1.01367e+06 | 67342.1 | 0.00547547 | 1.32488 | 6.50559 | 1.0127 | 0.00220401 | 2.14811e-06 | 5.04481e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5604.72 | 0.0320833 | 6880.61ms | 360584 | 640 | 247994 | 61355.3 | 0.00751203 | 0.885106 | 4.3741 | 0.665035 | 0.00129868 | 1.01398e-06 | 2.42662e-07 | 1(Win) | true |
| simdjson (ondemand) | 4617.67 | 0.0902079 | 4198.23ms | 360584 | 640 | 2.88826e+06 | 74470.3 | 0.0462973 | 1.07086 | 5.18364 | 0.773178 | 0.00162105 | 1.6293e-06 | 5.1999e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5719.52 | 0.0302061 | 6814.36ms | 360584 | 1280 | 422174 | 60123.8 | 0.0809545 | 0.866626 | 4.31531 | 0.652098 | 0.00126855 | 2.32045e-06 | 1.30647e-06 | 1(Win) | true |
| simdjson (ondemand) | 4734.51 | 0.101944 | 4147.19ms | 360584 | 40 | 219303 | 72632.6 | 0.00133092 | 1.04797 | 5.12573 | 0.760471 | 0.00157765 | 9.70648e-07 | 4.15992e-07 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1771.41 | 0.165709 | 893.221ms | 2632 | 80 | 441.076 | 1416.99 | 0.048542 | 2.88221 | 11.2633 | 2.13146 | 0.00099734 | 6.17401e-05 | 4.74924e-06 | 1(Win) | true |
| simdjson (ondemand) | 1504.86 | 0.053632 | 931.155ms | 2632 | 4890 | 3913.21 | 1667.97 | 0.0584715 | 3.37286 | 11.8644 | 2.15122 | 0.00438538 | 9.91416e-05 | 3.09235e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2227.85 | 0.0523476 | 867.146ms | 2632 | 4890 | 1700.99 | 1126.68 | 0.0180248 | 2.30748 | 9.23632 | 1.66489 | 0.000766793 | 5.09694e-05 | 1.181e-05 | 1(Win) | true |
| simdjson (ondemand) | 1824.22 | 0.0649703 | 892.005ms | 2632 | 1280 | 1022.95 | 1375.97 | 0.0735819 | 2.80287 | 10.1269 | 1.75076 | 0.00306415 | 6.17401e-05 | 2.07779e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2250.08 | 0.0396008 | 893.783ms | 3370 | 4890 | 1564.52 | 1428.34 | 0.0394273 | 2.26706 | 9.05371 | 1.64985 | 0.00067333 | 6.03788e-05 | 1.4321e-05 | 1(Win) | true |
| simdjson (ondemand) | 1926.52 | 0.081429 | 930.43ms | 3370 | 1280 | 2362.01 | 1668.23 | 0.270429 | 2.63762 | 9.54332 | 1.69199 | 0.00236508 | 9.18027e-05 | 2.96736e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2787.66 | 0.0532089 | 869.719ms | 3370 | 4890 | 1840.17 | 1152.9 | 0.0292569 | 1.84385 | 7.58694 | 1.31009 | 0.000896155 | 4.19921e-05 | 1.06194e-05 | 1(Win) | true |
| simdjson (ondemand) | 2340.71 | 0.0541093 | 892.643ms | 3370 | 4890 | 2699.08 | 1373.04 | 0.0591697 | 2.18172 | 8.18635 | 1.37923 | 0.001208 | 4.49048e-05 | 1.17117e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1210.3 | 0.0672023 | 954.422ms | 2632 | 2560 | 4972.74 | 2073.93 | 0.0788113 | 4.17857 | 16.6102 | 3.24772 | 0.00482552 | 0.000105225 | 4.86797e-05 | 1(Win) | true |
| simdjson (ondemand) | 684.181 | 0.0847115 | 1113.65ms | 2632 | 640 | 6181.51 | 3668.72 | 0.0280319 | 7.32458 | 31.6197 | 6.30091 | 0.0109369 | 4.74924e-05 | 8.90483e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1414.75 | 0.0423258 | 932.808ms | 2632 | 2560 | 1443.66 | 1774.22 | 0.0331682 | 3.59074 | 14.7306 | 2.81155 | 0.00464283 | 6.0256e-05 | 1.64739e-05 | 1(Win) | true |
| simdjson (ondemand) | 768.291 | 0.0718554 | 1083.1ms | 2632 | 1280 | 7054.23 | 3267.08 | 0.20025 | 6.73292 | 29.8807 | 5.89932 | 0.00920729 | 0.000111607 | 4.95702e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1415.09 | 0.0725036 | 969.873ms | 3370 | 320 | 867.681 | 2271.15 | 0.0556952 | 3.58232 | 13.6564 | 2.6368 | 0.00546087 | 3.15282e-05 | 1.8546e-06 | 1(Win) | true |
| simdjson (ondemand) | 872.294 | 0.0455616 | 1114.79ms | 3370 | 2560 | 7213.92 | 3684.4 | 0.0252076 | 5.7744 | 24.8223 | 4.89941 | 0.0093677 | 0.000102583 | 3.74397e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1673.53 | 0.046818 | 942.613ms | 3370 | 2560 | 2069.48 | 1920.43 | 0.0829565 | 3.04566 | 12.1884 | 2.29614 | 0.00349082 | 3.51215e-05 | 1.50686e-05 | 1(Win) | true |
| simdjson (ondemand) | 953.709 | 0.0445297 | 1094.19ms | 3370 | 2560 | 5764.57 | 3369.88 | 0.105898 | 5.28368 | 23.3481 | 4.56113 | 0.00777008 | 5.45948e-05 | 1.84301e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3001.58 | 0.0931176 | 826.998ms | 2632 | 320 | 194.038 | 836.25 | 0.0127039 | 1.73445 | 6.94111 | 1.25076 | 0.000439305 | 2.49335e-05 | 5.93655e-06 | 1(Win) | true |
| simdjson (ondemand) | 2279.07 | 0.0644301 | 853.779ms | 2632 | 4890 | 2462.32 | 1101.36 | 0.0354478 | 2.25966 | 8.24126 | 1.43313 | 0.00284745 | 4.49867e-05 | 1.71711e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3757.88 | 0.181701 | 810.347ms | 2632 | 1280 | 1885.44 | 667.948 | 0.00210528 | 1.40705 | 5.87424 | 0.997721 | 0.000772642 | 3.56193e-05 | 4.15559e-06 | 1(Win) | true |
| simdjson (ondemand) | 2800.12 | 0.0967991 | 829.229ms | 2632 | 1280 | 963.763 | 896.414 | 0.252332 | 1.86911 | 7.17439 | 1.18009 | 0.000762847 | 3.17605e-05 | 1.69192e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3619.26 | 0.0747512 | 831.43ms | 3370 | 4890 | 2154.59 | 887.994 | 0.0994992 | 1.43482 | 5.82463 | 0.998813 | 0.000396315 | 4.46621e-05 | 1.63842e-05 | 1(Win) | true |
| simdjson (ondemand) | 2905.87 | 0.0656888 | 852.891ms | 3370 | 640 | 337.807 | 1106 | 0.0224578 | 1.77096 | 6.51899 | 1.0908 | 0.00201641 | 1.90096e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4470.5 | 0.0644496 | 817.189ms | 3370 | 4890 | 1049.78 | 718.909 | 0.0807557 | 1.1726 | 4.99139 | 0.801187 | 0.000610827 | 5.08517e-05 | 1.36535e-05 | 1(Win) | true |
| simdjson (ondemand) | 3497.87 | 0.0493486 | 838.415ms | 3370 | 4890 | 1005.33 | 918.81 | 0.241949 | 1.48322 | 5.68576 | 0.893175 | 0.0011299 | 2.17849e-05 | 3.94434e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2161.5 | 0.0518371 | 859.832ms | 2632 | 4890 | 1771.95 | 1161.26 | 0.0285397 | 2.37254 | 9.5247 | 1.77584 | 0.00194111 | 4.60744e-05 | 1.33639e-05 | 1(Win) | true |
| simdjson (ondemand) | 1918.26 | 0.0537309 | 870.811ms | 2632 | 640 | 316.363 | 1308.52 | 0.058067 | 2.67094 | 10.1907 | 1.82143 | 0.00440492 | 3.68066e-05 | 7.12386e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2613.01 | 0.0689684 | 843.041ms | 2632 | 4890 | 2146.35 | 960.606 | 0.00734692 | 1.97927 | 8.46087 | 1.52546 | 0.00114199 | 3.8227e-05 | 1.04114e-05 | 1(Win) | true |
| simdjson (ondemand) | 2342.6 | 0.131232 | 853.431ms | 2632 | 80 | 158.177 | 1071.49 | 0.0967343 | 2.20204 | 9.1269 | 1.57105 | 0.00113982 | 0.000151976 | 4.74924e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2601.67 | 0.15732 | 853.935ms | 3370 | 640 | 2417.17 | 1235.32 | 0.0710089 | 1.96625 | 7.90059 | 1.42226 | 0.001977 | 3.24555e-05 | 1.8546e-05 | 1(Win) | true |
| simdjson (ondemand) | 2524.92 | 0.0683286 | 860.509ms | 3370 | 2560 | 1936.46 | 1272.86 | 0.0645886 | 2.06696 | 8.04154 | 1.39407 | 0.00283649 | 5.34356e-05 | 2.37621e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3194.94 | 0.0568293 | 837.852ms | 3370 | 4890 | 1598.04 | 1005.93 | 0.157521 | 1.64561 | 7.06973 | 1.22671 | 0.000907441 | 4.38732e-05 | 1.67483e-05 | 1(Win) | true |
| simdjson (ondemand) | 3059.67 | 0.118581 | 844.944ms | 3370 | 80 | 124.116 | 1050.4 | 0.021425 | 1.71871 | 7.21068 | 1.19852 | 0.000890208 | 1.8546e-05 | 0 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 693.233 | 0.0616449 | 1378.66ms | 4630 | 1280 | 19733.6 | 6369.45 | 0.0561694 | 7.3311 | 33.5579 | 6.44752 | 0.00450358 | 0.000131952 | 6.51323e-05 | 1(Win) | true |
| simdjson (ondemand) | 682.961 | 0.105803 | 1392.18ms | 4630 | 80 | 3743.3 | 6465.25 | 0.0919459 | 7.4518 | 32.613 | 5.9378 | 0.00634449 | 6.47948e-05 | 8.09935e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 805.68 | 0.045134 | 1387.39ms | 4630 | 2560 | 15663.4 | 5480.48 | 0.105635 | 6.26573 | 29.1205 | 5.41814 | 0.00322725 | 0.000145704 | 7.90531e-05 | 1(Win) | true |
| simdjson (ondemand) | 787.721 | 0.0276173 | 1395.1ms | 4630 | 4890 | 11718.9 | 5605.42 | 0.00617246 | 6.45433 | 28.1641 | 4.90734 | 0.00531658 | 7.63227e-05 | 2.65009e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1654.94 | 0.0629973 | 1406.56ms | 11579 | 80 | 1413.54 | 6672.49 | 0.0103024 | 3.0765 | 13.9825 | 2.57803 | 0.00262652 | 1.94317e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1590.39 | 0.0695208 | 1436.46ms | 11579 | 1280 | 29824.4 | 6943.31 | 0.162258 | 3.14198 | 13.7491 | 2.4053 | 0.00193818 | 5.33698e-05 | 2.32776e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1876.03 | 0.128381 | 1434.19ms | 11579 | 320 | 18273.1 | 5886.16 | 0.0197005 | 2.70003 | 12.4142 | 2.2071 | 0.0021966 | 3.10368e-05 | 1.34943e-05 | 1(Win) | true |
| simdjson (ondemand) | 1853.81 | 0.0436694 | 1445.46ms | 11579 | 640 | 4330.55 | 5956.69 | 0.252229 | 2.7466 | 11.959 | 1.9911 | 0.00194965 | 1.38991e-05 | 1.34943e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 645.893 | 0.0722324 | 1425.29ms | 4630 | 4890 | 119238 | 6836.29 | 0.0634717 | 7.82453 | 36.7216 | 7.10799 | 0.00589461 | 9.20025e-05 | 3.13595e-05 | 1(Win) | true |
| simdjson (ondemand) | 607.499 | 0.194983 | 1475.98ms | 4630 | 160 | 32135.6 | 7268.35 | 0.0680571 | 8.27292 | 36.8957 | 6.8851 | 0.00701269 | 0.000190335 | 9.58423e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 741.899 | 0.111307 | 1439.26ms | 4630 | 2560 | 112346 | 5951.64 | 0.147313 | 6.8154 | 32.2184 | 6.06674 | 0.00408984 | 7.5594e-05 | 2.83477e-05 | 1(Win) | true |
| simdjson (ondemand) | 698.653 | 0.197807 | 1467.46ms | 4630 | 80 | 12502.9 | 6320.04 | 0.0879363 | 7.28642 | 32.5184 | 5.87019 | 0.00576674 | 0.00025378 | 0.000102592 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1510.39 | 0.053312 | 1468.58ms | 11579 | 1280 | 19445.8 | 7311.1 | 0.361898 | 3.34218 | 15.4271 | 2.8784 | 0.00277078 | 4.50033e-05 | 2.01064e-05 | 1(Win) | true |
| simdjson (ondemand) | 1441.67 | 0.116636 | 1502.81ms | 11579 | 320 | 25540.3 | 7659.57 | 0.0222402 | 3.50815 | 15.4728 | 2.78617 | 0.00292124 | 4.91191e-05 | 2.18607e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1737.99 | 0.0246894 | 1474.32ms | 11579 | 4890 | 12033.1 | 6353.67 | 0.0206867 | 2.92693 | 13.6595 | 2.4687 | 0.00226226 | 7.23049e-05 | 3.99143e-05 | 1(Win) | true |
| simdjson (ondemand) | 1654.24 | 0.0355712 | 1508.44ms | 11579 | 4890 | 27570.9 | 6675.32 | 0.186281 | 3.05108 | 13.7248 | 2.38095 | 0.00223573 | 5.31072e-05 | 2.53085e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7200.18 | 0.120332 | 793.072ms | 4630 | 40 | 21.7821 | 613.25 | 0.149701 | 0.734519 | 3.63909 | 0.47041 | 0.000431965 | 2.15983e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6664.8 | 0.0798297 | 796.434ms | 4630 | 160 | 44.7546 | 662.513 | 0.126573 | 0.80406 | 3.93348 | 0.492657 | 0.000433315 | 1.34989e-05 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7519.61 | 0.113784 | 793.474ms | 4630 | 40 | 17.8564 | 587.2 | 0.119068 | 0.717273 | 3.60216 | 0.462419 | 0.000437365 | 2.69978e-05 | 5.39957e-06 | 1(Win) | true |
| simdjson (ondemand) | 6824.76 | 0.0715826 | 795.766ms | 4630 | 320 | 68.6361 | 646.984 | 0.082663 | 0.786756 | 3.89654 | 0.484665 | 0.00043264 | 1.01242e-05 | 6.74946e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12422.7 | 0.0668753 | 820.631ms | 11579 | 320 | 113.082 | 888.906 | 0.101146 | 0.425331 | 2.10631 | 0.211244 | 0.000172996 | 4.04828e-06 | 8.09655e-07 | 1(Win) | true |
| simdjson (ondemand) | 10872.5 | 0.205883 | 837.785ms | 11579 | 2560 | 11193.6 | 1015.65 | 0.0239168 | 0.482204 | 2.30072 | 0.231972 | 0.000175661 | 1.79474e-05 | 8.56885e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12630 | 0.0496196 | 821.343ms | 11579 | 640 | 120.455 | 874.317 | 0.00232319 | 0.418582 | 2.09155 | 0.208049 | 0.000172726 | 9.58092e-06 | 2.02414e-06 | 1(Win) | true |
| simdjson (ondemand) | 11157.2 | 0.0498728 | 835.535ms | 11579 | 4890 | 1191.43 | 989.731 | 0.121257 | 0.470581 | 2.28595 | 0.228776 | 0.000172832 | 1.93213e-05 | 1.1674e-05 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5275.68 | 0.0758539 | 818.545ms | 4630 | 4890 | 1970.92 | 836.956 | 0.064047 | 1.00129 | 5.15637 | 0.8054 | 0.000648302 | 2.76935e-05 | 1.27205e-05 | 1(Win) | true |
| simdjson (ondemand) | 5073.62 | 0.0913712 | 827.913ms | 4630 | 1280 | 809.382 | 870.288 | 0.133575 | 1.04196 | 5.41987 | 0.820303 | 0.000648961 | 2.21045e-05 | 1.02929e-05 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5385.83 | 0.0691506 | 819.091ms | 4630 | 4890 | 1571.65 | 819.838 | 0.0839353 | 0.972871 | 5.11944 | 0.797409 | 0.000648346 | 2.48226e-05 | 1.11304e-05 | 1(Win) | true |
| simdjson (ondemand) | 5084.43 | 0.0916959 | 820.286ms | 4630 | 80 | 50.7302 | 868.438 | 0.110709 | 1.02123 | 5.38294 | 0.812311 | 0.000647948 | 2.15983e-05 | 2.69978e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9731.16 | 0.0775282 | 847.409ms | 11579 | 30 | 23.2195 | 1134.77 | 0.0734905 | 0.537718 | 2.71276 | 0.345712 | 0.00025909 | 2.87877e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9094.81 | 0.048054 | 852.773ms | 11579 | 4890 | 1664.65 | 1214.16 | 0.0935129 | 0.572407 | 2.89507 | 0.362985 | 0.000259425 | 1.26454e-05 | 3.90312e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9933.41 | 0.0480342 | 845.829ms | 11579 | 160 | 45.6212 | 1111.66 | 0.0607568 | 0.527659 | 2.69799 | 0.342517 | 0.00025963 | 1.07954e-05 | 3.23862e-06 | 1(Win) | true |
| simdjson (ondemand) | 9240.48 | 0.0919399 | 854.696ms | 11579 | 2560 | 3090.3 | 1195.02 | 0.0794985 | 0.564663 | 2.8803 | 0.359789 | 0.000259562 | 1.40678e-05 | 7.69173e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1064.99 | 0.123803 | 1201.73ms | 5092 | 320 | 10197.5 | 4559.75 | 0.133409 | 4.77979 | 18.6094 | 3.22742 | 0.00314893 | 4.97103e-05 | 1.96386e-05 | 1(Win) | true |
| Jsonifier (generic) | 1050.49 | 0.0379036 | 1206.21ms | 5092 | 4890 | 15013 | 4622.73 | 0.199624 | 4.85282 | 19.1685 | 3.6302 | 0.0027462 | 0.00018225 | 0.000106828 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.28 | 0.0980857 | 1204.64ms | 5092 | 640 | 9962.17 | 4022.36 | 0.0383162 | 4.23202 | 16.8616 | 3.10194 | 0.00256284 | 0.000111695 | 6.56667e-05 | 1(Win) | true |
| simdjson (ondemand) | 1184.63 | 0.0377448 | 1190.93ms | 5092 | 4890 | 11706.7 | 4099.27 | 0.244888 | 4.2899 | 16.9219 | 2.82242 | 0.00361672 | 3.66668e-05 | 9.87957e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1919.57 | 0.0587587 | 1229.82ms | 9739 | 640 | 5173.04 | 4838.5 | 0.0633345 | 2.60616 | 10.2954 | 1.70962 | 0.0018277 | 1.81294e-05 | 4.01094e-06 | 1(Win) | true |
| Jsonifier (generic) | 1829.34 | 0.0811993 | 1257.61ms | 9739 | 160 | 2719.36 | 5077.16 | 0.0172311 | 2.78767 | 10.7675 | 1.94357 | 0.00205552 | 1.73272e-05 | 6.4175e-07 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2115.44 | 0.0311068 | 1228.97ms | 9739 | 4890 | 9121.09 | 4390.5 | 0.164364 | 2.36629 | 9.413 | 1.49992 | 0.00224327 | 3.43106e-05 | 1.08769e-05 | 1(Win) | true |
| Jsonifier (generic) | 2073.54 | 0.0275271 | 1248.06ms | 9739 | 4890 | 7434.19 | 4479.22 | 0.212295 | 2.41355 | 9.5612 | 1.66267 | 0.00137066 | 2.22158e-05 | 6.90832e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 650.741 | 0.0291405 | 1501.32ms | 5092 | 4890 | 23123.9 | 7462.43 | 0.00997063 | 7.67078 | 32.879 | 6.67955 | 0.00746614 | 0.0001749 | 9.6627e-05 | 1(Win) | true |
| simdjson (ondemand) | 410.128 | 0.0861601 | 1951.1ms | 5092 | 320 | 33304.3 | 11840.5 | 0.11465 | 12.3606 | 56.8824 | 11.4619 | 0.0149211 | 0.000144221 | 7.67135e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 708.538 | 0.106308 | 1501.95ms | 5092 | 320 | 16987.6 | 6853.7 | 0.0690797 | 7.03923 | 30.721 | 6.17712 | 0.00724728 | 4.29595e-05 | 7.9782e-06 | 1(Win) | true |
| simdjson (ondemand) | 421.924 | 0.0198501 | 1948.45ms | 5092 | 4890 | 25523.7 | 11509.4 | 0.0103621 | 11.8037 | 55.1983 | 11.061 | 0.0154856 | 5.40163e-05 | 1.85945e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1149.12 | 0.043876 | 1559.04ms | 9739 | 320 | 4024.38 | 8082.53 | 0.130544 | 4.34127 | 18.4089 | 3.61963 | 0.00376643 | 1.86107e-05 | 2.88787e-06 | 1(Win) | true |
| simdjson (ondemand) | 773.693 | 0.0327812 | 1950.66ms | 9739 | 2560 | 39644.2 | 12004.6 | 0.044544 | 6.46016 | 30.2372 | 6.00154 | 0.00765688 | 0.000126064 | 7.52853e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1254.33 | 0.0256837 | 1558.14ms | 9739 | 4890 | 17686 | 7404.64 | 0.11352 | 3.98921 | 17.2564 | 3.35076 | 0.00293623 | 0.000113032 | 7.23589e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.378 | 0.0180309 | 1949.7ms | 9739 | 4890 | 21090.9 | 11518 | 0.0871728 | 6.17059 | 29.3427 | 5.79035 | 0.00735682 | 3.18539e-05 | 7.22329e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4794.23 | 0.0367135 | 845.589ms | 5092 | 1280 | 177.011 | 1012.91 | 0.3183 | 1.07667 | 4.98252 | 0.691673 | 0.00103088 | 1.18139e-05 | 1.6877e-06 | 1(Win) | true |
| simdjson (ondemand) | 4461.26 | 0.0735486 | 851.186ms | 5092 | 2560 | 1640.78 | 1088.51 | 0.178386 | 1.15738 | 5.29654 | 0.6848 | 0.00132645 | 2.75401e-05 | 1.53427e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4939.93 | 0.075337 | 844.096ms | 5092 | 320 | 175.51 | 983.031 | 0.0209854 | 1.04548 | 4.85978 | 0.665554 | 0.00121637 | 9.20562e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4658.17 | 0.0709928 | 847.658ms | 5092 | 2560 | 1402.22 | 1042.49 | 0.15399 | 1.10577 | 5.17381 | 0.658681 | 0.00121806 | 1.08933e-05 | 1.6877e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7353.72 | 0.0802383 | 869.457ms | 9739 | 640 | 657.291 | 1263.01 | 0.0607797 | 0.722344 | 3.3755 | 0.389773 | 0.000505699 | 4.29972e-05 | 2.32634e-05 | 1(Win) | true |
| Jsonifier (generic) | 7196.89 | 0.0521362 | 870.673ms | 9739 | 4890 | 2213.74 | 1290.53 | 0.559463 | 0.712218 | 3.20936 | 0.390903 | 0.000859362 | 2.15019e-05 | 4.57755e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 7549.16 | 0.0794171 | 866.473ms | 9739 | 2560 | 2443.99 | 1230.31 | 0.106059 | 0.685604 | 3.14519 | 0.377246 | 0.000824007 | 1.78487e-05 | 6.77848e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 7541.35 | 0.127048 | 862.119ms | 9739 | 80 | 195.866 | 1231.59 | 0.0253673 | 0.680257 | 3.28535 | 0.370983 | 0.000395318 | 1.41185e-05 | 3.8505e-06 | 1(Tie) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3060.36 | 0.0934283 | 900.054ms | 5092 | 160 | 351.647 | 1586.78 | 0.0126058 | 1.66581 | 7.99607 | 1.38806 | 0.00180307 | 1.96386e-05 | 2.45483e-06 | 1(Win) | true |
| simdjson (ondemand) | 2771.75 | 0.213038 | 913.297ms | 5092 | 30 | 417.931 | 1752 | 0.062746 | 1.83117 | 8.4947 | 1.37372 | 0.00245483 | 2.61849e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3163.7 | 0.315341 | 893.113ms | 5092 | 320 | 7497.15 | 1534.95 | 0.00427521 | 1.61633 | 7.82365 | 1.35212 | 0.00197 | 9.81932e-06 | 1.22742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2871.87 | 0.0658096 | 909.854ms | 5092 | 2560 | 3170.04 | 1690.92 | 0.0232222 | 1.76785 | 8.32227 | 1.33779 | 0.00273706 | 2.53154e-05 | 1.61098e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4969.12 | 0.0472989 | 929.336ms | 9739 | 1280 | 1000.42 | 1869.11 | 0.129156 | 1.0313 | 4.83818 | 0.761269 | 0.00133933 | 2.68733e-05 | 1.12306e-05 | 1(Win) | true |
| simdjson (ondemand) | 4743.43 | 0.0457546 | 938.274ms | 9739 | 2560 | 2054.72 | 1958.04 | 0.0761302 | 1.06675 | 5.02167 | 0.744841 | 0.000840411 | 1.17119e-05 | 7.62078e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5040.27 | 0.079191 | 926.388ms | 9739 | 160 | 340.716 | 1842.72 | 0.00881924 | 1.00667 | 4.74802 | 0.742479 | 0.00159026 | 5.77575e-06 | 2.567e-06 | 1(Win) | true |
| simdjson (ondemand) | 4950.13 | 0.0452972 | 926.917ms | 9739 | 4890 | 3532.22 | 1876.28 | 0.122094 | 1.03089 | 4.93151 | 0.72605 | 0.00100452 | 1.18218e-05 | 9.44907e-07 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1351.52 | 0.119822 | 1090.77ms | 4857 | 640 | 10793.1 | 3427.25 | 0.261276 | 3.76637 | 14.917 | 2.93371 | 0.00119287 | 8.71809e-05 | 4.88985e-05 | 1(Win) | true |
| simdjson (ondemand) | 1256.68 | 0.0686419 | 1114.13ms | 4857 | 320 | 2048.41 | 3685.91 | 0.054375 | 3.99288 | 15.2858 | 2.70784 | 0.000986978 | 0.000118386 | 6.36967e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1738.27 | 0.0555202 | 1043.07ms | 4857 | 2560 | 5603.27 | 2664.71 | 0.109771 | 2.92187 | 11.7764 | 2.25015 | 0.00217751 | 0.000121362 | 7.46345e-05 | 1(Win) | true |
| simdjson (ondemand) | 1512.21 | 0.0590378 | 1080.06ms | 4857 | 1280 | 4185.83 | 3063.06 | 0.193015 | 3.33007 | 12.9323 | 2.19889 | 0.00168201 | 3.61913e-05 | 1.06161e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1785.47 | 0.0864042 | 1106.16ms | 6701 | 160 | 1530.25 | 3579.2 | 0.0914172 | 2.81229 | 11.2207 | 2.12446 | 0.000900052 | 3.35771e-05 | 1.49231e-05 | 1(Win) | true |
| simdjson (ondemand) | 1682 | 0.0431381 | 1128.66ms | 6701 | 2560 | 6876.89 | 3799.4 | 0.0881455 | 2.98006 | 11.4467 | 1.97881 | 0.00047381 | 3.92316e-05 | 1.49231e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2276.8 | 0.0549155 | 1057.9ms | 6701 | 2560 | 6082.2 | 2806.82 | 0.0717099 | 2.22927 | 9.01985 | 1.64393 | 0.00178728 | 6.44727e-05 | 2.87387e-05 | 1(Win) | true |
| simdjson (ondemand) | 2013.59 | 0.0350067 | 1095.81ms | 6701 | 4890 | 6035.97 | 3173.71 | 0.124055 | 2.49538 | 9.74079 | 1.60991 | 0.000640902 | 8.21841e-05 | 4.15956e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 671.299 | 0.034867 | 1440.92ms | 4857 | 2560 | 14817.4 | 6900.05 | 0.0358935 | 7.43353 | 31.0033 | 6.19374 | 0.0067685 | 0.00024972 | 0.000133908 | 1(Win) | true |
| simdjson (ondemand) | 196.686 | 0.022008 | 3114.13ms | 4857 | 4890 | 131360 | 23550.2 | 0.077064 | 25.4025 | 123.771 | 26.0023 | 0.0386596 | 0.000370683 | 0.000238182 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 773.773 | 0.0427444 | 1380.11ms | 4857 | 1280 | 8380.64 | 5986.25 | 0.0728874 | 6.45542 | 27.8701 | 5.5141 | 0.00664296 | 5.62976e-05 | 2.0428e-05 | 1(Win) | true |
| simdjson (ondemand) | 202.94 | 0.0457357 | 3060.93ms | 4857 | 640 | 69741.6 | 22824.5 | 0.0181584 | 24.5056 | 121.441 | 25.5009 | 0.0398372 | 5.14721e-05 | 1.76935e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 857.25 | 0.0255879 | 1494.94ms | 6701 | 4890 | 17792.7 | 7454.73 | 0.16897 | 5.81663 | 23.7409 | 4.73646 | 0.00613549 | 0.000179017 | 0.000116303 | 1(Win) | true |
| simdjson (ondemand) | 273.465 | 0.0204728 | 3092ms | 6701 | 4890 | 111928 | 23368.9 | 0.202655 | 18.2252 | 89.8469 | 18.8184 | 0.0271443 | 0.000194367 | 0.000117005 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 979.112 | 0.0452549 | 1436.55ms | 6701 | 2560 | 22334.9 | 6526.9 | 0.134276 | 5.10723 | 21.4699 | 4.24385 | 0.00573894 | 0.000110408 | 6.41229e-05 | 1(Win) | true |
| simdjson (ondemand) | 280.379 | 0.0288806 | 3054.74ms | 6701 | 2560 | 110928 | 22792.6 | 0.0600849 | 17.6958 | 88.1201 | 18.4475 | 0.0274726 | 0.000230726 | 0.000159433 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3921.85 | 0.0781096 | 865.811ms | 4857 | 1280 | 1089.36 | 1181.07 | 0.125308 | 1.30878 | 5.57278 | 0.895203 | 0.000517455 | 1.57633e-05 | 1.6085e-06 | 1(Win) | true |
| simdjson (ondemand) | 3513.35 | 0.0782937 | 875.655ms | 4857 | 2560 | 2727.64 | 1318.4 | 0.00586684 | 1.45377 | 6.01771 | 0.891703 | 0.000415396 | 2.53339e-05 | 8.68592e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4560.49 | 0.071722 | 853.962ms | 4857 | 2560 | 1358.49 | 1015.68 | 0.18074 | 1.12796 | 4.986 | 0.761581 | 0.00071128 | 1.02944e-05 | 1.2868e-06 | 1(Win) | true |
| simdjson (ondemand) | 4087.53 | 0.0915869 | 860.75ms | 4857 | 640 | 689.386 | 1133.2 | 0.190365 | 1.28137 | 5.44637 | 0.761993 | 0.000521798 | 4.92202e-05 | 2.47709e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4774.25 | 0.0488808 | 875.738ms | 6701 | 4890 | 2093.41 | 1338.55 | 0.0220788 | 1.07296 | 4.52768 | 0.678556 | 0.00052585 | 1.89515e-05 | 4.05885e-06 | 1(Win) | true |
| simdjson (ondemand) | 4538.64 | 0.114542 | 883.925ms | 6701 | 80 | 208.087 | 1408.04 | 0.0364114 | 1.12414 | 4.73317 | 0.661991 | 0.000300328 | 7.46157e-06 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5490.14 | 0.101777 | 865.36ms | 6701 | 320 | 449.119 | 1164.01 | 0.12736 | 0.940363 | 4.10237 | 0.581704 | 0.000398728 | 1.16587e-05 | 2.33174e-06 | 1(Win) | true |
| simdjson (ondemand) | 5129.31 | 0.0666819 | 873.794ms | 6701 | 1280 | 883.46 | 1245.89 | 0.035855 | 1.00474 | 4.31906 | 0.567975 | 0.00065895 | 1.56227e-05 | 4.08055e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2962.58 | 0.18513 | 899.434ms | 4857 | 40 | 335.128 | 1563.5 | 0.134495 | 1.74993 | 7.53593 | 1.32283 | 0.00110665 | 2.05888e-05 | 5.14721e-06 | 1(Win) | true |
| simdjson (ondemand) | 1981.34 | 0.0765633 | 977.287ms | 4857 | 1280 | 4100.82 | 2337.81 | 0.0309355 | 2.54522 | 11.3008 | 1.94379 | 0.00137656 | 1.52808e-05 | 3.05616e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3302.21 | 0.054323 | 891.598ms | 4857 | 1280 | 743.198 | 1402.7 | 0.143624 | 1.54545 | 6.96562 | 1.19621 | 0.00117035 | 1.86586e-05 | 2.41275e-06 | 1(Win) | true |
| simdjson (ondemand) | 2165.58 | 0.0818942 | 966.44ms | 4857 | 1280 | 3927.38 | 2138.91 | 0.0346382 | 2.34432 | 10.7468 | 1.82191 | 0.00148063 | 4.51989e-05 | 2.73446e-05 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3634.26 | 0.107981 | 922.3ms | 6701 | 80 | 288.425 | 1758.42 | 0.150931 | 1.39675 | 6.08984 | 1.01119 | 0.000423444 | 2.42501e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2660.87 | 0.0389993 | 984.327ms | 6701 | 4890 | 4289.97 | 2401.69 | 0.0660915 | 1.89753 | 8.48068 | 1.40725 | 0.00124448 | 2.35596e-05 | 9.55203e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4009.23 | 0.140814 | 912.593ms | 6701 | 30 | 151.137 | 1593.97 | 0.144503 | 1.2706 | 5.67647 | 0.919415 | 0.000785952 | 4.47694e-05 | 2.48719e-05 | 1(Win) | true |
| simdjson (ondemand) | 2892.67 | 0.0927209 | 971.251ms | 6701 | 1280 | 5370.89 | 2209.23 | 0.196092 | 1.75634 | 8.07909 | 1.31891 | 0.00155935 | 8.04451e-06 | 9.32697e-07 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1231.98 | 0.276325 | 877.242ms | 1691 | 40 | 523.333 | 1309 | 0.299584 | 4.23488 | 14.8261 | 2.95092 | 0.00116795 | 0.000118273 | 7.39208e-05 | 1(Win) | true |
| simdjson (ondemand) | 1063 | 0.0385491 | 903.023ms | 1691 | 4890 | 1672.48 | 1517.09 | 0.151997 | 4.79065 | 17.3353 | 3.27499 | 0.00128915 | 0.000109082 | 2.09215e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.8 | 0.0755894 | 873.281ms | 1691 | 320 | 236.555 | 1137.44 | 0.0335294 | 3.62416 | 13.1638 | 2.54524 | 0.000903681 | 5.35925e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1231.16 | 0.200983 | 885.885ms | 1691 | 640 | 4435.67 | 1309.88 | 0.0362762 | 4.28373 | 15.7132 | 2.87641 | 0.00177779 | 6.56047e-05 | 1.01641e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1441.89 | 0.0842157 | 889.907ms | 2158 | 1280 | 1849.42 | 1427.31 | 0.00760883 | 3.54102 | 12.4083 | 2.39945 | 0.000772561 | 6.58886e-05 | 1.12228e-05 | 1(Win) | true |
| simdjson (ondemand) | 1354.1 | 0.291178 | 892.809ms | 2158 | 320 | 6267.11 | 1519.85 | 0.320752 | 3.82424 | 13.817 | 2.576 | 0.000702329 | 0.000153499 | 8.97822e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1670.9 | 0.0614576 | 881.502ms | 2158 | 640 | 366.719 | 1231.69 | 0.128673 | 3.09058 | 11.1381 | 2.08712 | 0.000595169 | 2.75139e-05 | 3.62025e-06 | 1(Win) | true |
| simdjson (ondemand) | 1521.5 | 0.222905 | 890.995ms | 2158 | 30 | 272.723 | 1352.63 | 0.0147882 | 3.35836 | 12.5459 | 2.26367 | 0.000463392 | 6.17856e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 900.188 | 0.129139 | 927.521ms | 1691 | 1280 | 6850.85 | 1791.47 | 0.0855911 | 5.64839 | 20.696 | 4.17091 | 0.00194088 | 0.000196814 | 7.85408e-05 | 1(Win) | true |
| simdjson (ondemand) | 607.424 | 0.0678244 | 1006.83ms | 1691 | 640 | 2075.18 | 2654.92 | 0.139676 | 8.28897 | 31.9982 | 6.24483 | 0.00284318 | 8.87049e-05 | 1.20121e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1019.32 | 0.051731 | 917.893ms | 1691 | 4890 | 3275.47 | 1582.09 | 0.177728 | 5.00326 | 19.0751 | 3.77114 | 0.00110582 | 9.08212e-05 | 2.53961e-05 | 1(Win) | true |
| simdjson (ondemand) | 661.389 | 0.049812 | 1005.16ms | 1691 | 2560 | 3776.43 | 2438.3 | 0.00273941 | 7.62729 | 30.3761 | 5.84506 | 0.00237817 | 7.46138e-05 | 1.52462e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1034.39 | 0.081362 | 948.923ms | 2158 | 80 | 209.635 | 1989.6 | 0.0263942 | 4.89263 | 17.4027 | 3.51205 | 0.00237488 | 4.63392e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 772.21 | 0.0899012 | 1006.47ms | 2158 | 1280 | 7348.07 | 2665.12 | 0.0796704 | 6.51287 | 25.1937 | 4.87906 | 0.00205594 | 8.14556e-05 | 1.88253e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1144.44 | 0.040724 | 938.785ms | 2158 | 2560 | 1372.96 | 1798.29 | 0.0785938 | 4.43587 | 16.1325 | 3.1988 | 0.00230013 | 6.82417e-05 | 1.04987e-05 | 1(Win) | true |
| simdjson (ondemand) | 849.516 | 0.0829882 | 997.736ms | 2158 | 640 | 2586.86 | 2422.59 | 0.0115463 | 6.01537 | 23.9226 | 4.5658 | 0.00181157 | 2.96861e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4276.98 | 0.0738388 | 775.547ms | 1691 | 4890 | 379.045 | 377.056 | 0.152103 | 1.29374 | 4.60217 | 0.739239 | 0.00105394 | 4.81316e-05 | 1.0884e-05 | 1(Win) | true |
| simdjson (ondemand) | 3853.54 | 0.10468 | 778.866ms | 1691 | 2560 | 491.289 | 418.488 | 0.150986 | 1.42366 | 5.11177 | 0.754583 | 0.000873651 | 2.95683e-05 | 7.16107e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4730.56 | 0.120862 | 773.156ms | 1691 | 4890 | 830.146 | 340.903 | 0.0355226 | 1.17316 | 4.25251 | 0.660556 | 0.000989359 | 4.34152e-05 | 9.19097e-06 | 1(Win) | true |
| simdjson (ondemand) | 4242.73 | 0.23678 | 775.199ms | 1691 | 80 | 64.8 | 380.1 | 0.0854308 | 1.29056 | 4.76345 | 0.677114 | 0.000850089 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5103.05 | 0.247964 | 769.951ms | 2158 | 160 | 160.008 | 403.294 | 0.0727847 | 1.07335 | 4.00185 | 0.597776 | 0.000463392 | 1.73772e-05 | 8.6886e-06 | 1(Win) | true |
| simdjson (ondemand) | 4679.22 | 0.0893577 | 779.056ms | 2158 | 4890 | 755.317 | 439.824 | 0.248575 | 1.17488 | 4.25904 | 0.605654 | 0.000671397 | 5.05088e-05 | 3.23142e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5670.54 | 0.157289 | 774.464ms | 2158 | 4890 | 1593.52 | 362.934 | 0.00445396 | 0.976843 | 3.72799 | 0.536145 | 0.000466235 | 4.3212e-05 | 1.9995e-05 | 1(Win) | true |
| simdjson (ondemand) | 5156.11 | 0.109123 | 776.504ms | 2158 | 2560 | 485.655 | 399.144 | 0.309177 | 1.06627 | 3.9861 | 0.544949 | 0.000570008 | 2.40747e-05 | 1.23089e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2931.41 | 0.0739628 | 790.549ms | 1691 | 1280 | 211.92 | 550.133 | 0.254968 | 1.82472 | 6.90538 | 1.21881 | 0.00128114 | 4.80485e-05 | 6.93007e-06 | 1(Win) | true |
| simdjson (ondemand) | 2368.73 | 0.204876 | 797.68ms | 1691 | 160 | 311.285 | 680.812 | 0.119485 | 2.23391 | 8.89415 | 1.52454 | 0.00147842 | 2.58723e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3262.36 | 0.158172 | 789.916ms | 1691 | 640 | 391.255 | 494.323 | 0.277345 | 1.6701 | 6.55588 | 1.14015 | 0.000747524 | 5.08205e-05 | 2.21762e-05 | 1(Win) | true |
| simdjson (ondemand) | 2519.98 | 0.272371 | 800.032ms | 1691 | 160 | 486.111 | 639.95 | 0.122905 | 2.11701 | 8.54583 | 1.44707 | 0.00116425 | 7.39208e-05 | 3.69604e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3512.7 | 0.0895252 | 792.393ms | 2158 | 4890 | 1345.3 | 585.883 | 0.00546524 | 1.52531 | 5.79889 | 0.99027 | 0.00103766 | 4.39701e-05 | 2.22694e-05 | 1(Win) | true |
| simdjson (ondemand) | 2929.3 | 0.151052 | 818.768ms | 2158 | 2560 | 2883.15 | 702.566 | 0.0418285 | 1.80718 | 7.22614 | 1.21038 | 0.000936016 | 1.35759e-05 | 1.99114e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3884.74 | 0.0882518 | 785.675ms | 2158 | 4890 | 1068.9 | 529.773 | 0.592434 | 1.38996 | 5.52502 | 0.928638 | 0.000492105 | 3.12719e-05 | 1.13716e-05 | 1(Win) | true |
| simdjson (ondemand) | 3088.25 | 0.0978663 | 806.43ms | 2158 | 4890 | 2079.96 | 666.407 | 0.27778 | 1.71574 | 6.9532 | 1.14968 | 0.00113479 | 5.48679e-05 | 2.69127e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1254.98 | 0.0667583 | 1080.59ms | 4390 | 1280 | 6348.58 | 3336.02 | 0.0323307 | 4.14858 | 18.2212 | 3.52665 | 0.00186859 | 0.000112294 | 4.94732e-05 | 1(Win) | true |
| simdjson (ondemand) | 1030.71 | 0.108514 | 1151.64ms | 4390 | 640 | 12434 | 4061.89 | 0.0202682 | 4.9061 | 20.1779 | 3.64898 | 0.00340369 | 2.2779e-05 | 3.55923e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1356.53 | 0.0386537 | 1072.58ms | 4390 | 4890 | 6959.23 | 3086.28 | 0.0969298 | 3.73778 | 16.7289 | 3.19522 | 0.00219275 | 5.36169e-05 | 1.62109e-05 | 1(Win) | true |
| simdjson (ondemand) | 1119.44 | 0.058165 | 1139.05ms | 4390 | 1280 | 6057.06 | 3739.94 | 0.0989045 | 4.49399 | 18.6554 | 3.31139 | 0.00356261 | 3.38126e-05 | 5.33884e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2286.32 | 0.141586 | 1130.13ms | 9378 | 30 | 920.254 | 3911.77 | 0.294852 | 2.19246 | 9.45884 | 1.7218 | 0.00140044 | 3.55442e-05 | 1.06633e-05 | 1(Win) | true |
| simdjson (ondemand) | 2073.15 | 0.0633046 | 1175.46ms | 9378 | 1280 | 9546.42 | 4314 | 0.0266283 | 2.42641 | 10.073 | 1.73854 | 0.00105974 | 4.08203e-05 | 1.95771e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2516.63 | 0.122799 | 1121.72ms | 9378 | 320 | 6094.26 | 3553.78 | 0.157739 | 1.99951 | 8.70633 | 1.55598 | 0.00146586 | 5.99808e-05 | 2.86575e-05 | 1(Win) | true |
| simdjson (ondemand) | 2253.21 | 0.0770287 | 1162.28ms | 9378 | 640 | 5982.78 | 3969.25 | 0.125064 | 2.22482 | 9.36032 | 1.58051 | 0.00100818 | 1.48286e-05 | 2.16597e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 743.96 | 0.0677476 | 1303.54ms | 4390 | 1280 | 18604.9 | 5627.49 | 0.206827 | 6.74629 | 29.9262 | 5.9508 | 0.0122907 | 3.07873e-05 | 4.44903e-06 | 1(Win) | true |
| simdjson (ondemand) | 649.397 | 0.068689 | 1395.73ms | 4390 | 320 | 6275.28 | 6446.95 | 0.194364 | 7.68374 | 33.067 | 6.26128 | 0.00891728 | 4.84055e-05 | 1.49487e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 787.325 | 0.0366052 | 1304.79ms | 4390 | 2560 | 9699.46 | 5317.54 | 0.0266877 | 6.35235 | 28.4337 | 5.61914 | 0.0119086 | 8.49765e-05 | 3.24779e-05 | 1(Win) | true |
| simdjson (ondemand) | 688.87 | 0.027183 | 1370.96ms | 4390 | 4890 | 13346.2 | 6077.54 | 0.202746 | 7.26313 | 31.5169 | 5.91822 | 0.00914227 | 3.2841e-05 | 7.54643e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1443.36 | 0.105142 | 1368.34ms | 9378 | 30 | 1273.34 | 6196.37 | 0.100159 | 3.45986 | 14.9591 | 2.91224 | 0.00626644 | 4.97619e-05 | 1.42177e-05 | 1(Win) | true |
| simdjson (ondemand) | 1359.74 | 0.0604845 | 1403.95ms | 9378 | 160 | 2532.3 | 6577.39 | 0.0639092 | 3.67157 | 15.9579 | 2.9308 | 0.0046865 | 1.73278e-05 | 1.99936e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1533.97 | 0.135923 | 1356.55ms | 9378 | 320 | 20096.6 | 5830.32 | 0.0632869 | 3.25202 | 14.2604 | 2.75699 | 0.00628032 | 2.46588e-05 | 9.9968e-07 | 1(Win) | true |
| simdjson (ondemand) | 1441.8 | 0.0821682 | 1385.95ms | 9378 | 80 | 2078.29 | 6203.04 | 0.107523 | 3.46525 | 15.2322 | 2.77021 | 0.00498107 | 9.33035e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2014.22 | 0.0780305 | 954.206ms | 4390 | 640 | 1683.54 | 2078.53 | 0.00142831 | 2.50953 | 10.8399 | 1.98383 | 0.0026922 | 4.05752e-05 | 4.62699e-06 | 1(Win) | true |
| simdjson (ondemand) | 1799.11 | 0.0616232 | 979.148ms | 4390 | 2560 | 5264.33 | 2327.06 | 0.0282432 | 2.79935 | 11.9166 | 2.00433 | 0.00294392 | 1.68173e-05 | 1.42369e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2121.23 | 0.0584365 | 947.825ms | 4390 | 160 | 212.835 | 1973.68 | 0.0193204 | 2.38848 | 10.4991 | 1.90387 | 0.00240319 | 1.42369e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1877.02 | 0.0387193 | 966.137ms | 4390 | 320 | 238.67 | 2230.47 | 0.0670652 | 2.69735 | 11.5759 | 1.92437 | 0.00311931 | 1.56606e-05 | 4.27107e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3824.65 | 0.0332411 | 978.04ms | 9378 | 4890 | 2954.59 | 2338.4 | 0.086899 | 1.32129 | 5.84026 | 0.978993 | 0.00107324 | 2.69307e-05 | 1.20589e-05 | 1(Win) | true |
| simdjson (ondemand) | 3558.41 | 0.0666824 | 996.239ms | 9378 | 1280 | 3595.35 | 2513.36 | 0.0245813 | 1.41335 | 6.20751 | 0.96961 | 0.00082432 | 1.22461e-05 | 4.41525e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3937.85 | 0.0693939 | 976.722ms | 9378 | 1280 | 3179.47 | 2271.18 | 0.120044 | 1.28146 | 5.70772 | 0.946897 | 0.00102384 | 4.29029e-05 | 1.34124e-05 | 1(Win) | true |
| simdjson (ondemand) | 3689.96 | 0.0801481 | 990.102ms | 9378 | 2560 | 9660.6 | 2423.76 | 0.152021 | 1.3684 | 6.04798 | 0.932182 | 0.000917748 | 1.18295e-05 | 3.33227e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1642.56 | 0.0813377 | 1014.83ms | 4390 | 640 | 2750.73 | 2548.84 | 0.0657594 | 3.05858 | 14.2082 | 2.63554 | 0.0040803 | 9.25399e-06 | 7.11845e-07 | 1(Win) | true |
| simdjson (ondemand) | 1535.48 | 0.133786 | 1018.85ms | 4390 | 640 | 8516.11 | 2726.6 | 0.0104308 | 3.27504 | 14.5207 | 2.48975 | 0.00348484 | 4.84055e-05 | 2.7762e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1709.07 | 0.0438222 | 994.682ms | 4390 | 1280 | 1475.06 | 2449.66 | 0.0322008 | 2.95259 | 13.9251 | 2.56697 | 0.00355905 | 3.45245e-05 | 1.12116e-05 | 1(Win) | true |
| simdjson (ondemand) | 1598.55 | 0.0912041 | 1011.55ms | 4390 | 80 | 456.455 | 2619.03 | 0.0295824 | 3.15926 | 14.18 | 2.40979 | 0.00378986 | 5.69476e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3041.9 | 0.0555073 | 1040.17ms | 9378 | 1280 | 3409.11 | 2940.12 | 0.366989 | 1.652 | 7.42653 | 1.19684 | 0.0016678 | 1.02467e-05 | 2.24928e-06 | 1(Win) | true |
| Jsonifier (generic) | 3003.69 | 0.0522333 | 1035.26ms | 9378 | 2560 | 6192.21 | 2977.53 | 0.352384 | 1.67664 | 7.4003 | 1.31403 | 0.00191872 | 1.78276e-05 | 4.70683e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3126.41 | 0.0874376 | 1036.88ms | 9378 | 1280 | 8008.2 | 2860.65 | 0.0739836 | 1.6195 | 7.24078 | 1.27661 | 0.00162848 | 2.33259e-05 | 1.08299e-05 | 1(Win) | true |
| simdjson (ondemand) | 3117.05 | 0.053258 | 1035.94ms | 9378 | 2560 | 5977.81 | 2869.24 | 0.0987327 | 1.61605 | 7.26701 | 1.15942 | 0.00197191 | 1.21628e-05 | 3.91541e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1371.33 | 0.0518141 | 1070.08ms | 4669 | 2560 | 7246.06 | 3247 | 0.0157693 | 3.66127 | 14.8771 | 2.99422 | 0.00259909 | 3.12902e-05 | 2.7609e-06 | 1(Win) | true |
| simdjson (ondemand) | 1354.41 | 0.0981024 | 1072.35ms | 4669 | 1280 | 13314.2 | 3287.56 | 0.0173982 | 3.69838 | 16.2744 | 2.60805 | 0.00168314 | 3.31308e-05 | 3.6812e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1480.89 | 0.0367636 | 1051.22ms | 4669 | 4890 | 5975.16 | 3006.78 | 0.130522 | 3.39699 | 14.0595 | 2.80853 | 0.00257768 | 2.7068e-05 | 2.58416e-06 | 1(Win) | true |
| simdjson (ondemand) | 1453.38 | 0.0719258 | 1062.06ms | 4669 | 640 | 3107.71 | 3063.7 | 0.0567313 | 3.45993 | 15.4575 | 2.423 | 0.00169837 | 2.6103e-05 | 3.6812e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2200.41 | 0.125646 | 1091.21ms | 7932 | 80 | 1492.6 | 3437.79 | 0.0163649 | 2.28155 | 10.0886 | 1.55862 | 0.000854135 | 1.41831e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2118.21 | 0.132705 | 1106.82ms | 7932 | 320 | 7187.05 | 3571.19 | 0.00472553 | 2.36589 | 9.51727 | 1.81518 | 0.0013726 | 1.89107e-05 | 3.54576e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2345.22 | 0.151459 | 1071.43ms | 7932 | 320 | 7637.24 | 3225.52 | 0.00290659 | 2.13919 | 9.62065 | 1.4526 | 0.000821435 | 2.79721e-05 | 1.14252e-05 | 1(Win) | true |
| Jsonifier (generic) | 2283.63 | 0.0390957 | 1085.31ms | 7932 | 640 | 1073.37 | 3312.5 | 0.0148563 | 2.19966 | 9.04564 | 1.70777 | 0.00126663 | 1.5759e-05 | 2.9548e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 567.807 | 0.0345031 | 1516.91ms | 4669 | 2560 | 18741.5 | 7841.94 | 0.13916 | 8.8253 | 38.7124 | 7.7402 | 0.0102178 | 6.45046e-05 | 2.12505e-05 | 1(Win) | true |
| simdjson (ondemand) | 205.941 | 0.0410961 | 2907.48ms | 4669 | 2560 | 202118 | 21621.3 | 0.00437737 | 24.6219 | 112.77 | 23.9683 | 0.0612106 | 7.61338e-05 | 2.21708e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 607.217 | 0.114465 | 1485.61ms | 4669 | 320 | 22545.4 | 7332.98 | 0.047795 | 8.45793 | 37.8993 | 7.55622 | 0.0104934 | 6.35843e-05 | 2.67723e-05 | 1(Win) | true |
| simdjson (ondemand) | 209.855 | 0.076023 | 2887.81ms | 4669 | 640 | 166525 | 21218 | 0.245669 | 24.117 | 111.958 | 23.785 | 0.0604894 | 8.76794e-05 | 4.18318e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 908.413 | 0.0480226 | 1580.48ms | 7932 | 640 | 10234.6 | 8327.21 | 0.103113 | 5.59106 | 24.5006 | 4.84178 | 0.00482421 | 1.63499e-05 | 1.18192e-06 | 1(Win) | true |
| simdjson (ondemand) | 342.547 | 0.0613275 | 2953ms | 7932 | 1280 | 234772 | 22083.3 | 0.068722 | 14.5538 | 66.0991 | 13.9725 | 0.0391567 | 3.41772e-05 | 6.99303e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 920.243 | 0.0915453 | 1567.24ms | 7932 | 320 | 18121 | 8220.16 | 0.0921425 | 5.4204 | 24.0304 | 4.73487 | 0.00515593 | 2.83661e-05 | 7.4855e-06 | 1(Win) | true |
| simdjson (ondemand) | 349.537 | 0.0390083 | 2917.38ms | 7932 | 2560 | 182445 | 21641.6 | 0.233543 | 14.2513 | 65.6299 | 13.8662 | 0.0395201 | 3.89049e-05 | 1.16222e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4260.68 | 0.0792177 | 843.442ms | 4669 | 2560 | 1754.59 | 1045.07 | 0.00979205 | 1.21647 | 5.18398 | 0.763975 | 0.00128599 | 1.84896e-05 | 3.84852e-06 | 1(Win) | true |
| simdjson (ondemand) | 4053.49 | 0.0561507 | 850.417ms | 4669 | 4890 | 1860.41 | 1098.49 | 0.15886 | 1.27325 | 5.56672 | 0.771257 | 0.00117597 | 1.69065e-05 | 1.40158e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4631.6 | 0.0648794 | 838.008ms | 4669 | 4890 | 1902.42 | 961.374 | 0.113901 | 1.11693 | 4.91026 | 0.702292 | 0.00107203 | 1.58554e-05 | 1.97097e-06 | 1(Win) | true |
| simdjson (ondemand) | 4357.14 | 0.106019 | 842.809ms | 4669 | 1280 | 1502.52 | 1021.93 | 0.228413 | 1.18698 | 5.293 | 0.709574 | 0.00117413 | 1.38881e-05 | 1.17129e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6191.44 | 0.133448 | 863.391ms | 7932 | 40 | 106.333 | 1221.78 | 0.0429518 | 0.829063 | 3.66263 | 0.48525 | 0.000507438 | 6.30358e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5953.55 | 0.0956896 | 864.646ms | 7932 | 2560 | 3784.27 | 1270.59 | 0.0861252 | 0.857939 | 3.78114 | 0.475921 | 0.0009349 | 1.08835e-05 | 1.92062e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6602.68 | 0.0427547 | 856.784ms | 7932 | 640 | 153.558 | 1145.68 | 0.0914596 | 0.779032 | 3.50151 | 0.448941 | 0.000627797 | 9.84934e-06 | 7.87948e-07 | 1(Win) | true |
| simdjson (ondemand) | 6504.34 | 0.0679133 | 853.896ms | 7932 | 4890 | 3050.54 | 1163 | 0.0999706 | 0.796237 | 3.62002 | 0.439612 | 0.000747174 | 1.57783e-05 | 6.21335e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3011.69 | 0.0613372 | 882.945ms | 4669 | 4890 | 4021.45 | 1478.47 | 0.0614598 | 1.71659 | 7.67402 | 1.31334 | 0.00170502 | 2.82944e-05 | 8.84746e-06 | 1(Win) | true |
| simdjson (ondemand) | 2440.73 | 0.136007 | 921.403ms | 4669 | 320 | 1970.07 | 1824.33 | 0.294614 | 2.1164 | 9.88477 | 1.70765 | 0.00246439 | 1.47248e-05 | 6.69308e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3244 | 0.148006 | 869.39ms | 4669 | 640 | 2641.35 | 1372.6 | 0.280951 | 1.58954 | 7.4003 | 1.25166 | 0.00147214 | 9.37031e-06 | 1.00396e-06 | 1(Win) | true |
| simdjson (ondemand) | 2457.24 | 0.063333 | 918.869ms | 4669 | 4890 | 6440.51 | 1812.07 | 0.341911 | 2.09385 | 9.61105 | 1.64596 | 0.00269891 | 1.4629e-05 | 3.72294e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4464.26 | 0.0829933 | 909.306ms | 7932 | 160 | 316.427 | 1694.47 | 0.119732 | 1.1596 | 5.28101 | 0.819844 | 0.000989662 | 1.96987e-05 | 5.51563e-06 | 1(Win) | true |
| simdjson (ondemand) | 3704.29 | 0.0794042 | 937.087ms | 7932 | 2560 | 6731.05 | 2042.1 | 0.188311 | 1.37709 | 6.30446 | 1.02383 | 0.00146376 | 1.1967e-05 | 1.87138e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4691.37 | 0.0693693 | 898.805ms | 7932 | 4890 | 6118.01 | 1612.44 | 0.136255 | 1.09798 | 5.11989 | 0.783535 | 0.000907277 | 2.11151e-05 | 9.66807e-06 | 1(Win) | true |
| simdjson (ondemand) | 3861.75 | 0.309444 | 932.686ms | 7932 | 80 | 2939.35 | 1958.84 | 0.295854 | 1.33605 | 6.14334 | 0.987519 | 0.00162632 | 2.04866e-05 | 7.87948e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 536.428 | 0.103283 | 1552.2ms | 4604 | 160 | 11434.7 | 8185.1 | 0.0241234 | 9.29071 | 37.221 | 7.62685 | 0.0108968 | 4.34405e-05 | 5.43006e-06 | 1(Win) | true |
| simdjson (ondemand) | 519.278 | 0.0466597 | 1586.23ms | 4604 | 1280 | 19923.5 | 8455.43 | 0.0167486 | 9.7239 | 37.9751 | 7.14761 | 0.012256 | 9.19717e-05 | 4.07255e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 621.124 | 0.092421 | 1552.71ms | 4604 | 80 | 3414.65 | 7068.99 | 0.0911498 | 8.19072 | 32.6727 | 6.5947 | 0.00943745 | 0.000203627 | 0.000105886 | 1(Win) | true |
| simdjson (ondemand) | 598.639 | 0.139243 | 1577.23ms | 4604 | 30 | 3129.02 | 7334.5 | 0.108737 | 8.49668 | 33.6859 | 6.1705 | 0.0114248 | 0.000202722 | 8.6881e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1975.64 | 0.0781208 | 1627.22ms | 18245 | 320 | 15148 | 8807.15 | 0.00223545 | 2.56979 | 10.2952 | 1.97076 | 0.00263668 | 1.09619e-05 | 2.91176e-06 | 1(Win) | true |
| simdjson (ondemand) | 1891.35 | 0.069532 | 1664.95ms | 18245 | 640 | 26187.4 | 9199.65 | 0.139364 | 2.65177 | 10.5035 | 1.84385 | 0.00336608 | 6.32879e-05 | 3.8281e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2188.91 | 0.195614 | 1630.63ms | 18245 | 80 | 19342.9 | 7949.05 | 0.0311261 | 2.27567 | 9.16087 | 1.71324 | 0.00239244 | 2.53494e-05 | 6.85119e-06 | 1(Win) | true |
| simdjson (ondemand) | 2141.69 | 0.0415635 | 1649.41ms | 18245 | 2560 | 29190.2 | 8124.31 | 0.00311575 | 2.33693 | 9.42715 | 1.59858 | 0.00303788 | 1.94403e-05 | 7.98592e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 315.362 | 0.0688705 | 2134.6ms | 4604 | 320 | 29421.8 | 13922.8 | 0.100926 | 15.7691 | 69.8 | 14.8366 | 0.0187554 | 0.00012014 | 6.85545e-05 | 1(Win) | true |
| simdjson (ondemand) | 216.987 | 0.108849 | 2749.82ms | 4604 | 160 | 77620.1 | 20234.9 | 0.0784532 | 22.8859 | 110.717 | 22.8344 | 0.022061 | 0.000101814 | 4.2083e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 343.119 | 0.0259148 | 2138.81ms | 4604 | 4890 | 53775.9 | 12796.5 | 0.261649 | 14.6251 | 65.3907 | 13.8285 | 0.0170107 | 0.000127834 | 6.70263e-05 | 1(Win) | true |
| simdjson (ondemand) | 233.777 | 0.0597039 | 2744.16ms | 4604 | 640 | 80473.5 | 18781.7 | 0.029691 | 21.4978 | 106.367 | 21.8387 | 0.0225643 | 0.00021313 | 0.000102492 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1168.29 | 0.0334691 | 2246.43ms | 18245 | 2560 | 63608.7 | 14893.4 | 0.262233 | 4.3146 | 18.8013 | 3.83171 | 0.00450573 | 8.00947e-05 | 4.64168e-05 | 1(Win) | true |
| simdjson (ondemand) | 848.527 | 0.0507545 | 2828.75ms | 18245 | 640 | 69324.2 | 20505.9 | 0.15353 | 5.96528 | 28.8337 | 5.79734 | 0.00551298 | 1.62716e-05 | 3.51124e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1279.09 | 0.0728682 | 2227.76ms | 18245 | 320 | 31442.2 | 13603.3 | 0.0929978 | 3.96334 | 17.7022 | 3.58012 | 0.00407851 | 1.23321e-05 | 1.54152e-06 | 1(Win) | true |
| simdjson (ondemand) | 884.779 | 0.0223741 | 2823.75ms | 18245 | 4890 | 94670.9 | 19665.7 | 0.0894624 | 5.63756 | 27.7221 | 5.54335 | 0.00526812 | 6.48299e-05 | 4.016e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3773.11 | 0.133211 | 857.676ms | 4604 | 640 | 1537.92 | 1163.69 | 0.0421435 | 1.35902 | 6.8497 | 0.96894 | 0.000456464 | 1.83265e-05 | 3.05441e-06 | 1(Win) | true |
| Jsonifier (generic) | 3377.59 | 0.0476831 | 876.287ms | 4604 | 160 | 61.4761 | 1299.96 | 0.0312413 | 1.51675 | 6.74348 | 0.943962 | 0.000685545 | 1.08601e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3873.49 | 0.0387765 | 856.971ms | 4604 | 320 | 61.8235 | 1133.53 | 0.0473957 | 1.32566 | 6.76238 | 0.949392 | 0.000454768 | 2.37565e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 3438 | 0.0489904 | 872.303ms | 4604 | 80 | 31.3163 | 1277.11 | 0.0107653 | 1.48822 | 6.65617 | 0.924414 | 0.000662467 | 2.71503e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10007.2 | 0.107789 | 912.882ms | 18245 | 30 | 105.375 | 1738.73 | 0.00575164 | 0.507259 | 2.54223 | 0.275199 | 0.000164429 | 7.30794e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9604.59 | 0.06995 | 924.111ms | 18245 | 1280 | 2055.49 | 1811.61 | 0.00250116 | 0.527702 | 2.65793 | 0.285722 | 0.000117369 | 7.15093e-06 | 1.11332e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10170 | 0.0887111 | 917.588ms | 18245 | 40 | 92.1436 | 1710.9 | 0.140474 | 0.499455 | 2.5202 | 0.270266 | 0.00017128 | 1.37024e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9700.86 | 0.0915715 | 919.979ms | 18245 | 30 | 80.9299 | 1793.63 | 0.029726 | 0.523219 | 2.6359 | 0.280789 | 0.000160775 | 1.27889e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2820.56 | 0.187211 | 899.358ms | 4604 | 320 | 2717.77 | 1556.68 | 0.0860464 | 1.8019 | 9.44461 | 1.6755 | 0.000659752 | 2.85078e-05 | 1.35752e-06 | 1(Win) | true |
| simdjson (ondemand) | 2164.16 | 0.0693518 | 942.607ms | 4604 | 160 | 316.758 | 2028.83 | 0.132332 | 2.35018 | 13.318 | 2.38445 | 0.00100049 | 1.22176e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2881.53 | 0.043308 | 915.62ms | 4604 | 320 | 139.351 | 1523.74 | 0.0857999 | 1.76848 | 9.3573 | 1.65595 | 0.000653644 | 1.69689e-05 | 6.78758e-06 | 1(Win) | true |
| simdjson (ondemand) | 2189.73 | 0.0629554 | 946.39ms | 4604 | 2560 | 4079.4 | 2005.14 | 0.0404008 | 2.31375 | 13.2307 | 2.3649 | 0.000940928 | 1.62053e-05 | 4.92099e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7851.42 | 0.206008 | 966.526ms | 18245 | 30 | 625.292 | 2216.13 | 0.0120344 | 0.644171 | 3.30743 | 0.461058 | 0.000219238 | 9.13492e-06 | 3.65397e-06 | 1(Win) | true |
| simdjson (ondemand) | 6499.4 | 0.0468727 | 1010.44ms | 18245 | 2560 | 4031.08 | 2677.14 | 0.0879014 | 0.777592 | 4.29022 | 0.642916 | 0.000246129 | 6.48722e-06 | 9.20629e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8027.06 | 0.0447662 | 962.693ms | 18245 | 4890 | 4604.52 | 2167.64 | 0.134567 | 0.633944 | 3.28539 | 0.456125 | 0.000236712 | 7.95803e-06 | 1.64765e-06 | 1(Win) | true |
| simdjson (ondemand) | 6532.31 | 0.0846254 | 1009.43ms | 18245 | 1280 | 6503.78 | 2663.65 | 0.055259 | 0.770803 | 4.26818 | 0.637983 | 0.000255078 | 6.46581e-06 | 7.70759e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1185.22 | 0.110585 | 1137.68ms | 4926 | 640 | 12295.8 | 3963.64 | 0.100427 | 4.22361 | 17.335 | 3.39424 | 0.00431448 | 3.55258e-05 | 1.26878e-05 | 1(Win) | true |
| simdjson (ondemand) | 1017.87 | 0.0546726 | 1209.11ms | 4926 | 1280 | 8149.92 | 4615.32 | 0.0704695 | 4.92404 | 19.2962 | 3.52761 | 0.00340239 | 6.04255e-05 | 1.47495e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1446.69 | 0.135821 | 1113.13ms | 4926 | 640 | 12449.5 | 3247.26 | 0.0616764 | 3.4699 | 14.6204 | 2.79233 | 0.00434239 | 3.96493e-05 | 8.88145e-06 | 1(Win) | true |
| simdjson (ondemand) | 1231.36 | 0.0603193 | 1170.62ms | 4926 | 1280 | 6778.69 | 3815.15 | 0.0360331 | 4.14336 | 16.5869 | 2.92773 | 0.00397461 | 8.32636e-05 | 4.26627e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1894.35 | 0.0554395 | 1156.89ms | 8150 | 1280 | 6622.85 | 4102.97 | 0.154489 | 2.64848 | 11.0614 | 2.07337 | 0.00258407 | 2.78949e-05 | 8.91488e-06 | 1(Win) | true |
| simdjson (ondemand) | 1624.64 | 0.0529857 | 1223.83ms | 8150 | 1280 | 8224.82 | 4784.09 | 0.153284 | 3.08904 | 12.1321 | 2.1492 | 0.00220236 | 3.91104e-05 | 1.16948e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2320.89 | 0.0905771 | 1116.07ms | 8150 | 160 | 1472.19 | 3348.91 | 0.179029 | 2.17011 | 9.42503 | 1.71129 | 0.00260353 | 2.30061e-05 | 1.53374e-06 | 1(Win) | true |
| simdjson (ondemand) | 1910.56 | 0.200138 | 1191.22ms | 8150 | 40 | 2651.62 | 4068.15 | 0.0454545 | 2.62434 | 10.5183 | 1.79313 | 0.00277301 | 4.29448e-05 | 3.37423e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 770.226 | 0.105047 | 1349.89ms | 4926 | 40 | 1642.04 | 6099.25 | 0.165046 | 6.48722 | 27.5292 | 5.52071 | 0.00776492 | 7.10516e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 407.875 | 0.0220434 | 1895.11ms | 4926 | 4890 | 31520.9 | 11517.7 | 0.150169 | 12.2204 | 52.1427 | 10.4145 | 0.0284836 | 5.2474e-05 | 1.24958e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.211 | 0.0265825 | 1318.79ms | 4926 | 4890 | 9601.27 | 5271.26 | 0.137462 | 5.62411 | 24.867 | 4.9322 | 0.00751569 | 5.67914e-05 | 1.40733e-05 | 1(Win) | true |
| simdjson (ondemand) | 442.994 | 0.17782 | 1846.33ms | 4926 | 4890 | 1.73886e+06 | 10604.7 | 0.0443003 | 11.2931 | 49.4827 | 9.82643 | 0.0259913 | 5.43421e-05 | 1.44054e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1180.11 | 0.0326354 | 1401.01ms | 8150 | 2560 | 11827.4 | 6586.22 | 0.119021 | 4.23238 | 17.6426 | 3.51301 | 0.00581609 | 2.60257e-05 | 5.84739e-06 | 1(Win) | true |
| simdjson (ondemand) | 677.731 | 0.028465 | 1921.83ms | 8150 | 4890 | 52111.4 | 11468.3 | 0.0975154 | 7.42938 | 31.7492 | 6.26565 | 0.0159021 | 3.49781e-05 | 1.36249e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1343.4 | 0.104976 | 1370.36ms | 8150 | 40 | 1475.52 | 5785.65 | 0.172852 | 3.72206 | 16.02 | 3.15423 | 0.00557362 | 1.84049e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 738.214 | 0.0747997 | 1845.35ms | 8150 | 640 | 39694.5 | 10528.7 | 0.0889186 | 6.86795 | 30.1415 | 5.91019 | 0.0153296 | 5.61733e-05 | 2.49233e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2450.88 | 0.043296 | 932.385ms | 4926 | 640 | 440.777 | 1916.78 | 0.0277235 | 2.10668 | 8.99777 | 1.6754 | 0.0022413 | 1.39566e-05 | 6.34389e-07 | 1(Win) | true |
| simdjson (ondemand) | 1987.31 | 0.0550204 | 974.801ms | 4926 | 640 | 1082.65 | 2363.9 | 0.0889813 | 2.58779 | 10.2946 | 1.76451 | 0.00305775 | 4.25041e-05 | 2.22036e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2683.64 | 0.0369262 | 923.937ms | 4926 | 1280 | 534.837 | 1750.54 | 0.19671 | 1.92458 | 8.39281 | 1.52761 | 0.00249172 | 2.06176e-05 | 2.22036e-06 | 1(Win) | true |
| simdjson (ondemand) | 2104.54 | 0.119029 | 974.077ms | 4926 | 40 | 282.384 | 2232.22 | 0.21962 | 2.40088 | 9.68961 | 1.61673 | 0.00341048 | 1.52253e-05 | 5.07511e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3578.5 | 0.0983056 | 960.728ms | 8150 | 1280 | 5835.52 | 2171.99 | 0.557387 | 1.42274 | 6.06884 | 1.05423 | 0.00148505 | 5.2339e-05 | 2.41564e-05 | 1(Win) | true |
| simdjson (ondemand) | 3097.83 | 0.0939865 | 1007.58ms | 8150 | 640 | 3558.86 | 2509 | 0.0821366 | 1.63084 | 6.59742 | 1.06663 | 0.00163133 | 1.57209e-05 | 2.68405e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3881.62 | 0.156902 | 956.118ms | 8150 | 320 | 3158.62 | 2002.37 | 0.218791 | 1.3098 | 5.70319 | 0.964908 | 0.00159931 | 1.57209e-05 | 1.53374e-06 | 1(Win) | true |
| simdjson (ondemand) | 3374.43 | 0.0829873 | 994.211ms | 8150 | 640 | 2338.4 | 2303.34 | 0.133612 | 1.51998 | 6.23178 | 0.977301 | 0.00183934 | 2.60736e-05 | 1.20782e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1908.04 | 0.0588629 | 993.476ms | 4926 | 2560 | 5376.94 | 2462.1 | 0.115078 | 2.66823 | 12.0747 | 2.30776 | 0.0025661 | 7.29547e-05 | 3.33847e-05 | 1(Win) | true |
| simdjson (ondemand) | 1386.96 | 0.0563397 | 1078.33ms | 4926 | 2560 | 9322.49 | 3387.12 | 0.00791077 | 3.64116 | 15.0181 | 2.75071 | 0.00633318 | 4.81343e-05 | 2.07762e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1998.01 | 0.0382587 | 993.54ms | 4926 | 4890 | 3956.97 | 2351.24 | 0.0288116 | 2.53997 | 11.4633 | 2.15814 | 0.00419086 | 2.12138e-05 | 3.32114e-06 | 1(Win) | true |
| simdjson (ondemand) | 1508.39 | 0.0718661 | 1064.78ms | 4926 | 160 | 801.543 | 3114.44 | 0.0779239 | 3.39789 | 14.4066 | 2.6011 | 0.0056892 | 2.03004e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2722.83 | 0.0564732 | 1026.1ms | 8150 | 2560 | 6652.7 | 2854.54 | 0.104822 | 1.8669 | 8.0335 | 1.45325 | 0.00204357 | 3.94459e-05 | 1.94594e-05 | 1(Win) | true |
| simdjson (ondemand) | 2224.58 | 0.0396758 | 1093.33ms | 8150 | 4890 | 9396.78 | 3493.89 | 0.0172799 | 2.27797 | 9.49166 | 1.67055 | 0.00371112 | 5.23166e-05 | 2.86048e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2816.72 | 0.173949 | 1033.82ms | 8150 | 40 | 921.579 | 2759.4 | 0.0446757 | 1.78942 | 7.66393 | 1.36282 | 0.00299387 | 1.84049e-05 | 9.20245e-06 | 1(Win) | true |
| simdjson (ondemand) | 2360.13 | 0.0354699 | 1082.11ms | 8150 | 4890 | 6672.25 | 3293.23 | 0.0836757 | 2.1538 | 9.12209 | 1.58012 | 0.00367205 | 2.84291e-05 | 1.31482e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1998.97 | 0.139847 | 875.684ms | 2821 | 320 | 1133.59 | 1345.85 | 0.00441151 | 2.60495 | 9.29032 | 1.72705 | 0.000369993 | 8.97288e-05 | 2.65863e-05 | 1(Win) | true |
| simdjson (ondemand) | 1939.32 | 0.142336 | 883.385ms | 2821 | 80 | 311.911 | 1387.25 | 0.233729 | 2.6809 | 9.81886 | 1.59731 | 0.000354484 | 4.87416e-05 | 2.65863e-05 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2176.79 | 0.0529475 | 863.618ms | 2821 | 1280 | 548.121 | 1235.91 | 0.109932 | 2.3628 | 8.65686 | 1.56611 | 0.000390487 | 0.000120469 | 4.65261e-05 | 1(Win) | true |
| simdjson (ondemand) | 2059.1 | 0.136216 | 879.079ms | 2821 | 160 | 506.79 | 1306.55 | 0.0583258 | 2.53429 | 9.41865 | 1.49734 | 0.000354484 | 5.76037e-05 | 2.21553e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2545.41 | 0.0653919 | 882.873ms | 3770 | 2560 | 2184.01 | 1412.48 | 0.0548427 | 2.01266 | 7.41326 | 1.30345 | 0.00026836 | 3.55396e-05 | 7.46021e-06 | 1(Win) | true |
| simdjson (ondemand) | 2464.37 | 0.0880009 | 884.048ms | 3770 | 2560 | 4219.74 | 1458.93 | 0.0207279 | 2.09733 | 7.73369 | 1.22653 | 0.000270018 | 4.51757e-05 | 2.30023e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2824.75 | 0.0756497 | 872.635ms | 3770 | 320 | 296.679 | 1272.8 | 0.150278 | 1.84634 | 6.94907 | 1.18621 | 0.00026691 | 3.39854e-05 | 2.48674e-06 | 1(Win) | true |
| simdjson (ondemand) | 2645.53 | 0.106491 | 879.283ms | 3770 | 320 | 670.25 | 1359.03 | 0.0211593 | 1.97042 | 7.37639 | 1.1366 | 0.000267739 | 3.73011e-05 | 1.74072e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 826.315 | 0.150133 | 1061.32ms | 2821 | 30 | 716.786 | 3255.8 | 0 | 6.19534 | 26.0635 | 4.83162 | 0.00159518 | 1.18161e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 301.664 | 0.0249657 | 1639.12ms | 2821 | 4890 | 24241.2 | 8918.25 | 0.245991 | 16.5669 | 76.3134 | 15.369 | 0.0162771 | 0.00021762 | 0.0001062 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 842.923 | 0.135115 | 1064.95ms | 2821 | 40 | 743.874 | 3191.65 | 0.0130532 | 5.98669 | 25.4353 | 4.67068 | 0.00167494 | 1.77242e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 304.886 | 0.065254 | 1642.16ms | 2821 | 640 | 21219 | 8824 | 0.0983739 | 16.366 | 75.8408 | 15.2496 | 0.016283 | 4.76338e-05 | 5.53882e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 985.365 | 0.0707827 | 1111.76ms | 3770 | 320 | 2134.48 | 3648.75 | 0.0179824 | 5.11649 | 20.5735 | 3.80265 | 0.00210212 | 6.46552e-05 | 2.07228e-05 | 1(Win) | true |
| simdjson (ondemand) | 412.636 | 0.137896 | 1630.4ms | 3770 | 80 | 11549 | 8713.14 | 0.053827 | 12.2991 | 56.7151 | 11.3637 | 0.0112135 | 0.00015252 | 8.62069e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1023.74 | 0.123049 | 1107.59ms | 3770 | 40 | 746.999 | 3511.97 | 0.1038 | 4.90279 | 20.1103 | 3.68488 | 0.00157162 | 0.000225464 | 0.00015252 | 1(Win) | true |
| simdjson (ondemand) | 407.156 | 0.0314944 | 1634.63ms | 3770 | 4890 | 37821.2 | 8830.4 | 0.366632 | 12.2537 | 56.3615 | 11.2743 | 0.0119892 | 5.90172e-05 | 1.70868e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5885.66 | 0.0715672 | 788.71ms | 2821 | 4890 | 523.303 | 457.097 | 0.171467 | 0.922264 | 3.73626 | 0.51223 | 0.000358254 | 1.97902e-05 | 3.55209e-06 | 1(Win) | true |
| simdjson (ondemand) | 5110.81 | 0.147709 | 793.55ms | 2821 | 1280 | 773.839 | 526.397 | 0.134049 | 1.04604 | 4.03935 | 0.484225 | 0.00106345 | 4.70799e-05 | 1.32932e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5848.4 | 0.116049 | 786.866ms | 2821 | 4890 | 1393.55 | 460.009 | 0.0583857 | 0.942091 | 3.65757 | 0.494151 | 0.000711796 | 4.7482e-05 | 2.182e-05 | 1(Win) | true |
| simdjson (ondemand) | 5382.2 | 0.180925 | 788.064ms | 2821 | 1280 | 1046.87 | 499.854 | 0.158265 | 1.00345 | 3.96065 | 0.466147 | 0.00106595 | 2.74171e-05 | 5.53882e-07 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6285.72 | 0.124188 | 787.545ms | 3770 | 80 | 40.3669 | 571.987 | 0.211532 | 0.860567 | 3.25464 | 0.406101 | 0.000265252 | 1.65782e-05 | 6.6313e-06 | 1(Win) | true |
| simdjson (ondemand) | 6232.59 | 0.10044 | 798.375ms | 3770 | 2560 | 859.415 | 576.863 | 0.0788828 | 0.853928 | 3.35093 | 0.37825 | 0.000796481 | 1.48168e-05 | 3.73011e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6477.72 | 0.308392 | 800.069ms | 3770 | 30 | 87.8954 | 555.033 | 0.0781344 | 0.83374 | 3.29204 | 0.364721 | 0.000795756 | 0 | 0 | 1(Win) | true |
| Jsonifier (generic) | 6396.6 | 0.0318878 | 800.177ms | 3770 | 4890 | 157.088 | 562.072 | 0.0822639 | 0.830867 | 3.19576 | 0.392573 | 0.000268832 | 1.84429e-05 | 1.7358e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4100.35 | 0.055349 | 810.454ms | 2821 | 4890 | 644.902 | 656.119 | 0.142534 | 1.28671 | 5.43353 | 0.868487 | 0.000833944 | 3.01565e-05 | 4.27701e-06 | 1(Win) | true |
| simdjson (ondemand) | 3391.15 | 0.0953165 | 821.977ms | 2821 | 1280 | 731.91 | 793.334 | 0.000689333 | 1.54035 | 6.44771 | 0.991138 | 0.00115595 | 1.68934e-05 | 2.49247e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4153.84 | 0.056091 | 808.856ms | 2821 | 160 | 21.116 | 647.669 | 0.0956263 | 1.26914 | 5.35519 | 0.850762 | 0.00141351 | 1.10776e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3488.93 | 0.134163 | 821.211ms | 2821 | 2560 | 2739.86 | 771.1 | 0.0474441 | 1.50147 | 6.36937 | 0.973414 | 0.00117132 | 2.61709e-05 | 2.63094e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4763.91 | 0.256326 | 811.606ms | 3770 | 320 | 1197.54 | 754.706 | 0.0621489 | 1.1007 | 4.54748 | 0.680902 | 0.000633289 | 2.23806e-05 | 7.46021e-06 | 1(Win) | true |
| simdjson (ondemand) | 4277.42 | 0.100876 | 825.503ms | 3770 | 2560 | 1840.5 | 840.541 | 0.0691041 | 1.21908 | 5.16366 | 0.759682 | 0.000861655 | 2.6318e-05 | 9.11804e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4791.8 | 0.0506695 | 815.589ms | 3770 | 640 | 92.5037 | 750.314 | 0.180876 | 1.09067 | 4.48886 | 0.667639 | 0.000939987 | 1.11903e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 4397.04 | 0.211889 | 822.223ms | 3770 | 40 | 120.071 | 817.675 | 0.0600937 | 1.18298 | 5.10504 | 0.746419 | 0.00081565 | 0 | 0 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4284.44 | 0.0685713 | 6909.38ms | 277673 | 640 | 1.14959e+06 | 61807.2 | 0.11291 | 1.16493 | 4.33474 | 0.685588 | 0.00464475 | 4.19783e-06 | 3.27499e-06 | 1(Win) | true |
| simdjson (ondemand) | 3681.64 | 0.0900411 | 4055.13ms | 277673 | 1280 | 5.36879e+06 | 71927.1 | 0.0449409 | 1.36162 | 4.74902 | 0.794456 | 0.00395819 | 4.43136e-06 | 2.25929e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3597.57 | 0.135724 | 4195.86ms | 10548466 | 80 | 1.15229e+09 | 2.79628e+06 | 0.190146 | 1.37877 | 4.33231 | 0.685511 | 0.0100591 | 0.0172613 | 2.68297e-05 | 1(Win) | true |
| simdjson (ondemand) | 3218.58 | 0.205809 | 4698.54ms | 10548466 | 80 | 3.31033e+09 | 3.12554e+06 | 0.187597 | 1.54139 | 4.7454 | 0.794478 | 0.00979735 | 0.0178538 | 8.10663e-05 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3597.27 | 0.195183 | 6353.82ms | 16002592 | 80 | 5.48539e+09 | 4.24245e+06 | 0.313838 | 1.38224 | 7.6565 | 1.20636 | 0.000877169 | 0.0336236 | 0.00233338 | 1(Win) | true |
| simdjson (ondemand) | 3098.07 | 0.16053 | 7429.91ms | 16002592 | 30 | 1.87601e+09 | 4.92605e+06 | 0.414391 | 1.60673 | 8.45534 | 1.25311 | 0.0014588 | 0.0372146 | 0.00656708 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3519.78 | 0.121996 | 6495.89ms | 16002591 | 40 | 1.11918e+09 | 4.33586e+06 | 0.0638455 | 1.40689 | 7.93974 | 1.29591 | 0.000830775 | 0.0366142 | 0.00423129 | 1(Win) | true |
| simdjson (ondemand) | 1650.19 | 0.174804 | 6471.52ms | 16002591 | 30 | 7.84041e+09 | 9.24819e+06 | 0.179277 | 3.00911 | 12.9509 | 2.14169 | 0.001414 | 0.0540751 | 0.00729496 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 17977.5 | 0.0751484 | 5490.13ms | 16197086 | 160 | 6.67072e+07 | 859225 | 0.102206 | 0.280007 | 1.3364 | 0.070273 | 7.80248e-05 | 0.0157086 | 0.00027093 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 17977.5 | 0.130652 | 5591.34ms | 16197086 | 80 | 1.00818e+08 | 859228 | 0.381431 | 0.277421 | 1.25971 | 0.0749137 | 9.86914e-05 | 0.0157237 | 0.000181817 | 1(Tie) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 17554.1 | 0.239578 | 5614.92ms | 16197085 | 40 | 1.77776e+08 | 879953 | 0.0501699 | 0.282909 | 1.34053 | 0.0717036 | 9.34211e-05 | 0.0157309 | 0.000344997 | 1(Win) | true |
| simdjson (ondemand) | 16574.4 | 0.0697275 | 6490.07ms | 16197085 | 80 | 3.37829e+07 | 931965 | 0.802564 | 0.29896 | 1.33418 | 0.0897197 | 0.000112388 | 0.0157402 | 0.000140007 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1944.2 | 0.164687 | 4013.73ms | 4212000 | 30 | 3.47322e+08 | 2.06608e+06 | 0.231485 | 2.54869 | 11.5378 | 2.12714 | 0.0112204 | 0.0659634 | 0.00727124 | 1(Win) | true |
| simdjson (ondemand) | 1491.29 | 0.151276 | 4931.86ms | 4212000 | 80 | 1.32826e+09 | 2.69355e+06 | 1.15116 | 3.28816 | 13.1567 | 2.37706 | 0.0128458 | 0.0658727 | 0.0125571 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1451.79 | 0.161577 | 5064.93ms | 4212000 | 40 | 7.99449e+08 | 2.76685e+06 | 0.159712 | 3.40162 | 15.305 | 2.93106 | 0.0119021 | 0.0664634 | 0.0144802 | 1(Win) | true |
| simdjson (ondemand) | 1241.76 | 0.139331 | 5775.92ms | 4212000 | 30 | 6.09421e+08 | 3.23482e+06 | 0.0890383 | 3.97847 | 16.7764 | 3.10709 | 0.0124397 | 0.0659325 | 0.0167239 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1802.25 | 0.118691 | 4249.12ms | 4211999 | 80 | 5.59849e+08 | 2.22881e+06 | 0.0170527 | 2.74605 | 12.4684 | 2.34289 | 0.0119204 | 0.0683636 | 0.00258848 | 1(Win) | true |
| simdjson (ondemand) | 1240.01 | 0.12826 | 5768.59ms | 4211999 | 40 | 6.90513e+08 | 3.2394e+06 | 0.268013 | 3.99782 | 15.3962 | 2.82659 | 0.013114 | 0.0677494 | 0.010542 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1443.08 | 0.147225 | 5105.85ms | 4211999 | 40 | 6.71764e+08 | 2.78353e+06 | 0.752256 | 3.45728 | 15.5255 | 2.98798 | 0.0123218 | 0.068515 | 0.0035311 | 1(Win) | true |
| simdjson (ondemand) | 1059.94 | 0.0976996 | 6616.55ms | 4211999 | 80 | 1.0967e+09 | 3.7897e+06 | 1.20837 | 4.66826 | 19.016 | 3.55664 | 0.0127043 | 0.0680986 | 0.0112339 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1239.79 | 0.0932953 | 5657.74ms | 4525120 | 80 | 8.43678e+08 | 3.48084e+06 | 0.149647 | 4.01738 | 16.7774 | 3.01585 | 0.0101136 | 0.0777319 | 0.00625407 | 1(Win) | true |
| simdjson (ondemand) | 1163.57 | 0.32005 | 5992.68ms | 4525120 | 30 | 4.22701e+09 | 3.70884e+06 | 0.68229 | 4.27742 | 17.1039 | 2.74461 | 0.0146775 | 0.0772545 | 0.00830175 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 731.063 | 0.212961 | 4305.98ms | 4525120 | 30 | 4.74102e+09 | 5.90304e+06 | 1.16558 | 6.81347 | 32.179 | 6.41867 | 0.0157319 | 0.0782832 | 0.0195433 | 1(Win) | true |
| simdjson (ondemand) | 552.419 | 0.121057 | 5676.81ms | 4525120 | 30 | 2.683e+09 | 7.81198e+06 | 0.0374476 | 9.06695 | 42.9826 | 8.45386 | 0.0257468 | 0.0776029 | 0.012711 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1122.66 | 0.0786493 | 6178.31ms | 4525119 | 40 | 3.65606e+08 | 3.84398e+06 | 0.0682911 | 4.42579 | 18.9978 | 3.57081 | 0.0105099 | 0.0773592 | 0.00217727 | 1(Win) | true |
| simdjson (ondemand) | 848.958 | 0.197898 | 8002.24ms | 4525119 | 40 | 4.04793e+09 | 5.08328e+06 | 0.06058 | 5.86975 | 22.0189 | 3.72942 | 0.017557 | 0.0940769 | 0.00391499 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 735.999 | 0.115901 | 4279.61ms | 4525119 | 40 | 1.84732e+09 | 5.86344e+06 | 0.323492 | 6.76733 | 31.9098 | 6.4203 | 0.0156258 | 0.07784 | 0.00287578 | 1(Win) | true |
| simdjson (ondemand) | 466.949 | 0.0943228 | 6630.75ms | 4525119 | 40 | 3.03958e+09 | 9.24188e+06 | 0.0477832 | 10.6491 | 47.898 | 9.43873 | 0.0286514 | 0.0946231 | 0.00280221 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1214.52 | 0.130688 | 5216.45ms | 4203059 | 80 | 1.48829e+09 | 3.30037e+06 | 0.058547 | 4.08447 | 17.995 | 3.46202 | 0.0141891 | 0.0893917 | 0.00118501 | 1(Win) | true |
| simdjson (ondemand) | 944.356 | 0.134982 | 6640.03ms | 4203059 | 40 | 1.31302e+09 | 4.24453e+06 | 0.0694691 | 5.25304 | 19.8723 | 3.60389 | 0.0285034 | 0.0887458 | 0.00162423 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 795.442 | 0.0677563 | 7944.39ms | 4203059 | 80 | 9.32618e+08 | 5.03915e+06 | 0.0181048 | 6.25299 | 28.081 | 5.61847 | 0.0223932 | 0.08915 | 0.00615907 | 1(Win) | true |
| simdjson (ondemand) | 712.541 | 0.138724 | 4116.53ms | 4203059 | 30 | 1.827e+09 | 5.62543e+06 | 0.0593854 | 7.0228 | 28.4918 | 5.259 | 0.0306889 | 0.0882788 | 0.0075629 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1106.22 | 0.116346 | 5757.19ms | 4203058 | 40 | 7.10903e+08 | 3.62347e+06 | 0.151505 | 4.50162 | 20.1353 | 3.99622 | 0.0155216 | 0.0886313 | 0.00274309 | 1(Win) | true |
| simdjson (ondemand) | 744.589 | 0.110312 | 8359.31ms | 4203058 | 30 | 1.05795e+09 | 5.38331e+06 | 0.214713 | 6.65774 | 24.5043 | 4.5173 | 0.0295885 | 0.104787 | 0.00610548 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 744.645 | 0.0991997 | 8481.55ms | 4203058 | 30 | 8.5541e+08 | 5.3829e+06 | 0.230941 | 6.68988 | 30.2205 | 6.15264 | 0.0236582 | 0.0884515 | 0.00494079 | 1(Win) | true |
| simdjson (ondemand) | 589.55 | 0.0878117 | 4953.78ms | 4203058 | 40 | 1.42579e+09 | 6.799e+06 | 0.436503 | 8.46136 | 33.121 | 6.17147 | 0.0321567 | 0.104171 | 0.0141473 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1642.31 | 0.140987 | 7885.5ms | 4197496 | 40 | 4.72381e+08 | 2.43745e+06 | 0.220945 | 3.04026 | 15.8515 | 3.11185 | 0.000522276 | 0.0814504 | 0.00288092 | 1(Win) | true |
| simdjson (ondemand) | 1439.39 | 0.0779307 | 4349.48ms | 4197496 | 30 | 1.40916e+08 | 2.78107e+06 | 0.0363374 | 3.50902 | 18.3435 | 2.88754 | 0.0044991 | 0.0811075 | 0.00129908 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1041.11 | 0.0783334 | 5967.29ms | 4197496 | 30 | 2.72148e+08 | 3.84499e+06 | 0.0893637 | 4.84482 | 27.6305 | 5.67736 | 0.000901831 | 0.0816998 | 0.00270226 | 1(Win) | true |
| simdjson (ondemand) | 685.596 | 0.216495 | 4197.89ms | 4197496 | 30 | 4.79361e+09 | 5.83878e+06 | 0.162273 | 7.41624 | 36.2286 | 6.74789 | 0.0126048 | 0.0815426 | 0.0151949 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.14 | 0.121526 | 4313.38ms | 4197495 | 30 | 3.36222e+08 | 2.75475e+06 | 0.160159 | 3.47717 | 18.1267 | 3.64656 | 0.000729419 | 0.0844303 | 0.000500775 | 1(Win) | true |
| simdjson (ondemand) | 998.432 | 0.142514 | 6212.73ms | 4197495 | 80 | 2.61187e+09 | 4.00933e+06 | 0.368926 | 5.07217 | 23.4605 | 3.89976 | 0.00451478 | 0.104423 | 0.00655732 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1007.17 | 0.0662698 | 6116.48ms | 4197495 | 80 | 5.55005e+08 | 3.97455e+06 | 0.228094 | 5.00226 | 27.9087 | 5.76678 | 0.00127567 | 0.0846365 | 0.00119107 | 1(Win) | true |
| simdjson (ondemand) | 568.085 | 0.154541 | 5055.36ms | 4197495 | 30 | 3.55766e+09 | 7.04656e+06 | 0.613365 | 8.90924 | 41.3455 | 7.76009 | 0.0132653 | 0.104733 | 0.00725483 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.94 | 0.114617 | 5055.73ms | 4506447 | 80 | 8.61651e+08 | 2.86333e+06 | 0.363433 | 3.32873 | 16.005 | 3.04443 | 0.00849481 | 0.0807242 | 0.00161376 | 1(Win) | true |
| simdjson (ondemand) | 1148.16 | 0.194334 | 6404.93ms | 4506447 | 40 | 2.11651e+09 | 3.7431e+06 | 0.187056 | 4.38294 | 17.9031 | 3.21138 | 0.0137102 | 0.0791223 | 0.00145604 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 869.798 | 0.114794 | 8196.29ms | 4506447 | 80 | 2.57371e+09 | 4.94101e+06 | 0.03062 | 5.78858 | 26.8482 | 5.41419 | 0.0109681 | 0.0811429 | 0.0124518 | 1(Win) | true |
| simdjson (ondemand) | 457.697 | 0.0931445 | 6972.03ms | 4506447 | 40 | 3.05976e+09 | 9.3898e+06 | 0.0314011 | 10.9721 | 46.5708 | 9.22054 | 0.0375339 | 0.0795122 | 0.0120142 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1366.8 | 0.135145 | 5473.62ms | 4506446 | 30 | 5.41725e+08 | 3.14434e+06 | 0.264884 | 3.69175 | 17.6722 | 3.46198 | 0.01119 | 0.0812716 | 0.0036572 | 1(Win) | true |
| simdjson (ondemand) | 923.918 | 0.130865 | 7801.61ms | 4506446 | 30 | 1.11165e+09 | 4.65159e+06 | 0.0265686 | 5.43578 | 21.5589 | 3.9297 | 0.0138152 | 0.0861559 | 0.00267231 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 868.539 | 0.111455 | 8207.21ms | 4506446 | 40 | 1.2166e+09 | 4.94817e+06 | 0.493785 | 5.76583 | 26.7043 | 5.42899 | 0.0111463 | 0.0815233 | 0.00711753 | 1(Win) | true |
| simdjson (ondemand) | 414.371 | 0.13144 | 7581.13ms | 4506446 | 40 | 7.4337e+09 | 1.03716e+07 | 0.303288 | 12.0635 | 50.2261 | 9.93867 | 0.0370211 | 0.086186 | 0.0167962 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1968.16 | 0.0920486 | 7122.5ms | 4219120 | 30 | 1.06237e+08 | 2.04438e+06 | 0.0821119 | 2.56464 | 9.33965 | 1.66924 | 0.0120387 | 0.0567872 | 0.000356733 | 1(Win) | true |
| simdjson (ondemand) | 1674.89 | 0.0750466 | 8227.68ms | 4219120 | 160 | 5.20059e+08 | 2.40234e+06 | 0.105223 | 2.98886 | 9.79974 | 1.58779 | 0.0167086 | 0.0548804 | 0.00183977 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 705.572 | 0.111012 | 4195.06ms | 4219120 | 30 | 1.20233e+09 | 5.7027e+06 | 0.137689 | 7.14792 | 26.6021 | 4.95737 | 0.0172007 | 0.0578582 | 0.00625802 | 1(Win) | true |
| simdjson (ondemand) | 265.129 | 0.122974 | 4642.32ms | 4219120 | 30 | 1.0449e+10 | 1.51763e+07 | 0.453262 | 19.0551 | 79.8997 | 16.1062 | 0.0816303 | 0.0554709 | 0.0109628 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1815.16 | 0.0865824 | 7601.88ms | 4219119 | 160 | 5.8938e+08 | 2.21671e+06 | 0.0729237 | 2.7543 | 10.3657 | 1.92471 | 0.0120693 | 0.0563358 | 0.000762676 | 1(Win) | true |
| simdjson (ondemand) | 1377.03 | 0.201637 | 4737.62ms | 4219119 | 30 | 1.0414e+09 | 2.92198e+06 | 0.0145767 | 3.61367 | 12.0005 | 2.01584 | 0.0186971 | 0.0548037 | 0.00119634 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.332 | 0.0774296 | 8470.75ms | 4219119 | 80 | 1.39034e+09 | 5.38404e+06 | 0.304158 | 6.75104 | 26.4994 | 4.96163 | 0.0169591 | 0.0573859 | 0.000856423 | 1(Win) | true |
| simdjson (ondemand) | 255.155 | 0.10289 | 4799.87ms | 4219119 | 30 | 7.89778e+09 | 1.57695e+07 | 0.608735 | 19.7289 | 82.0999 | 16.5342 | 0.0840414 | 0.0558012 | 0.0101008 | 2(Loss) | true |
