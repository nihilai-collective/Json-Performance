# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Windows 10.0.26200 using the MSVC 19.52.37029.0 compiler).  

Latest Results: (Nov 14, 2026)
#### Using the following commits:
----
| Jsonifier (Generic): [d4727ec](https://github.com/nihilai-collective/Jsonifier/commit/d4727ec)  
| simdjson: [449f38e63](https://github.com/simdjson/simdjson/commit/449f38e63)  

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
*Environment generated via BenchmarkSuite commit: [27950a9](https://github.com/nihilai-collective/benchmarksuite/commit/27950a9)*

----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 239.434 | 0.0790359 | 367.258ms | 905 | 4890 | 39690 | 3604.64 | 0.252034 | 12.6246 | 1(Win) | true |
| simdjson (ondemand) | 119.705 | 0.138696 | 708.326ms | 905 | 30 | 3000 | 7210 | 0.551724 | 25.3172 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 246.197 | 0.247919 | 356.132ms | 905 | 4890 | 369367 | 3505.62 | 0.281157 | 12.2784 | 1(Win) | true |
| simdjson (ondemand) | 127.438 | 0.105573 | 692.499ms | 905 | 40 | 2044.87 | 6772.5 | 0.631501 | 23.786 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 471.886 | 0.158244 | 357.263ms | 1811 | 80 | 2683.54 | 3660 | 0.480439 | 6.39671 | 1(Win) | true |
| simdjson (ondemand) | 266.657 | 0.303824 | 674.693ms | 1811 | 320 | 123915 | 6476.88 | 0.0289575 | 11.3595 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 579.079 | 0.265409 | 305.826ms | 1811 | 40 | 2506.41 | 2982.5 | 0.308296 | 5.20939 | 1(Win) | true |
| simdjson (ondemand) | 274.111 | 0.392109 | 629.044ms | 1811 | 2560 | 1.56256e+06 | 6300.74 | 0.144661 | 11.0387 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.919 | 0.164963 | 454.278ms | 3862 | 4890 | 264626 | 4459.39 | 0.367757 | 3.6635 | 1(Win) | true |
| simdjson (ondemand) | 579.216 | 0.0644859 | 657.596ms | 3862 | 160 | 2690.25 | 6358.75 | 0.857533 | 5.23491 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 923.659 | 0.129107 | 414.043ms | 3862 | 80 | 2120.25 | 3987.5 | 1.23839 | 3.2638 | 1(Win) | true |
| simdjson (ondemand) | 605.771 | 0.0740189 | 620.734ms | 3862 | 80 | 1620.25 | 6080 | 0.620604 | 4.98892 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 758.662 | 0.234243 | 1385.49ms | 9578 | 30 | 23862.1 | 12040 | 0.249792 | 3.99706 | 1(Win) | true |
| simdjson (ondemand) | 734.946 | 0.361384 | 1249.18ms | 9578 | 4890 | 9.86473e+06 | 12428.5 | 0.131421 | 4.128 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1123.53 | 0.460228 | 1043.15ms | 9578 | 40 | 56000 | 8130 | 0.326931 | 2.69709 | 1(Win) | true |
| simdjson (ondemand) | 1067.54 | 0.573906 | 1063.76ms | 9578 | 640 | 1.54328e+06 | 8556.41 | 0.118557 | 2.83893 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 834.369 | 0.118158 | 456.44ms | 3873 | 1280 | 35020.2 | 4426.8 | 0.11106 | 3.62599 | 1(Win) | true |
| simdjson (ondemand) | 566.283 | 0.287727 | 662.028ms | 3873 | 640 | 225408 | 6522.5 | 0.0478881 | 5.34907 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 876.814 | 0.125715 | 433.539ms | 3873 | 40 | 1121.79 | 4212.5 | 1.11502 | 3.43258 | 1(Win) | true |
| simdjson (ondemand) | 611.52 | 0.173818 | 623.525ms | 3873 | 160 | 17635.2 | 6040 | 0.248963 | 4.95136 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 744.273 | 0.454658 | 6204.44ms | 94653 | 2560 | 7.78419e+08 | 121284 | 1.12141 | 4.08227 | 1(Win) | true |
| simdjson (ondemand) | 645.583 | 0.431484 | 7161.11ms | 94653 | 2560 | 9.31825e+08 | 139824 | 0.310445 | 4.7065 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1239.8 | 0.386841 | 9020.47ms | 94653 | 1280 | 1.0154e+08 | 72808.4 | 0.756691 | 2.45054 | 1(Win) | true |
| simdjson (ondemand) | 1063.08 | 0.10544 | 5214.17ms | 94653 | 2560 | 2.05206e+07 | 84911.8 | 0.232212 | 2.85802 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1037.52 | 0.809169 | 6165.33ms | 124597 | 160 | 1.3741e+08 | 114528 | 1.39159 | 2.92872 | 1(Win) | true |
| simdjson (ondemand) | 981.335 | 0.328256 | 6413.34ms | 124597 | 40 | 6.31926e+06 | 121085 | 0.295062 | 3.09656 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1510.56 | 0.0908672 | 9585.81ms | 124597 | 320 | 1.63495e+06 | 78662.8 | 0.0974248 | 2.01139 | 1(Win) | true |
| simdjson (ondemand) | 1367.01 | 0.10363 | 5292.74ms | 124597 | 2560 | 2.0772e+07 | 86923.1 | 0.182245 | 2.22273 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 654.48 | 0.281125 | 7053.01ms | 94653 | 2560 | 3.84871e+08 | 137923 | 0.138942 | 4.64268 | 1(Win) | true |
| simdjson (ondemand) | 478.652 | 0.209744 | 9669.96ms | 94653 | 2560 | 4.00541e+08 | 188588 | 0.045258 | 6.34867 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 966.3 | 0.1475 | 5675.04ms | 94653 | 160 | 3.03772e+06 | 93416.2 | 0.137634 | 3.14458 | 1(Win) | true |
| simdjson (ondemand) | 629.073 | 0.0884944 | 8215.67ms | 94653 | 1280 | 2.064e+07 | 143494 | 0.212264 | 4.83067 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.458 | 0.400874 | 8100.34ms | 124597 | 2560 | 1.03967e+09 | 158972 | 0.427875 | 4.06518 | 1(Win) | true |
| simdjson (ondemand) | 574.021 | 0.462155 | 5262.76ms | 124597 | 1280 | 1.1715e+09 | 207004 | 0.504302 | 5.29366 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1180.23 | 0.154676 | 6041.75ms | 124597 | 2560 | 6.20822e+07 | 100679 | 0.132169 | 2.57466 | 1(Win) | true |
| simdjson (ondemand) | 824.218 | 0.217844 | 8286.85ms | 124597 | 160 | 1.57813e+07 | 144167 | 0.0576921 | 3.68692 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1304.85 | 0.248528 | 6915.35ms | 94653 | 2560 | 7.56733e+07 | 69179.2 | 0.19343 | 2.32836 | 1(Win) | true |
| simdjson (ondemand) | 1170.83 | 0.227078 | 7790.51ms | 94653 | 320 | 9.80802e+06 | 77097.5 | 0.0235147 | 2.59499 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.53 | 0.19333 | 5455.9ms | 94653 | 30 | 238437 | 46113.3 | 0.137532 | 1.5515 | 1(Win) | true |
| simdjson (ondemand) | 1557.78 | 0.151469 | 6609.79ms | 94653 | 1280 | 9.8609e+06 | 57946.8 | 0.169722 | 1.95028 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1587.7 | 0.545711 | 7494.68ms | 124597 | 1280 | 2.13509e+08 | 74841.1 | 0.598784 | 1.91349 | 1(Win) | true |
| simdjson (ondemand) | 1507.68 | 0.0786271 | 7891.25ms | 124597 | 4890 | 1.8778e+07 | 78813 | 0.110997 | 2.01517 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2325.83 | 0.172189 | 5935.36ms | 124597 | 4890 | 3.78426e+07 | 51089.3 | 0.0722992 | 1.30603 | 1(Win) | true |
| simdjson (ondemand) | 2042.65 | 0.132359 | 6679.22ms | 124597 | 320 | 1.89707e+06 | 58171.9 | 0.221818 | 1.48733 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1103.31 | 0.737851 | 8079.54ms | 94653 | 2560 | 9.3293e+08 | 81815.5 | 0.256683 | 2.75347 | 1(Win) | true |
| simdjson (ondemand) | 1024.36 | 0.243715 | 8796.74ms | 94653 | 2560 | 1.18079e+08 | 88121.8 | 0.0753449 | 2.96619 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1544.92 | 0.0426808 | 6675.07ms | 94653 | 2560 | 1.59208e+06 | 58429.1 | 0.11921 | 1.96643 | 1(Win) | true |
| simdjson (ondemand) | 1340.96 | 0.200605 | 7593.61ms | 94653 | 160 | 2.91772e+06 | 67316.2 | 0.0389798 | 2.26568 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.32 | 0.136953 | 8195.32ms | 124597 | 4890 | 6.13114e+07 | 81760.8 | 0.045763 | 2.09062 | 1(Win) | true |
| simdjson (ondemand) | 1396.75 | 0.290532 | 8768.73ms | 124597 | 40 | 2.44358e+06 | 85072.5 | 0.0892192 | 2.17523 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1951.13 | 0.0712599 | 7017.86ms | 124597 | 640 | 1.20535e+06 | 60900.6 | 0.343639 | 1.55716 | 1(Win) | true |
| simdjson (ondemand) | 1774.72 | 0.0460593 | 7567.39ms | 124597 | 4890 | 4.6505e+06 | 66954.2 | 0.431389 | 1.71194 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 396.029 | 0.788331 | 7747ms | 2090234 | 30 | 4.72361e+10 | 5.03348e+06 | 0.413372 | 7.67439 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 394.862 | 0.625497 | 7699.04ms | 2090234 | 80 | 7.97698e+10 | 5.04835e+06 | 2.08176 | 7.69693 | 1(Tie) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 428.358 | 1.09456 | 7631.41ms | 2090234 | 40 | 1.03779e+11 | 4.65358e+06 | 0.572355 | 7.09508 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 418.299 | 0.827899 | 7940.57ms | 2090234 | 80 | 1.24526e+11 | 4.76549e+06 | 1.99693 | 7.26565 | 1(Tie) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 951.139 | 0.427831 | 7827.03ms | 5212421 | 80 | 3.99969e+10 | 5.22631e+06 | 0.0781514 | 3.19533 | 1(Win) | true |
| simdjson (ondemand) | 927.872 | 0.364945 | 8047.25ms | 5212421 | 80 | 3.05807e+10 | 5.35737e+06 | 0.357568 | 3.27509 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1057.66 | 0.559796 | 7837.27ms | 5212421 | 40 | 2.7689e+10 | 4.69996e+06 | 0.154993 | 2.87341 | 1(Win) | true |
| simdjson (ondemand) | 981.592 | 0.492933 | 8357.16ms | 5212421 | 80 | 4.98521e+10 | 5.06417e+06 | 0.0947184 | 3.09595 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 387.121 | 0.371551 | 7715.63ms | 2090234 | 80 | 2.92836e+10 | 5.1493e+06 | 0.260013 | 7.85065 | 1(Win) | true |
| simdjson (ondemand) | 374.014 | 0.378896 | 7989.69ms | 2090234 | 80 | 3.26245e+10 | 5.32975e+06 | 0.0563899 | 8.12595 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 430.409 | 0.376161 | 7724.86ms | 2090234 | 80 | 2.42809e+10 | 4.63142e+06 | 0.0108486 | 7.06099 | 1(Win) | true |
| simdjson (ondemand) | 413.385 | 0.410373 | 8022.78ms | 2090234 | 80 | 3.13276e+10 | 4.82214e+06 | 0.0532464 | 7.35209 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 908.749 | 0.654536 | 8201.83ms | 5212421 | 30 | 3.84574e+10 | 5.47011e+06 | 0.622415 | 3.34442 | 1(Win) | true |
| simdjson (ondemand) | 870.142 | 0.33067 | 8628.42ms | 5212421 | 80 | 2.85482e+10 | 5.71281e+06 | 1.01241 | 3.49284 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 994.095 | 0.401995 | 8255.81ms | 5212421 | 80 | 3.23262e+10 | 5.00048e+06 | 0.137626 | 3.05721 | 1(Win) | true |
| simdjson (ondemand) | 953.991 | 0.61058 | 8556.42ms | 5212421 | 40 | 4.04889e+10 | 5.21069e+06 | 0.589623 | 3.18588 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8307.92 | 0.170428 | 6108.04ms | 2090234 | 80 | 1.33776e+07 | 239940 | 0.0333528 | 0.365751 | 1(Win) | true |
| simdjson (ondemand) | 6425.44 | 0.0838316 | 7929.36ms | 2090234 | 320 | 2.16446e+07 | 310236 | 0.100126 | 0.472937 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8338.08 | 0.0513037 | 6108.24ms | 2090234 | 1280 | 1.92559e+07 | 239072 | 0.149769 | 0.364365 | 1(Win) | true |
| simdjson (ondemand) | 6420.38 | 0.140897 | 7961.28ms | 2090234 | 160 | 3.06193e+07 | 310481 | 0.231963 | 0.473234 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11027.4 | 0.0775526 | 5746.2ms | 5212421 | 320 | 3.91089e+07 | 450782 | 0.371852 | 0.275564 | 1(Win) | true |
| simdjson (ondemand) | 8372.04 | 0.204267 | 7485.53ms | 5212421 | 30 | 4.41301e+07 | 593757 | 0.0741594 | 0.362972 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11039.3 | 0.240967 | 5745.47ms | 5212421 | 30 | 3.5321e+07 | 450297 | 0.413564 | 0.275224 | 1(Win) | true |
| simdjson (ondemand) | 8499.21 | 0.0864152 | 7434.91ms | 5212421 | 320 | 8.17433e+07 | 584872 | 0.0785345 | 0.357488 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6162.79 | 0.0950273 | 8250.56ms | 2090234 | 640 | 6.04661e+07 | 323458 | 0.186933 | 0.493092 | 1(Win) | true |
| simdjson (ondemand) | 5054.56 | 0.0739407 | 5012.34ms | 2090234 | 640 | 5.44214e+07 | 394377 | 0.120271 | 0.601227 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6180.79 | 0.0588927 | 8219.62ms | 2090234 | 1280 | 4.6178e+07 | 322516 | 0.199374 | 0.491568 | 1(Win) | true |
| simdjson (ondemand) | 5050.2 | 0.15132 | 5023.22ms | 2090234 | 160 | 5.70803e+07 | 394718 | 0.0189973 | 0.601704 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8644.29 | 0.111057 | 7369.51ms | 5212421 | 80 | 3.26291e+07 | 575056 | 0.0953345 | 0.351534 | 1(Win) | true |
| simdjson (ondemand) | 6909.99 | 0.0922012 | 9151.93ms | 5212421 | 640 | 2.81564e+08 | 719386 | 0.339895 | 0.439782 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8587.62 | 0.108604 | 7350.4ms | 5212421 | 160 | 6.32333e+07 | 578851 | 0.172297 | 0.353799 | 1(Win) | true |
| simdjson (ondemand) | 6927.62 | 0.129622 | 9117.99ms | 5212421 | 320 | 2.76833e+08 | 717555 | 0.064196 | 0.438593 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.624 | 0.149281 | 8873.11ms | 500299 | 320 | 3.45339e+08 | 695895 | 0.0519295 | 4.43259 | 1(Win) | true |
| simdjson (ondemand) | 638.492 | 0.126251 | 9482.92ms | 500299 | 640 | 5.69636e+08 | 747264 | 0.143234 | 4.75983 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.505 | 0.147209 | 8595.73ms | 500299 | 160 | 1.4126e+08 | 638286 | 0.0182161 | 4.06583 | 1(Win) | true |
| simdjson (ondemand) | 703.828 | 0.183293 | 9114.3ms | 500299 | 80 | 1.23512e+08 | 677896 | 0.0669799 | 4.31815 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1480.28 | 0.114185 | 9413.8ms | 1151920 | 640 | 4.5958e+08 | 742129 | 0.109215 | 2.05298 | 1(Win) | true |
| simdjson (ondemand) | 1401.68 | 0.108344 | 9964.48ms | 1151920 | 640 | 4.61469e+08 | 783745 | 0.105094 | 2.16813 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1600.39 | 0.0689973 | 9248.19ms | 1151920 | 640 | 1.43562e+08 | 686432 | 0.0109021 | 1.89893 | 1(Win) | true |
| simdjson (ondemand) | 1495.48 | 0.0937583 | 9826.47ms | 1151920 | 640 | 3.03586e+08 | 734584 | 0.166463 | 2.03218 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 452.756 | 0.0889888 | 6670.62ms | 500299 | 160 | 1.40709e+08 | 1.05382e+06 | 0.136282 | 6.71271 | 1(Win) | true |
| simdjson (ondemand) | 316.645 | 0.11922 | 9480.45ms | 500299 | 320 | 1.03268e+09 | 1.50681e+06 | 0.229966 | 9.5983 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 472.394 | 0.0964675 | 6518.33ms | 500299 | 160 | 1.51891e+08 | 1.01001e+06 | 0.146624 | 6.43374 | 1(Win) | true |
| simdjson (ondemand) | 329.852 | 0.0881047 | 9349.05ms | 500299 | 320 | 5.19721e+08 | 1.44647e+06 | 0.0781678 | 9.21417 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1004.08 | 0.208982 | 6880.77ms | 1151920 | 160 | 8.36462e+08 | 1.0941e+06 | 0.0653936 | 3.02673 | 1(Win) | true |
| simdjson (ondemand) | 705.468 | 0.134495 | 9832.54ms | 1151920 | 160 | 7.01812e+08 | 1.5572e+06 | 0.452723 | 4.30796 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1057.63 | 0.143428 | 6775.39ms | 1151920 | 40 | 8.87777e+07 | 1.0387e+06 | 0.320091 | 2.87353 | 1(Win) | true |
| simdjson (ondemand) | 730.637 | 0.21833 | 9766.44ms | 1151920 | 40 | 4.3105e+08 | 1.50356e+06 | 0.0734353 | 4.15972 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4736.06 | 0.173362 | 5153.58ms | 500299 | 80 | 2.4402e+06 | 100742 | 0.121449 | 0.641633 | 1(Win) | true |
| simdjson (ondemand) | 4216.18 | 0.133421 | 5744.78ms | 500299 | 1280 | 2.91795e+07 | 113165 | 0.522701 | 0.720723 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4926.56 | 0.0398973 | 9723.75ms | 500299 | 1280 | 1.91103e+06 | 96846.9 | 0.0543411 | 0.616766 | 1(Win) | true |
| simdjson (ondemand) | 4325.6 | 0.121704 | 5642.31ms | 500299 | 1280 | 2.30669e+07 | 110302 | 0.24581 | 0.702471 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7805.8 | 0.0423212 | 7193.43ms | 1151920 | 1280 | 4.54083e+06 | 140736 | 0.0301338 | 0.389301 | 1(Win) | true |
| simdjson (ondemand) | 7021.07 | 0.142103 | 8001.75ms | 1151920 | 640 | 3.16392e+07 | 156466 | 0.355142 | 0.432787 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7970.31 | 0.0643873 | 7046.77ms | 1151920 | 2560 | 2.01621e+07 | 137831 | 0.00702902 | 0.381234 | 1(Win) | true |
| simdjson (ondemand) | 7167.35 | 0.0675923 | 7856.77ms | 1151920 | 2560 | 2.74765e+07 | 153272 | 0.128944 | 0.423964 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2653.86 | 0.069164 | 9225.62ms | 500299 | 1280 | 1.97912e+07 | 179784 | 0.0912589 | 1.14509 | 1(Win) | true |
| simdjson (ondemand) | 2477.59 | 0.18404 | 9835.24ms | 500299 | 320 | 4.01953e+07 | 192575 | 0.00146045 | 1.22664 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2703.75 | 0.0405005 | 9043.86ms | 500299 | 2560 | 1.30764e+07 | 176467 | 0.00801382 | 1.12393 | 1(Win) | true |
| simdjson (ondemand) | 2484.82 | 0.081171 | 9817.14ms | 500299 | 2560 | 6.21885e+07 | 192014 | 0.355276 | 1.22299 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5222.02 | 0.158988 | 5387.76ms | 1151920 | 30 | 3.35597e+06 | 210370 | 0.0459297 | 0.581955 | 1(Win) | true |
| simdjson (ondemand) | 4632.67 | 0.319955 | 6043.72ms | 1151920 | 320 | 1.84209e+08 | 237132 | 0.0205539 | 0.655957 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5294.62 | 0.100942 | 5292.64ms | 1151920 | 160 | 7.01847e+06 | 207486 | 0.130261 | 0.573921 | 1(Win) | true |
| simdjson (ondemand) | 4677.07 | 0.106171 | 5991.77ms | 1151920 | 1280 | 7.96007e+07 | 234881 | 0.0104763 | 0.649737 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 862.365 | 0.136995 | 6276.45ms | 56369 | 160 | 1.16689e+06 | 62337.5 | 0.114167 | 3.52312 | 1(Win) | true |
| simdjson (ondemand) | 779.445 | 0.0628705 | 6902.69ms | 56369 | 4890 | 9.19415e+06 | 68969.1 | 0.320176 | 3.89788 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1159.18 | 0.0912872 | 5119.26ms | 56369 | 160 | 286761 | 46375.6 | 0.0283095 | 2.62043 | 1(Win) | true |
| simdjson (ondemand) | 1009.66 | 0.0975292 | 5783.27ms | 56369 | 2560 | 6.90301e+06 | 53243.3 | 0.0363763 | 3.00889 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1203.49 | 0.0503126 | 6657.5ms | 83958 | 4890 | 5.47898e+06 | 66530.1 | 0.0797467 | 2.52444 | 1(Win) | true |
| simdjson (ondemand) | 1140.89 | 0.0408587 | 7029.93ms | 83958 | 4890 | 4.02083e+06 | 70180.8 | 0.0749709 | 2.66307 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1590.5 | 0.0736675 | 5497.99ms | 83958 | 1280 | 1.76043e+06 | 50341.8 | 0.009157 | 1.91004 | 1(Win) | true |
| simdjson (ondemand) | 1458.32 | 0.0454676 | 5948.67ms | 83958 | 2560 | 1.59538e+06 | 54904.7 | 0.0804014 | 2.0833 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 501.617 | 0.0628447 | 5492.08ms | 56369 | 2560 | 1.16122e+07 | 107169 | 0.152345 | 6.05774 | 1(Win) | true |
| simdjson (ondemand) | 170.227 | 0.150817 | 8054.35ms | 56369 | 320 | 7.25896e+07 | 315800 | 0.130891 | 17.8535 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 590.523 | 0.0979422 | 9619.4ms | 56369 | 320 | 2.54388e+06 | 91034.1 | 0.0133896 | 5.14522 | 1(Win) | true |
| simdjson (ondemand) | 178.584 | 0.128096 | 7794.9ms | 56369 | 320 | 4.75792e+07 | 301021 | 0.101216 | 17.018 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 643.249 | 0.0683084 | 6361.47ms | 83958 | 1280 | 9.2539e+06 | 124475 | 0.125119 | 4.72407 | 1(Win) | true |
| simdjson (ondemand) | 252.2 | 0.0898073 | 8107.12ms | 83958 | 1280 | 1.04056e+08 | 317480 | 0.000344511 | 12.0505 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 737.645 | 0.145029 | 5763.18ms | 83958 | 160 | 3.96514e+06 | 108546 | 0.405846 | 4.11936 | 1(Win) | true |
| simdjson (ondemand) | 266.062 | 0.124965 | 7825.5ms | 83958 | 320 | 4.52571e+07 | 300939 | 0.0856996 | 11.422 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1530.79 | 0.0515585 | 3512.48ms | 56369 | 2560 | 839248 | 35117.6 | 0.00589571 | 1.98398 | 1(Win) | true |
| simdjson (ondemand) | 1373.01 | 0.0679766 | 3908.19ms | 56369 | 2560 | 1.81341e+06 | 39153.3 | 0.197732 | 2.21221 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2112.18 | 0.0939647 | 2944.81ms | 56369 | 640 | 366039 | 25451.2 | 0.286907 | 1.43759 | 1(Win) | true |
| simdjson (ondemand) | 1797.54 | 0.0443802 | 3402.33ms | 56369 | 4890 | 861409 | 29906.2 | 0.0413114 | 1.68952 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2150.11 | 0.0556365 | 3732.51ms | 83958 | 1280 | 549454 | 37239.2 | 0.00923171 | 1.41261 | 1(Win) | true |
| simdjson (ondemand) | 1959.48 | 0.0993843 | 4092.58ms | 83958 | 640 | 1.0555e+06 | 40862.2 | 0.0803649 | 1.55016 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2886.37 | 0.037729 | 3178.75ms | 83958 | 4890 | 535647 | 27740.2 | 0.183079 | 1.05201 | 1(Win) | true |
| simdjson (ondemand) | 2536.33 | 0.0693383 | 3558.9ms | 83958 | 4890 | 2.34299e+06 | 31568.7 | 0.304396 | 1.1974 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1286.43 | 0.0611364 | 4181.56ms | 56369 | 1280 | 835443 | 41788.2 | 0.0203822 | 2.36114 | 1(Win) | true |
| simdjson (ondemand) | 940.04 | 0.0689112 | 5737.07ms | 56369 | 2560 | 3.97565e+06 | 57186.6 | 0.237246 | 3.23166 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.71 | 0.0828227 | 3669.5ms | 56369 | 4890 | 3.53178e+06 | 32448.4 | 0.0483565 | 1.83298 | 1(Win) | true |
| simdjson (ondemand) | 1120.89 | 0.117753 | 5212.8ms | 56369 | 2560 | 8.16473e+06 | 47959.8 | 0.207831 | 2.70989 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.87 | 0.151368 | 4486.4ms | 83958 | 320 | 1.46888e+06 | 44759.4 | 0.136656 | 1.69817 | 1(Win) | true |
| simdjson (ondemand) | 1382.78 | 0.0387983 | 5789.55ms | 83958 | 4890 | 2.46805e+06 | 57904.3 | 0.137296 | 2.19702 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2248.58 | 0.0404158 | 3993.81ms | 83958 | 2560 | 530213 | 35608.5 | 0.0184262 | 1.35072 | 1(Win) | true |
| simdjson (ondemand) | 1652.41 | 0.0444294 | 5245.47ms | 83958 | 4890 | 2.26641e+06 | 48455.6 | 0.0676406 | 1.83833 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 847.922 | 0.224377 | 5982.02ms | 53331 | 2560 | 4.63709e+07 | 59982.4 | 0.300533 | 3.5828 | 1(Win) | true |
| simdjson (ondemand) | 713.699 | 0.212481 | 7148.48ms | 53331 | 160 | 3.66851e+06 | 71263.1 | 0.0886587 | 4.25703 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1170.55 | 0.121168 | 4970.25ms | 53331 | 4890 | 1.3554e+07 | 43450.1 | 0.0849481 | 2.59498 | 1(Win) | true |
| simdjson (ondemand) | 934.769 | 0.0437097 | 6075.94ms | 53331 | 4890 | 2.76577e+06 | 54409.6 | 0.122956 | 3.24998 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.504 | 0.247901 | 6272.99ms | 65103 | 2560 | 6.1939e+07 | 62745.7 | 0.0617331 | 3.07034 | 1(Win) | true |
| simdjson (ondemand) | 863.744 | 0.126198 | 7201.28ms | 65103 | 4890 | 4.02387e+07 | 71881.3 | 0.310964 | 3.5175 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1355.75 | 0.0848019 | 5208.7ms | 65103 | 640 | 965236 | 45795.3 | 0.0245598 | 2.24073 | 1(Win) | true |
| simdjson (ondemand) | 1120.16 | 0.0518654 | 6136.17ms | 65103 | 2560 | 2.11561e+06 | 55426.9 | 0.145391 | 2.71203 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 677.671 | 0.135484 | 7501.52ms | 53331 | 4890 | 5.05603e+07 | 75051.8 | 0.00754513 | 4.48335 | 1(Win) | true |
| simdjson (ondemand) | 356.782 | 0.222446 | 7286.54ms | 53331 | 1280 | 1.2871e+08 | 142553 | 0.0927598 | 8.51706 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 888.113 | 0.0865796 | 6369.15ms | 53331 | 640 | 1.57339e+06 | 57268 | 0.22286 | 3.42077 | 1(Win) | true |
| simdjson (ondemand) | 411.644 | 0.0578355 | 6671.07ms | 53331 | 2560 | 1.30721e+07 | 123554 | 0.0411489 | 7.38199 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.661 | 0.322555 | 8035.87ms | 65103 | 40 | 2.57269e+06 | 78625 | 0.0997284 | 3.84818 | 1(Win) | true |
| simdjson (ondemand) | 436.31 | 0.156687 | 7247.29ms | 65103 | 2560 | 1.27267e+08 | 142300 | 0.156742 | 6.96463 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 988.785 | 0.0446831 | 6954.96ms | 65103 | 4890 | 3.84941e+06 | 62791.3 | 0.627348 | 3.07257 | 1(Win) | true |
| simdjson (ondemand) | 504.182 | 0.0743458 | 6624.21ms | 65103 | 2560 | 2.14576e+07 | 123144 | 0.00672439 | 6.02712 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5359.63 | 0.136978 | 952.821ms | 53331 | 4890 | 826227 | 9489.53 | 0.0378682 | 0.565667 | 1(Win) | true |
| simdjson (ondemand) | 4586.57 | 0.100818 | 1115.16ms | 53331 | 1280 | 159980 | 11089 | 0.234059 | 0.661181 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6635.75 | 0.169665 | 822.005ms | 53331 | 2560 | 432917 | 7664.61 | 0.319038 | 0.456598 | 1(Win) | true |
| simdjson (ondemand) | 5391.32 | 0.236134 | 977.808ms | 53331 | 320 | 158795 | 9433.75 | 0.474746 | 0.562034 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5706.53 | 0.207076 | 1092.54ms | 65103 | 80 | 40607.6 | 10880 | 0.115022 | 0.531404 | 1(Win) | true |
| simdjson (ondemand) | 5212.75 | 0.0674231 | 1194.57ms | 65103 | 2560 | 165092 | 11910.6 | 0.124782 | 0.581868 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6771.55 | 0.0563771 | 959.124ms | 65103 | 4890 | 130659 | 9168.81 | 0.333689 | 0.447615 | 1(Win) | true |
| simdjson (ondemand) | 6167.6 | 0.139201 | 1059.54ms | 65103 | 1280 | 251341 | 10066.6 | 0.103112 | 0.491592 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4151.02 | 0.172003 | 1235.31ms | 53331 | 160 | 71062.9 | 12252.5 | 0.071465 | 0.730822 | 1(Win) | true |
| simdjson (ondemand) | 3055.48 | 0.170607 | 1688.42ms | 53331 | 160 | 129037 | 16645.6 | 0.0338041 | 0.99303 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4910.49 | 0.186484 | 1086.33ms | 53331 | 160 | 59691.8 | 10357.5 | 0.120831 | 0.61706 | 1(Win) | true |
| simdjson (ondemand) | 3461.14 | 0.17398 | 1537.65ms | 53331 | 320 | 209157 | 14694.7 | 0.0787469 | 0.876542 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4417.36 | 0.0618338 | 1409.61ms | 65103 | 2560 | 193361 | 14055.2 | 0.0516667 | 0.686998 | 1(Win) | true |
| simdjson (ondemand) | 3534.31 | 0.0864588 | 1760.67ms | 65103 | 1280 | 295271 | 17567 | 0.0449376 | 0.858775 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5169.61 | 0.180561 | 1255.36ms | 65103 | 80 | 37620.3 | 12010 | 0.062409 | 0.586752 | 1(Win) | true |
| simdjson (ondemand) | 3944.47 | 0.0524149 | 1620.27ms | 65103 | 4890 | 332846 | 15740.3 | 0.0384996 | 0.769314 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 653.205 | 0.139921 | 1723.17ms | 11812 | 4890 | 2.84723e+06 | 17245.4 | 0.150795 | 4.64686 | 1(Win) | true |
| simdjson (ondemand) | 575.526 | 0.0877611 | 1968.75ms | 11812 | 1280 | 377686 | 19573 | 0.161393 | 5.2747 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 737.785 | 0.141392 | 1633.67ms | 11812 | 2560 | 1.1931e+06 | 15268.4 | 0.0248102 | 4.11321 | 1(Win) | true |
| simdjson (ondemand) | 638.807 | 0.0485254 | 1857.49ms | 11812 | 4890 | 358059 | 17634.1 | 0.146688 | 4.75148 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1298.05 | 0.14848 | 1877.84ms | 25388 | 320 | 245448 | 18652.5 | 0.446994 | 2.33807 | 1(Win) | true |
| simdjson (ondemand) | 1176.77 | 0.0818117 | 2049.47ms | 25388 | 2560 | 725350 | 20574.9 | 0.0406125 | 2.58013 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.81 | 0.0454673 | 1794.03ms | 25388 | 4890 | 287456 | 16862.9 | 0.0727477 | 2.11379 | 1(Win) | true |
| simdjson (ondemand) | 1300.02 | 0.082932 | 1963.59ms | 25388 | 4890 | 1.16656e+06 | 18624.2 | 0.345551 | 2.33505 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 486.573 | 0.0621209 | 2315.39ms | 11812 | 2560 | 529502 | 23151.3 | 0.0401731 | 6.24012 | 1(Win) | true |
| simdjson (ondemand) | 436.324 | 0.146476 | 2596.44ms | 11812 | 320 | 457624 | 25817.5 | 0.0654054 | 6.96 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 530.381 | 0.237034 | 2236.3ms | 11812 | 320 | 811040 | 21239.1 | 0.0809895 | 5.72467 | 1(Win) | true |
| simdjson (ondemand) | 466.979 | 0.0800297 | 2512.76ms | 11812 | 1280 | 477051 | 24122.7 | 0.0223417 | 6.50194 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 953.921 | 0.118271 | 2531.73ms | 25388 | 2560 | 2.30691e+06 | 25381.4 | 0.471629 | 3.18323 | 1(Win) | true |
| simdjson (ondemand) | 913.006 | 0.137404 | 2653.96ms | 25388 | 4890 | 6.49261e+06 | 26518.9 | 0.0597229 | 3.32593 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1030.24 | 0.0594879 | 2459.27ms | 25388 | 4890 | 955756 | 23501.2 | 0.386378 | 2.94707 | 1(Win) | true |
| simdjson (ondemand) | 982.089 | 0.0436255 | 2562.17ms | 25388 | 4890 | 565647 | 24653.5 | 0.0650805 | 3.09192 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1307.07 | 0.117824 | 862.833ms | 11812 | 4890 | 504227 | 8618.34 | 0.357342 | 2.31953 | 1(Win) | true |
| simdjson (ondemand) | 1221.11 | 0.0946274 | 927.465ms | 11812 | 4890 | 372634 | 9225.07 | 0.00162277 | 2.48319 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1405.59 | 0.0895826 | 825.404ms | 11812 | 4890 | 252051 | 8014.31 | 0.373017 | 2.15617 | 1(Win) | true |
| simdjson (ondemand) | 1292.09 | 0.237182 | 898.363ms | 11812 | 1280 | 547312 | 8718.28 | 0.479792 | 2.34608 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2625.37 | 0.112288 | 926.164ms | 25388 | 2560 | 274526 | 9222.27 | 0.076184 | 1.155 | 1(Win) | true |
| simdjson (ondemand) | 2392.63 | 0.0899184 | 1009.64ms | 25388 | 4890 | 404867 | 10119.4 | 0.243457 | 1.26749 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2801.88 | 0.0977931 | 887.1ms | 25388 | 2560 | 182816 | 8641.29 | 0.0311814 | 1.08161 | 1(Win) | true |
| simdjson (ondemand) | 2499.22 | 0.136556 | 988.503ms | 25388 | 4890 | 855813 | 9687.77 | 0.761761 | 1.21306 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1152.41 | 0.086958 | 980.004ms | 11812 | 2560 | 184965 | 9774.96 | 0.0123897 | 2.63149 | 1(Win) | true |
| simdjson (ondemand) | 1032.84 | 0.154062 | 1091.92ms | 11812 | 4890 | 1.38065e+06 | 10906.7 | 0.108879 | 2.9371 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1230.49 | 0.11279 | 939.073ms | 11812 | 2560 | 272944 | 9154.73 | 0.230517 | 2.46329 | 1(Win) | true |
| simdjson (ondemand) | 1088.31 | 0.0852412 | 1053.01ms | 11812 | 2560 | 199288 | 10350.7 | 0.0094356 | 2.78673 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2175.07 | 0.0842642 | 1119.76ms | 25388 | 4890 | 430235 | 11131.6 | 0.145843 | 1.39456 | 1(Win) | true |
| simdjson (ondemand) | 2041.3 | 0.148988 | 1198.93ms | 25388 | 1280 | 399722 | 11861 | 0.116449 | 1.48557 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2275.13 | 0.0664836 | 1086.07ms | 25388 | 4890 | 244784 | 10642 | 0.550589 | 1.33289 | 1(Win) | true |
| simdjson (ondemand) | 2119.21 | 0.0908853 | 1157.2ms | 25388 | 4890 | 527237 | 11425 | 0.187446 | 1.43117 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1009.6 | 0.184492 | 5228.67ms | 108313 | 2560 | 9.12139e+07 | 102314 | 0.00576539 | 3.0096 | 1(Win) | true |
| simdjson (ondemand) | 881.641 | 0.174693 | 5976.29ms | 108313 | 1280 | 5.36213e+07 | 117163 | 0.0296818 | 3.44642 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1187.45 | 0.0724425 | 8998.89ms | 108313 | 1280 | 5.08308e+06 | 86989.1 | 0.0934049 | 2.55886 | 1(Win) | true |
| simdjson (ondemand) | 999.608 | 0.0581956 | 5405.86ms | 108313 | 2560 | 9.25812e+06 | 103336 | 0.127402 | 3.03985 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1587.64 | 0.266004 | 5665.36ms | 183677 | 320 | 2.75632e+07 | 110332 | 0.224102 | 1.91395 | 1(Win) | true |
| simdjson (ondemand) | 1447.16 | 0.0884709 | 6199.16ms | 183677 | 2560 | 2.93576e+07 | 121043 | 0.144365 | 2.09974 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1835.87 | 0.151636 | 5041.32ms | 183677 | 160 | 3.34929e+06 | 95414.4 | 0.0896597 | 1.65503 | 1(Win) | true |
| simdjson (ondemand) | 1634.76 | 0.148282 | 5655.53ms | 183677 | 320 | 8.07843e+06 | 107152 | 0.124958 | 1.85876 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 480.3 | 0.0683415 | 5484.06ms | 108313 | 640 | 1.38256e+07 | 215064 | 0.00247026 | 6.32738 | 1(Win) | true |
| simdjson (ondemand) | 186.994 | 0.143134 | 7004.32ms | 108313 | 640 | 4.00101e+08 | 552400 | 0.376309 | 16.2533 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 514.156 | 0.174331 | 5163.39ms | 108313 | 80 | 9.81316e+06 | 200902 | 0.108144 | 5.91072 | 1(Win) | true |
| simdjson (ondemand) | 193.01 | 0.194931 | 6809.73ms | 108313 | 320 | 3.48268e+08 | 535182 | 0.048313 | 15.7464 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 748.123 | 0.25121 | 5969.68ms | 183677 | 30 | 1.03791e+07 | 234143 | 0.0512769 | 4.0625 | 1(Win) | true |
| simdjson (ondemand) | 317.759 | 0.474385 | 6980.59ms | 183677 | 80 | 5.47097e+08 | 551260 | 0.12487 | 9.56474 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 803.311 | 0.117819 | 5641.81ms | 183677 | 320 | 2.11214e+07 | 218058 | 0.042402 | 3.78315 | 1(Win) | true |
| simdjson (ondemand) | 329.721 | 0.129685 | 6781.3ms | 183677 | 640 | 3.03792e+08 | 531261 | 0.255165 | 9.21755 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3752.7 | 0.0566875 | 2770.09ms | 108313 | 4890 | 1.19058e+06 | 27525.6 | 0.218781 | 0.809211 | 1(Win) | true |
| simdjson (ondemand) | 3254.84 | 0.210342 | 3193.87ms | 108313 | 320 | 1.42595e+06 | 31735.9 | 0.00295415 | 0.932932 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4354.5 | 0.0618264 | 2413.94ms | 108313 | 2560 | 550646 | 23721.5 | 0.0373664 | 0.697222 | 1(Win) | true |
| simdjson (ondemand) | 3630.99 | 0.0574209 | 2876.99ms | 108313 | 4890 | 1.30485e+06 | 28448.3 | 0.275641 | 0.836317 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5131.48 | 0.0435799 | 3432.23ms | 183677 | 4890 | 1.0822e+06 | 34136 | 0.0823385 | 0.591823 | 1(Win) | true |
| simdjson (ondemand) | 4763.64 | 0.289459 | 3676.42ms | 183677 | 640 | 7.25079e+06 | 36771.9 | 0.00424935 | 0.637543 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5745.83 | 0.0506628 | 3072.03ms | 183677 | 4890 | 1.16652e+06 | 30486.1 | 0.275865 | 0.528488 | 1(Win) | true |
| simdjson (ondemand) | 5253.4 | 0.167435 | 3373.38ms | 183677 | 160 | 498703 | 33343.8 | 0.0187477 | 0.578134 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2771.47 | 0.129636 | 3757.86ms | 108313 | 2560 | 5.97627e+06 | 37270.9 | 0.216054 | 1.09592 | 1(Win) | true |
| simdjson (ondemand) | 2131.91 | 0.0829822 | 4858.45ms | 108313 | 2560 | 4.13839e+06 | 48451.9 | 0.34123 | 1.42485 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3097.92 | 0.0869687 | 3391.62ms | 108313 | 2560 | 2.15272e+06 | 33343.5 | 0.0995609 | 0.980331 | 1(Win) | true |
| simdjson (ondemand) | 2306.46 | 0.111774 | 4527.06ms | 108313 | 2560 | 6.41485e+06 | 44785.2 | 0.128487 | 1.31696 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4051.86 | 0.0530653 | 4380.97ms | 183677 | 4890 | 2.57354e+06 | 43231.5 | 0.201473 | 0.749646 | 1(Win) | true |
| simdjson (ondemand) | 3260.42 | 0.0796528 | 5388.52ms | 183677 | 1280 | 2.3441e+06 | 53725.6 | 0.16144 | 0.931757 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4394.94 | 0.0800163 | 4029.73ms | 183677 | 4890 | 4.97359e+06 | 39856.8 | 0.130054 | 0.691082 | 1(Win) | true |
| simdjson (ondemand) | 3524.73 | 0.145638 | 4994.07ms | 183677 | 1280 | 6.70524e+06 | 49696.8 | 0.237152 | 0.86176 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 320.894 | 1.25963 | 8189.97ms | 1834197 | 40 | 1.88588e+11 | 5.4511e+06 | 0.0843967 | 9.47037 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 318.804 | 1.5252 | 8126.92ms | 1834197 | 30 | 2.10096e+11 | 5.48684e+06 | 0.18466 | 9.53352 | 1(Tie) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 353.364 | 1.46493 | 8124.98ms | 1834197 | 30 | 1.57761e+11 | 4.95021e+06 | 1.74665 | 8.59994 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 340.952 | 1.20667 | 8230.96ms | 1834197 | 40 | 1.53299e+11 | 5.13041e+06 | 1.51453 | 8.91392 | 1(Tie) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1247.31 | 0.982347 | 8356.15ms | 7351818 | 30 | 9.1473e+10 | 5.6211e+06 | 0.415159 | 2.43651 | 1(Win) | true |
| Jsonifier (generic) | 1188.69 | 0.655549 | 8894.98ms | 7351818 | 80 | 1.19607e+11 | 5.8983e+06 | 0.809351 | 2.55662 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1350.48 | 0.704207 | 8376.39ms | 7351818 | 80 | 1.06932e+11 | 5.19168e+06 | 2.13268 | 2.25048 | 1(Win) | true |
| Jsonifier (generic) | 1283.41 | 0.89173 | 8816.33ms | 7351818 | 40 | 9.49256e+10 | 5.46296e+06 | 0.08797 | 2.36801 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 253.681 | 0.474537 | 10223.5ms | 1834197 | 80 | 8.56537e+10 | 6.89538e+06 | 0.763337 | 11.9797 | 1(Win) | true |
| simdjson (ondemand) | 194.16 | 0.496218 | 6285.3ms | 1834197 | 40 | 7.99429e+10 | 9.00922e+06 | 0.103677 | 15.6533 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 267.188 | 0.37637 | 10308.6ms | 1834197 | 80 | 4.85711e+10 | 6.5468e+06 | 0.0816526 | 11.3749 | 1(Win) | true |
| simdjson (ondemand) | 202.526 | 0.541802 | 6286.28ms | 1834197 | 30 | 6.56953e+10 | 8.63707e+06 | 0.129429 | 15.007 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.686 | 0.884545 | 5514.18ms | 7351818 | 40 | 1.96124e+11 | 7.91617e+06 | 1.78886 | 3.43143 | 1(Win) | true |
| simdjson (ondemand) | 668.548 | 0.63575 | 7342.65ms | 7351818 | 40 | 1.7781e+11 | 1.04873e+07 | 0.107404 | 4.54606 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 943.714 | 0.683548 | 5473.48ms | 7351818 | 40 | 1.03159e+11 | 7.42941e+06 | 3.57198 | 3.22057 | -(Win) | false |
| simdjson (ondemand) | 695.022 | 0.562114 | 7357.34ms | 7351818 | 40 | 1.28618e+11 | 1.00878e+07 | 0.208464 | 4.37306 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4604.29 | 0.113683 | 9704.74ms | 1834197 | 640 | 1.19382e+08 | 379912 | 0.0636666 | 0.659976 | 1(Win) | true |
| simdjson (ondemand) | 4012.55 | 0.102198 | 5558.78ms | 1834197 | 640 | 1.27034e+08 | 435939 | 0.164567 | 0.75733 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4630.2 | 0.0801106 | 9679.19ms | 1834197 | 320 | 2.93104e+07 | 377786 | 0.577497 | 0.656293 | 1(Win) | true |
| simdjson (ondemand) | 3976.49 | 0.177128 | 5573.14ms | 1834197 | 640 | 3.88549e+08 | 439892 | 0.559679 | 0.764161 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9418.67 | 0.192192 | 9471.06ms | 7351818 | 320 | 6.54988e+08 | 744398 | 0.207813 | 0.322616 | 1(Win) | true |
| simdjson (ondemand) | 8185.51 | 0.190722 | 5408.23ms | 7351818 | 160 | 4.26993e+08 | 856543 | 0.0584813 | 0.37123 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9483.27 | 0.235488 | 9485.5ms | 7351818 | 80 | 2.42493e+08 | 739328 | 0.245565 | 0.320413 | 1(Win) | true |
| simdjson (ondemand) | 8244.09 | 0.13489 | 5365.11ms | 7351818 | 320 | 4.21128e+08 | 850456 | 0.397686 | 0.368597 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3141.27 | 0.420878 | 7034.4ms | 1834197 | 640 | 3.51539e+09 | 556853 | 1.07623 | 0.967371 | 1(Win) | true |
| simdjson (ondemand) | 2311.82 | 0.462496 | 9691.9ms | 1834197 | 30 | 3.67383e+08 | 756643 | 0.146916 | 1.31452 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3120.6 | 0.558896 | 7025ms | 1834197 | 160 | 1.57036e+09 | 560542 | 0.0490356 | 0.973739 | 1(Win) | true |
| simdjson (ondemand) | 2308.84 | 0.119116 | 9653.17ms | 1834197 | 640 | 5.21225e+08 | 757620 | 0.338091 | 1.3162 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7341.54 | 0.363635 | 5999.2ms | 7351818 | 30 | 3.618e+08 | 955010 | 0.0716037 | 0.413893 | 1(Win) | true |
| simdjson (ondemand) | 5497.78 | 0.295354 | 8064.79ms | 7351818 | 40 | 5.67492e+08 | 1.27528e+06 | 0.0526957 | 0.552727 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7386.92 | 0.171742 | 5963.54ms | 7351818 | 320 | 8.50291e+08 | 949143 | 0.0760144 | 0.411363 | 1(Win) | true |
| simdjson (ondemand) | 5522.35 | 0.089238 | 8006.83ms | 7351818 | 320 | 4.10763e+08 | 1.26961e+06 | 0.0750158 | 0.550267 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.931 | 0.176777 | 6971.43ms | 409725 | 320 | 2.99553e+08 | 547313 | 0.30539 | 4.25661 | 1(Win) | true |
| simdjson (ondemand) | 596.212 | 0.257177 | 8292.99ms | 409725 | 640 | 1.81814e+09 | 655378 | 0.040204 | 5.09715 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 931.269 | 0.218316 | 6093.84ms | 409725 | 40 | 3.35635e+07 | 419582 | 0.0284093 | 3.26336 | 1(Win) | true |
| simdjson (ondemand) | 753.212 | 0.16128 | 7396.26ms | 409725 | 320 | 2.24007e+08 | 518770 | 0.0767453 | 4.03477 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1103.94 | 0.150427 | 7438.78ms | 676745 | 640 | 4.94989e+08 | 584630 | 0.105038 | 2.75272 | 1(Win) | true |
| simdjson (ondemand) | 953.914 | 0.230613 | 8604.33ms | 676745 | 80 | 1.94756e+08 | 676575 | 0.122457 | 3.1856 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1436.06 | 0.182011 | 6502.93ms | 676745 | 160 | 1.07058e+08 | 449420 | 0.0656833 | 2.11601 | 1(Win) | true |
| simdjson (ondemand) | 1187.19 | 0.0849468 | 7702.96ms | 676745 | 640 | 1.36485e+08 | 543632 | 0.264115 | 2.55979 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 541.448 | 0.13769 | 9215.89ms | 409725 | 80 | 7.89894e+07 | 721665 | 0.0650848 | 5.61306 | 1(Win) | true |
| simdjson (ondemand) | 334.424 | 0.155407 | 7374.89ms | 409725 | 320 | 1.05508e+09 | 1.16841e+06 | 0.153837 | 9.08771 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 644.584 | 0.101089 | 8488.13ms | 409725 | 160 | 6.00831e+07 | 606196 | 0.0217498 | 4.71484 | 1(Win) | true |
| simdjson (ondemand) | 374.314 | 0.198725 | 6990.36ms | 409725 | 320 | 1.37711e+09 | 1.04389e+06 | 0.322445 | 8.11958 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.91 | 0.131489 | 5011.42ms | 676745 | 80 | 8.65435e+07 | 791011 | 0.170534 | 3.72476 | 1(Win) | true |
| simdjson (ondemand) | 546.359 | 0.23482 | 7432.13ms | 676745 | 160 | 1.23108e+09 | 1.18126e+06 | 0.137481 | 5.56246 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 949.85 | 0.153653 | 9404.36ms | 676745 | 640 | 6.9759e+08 | 679470 | 0.153858 | 3.19959 | 1(Win) | true |
| simdjson (ondemand) | 610.365 | 0.309636 | 7079.46ms | 676745 | 40 | 4.28778e+08 | 1.05739e+06 | 0.215141 | 4.97931 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1490.61 | 0.0763917 | 6688.28ms | 409725 | 320 | 1.28321e+07 | 262137 | 0.029812 | 2.03882 | 1(Win) | true |
| simdjson (ondemand) | 1243.01 | 0.137497 | 8058.83ms | 409725 | 320 | 5.97824e+07 | 314353 | 0.139874 | 2.44498 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1732.18 | 0.0713334 | 6367.1ms | 409725 | 640 | 1.65717e+07 | 225580 | 0.0449045 | 1.75439 | 1(Win) | true |
| simdjson (ondemand) | 1404.94 | 0.064771 | 7696.63ms | 409725 | 1280 | 4.15376e+07 | 278122 | 0.196246 | 2.16312 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2248.49 | 0.178461 | 7315.12ms | 676745 | 160 | 4.19833e+07 | 287034 | 0.0189473 | 1.35159 | 1(Win) | true |
| simdjson (ondemand) | 1959.79 | 0.210935 | 8444.48ms | 676745 | 160 | 7.72059e+07 | 329319 | 0.112606 | 1.55067 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2583.99 | 0.115091 | 6993.98ms | 676745 | 80 | 6.61062e+06 | 249766 | 0.0655183 | 1.17608 | 1(Win) | true |
| simdjson (ondemand) | 2198.49 | 0.171522 | 8099.37ms | 676745 | 160 | 4.05658e+07 | 293562 | 0.353813 | 1.38238 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1238.09 | 0.173717 | 8118.35ms | 409725 | 30 | 9.01757e+06 | 315603 | 0.10129 | 2.45475 | 1(Win) | true |
| simdjson (ondemand) | 1023.63 | 0.0775606 | 9742.17ms | 409725 | 1280 | 1.122e+08 | 381724 | 0.292812 | 2.96896 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.45 | 0.123762 | 7742.47ms | 409725 | 320 | 3.84308e+07 | 280013 | 0.0746061 | 2.17787 | 1(Win) | true |
| simdjson (ondemand) | 1126.93 | 0.183443 | 9435.37ms | 409725 | 640 | 2.58925e+08 | 346734 | 0.174631 | 2.69684 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1908.91 | 0.155963 | 8600.6ms | 676745 | 1280 | 3.55904e+08 | 338097 | 0.300231 | 1.59205 | 1(Win) | true |
| simdjson (ondemand) | 1613.87 | 0.189378 | 5093.24ms | 676745 | 320 | 1.83537e+08 | 399906 | 0.157134 | 1.88315 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2156.47 | 0.172635 | 8226.85ms | 676745 | 1280 | 3.41689e+08 | 299282 | 0.0173361 | 1.40932 | 1(Win) | true |
| simdjson (ondemand) | 1790.04 | 0.0724307 | 9827.26ms | 676745 | 1280 | 8.72934e+07 | 360548 | 0.0784864 | 1.69781 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1087.9 | 0.24558 | 5882.96ms | 264040 | 1280 | 4.13575e+08 | 231462 | 0.815588 | 2.79323 | 1(Win) | true |
| simdjson (ondemand) | 964.14 | 0.311922 | 6763.32ms | 264040 | 160 | 1.06187e+08 | 261174 | 0.0100498 | 3.15186 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1467.38 | 0.113181 | 9793.28ms | 264040 | 1280 | 4.82855e+07 | 171604 | 0.00346011 | 2.07097 | 1(Win) | true |
| simdjson (ondemand) | 1227.29 | 0.199384 | 5738.15ms | 264040 | 320 | 5.35519e+07 | 205174 | 0.00670117 | 2.47619 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.42 | 0.454309 | 6308.61ms | 360584 | 160 | 2.00552e+08 | 246434 | 0.00634003 | 2.17774 | 1(Win) | true |
| simdjson (ondemand) | 1236.75 | 0.155913 | 7077.79ms | 360584 | 1280 | 2.40561e+08 | 278051 | 0.0509945 | 2.45708 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1832.79 | 0.14055 | 5314.62ms | 360584 | 1280 | 8.90145e+07 | 187626 | 0.0913553 | 1.65805 | 1(Win) | true |
| simdjson (ondemand) | 1616.94 | 0.117984 | 5953.86ms | 360584 | 640 | 4.02952e+07 | 212673 | 0.147456 | 1.87941 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 539.597 | 0.256507 | 5997.45ms | 264040 | 30 | 4.29852e+07 | 466660 | 0.556183 | 5.63214 | 1(Win) | true |
| simdjson (ondemand) | 207.169 | 0.325881 | 7669.83ms | 264040 | 80 | 1.25516e+09 | 1.21547e+06 | 0.0560795 | 14.6702 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 612.349 | 0.145636 | 5500.23ms | 264040 | 320 | 1.1477e+08 | 411217 | 0.27132 | 4.96311 | 1(Win) | true |
| simdjson (ondemand) | 220.782 | 0.235373 | 7364.89ms | 264040 | 80 | 5.76519e+08 | 1.14053e+06 | 0.0734866 | 13.7661 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 688.492 | 0.156484 | 6391.15ms | 360584 | 640 | 3.90961e+08 | 499468 | 0.0481369 | 4.41416 | 1(Win) | true |
| simdjson (ondemand) | 298.958 | 0.254482 | 7254.68ms | 360584 | 160 | 1.37097e+09 | 1.15026e+06 | 0.0196733 | 10.166 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 795.275 | 0.110579 | 5797.54ms | 360584 | 160 | 3.65802e+07 | 432404 | 0.0179263 | 3.82148 | 1(Win) | true |
| simdjson (ondemand) | 315.161 | 0.136594 | 7012.93ms | 360584 | 320 | 7.10827e+08 | 1.09113e+06 | 0.387392 | 9.64363 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5604.04 | 0.0712749 | 4503.11ms | 264040 | 2560 | 2.62573e+06 | 44933.4 | 0.0173838 | 0.542047 | 1(Win) | true |
| simdjson (ondemand) | 3753.43 | 0.0681671 | 6729.75ms | 264040 | 1280 | 2.67697e+06 | 67087.5 | 0.0118767 | 0.809477 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6093.04 | 0.0964399 | 4239.21ms | 264040 | 320 | 508318 | 41327.2 | 0.258517 | 0.498488 | 1(Win) | true |
| simdjson (ondemand) | 3982.71 | 0.0809774 | 6452.2ms | 264040 | 1280 | 3.35522e+06 | 63225.4 | 0.0179203 | 0.762802 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6272.77 | 0.0567763 | 5496.31ms | 360584 | 2560 | 2.4801e+06 | 54821 | 0.0494752 | 0.484313 | 1(Win) | true |
| simdjson (ondemand) | 4609.38 | 0.106633 | 7457.87ms | 360584 | 640 | 4.05034e+06 | 74604.4 | 0.0456784 | 0.659162 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6736.63 | 0.0619567 | 5245.69ms | 360584 | 4890 | 4.89118e+06 | 51046.2 | 0.0412748 | 0.450907 | 1(Win) | true |
| simdjson (ondemand) | 4872.66 | 0.132674 | 7224.49ms | 360584 | 640 | 5.61091e+06 | 70573.3 | 0.0683662 | 0.623501 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4034.51 | 0.0550897 | 6253.26ms | 264040 | 4890 | 5.78107e+06 | 62413.6 | 0.0583078 | 0.753041 | 1(Win) | true |
| simdjson (ondemand) | 2703.95 | 0.0540795 | 9316ms | 264040 | 2560 | 6.49302e+06 | 93125.9 | 0.0450296 | 1.12374 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4291.02 | 0.0919196 | 6001.02ms | 264040 | 640 | 1.86216e+06 | 58682.7 | 0.220685 | 0.707996 | 1(Win) | true |
| simdjson (ondemand) | 2831.58 | 0.0799512 | 9056.48ms | 264040 | 1280 | 6.47056e+06 | 88928.4 | 0.0291582 | 1.07305 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4685.01 | 0.287713 | 7538ms | 360584 | 30 | 1.33793e+06 | 73400 | 0.108873 | 0.648532 | 1(Win) | true |
| simdjson (ondemand) | 3415.83 | 0.0468535 | 5143.89ms | 360584 | 2560 | 5.69567e+06 | 100672 | 0.0704141 | 0.889577 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4847.33 | 0.0533034 | 7372.86ms | 360584 | 2560 | 3.66064e+06 | 70942.1 | 0.0278143 | 0.626763 | 1(Win) | true |
| simdjson (ondemand) | 3529.68 | 0.0599172 | 5044.26ms | 360584 | 2560 | 8.7234e+06 | 97425.2 | 0.0721024 | 0.860859 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 847.938 | 0.104852 | 299.851ms | 2632 | 4890 | 47109 | 2960.2 | 0.00892599 | 3.55829 | 1(Win) | true |
| simdjson (ondemand) | 786.625 | 0.135854 | 321.18ms | 2632 | 2560 | 48108.5 | 3190.94 | 0.210115 | 3.83955 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1536.55 | 0.117943 | 191.201ms | 2632 | 4890 | 18152.3 | 1633.58 | 0.118783 | 1.95554 | 1(Win) | true |
| simdjson (ondemand) | 1240.44 | 0.0865206 | 229.099ms | 2632 | 4890 | 14988.9 | 2023.54 | 0.0664226 | 2.42669 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1023.8 | 0.0927689 | 317.212ms | 3370 | 4890 | 41471.2 | 3139.18 | 0.0534048 | 2.94777 | 1(Win) | true |
| simdjson (ondemand) | 996.208 | 0.0917446 | 324.041ms | 3370 | 4890 | 42838 | 3226.11 | 0.210805 | 3.03094 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1757.12 | 0.182503 | 209.9ms | 3370 | 2560 | 28525.9 | 1829.06 | 0.0640287 | 1.71126 | 1(Win) | true |
| simdjson (ondemand) | 1615.02 | 0.262152 | 231.922ms | 3370 | 80 | 2177.22 | 1990 | 0.125471 | 1.86542 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 690.617 | 0.188261 | 359.535ms | 2632 | 640 | 29963.8 | 3634.53 | 0.0645272 | 4.37404 | 1(Win) | true |
| simdjson (ondemand) | 468.324 | 0.191645 | 543.979ms | 2632 | 320 | 33761.7 | 5359.69 | 0.677554 | 6.4645 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1096.7 | 0.205548 | 258.968ms | 2632 | 80 | 1770.57 | 2288.75 | 0.0546448 | 2.74854 | 1(Win) | true |
| simdjson (ondemand) | 607.053 | 0.20059 | 443.45ms | 2632 | 640 | 44026.6 | 4134.84 | 0.0188979 | 4.98277 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 832.444 | 0.247768 | 387.57ms | 3370 | 4890 | 447453 | 3860.78 | 0.157696 | 3.63042 | 1(Win) | true |
| simdjson (ondemand) | 595.202 | 0.125703 | 540.838ms | 3370 | 2560 | 117940 | 5399.65 | 0.0759022 | 5.08459 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1262.49 | 0.239939 | 283.024ms | 3370 | 4890 | 182437 | 2545.66 | 0.439267 | 2.38993 | 1(Win) | true |
| simdjson (ondemand) | 769.771 | 0.125054 | 445.644ms | 3370 | 4890 | 133304 | 4175.11 | 0.0541815 | 3.93094 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1733.32 | 0.287001 | 148.903ms | 2632 | 160 | 2763.76 | 1448.12 | 0.215332 | 1.72487 | 1(Win) | true |
| simdjson (ondemand) | 1502.45 | 0.215436 | 170.139ms | 2632 | 4890 | 63346.1 | 1670.65 | 0.478686 | 2.00117 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2781.24 | 0.194631 | 99.987ms | 2632 | 80 | 246.835 | 902.5 | 0 | 1.07257 | 1(Win) | true |
| simdjson (ondemand) | 2278 | 0.127407 | 122.452ms | 2632 | 2560 | 5045.33 | 1101.88 | 0.247542 | 1.31265 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2096.88 | 0.235007 | 158.421ms | 3370 | 2560 | 33213.5 | 1532.7 | 0.195859 | 1.43361 | 1(Win) | true |
| simdjson (ondemand) | 1918.11 | 0.161613 | 171.673ms | 3370 | 1280 | 9385.94 | 1675.55 | 0.09782 | 1.56963 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3214.34 | 0.266974 | 110.747ms | 3370 | 4890 | 34843.5 | 999.857 | 0.271428 | 0.926792 | 1(Win) | true |
| simdjson (ondemand) | 2865.94 | 0.146032 | 123.806ms | 3370 | 640 | 1716.33 | 1121.41 | 0.0974388 | 1.04363 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.23 | 0.152994 | 171.393ms | 2632 | 320 | 2096.79 | 1673.12 | 0.224635 | 2.00262 | 1(Win) | true |
| simdjson (ondemand) | 1329.62 | 0.158784 | 192.97ms | 2632 | 1280 | 11501.1 | 1887.81 | 0.0745465 | 2.26212 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2197.9 | 0.207109 | 126.193ms | 2632 | 1280 | 7160.84 | 1142.03 | 0.027356 | 1.359 | 1(Win) | true |
| simdjson (ondemand) | 1837.62 | 0.281291 | 150.317ms | 2632 | 640 | 9448.26 | 1365.94 | 0.114521 | 1.62988 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.64 | 0.292191 | 183.273ms | 3370 | 80 | 2151.9 | 1775 | 0.141044 | 1.66639 | 1(Win) | true |
| simdjson (ondemand) | 1711.65 | 0.167195 | 190.695ms | 3370 | 640 | 6307.49 | 1877.66 | 0.373072 | 1.75652 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2538.11 | 0.29615 | 140.973ms | 3370 | 160 | 2250 | 1266.25 | 0.197824 | 1.18206 | 1(Win) | true |
| simdjson (ondemand) | 2411 | 0.145855 | 145.605ms | 3370 | 4890 | 18484.9 | 1333.01 | 0.34391 | 1.24276 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 355.668 | 0.149164 | 1304.45ms | 4630 | 640 | 219471 | 12414.7 | 1.7072 | 8.53417 | 1(Win) | true |
| simdjson (ondemand) | 339.05 | 1.22212 | 1290.58ms | 4630 | 4890 | 1.23871e+08 | 13023.2 | 0.886068 | 8.94816 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 393.134 | 0.235655 | 1258.27ms | 4630 | 320 | 224173 | 11231.6 | 0.00834632 | 7.71853 | 1(Win) | true |
| Jsonifier (generic) | 389.58 | 0.0567105 | 1266.35ms | 4630 | 4890 | 202024 | 11334 | 0.409434 | 7.78528 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 866.997 | 0.136462 | 1292.84ms | 11579 | 2560 | 773341 | 12736.6 | 0.13113 | 3.49995 | 1(Win) | true |
| Jsonifier (generic) | 845.947 | 0.0483798 | 1320.78ms | 11579 | 4890 | 195026 | 13053.5 | 0.0617362 | 3.58674 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 975.602 | 0.393572 | 1299.13ms | 11579 | 80 | 158758 | 11318.8 | 0.25465 | 3.10945 | 1(Win) | true |
| Jsonifier (generic) | 952.872 | 0.159598 | 1312.65ms | 11579 | 320 | 109466 | 11588.8 | 0.40613 | 3.18302 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 352.389 | 0.114329 | 1256.93ms | 4630 | 1280 | 262690 | 12530.2 | 0.263181 | 8.61151 | 1(Win) | true |
| simdjson (ondemand) | 350.664 | 0.0657656 | 1267.41ms | 4630 | 2560 | 175557 | 12591.9 | 0.122998 | 8.65416 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 389.515 | 0.127666 | 1249.98ms | 4630 | 4890 | 1.02418e+06 | 11335.9 | 0.04656 | 7.78831 | 1(Win) | true |
| simdjson (ondemand) | 384.658 | 0.177561 | 1262.84ms | 4630 | 2560 | 1.06352e+06 | 11479.1 | 0.00136119 | 7.88756 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 860.239 | 0.126572 | 1310.52ms | 11579 | 30 | 7919.54 | 12836.7 | 0.0519076 | 3.52938 | 1(Win) | true |
| simdjson (ondemand) | 840.995 | 0.0527844 | 1317.32ms | 11579 | 4890 | 234896 | 13130.4 | 0.323535 | 3.60861 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 899.457 | 0.157911 | 1371.57ms | 11579 | 2560 | 962157 | 12277 | 0.135995 | 3.37322 | 1(Win) | true |
| simdjson (ondemand) | 889.693 | 0.15175 | 1378.32ms | 11579 | 4890 | 1.73471e+06 | 12411.7 | 0.211769 | 3.41039 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6861.96 | 0.146952 | 66.8237ms | 4630 | 4890 | 4372.45 | 643.476 | 0.463487 | 0.431081 | 1(Win) | true |
| simdjson (ondemand) | 5160.57 | 0.348929 | 87.9475ms | 4630 | 320 | 2852.27 | 855.625 | 0.218659 | 0.575894 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7380.33 | 0.164007 | 62.8233ms | 4630 | 1280 | 1232.38 | 598.281 | 0.235602 | 0.398747 | 1(Win) | true |
| simdjson (ondemand) | 5357.72 | 0.199381 | 84.8667ms | 4630 | 2560 | 6912.12 | 824.141 | 0.323348 | 0.555432 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11166.1 | 0.171053 | 101.851ms | 11579 | 4890 | 13992.9 | 988.937 | 0.463401 | 0.267081 | 1(Win) | true |
| simdjson (ondemand) | 9014.36 | 0.589878 | 128.42ms | 11579 | 80 | 4177.22 | 1225 | 0.406504 | 0.332945 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11710.2 | 0.177455 | 97.2283ms | 11579 | 4890 | 13692.9 | 942.986 | 0.00179593 | 0.25464 | 1(Win) | true |
| simdjson (ondemand) | 9053.63 | 0.170661 | 125.121ms | 11579 | 640 | 2772.99 | 1219.69 | 0.153965 | 0.330902 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5253.63 | 0.2384 | 87.4361ms | 4630 | 640 | 2569.42 | 840.469 | 0.129967 | 0.564504 | 1(Win) | true |
| simdjson (ondemand) | 4274.77 | 0.115248 | 106.933ms | 4630 | 4890 | 6929.68 | 1032.92 | 0.0685424 | 0.698989 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5551.03 | 0.187656 | 82.6137ms | 4630 | 4890 | 10895.5 | 795.44 | 0.0919653 | 0.535614 | 1(Win) | true |
| simdjson (ondemand) | 4575.66 | 0.556096 | 102.292ms | 4630 | 80 | 2303.8 | 965 | 0 | 0.652638 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9121.4 | 0.151607 | 122.516ms | 11579 | 320 | 1077.98 | 1210.62 | 0.8329 | 0.328599 | 1(Win) | true |
| simdjson (ondemand) | 7573.15 | 0.19893 | 148.752ms | 11579 | 320 | 2692.4 | 1458.12 | 0.299145 | 0.396199 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9750.64 | 0.129433 | 117.351ms | 11579 | 2560 | 5500.59 | 1132.5 | 0.08285 | 0.307093 | 1(Win) | true |
| simdjson (ondemand) | 7817.77 | 0.452574 | 143.11ms | 11579 | 40 | 1634.62 | 1412.5 | 0.414692 | 0.382693 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 564.418 | 0.129901 | 879.977ms | 5092 | 160 | 19985.8 | 8603.75 | 0.534682 | 5.37408 | 1(Win) | true |
| simdjson (ondemand) | 545.745 | 0.231657 | 901.404ms | 5092 | 160 | 67983.9 | 8898.12 | 0.387816 | 5.55855 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 654.988 | 0.0657394 | 835.37ms | 5092 | 4890 | 116164 | 7414.05 | 0.123842 | 4.62577 | 1(Win) | true |
| Jsonifier (generic) | 599.427 | 0.0656801 | 908.576ms | 5092 | 4890 | 138446 | 8101.25 | 0.0982993 | 5.05653 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1026.56 | 0.351725 | 917.957ms | 9739 | 40 | 40506.4 | 9047.5 | 0.0460745 | 2.95355 | 1(Win) | true |
| simdjson (ondemand) | 1006.95 | 0.420885 | 936.735ms | 9739 | 80 | 120568 | 9223.75 | 0.0406394 | 3.01206 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1234.23 | 0.07951 | 857.269ms | 9739 | 2560 | 91647.1 | 7525.2 | 0.391362 | 2.456 | 1(Win) | true |
| Jsonifier (generic) | 1214.49 | 0.185487 | 859.012ms | 9739 | 160 | 32195 | 7647.5 | 0.277099 | 2.49402 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 408.223 | 0.129631 | 1190.99ms | 5092 | 4890 | 1.1628e+06 | 11895.7 | 0.146862 | 7.43112 | 1(Win) | true |
| simdjson (ondemand) | 309.478 | 0.0707223 | 1573.93ms | 5092 | 4890 | 602196 | 15691.3 | 0.166686 | 9.80642 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 477.083 | 0.0714067 | 1120.81ms | 5092 | 80 | 4226.27 | 10178.8 | 0.209205 | 6.35424 | 1(Win) | true |
| simdjson (ondemand) | 331.815 | 0.296274 | 1530.47ms | 5092 | 80 | 150405 | 14635 | 0 | 9.14386 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.244 | 0.191742 | 1239.13ms | 9739 | 80 | 43213.6 | 12121.2 | 0.0103135 | 3.96028 | 1(Win) | true |
| simdjson (ondemand) | 574.359 | 0.0870107 | 1616.78ms | 9739 | 2560 | 506813 | 16170.8 | 0.214968 | 5.28356 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 857.126 | 0.110869 | 1166.23ms | 9739 | 2560 | 369488 | 10836 | 0.00072097 | 3.53684 | 1(Win) | true |
| simdjson (ondemand) | 629.139 | 0.0716234 | 1567.2ms | 9739 | 4890 | 546707 | 14762.8 | 0.03553 | 4.82342 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4089.36 | 0.617016 | 120.391ms | 5092 | 40 | 2147.44 | 1187.5 | 0.0702247 | 0.730749 | 1(Win) | true |
| simdjson (ondemand) | 3556.78 | 0.157311 | 138.066ms | 5092 | 2560 | 11809.2 | 1365.31 | 0.160477 | 0.842661 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4709.67 | 0.13378 | 105.029ms | 5092 | 2560 | 4871.02 | 1031.09 | 0.0910056 | 0.634162 | 1(Win) | true |
| simdjson (ondemand) | 3887.43 | 0.27528 | 126.825ms | 5092 | 4890 | 57824 | 1249.18 | 0.0909524 | 0.770284 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6275.56 | 0.214338 | 152.093ms | 9739 | 160 | 1610.06 | 1480 | 0.420521 | 0.478658 | 1(Win) | true |
| simdjson (ondemand) | 5620.08 | 0.333488 | 166.945ms | 9739 | 2560 | 77757.9 | 1652.62 | 0.215558 | 0.534798 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6966.35 | 0.122594 | 136.341ms | 9739 | 2560 | 6839.03 | 1333.24 | 0.0497833 | 0.430428 | 1(Win) | true |
| simdjson (ondemand) | 6125.53 | 0.136224 | 154.715ms | 9739 | 320 | 1365.2 | 1516.25 | 0.0823723 | 0.49027 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2683.86 | 0.142395 | 181.571ms | 5092 | 1280 | 8496.87 | 1809.38 | 0.0691324 | 1.12074 | 1(Win) | true |
| simdjson (ondemand) | 2458.42 | 0.188491 | 199.453ms | 5092 | 4890 | 67788.1 | 1975.3 | 0.227708 | 1.22465 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2968.89 | 0.178292 | 164.607ms | 5092 | 2560 | 21771.7 | 1635.66 | 0.0406154 | 1.01215 | 1(Win) | true |
| simdjson (ondemand) | 2607.31 | 0.497151 | 187.289ms | 5092 | 40 | 3429.49 | 1862.5 | 0.494604 | 1.16085 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4589.42 | 0.236582 | 206.146ms | 9739 | 80 | 1833.86 | 2023.75 | 0.307882 | 0.654375 | 1(Win) | true |
| simdjson (ondemand) | 4159.05 | 0.0931939 | 226.038ms | 9739 | 2560 | 11088.1 | 2233.16 | 0.0122429 | 0.724518 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5137.83 | 0.127033 | 185.532ms | 9739 | 1280 | 6750.14 | 1807.73 | 0.229576 | 0.585427 | 1(Win) | true |
| simdjson (ondemand) | 4417.53 | 0.163361 | 213.645ms | 9739 | 4890 | 57686.6 | 2102.49 | 0.133833 | 0.681945 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 759.636 | 0.122009 | 612.314ms | 4857 | 1280 | 70846.7 | 6097.66 | 0.29127 | 3.98466 | 1(Win) | true |
| simdjson (ondemand) | 751.062 | 0.238764 | 622.106ms | 4857 | 1280 | 277544 | 6167.27 | 0.992073 | 4.03243 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1170.09 | 0.102459 | 444.207ms | 4857 | 4890 | 80445.7 | 3958.65 | 0.286868 | 2.58479 | 1(Win) | true |
| simdjson (ondemand) | 1064.01 | 0.263716 | 484.659ms | 4857 | 30 | 3954.02 | 4353.33 | 0.0765111 | 2.84381 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1019.6 | 0.0997856 | 632.73ms | 6701 | 4890 | 191279 | 6267.75 | 0.124435 | 2.9705 | 1(Win) | true |
| Jsonifier (generic) | 1004.26 | 0.220457 | 643.983ms | 6701 | 640 | 125954 | 6363.44 | 0.00491063 | 3.01561 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1509.1 | 0.107711 | 473.251ms | 6701 | 1280 | 26630.1 | 4234.69 | 0.0847926 | 2.00477 | 1(Win) | true |
| simdjson (ondemand) | 1423.49 | 0.0851708 | 493.874ms | 6701 | 160 | 2339.23 | 4489.38 | 0.152905 | 2.12495 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 473.68 | 0.210343 | 988.927ms | 4857 | 80 | 33846.5 | 9778.75 | 0.0895599 | 6.40249 | 1(Win) | true |
| simdjson (ondemand) | 179.395 | 0.119616 | 2587.52ms | 4857 | 1280 | 1.22097e+06 | 25820.2 | 0.016947 | 16.9291 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 634.52 | 0.138731 | 797.97ms | 4857 | 40 | 4102.56 | 7300 | 0.045683 | 4.77576 | 1(Win) | true |
| simdjson (ondemand) | 192.222 | 0.103312 | 2457.86ms | 4857 | 2560 | 1.58662e+06 | 24097.1 | 0.0291873 | 15.798 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.72 | 0.109087 | 1080.66ms | 6701 | 2560 | 355334 | 10800 | 0.0796351 | 5.12466 | 1(Win) | true |
| simdjson (ondemand) | 247.415 | 0.152269 | 2607.66ms | 6701 | 160 | 247496 | 25829.4 | 0.229347 | 12.2739 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.109 | 0.121155 | 890.182ms | 6701 | 40 | 4096.15 | 8352.5 | 0.20908 | 3.95686 | 1(Win) | true |
| simdjson (ondemand) | 262.82 | 0.118884 | 2481.45ms | 6701 | 4890 | 4.0862e+06 | 24315.4 | 0.426356 | 11.5541 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2278.83 | 0.344762 | 204.378ms | 4857 | 2560 | 125716 | 2032.62 | 0.403272 | 1.32058 | 1(Win) | true |
| simdjson (ondemand) | 2119.45 | 0.329839 | 219.861ms | 4857 | 1280 | 66512.7 | 2185.47 | 0.142786 | 1.41953 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3143 | 0.258685 | 171.076ms | 4857 | 160 | 2325.47 | 1473.75 | 0.253807 | 0.956165 | 1(Win) | true |
| simdjson (ondemand) | 2820.55 | 0.288399 | 183.636ms | 4857 | 4890 | 109689 | 1642.23 | 0.0810898 | 1.06562 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2901.08 | 0.329272 | 223.837ms | 6701 | 4890 | 257263 | 2202.82 | 0.817458 | 1.03822 | 1(Win) | true |
| simdjson (ondemand) | 2824.56 | 0.466457 | 233.404ms | 6701 | 40 | 4455.13 | 2262.5 | 0.0368189 | 1.06499 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3877.66 | 0.165065 | 187.9ms | 6701 | 1280 | 9472.34 | 1648.05 | 0.0142194 | 0.77468 | 1(Win) | true |
| simdjson (ondemand) | 3672.08 | 0.119429 | 196.446ms | 6701 | 2560 | 11058.9 | 1740.31 | 0.406849 | 0.818947 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1850.33 | 0.557853 | 251.972ms | 4857 | 30 | 5850.57 | 2503.33 | 0.267023 | 1.63101 | 1(Win) | true |
| simdjson (ondemand) | 1480.02 | 0.19541 | 316.364ms | 4857 | 640 | 23937.3 | 3129.69 | 0.129974 | 2.03973 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2446.48 | 0.244651 | 216.24ms | 4857 | 30 | 643.678 | 1893.33 | 0.175747 | 1.23337 | 1(Win) | true |
| simdjson (ondemand) | 1811.24 | 0.090054 | 276.703ms | 4857 | 4890 | 25935.8 | 2557.36 | 0.481109 | 1.66599 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2407.1 | 0.159437 | 269.089ms | 6701 | 4890 | 87614.7 | 2654.89 | 0.225802 | 1.25368 | 1(Win) | true |
| simdjson (ondemand) | 1971.18 | 0.156774 | 328.184ms | 6701 | 4890 | 126323 | 3242 | 0.210046 | 1.53347 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3048.15 | 0.0884608 | 233.832ms | 6701 | 4890 | 16819.7 | 2096.54 | 0.246217 | 0.988551 | 1(Win) | true |
| simdjson (ondemand) | 2408.25 | 0.11717 | 286.667ms | 6701 | 4890 | 47273.7 | 2653.62 | 0.413378 | 1.25352 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 793.469 | 0.104673 | 207.53ms | 1691 | 2560 | 11586.2 | 2032.42 | 0.331675 | 3.7981 | 1(Win) | true |
| simdjson (ondemand) | 721.36 | 0.133884 | 225.579ms | 1691 | 2560 | 22934 | 2235.59 | 0.266625 | 4.18031 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 967.296 | 0.155351 | 191.274ms | 1691 | 1280 | 8586.3 | 1667.19 | 0.679512 | 3.10924 | 1(Win) | true |
| simdjson (ondemand) | 890.974 | 0.120231 | 210.912ms | 1691 | 2560 | 12123.5 | 1810 | 0.493923 | 3.37656 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 956.007 | 0.132255 | 219.835ms | 2158 | 1280 | 10375.6 | 2152.73 | 0.0833998 | 3.14931 | 1(Win) | true |
| simdjson (ondemand) | 913.608 | 0.128434 | 227.339ms | 2158 | 4890 | 40930.9 | 2252.64 | 0.214677 | 3.29896 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1178.91 | 0.164474 | 201.175ms | 2158 | 1280 | 10552.3 | 1745.7 | 1.27684 | 2.55048 | 1(Win) | true |
| simdjson (ondemand) | 1118.54 | 0.148064 | 211.342ms | 2158 | 1280 | 9499.6 | 1839.92 | 0.511152 | 2.68984 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 632.417 | 0.313977 | 256.06ms | 1691 | 40 | 2564.1 | 2550 | 0.262123 | 4.75266 | 1(Win) | true |
| simdjson (ondemand) | 492.203 | 0.0960223 | 331.847ms | 1691 | 4890 | 48400.8 | 3276.42 | 0.289605 | 6.14097 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.231 | 0.24711 | 237.62ms | 1691 | 80 | 2221.52 | 2132.5 | 0.235018 | 3.98138 | 1(Win) | true |
| simdjson (ondemand) | 560.701 | 0.167074 | 314.431ms | 1691 | 4890 | 112915 | 2876.16 | 0.139512 | 5.38586 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.51 | 0.31546 | 285.698ms | 2158 | 30 | 2402.3 | 2836.67 | 0 | 4.15585 | 1(Win) | true |
| simdjson (ondemand) | 621.761 | 0.335046 | 335.445ms | 2158 | 30 | 3689.66 | 3310 | 0 | 4.85188 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 866.838 | 0.132882 | 263.728ms | 2158 | 2560 | 25480 | 2374.18 | 0.384831 | 3.48029 | 1(Win) | true |
| simdjson (ondemand) | 701.258 | 0.208756 | 318.997ms | 2158 | 2560 | 96086.7 | 2934.77 | 0.289324 | 4.30425 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3384.23 | 0.197782 | 50.0773ms | 1691 | 2560 | 2273.96 | 476.523 | 0.0902527 | 0.864096 | 1(Win) | true |
| simdjson (ondemand) | 2961.07 | 0.367984 | 56.4906ms | 1691 | 4890 | 19640.7 | 544.622 | 0.943491 | 0.993621 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4082.69 | 0.620778 | 43.8897ms | 1691 | 80 | 481.013 | 395 | 0.628931 | 0.693902 | 1(Win) | true |
| simdjson (ondemand) | 3539.76 | 0.217631 | 49.5308ms | 1691 | 2560 | 2516.66 | 455.586 | 1.24471 | 0.824345 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3819.7 | 0.168012 | 55.516ms | 2158 | 4890 | 4007.13 | 538.793 | 0.974469 | 0.768939 | 1(Win) | true |
| simdjson (ondemand) | 3683.27 | 0.698715 | 58.7259ms | 2158 | 160 | 2438.68 | 558.75 | 1.10619 | 0.800348 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4668.22 | 0.317637 | 48.3786ms | 2158 | 2560 | 5019.97 | 440.859 | 0.598908 | 0.624855 | 1(Win) | true |
| simdjson (ondemand) | 4378.79 | 0.391408 | 52.4289ms | 2158 | 640 | 2165.88 | 470 | 0.791557 | 0.664122 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2479.77 | 0.148924 | 67.3414ms | 1691 | 4890 | 4586.72 | 650.327 | 0.0217615 | 1.19111 | 1(Win) | true |
| simdjson (ondemand) | 1942.35 | 0.126856 | 85.6022ms | 1691 | 4890 | 5424.56 | 830.266 | 0.0808305 | 1.53072 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2931.49 | 0.179952 | 59.7986ms | 1691 | 2560 | 2508.78 | 550.117 | 0.60723 | 1.00658 | 1(Win) | true |
| simdjson (ondemand) | 2236.57 | 0.130306 | 77.6831ms | 1691 | 4890 | 4316.77 | 721.043 | 0.532103 | 1.32486 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2772.46 | 0.145101 | 75.9336ms | 2158 | 4890 | 5673.12 | 742.311 | 0.230181 | 1.06958 | 1(Win) | true |
| simdjson (ondemand) | 2336.39 | 0.118318 | 89.3466ms | 2158 | 4890 | 5311.6 | 880.859 | 0.23895 | 1.27488 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3198.81 | 0.143332 | 68.7709ms | 2158 | 4890 | 4158.38 | 643.374 | 0.924083 | 0.92369 | 1(Win) | true |
| simdjson (ondemand) | 2699.29 | 0.35052 | 80.87ms | 2158 | 4890 | 34925.1 | 762.434 | 0.23777 | 1.0977 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 586.324 | 0.367233 | 718.286ms | 4390 | 640 | 440066 | 7140.47 | 0.0196902 | 5.16653 | 1(Win) | true |
| simdjson (ondemand) | 514.19 | 0.321927 | 821.522ms | 4390 | 640 | 439720 | 8142.19 | 0.180063 | 5.89812 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 675.827 | 0.151464 | 669.33ms | 4390 | 4890 | 430513 | 6194.83 | 1.09295 | 4.48282 | 1(Win) | true |
| simdjson (ondemand) | 566.138 | 0.311077 | 786.467ms | 4390 | 4890 | 2.58779e+06 | 7395.07 | 0.0458879 | 5.35427 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1199.82 | 0.199911 | 752.598ms | 9378 | 2560 | 568463 | 7454.1 | 0.124044 | 2.5256 | 1(Win) | true |
| simdjson (ondemand) | 1098.17 | 0.177388 | 826.535ms | 9378 | 2560 | 534275 | 8144.02 | 0.256908 | 2.76066 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1355.41 | 0.193447 | 715.089ms | 9378 | 2560 | 417102 | 6598.4 | 0.335717 | 2.23495 | 1(Win) | true |
| simdjson (ondemand) | 1196.76 | 0.603666 | 802.26ms | 9378 | 160 | 325625 | 7473.12 | 0.0250962 | 2.53359 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 440.288 | 0.107571 | 951.598ms | 4390 | 4890 | 511627 | 9508.85 | 0.153943 | 6.8884 | 1(Win) | true |
| simdjson (ondemand) | 427.042 | 0.0975158 | 987.256ms | 4390 | 2560 | 233979 | 9803.79 | 0.0521688 | 7.1025 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 495.97 | 0.359993 | 895.596ms | 4390 | 2560 | 2.36399e+06 | 8441.29 | 0.0374972 | 6.11315 | 1(Win) | true |
| simdjson (ondemand) | 472.36 | 0.267515 | 930.99ms | 4390 | 4890 | 2.74908e+06 | 8863.21 | 0.0516764 | 6.41891 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.391 | 0.167575 | 1030.12ms | 9378 | 1280 | 359413 | 9999.61 | 0.799064 | 3.39083 | 1(Win) | true |
| simdjson (ondemand) | 879.764 | 0.122173 | 1005.22ms | 9378 | 2560 | 394895 | 10165.9 | 0.386508 | 3.44693 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 995.717 | 0.141435 | 951.578ms | 9378 | 1280 | 206573 | 8982.03 | 0.0644061 | 3.04519 | 1(Win) | true |
| Jsonifier (generic) | 984.465 | 0.23439 | 983.149ms | 9378 | 640 | 290188 | 9084.69 | 0.52213 | 3.08034 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1331.91 | 0.330098 | 322.119ms | 4390 | 30 | 3229.89 | 3143.33 | 0 | 2.26709 | 1(Win) | true |
| simdjson (ondemand) | 1237.43 | 0.31951 | 340.169ms | 4390 | 30 | 3505.75 | 3383.33 | 0.392542 | 2.44289 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.55 | 0.259538 | 303.892ms | 4390 | 40 | 2301.28 | 2922.5 | 0.0285063 | 2.10651 | 1(Win) | true |
| simdjson (ondemand) | 1341.94 | 0.111064 | 325.106ms | 4390 | 1280 | 15368.2 | 3119.84 | 0.165546 | 2.25153 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2588.33 | 0.0883939 | 347.829ms | 9378 | 4890 | 45617.9 | 3455.34 | 0.22393 | 1.16816 | 1(Win) | true |
| simdjson (ondemand) | 2455.34 | 0.12061 | 370.514ms | 9378 | 160 | 3088.05 | 3642.5 | 0.309811 | 1.23136 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2842.79 | 0.16071 | 327.649ms | 9378 | 4890 | 125005 | 3146.05 | 0.0757306 | 1.06217 | 1(Win) | true |
| simdjson (ondemand) | 2617.95 | 0.527379 | 355.449ms | 9378 | 160 | 51935.5 | 3416.25 | 0.10989 | 1.15468 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1152.3 | 0.187706 | 367.867ms | 4390 | 640 | 29767 | 3633.28 | 0.141716 | 2.6237 | 1(Win) | true |
| simdjson (ondemand) | 1048.62 | 0.165062 | 400.623ms | 4390 | 40 | 1737.18 | 3992.5 | 0.146321 | 2.87486 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1252.54 | 0.236823 | 348.044ms | 4390 | 40 | 2506.41 | 3342.5 | 0.0249252 | 2.40958 | 1(Win) | true |
| simdjson (ondemand) | 1139.87 | 0.127053 | 378.645ms | 4390 | 2560 | 55747.8 | 3672.89 | 0.12139 | 2.6521 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2195.64 | 0.261442 | 420.707ms | 9378 | 30 | 3402.3 | 4073.33 | 0 | 1.38038 | 1(Win) | true |
| simdjson (ondemand) | 2079.31 | 0.138852 | 445.595ms | 9378 | 2560 | 91311.5 | 4301.21 | 0.268631 | 1.4553 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2341.25 | 0.233392 | 398.716ms | 9378 | 40 | 3179.49 | 3820 | 0.262467 | 1.2944 | 1(Win) | true |
| simdjson (ondemand) | 2229.62 | 0.174486 | 413.494ms | 9378 | 1280 | 62703.7 | 4011.25 | 0.124494 | 1.35597 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 905.467 | 0.159355 | 496.749ms | 4669 | 1280 | 78604 | 4917.58 | 0.00476584 | 3.34123 | 1(Win) | true |
| simdjson (ondemand) | 811.647 | 0.134885 | 549.433ms | 4669 | 2560 | 140180 | 5486.02 | 0.0242151 | 3.73054 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1045.36 | 0.127445 | 448.547ms | 4669 | 2560 | 75439.4 | 4259.49 | 0.143773 | 2.89289 | 1(Win) | true |
| simdjson (ondemand) | 928.614 | 0.166137 | 500.467ms | 4669 | 40 | 2538.46 | 4795 | 0.104384 | 3.25759 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1450.3 | 0.169188 | 532.722ms | 7932 | 1280 | 99677.9 | 5215.86 | 0.350218 | 2.08796 | 1(Win) | true |
| simdjson (ondemand) | 1330.7 | 0.0729775 | 572.722ms | 7932 | 4890 | 84157 | 5684.62 | 0.539712 | 2.27588 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1636.7 | 0.0788219 | 485.046ms | 7932 | 4890 | 64898.2 | 4621.84 | 0.166875 | 1.84917 | 1(Win) | true |
| simdjson (ondemand) | 1511.35 | 0.0708263 | 530.061ms | 7932 | 4890 | 61452.1 | 5005.17 | 0.603944 | 2.00278 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 446.135 | 0.139682 | 1002.13ms | 4669 | 320 | 62194 | 9980.62 | 0.0813415 | 6.79814 | 1(Win) | true |
| simdjson (ondemand) | 199.366 | 0.146109 | 2333.17ms | 4669 | 1280 | 1.36304e+06 | 22334.3 | 0.156116 | 15.2309 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 481.207 | 0.130601 | 952.625ms | 4669 | 1280 | 186933 | 9253.2 | 0.0481021 | 6.30194 | 1(Win) | true |
| simdjson (ondemand) | 203.636 | 0.0960351 | 2216.88ms | 4669 | 2560 | 1.12886e+06 | 21866.1 | 0.311476 | 14.911 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 682.836 | 0.0957192 | 1110.29ms | 7932 | 2560 | 287853 | 11078.1 | 0.0155124 | 4.44286 | 1(Win) | true |
| simdjson (ondemand) | 333.546 | 0.070307 | 2291.04ms | 7932 | 4890 | 1.24325e+06 | 22679.2 | 0.0716802 | 9.10189 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.411 | 0.156298 | 1072.92ms | 7932 | 40 | 10538.5 | 10385 | 0.0481232 | 4.16631 | 1(Win) | true |
| simdjson (ondemand) | 342.219 | 0.122859 | 2322.87ms | 7932 | 2560 | 1.88802e+06 | 22104.4 | 0.514068 | 8.87204 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3684.68 | 0.180787 | 123.417ms | 4669 | 320 | 1527.33 | 1208.44 | 0.129467 | 0.812489 | 1(Win) | true |
| simdjson (ondemand) | 3445.48 | 0.212937 | 131.735ms | 4669 | 4890 | 37030.6 | 1292.33 | 0.227145 | 0.869456 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4607.12 | 0.521645 | 105.374ms | 4669 | 1280 | 32534.9 | 966.484 | 0.0404008 | 0.649722 | 1(Win) | true |
| simdjson (ondemand) | 4068.11 | 0.300717 | 114.11ms | 4669 | 4890 | 52976.9 | 1094.54 | 0.145323 | 0.73447 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5089.69 | 0.181386 | 150.438ms | 7932 | 1280 | 9302.58 | 1486.25 | 0.0947069 | 0.588969 | 1(Win) | true |
| Jsonifier (generic) | 5040.93 | 0.16178 | 156.198ms | 7932 | 160 | 943.003 | 1500.62 | 0.125104 | 0.596041 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6027.53 | 0.676915 | 135.026ms | 7932 | 160 | 11547.2 | 1255 | 0.297915 | 0.498894 | 1(Win) | true |
| simdjson (ondemand) | 5874.98 | 0.278734 | 133.738ms | 7932 | 4890 | 62985.6 | 1287.59 | 0.289728 | 0.509995 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2771.17 | 0.115906 | 163.583ms | 4669 | 2560 | 8879.15 | 1606.8 | 0.238815 | 1.08472 | 1(Win) | true |
| simdjson (ondemand) | 2209.14 | 0.121004 | 204.826ms | 4669 | 2560 | 15227.9 | 2015.59 | 0.0755258 | 1.36315 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3219.31 | 0.363154 | 141.819ms | 4669 | 640 | 16146.7 | 1383.12 | 0.539326 | 0.932597 | 1(Win) | true |
| simdjson (ondemand) | 2547.08 | 0.121985 | 181.107ms | 4669 | 2560 | 11641.8 | 1748.16 | 0.145453 | 1.18127 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4053.93 | 0.135479 | 186.266ms | 7932 | 2560 | 16360.5 | 1865.98 | 0.148853 | 0.742168 | 1(Win) | true |
| simdjson (ondemand) | 3288.93 | 0.361067 | 231.61ms | 7932 | 30 | 2068.97 | 2300 | 0.144718 | 0.915335 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4645.66 | 0.105986 | 166.158ms | 7932 | 4890 | 14563.9 | 1628.3 | 0.326276 | 0.646959 | 1(Win) | true |
| simdjson (ondemand) | 3703 | 0.280156 | 209.517ms | 7932 | 320 | 10481.1 | 2042.81 | 0.0765462 | 0.812219 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 294.245 | 0.0971876 | 1514.9ms | 4604 | 1280 | 269205 | 14922 | 0.122138 | 10.3122 | 1(Win) | true |
| Jsonifier (generic) | 288.652 | 0.133369 | 1577.02ms | 4604 | 640 | 263398 | 15211.1 | 0.0338865 | 10.5137 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 333.164 | 0.0962288 | 1486.59ms | 4604 | 1280 | 205861 | 13178.8 | 0.203747 | 9.10573 | 1(Win) | true |
| Jsonifier (generic) | 325.935 | 0.0515951 | 1472.47ms | 4604 | 4890 | 236229 | 13471.1 | 0.031367 | 9.30966 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1106.75 | 0.251334 | 1581.34ms | 18245 | 1280 | 1.9985e+06 | 15721.6 | 0.055687 | 2.74225 | 1(Win) | true |
| Jsonifier (generic) | 1079.95 | 0.169932 | 1619.32ms | 18245 | 4890 | 3.66557e+06 | 16111.7 | 0.100901 | 2.80999 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1217.78 | 0.119651 | 1635.4ms | 18245 | 320 | 93526.3 | 14288.1 | 0.117966 | 2.49121 | 1(Win) | true |
| simdjson (ondemand) | 1177.18 | 0.326065 | 1642.46ms | 18245 | 2560 | 5.94638e+06 | 14780.9 | 0.293146 | 2.57775 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 203.853 | 0.0912606 | 2165.39ms | 4604 | 1280 | 494555 | 21538.7 | 0.0250214 | 14.8953 | 1(Win) | true |
| simdjson (ondemand) | 160.597 | 0.279016 | 2705.49ms | 4604 | 2560 | 1.48968e+07 | 27340 | 0.252671 | 18.9105 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 217.362 | 0.162185 | 2147.51ms | 4604 | 640 | 686917 | 20200 | 0.242295 | 13.9671 | 1(Win) | true |
| simdjson (ondemand) | 171.949 | 0.280495 | 2691.2ms | 4604 | 80 | 410405 | 25535 | 0.117624 | 17.6533 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 760.654 | 0.0862366 | 2286.99ms | 18245 | 1280 | 498088 | 22874.8 | 0.0420263 | 3.99216 | 1(Win) | true |
| simdjson (ondemand) | 620.063 | 0.0790748 | 2807.86ms | 18245 | 4890 | 2.40769e+06 | 28061.3 | 0.224206 | 4.89808 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.549 | 0.137271 | 2267.74ms | 18245 | 320 | 271798 | 21230.9 | 0.00147189 | 3.70377 | 1(Win) | true |
| simdjson (ondemand) | 649.594 | 0.166758 | 2792.71ms | 18245 | 160 | 319226 | 26785.6 | 0.0443138 | 4.67457 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3690.31 | 0.0990461 | 120.905ms | 4604 | 4890 | 6790.92 | 1189.8 | 0.0663905 | 0.810527 | 1(Win) | true |
| simdjson (ondemand) | 3312.19 | 0.355485 | 135.917ms | 4604 | 160 | 3553.07 | 1325.62 | 0.0471254 | 0.904043 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3961.46 | 0.190005 | 114.037ms | 4604 | 1280 | 5676.74 | 1108.36 | 0.318201 | 0.755153 | 1(Win) | true |
| simdjson (ondemand) | 3451.59 | 0.602832 | 130.836ms | 4604 | 4890 | 287564 | 1272.09 | 0.389651 | 0.86759 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8950.75 | 0.101047 | 197.023ms | 18245 | 4890 | 18868 | 1943.95 | 0.53137 | 0.336257 | 1(Win) | true |
| simdjson (ondemand) | 7527.24 | 0.09148 | 234.046ms | 18245 | 4890 | 21866.4 | 2311.57 | 0.360069 | 0.400645 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9358.84 | 0.124093 | 189.808ms | 18245 | 4890 | 26028.4 | 1859.18 | 0.235999 | 0.321285 | 1(Win) | true |
| simdjson (ondemand) | 7692.13 | 0.393906 | 228.618ms | 18245 | 4890 | 388230 | 2262.02 | 0.391506 | 0.392083 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2427.49 | 0.161109 | 186.456ms | 4604 | 1280 | 10869.4 | 1808.75 | 0.395801 | 1.23933 | 1(Win) | true |
| simdjson (ondemand) | 1836.64 | 0.624811 | 245.087ms | 4604 | 160 | 35697.7 | 2390.62 | 0.442478 | 1.64508 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2514.82 | 0.12696 | 178.579ms | 4604 | 640 | 3144.66 | 1745.94 | 0.0715436 | 1.20431 | 1(Win) | true |
| simdjson (ondemand) | 1921.54 | 0.474195 | 240.004ms | 4604 | 80 | 9392.41 | 2285 | 0.10929 | 1.57387 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6733.6 | 0.116763 | 260.429ms | 18245 | 2560 | 23304.6 | 2584.02 | 0.0105807 | 0.448289 | 1(Win) | true |
| simdjson (ondemand) | 5418.38 | 0.299916 | 327.024ms | 18245 | 160 | 14841.2 | 3211.25 | 0.155945 | 0.556892 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7145.7 | 0.31366 | 252.574ms | 18245 | 40 | 2333.33 | 2435 | 0.0683995 | 0.424333 | 1(Win) | true |
| simdjson (ondemand) | 5645.7 | 0.14984 | 314.055ms | 18245 | 1280 | 27297.2 | 3081.95 | 0.139615 | 0.534692 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 657.853 | 0.0806158 | 719.012ms | 4926 | 4890 | 162061 | 7141.1 | 0.311223 | 4.60604 | 1(Win) | true |
| simdjson (ondemand) | 591.467 | 0.0809818 | 796.338ms | 4926 | 4890 | 202307 | 7942.62 | 0.0546256 | 5.12438 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 867.153 | 0.258885 | 622.507ms | 4926 | 640 | 125890 | 5417.5 | 0.260251 | 3.49217 | 1(Win) | true |
| simdjson (ondemand) | 780.365 | 0.146858 | 704.488ms | 4926 | 30 | 2344.83 | 6020 | 0.166389 | 3.8894 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1029.75 | 0.16766 | 755.345ms | 8150 | 1280 | 204984 | 7547.89 | 0.0984272 | 2.94264 | 1(Win) | true |
| simdjson (ondemand) | 947.882 | 0.26795 | 823.343ms | 8150 | 2560 | 1.23582e+06 | 8199.8 | 0.255165 | 3.19849 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1362.17 | 0.153218 | 651.197ms | 8150 | 640 | 48916.2 | 5705.94 | 0.0547975 | 2.22291 | 1(Win) | true |
| simdjson (ondemand) | 1230.47 | 0.202016 | 729.813ms | 8150 | 30 | 4885.06 | 6316.67 | 0.681342 | 2.45843 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 497.009 | 0.306967 | 952.611ms | 4926 | 2560 | 2.15518e+06 | 9452.15 | 0.118748 | 6.10109 | 1(Win) | true |
| simdjson (ondemand) | 318.498 | 0.22149 | 1487.02ms | 4926 | 1280 | 1.36613e+06 | 14749.8 | 0.0816352 | 9.5278 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 609.708 | 0.192838 | 854.123ms | 4926 | 2560 | 565157 | 7705 | 0.353628 | 4.97184 | 1(Win) | true |
| simdjson (ondemand) | 362.501 | 0.15975 | 1385.09ms | 4926 | 4890 | 2.09586e+06 | 12959.4 | 0.226511 | 8.37008 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 743.308 | 0.16687 | 1050.26ms | 8150 | 640 | 194855 | 10456.6 | 0.0358498 | 4.08015 | 1(Win) | true |
| simdjson (ondemand) | 527.904 | 0.0684905 | 1488.74ms | 8150 | 4890 | 497251 | 14723.2 | 0.860182 | 5.74811 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 910.347 | 0.121431 | 937.276ms | 8150 | 1280 | 137586 | 8537.89 | 0.0760059 | 3.33064 | 1(Win) | true |
| simdjson (ondemand) | 612.124 | 0.374398 | 1375.79ms | 8150 | 320 | 723191 | 12697.5 | 0.370535 | 4.95829 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1215.1 | 0.126452 | 395.325ms | 4926 | 4890 | 116876 | 3866.18 | 0.659331 | 2.48799 | 1(Win) | true |
| simdjson (ondemand) | 1156.61 | 0.151845 | 408.698ms | 4926 | 4890 | 186004 | 4061.7 | 0.165669 | 2.61506 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1576.11 | 0.159616 | 334.652ms | 4926 | 2560 | 57944.1 | 2980.62 | 0.27861 | 1.91575 | 1(Win) | true |
| simdjson (ondemand) | 1433.55 | 0.177855 | 363.873ms | 4926 | 640 | 21740.8 | 3277.03 | 0.0714694 | 2.10847 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1925.44 | 0.248062 | 427.157ms | 8150 | 640 | 64173.9 | 4036.72 | 0.435486 | 1.57045 | 1(Win) | true |
| simdjson (ondemand) | 1800.57 | 0.695716 | 441.59ms | 8150 | 4890 | 4.41032e+06 | 4316.67 | 0.350181 | 1.67963 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2361.1 | 0.110149 | 364.429ms | 8150 | 2560 | 33658.1 | 3291.88 | 0.0427371 | 1.27965 | 1(Win) | true |
| simdjson (ondemand) | 2258.23 | 0.221372 | 382.934ms | 8150 | 2560 | 148616 | 3441.84 | 0.283399 | 1.33837 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1077.33 | 0.179843 | 439.284ms | 4926 | 4890 | 300739 | 4360.61 | 0.171127 | 2.80777 | 1(Win) | true |
| simdjson (ondemand) | 961.909 | 0.0949364 | 493.696ms | 4926 | 2560 | 55033.4 | 4883.83 | 0.456379 | 3.14778 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1285.58 | 0.0885384 | 401.794ms | 4926 | 2560 | 26797.4 | 3654.22 | 0.164893 | 2.35137 | 1(Win) | true |
| simdjson (ondemand) | 1115.62 | 0.0918167 | 459.006ms | 4926 | 4890 | 73098.2 | 4210.92 | 0.0227866 | 2.71281 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1670.92 | 0.166147 | 468.036ms | 8150 | 2560 | 152909 | 4651.6 | 0.0293831 | 1.8115 | 1(Win) | true |
| simdjson (ondemand) | 1546.84 | 0.181726 | 509.742ms | 8150 | 2560 | 213452 | 5024.73 | 0.309585 | 1.95709 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1949.78 | 0.171852 | 435.605ms | 8150 | 1280 | 60070.9 | 3986.33 | 0.123622 | 1.55047 | 1(Win) | true |
| simdjson (ondemand) | 1791.37 | 0.126689 | 472.298ms | 8150 | 2560 | 77350.7 | 4338.83 | 0.279874 | 1.68962 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1396.36 | 0.426216 | 200.087ms | 2821 | 30 | 2022.99 | 1926.67 | 0 | 2.16017 | 1(Win) | true |
| simdjson (ondemand) | 1228.45 | 0.219354 | 222.342ms | 2821 | 40 | 923.077 | 2190 | 0 | 2.43239 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.36 | 0.246565 | 187.572ms | 2821 | 4890 | 85826.6 | 1699.12 | 0.353961 | 1.89836 | 1(Win) | true |
| simdjson (ondemand) | 1348.32 | 0.0970734 | 218.391ms | 2821 | 320 | 1200.53 | 1995.31 | 0.607098 | 2.23533 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1695.92 | 0.38514 | 215.524ms | 3770 | 40 | 2666.67 | 2120 | 0 | 1.77871 | 1(Win) | true |
| simdjson (ondemand) | 1593.21 | 0.407764 | 228.89ms | 3770 | 30 | 2540.23 | 2256.67 | 0 | 1.89327 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1952.13 | 0.51449 | 201.502ms | 3770 | 2560 | 229858 | 1841.76 | 0.112283 | 1.542 | 1(Win) | true |
| simdjson (ondemand) | 1742.55 | 0.0830419 | 223.539ms | 3770 | 4890 | 14355.4 | 2063.27 | 0.411473 | 1.7293 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 664.823 | 0.228932 | 411.99ms | 2821 | 30 | 2574.71 | 4046.67 | 0.978793 | 4.57207 | 1(Win) | true |
| simdjson (ondemand) | 283.176 | 0.155098 | 953.07ms | 2821 | 4890 | 1.06173e+06 | 9500.49 | 0.286349 | 10.7117 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.641 | 0.149226 | 399.701ms | 2821 | 40 | 1224.36 | 3707.5 | 0.112511 | 4.16507 | 1(Win) | true |
| simdjson (ondemand) | 288.544 | 0.254251 | 948.778ms | 2821 | 640 | 359654 | 9323.75 | 0.630713 | 10.5143 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.326 | 0.153051 | 443.892ms | 3770 | 4890 | 223838 | 4420.55 | 0.108928 | 3.72004 | 1(Win) | true |
| simdjson (ondemand) | 379.463 | 0.474592 | 957.911ms | 3770 | 640 | 1.29409e+06 | 9474.84 | 0.35003 | 7.99401 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 887.467 | 0.138813 | 426.368ms | 3770 | 80 | 2530.06 | 4051.25 | 0.154512 | 3.41082 | 1(Win) | true |
| simdjson (ondemand) | 376.921 | 1.01872 | 947.585ms | 3770 | 160 | 1.51082e+06 | 9538.75 | 0.352572 | 8.0484 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4825.68 | 1.41988 | 57.4253ms | 2821 | 40 | 2506.41 | 557.5 | 0.446429 | 0.603722 | 1(Win) | true |
| simdjson (ondemand) | 3768.86 | 0.168385 | 73.5932ms | 2821 | 1280 | 1849.29 | 713.828 | 0.274363 | 0.783866 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5400.88 | 0.416376 | 53.4135ms | 2821 | 160 | 688.286 | 498.125 | 0.623441 | 0.546449 | 1(Win) | true |
| simdjson (ondemand) | 4048.2 | 0.167284 | 70.2506ms | 2821 | 2560 | 3163.94 | 664.57 | 0.300672 | 0.732047 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5706.91 | 0.229018 | 66.1544ms | 3770 | 1280 | 2664.58 | 630 | 0 | 0.517511 | 1(Win) | true |
| simdjson (ondemand) | 4658.89 | 0.164434 | 80.5055ms | 3770 | 1280 | 2061.16 | 771.719 | 0.141529 | 0.640286 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6080.75 | 0.162967 | 62.5353ms | 3770 | 4890 | 4540.22 | 591.268 | 0.3656 | 0.48502 | 1(Win) | true |
| simdjson (ondemand) | 4941 | 0.320226 | 77.1822ms | 3770 | 640 | 3474.94 | 727.656 | 0.539724 | 0.59931 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3463 | 0.430411 | 79.4894ms | 2821 | 160 | 1788.92 | 776.875 | 0.241935 | 0.854932 | 1(Win) | true |
| simdjson (ondemand) | 2758.98 | 0.360997 | 99.8374ms | 2821 | 4890 | 60593.4 | 975.112 | 0.518554 | 1.08073 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3735.33 | 0.183062 | 75.386ms | 2821 | 1280 | 2225.12 | 720.234 | 0.271916 | 0.792889 | 1(Win) | true |
| simdjson (ondemand) | 2931.55 | 0.165856 | 95.8346ms | 2821 | 4890 | 11328.8 | 917.71 | 0.388526 | 1.01642 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3915.47 | 0.146024 | 93.4574ms | 3770 | 2560 | 4602.61 | 918.242 | 0.1918 | 0.761386 | 1(Win) | true |
| simdjson (ondemand) | 3468.01 | 0.495394 | 106.767ms | 3770 | 640 | 16881.2 | 1036.72 | 0.591267 | 0.861261 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4143.01 | 0.186931 | 90.0553ms | 3770 | 4890 | 12868.4 | 867.812 | 0.171267 | 0.717435 | 1(Win) | true |
| simdjson (ondemand) | 3617.84 | 0.103169 | 103.714ms | 3770 | 4890 | 5140.32 | 993.783 | 0.121412 | 0.824284 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3565.47 | 0.34574 | 7519.42ms | 277673 | 1280 | 8.44001e+07 | 74270.6 | 0.130475 | 0.852139 | 1(Win) | true |
| Jsonifier (generic) | 3497.34 | 0.123071 | 7688.64ms | 277673 | 640 | 5.55749e+06 | 75717.3 | 0.0785612 | 0.868719 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3117.54 | 0.23784 | 5013.78ms | 10548466 | 30 | 1.76704e+09 | 3.22684e+06 | 1.19539 | 0.974745 | 1(Win) | true |
| Jsonifier (generic) | 2994.99 | 0.287484 | 5133.41ms | 10548466 | 30 | 2.79728e+09 | 3.35888e+06 | 0.337265 | 1.01475 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3088.47 | 0.118695 | 7405.87ms | 16002592 | 80 | 2.75202e+09 | 4.94137e+06 | 0.0435924 | 0.983932 | 1(Win) | true |
| simdjson (ondemand) | 2717.64 | 0.230269 | 8415.03ms | 16002592 | 80 | 1.3377e+10 | 5.61562e+06 | 0.121773 | 1.11832 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2730.22 | 0.165572 | 8420.68ms | 16002591 | 40 | 3.42626e+09 | 5.58976e+06 | 0.225276 | 1.11314 | 1(Win) | true |
| simdjson (ondemand) | 1718.26 | 0.152252 | 6222.54ms | 16002591 | 30 | 5.48596e+09 | 8.88182e+06 | 0.13529 | 1.76869 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 15931.5 | 0.112099 | 6131.24ms | 16197086 | 160 | 1.89009e+08 | 969570 | 0.221982 | 0.190702 | 1(Win) | true |
| simdjson (ondemand) | 14490.3 | 0.198779 | 6731ms | 16197086 | 320 | 1.43685e+09 | 1.06601e+06 | 0.963993 | 0.209668 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 15740.8 | 0.161666 | 6211.58ms | 16197085 | 160 | 4.02694e+08 | 981316 | 0.231346 | 0.193014 | 1(Win) | true |
| simdjson (ondemand) | 13671.9 | 0.446901 | 7266.33ms | 16197085 | 160 | 4.07903e+09 | 1.12981e+06 | 0.305145 | 0.222223 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1095.98 | 0.473664 | 6842.79ms | 4212000 | 80 | 2.41101e+10 | 3.66508e+06 | 0.226085 | 2.77258 | 1(Win) | true |
| simdjson (ondemand) | 1006.04 | 0.484953 | 7350.17ms | 4212000 | 40 | 1.4997e+10 | 3.99276e+06 | 0.049113 | 3.02062 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.68 | 0.580575 | 7619.56ms | 4212000 | 40 | 2.36211e+10 | 4.18564e+06 | 1.12615 | 3.16664 | 1(Win) | true |
| simdjson (ondemand) | 870.034 | 0.41025 | 8254.96ms | 4212000 | 80 | 2.87006e+10 | 4.61692e+06 | 0.0385416 | 3.49303 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1089.17 | 0.437945 | 6840.69ms | 4211999 | 80 | 2.08698e+10 | 3.68803e+06 | 0.278066 | 2.79026 | 1(Win) | true |
| simdjson (ondemand) | 901.799 | 0.324048 | 7879.17ms | 4211999 | 80 | 1.66673e+10 | 4.45429e+06 | 1.16285 | 3.36982 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.013 | 0.601719 | 7474.28ms | 4211999 | 30 | 1.90562e+10 | 4.18855e+06 | 0.422688 | 3.16901 | 1(Win) | true |
| simdjson (ondemand) | 797.323 | 0.615235 | 8809.11ms | 4211999 | 30 | 2.88212e+10 | 5.03795e+06 | 0.217624 | 3.8116 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 735.492 | 0.458895 | 9299.28ms | 4525120 | 30 | 2.17496e+10 | 5.86749e+06 | 0.297203 | 4.13202 | 1(Win) | true |
| simdjson (ondemand) | 707.652 | 0.245213 | 9746.84ms | 4525120 | 40 | 8.94472e+09 | 6.09832e+06 | 0.0118188 | 4.29471 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 490.864 | 0.273989 | 6382.29ms | 4525120 | 30 | 1.74071e+10 | 8.79162e+06 | 1.0968 | 6.19131 | 1(Win) | true |
| simdjson (ondemand) | 404.351 | 0.270897 | 7736.86ms | 4525120 | 40 | 3.34359e+10 | 1.06726e+07 | 0.0101906 | 7.51639 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.38 | 0.210008 | 9937.02ms | 4525119 | 80 | 1.38262e+10 | 6.25995e+06 | 0.714965 | 4.40839 | 1(Win) | true |
| simdjson (ondemand) | 607.56 | 0.182864 | 5263.79ms | 4525119 | 30 | 5.06128e+09 | 7.10299e+06 | 0.0443747 | 5.0022 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 500.333 | 0.305987 | 6265.69ms | 4525119 | 30 | 2.08963e+10 | 8.62524e+06 | 0.183156 | 6.07435 | 1(Win) | true |
| simdjson (ondemand) | 371.108 | 0.14702 | 8394.64ms | 4525119 | 40 | 1.16916e+10 | 1.16287e+07 | 0.336752 | 8.18975 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 695.976 | 0.310329 | 9327.9ms | 4203059 | 80 | 2.5555e+10 | 5.75932e+06 | 0.387369 | 4.36657 | 1(Win) | true |
| simdjson (ondemand) | 596.009 | 0.355414 | 5026.18ms | 4203059 | 30 | 1.71402e+10 | 6.72531e+06 | 0.0182925 | 5.09908 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 511.384 | 0.169306 | 5836.49ms | 4203059 | 40 | 7.04434e+09 | 7.83824e+06 | 0.0252672 | 5.94301 | 1(Win) | true |
| simdjson (ondemand) | 485.581 | 0.395678 | 6082.75ms | 4203059 | 30 | 3.20047e+10 | 8.25476e+06 | 0.133885 | 6.25886 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 671.532 | 0.17954 | 9666.02ms | 4203058 | 40 | 4.59391e+09 | 5.96896e+06 | 0.337623 | 4.52577 | 1(Win) | true |
| simdjson (ondemand) | 531.95 | 0.442044 | 5565.57ms | 4203058 | 30 | 3.32844e+10 | 7.5352e+06 | 0.15285 | 5.71309 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 497.991 | 0.17321 | 5995.93ms | 4203058 | 40 | 7.77492e+09 | 8.04904e+06 | 1.05116 | 6.10277 | 1(Win) | true |
| simdjson (ondemand) | 439.187 | 0.243659 | 6755.99ms | 4203058 | 40 | 1.97814e+10 | 9.12675e+06 | 1.07405 | 6.91999 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1135.24 | 0.188985 | 5512.22ms | 4197496 | 80 | 3.55264e+09 | 3.52618e+06 | 0.915845 | 2.67679 | 1(Win) | true |
| simdjson (ondemand) | 966.547 | 0.159234 | 6474.67ms | 4197496 | 80 | 3.47933e+09 | 4.14159e+06 | 0.109165 | 3.14416 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 733.012 | 0.16803 | 8427.53ms | 4197496 | 40 | 3.36816e+09 | 5.46109e+06 | 0.348952 | 4.14599 | 1(Win) | true |
| simdjson (ondemand) | 553.983 | 0.144233 | 5172.25ms | 4197496 | 40 | 4.34484e+09 | 7.22593e+06 | 0.0824448 | 5.48609 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1054.97 | 0.36119 | 5947.56ms | 4197495 | 30 | 5.63495e+09 | 3.79445e+06 | 0.140049 | 2.88066 | 1(Win) | true |
| simdjson (ondemand) | 790.807 | 0.118194 | 7872.89ms | 4197495 | 80 | 2.86363e+09 | 5.06197e+06 | 0.160056 | 3.84304 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 698.86 | 0.145151 | 8850.28ms | 4197495 | 80 | 5.53008e+09 | 5.72796e+06 | 0.535981 | 4.34872 | 1(Win) | true |
| simdjson (ondemand) | 493.732 | 0.139024 | 5828.76ms | 4197495 | 30 | 3.8115e+09 | 8.10772e+06 | 0.403412 | 6.15574 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 881.219 | 0.39203 | 8380ms | 4506447 | 30 | 1.09663e+10 | 4.87698e+06 | 0.173221 | 3.44881 | 1(Win) | true |
| simdjson (ondemand) | 746.096 | 0.124868 | 9819.07ms | 4506447 | 40 | 2.06938e+09 | 5.76022e+06 | 0.0892254 | 4.07346 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 590.907 | 0.230054 | 5593.98ms | 4506447 | 40 | 1.11982e+10 | 7.27302e+06 | 0.0465176 | 5.14345 | 1(Win) | true |
| simdjson (ondemand) | 397.176 | 0.228787 | 8172.07ms | 4506447 | 40 | 2.45146e+10 | 1.08206e+07 | 0.842546 | 7.65251 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.004 | 0.367801 | 8904.2ms | 4506446 | 80 | 2.93679e+10 | 5.20929e+06 | 0.0586828 | 3.68388 | 1(Win) | true |
| simdjson (ondemand) | 648.475 | 0.469033 | 5145.91ms | 4506446 | 30 | 2.89874e+10 | 6.62737e+06 | 0.402273 | 4.68678 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 581.928 | 0.291331 | 5715.2ms | 4506446 | 30 | 1.38875e+10 | 7.38525e+06 | 0.0313335 | 5.22264 | 1(Win) | true |
| simdjson (ondemand) | 366.357 | 0.185887 | 8767.94ms | 4506446 | 30 | 1.42652e+10 | 1.17309e+07 | 0.107012 | 8.29599 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1251.35 | 0.631257 | 5427.8ms | 4219120 | 80 | 3.29599e+10 | 3.21545e+06 | 0.31552 | 2.4286 | 1(Win) | true |
| simdjson (ondemand) | 1096.08 | 0.355057 | 6056.28ms | 4219120 | 80 | 1.35908e+10 | 3.67096e+06 | 0.45357 | 2.7727 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.416 | 0.481184 | 5044.28ms | 4219120 | 30 | 3.21515e+10 | 6.80344e+06 | 0.184413 | 5.13887 | 1(Win) | true |
| simdjson (ondemand) | 220.226 | 0.218453 | 5640.44ms | 4219120 | 30 | 4.77909e+10 | 1.82706e+07 | 0.188999 | 13.8012 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1191.94 | 0.596842 | 5613.16ms | 4219119 | 80 | 3.24745e+10 | 3.37572e+06 | 0.938415 | 2.54975 | 1(Win) | true |
| simdjson (ondemand) | 987.541 | 0.276229 | 6601.53ms | 4219119 | 80 | 1.01336e+10 | 4.07443e+06 | 0.334042 | 3.07757 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 595.832 | 0.370782 | 5007.51ms | 4219119 | 40 | 2.5078e+10 | 6.75302e+06 | 0.133564 | 5.10099 | 1(Win) | true |
| simdjson (ondemand) | 214.966 | 0.191291 | 5713.23ms | 4219119 | 30 | 3.84606e+10 | 1.87177e+07 | 0.00470166 | 14.139 | 2(Loss) | true |
