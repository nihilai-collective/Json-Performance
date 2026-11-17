# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 524.575 | 0.0902607 | 880.882ms | 905 | 1280 | 2822.86 | 1645.29 | 0.484778 | 10.1357 | 55.4608 | 5.50387 | 0.0011136 | 0.000115677 | 1.89917e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.398 | 0.0294175 | 1091.1ms | 905 | 4890 | 6042.71 | 3778.81 | 0.0573344 | 22.7554 | 104.421 | 9.82431 | 0.0802725 | 0.00012993 | 7.9088e-06 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 523.302 | 0.081691 | 877.187ms | 905 | 2560 | 4647.08 | 1649.29 | 0.0695367 | 10.0231 | 54.8055 | 5.27735 | 0.0015379 | 0.000110497 | 2.28764e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.311 | 0.048749 | 1092.4ms | 905 | 2560 | 8693.91 | 3780.26 | 0.124464 | 22.7593 | 103.737 | 9.68509 | 0.0889654 | 0.000200708 | 6.34496e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.023 | 0.0643782 | 1009.86ms | 1811 | 1280 | 4530.19 | 2922.23 | 0.0312164 | 8.83174 | 41.5191 | 6.03368 | 0.00115785 | 0.00014883 | 3.79625e-05 | 1(Win) | true |
| simdjson (ondemand) | 329.117 | 0.0528346 | 1245.49ms | 1811 | 2560 | 19679.4 | 5247.69 | 0.0081949 | 15.7115 | 77.2275 | 9.76091 | 0.00228875 | 0.000115613 | 3.58055e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 614.329 | 0.0768691 | 994.095ms | 1811 | 1280 | 5977.88 | 2811.36 | 0.15762 | 8.43031 | 40.3539 | 5.76532 | 0.00132912 | 9.18864e-05 | 1.03534e-05 | 1(Win) | true |
| simdjson (ondemand) | 338.785 | 0.0670485 | 1231.67ms | 1811 | 80 | 934.667 | 5097.94 | 0.0237785 | 15.3241 | 76.1817 | 9.53319 | 0.000738542 | 0.000110436 | 0 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1344.82 | 0.0222094 | 990.07ms | 3862 | 4890 | 1809.16 | 2738.72 | 0.0837304 | 3.88927 | 18.1567 | 2.01605 | 0.000263434 | 3.73309e-05 | 3.81251e-06 | 1(Win) | true |
| simdjson (ondemand) | 740.802 | 0.0539043 | 1213.48ms | 3862 | 80 | 574.588 | 4971.76 | 0.0434767 | 7.01487 | 32.0163 | 3.55153 | 0.00258933 | 0.000100337 | 7.44433e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1387.35 | 0.0417026 | 977.921ms | 3862 | 4890 | 5993.64 | 2654.77 | 0.136763 | 3.75899 | 17.6567 | 1.90471 | 0.000266823 | 4.31555e-05 | 4.50088e-06 | 1(Win) | true |
| simdjson (ondemand) | 759.292 | 0.0249562 | 1201.23ms | 3862 | 4890 | 7165.93 | 4850.69 | 0.0470601 | 6.8266 | 31.5601 | 3.45236 | 0.00182461 | 3.92901e-05 | 4.87154e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1381.55 | 0.250252 | 1371.13ms | 9578 | 80 | 21901 | 6611.64 | 0.028178 | 3.7454 | 17.7196 | 3.34172 | 0.00182188 | 3.13218e-05 | 1.30507e-06 | 1(Win) | true |
| simdjson (ondemand) | 1348.36 | 0.763663 | 1399.8ms | 9578 | 4890 | 1.30874e+07 | 6774.39 | 0.0929145 | 3.77733 | 19.237 | 2.98089 | 0.00333969 | 3.09802e-05 | 8.92468e-06 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1910.76 | 0.0340502 | 1330.97ms | 9578 | 2560 | 6782.94 | 4780.46 | 0.0245324 | 2.71341 | 13.6113 | 2.40342 | 0.000442339 | 2.89563e-05 | 5.42421e-06 | 1(Win) | true |
| simdjson (ondemand) | 1806.72 | 0.116074 | 1366.43ms | 9578 | 640 | 22040.2 | 5055.74 | 0.0045429 | 2.86355 | 15.0951 | 2.03257 | 0.00204603 | 3.86628e-05 | 1.40295e-05 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1332.47 | 0.0425117 | 996.691ms | 3873 | 320 | 444.373 | 2771.98 | 0.00078914 | 3.92079 | 18.1479 | 2.00645 | 0.00129502 | 4.84121e-05 | 2.4206e-06 | 1(Win) | true |
| simdjson (ondemand) | 741.844 | 0.0555835 | 1215.87ms | 3873 | 1280 | 9803.27 | 4978.92 | 0.0554219 | 6.95914 | 31.7565 | 3.66357 | 0.00488337 | 7.16095e-05 | 2.05751e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1376.37 | 0.0806143 | 983.501ms | 3873 | 80 | 374.401 | 2683.56 | 0.0647041 | 3.79796 | 17.6558 | 1.89801 | 0.00119739 | 8.06868e-05 | 1.61374e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.98 | 0.0485092 | 1209.73ms | 3873 | 1280 | 7266.77 | 4911.81 | 0.130835 | 6.87853 | 31.3016 | 3.56468 | 0.00759525 | 4.43777e-05 | 3.22747e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1565.21 | 0.0231019 | 6506.29ms | 94653 | 2560 | 454421 | 57671.6 | 0.0267941 | 3.24148 | 14.8731 | 2.85132 | 0.00885107 | 1.32763e-05 | 8.66652e-06 | 1(Win) | true |
| simdjson (ondemand) | 1240.08 | 0.0166565 | 8023.77ms | 94653 | 4890 | 718861 | 72792.3 | 0.00278093 | 4.09264 | 15.8667 | 3.10348 | 0.0118896 | 1.70335e-05 | 1.17856e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2288.39 | 0.065708 | 5946.98ms | 94653 | 4890 | 3.28513e+06 | 39446.1 | 0.0592466 | 2.21375 | 11.0843 | 1.98275 | 0.0057676 | 1.23128e-05 | 7.9334e-06 | 1(Win) | true |
| simdjson (ondemand) | 1630.32 | 0.0969358 | 7478.8ms | 94653 | 160 | 460905 | 55368.4 | 0.0321812 | 3.12686 | 12.1068 | 2.24341 | 0.00882704 | 9.70651e-06 | 5.87673e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.92 | 0.0411218 | 6818.03ms | 124597 | 640 | 398611 | 60689.4 | 0.00726495 | 2.59305 | 11.671 | 2.17247 | 0.00718291 | 3.26051e-06 | 7.39885e-07 | 1(Win) | true |
| simdjson (ondemand) | 1596.65 | 0.0314865 | 8156.85ms | 124597 | 1280 | 702838 | 74421.6 | 0.0124707 | 3.1832 | 12.3701 | 2.36885 | 0.00924659 | 6.21378e-06 | 2.87803e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2829.23 | 0.034429 | 6201.47ms | 124597 | 2560 | 535262 | 41999 | 0.135061 | 1.7899 | 8.79962 | 1.51452 | 0.00448245 | 1.19761e-05 | 8.46793e-06 | 1(Win) | true |
| simdjson (ondemand) | 2100.57 | 0.0338336 | 7606.02ms | 124597 | 4890 | 1.79121e+06 | 56567.9 | 0.213175 | 2.42793 | 9.51668 | 1.71565 | 0.00656843 | 7.29222e-06 | 3.93744e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1113.32 | 0.058559 | 8827.6ms | 94653 | 320 | 721388 | 81080.4 | 0.0573679 | 4.54869 | 20.6428 | 4.21044 | 0.010938 | 1.22157e-05 | 6.471e-06 | 1(Win) | true |
| simdjson (ondemand) | 700.137 | 0.0305407 | 6968.92ms | 94653 | 2560 | 3.96917e+06 | 128929 | 0.166858 | 7.24311 | 34.1184 | 7.06154 | 0.0128311 | 6.81849e-05 | 5.31918e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1439.17 | 0.0166634 | 8266.76ms | 94653 | 4890 | 534171 | 62722.5 | 0.163941 | 3.51841 | 16.8554 | 3.34383 | 0.00779316 | 7.44513e-06 | 3.34879e-06 | 1(Win) | true |
| simdjson (ondemand) | 812.31 | 0.0331881 | 6708.15ms | 94653 | 1280 | 1.741e+06 | 111125 | 0.0946126 | 6.22536 | 30.3784 | 6.20564 | 0.0105151 | 2.89462e-05 | 2.094e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1441.15 | 0.0240054 | 9018.94ms | 124597 | 2560 | 1.0029e+06 | 82451.6 | 0.00174064 | 3.53575 | 16.2022 | 3.25294 | 0.00790579 | 1.23774e-05 | 8.33625e-06 | 1(Win) | true |
| simdjson (ondemand) | 914.782 | 0.0367294 | 7032.78ms | 124597 | 1280 | 2.91352e+06 | 129894 | 0.59945 | 5.55274 | 25.9927 | 5.32434 | 0.0101903 | 1.52554e-05 | 1.02957e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1822.29 | 0.0204773 | 8488.76ms | 124597 | 2560 | 456422 | 65206.6 | 0.0187972 | 2.78345 | 13.3353 | 2.59718 | 0.00586794 | 1.6939e-05 | 9.96964e-06 | 1(Win) | true |
| simdjson (ondemand) | 1072.6 | 0.220746 | 6700.6ms | 124597 | 30 | 1.7941e+06 | 110782 | 0.231599 | 4.77134 | 23.1441 | 4.67254 | 0.00769441 | 6.4207e-06 | 2.67529e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.8 | 0.105986 | 4378.24ms | 94653 | 640 | 934429 | 36052.4 | 0.190567 | 2.02532 | 9.5773 | 1.71248 | 0.00517287 | 3.89581e-06 | 1.43617e-06 | 1(Win) | true |
| simdjson (ondemand) | 1794.02 | 0.0190647 | 5780.26ms | 94653 | 4890 | 449969 | 50316.1 | 0.00156859 | 2.84297 | 10.6669 | 1.97229 | 0.00829069 | 2.38996e-05 | 1.69557e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3304.5 | 0.0412228 | 3965.77ms | 94653 | 4890 | 620071 | 27316.7 | 0.0180563 | 1.52936 | 7.72976 | 1.27821 | 0.00324509 | 3.21484e-06 | 7.19451e-07 | 1(Win) | true |
| simdjson (ondemand) | 2104.96 | 0.109083 | 5451.52ms | 94653 | 160 | 350116 | 42883.4 | 0.0324531 | 2.40817 | 8.84344 | 1.54555 | 0.0080533 | 3.16947e-06 | 6.60307e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3053.87 | 0.0994294 | 4637.3ms | 124597 | 80 | 119738 | 38909.6 | 0.0616874 | 1.6869 | 7.69259 | 1.31784 | 0.00474179 | 1.3042e-05 | 1.09353e-05 | 1(Win) | true |
| simdjson (ondemand) | 2438.65 | 0.0208662 | 5629.92ms | 124597 | 4890 | 505486 | 48725.7 | 0.0255628 | 2.09119 | 8.16262 | 1.45471 | 0.00538409 | 1.26067e-05 | 8.89576e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4091.14 | 0.069958 | 4158.7ms | 124597 | 1280 | 528457 | 29044.4 | 0.123037 | 1.24715 | 6.28651 | 0.987855 | 0.00233342 | 3.04105e-06 | 1.08475e-06 | 1(Win) | true |
| simdjson (ondemand) | 2935.78 | 0.0345845 | 5267.45ms | 124597 | 4890 | 958162 | 40474.7 | 0.104778 | 1.73378 | 6.78006 | 1.1308 | 0.00465579 | 1.35291e-05 | 1.0089e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1820.82 | 0.0902405 | 5711.66ms | 94653 | 1280 | 2.5618e+06 | 49575.4 | 0.0137499 | 2.7678 | 12.6873 | 2.50996 | 0.00767166 | 1.07547e-05 | 6.92497e-06 | 1(Win) | true |
| simdjson (ondemand) | 1539 | 0.0336766 | 6576.46ms | 94653 | 1280 | 499411 | 58653.7 | 0.068052 | 3.2851 | 13.2163 | 2.50824 | 0.00952562 | 8.46843e-06 | 3.13646e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2201.78 | 0.192172 | 5401.41ms | 94653 | 320 | 1.98632e+06 | 40997.8 | 0.172738 | 2.31509 | 10.8438 | 2.07789 | 0.00686659 | 1.86206e-05 | 1.2975e-05 | 1(Win) | true |
| simdjson (ondemand) | 1791.02 | 0.194846 | 6198.34ms | 94653 | 30 | 289315 | 50400.3 | 0.0338075 | 2.84574 | 11.3914 | 2.081 | 0.00942953 | 3.8738e-05 | 2.99339e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2337.43 | 0.0310605 | 5832.2ms | 124597 | 4890 | 1.21917e+06 | 50835.6 | 0.450079 | 2.18198 | 10.0945 | 1.9305 | 0.00548468 | 1.21947e-05 | 7.28566e-06 | 1(Win) | true |
| simdjson (ondemand) | 2072.89 | 0.0378658 | 6476.78ms | 124597 | 1280 | 603067 | 57323.3 | 0.0914418 | 2.46147 | 10.0984 | 1.86079 | 0.0071303 | 4.57726e-06 | 1.58009e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2772.63 | 0.0248431 | 5503.22ms | 124597 | 1280 | 145095 | 42856.4 | 0.000242453 | 1.82552 | 8.69081 | 1.60163 | 0.00483377 | 2.66484e-06 | 6.27022e-07 | 1(Win) | true |
| simdjson (ondemand) | 2432.44 | 0.0435893 | 6124.58ms | 124597 | 640 | 290182 | 48850.1 | 0.00318247 | 2.09143 | 8.71778 | 1.53843 | 0.00617264 | 9.01657e-06 | 5.63065e-06 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 802.146 | 0.162454 | 7756.44ms | 2090234 | 40 | 6.51936e+08 | 2.48509e+06 | 0.11019 | 6.32798 | 30.3516 | 5.61815 | 0.0232553 | 0.105551 | 0.00100216 | 1(Win) | true |
| Jsonifier (generic) | 762.829 | 0.443205 | 8117.71ms | 2090234 | 160 | 2.14618e+10 | 2.61317e+06 | 0.0593681 | 6.65966 | 30.981 | 6.39269 | 0.0224095 | 0.103286 | 0.000866895 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 944.573 | 0.512969 | 7745.43ms | 2090234 | 30 | 3.51579e+09 | 2.11038e+06 | 0.189973 | 5.41087 | 25.0602 | 4.35791 | 0.0224841 | 0.0806506 | 0.000639546 | 1(Win) | true |
| Jsonifier (generic) | 902.867 | 0.178674 | 8072.82ms | 2090234 | 80 | 1.24496e+09 | 2.20786e+06 | 0.129119 | 5.61663 | 25.6684 | 5.12899 | 0.0214033 | 0.079108 | 0.00153053 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1850.77 | 0.219525 | 8339.97ms | 5212421 | 30 | 1.04295e+09 | 2.68589e+06 | 0.182999 | 2.75238 | 12.9706 | 2.28631 | 0.0103844 | 0.0621325 | 0.00121618 | 1(Win) | true |
| Jsonifier (generic) | 1780.79 | 0.0886109 | 8681.61ms | 5212421 | 160 | 9.78919e+08 | 2.79143e+06 | 0.0494479 | 2.84948 | 13.2668 | 2.60424 | 0.0103334 | 0.0620854 | 0.00044157 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2178.22 | 0.0403093 | 8259.87ms | 5212421 | 160 | 1.35396e+08 | 2.28212e+06 | 0.0172792 | 2.35955 | 10.8569 | 1.78258 | 0.0100525 | 0.0519095 | 0.000243349 | 1(Win) | true |
| Jsonifier (generic) | 2042.16 | 0.114258 | 8730.85ms | 5212421 | 160 | 1.23764e+09 | 2.43417e+06 | 0.315843 | 2.47991 | 11.1545 | 2.10082 | 0.00993631 | 0.0518829 | 0.000846582 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.8 | 0.147873 | 8502.12ms | 2090234 | 40 | 6.54353e+08 | 2.73519e+06 | 0.0167317 | 6.92031 | 33.851 | 7.0314 | 0.0225314 | 0.155594 | 5.5257e-05 | 1(Win) | true |
| simdjson (ondemand) | 724.105 | 0.235693 | 8547.52ms | 2090234 | 80 | 3.368e+09 | 2.75292e+06 | 0.188012 | 6.98442 | 34.6601 | 6.57596 | 0.0232925 | 0.180978 | 0.000135445 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 853.593 | 0.0780038 | 8478.2ms | 2090234 | 160 | 5.30934e+08 | 2.33531e+06 | 0.0676436 | 5.96587 | 28.5482 | 5.76888 | 0.0213732 | 0.130074 | 0.000218968 | 1(Win) | true |
| simdjson (ondemand) | 844.322 | 0.212687 | 8555.52ms | 2090234 | 160 | 4.03436e+09 | 2.36095e+06 | 0.482181 | 6.01999 | 29.379 | 5.3176 | 0.0222502 | 0.155225 | 7.46597e-05 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1595.1 | 0.15697 | 9687.41ms | 5212421 | 160 | 3.82872e+09 | 3.11638e+06 | 0.18402 | 3.15713 | 14.4215 | 2.86079 | 0.0103214 | 0.101567 | 0.00107828 | 1(Win) | true |
| simdjson (ondemand) | 1557.63 | 0.626771 | 9903.71ms | 5212421 | 160 | 6.40155e+10 | 3.19135e+06 | 0.0024851 | 3.22551 | 14.7124 | 2.67314 | 0.0104583 | 0.121099 | 0.00117534 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1844.07 | 0.269302 | 9573.18ms | 5212421 | 160 | 8.43187e+09 | 2.69564e+06 | 0.364851 | 2.77335 | 12.5889 | 2.16753 | 0.0100202 | 0.1103 | 0.000923146 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1833.7 | 0.184797 | 9724.62ms | 5212421 | 40 | 1.00386e+09 | 2.71089e+06 | 0.667238 | 2.73115 | 12.309 | 2.35719 | 0.00985032 | 0.089844 | 0.000177772 | 1(Tie) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8430.96 | 0.315944 | 6244.35ms | 2090234 | 320 | 1.78569e+08 | 236438 | 0.128845 | 0.594696 | 3.18965 | 0.396912 | 0.00247093 | 0.0502538 | 3.5313e-06 | 1(Win) | true |
| simdjson (ondemand) | 7066.46 | 0.111379 | 7326.81ms | 2090234 | 80 | 7.89737e+06 | 282093 | 0.0171545 | 0.717452 | 3.66628 | 0.418404 | 0.00293722 | 0.0497695 | 2.3861e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8525.08 | 0.140999 | 6295.57ms | 2090234 | 40 | 4.34796e+06 | 233828 | 0.271715 | 0.59217 | 3.18958 | 0.396895 | 0.00244135 | 0.0501908 | 3.97085e-06 | 1(Win) | true |
| simdjson (ondemand) | 7254.83 | 0.228664 | 7290.41ms | 2090234 | 80 | 3.15807e+07 | 274769 | 0.261025 | 0.706786 | 3.6662 | 0.418386 | 0.00235827 | 0.0497088 | 5.74098e-07 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11284.6 | 0.776665 | 5704.28ms | 5212421 | 160 | 1.87281e+09 | 440508 | 0.117342 | 0.447269 | 1.96707 | 0.181297 | 0.0022839 | 0.0394066 | 1.71945e-06 | 1(Win) | true |
| simdjson (ondemand) | 9658.15 | 0.103707 | 6698.04ms | 5212421 | 640 | 1.82343e+08 | 514690 | 0.624121 | 0.526363 | 2.27766 | 0.202785 | 0.00212592 | 0.0394736 | 8.04269e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11420.1 | 0.220099 | 5656.51ms | 5212421 | 160 | 1.46857e+08 | 435280 | 0.103794 | 0.443041 | 1.96704 | 0.18129 | 0.00227705 | 0.0393858 | 2.1631e-06 | 1(Win) | true |
| simdjson (ondemand) | 9694.64 | 0.0720456 | 6671.58ms | 5212421 | 640 | 8.73393e+07 | 512752 | 0.467094 | 0.52551 | 2.27762 | 0.202778 | 0.00212416 | 0.0393925 | 4.7168e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6308.57 | 0.269671 | 8312.82ms | 2090234 | 160 | 1.16176e+08 | 315983 | 0.0168253 | 0.802983 | 4.62947 | 0.716865 | 0.00247044 | 0.0751966 | 5.37918e-06 | 1(Win) | true |
| simdjson (ondemand) | 5590.19 | 0.135797 | 9490.8ms | 2090234 | 160 | 3.7518e+07 | 356590 | 0.200676 | 0.91461 | 5.10596 | 0.738336 | 0.00249183 | 0.0742858 | 3.26817e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6353.79 | 0.100026 | 8275.77ms | 2090234 | 640 | 6.3028e+07 | 313735 | 0.0545257 | 0.800722 | 4.62939 | 0.716848 | 0.00240175 | 0.0751273 | 4.14128e-06 | 1(Win) | true |
| simdjson (ondemand) | 5434.49 | 0.956253 | 9537.3ms | 2090234 | 640 | 7.87406e+09 | 366806 | 0.140474 | 0.935264 | 5.10588 | 0.738318 | 0.00234006 | 0.074207 | 2.7008e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8940.42 | 0.220181 | 7200.98ms | 5212421 | 80 | 1.19899e+08 | 556009 | 0.414866 | 0.566356 | 2.54445 | 0.309603 | 0.00225188 | 0.0590724 | 3.54202e-06 | 1(Win) | true |
| simdjson (ondemand) | 7826.32 | 0.0953822 | 8199.52ms | 5212421 | 320 | 1.17449e+08 | 635158 | 0.2085 | 0.649412 | 2.85498 | 0.331081 | 0.00218947 | 0.059067 | 8.04449e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8959.15 | 0.271041 | 7343.63ms | 5212421 | 30 | 6.78482e+07 | 554847 | 0.00574967 | 0.565148 | 2.54442 | 0.309596 | 0.00224566 | 0.0590648 | 2.36614e-06 | 1(Win) | true |
| simdjson (ondemand) | 7771.52 | 0.238886 | 8271.59ms | 5212421 | 640 | 1.49427e+09 | 639637 | 0.172993 | 0.65241 | 2.85495 | 0.331074 | 0.00213405 | 0.0590408 | 4.85619e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1402.15 | 0.202441 | 8982.08ms | 500299 | 40 | 1.89813e+07 | 340278 | 0.00540273 | 3.62736 | 16.7806 | 3.13038 | 0.0145345 | 0.0100136 | 8.66482e-05 | 1(Win) | true |
| simdjson (ondemand) | 1164.64 | 0.249283 | 5308.11ms | 500299 | 160 | 1.66872e+08 | 409675 | 0.158192 | 4.33663 | 17.745 | 2.9652 | 0.0238359 | 0.0171811 | 4.63473e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1567.61 | 0.393426 | 8783.96ms | 500299 | 320 | 4.58836e+08 | 304362 | 0.535791 | 3.22657 | 15.6556 | 2.85677 | 0.00974652 | 0.00920591 | 1.90324e-05 | 1(Win) | true |
| simdjson (ondemand) | 1312.95 | 0.174042 | 5206.29ms | 500299 | 40 | 1.60003e+07 | 363397 | 0.0330235 | 3.86257 | 16.6243 | 2.69375 | 0.0188642 | 0.0131214 | 0.00010079 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2756.86 | 1.0223 | 5170.03ms | 1151920 | 320 | 5.31035e+09 | 398481 | 0.149284 | 1.83096 | 8.01192 | 1.39408 | 0.00639899 | 0.0333485 | 2.22834e-05 | 1(Win) | true |
| simdjson (ondemand) | 2479.42 | 0.0515689 | 5776.59ms | 1151920 | 640 | 3.34118e+07 | 443070 | 0.296414 | 2.04182 | 8.47093 | 1.32101 | 0.0100484 | 0.0343001 | 4.5728e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3098.78 | 0.757112 | 5035.23ms | 1151920 | 640 | 4.61067e+09 | 354513 | 0.0671075 | 1.62567 | 7.52153 | 1.2748 | 0.00430095 | 0.0299137 | 1.42385e-05 | 1(Win) | true |
| simdjson (ondemand) | 2749.21 | 0.15058 | 5671ms | 1151920 | 40 | 1.44819e+07 | 399590 | 0.0211589 | 1.84192 | 7.98487 | 1.20338 | 0.00807567 | 0.0303145 | 5.49083e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 691.314 | 0.212244 | 8967.98ms | 500299 | 30 | 6.43728e+07 | 690168 | 0.202819 | 7.37737 | 35.6971 | 7.46767 | 0.0207511 | 0.0118689 | 5.3568e-05 | 1(Win) | true |
| simdjson (ondemand) | 423.858 | 0.267007 | 7163.35ms | 500299 | 320 | 2.89079e+09 | 1.12567e+06 | 0.198203 | 12.033 | 63.4992 | 13.0632 | 0.0359795 | 0.0191071 | 0.000335175 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 739.305 | 0.0490344 | 8750.05ms | 500299 | 320 | 3.20453e+07 | 645366 | 0.0110942 | 6.86604 | 34.5597 | 7.19217 | 0.0149748 | 0.00900839 | 4.70406e-05 | 1(Win) | true |
| simdjson (ondemand) | 443.675 | 0.0968055 | 7094.11ms | 500299 | 160 | 1.734e+08 | 1.07539e+06 | 0.157477 | 11.4224 | 62.3711 | 12.7908 | 0.0299685 | 0.0136618 | 3.23182e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1478.55 | 0.11799 | 9618.48ms | 1151920 | 160 | 1.22965e+08 | 742996 | 0.218483 | 3.42934 | 16.281 | 3.30691 | 0.00882335 | 0.0397234 | 4.7551e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.652 | 0.157464 | 7457.56ms | 1151920 | 30 | 1.00172e+08 | 1.16047e+06 | 0.1566 | 5.37337 | 28.3071 | 5.69846 | 0.0148778 | 0.080316 | 0.000118845 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.25 | 0.104852 | 9403.91ms | 1151920 | 320 | 1.72191e+08 | 699605 | 0.0534387 | 3.21808 | 15.7892 | 3.18802 | 0.00593913 | 0.0345924 | 1.2821e-05 | 1(Win) | true |
| simdjson (ondemand) | 970.373 | 0.513231 | 7479.42ms | 1151920 | 160 | 5.4015e+09 | 1.1321e+06 | 0.21553 | 5.22492 | 27.8221 | 5.58149 | 0.012822 | 0.0717891 | 3.94287e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5443.84 | 0.052315 | 9523.73ms | 500299 | 640 | 1.34549e+06 | 87644.5 | 0.0828872 | 0.938007 | 4.98824 | 0.721071 | 0.000931733 | 1.83984e-05 | 3.08878e-06 | 1(Win) | true |
| simdjson (ondemand) | 4984.87 | 0.0297389 | 5273.86ms | 500299 | 1280 | 1.03708e+06 | 95714.1 | 0.0610278 | 1.02656 | 5.64575 | 0.723983 | 0.00102418 | 0.000606551 | 1.73818e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5469.83 | 0.0505124 | 9457.61ms | 500299 | 2560 | 4.9699e+06 | 87228 | 0.131907 | 0.930516 | 4.96274 | 0.714799 | 0.000910715 | 5.67785e-06 | 4.00542e-06 | 1(Win) | true |
| simdjson (ondemand) | 5068.18 | 0.0880877 | 5249.45ms | 500299 | 30 | 206304 | 94140.8 | 0.0169929 | 1.01615 | 5.62024 | 0.717693 | 0.000991474 | 0.000303552 | 5.66328e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8752.44 | 0.116541 | 6869.43ms | 1151920 | 80 | 1.71172e+06 | 125514 | 0.0609067 | 0.584738 | 2.88336 | 0.336227 | 0.000606086 | 0.00788671 | 6.23958e-06 | 1(Win) | true |
| simdjson (ondemand) | 8046.65 | 0.0850656 | 7383.51ms | 1151920 | 2560 | 3.45273e+07 | 136524 | 0.0503683 | 0.633718 | 3.21555 | 0.347537 | 0.000889466 | 0.0100421 | 1.07236e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8709.26 | 0.0673757 | 6835.63ms | 1151920 | 30 | 216676 | 126137 | 0.0706082 | 0.580448 | 2.87229 | 0.333502 | 0.000562481 | 0.00713157 | 4.16696e-06 | 1(Win) | true |
| simdjson (ondemand) | 8045.96 | 0.0597407 | 7366.72ms | 1151920 | 640 | 4.25804e+06 | 136535 | 0.567605 | 0.628649 | 3.20446 | 0.344805 | 0.000857526 | 0.00957411 | 8.65132e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3070.33 | 0.0587032 | 8349.56ms | 500299 | 320 | 2.66294e+06 | 155398 | 0.0140205 | 1.66604 | 9.43971 | 1.76389 | 0.0021343 | 2.01192e-05 | 5.12818e-06 | 1(Win) | true |
| simdjson (ondemand) | 2976.86 | 0.0427468 | 8546.03ms | 500299 | 640 | 3.00421e+06 | 160277 | 0.027974 | 1.70761 | 10.191 | 1.7313 | 0.00221567 | 0.000428581 | 9.83474e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3078.18 | 0.0630635 | 8377.88ms | 500299 | 320 | 3.05758e+06 | 155002 | 0.0167228 | 1.66473 | 9.41419 | 1.7576 | 0.00211112 | 5.91209e-05 | 5.47423e-05 | 1(Win) | true |
| simdjson (ondemand) | 3020.21 | 0.0918605 | 8529.51ms | 500299 | 80 | 1.68474e+06 | 157977 | 0.108719 | 1.6989 | 10.1655 | 1.72501 | 0.00218837 | 0.000175295 | 1.0044e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5699.67 | 0.0602181 | 5196.34ms | 1151920 | 30 | 404129 | 192740 | 0.0522911 | 0.90319 | 4.82304 | 0.792308 | 0.00121692 | 0.00790689 | 3.44642e-05 | 1(Win) | true |
| simdjson (ondemand) | 5621.1 | 0.0469544 | 5222.99ms | 1151920 | 160 | 1.34733e+06 | 195434 | 0.0855693 | 0.914478 | 5.18965 | 0.785032 | 0.00148591 | 0.0099486 | 1.05259e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5709.83 | 0.0600298 | 5116.81ms | 1151920 | 640 | 8.53715e+06 | 192397 | 0.0756316 | 0.898742 | 4.81196 | 0.789576 | 0.0011616 | 0.00722829 | 1.11499e-06 | 1(Win) | true |
| simdjson (ondemand) | 5663.33 | 0.0336646 | 5166.22ms | 1151920 | 160 | 682288 | 193977 | 0.0145099 | 0.908919 | 5.17857 | 0.7823 | 0.00141068 | 0.00961335 | 2.51211e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1458.51 | 0.0694267 | 4435.92ms | 56369 | 160 | 104769 | 36857.8 | 0.000237398 | 3.53231 | 15.0925 | 2.97584 | 0.00783354 | 2.86061e-05 | 2.00687e-05 | 1(Win) | true |
| simdjson (ondemand) | 1285.45 | 0.0167645 | 4908.36ms | 56369 | 4890 | 240357 | 41820 | 0.00715148 | 3.99212 | 15.7675 | 2.79637 | 0.0102245 | 1.68623e-05 | 8.4892e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1829.74 | 0.0555053 | 4003.58ms | 56369 | 160 | 42549.3 | 29380 | 0.00738118 | 2.81778 | 12.9451 | 2.5053 | 0.00570183 | 4.43506e-06 | 9.97889e-07 | 1(Win) | true |
| simdjson (ondemand) | 1507.87 | 0.0515737 | 4677.68ms | 56369 | 640 | 216365 | 35651.3 | 0.0043168 | 3.41217 | 13.6462 | 2.33469 | 0.010937 | 1.79897e-05 | 7.6782e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2072.2 | 0.0646725 | 4601.29ms | 83958 | 320 | 199826 | 38639.4 | 0.119053 | 2.47377 | 10.6036 | 2.00465 | 0.00443231 | 3.05957e-05 | 2.06949e-05 | 1(Win) | true |
| simdjson (ondemand) | 1808.23 | 0.0431794 | 5166.83ms | 83958 | 320 | 116982 | 44280 | 0.0467839 | 2.84937 | 11.0492 | 1.8967 | 0.00974736 | 1.20596e-05 | 5.50871e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2500.51 | 0.0220374 | 4273.13ms | 83958 | 4890 | 243499 | 32020.9 | 0.0323646 | 2.0595 | 9.17348 | 1.69356 | 0.00416281 | 1.49481e-05 | 7.47282e-06 | 1(Win) | true |
| simdjson (ondemand) | 2248.14 | 0.0484336 | 4600.49ms | 83958 | 640 | 190437 | 35615.4 | 0.101938 | 2.28872 | 9.63681 | 1.58889 | 0.00452401 | 4.71962e-05 | 3.46155e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.662 | 0.0241515 | 9096.21ms | 56369 | 4890 | 1.97117e+06 | 83131 | 0.0431614 | 7.91236 | 35.0349 | 7.33999 | 0.0118357 | 4.42091e-05 | 2.89649e-05 | 1(Win) | true |
| simdjson (ondemand) | 209.208 | 0.032534 | 6731.3ms | 56369 | 1280 | 8.94561e+06 | 256959 | 0.22868 | 24.3746 | 132.868 | 28.2675 | 0.044731 | 3.4843e-05 | 1.43447e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.938 | 0.168982 | 8627.96ms | 56369 | 30 | 485695 | 75297.4 | 0.00974011 | 7.21206 | 32.8781 | 6.86546 | 0.0102515 | 8.87012e-06 | 2.36537e-06 | 1(Win) | true |
| simdjson (ondemand) | 216.533 | 0.0728458 | 6660.98ms | 56369 | 160 | 5.23312e+06 | 248265 | 0.0669087 | 23.7043 | 130.769 | 27.8069 | 0.0428329 | 3.62566e-05 | 1.82946e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.9 | 0.0239239 | 9602.08ms | 83958 | 1280 | 574853 | 88581.3 | 0.225463 | 5.68802 | 24.715 | 5.23774 | 0.00820764 | 1.0701e-05 | 3.8989e-06 | 1(Win) | true |
| simdjson (ondemand) | 311.833 | 0.0538835 | 6740.38ms | 83958 | 640 | 1.22511e+07 | 256768 | 0.0909545 | 16.3983 | 89.3675 | 18.9301 | 0.0282328 | 4.45163e-05 | 2.12532e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.837 | 0.0910259 | 9237.05ms | 83958 | 40 | 222219 | 81883.4 | 0.113848 | 5.26675 | 23.2811 | 4.92208 | 0.00711576 | 8.93304e-06 | 5.06205e-06 | 1(Win) | true |
| simdjson (ondemand) | 320.834 | 0.125088 | 6645.73ms | 83958 | 80 | 7.79621e+06 | 249564 | 0.112989 | 15.9241 | 87.9664 | 18.623 | 0.0279906 | 1.4144e-05 | 4.16875e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2493.82 | 0.0425622 | 2893.75ms | 56369 | 1280 | 107748 | 21556.4 | 0.0954252 | 2.06283 | 9.68004 | 1.70013 | 0.00374247 | 1.76987e-05 | 9.72942e-06 | 1(Win) | true |
| simdjson (ondemand) | 2162.82 | 0.0291812 | 3220.66ms | 56369 | 2560 | 134676 | 24855.4 | 0.0459244 | 2.37119 | 10.1759 | 1.70338 | 0.00462404 | 1.11154e-05 | 4.22024e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.04 | 0.0605781 | 2728.9ms | 56369 | 640 | 68661.7 | 17098.3 | 0.0265357 | 1.63587 | 8.12345 | 1.36109 | 0.00256527 | 4.01927e-06 | 4.43506e-07 | 1(Win) | true |
| simdjson (ondemand) | 2677.9 | 0.0246424 | 3022.94ms | 56369 | 2560 | 62646.7 | 20074.6 | 0.0687412 | 1.92395 | 8.62093 | 1.36614 | 0.00279416 | 1.80798e-05 | 1.07827e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3418.55 | 0.0216314 | 3071.24ms | 83958 | 2560 | 65713.1 | 23421.8 | 0.00523044 | 1.50483 | 7.01835 | 1.16112 | 0.00227097 | 6.2066e-06 | 2.46124e-06 | 1(Win) | true |
| simdjson (ondemand) | 3081.13 | 0.0449108 | 3334.67ms | 83958 | 320 | 43586.9 | 25986.7 | 0.0602228 | 1.67319 | 7.3063 | 1.16502 | 0.00338313 | 3.38711e-06 | 6.32757e-07 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4146.24 | 0.037549 | 2949.16ms | 83958 | 4890 | 257111 | 19311.1 | 0.0708103 | 1.2342 | 5.97592 | 0.934658 | 0.00198426 | 3.93857e-06 | 9.03656e-07 | 1(Win) | true |
| simdjson (ondemand) | 3738.17 | 0.0271086 | 3154ms | 83958 | 1280 | 43154.8 | 21419.2 | 0.0266844 | 1.37975 | 6.26096 | 0.938338 | 0.00186136 | 4.13153e-06 | 9.58441e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.34 | 0.0467705 | 3610.02ms | 56369 | 640 | 118681 | 29115.8 | 0.0702969 | 2.7432 | 13.1183 | 2.49577 | 0.00434736 | 7.12382e-06 | 1.66315e-06 | 1(Win) | true |
| simdjson (ondemand) | 1318.56 | 0.0242858 | 4807.62ms | 56369 | 4890 | 479397 | 40770.1 | 0.0070717 | 3.88081 | 16.6249 | 2.98541 | 0.0118375 | 1.30639e-05 | 5.46719e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2201.97 | 0.0138317 | 3463.34ms | 56369 | 4890 | 55759 | 24413.4 | 0.00161065 | 2.34021 | 11.553 | 2.15384 | 0.00389525 | 1.5266e-05 | 7.9813e-06 | 1(Win) | true |
| simdjson (ondemand) | 1480.26 | 0.130102 | 4644.96ms | 56369 | 80 | 178592 | 36316.3 | 0.0304708 | 3.48088 | 15.1214 | 2.65902 | 0.0111021 | 3.7698e-06 | 0 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2537.4 | 0.122907 | 3865.73ms | 83958 | 160 | 240668 | 31555.4 | 0.176796 | 2.02157 | 9.36803 | 1.71623 | 0.0029782 | 3.32011e-05 | 2.87346e-05 | 1(Win) | true |
| simdjson (ondemand) | 1910.43 | 0.0405646 | 4918.82ms | 83958 | 1280 | 369971 | 41911.3 | 0.00771778 | 2.68472 | 11.504 | 1.99609 | 0.00846822 | 8.19792e-06 | 3.0149e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2951.21 | 0.0578878 | 3734.91ms | 83958 | 1280 | 315725 | 27130.8 | 0.0367078 | 1.73703 | 8.30289 | 1.48379 | 0.00284099 | 4.45721e-06 | 1.0701e-06 | 1(Win) | true |
| simdjson (ondemand) | 2145.65 | 0.0683258 | 4759.99ms | 83958 | 640 | 416062 | 37316.8 | 0.0385653 | 2.39594 | 10.4968 | 1.7775 | 0.0077565 | 3.57322e-06 | 8.74693e-07 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1279.89 | 0.0402512 | 4727.28ms | 53331 | 2560 | 654954 | 39738.1 | 0.0739367 | 4.02379 | 13.8593 | 2.70975 | 0.0131712 | 6.29031e-05 | 1.7469e-05 | 1(Win) | true |
| simdjson (ondemand) | 1032.75 | 0.133845 | 5654.98ms | 53331 | 160 | 695183 | 49247.7 | 0.0060659 | 4.98852 | 17.7821 | 3.49489 | 0.0201871 | 0.000190555 | 0.000122583 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1581.22 | 0.0238119 | 4500.25ms | 53331 | 4890 | 286862 | 32165.3 | 0.0803667 | 3.2558 | 11.6843 | 2.21519 | 0.0100457 | 3.35559e-05 | 1.96749e-05 | 1(Win) | true |
| simdjson (ondemand) | 1230.54 | 0.0326603 | 5417.13ms | 53331 | 2560 | 466496 | 41331.8 | 0.140279 | 4.18431 | 15.6491 | 3.01052 | 0.0164603 | 1.35138e-05 | 4.42402e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.96 | 0.0564219 | 4862.82ms | 65103 | 640 | 348609 | 41364.8 | 0.0315839 | 3.43212 | 11.8587 | 2.28739 | 0.0103432 | 4.14487e-05 | 1.36082e-05 | 1(Win) | true |
| simdjson (ondemand) | 1253.83 | 0.0225225 | 5681.79ms | 65103 | 4890 | 608231 | 49518 | 0.13252 | 4.10132 | 14.7615 | 2.85616 | 0.0164571 | 4.25345e-05 | 2.08102e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.07 | 0.0224595 | 4664.51ms | 65103 | 4890 | 285153 | 34000.4 | 0.0338599 | 2.81391 | 10.0714 | 1.88073 | 0.00812704 | 1.7801e-05 | 9.51772e-06 | 1(Win) | true |
| simdjson (ondemand) | 1489.84 | 0.0478015 | 5464.95ms | 65103 | 1280 | 507945 | 41673.7 | 0.0346092 | 3.45539 | 13.0161 | 2.46108 | 0.0135015 | 2.95205e-05 | 1.48923e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 924.224 | 0.0176818 | 6235.74ms | 53331 | 4890 | 462983 | 55030.4 | 0.0228204 | 5.57312 | 19.7618 | 3.93655 | 0.0168654 | 5.46573e-05 | 2.1481e-05 | 1(Win) | true |
| simdjson (ondemand) | 477.266 | 0.122058 | 5829.58ms | 53331 | 320 | 5.414e+06 | 106566 | 0.0234717 | 10.6815 | 36.9715 | 7.4847 | 0.0728881 | 9.12345e-05 | 5.15648e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1081.5 | 0.0335019 | 6002.25ms | 53331 | 1280 | 317729 | 47027.8 | 0.165888 | 4.76403 | 17.5103 | 3.42537 | 0.0138014 | 1.6949e-05 | 4.64376e-06 | 1(Win) | true |
| simdjson (ondemand) | 522.969 | 0.174853 | 5693.29ms | 53331 | 160 | 4.62674e+06 | 97253.1 | 0.159774 | 9.81953 | 34.7677 | 6.98684 | 0.0674051 | 6.23465e-05 | 4.03143e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1073.7 | 0.0233954 | 6541.66ms | 65103 | 4890 | 894960 | 57825.1 | 0.0259867 | 4.79417 | 16.9372 | 3.38629 | 0.0137918 | 6.56157e-05 | 2.95646e-05 | 1(Win) | true |
| simdjson (ondemand) | 598.08 | 0.0809325 | 5701.31ms | 65103 | 640 | 4.51762e+06 | 103811 | 0.118038 | 8.57998 | 30.2261 | 6.07172 | 0.0555306 | 0.000105602 | 6.49692e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.03 | 0.0217912 | 6279.05ms | 65103 | 4890 | 578379 | 49908.1 | 0.102433 | 4.11803 | 15.0935 | 2.96844 | 0.0109838 | 2.48937e-05 | 1.47038e-05 | 1(Win) | true |
| simdjson (ondemand) | 653.37 | 0.0602655 | 5548.69ms | 65103 | 1280 | 4.19789e+06 | 95025.9 | 0.0210236 | 7.83247 | 28.4123 | 5.66214 | 0.0506673 | 2.38084e-05 | 1.09562e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8074.96 | 0.100344 | 1360.03ms | 53331 | 1280 | 51129.4 | 6298.53 | 0.181995 | 0.632951 | 3.02601 | 0.401286 | 0.000667778 | 4.07244e-06 | 1.30377e-06 | 1(Win) | true |
| simdjson (ondemand) | 6783.49 | 0.0276325 | 1471.37ms | 53331 | 320 | 1373.55 | 7497.67 | 0.149946 | 0.763616 | 3.40252 | 0.420318 | 0.000983715 | 2.22666e-06 | 0 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8770.53 | 0.0678761 | 1336.2ms | 53331 | 320 | 4957.83 | 5799.01 | 0.0572507 | 0.59032 | 2.86698 | 0.364797 | 0.000726887 | 6.91437e-06 | 2.81262e-06 | 1(Win) | true |
| simdjson (ondemand) | 7139.8 | 0.0444797 | 1456.17ms | 53331 | 160 | 1606.31 | 7123.51 | 0.0880987 | 0.725782 | 3.25407 | 0.385554 | 0.000953128 | 8.78945e-06 | 6.91437e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8516.47 | 0.0320947 | 1455ms | 65103 | 2560 | 14014.9 | 7290.23 | 0.030436 | 0.605921 | 2.85564 | 0.339938 | 0.000617555 | 3.28806e-06 | 4.98009e-07 | 1(Win) | true |
| simdjson (ondemand) | 7714.7 | 0.0389267 | 1526.59ms | 65103 | 2560 | 25124.6 | 8047.89 | 0.00345114 | 0.670274 | 3.05786 | 0.356604 | 0.000705229 | 2.92805e-06 | 3.54006e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9073.21 | 0.0437668 | 1426.34ms | 65103 | 1280 | 11481 | 6842.9 | 0.0134245 | 0.570777 | 2.72722 | 0.310401 | 0.000681456 | 2.23204e-06 | 1.20002e-08 | 1(Win) | true |
| simdjson (ondemand) | 8100.31 | 0.0301638 | 1508.45ms | 65103 | 4890 | 26138.4 | 7664.77 | 0.00582777 | 0.638674 | 2.93441 | 0.327773 | 0.000723365 | 3.00609e-06 | 1.97893e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5634.53 | 0.215028 | 1635.48ms | 53331 | 320 | 120555 | 9026.56 | 0.0355328 | 0.909259 | 4.34646 | 0.704637 | 0.00169314 | 3.1056e-06 | 1.17193e-07 | 1(Win) | true |
| simdjson (ondemand) | 4220.43 | 0.0505927 | 1928.22ms | 53331 | 640 | 23790.4 | 12051 | 0.0238124 | 1.22353 | 5.85993 | 0.956761 | 0.00236351 | 3.1642e-06 | 7.03156e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5948.34 | 0.0456605 | 1611.51ms | 53331 | 4890 | 74534.5 | 8550.35 | 0.0813529 | 0.864011 | 4.18563 | 0.667811 | 0.00167604 | 6.28478e-06 | 2.7877e-06 | 1(Win) | true |
| simdjson (ondemand) | 4309.74 | 0.0408664 | 1929.01ms | 53331 | 1280 | 29771.6 | 11801.3 | 0.30442 | 1.18879 | 5.70923 | 0.921566 | 0.00255064 | 3.51578e-06 | 5.85963e-08 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6205.23 | 0.0417322 | 1727.69ms | 65103 | 4890 | 85258.6 | 10005.6 | 0.11102 | 0.830728 | 3.94821 | 0.596701 | 0.0014368 | 1.7735e-05 | 1.16506e-05 | 1(Win) | true |
| simdjson (ondemand) | 4835.53 | 0.0527237 | 2006.33ms | 65103 | 2560 | 117318 | 12839.8 | 0.0054941 | 1.06217 | 5.06878 | 0.795847 | 0.00223829 | 1.42803e-05 | 8.53215e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6530.98 | 0.0698128 | 1706ms | 65103 | 320 | 14095 | 9506.55 | 0.0529617 | 0.79177 | 3.81609 | 0.566456 | 0.0014491 | 3.12006e-06 | 4.80009e-07 | 1(Win) | true |
| simdjson (ondemand) | 4981.56 | 0.0418791 | 1991.91ms | 65103 | 4890 | 133221 | 12463.4 | 0.033686 | 1.03062 | 4.94533 | 0.767016 | 0.00229886 | 1.39405e-05 | 8.55024e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1369.72 | 0.0343346 | 1550.77ms | 11812 | 4890 | 38990.4 | 8224.17 | 0.135339 | 3.71671 | 17.695 | 3.32306 | 0.0045523 | 4.66234e-05 | 2.43938e-05 | 1(Win) | true |
| simdjson (ondemand) | 1066.13 | 0.0448907 | 1786.99ms | 11812 | 2560 | 57594.5 | 10566.1 | 0.169846 | 4.80578 | 19.646 | 3.66767 | 0.00908977 | 4.41818e-05 | 1.91146e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1504.72 | 0.0880144 | 1528.92ms | 11812 | 2560 | 111143 | 7486.29 | 0.0253681 | 3.42109 | 16.6726 | 3.08762 | 0.00447906 | 2.50672e-05 | 4.56369e-06 | 1(Win) | true |
| simdjson (ondemand) | 1149.63 | 0.0569618 | 1762.27ms | 11812 | 1280 | 39875.4 | 9798.6 | 0.0248663 | 4.49611 | 18.6022 | 3.43117 | 0.00869819 | 2.13633e-05 | 4.62983e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.46 | 0.0992588 | 1656.46ms | 25388 | 40 | 3361.77 | 9236.02 | 0.0678944 | 1.97394 | 9.10672 | 1.60107 | 0.00283008 | 1.67402e-05 | 1.18166e-05 | 1(Win) | true |
| simdjson (ondemand) | 2176.5 | 0.198982 | 1844.84ms | 25388 | 80 | 39197.6 | 11124.2 | 0.0406604 | 2.37234 | 9.86019 | 1.7398 | 0.00388422 | 1.08319e-05 | 1.47708e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2818.6 | 0.0410305 | 1648.18ms | 25388 | 2560 | 31801.2 | 8590.04 | 0.163421 | 1.83003 | 8.62435 | 1.49035 | 0.00267103 | 2.01559e-05 | 7.93928e-06 | 1(Win) | true |
| simdjson (ondemand) | 2322.62 | 0.05692 | 1821.26ms | 25388 | 80 | 2816.56 | 10424.4 | 0.0803959 | 2.22752 | 9.37616 | 1.62998 | 0.00349378 | 1.2309e-05 | 5.9083e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 768.894 | 0.0543103 | 2195.68ms | 11812 | 1280 | 81038 | 14650.6 | 0.0191721 | 6.64097 | 29.5995 | 6.03065 | 0.014809 | 6.48176e-05 | 3.7237e-05 | 1(Win) | true |
| simdjson (ondemand) | 713.074 | 0.0596975 | 2322.97ms | 11812 | 640 | 56920.7 | 15797.5 | 0.0546765 | 7.20933 | 31.8917 | 6.2489 | 0.0145092 | 2.72498e-05 | 1.09793e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 812.55 | 0.126388 | 2161.94ms | 11812 | 640 | 196490 | 13863.5 | 0.10923 | 6.33802 | 28.5614 | 5.79275 | 0.0142866 | 2.22232e-05 | 3.83614e-06 | 1(Win) | true |
| simdjson (ondemand) | 728.324 | 0.0930133 | 2337.41ms | 11812 | 160 | 33113.8 | 15466.8 | 0.0116365 | 7.09179 | 30.846 | 6.01261 | 0.0147858 | 2.5927e-05 | 3.70386e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.55 | 0.0952206 | 2266.91ms | 25388 | 320 | 67827.2 | 15289.6 | 0.0408608 | 3.25656 | 14.6661 | 2.89316 | 0.00704676 | 7.26229e-06 | 9.84717e-07 | 1(Win) | true |
| simdjson (ondemand) | 1447.44 | 0.0595167 | 2409.69ms | 25388 | 2560 | 253732 | 16727.4 | 0.00690578 | 3.56178 | 15.387 | 2.90358 | 0.00728303 | 4.35583e-05 | 2.89722e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1661.31 | 0.0729774 | 2234.91ms | 25388 | 1280 | 144792 | 14574 | 0.0190497 | 3.09506 | 14.187 | 2.78328 | 0.00674005 | 1.43399e-05 | 4.00041e-06 | 1(Win) | true |
| simdjson (ondemand) | 1506.52 | 0.0215135 | 2387.81ms | 25388 | 4890 | 58457.6 | 16071.4 | 0.09151 | 3.42114 | 14.9105 | 2.79569 | 0.00726218 | 2.69357e-05 | 1.21307e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2434.56 | 0.0726771 | 1194.74ms | 11812 | 4890 | 55298.1 | 4627.04 | 0.118063 | 2.13078 | 10.5002 | 1.84482 | 0.00293715 | 4.10833e-05 | 2.26798e-05 | 1(Win) | true |
| simdjson (ondemand) | 2091.43 | 0.0319498 | 1258.65ms | 11812 | 2560 | 7581.14 | 5386.16 | 0.0588006 | 2.47819 | 11.3337 | 1.89384 | 0.00353735 | 1.66674e-05 | 4.53062e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2534.66 | 0.158403 | 1181.75ms | 11812 | 320 | 15859.3 | 4444.31 | 0.194799 | 2.04677 | 10.3176 | 1.79961 | 0.0022038 | 1.0847e-05 | 1.85193e-06 | 1(Win) | true |
| simdjson (ondemand) | 2129.62 | 0.0300909 | 1257.46ms | 11812 | 4890 | 12388.6 | 5289.57 | 0.0629873 | 2.43527 | 11.1472 | 1.84778 | 0.00368003 | 2.97088e-05 | 6.18068e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4280.27 | 0.119281 | 1285.2ms | 25388 | 320 | 14568.2 | 5656.63 | 0.00480654 | 1.21052 | 5.69474 | 0.909879 | 0.00155795 | 4.30814e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3983.9 | 0.0566757 | 1330.52ms | 25388 | 640 | 7593.01 | 6077.44 | 0.0524463 | 1.30078 | 5.98472 | 0.912715 | 0.00148582 | 7.20074e-06 | 1.35399e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4461.87 | 0.0453106 | 1275.18ms | 25388 | 1280 | 7738.05 | 5426.39 | 0.0113293 | 1.16256 | 5.61005 | 0.888845 | 0.00135143 | 5.07745e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 4072.64 | 0.0439417 | 1324.05ms | 25388 | 1280 | 8735.14 | 5945.01 | 0.00428387 | 1.27258 | 5.89794 | 0.891287 | 0.00145683 | 1.33552e-05 | 8.924e-07 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.67 | 0.0376902 | 1356.83ms | 11812 | 2560 | 14424 | 6297.88 | 0.0444357 | 2.89545 | 13.6771 | 2.58576 | 0.00727432 | 4.15031e-05 | 2.52325e-05 | 1(Win) | true |
| simdjson (ondemand) | 1656.94 | 0.0423694 | 1400.64ms | 11812 | 1280 | 10620.6 | 6798.55 | 0.151652 | 3.12443 | 13.95 | 2.42889 | 0.00753954 | 3.04246e-05 | 1.04502e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1833.24 | 0.0383026 | 1349.66ms | 11812 | 2560 | 14181 | 6144.76 | 0.107839 | 2.82315 | 13.4944 | 2.54055 | 0.00684073 | 2.49349e-05 | 1.16738e-05 | 1(Win) | true |
| simdjson (ondemand) | 1691.92 | 0.0305359 | 1397.21ms | 11812 | 2560 | 10581.5 | 6658 | 0.0197875 | 3.06015 | 13.7635 | 2.38283 | 0.0072514 | 1.61382e-05 | 1.25667e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3396.59 | 0.119098 | 1441.41ms | 25388 | 40 | 2882.98 | 7128.3 | 0.0294514 | 1.52513 | 7.18391 | 1.27044 | 0.00378427 | 5.9083e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3247.46 | 0.0447165 | 1474.09ms | 25388 | 1280 | 14227.1 | 7455.63 | 0.0265982 | 1.59342 | 7.20195 | 1.16165 | 0.00321138 | 8.3701e-06 | 3.16956e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3448.37 | 0.0454406 | 1436.09ms | 25388 | 4890 | 49776.8 | 7021.26 | 0.0549471 | 1.4915 | 7.09918 | 1.24941 | 0.00345087 | 8.94099e-06 | 1.00687e-06 | 1(Win) | true |
| simdjson (ondemand) | 3305.95 | 0.0256225 | 1465.52ms | 25388 | 4890 | 17219.4 | 7323.74 | 0.0926815 | 1.56587 | 7.11517 | 1.14022 | 0.00323248 | 1.19455e-05 | 4.60743e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1650.26 | 0.0336292 | 7005.87ms | 108313 | 2560 | 1.13431e+06 | 62593.5 | 0.00600191 | 3.10124 | 13.8783 | 2.79373 | 0.00362751 | 2.39648e-05 | 1.63516e-05 | 1(Win) | true |
| simdjson (ondemand) | 1502.14 | 0.0475467 | 7633.25ms | 108313 | 1280 | 1.36832e+06 | 68765.2 | 0.0520977 | 3.40221 | 15.2886 | 2.51076 | 0.00541413 | 1.47936e-05 | 9.3984e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1746 | 0.217533 | 6778ms | 108313 | 40 | 662496 | 59161.2 | 0.0899273 | 2.8944 | 13.1868 | 2.63173 | 0.00333178 | 1.54644e-05 | 1.24639e-05 | 1(Win) | true |
| simdjson (ondemand) | 1598.46 | 0.141095 | 7408.56ms | 108313 | 160 | 1.33015e+06 | 64621.8 | 0.0728323 | 3.20495 | 14.6005 | 2.34905 | 0.00542179 | 5.36639e-06 | 2.48123e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2495.88 | 0.054981 | 7768.34ms | 183677 | 640 | 952940 | 70182.7 | 0.0626592 | 2.04012 | 8.82198 | 1.69505 | 0.00211552 | 1.16968e-05 | 8.23456e-06 | 1(Win) | true |
| simdjson (ondemand) | 2397.48 | 0.051642 | 8021.48ms | 183677 | 4890 | 6.96171e+06 | 73063.5 | 0.0286974 | 2.12637 | 9.5929 | 1.50224 | 0.00353024 | 3.32784e-05 | 2.4416e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2655.91 | 0.0241313 | 7477.86ms | 183677 | 2560 | 648463 | 65954 | 0.0349655 | 1.93523 | 8.42284 | 1.60145 | 0.00189279 | 5.38479e-06 | 2.95823e-06 | 1(Win) | true |
| simdjson (ondemand) | 2568.12 | 0.083722 | 7786.04ms | 183677 | 640 | 2.08708e+06 | 68208.7 | 0.192449 | 1.98206 | 9.19238 | 1.40808 | 0.00330858 | 6.07384e-06 | 2.37339e-06 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 588.74 | 0.067263 | 9331.51ms | 108313 | 320 | 4.45673e+06 | 175452 | 0.192471 | 8.61954 | 38.4257 | 7.71378 | 0.011442 | 0.000104068 | 8.05824e-05 | 1(Win) | true |
| simdjson (ondemand) | 251.254 | 0.0610574 | 5325.17ms | 108313 | 320 | 2.01633e+07 | 411119 | 0.126094 | 20.3326 | 90.6895 | 18.5027 | 0.0837972 | 0.000146797 | 0.000107761 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 608.816 | 0.038705 | 9142.44ms | 108313 | 1280 | 5.51992e+06 | 169666 | 0.0873839 | 8.39852 | 37.7457 | 7.55556 | 0.0107603 | 1.30265e-05 | 6.20309e-06 | 1(Win) | true |
| simdjson (ondemand) | 256.787 | 0.111686 | 5253.28ms | 108313 | 80 | 1.61473e+07 | 402260 | 0.0744454 | 19.9526 | 90.0121 | 18.3458 | 0.0812558 | 2.76975e-05 | 1.95037e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.393 | 0.108527 | 5200.88ms | 183677 | 160 | 7.22852e+06 | 195851 | 0.246488 | 5.71994 | 23.9695 | 4.81131 | 0.00649921 | 9.83384e-06 | 5.37629e-06 | 1(Win) | true |
| simdjson (ondemand) | 433.437 | 0.0803951 | 5233.76ms | 183677 | 160 | 1.68903e+07 | 404137 | 0.216236 | 11.7663 | 53.3754 | 10.778 | 0.045039 | 8.81643e-05 | 6.4039e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 907.639 | 0.0738617 | 5122.91ms | 183677 | 320 | 6.50238e+06 | 192993 | 0.0566144 | 5.61934 | 23.5689 | 4.71816 | 0.0058125 | 6.58425e-06 | 1.97357e-06 | 1(Win) | true |
| simdjson (ondemand) | 441.64 | 0.0848428 | 5179.98ms | 183677 | 640 | 7.2474e+07 | 396630 | 0.0258281 | 11.5966 | 52.9764 | 10.6855 | 0.0445076 | 4.75274e-05 | 3.30063e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4987.91 | 0.0537365 | 2802.04ms | 108313 | 640 | 79257.8 | 20709.1 | 0.0176748 | 1.02902 | 5.56725 | 0.815969 | 0.00109714 | 1.42815e-06 | 1.15406e-07 | 1(Win) | true |
| simdjson (ondemand) | 4526.29 | 0.031395 | 3024.56ms | 108313 | 2560 | 131413 | 22821.2 | 0.0426457 | 1.13623 | 5.95205 | 0.776971 | 0.00123237 | 2.08813e-06 | 3.93103e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5207.59 | 0.0502158 | 2721.17ms | 108313 | 640 | 63496.5 | 19835.5 | 0.0606839 | 0.986773 | 5.40314 | 0.772456 | 0.000895971 | 4.94804e-06 | 3.46219e-06 | 1(Win) | true |
| simdjson (ondemand) | 4671.23 | 0.18781 | 2979.02ms | 108313 | 30 | 51743.9 | 22113.1 | 0.21012 | 1.10144 | 5.78844 | 0.733421 | 0.00104912 | 2.80053e-05 | 2.67743e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6676.04 | 0.0486661 | 3369.64ms | 183677 | 640 | 104353 | 26238.3 | 0.00873084 | 0.764546 | 3.90216 | 0.507685 | 0.000683256 | 1.26751e-06 | 2.04163e-07 | 1(Win) | true |
| simdjson (ondemand) | 6547.62 | 0.0383174 | 3414.67ms | 183677 | 2560 | 269013 | 26752.9 | 0.113457 | 0.778911 | 4.08815 | 0.479957 | 0.000822385 | 2.02461e-06 | 7.99637e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6985.11 | 0.0531364 | 3280.66ms | 183677 | 320 | 56819.6 | 25077.4 | 0.0152256 | 0.738027 | 3.80574 | 0.482091 | 0.000567777 | 3.21556e-06 | 2.50099e-06 | 1(Win) | true |
| simdjson (ondemand) | 6724.51 | 0.0260782 | 3354.04ms | 183677 | 2560 | 118137 | 26049.2 | 0.115384 | 0.758284 | 3.99167 | 0.454276 | 0.000774823 | 2.36489e-06 | 1.21434e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3374.63 | 0.0548179 | 3780.77ms | 108313 | 640 | 180191 | 30609.4 | 0.0233439 | 1.51604 | 8.05058 | 1.45544 | 0.0014318 | 4.90477e-06 | 2.25042e-06 | 1(Win) | true |
| simdjson (ondemand) | 2586.01 | 0.054962 | 4734.67ms | 108313 | 2560 | 1.23386e+06 | 39943.9 | 0.125657 | 1.98778 | 9.92381 | 1.63025 | 0.0037228 | 4.88313e-06 | 2.33698e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3515.1 | 0.0177113 | 3677.53ms | 108313 | 2560 | 69347 | 29386.2 | 0.0445496 | 1.46586 | 7.88731 | 1.41192 | 0.00123569 | 2.58222e-06 | 7.21289e-07 | 1(Win) | true |
| simdjson (ondemand) | 2658.64 | 0.0845885 | 4636ms | 108313 | 1280 | 1.38253e+06 | 38852.7 | 0.0344753 | 1.93637 | 9.76064 | 1.58674 | 0.00354958 | 2.18551e-06 | 1.15406e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4881.24 | 0.0541944 | 4319.4ms | 183677 | 4890 | 1.84955e+06 | 35886 | 0.0931482 | 1.0506 | 5.38262 | 0.894059 | 0.000864002 | 3.94687e-06 | 1.58654e-06 | 1(Win) | true |
| simdjson (ondemand) | 4045.82 | 0.0387379 | 5070.21ms | 183677 | 4890 | 1.37555e+06 | 43296 | 0.424853 | 1.26463 | 6.41805 | 0.98009 | 0.00215768 | 1.7747e-06 | 4.53138e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5017.97 | 0.0197849 | 4232.84ms | 183677 | 4890 | 233254 | 34908.1 | 0.247629 | 1.02342 | 5.28637 | 0.868405 | 0.000744874 | 1.49859e-06 | 3.39575e-07 | 1(Win) | true |
| simdjson (ondemand) | 4117.33 | 0.0545615 | 4991.98ms | 183677 | 2560 | 1.3794e+06 | 42544.1 | 0.0343964 | 1.24922 | 6.32183 | 0.954437 | 0.00210235 | 1.34407e-06 | 1.68009e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 636.549 | 0.0729692 | 8588.33ms | 1834197 | 160 | 6.4332e+08 | 2.74798e+06 | 0.0629956 | 8.03145 | 33.6916 | 7.1199 | 0.0376337 | 0.138988 | 2.57504e-05 | 1(Win) | true |
| simdjson (ondemand) | 604.955 | 0.227649 | 9019.12ms | 1834197 | 30 | 1.29987e+09 | 2.8915e+06 | 0.384614 | 8.38055 | 34.9304 | 6.32115 | 0.044178 | 0.1397 | 0.000563934 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.058 | 0.135328 | 8572.74ms | 1834197 | 40 | 4.62632e+08 | 2.51305e+06 | 0.00910995 | 7.3789 | 30.7033 | 6.42527 | 0.0366104 | 0.11816 | 1.45977e-05 | 1(Win) | true |
| simdjson (ondemand) | 650.494 | 0.0798838 | 9079.45ms | 1834197 | 160 | 7.38317e+08 | 2.68907e+06 | 0.0578412 | 7.79621 | 31.9435 | 5.62697 | 0.0432128 | 0.118933 | 0.00540898 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2228.13 | 0.079272 | 9786.58ms | 7351818 | 160 | 9.95559e+08 | 3.14669e+06 | 0.60712 | 2.2628 | 9.3265 | 1.82015 | 0.0107838 | 0.0588036 | 0.00457712 | 1(Win) | true |
| simdjson (ondemand) | 2139.38 | 0.170741 | 10190.7ms | 7351818 | 80 | 2.50485e+09 | 3.27723e+06 | 0.193511 | 2.35415 | 9.73245 | 1.61549 | 0.0108547 | 0.0590222 | 0.00822112 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2405.2 | 0.101329 | 9820.72ms | 7351818 | 80 | 6.97978e+08 | 2.91503e+06 | 0.0658604 | 2.09691 | 8.5812 | 1.64695 | 0.0105228 | 0.0535552 | 0.00480047 | 1(Win) | true |
| simdjson (ondemand) | 2333.29 | 0.118432 | 10130.5ms | 7351818 | 80 | 1.01317e+09 | 3.00487e+06 | 0.044044 | 2.17364 | 8.98724 | 1.44229 | 0.010595 | 0.0537326 | 0.00534579 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 407.031 | 0.111021 | 6533.94ms | 1834197 | 40 | 9.10555e+08 | 4.29752e+06 | 0.385998 | 12.5852 | 60.0116 | 13.3054 | 0.0386351 | 0.344376 | 0.00790905 | 1(Win) | true |
| simdjson (ondemand) | 271.168 | 0.180317 | 9720.94ms | 1834197 | 30 | 4.05894e+09 | 6.45072e+06 | 1.25183 | 18.7271 | 101.938 | 21.1703 | 0.0480201 | 0.790254 | 0.00566698 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 422.324 | 0.111781 | 6562.43ms | 1834197 | 40 | 8.57427e+08 | 4.14191e+06 | 0.137507 | 11.9129 | 57.0247 | 12.6111 | 0.0375349 | 0.323185 | 0.00171559 | 1(Win) | true |
| simdjson (ondemand) | 280.702 | 0.132936 | 9707.68ms | 1834197 | 40 | 2.74502e+09 | 6.23162e+06 | 0.081912 | 18.1281 | 98.953 | 20.4767 | 0.0467955 | 0.768582 | 0.0125624 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.32 | 0.152914 | 7775.7ms | 7351818 | 80 | 4.9402e+09 | 5.13902e+06 | 0.0250827 | 3.72075 | 15.8823 | 3.37013 | 0.011082 | 0.186145 | 0.00173529 | 1(Win) | true |
| simdjson (ondemand) | 909.773 | 0.197298 | 5462.15ms | 7351818 | 40 | 9.24759e+09 | 7.70659e+06 | 0.870469 | 5.5862 | 26.4499 | 5.32016 | 0.0122538 | 0.435561 | 0.00517814 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.84 | 0.254809 | 7847.38ms | 7351818 | 30 | 4.76307e+09 | 4.94502e+06 | 0.171222 | 3.55862 | 15.1379 | 3.19719 | 0.010811 | 0.180873 | 0.00144474 | 1(Win) | true |
| simdjson (ondemand) | 937.235 | 0.169979 | 5418.66ms | 7351818 | 30 | 4.85068e+09 | 7.48077e+06 | 0.0215083 | 5.41079 | 25.7051 | 5.14712 | 0.0119587 | 0.430193 | 0.00416217 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5052.31 | 0.022942 | 9065.96ms | 1834197 | 1280 | 8.07576e+06 | 346223 | 0.0502428 | 1.01517 | 5.6989 | 0.827984 | 0.000456594 | 0.0755813 | 2.46659e-06 | 1(Win) | true |
| simdjson (ondemand) | 4279.38 | 0.0811345 | 5307.64ms | 1834197 | 640 | 7.03917e+07 | 408757 | 0.0277412 | 1.19595 | 6.52919 | 0.874483 | 0.00489369 | 0.0754919 | 3.04629e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5036.37 | 0.0565752 | 9065.22ms | 1834197 | 320 | 1.23555e+07 | 347319 | 0.0279303 | 1.01602 | 5.69871 | 0.827937 | 0.000438671 | 0.0755488 | 1.82812e-06 | 1(Win) | true |
| simdjson (ondemand) | 4247.12 | 0.0551238 | 5321.88ms | 1834197 | 320 | 1.64941e+07 | 411861 | 0.0636754 | 1.19755 | 6.52899 | 0.874436 | 0.00498321 | 0.0754747 | 1.49077e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10284.1 | 0.0637894 | 8792.98ms | 7351818 | 640 | 1.21041e+08 | 681754 | 0.275122 | 0.49254 | 2.27778 | 0.23517 | 0.00133299 | 0.0423555 | 1.85579e-05 | 1(Win) | true |
| simdjson (ondemand) | 9532.35 | 0.166886 | 9536.04ms | 7351818 | 40 | 6.02681e+07 | 735521 | 0.128468 | 0.536101 | 2.64676 | 0.256657 | 0.000963969 | 0.0424192 | 0.000251921 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10318.9 | 0.094668 | 8797.75ms | 7351818 | 320 | 1.32397e+08 | 679455 | 0.281749 | 0.49286 | 2.27773 | 0.235159 | 0.00131787 | 0.0423491 | 2.24902e-05 | 1(Win) | true |
| simdjson (ondemand) | 9572.78 | 0.151571 | 9607.24ms | 7351818 | 40 | 4.92954e+07 | 732414 | 0.133069 | 0.536454 | 2.64671 | 0.256645 | 0.000934436 | 0.0424118 | 0.000266091 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3137.56 | 0.372147 | 7123.08ms | 1834197 | 320 | 1.37749e+09 | 557512 | 0.558721 | 1.63376 | 8.50401 | 1.52924 | 0.000619345 | 0.113247 | 1.00095e-05 | 1(Win) | true |
| simdjson (ondemand) | 2286.09 | 0.535888 | 9798.91ms | 1834197 | 80 | 1.34506e+09 | 765160 | 0.049382 | 2.24543 | 12.8396 | 2.27677 | 0.00500727 | 0.150814 | 3.9595e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3195.22 | 0.299031 | 7131.84ms | 1834197 | 640 | 1.71515e+09 | 547451 | 0.609198 | 1.61116 | 8.50381 | 1.52919 | 0.000584575 | 0.113194 | 6.28511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2242.71 | 0.256499 | 9866.9ms | 1834197 | 320 | 1.28075e+09 | 779961 | 0.0328233 | 2.27651 | 12.8394 | 2.27672 | 0.00481044 | 0.150773 | 4.67337e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7892.27 | 0.127824 | 5661.24ms | 7351818 | 160 | 2.06313e+08 | 888368 | 0.112952 | 0.645749 | 2.97762 | 0.41013 | 0.00129582 | 0.063573 | 5.51819e-06 | 1(Win) | true |
| simdjson (ondemand) | 6028.54 | 0.148673 | 7369.8ms | 7351818 | 160 | 4.78353e+08 | 1.16301e+06 | 0.0594895 | 0.851573 | 4.22114 | 0.606513 | 0.00100006 | 0.0848024 | 0.000253685 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7872.39 | 0.191997 | 5661.82ms | 7351818 | 80 | 2.33912e+08 | 890611 | 0.0432938 | 0.646791 | 2.97757 | 0.410118 | 0.00136001 | 0.0635568 | 5.61426e-06 | 1(Win) | true |
| simdjson (ondemand) | 5990.43 | 0.298709 | 7423.32ms | 7351818 | 160 | 1.95565e+09 | 1.17041e+06 | 1.47103 | 0.849939 | 4.22109 | 0.606501 | 0.000976823 | 0.0847759 | 0.000386586 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1351.6 | 0.149434 | 7554.84ms | 409725 | 160 | 2.9861e+07 | 289097 | 0.0332698 | 3.75086 | 18.0091 | 3.50411 | 0.00891154 | 0.0195382 | 8.36537e-05 | 1(Win) | true |
| simdjson (ondemand) | 981.11 | 0.121819 | 5166.88ms | 409725 | 80 | 1.88309e+07 | 398268 | 0.163623 | 5.17438 | 19.945 | 3.78726 | 0.0166993 | 0.0430577 | 4.44505e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1716.11 | 0.184292 | 7066.02ms | 409725 | 80 | 1.40863e+07 | 227691 | 0.0143856 | 2.94313 | 15.1515 | 2.85795 | 0.00613591 | 0.0108359 | 2.37964e-06 | 1(Win) | true |
| simdjson (ondemand) | 1171.42 | 0.113114 | 9877.59ms | 409725 | 160 | 2.27778e+07 | 333565 | 0.0761808 | 4.35575 | 17.0956 | 3.14278 | 0.0126493 | 0.0215549 | 1.33169e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1997.15 | 0.101301 | 8430.33ms | 676745 | 640 | 6.85859e+07 | 323157 | 0.0515345 | 2.52363 | 11.4884 | 2.13914 | 0.00601399 | 0.0295791 | 5.09331e-05 | 1(Win) | true |
| simdjson (ondemand) | 1546.71 | 0.0913505 | 5400ms | 676745 | 80 | 1.16236e+07 | 417268 | 0.12863 | 3.27214 | 12.6557 | 2.31827 | 0.0107286 | 0.0383922 | 0.000106078 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2476.35 | 0.148448 | 7972.54ms | 676745 | 1280 | 1.91596e+08 | 260624 | 0.185058 | 2.02714 | 9.75766 | 1.74775 | 0.00411636 | 0.0122346 | 4.26478e-05 | 1(Win) | true |
| simdjson (ondemand) | 1820.44 | 0.101016 | 5175.61ms | 676745 | 160 | 2.05209e+07 | 354526 | 0.0599557 | 2.79224 | 10.9298 | 1.92793 | 0.00840812 | 0.0193323 | 1.30958e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 806.423 | 0.160856 | 6258.68ms | 409725 | 320 | 1.94393e+08 | 484540 | 0.253952 | 6.30547 | 28.7764 | 5.82013 | 0.0129993 | 0.0216277 | 7.67359e-05 | 1(Win) | true |
| simdjson (ondemand) | 482.109 | 0.0537861 | 5149.02ms | 409725 | 320 | 6.08113e+07 | 810490 | 0.0646136 | 10.5403 | 46.7606 | 9.42332 | 0.0318291 | 0.0494045 | 8.70325e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 913.985 | 0.153157 | 6070.95ms | 409725 | 40 | 1.71492e+07 | 427517 | 0.0175849 | 5.51161 | 25.9247 | 5.17328 | 0.0101676 | 0.00793172 | 1.36067e-05 | 1(Win) | true |
| simdjson (ondemand) | 522.123 | 0.178718 | 5034.39ms | 409725 | 40 | 7.15538e+07 | 748375 | 0.181918 | 9.74106 | 43.9154 | 8.77799 | 0.0282064 | 0.0210776 | 2.51388e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1246.35 | 0.0788031 | 6697.3ms | 676745 | 320 | 5.32849e+07 | 517826 | 0.0436961 | 4.07932 | 18.3039 | 3.67616 | 0.00759227 | 0.0292289 | 5.60034e-05 | 1(Win) | true |
| simdjson (ondemand) | 794.357 | 0.148345 | 5167.16ms | 676745 | 40 | 5.81067e+07 | 812474 | 0.330901 | 6.41436 | 28.7122 | 5.69204 | 0.0190927 | 0.0459968 | 0.000116329 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1397.99 | 0.0872016 | 6542.89ms | 676745 | 640 | 1.03722e+08 | 461659 | 0.0239049 | 3.60205 | 16.5733 | 3.28339 | 0.00570284 | 0.0134517 | 1.71339e-05 | 1(Win) | true |
| simdjson (ondemand) | 861.211 | 0.0556091 | 5070.92ms | 676745 | 320 | 5.5574e+07 | 749403 | 0.0331333 | 5.9093 | 26.9902 | 5.30155 | 0.0167038 | 0.0205139 | 3.37415e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2441.69 | 0.0292494 | 8550.05ms | 409725 | 1280 | 2.80444e+06 | 160030 | 0.0577266 | 2.08323 | 10.1568 | 1.7835 | 0.00548231 | 2.67233e-05 | 1.18525e-05 | 1(Win) | true |
| simdjson (ondemand) | 1916.16 | 0.0504709 | 5318.25ms | 409725 | 80 | 847410 | 203920 | 0.0504618 | 2.63737 | 10.8143 | 1.83904 | 0.0082372 | 0.000109159 | 4.14912e-06 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2825.81 | 0.0438085 | 8436.53ms | 409725 | 640 | 2.34854e+06 | 138277 | 0.17344 | 1.80745 | 9.16442 | 1.55542 | 0.00396833 | 3.25218e-05 | 2.12719e-05 | 1(Win) | true |
| simdjson (ondemand) | 2156.37 | 0.0307111 | 5305.4ms | 409725 | 1280 | 3.96406e+06 | 181205 | 0.0775174 | 2.36397 | 9.8274 | 1.60997 | 0.00704765 | 4.5751e-05 | 1.40433e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3416.38 | 0.223981 | 5003.9ms | 676745 | 160 | 2.86458e+07 | 188912 | 0.0106443 | 1.4721 | 6.779 | 1.11354 | 0.00378678 | 0.000440519 | 7.15742e-06 | 1(Win) | true |
| simdjson (ondemand) | 3004.55 | 0.111111 | 5692.9ms | 676745 | 80 | 4.55718e+06 | 214806 | 0.00218215 | 1.69621 | 7.01317 | 1.11441 | 0.00565963 | 0.00509906 | 7.53607e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3907.91 | 0.0559933 | 9799.67ms | 676745 | 1280 | 1.09457e+07 | 165151 | 0.0105092 | 1.29516 | 6.17938 | 0.975809 | 0.0027357 | 0.000101796 | 9.52399e-06 | 1(Win) | true |
| simdjson (ondemand) | 3383.16 | 0.033375 | 5584.04ms | 676745 | 640 | 2.59434e+06 | 190767 | 0.269246 | 1.51628 | 6.41586 | 0.975805 | 0.00470732 | 0.00417904 | 8.31185e-07 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1907.14 | 0.0666246 | 5463.19ms | 409725 | 30 | 559001 | 204885 | 0.105411 | 2.69971 | 13.0839 | 2.45458 | 0.00833876 | 0.000170684 | 7.64741e-06 | 1(Win) | true |
| simdjson (ondemand) | 1413.77 | 0.0363812 | 7237.5ms | 409725 | 640 | 6.47081e+06 | 276384 | 0.0185538 | 3.62126 | 14.7733 | 2.68278 | 0.0144641 | 0.000169039 | 2.13291e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2084.54 | 0.037076 | 5400.68ms | 409725 | 640 | 3.09122e+06 | 187448 | 0.0346866 | 2.43618 | 12.0668 | 2.22118 | 0.00717947 | 9.3546e-06 | 1.45296e-06 | 1(Win) | true |
| simdjson (ondemand) | 1544.59 | 0.0340802 | 7112.05ms | 409725 | 640 | 4.75713e+06 | 252976 | 0.020251 | 3.31789 | 13.7634 | 2.44918 | 0.0125384 | 7.88639e-06 | 1.73134e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2643.42 | 0.0701783 | 6402.46ms | 676745 | 320 | 9.3945e+06 | 244151 | 0.0721154 | 1.91837 | 8.60411 | 1.5369 | 0.00578853 | 0.000530296 | 4.41913e-06 | 1(Win) | true |
| simdjson (ondemand) | 2229.13 | 0.0579485 | 7583.5ms | 676745 | 320 | 9.00773e+06 | 289528 | 0.0239492 | 2.2907 | 9.46257 | 1.6358 | 0.00910186 | 0.00190225 | 2.87728e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2928.86 | 0.0477732 | 6295.78ms | 676745 | 1280 | 1.41851e+07 | 220357 | 0.0076501 | 1.74564 | 7.98831 | 1.39546 | 0.00481469 | 0.000466011 | 7.95513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2401.52 | 0.047742 | 7505.86ms | 676745 | 640 | 1.05356e+07 | 268745 | 0.0773206 | 2.11077 | 8.8494 | 1.49368 | 0.00791351 | 0.00100138 | 5.02636e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1960.28 | 0.0573091 | 6971.87ms | 264040 | 1280 | 6.93683e+06 | 128455 | 0.063963 | 2.5878 | 10.299 | 1.89341 | 0.00401642 | 0.000296093 | 2.997e-05 | 1(Win) | true |
| simdjson (ondemand) | 1705.9 | 0.0999631 | 7896.95ms | 264040 | 320 | 6.96724e+06 | 147610 | 0.177499 | 2.9671 | 10.7143 | 1.8331 | 0.00931264 | 6.93905e-05 | 1.85815e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2237.05 | 0.0499297 | 6865.98ms | 264040 | 2560 | 8.08621e+06 | 112562 | 0.0484798 | 2.25894 | 8.92915 | 1.58034 | 0.00631677 | 2.61916e-05 | 1.58978e-05 | 1(Win) | true |
| simdjson (ondemand) | 1907.86 | 0.0907191 | 7909.91ms | 264040 | 640 | 9.17542e+06 | 131985 | 0.0711869 | 2.65213 | 9.34734 | 1.52201 | 0.0119414 | 8.21549e-05 | 6.21591e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2465.36 | 0.0879039 | 7502.72ms | 360584 | 2560 | 3.84864e+07 | 139484 | 0.358662 | 2.05152 | 7.99539 | 1.39907 | 0.00422531 | 0.000475901 | 1.52195e-05 | 1(Win) | true |
| simdjson (ondemand) | 2164.37 | 0.0818469 | 8513.15ms | 360584 | 640 | 1.08227e+07 | 158882 | 0.224782 | 2.34251 | 8.23825 | 1.36027 | 0.00868448 | 0.00255113 | 9.27315e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2961.45 | 0.0494147 | 7055.38ms | 360584 | 1280 | 4.21431e+06 | 116119 | 0.119743 | 1.71667 | 6.98846 | 1.16951 | 0.00339208 | 3.93286e-05 | 3.02591e-05 | 1(Win) | true |
| simdjson (ondemand) | 2484.45 | 0.0826889 | 8240.03ms | 360584 | 640 | 8.38351e+06 | 138413 | 0.118809 | 2.04487 | 7.23574 | 1.13215 | 0.00926534 | 7.20316e-05 | 4.77091e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 651.831 | 0.0412844 | 10028.9ms | 264040 | 1280 | 3.25574e+07 | 386309 | 0.0506957 | 7.8083 | 28.6322 | 5.43283 | 0.0265254 | 0.00079668 | 8.87857e-05 | 1(Win) | true |
| simdjson (ondemand) | 306.979 | 0.149127 | 5209.68ms | 264040 | 80 | 1.19708e+08 | 820278 | 0.0308626 | 16.48 | 64.3395 | 13.0848 | 0.0935266 | 0.00101978 | 0.000201106 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 703.87 | 0.043824 | 9725.54ms | 264040 | 1280 | 3.14621e+07 | 357748 | 0.302335 | 7.26615 | 27.2618 | 5.12025 | 0.0224937 | 5.45816e-05 | 2.9464e-05 | 1(Win) | true |
| simdjson (ondemand) | 319.519 | 0.134254 | 5098.47ms | 264040 | 160 | 1.7911e+08 | 788086 | 0.272323 | 15.8694 | 62.9719 | 12.774 | 0.0889232 | 4.90929e-05 | 2.87362e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.882 | 0.130332 | 5229ms | 360584 | 640 | 1.76732e+08 | 403198 | 0.0691928 | 5.98354 | 22.046 | 4.19885 | 0.0173682 | 0.00373803 | 4.50398e-05 | 1(Win) | true |
| simdjson (ondemand) | 436.303 | 0.161648 | 5009.08ms | 360584 | 80 | 1.29857e+08 | 788168 | 0.014706 | 11.5344 | 46.8979 | 9.4643 | 0.0564554 | 0.00468584 | 4.51698e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 905.55 | 0.114363 | 5136.86ms | 360584 | 320 | 6.03545e+07 | 379747 | 0.0963559 | 5.63374 | 21.0413 | 3.9695 | 0.0159898 | 0.000120178 | 9.93181e-06 | 1(Win) | true |
| simdjson (ondemand) | 455.863 | 0.0720402 | 9922.63ms | 360584 | 640 | 1.89005e+08 | 754349 | 0.130929 | 11.1012 | 45.8953 | 9.2365 | 0.0529672 | 0.000286241 | 1.8074e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6945.36 | 0.109636 | 4407.53ms | 264040 | 80 | 126399 | 36255.6 | 0.10119 | 0.741847 | 3.61395 | 0.467861 | 0.00136409 | 3.35176e-05 | 2.79787e-05 | 1(Win) | true |
| simdjson (ondemand) | 6201.05 | 0.0321218 | 4783.18ms | 264040 | 4890 | 831992 | 40607.3 | 0.299706 | 0.814996 | 4.00273 | 0.440913 | 0.00109387 | 1.30224e-05 | 9.43651e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7052.72 | 0.0309631 | 4370.49ms | 264040 | 2560 | 312864 | 35703.7 | 0.0197224 | 0.720749 | 3.53611 | 0.450125 | 0.00134734 | 6.97397e-06 | 5.28004e-06 | 1(Win) | true |
| simdjson (ondemand) | 6376.84 | 0.0469387 | 4743.07ms | 264040 | 80 | 27484 | 39487.9 | 0.0242104 | 0.793904 | 3.92424 | 0.423063 | 0.00109472 | 4.73413e-06 | 3.07719e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7843.93 | 0.143209 | 5133.29ms | 360584 | 80 | 315337 | 43840.2 | 0.00761229 | 0.649281 | 3.1148 | 0.360948 | 0.00117708 | 4.67991e-06 | 4.09059e-06 | 1(Win) | true |
| simdjson (ondemand) | 7450.15 | 0.0176866 | 5347.73ms | 360584 | 4890 | 325896 | 46157.4 | 0.0290042 | 0.680784 | 3.32074 | 0.339695 | 0.000868668 | 7.54513e-06 | 4.69246e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8033.02 | 0.0400586 | 5097.73ms | 360584 | 2560 | 752813 | 42808.3 | 8.66873e-05 | 0.635065 | 3.0578 | 0.347961 | 0.00121805 | 9.3804e-06 | 6.93536e-06 | 1(Win) | true |
| simdjson (ondemand) | 7603.26 | 0.0392989 | 5306.73ms | 360584 | 2560 | 808749 | 45227.9 | 0.0534558 | 0.666607 | 3.26327 | 0.326624 | 0.000880166 | 4.83591e-06 | 3.16219e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4674.4 | 0.0794259 | 6067.71ms | 264040 | 40 | 73227.2 | 53869.6 | 0.268946 | 1.0819 | 5.3236 | 0.873811 | 0.00215763 | 3.40857e-06 | 2.1777e-06 | 1(Win) | true |
| simdjson (ondemand) | 3919.08 | 0.0454278 | 7165.75ms | 264040 | 1280 | 1.0905e+06 | 64251.8 | 0.0493966 | 1.29068 | 6.34431 | 0.953653 | 0.0024783 | 3.18962e-06 | 1.88773e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4829.93 | 0.197987 | 6035.95ms | 264040 | 40 | 426180 | 52135 | 0.0677547 | 1.05994 | 5.24586 | 0.856045 | 0.00214664 | 2.08302e-06 | 1.42024e-06 | 1(Win) | true |
| simdjson (ondemand) | 3998.47 | 0.0625059 | 7097.44ms | 264040 | 320 | 495841 | 62976.1 | 0.00178642 | 1.26918 | 6.26582 | 0.935804 | 0.00245659 | 1.01784e-06 | 5.91766e-08 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5630.08 | 0.0264488 | 6816.96ms | 360584 | 4890 | 1.27616e+06 | 61079 | 0.00523351 | 0.898254 | 4.37789 | 0.66597 | 0.00149251 | 3.15042e-06 | 1.73486e-06 | 1(Win) | true |
| simdjson (ondemand) | 4897.27 | 0.09366 | 7790.67ms | 360584 | 160 | 692042 | 70218.6 | 0.00283927 | 1.03617 | 5.04605 | 0.717465 | 0.00215742 | 2.53062e-06 | 1.03998e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5723.56 | 0.109783 | 6793.39ms | 360584 | 30 | 130519 | 60081.4 | 0.299967 | 0.883348 | 4.321 | 0.65298 | 0.00149091 | 1.68246e-05 | 1.53455e-05 | 1(Win) | true |
| simdjson (ondemand) | 4981.59 | 0.0281928 | 7703.94ms | 360584 | 2560 | 969600 | 69030.1 | 0.153609 | 1.01742 | 4.98858 | 0.704395 | 0.00212868 | 5.73289e-06 | 3.88151e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1912.41 | 0.0506887 | 860.416ms | 2632 | 1280 | 566.558 | 1312.52 | 0.0666807 | 2.76757 | 11.0638 | 2.01064 | 0.000772345 | 2.96828e-05 | 5.63972e-06 | 1(Win) | true |
| simdjson (ondemand) | 1520.05 | 0.044497 | 887.289ms | 2632 | 4890 | 2640.15 | 1651.31 | 0.154323 | 3.44457 | 11.6337 | 2.13944 | 0.00319001 | 6.78296e-05 | 1.94243e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2392.55 | 0.0885295 | 837.715ms | 2632 | 2560 | 2208.34 | 1049.12 | 0.143701 | 2.22 | 9.09157 | 1.54977 | 0.000766409 | 5.23901e-05 | 1.36541e-05 | 1(Win) | true |
| simdjson (ondemand) | 1810.81 | 0.0843764 | 871.56ms | 2632 | 2560 | 3501.93 | 1386.16 | 0.175901 | 2.91427 | 9.89172 | 1.731 | 0.00180634 | 9.39459e-05 | 4.49694e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2363.52 | 0.0553031 | 889.607ms | 3370 | 4890 | 2765.34 | 1359.78 | 0.192166 | 2.22428 | 8.95519 | 1.56499 | 0.000695114 | 4.53903e-05 | 6.97845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1946.49 | 0.0815768 | 888.97ms | 3370 | 2560 | 4644.4 | 1651.12 | 0.017575 | 2.68669 | 9.39881 | 1.68457 | 0.00261429 | 4.47422e-05 | 1.13594e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2933.61 | 0.178276 | 875.075ms | 3370 | 80 | 305.163 | 1095.54 | 0.103723 | 1.78712 | 7.4911 | 1.22047 | 0.00060089 | 1.8546e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2284.13 | 0.0400686 | 871.44ms | 3370 | 4890 | 1554.31 | 1407.05 | 0.261776 | 2.29681 | 8.03805 | 1.36559 | 0.00241212 | 4.15066e-05 | 7.28186e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1254.79 | 0.0798916 | 922.542ms | 2632 | 2560 | 6538.41 | 2000.39 | 0.185692 | 4.16689 | 16.5084 | 3.24544 | 0.00351459 | 5.01638e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 712.097 | 0.0477271 | 1076.17ms | 2632 | 2560 | 7245.41 | 3524.9 | 0.0587019 | 7.28894 | 29.4202 | 5.95783 | 0.0111261 | 4.15559e-05 | 3.85876e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1416.65 | 0.082987 | 908.492ms | 2632 | 2560 | 5534.88 | 1771.84 | 0.0232202 | 3.68767 | 14.6155 | 2.80395 | 0.00467919 | 5.14996e-05 | 8.90483e-06 | 1(Win) | true |
| simdjson (ondemand) | 782.016 | 0.0380843 | 1057.57ms | 2632 | 160 | 239.085 | 3209.74 | 0.0399335 | 6.67405 | 27.6767 | 5.54825 | 0.00948423 | 2.13716e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1528.39 | 0.0373341 | 932.872ms | 3370 | 4890 | 3013.79 | 2102.79 | 0.0726492 | 3.40291 | 13.489 | 2.62849 | 0.00282852 | 4.23562e-05 | 7.94937e-06 | 1(Win) | true |
| simdjson (ondemand) | 915.207 | 0.0551949 | 1075.75ms | 3370 | 2560 | 9617.42 | 3511.65 | 0.153726 | 5.64398 | 23.0407 | 4.61187 | 0.00847482 | 3.18759e-05 | 3.7092e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1711.38 | 0.0679444 | 923.143ms | 3370 | 1280 | 2083.94 | 1877.95 | 0.0056997 | 3.02658 | 12.0148 | 2.28368 | 0.00365032 | 2.7819e-05 | 3.47737e-06 | 1(Win) | true |
| simdjson (ondemand) | 989.989 | 0.0378537 | 1058.8ms | 3370 | 160 | 241.621 | 3246.38 | 0.0075078 | 5.27078 | 21.6792 | 4.29199 | 0.0084681 | 4.26558e-05 | 3.7092e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3221.72 | 0.139822 | 799.434ms | 2632 | 1280 | 1519 | 779.108 | 0.0467063 | 1.66249 | 7.05775 | 1.16641 | 0.000387657 | 1.51382e-05 | 1.48414e-06 | 1(Win) | true |
| simdjson (ondemand) | 2326.23 | 0.0797993 | 824.11ms | 2632 | 2560 | 1898.03 | 1079.03 | 0.091217 | 2.29356 | 8.1079 | 1.38754 | 0.00102079 | 3.04248e-05 | 4.00717e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3957.37 | 0.0700264 | 781.494ms | 2632 | 4890 | 964.697 | 634.278 | 0.0414633 | 1.38199 | 6.03382 | 0.921733 | 0.00100509 | 1.58502e-05 | 1.16546e-06 | 1(Win) | true |
| simdjson (ondemand) | 2717.57 | 0.0555704 | 811.199ms | 2632 | 2560 | 674.429 | 923.645 | 0.00477919 | 1.97867 | 7.08169 | 1.14134 | 0.000761363 | 3.23542e-05 | 1.14279e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3811.09 | 0.107262 | 800.145ms | 3370 | 2560 | 2094.57 | 843.298 | 0.298175 | 1.41438 | 5.94392 | 0.933828 | 0.000298938 | 3.22237e-05 | 1.39095e-05 | 1(Win) | true |
| simdjson (ondemand) | 3044.41 | 0.114119 | 822.121ms | 3370 | 30 | 43.5402 | 1055.67 | 0.0284261 | 1.76403 | 6.46261 | 1.05846 | 0.000296736 | 2.96736e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4575.1 | 0.0887824 | 788.991ms | 3370 | 640 | 248.938 | 702.472 | 0.298051 | 1.19091 | 5.14421 | 0.74273 | 0.000828542 | 2.73553e-05 | 8.80935e-06 | 1(Win) | true |
| simdjson (ondemand) | 3507.79 | 0.0845183 | 809.458ms | 3370 | 2560 | 1535.09 | 916.213 | 0.0438904 | 1.53082 | 5.66113 | 0.866172 | 0.000885687 | 2.79349e-05 | 3.7092e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2372.26 | 0.0600987 | 822.034ms | 2632 | 4890 | 1977.37 | 1058.09 | 0.0170388 | 2.24578 | 9.32371 | 1.7424 | 0.000953267 | 3.28659e-05 | 8.93518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2107.51 | 0.0898719 | 835.048ms | 2632 | 80 | 91.6581 | 1191.01 | 0.00104954 | 2.52525 | 9.87006 | 1.76026 | 0.00134403 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2759.66 | 0.0658361 | 808.786ms | 2632 | 4890 | 1753.47 | 909.557 | 0.0310362 | 1.94718 | 8.30595 | 1.49584 | 0.00114596 | 1.68603e-05 | 2.17552e-06 | 1(Win) | true |
| simdjson (ondemand) | 2384.41 | 0.106185 | 821.91ms | 2632 | 80 | 99.9595 | 1052.7 | 0.0593359 | 2.24413 | 8.84384 | 1.51406 | 0.00166223 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2900.42 | 0.152584 | 825.978ms | 3370 | 640 | 1829.53 | 1108.08 | 0.0394673 | 1.83665 | 7.74807 | 1.39229 | 0.00059579 | 1.02003e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2698.46 | 0.0311727 | 832.024ms | 3370 | 640 | 88.2175 | 1191 | 0.128602 | 1.97355 | 7.83887 | 1.34955 | 0.00105527 | 1.57641e-05 | 1.8546e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3337.4 | 0.0685236 | 813.527ms | 3370 | 640 | 278.679 | 962.991 | 0.0529231 | 1.60747 | 6.95312 | 1.1997 | 0.000890671 | 9.273e-06 | 4.17285e-06 | 1(Win) | true |
| simdjson (ondemand) | 3034.61 | 0.168649 | 825.479ms | 3370 | 40 | 127.61 | 1059.08 | 0.0480209 | 1.76223 | 7.03739 | 1.15727 | 0.00176558 | 0 | 0 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 800.675 | 0.0284026 | 1266.38ms | 4630 | 4890 | 11997 | 5514.74 | 0.0926792 | 6.51375 | 31.3054 | 5.75076 | 0.00308511 | 3.72338e-05 | 7.46443e-06 | 1(Win) | true |
| Jsonifier (generic) | 719.148 | 0.117451 | 1337.59ms | 4630 | 40 | 2080.17 | 6139.93 | 0.111826 | 7.34338 | 31.5624 | 6.42765 | 0.0107235 | 0.00012419 | 3.23974e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 960.916 | 0.073025 | 1267.41ms | 4630 | 1280 | 14412.7 | 4595.11 | 0.0511322 | 5.43638 | 26.5881 | 4.65443 | 0.00259905 | 4.08342e-05 | 7.25567e-06 | 1(Win) | true |
| Jsonifier (generic) | 838.791 | 0.0799696 | 1332.44ms | 4630 | 640 | 11341.9 | 5264.14 | 0.140891 | 6.24777 | 26.8687 | 5.34341 | 0.00945937 | 1.88985e-05 | 3.37473e-07 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1880.13 | 0.0666626 | 1306.76ms | 11579 | 160 | 2452.73 | 5873.31 | 0.0399211 | 2.7588 | 13.3149 | 2.32818 | 0.00127548 | 1.02556e-05 | 1.07954e-06 | 1(Win) | true |
| Jsonifier (generic) | 1665.98 | 0.10261 | 1387.36ms | 11579 | 160 | 7401.13 | 6628.27 | 0.225964 | 3.10892 | 13.5103 | 2.6143 | 0.00331149 | 2.48294e-05 | 8.09655e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2259.14 | 0.0457809 | 1301.73ms | 11579 | 4890 | 24486.9 | 4887.97 | 0.0368717 | 2.29851 | 11.4185 | 1.89006 | 0.000620738 | 2.96531e-05 | 1.53652e-05 | 1(Win) | true |
| Jsonifier (generic) | 1934.07 | 0.0598014 | 1389.8ms | 11579 | 1280 | 14922.1 | 5709.51 | 0.0594049 | 2.67857 | 11.6483 | 2.18689 | 0.00317493 | 2.1051e-05 | 8.02908e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 714.227 | 0.094803 | 1341.15ms | 4630 | 4890 | 167974 | 6182.22 | 0.00720883 | 7.23737 | 35.6914 | 6.70605 | 0.00338302 | 8.88665e-05 | 4.71275e-05 | 1(Win) | true |
| Jsonifier (generic) | 661.689 | 0.0571575 | 1387.83ms | 4630 | 160 | 2327.67 | 6673.09 | 0.229966 | 7.83207 | 34.6821 | 7.10518 | 0.00976647 | 3.7797e-05 | 8.09935e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 834.811 | 0.0743391 | 1339.53ms | 4630 | 4890 | 75601.3 | 5289.23 | 0.0761957 | 6.19567 | 31.0765 | 5.64428 | 0.00284183 | 8.34338e-05 | 3.97073e-05 | 1(Win) | true |
| Jsonifier (generic) | 765.611 | 0.100425 | 1387.08ms | 4630 | 640 | 21469.1 | 5767.31 | 0.162357 | 6.76636 | 29.9302 | 6.00886 | 0.00833255 | 0.000195397 | 0.000136677 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1697.28 | 0.0289528 | 1374.89ms | 11579 | 4890 | 17351.1 | 6506.07 | 0.0242409 | 3.05528 | 15.1046 | 2.71949 | 0.00161699 | 1.94097e-05 | 6.79956e-06 | 1(Win) | true |
| Jsonifier (generic) | 1560.56 | 0.191655 | 1422.53ms | 11579 | 160 | 29426.8 | 7076.04 | 0.163228 | 3.31233 | 14.7257 | 2.88263 | 0.00297251 | 3.88635e-05 | 2.91476e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1995.04 | 0.0384376 | 1364.09ms | 11579 | 4890 | 22134.1 | 5535.03 | 0.0478441 | 2.60314 | 13.2023 | 2.28595 | 0.000862749 | 2.92999e-05 | 1.35638e-05 | 1(Win) | true |
| Jsonifier (generic) | 1810.29 | 0.0812864 | 1427.67ms | 11579 | 40 | 983.426 | 6099.9 | 0.0895387 | 2.86468 | 12.8288 | 2.449 | 0.00336385 | 3.45453e-05 | 1.29545e-05 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7282.72 | 0.113634 | 776.469ms | 4630 | 160 | 75.9472 | 606.3 | 0.0164908 | 0.754332 | 3.56566 | 0.463715 | 0.000433315 | 5.39957e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6530.21 | 0.0508742 | 781.517ms | 4630 | 640 | 75.7326 | 676.167 | 0.0358049 | 0.837685 | 4.11512 | 0.492009 | 0.000431965 | 9.11177e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7304.05 | 0.236135 | 772.479ms | 4630 | 640 | 1304.17 | 604.53 | 0.0965006 | 0.74992 | 3.53218 | 0.45594 | 0.00043399 | 9.44924e-06 | 1.01242e-06 | 1(Win) | true |
| simdjson (ondemand) | 6666 | 0.0219876 | 779.276ms | 4630 | 4890 | 103.728 | 662.393 | 0.193249 | 0.819966 | 4.08013 | 0.484233 | 0.00043201 | 1.38688e-05 | 3.18011e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12006.2 | 0.131192 | 805.948ms | 11579 | 80 | 116.475 | 919.737 | 0.0421138 | 0.447733 | 2.126 | 0.20874 | 0.000345453 | 2.15908e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 10725.8 | 0.0594654 | 817.641ms | 11579 | 4890 | 1832.81 | 1029.53 | 0.0367919 | 0.498483 | 2.45073 | 0.231626 | 0.000173133 | 6.32271e-06 | 4.94513e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12274 | 0.0718525 | 806.36ms | 11579 | 4890 | 2043.45 | 899.676 | 0.129738 | 0.437383 | 2.11262 | 0.205631 | 0.000222301 | 1.1886e-05 | 2.27829e-06 | 1(Win) | true |
| simdjson (ondemand) | 10844 | 0.0659193 | 815.127ms | 11579 | 320 | 144.192 | 1018.32 | 0.122907 | 0.492778 | 2.43674 | 0.228517 | 0.000172726 | 7.82667e-06 | 5.3977e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5376.38 | 0.101834 | 795.745ms | 4630 | 2560 | 1790.63 | 821.279 | 0.00623036 | 1.00417 | 5.09482 | 0.800864 | 0.00064837 | 1.4427e-05 | 5.65267e-06 | 1(Win) | true |
| simdjson (ondemand) | 4222.26 | 0.118653 | 819.501ms | 4630 | 1280 | 1970.78 | 1045.77 | 0.517688 | 1.26658 | 5.58575 | 0.819655 | 0.000650985 | 1.41739e-05 | 3.03726e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5459.36 | 0.0672786 | 793.725ms | 4630 | 4890 | 1447.91 | 808.797 | 0.121112 | 0.989099 | 5.06134 | 0.792873 | 0.000648346 | 1.01587e-05 | 2.29675e-06 | 1(Win) | true |
| simdjson (ondemand) | 4343.41 | 0.163997 | 815.166ms | 4630 | 1280 | 3557.82 | 1016.6 | 0.102622 | 1.23218 | 5.55076 | 0.811879 | 0.000648792 | 8.26809e-06 | 6.74946e-07 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9927.07 | 0.0749827 | 827.851ms | 11579 | 4890 | 3401.97 | 1112.37 | 0.0470711 | 0.536425 | 2.7372 | 0.344158 | 0.000259726 | 8.88358e-06 | 1.94273e-06 | 1(Win) | true |
| simdjson (ondemand) | 7888.36 | 0.122202 | 854.739ms | 11579 | 1280 | 3745.71 | 1399.86 | 0.270888 | 0.671745 | 3.03878 | 0.362639 | 0.000259495 | 1.49112e-05 | 3.44104e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10096.4 | 0.0603655 | 824.026ms | 11579 | 2560 | 1115.91 | 1093.72 | 0.0649725 | 0.529756 | 2.72381 | 0.340962 | 0.000259326 | 1.45738e-05 | 7.05075e-06 | 1(Win) | true |
| simdjson (ondemand) | 8002.65 | 0.133212 | 851.92ms | 11579 | 1280 | 4324.84 | 1379.87 | 0.216264 | 0.662312 | 3.02479 | 0.35953 | 0.000266377 | 3.56923e-05 | 1.47762e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1210.94 | 0.0763902 | 1131.11ms | 5092 | 160 | 1501.51 | 4010.2 | 0.0408501 | 4.297 | 17.4683 | 3.31918 | 0.00340117 | 5.27789e-05 | 7.36449e-06 | 1(Win) | true |
| simdjson (ondemand) | 1203.17 | 0.0850857 | 1136.26ms | 5092 | 40 | 471.733 | 4036.1 | 0.1262 | 4.3242 | 17.5142 | 3.01417 | 0.00237137 | 1.96386e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1377.51 | 0.105589 | 1122.64ms | 5092 | 80 | 1108.46 | 3525.29 | 0.128168 | 3.78426 | 15.7903 | 2.89827 | 0.00248429 | 0.000186567 | 5.40063e-05 | 1(Win) | true |
| simdjson (ondemand) | 1342.39 | 0.11159 | 1132.38ms | 5092 | 80 | 1303.65 | 3617.5 | 0.0883807 | 3.95524 | 16.262 | 2.69104 | 0.00323547 | 8.59191e-05 | 4.17321e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2168.28 | 0.0566311 | 1160.23ms | 9739 | 160 | 941.522 | 4283.51 | 0.0183811 | 2.3985 | 9.81158 | 1.60659 | 0.00125462 | 1.41185e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2157.34 | 0.068658 | 1162.36ms | 9739 | 1280 | 11183.7 | 4305.23 | 0.0800348 | 2.39655 | 9.74421 | 1.75638 | 0.00203194 | 2.19799e-05 | 4.25159e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2410.52 | 0.0872753 | 1165.15ms | 9739 | 640 | 7237.18 | 3853.04 | 0.00944782 | 2.15962 | 8.93162 | 1.5517 | 0.00123794 | 8.8401e-05 | 6.12871e-05 | 1(Win) | true |
| simdjson (ondemand) | 2341.82 | 0.0484817 | 1157.95ms | 9739 | 1280 | 4732.45 | 3966.07 | 0.00551584 | 2.22196 | 9.16342 | 1.43665 | 0.00135177 | 3.24886e-05 | 1.00273e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 687.041 | 0.0629614 | 1434.71ms | 5092 | 160 | 3168.7 | 7068.16 | 0.07431 | 7.54165 | 32.0024 | 6.55818 | 0.00722457 | 3.06854e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 451.605 | 0.0352826 | 1795.75ms | 5092 | 2560 | 36848.5 | 10753 | 0.0666319 | 11.4338 | 53.6991 | 10.9242 | 0.0183536 | 0.000151279 | 8.66095e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 740.698 | 0.101688 | 1435.08ms | 5092 | 40 | 1777.86 | 6556.12 | 0.0717643 | 6.99976 | 30.075 | 6.10112 | 0.00760998 | 5.89159e-05 | 4.90966e-06 | 1(Win) | true |
| simdjson (ondemand) | 471.684 | 0.0554119 | 1793.64ms | 5092 | 640 | 20828.7 | 10295.3 | 0.00840729 | 10.9541 | 52.1233 | 10.5396 | 0.0180961 | 5.30857e-05 | 9.81932e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1222.94 | 0.0298366 | 1498.53ms | 9739 | 1280 | 6572.5 | 7594.7 | 0.436243 | 4.23447 | 17.5094 | 3.52134 | 0.00408971 | 2.95205e-05 | 1.0268e-05 | 1(Win) | true |
| simdjson (ondemand) | 849.885 | 0.0471964 | 1815.7ms | 9739 | 640 | 17025.8 | 10928.3 | 0.0168112 | 6.07846 | 28.6469 | 5.72061 | 0.0089561 | 2.19799e-05 | 5.29443e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.44 | 0.0730088 | 1490.77ms | 9739 | 320 | 8490.37 | 7055.26 | 0.000177173 | 3.93383 | 16.5143 | 3.28468 | 0.00407607 | 4.58851e-05 | 5.77575e-06 | 1(Win) | true |
| simdjson (ondemand) | 885.659 | 0.0380992 | 1817.17ms | 9739 | 1280 | 20433.2 | 10486.9 | 0.0390662 | 5.83405 | 27.8232 | 5.51818 | 0.0092586 | 2.96809e-05 | 8.10209e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5094.5 | 0.0763485 | 811.201ms | 5092 | 2560 | 1355.86 | 953.207 | 0.158587 | 1.05234 | 4.72467 | 0.676552 | 0.00126247 | 1.0433e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4794.65 | 0.102698 | 816.127ms | 5092 | 160 | 173.105 | 1012.82 | 0.0351617 | 1.13603 | 5.40102 | 0.663197 | 0.00115254 | 9.81932e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5229.6 | 0.0716094 | 808.857ms | 5092 | 640 | 282.982 | 928.581 | 0.109254 | 1.02636 | 4.60978 | 0.652003 | 0.00124552 | 6.44393e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4833.49 | 0.123699 | 814.028ms | 5092 | 1280 | 1976.97 | 1004.68 | 0.0435273 | 1.10678 | 5.28574 | 0.63806 | 0.00126562 | 6.13708e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7573.07 | 0.0514819 | 837.524ms | 9739 | 4890 | 1949.41 | 1226.43 | 0.0107927 | 0.701572 | 3.08289 | 0.373144 | 0.000666853 | 1.35437e-05 | 3.69564e-06 | 1(Win) | true |
| simdjson (ondemand) | 7091.19 | 0.0307925 | 845.821ms | 9739 | 640 | 104.102 | 1309.77 | 0.0540702 | 0.748326 | 3.502 | 0.379916 | 0.00052832 | 9.46581e-06 | 4.81312e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7822.86 | 0.0560363 | 832.658ms | 9739 | 4890 | 2164.44 | 1187.27 | 0.00499645 | 0.679786 | 3.0228 | 0.360304 | 0.000641655 | 1.35857e-05 | 2.12079e-06 | 1(Win) | true |
| simdjson (ondemand) | 7344.72 | 0.049787 | 842.872ms | 9739 | 2560 | 1014.73 | 1264.56 | 0.0116161 | 0.723517 | 3.41575 | 0.361639 | 0.000563456 | 1.05889e-05 | 1.60437e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3348.84 | 0.0728644 | 862.252ms | 5092 | 2560 | 2857.97 | 1450.09 | 0.106185 | 1.58459 | 7.76984 | 1.38374 | 0.0016037 | 2.24003e-05 | 8.82205e-06 | 1(Win) | true |
| simdjson (ondemand) | 3170.19 | 0.0691018 | 867.521ms | 5092 | 320 | 358.539 | 1531.81 | 0.146283 | 1.66724 | 8.32718 | 1.30931 | 0.00216455 | 1.4729e-05 | 3.68225e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3289.94 | 0.0531097 | 864.538ms | 5092 | 4890 | 3005.1 | 1476.05 | 0.114063 | 1.60258 | 7.65436 | 1.3586 | 0.00259829 | 1.75101e-05 | 6.10445e-06 | 1(Win) | true |
| simdjson (ondemand) | 3146.83 | 0.026893 | 868.272ms | 5092 | 1280 | 220.455 | 1543.17 | 0.204237 | 1.67914 | 8.2119 | 1.28417 | 0.00292999 | 7.9782e-06 | 9.20562e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5157.52 | 0.15143 | 901.988ms | 9739 | 1280 | 9518.82 | 1800.83 | 0.000216914 | 1.00938 | 4.68703 | 0.749153 | 0.00132008 | 1.66855e-05 | 3.93072e-06 | 1(Win) | true |
| simdjson (ondemand) | 5139.39 | 0.0931577 | 903.048ms | 9739 | 2560 | 7255.77 | 1807.19 | 0.430677 | 1.01486 | 5.00647 | 0.712599 | 0.00125907 | 3.14457e-05 | 1.56025e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5260.42 | 0.0461245 | 890.863ms | 9739 | 4890 | 3243.09 | 1765.61 | 0.129486 | 0.998745 | 4.62666 | 0.73601 | 0.00138889 | 1.65254e-05 | 2.68774e-06 | 1(Win) | true |
| simdjson (ondemand) | 5166.93 | 0.0414344 | 892.108ms | 9739 | 4890 | 2712.66 | 1797.55 | 0.0920089 | 1.01862 | 4.94579 | 0.699456 | 0.00143422 | 1.48036e-05 | 2.89772e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.68 | 0.0884369 | 1031.08ms | 4857 | 640 | 4858.98 | 3115.65 | 0.116963 | 3.50694 | 14.1414 | 2.72782 | 0.00176646 | 2.54144e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 1397.47 | 0.156952 | 1051.11ms | 4857 | 30 | 811.909 | 3314.57 | 0.0603761 | 3.73217 | 14.3351 | 2.55487 | 0.0014069 | 6.86295e-05 | 2.74518e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1928.3 | 0.0604695 | 984.709ms | 4857 | 320 | 675.164 | 2402.11 | 0.148658 | 2.71752 | 11.2771 | 2.09656 | 0.00198618 | 3.41003e-05 | 8.36422e-06 | 1(Win) | true |
| simdjson (ondemand) | 1721.51 | 0.0367809 | 1031.62ms | 4857 | 4890 | 4789.27 | 2690.65 | 0.0519963 | 3.04058 | 12.1604 | 2.08627 | 0.000773618 | 3.57884e-05 | 4.71564e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1959.18 | 0.185298 | 1049.73ms | 6701 | 320 | 11690.1 | 3261.85 | 0.0286537 | 2.69239 | 10.6927 | 1.98732 | 0.000936427 | 2.70482e-05 | 6.06253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1901.29 | 0.033903 | 1056.97ms | 6701 | 4890 | 6349.9 | 3361.17 | 0.137248 | 2.73974 | 10.8105 | 1.86845 | 0.000593447 | 3.00599e-05 | 6.53078e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2492.8 | 0.0379351 | 1000.67ms | 6701 | 2560 | 2421.18 | 2563.61 | 0.0675469 | 2.09899 | 8.63758 | 1.53501 | 0.00185851 | 2.6407e-05 | 4.19713e-06 | 1(Win) | true |
| simdjson (ondemand) | 2300.56 | 0.0496718 | 1020.62ms | 6701 | 1280 | 2436.91 | 2777.83 | 0.0719098 | 2.27185 | 9.22937 | 1.52783 | 0.000536417 | 2.71648e-05 | 5.47959e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 678.011 | 0.0739949 | 1406.98ms | 4857 | 320 | 8177.42 | 6831.74 | 0.029678 | 7.63854 | 31.1108 | 6.22936 | 0.00801742 | 0.000103588 | 6.69137e-05 | 1(Win) | true |
| simdjson (ondemand) | 237.703 | 0.0196519 | 2673.19ms | 4857 | 2560 | 37542 | 19486.5 | 0.0813043 | 21.667 | 107.326 | 22.5853 | 0.0487615 | 6.13644e-05 | 1.53612e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.569 | 0.0468615 | 1349.24ms | 4857 | 640 | 5131.53 | 6042.51 | 0.0543323 | 6.76301 | 28.1787 | 5.58164 | 0.00749595 | 3.4422e-05 | 7.07741e-06 | 1(Win) | true |
| simdjson (ondemand) | 245.667 | 0.0566988 | 2638.02ms | 4857 | 320 | 36571.2 | 18854.8 | 0.0377746 | 20.9924 | 105.15 | 22.1116 | 0.0487409 | 5.40457e-05 | 1.9302e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 878.719 | 0.0545092 | 1452.26ms | 6701 | 160 | 2514.43 | 7272.6 | 0.0910062 | 5.89653 | 23.5739 | 4.76213 | 0.00608118 | 6.06253e-05 | 1.21251e-05 | 1(Win) | true |
| simdjson (ondemand) | 328.808 | 0.0427759 | 2669.82ms | 6701 | 320 | 22117.8 | 19435.6 | 0.0801848 | 15.6907 | 77.9331 | 16.324 | 0.0345018 | 3.68415e-05 | 1.30578e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 995.259 | 0.0585048 | 1398.64ms | 6701 | 640 | 9031.69 | 6421.01 | 0.0339577 | 5.20541 | 21.4672 | 4.29637 | 0.00533782 | 2.44833e-05 | 8.86062e-06 | 1(Win) | true |
| simdjson (ondemand) | 338.411 | 0.0485288 | 2639.38ms | 6701 | 1280 | 107497 | 18884 | 0.0877004 | 15.2312 | 76.3585 | 15.981 | 0.0363883 | 6.56385e-05 | 3.18283e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4056.78 | 0.122935 | 830.334ms | 4857 | 640 | 1260.97 | 1141.79 | 0.0506588 | 1.3136 | 5.51799 | 0.850808 | 0.000211679 | 2.09105e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3717.33 | 0.0608939 | 840.68ms | 4857 | 320 | 184.235 | 1246.06 | 0.00601935 | 1.43115 | 5.98044 | 0.837142 | 0.000231624 | 3.53871e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4615.37 | 0.0933039 | 822.347ms | 4857 | 1280 | 1122.36 | 1003.6 | 0.0759186 | 1.15933 | 4.96026 | 0.725345 | 0.000619113 | 1.02944e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4178.73 | 0.0389056 | 831.636ms | 4857 | 1280 | 238.057 | 1108.47 | 0.0307903 | 1.27811 | 5.43422 | 0.714639 | 0.000534988 | 1.84978e-05 | 3.86041e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4972.24 | 0.221593 | 847.427ms | 6701 | 40 | 324.449 | 1285.25 | 0.0947535 | 1.06771 | 4.49291 | 0.641098 | 0.000149231 | 1.49231e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4745.66 | 0.0778163 | 855.94ms | 6701 | 320 | 351.379 | 1346.61 | 0.0761749 | 1.11855 | 4.76004 | 0.625429 | 0.000152962 | 3.31107e-05 | 1.67885e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5562.22 | 0.110216 | 838.959ms | 6701 | 160 | 256.56 | 1148.92 | 0.0587851 | 0.958253 | 4.08894 | 0.550216 | 0.000465416 | 1.77212e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5234.42 | 0.124411 | 847.003ms | 6701 | 80 | 184.566 | 1220.88 | 0.051219 | 1.01662 | 4.36412 | 0.536636 | 0.000520445 | 1.49231e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2951.7 | 0.0657964 | 878.281ms | 4857 | 4890 | 5213.2 | 1569.26 | 0.0609712 | 1.78668 | 7.50525 | 1.32592 | 0.00044727 | 3.322e-05 | 1.77679e-05 | 1(Win) | true |
| simdjson (ondemand) | 2268.02 | 0.0901665 | 920.753ms | 4857 | 160 | 542.566 | 2042.31 | 0.0339805 | 2.31485 | 10.2399 | 1.70764 | 0.00179766 | 2.57361e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3255.03 | 0.0589554 | 864.178ms | 4857 | 320 | 225.228 | 1423.03 | 0.0373185 | 1.62628 | 6.94667 | 1.19971 | 0.00109185 | 2.12322e-05 | 2.57361e-06 | 1(Win) | true |
| simdjson (ondemand) | 2397.87 | 0.0283745 | 914.764ms | 4857 | 4890 | 1469.1 | 1931.72 | 0.0245368 | 2.19276 | 9.69405 | 1.58514 | 0.0025374 | 1.701e-05 | 2.1052e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3736.89 | 0.0695592 | 890.502ms | 6701 | 1280 | 1811.25 | 1710.13 | 0.0132922 | 1.40948 | 5.97269 | 1.00522 | 0.000368415 | 1.56227e-05 | 2.09857e-06 | 1(Win) | true |
| simdjson (ondemand) | 2992.08 | 0.0350248 | 932.114ms | 6701 | 4890 | 2736.48 | 2135.83 | 0.203429 | 1.75287 | 7.77556 | 1.24086 | 0.00124512 | 1.60523e-05 | 3.29591e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4040.41 | 0.045119 | 882.613ms | 6701 | 640 | 325.932 | 1581.66 | 0.0224199 | 1.30747 | 5.5726 | 0.913147 | 0.000882098 | 1.469e-05 | 1.16587e-06 | 1(Win) | true |
| simdjson (ondemand) | 3154.13 | 0.0559774 | 923.102ms | 6701 | 2560 | 3292.96 | 2026.1 | 0.011762 | 1.66434 | 7.37994 | 1.15207 | 0.00206557 | 1.48649e-05 | 1.98198e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1217.41 | 0.205048 | 851.97ms | 1691 | 30 | 221.333 | 1324.67 | 0.0678955 | 4.35446 | 14.7179 | 2.84151 | 0.00301597 | 0.000433668 | 0.000295683 | 1(Win) | true |
| simdjson (ondemand) | 1198.44 | 0.182884 | 863.201ms | 1691 | 30 | 181.689 | 1345.63 | 0.0594869 | 4.34739 | 15.2194 | 2.87226 | 0.000729351 | 0.000137985 | 1.97122e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1409.35 | 0.151598 | 845.763ms | 1691 | 80 | 240.728 | 1144.26 | 0.0600463 | 3.78321 | 13.1821 | 2.46008 | 0.0019589 | 2.21762e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1396.09 | 0.0716658 | 847.36ms | 1691 | 2560 | 1754.38 | 1155.13 | 0.0565734 | 3.78655 | 13.6777 | 2.49084 | 0.000594831 | 0.000142066 | 3.99634e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1552.04 | 0.0709499 | 852.851ms | 2158 | 2560 | 2265.91 | 1326.02 | 0.00285756 | 3.41175 | 12.114 | 2.3202 | 0.000467736 | 8.6162e-05 | 1.66532e-05 | 1(Win) | true |
| simdjson (ondemand) | 1530.02 | 0.0593337 | 856.793ms | 2158 | 4890 | 3114.74 | 1345.1 | 0.0344746 | 3.46173 | 12.1501 | 2.24375 | 0.000467846 | 9.43841e-05 | 2.78604e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1770.34 | 0.0842651 | 846.443ms | 2158 | 160 | 153.535 | 1162.51 | 0.288463 | 3.00836 | 10.8832 | 2.01483 | 0.000474977 | 9.26784e-05 | 5.7924e-06 | 1(Win) | true |
| simdjson (ondemand) | 1759.76 | 0.0853692 | 847.435ms | 2158 | 160 | 159.484 | 1169.49 | 0.1851 | 3.02519 | 10.9411 | 1.94532 | 0.000463392 | 7.53012e-05 | 5.7924e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 897.019 | 0.108667 | 901.351ms | 1691 | 640 | 2442.62 | 1797.8 | 0.014951 | 5.86671 | 20.8995 | 4.14075 | 0.00196629 | 7.66928e-05 | 1.57082e-05 | 1(Win) | true |
| simdjson (ondemand) | 727.944 | 0.0498173 | 943.37ms | 1691 | 2560 | 3118.1 | 2215.37 | 0.178459 | 7.20085 | 27.851 | 5.45831 | 0.00118227 | 0.000115039 | 2.33312e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.428 | 0.108903 | 897.317ms | 1691 | 640 | 2016.41 | 1629.9 | 0.0571987 | 5.32452 | 19.3631 | 3.75931 | 0.00227029 | 8.22368e-05 | 1.66322e-05 | 1(Win) | true |
| simdjson (ondemand) | 782.125 | 0.0473008 | 939.308ms | 1691 | 4890 | 4651.36 | 2061.9 | 0.0926143 | 6.72017 | 26.3087 | 5.07688 | 0.00214101 | 9.72307e-05 | 2.33402e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1045.83 | 0.138112 | 902.782ms | 2158 | 40 | 295.464 | 1967.85 | 0.00762311 | 5.02298 | 17.2159 | 3.46803 | 0.00282669 | 9.26784e-05 | 3.47544e-05 | 1(Win) | true |
| simdjson (ondemand) | 930.039 | 0.0492091 | 936.528ms | 2158 | 2560 | 3035.51 | 2212.84 | 0.315669 | 5.65797 | 21.962 | 4.25533 | 0.000972218 | 9.34025e-05 | 2.08164e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1185.45 | 0.115133 | 896.382ms | 2158 | 80 | 319.615 | 1736.08 | 0.0546912 | 4.53176 | 16.012 | 3.16914 | 0.00189411 | 8.6886e-05 | 2.31696e-05 | 1(Win) | true |
| simdjson (ondemand) | 1019.47 | 0.0971379 | 932.279ms | 2158 | 160 | 615.254 | 2018.73 | 0.0213579 | 5.24866 | 20.7535 | 3.95644 | 0.00143941 | 4.63392e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4595.37 | 0.100309 | 746.425ms | 1691 | 4890 | 605.951 | 350.932 | 0.0627767 | 1.249 | 4.70136 | 0.70964 | 0.000592213 | 2.86613e-05 | 8.2235e-06 | 1(Win) | true |
| simdjson (ondemand) | 3976.67 | 0.102081 | 750.829ms | 1691 | 320 | 54.8391 | 405.531 | 0.021572 | 1.42338 | 5.11709 | 0.719692 | 0.00110142 | 4.62005e-05 | 7.39208e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5046.33 | 0.0945505 | 742.528ms | 1691 | 4890 | 446.45 | 319.572 | 0.0444452 | 1.15318 | 4.3702 | 0.635128 | 0.000592334 | 4.81316e-05 | 3.08381e-05 | 1(Win) | true |
| simdjson (ondemand) | 4416.44 | 0.185325 | 747.995ms | 1691 | 80 | 36.6354 | 365.15 | 0.0479485 | 1.31678 | 4.79539 | 0.64518 | 0.00113838 | 4.43525e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5343.38 | 0.207764 | 747.049ms | 2158 | 1280 | 819.635 | 385.155 | 0.215882 | 1.07987 | 4.08434 | 0.569046 | 0.00046484 | 2.02734e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4821.39 | 0.0977655 | 753.84ms | 2158 | 2560 | 445.83 | 426.854 | 0.074984 | 1.1724 | 4.27433 | 0.57368 | 0.000773104 | 2.46177e-05 | 4.52531e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5636.51 | 0.130466 | 745.6ms | 2158 | 640 | 145.23 | 365.125 | 0.24108 | 1.01692 | 3.82484 | 0.510658 | 0.000621235 | 1.30329e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5324.78 | 0.297144 | 750.772ms | 2158 | 30 | 39.569 | 386.5 | 0.172191 | 1.08386 | 4.02224 | 0.515292 | 0.00077232 | 0 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3198.46 | 0.0621835 | 761.314ms | 1691 | 4890 | 480.689 | 504.199 | 0.167958 | 1.748 | 6.87877 | 1.21348 | 0.000609869 | 3.25312e-05 | 5.44202e-06 | 1(Win) | true |
| simdjson (ondemand) | 2700.92 | 0.0758122 | 769.68ms | 1691 | 4890 | 1001.96 | 597.079 | 0.108609 | 2.04278 | 8.48212 | 1.44829 | 0.000675294 | 3.74895e-05 | 1.25771e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3397.87 | 0.0562708 | 763.418ms | 1691 | 4890 | 348.779 | 474.611 | 0.0578904 | 1.64308 | 6.54761 | 1.13897 | 0.000761641 | 3.41033e-05 | 3.02334e-06 | 1(Win) | true |
| simdjson (ondemand) | 2863.08 | 0.184636 | 769.436ms | 1691 | 80 | 86.5252 | 563.263 | 0.214801 | 1.92839 | 8.16026 | 1.37374 | 0.000643111 | 1.47842e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3774.38 | 0.180259 | 774.481ms | 2158 | 80 | 77.2847 | 545.263 | 0.0114637 | 1.46258 | 5.80816 | 0.979611 | 0.000474977 | 2.8962e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3274.25 | 0.0600771 | 774.554ms | 2158 | 1280 | 182.518 | 628.549 | 0.307327 | 1.67524 | 6.90686 | 1.14319 | 0.000600962 | 1.66532e-05 | 2.8962e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3892.25 | 0.162018 | 769.155ms | 2158 | 160 | 117.421 | 528.75 | 0.0449374 | 1.42547 | 5.54866 | 0.921223 | 0.0013757 | 4.05468e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3474.38 | 0.111595 | 772.152ms | 2158 | 160 | 69.9125 | 592.344 | 0.0896057 | 1.58288 | 6.65477 | 1.0848 | 0.000489458 | 8.6886e-06 | 2.8962e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1352.97 | 0.0478673 | 1027.61ms | 4390 | 2560 | 5616.56 | 3094.4 | 0.0582493 | 3.84988 | 17.6444 | 3.28907 | 0.00147752 | 8.37308e-05 | 3.07873e-05 | 1(Win) | true |
| simdjson (ondemand) | 1066.32 | 0.0534554 | 1107.52ms | 4390 | 640 | 2819.14 | 3926.24 | 0.00795863 | 4.89969 | 19.6932 | 3.64624 | 0.00394647 | 2.66942e-05 | 2.49146e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.82 | 0.0451219 | 1014.09ms | 4390 | 2560 | 3970.76 | 2760.13 | 0.156331 | 3.4459 | 16.2403 | 2.97062 | 0.00153234 | 3.63041e-05 | 6.58457e-06 | 1(Win) | true |
| simdjson (ondemand) | 1181.05 | 0.0475024 | 1091.3ms | 4390 | 1280 | 3629.4 | 3544.84 | 0.0358484 | 4.40916 | 18.2064 | 3.31458 | 0.00431983 | 3.00755e-05 | 5.33884e-07 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2569.8 | 0.0294461 | 1066.05ms | 9378 | 4890 | 5135.53 | 3480.25 | 0.0555537 | 2.02566 | 9.127 | 1.5964 | 0.000880798 | 2.7912e-05 | 9.52933e-06 | 1(Win) | true |
| simdjson (ondemand) | 2142.81 | 0.0344874 | 1133.46ms | 9378 | 320 | 663.017 | 4173.76 | 0.0111548 | 2.42701 | 9.92354 | 1.73822 | 0.00182375 | 1.23294e-05 | 1.33291e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2826.97 | 0.0583857 | 1061.39ms | 9378 | 1280 | 4367.17 | 3163.65 | 0.137515 | 1.84464 | 8.47004 | 1.44732 | 0.000849145 | 2.23262e-05 | 1.66613e-06 | 1(Win) | true |
| simdjson (ondemand) | 2377.81 | 0.049353 | 1115.09ms | 9378 | 1280 | 4410.68 | 3761.26 | 0.127951 | 2.18902 | 9.22755 | 1.58296 | 0.00188923 | 1.8744e-05 | 1.41621e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 763.637 | 0.0305458 | 1267.16ms | 4390 | 4890 | 13714.1 | 5482.49 | 0.0467668 | 6.78538 | 29.4481 | 5.96606 | 0.0112035 | 4.78872e-05 | 1.15991e-05 | 1(Win) | true |
| simdjson (ondemand) | 696.831 | 0.0310319 | 1322.6ms | 4390 | 4890 | 16998.1 | 6008.1 | 0.0785969 | 7.43519 | 31.7656 | 6.19567 | 0.0111456 | 0.00013523 | 5.57597e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.942 | 0.0778095 | 1257.14ms | 4390 | 4890 | 79299.2 | 5175.44 | 0.0925123 | 6.41956 | 28.0442 | 5.64761 | 0.0109828 | 0.000124004 | 6.8011e-05 | 1(Win) | true |
| simdjson (ondemand) | 739.621 | 0.155648 | 1307.67ms | 4390 | 160 | 12419.8 | 5660.51 | 0.0874818 | 7.00836 | 30.2786 | 5.86401 | 0.0112201 | 5.83713e-05 | 1.70843e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1552.86 | 0.0326429 | 1302.76ms | 9378 | 4890 | 17283.9 | 5759.4 | 0.0780225 | 3.33688 | 14.654 | 2.87791 | 0.0055793 | 3.27312e-05 | 1.31056e-05 | 1(Win) | true |
| simdjson (ondemand) | 1443.42 | 0.0528475 | 1340.23ms | 9378 | 1280 | 13724.4 | 6196.07 | 0.141045 | 3.58923 | 15.4374 | 2.90051 | 0.00485686 | 2.69081e-05 | 7.4976e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1649.02 | 0.0956884 | 1285.18ms | 9378 | 4890 | 131703 | 5423.54 | 0.0337957 | 3.14116 | 13.9971 | 2.72883 | 0.00580864 | 3.93821e-05 | 1.29311e-05 | 1(Win) | true |
| simdjson (ondemand) | 1538.64 | 0.0554757 | 1327.59ms | 9378 | 1280 | 13309.4 | 5812.63 | 0.0684997 | 3.36921 | 14.7413 | 2.74526 | 0.00471016 | 1.62448e-05 | 1.08299e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2222.57 | 0.0881423 | 902.286ms | 4390 | 1280 | 3528.56 | 1883.69 | 0.0335416 | 2.36348 | 10.6829 | 1.87039 | 0.00204086 | 3.11432e-05 | 8.54214e-06 | 1(Win) | true |
| simdjson (ondemand) | 1953.97 | 0.037052 | 930.6ms | 4390 | 2560 | 1613.46 | 2142.63 | 0.0408574 | 2.68379 | 11.5866 | 1.92847 | 0.0016998 | 2.35799e-05 | 1.95757e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2316.01 | 0.0405298 | 899.25ms | 4390 | 640 | 343.539 | 1807.69 | 0.000605058 | 2.27406 | 10.3913 | 1.80091 | 0.00200847 | 1.60165e-05 | 3.55923e-07 | 1(Win) | true |
| simdjson (ondemand) | 2040.6 | 0.0783277 | 924.773ms | 4390 | 1280 | 3305.62 | 2051.67 | 0.0873526 | 2.57225 | 11.2289 | 1.84579 | 0.00225602 | 1.67284e-05 | 5.33884e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3998.79 | 0.0413684 | 961.833ms | 9378 | 4890 | 4186.1 | 2236.57 | 0.283771 | 1.30389 | 5.78482 | 0.924398 | 0.00104539 | 1.80992e-05 | 6.10575e-06 | 1(Win) | true |
| simdjson (ondemand) | 3756.26 | 0.0442489 | 957.263ms | 9378 | 160 | 177.597 | 2380.97 | 0.000524992 | 1.39448 | 6.12487 | 0.932821 | 0.00106633 | 1.99936e-05 | 1.33291e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4169.11 | 0.117249 | 972.581ms | 9378 | 640 | 4048.82 | 2145.2 | 0.144353 | 1.25794 | 5.64865 | 0.891875 | 0.00107182 | 9.33035e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3926.19 | 0.0545829 | 950.32ms | 9378 | 4890 | 7559.63 | 2277.92 | 0.113006 | 1.33335 | 5.95745 | 0.894114 | 0.00113281 | 2.17844e-05 | 9.20224e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1676.77 | 0.230542 | 972.212ms | 4390 | 320 | 10603.2 | 2496.85 | 0.0399413 | 3.11438 | 13.8574 | 2.60205 | 0.00404399 | 1.70843e-05 | 7.11845e-07 | 1(Win) | true |
| simdjson (ondemand) | 1601.39 | 0.0300774 | 979.749ms | 4390 | 4890 | 3023.61 | 2614.38 | 0.00356039 | 3.25764 | 14.1203 | 2.44784 | 0.00459531 | 2.65988e-05 | 9.03708e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1750.05 | 0.160949 | 967.595ms | 4390 | 320 | 4744.12 | 2392.29 | 0.127001 | 2.98907 | 13.508 | 2.52119 | 0.00351865 | 2.06435e-05 | 7.8303e-06 | 1(Win) | true |
| simdjson (ondemand) | 1679.42 | 0.0735993 | 975.227ms | 4390 | 80 | 269.306 | 2492.9 | 0.087324 | 3.11807 | 13.7626 | 2.36515 | 0.004291 | 5.69476e-05 | 2.56264e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3182.3 | 0.0703763 | 1007.93ms | 9378 | 1280 | 5007.27 | 2810.41 | 0.141073 | 1.6365 | 7.2813 | 1.28247 | 0.00232642 | 1.38289e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 3151.08 | 0.0325333 | 999.863ms | 9378 | 4890 | 4169.33 | 2838.25 | 0.147937 | 1.65643 | 7.28396 | 1.17061 | 0.00210241 | 1.84917e-05 | 5.12447e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3325.29 | 0.0516878 | 996.152ms | 9378 | 1280 | 2473.71 | 2689.56 | 0.161591 | 1.56355 | 7.11804 | 1.24462 | 0.0019872 | 3.49888e-05 | 1.47453e-05 | 1(Win) | true |
| simdjson (ondemand) | 3259.07 | 0.0428422 | 1006.43ms | 9378 | 4890 | 6759.05 | 2744.21 | 0.152239 | 1.6012 | 7.14353 | 1.13724 | 0.00206457 | 1.26258e-05 | 2.37688e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.93 | 0.117292 | 1012.79ms | 4669 | 40 | 467.958 | 2916.12 | 0.0893652 | 3.41834 | 13.7406 | 2.76783 | 0.00171878 | 9.10259e-05 | 8.0317e-05 | 1(Win) | true |
| simdjson (ondemand) | 1498.49 | 0.0465043 | 1020.9ms | 4669 | 2560 | 4888.38 | 2971.46 | 0.206224 | 3.47139 | 15.211 | 2.49177 | 0.000431453 | 2.96169e-05 | 8.53368e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1674.21 | 0.123734 | 994.406ms | 4669 | 320 | 3465.43 | 2659.59 | 0.00235004 | 3.11917 | 12.9321 | 2.58771 | 0.00173619 | 2.14179e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 1625.06 | 0.0363467 | 1002.01ms | 4669 | 4890 | 4850.08 | 2740.03 | 0.202161 | 3.20141 | 14.4097 | 2.3097 | 0.000431292 | 3.29371e-05 | 5.56251e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2400.42 | 0.0601854 | 1032.8ms | 7932 | 2560 | 9209.03 | 3151.34 | 0.115516 | 2.17854 | 9.52219 | 1.4879 | 0.000833845 | 1.62514e-05 | 4.4322e-06 | 1(Win) | true |
| Jsonifier (generic) | 2361.07 | 0.224509 | 1035.24ms | 7932 | 320 | 16556.4 | 3203.87 | 0.106332 | 2.20358 | 8.75139 | 1.68217 | 0.00111495 | 2.36384e-05 | 4.72769e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2611.33 | 0.0476317 | 1011.57ms | 7932 | 2560 | 4873.87 | 2896.82 | 0.34742 | 2.02059 | 9.06833 | 1.38591 | 0.000728753 | 1.5759e-05 | 4.72769e-06 | 1(Win) | true |
| Jsonifier (generic) | 2547.85 | 0.0456496 | 1016.88ms | 7932 | 2560 | 4702.55 | 2968.99 | 0.113409 | 2.05138 | 8.26929 | 1.57249 | 0.00110505 | 1.63007e-05 | 2.61008e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.693 | 0.06195 | 1520.24ms | 4669 | 640 | 15490.3 | 7941.43 | 0.0994187 | 9.22827 | 39.072 | 7.81238 | 0.00971501 | 2.67723e-05 | 2.00792e-06 | 1(Win) | true |
| simdjson (ondemand) | 242.853 | 0.0615102 | 2564.58ms | 4669 | 320 | 40701.1 | 18335 | 0.0152566 | 21.2371 | 94.8042 | 19.3697 | 0.0500033 | 3.27961e-05 | 4.68516e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 570.759 | 0.0383961 | 1505.2ms | 4669 | 2560 | 22969.8 | 7801.37 | 0.00642957 | 9.04235 | 38.296 | 7.63418 | 0.0104952 | 4.75209e-05 | 1.19639e-05 | 1(Win) | true |
| simdjson (ondemand) | 245.862 | 0.0181954 | 2540.17ms | 4669 | 4890 | 53100.8 | 18110.6 | 0.169427 | 20.9145 | 94.0159 | 19.1902 | 0.050243 | 3.12727e-05 | 6.0881e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.305 | 0.0768325 | 1626.97ms | 7932 | 160 | 7492.87 | 8906.75 | 0.0213276 | 6.09337 | 24.357 | 4.87645 | 0.00529895 | 1.02433e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 413.22 | 0.0284235 | 2566.01ms | 7932 | 2560 | 69310.4 | 18306.3 | 0.0762783 | 12.4516 | 55.6612 | 11.2611 | 0.0303581 | 0.000118438 | 6.43655e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 864.166 | 0.0548782 | 1611.42ms | 7932 | 1280 | 29538 | 8753.58 | 0.0516842 | 5.98095 | 23.8999 | 4.77156 | 0.00568238 | 2.48203e-05 | 6.59906e-06 | 1(Win) | true |
| simdjson (ondemand) | 417.957 | 0.0365501 | 2547.05ms | 7932 | 1280 | 56013.1 | 18098.9 | 0.0652486 | 12.3086 | 55.2073 | 11.1576 | 0.0316367 | 2.07821e-05 | 5.41714e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4480.08 | 0.046896 | 813.3ms | 4669 | 4890 | 1062.33 | 993.89 | 0.0757232 | 1.19551 | 5.19576 | 0.739559 | 0.00154725 | 3.95508e-05 | 1.31398e-05 | 1(Win) | true |
| simdjson (ondemand) | 4363.38 | 0.0800133 | 816.592ms | 4669 | 4890 | 3260.13 | 1020.47 | 0.0157858 | 1.22553 | 5.57061 | 0.702299 | 0.00129357 | 2.09361e-05 | 3.10975e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4843.29 | 0.180798 | 806.849ms | 4669 | 1280 | 3536.43 | 919.356 | 0.0695603 | 1.10629 | 4.93639 | 0.682588 | 0.00124608 | 1.12109e-05 | 1.00396e-06 | 1(Win) | true |
| simdjson (ondemand) | 4662.07 | 0.090961 | 810.935ms | 4669 | 1280 | 966.074 | 955.092 | 0.0545074 | 1.14981 | 5.3112 | 0.644035 | 0.00113799 | 1.42228e-05 | 2.84456e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6405.85 | 0.0423376 | 828.796ms | 7932 | 4890 | 1222.29 | 1180.88 | 0.119135 | 0.837429 | 3.84468 | 0.434317 | 0.000729385 | 1.24525e-05 | 2.39768e-06 | 1(Win) | true |
| Jsonifier (generic) | 6277.6 | 0.0580758 | 830.106ms | 7932 | 640 | 313.437 | 1205.01 | 0.166216 | 0.847633 | 3.6852 | 0.463944 | 0.000889396 | 2.9548e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6807.45 | 0.112483 | 820.958ms | 7932 | 2560 | 3999.55 | 1111.22 | 0.0941227 | 0.788734 | 3.69201 | 0.400025 | 0.000641045 | 2.98928e-05 | 1.31489e-05 | 1(Win) | true |
| Jsonifier (generic) | 6769.32 | 0.0664821 | 822.115ms | 7932 | 640 | 353.236 | 1117.47 | 0.0456035 | 0.797615 | 3.53253 | 0.430408 | 0.00071132 | 5.71262e-06 | 1.96987e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3185.17 | 0.0682638 | 857.793ms | 4669 | 1280 | 1165.66 | 1397.95 | 0.0252107 | 1.66296 | 7.48147 | 1.32255 | 0.00153757 | 2.87803e-05 | 1.10436e-05 | 1(Win) | true |
| simdjson (ondemand) | 2587.26 | 0.223671 | 890.274ms | 4669 | 640 | 9483.51 | 1721.01 | 0.0356675 | 2.06789 | 9.48319 | 1.55365 | 0.00291718 | 3.24614e-05 | 1.53941e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3377.33 | 0.0527257 | 851.344ms | 4669 | 2560 | 1237.05 | 1318.41 | 0.0697942 | 1.57058 | 7.22082 | 1.2643 | 0.00141651 | 1.57287e-05 | 1.75693e-06 | 1(Win) | true |
| simdjson (ondemand) | 2673.46 | 0.0843786 | 882.468ms | 4669 | 2560 | 5055.98 | 1665.52 | 0.0641163 | 1.97151 | 9.22382 | 1.4954 | 0.0028136 | 9.20299e-06 | 1.00396e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4684.84 | 0.157574 | 878.67ms | 7932 | 80 | 517.888 | 1614.69 | 0.0487948 | 1.12731 | 5.0474 | 0.816944 | 0.000893533 | 7.87948e-06 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 3886.52 | 0.0458285 | 914.659ms | 7932 | 4890 | 3890.67 | 1946.36 | 0.0238491 | 1.33861 | 6.12822 | 0.930661 | 0.00165311 | 1.07767e-05 | 1.49533e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4857.66 | 0.149977 | 876.506ms | 7932 | 2560 | 13963.7 | 1557.24 | 0.0216525 | 1.07265 | 4.89397 | 0.782653 | 0.000789523 | 1.57097e-05 | 2.06836e-06 | 1(Win) | true |
| simdjson (ondemand) | 4083.4 | 0.14054 | 932.928ms | 7932 | 320 | 2169.05 | 1852.51 | 0.0420215 | 1.28406 | 5.97554 | 0.896369 | 0.00162672 | 1.4577e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 549.146 | 0.109754 | 1544.1ms | 4604 | 160 | 12321.2 | 7995.53 | 0.0025795 | 9.42125 | 37.1033 | 7.74707 | 0.00837451 | 4.88705e-05 | 1.22176e-05 | 1(Win) | true |
| simdjson (ondemand) | 536.561 | 0.102991 | 1542.32ms | 4604 | 320 | 22729.1 | 8183.07 | 0.0599538 | 9.47262 | 38.716 | 7.48892 | 0.0111561 | 3.59742e-05 | 1.15389e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 650.777 | 0.0717212 | 1488.3ms | 4604 | 320 | 7492.94 | 6746.89 | 0.384159 | 7.96259 | 30.7285 | 6.26868 | 0.00891209 | 4.27617e-05 | 2.71503e-06 | 1(Win) | true |
| simdjson (ondemand) | 647.699 | 0.0539689 | 1491.55ms | 4604 | 1280 | 17132.5 | 6778.95 | 0.102859 | 7.98207 | 32.4466 | 6.03345 | 0.0100398 | 5.29431e-05 | 1.35752e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2035.18 | 0.0972183 | 1611.96ms | 18245 | 80 | 5526.73 | 8549.51 | 0.0799114 | 2.54336 | 10.3289 | 2.00543 | 0.00245204 | 7.53631e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 1983.74 | 0.0364437 | 1614.81ms | 18245 | 4890 | 49965.8 | 8771.21 | 0.812179 | 2.57957 | 10.7568 | 1.91981 | 0.00302159 | 2.84135e-05 | 1.39994e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2268.75 | 0.0277443 | 1600.25ms | 18245 | 4890 | 22139.7 | 7669.33 | 0.069334 | 2.27127 | 9.09591 | 1.72237 | 0.00255569 | 1.44253e-05 | 4.56186e-06 | 1(Win) | true |
| simdjson (ondemand) | 2246.43 | 0.105071 | 1601.67ms | 18245 | 320 | 21194.2 | 7745.52 | 0.103554 | 2.30343 | 9.61829 | 1.65696 | 0.00294224 | 2.0211e-05 | 5.48095e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 323.051 | 0.0544552 | 2095.44ms | 4604 | 320 | 17529 | 13591.4 | 0.0134984 | 15.9896 | 66.7743 | 14.5406 | 0.0237171 | 0.000793468 | 0.000397073 | 1(Win) | true |
| simdjson (ondemand) | 241.541 | 0.0925377 | 2538.5ms | 4604 | 80 | 22636.8 | 18177.9 | 0.0248179 | 21.3607 | 105.179 | 22.0321 | 0.025391 | 9.2311e-05 | 3.25804e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 346.057 | 0.0314531 | 2096.83ms | 4604 | 1280 | 20385.1 | 12687.9 | 0.110515 | 14.9243 | 62.543 | 13.5838 | 0.0213542 | 8.39963e-05 | 3.30894e-05 | 1(Win) | true |
| simdjson (ondemand) | 256.332 | 0.0407638 | 2528.47ms | 4604 | 640 | 31202.8 | 17129 | 0.0621408 | 20.1374 | 100.921 | 21.0734 | 0.0235437 | 5.76944e-05 | 1.2557e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1190.73 | 0.0443125 | 2194.16ms | 18245 | 1280 | 53669.4 | 14612.8 | 0.0216908 | 4.33506 | 17.8653 | 3.75588 | 0.00543792 | 4.86435e-05 | 2.40648e-05 | 1(Win) | true |
| simdjson (ondemand) | 912.506 | 0.0771962 | 2631.53ms | 18245 | 640 | 138672 | 19068.1 | 0.155499 | 5.61953 | 27.5252 | 5.58772 | 0.00642034 | 2.45787e-05 | 9.50603e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1275.06 | 0.0462985 | 2195.17ms | 18245 | 1280 | 51094.2 | 13646.3 | 0.077485 | 4.03452 | 16.7989 | 3.51483 | 0.00510816 | 2.77473e-05 | 1.42162e-05 | 1(Win) | true |
| simdjson (ondemand) | 978.276 | 0.0480501 | 2633.99ms | 18245 | 640 | 46744.9 | 17786.2 | 0.0905431 | 5.27577 | 26.4497 | 5.34541 | 0.00634497 | 2.25233e-05 | 1.19039e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4031.6 | 0.0988864 | 836.369ms | 4604 | 2560 | 2969.14 | 1089.08 | 0.0266425 | 1.32146 | 6.24957 | 0.926152 | 0.000438562 | 1.76477e-05 | 2.96956e-06 | 1(Win) | true |
| simdjson (ondemand) | 3800.21 | 0.0846591 | 832.852ms | 4604 | 160 | 153.082 | 1155.39 | 0.0996329 | 1.40354 | 7.04909 | 0.976542 | 0.000435762 | 9.50261e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4153.45 | 0.0976363 | 824.12ms | 4604 | 80 | 85.2247 | 1057.12 | 0.0661735 | 1.28671 | 6.17029 | 0.907472 | 0.000434405 | 1.08601e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3904.67 | 0.0615653 | 829.098ms | 4604 | 2560 | 1226.92 | 1124.48 | 0.0371909 | 1.36563 | 6.96785 | 0.957863 | 0.000442889 | 2.12112e-05 | 3.2241e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10048.9 | 0.0764443 | 892.346ms | 18245 | 160 | 280.327 | 1731.52 | 0.0883558 | 0.524855 | 2.46424 | 0.26325 | 0.000110304 | 1.19896e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9651.17 | 0.0166853 | 898.073ms | 18245 | 1280 | 115.825 | 1802.87 | 0.201312 | 0.545829 | 2.80269 | 0.283968 | 0.000113987 | 5.86633e-06 | 1.7128e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10243.7 | 0.101233 | 889.104ms | 18245 | 4890 | 14458.7 | 1698.59 | 0.0539883 | 0.513392 | 2.44423 | 0.258537 | 0.000110135 | 1.06144e-05 | 2.53312e-06 | 1(Win) | true |
| simdjson (ondemand) | 9752.37 | 0.0461618 | 896.006ms | 18245 | 1280 | 868.247 | 1784.16 | 0.00678762 | 0.540241 | 2.78219 | 0.279255 | 0.000146144 | 8.26425e-06 | 1.24178e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2541.1 | 0.238614 | 891.966ms | 4604 | 640 | 10879.2 | 1727.88 | 0.346453 | 2.07065 | 9.24066 | 1.66942 | 0.00109551 | 1.79871e-05 | 1.35752e-06 | 1(Win) | true |
| simdjson (ondemand) | 1852.1 | 0.118921 | 952.705ms | 4604 | 320 | 2543.37 | 2370.67 | 0.207448 | 2.82912 | 13.3658 | 2.37142 | 0.00130525 | 1.28964e-05 | 1.35752e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2551.81 | 0.157186 | 890.851ms | 4604 | 640 | 4681.43 | 1720.62 | 0.0254333 | 2.06226 | 9.16182 | 1.6503 | 0.00108601 | 2.78291e-05 | 1.15389e-05 | 1(Win) | true |
| simdjson (ondemand) | 1887.46 | 0.0693355 | 953.505ms | 4604 | 2560 | 6659.88 | 2326.26 | 0.092539 | 2.76737 | 13.2848 | 2.35274 | 0.00136116 | 2.90169e-05 | 6.10882e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7758.41 | 0.0923983 | 948.487ms | 18245 | 1280 | 5496.43 | 2242.7 | 0.0795573 | 0.670858 | 3.22077 | 0.452234 | 0.000439718 | 1.66141e-05 | 8.26425e-06 | 1(Win) | true |
| simdjson (ondemand) | 5760.25 | 0.0820906 | 1024.12ms | 18245 | 1280 | 7870.48 | 3020.66 | 0.188512 | 0.90249 | 4.39682 | 0.635955 | 0.000339434 | 6.16607e-06 | 4.71019e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7946.96 | 0.0438329 | 939.354ms | 18245 | 4890 | 4503.97 | 2189.49 | 0.0714983 | 0.658905 | 3.20088 | 0.44741 | 0.000329911 | 9.11251e-06 | 7.39761e-07 | 1(Win) | true |
| simdjson (ondemand) | 5789.23 | 0.0649061 | 1019.35ms | 18245 | 4890 | 18609.2 | 3005.54 | 0.0872015 | 0.900804 | 4.37638 | 0.631242 | 0.000388879 | 9.00042e-06 | 1.00876e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1339.83 | 0.0714967 | 1074.57ms | 4926 | 640 | 4022.01 | 3506.27 | 0.0624718 | 3.88715 | 16.5483 | 3.17519 | 0.00458219 | 3.23538e-05 | 1.90317e-06 | 1(Win) | true |
| simdjson (ondemand) | 1085.84 | 0.0607064 | 1154.86ms | 4926 | 4890 | 33731.2 | 4326.4 | 0.129102 | 4.78207 | 18.447 | 3.43017 | 0.00348508 | 4.74923e-05 | 1.61075e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1665.53 | 0.105015 | 1048.08ms | 4926 | 4890 | 42903.8 | 2820.6 | 0.105762 | 3.12139 | 13.962 | 2.59968 | 0.00381511 | 4.10575e-05 | 6.22713e-06 | 1(Win) | true |
| simdjson (ondemand) | 1266.82 | 0.0678943 | 1127.38ms | 4926 | 1280 | 8113.96 | 3708.33 | 0.0174829 | 4.10867 | 15.8975 | 2.86703 | 0.00380078 | 4.18697e-05 | 1.42738e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2060.4 | 0.0530148 | 1101.44ms | 8150 | 640 | 2559.7 | 3772.3 | 0.00890457 | 2.52714 | 10.5704 | 1.9346 | 0.00264225 | 7.59202e-05 | 4.90798e-05 | 1(Win) | true |
| simdjson (ondemand) | 1720.65 | 0.0655547 | 1174.04ms | 8150 | 1280 | 11224 | 4517.15 | 0.033339 | 3.01574 | 11.7036 | 2.09755 | 0.00243184 | 5.19555e-05 | 2.55943e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2512.72 | 0.0947698 | 1074.11ms | 8150 | 640 | 5499.82 | 3093.25 | 0.116873 | 2.07714 | 9.01092 | 1.58822 | 0.0023217 | 2.28144e-05 | 8.81902e-06 | 1(Win) | true |
| simdjson (ondemand) | 1989.93 | 0.032446 | 1145.47ms | 8150 | 4890 | 7853.65 | 3905.9 | 0.169859 | 2.60926 | 10.1675 | 1.75914 | 0.00273717 | 2.73753e-05 | 1.43024e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 799.266 | 0.0513591 | 1308.19ms | 4926 | 2560 | 23328.2 | 5877.64 | 0.00284455 | 6.48995 | 27.4271 | 5.50569 | 0.00936429 | 0.000117124 | 6.71659e-05 | 1(Win) | true |
| simdjson (ondemand) | 499.343 | 0.0218006 | 1665.52ms | 4926 | 4890 | 20570.2 | 9407.97 | 0.096567 | 10.3364 | 45.3924 | 9.09217 | 0.0190933 | 6.23959e-05 | 2.45349e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 915.375 | 0.169344 | 1277.23ms | 4926 | 160 | 12085.1 | 5132.11 | 0.142647 | 5.66706 | 24.8238 | 4.93037 | 0.00952218 | 5.07511e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (ondemand) | 538.089 | 0.0600559 | 1634.12ms | 4926 | 320 | 8797.13 | 8730.52 | 0.0518207 | 9.61765 | 42.8473 | 8.53005 | 0.0184353 | 0.000111652 | 6.40733e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1242.34 | 0.0387309 | 1351.87ms | 8150 | 2560 | 15031.2 | 6256.32 | 0.0092086 | 4.16961 | 17.4361 | 3.47657 | 0.00596832 | 3.42216e-05 | 9.63382e-06 | 1(Win) | true |
| simdjson (ondemand) | 814.369 | 0.0663734 | 1673.98ms | 8150 | 320 | 12841.4 | 9544.13 | 0.0411078 | 6.34753 | 27.7521 | 5.46871 | 0.0132431 | 7.05521e-05 | 4.29448e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1407.88 | 0.0309074 | 1320.37ms | 8150 | 4890 | 14237.1 | 5520.69 | 0.0280842 | 3.6832 | 15.8741 | 3.13239 | 0.00546594 | 3.46017e-05 | 9.10836e-06 | 1(Win) | true |
| simdjson (ondemand) | 882.998 | 0.0459225 | 1647.06ms | 8150 | 1280 | 20915 | 8802.34 | 0.115025 | 5.85785 | 26.2214 | 5.13166 | 0.0126424 | 1.87883e-05 | 1.24617e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2516.23 | 0.152996 | 904.377ms | 4926 | 80 | 652.734 | 1867 | 0.0120529 | 2.08547 | 9.33151 | 1.60495 | 0.00160881 | 2.79131e-05 | 1.77629e-05 | 1(Win) | true |
| simdjson (ondemand) | 2120.95 | 0.0851062 | 943.99ms | 4926 | 80 | 284.276 | 2214.95 | 0.0180558 | 2.47361 | 9.99513 | 1.64373 | 0.00285221 | 5.07511e-06 | 2.53756e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2749.56 | 0.113678 | 909.58ms | 4926 | 640 | 2414.33 | 1708.57 | 0.0274278 | 1.91523 | 8.76492 | 1.46691 | 0.00177788 | 1.52253e-05 | 2.22036e-06 | 1(Win) | true |
| simdjson (ondemand) | 2256.44 | 0.0368065 | 934.959ms | 4926 | 2560 | 1503.25 | 2081.95 | 0.0957467 | 2.32678 | 9.42408 | 1.50467 | 0.00246175 | 2.00626e-05 | 1.58597e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3606.32 | 0.0427482 | 932.746ms | 8150 | 4890 | 4150.8 | 2155.23 | 0.178931 | 1.4504 | 6.26479 | 1.00503 | 0.00144896 | 1.3374e-05 | 1.48042e-06 | 1(Win) | true |
| simdjson (ondemand) | 3351.44 | 0.0835898 | 952.889ms | 8150 | 30 | 112.74 | 2319.13 | 0.043101 | 1.56676 | 6.48577 | 0.995706 | 0.00117382 | 2.45399e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3898.86 | 0.0502097 | 925.914ms | 8150 | 2560 | 2564.82 | 1993.52 | 0.235795 | 1.34657 | 5.92282 | 0.921595 | 0.0015221 | 1.53854e-05 | 2.06097e-06 | 1(Win) | true |
| simdjson (ondemand) | 3604.65 | 0.0231072 | 943.251ms | 8150 | 4890 | 1213.93 | 2156.23 | 0.022026 | 1.45577 | 6.14061 | 0.911657 | 0.00113649 | 1.68868e-05 | 1.35496e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1904.72 | 0.0319554 | 965.565ms | 4926 | 4890 | 3037.57 | 2466.41 | 0.126564 | 2.74542 | 12.3382 | 2.2905 | 0.00349396 | 4.29672e-05 | 1.43224e-05 | 1(Win) | true |
| simdjson (ondemand) | 1476.67 | 0.0593715 | 1037.29ms | 4926 | 1280 | 4566.53 | 3181.34 | 0.255527 | 3.53007 | 13.9982 | 2.49574 | 0.00661477 | 5.58262e-05 | 2.77545e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2004.29 | 0.059615 | 961.488ms | 4926 | 320 | 624.783 | 2343.87 | 0.0425492 | 2.61466 | 11.7343 | 2.14576 | 0.00493681 | 2.47412e-05 | 6.97828e-06 | 1(Win) | true |
| simdjson (ondemand) | 1560.78 | 0.0336645 | 1032.61ms | 4926 | 2560 | 2628.39 | 3009.9 | 0.029192 | 3.34685 | 13.393 | 2.34998 | 0.00732688 | 4.87687e-05 | 1.57804e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2802.94 | 0.093579 | 998.931ms | 8150 | 640 | 4309.47 | 2772.96 | 0.0561539 | 1.86004 | 8.13362 | 1.4362 | 0.00161522 | 1.64877e-05 | 3.45092e-06 | 1(Win) | true |
| simdjson (ondemand) | 2354.09 | 0.0548479 | 1053.51ms | 8150 | 80 | 262.349 | 3301.68 | 0.101567 | 2.21441 | 8.94626 | 1.51926 | 0.00419479 | 1.07362e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2944.65 | 0.0377828 | 992.611ms | 8150 | 2560 | 2546.1 | 2639.51 | 0.125372 | 1.77283 | 7.76859 | 1.34871 | 0.00251198 | 1.00652e-05 | 2.06097e-06 | 1(Win) | true |
| simdjson (ondemand) | 2474.32 | 0.0626931 | 1044.65ms | 8150 | 80 | 310.266 | 3141.25 | 0.131939 | 2.1124 | 8.58049 | 1.43117 | 0.00457822 | 1.99387e-05 | 4.60123e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2179.05 | 0.062755 | 842.888ms | 2821 | 4890 | 2935.46 | 1234.63 | 0.0904389 | 2.42071 | 9.1067 | 1.62921 | 0.000361371 | 7.45214e-05 | 1.92103e-05 | 1(Win) | true |
| simdjson (ondemand) | 2054.53 | 0.0661543 | 849.016ms | 2821 | 320 | 240.129 | 1309.45 | 0.0021478 | 2.5849 | 9.486 | 1.55335 | 0.000367777 | 5.20649e-05 | 4.43105e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2386.21 | 0.130545 | 836.156ms | 2821 | 160 | 346.601 | 1127.44 | 0.216109 | 2.23631 | 8.55229 | 1.48706 | 0.000361131 | 6.42503e-05 | 4.43105e-06 | 1(Win) | true |
| simdjson (ondemand) | 2183.18 | 0.0694212 | 845.127ms | 2821 | 1280 | 936.742 | 1232.29 | 0.0254292 | 2.43851 | 9.07267 | 1.44913 | 0.000706753 | 4.34797e-05 | 2.49247e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2796.65 | 0.0813256 | 847.786ms | 3770 | 160 | 174.897 | 1285.59 | 0.0393942 | 1.89739 | 7.22546 | 1.22653 | 0.00026691 | 2.32095e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2644.76 | 0.119772 | 856.16ms | 3770 | 160 | 424.17 | 1359.42 | 0.227635 | 2.00691 | 7.45809 | 1.17613 | 0.000303382 | 8.12334e-05 | 1.98939e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3047.12 | 0.0588469 | 844.064ms | 3770 | 4890 | 2357.54 | 1179.92 | 0.302255 | 1.75149 | 6.81061 | 1.12016 | 0.000266825 | 7.10051e-05 | 2.6254e-05 | 1(Win) | true |
| simdjson (ondemand) | 2801.03 | 0.122567 | 856.758ms | 3770 | 160 | 396.019 | 1283.58 | 0.0170451 | 1.8981 | 7.14881 | 1.09814 | 0.00028183 | 5.30504e-05 | 8.28912e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 804.768 | 0.0530379 | 1060.3ms | 2821 | 320 | 1005.97 | 3342.97 | 0.0181318 | 6.47819 | 26.3676 | 4.95427 | 0.00229861 | 4.65261e-05 | 2.21553e-06 | 1(Win) | true |
| simdjson (ondemand) | 397.62 | 0.0363903 | 1403.48ms | 2821 | 2560 | 15519.6 | 6766.05 | 0.0471515 | 13.0153 | 58.9309 | 11.9 | 0.0102692 | 0.000148025 | 7.17277e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 838.558 | 0.0846691 | 1048.11ms | 2821 | 640 | 4722.48 | 3208.27 | 0.0547714 | 6.2179 | 25.8107 | 4.81141 | 0.00190535 | 5.37265e-05 | 1.93859e-05 | 1(Win) | true |
| simdjson (ondemand) | 400.334 | 0.0493063 | 1397.09ms | 2821 | 2560 | 28106.5 | 6720.18 | 0.034899 | 12.8929 | 58.5154 | 11.7948 | 0.0116873 | 6.23117e-05 | 1.42625e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1011.23 | 0.0869007 | 1077.07ms | 3770 | 80 | 763.688 | 3555.41 | 0.0341146 | 5.14954 | 20.7719 | 3.92732 | 0.00136605 | 7.29443e-05 | 2.98408e-05 | 1(Win) | true |
| simdjson (ondemand) | 539.143 | 0.0332835 | 1387.79ms | 3770 | 2560 | 12611.6 | 6668.64 | 0.218416 | 9.60401 | 43.7944 | 8.76764 | 0.00874161 | 4.32071e-05 | 9.22165e-06 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1043.87 | 0.0442804 | 1071.23ms | 3770 | 2560 | 5954.55 | 3444.24 | 0.131756 | 5.01372 | 20.3553 | 3.82044 | 0.00153359 | 5.61588e-05 | 1.55421e-05 | 1(Win) | true |
| simdjson (ondemand) | 545.27 | 0.0314066 | 1383.92ms | 3770 | 2560 | 10978.5 | 6593.71 | 0.0420796 | 9.50002 | 43.4836 | 8.68886 | 0.00927802 | 5.98889e-05 | 2.35204e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5445.8 | 0.138638 | 762.231ms | 2821 | 4890 | 2293.82 | 494.017 | 0.0360115 | 1.02116 | 3.90961 | 0.502659 | 0.000711288 | 2.50821e-05 | 7.32166e-06 | 1(Win) | true |
| simdjson (ondemand) | 5371.77 | 0.0826803 | 762.139ms | 2821 | 4890 | 838.463 | 500.825 | 0.2811 | 1.03805 | 4.15881 | 0.455158 | 0.000424801 | 2.92141e-05 | 2.6097e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5740.26 | 0.124916 | 762.146ms | 2821 | 320 | 109.681 | 468.675 | 0.136207 | 0.992042 | 3.838 | 0.485289 | 0.000631425 | 2.76941e-05 | 9.96987e-06 | 1(Win) | true |
| simdjson (ondemand) | 5490.44 | 0.0511937 | 769.939ms | 2821 | 2560 | 161.088 | 490 | 0.025437 | 1.02987 | 4.08401 | 0.437788 | 0.000412226 | 1.74473e-05 | 9.69293e-07 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6639.22 | 0.0714802 | 766.411ms | 3770 | 4890 | 732.706 | 541.533 | 0.300995 | 0.832143 | 3.36313 | 0.390982 | 0.000265577 | 1.86599e-05 | 4.06828e-06 | 1(Win) | true |
| simdjson (ondemand) | 6514.63 | 0.0384411 | 768.307ms | 3770 | 2560 | 115.222 | 551.889 | 0.103867 | 0.848275 | 3.47639 | 0.357029 | 0.000283592 | 3.45035e-05 | 9.01442e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6731.81 | 0.114336 | 766.822ms | 3770 | 320 | 119.325 | 534.084 | 0.0707486 | 0.822692 | 3.30955 | 0.377984 | 0.000265252 | 1.9065e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6662.23 | 0.13316 | 766.862ms | 3770 | 2560 | 1322.01 | 539.662 | 0.00434281 | 0.829796 | 3.42042 | 0.344032 | 0.000309702 | 1.6371e-05 | 3.73011e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3978.9 | 0.123239 | 784.929ms | 2821 | 2560 | 1777.53 | 676.145 | 0.00756875 | 1.36807 | 5.50585 | 0.877349 | 0.000902135 | 3.65562e-05 | 1.08007e-05 | 1(Win) | true |
| simdjson (ondemand) | 3475.97 | 0.0582687 | 794.04ms | 2821 | 320 | 65.084 | 773.975 | 0.166626 | 1.55998 | 6.26693 | 0.917405 | 0.00076768 | 2.43708e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4058.39 | 0.105027 | 783.134ms | 2821 | 4890 | 2370.32 | 662.903 | 0.15958 | 1.34468 | 5.43424 | 0.859625 | 0.00085098 | 1.70355e-05 | 4.05953e-06 | 1(Win) | true |
| simdjson (ondemand) | 3563.42 | 0.0669197 | 789.697ms | 2821 | 2560 | 653.462 | 754.982 | 0.00905362 | 1.52242 | 6.19213 | 0.900036 | 0.000762556 | 2.10475e-05 | 6.23117e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4886.16 | 0.0433406 | 785.985ms | 3770 | 1280 | 130.181 | 735.824 | 0.013061 | 1.11272 | 4.56764 | 0.67878 | 0.000600133 | 1.65782e-05 | 2.48674e-06 | 1(Win) | true |
| simdjson (ondemand) | 4369.52 | 0.110869 | 797.513ms | 3770 | 80 | 66.5766 | 822.825 | 0.0607294 | 1.23789 | 5.06393 | 0.70504 | 0.000573607 | 1.98939e-05 | 3.31565e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5017.29 | 0.0691414 | 787.202ms | 3770 | 640 | 157.109 | 716.592 | 0.0098111 | 1.0839 | 4.51406 | 0.665517 | 0.000790368 | 2.11373e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4461.45 | 0.066191 | 795.575ms | 3770 | 4890 | 1391.35 | 805.871 | 0.0320972 | 1.21178 | 5.00796 | 0.692043 | 0.000569397 | 1.69241e-05 | 4.88194e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5860.04 | 0.0807933 | 5260.06ms | 277673 | 160 | 213273 | 45189.1 | 0.0337081 | 0.878991 | 4.00578 | 0.653639 | 0.00301909 | 8.05804e-06 | 7.11268e-06 | 1(Win) | true |
| simdjson (ondemand) | 4535.62 | 0.0862099 | 6589.92ms | 277673 | 320 | 810697 | 58384.4 | 0.124995 | 1.12446 | 4.49958 | 0.721679 | 0.00397192 | 1.00163e-06 | 1.46305e-07 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4486.02 | 0.08913 | 6994.05ms | 10548466 | 80 | 3.19591e+08 | 2.24248e+06 | 0.155885 | 1.14226 | 4.00436 | 0.654211 | 0.0115636 | 0.017241 | 0.000326987 | 1(Win) | true |
| simdjson (ondemand) | 3853.87 | 0.0635548 | 8202.46ms | 10548466 | 160 | 4.40354e+08 | 2.61031e+06 | 0.705752 | 1.33157 | 4.49725 | 0.722092 | 0.0102688 | 0.0174891 | 6.11671e-05 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4016.37 | 0.0841621 | 5700.05ms | 16002592 | 80 | 8.18157e+08 | 3.79977e+06 | 0.181014 | 1.2671 | 7.26695 | 1.14523 | 0.000760923 | 0.0333136 | 0.00342426 | 1(Win) | true |
| simdjson (ondemand) | 3250.71 | 0.0938251 | 7084.64ms | 16002592 | 80 | 1.55221e+09 | 4.69474e+06 | 0.14438 | 1.56869 | 7.97997 | 1.16739 | 0.00120454 | 0.0367668 | 0.00267375 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3236.96 | 0.0838603 | 7071.32ms | 16002591 | 80 | 1.25057e+09 | 4.71469e+06 | 0.466096 | 1.56376 | 7.3928 | 1.22025 | 0.000678364 | 0.036642 | 0.00222013 | 1(Win) | true |
| simdjson (ondemand) | 1745.57 | 0.0853081 | 6133.46ms | 16002591 | 30 | 1.66881e+09 | 8.74283e+06 | 0.307876 | 2.90601 | 12.9572 | 2.70942 | 0.00126685 | 0.0537986 | 0.00600471 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18983.3 | 0.0607817 | 5180.4ms | 16197086 | 160 | 3.91378e+07 | 813703 | 0.0132537 | 0.266005 | 1.40124 | 0.0671858 | 8.10582e-05 | 0.0157348 | 0.000158766 | 1(Win) | true |
| simdjson (ondemand) | 17771.1 | 0.544211 | 5511.55ms | 16197086 | 30 | 6.71279e+08 | 869208 | 0.413504 | 0.284052 | 1.3372 | 0.0735079 | 8.96519e-05 | 0.0157238 | 0.000300173 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18882.4 | 0.0828751 | 5208.28ms | 16197085 | 40 | 1.83851e+07 | 818049 | 0.116169 | 0.267633 | 1.40268 | 0.0683635 | 9.91274e-05 | 0.0157505 | 0.000314526 | 1(Win) | true |
| simdjson (ondemand) | 16910.6 | 0.134841 | 5857.38ms | 16197085 | 320 | 4.85457e+08 | 913434 | 0.313927 | 0.299761 | 1.41971 | 0.0991946 | 0.000100349 | 0.015752 | 0.000100669 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2070.55 | 0.191277 | 7867ms | 4212000 | 40 | 5.50792e+08 | 1.94e+06 | 0.0556735 | 2.44149 | 11.3164 | 2.01977 | 0.0116455 | 0.0663117 | 0.0078696 | 1(Win) | true |
| simdjson (ondemand) | 1534.28 | 0.136873 | 9972.25ms | 4212000 | 30 | 3.85236e+08 | 2.61809e+06 | 0.0725572 | 3.30921 | 12.6013 | 2.34243 | 0.012492 | 0.0662127 | 0.00575204 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1528.03 | 0.123625 | 9997.2ms | 4212000 | 40 | 4.22462e+08 | 2.6288e+06 | 0.343174 | 3.31925 | 15.1672 | 2.91952 | 0.012493 | 0.0665467 | 0.00667105 | 1(Win) | true |
| simdjson (ondemand) | 1325.11 | 0.139076 | 5471.97ms | 4212000 | 40 | 7.10948e+08 | 3.03135e+06 | 0.403867 | 3.85086 | 15.6689 | 2.91446 | 0.0133619 | 0.066385 | 0.00288332 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1941.72 | 0.0669079 | 8268.88ms | 4211999 | 160 | 3.06532e+08 | 2.06872e+06 | 0.00618508 | 2.60952 | 12.1259 | 2.20749 | 0.0122862 | 0.0680927 | 0.00129871 | 1(Win) | true |
| simdjson (ondemand) | 1274.57 | 0.0942599 | 5632.22ms | 4211999 | 40 | 3.52989e+08 | 3.15155e+06 | 0.321895 | 3.98492 | 15.0747 | 3.10977 | 0.0129133 | 0.0694323 | 0.00346324 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1512.25 | 0.0606929 | 10062.9ms | 4211999 | 80 | 2.0792e+08 | 2.65622e+06 | 0.1719 | 3.34435 | 15.2564 | 2.94822 | 0.0127913 | 0.0680875 | 0.00112784 | 1(Win) | true |
| simdjson (ondemand) | 1123.06 | 0.101765 | 6253.17ms | 4211999 | 40 | 5.29939e+08 | 3.57672e+06 | 0.414378 | 4.54904 | 18.1423 | 3.68178 | 0.0140858 | 0.069752 | 0.00249678 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1664.26 | 0.120808 | 8719.68ms | 4525120 | 30 | 2.94394e+08 | 2.59303e+06 | 0.0296001 | 3.06316 | 15.2795 | 2.75502 | 0.00956783 | 0.0774521 | 0.000952726 | 1(Win) | true |
| simdjson (ondemand) | 1408.35 | 0.0824122 | 10202.4ms | 4525120 | 80 | 5.10163e+08 | 3.06421e+06 | 0.173854 | 3.61084 | 16.3054 | 2.60332 | 0.0149448 | 0.0769058 | 0.00168662 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.502 | 0.0689809 | 8259.87ms | 4525120 | 80 | 1.04033e+09 | 5.22772e+06 | 0.185043 | 6.1634 | 30.694 | 6.251 | 0.0151679 | 0.0779186 | 0.00369576 | 1(Win) | true |
| simdjson (ondemand) | 626.53 | 0.0952577 | 5039.06ms | 4525120 | 30 | 1.29151e+09 | 6.88792e+06 | 0.335103 | 8.12515 | 41.228 | 8.08556 | 0.0258047 | 0.0772245 | 0.00492836 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1454.88 | 0.110361 | 9911.47ms | 4525119 | 40 | 4.28642e+08 | 2.96622e+06 | 0.157554 | 3.48402 | 17.4931 | 3.30814 | 0.0102445 | 0.0776413 | 0.00263862 | 1(Win) | true |
| simdjson (ondemand) | 1023.53 | 0.136474 | 6658.06ms | 4525119 | 40 | 1.32441e+09 | 4.2163e+06 | 0.0218826 | 4.96368 | 21.517 | 4.14794 | 0.0177141 | 0.0924875 | 0.00302303 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 824.919 | 0.0838493 | 8216.26ms | 4525119 | 40 | 7.69655e+08 | 5.23141e+06 | 0.20989 | 6.16604 | 30.4225 | 6.25074 | 0.0152252 | 0.0781397 | 0.00201872 | 1(Win) | true |
| simdjson (ondemand) | 542.904 | 0.116676 | 5806.87ms | 4525119 | 30 | 2.58045e+09 | 7.9489e+06 | 0.393967 | 9.40773 | 46.4391 | 9.63005 | 0.0283217 | 0.0931309 | 0.0123681 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.83 | 0.0998922 | 9854.26ms | 4203059 | 160 | 1.41624e+09 | 2.97836e+06 | 0.0973129 | 3.77928 | 17.4233 | 3.23825 | 0.0141748 | 0.0887702 | 0.00227005 | 1(Win) | true |
| simdjson (ondemand) | 1031.11 | 0.146727 | 6167.71ms | 4203059 | 30 | 9.76038e+08 | 3.88743e+06 | 0.073447 | 4.94053 | 19.3013 | 3.6176 | 0.021442 | 0.088865 | 0.0025707 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.731 | 0.115974 | 7745.74ms | 4203059 | 40 | 1.28637e+09 | 4.88983e+06 | 0.562527 | 6.24103 | 27.6901 | 5.59929 | 0.0221059 | 0.0885769 | 0.0185928 | 1(Win) | true |
| simdjson (ondemand) | 751.313 | 0.0587864 | 8420.62ms | 4203059 | 80 | 7.86925e+08 | 5.33512e+06 | 0.0950206 | 6.73677 | 27.1249 | 5.21161 | 0.0264916 | 0.0880991 | 0.0120072 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1204.91 | 0.156386 | 5370.55ms | 4203058 | 30 | 8.11973e+08 | 3.32668e+06 | 0.530995 | 4.22069 | 19.5471 | 3.77044 | 0.0155551 | 0.0880988 | 0.00793116 | 1(Win) | true |
| simdjson (ondemand) | 816.738 | 0.10362 | 7704.88ms | 4203058 | 80 | 2.06891e+09 | 4.90775e+06 | 0.521209 | 6.22211 | 24.4107 | 5.1822 | 0.0226459 | 0.104197 | 0.00485306 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 767.161 | 0.110055 | 8268.05ms | 4203058 | 40 | 1.32262e+09 | 5.22491e+06 | 0.662806 | 6.6794 | 29.8144 | 6.13158 | 0.0240868 | 0.088251 | 0.00450384 | 1(Win) | true |
| simdjson (ondemand) | 637.649 | 0.134821 | 9812.05ms | 4203058 | 30 | 2.1548e+09 | 6.28614e+06 | 0.575492 | 7.99849 | 32.2342 | 6.77609 | 0.0274741 | 0.10336 | 0.00227476 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1738.35 | 0.126179 | 7449.59ms | 4197496 | 40 | 3.37709e+08 | 2.30278e+06 | 0.0254023 | 2.92316 | 14.6094 | 2.8874 | 0.000515945 | 0.080757 | 0.000988262 | 1(Win) | true |
| simdjson (ondemand) | 1465.54 | 0.0775658 | 8817.92ms | 4197496 | 80 | 3.59102e+08 | 2.73145e+06 | 0.718669 | 3.47119 | 16.5291 | 2.70204 | 0.00539609 | 0.0813066 | 0.000523369 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 842.614 | 0.106403 | 7315.91ms | 4197496 | 80 | 2.0442e+09 | 4.75074e+06 | 0.242851 | 6.00953 | 30.3192 | 5.40528 | 0.0105933 | 0.0795177 | 0.00056093 | 1(Win) | true |
| Jsonifier (generic) | 791.737 | 0.103602 | 7718.89ms | 4197496 | 30 | 8.23141e+08 | 5.05603e+06 | 0.572515 | 6.3935 | 27.699 | 5.68614 | 0.000709629 | 0.0793489 | 0.00084359 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1573.84 | 0.0448612 | 8258.42ms | 4197495 | 160 | 2.08315e+08 | 2.54349e+06 | 0.12897 | 3.21192 | 16.6024 | 3.38168 | 0.000752977 | 0.083584 | 0.00112736 | 1(Win) | true |
| simdjson (ondemand) | 1023.7 | 0.230198 | 6100.43ms | 4197495 | 30 | 2.43083e+09 | 3.91035e+06 | 0.0798038 | 4.98593 | 22.2209 | 4.47951 | 0.00833446 | 0.102867 | 0.0022722 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 791.888 | 0.110136 | 7794.71ms | 4197495 | 40 | 1.23985e+09 | 5.05506e+06 | 0.0385978 | 6.4113 | 27.6257 | 5.73487 | 0.000938947 | 0.083573 | 0.00164782 | 1(Win) | true |
| simdjson (ondemand) | 663.726 | 0.133578 | 9217.86ms | 4197495 | 80 | 5.19235e+09 | 6.03117e+06 | 0.0904506 | 7.63315 | 36.0099 | 7.18262 | 0.0167827 | 0.103093 | 0.012335 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1561.76 | 0.116414 | 10109.2ms | 4506447 | 40 | 4.10494e+08 | 2.75181e+06 | 0.0382387 | 3.24122 | 15.2693 | 2.85088 | 0.00869347 | 0.0808973 | 0.00287212 | 1(Win) | true |
| simdjson (ondemand) | 1160.74 | 0.100643 | 6328.06ms | 4506447 | 80 | 1.11086e+09 | 3.70253e+06 | 0.234979 | 4.37959 | 17.1579 | 3.15325 | 0.0133964 | 0.0788828 | 0.00198667 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 867.534 | 0.0753414 | 8212.81ms | 4506447 | 40 | 5.57215e+08 | 4.95391e+06 | 0.0990603 | 5.82699 | 26.5409 | 5.387 | 0.0110545 | 0.0812078 | 0.0123656 | 1(Win) | true |
| simdjson (ondemand) | 556.187 | 0.0934197 | 5767.97ms | 4506447 | 30 | 1.56324e+09 | 7.72705e+06 | 0.368056 | 9.09943 | 40.1281 | 7.92924 | 0.0260565 | 0.0791717 | 0.0183486 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1396.05 | 0.123762 | 5320.38ms | 4506446 | 40 | 5.8063e+08 | 3.07846e+06 | 0.455639 | 3.63011 | 16.9 | 3.26103 | 0.011305 | 0.0813363 | 0.00524464 | 1(Win) | true |
| simdjson (ondemand) | 924.238 | 0.329723 | 7733.38ms | 4506446 | 30 | 7.05215e+09 | 4.64997e+06 | 0.168479 | 5.4686 | 21.2216 | 4.4134 | 0.013439 | 0.0886097 | 0.00902644 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 865.089 | 0.348183 | 8256.42ms | 4506446 | 80 | 2.39361e+10 | 4.96791e+06 | 0.0532283 | 5.89142 | 26.3603 | 5.39438 | 0.0109463 | 0.081368 | 0.00647726 | 1(Win) | true |
| simdjson (ondemand) | 494.425 | 0.178939 | 6443.82ms | 4506446 | 40 | 9.6769e+09 | 8.69228e+06 | 0.23855 | 10.2953 | 44.192 | 9.18949 | 0.0279526 | 0.088907 | 0.0122648 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2019.41 | 0.273295 | 6987.06ms | 4219120 | 160 | 4.74436e+09 | 1.99249e+06 | 0.146993 | 2.49557 | 9.1929 | 1.59761 | 0.0146913 | 0.0572806 | 0.000462245 | 1(Win) | true |
| simdjson (ondemand) | 1817.25 | 0.364996 | 7643.85ms | 4219120 | 80 | 5.22491e+09 | 2.21415e+06 | 0.0696555 | 2.7728 | 9.42865 | 1.53537 | 0.0157463 | 0.0543795 | 0.000380198 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 720.792 | 0.202215 | 8867.79ms | 4219120 | 40 | 5.09693e+09 | 5.58228e+06 | 0.760127 | 7.06098 | 27.3297 | 5.16365 | 0.0203271 | 0.0579654 | 0.00187758 | 1(Win) | true |
| simdjson (ondemand) | 324.08 | 0.155005 | 8938.91ms | 4219120 | 40 | 1.48146e+10 | 1.24156e+07 | 0.218588 | 15.502 | 61.9484 | 12.5404 | 0.0866111 | 0.0550606 | 0.00587823 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1852.79 | 0.398405 | 7606.21ms | 4219119 | 80 | 5.98868e+09 | 2.17168e+06 | 0.0178016 | 2.73473 | 10.2104 | 1.85267 | 0.0150106 | 0.0564483 | 0.000810089 | 1(Win) | true |
| simdjson (ondemand) | 1444.35 | 0.115723 | 9487.12ms | 4219119 | 30 | 3.11787e+08 | 2.7858e+06 | 0.440067 | 3.48598 | 11.8716 | 2.29447 | 0.0187356 | 0.0539937 | 0.00130654 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 716.061 | 0.206943 | 8960.29ms | 4219119 | 30 | 4.05664e+09 | 5.61916e+06 | 0.311823 | 7.07596 | 27.2144 | 5.16715 | 0.0202669 | 0.0578374 | 0.00792093 | 1(Win) | true |
| simdjson (ondemand) | 310.946 | 0.0664348 | 9335.25ms | 4219119 | 40 | 2.95615e+09 | 1.29401e+07 | 0.245187 | 16.2329 | 64.3899 | 13.299 | 0.0894148 | 0.0577301 | 0.010554 | 2(Loss) | true |
