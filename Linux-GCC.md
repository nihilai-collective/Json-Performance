# Json-Performance: Generic Parsing & Streaming vs simdjson On Demand
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-43-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 522.104 | 0.0499673 | 882.387ms | 905 | 4890 | 3336.28 | 1653.07 | 0.152981 | 10.0821 | 55.4608 | 5.50387 | 0.00111876 | 0.0001053 | 7.00494e-06 | 1(Win) | true |
| simdjson (ondemand) | 227.63 | 0.0366239 | 1093.27ms | 905 | 2560 | 4936.36 | 3791.57 | 0.0395977 | 22.8533 | 104.421 | 9.82431 | 0.0789814 | 0.000111792 | 7.33771e-06 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 524.708 | 0.080926 | 874.377ms | 905 | 2560 | 4536.05 | 1644.87 | 0.0216061 | 10.052 | 54.8055 | 5.27735 | 0.00202391 | 0.000131215 | 1.9855e-05 | 1(Win) | true |
| simdjson (ondemand) | 227.095 | 0.0495405 | 1092.6ms | 905 | 1280 | 4537.45 | 3800.5 | 0.0518167 | 22.9383 | 103.737 | 9.68509 | 0.0889451 | 0.000162293 | 6.12914e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 614 | 0.0848285 | 995.919ms | 1811 | 320 | 1821.94 | 2812.88 | 0.034007 | 8.52092 | 41.4809 | 5.98454 | 0.000560809 | 0.000139771 | 6.72971e-05 | 1(Win) | true |
| simdjson (ondemand) | 331.077 | 0.0934575 | 1243.43ms | 1811 | 640 | 15212 | 5216.62 | 0.0151582 | 15.6635 | 77.2275 | 9.76091 | 0.000604811 | 6.98854e-05 | 4.31391e-06 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 636.955 | 0.0372019 | 983.514ms | 1811 | 4890 | 4975.76 | 2711.5 | 0.160948 | 8.20258 | 40.3385 | 5.71618 | 0.00111588 | 9.57566e-05 | 1.18566e-05 | 1(Win) | true |
| simdjson (ondemand) | 334.088 | 0.0758179 | 1233.68ms | 1811 | 1280 | 19663.8 | 5169.6 | 0.0859608 | 15.3573 | 76.1773 | 9.5323 | 0.00150211 | 8.28272e-05 | 4.31391e-06 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1342.06 | 0.0299737 | 989.245ms | 3862 | 4890 | 3308.81 | 2744.36 | 0.0559077 | 3.89226 | 18.1567 | 2.01607 | 0.00027466 | 6.08414e-05 | 5.77172e-06 | 1(Win) | true |
| simdjson (ondemand) | 745.907 | 0.0269038 | 1206.67ms | 3862 | 4890 | 8629.61 | 4937.74 | 0.00487562 | 6.95636 | 32.0163 | 3.55153 | 0.000813018 | 6.34889e-05 | 1.76329e-05 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.11 | 0.0340565 | 976.924ms | 3862 | 4890 | 3969.95 | 2645.69 | 0.0879699 | 3.75589 | 17.6567 | 1.90471 | 0.00026497 | 6.09473e-05 | 8.26045e-06 | 1(Win) | true |
| simdjson (ondemand) | 760.839 | 0.0478049 | 1196.44ms | 3862 | 1280 | 6854.79 | 4840.83 | 0.0271689 | 6.8222 | 31.5601 | 3.45236 | 0.00109076 | 2.44773e-05 | 2.02292e-06 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1390.34 | 0.0300254 | 1376.08ms | 9578 | 4890 | 19028.1 | 6569.82 | 0.0245309 | 3.72344 | 17.7196 | 3.34172 | 0.00222079 | 2.47243e-05 | 9.71466e-06 | 1(Win) | true |
| simdjson (ondemand) | 1358.92 | 0.0497313 | 1398.9ms | 9578 | 1280 | 14303.2 | 6721.74 | 0.0982038 | 3.79251 | 19.237 | 2.98089 | 0.00372819 | 1.68844e-05 | 1.71291e-06 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1891.22 | 0.0844289 | 1330.46ms | 9578 | 640 | 10642.1 | 4829.85 | 0.0209678 | 2.74526 | 13.6113 | 2.40343 | 0.000781739 | 2.9201e-05 | 8.15671e-07 | 1(Win) | true |
| simdjson (ondemand) | 1796.3 | 0.0536433 | 1358.38ms | 9578 | 4890 | 36385.9 | 5085.07 | 0.028615 | 2.88303 | 15.0951 | 2.03258 | 0.00204403 | 3.38198e-05 | 9.80007e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1336.22 | 0.209095 | 989.697ms | 3873 | 2560 | 85519.9 | 2764.2 | 0.0372228 | 3.90025 | 18.1479 | 2.00646 | 0.00110521 | 5.0631e-05 | 4.63949e-06 | 1(Win) | true |
| simdjson (ondemand) | 744.176 | 0.0501307 | 1210.2ms | 3873 | 1280 | 7924.31 | 4963.32 | 0.00939795 | 6.97442 | 31.7565 | 3.66357 | 0.00553854 | 6.65666e-05 | 1.49271e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.01 | 0.0538017 | 976.302ms | 3873 | 1280 | 2601.15 | 2649.61 | 0.00869898 | 3.75076 | 17.6558 | 1.89801 | 0.000553511 | 7.50387e-05 | 2.09786e-05 | 1(Win) | true |
| simdjson (ondemand) | 755.37 | 0.0470156 | 1201.31ms | 3873 | 1280 | 6765.03 | 4889.76 | 0.00968316 | 6.87023 | 31.3016 | 3.56468 | 0.00745707 | 3.67125e-05 | 1.41202e-06 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.8 | 0.079055 | 6435.03ms | 94653 | 160 | 328548 | 57320.5 | 0.140318 | 3.2219 | 14.8731 | 2.85132 | 0.00884045 | 8.1878e-06 | 5.01833e-06 | 1(Win) | true |
| simdjson (ondemand) | 1242.5 | 0.0480665 | 7984.29ms | 94653 | 640 | 780444 | 72650.5 | 0.144364 | 4.11099 | 15.8653 | 3.10282 | 0.0117886 | 4.27549e-06 | 8.74906e-07 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.16 | 0.139826 | 5910.32ms | 94653 | 80 | 238809 | 39074.4 | 0.0228678 | 2.20927 | 11.0843 | 1.98275 | 0.00596983 | 4.62215e-06 | 1.05649e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.23 | 0.0440091 | 7497ms | 94653 | 4890 | 2.85454e+06 | 54899.8 | 0.278375 | 3.1284 | 12.1054 | 2.24274 | 0.00840274 | 9.79792e-06 | 5.85715e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1991.32 | 0.0582467 | 6709.87ms | 124597 | 640 | 773134 | 59671.4 | 0.013474 | 2.56554 | 11.671 | 2.17247 | 0.00714995 | 3.51132e-06 | 6.77183e-07 | 1(Win) | true |
| simdjson (ondemand) | 1582.02 | 0.0425103 | 8223.48ms | 124597 | 640 | 652468 | 75109.5 | 0.0292846 | 3.22116 | 12.3701 | 2.3687 | 0.00909846 | 2.73381e-06 | 4.63996e-07 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2842.86 | 0.032723 | 6183.96ms | 124597 | 1280 | 239453 | 41797.7 | 0.000194389 | 1.79187 | 8.79962 | 1.51452 | 0.00457495 | 2.27609e-06 | 1.88106e-07 | 1(Win) | true |
| simdjson (ondemand) | 2080.96 | 0.0221762 | 7665.88ms | 124597 | 2560 | 410491 | 57101.1 | 0.0220204 | 2.45884 | 9.51666 | 1.7155 | 0.00660147 | 3.13824e-06 | 5.7059e-07 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1130.46 | 0.017769 | 8725.76ms | 94653 | 4890 | 984450 | 79850.7 | 0.0578396 | 4.53621 | 20.6428 | 4.21044 | 0.0107707 | 1.74461e-05 | 1.29976e-05 | 1(Win) | true |
| simdjson (ondemand) | 709.058 | 0.0672392 | 6876.95ms | 94653 | 320 | 2.34476e+06 | 127307 | 0.222612 | 7.17784 | 34.1199 | 7.06221 | 0.0122895 | 6.60307e-06 | 2.01394e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1449.18 | 0.154467 | 8183.29ms | 94653 | 80 | 740601 | 62288.9 | 0.000200678 | 3.51758 | 16.8554 | 3.34383 | 0.00788617 | 3.96184e-06 | 1.32061e-07 | 1(Win) | true |
| simdjson (ondemand) | 833.297 | 0.175337 | 6584.66ms | 94653 | 40 | 1.44303e+06 | 108326 | 0.0572363 | 6.17831 | 30.3799 | 6.20631 | 0.00969356 | 0.00018964 | 0.000176434 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.97 | 0.0591662 | 8988.48ms | 124597 | 640 | 1.51924e+06 | 82347.3 | 0.176447 | 3.54343 | 16.2022 | 3.25295 | 0.00787631 | 1.32051e-05 | 7.98825e-06 | 1(Win) | true |
| simdjson (ondemand) | 926.276 | 0.0485127 | 6959.27ms | 124597 | 640 | 2.47871e+06 | 128282 | 0.010665 | 5.52841 | 25.9892 | 5.32316 | 0.0102698 | 7.51172e-06 | 1.98139e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1824.85 | 0.0215651 | 8481.56ms | 124597 | 2560 | 504784 | 65115 | 0.0299003 | 2.78059 | 13.3353 | 2.59718 | 0.00580241 | 3.39846e-06 | 5.51779e-07 | 1(Win) | true |
| simdjson (ondemand) | 1068.13 | 0.0279707 | 6691.65ms | 124597 | 2560 | 2.47865e+06 | 111246 | 0.0179339 | 4.76415 | 23.1406 | 4.67136 | 0.00758609 | 4.53023e-06 | 6.58373e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.33 | 0.0476048 | 4334.71ms | 94653 | 2560 | 754352 | 36059.2 | 0.0646012 | 2.02224 | 9.5773 | 1.71249 | 0.00497251 | 3.83803e-06 | 1.38252e-06 | 1(Win) | true |
| simdjson (ondemand) | 1807.95 | 0.0321341 | 5704.05ms | 94653 | 1280 | 329488 | 49928.6 | 0.0124428 | 2.82643 | 10.6684 | 1.97307 | 0.00839203 | 5.48054e-06 | 2.07997e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3295.86 | 0.127668 | 3947.79ms | 94653 | 320 | 391242 | 27388.3 | 0.0743263 | 1.53532 | 7.72976 | 1.27821 | 0.00324884 | 2.34409e-06 | 4.29199e-07 | 1(Win) | true |
| simdjson (ondemand) | 2179.43 | 0.0351834 | 5348.2ms | 94653 | 1280 | 271812 | 41418.2 | 0.134202 | 2.34791 | 8.84793 | 1.54693 | 0.00682527 | 8.26209e-06 | 4.29199e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3098.39 | 0.0582123 | 4563.2ms | 124597 | 1280 | 637945 | 38350.6 | 0.0280251 | 1.64853 | 7.69258 | 1.31784 | 0.00448246 | 3.36084e-06 | 6.64643e-07 | 1(Win) | true |
| simdjson (ondemand) | 2455 | 0.018324 | 5587.15ms | 124597 | 4890 | 384648 | 48401.2 | 0.110618 | 2.08503 | 8.16149 | 1.4543 | 0.00568556 | 3.18737e-06 | 7.94381e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4119.29 | 0.0508354 | 4134.59ms | 124597 | 1280 | 275241 | 28846 | 0.0557284 | 1.24594 | 6.28651 | 0.987855 | 0.00233945 | 1.81209e-06 | 3.07241e-07 | 1(Win) | true |
| simdjson (ondemand) | 2975.27 | 0.0196656 | 5209.58ms | 124597 | 2560 | 157912 | 39937.5 | 0.0607812 | 1.72657 | 6.77893 | 1.13039 | 0.00474641 | 2.12874e-06 | 2.75889e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.26 | 0.193085 | 5680.26ms | 94653 | 30 | 267365 | 48892.5 | 0.0271951 | 2.78773 | 12.6873 | 2.50996 | 0.00778 | 3.8738e-06 | 7.04327e-07 | 1(Win) | true |
| simdjson (ondemand) | 1576.39 | 0.0379879 | 6440.24ms | 94653 | 1280 | 605679 | 57262.6 | 0.0955315 | 3.23832 | 13.218 | 2.50911 | 0.00905381 | 2.09565e-05 | 1.36188e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2193.59 | 0.0397835 | 5340.51ms | 94653 | 4890 | 1.31061e+06 | 41150.9 | 0.403756 | 2.31567 | 10.8438 | 2.07789 | 0.00692853 | 4.44633e-06 | 1.64199e-06 | 1(Win) | true |
| simdjson (ondemand) | 1859.63 | 0.0349071 | 6063.13ms | 94653 | 1280 | 367499 | 48541 | 0.154439 | 2.75626 | 11.3923 | 2.0817 | 0.00762393 | 3.19423e-06 | 4.86976e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2363.39 | 0.0961223 | 5777.79ms | 124597 | 40 | 93422.7 | 50277.3 | 0.0835332 | 2.18078 | 10.0945 | 1.9305 | 0.00590383 | 3.61164e-06 | 8.02588e-07 | 1(Win) | true |
| simdjson (ondemand) | 2120.67 | 0.0367188 | 6336.18ms | 124597 | 1280 | 541823 | 56031.9 | 0.226605 | 2.41621 | 10.097 | 1.86025 | 0.00685063 | 3.79975e-06 | 8.33939e-07 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2814.68 | 0.0230105 | 5456.06ms | 124597 | 2560 | 241574 | 42216.1 | 0.0347302 | 1.81589 | 8.69081 | 1.60163 | 0.00479576 | 3.91261e-06 | 9.53073e-07 | 1(Win) | true |
| simdjson (ondemand) | 2479.14 | 0.0995241 | 6009.29ms | 124597 | 160 | 364074 | 47929.9 | 0.0221629 | 2.07207 | 8.71633 | 1.53789 | 0.00601855 | 3.411e-06 | 6.01941e-07 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 802.065 | 0.0807018 | 7742.21ms | 2090234 | 160 | 6.43662e+08 | 2.48534e+06 | 0.0793309 | 6.31567 | 30.3586 | 5.61964 | 0.0231564 | 0.105401 | 0.00091093 | 1(Win) | true |
| Jsonifier (generic) | 733.265 | 0.0975849 | 8449.76ms | 2090234 | 160 | 1.12604e+09 | 2.71853e+06 | 0.300997 | 6.88274 | 31.1375 | 6.38675 | 0.0217599 | 0.103714 | 0.00125169 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 946.897 | 0.105348 | 7767.47ms | 2090234 | 80 | 3.93481e+08 | 2.10519e+06 | 0.132684 | 5.36284 | 25.0602 | 4.35795 | 0.0223106 | 0.080224 | 0.00132787 | 1(Win) | true |
| Jsonifier (generic) | 856.956 | 0.161019 | 8421.83ms | 2090234 | 80 | 1.12232e+09 | 2.32614e+06 | 0.294494 | 5.92078 | 25.8085 | 5.11874 | 0.0208602 | 0.0784304 | 0.000671318 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1868.26 | 0.0824665 | 8274.06ms | 5212421 | 160 | 7.70338e+08 | 2.66074e+06 | 0.104002 | 2.72294 | 12.986 | 2.28953 | 0.0104004 | 0.0609262 | 0.000717832 | 1(Win) | true |
| Jsonifier (generic) | 1735.34 | 0.0812283 | 8907ms | 5212421 | 160 | 8.66249e+08 | 2.86453e+06 | 0.0209746 | 2.9309 | 13.353 | 2.60421 | 0.0102243 | 0.0607565 | 0.000839755 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2173.58 | 0.172521 | 8304.2ms | 5212421 | 30 | 4.67018e+08 | 2.28699e+06 | 0.00193125 | 2.33939 | 10.857 | 1.78264 | 0.0100166 | 0.0507182 | 0.000333127 | 1(Win) | true |
| Jsonifier (generic) | 1990.14 | 0.0786359 | 8959.39ms | 5212421 | 80 | 3.08633e+08 | 2.49779e+06 | 0.589722 | 2.54711 | 11.2235 | 2.09727 | 0.00984016 | 0.0507796 | 0.000827588 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 733.679 | 0.22841 | 8555ms | 2090234 | 30 | 1.15539e+09 | 2.71699e+06 | 0.581436 | 6.95844 | 34.6585 | 6.57569 | 0.0232366 | 0.180947 | 0.000986572 | 1(Win) | true |
| Jsonifier (generic) | 696.097 | 0.34763 | 8900ms | 2090234 | 160 | 1.58564e+10 | 2.86369e+06 | 0.680584 | 7.35256 | 34.0008 | 7.02411 | 0.0218087 | 0.155829 | 0.000368918 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 839.091 | 0.643608 | 8574.2ms | 2090234 | 80 | 1.87027e+10 | 2.37567e+06 | 0.408588 | 6.07703 | 29.3791 | 5.31764 | 0.0222059 | 0.154876 | 0.00114921 | 1(Win) | true |
| Jsonifier (generic) | 794.767 | 0.715448 | 8939.86ms | 2090234 | 80 | 2.57606e+10 | 2.50816e+06 | 0.325872 | 6.44239 | 28.6896 | 5.7597 | 0.020972 | 0.130261 | 0.000832807 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1607.51 | 0.44502 | 9639.87ms | 5212421 | 160 | 3.03004e+10 | 3.09232e+06 | 0.384244 | 3.18209 | 14.7144 | 2.67355 | 0.0105404 | 0.120897 | 0.000531766 | 1(Win) | true |
| Jsonifier (generic) | 1548.99 | 0.684486 | 9895.27ms | 5212421 | 80 | 3.86011e+10 | 3.20915e+06 | 0.311078 | 3.27106 | 14.5067 | 2.86064 | 0.0103011 | 0.100387 | 0.000740138 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1840.7 | 0.168742 | 9581.08ms | 5212421 | 160 | 3.32261e+09 | 2.70058e+06 | 1.16022 | 2.76929 | 12.589 | 2.16751 | 0.0100508 | 0.109983 | 0.0008904 | 1(Win) | true |
| Jsonifier (generic) | 1778.22 | 0.480815 | 9838.22ms | 5212421 | 160 | 2.89057e+10 | 2.79546e+06 | 0.141158 | 2.86416 | 12.3782 | 2.35386 | 0.00980679 | 0.0901382 | 0.000742502 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8553.02 | 0.0688507 | 6152.82ms | 2090234 | 640 | 1.64796e+07 | 233064 | 0.06901 | 0.591451 | 3.18965 | 0.396912 | 0.00243292 | 0.0508256 | 1.6767e-06 | 1(Win) | true |
| simdjson (ondemand) | 7411.15 | 0.0550718 | 7075.27ms | 2090234 | 320 | 7.02145e+06 | 268973 | 0.149928 | 0.689356 | 3.66628 | 0.418404 | 0.00236034 | 0.0493786 | 2.77481e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8585.2 | 0.0537177 | 6139.73ms | 2090234 | 1280 | 1.99128e+07 | 232190 | 0.0631387 | 0.590893 | 3.18958 | 0.396895 | 0.00240418 | 0.0507874 | 1.43263e-06 | 1(Win) | true |
| simdjson (ondemand) | 7436.94 | 0.0391221 | 7056.14ms | 2090234 | 640 | 7.03762e+06 | 268041 | 0.0437362 | 0.687148 | 3.6662 | 0.418387 | 0.00231068 | 0.0493274 | 1.49505e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11476.5 | 0.0767826 | 5615.85ms | 5212421 | 320 | 3.53947e+07 | 433143 | 0.138339 | 0.442065 | 1.96707 | 0.181297 | 0.00222042 | 0.0394179 | 3.16971e-06 | 1(Win) | true |
| simdjson (ondemand) | 9771.12 | 0.0382487 | 6585.06ms | 5212421 | 640 | 2.42328e+07 | 508739 | 0.0661882 | 0.524207 | 2.27766 | 0.202785 | 0.00214232 | 0.0393999 | 2.59986e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11506.4 | 0.144409 | 5597.54ms | 5212421 | 160 | 6.22741e+07 | 432016 | 0.0489442 | 0.442307 | 1.96704 | 0.18129 | 0.00223307 | 0.0393919 | 5.66555e-06 | 1(Win) | true |
| simdjson (ondemand) | 9749.32 | 0.0240402 | 6596.54ms | 5212421 | 640 | 9.61585e+06 | 509877 | 0.11233 | 0.527314 | 2.27762 | 0.202778 | 0.00216729 | 0.0393846 | 2.8013e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6341.91 | 0.0599873 | 8252.02ms | 2090234 | 1280 | 4.5507e+07 | 314322 | 0.0800295 | 0.79996 | 4.62947 | 0.716865 | 0.0024252 | 0.0760871 | 3.02149e-06 | 1(Win) | true |
| simdjson (ondemand) | 5608.27 | 0.0456905 | 9302.52ms | 2090234 | 640 | 1.68797e+07 | 355440 | 0.122573 | 0.910217 | 5.10596 | 0.738337 | 0.00233051 | 0.0753076 | 8.04336e-07 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6322 | 0.0419455 | 8244.21ms | 2090234 | 1280 | 2.23904e+07 | 315312 | 0.0911348 | 0.800256 | 4.62939 | 0.716848 | 0.00241851 | 0.0760451 | 1.81686e-06 | 1(Win) | true |
| simdjson (ondemand) | 5581.2 | 0.312233 | 9266.56ms | 2090234 | 320 | 3.97963e+08 | 357164 | 0.204248 | 0.909435 | 5.10588 | 0.738319 | 0.00233985 | 0.0752324 | 6.95197e-07 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9063.08 | 0.150395 | 7123.2ms | 5212421 | 80 | 5.44357e+07 | 548484 | 0.265606 | 0.566239 | 2.54445 | 0.309603 | 0.00221432 | 0.0591118 | 1.55878e-06 | 1(Win) | true |
| simdjson (ondemand) | 7950.73 | 0.0841107 | 8074.9ms | 5212421 | 80 | 2.21237e+07 | 625220 | 0.256357 | 0.646142 | 2.85498 | 0.331081 | 0.00215496 | 0.059186 | 3.68831e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9030.92 | 0.186972 | 7114.67ms | 5212421 | 40 | 4.2367e+07 | 550437 | 0.043684 | 0.5678 | 2.54442 | 0.309596 | 0.00224657 | 0.0590648 | 5.05044e-06 | 1(Win) | true |
| simdjson (ondemand) | 7813.52 | 0.134236 | 8134.98ms | 5212421 | 40 | 2.9173e+07 | 636198 | 0.0444949 | 0.650285 | 2.85495 | 0.331074 | 0.00213905 | 0.0590747 | 4.9641e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1391.75 | 0.044122 | 8913.98ms | 500299 | 640 | 1.4643e+07 | 342823 | 0.20997 | 3.6421 | 16.7854 | 3.13058 | 0.0145547 | 0.0145646 | 2.76772e-05 | 1(Win) | true |
| simdjson (ondemand) | 1202.49 | 0.144218 | 5139.44ms | 500299 | 40 | 1.30978e+07 | 396778 | 0.109079 | 4.22009 | 17.7439 | 2.9633 | 0.0205423 | 0.0176067 | 1.79393e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1594.19 | 0.0495992 | 8687.16ms | 500299 | 1280 | 2.82059e+07 | 299289 | 0.182087 | 3.18356 | 15.6564 | 2.85605 | 0.00953883 | 0.0127944 | 1.50816e-05 | 1(Win) | true |
| simdjson (ondemand) | 1354.33 | 0.0411491 | 10032.9ms | 500299 | 1280 | 2.68992e+07 | 352293 | 0.0704578 | 3.74758 | 16.6246 | 2.69129 | 0.0149765 | 0.0151486 | 7.50957e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2818.93 | 0.0772478 | 5048.4ms | 1151920 | 640 | 5.79999e+07 | 389707 | 0.0489165 | 1.7836 | 8.01461 | 1.39426 | 0.00633113 | 0.0332095 | 1.18227e-05 | 1(Win) | true |
| simdjson (ondemand) | 2558.38 | 0.0420799 | 5572.52ms | 1151920 | 640 | 2.08951e+07 | 429396 | 0.212694 | 1.99421 | 8.47188 | 1.32044 | 0.00856014 | 0.0345134 | 1.03089e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3182.12 | 0.145235 | 9866.86ms | 1151920 | 160 | 4.02232e+07 | 345228 | 0.185978 | 1.58447 | 7.52399 | 1.27505 | 0.00430977 | 0.0297747 | 6.32097e-06 | 1(Win) | true |
| simdjson (ondemand) | 2841.58 | 0.0926765 | 5450.85ms | 1151920 | 80 | 1.02696e+07 | 386600 | 0.172929 | 1.80732 | 7.98506 | 1.20223 | 0.00636829 | 0.0307527 | 4.10185e-06 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.037 | 0.0745847 | 8825.62ms | 500299 | 160 | 4.18229e+07 | 685484 | 0.0207698 | 7.36826 | 35.7032 | 7.46815 | 0.0208237 | 0.0161188 | 2.13872e-05 | 1(Win) | true |
| simdjson (ondemand) | 433.659 | 0.117464 | 6990.39ms | 500299 | 40 | 6.68085e+07 | 1.10023e+06 | 0.010255 | 11.8203 | 63.4971 | 13.0607 | 0.0322536 | 0.0202036 | 2.13372e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.508 | 0.0355811 | 8645.68ms | 500299 | 640 | 3.30101e+07 | 638284 | 0.534198 | 6.852 | 34.5628 | 7.19204 | 0.0144857 | 0.0128076 | 6.79281e-06 | 1(Win) | true |
| simdjson (ondemand) | 452.337 | 0.12387 | 6967.04ms | 500299 | 30 | 5.12138e+07 | 1.05479e+06 | 0.0643382 | 11.3634 | 62.3729 | 12.7893 | 0.0268023 | 0.014987 | 1.86555e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1476.66 | 0.0594723 | 9529.3ms | 1151920 | 640 | 1.25283e+08 | 743947 | 0.0484255 | 3.45171 | 16.2835 | 3.30716 | 0.00883042 | 0.0365391 | 2.33293e-05 | 1(Win) | true |
| simdjson (ondemand) | 951.247 | 0.0510737 | 7334.68ms | 1151920 | 320 | 1.11328e+08 | 1.15486e+06 | 0.0564328 | 5.3648 | 28.3075 | 5.69766 | 0.0134117 | 0.0583113 | 1.97252e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1577.73 | 0.254541 | 9393.59ms | 1151920 | 40 | 1.25648e+08 | 696291 | 0.0517069 | 3.24579 | 15.7936 | 3.18863 | 0.00650384 | 0.031673 | 1.49316e-05 | 1(Win) | true |
| simdjson (ondemand) | 999.654 | 0.0430783 | 7211.57ms | 1151920 | 320 | 7.17153e+07 | 1.09894e+06 | 0.20299 | 5.12528 | 27.8174 | 5.57934 | 0.0110012 | 0.0481709 | 3.36937e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5489.99 | 0.0375292 | 9448.61ms | 500299 | 640 | 680825 | 86907.6 | 0.000871967 | 0.937647 | 4.98844 | 0.721119 | 0.000937005 | 2.34235e-05 | 6.02765e-07 | 1(Win) | true |
| simdjson (ondemand) | 4882.86 | 0.0484426 | 5370.95ms | 500299 | 640 | 1.43399e+06 | 97713.8 | 0.0501788 | 1.04685 | 5.64612 | 0.724185 | 0.00103386 | 3.35768e-05 | 7.71414e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5540.33 | 0.0100882 | 9356.78ms | 500299 | 4890 | 369085 | 86118 | 0.059727 | 0.928876 | 4.96274 | 0.714799 | 0.000903672 | 6.94554e-06 | 5.97598e-07 | 1(Win) | true |
| simdjson (ondemand) | 4918.4 | 0.0739848 | 5334.07ms | 500299 | 2560 | 1.31867e+07 | 97007.6 | 0.174445 | 1.04257 | 5.6204 | 0.717847 | 0.00101706 | 1.12901e-05 | 1.39448e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8743.14 | 0.0960871 | 6787.86ms | 1151920 | 320 | 4.66434e+06 | 125648 | 0.0501155 | 0.581577 | 2.88345 | 0.336247 | 0.000608517 | 0.00471675 | 1.81762e-07 | 1(Win) | true |
| simdjson (ondemand) | 8031.66 | 0.0265779 | 7380.14ms | 1151920 | 1280 | 1.69155e+06 | 136778 | 0.0616106 | 0.638745 | 3.21565 | 0.347607 | 0.000869515 | 0.00530305 | 1.77421e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8900.21 | 0.0661894 | 6737.05ms | 1151920 | 30 | 200237 | 123430 | 0.0324234 | 0.578639 | 2.87229 | 0.333502 | 0.000580596 | 0.00445372 | 2.60435e-07 | 1(Win) | true |
| simdjson (ondemand) | 8093.52 | 0.0389669 | 7340.09ms | 1151920 | 320 | 895185 | 135733 | 0.0130259 | 0.634854 | 3.20449 | 0.344854 | 0.000864163 | 0.0046825 | 7.32473e-08 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3088.01 | 0.0692061 | 8286.42ms | 500299 | 80 | 914706 | 154508 | 0.0612236 | 1.66472 | 9.43991 | 1.76394 | 0.0021366 | 2.86828e-05 | 1.09934e-06 | 1(Win) | true |
| simdjson (ondemand) | 2986.67 | 0.0448546 | 8571.59ms | 500299 | 640 | 3.2861e+06 | 159751 | 0.139619 | 1.70997 | 10.1914 | 1.7315 | 0.00228666 | 2.06845e-05 | 5.01575e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3107.91 | 0.0773873 | 8291.88ms | 500299 | 30 | 423431 | 153519 | 0.0158045 | 1.65604 | 9.41419 | 1.7576 | 0.00214845 | 1.92552e-05 | 6.79594e-06 | 1(Win) | true |
| simdjson (ondemand) | 3012.7 | 0.0440727 | 8479.94ms | 500299 | 320 | 1.55896e+06 | 158370 | 0.0153552 | 1.70324 | 10.1657 | 1.72516 | 0.00226748 | 3.51665e-06 | 1.31172e-07 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5593.05 | 0.141429 | 5154.27ms | 1151920 | 1280 | 9.87719e+07 | 196415 | 0.128611 | 0.901629 | 4.82313 | 0.792329 | 0.00112346 | 0.00482896 | 1.93664e-05 | 1(Win) | true |
| simdjson (ondemand) | 5559.5 | 0.0773919 | 5218ms | 1151920 | 160 | 3.74183e+06 | 197600 | 0.186973 | 0.91454 | 5.18976 | 0.785102 | 0.00144542 | 0.00513046 | 6.51087e-06 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5640.95 | 0.208528 | 5148.93ms | 1151920 | 640 | 1.05548e+08 | 194747 | 0.276838 | 0.901128 | 4.81196 | 0.789576 | 0.00111403 | 0.00487323 | 7.30302e-06 | 1(Win) | true |
| simdjson (ondemand) | 5596.69 | 0.0352964 | 5219.08ms | 1151920 | 1280 | 6.14403e+06 | 196287 | 0.136969 | 0.911426 | 5.17859 | 0.782349 | 0.00144117 | 0.00471934 | 2.55212e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1458.12 | 0.0257088 | 4418.63ms | 56369 | 2560 | 229985 | 36867.8 | 0.0232631 | 3.5028 | 15.0917 | 2.97506 | 0.00730767 | 3.17661e-05 | 1.86688e-05 | 1(Win) | true |
| simdjson (ondemand) | 1285.6 | 0.0233886 | 4914.31ms | 56369 | 2560 | 244859 | 41815.2 | 0.0580641 | 3.98395 | 15.7498 | 2.78775 | 0.00980135 | 1.33953e-05 | 3.88068e-06 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1841.58 | 0.0292098 | 3985.88ms | 56369 | 2560 | 186123 | 29191.1 | 0.113098 | 2.79198 | 12.9595 | 2.51 | 0.00528348 | 8.92556e-06 | 1.61464e-06 | 1(Win) | true |
| simdjson (ondemand) | 1505.89 | 0.026935 | 4690.93ms | 56369 | 2560 | 236683 | 35698.2 | 0.294642 | 3.39673 | 13.634 | 2.32712 | 0.010385 | 1.42476e-05 | 5.13497e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2021.13 | 0.0231748 | 4695.34ms | 83958 | 4890 | 412172 | 39615.8 | 0.140026 | 2.52498 | 10.6218 | 2.00982 | 0.00621503 | 3.04223e-05 | 1.81316e-05 | 1(Win) | true |
| simdjson (ondemand) | 1836.5 | 0.0678458 | 5084.07ms | 83958 | 4890 | 4.27857e+06 | 43598.6 | 0.0195985 | 2.77893 | 11.0435 | 1.8917 | 0.00744299 | 3.67332e-05 | 2.38044e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2525.95 | 0.0577326 | 4235.27ms | 83958 | 160 | 53584.3 | 31698.5 | 0.00640845 | 2.04049 | 9.18229 | 1.69531 | 0.00390962 | 4.98761e-06 | 5.95536e-07 | 1(Win) | true |
| simdjson (ondemand) | 2177.47 | 0.107074 | 4778.15ms | 83958 | 80 | 124015 | 36771.4 | 0.0348218 | 2.36743 | 9.61962 | 1.58238 | 0.00723948 | 2.84368e-05 | 2.00993e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.076 | 0.0996651 | 9021.44ms | 56369 | 160 | 1.10032e+06 | 83206.5 | 0.110299 | 7.89173 | 35.0405 | 7.34068 | 0.0123824 | 1.04224e-05 | 2.77191e-06 | 1(Win) | true |
| simdjson (ondemand) | 209.89 | 0.0777162 | 6709.79ms | 56369 | 320 | 1.26785e+07 | 256123 | 0.0812256 | 24.2391 | 132.848 | 28.2488 | 0.0373043 | 0.000100565 | 4.59029e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 706.816 | 0.0407871 | 8635.3ms | 56369 | 1280 | 1.23175e+06 | 76056 | 0.043283 | 7.20553 | 32.9022 | 6.87073 | 0.0102175 | 1.93895e-05 | 8.9117e-06 | 1(Win) | true |
| simdjson (ondemand) | 216.56 | 0.0664375 | 6632.74ms | 56369 | 320 | 8.70364e+06 | 248235 | 0.0964574 | 23.5436 | 130.76 | 27.7906 | 0.0348379 | 3.415e-05 | 1.44694e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.682 | 0.0340836 | 9768.17ms | 83958 | 1280 | 1.20436e+06 | 89996.8 | 0.0836733 | 5.76106 | 24.757 | 5.24701 | 0.00840141 | 1.48977e-05 | 7.01616e-06 | 1(Win) | true |
| simdjson (ondemand) | 313.413 | 0.191368 | 6709.77ms | 83958 | 40 | 9.56069e+06 | 255473 | 0.114363 | 16.3006 | 89.3577 | 18.9219 | 0.025466 | 5.15139e-05 | 3.03723e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.803 | 0.0234511 | 9442.44ms | 83958 | 2560 | 979775 | 83421.9 | 0.00451556 | 5.32367 | 23.3074 | 4.92783 | 0.00678542 | 1.38648e-05 | 8.09557e-06 | 1(Win) | true |
| simdjson (ondemand) | 322.664 | 0.0955393 | 6612.4ms | 83958 | 160 | 8.99304e+06 | 248148 | 0.219237 | 15.789 | 87.9495 | 18.6129 | 0.0235483 | 1.4814e-05 | 3.79654e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2476.62 | 0.0477579 | 2894.95ms | 56369 | 640 | 68775.3 | 21706.1 | 0.0309797 | 2.07481 | 9.7062 | 1.70636 | 0.00376359 | 4.98944e-06 | 1.41368e-06 | 1(Win) | true |
| simdjson (ondemand) | 2167.67 | 0.0895842 | 3204.78ms | 56369 | 80 | 39486.3 | 24799.7 | 0.0169328 | 2.37796 | 10.1608 | 1.6973 | 0.00454195 | 5.54383e-06 | 1.33052e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3092.95 | 0.0456351 | 2745.88ms | 56369 | 4890 | 307640 | 17380.7 | 0.027386 | 1.65713 | 8.13257 | 1.36249 | 0.00279289 | 1.37278e-05 | 6.73331e-06 | 1(Win) | true |
| simdjson (ondemand) | 2659.97 | 0.0170124 | 3031.83ms | 56369 | 4890 | 57805.6 | 20209.9 | 0.0225787 | 1.93435 | 8.60265 | 1.3593 | 0.00302071 | 6.20364e-06 | 1.85384e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3413.39 | 0.0357097 | 3083.17ms | 83958 | 640 | 44906.1 | 23457.2 | 0.0196673 | 1.51039 | 7.03511 | 1.1654 | 0.00221149 | 9.60302e-06 | 5.47149e-06 | 1(Win) | true |
| simdjson (ondemand) | 3121.27 | 0.0726267 | 3322.56ms | 83958 | 320 | 111072 | 25652.5 | 0.00862413 | 1.64853 | 7.2875 | 1.15903 | 0.0024947 | 3.49877e-06 | 1.11663e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4118.58 | 0.0763263 | 2957.23ms | 83958 | 160 | 35228.8 | 19440.8 | 0.0499986 | 1.25242 | 5.98375 | 0.936337 | 0.00213247 | 1.92805e-05 | 1.48884e-05 | 1(Win) | true |
| simdjson (ondemand) | 3704.81 | 0.0356059 | 3161.84ms | 83958 | 1280 | 75796 | 21612.1 | 0.0918925 | 1.37935 | 6.24253 | 0.932209 | 0.00202071 | 4.22458e-06 | 1.56328e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.48 | 0.0193717 | 3597.6ms | 56369 | 4890 | 150283 | 28617.6 | 0.0161293 | 2.72552 | 13.1344 | 2.49882 | 0.00411835 | 1.3122e-05 | 5.63044e-06 | 1(Win) | true |
| simdjson (ondemand) | 1345.12 | 0.168805 | 4736.96ms | 56369 | 30 | 136537 | 39965 | 0.0529076 | 3.83157 | 16.6249 | 2.9803 | 0.0106507 | 2.01056e-05 | 1.53749e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2184.22 | 0.0232272 | 3487.32ms | 56369 | 2560 | 83660.8 | 24611.8 | 0.376763 | 2.35649 | 11.5663 | 2.15698 | 0.00435685 | 8.50285e-06 | 3.76287e-06 | 1(Win) | true |
| simdjson (ondemand) | 1494.76 | 0.0368098 | 4596.69ms | 56369 | 1280 | 224325 | 35964.2 | 0.112356 | 3.41869 | 15.1001 | 2.64941 | 0.00959944 | 1.0464e-05 | 4.13015e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2518.15 | 0.0638627 | 3903.85ms | 83958 | 1280 | 527797 | 31796.6 | 0.0306076 | 2.02747 | 9.37298 | 1.71673 | 0.00355944 | 1.04405e-05 | 3.98265e-06 | 1(Win) | true |
| simdjson (ondemand) | 1935.15 | 0.08817 | 4849.37ms | 83958 | 160 | 212940 | 41375.9 | 0.0151984 | 2.65205 | 11.5053 | 1.99393 | 0.00747338 | 8.78415e-06 | 5.06205e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2938.11 | 0.0194723 | 3745.4ms | 83958 | 4890 | 137699 | 27251.7 | 0.0271067 | 1.7452 | 8.33257 | 1.48975 | 0.00258113 | 4.39406e-06 | 1.07659e-06 | 1(Win) | true |
| simdjson (ondemand) | 2169.68 | 0.0328296 | 4691.6ms | 83958 | 2560 | 375754 | 36903.4 | 0.0920065 | 2.35645 | 10.4896 | 1.77323 | 0.00641597 | 6.40201e-06 | 2.43797e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1270.22 | 0.0225988 | 4737.21ms | 53331 | 4890 | 400389 | 40040.6 | 0.0529159 | 4.03718 | 13.8574 | 2.70936 | 0.013274 | 4.82997e-05 | 1.52729e-05 | 1(Win) | true |
| simdjson (ondemand) | 1040.38 | 0.0546591 | 5620.96ms | 53331 | 4890 | 3.49148e+06 | 48886.4 | 0.168339 | 4.93184 | 17.7619 | 3.48738 | 0.0201081 | 7.85464e-05 | 2.69184e-05 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.56 | 0.0406321 | 4502.76ms | 53331 | 1280 | 221616 | 32383.7 | 0.0816922 | 3.26981 | 11.6734 | 2.21337 | 0.0103718 | 2.05234e-05 | 1.01958e-05 | 1(Win) | true |
| simdjson (ondemand) | 1233.94 | 0.0824095 | 5420.1ms | 53331 | 320 | 369210 | 41217.8 | 0.0287352 | 4.15354 | 15.6297 | 3.00451 | 0.0165201 | 1.67585e-05 | 6.67998e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1493.8 | 0.0707019 | 4897.64ms | 65103 | 640 | 552660 | 41563.1 | 0.000203005 | 3.43261 | 11.8627 | 2.28831 | 0.0105017 | 3.27606e-05 | 1.53363e-05 | 1(Win) | true |
| simdjson (ondemand) | 1256.36 | 0.0273778 | 5672.09ms | 65103 | 4890 | 895112 | 49418.1 | 0.0760289 | 4.08733 | 14.77 | 2.85788 | 0.0169242 | 4.43595e-05 | 1.44493e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1829.7 | 0.0290863 | 4673.8ms | 65103 | 4890 | 476352 | 33933 | 0.0747312 | 2.80486 | 10.073 | 1.88158 | 0.00832076 | 2.46675e-05 | 1.44556e-05 | 1(Win) | true |
| simdjson (ondemand) | 1496.68 | 0.175616 | 5446.9ms | 65103 | 80 | 424585 | 41483.3 | 0.0977552 | 3.44233 | 13.0286 | 2.46422 | 0.0138338 | 4.72328e-05 | 2.61125e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 928.669 | 0.0269679 | 6215.4ms | 53331 | 2560 | 558435 | 54767 | 0.125497 | 5.54239 | 19.7759 | 3.94037 | 0.016977 | 5.17186e-05 | 1.98934e-05 | 1(Win) | true |
| simdjson (ondemand) | 485.426 | 0.0592256 | 5750.34ms | 53331 | 1280 | 4.92882e+06 | 104775 | 0.171655 | 10.5933 | 36.9768 | 7.48488 | 0.0717104 | 6.19217e-05 | 1.79598e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1087.01 | 0.0630407 | 5970.87ms | 53331 | 320 | 278411 | 46789.4 | 0.139542 | 4.73987 | 17.5305 | 3.43058 | 0.013914 | 1.002e-05 | 2.98841e-06 | 1(Win) | true |
| simdjson (ondemand) | 529.261 | 0.0877647 | 5609.96ms | 53331 | 640 | 4.55239e+06 | 96097.1 | 0.216966 | 9.6884 | 34.7767 | 6.9882 | 0.0661322 | 1.49128e-05 | 4.13104e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1065.42 | 0.0473845 | 6560.58ms | 65103 | 640 | 487989 | 58274.6 | 0.0156343 | 4.83333 | 16.9534 | 3.39068 | 0.0149041 | 6.30011e-05 | 4.44008e-05 | 1(Win) | true |
| simdjson (ondemand) | 606.105 | 0.11296 | 5607.37ms | 65103 | 320 | 4.28457e+06 | 102436 | 0.0934647 | 8.47037 | 30.2332 | 6.06999 | 0.0537049 | 4.14247e-05 | 1.89123e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.94 | 0.061763 | 6306.6ms | 65103 | 320 | 303607 | 49871.5 | 0.0391597 | 4.13817 | 15.1066 | 2.972 | 0.0120309 | 2.80805e-05 | 2.01604e-05 | 1(Win) | true |
| simdjson (ondemand) | 666.957 | 0.0738001 | 5463.24ms | 65103 | 640 | 3.02065e+06 | 93090.1 | 0.0242314 | 7.72074 | 28.4294 | 5.66275 | 0.0491591 | 1.77363e-05 | 5.6641e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8099.61 | 0.0406566 | 1352.41ms | 53331 | 4890 | 31871.5 | 6279.37 | 0.00792967 | 0.637198 | 3.01418 | 0.39898 | 0.000712669 | 3.38588e-06 | 9.12617e-07 | 1(Win) | true |
| simdjson (ondemand) | 6829.08 | 0.0801078 | 1463.94ms | 53331 | 640 | 22780.6 | 7447.62 | 0.0279373 | 0.756721 | 3.39 | 0.417768 | 0.000833913 | 1.19829e-05 | 5.62525e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8672.74 | 0.0395323 | 1325.6ms | 53331 | 2560 | 13759.1 | 5864.4 | 0.0960918 | 0.597196 | 2.86518 | 0.364422 | 0.000790113 | 3.32534e-06 | 2.71008e-07 | 1(Win) | true |
| simdjson (ondemand) | 7154.58 | 0.0612106 | 1443.35ms | 53331 | 80 | 1514.73 | 7108.79 | 0.021975 | 0.724381 | 3.25158 | 0.384936 | 0.000941057 | 4.68771e-06 | 3.28139e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8429.31 | 0.0333599 | 1459.64ms | 65103 | 2560 | 15456.4 | 7365.62 | 0.0430765 | 0.613876 | 2.85097 | 0.339109 | 0.000621065 | 4.02007e-06 | 9.96018e-07 | 1(Win) | true |
| simdjson (ondemand) | 7704.51 | 0.0610759 | 1528.94ms | 65103 | 640 | 15503.6 | 8058.54 | 0.0245022 | 0.67139 | 3.04537 | 0.354101 | 0.000737893 | 2.90405e-06 | 6.24011e-07 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8920.77 | 0.0203041 | 1437.81ms | 65103 | 4890 | 9765.05 | 6959.83 | 0.0723617 | 0.580482 | 2.72779 | 0.310508 | 0.000688492 | 3.16629e-06 | 5.21433e-07 | 1(Win) | true |
| simdjson (ondemand) | 8082.64 | 0.0233357 | 1502.81ms | 65103 | 2560 | 8225.78 | 7681.53 | 0.00600095 | 0.640407 | 2.93235 | 0.327282 | 0.000752239 | 6.94212e-06 | 2.74205e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5668.92 | 0.118384 | 1622.9ms | 53331 | 640 | 72197.7 | 8971.8 | 0.0939215 | 0.905293 | 4.33193 | 0.701806 | 0.00176565 | 3.1056e-06 | 1.17193e-07 | 1(Win) | true |
| simdjson (ondemand) | 4232.82 | 0.0288343 | 1926.82ms | 53331 | 4890 | 58698.6 | 12015.7 | 0.0626241 | 1.21728 | 5.84767 | 0.954323 | 0.00238064 | 7.22808e-06 | 3.17499e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5979.54 | 0.0449498 | 1591.2ms | 53331 | 4890 | 71480.7 | 8505.73 | 0.102676 | 0.860902 | 4.18293 | 0.667248 | 0.00170078 | 6.50719e-06 | 1.33058e-06 | 1(Win) | true |
| simdjson (ondemand) | 4332.29 | 0.0223223 | 1912.2ms | 53331 | 2560 | 17581 | 11739.9 | 0.00596557 | 1.19136 | 5.707 | 0.921059 | 0.00277124 | 3.74284e-06 | 3.2228e-07 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6189.66 | 0.0342112 | 1727.68ms | 65103 | 4890 | 57585.8 | 10030.8 | 0.0139014 | 0.834843 | 3.93911 | 0.595011 | 0.00144464 | 4.4416e-06 | 1.1371e-06 | 1(Win) | true |
| simdjson (ondemand) | 4910.25 | 0.0191214 | 1989.35ms | 65103 | 4890 | 28585.4 | 12644.4 | 0.0807497 | 1.04959 | 5.05786 | 0.793497 | 0.00205447 | 4.12434e-06 | 1.18108e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6474.52 | 0.0300961 | 1702.88ms | 65103 | 2560 | 21323 | 9589.45 | 0.123006 | 0.797476 | 3.81592 | 0.56641 | 0.00144953 | 5.04009e-06 | 1.90803e-06 | 1(Win) | true |
| simdjson (ondemand) | 5054.27 | 0.0363994 | 1968.76ms | 65103 | 1280 | 25590.8 | 12284.1 | 0.0105839 | 1.02159 | 4.94263 | 0.766248 | 0.0021241 | 5.8201e-06 | 2.73605e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.49 | 0.10317 | 1534.16ms | 11812 | 80 | 5556.65 | 8078.07 | 0.115612 | 3.70613 | 17.673 | 3.32509 | 0.00474623 | 7.51355e-05 | 6.24365e-05 | 1(Win) | true |
| simdjson (ondemand) | 1084.45 | 0.0314161 | 1766.39ms | 11812 | 1280 | 13631.5 | 10387.6 | 0.00954322 | 4.7657 | 19.5475 | 3.64241 | 0.00630662 | 3.07553e-05 | 1.17068e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1540.17 | 0.0305194 | 1508.14ms | 11812 | 4890 | 24365.1 | 7313.99 | 0.0487381 | 3.35811 | 16.6684 | 3.09321 | 0.00393049 | 2.52248e-05 | 5.31503e-06 | 1(Win) | true |
| simdjson (ondemand) | 1174.12 | 0.0248316 | 1730.83ms | 11812 | 2560 | 14530.3 | 9594.29 | 0.0460796 | 4.40349 | 18.543 | 3.4139 | 0.00513041 | 2.80766e-05 | 2.24877e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2672.05 | 0.0380278 | 1634.19ms | 25388 | 1280 | 15197.7 | 9061.16 | 0.155153 | 1.93489 | 9.08707 | 1.59997 | 0.00261682 | 1.16627e-05 | 4.1235e-06 | 1(Win) | true |
| simdjson (ondemand) | 2205.41 | 0.0234391 | 1821ms | 25388 | 4890 | 32379.3 | 10978.4 | 0.00983189 | 2.34185 | 9.81304 | 1.72733 | 0.00229709 | 9.84314e-06 | 2.76285e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2891.14 | 0.0262636 | 1618.05ms | 25388 | 640 | 3096.04 | 8374.51 | 0.0304216 | 1.79119 | 8.59434 | 1.48716 | 0.00246893 | 8.73937e-06 | 2.27716e-06 | 1(Win) | true |
| simdjson (ondemand) | 2393.99 | 0.0274613 | 1787.55ms | 25388 | 2560 | 19746.7 | 10113.6 | 0.0802316 | 2.15623 | 9.32653 | 1.61667 | 0.00189481 | 1.18012e-05 | 2.50795e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 776.311 | 0.0345545 | 2177.61ms | 11812 | 2560 | 64361.5 | 14510.7 | 0.0155115 | 6.64124 | 29.5444 | 6.02439 | 0.0150056 | 3.95519e-05 | 1.55761e-05 | 1(Win) | true |
| simdjson (ondemand) | 701.343 | 0.034517 | 2331.39ms | 11812 | 640 | 19671.2 | 16061.8 | 0.0203275 | 7.34594 | 31.7569 | 6.21656 | 0.0133716 | 1.6006e-05 | 1.58737e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 807.43 | 0.0237337 | 2171.2ms | 11812 | 2560 | 28067.8 | 13951.4 | 0.0760041 | 6.38694 | 28.6059 | 5.80782 | 0.0142617 | 1.80563e-05 | 1.12439e-06 | 1(Win) | true |
| simdjson (ondemand) | 733.299 | 0.0720486 | 2315.13ms | 11812 | 160 | 19600 | 15361.8 | 0.0209573 | 7.03974 | 30.7329 | 5.98468 | 0.0132662 | 4.60337e-05 | 1.21698e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1583.46 | 0.0225975 | 2256.38ms | 25388 | 2560 | 30563.4 | 15290.5 | 0.088396 | 3.25614 | 14.636 | 2.88946 | 0.00702037 | 1.25244e-05 | 4.98513e-06 | 1(Win) | true |
| simdjson (ondemand) | 1489.11 | 0.062608 | 2359.09ms | 25388 | 1280 | 132639 | 16259.3 | 0.216508 | 3.45084 | 15.3562 | 2.89401 | 0.00624714 | 1.52016e-05 | 5.16977e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.29 | 0.0452123 | 2232.45ms | 25388 | 1280 | 55912.4 | 14618.2 | 0.00623116 | 3.09741 | 14.1403 | 2.77655 | 0.00666106 | 1.19397e-05 | 2.6772e-06 | 1(Win) | true |
| simdjson (ondemand) | 1523.38 | 0.0335998 | 2363.99ms | 25388 | 1280 | 36502.6 | 15893.5 | 0.0267919 | 3.38715 | 14.8798 | 2.78612 | 0.00631628 | 1.76018e-05 | 7.50847e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2441.28 | 0.0827511 | 1179.32ms | 11812 | 320 | 4665.62 | 4614.3 | 0.138507 | 2.1272 | 10.5002 | 1.84482 | 0.00268927 | 1.74611e-05 | 3.17474e-06 | 1(Win) | true |
| simdjson (ondemand) | 2026.05 | 0.0293265 | 1274.61ms | 11812 | 4890 | 13000.9 | 5559.98 | 0.1259 | 2.55864 | 11.3506 | 1.89959 | 0.00392352 | 2.38224e-05 | 9.8683e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2509.65 | 0.105371 | 1176.76ms | 11812 | 640 | 14316.8 | 4488.6 | 0.00222781 | 2.06731 | 10.3176 | 1.79961 | 0.00256122 | 1.01856e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 2060.82 | 0.0254554 | 1273.55ms | 11812 | 4890 | 9467.48 | 5466.17 | 0.0965068 | 2.51631 | 11.1641 | 1.85354 | 0.0040262 | 3.14401e-05 | 1.31577e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4389.96 | 0.0375351 | 1272.85ms | 25388 | 2560 | 10971.1 | 5515.28 | 0.0148358 | 1.18078 | 5.69474 | 0.909879 | 0.00164037 | 6.20064e-06 | 8.924e-07 | 1(Win) | true |
| simdjson (ondemand) | 3968.41 | 0.0417345 | 1329.89ms | 25388 | 1280 | 8298.97 | 6101.15 | 0.00693981 | 1.30503 | 5.98925 | 0.914093 | 0.00130266 | 4.95436e-06 | 6.15448e-08 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4587.14 | 0.0533834 | 1268.71ms | 25388 | 1280 | 10162.4 | 5278.21 | 0.0137672 | 1.13045 | 5.61005 | 0.888845 | 0.00147212 | 6.89302e-06 | 1.53862e-06 | 1(Win) | true |
| simdjson (ondemand) | 4017.96 | 0.0315552 | 1330.75ms | 25388 | 2560 | 9256.09 | 6025.91 | 0.125261 | 1.28907 | 5.90247 | 0.892666 | 0.00140802 | 1.14627e-05 | 1.20012e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1816.93 | 0.0311975 | 1341.03ms | 11812 | 4890 | 18294.4 | 6199.91 | 0.0551728 | 2.85018 | 13.6985 | 2.58999 | 0.00688181 | 4.25895e-05 | 1.85593e-05 | 1(Win) | true |
| simdjson (ondemand) | 1630.53 | 0.0511826 | 1408.84ms | 11812 | 2560 | 32009.2 | 6908.68 | 0.00203552 | 3.17514 | 14.0097 | 2.44311 | 0.0077879 | 1.54438e-05 | 1.12439e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1847.91 | 0.0254513 | 1335.77ms | 11812 | 4890 | 11771 | 6095.97 | 0.00110426 | 2.80375 | 13.4944 | 2.54055 | 0.00674519 | 1.68107e-05 | 2.80468e-06 | 1(Win) | true |
| simdjson (ondemand) | 1679.88 | 0.026338 | 1399.06ms | 11812 | 2560 | 7985.35 | 6705.72 | 0.0176591 | 3.08459 | 13.7803 | 2.38859 | 0.00744899 | 3.31694e-05 | 1.03179e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3421.76 | 0.0743153 | 1433.78ms | 25388 | 640 | 17696.8 | 7075.85 | 0.023203 | 1.51525 | 7.19387 | 1.27241 | 0.00365453 | 1.19397e-05 | 5.9083e-06 | 1(Win) | true |
| simdjson (ondemand) | 3262.71 | 0.0511058 | 1466.28ms | 25388 | 1280 | 18409.9 | 7420.79 | 0.0430299 | 1.58216 | 7.20648 | 1.16303 | 0.00342355 | 7.84697e-06 | 1.63094e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3479.23 | 0.0256676 | 1428.76ms | 25388 | 4890 | 15601.6 | 6958.99 | 0.0101404 | 1.4819 | 7.09918 | 1.24941 | 0.0035031 | 1.35806e-05 | 4.41411e-06 | 1(Win) | true |
| simdjson (ondemand) | 3294.85 | 0.0641389 | 1470.17ms | 25388 | 640 | 14217.1 | 7348.41 | 0.020876 | 1.56538 | 7.1197 | 1.1416 | 0.00347531 | 4.61586e-06 | 1.84634e-07 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1663.39 | 0.040514 | 6957.46ms | 108313 | 1280 | 810204 | 62099.4 | 0.0142005 | 3.09119 | 13.8842 | 2.79489 | 0.00364478 | 3.73339e-05 | 2.84188e-05 | 1(Win) | true |
| simdjson (ondemand) | 1491.63 | 0.057927 | 7626.3ms | 108313 | 640 | 1.02987e+06 | 69250 | 0.182929 | 3.3919 | 15.3163 | 2.5203 | 0.00700986 | 7.78992e-06 | 4.16905e-06 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1790.21 | 0.202 | 6740.59ms | 108313 | 30 | 407543 | 57700 | 0.0183675 | 2.88 | 13.1948 | 2.63321 | 0.00338679 | 2.15425e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1604.03 | 0.0377351 | 7364.75ms | 108313 | 2560 | 1.51171e+06 | 64397.4 | 0.0477985 | 3.1742 | 14.6278 | 2.35847 | 0.00665989 | 7.86927e-06 | 2.84188e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2493.1 | 0.0267795 | 7754.96ms | 183677 | 2560 | 906306 | 70261.1 | 0.00299098 | 2.05631 | 8.82701 | 1.6961 | 0.00219405 | 1.08866e-05 | 6.11e-06 | 1(Win) | true |
| simdjson (ondemand) | 2400.46 | 0.0905382 | 8021.89ms | 183677 | 320 | 1.3968e+06 | 72972.6 | 0.0091079 | 2.11471 | 9.60899 | 1.50767 | 0.00462531 | 1.02081e-05 | 6.31203e-06 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2652.79 | 0.05392 | 7510.36ms | 183677 | 640 | 811304 | 66031.7 | 0.0560851 | 1.92673 | 8.42444 | 1.60165 | 0.00198029 | 4.09176e-06 | 1.95656e-06 | 1(Win) | true |
| simdjson (ondemand) | 2553.86 | 0.0677206 | 7756.8ms | 183677 | 640 | 1.38082e+06 | 68589.6 | 0.161303 | 1.98688 | 9.20961 | 1.41372 | 0.00419874 | 1.68264e-05 | 1.11949e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 598.348 | 0.0705695 | 9162.06ms | 108313 | 320 | 4.74939e+06 | 172634 | 0.0308551 | 8.54825 | 38.4444 | 7.71751 | 0.0121972 | 1.28678e-05 | 4.87592e-06 | 1(Win) | true |
| simdjson (ondemand) | 251.968 | 0.199428 | 5330.2ms | 108313 | 30 | 2.00524e+07 | 409955 | 0.116351 | 20.2576 | 90.7172 | 18.5156 | 0.0894669 | 2.9544e-05 | 1.04635e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 617.694 | 0.0561618 | 8988.7ms | 108313 | 640 | 5.64517e+06 | 167227 | 0.0252677 | 8.29755 | 37.7606 | 7.55848 | 0.011268 | 1.57241e-05 | 7.21289e-06 | 1(Win) | true |
| simdjson (ondemand) | 256.623 | 0.11322 | 5243.13ms | 108313 | 80 | 1.66154e+07 | 402518 | 0.00420495 | 19.996 | 90.0324 | 18.3571 | 0.0872873 | 2.63126e-05 | 1.25793e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 921.46 | 0.0338322 | 5040.74ms | 183677 | 640 | 2.64726e+06 | 190098 | 0.0206134 | 5.57821 | 23.9753 | 4.81233 | 0.00651439 | 1.85873e-05 | 1.07441e-05 | 1(Win) | true |
| simdjson (ondemand) | 436.941 | 0.0582219 | 5180.8ms | 183677 | 320 | 1.74336e+07 | 400897 | 0.158662 | 11.6759 | 53.394 | 10.7853 | 0.0468427 | 3.80423e-05 | 2.50269e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 950.937 | 0.124959 | 9928.66ms | 183677 | 40 | 2.11935e+06 | 184206 | 0.0350979 | 5.41278 | 23.5742 | 4.7191 | 0.00632578 | 0.000163058 | 0.000153803 | 1(Win) | true |
| simdjson (ondemand) | 443.125 | 0.0852473 | 5142.98ms | 183677 | 640 | 7.26773e+07 | 395302 | 0.0791326 | 11.5249 | 52.9936 | 10.6925 | 0.0462122 | 4.37249e-05 | 2.78512e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4968.74 | 0.0236415 | 2803.06ms | 108313 | 4890 | 118121 | 20789.1 | 0.0658282 | 1.03388 | 5.56753 | 0.81608 | 0.00110043 | 8.37722e-06 | 5.666e-06 | 1(Win) | true |
| simdjson (ondemand) | 4455.59 | 0.0259558 | 3042.51ms | 108313 | 2560 | 92695.5 | 23183.3 | 0.0379238 | 1.15321 | 5.94996 | 0.775964 | 0.00149105 | 2.39107e-06 | 6.56373e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5229 | 0.0493674 | 2720.95ms | 108313 | 320 | 30433.6 | 19754.3 | 0.00417613 | 0.986409 | 5.40314 | 0.772456 | 0.000850025 | 1.8465e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4630.85 | 0.0758397 | 2973.34ms | 108313 | 160 | 45788.3 | 22305.9 | 0.0470785 | 1.11388 | 5.78547 | 0.732193 | 0.0013622 | 1.01558e-05 | 8.42466e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6779.17 | 0.0396671 | 3309.2ms | 183677 | 1280 | 134471 | 25839.2 | 0.0338337 | 0.758742 | 3.90268 | 0.507816 | 0.000672823 | 2.29258e-06 | 9.9104e-07 | 1(Win) | true |
| simdjson (ondemand) | 6551.83 | 0.0637149 | 3408.6ms | 183677 | 160 | 46428.8 | 26735.8 | 0.00278193 | 0.786796 | 4.08647 | 0.479216 | 0.00095572 | 5.34226e-06 | 4.32144e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7047.28 | 0.0468417 | 3227.4ms | 183677 | 640 | 86758.4 | 24856.1 | 0.0631657 | 0.731442 | 3.80574 | 0.482091 | 0.000521202 | 7.42642e-06 | 5.019e-06 | 1(Win) | true |
| simdjson (ondemand) | 6723.6 | 0.0353748 | 3356.65ms | 183677 | 640 | 54359.3 | 26052.7 | 0.037072 | 0.766935 | 3.98948 | 0.453405 | 0.000864714 | 3.19855e-06 | 2.07565e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3400.86 | 0.100309 | 3766.64ms | 108313 | 160 | 148519 | 30373.3 | 0.0499866 | 1.51275 | 8.05213 | 1.45575 | 0.00144875 | 3.98152e-06 | 6.34735e-07 | 1(Win) | true |
| simdjson (ondemand) | 2650.35 | 0.0269393 | 4629.89ms | 108313 | 4890 | 539056 | 38974.2 | 0.0402458 | 1.934 | 9.92138 | 1.62881 | 0.00342744 | 5.84348e-06 | 2.99443e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3523 | 0.0185331 | 3675.06ms | 108313 | 2560 | 75591.2 | 29320.3 | 0.171255 | 1.46186 | 7.88731 | 1.41192 | 0.00124206 | 2.58222e-06 | 8.1145e-07 | 1(Win) | true |
| simdjson (ondemand) | 2733.3 | 0.0196994 | 4529.92ms | 108313 | 4890 | 271022 | 37791.5 | 0.167658 | 1.87876 | 9.75661 | 1.58497 | 0.00329955 | 2.29397e-06 | 4.07816e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4896.59 | 0.0169941 | 4318.51ms | 183677 | 4890 | 180729 | 35773.4 | 0.0550455 | 1.04896 | 5.38356 | 0.894255 | 0.000874519 | 1.63219e-06 | 4.0749e-07 | 1(Win) | true |
| simdjson (ondemand) | 4114.96 | 0.0388314 | 4979.12ms | 183677 | 2560 | 699495 | 42568.6 | 0.131097 | 1.24567 | 6.41572 | 0.979132 | 0.00202912 | 2.49461e-06 | 9.6552e-07 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5004.98 | 0.0283548 | 4241.26ms | 183677 | 1280 | 126058 | 34998.8 | 0.0659923 | 1.02803 | 5.28637 | 0.868405 | 0.000746283 | 2.49249e-06 | 1.38235e-06 | 1(Win) | true |
| simdjson (ondemand) | 4216.19 | 0.0298913 | 4902.83ms | 183677 | 2560 | 394822 | 41546.6 | 0.00687904 | 1.21487 | 6.3194 | 0.953467 | 0.00194198 | 2.02461e-06 | 7.95384e-07 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 602.017 | 0.192448 | 9073.19ms | 1834197 | 80 | 2.50145e+09 | 2.90561e+06 | 0.266013 | 8.44564 | 34.9435 | 6.32611 | 0.0450189 | 0.137823 | 0.00105697 | 1(Win) | true |
| Jsonifier (generic) | 592.06 | 0.101407 | 9190.24ms | 1834197 | 160 | 1.43621e+09 | 2.95447e+06 | 0.148776 | 8.57576 | 34.1552 | 7.16485 | 0.0368213 | 0.137827 | 0.000853483 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 649.994 | 0.165213 | 9066.99ms | 1834197 | 80 | 1.58144e+09 | 2.69114e+06 | 0.184515 | 7.80458 | 31.9518 | 5.63055 | 0.0441458 | 0.117786 | 0.000682036 | 1(Win) | true |
| Jsonifier (generic) | 643.217 | 0.125893 | 9133.38ms | 1834197 | 160 | 1.87544e+09 | 2.71949e+06 | 0.0597271 | 7.90003 | 31.1627 | 6.4691 | 0.0359463 | 0.11763 | 0.00107678 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2171.48 | 0.19298 | 10046.1ms | 7351818 | 40 | 1.55297e+09 | 3.22878e+06 | 0.188759 | 2.33023 | 9.7344 | 1.61637 | 0.0110037 | 0.0584184 | 0.00177573 | 1(Win) | true |
| Jsonifier (generic) | 2138.92 | 0.277694 | 10227.7ms | 7351818 | 30 | 2.48573e+09 | 3.27793e+06 | 0.284551 | 2.38609 | 9.45964 | 1.83011 | 0.0105024 | 0.0585747 | 0.000614991 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2346.43 | 0.144675 | 10076.3ms | 7351818 | 80 | 1.49504e+09 | 2.98805e+06 | 1.26164 | 2.17064 | 8.98884 | 1.44299 | 0.0108085 | 0.0533853 | 0.00130546 | 1(Win) | true |
| Jsonifier (generic) | 2301.96 | 0.124383 | 10174.5ms | 7351818 | 160 | 2.29634e+09 | 3.04577e+06 | 0.0937409 | 2.21075 | 8.7135 | 1.6566 | 0.010221 | 0.0535192 | 0.00102076 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 388.03 | 0.193951 | 6882.55ms | 1834197 | 30 | 2.29333e+09 | 4.50796e+06 | 1.32431 | 13.0669 | 60.4532 | 13.3451 | 0.0392786 | 0.344397 | 0.00498087 | 1(Win) | true |
| simdjson (ondemand) | 271.263 | 0.092163 | 9684.37ms | 1834197 | 80 | 2.82562e+09 | 6.44845e+06 | 0.265698 | 18.7156 | 101.951 | 21.1749 | 0.050199 | 0.788691 | 0.00364917 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 406.315 | 0.0812067 | 6855.94ms | 1834197 | 80 | 9.77781e+08 | 4.3051e+06 | 0.0741428 | 12.4138 | 57.4684 | 12.6515 | 0.0380977 | 0.323196 | 0.00130415 | 1(Win) | true |
| simdjson (ondemand) | 280.734 | 0.11341 | 9707.44ms | 1834197 | 30 | 1.49804e+09 | 6.23091e+06 | 0.0646443 | 18.1388 | 98.9655 | 20.481 | 0.0491731 | 0.767355 | 0.0139982 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1309.15 | 0.291058 | 8065.23ms | 7351818 | 40 | 9.71916e+09 | 5.35555e+06 | 0.00736113 | 3.88213 | 16.0203 | 3.37909 | 0.0110902 | 0.185536 | 0.00532174 | 1(Win) | true |
| simdjson (ondemand) | 898.052 | 0.258165 | 5441.68ms | 7351818 | 30 | 1.21872e+10 | 7.80716e+06 | 0.0458365 | 5.69265 | 26.4531 | 5.32127 | 0.0126643 | 0.43518 | 0.00699387 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1363.31 | 0.328076 | 8175.04ms | 7351818 | 40 | 1.13869e+10 | 5.14279e+06 | 0.172642 | 3.73672 | 15.2754 | 3.20597 | 0.0107995 | 0.180269 | 0.00516621 | 1(Win) | true |
| simdjson (ondemand) | 942.359 | 0.187198 | 5386.22ms | 7351818 | 40 | 7.75921e+09 | 7.44009e+06 | 0.278742 | 5.38891 | 25.708 | 5.14811 | 0.0123912 | 0.429783 | 0.00181287 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5004.53 | 0.0418957 | 9137ms | 1834197 | 640 | 1.37241e+07 | 349529 | 0.138831 | 1.02107 | 5.69891 | 0.827984 | 0.000707447 | 0.0756114 | 2.46106e-06 | 1(Win) | true |
| simdjson (ondemand) | 4290.58 | 0.0398044 | 5281.49ms | 1834197 | 640 | 1.6854e+07 | 407690 | 0.0552682 | 1.18441 | 6.52919 | 0.874485 | 0.00494846 | 0.0754727 | 4.59499e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5020.04 | 0.0487657 | 9110.92ms | 1834197 | 320 | 9.23968e+06 | 348448 | 0.176806 | 1.02136 | 5.69871 | 0.827937 | 0.000710691 | 0.0755821 | 1.63048e-06 | 1(Win) | true |
| simdjson (ondemand) | 4289.98 | 0.0742648 | 5276.16ms | 1834197 | 160 | 1.46712e+07 | 407747 | 0.219137 | 1.1847 | 6.52899 | 0.874438 | 0.00494396 | 0.0754424 | 3.30526e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10083.5 | 0.0945513 | 8943.15ms | 7351818 | 320 | 1.38311e+08 | 695321 | 0.27466 | 0.50454 | 2.27778 | 0.23517 | 0.00143573 | 0.0423942 | 0.000293976 | 1(Win) | true |
| simdjson (ondemand) | 9633.86 | 0.0446238 | 9372.06ms | 7351818 | 640 | 6.74997e+07 | 727771 | 0.0131345 | 0.531699 | 2.64676 | 0.256657 | 0.000969951 | 0.0424154 | 0.000163291 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10215.1 | 0.0774102 | 8870.48ms | 7351818 | 640 | 1.80668e+08 | 686361 | 0.103298 | 0.500436 | 2.27773 | 0.235159 | 0.00136953 | 0.0423776 | 0.000188147 | 1(Win) | true |
| simdjson (ondemand) | 9640.74 | 0.11077 | 9247.63ms | 7351818 | 80 | 5.19161e+07 | 727251 | 0.0257479 | 0.530285 | 2.64671 | 0.256645 | 0.000969463 | 0.0424042 | 0.000140511 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3142.65 | 0.51235 | 7192.48ms | 1834197 | 160 | 1.30123e+09 | 556608 | 0.629875 | 1.63667 | 8.50401 | 1.52924 | 0.000657682 | 0.113275 | 2.51813e-06 | 1(Win) | true |
| simdjson (ondemand) | 2218.36 | 0.163756 | 5049.67ms | 1834197 | 320 | 5.33546e+08 | 788524 | 0.0881739 | 2.30018 | 12.8396 | 2.27677 | 0.00496616 | 0.150668 | 5.42131e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3092.98 | 0.373548 | 7259.7ms | 1834197 | 320 | 1.42817e+09 | 565547 | 0.0413604 | 1.65252 | 8.50381 | 1.52919 | 0.000761132 | 0.113217 | 3.75164e-06 | 1(Win) | true |
| simdjson (ondemand) | 2209.49 | 0.242136 | 5030.24ms | 1834197 | 80 | 2.93977e+08 | 791686 | 0.0271077 | 2.31193 | 12.8394 | 2.27673 | 0.00488526 | 0.150598 | 4.89315e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7721.85 | 0.136674 | 5784.68ms | 7351818 | 160 | 2.46398e+08 | 907975 | 0.0064867 | 0.661578 | 2.97762 | 0.41013 | 0.00133331 | 0.0635767 | 0.000189963 | 1(Win) | true |
| simdjson (ondemand) | 5977.98 | 0.0942494 | 7445.72ms | 7351818 | 320 | 3.9101e+08 | 1.17284e+06 | 0.760832 | 0.856523 | 4.22114 | 0.606513 | 0.000991566 | 0.0847846 | 0.000361898 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7694.53 | 0.225132 | 5824.46ms | 7351818 | 80 | 3.36658e+08 | 911198 | 0.279849 | 0.665686 | 2.97757 | 0.410118 | 0.00141679 | 0.0635585 | 0.000230531 | 1(Win) | true |
| simdjson (ondemand) | 5942.84 | 0.183878 | 7474.15ms | 7351818 | 160 | 7.52974e+08 | 1.17978e+06 | 0.0671105 | 0.860384 | 4.22109 | 0.606501 | 0.00102076 | 0.084758 | 0.000517061 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1354.91 | 0.230726 | 7598.13ms | 409725 | 40 | 1.77099e+07 | 288391 | 0.161369 | 3.75304 | 18.0203 | 3.50719 | 0.00902136 | 0.0228997 | 2.45286e-05 | 1(Win) | true |
| simdjson (ondemand) | 983.729 | 0.167849 | 5153.93ms | 409725 | 40 | 1.778e+07 | 397207 | 0.316677 | 5.15882 | 19.9526 | 3.79085 | 0.0166393 | 0.0350317 | 1.70236e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1725.44 | 0.181268 | 7115.03ms | 409725 | 80 | 1.34808e+07 | 226460 | 0.0231885 | 2.94805 | 15.1566 | 2.85924 | 0.00607331 | 0.00667457 | 2.22405e-05 | 1(Win) | true |
| simdjson (ondemand) | 1159.93 | 0.202411 | 9884ms | 409725 | 40 | 1.85974e+07 | 336870 | 0.0282013 | 4.3696 | 17.1013 | 3.14597 | 0.0128806 | 0.0117146 | 1.07389e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2024.06 | 0.113126 | 8345.1ms | 676745 | 320 | 4.16369e+07 | 318862 | 0.132288 | 2.48967 | 11.49 | 2.13972 | 0.00602367 | 0.0278802 | 6.40474e-06 | 1(Win) | true |
| simdjson (ondemand) | 1546.07 | 0.0871952 | 5385.31ms | 676745 | 80 | 1.05991e+07 | 417442 | 0.322534 | 3.27171 | 12.6587 | 2.32 | 0.0105905 | 0.0363365 | 1.60326e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2513.34 | 0.0777698 | 7865.15ms | 676745 | 1280 | 5.1048e+07 | 256787 | 0.145231 | 1.9969 | 9.76068 | 1.74851 | 0.00406955 | 0.0108785 | 4.96286e-06 | 1(Win) | true |
| simdjson (ondemand) | 1844.26 | 0.0737244 | 5162.19ms | 676745 | 160 | 1.065e+07 | 349947 | 0.0961755 | 2.78622 | 10.9319 | 1.92954 | 0.00831169 | 0.01915 | 7.76234e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.431 | 0.186979 | 6145.66ms | 409725 | 30 | 2.36177e+07 | 474532 | 0.0141985 | 6.16654 | 28.7842 | 5.82221 | 0.0143735 | 0.0239285 | 5.1742e-05 | 1(Win) | true |
| simdjson (ondemand) | 481.664 | 0.0647706 | 5216.07ms | 409725 | 160 | 4.41746e+07 | 811238 | 0.151627 | 10.6335 | 46.7674 | 9.42949 | 0.0352755 | 0.0393142 | 2.54286e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 943.68 | 0.0625954 | 5912.6ms | 409725 | 320 | 2.14966e+07 | 414064 | 0.119332 | 5.39432 | 25.9311 | 5.17475 | 0.0113568 | 0.00648105 | 4.622e-06 | 1(Win) | true |
| simdjson (ondemand) | 522.397 | 0.0743081 | 5077.97ms | 409725 | 160 | 4.94283e+07 | 747983 | 0.0638894 | 9.78542 | 43.9211 | 8.78386 | 0.0313973 | 0.013734 | 2.06541e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.07 | 0.0711145 | 6696.58ms | 676745 | 40 | 5.44421e+06 | 518775 | 0.551974 | 4.05958 | 18.3054 | 3.67641 | 0.00786445 | 0.0283146 | 2.9036e-05 | 1(Win) | true |
| simdjson (ondemand) | 794.601 | 0.188391 | 5210.64ms | 676745 | 160 | 3.74621e+08 | 812225 | 0.240682 | 6.44353 | 28.7093 | 5.69338 | 0.0202863 | 0.0427947 | 4.57429e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1413.83 | 0.0826115 | 6484.21ms | 676745 | 640 | 9.10154e+07 | 456485 | 0.0892219 | 3.57661 | 16.5774 | 3.28434 | 0.00618382 | 0.0114099 | 5.43964e-06 | 1(Win) | true |
| simdjson (ondemand) | 853.953 | 0.127004 | 5092.98ms | 676745 | 30 | 2.76399e+07 | 755773 | 0.00835278 | 5.94182 | 26.9857 | 5.30236 | 0.018028 | 0.0186934 | 2.19679e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2429.93 | 0.0422089 | 8605.99ms | 409725 | 640 | 2.94839e+06 | 160804 | 0.0110161 | 2.08964 | 10.159 | 1.78364 | 0.00542289 | 0.00141061 | 3.90315e-05 | 1(Win) | true |
| simdjson (ondemand) | 1937.63 | 0.0436972 | 5359.09ms | 409725 | 640 | 4.96972e+06 | 201661 | 0.191886 | 2.64161 | 10.8106 | 1.83693 | 0.00728311 | 0.0025961 | 1.04338e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2817.84 | 0.0232488 | 8432.73ms | 409725 | 2560 | 2.66069e+06 | 138668 | 0.242742 | 1.80756 | 9.16679 | 1.55604 | 0.00405757 | 0.000481684 | 3.53515e-06 | 1(Win) | true |
| simdjson (ondemand) | 2160.38 | 0.0746118 | 5237.24ms | 409725 | 160 | 2.91381e+06 | 180869 | 0.0181691 | 2.35048 | 9.82371 | 1.60777 | 0.00547266 | 0.00108167 | 2.13558e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3518.14 | 0.0530073 | 9783.44ms | 676745 | 1280 | 1.21034e+07 | 183448 | 0.00304209 | 1.44102 | 6.78443 | 1.11455 | 0.00380622 | 0.00147277 | 1.88056e-05 | 1(Win) | true |
| simdjson (ondemand) | 3007.44 | 0.0446316 | 5681.11ms | 676745 | 640 | 5.87114e+06 | 214599 | 0.0491863 | 1.69886 | 7.01045 | 1.11296 | 0.00462198 | 0.00347399 | 5.5343e-06 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3992.44 | 0.102818 | 9619.99ms | 676745 | 320 | 8.84026e+06 | 161654 | 0.0666296 | 1.26895 | 6.18355 | 0.976767 | 0.00281161 | 0.000849951 | 8.12714e-07 | 1(Win) | true |
| simdjson (ondemand) | 3340.78 | 0.0873202 | 5623.54ms | 676745 | 160 | 4.55306e+06 | 193187 | 0.0329842 | 1.53017 | 6.41319 | 0.974404 | 0.00386757 | 0.0025016 | 3.11232e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1872.2 | 0.04451 | 5520.75ms | 409725 | 640 | 5.52299e+06 | 208708 | 0.0366885 | 2.72646 | 13.0925 | 2.45643 | 0.00872305 | 0.00142432 | 8.24486e-06 | 1(Win) | true |
| simdjson (ondemand) | 1415 | 0.107685 | 7203.4ms | 409725 | 80 | 7.07415e+06 | 276144 | 0.0430658 | 3.59957 | 14.7661 | 2.67877 | 0.0117912 | 0.00336515 | 6.46775e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2076.62 | 0.0349904 | 5415.02ms | 409725 | 1280 | 5.54853e+06 | 188163 | 0.0940708 | 2.45421 | 12.0765 | 2.22347 | 0.00748932 | 0.000527524 | 2.69617e-06 | 1(Win) | true |
| simdjson (ondemand) | 1537.18 | 0.143768 | 7110.83ms | 409725 | 40 | 5.34219e+06 | 254195 | 0.0868593 | 3.33039 | 13.7539 | 2.44449 | 0.010619 | 0.00137604 | 6.22369e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2689.77 | 0.0518119 | 6302.95ms | 676745 | 1280 | 1.97829e+07 | 239944 | 0.00656772 | 1.88167 | 8.60809 | 1.5378 | 0.00586787 | 0.00178927 | 2.26429e-05 | 1(Win) | true |
| simdjson (ondemand) | 2225.72 | 0.0361599 | 7583.55ms | 676745 | 640 | 7.03627e+06 | 289971 | 0.262315 | 2.30059 | 9.45956 | 1.63397 | 0.00792265 | 0.00388735 | 1.29619e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2962.87 | 0.189581 | 6195.34ms | 676745 | 160 | 2.72858e+07 | 217828 | 0.0714132 | 1.70398 | 7.98991 | 1.396 | 0.00481335 | 0.00115443 | 4.24828e-06 | 1(Win) | true |
| simdjson (ondemand) | 2414.74 | 0.0374416 | 7474.07ms | 676745 | 640 | 6.40909e+06 | 267272 | 0.0477468 | 2.1206 | 8.84694 | 1.49224 | 0.00695014 | 0.00258292 | 2.1934e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1937.01 | 0.0525553 | 7040.62ms | 264040 | 2560 | 1.19495e+07 | 129999 | 0.0936941 | 2.62449 | 10.2968 | 1.89243 | 0.00581706 | 6.10733e-05 | 9.41352e-06 | 1(Win) | true |
| simdjson (ondemand) | 1735.98 | 0.0898021 | 7818.84ms | 264040 | 640 | 1.08594e+07 | 145053 | 0.0506897 | 2.92632 | 10.7024 | 1.82911 | 0.00873239 | 0.000504096 | 1.15099e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2302.33 | 0.347401 | 6429.41ms | 264040 | 80 | 1.15493e+07 | 109371 | 0.0820499 | 2.199 | 8.9289 | 1.57967 | 0.00549486 | 2.16823e-05 | 5.20754e-06 | 1(Win) | true |
| simdjson (ondemand) | 1936.34 | 0.102503 | 7615.8ms | 264040 | 640 | 1.13717e+07 | 130043 | 0.232711 | 2.61151 | 9.33722 | 1.5185 | 0.0114237 | 5.36614e-05 | 3.50326e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2470.59 | 0.0567294 | 7496.17ms | 360584 | 1280 | 7.98067e+06 | 139190 | 0.0844581 | 2.04707 | 7.99867 | 1.40003 | 0.00415084 | 0.000354663 | 7.64602e-06 | 1(Win) | true |
| simdjson (ondemand) | 2151.23 | 0.058334 | 8577.25ms | 360584 | 1280 | 1.11299e+07 | 159852 | 0.218381 | 2.36275 | 8.22613 | 1.3562 | 0.0102339 | 0.00183731 | 1.29131e-05 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2837.08 | 0.0637906 | 7336.37ms | 360584 | 1280 | 7.65232e+06 | 121209 | 0.0370211 | 1.7879 | 6.99195 | 1.17014 | 0.0054779 | 4.4574e-05 | 5.2129e-06 | 1(Win) | true |
| simdjson (ondemand) | 2526 | 0.0732564 | 8116.85ms | 360584 | 1280 | 1.27306e+07 | 136136 | 0.0948065 | 1.99288 | 7.22621 | 1.12869 | 0.00830203 | 7.25819e-05 | 1.12881e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 657.264 | 0.206193 | 9894.6ms | 264040 | 80 | 4.99228e+07 | 383116 | 0.128004 | 7.70924 | 28.633 | 5.43237 | 0.0240715 | 0.00200765 | 7.44205e-05 | 1(Win) | true |
| simdjson (ondemand) | 310.398 | 0.0976065 | 5137.42ms | 264040 | 320 | 2.00636e+08 | 811243 | 0.435585 | 16.2303 | 64.3159 | 13.0753 | 0.0894179 | 0.000395122 | 0.00014219 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.275 | 0.196308 | 9608.23ms | 264040 | 80 | 3.87483e+07 | 354522 | 0.0658749 | 7.21601 | 27.2615 | 5.11919 | 0.0218157 | 0.000518577 | 2.21557e-05 | 1(Win) | true |
| simdjson (ondemand) | 321.827 | 0.312433 | 5085.25ms | 264040 | 40 | 2.39039e+08 | 782433 | 0.214322 | 15.6446 | 62.9517 | 12.7655 | 0.0846923 | 4.9235e-05 | 1.4013e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 851.776 | 0.0798126 | 5230.71ms | 360584 | 640 | 6.64485e+07 | 403721 | 0.0652489 | 5.93 | 22.0427 | 4.19662 | 0.0156637 | 0.00502096 | 8.2453e-05 | 1(Win) | true |
| simdjson (ondemand) | 444.78 | 0.0738982 | 9898.49ms | 360584 | 640 | 2.08916e+08 | 773146 | 0.144005 | 11.3552 | 46.8803 | 9.45609 | 0.052548 | 0.00216866 | 9.83171e-05 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 912.065 | 0.110392 | 5091.09ms | 360584 | 320 | 5.54355e+07 | 377034 | 0.23097 | 5.57487 | 21.0424 | 3.96863 | 0.0142182 | 0.00170635 | 2.23509e-05 | 1(Win) | true |
| simdjson (ondemand) | 460.308 | 0.0751136 | 9791.79ms | 360584 | 640 | 2.01527e+08 | 747064 | 0.0902196 | 10.9341 | 45.8805 | 9.22901 | 0.0494824 | 0.000270421 | 5.1817e-05 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6835.81 | 0.0281896 | 4420.15ms | 264040 | 4890 | 527285 | 36836.6 | 0.191569 | 0.742528 | 3.61408 | 0.46821 | 0.00134443 | 1.92231e-06 | 6.95501e-07 | 1(Win) | true |
| simdjson (ondemand) | 6054.28 | 0.0684974 | 4891.94ms | 264040 | 160 | 129862 | 41591.7 | 0.0401533 | 0.837042 | 3.99731 | 0.439348 | 0.000975018 | 2.08302e-06 | 1.11252e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7022.56 | 0.0675028 | 4370.67ms | 264040 | 4890 | 2.86485e+06 | 35857.1 | 0.00583553 | 0.723267 | 3.53548 | 0.450299 | 0.0013483 | 1.30062e-05 | 1.03768e-05 | 1(Win) | true |
| simdjson (ondemand) | 6218.19 | 0.052952 | 4835.46ms | 264040 | 320 | 147138 | 40495.4 | 0.0260147 | 0.814838 | 3.91861 | 0.421431 | 0.000969964 | 2.84048e-06 | 1.90549e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7823.84 | 0.121854 | 5156.04ms | 360584 | 80 | 229479 | 43952.8 | 0.1882 | 0.653764 | 3.11489 | 0.361203 | 0.00121151 | 4.92257e-06 | 3.67459e-06 | 1(Win) | true |
| simdjson (ondemand) | 7295.24 | 0.0254124 | 5442.2ms | 360584 | 2560 | 367337 | 47137.6 | 0.0377753 | 0.692906 | 3.31676 | 0.338541 | 0.000753346 | 2.94553e-06 | 1.47005e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7967.67 | 0.05215 | 5108.33ms | 360584 | 1280 | 648438 | 43159.4 | 0.324598 | 0.6392 | 3.05734 | 0.348088 | 0.00122561 | 8.49317e-07 | 1.81996e-07 | 1(Win) | true |
| simdjson (ondemand) | 7480.16 | 0.0269943 | 5391.87ms | 360584 | 1280 | 197126 | 45972.2 | 0.0976911 | 0.677062 | 3.25914 | 0.325421 | 0.000760882 | 1.52747e-06 | 3.3366e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4704.54 | 0.067937 | 6043.04ms | 264040 | 640 | 846248 | 53524.5 | 0.0277287 | 1.07642 | 5.32372 | 0.874159 | 0.00217223 | 1.24271e-06 | 2.89966e-07 | 1(Win) | true |
| simdjson (ondemand) | 4028.32 | 0.0949845 | 7030.88ms | 264040 | 160 | 564050 | 62509.5 | 0.00600945 | 1.26523 | 6.33596 | 0.950828 | 0.00212184 | 1.3729e-06 | 3.31389e-07 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4837.37 | 0.0366528 | 5987.62ms | 264040 | 2560 | 931914 | 52054.7 | 0.169137 | 1.05383 | 5.24523 | 0.856219 | 0.00215152 | 5.175e-06 | 3.27839e-06 | 1(Win) | true |
| simdjson (ondemand) | 4053.87 | 0.137411 | 6989.69ms | 264040 | 320 | 2.33128e+06 | 62115.4 | 0.0384117 | 1.2484 | 6.25726 | 0.93291 | 0.00212744 | 5.88216e-06 | 4.09502e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5677.15 | 0.0243689 | 6779.33ms | 360584 | 4890 | 1.06545e+06 | 60572.6 | 0.0696265 | 0.899979 | 4.37729 | 0.666017 | 0.00145519 | 3.27122e-06 | 1.61576e-06 | 1(Win) | true |
| simdjson (ondemand) | 5003.04 | 0.07084 | 7656.49ms | 360584 | 320 | 758668 | 68734.2 | 0.0386621 | 1.01531 | 5.0398 | 0.715319 | 0.00186235 | 4.31592e-06 | 1.81996e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5805.81 | 0.093671 | 6723.47ms | 360584 | 4890 | 1.50524e+07 | 59230.3 | 0.0198741 | 0.882735 | 4.31988 | 0.652899 | 0.00144324 | 6.68706e-06 | 3.98467e-06 | 1(Win) | true |
| simdjson (ondemand) | 5049 | 0.0764143 | 7595.62ms | 360584 | 4890 | 1.32452e+07 | 68108.5 | 0.00585688 | 1.00135 | 4.98217 | 0.702199 | 0.00185217 | 6.23336e-06 | 3.38975e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1968.33 | 0.0434378 | 846.443ms | 2632 | 4890 | 1500.45 | 1275.23 | 0.025215 | 2.69426 | 10.9612 | 1.9905 | 0.000832681 | 4.08687e-05 | 6.68196e-06 | 1(Win) | true |
| simdjson (ondemand) | 1549.74 | 0.128417 | 876.314ms | 2632 | 40 | 173.046 | 1619.67 | 0.0776302 | 3.40956 | 11.7238 | 2.15843 | 0.00384688 | 1.8997e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2550.3 | 0.0765645 | 823.322ms | 2632 | 2560 | 1453.73 | 984.225 | 0.0905719 | 2.10083 | 9.09157 | 1.54977 | 0.000791787 | 5.50615e-05 | 1.06858e-05 | 1(Win) | true |
| simdjson (ondemand) | 1862.9 | 0.0713221 | 857.044ms | 2632 | 2560 | 2364.18 | 1347.4 | 0.103751 | 2.84415 | 9.88906 | 1.73062 | 0.0026759 | 3.25026e-05 | 2.96828e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2357.97 | 0.160038 | 866.41ms | 3370 | 640 | 3045.17 | 1362.99 | 0.0135254 | 2.25605 | 9.0276 | 1.58012 | 0.000532734 | 0.000197515 | 0.000135386 | 1(Win) | true |
| simdjson (ondemand) | 1952.05 | 0.07106 | 882.995ms | 3370 | 4890 | 6693.25 | 1646.41 | 0.0489484 | 2.70111 | 9.39021 | 1.68338 | 0.00226648 | 5.29149e-05 | 1.02553e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3004.01 | 0.18691 | 835.107ms | 3370 | 1280 | 5118.35 | 1069.86 | 0.0585991 | 1.77646 | 7.4911 | 1.22048 | 0.00060089 | 3.24555e-05 | 2.08642e-06 | 1(Win) | true |
| simdjson (ondemand) | 2290.65 | 0.0577563 | 867.363ms | 3370 | 2560 | 1681.05 | 1403.04 | 0.0388234 | 2.3026 | 8.03323 | 1.36469 | 0.0015414 | 3.4426e-05 | 7.07066e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1248.24 | 0.0524409 | 918.844ms | 2632 | 2560 | 2846.79 | 2010.89 | 0.0406158 | 4.20742 | 16.5034 | 3.24506 | 0.00318155 | 6.94576e-05 | 2.24105e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.119 | 0.0397263 | 1070.62ms | 2632 | 4890 | 9454.84 | 3500.22 | 0.0455018 | 7.25772 | 29.5144 | 5.97493 | 0.0131326 | 4.87161e-05 | 1.50733e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1438.17 | 0.0429157 | 901.601ms | 2632 | 4890 | 2743.44 | 1745.33 | 0.0170064 | 3.66151 | 14.6155 | 2.80395 | 0.0046386 | 6.65865e-05 | 2.13667e-05 | 1(Win) | true |
| simdjson (ondemand) | 787.642 | 0.0515992 | 1044.85ms | 2632 | 1280 | 3461.07 | 3186.82 | 0.00877562 | 6.61804 | 27.6782 | 5.54597 | 0.0110078 | 3.91812e-05 | 7.71752e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.31 | 0.0839358 | 931.535ms | 3370 | 1280 | 4051.24 | 2119.54 | 0.0432542 | 3.45773 | 13.4852 | 2.62819 | 0.00305615 | 6.69974e-05 | 3.08327e-05 | 1(Win) | true |
| simdjson (ondemand) | 938.308 | 0.0617924 | 1059.85ms | 3370 | 640 | 2866.94 | 3425.19 | 0.0777934 | 5.55306 | 23.035 | 4.60979 | 0.00807307 | 2.27188e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1716.1 | 0.0648439 | 914.533ms | 3370 | 320 | 471.917 | 1872.79 | 0.0444054 | 3.06642 | 12.0148 | 2.28368 | 0.00388817 | 4.26558e-05 | 2.7819e-06 | 1(Win) | true |
| simdjson (ondemand) | 1011.94 | 0.130833 | 1045.38ms | 3370 | 40 | 690.64 | 3175.97 | 0.0643261 | 5.15512 | 21.6774 | 4.29021 | 0.00772997 | 1.48368e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3253.18 | 0.128879 | 790.342ms | 2632 | 1280 | 1265.69 | 771.574 | 0.198972 | 1.66078 | 7.05775 | 1.16641 | 0.000384688 | 2.49335e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2393.95 | 0.0801174 | 818.044ms | 2632 | 160 | 112.906 | 1048.51 | 0.0256383 | 2.23201 | 8.10904 | 1.3883 | 0.00167648 | 1.8997e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3972.82 | 0.0971633 | 778.84ms | 2632 | 640 | 241.19 | 631.811 | 0.390448 | 1.37691 | 6.03381 | 0.921733 | 0.00101218 | 1.48414e-05 | 4.15559e-06 | 1(Win) | true |
| simdjson (ondemand) | 2781.55 | 0.156606 | 805.133ms | 2632 | 40 | 79.8872 | 902.4 | 0.0110828 | 1.93523 | 7.08283 | 1.1421 | 0.00139628 | 0 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3728.3 | 0.110332 | 800.357ms | 3370 | 2560 | 2315.7 | 862.024 | 0.00557404 | 1.44887 | 5.94392 | 0.933828 | 0.000430847 | 3.19918e-05 | 1.13594e-05 | 1(Win) | true |
| simdjson (ondemand) | 3079.02 | 0.148518 | 818.4ms | 3370 | 30 | 72.0966 | 1043.8 | 0.102086 | 1.73489 | 6.4635 | 1.05905 | 0.000544016 | 1.97824e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4462.68 | 0.219258 | 789.013ms | 3370 | 160 | 398.934 | 720.169 | 0.167215 | 1.21896 | 5.14421 | 0.74273 | 0.000795623 | 2.96736e-05 | 7.4184e-06 | 1(Win) | true |
| simdjson (ondemand) | 3595.5 | 0.0520749 | 805.867ms | 3370 | 4890 | 1059.52 | 893.863 | 0.0746636 | 1.49669 | 5.66202 | 0.866766 | 0.00059511 | 2.83386e-05 | 4.12639e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2337.83 | 0.106957 | 821.04ms | 2632 | 160 | 211.001 | 1073.67 | 0.133707 | 2.28303 | 9.32371 | 1.7424 | 0.00152688 | 4.27432e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 2090.83 | 0.0678999 | 834.138ms | 2632 | 160 | 106.314 | 1200.51 | 0.0573 | 2.54396 | 9.8712 | 1.76102 | 0.0021989 | 3.32447e-05 | 2.37462e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2753.88 | 0.113849 | 808.204ms | 2632 | 1280 | 1378.31 | 911.466 | 0.107883 | 1.95491 | 8.30586 | 1.49582 | 0.0014031 | 1.36541e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2360.38 | 0.0556855 | 823.053ms | 2632 | 320 | 112.213 | 1063.42 | 0.0964802 | 2.26552 | 8.84498 | 1.51482 | 0.00247792 | 1.78097e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2849.55 | 0.0460469 | 828.499ms | 3370 | 4890 | 1318.91 | 1127.86 | 0.0179213 | 1.86792 | 7.74807 | 1.39229 | 0.000594625 | 3.84725e-05 | 4.91526e-06 | 1(Win) | true |
| simdjson (ondemand) | 2693.2 | 0.0636207 | 835.538ms | 3370 | 160 | 92.2229 | 1193.33 | 0.14949 | 1.97529 | 7.83976 | 1.35015 | 0.00107567 | 7.4184e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3285.17 | 0.056525 | 813.925ms | 3370 | 4890 | 1495.32 | 978.301 | 0.146817 | 1.63208 | 6.95312 | 1.1997 | 0.000891543 | 2.56686e-05 | 4.4298e-06 | 1(Win) | true |
| simdjson (ondemand) | 3043.55 | 0.0433421 | 823.851ms | 3370 | 640 | 134.06 | 1055.96 | 0.00103577 | 1.75702 | 7.03828 | 1.15786 | 0.00133763 | 1.90096e-05 | 2.7819e-06 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 795.764 | 0.0705199 | 1273.76ms | 4630 | 640 | 9799.33 | 5548.77 | 0.0282237 | 6.51519 | 31.4104 | 5.75616 | 0.00386373 | 3.03726e-05 | 1.11366e-05 | 1(Win) | true |
| Jsonifier (generic) | 677.442 | 0.0335232 | 1374.98ms | 4630 | 4890 | 23346.3 | 6517.92 | 0.0758223 | 7.69052 | 31.9069 | 6.44946 | 0.0102695 | 5.94063e-05 | 1.98757e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 962.134 | 0.0948741 | 1276.84ms | 4630 | 4890 | 92703.4 | 4589.29 | 0.283763 | 5.40154 | 26.7134 | 4.68165 | 0.00257828 | 5.68004e-05 | 2.32767e-05 | 1(Win) | true |
| Jsonifier (generic) | 783.231 | 0.0529674 | 1377.79ms | 4630 | 2560 | 22826.6 | 5637.56 | 0.0551434 | 6.61514 | 27.222 | 5.37797 | 0.00811403 | 3.52659e-05 | 6.15888e-06 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1867.7 | 0.175167 | 1315.69ms | 11579 | 2560 | 274582 | 5912.4 | 0.0869626 | 2.76262 | 13.3566 | 2.33621 | 0.00167002 | 7.55004e-05 | 3.90659e-05 | 1(Win) | true |
| Jsonifier (generic) | 1627.76 | 0.0932376 | 1402.66ms | 11579 | 2560 | 102420 | 6783.92 | 0.118758 | 3.17549 | 13.5964 | 2.61232 | 0.00365796 | 3.00585e-05 | 1.06267e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2253.95 | 0.0458121 | 1309.09ms | 11579 | 320 | 1612 | 4899.22 | 0.0915524 | 2.30551 | 11.5071 | 1.91165 | 0.000584571 | 1.45738e-05 | 2.42897e-06 | 1(Win) | true |
| Jsonifier (generic) | 1856 | 0.107122 | 1419.48ms | 11579 | 320 | 12998.5 | 5949.68 | 0.0727459 | 2.79142 | 11.8126 | 2.2046 | 0.00354737 | 2.15908e-05 | 4.31816e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 715.505 | 0.0707993 | 1342.7ms | 4630 | 2560 | 48869.2 | 6171.18 | 0.0520231 | 7.21837 | 35.7575 | 6.7108 | 0.00427232 | 9.05271e-05 | 4.47995e-05 | 1(Win) | true |
| Jsonifier (generic) | 635.202 | 0.0620834 | 1417.69ms | 4630 | 1280 | 23839.6 | 6951.35 | 0.0968713 | 8.14834 | 34.813 | 7.08942 | 0.0107873 | 4.70775e-05 | 2.05859e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 829.147 | 0.0783014 | 1352.05ms | 4630 | 2560 | 44512.1 | 5325.37 | 0.134083 | 6.24723 | 31.1821 | 5.66436 | 0.0028978 | 4.17623e-05 | 1.19803e-05 | 1(Win) | true |
| Jsonifier (generic) | 738.742 | 0.0916055 | 1421.32ms | 4630 | 30 | 899.375 | 5977.07 | 0.0217451 | 7.15 | 30.265 | 6.04924 | 0.00945284 | 2.87977e-05 | 0 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1698.16 | 0.202572 | 1410.22ms | 11579 | 40 | 6940.73 | 6502.7 | 0.0988355 | 3.05323 | 15.138 | 2.72675 | 0.00185897 | 3.02271e-05 | 4.31816e-06 | 1(Win) | true |
| Jsonifier (generic) | 1530.38 | 0.0515207 | 1449.89ms | 11579 | 160 | 2211.19 | 7215.57 | 0.128031 | 3.38587 | 14.815 | 2.88091 | 0.00339516 | 3.72441e-05 | 2.21306e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1975.25 | 0.0616756 | 1380.45ms | 11579 | 1280 | 15217.1 | 5590.47 | 0.132754 | 2.62591 | 13.2742 | 2.30098 | 0.000961331 | 1.41015e-05 | 4.52058e-06 | 1(Win) | true |
| Jsonifier (generic) | 1743.58 | 0.0747413 | 1450.26ms | 11579 | 1280 | 28680.5 | 6333.27 | 0.0258612 | 2.9771 | 12.9794 | 2.46196 | 0.0034212 | 2.4762e-05 | 8.50138e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7182.18 | 0.100111 | 773.373ms | 4630 | 160 | 60.6086 | 614.788 | 0.134013 | 0.762589 | 3.56566 | 0.463715 | 0.000431965 | 2.29482e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6504.02 | 0.0244529 | 777.014ms | 4630 | 2560 | 70.5506 | 678.89 | 0.0546917 | 0.838457 | 4.1149 | 0.492441 | 0.000431965 | 1.73799e-05 | 1.8561e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7326.36 | 0.0619173 | 771.215ms | 4630 | 2560 | 356.493 | 602.689 | 0.214139 | 0.748735 | 3.53218 | 0.45594 | 0.000432387 | 2.10077e-05 | 6.83383e-06 | 1(Win) | true |
| simdjson (ondemand) | 6669.67 | 0.131629 | 775.285ms | 4630 | 1280 | 972.003 | 662.029 | 0.0216002 | 0.821282 | 4.07991 | 0.484665 | 0.000432809 | 1.02929e-05 | 2.19357e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12132.3 | 0.0368017 | 805.246ms | 11579 | 1280 | 143.616 | 910.182 | 0.00952672 | 0.442742 | 2.126 | 0.20874 | 0.000172726 | 8.36644e-06 | 3.37356e-07 | 1(Win) | true |
| simdjson (ondemand) | 10936.9 | 0.0491479 | 811.577ms | 11579 | 4890 | 1204.14 | 1009.67 | 0.03014 | 0.489019 | 2.45064 | 0.231799 | 0.000173044 | 7.50601e-06 | 5.12175e-07 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12210.8 | 0.0472857 | 804.598ms | 11579 | 4890 | 894.174 | 904.33 | 0.182723 | 0.439573 | 2.11262 | 0.205631 | 0.000173009 | 1.03495e-05 | 8.30076e-07 | 1(Win) | true |
| simdjson (ondemand) | 11094.8 | 0.0526308 | 811.681ms | 11579 | 320 | 87.8081 | 995.297 | 0.139915 | 0.482569 | 2.43665 | 0.22869 | 0.000172726 | 1.16051e-05 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5337.68 | 0.0463911 | 795.275ms | 4630 | 2560 | 377.021 | 827.234 | 0.0468648 | 1.01 | 5.09482 | 0.800864 | 0.000648539 | 1.99109e-05 | 2.69978e-06 | 1(Win) | true |
| simdjson (ondemand) | 4154.07 | 0.11978 | 816.861ms | 4630 | 320 | 518.723 | 1062.94 | 0.00411578 | 1.28644 | 5.58553 | 0.820086 | 0.000647948 | 1.2824e-05 | 1.34989e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5449.95 | 0.0811759 | 788.92ms | 4630 | 4890 | 2115.15 | 810.193 | 0.184549 | 0.988915 | 5.06134 | 0.792873 | 0.000650642 | 1.77115e-05 | 2.34092e-06 | 1(Win) | true |
| simdjson (ondemand) | 4291.87 | 0.129656 | 813.087ms | 4630 | 1280 | 2277.54 | 1028.81 | 0.324864 | 1.24573 | 5.55054 | 0.812311 | 0.000648792 | 1.26552e-05 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10009.4 | 0.100962 | 823.883ms | 11579 | 1280 | 1588.01 | 1103.22 | 0.0853305 | 0.533049 | 2.7372 | 0.344158 | 0.000259562 | 7.42184e-06 | 6.07242e-07 | 1(Win) | true |
| simdjson (ondemand) | 7916.87 | 0.0827041 | 851.084ms | 11579 | 160 | 212.917 | 1394.82 | 0.157032 | 0.669204 | 3.03869 | 0.362812 | 0.00025963 | 1.07954e-06 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10138 | 0.0916172 | 821.698ms | 11579 | 160 | 159.336 | 1089.23 | 0.00745883 | 0.526267 | 2.72381 | 0.340962 | 0.00025909 | 8.09655e-06 | 1.07954e-06 | 1(Win) | true |
| simdjson (ondemand) | 8096.72 | 0.117149 | 849.748ms | 11579 | 640 | 1633.72 | 1363.84 | 0.0971725 | 0.654524 | 3.0247 | 0.359703 | 0.000259225 | 5.93747e-06 | 1.07954e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1179.98 | 0.0306873 | 1131.26ms | 5092 | 4890 | 7799.22 | 4115.4 | 0.0590199 | 4.40419 | 17.7056 | 3.35324 | 0.00293945 | 8.06831e-05 | 2.96789e-05 | 1(Win) | true |
| simdjson (ondemand) | 1162.97 | 0.0265878 | 1139.21ms | 5092 | 4890 | 6027.18 | 4175.61 | 0.00698492 | 4.46981 | 17.9038 | 3.08896 | 0.00279021 | 5.84742e-05 | 1.93174e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1366.68 | 0.0519665 | 1122.24ms | 5092 | 1280 | 4364.18 | 3553.22 | 0.0654566 | 3.81537 | 15.9089 | 2.92189 | 0.00232641 | 2.85374e-05 | 2.14798e-06 | 1(Win) | true |
| simdjson (ondemand) | 1293.79 | 0.0727546 | 1140.98ms | 5092 | 640 | 4772.57 | 3753.41 | 0.0159829 | 4.02407 | 16.3078 | 2.70066 | 0.00326738 | 3.95842e-05 | 3.37539e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2160.69 | 0.173115 | 1160.87ms | 9739 | 320 | 17720.1 | 4298.55 | 0.331856 | 2.40246 | 9.70099 | 1.74533 | 0.00194996 | 1.15515e-05 | 1.2835e-06 | 1(Win) | true |
| simdjson (ondemand) | 2132.71 | 0.0504366 | 1165.74ms | 9739 | 2560 | 12350.8 | 4354.94 | 0.0389402 | 2.41437 | 9.82878 | 1.6086 | 0.0015635 | 1.66053e-05 | 4.49225e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2424.56 | 0.0687261 | 1152.03ms | 9739 | 1280 | 8871.91 | 3830.73 | 0.0407516 | 2.14483 | 8.94545 | 1.55397 | 0.0013281 | 1.58031e-05 | 3.36919e-06 | 1(Win) | true |
| simdjson (ondemand) | 2352.79 | 0.0968484 | 1157.06ms | 9739 | 80 | 1169.33 | 3947.59 | 0.00855026 | 2.21302 | 9.18434 | 1.44334 | 0.00155945 | 2.3103e-05 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 673.235 | 0.0295061 | 1445.85ms | 5092 | 4890 | 22150.1 | 7213.1 | 0.18553 | 7.64238 | 31.9878 | 6.55596 | 0.00746984 | 5.34942e-05 | 1.32531e-05 | 1(Win) | true |
| simdjson (ondemand) | 455.537 | 0.0202525 | 1791.5ms | 5092 | 4890 | 22792.7 | 10660.2 | 0.107612 | 11.34 | 53.7581 | 10.9344 | 0.0165508 | 7.22895e-05 | 1.97993e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 732.423 | 0.0511501 | 1438.55ms | 5092 | 4890 | 56241.1 | 6630.19 | 0.0346185 | 7.06231 | 30.1486 | 6.11614 | 0.00787783 | 8.52213e-05 | 3.34138e-05 | 1(Win) | true |
| simdjson (ondemand) | 475.729 | 0.041801 | 1780.56ms | 5092 | 1280 | 23304.6 | 10207.7 | 0.000397981 | 10.8629 | 52.1363 | 10.5393 | 0.0166255 | 4.38801e-05 | 8.89876e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1224.94 | 0.0338715 | 1485.01ms | 9739 | 2560 | 16885.2 | 7582.25 | 0.0554956 | 4.23161 | 17.5024 | 3.52083 | 0.00389033 | 8.94439e-05 | 4.94147e-05 | 1(Win) | true |
| simdjson (ondemand) | 852.547 | 0.036246 | 1811.8ms | 9739 | 1280 | 19958.2 | 10894.2 | 0.0730421 | 6.06031 | 28.6795 | 5.72656 | 0.00899428 | 3.36116e-05 | 9.22515e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.24 | 0.0231553 | 1482.01ms | 9739 | 4890 | 13054.7 | 7056.32 | 0.0697598 | 3.93428 | 16.5523 | 3.29237 | 0.00412624 | 2.77173e-05 | 5.77443e-06 | 1(Win) | true |
| simdjson (ondemand) | 888.743 | 0.0769932 | 1805.89ms | 9739 | 320 | 20717.2 | 10450.5 | 0.0275628 | 5.81511 | 27.8316 | 5.522 | 0.00934035 | 3.27292e-05 | 5.77575e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5045.45 | 0.0480053 | 808.596ms | 5092 | 4890 | 1043.91 | 962.472 | 0.073771 | 1.06121 | 4.72467 | 0.676552 | 0.00127543 | 1.46989e-05 | 1.48595e-06 | 1(Win) | true |
| simdjson (ondemand) | 4440.9 | 0.0669017 | 824.568ms | 5092 | 2560 | 1370.09 | 1093.5 | 0.0605845 | 1.20084 | 5.40083 | 0.66359 | 0.00141314 | 1.19673e-05 | 1.07399e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5249.94 | 0.0602941 | 804.49ms | 5092 | 2560 | 796.265 | 924.984 | 0.237178 | 1.02179 | 4.60978 | 0.652003 | 0.00118031 | 1.11235e-05 | 7.67135e-08 | 1(Win) | true |
| simdjson (ondemand) | 4612.85 | 0.0430798 | 818.99ms | 5092 | 4890 | 1005.76 | 1052.74 | 0.0314259 | 1.15694 | 5.28555 | 0.638453 | 0.00147422 | 1.22892e-05 | 8.83538e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7716.1 | 0.0545446 | 832.606ms | 9739 | 4890 | 2107.88 | 1203.7 | 0.0928485 | 0.6883 | 3.08286 | 0.373139 | 0.000665488 | 1.14019e-05 | 9.86903e-07 | 1(Win) | true |
| simdjson (ondemand) | 6977.17 | 0.0257416 | 848.072ms | 9739 | 1280 | 150.298 | 1331.17 | 0.0497928 | 0.760423 | 3.47633 | 0.374987 | 0.000665334 | 7.13947e-06 | 8.02187e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7837.02 | 0.200674 | 830.678ms | 9739 | 2560 | 14479.3 | 1185.12 | 0.279031 | 0.677165 | 3.0228 | 0.360304 | 0.000669385 | 1.55223e-05 | 2.36645e-06 | 1(Win) | true |
| simdjson (ondemand) | 7168.99 | 0.0846549 | 844.168ms | 9739 | 4890 | 5882.02 | 1295.56 | 0.060444 | 0.738891 | 3.41606 | 0.361844 | 0.000665803 | 1.15279e-05 | 1.0709e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3202.77 | 0.0721709 | 867.536ms | 5092 | 4890 | 5855.44 | 1516.22 | 0.119288 | 1.6481 | 7.76984 | 1.38374 | 0.00253993 | 1.41768e-05 | 6.42573e-07 | 1(Win) | true |
| simdjson (ondemand) | 3170.21 | 0.0964351 | 869.692ms | 5092 | 160 | 349.133 | 1531.79 | 0.156516 | 1.67336 | 8.32698 | 1.3097 | 0.00224249 | 4.90966e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3168.03 | 0.0522628 | 867.378ms | 5092 | 2560 | 1642.95 | 1532.85 | 0.0474985 | 1.66602 | 7.65436 | 1.3586 | 0.00337931 | 1.28111e-05 | 3.83567e-07 | 1(Win) | true |
| simdjson (ondemand) | 3143.25 | 0.0366994 | 868.526ms | 5092 | 4890 | 1571.97 | 1544.93 | 0.20681 | 1.67944 | 8.2117 | 1.28456 | 0.00317247 | 1.58635e-05 | 6.42573e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5342.98 | 0.07934 | 890.547ms | 9739 | 320 | 608.69 | 1738.33 | 0.121736 | 0.993139 | 5.00554 | 0.712496 | 0.000996316 | 5.77575e-06 | 1.60437e-06 | 1(Win) | true |
| Jsonifier (generic) | 5219.68 | 0.0523794 | 894.318ms | 9739 | 4890 | 4247.87 | 1779.39 | 0.0502253 | 1.0096 | 4.68703 | 0.749153 | 0.00146003 | 1.11709e-05 | 4.0736e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5353.65 | 0.110858 | 889.062ms | 9739 | 1280 | 4734.45 | 1734.86 | 0.062499 | 0.982482 | 4.62666 | 0.73601 | 0.00125639 | 1.62042e-05 | 2.08569e-06 | 1(Win) | true |
| simdjson (ondemand) | 5261.12 | 0.0991631 | 892.888ms | 9739 | 640 | 1961.34 | 1765.37 | 0.194654 | 1.00071 | 4.94527 | 0.699353 | 0.00128863 | 9.62624e-06 | 0 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1501.1 | 0.132418 | 1027.17ms | 4857 | 320 | 5342.75 | 3085.74 | 0.0836821 | 3.48164 | 14.1666 | 2.73296 | 0.000938079 | 8.62158e-05 | 3.41003e-05 | 1(Win) | true |
| simdjson (ondemand) | 1421.33 | 0.0557244 | 1045.24ms | 4857 | 1280 | 4221.32 | 3258.92 | 0.0668152 | 3.6679 | 14.2837 | 2.54293 | 0.00135581 | 2.7988e-05 | 2.57361e-06 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1945.54 | 0.0494959 | 979.814ms | 4857 | 4890 | 6790.49 | 2380.82 | 0.0365399 | 2.68949 | 11.2771 | 2.09656 | 0.00223791 | 3.75988e-05 | 3.49463e-06 | 1(Win) | true |
| simdjson (ondemand) | 1733.3 | 0.0630416 | 1003.33ms | 4857 | 1280 | 3632.89 | 2672.35 | 0.0961571 | 3.01546 | 12.0496 | 2.063 | 0.00151376 | 2.7988e-05 | 1.76935e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1950.22 | 0.0416805 | 1048.51ms | 6701 | 4890 | 9121.9 | 3276.84 | 0.129202 | 2.67119 | 10.7172 | 1.99224 | 0.00107859 | 3.68348e-05 | 1.01014e-05 | 1(Win) | true |
| simdjson (ondemand) | 1922.17 | 0.0346821 | 1050.62ms | 6701 | 4890 | 6501.55 | 3324.67 | 0.0297723 | 2.70974 | 10.7763 | 1.85942 | 0.000362123 | 3.39051e-05 | 9.97928e-06 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2508.89 | 0.0369742 | 996.743ms | 6701 | 4890 | 4337.32 | 2547.17 | 0.0523183 | 2.08424 | 8.61767 | 1.53097 | 0.0019809 | 3.02735e-05 | 2.28883e-06 | 1(Win) | true |
| simdjson (ondemand) | 2335.64 | 0.0276039 | 1010.3ms | 6701 | 4890 | 2789.44 | 2736.11 | 0.00678294 | 2.23737 | 9.15699 | 1.51157 | 0.000549105 | 3.25013e-05 | 1.40381e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.702 | 0.0916815 | 1396.82ms | 4857 | 4890 | 187559 | 6755.12 | 0.0611869 | 7.54487 | 31.0601 | 6.21824 | 0.00827562 | 5.93666e-05 | 1.46522e-05 | 1(Win) | true |
| simdjson (ondemand) | 238.881 | 0.0444681 | 2664.59ms | 4857 | 320 | 23791.4 | 19390.4 | 0.0135878 | 21.5976 | 107.356 | 22.5893 | 0.0483767 | 9.39366e-05 | 3.79607e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 773.953 | 0.0874567 | 1343.84ms | 4857 | 640 | 17533.7 | 5984.85 | 0.0408489 | 6.69148 | 28.1513 | 5.57608 | 0.00748662 | 4.56815e-05 | 6.75571e-06 | 1(Win) | true |
| simdjson (ondemand) | 246.382 | 0.019525 | 2624.57ms | 4857 | 2560 | 34493.9 | 18800.1 | 0.0672699 | 20.9253 | 105.085 | 22.097 | 0.0482539 | 4.71291e-05 | 8.92719e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.414 | 0.0294032 | 1453.65ms | 6701 | 2560 | 11740.8 | 7283.41 | 0.012809 | 5.89954 | 23.5756 | 4.76183 | 0.00620377 | 4.37202e-05 | 1.51563e-05 | 1(Win) | true |
| simdjson (ondemand) | 327.507 | 0.041338 | 2676.09ms | 6701 | 640 | 41640.4 | 19512.8 | 0.00755859 | 15.7456 | 77.9858 | 16.3314 | 0.0339798 | 4.61685e-05 | 1.77212e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 985.995 | 0.0242112 | 1395.46ms | 6701 | 4890 | 12041.2 | 6481.34 | 0.0542066 | 5.24431 | 21.4672 | 4.29637 | 0.00561168 | 2.64283e-05 | 4.4861e-06 | 1(Win) | true |
| simdjson (ondemand) | 336.725 | 0.0628305 | 2641.04ms | 6701 | 160 | 22750.4 | 18978.6 | 0.0163644 | 15.3249 | 76.3395 | 15.9746 | 0.0355329 | 4.19713e-05 | 8.39427e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4085.02 | 0.0356751 | 827.16ms | 4857 | 1280 | 209.454 | 1133.9 | 0.162246 | 1.30388 | 5.5176 | 0.850731 | 0.000208301 | 2.39667e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 3721.57 | 0.0626394 | 839.522ms | 4857 | 4890 | 2972.27 | 1244.64 | 0.171046 | 1.42639 | 5.97694 | 0.835084 | 0.000265676 | 2.58097e-05 | 3.78936e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4677.71 | 0.0765507 | 819.442ms | 4857 | 2560 | 1470.99 | 990.228 | 0.0557483 | 1.14468 | 4.96026 | 0.725345 | 0.000432205 | 2.98377e-05 | 5.95146e-06 | 1(Win) | true |
| simdjson (ondemand) | 4109.66 | 0.0443468 | 830.114ms | 4857 | 2560 | 639.574 | 1127.1 | 0.236669 | 1.2975 | 5.43072 | 0.71258 | 0.00120429 | 1.50395e-05 | 2.2519e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4911.85 | 0.0667919 | 843.862ms | 6701 | 2560 | 1933.2 | 1301.05 | 0.02802 | 1.07908 | 4.49291 | 0.641099 | 0.000158092 | 1.61473e-05 | 1.69051e-06 | 1(Win) | true |
| simdjson (ondemand) | 4742.6 | 0.0884449 | 849.632ms | 6701 | 1280 | 1818.03 | 1347.48 | 0.039499 | 1.11644 | 4.75571 | 0.623042 | 0.000154478 | 1.78378e-05 | 1.98198e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5586.94 | 0.0338761 | 833.937ms | 6701 | 4890 | 734.22 | 1143.84 | 0.242756 | 0.953703 | 4.08894 | 0.550216 | 0.000317903 | 1.62964e-05 | 1.52588e-06 | 1(Win) | true |
| simdjson (ondemand) | 5216.26 | 0.0288565 | 842.142ms | 6701 | 1280 | 159.977 | 1225.13 | 0.128276 | 1.02026 | 4.3598 | 0.534249 | 0.000858431 | 1.52729e-05 | 3.49761e-07 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2953.97 | 0.0393077 | 872.497ms | 4857 | 4890 | 1857.76 | 1568.06 | 0.0302589 | 1.78614 | 7.50525 | 1.32592 | 0.000450428 | 2.40414e-05 | 9.68391e-07 | 1(Win) | true |
| simdjson (ondemand) | 2267.11 | 0.0873521 | 917.739ms | 4857 | 160 | 509.632 | 2043.12 | 0.0238548 | 2.31539 | 10.2364 | 1.70558 | 0.00195723 | 1.54416e-05 | 0 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3264.93 | 0.0407603 | 863.647ms | 4857 | 4890 | 1635.21 | 1418.71 | 0.164409 | 1.62126 | 6.94668 | 1.19971 | 0.00105193 | 2.98096e-05 | 2.31572e-06 | 1(Win) | true |
| simdjson (ondemand) | 2411.77 | 0.0440764 | 911.48ms | 4857 | 2560 | 1834.49 | 1920.58 | 0.12885 | 2.17989 | 9.69055 | 1.58308 | 0.00265821 | 1.69697e-05 | 3.45828e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3722.43 | 0.0556067 | 889.069ms | 6701 | 1280 | 1166.51 | 1716.77 | 0.0075092 | 1.41505 | 5.97269 | 1.00522 | 0.000385903 | 1.74881e-05 | 8.1611e-07 | 1(Win) | true |
| simdjson (ondemand) | 3022.59 | 0.0221343 | 925.943ms | 6701 | 1280 | 280.327 | 2114.27 | 0.178534 | 1.7361 | 7.77018 | 1.23802 | 0.00126229 | 1.73715e-05 | 6.52888e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4068.53 | 0.043045 | 879.282ms | 6701 | 2560 | 1170.28 | 1570.73 | 0.120841 | 1.29798 | 5.5726 | 0.913147 | 0.000815643 | 1.79544e-05 | 1.8071e-06 | 1(Win) | true |
| simdjson (ondemand) | 3157.98 | 0.0389836 | 921.296ms | 6701 | 2560 | 1593.18 | 2023.62 | 0.0603441 | 1.66299 | 7.37457 | 1.14923 | 0.00223462 | 1.06094e-05 | 7.57816e-07 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1298.89 | 0.0594632 | 841.723ms | 1691 | 1280 | 697.674 | 1241.57 | 0.0495458 | 4.09135 | 14.5843 | 2.81017 | 0.000714721 | 6.42187e-05 | 8.31609e-06 | 1(Win) | true |
| simdjson (ondemand) | 1232.95 | 0.052411 | 848.331ms | 1691 | 2560 | 1203.04 | 1307.97 | 0.0221647 | 4.30128 | 15.0414 | 2.82436 | 0.00170295 | 5.38236e-05 | 3.46504e-06 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1471.12 | 0.038483 | 835.283ms | 1691 | 4890 | 870.245 | 1096.22 | 0.0318523 | 3.63125 | 13.1821 | 2.46008 | 0.00101415 | 7.81232e-05 | 7.61883e-06 | 1(Win) | true |
| simdjson (ondemand) | 1413.32 | 0.073206 | 839ms | 1691 | 160 | 111.64 | 1141.04 | 0.00273865 | 3.7732 | 13.6334 | 2.47428 | 0.000595062 | 0.000110881 | 0 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.13 | 0.0589734 | 850.5ms | 2158 | 640 | 380.464 | 1307.4 | 0.0735537 | 3.37295 | 11.9212 | 2.27016 | 0.000464116 | 6.29924e-05 | 1.95494e-05 | 1(Win) | true |
| simdjson (ondemand) | 1558.4 | 0.0569378 | 855.098ms | 2158 | 4890 | 2764.76 | 1320.61 | 0.30948 | 3.41347 | 11.9805 | 2.20158 | 0.00048007 | 0.000134279 | 7.17357e-05 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1790.57 | 0.130148 | 839.667ms | 2158 | 2560 | 5728.41 | 1149.37 | 0.0235807 | 2.96999 | 10.8832 | 2.01483 | 0.000470452 | 7.92835e-05 | 1.14038e-05 | 1(Win) | true |
| simdjson (ondemand) | 1750.56 | 0.0544992 | 842.069ms | 2158 | 2560 | 1050.92 | 1175.64 | 0.286124 | 3.04253 | 10.9444 | 1.94903 | 0.000776182 | 5.7562e-05 | 6.51645e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 908.174 | 0.0527933 | 895.665ms | 1691 | 2560 | 2249.82 | 1775.72 | 0.0461088 | 5.79555 | 20.67 | 4.0893 | 0.00210212 | 5.65956e-05 | 3.00303e-06 | 1(Win) | true |
| simdjson (ondemand) | 742.747 | 0.0452013 | 934.057ms | 1691 | 2560 | 2465.74 | 2171.21 | 0.014089 | 7.05573 | 27.5801 | 5.38676 | 0.00120514 | 6.09846e-05 | 7.85408e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 999.406 | 0.0500785 | 886.532ms | 1691 | 320 | 208.957 | 1613.62 | 0.0334926 | 5.28414 | 19.3631 | 3.75931 | 0.00207717 | 8.50089e-05 | 3.69604e-06 | 1(Win) | true |
| simdjson (ondemand) | 803.763 | 0.0775094 | 926.028ms | 1691 | 1280 | 3095.63 | 2006.39 | 0.0106679 | 6.53016 | 26.2673 | 5.05677 | 0.00144238 | 4.15804e-05 | 1.38601e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1077.75 | 0.0584483 | 911.757ms | 2158 | 320 | 398.618 | 1909.55 | 0.00212751 | 4.88063 | 17.1835 | 3.46154 | 0.00182316 | 8.10936e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 926.107 | 0.0341917 | 941.246ms | 2158 | 4890 | 2823.13 | 2222.24 | 0.0760224 | 5.65997 | 21.9078 | 4.24004 | 0.00184902 | 5.31622e-05 | 5.87532e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1183.65 | 0.0605204 | 901.95ms | 2158 | 320 | 354.331 | 1738.71 | 0.141108 | 4.4539 | 16.012 | 3.16914 | 0.00187819 | 5.64759e-05 | 4.3443e-06 | 1(Win) | true |
| simdjson (ondemand) | 1008.92 | 0.0408552 | 928.919ms | 2158 | 4890 | 3396.23 | 2039.84 | 0.151591 | 5.21629 | 20.7317 | 3.94764 | 0.00177141 | 0.000113242 | 4.72868e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4572.3 | 0.0467624 | 747.538ms | 1691 | 2560 | 69.6391 | 352.703 | 0.0940058 | 1.24943 | 4.70136 | 0.709639 | 0.000591597 | 3.67294e-05 | 1.61702e-06 | 1(Win) | true |
| simdjson (ondemand) | 4054.46 | 0.214375 | 746.785ms | 1691 | 80 | 58.1646 | 397.75 | 0.0628141 | 1.3954 | 5.11413 | 0.719101 | 0.000657895 | 2.95683e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5024.02 | 0.19286 | 742.035ms | 1691 | 320 | 122.636 | 320.991 | 0.413984 | 1.16003 | 4.3702 | 0.635127 | 0.000591366 | 2.95683e-05 | 7.39208e-06 | 1(Win) | true |
| simdjson (ondemand) | 4417.42 | 0.16965 | 746.026ms | 1691 | 160 | 61.3726 | 365.069 | 0.158963 | 1.29073 | 4.79243 | 0.644589 | 0.000694855 | 5.54406e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5192.54 | 0.117356 | 750.084ms | 2158 | 640 | 138.464 | 396.344 | 0.0740601 | 1.08984 | 4.08434 | 0.569045 | 0.000466288 | 2.67899e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4923.49 | 0.0592116 | 749.738ms | 2158 | 4890 | 299.557 | 418.002 | 0.0166633 | 1.15777 | 4.27572 | 0.574606 | 0.000533043 | 2.00898e-05 | 1.0424e-05 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5628.03 | 0.226144 | 747.42ms | 2158 | 160 | 109.416 | 365.675 | 0.136547 | 1.01262 | 3.82484 | 0.510658 | 0.000463392 | 1.15848e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5280.57 | 0.040122 | 749.623ms | 2158 | 2560 | 62.5959 | 389.736 | 0.0650903 | 1.07336 | 4.02363 | 0.516219 | 0.000478416 | 1.73772e-05 | 1.99114e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.84 | 0.105692 | 762.075ms | 1691 | 4890 | 1436.42 | 512.797 | 0.133614 | 1.76781 | 6.87877 | 1.21348 | 0.000600557 | 5.91366e-05 | 1.62051e-05 | 1(Win) | true |
| simdjson (ondemand) | 2617.21 | 0.0365881 | 771.397ms | 1691 | 2560 | 130.115 | 616.176 | 0.0841178 | 2.09802 | 8.47901 | 1.44767 | 0.00072604 | 3.92704e-05 | 3.69604e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3314.62 | 0.0431638 | 760.229ms | 1691 | 2560 | 112.901 | 486.53 | 0.00746734 | 1.67887 | 6.5476 | 1.13897 | 0.000766235 | 2.44863e-05 | 2.31002e-07 | 1(Win) | true |
| simdjson (ondemand) | 2799.71 | 0.0547785 | 768.767ms | 1691 | 4890 | 486.844 | 576.01 | 0.0362741 | 1.96407 | 8.1573 | 1.37315 | 0.000610836 | 2.69682e-05 | 6.89322e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3776.37 | 0.198963 | 766.688ms | 2158 | 160 | 188.113 | 544.975 | 0.0527269 | 1.46552 | 5.80816 | 0.979611 | 0.000535797 | 5.7924e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3237.02 | 0.0743791 | 774.251ms | 2158 | 320 | 71.5588 | 635.778 | 0.025074 | 1.68919 | 6.91149 | 1.14551 | 0.00048801 | 2.31696e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.31 | 0.0809983 | 764.08ms | 2158 | 1280 | 230.257 | 523.63 | 0.14972 | 1.40658 | 5.54866 | 0.921223 | 0.000905425 | 2.42557e-05 | 3.62025e-07 | 1(Win) | true |
| simdjson (ondemand) | 3420.57 | 0.0857026 | 773.444ms | 2158 | 320 | 85.0832 | 601.663 | 0.0301339 | 1.60338 | 6.65941 | 1.08712 | 0.000519868 | 1.59291e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1362.35 | 0.0407395 | 1028.17ms | 4390 | 2560 | 4012.54 | 3073.08 | 0.0227709 | 3.82826 | 17.6116 | 3.28907 | 0.00117063 | 3.56812e-05 | 3.2033e-06 | 1(Win) | true |
| simdjson (ondemand) | 1055.21 | 0.0358799 | 1112.48ms | 4390 | 2560 | 5187.91 | 3967.57 | 0.0423175 | 4.92792 | 19.5522 | 3.61526 | 0.00292924 | 3.70159e-05 | 8.18622e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1527.21 | 0.0525157 | 1016.48ms | 4390 | 2560 | 5305.78 | 2741.36 | 0.0128403 | 3.42154 | 16.2075 | 2.97062 | 0.00139308 | 0.000120035 | 4.29776e-05 | 1(Win) | true |
| simdjson (ondemand) | 1184.94 | 0.0818291 | 1091.03ms | 4390 | 80 | 668.711 | 3533.19 | 0.00176897 | 4.39801 | 18.123 | 3.29499 | 0.00245159 | 7.97267e-05 | 2.84738e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2605.78 | 0.0349357 | 1062.08ms | 9378 | 4890 | 7030.62 | 3432.2 | 0.0457956 | 1.99897 | 9.11164 | 1.5964 | 0.00104404 | 2.79556e-05 | 6.52007e-06 | 1(Win) | true |
| simdjson (ondemand) | 2144.17 | 0.0448758 | 1134.04ms | 9378 | 640 | 2242.36 | 4171.1 | 0.0869081 | 2.42541 | 9.84304 | 1.71892 | 0.00110581 | 3.03236e-05 | 9.33035e-06 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2864.06 | 0.0308489 | 1054.07ms | 9378 | 4890 | 4537.81 | 3122.69 | 0.00924031 | 1.82049 | 8.45468 | 1.44732 | 0.000970007 | 2.28748e-05 | 1.11212e-06 | 1(Win) | true |
| simdjson (ondemand) | 2391.92 | 0.0481395 | 1113.7ms | 9378 | 1280 | 4147.05 | 3739.07 | 0.0775569 | 2.17578 | 9.17402 | 1.56899 | 0.00116171 | 1.56617e-05 | 5.83147e-07 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 752.63 | 0.0318388 | 1274.22ms | 4390 | 2560 | 8030.09 | 5562.67 | 0.0101482 | 6.88794 | 29.4153 | 5.96606 | 0.0120032 | 4.01303e-05 | 5.5168e-06 | 1(Win) | true |
| simdjson (ondemand) | 713.664 | 0.0273803 | 1304.27ms | 4390 | 4890 | 12616.1 | 5866.39 | 0.269436 | 7.26113 | 31.6255 | 6.16287 | 0.00624481 | 3.86172e-05 | 5.68312e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 801.965 | 0.0670098 | 1261.16ms | 4390 | 1280 | 15664.1 | 5220.46 | 0.0123148 | 6.46921 | 28.0114 | 5.64761 | 0.0116431 | 4.1287e-05 | 5.5168e-06 | 1(Win) | true |
| simdjson (ondemand) | 749.914 | 0.061049 | 1298.11ms | 4390 | 640 | 7434.36 | 5582.81 | 0.00559722 | 6.91611 | 30.1961 | 5.8426 | 0.00665433 | 2.95416e-05 | 4.27107e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1558.31 | 0.0352471 | 1295.1ms | 9378 | 2560 | 10476 | 5739.25 | 0.092139 | 3.32616 | 14.6386 | 2.87791 | 0.00569955 | 2.77828e-05 | 4.66517e-06 | 1(Win) | true |
| simdjson (ondemand) | 1483.18 | 0.121073 | 1319.75ms | 9378 | 320 | 17055.8 | 6029.98 | 0.00995127 | 3.49278 | 15.3569 | 2.88121 | 0.00282276 | 1.36623e-05 | 3.33227e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1646.9 | 0.052012 | 1288.2ms | 9378 | 640 | 5105.91 | 5430.54 | 0.0282913 | 3.14988 | 13.9818 | 2.72883 | 0.00600624 | 1.56617e-05 | 8.33067e-07 | 1(Win) | true |
| simdjson (ondemand) | 1564.32 | 0.0389155 | 1310.94ms | 9378 | 4890 | 24206 | 5717.21 | 0.011596 | 3.31181 | 14.6878 | 2.73129 | 0.00281137 | 3.6351e-05 | 1.40432e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2234.38 | 0.0905019 | 902.557ms | 4390 | 160 | 460.097 | 1873.73 | 0.0296956 | 2.35333 | 10.6829 | 1.87039 | 0.00174972 | 9.96583e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1908.75 | 0.0513443 | 956.923ms | 4390 | 2560 | 3246.78 | 2193.38 | 0.0211262 | 2.74617 | 11.5507 | 1.92508 | 0.00195339 | 2.18892e-05 | 3.38126e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2304.09 | 0.0423251 | 901.169ms | 4390 | 4890 | 2892.26 | 1817.05 | 0.019842 | 2.28587 | 10.3913 | 1.80091 | 0.00225196 | 3.69868e-05 | 1.3183e-05 | 1(Win) | true |
| simdjson (ondemand) | 1950.45 | 0.04453 | 934.029ms | 4390 | 320 | 292.357 | 2146.49 | 0.0664888 | 2.68991 | 11.2506 | 1.85376 | 0.00256193 | 2.56264e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4048.11 | 0.0412946 | 942.643ms | 9378 | 4890 | 4070.16 | 2209.32 | 0.0356897 | 1.29647 | 5.78482 | 0.924398 | 0.0011542 | 1.96256e-05 | 7.41412e-06 | 1(Win) | true |
| simdjson (ondemand) | 3671.25 | 0.0575475 | 958.608ms | 9378 | 640 | 1257.84 | 2436.1 | 0.0213538 | 1.42526 | 6.10035 | 0.928024 | 0.00113264 | 1.14963e-05 | 3.33227e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4232.61 | 0.0732942 | 948.315ms | 9378 | 1280 | 3070.1 | 2113.01 | 0.0543063 | 1.23853 | 5.64865 | 0.891875 | 0.00104458 | 1.39122e-05 | 2.58251e-06 | 1(Win) | true |
| simdjson (ondemand) | 3763.49 | 0.0582329 | 956.937ms | 9378 | 160 | 306.405 | 2376.4 | 0.0110473 | 1.39135 | 5.95991 | 0.894647 | 0.00141221 | 1.86607e-05 | 6.66453e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1728.44 | 0.0611895 | 958.911ms | 4390 | 640 | 1405.9 | 2422.2 | 0.135475 | 3.02788 | 13.7998 | 2.59066 | 0.00363255 | 2.70501e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1589.64 | 0.043954 | 977.647ms | 4390 | 2560 | 3430.59 | 2633.7 | 0.0950732 | 3.28778 | 14.1419 | 2.45581 | 0.00404844 | 2.80289e-05 | 4.00413e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1766.89 | 0.0777748 | 954.85ms | 4390 | 320 | 1086.78 | 2369.5 | 0.0433712 | 2.96525 | 13.508 | 2.52118 | 0.0032695 | 3.34567e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1657.5 | 0.0201092 | 972.276ms | 4390 | 2560 | 660.471 | 2525.88 | 0.109897 | 3.15547 | 13.7843 | 2.37312 | 0.00442278 | 2.11774e-05 | 3.38126e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3255.03 | 0.0854606 | 997.572ms | 9378 | 640 | 3528.76 | 2747.61 | 0.0729079 | 1.60372 | 7.25432 | 1.27714 | 0.0022851 | 1.11631e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3111.49 | 0.0429643 | 1002.37ms | 9378 | 2560 | 3904.25 | 2874.36 | 0.050621 | 1.67658 | 7.28642 | 1.17115 | 0.00231234 | 1.05799e-05 | 9.16373e-07 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3321.9 | 0.13145 | 1009.27ms | 9378 | 1280 | 16031.7 | 2692.3 | 0.293898 | 1.57078 | 7.11804 | 1.24462 | 0.00230018 | 1.77443e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 3150.51 | 0.23992 | 1044.14ms | 9378 | 640 | 29687.6 | 2838.77 | 0.274971 | 1.65921 | 7.14598 | 1.13777 | 0.00328661 | 1.33291e-05 | 3.33227e-07 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1550.24 | 0.118286 | 1007.08ms | 4669 | 320 | 3693.72 | 2872.27 | 0.0508349 | 3.36619 | 13.7333 | 2.7644 | 0.00163847 | 3.6812e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1495.81 | 0.0383169 | 1018.03ms | 4669 | 4890 | 6361.88 | 2976.79 | 0.0197338 | 3.48603 | 15.2215 | 2.50375 | 0.00106993 | 3.89814e-05 | 1.10812e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1669.95 | 0.0387861 | 988.48ms | 4669 | 1280 | 1369 | 2666.38 | 0.150376 | 3.13054 | 12.9334 | 2.58771 | 0.00185599 | 2.02466e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 1613.76 | 0.057859 | 1000.03ms | 4669 | 1280 | 3262.26 | 2759.2 | 0.16576 | 3.23793 | 14.4448 | 2.32876 | 0.00128457 | 2.44297e-05 | 3.01189e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2428.85 | 0.0401172 | 1032.97ms | 7932 | 4890 | 7633.67 | 3114.45 | 0.0826737 | 2.15574 | 9.52272 | 1.48954 | 0.000638118 | 2.05736e-05 | 6.00709e-06 | 1(Win) | true |
| Jsonifier (generic) | 2368.25 | 0.0702202 | 1061.08ms | 7932 | 1280 | 6439.37 | 3194.14 | 0.0375546 | 2.20301 | 8.73777 | 1.6765 | 0.0011963 | 1.5365e-05 | 2.46234e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2607.7 | 0.0602131 | 1013.35ms | 7932 | 2560 | 7810.4 | 2900.85 | 0.276536 | 2.00327 | 9.06732 | 1.38691 | 0.00063548 | 2.07821e-05 | 4.82618e-06 | 1(Win) | true |
| Jsonifier (generic) | 2525.22 | 0.0500993 | 1020.84ms | 7932 | 4890 | 11013.9 | 2995.6 | 0.0564838 | 2.07268 | 8.27005 | 1.57249 | 0.00141979 | 3.43152e-05 | 1.3329e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 569.825 | 0.0825691 | 1517.11ms | 4669 | 160 | 6660.7 | 7814.16 | 0.112888 | 9.25618 | 39.0722 | 7.81238 | 0.0108093 | 6.02377e-05 | 3.07882e-05 | 1(Win) | true |
| simdjson (ondemand) | 246.828 | 0.0338322 | 2522.22ms | 4669 | 1280 | 47679.5 | 18039.7 | 0.00161105 | 20.8807 | 94.8415 | 19.4065 | 0.0486691 | 4.56803e-05 | 9.20299e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 577.323 | 0.023469 | 1498.49ms | 4669 | 4890 | 16021.7 | 7712.67 | 0.277307 | 8.95956 | 38.2973 | 7.63418 | 0.0105792 | 3.44263e-05 | 5.38732e-06 | 1(Win) | true |
| simdjson (ondemand) | 250.166 | 0.0150789 | 2505.14ms | 4669 | 4890 | 35224.1 | 17799 | 0.211596 | 20.6262 | 94.0542 | 19.227 | 0.0509337 | 4.23539e-05 | 8.05907e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 845.779 | 0.0985697 | 1612.06ms | 7932 | 80 | 6217.68 | 8943.88 | 0.0539767 | 6.11956 | 24.3567 | 4.87595 | 0.00573626 | 2.04866e-05 | 4.72769e-06 | 1(Win) | true |
| simdjson (ondemand) | 424.373 | 0.0431565 | 2509.29ms | 7932 | 1280 | 75748.3 | 17825.2 | 0.0674545 | 12.1445 | 55.6912 | 11.2751 | 0.0294873 | 5.04286e-05 | 1.52665e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 870.263 | 0.021165 | 1594.74ms | 7932 | 4890 | 16550.4 | 8692.25 | 0.0402075 | 5.93239 | 23.9007 | 4.77156 | 0.00637195 | 2.4776e-05 | 3.22269e-06 | 1(Win) | true |
| simdjson (ondemand) | 428.092 | 0.0207309 | 2492.72ms | 7932 | 4890 | 65620.1 | 17670.4 | 0.072652 | 12.0488 | 55.2282 | 11.1699 | 0.030397 | 2.15791e-05 | 2.99066e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4494.04 | 0.0551999 | 811.517ms | 4669 | 1280 | 382.878 | 990.802 | 0.0692614 | 1.20652 | 5.19576 | 0.739559 | 0.00148302 | 3.4804e-05 | 1.22149e-05 | 1(Win) | true |
| simdjson (ondemand) | 4387.32 | 0.0943305 | 814.268ms | 4669 | 1280 | 1173.17 | 1014.9 | 0.0735679 | 1.23108 | 5.56457 | 0.70015 | 0.00120693 | 2.25892e-05 | 5.35447e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4943.67 | 0.0627109 | 801.087ms | 4669 | 320 | 102.09 | 900.688 | 0.144818 | 1.10609 | 4.93639 | 0.682587 | 0.00115656 | 1.87406e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4662.14 | 0.0503002 | 806.556ms | 4669 | 320 | 73.8528 | 955.078 | 0.0147261 | 1.15064 | 5.3052 | 0.641893 | 0.00107089 | 1.80713e-05 | 4.68516e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6445.18 | 0.0471269 | 851.833ms | 7932 | 320 | 97.9003 | 1173.67 | 0.0441793 | 0.829521 | 3.84102 | 0.433056 | 0.000758006 | 1.10313e-05 | 3.93974e-07 | 1(Win) | true |
| Jsonifier (generic) | 6321.52 | 0.126848 | 830.748ms | 7932 | 2560 | 5898.31 | 1196.63 | 0.0659945 | 0.842636 | 3.6852 | 0.463944 | 0.000884865 | 9.94784e-06 | 2.01912e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6910.21 | 0.0929936 | 824.102ms | 7932 | 320 | 331.619 | 1094.69 | 0.0949708 | 0.786528 | 3.53253 | 0.430408 | 0.000678423 | 1.14252e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 6855.05 | 0.0253091 | 824.569ms | 7932 | 1280 | 99.8405 | 1103.5 | 0.023287 | 0.778533 | 3.68835 | 0.398764 | 0.000632623 | 1.23117e-05 | 2.46234e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3167.55 | 0.129077 | 854.712ms | 4669 | 40 | 131.692 | 1405.72 | 0.145029 | 1.67183 | 7.48147 | 1.32255 | 0.00146177 | 1.07089e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2597.07 | 0.0525993 | 883.283ms | 4669 | 4890 | 3976.93 | 1714.51 | 0.469413 | 2.03028 | 9.47719 | 1.55151 | 0.0028399 | 1.78701e-05 | 3.41635e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3364.67 | 0.0520861 | 846.303ms | 4669 | 320 | 152.04 | 1323.37 | 0.0333067 | 1.5769 | 7.22082 | 1.2643 | 0.00138547 | 2.74416e-05 | 2.00792e-06 | 1(Win) | true |
| simdjson (ondemand) | 2616.47 | 0.601817 | 877.792ms | 4669 | 30 | 3146.79 | 1701.8 | 0.0117509 | 2.01903 | 9.21782 | 1.49325 | 0.00262012 | 5.71143e-05 | 2.14179e-05 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4730.28 | 0.137638 | 873.6ms | 7932 | 1280 | 6201.2 | 1599.17 | 0.0276922 | 1.124 | 5.0474 | 0.816944 | 0.000897669 | 1.87138e-05 | 6.59906e-06 | 1(Win) | true |
| simdjson (ondemand) | 3882.44 | 0.0298967 | 907.03ms | 7932 | 2560 | 868.646 | 1948.4 | 0.161229 | 1.35406 | 6.12607 | 0.929778 | 0.0016442 | 1.31981e-05 | 1.77288e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5024.94 | 0.104482 | 867.839ms | 7932 | 80 | 197.914 | 1505.4 | 0.192269 | 1.07144 | 4.89397 | 0.782653 | 0.000855711 | 6.30358e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4048.53 | 0.0400242 | 900.996ms | 7932 | 320 | 178.965 | 1868.47 | 0.0512045 | 1.2999 | 5.9734 | 0.895487 | 0.00156368 | 1.06373e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 546.705 | 0.0897868 | 1528.12ms | 4604 | 320 | 16639.5 | 8031.24 | 0.0831605 | 9.4587 | 38.7164 | 7.48436 | 0.00837519 | 6.58395e-05 | 2.78291e-05 | 1(Win) | true |
| Jsonifier (generic) | 533.116 | 0.143392 | 1547.8ms | 4604 | 320 | 44630.1 | 8235.95 | 0.13743 | 9.69526 | 37.3159 | 7.81277 | 0.0104108 | 6.58395e-05 | 3.05441e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 622.411 | 0.0860602 | 1520.93ms | 4604 | 1280 | 47177.1 | 7054.37 | 0.0715383 | 8.33668 | 34.1236 | 6.42708 | 0.00858374 | 7.00817e-05 | 2.49443e-05 | 1(Win) | true |
| Jsonifier (generic) | 605.725 | 0.0308968 | 1549.91ms | 4604 | 4890 | 24527.6 | 7248.7 | 0.225082 | 8.56053 | 32.6204 | 6.73098 | 0.0123566 | 5.92976e-05 | 1.73673e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2048.9 | 0.193434 | 1612.02ms | 18245 | 30 | 8095.31 | 8492.27 | 0.424461 | 2.57328 | 10.7955 | 1.92754 | 0.00245364 | 6.02905e-05 | 3.47127e-05 | 1(Win) | true |
| Jsonifier (generic) | 1926.76 | 0.0503622 | 1631.11ms | 18245 | 1280 | 26476.1 | 9030.61 | 0.149838 | 2.68419 | 10.4333 | 2.02508 | 0.00266165 | 2.21807e-05 | 1.05765e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2216.14 | 0.179167 | 1616ms | 18245 | 160 | 31661.5 | 7851.41 | 0.078471 | 2.33319 | 9.66994 | 1.66633 | 0.00320841 | 3.1858e-05 | 1.57577e-05 | 1(Win) | true |
| Jsonifier (generic) | 2154.79 | 0.0854072 | 1659.45ms | 18245 | 80 | 3805.02 | 8074.94 | 0.114528 | 2.4031 | 9.26101 | 1.7556 | 0.00258975 | 1.43875e-05 | 2.74048e-06 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 316.327 | 0.0244105 | 2115.17ms | 4604 | 2560 | 29389.6 | 13880.3 | 0.0518341 | 16.3202 | 67.2322 | 14.6577 | 0.0241123 | 7.55966e-05 | 2.1296e-05 | 1(Win) | true |
| simdjson (ondemand) | 240.914 | 0.0871897 | 2545.09ms | 4604 | 160 | 40401.6 | 18225.3 | 0.0115897 | 21.4136 | 105.422 | 22.0865 | 0.023337 | 6.78758e-05 | 2.17202e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 339.468 | 0.0433924 | 2107.55ms | 4604 | 4890 | 154031 | 12934.1 | 0.023605 | 15.2027 | 62.9913 | 13.6979 | 0.022259 | 8.51931e-05 | 2.11872e-05 | 1(Win) | true |
| simdjson (ondemand) | 255.387 | 0.0319417 | 2530.35ms | 4604 | 2560 | 77202.1 | 17192.4 | 0.144257 | 20.197 | 101.151 | 21.1232 | 0.0225011 | 0.000110128 | 4.32708e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1173.81 | 0.0325799 | 2212.29ms | 18245 | 1280 | 29853.7 | 14823.3 | 0.0279517 | 4.39386 | 18.003 | 3.78202 | 0.00594238 | 2.56063e-05 | 1.29316e-05 | 1(Win) | true |
| simdjson (ondemand) | 916.921 | 0.0783089 | 2614ms | 18245 | 80 | 17665.9 | 18976.3 | 0.121813 | 5.62871 | 27.5754 | 5.59885 | 0.00653467 | 7.53631e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.66 | 0.122927 | 2212.7ms | 18245 | 80 | 23625.2 | 13979.6 | 0.0149347 | 4.14793 | 16.9354 | 3.54059 | 0.00559057 | 4.17923e-05 | 1.50726e-05 | 1(Win) | true |
| simdjson (ondemand) | 966.294 | 0.0440555 | 2608.66ms | 18245 | 1280 | 80552.4 | 18006.7 | 0.00934635 | 5.33465 | 26.4975 | 5.35577 | 0.00650555 | 0.000105423 | 6.47866e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4023.88 | 0.0408151 | 823.476ms | 4604 | 4890 | 969.908 | 1091.16 | 0.0192594 | 1.32691 | 6.2513 | 0.926151 | 0.000434671 | 2.3719e-05 | 2.48739e-06 | 1(Win) | true |
| simdjson (ondemand) | 3789.05 | 0.0563511 | 828.937ms | 4604 | 4890 | 2085.09 | 1158.79 | 0.0175101 | 1.40429 | 7.04952 | 0.977411 | 0.000460789 | 2.42521e-05 | 3.95317e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4141.47 | 0.0414748 | 823.091ms | 4604 | 640 | 123.741 | 1060.18 | 0.0291727 | 1.29084 | 6.17202 | 0.907472 | 0.000451374 | 1.66296e-05 | 3.39379e-07 | 1(Win) | true |
| simdjson (ondemand) | 3878.45 | 0.0389856 | 828.571ms | 4604 | 4890 | 952.517 | 1132.08 | 0.0841028 | 1.37429 | 6.96829 | 0.958732 | 0.000436226 | 2.18535e-05 | 4.61944e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9854.19 | 0.158715 | 898.198ms | 18245 | 40 | 314.153 | 1765.72 | 0.0826595 | 0.535625 | 2.46435 | 0.263305 | 0.000109619 | 4.11072e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9809.4 | 0.0603922 | 891.334ms | 18245 | 2560 | 2937.69 | 1773.79 | 0.0341446 | 0.537211 | 2.8028 | 0.284187 | 0.00011844 | 7.36503e-06 | 1.39165e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10337.2 | 0.0372523 | 886.427ms | 18245 | 4890 | 1922.64 | 1683.22 | 0.00181192 | 0.509795 | 2.44434 | 0.258592 | 0.000110179 | 8.07012e-06 | 4.25923e-07 | 1(Win) | true |
| simdjson (ondemand) | 9924.8 | 0.0388894 | 889.288ms | 18245 | 4890 | 2273.08 | 1753.16 | 0.0047063 | 0.530805 | 2.7823 | 0.279474 | 0.000126073 | 9.98677e-06 | 3.32892e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2495.28 | 0.186105 | 893.641ms | 4604 | 1280 | 13726.5 | 1759.61 | 0.516529 | 2.12794 | 9.24066 | 1.66942 | 0.00110621 | 4.24224e-05 | 8.14509e-06 | 1(Win) | true |
| simdjson (ondemand) | 1822.99 | 0.0205547 | 955.642ms | 4604 | 640 | 156.857 | 2408.52 | 0.0582228 | 2.87204 | 13.3677 | 2.37294 | 0.00149802 | 1.32358e-05 | 3.39379e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2551.6 | 0.0450433 | 885.571ms | 4604 | 4890 | 2937.74 | 1720.77 | 0.132805 | 2.06703 | 9.16182 | 1.6503 | 0.00108774 | 2.03877e-05 | 1.33253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1853.02 | 0.0370106 | 953.518ms | 4604 | 4890 | 3760.72 | 2369.49 | 0.108392 | 2.82461 | 13.2867 | 2.35426 | 0.00132183 | 1.97214e-05 | 2.13205e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7924.29 | 0.0969898 | 937.665ms | 18245 | 640 | 2902.68 | 2195.75 | 0.0426778 | 0.661211 | 3.22055 | 0.452179 | 0.00036337 | 5.39531e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5753.14 | 0.0853539 | 1020ms | 18245 | 40 | 266.554 | 3024.4 | 0.0242531 | 0.907936 | 4.39693 | 0.636174 | 0.000360373 | 8.22143e-06 | 4.11072e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7988.2 | 0.113427 | 937.897ms | 18245 | 80 | 488.331 | 2178.19 | 0.00516458 | 0.657339 | 3.20066 | 0.447355 | 0.000329542 | 9.59167e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5818.21 | 0.0305545 | 1017.69ms | 18245 | 160 | 133.592 | 2990.57 | 0.0309401 | 0.897583 | 4.37649 | 0.631461 | 0.000343245 | 9.93423e-06 | 6.85119e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1350.35 | 0.13808 | 1067.13ms | 4926 | 160 | 3692.12 | 3478.95 | 0.0782669 | 3.85995 | 16.5538 | 3.1758 | 0.004088 | 5.32887e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1070.44 | 0.0540582 | 1158.31ms | 4926 | 2560 | 14408.7 | 4388.64 | 0.00842978 | 4.85416 | 18.3965 | 3.42144 | 0.00454064 | 8.88145e-05 | 4.25041e-05 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1654.23 | 0.0682466 | 1043.49ms | 4926 | 2560 | 9616.11 | 2839.87 | 0.121145 | 3.15837 | 13.962 | 2.59968 | 0.00380356 | 7.85849e-05 | 3.4257e-05 | 1(Win) | true |
| simdjson (ondemand) | 1242.95 | 0.0562309 | 1130.85ms | 4926 | 2560 | 11563 | 3779.55 | 0.0418814 | 4.18444 | 15.8973 | 2.86906 | 0.00557612 | 6.13771e-05 | 2.45826e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2052.43 | 0.0375973 | 1099.14ms | 8150 | 4890 | 9912.93 | 3786.95 | 0.19481 | 2.53408 | 10.5702 | 1.93436 | 0.00283187 | 2.05503e-05 | 3.28704e-06 | 1(Win) | true |
| simdjson (ondemand) | 1717.9 | 0.0801671 | 1173.18ms | 8150 | 160 | 2104.91 | 4524.39 | 0.0205786 | 3.02714 | 11.6629 | 2.08994 | 0.00257285 | 3.68098e-05 | 1.38037e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2467.74 | 0.0741754 | 1076.48ms | 8150 | 1280 | 6986.27 | 3149.62 | 0.0528059 | 2.11459 | 9.01092 | 1.58822 | 0.00278834 | 2.55943e-05 | 1.05445e-06 | 1(Win) | true |
| simdjson (ondemand) | 1981.76 | 0.0282563 | 1144.99ms | 8150 | 4890 | 6005.59 | 3922 | 0.0296792 | 2.62465 | 10.159 | 1.75791 | 0.00313345 | 2.10521e-05 | 1.32987e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.887 | 0.0575033 | 1293.97ms | 4926 | 1280 | 14032.1 | 5757.91 | 0.00478938 | 6.3524 | 27.4206 | 5.50386 | 0.00915994 | 4.04423e-05 | 9.67443e-06 | 1(Win) | true |
| simdjson (ondemand) | 502.176 | 0.0295443 | 1655.68ms | 4926 | 2560 | 19555.3 | 9354.88 | 0.127045 | 10.2952 | 45.3632 | 9.09338 | 0.0204678 | 5.2575e-05 | 1.72871e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 919.649 | 0.0543259 | 1268.19ms | 4926 | 1280 | 9857.56 | 5108.26 | 0.0324583 | 5.64269 | 24.8238 | 4.93037 | 0.00962289 | 7.18445e-05 | 1.77629e-05 | 1(Win) | true |
| simdjson (ondemand) | 541.334 | 0.0332363 | 1624.61ms | 4926 | 2560 | 21297.3 | 8678.19 | 0.12095 | 9.55254 | 42.8547 | 8.53776 | 0.0202399 | 3.91735e-05 | 3.88563e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1248.85 | 0.0346122 | 1343.52ms | 8150 | 2560 | 11879.4 | 6223.69 | 0.000207122 | 4.14862 | 17.4442 | 3.4789 | 0.0055995 | 2.48275e-05 | 4.21779e-06 | 1(Win) | true |
| simdjson (ondemand) | 827.836 | 0.0747659 | 1657.7ms | 8150 | 320 | 15768.3 | 9388.88 | 0.0328955 | 6.24489 | 27.7063 | 5.4589 | 0.0113052 | 1.57209e-05 | 2.68405e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1408.19 | 0.0244227 | 1308.08ms | 8150 | 4890 | 8885.62 | 5519.44 | 0.0307268 | 3.68205 | 15.8741 | 3.13239 | 0.00560749 | 3.67596e-05 | 3.53796e-06 | 1(Win) | true |
| simdjson (ondemand) | 902.819 | 0.0309582 | 1620.33ms | 8150 | 2560 | 18184.7 | 8609.08 | 0.0245819 | 5.72838 | 26.2048 | 5.12785 | 0.0105504 | 2.20475e-05 | 3.93021e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2520.74 | 0.0421366 | 903.427ms | 4926 | 4890 | 3015.51 | 1863.66 | 0.0605877 | 2.08478 | 9.33151 | 1.60495 | 0.00136312 | 2.28328e-05 | 2.98902e-06 | 1(Win) | true |
| simdjson (ondemand) | 2085.2 | 0.0694 | 940.8ms | 4926 | 2560 | 6258.23 | 2252.92 | 0.0628224 | 2.51291 | 9.98153 | 1.63865 | 0.00252304 | 4.29006e-05 | 1.98247e-05 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2743.78 | 0.0506854 | 898.398ms | 4926 | 2560 | 1927.96 | 1712.17 | 0.0619802 | 1.92241 | 8.76492 | 1.46691 | 0.00178882 | 3.37812e-05 | 1.16569e-05 | 1(Win) | true |
| simdjson (ondemand) | 2246.45 | 0.0767943 | 935.268ms | 4926 | 80 | 206.321 | 2091.21 | 0.0269055 | 2.33893 | 9.41048 | 1.49959 | 0.00263652 | 2.79131e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3630.7 | 0.0514633 | 930.67ms | 8150 | 2560 | 3107.2 | 2140.76 | 0.00432474 | 1.44738 | 6.26479 | 1.00503 | 0.00136053 | 1.73505e-05 | 4.5533e-06 | 1(Win) | true |
| simdjson (ondemand) | 3264.23 | 0.0472326 | 964.098ms | 8150 | 160 | 202.375 | 2381.09 | 0.163269 | 1.60419 | 6.47571 | 0.991902 | 0.00171472 | 3.06748e-05 | 1.53374e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3926.49 | 0.0856225 | 923.862ms | 8150 | 160 | 459.622 | 1979.49 | 0.0769808 | 1.33845 | 5.92282 | 0.921595 | 0.00155215 | 2.30061e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3509.66 | 0.0895558 | 946.552ms | 8150 | 80 | 314.676 | 2214.59 | 0.0445708 | 1.49454 | 6.13055 | 0.907853 | 0.00169632 | 6.13497e-06 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.71 | 0.035222 | 966.493ms | 4926 | 4890 | 3793.2 | 2500.54 | 0.00255613 | 2.78402 | 12.3382 | 2.2905 | 0.00307018 | 2.76069e-05 | 6.68379e-06 | 1(Win) | true |
| simdjson (ondemand) | 1448.32 | 0.0291399 | 1041.23ms | 4926 | 4890 | 4368.62 | 3243.62 | 0.0138523 | 3.59656 | 13.9832 | 2.49006 | 0.00725291 | 2.43273e-05 | 3.27962e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1972.97 | 0.0344429 | 964.754ms | 4926 | 4890 | 3288.95 | 2381.08 | 0.0808692 | 2.6524 | 11.7343 | 2.14576 | 0.00477538 | 2.29574e-05 | 2.24177e-06 | 1(Win) | true |
| simdjson (ondemand) | 1546.46 | 0.0965621 | 1032.02ms | 4926 | 40 | 344.179 | 3037.78 | 0.0518741 | 3.37645 | 13.378 | 2.3443 | 0.00676512 | 2.03004e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2822.62 | 0.0422585 | 993.707ms | 8150 | 2560 | 3466.4 | 2753.63 | 0.0385294 | 1.85042 | 8.13362 | 1.4362 | 0.00185822 | 1.16469e-05 | 1.38995e-06 | 1(Win) | true |
| simdjson (ondemand) | 2308.93 | 0.0318364 | 1051.24ms | 8150 | 2560 | 2940.23 | 3366.26 | 0.0265896 | 2.25585 | 8.93448 | 1.51472 | 0.00478413 | 1.54812e-05 | 2.58819e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2947.74 | 0.0543557 | 990.017ms | 8150 | 2560 | 5258.57 | 2636.75 | 0.000962942 | 1.7716 | 7.76859 | 1.34871 | 0.00297388 | 1.24617e-05 | 1.91718e-07 | 1(Win) | true |
| simdjson (ondemand) | 2434.18 | 0.0531961 | 1044.8ms | 8150 | 1280 | 3693.02 | 3193.05 | 0.0208994 | 2.14146 | 8.56871 | 1.42663 | 0.00483503 | 1.51457e-05 | 2.20475e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2200.8 | 0.146702 | 840.083ms | 2821 | 640 | 2058.24 | 1222.43 | 0.152978 | 2.41147 | 9.134 | 1.63417 | 0.000362792 | 6.59119e-05 | 1.10776e-05 | 1(Win) | true |
| simdjson (ondemand) | 2074.46 | 0.0436862 | 846.14ms | 2821 | 4890 | 1569.62 | 1296.88 | 0.16328 | 2.5575 | 9.43921 | 1.54272 | 0.000362748 | 4.13202e-05 | 3.04465e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2419.97 | 0.0858162 | 833.302ms | 2821 | 2560 | 2330.06 | 1111.72 | 0.0423574 | 2.20039 | 8.56079 | 1.48671 | 0.000359469 | 6.38349e-05 | 1.26008e-05 | 1(Win) | true |
| simdjson (ondemand) | 2208.06 | 0.0575826 | 843.588ms | 2821 | 4890 | 2407 | 1218.41 | 0.0209088 | 2.40561 | 9.0646 | 1.44631 | 0.000363328 | 4.25526e-05 | 4.3495e-06 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2767.22 | 0.0366473 | 846.549ms | 3770 | 4890 | 1108.64 | 1299.27 | 0.0589814 | 1.91687 | 7.1947 | 1.21989 | 0.000386867 | 3.4716e-05 | 2.33248e-06 | 1(Win) | true |
| simdjson (ondemand) | 2668.47 | 0.0463822 | 851.033ms | 3770 | 4890 | 1909.72 | 1347.35 | 0.0171147 | 1.98524 | 7.41671 | 1.16499 | 0.000307074 | 6.34652e-05 | 1.75207e-05 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3066.83 | 0.241519 | 843.03ms | 3770 | 30 | 240.506 | 1172.33 | 0.0909039 | 1.76809 | 6.81167 | 1.11989 | 0.000831123 | 6.18921e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2878.27 | 0.176423 | 848.05ms | 3770 | 80 | 388.525 | 1249.14 | 0.189489 | 1.88168 | 7.13634 | 1.09284 | 0.000331565 | 2.65252e-05 | 1.32626e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 811.595 | 0.078326 | 1050.77ms | 2821 | 640 | 4314.4 | 3314.85 | 0.0333614 | 6.41744 | 26.3339 | 4.94541 | 0.00178848 | 4.04334e-05 | 8.86211e-06 | 1(Win) | true |
| simdjson (ondemand) | 402.7 | 0.0429079 | 1386.66ms | 2821 | 2560 | 21035.7 | 6680.7 | 0.0208346 | 12.8549 | 58.8798 | 11.8788 | 0.0103202 | 7.18661e-05 | 1.8555e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 834.099 | 0.0598319 | 1050.58ms | 2821 | 1280 | 4767.02 | 3225.42 | 0.0126421 | 6.24761 | 25.8196 | 4.81106 | 0.00204133 | 5.78806e-05 | 6.64658e-06 | 1(Win) | true |
| simdjson (ondemand) | 406.032 | 0.104312 | 1386.01ms | 2821 | 640 | 30572.7 | 6625.87 | 0.023317 | 12.746 | 58.503 | 11.7813 | 0.0103908 | 6.25886e-05 | 1.71703e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 996.342 | 0.0381026 | 1082.39ms | 3770 | 4890 | 9244.52 | 3608.55 | 0.0487642 | 5.22087 | 20.747 | 3.92016 | 0.00150564 | 5.99936e-05 | 1.83344e-05 | 1(Win) | true |
| simdjson (ondemand) | 538.181 | 0.0283786 | 1387.42ms | 3770 | 4890 | 17575.8 | 6680.56 | 0.112387 | 9.62222 | 43.7403 | 8.74854 | 0.00926565 | 4.23101e-05 | 1.17709e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1019.7 | 0.0847301 | 1079.65ms | 3770 | 320 | 2856.04 | 3525.89 | 0.0290791 | 5.107 | 20.3621 | 3.81963 | 0.00172497 | 2.56963e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 543.617 | 0.0324697 | 1384.61ms | 3770 | 2560 | 11805.7 | 6613.76 | 0.0435303 | 9.52518 | 43.4584 | 8.6756 | 0.0101439 | 3.38818e-05 | 7.56383e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5260.22 | 0.0820642 | 763.27ms | 2821 | 640 | 112.742 | 511.445 | 0.0626681 | 1.05509 | 3.9089 | 0.502659 | 0.000708968 | 1.82781e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5209.73 | 0.102633 | 764.239ms | 2821 | 2560 | 719.106 | 516.402 | 0.0973725 | 1.06604 | 4.15349 | 0.45374 | 0.000361685 | 1.05238e-05 | 2.07706e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5393.68 | 0.0890636 | 761.071ms | 2821 | 2560 | 505.215 | 498.79 | 0.0877108 | 1.03283 | 3.83729 | 0.485289 | 0.000709522 | 2.7971e-05 | 8.16975e-06 | 1(Win) | true |
| simdjson (ondemand) | 4793.46 | 0.104484 | 773.456ms | 2821 | 320 | 110.042 | 561.247 | 0.0205972 | 1.15843 | 4.0787 | 0.43637 | 0.00106788 | 1.8832e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6416.38 | 0.0929257 | 768.066ms | 3770 | 2560 | 694.087 | 560.339 | 0.122613 | 0.858259 | 3.3626 | 0.390982 | 0.000266392 | 1.89614e-05 | 8.28912e-07 | 1(Win) | true |
| simdjson (ondemand) | 6383.1 | 0.0307859 | 768.882ms | 3770 | 4890 | 147.039 | 563.261 | 0.045057 | 0.870173 | 3.4687 | 0.354377 | 0.000269266 | 1.93108e-05 | 4.82769e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6596.64 | 0.0810141 | 777.289ms | 3770 | 4890 | 953.382 | 545.028 | 0.181777 | 0.827842 | 3.30902 | 0.377984 | 0.00026536 | 2.43012e-05 | 6.61774e-06 | 1(Win) | true |
| simdjson (ondemand) | 6433.7 | 0.0568139 | 778.501ms | 3770 | 1280 | 129.027 | 558.831 | 0.233758 | 0.850427 | 3.41538 | 0.342175 | 0.000266288 | 1.82361e-05 | 3.31565e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.53 | 0.34536 | 782.85ms | 2821 | 30 | 167.637 | 684.467 | 0.00974089 | 1.38686 | 5.50514 | 0.877348 | 0.000838946 | 1.18161e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3485.81 | 0.0717194 | 790.447ms | 2821 | 2560 | 784.357 | 771.791 | 0.0671576 | 1.55489 | 6.25665 | 0.913861 | 0.000752587 | 1.73088e-05 | 5.1234e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3949.07 | 0.0750024 | 781.232ms | 2821 | 4890 | 1276.67 | 681.254 | 0.370173 | 1.39057 | 5.43353 | 0.859624 | 0.000941884 | 4.3205e-05 | 1.63831e-05 | 1(Win) | true |
| simdjson (ondemand) | 3564.13 | 0.18882 | 788.086ms | 2821 | 640 | 1300.09 | 754.831 | 0.0546181 | 1.52526 | 6.18185 | 0.896491 | 0.000752725 | 1.27393e-05 | 5.53882e-07 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4838.61 | 0.0880202 | 787.62ms | 3770 | 640 | 273.77 | 743.055 | 0.0679668 | 1.12184 | 4.56711 | 0.67878 | 0.000738975 | 2.32095e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4294.91 | 0.0587394 | 800.957ms | 3770 | 4890 | 1182.34 | 837.119 | 0.0976286 | 1.25317 | 5.05252 | 0.700796 | 0.000648484 | 2.10466e-05 | 3.41736e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4960.6 | 0.0603279 | 787.444ms | 3770 | 1280 | 244.715 | 724.781 | 0.0844369 | 1.09478 | 4.51353 | 0.665517 | 0.000807982 | 1.94794e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4419.66 | 0.0656873 | 798.277ms | 3770 | 320 | 91.373 | 813.491 | 0.0318944 | 1.22377 | 4.99655 | 0.687798 | 0.000565318 | 2.15517e-05 | 0 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5866.07 | 0.172886 | 5256.58ms | 277673 | 30 | 182731 | 45142.6 | 0.109625 | 0.878328 | 3.9811 | 0.638841 | 0.00321205 | 3.00113e-06 | 1.80068e-06 | 1(Win) | true |
| simdjson (ondemand) | 4525.26 | 0.0620271 | 6590.4ms | 277673 | 160 | 210796 | 58518.1 | 0.0421487 | 1.13835 | 4.49958 | 0.721679 | 0.0039678 | 2.9261e-06 | 1.75566e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4556.54 | 0.128371 | 6894.15ms | 10548466 | 40 | 3.21295e+08 | 2.20777e+06 | 0.0246384 | 1.11978 | 3.97968 | 0.639409 | 0.0112896 | 0.0175468 | 0.00022034 | 1(Win) | true |
| simdjson (ondemand) | 3832.59 | 0.158232 | 8131.19ms | 10548466 | 40 | 6.89985e+08 | 2.6248e+06 | 0.19611 | 1.326 | 4.49725 | 0.722092 | 0.0101994 | 0.0178436 | 0.000165439 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4006.12 | 0.0587317 | 5749.44ms | 16002592 | 40 | 2.00234e+08 | 3.80949e+06 | 0.1174 | 1.26455 | 7.26695 | 1.14523 | 0.000764386 | 0.0328342 | 0.00172639 | 1(Win) | true |
| simdjson (ondemand) | 3387.45 | 0.0658496 | 6764.2ms | 16002592 | 80 | 7.04094e+08 | 4.50524e+06 | 0.161763 | 1.49677 | 7.97793 | 1.16694 | 0.00105343 | 0.0351108 | 0.00335036 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3208.19 | 0.111876 | 7109.42ms | 16002591 | 30 | 8.49677e+08 | 4.75698e+06 | 0.339643 | 1.57865 | 7.3928 | 1.22025 | 0.000673176 | 0.0360472 | 0.00466162 | 1(Win) | true |
| simdjson (ondemand) | 1862.71 | 0.0634291 | 5770.21ms | 16002591 | 30 | 8.10192e+08 | 8.19303e+06 | 0.190824 | 2.7602 | 12.9551 | 2.70896 | 0.00100719 | 0.0511215 | 0.00447442 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18789 | 0.0394922 | 5232.5ms | 16197086 | 320 | 3.37316e+07 | 822115 | 0.142245 | 0.268547 | 1.40124 | 0.0671858 | 8.13509e-05 | 0.0157189 | 0.00138426 | 1(Win) | true |
| simdjson (ondemand) | 16104.5 | 0.579373 | 6080.64ms | 16197086 | 30 | 9.26435e+08 | 959155 | 0.307742 | 0.315715 | 1.33717 | 0.0735003 | 8.55668e-05 | 0.0157223 | 0.00213657 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18752.7 | 0.0638871 | 5250.32ms | 16197085 | 160 | 4.43091e+07 | 823708 | 0.153256 | 0.269124 | 1.40268 | 0.0683635 | 9.31028e-05 | 0.0157372 | 0.00134383 | 1(Win) | true |
| simdjson (ondemand) | 15351.1 | 0.16763 | 6466.01ms | 16197085 | 320 | 9.10437e+08 | 1.00623e+06 | 0.0293135 | 0.33095 | 1.41968 | 0.0991874 | 9.52451e-05 | 0.0157491 | 0.00163846 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2090.77 | 0.187937 | 7879.81ms | 4212000 | 30 | 3.91118e+08 | 1.92124e+06 | 0.0484818 | 2.43232 | 11.3158 | 2.01958 | 0.0116307 | 0.0664041 | 0.00680157 | 1(Win) | true |
| simdjson (ondemand) | 1534.02 | 0.102067 | 9951.45ms | 4212000 | 30 | 2.14292e+08 | 2.61854e+06 | 0.369623 | 3.30909 | 12.5987 | 2.34147 | 0.0119655 | 0.0659368 | 0.00187844 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1533.32 | 0.0772913 | 10002.4ms | 4212000 | 80 | 3.27993e+08 | 2.61973e+06 | 0.387952 | 3.31118 | 15.1667 | 2.91937 | 0.0123025 | 0.0667675 | 0.00194153 | 1(Win) | true |
| simdjson (ondemand) | 1331.35 | 0.0658056 | 5409.73ms | 4212000 | 30 | 1.1826e+08 | 3.01714e+06 | 0.0859302 | 3.79552 | 15.6703 | 2.91523 | 0.01204 | 0.0661238 | 0.00214938 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1956.18 | 0.138139 | 8244.27ms | 4211999 | 30 | 2.41387e+08 | 2.05343e+06 | 0.0557979 | 2.5981 | 12.1252 | 2.20728 | 0.0122777 | 0.0684452 | 0.000912069 | 1(Win) | true |
| simdjson (ondemand) | 1267.72 | 0.111591 | 5660.55ms | 4211999 | 80 | 1.00019e+09 | 3.16858e+06 | 0.107917 | 4.02203 | 15.072 | 3.10875 | 0.0124804 | 0.0674668 | 0.00366818 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.51 | 0.0950375 | 10033.6ms | 4211999 | 30 | 1.88363e+08 | 2.63659e+06 | 0.0741886 | 3.3233 | 15.256 | 2.94805 | 0.0125202 | 0.0684256 | 0.00111164 | 1(Win) | true |
| simdjson (ondemand) | 1144.99 | 0.115558 | 6206.06ms | 4211999 | 40 | 6.57414e+08 | 3.50823e+06 | 0.370596 | 4.43989 | 18.1438 | 3.68254 | 0.0126366 | 0.0676009 | 0.00222553 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1649.62 | 0.0822842 | 8774.2ms | 4525120 | 80 | 3.70691e+08 | 2.61604e+06 | 0.00897267 | 3.07572 | 15.2833 | 2.75497 | 0.00975861 | 0.0776958 | 0.000753662 | 1(Win) | true |
| simdjson (ondemand) | 1429.41 | 0.0712559 | 10042.6ms | 4525120 | 30 | 1.38839e+08 | 3.01908e+06 | 0.0167993 | 3.53501 | 16.307 | 2.60221 | 0.0123075 | 0.0769295 | 0.00128963 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 829.329 | 0.0608545 | 8142.32ms | 4525120 | 80 | 8.02199e+08 | 5.20359e+06 | 0.0991124 | 6.13616 | 30.6981 | 6.25099 | 0.0150874 | 0.0781591 | 0.00257119 | 1(Win) | true |
| simdjson (ondemand) | 633.045 | 0.0640905 | 10638.3ms | 4525120 | 80 | 1.5271e+09 | 6.81704e+06 | 0.149282 | 8.03196 | 41.2294 | 8.08443 | 0.0231619 | 0.0775056 | 0.00410365 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1461.57 | 0.077396 | 9795.91ms | 4525119 | 80 | 4.17781e+08 | 2.95264e+06 | 0.00437635 | 3.48003 | 17.4961 | 3.30791 | 0.0100277 | 0.0778867 | 0.000650256 | 1(Win) | true |
| simdjson (ondemand) | 1047.81 | 0.117914 | 6473.78ms | 4525119 | 40 | 9.43375e+08 | 4.11859e+06 | 0.229275 | 4.84865 | 21.5187 | 4.14683 | 0.0150335 | 0.0920027 | 0.00188719 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 824.558 | 0.0890456 | 8218.3ms | 4525119 | 80 | 1.73753e+09 | 5.2337e+06 | 0.172214 | 6.20765 | 30.4265 | 6.25072 | 0.0150887 | 0.0782204 | 0.00346139 | 1(Win) | true |
| simdjson (ondemand) | 546.572 | 0.138069 | 5754.89ms | 4525119 | 30 | 3.56516e+09 | 7.89555e+06 | 0.0822293 | 9.32885 | 46.4412 | 9.62908 | 0.0259994 | 0.0927458 | 0.0036497 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1397.78 | 0.108042 | 9511.25ms | 4203059 | 80 | 7.67934e+08 | 2.86765e+06 | 0.0971959 | 3.64936 | 17.3975 | 3.24139 | 0.0136809 | 0.0889705 | 0.00382095 | 1(Win) | true |
| simdjson (ondemand) | 979.252 | 0.0756698 | 6441.84ms | 4203059 | 80 | 7.67497e+08 | 4.09328e+06 | 0.426451 | 5.21674 | 19.1951 | 3.59072 | 0.0305564 | 0.0885134 | 0.00265042 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 818.022 | 0.0455315 | 7690.01ms | 4203059 | 80 | 3.98212e+08 | 4.90005e+06 | 0.098896 | 6.27503 | 27.6627 | 5.60198 | 0.0223246 | 0.088355 | 0.00694301 | 1(Win) | true |
| simdjson (ondemand) | 731.036 | 0.0718283 | 8575.85ms | 4203059 | 80 | 1.2409e+09 | 5.48311e+06 | 0.0653106 | 7.0022 | 27.0165 | 5.18336 | 0.0338016 | 0.0876683 | 0.00281059 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1259.53 | 0.0567274 | 5057.18ms | 4203058 | 80 | 2.60728e+08 | 3.18241e+06 | 0.15039 | 4.06591 | 19.5166 | 3.77216 | 0.0153688 | 0.0882561 | 0.0017534 | 1(Win) | true |
| simdjson (ondemand) | 789.701 | 0.0866105 | 7996.36ms | 4203058 | 30 | 5.79787e+08 | 5.07578e+06 | 0.417442 | 6.50297 | 24.3016 | 5.15429 | 0.0318053 | 0.103704 | 0.00261144 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 762.329 | 0.0709215 | 8234.19ms | 4203058 | 80 | 1.11248e+09 | 5.25803e+06 | 0.418695 | 6.67796 | 29.7818 | 6.13265 | 0.0239213 | 0.0886704 | 0.00372994 | 1(Win) | true |
| simdjson (ondemand) | 610.562 | 0.0853484 | 10192.4ms | 4203058 | 80 | 2.51161e+09 | 6.56502e+06 | 0.123697 | 8.29982 | 32.123 | 6.74674 | 0.0351092 | 0.102961 | 0.0197394 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1717 | 0.104815 | 7566.68ms | 4197496 | 40 | 2.38863e+08 | 2.33141e+06 | 0.00873214 | 2.95402 | 14.6093 | 2.88738 | 0.000503336 | 0.0817154 | 0.000627261 | 1(Win) | true |
| simdjson (ondemand) | 1560.56 | 0.193655 | 8219.58ms | 4197496 | 80 | 1.9741e+09 | 2.56514e+06 | 0.400992 | 3.23227 | 16.5063 | 2.69504 | 0.00343208 | 0.0808823 | 0.000344086 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 887.517 | 0.0709683 | 6948.13ms | 4197496 | 40 | 4.09842e+08 | 4.51038e+06 | 0.200862 | 5.73985 | 27.6973 | 5.68588 | 0.000882228 | 0.0819066 | 0.00238885 | 1(Win) | true |
| simdjson (ondemand) | 854.754 | 0.134261 | 7186.97ms | 4197496 | 80 | 3.16293e+09 | 4.68327e+06 | 0.0495038 | 5.92144 | 30.2757 | 5.38904 | 0.00579674 | 0.081399 | 0.00319579 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1543.55 | 0.129233 | 8363.56ms | 4197495 | 80 | 8.98629e+08 | 2.5934e+06 | 0.150204 | 3.27825 | 16.6021 | 3.38162 | 0.000754852 | 0.0841228 | 0.000430364 | 1(Win) | true |
| simdjson (ondemand) | 1033.49 | 0.0629864 | 5903.7ms | 4197495 | 40 | 2.38081e+08 | 3.87334e+06 | 2.13527 | 4.90299 | 22.1979 | 4.47248 | 0.0115474 | 0.102927 | 0.000895165 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.086 | 0.0862257 | 7006.43ms | 4197495 | 30 | 4.64613e+08 | 4.56403e+06 | 0.0126483 | 5.78477 | 27.6255 | 5.73481 | 0.000845242 | 0.084265 | 0.000247949 | 1(Win) | true |
| simdjson (ondemand) | 684.639 | 0.0641586 | 9031.99ms | 4197495 | 80 | 1.12579e+09 | 5.84694e+06 | 0.479813 | 7.45107 | 35.9674 | 7.16649 | 0.00833553 | 0.103462 | 0.00120874 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1635.24 | 0.209903 | 9723.4ms | 4506447 | 40 | 1.21731e+09 | 2.62817e+06 | 0.100064 | 3.10763 | 15.2691 | 2.85081 | 0.00874005 | 0.0809546 | 0.000978631 | 1(Win) | true |
| simdjson (ondemand) | 1167.95 | 0.138777 | 6293.93ms | 4506447 | 80 | 2.08613e+09 | 3.67967e+06 | 0.36136 | 4.37349 | 17.1557 | 3.15455 | 0.0134883 | 0.0789807 | 0.00349918 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.363 | 0.112215 | 7988.99ms | 4506447 | 40 | 1.17355e+09 | 4.82689e+06 | 0.0247602 | 5.70673 | 26.5408 | 5.38696 | 0.0108981 | 0.0812864 | 0.00684429 | 1(Win) | true |
| simdjson (ondemand) | 548.31 | 0.254742 | 5816.78ms | 4506447 | 40 | 1.59469e+10 | 7.83805e+06 | 0.47167 | 9.22485 | 40.1256 | 7.93318 | 0.0288838 | 0.0791796 | 0.0135899 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1451.7 | 0.238149 | 5244.02ms | 4506446 | 30 | 1.4912e+09 | 2.96045e+06 | 0.00436063 | 3.50584 | 16.8994 | 3.26091 | 0.0111585 | 0.0813177 | 0.00192214 | 1(Win) | true |
| simdjson (ondemand) | 942.365 | 0.107436 | 7596.85ms | 4506446 | 80 | 1.92052e+09 | 4.56053e+06 | 0.653637 | 5.41361 | 21.2197 | 4.41481 | 0.0136754 | 0.088716 | 0.00236273 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.136 | 0.0855155 | 8007.86ms | 4506446 | 40 | 6.80345e+08 | 4.8227e+06 | 0.331403 | 5.72125 | 26.3601 | 5.39433 | 0.0116069 | 0.0816116 | 0.00284475 | 1(Win) | true |
| simdjson (ondemand) | 489.598 | 0.188759 | 6499.73ms | 4506446 | 30 | 8.23621e+09 | 8.77798e+06 | 0.288415 | 10.351 | 44.1892 | 9.1933 | 0.0308026 | 0.0885962 | 0.00785706 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2027.88 | 0.255302 | 6987.67ms | 4219120 | 30 | 7.69822e+08 | 1.98418e+06 | 0.0307808 | 2.49578 | 9.19097 | 1.59769 | 0.0145595 | 0.0564623 | 5.16221e-05 | 1(Win) | true |
| simdjson (ondemand) | 1859.42 | 0.0662406 | 7516.54ms | 4219120 | 160 | 3.28743e+08 | 2.16393e+06 | 0.0100513 | 2.71008 | 9.41697 | 1.53176 | 0.0148131 | 0.0534411 | 0.000242447 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.836 | 0.109166 | 8806.03ms | 4219120 | 80 | 2.95414e+09 | 5.5665e+06 | 0.100603 | 7.07129 | 27.3303 | 5.16271 | 0.020239 | 0.0569465 | 0.00121388 | 1(Win) | true |
| simdjson (ondemand) | 330.305 | 0.0725056 | 8716.29ms | 4219120 | 40 | 3.12044e+09 | 1.21817e+07 | 0.100313 | 15.2825 | 61.9272 | 12.5319 | 0.0829527 | 0.0548194 | 0.00801171 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1871.36 | 0.22982 | 7452.67ms | 4219119 | 160 | 3.90682e+09 | 2.15013e+06 | 0.635787 | 2.71639 | 10.2057 | 1.85204 | 0.014781 | 0.0560103 | 0.00248037 | 1(Win) | true |
| simdjson (ondemand) | 1469.93 | 0.069914 | 9283.31ms | 4219119 | 160 | 5.86001e+08 | 2.73731e+06 | 0.0106233 | 3.43179 | 11.8603 | 2.29096 | 0.0178183 | 0.0570876 | 0.00017282 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.339 | 0.0987072 | 8847.59ms | 4219119 | 30 | 9.06944e+08 | 5.57033e+06 | 0.160628 | 7.05242 | 27.2144 | 5.16607 | 0.0199981 | 0.0569846 | 7.22505e-05 | 1(Win) | true |
| simdjson (ondemand) | 313.338 | 0.344183 | 9215.26ms | 4219119 | 30 | 5.86029e+10 | 1.28413e+07 | 0.228224 | 16.102 | 64.3696 | 13.2909 | 0.0866732 | 0.0573884 | 0.0097863 | 2(Loss) | true |
