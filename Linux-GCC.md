# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Linux 7.0.0-38-generic using the GCC 16.2.1 compiler).  

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

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 533.915 | 0.112096 | 921.215ms | 905 | 4890 | 16056.2 | 1616.5 | 0.396902 | 9.58841 | 48.4376 | 5.28066 | 0.00186874 | 0.000149363 | 3.63805e-05 | 1(Win) | true |
| simdjson (ondemand) | 247.391 | 0.0473651 | 1094.17ms | 905 | 4890 | 13352.3 | 3488.71 | 0.00747405 | 20.563 | 101.328 | 9.82436 | 0.0138917 | 0.000141681 | 3.11833e-05 | 2(Loss) | true |

----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 496.727 | 0.138971 | 913.895ms | 905 | 160 | 932.892 | 1737.53 | 0.135433 | 10.2216 | 47.5591 | 5.04972 | 0.0104972 | 0.000151934 | 1.38122e-05 | 1(Win) | true |
| simdjson (ondemand) | 250.242 | 0.0900756 | 1090.4ms | 905 | 2560 | 24707.7 | 3448.97 | 0.0217844 | 20.1547 | 100.646 | 9.68509 | 0.0147333 | 0.00017481 | 5.78384e-05 | 2(Loss) | true |

----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 612.326 | 0.18582 | 1030.81ms | 1811 | 2560 | 70322.6 | 2820.56 | 0.352104 | 8.23864 | 38.3954 | 5.88901 | 0.000567064 | 0.0001704 | 4.85315e-05 | 1(Win) | true |
| simdjson (ondemand) | 312.829 | 0.086752 | 1296.61ms | 1811 | 1280 | 29362.5 | 5520.93 | 0.154623 | 15.9367 | 77.9227 | 10.4699 | 0.000575476 | 0.000106554 | 3.23544e-05 | 2(Loss) | true |

----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 642.631 | 0.106247 | 1008ms | 1811 | 2560 | 20873.1 | 2687.55 | 0.0114229 | 7.90645 | 37.3142 | 5.64937 | 0.00115009 | 0.000112809 | 2.17853e-05 | 1(Win) | true |
| simdjson (ondemand) | 322.859 | 0.111146 | 1276.54ms | 1811 | 2560 | 90497.3 | 5349.41 | 0.0474856 | 15.6125 | 76.8459 | 10.2303 | 0.00114081 | 0.000228206 | 0.000117986 | 2(Loss) | true |

----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1138.2 | 0.12216 | 1049.74ms | 3862 | 30 | 468.783 | 3235.9 | 0.0422167 | 4.24528 | 17.5135 | 2.03858 | 0.000802693 | 2.58933e-05 | 8.63111e-06 | 1(Win) | true |
| simdjson (ondemand) | 712.718 | 0.126966 | 1256.45ms | 3862 | 320 | 13775.7 | 5167.67 | 0.146193 | 7.06147 | 32.7071 | 3.87934 | 0.00845741 | 3.07483e-05 | 9.70999e-06 | 2(Loss) | true |

----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1257.94 | 0.0409153 | 1030.35ms | 3862 | 4890 | 7017.5 | 2927.87 | 0.0137056 | 4.03412 | 16.9738 | 1.91274 | 0.000268835 | 8.22338e-05 | 2.45166e-05 | 1(Win) | true |
| simdjson (ondemand) | 731.496 | 0.0947348 | 1240.6ms | 3862 | 320 | 7280.64 | 5035.01 | 0.0457632 | 6.96152 | 32.2227 | 3.7724 | 0.00993656 | 2.10383e-05 | 0 | 2(Loss) | true |

----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1324.2 | 0.0498367 | 1437.09ms | 9578 | 2560 | 30253.7 | 6897.95 | 0.056083 | 3.79499 | 18.837 | 2.94498 | 0.00332798 | 2.60607e-05 | 2.9772e-06 | 1(Win) | true |
| jsonifier (generic) | 1319.22 | 0.0473004 | 1437.33ms | 9578 | 4890 | 52450.7 | 6923.98 | 0.222499 | 3.82376 | 17.3757 | 3.12852 | 0.000922445 | 4.05027e-05 | 1.08676e-05 | 2(Loss) | true |

----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1787.06 | 0.065119 | 1397.35ms | 9578 | 1280 | 14180.7 | 5111.36 | 0.173301 | 2.8512 | 13.2841 | 2.20025 | 0.000183281 | 2.09628e-05 | 5.465e-06 | 1(Win) | true |
| simdjson (ondemand) | 1779.21 | 0.212388 | 1395.69ms | 9578 | 640 | 76091.1 | 5133.9 | 0.0926079 | 2.82221 | 14.7512 | 2.02266 | 0.00182612 | 1.74554e-05 | 3.42582e-06 | 2(Loss) | true |

----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1396.37 | 0.063601 | 1003.05ms | 3873 | 2560 | 7245.38 | 2645.13 | 0.0121996 | 3.64573 | 16.9744 | 2.0093 | 0.000270503 | 4.65966e-05 | 1.26073e-05 | 1(Win) | true |
| simdjson (ondemand) | 716.589 | 0.0824563 | 1254.34ms | 3873 | 4890 | 88330.7 | 5154.39 | 0.184896 | 7.08379 | 32.4418 | 3.98735 | 0.0109726 | 6.20414e-05 | 1.86916e-05 | 2(Loss) | true |

----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1465.47 | 0.0539064 | 989.653ms | 3873 | 4890 | 9026.68 | 2520.4 | 0.0181225 | 3.48725 | 16.4772 | 1.89879 | 0.000270817 | 3.90729e-05 | 1.38339e-05 | 1(Win) | true |
| simdjson (ondemand) | 721.901 | 0.0449275 | 1248.32ms | 3873 | 2560 | 13527.1 | 5116.46 | 0.138578 | 6.95381 | 31.9553 | 3.88046 | 0.0124389 | 3.56031e-05 | 1.20022e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1476.02 | 0.0254609 | 6916.71ms | 94653 | 2560 | 620680 | 61156.2 | 0.100475 | 3.40205 | 14.9688 | 2.92492 | 0.0108352 | 1.18525e-05 | 7.6513e-06 | 1(Win) | true |
| simdjson (ondemand) | 1229.55 | 0.0732392 | 4120.05ms | 94653 | 160 | 462576 | 73415.5 | 0.0512331 | 4.0998 | 15.6173 | 3.11133 | 0.0117895 | 4.47028e-05 | 3.39398e-05 | 2(Loss) | true |

----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2120.34 | 0.0244259 | 6295.17ms | 94653 | 2560 | 276822 | 42572.5 | 0.00508259 | 2.3788 | 11.2366 | 2.12005 | 0.00781617 | 9.6446e-06 | 5.41039e-06 | 1(Win) | true |
| simdjson (ondemand) | 1591.43 | 0.151936 | 7656.67ms | 94653 | 160 | 1.18832e+06 | 56721.3 | 0.0488812 | 3.12878 | 11.9338 | 2.31535 | 0.00963156 | 1.33382e-05 | 8.91414e-06 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1847.19 | 0.047672 | 7168.59ms | 124597 | 640 | 601867 | 64327.5 | 0.252145 | 2.69863 | 11.723 | 2.22322 | 0.00844142 | 6.05703e-06 | 3.37338e-06 | 1(Win) | true |
| simdjson (ondemand) | 1560.81 | 0.175834 | 4239.94ms | 124597 | 30 | 537582 | 76130.5 | 0.111907 | 3.22765 | 12.1721 | 2.37246 | 0.00938466 | 0.000197704 | 0.000187805 | 2(Loss) | true |

----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2587.43 | 0.0675483 | 6608.56ms | 124597 | 640 | 615869 | 45924 | 0.211068 | 1.92637 | 8.89489 | 1.61223 | 0.00590689 | 4.74028e-06 | 2.04409e-06 | 1(Win) | true |
| simdjson (ondemand) | 2080.52 | 0.125919 | 7728.41ms | 124597 | 40 | 206877 | 57113.1 | 0.00806944 | 2.42828 | 9.37593 | 1.76837 | 0.00713219 | 4.01294e-06 | 2.00647e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1070.59 | 0.0835394 | 4684.39ms | 94653 | 320 | 1.58766e+06 | 84316.5 | 0.276017 | 4.67248 | 20.21 | 4.00359 | 0.0152968 | 1.44607e-05 | 7.29639e-06 | 1(Win) | true |
| simdjson (ondemand) | 672.828 | 0.123466 | 7353.76ms | 94653 | 30 | 823144 | 134162 | 0.089364 | 7.50675 | 31.9279 | 5.84475 | 0.0151187 | 1.26779e-05 | 8.80409e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1384.85 | 0.151458 | 4393.41ms | 94653 | 1280 | 1.24755e+07 | 65182.7 | 0.0363988 | 3.64191 | 16.5008 | 3.20166 | 0.0116218 | 1.79521e-05 | 8.79033e-06 | 1(Win) | true |
| simdjson (ondemand) | 778.546 | 0.084724 | 6977.89ms | 94653 | 1280 | 1.23516e+07 | 115945 | 0.0431096 | 6.49437 | 28.2624 | 5.05184 | 0.0121608 | 2.69983e-05 | 1.5509e-05 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1360.13 | 0.0532713 | 4868.33ms | 124597 | 640 | 1.38619e+06 | 87363.2 | 0.0879826 | 3.69319 | 15.806 | 3.09602 | 0.0100472 | 1.03208e-05 | 6.5461e-06 | 1(Win) | true |
| simdjson (ondemand) | 849.845 | 0.081027 | 7520.56ms | 124597 | 160 | 2.0536e+06 | 139820 | 0.178118 | 5.90712 | 24.3039 | 4.39508 | 0.0112694 | 1.17378e-05 | 3.411e-06 | 2(Loss) | true |

----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1714.39 | 0.0560252 | 4590.32ms | 124597 | 640 | 965038 | 69310.5 | 0.0875836 | 2.94377 | 12.9908 | 2.48695 | 0.00822488 | 9.94456e-06 | 5.88146e-06 | 1(Win) | true |
| simdjson (ondemand) | 987.965 | 0.188522 | 7189.23ms | 124597 | 1280 | 6.58063e+07 | 120272 | 0.148799 | 5.09068 | 21.5121 | 3.7911 | 0.00815647 | 8.52436e-05 | 6.94489e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2491.28 | 0.0325275 | 4389.33ms | 94653 | 4890 | 679258 | 36233.7 | 0.10738 | 2.0267 | 9.52405 | 1.75107 | 0.00472545 | 3.23342e-05 | 2.5049e-05 | 1(Win) | true |
| simdjson (ondemand) | 1812.61 | 0.0911112 | 5762.9ms | 94653 | 160 | 329401 | 49800.2 | 0.0162677 | 2.78705 | 10.5559 | 1.98127 | 0.00820055 | 7.72559e-06 | 4.02787e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3238.82 | 0.0503949 | 4030.87ms | 94653 | 4890 | 964668 | 27870.7 | 0.0499913 | 1.5528 | 7.75801 | 1.38397 | 0.00348183 | 9.36582e-06 | 5.47474e-06 | 1(Win) | true |
| simdjson (ondemand) | 2178.45 | 0.0465877 | 5366.82ms | 94653 | 640 | 238504 | 41436.8 | 0.164799 | 2.31915 | 8.81054 | 1.61973 | 0.00705429 | 6.93322e-06 | 3.64819e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3104.54 | 0.0242117 | 4589.69ms | 124597 | 2560 | 219841 | 38274.6 | 0.131231 | 1.62413 | 7.67772 | 1.34662 | 0.00328343 | 7.3581e-06 | 3.66808e-06 | 1(Win) | true |
| simdjson (ondemand) | 2298.74 | 0.174719 | 5779.08ms | 124597 | 30 | 244701 | 51691.4 | 0.00747973 | 2.20158 | 8.06514 | 1.45993 | 0.00835841 | 4.11995e-05 | 3.1836e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4019.91 | 0.200797 | 4159.75ms | 124597 | 160 | 563661 | 29559.1 | 0.0261273 | 1.24736 | 6.33906 | 1.06761 | 0.00222558 | 2.80404e-05 | 2.30242e-05 | 1(Win) | true |
| simdjson (ondemand) | 2866 | 0.0937506 | 5407.31ms | 124597 | 160 | 241730 | 41460.2 | 0.00316559 | 1.75826 | 6.74168 | 1.18537 | 0.005443 | 1.47475e-05 | 1.17378e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1871.41 | 0.0251963 | 5570.87ms | 94653 | 2560 | 378134 | 48235.5 | 0.00793165 | 2.66982 | 12.3493 | 2.38631 | 0.0069029 | 1.89673e-05 | 1.42131e-05 | 1(Win) | true |
| simdjson (ondemand) | 1543.75 | 0.0465068 | 6609.04ms | 94653 | 640 | 473290 | 58473.3 | 0.0384592 | 3.26871 | 13.0526 | 2.38075 | 0.0114208 | 1.45928e-05 | 8.53446e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2261.51 | 0.0379119 | 5242.79ms | 94653 | 2560 | 586221 | 39914.9 | 0.105451 | 2.21927 | 10.5888 | 2.01973 | 0.00617184 | 9.03382e-06 | 4.54373e-06 | 1(Win) | true |
| simdjson (ondemand) | 1830.51 | 0.0200095 | 6188.9ms | 94653 | 2560 | 249251 | 49313.1 | 0.0231063 | 2.76225 | 11.3209 | 2.02149 | 0.00947835 | 1.39366e-05 | 8.80684e-06 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2316.05 | 0.0579665 | 5874.79ms | 124597 | 320 | 283024 | 51304.9 | 0.0169424 | 2.18073 | 9.7986 | 1.8413 | 0.00516821 | 9.98218e-06 | 6.9474e-06 | 1(Win) | true |
| simdjson (ondemand) | 2060.36 | 0.0257233 | 6581.41ms | 124597 | 2560 | 563406 | 57671.9 | 0.0497849 | 2.45541 | 9.96954 | 1.76415 | 0.00814193 | 3.07993e-05 | 1.85348e-05 | 2(Loss) | true |

----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2777.47 | 0.0307878 | 5509.3ms | 124597 | 2560 | 444132 | 42781.7 | 0.164583 | 1.81216 | 8.4595 | 1.56328 | 0.0043575 | 4.7685e-06 | 1.71177e-06 | 1(Win) | true |
| simdjson (ondemand) | 2440.33 | 0.0452862 | 6087.58ms | 124597 | 640 | 311193 | 48692.1 | 0.0126705 | 2.06704 | 8.64999 | 1.49063 | 0.00655846 | 2.04409e-05 | 1.28665e-05 | 2(Loss) | true |

----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 774.2 | 0.0729204 | 8032.58ms | 2090234 | 40 | 1.41007e+08 | 2.57479e+06 | 0.408688 | 6.52203 | 30.7841 | 5.61639 | 0.0233548 | 0.105347 | 0.00209489 | 1(Win) | true |
| jsonifier (generic) | 725.185 | 0.113645 | 4133.4ms | 2090234 | 80 | 7.80693e+08 | 2.74882e+06 | 0.10295 | 6.9153 | 31.6824 | 6.46675 | 0.0275697 | 0.106111 | 0.0011333 | 2(Loss) | true |

----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 907.846 | 0.157642 | 8024.84ms | 2090234 | 80 | 9.5852e+08 | 2.19575e+06 | 0.14386 | 5.55792 | 25.48 | 4.35399 | 0.0224314 | 0.0799343 | 0.000469325 | 1(Win) | true |
| jsonifier (generic) | 848.572 | 0.0922985 | 4121.63ms | 2090234 | 80 | 3.76091e+08 | 2.34913e+06 | 0.0475849 | 5.91176 | 26.4054 | 5.21003 | 0.026607 | 0.0803575 | 0.000530114 | 2(Loss) | true |

----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1798.15 | 0.0677808 | 4175.04ms | 5212421 | 80 | 2.80886e+08 | 2.76448e+06 | 0.256 | 2.80526 | 13.1503 | 2.28685 | 0.0105532 | 0.0618263 | 0.00124259 | 1(Win) | true |
| jsonifier (generic) | 1726.68 | 0.0672849 | 4340.58ms | 5212421 | 80 | 3.00178e+08 | 2.8789e+06 | 0.328264 | 2.91701 | 13.4986 | 2.64602 | 0.0103637 | 0.0615444 | 0.00120618 | 2(Loss) | true |

----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2081.67 | 0.209779 | 4166.78ms | 5212421 | 80 | 2.00755e+09 | 2.38796e+06 | 0.129477 | 2.42753 | 11.0251 | 1.78095 | 0.0101677 | 0.0515565 | 0.00058275 | 1(Win) | true |
| jsonifier (generic) | 1986.48 | 0.258426 | 4352.29ms | 5212421 | 40 | 1.67281e+09 | 2.5024e+06 | 0.0852493 | 2.53587 | 11.3699 | 2.13942 | 0.00999367 | 0.0513367 | 0.000418155 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 703.697 | 0.259985 | 4278.18ms | 2090234 | 80 | 4.33915e+09 | 2.83276e+06 | 0.122535 | 7.17777 | 34.377 | 6.21489 | 0.0234054 | 0.180641 | 0.000214844 | 1(Win) | true |
| jsonifier (generic) | 682.393 | 0.281446 | 4393.64ms | 2090234 | 80 | 5.40755e+09 | 2.9212e+06 | 0.514366 | 7.37128 | 34.1931 | 6.87323 | 0.0274906 | 0.156091 | 0.000469206 | 2(Loss) | true |

----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 808.422 | 0.294069 | 4278.38ms | 2090234 | 80 | 4.20634e+09 | 2.4658e+06 | 0.121026 | 6.24358 | 29.0788 | 4.95365 | 0.0225463 | 0.154877 | 0.000595059 | 1(Win) | true |
| jsonifier (generic) | 790.554 | 0.166103 | 4415.21ms | 2090234 | 40 | 7.01688e+08 | 2.52152e+06 | 0.456505 | 6.36205 | 28.8855 | 5.61023 | 0.0263561 | 0.130191 | 0.000110622 | 2(Loss) | true |

----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1565.41 | 0.13518 | 4796.03ms | 5212421 | 40 | 7.37065e+08 | 3.17549e+06 | 0.236413 | 3.24148 | 14.583 | 2.52511 | 0.0105881 | 0.121746 | 0.00119841 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 1556.82 | 0.250474 | 4791.03ms | 5212421 | 80 | 5.11703e+09 | 3.19302e+06 | 0.529892 | 3.23207 | 14.4944 | 2.80671 | 0.010341 | 0.10107 | 0.000476525 | 1(Tie) | true |

----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1779.41 | 0.152049 | 4787.08ms | 5212421 | 80 | 1.44339e+09 | 2.79359e+06 | 0.387886 | 2.83545 | 12.3646 | 2.2999 | 0.00999912 | 0.0907218 | 0.000865754 | 1(Win) | true |
| simdjson (ondemand) | 1772.52 | 0.0950439 | 4822.6ms | 5212421 | 30 | 2.13142e+08 | 2.80446e+06 | 0.0716285 | 2.85406 | 12.4683 | 2.02143 | 0.0102352 | 0.111375 | 0.000307969 | 2(Loss) | true |

----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 7189.25 | 0.103367 | 7251.62ms | 2090234 | 80 | 6.57172e+06 | 277276 | 0.0759072 | 0.704138 | 3.4262 | 0.298422 | 0.00262695 | 0.0495449 | 1.69239e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 7165.44 | 0.227021 | 7314.76ms | 2090234 | 640 | 2.5528e+08 | 278197 | 0.0589589 | 0.709804 | 2.97957 | 0.393263 | 0.00588334 | 0.0504056 | 2.13941e-06 | 1(Tie) | true |

----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7255.09 | 0.0400978 | 7224.53ms | 2090234 | 640 | 7.76831e+06 | 274759 | 0.0958931 | 0.697727 | 3.42613 | 0.298404 | 0.00239404 | 0.0494904 | 4.04261e-06 | 1(Win) | true |
| jsonifier (generic) | 7143.85 | 0.0818075 | 7340.06ms | 2090234 | 1280 | 6.66993e+07 | 279038 | 0.40107 | 0.709022 | 2.97949 | 0.393246 | 0.00587733 | 0.0503293 | 3.14708e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10799.7 | 0.227971 | 5955.05ms | 5212421 | 40 | 4.4043e+07 | 460287 | 0.0450675 | 0.467414 | 1.81398 | 0.17759 | 0.00215724 | 0.0394247 | 3.51564e-06 | 1(Win) | true |
| simdjson (ondemand) | 9297.48 | 0.307035 | 6930.93ms | 5212421 | 80 | 2.15584e+08 | 534656 | 0.0659288 | 0.543729 | 2.18139 | 0.154671 | 0.00213266 | 0.0394713 | 4.28064e-06 | 2(Loss) | true |

----
### Canada Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10783.2 | 0.394358 | 5952.96ms | 5212421 | 640 | 2.11518e+09 | 460991 | 0.0046112 | 0.468739 | 1.81395 | 0.177583 | 0.00211988 | 0.0394066 | 1.95327e-06 | 1(Win) | true |
| simdjson (ondemand) | 9360.15 | 0.0409411 | 6896.82ms | 5212421 | 640 | 3.02561e+07 | 531076 | 0.175993 | 0.543217 | 2.18135 | 0.154664 | 0.00218302 | 0.0393872 | 4.23717e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5529.89 | 0.0546714 | 4719.01ms | 2090234 | 640 | 2.48575e+07 | 360478 | 0.700698 | 0.921519 | 4.21941 | 0.593252 | 0.00588417 | 0.07541 | 4.46945e-06 | 1(Win) | true |
| simdjson (ondemand) | 5490.98 | 0.0573294 | 4705.11ms | 2090234 | 160 | 6.93052e+06 | 363032 | 0.18344 | 0.92235 | 4.62596 | 0.498384 | 0.00257605 | 0.0751228 | 1.94057e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 5523.99 | 0.0460476 | 4691.63ms | 2090234 | 640 | 1.76717e+07 | 360862 | 0.101298 | 0.918755 | 4.62588 | 0.498366 | 0.0024548 | 0.0750591 | 4.68623e-06 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 5515.08 | 0.164869 | 4771.42ms | 2090234 | 40 | 1.42044e+07 | 361446 | 0.0374743 | 0.919278 | 4.21933 | 0.593235 | 0.00583933 | 0.0753605 | 3.65988e-06 | 1(Tie) | true |

----
### Canada Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8341.19 | 0.241781 | 7686.2ms | 5212421 | 40 | 8.30473e+07 | 595952 | 0.201127 | 0.605395 | 2.31118 | 0.257789 | 0.00215677 | 0.0591065 | 6.66677e-06 | 1(Win) | true |
| simdjson (ondemand) | 7296.21 | 0.491936 | 4317.55ms | 5212421 | 320 | 3.59461e+09 | 681306 | 0.310729 | 0.692815 | 2.6625 | 0.234858 | 0.00217736 | 0.0591706 | 2.63193e-06 | 2(Loss) | true |

----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8388.14 | 0.177064 | 7773.39ms | 5212421 | 30 | 3.30316e+07 | 592616 | 0.272389 | 0.606172 | 2.31115 | 0.257782 | 0.00215636 | 0.0590902 | 1.75862e-06 | 1(Win) | true |
| simdjson (ondemand) | 7438.14 | 0.336412 | 4345.36ms | 5212421 | 160 | 8.0875e+08 | 668306 | 0.590861 | 0.688039 | 2.66247 | 0.23485 | 0.00215655 | 0.0591383 | 2.33097e-06 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1318.19 | 0.188934 | 4835.26ms | 500299 | 40 | 1.87062e+07 | 361954 | 0.000181883 | 3.83887 | 16.9876 | 3.35425 | 0.0167827 | 0.00883492 | 6.32122e-05 | 1(Win) | true |
| simdjson (ondemand) | 1173.16 | 0.0411663 | 5274.24ms | 500299 | 640 | 1.79394e+07 | 406698 | 0.118596 | 4.3004 | 17.2265 | 2.95183 | 0.021173 | 0.01363 | 0.000146281 | 2(Loss) | true |

----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1449.31 | 0.993032 | 4694.63ms | 500299 | 320 | 3.41992e+09 | 329208 | 0.449647 | 3.48492 | 15.8571 | 3.08355 | 0.0113439 | 0.0072562 | 3.3099e-05 | 1(Win) | true |
| simdjson (ondemand) | 1321.43 | 0.0478194 | 5148.92ms | 500299 | 320 | 9.53955e+06 | 361064 | 0.0755172 | 3.81949 | 16.0975 | 2.68064 | 0.0150484 | 0.0113426 | 0.000119547 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2618.5 | 0.134495 | 5445.92ms | 1151920 | 80 | 2.54708e+07 | 419536 | 0.0694105 | 1.92864 | 8.11355 | 1.48967 | 0.0102003 | 0.0372931 | 6.0486e-05 | 1(Win) | true |
| simdjson (ondemand) | 2479.09 | 0.0930513 | 5747.38ms | 1151920 | 80 | 1.36018e+07 | 443130 | 0.0916542 | 2.03472 | 8.24718 | 1.31556 | 0.00889079 | 0.0359915 | 5.95202e-05 | 2(Loss) | true |

----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2938.58 | 0.0616564 | 5319.6ms | 1151920 | 640 | 3.40023e+07 | 373840 | 0.0840973 | 1.71841 | 7.62315 | 1.37228 | 0.00764841 | 0.032782 | 2.92433e-05 | 1(Win) | true |
| simdjson (ondemand) | 2750.77 | 0.0568635 | 5615.78ms | 1151920 | 160 | 8.25136e+06 | 399364 | 0.0193908 | 1.83451 | 7.75906 | 1.19839 | 0.00661327 | 0.031602 | 1.54145e-05 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 655.965 | 0.108717 | 4639.76ms | 500299 | 160 | 1.00048e+08 | 727360 | 0.0132981 | 7.72281 | 34.0267 | 6.41861 | 0.0308316 | 0.0112582 | 0.000213647 | 1(Win) | true |
| simdjson (ondemand) | 383.283 | 0.682567 | 8017.78ms | 500299 | 160 | 1.15513e+10 | 1.24483e+06 | 0.279613 | 13.2172 | 57.8399 | 9.6881 | 0.0555085 | 0.0160422 | 0.000282019 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 703.905 | 0.133507 | 4545.9ms | 500299 | 40 | 3.27568e+07 | 677822 | 0.0421664 | 7.18898 | 32.8899 | 6.14802 | 0.0236451 | 0.00808681 | 9.99402e-05 | 1(Win) | true |
| simdjson (ondemand) | 404.478 | 0.246613 | 7748.78ms | 500299 | 320 | 2.70803e+09 | 1.1796e+06 | 0.296761 | 12.5663 | 56.7083 | 9.41936 | 0.0486645 | 0.010352 | 0.000223242 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1313.88 | 0.136658 | 5432.04ms | 1151920 | 320 | 4.17782e+08 | 836114 | 0.413631 | 3.86122 | 15.5952 | 2.85969 | 0.016516 | 0.0418353 | 8.86428e-05 | 1(Win) | true |
| simdjson (ondemand) | 745.301 | 2.35358 | 4592.11ms | 1151920 | 160 | 1.92558e+11 | 1.47398e+06 | 1.05125 | 6.83424 | 25.8596 | 4.23549 | 0.0227412 | 0.0701998 | 0.000335749 | 2(Loss) | true |

----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1395.21 | 0.143003 | 5333.95ms | 1151920 | 80 | 1.01425e+08 | 787380 | 0.0596101 | 3.63121 | 15.1018 | 2.74229 | 0.0136417 | 0.0371681 | 6.8375e-05 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 773.575 | 3.09142 | 4447.97ms | 1151920 | 80 | 1.54187e+11 | 1.4201e+06 | 2.73172 | 6.56974 | 25.3695 | 4.1191 | 0.0198119 | 0.0595634 | 4.2809e-05 | -(Loss) | false |

----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5481.23 | 0.0322296 | 4845.61ms | 500299 | 640 | 503725 | 87046.6 | 0.0650091 | 0.923485 | 4.60482 | 0.701906 | 0.000589797 | 6.70849e-06 | 4.8065e-06 | 1(Win) | true |
| simdjson (ondemand) | 5063.63 | 0.033235 | 5203.41ms | 500299 | 2560 | 2.51053e+06 | 94225.4 | 0.207789 | 1.00184 | 5.26911 | 0.542038 | 0.000808119 | 0.000167889 | 2.61726e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5490.76 | 0.0285451 | 4825.31ms | 500299 | 1280 | 787530 | 86895.5 | 0.0947457 | 0.91848 | 4.58021 | 0.698027 | 0.000580826 | 1.86389e-05 | 1.71991e-05 | 1(Win) | true |
| simdjson (ondemand) | 5082.42 | 0.0722216 | 5200.08ms | 500299 | 320 | 1.47097e+06 | 93877 | 0.0672108 | 0.997145 | 5.24474 | 0.538138 | 0.000821221 | 9.68671e-05 | 1.47537e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8360.69 | 0.190071 | 7177.39ms | 1151920 | 2560 | 1.59673e+08 | 131395 | 0.183101 | 0.603347 | 2.65376 | 0.325748 | 0.000351404 | 0.00683539 | 1.33198e-05 | 1(Win) | true |
| simdjson (ondemand) | 7681.64 | 0.138551 | 7721.56ms | 1151920 | 80 | 3.14084e+06 | 143011 | 0.00381105 | 0.656182 | 3.05194 | 0.268505 | 0.000777712 | 0.00658152 | 1.62663e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8444.32 | 0.104714 | 7086.39ms | 1151920 | 640 | 1.18769e+07 | 130094 | 0.023888 | 0.598838 | 2.64307 | 0.324063 | 0.000360713 | 0.00661087 | 2.09474e-05 | 1(Win) | true |
| simdjson (ondemand) | 7692.76 | 0.0693655 | 7701.7ms | 1151920 | 1280 | 1.25596e+07 | 142804 | 0.0257301 | 0.654952 | 3.04136 | 0.266811 | 0.000795436 | 0.00633664 | 1.39699e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3107.93 | 0.0503761 | 4113.47ms | 500299 | 160 | 956941 | 153518 | 0.107315 | 1.62618 | 8.37694 | 1.35875 | 0.00161751 | 3.61909e-05 | 3.29928e-05 | 1(Win) | true |
| simdjson (ondemand) | 2939.04 | 0.0284956 | 4338.75ms | 500299 | 1280 | 2.73915e+06 | 162340 | 0.0436337 | 1.7173 | 9.14556 | 1.19884 | 0.00230266 | 0.000134323 | 3.23619e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3122.89 | 0.0809094 | 4099.45ms | 500299 | 40 | 611227 | 152782 | 0.0169769 | 1.61755 | 8.35236 | 1.35487 | 0.00160744 | 1.65401e-05 | 1.45413e-05 | 1(Win) | true |
| simdjson (ondemand) | 2956.17 | 0.0311622 | 4318.91ms | 500299 | 640 | 1.61897e+06 | 161399 | 0.102821 | 1.71025 | 9.12117 | 1.19494 | 0.0023119 | 0.000102648 | 2.10749e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5474.77 | 0.397705 | 5338.83ms | 1151920 | 40 | 2.54739e+07 | 200658 | 0.0755856 | 0.915684 | 4.29805 | 0.614401 | 0.00122172 | 0.00695519 | 2.0596e-05 | 1(Win) | true |
| simdjson (ondemand) | 5217.88 | 0.0904515 | 5574.32ms | 1151920 | 320 | 1.16048e+07 | 210537 | 0.00752597 | 0.968392 | 4.73555 | 0.553765 | 0.00142864 | 0.00682107 | 2.26632e-05 | 2(Loss) | true |

----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5497.19 | 0.177825 | 5303.44ms | 1151920 | 320 | 4.04108e+07 | 199840 | 0.2198 | 0.911378 | 4.28737 | 0.612716 | 0.00116649 | 0.00666298 | 1.07809e-05 | 1(Win) | true |
| simdjson (ondemand) | 5222.94 | 0.0752702 | 5567.91ms | 1151920 | 80 | 2.00516e+06 | 210333 | 0.168487 | 0.966748 | 4.72496 | 0.552072 | 0.00143041 | 0.006536 | 3.43448e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1418.99 | 0.0889109 | 4547.64ms | 56369 | 160 | 181531 | 37884.4 | 0.0485123 | 3.5581 | 14.9867 | 3.09284 | 0.00782012 | 3.79198e-05 | 2.61669e-05 | 1(Win) | true |
| simdjson (ondemand) | 1214.45 | 0.0394711 | 5169.35ms | 56369 | 1280 | 390743 | 44265.1 | 0.118759 | 4.14854 | 15.2279 | 2.79876 | 0.0105575 | 5.4579e-05 | 3.6714e-05 | 2(Loss) | true |

----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1746 | 0.0279436 | 4167.42ms | 56369 | 2560 | 189494 | 30789 | 0.117765 | 2.89273 | 12.8582 | 2.6568 | 0.00579526 | 2.91536e-05 | 1.7761e-05 | 1(Win) | true |
| simdjson (ondemand) | 1405.63 | 0.0379058 | 4930.88ms | 56369 | 1280 | 269006 | 38244.6 | 0.118011 | 3.58987 | 13.159 | 2.37797 | 0.0118961 | 1.74492e-05 | 8.88398e-06 | 2(Loss) | true |

----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2025.47 | 0.124465 | 4714.27ms | 83958 | 80 | 193668 | 39530.9 | 0.0454185 | 2.49562 | 10.5191 | 2.08635 | 0.0054767 | 1.9206e-05 | 1.29529e-05 | 1(Win) | true |
| simdjson (ondemand) | 1746.04 | 0.026088 | 5333.12ms | 83958 | 4890 | 699851 | 45857.3 | 0.0691539 | 2.89008 | 10.6899 | 1.89928 | 0.00785708 | 4.12223e-05 | 2.67541e-05 | 2(Loss) | true |

----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2496.17 | 0.0477932 | 4286.21ms | 83958 | 640 | 150414 | 32076.6 | 0.0704652 | 2.02222 | 9.09206 | 1.79408 | 0.00394154 | 1.8108e-05 | 1.25993e-05 | 1(Win) | true |
| simdjson (ondemand) | 2021.95 | 0.0430304 | 5085.01ms | 83958 | 640 | 185829 | 39599.7 | 0.066202 | 2.49758 | 9.29587 | 1.61609 | 0.00803919 | 3.81143e-05 | 2.73202e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 663.752 | 0.0788184 | 4537.19ms | 56369 | 30 | 122249 | 80990.6 | 0.0333261 | 7.61608 | 33.3339 | 6.50127 | 0.0126991 | 1.89229e-05 | 1.18268e-05 | 1(Win) | true |
| simdjson (ondemand) | 207.643 | 0.049698 | 6805.67ms | 56369 | 320 | 5.29753e+06 | 258894 | 0.0862679 | 24.2607 | 117.835 | 21.0378 | 0.0342056 | 0.000215877 | 0.000166814 | 2(Loss) | true |

----
### Discord Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 732.569 | 0.0713566 | 4326.1ms | 56369 | 40 | 109676 | 73382.4 | 0.0280302 | 6.89939 | 31.2121 | 6.06305 | 0.0119095 | 1.72967e-05 | 7.53961e-06 | 1(Win) | true |
| simdjson (ondemand) | 214.681 | 0.0530321 | 6709.38ms | 56369 | 160 | 2.82157e+06 | 250407 | 0.20581 | 23.5774 | 115.765 | 20.6146 | 0.0320311 | 9.38016e-05 | 6.89652e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 932.379 | 0.090044 | 4769.84ms | 83958 | 30 | 179378 | 85875.6 | 0.0940786 | 5.42209 | 23.4851 | 4.67284 | 0.00889175 | 6.55089e-05 | 4.9231e-05 | 1(Win) | true |
| simdjson (ondemand) | 308.698 | 0.0534979 | 6829.75ms | 83958 | 320 | 6.16142e+06 | 259375 | 0.00407694 | 16.5164 | 79.3522 | 14.0896 | 0.021843 | 8.62783e-05 | 6.49879e-05 | 2(Loss) | true |

----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1017.66 | 0.052491 | 4598.46ms | 83958 | 320 | 545811 | 78679.5 | 0.00158478 | 4.9724 | 22.0629 | 4.37967 | 0.0080905 | 4.87223e-05 | 3.71093e-05 | 1(Win) | true |
| simdjson (ondemand) | 317.4 | 0.159536 | 6789.65ms | 83958 | 30 | 4.85902e+06 | 252264 | 0.0411115 | 16.0694 | 77.9625 | 13.805 | 0.0208537 | 3.49381e-05 | 1.98512e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2467.39 | 0.13189 | 2954.23ms | 56369 | 160 | 132115 | 21787.3 | 0.491723 | 2.05739 | 9.54996 | 1.77013 | 0.00268377 | 7.68374e-05 | 5.14467e-05 | 1(Win) | true |
| simdjson (ondemand) | 2244.51 | 0.0753356 | 3206.76ms | 56369 | 80 | 26045.4 | 23950.8 | 0.279108 | 2.25558 | 9.91397 | 1.61813 | 0.00254151 | 7.73918e-05 | 6.96305e-05 | 2(Loss) | true |

----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3151.97 | 0.0643771 | 2798.58ms | 56369 | 320 | 38577 | 17055.2 | 0.265505 | 1.60505 | 8.00765 | 1.45055 | 0.00147255 | 1.38041e-05 | 7.53961e-06 | 1(Win) | true |
| simdjson (ondemand) | 2778.78 | 0.0304827 | 3004.94ms | 56369 | 4890 | 170054 | 19345.8 | 0.13311 | 1.8353 | 8.37301 | 1.30047 | 0.00164904 | 9.47235e-06 | 4.49855e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3356.37 | 0.0426525 | 3140.31ms | 83958 | 1280 | 132521 | 23855.7 | 0.0131013 | 1.51409 | 6.89856 | 1.20991 | 0.00228982 | 1.29808e-05 | 7.30462e-06 | 1(Win) | true |
| simdjson (ondemand) | 3176.99 | 0.0271248 | 3274.49ms | 83958 | 2560 | 119637 | 25202.7 | 0.00638533 | 1.59824 | 7.12527 | 1.1065 | 0.00158149 | 1.36508e-05 | 8.34681e-06 | 2(Loss) | true |

----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4203.72 | 0.0229264 | 2976.55ms | 83958 | 4890 | 93247.9 | 19047.1 | 0.108605 | 1.20935 | 5.85914 | 0.994617 | 0.00124324 | 9.36782e-06 | 6.03087e-06 | 1(Win) | true |
| simdjson (ondemand) | 3830.93 | 0.0751924 | 3125.56ms | 83958 | 160 | 39517 | 20900.6 | 0.0603817 | 1.32299 | 6.09105 | 0.893363 | 0.00112638 | 3.27545e-06 | 8.93304e-07 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1899.14 | 0.0218408 | 3576.19ms | 56369 | 2560 | 97845.6 | 28306.3 | 0.0227247 | 2.66196 | 12.5728 | 2.35773 | 0.00286172 | 2.34365e-05 | 1.40328e-05 | 1(Win) | true |
| simdjson (ondemand) | 1460.34 | 0.0773376 | 4421.08ms | 56369 | 80 | 64840 | 36811.7 | 0.0183399 | 3.46304 | 16.0649 | 2.73392 | 0.00697458 | 5.10032e-06 | 1.99578e-06 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2250.18 | 0.058406 | 3430.33ms | 56369 | 640 | 124607 | 23890.4 | 0.047388 | 2.24799 | 11.0217 | 2.03706 | 0.00213443 | 7.65048e-06 | 2.91051e-06 | 1(Win) | true |
| simdjson (ondemand) | 1650.31 | 0.0327868 | 4323.16ms | 56369 | 2560 | 292005 | 32574.3 | 0.0541389 | 3.06107 | 14.5552 | 2.42391 | 0.00636659 | 3.1184e-05 | 2.25426e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2618.17 | 0.189256 | 3792.42ms | 83958 | 80 | 267990 | 30581.9 | 0.0397043 | 1.92301 | 8.97555 | 1.62735 | 0.00188219 | 2.70969e-05 | 1.9206e-05 | 1(Win) | true |
| simdjson (ondemand) | 2113.08 | 0.0560793 | 4535.34ms | 83958 | 320 | 144493 | 37891.8 | 0.0410713 | 2.38906 | 11.1262 | 1.8296 | 0.00468999 | 2.55336e-05 | 1.63772e-05 | 2(Loss) | true |

----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3086.1 | 0.0392277 | 3643.01ms | 83958 | 640 | 66293.5 | 25944.9 | 0.0207127 | 1.64028 | 7.93325 | 1.41211 | 0.0014645 | 1.62097e-05 | 9.54718e-06 | 1(Win) | true |
| simdjson (ondemand) | 2399.93 | 0.0256822 | 4390.87ms | 83958 | 4890 | 359008 | 33363 | 0.0656285 | 2.10855 | 10.1162 | 1.62203 | 0.00434295 | 9.1827e-06 | 4.51097e-06 | 2(Loss) | true |

----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1252.67 | 0.0659434 | 4855.07ms | 53331 | 2560 | 1.83515e+06 | 40601.7 | 0.0416845 | 4.02812 | 13.4879 | 2.61566 | 0.0146202 | 9.82001e-05 | 6.15188e-05 | 1(Win) | true |
| simdjson (ondemand) | 1064.06 | 0.157231 | 5517.06ms | 53331 | 320 | 1.80739e+06 | 47798.3 | 0.0156215 | 4.74358 | 16.8682 | 3.15207 | 0.0169221 | 0.000262394 | 0.000153288 | 2(Loss) | true |

----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1560.58 | 0.0700072 | 4574.58ms | 53331 | 4890 | 2.54553e+06 | 32590.6 | 0.0693327 | 3.24363 | 11.3249 | 2.13419 | 0.011716 | 5.50408e-05 | 3.34255e-05 | 1(Win) | true |
| simdjson (ondemand) | 1295.99 | 0.0957005 | 5252.26ms | 53331 | 320 | 451376 | 39244.6 | 0.0281727 | 3.90343 | 14.7512 | 2.68175 | 0.0128141 | 1.68171e-05 | 8.08629e-06 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1465.12 | 0.0294156 | 4982.79ms | 65103 | 4890 | 759830 | 42376.7 | 0.153339 | 3.45074 | 11.4566 | 2.19891 | 0.0120614 | 5.01549e-05 | 2.70611e-05 | 1(Win) | true |
| simdjson (ondemand) | 1289.75 | 0.0438283 | 5574.18ms | 65103 | 2560 | 1.13956e+06 | 48138.7 | 0.0166498 | 3.92163 | 14.0366 | 2.58244 | 0.0142875 | 7.26133e-05 | 4.01107e-05 | 2(Loss) | true |

----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1814.24 | 0.0394107 | 4746.3ms | 65103 | 2560 | 465675 | 34222.1 | 0.0174123 | 2.78695 | 9.686 | 1.80503 | 0.0095942 | 1.72923e-05 | 9.63017e-06 | 1(Win) | true |
| simdjson (ondemand) | 1553.43 | 0.0241347 | 5330.29ms | 65103 | 4890 | 454999 | 39967.6 | 0.071781 | 3.25378 | 12.3037 | 2.19845 | 0.01101 | 1.7113e-05 | 8.18901e-06 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 895.159 | 0.0749022 | 6446.02ms | 53331 | 1280 | 2.31824e+06 | 56817.2 | 0.00713414 | 5.65843 | 19.078 | 3.67088 | 0.0214868 | 0.000192269 | 0.000133673 | 1(Win) | true |
| simdjson (ondemand) | 419.253 | 0.132967 | 6618.62ms | 53331 | 1280 | 3.33048e+07 | 121312 | 0.104601 | 12.0726 | 36.8783 | 7.17651 | 0.108503 | 0.000190819 | 0.00012462 | 2(Loss) | true |

----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1062.82 | 0.0940363 | 6153.95ms | 53331 | 640 | 1.29601e+06 | 47854 | 0.15723 | 4.7556 | 16.8451 | 3.17138 | 0.0166572 | 2.60168e-05 | 1.59968e-05 | 1(Win) | true |
| simdjson (ondemand) | 461.974 | 0.0982929 | 6375.31ms | 53331 | 2560 | 2.99785e+07 | 110094 | 0.139979 | 10.9767 | 34.6979 | 6.69157 | 0.0970796 | 0.000114439 | 7.68784e-05 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1040.5 | 0.0870552 | 6735.26ms | 65103 | 640 | 1.72699e+06 | 59670.6 | 0.142066 | 4.8654 | 16.2302 | 3.15503 | 0.0176809 | 2.82485e-05 | 1.76163e-05 | 1(Win) | true |
| simdjson (ondemand) | 547.257 | 0.116882 | 6184.87ms | 65103 | 1280 | 2.25072e+07 | 113451 | 0.0803182 | 9.22766 | 30.1155 | 5.81485 | 0.0711882 | 0.000233452 | 0.000174807 | 2(Loss) | true |

----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1224.93 | 0.0456297 | 6426.95ms | 65103 | 2560 | 1.36935e+06 | 50686.2 | 0.0511773 | 4.14889 | 14.4019 | 2.7463 | 0.0138742 | 2.01124e-05 | 1.04222e-05 | 1(Win) | true |
| simdjson (ondemand) | 607.88 | 0.173069 | 5967.9ms | 65103 | 640 | 1.99979e+07 | 102137 | 0.0963034 | 8.31661 | 28.3366 | 5.41917 | 0.0621188 | 6.08651e-05 | 3.82087e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8380.67 | 0.147148 | 1350.63ms | 53331 | 40 | 3189.87 | 6068.77 | 0.00672888 | 0.607535 | 2.8267 | 0.401961 | 0.000269543 | 5.62525e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7065.61 | 0.0872948 | 1465.61ms | 53331 | 30 | 1184.56 | 7198.3 | 0.0490616 | 0.720038 | 3.26394 | 0.375391 | 0.00045377 | 5.62525e-06 | 0 | 2(Loss) | true |

----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9033 | 0.0360233 | 1324.99ms | 53331 | 2560 | 10531.8 | 5630.51 | 0.076055 | 0.564108 | 2.67867 | 0.374566 | 0.000218872 | 3.75016e-06 | 8.42322e-07 | 1(Win) | true |
| simdjson (ondemand) | 7620.16 | 0.108925 | 1433.44ms | 53331 | 40 | 2114.2 | 6674.45 | 0.00224743 | 0.680395 | 3.12276 | 0.349178 | 0.000402674 | 1.73445e-05 | 1.07817e-05 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8848.19 | 0.050455 | 1446.69ms | 65103 | 1280 | 16044 | 7016.92 | 0.0109211 | 0.57527 | 2.6475 | 0.339585 | 0.000207376 | 5.19609e-06 | 2.19604e-06 | 1(Win) | true |
| simdjson (ondemand) | 7921.54 | 0.0300838 | 1523.47ms | 65103 | 4890 | 27186.8 | 7837.75 | 0.352862 | 0.642292 | 2.94874 | 0.320692 | 0.000247489 | 1.22914e-05 | 7.36602e-06 | 2(Loss) | true |

----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9364.62 | 0.0562051 | 1425.05ms | 65103 | 1280 | 17774 | 6629.96 | 0.0953446 | 0.54274 | 2.52807 | 0.317497 | 0.000205684 | 1.27802e-05 | 9.45617e-06 | 1(Win) | true |
| simdjson (ondemand) | 8344.21 | 0.105536 | 1512.04ms | 65103 | 1280 | 78930.9 | 7440.74 | 0.15933 | 0.610333 | 2.82757 | 0.298158 | 0.000288017 | 8.07614e-06 | 5.00409e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6082.69 | 0.0633383 | 1586.38ms | 53331 | 640 | 17950.7 | 8361.5 | 0.0228218 | 0.835318 | 4.02424 | 0.629278 | 0.000314223 | 5.33226e-06 | 1.69929e-06 | 1(Win) | true |
| simdjson (ondemand) | 4560.48 | 0.0646077 | 1863.39ms | 53331 | 640 | 33226.6 | 11152.4 | 0.0326549 | 1.11046 | 5.44184 | 0.751158 | 0.000456172 | 1.33893e-05 | 8.14489e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6413.52 | 0.0399759 | 1556.8ms | 53331 | 2560 | 25727.8 | 7930.19 | 0.0555939 | 0.792199 | 3.87204 | 0.601451 | 0.000401553 | 8.32068e-06 | 4.65108e-06 | 1(Win) | true |
| simdjson (ondemand) | 4736.47 | 0.140838 | 1839.02ms | 53331 | 1280 | 292753 | 10738 | 0.21122 | 1.06951 | 5.29379 | 0.723651 | 0.000518739 | 1.58503e-05 | 9.22892e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6623.06 | 0.0831141 | 1679.19ms | 65103 | 2560 | 155408 | 9374.37 | 0.0860506 | 0.769035 | 3.63762 | 0.532249 | 0.000358368 | 6.61812e-06 | 3.17406e-06 | 1(Win) | true |
| simdjson (ondemand) | 5248.75 | 0.0418089 | 1923.16ms | 65103 | 1280 | 31306.7 | 11828.9 | 0.00494658 | 0.965457 | 4.70958 | 0.62418 | 0.000440048 | 5.8201e-06 | 2.73605e-06 | 2(Loss) | true |

----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6917.41 | 0.100358 | 1654.98ms | 65103 | 160 | 12981.8 | 8975.48 | 0.0371985 | 0.73387 | 3.51478 | 0.509808 | 0.000410599 | 3.74407e-06 | 1.34402e-06 | 1(Win) | true |
| simdjson (ondemand) | 5467.4 | 0.111861 | 1891.03ms | 65103 | 30 | 4840.81 | 11355.9 | 0.0111555 | 0.928372 | 4.5883 | 0.601647 | 0.000414727 | 7.68014e-06 | 1.02402e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1338.94 | 0.0260381 | 1585.95ms | 11812 | 4890 | 23466.8 | 8413.22 | 0.0833594 | 3.79484 | 17.7511 | 3.37991 | 0.00470685 | 4.671e-05 | 1.78149e-05 | 1(Win) | true |
| simdjson (ondemand) | 1039.57 | 0.080399 | 1831.63ms | 11812 | 2560 | 194303 | 10836 | 0.202777 | 4.91354 | 18.9355 | 3.55655 | 0.00929566 | 9.79208e-05 | 6.59089e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1460.29 | 0.0319517 | 1568.11ms | 11812 | 4890 | 29707.5 | 7714.1 | 0.280872 | 3.48433 | 16.7567 | 3.15417 | 0.00435152 | 2.57442e-05 | 8.89879e-06 | 1(Win) | true |
| simdjson (ondemand) | 1099.28 | 0.0446195 | 1811.79ms | 11812 | 640 | 13380.2 | 10247.5 | 0.00690768 | 4.61736 | 17.9186 | 3.32746 | 0.00907882 | 2.61916e-05 | 8.33369e-06 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2560.58 | 0.0317967 | 1690.68ms | 25388 | 2560 | 23141.2 | 9455.64 | 0.0779408 | 1.9853 | 9.10836 | 1.63371 | 0.00251828 | 2.06944e-05 | 9.18557e-06 | 1(Win) | true |
| simdjson (ondemand) | 2081.25 | 0.0248557 | 1909.04ms | 25388 | 4890 | 40885.6 | 11633.4 | 0.00413225 | 2.43793 | 9.52194 | 1.68542 | 0.00483558 | 2.43582e-05 | 1.21469e-05 | 2(Loss) | true |

----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2787.56 | 0.0544926 | 1663.27ms | 25388 | 640 | 14337.2 | 8685.7 | 0.0535615 | 1.82453 | 8.65299 | 1.53029 | 0.00208871 | 6.76993e-06 | 9.84717e-07 | 1(Win) | true |
| simdjson (ondemand) | 2191.13 | 0.0777847 | 1897.32ms | 25388 | 320 | 23640.6 | 11050 | 0.0971819 | 2.3093 | 9.04278 | 1.57756 | 0.00454484 | 1.72326e-05 | 9.23172e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 793.929 | 0.168584 | 2154.99ms | 11812 | 160 | 91545.3 | 14188.7 | 0.0402008 | 6.37621 | 29.1791 | 5.686 | 0.011665 | 3.38639e-05 | 5.29123e-06 | 1(Win) | true |
| simdjson (ondemand) | 745.558 | 0.0412254 | 2251.65ms | 11812 | 2560 | 99323.9 | 15109.2 | 0.178487 | 6.81405 | 30.4293 | 5.61607 | 0.0092915 | 4.07425e-05 | 1.83209e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 835.872 | 0.0281792 | 2139.24ms | 11812 | 4890 | 70523.3 | 13476.7 | 0.000403746 | 6.0706 | 28.1535 | 5.45488 | 0.0112193 | 3.47988e-05 | 1.46466e-05 | 1(Win) | true |
| simdjson (ondemand) | 776.31 | 0.0563383 | 2246.37ms | 11812 | 2560 | 171090 | 14510.7 | 0.011593 | 6.53058 | 29.4111 | 5.38698 | 0.00938171 | 5.82035e-05 | 3.17804e-05 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1575.17 | 0.0255947 | 2281.57ms | 25388 | 2560 | 39622.6 | 15371 | 0.0451439 | 3.21745 | 14.5537 | 2.74561 | 0.00517595 | 3.53421e-05 | 1.96943e-05 | 1(Win) | true |
| simdjson (ondemand) | 1539.01 | 0.145146 | 2318.51ms | 25388 | 320 | 166853 | 15732.1 | 0.00260224 | 3.28912 | 14.724 | 2.61348 | 0.00432734 | 9.72408e-06 | 2.83106e-06 | 2(Loss) | true |

----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1652.16 | 0.0445168 | 2258.15ms | 25388 | 4890 | 208117 | 14654.6 | 0.0626749 | 3.06152 | 14.0608 | 2.63471 | 0.00511072 | 2.71291e-05 | 1.51675e-05 | 1(Win) | true |
| simdjson (ondemand) | 1614.86 | 0.0336871 | 2291.88ms | 25388 | 4890 | 124745 | 14993.2 | 0.191198 | 3.13648 | 14.2276 | 2.50217 | 0.00402285 | 2.00488e-05 | 9.98813e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2697.6 | 0.0402506 | 1155.97ms | 11812 | 4890 | 13814.8 | 4175.86 | 0.0589843 | 1.89244 | 9.86573 | 1.83712 | 0.000715608 | 2.69214e-05 | 1.08724e-05 | 1(Win) | true |
| simdjson (ondemand) | 2283.51 | 0.113991 | 1228.05ms | 11812 | 40 | 1264.86 | 4933.1 | 0.0924863 | 2.23433 | 10.2003 | 1.72392 | 0.000783102 | 9.73586e-05 | 5.07958e-05 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2773.51 | 0.113271 | 1152.37ms | 11812 | 40 | 846.61 | 4061.57 | 0.0938529 | 1.84523 | 9.68676 | 1.79512 | 0.00080215 | 5.50288e-05 | 3.17474e-05 | 1(Win) | true |
| simdjson (ondemand) | 2347.02 | 0.0890892 | 1221.69ms | 11812 | 640 | 11701.6 | 4799.63 | 0.0941893 | 2.17328 | 10.0218 | 1.68176 | 0.000868291 | 1.95775e-05 | 5.55579e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4685.96 | 0.0930481 | 1254.87ms | 25388 | 640 | 14793 | 5166.9 | 0.0177846 | 1.08704 | 5.51201 | 0.921853 | 0.000673916 | 2.21561e-05 | 1.18166e-05 | 1(Win) | true |
| simdjson (ondemand) | 4334.66 | 0.0844716 | 1299.7ms | 25388 | 40 | 890.49 | 5585.65 | 0.0134291 | 1.17588 | 5.45155 | 0.83118 | 0.000694226 | 1.28013e-05 | 0 | 2(Loss) | true |

----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4787.34 | 0.0413738 | 1262.22ms | 25388 | 4890 | 21410.5 | 5057.48 | 0.0152786 | 1.0631 | 5.42969 | 0.902316 | 0.000687264 | 1.04714e-05 | 3.71333e-06 | 1(Win) | true |
| simdjson (ondemand) | 4406.34 | 0.0895256 | 1293.85ms | 25388 | 80 | 1935.92 | 5494.79 | 0.0729705 | 1.15678 | 5.36848 | 0.811565 | 0.000630219 | 1.67402e-05 | 5.9083e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2066.98 | 0.0383024 | 1287.17ms | 11812 | 4890 | 21307.6 | 5449.88 | 0.0159148 | 2.45803 | 12.8936 | 2.50288 | 0.00198999 | 1.78841e-05 | 5.21116e-06 | 1(Win) | true |
| simdjson (ondemand) | 2003.23 | 0.0474326 | 1303.9ms | 11812 | 160 | 1138.31 | 5623.32 | 0.0186687 | 2.54331 | 12.4077 | 2.09465 | 0.0011011 | 1.69319e-05 | 1.58737e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2113.67 | 0.140251 | 1288.73ms | 11812 | 30 | 1676.12 | 5329.5 | 0.0281373 | 2.4109 | 12.714 | 2.46089 | 0.00226324 | 7.05497e-05 | 8.46597e-06 | 1(Win) | true |
| simdjson (ondemand) | 2048.55 | 0.117377 | 1297.65ms | 11812 | 160 | 6665.64 | 5498.91 | 0.202038 | 2.48387 | 12.2331 | 2.05249 | 0.000952421 | 1.74611e-05 | 4.23298e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3820.91 | 0.034181 | 1373.53ms | 25388 | 4890 | 22940.5 | 6336.69 | 0.0247601 | 1.33157 | 6.47857 | 1.00366 | 0.000729754 | 2.00327e-05 | 9.88342e-06 | 1(Win) | true |
| jsonifier (generic) | 3795.46 | 0.0500996 | 1378.67ms | 25388 | 1280 | 13073.9 | 6379.16 | 0.00971274 | 1.34198 | 6.82657 | 1.23365 | 0.00108125 | 1.30475e-05 | 4.58509e-06 | 2(Loss) | true |

----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3890.96 | 0.0777497 | 1373.83ms | 25388 | 320 | 7490.16 | 6222.6 | 0.0546192 | 1.30822 | 6.39731 | 0.984048 | 0.000785189 | 2.09252e-05 | 1.3786e-05 | 1(Win) | true |
| jsonifier (generic) | 3842.08 | 0.135454 | 1382.4ms | 25388 | 30 | 2185.91 | 6301.77 | 0.00105792 | 1.32509 | 6.74303 | 1.21412 | 0.00130508 | 2.36332e-05 | 1.83814e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1599.28 | 0.133329 | 7224.97ms | 108313 | 80 | 593268 | 64588.4 | 0.00263198 | 3.15916 | 13.977 | 2.96027 | 0.00372474 | 2.05423e-05 | 1.54644e-05 | 1(Win) | true |
| simdjson (ondemand) | 1404.16 | 0.12448 | 4122.87ms | 108313 | 160 | 1.34167e+06 | 73563.8 | 0.0420207 | 3.60055 | 14.6811 | 2.51529 | 0.00611497 | 4.37967e-05 | 3.31793e-05 | 2(Loss) | true |

----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1724.33 | 0.0268966 | 6919.04ms | 108313 | 4890 | 1.26947e+06 | 59904.5 | 0.0887058 | 2.92931 | 13.3239 | 2.82264 | 0.00340619 | 1.60219e-05 | 1.13773e-05 | 1(Win) | true |
| simdjson (ondemand) | 1508.25 | 0.0257154 | 7788.92ms | 108313 | 4890 | 1.51672e+06 | 68486.7 | 0.0664263 | 3.34804 | 14.0341 | 2.37803 | 0.0056532 | 2.26055e-05 | 1.65505e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2489.14 | 0.038962 | 7790.78ms | 183677 | 4890 | 3.67622e+06 | 70372.9 | 0.0469756 | 2.02972 | 8.90415 | 1.7935 | 0.00220414 | 1.51929e-05 | 1.01861e-05 | 1(Win) | true |
| simdjson (ondemand) | 2278.32 | 0.0485156 | 4307.74ms | 183677 | 1280 | 1.78096e+06 | 76884.9 | 0.0913603 | 2.21353 | 9.24789 | 1.50725 | 0.00376875 | 2.48951e-05 | 1.88936e-05 | 2(Loss) | true |

----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2638.38 | 0.0517067 | 7557.47ms | 183677 | 640 | 754235 | 66392.1 | 0.244483 | 1.9142 | 8.53053 | 1.71482 | 0.00198427 | 4.63109e-05 | 4.05008e-05 | 1(Win) | true |
| simdjson (ondemand) | 2397.56 | 0.0452565 | 4195.31ms | 183677 | 1280 | 1.3994e+06 | 73060.8 | 0.0465416 | 2.10378 | 8.87143 | 1.42741 | 0.00371242 | 2.25089e-05 | 1.1599e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 577.47 | 0.0445172 | 4751.13ms | 108313 | 320 | 2.02912e+06 | 178876 | 0.0440755 | 8.75434 | 38.1182 | 7.04799 | 0.0115715 | 3.12174e-05 | 2.10616e-05 | 1(Win) | true |
| simdjson (ondemand) | 262.808 | 0.162142 | 5129.8ms | 108313 | 640 | 2.59931e+08 | 393045 | 0.322241 | 19.2722 | 85.5559 | 16.2241 | 0.0832789 | 0.000214584 | 0.000128418 | 2(Loss) | true |

----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 596.428 | 0.0700003 | 4686.95ms | 108313 | 160 | 2.35161e+06 | 173190 | 0.16071 | 8.44847 | 37.4732 | 6.91408 | 0.010938 | 1.93306e-05 | 9.52102e-06 | 1(Win) | true |
| simdjson (ondemand) | 265.248 | 0.169294 | 5097.27ms | 108313 | 320 | 1.39088e+08 | 389429 | 0.031031 | 18.9211 | 84.9142 | 16.0899 | 0.0807391 | 8.28329e-05 | 4.91919e-05 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 939.193 | 0.062796 | 5039.84ms | 183677 | 320 | 4.3895e+06 | 186509 | 0.437388 | 5.41026 | 23.4701 | 4.38776 | 0.005995 | 5.67232e-05 | 3.73958e-05 | 1(Win) | true |
| simdjson (ondemand) | 466.745 | 0.0546248 | 4869.91ms | 183677 | 640 | 2.68974e+07 | 375297 | 0.0646902 | 10.8369 | 50.3117 | 9.4339 | 0.0364775 | 0.00015097 | 0.00012231 | 2(Loss) | true |

----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 959.604 | 0.0721294 | 4905.36ms | 183677 | 160 | 2.77377e+06 | 182542 | 0.105433 | 5.28207 | 23.0912 | 4.30915 | 0.00560335 | 1.32366e-05 | 8.98316e-06 | 1(Win) | true |
| simdjson (ondemand) | 474.222 | 0.17715 | 4816.69ms | 183677 | 30 | 1.28455e+07 | 369380 | 0.0999685 | 10.6564 | 49.9371 | 9.35562 | 0.0354134 | 2.52254e-05 | 1.43368e-05 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4873.8 | 0.0283817 | 2869.76ms | 108313 | 4890 | 176934 | 21194 | 0.0398674 | 1.04159 | 5.42234 | 0.894463 | 0.00117008 | 5.65467e-06 | 3.40413e-06 | 1(Win) | true |
| simdjson (ondemand) | 4477 | 0.0476342 | 3048.33ms | 108313 | 1280 | 154609 | 23072.4 | 0.102243 | 1.12836 | 5.70619 | 0.691792 | 0.000956502 | 6.59258e-06 | 3.36842e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5044.94 | 0.0389692 | 2807.33ms | 108313 | 2560 | 162979 | 20475 | 0.0478708 | 1.00881 | 5.28576 | 0.864569 | 0.00111747 | 5.83162e-06 | 3.84447e-06 | 1(Win) | true |
| simdjson (ondemand) | 4610.82 | 0.0270629 | 2995.05ms | 108313 | 2560 | 94100.8 | 22402.8 | 0.0755568 | 1.09844 | 5.57125 | 0.661731 | 0.000933482 | 3.9743e-06 | 1.13242e-06 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6998.53 | 0.0469317 | 3245.33ms | 183677 | 1280 | 176619 | 25029.3 | 0.010929 | 0.722278 | 3.74241 | 0.55069 | 0.000389198 | 2.05013e-06 | 4.33846e-07 | 1(Win) | true |
| simdjson (ondemand) | 6490.31 | 0.0877291 | 3426.59ms | 183677 | 320 | 179397 | 26989.2 | 0.0138694 | 0.776518 | 3.94242 | 0.429586 | 0.000618579 | 1.3781e-06 | 3.06244e-07 | 2(Loss) | true |

----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7178.79 | 0.0323845 | 3197.64ms | 183677 | 1280 | 79926.5 | 24400.8 | 0.0127061 | 0.70489 | 3.66186 | 0.533061 | 0.000366689 | 2.23728e-06 | 9.48506e-07 | 1(Win) | true |
| simdjson (ondemand) | 6715.53 | 0.0244159 | 3360.48ms | 183677 | 1280 | 51916.4 | 26084 | 0.113572 | 0.753098 | 3.86285 | 0.411859 | 0.000490931 | 3.12199e-06 | 2.05013e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3391.28 | 0.0304623 | 3783.28ms | 108313 | 1280 | 110197 | 30459.1 | 0.050611 | 1.49188 | 7.57029 | 1.36647 | 0.00131027 | 7.19125e-06 | 4.38544e-06 | 1(Win) | true |
| simdjson (ondemand) | 2867.12 | 0.0214692 | 4341.2ms | 108313 | 4890 | 292558 | 36027.6 | 0.0175012 | 1.7633 | 9.45954 | 1.33339 | 0.00123828 | 1.58123e-05 | 1.22345e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3489.26 | 0.0865138 | 3701.91ms | 108313 | 160 | 104951 | 29603.8 | 0.0196937 | 1.44943 | 7.43375 | 1.33655 | 0.00113433 | 2.01961e-06 | 4.61625e-07 | 1(Win) | true |
| simdjson (ondemand) | 2932.14 | 0.0312732 | 4282.59ms | 108313 | 1280 | 155363 | 35228.7 | 0.164983 | 1.72612 | 9.32412 | 1.30299 | 0.00116942 | 1.14757e-05 | 9.13873e-06 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5021.85 | 0.068685 | 4223.58ms | 183677 | 320 | 183677 | 34881.2 | 0.062528 | 1.0086 | 5.0317 | 0.841396 | 0.000798991 | 3.03692e-05 | 2.77151e-05 | 1(Win) | true |
| simdjson (ondemand) | 4377.41 | 0.0220929 | 4750.03ms | 183677 | 2560 | 200087 | 40016.3 | 0.0273996 | 1.15644 | 6.14281 | 0.805049 | 0.000775806 | 1.79217e-05 | 1.53824e-05 | 2(Loss) | true |

----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5167.47 | 0.0940368 | 4152.08ms | 183677 | 320 | 325162 | 33898.2 | 0.226195 | 0.983206 | 4.95076 | 0.823571 | 0.0007283 | 1.56525e-06 | 3.91312e-07 | 1(Win) | true |
| simdjson (ondemand) | 4459.89 | 0.136738 | 4679.44ms | 183677 | 30 | 86528.3 | 39276.3 | 0.0236728 | 1.13406 | 6.06295 | 0.787126 | 0.000770011 | 7.25912e-06 | 5.62582e-06 | 2(Loss) | true |

----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 592.243 | 0.117347 | 4453.35ms | 1834197 | 40 | 4.80504e+08 | 2.95356e+06 | 0.0728482 | 8.43088 | 34.6943 | 7.51343 | 0.0463237 | 0.139362 | 0.000198029 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 586.301 | 0.4928 | 4512.94ms | 1834197 | 80 | 1.72935e+10 | 2.9835e+06 | 0.547501 | 8.60207 | 35.2571 | 6.33076 | 0.0424974 | 0.139304 | 0.000577848 | 1(Tie) | true |

----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 644.942 | 0.18794 | 4492.71ms | 1834197 | 30 | 7.79492e+08 | 2.71222e+06 | 0.703671 | 7.81602 | 31.7067 | 6.81916 | 0.0451356 | 0.118203 | 0.000165776 | 1(Win) | true |
| simdjson (ondemand) | 640.97 | 0.0951585 | 4473.13ms | 1834197 | 80 | 5.39513e+08 | 2.72903e+06 | 0.00284296 | 7.8633 | 32.2735 | 5.63752 | 0.0415115 | 0.11867 | 0.00051971 | 2(Loss) | true |

----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2135.15 | 0.501181 | 4916.82ms | 7351818 | 80 | 2.16676e+10 | 3.28372e+06 | 1.09238 | 2.35272 | 9.8138 | 1.61785 | 0.010407 | 0.0589467 | 0.000629183 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2104.84 | 0.528537 | 5003.16ms | 7351818 | 80 | 2.47966e+10 | 3.33101e+06 | 0.0902132 | 2.38258 | 9.48528 | 1.91207 | 0.0139164 | 0.0590821 | 0.00048165 | 1(Tie) | true |

----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 2299.22 | 0.824629 | 4969.6ms | 7351818 | 30 | 1.897e+10 | 3.0494e+06 | 0.524084 | 2.19196 | 9.06937 | 1.44486 | 0.0101764 | 0.0537185 | 0.000328304 | 1(Tie) | true |
| jsonifier (generic) STATISTICAL TIE | 2291.79 | 0.125358 | 4976.57ms | 7351818 | 80 | 1.17661e+09 | 3.05928e+06 | 0.430894 | 2.19761 | 8.74045 | 1.73897 | 0.0136281 | 0.0537877 | 0.000524457 | 1(Tie) | true |

----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 372.299 | 0.0654418 | 7128.88ms | 1834197 | 30 | 2.83623e+08 | 4.69845e+06 | 0.17232 | 13.4863 | 57.2262 | 11.5271 | 0.0562451 | 0.344616 | 0.000235707 | 1(Win) | true |
| simdjson (ondemand) | 253.021 | 0.14134 | 4913.6ms | 1834197 | 30 | 2.86438e+09 | 6.91337e+06 | 0.769618 | 19.9203 | 92.7243 | 15.9629 | 0.0556211 | 0.79086 | 0.000602825 | 2(Loss) | true |

----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 389.697 | 0.0707435 | 7115.93ms | 1834197 | 80 | 8.06681e+08 | 4.48869e+06 | 0.018013 | 12.8568 | 54.2427 | 10.834 | 0.0549942 | 0.323139 | 0.000360246 | 1(Win) | true |
| simdjson (ondemand) | 258.986 | 0.555161 | 4896.34ms | 1834197 | 40 | 5.62388e+10 | 6.75413e+06 | 0.0240369 | 19.4681 | 89.7426 | 15.2703 | 0.0543038 | 0.769353 | 0.000645787 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1248.42 | 0.808406 | 8436.07ms | 7351818 | 30 | 6.18375e+10 | 5.61611e+06 | 0.257364 | 4.02533 | 15.0847 | 2.92071 | 0.0164696 | 0.187082 | 0.0016812 | 1(Win) | true |
| simdjson (ondemand) | 819.864 | 0.167089 | 6024.15ms | 7351818 | 30 | 6.12526e+09 | 8.55171e+06 | 1.18104 | 6.16172 | 24.1511 | 4.02095 | 0.0138081 | 0.4373 | 0.00261831 | 2(Loss) | true |

----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1303.89 | 0.840013 | 8416.9ms | 7351818 | 30 | 6.1207e+10 | 5.37717e+06 | 0.574157 | 3.85982 | 14.3407 | 2.74787 | 0.0161675 | 0.181703 | 0.00124254 | 1(Win) | true |
| simdjson (ondemand) | 841.831 | 0.12876 | 6016.71ms | 7351818 | 40 | 4.60003e+09 | 8.32856e+06 | 0.267095 | 5.985 | 23.4071 | 3.8481 | 0.0135266 | 0.431951 | 0.0014229 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4300.39 | 0.127622 | 5302.6ms | 1834197 | 640 | 1.72468e+08 | 406760 | 0.225695 | 1.17408 | 6.00319 | 0.611593 | 0.00327029 | 0.0750721 | 1.14568e-05 | 1(Win) | true |
| jsonifier (generic) | 4064.96 | 0.26397 | 5604.5ms | 1834197 | 160 | 2.06446e+08 | 430318 | 0.44913 | 1.24392 | 5.16791 | 0.778454 | 0.00840881 | 0.0756318 | 2.01042e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4311.13 | 0.0616799 | 5299.77ms | 1834197 | 160 | 1.00211e+07 | 405746 | 0.153768 | 1.17077 | 6.00298 | 0.611544 | 0.00328023 | 0.0750452 | 7.08757e-06 | 1(Win) | true |
| jsonifier (generic) | 4117.77 | 0.105241 | 5642.05ms | 1834197 | 30 | 5.99596e+06 | 424799 | 0.0685266 | 1.2244 | 5.1677 | 0.778405 | 0.00774966 | 0.0756071 | 1.76281e-06 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9210.77 | 0.144771 | 4902.77ms | 7351818 | 320 | 3.88605e+08 | 761200 | 0.284574 | 0.550459 | 2.51553 | 0.191069 | 0.00100793 | 0.0424156 | 5.17814e-06 | 1(Win) | true |
| jsonifier (generic) | 8500.14 | 0.878147 | 5341.73ms | 7351818 | 40 | 2.09861e+09 | 824839 | 0.35217 | 0.599531 | 2.04338 | 0.219135 | 0.00461229 | 0.0423918 | 8.5013e-07 | 2(Loss) | true |

----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9178 | 0.177891 | 4889.22ms | 7351818 | 160 | 2.95475e+08 | 763918 | 0.178753 | 0.551745 | 2.51548 | 0.191056 | 0.00105442 | 0.0424068 | 2.19844e-06 | 1(Win) | true |
| jsonifier (generic) | 8459.59 | 0.244493 | 5315.56ms | 7351818 | 40 | 1.64242e+08 | 828792 | 0.11405 | 0.595437 | 2.04333 | 0.219123 | 0.00464071 | 0.0423907 | 2.81563e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2940.84 | 0.153952 | 7642.3ms | 1834197 | 640 | 5.36659e+08 | 594804 | 0.404878 | 1.71094 | 7.40337 | 1.173 | 0.00855254 | 0.113319 | 3.85983e-06 | 1(Win) | true |
| simdjson (ondemand) | 2406.58 | 0.126206 | 4636.43ms | 1834197 | 320 | 2.69277e+08 | 726850 | 0.219481 | 2.10706 | 11.5688 | 1.44429 | 0.00317101 | 0.150729 | 6.56793e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2963.18 | 0.151364 | 7737.03ms | 1834197 | 80 | 6.38716e+07 | 590320 | 0.0227494 | 1.6983 | 7.40316 | 1.17295 | 0.00839226 | 0.113275 | 3.79594e-06 | 1(Win) | true |
| simdjson (ondemand) | 2368.95 | 0.613381 | 4706.66ms | 1834197 | 320 | 6.56436e+09 | 738399 | 0.0781634 | 2.13566 | 11.5686 | 1.44424 | 0.00340526 | 0.150654 | 3.85046e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6595.42 | 0.149803 | 6865.7ms | 7351818 | 320 | 8.11517e+08 | 1.06305e+06 | 0.954999 | 0.760855 | 2.6011 | 0.317572 | 0.0045856 | 0.0634817 | 6.51497e-06 | 1(Win) | true |
| simdjson (ondemand) | 5613.09 | 0.517045 | 7956.23ms | 7351818 | 320 | 1.33473e+10 | 1.24909e+06 | 0.125916 | 0.900757 | 3.90409 | 0.398817 | 0.00109354 | 0.0848047 | 6.90348e-06 | 2(Loss) | true |

----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6599.63 | 0.215462 | 6794.63ms | 7351818 | 160 | 8.38323e+08 | 1.06237e+06 | 0.0495216 | 0.759156 | 2.60105 | 0.31756 | 0.00454669 | 0.0634955 | 5.08293e-06 | 1(Win) | true |
| simdjson (ondemand) | 5582.89 | 1.1287 | 7991.24ms | 7351818 | 80 | 1.60738e+10 | 1.25584e+06 | 0.144079 | 0.903869 | 3.90404 | 0.398805 | 0.0010296 | 0.0847864 | 6.82144e-06 | 2(Loss) | true |

----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1310.54 | 0.156957 | 7941.92ms | 409725 | 80 | 1.75201e+07 | 298155 | 0.185006 | 3.85023 | 18.132 | 3.57372 | 0.00904509 | 0.0279399 | 2.69083e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.067 | 0.177619 | 5387.06ms | 409725 | 30 | 1.61451e+07 | 413020 | 0.0405224 | 5.33998 | 19.6125 | 3.78811 | 0.0166138 | 0.0400665 | 6.25623e-05 | 2(Loss) | true |

----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1656.56 | 0.0831143 | 7355.92ms | 409725 | 640 | 2.45981e+07 | 235877 | 0.403709 | 3.03736 | 15.242 | 2.959 | 0.00626273 | 0.00781843 | 1.44914e-05 | 1(Win) | true |
| simdjson (ondemand) | 1124.34 | 0.0430491 | 5082.08ms | 409725 | 640 | 1.4325e+07 | 347531 | 0.124596 | 4.48579 | 16.7307 | 3.17519 | 0.0124212 | 0.0161825 | 4.35734e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1898.87 | 0.404233 | 4408.75ms | 676745 | 40 | 7.55067e+07 | 339884 | 0.0750918 | 2.6263 | 11.5231 | 2.1775 | 0.00740253 | 0.0347494 | 3.01812e-05 | 1(Win) | true |
| simdjson (ondemand) | 1484.25 | 0.358889 | 5682.79ms | 676745 | 640 | 1.5586e+09 | 434828 | 0.273863 | 3.40113 | 12.4549 | 2.31904 | 0.0108797 | 0.0439727 | 2.75399e-05 | 2(Loss) | true |

----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2374.93 | 0.276459 | 4159.5ms | 676745 | 80 | 4.51544e+07 | 271753 | 0.0871356 | 2.10367 | 9.77066 | 1.80453 | 0.00451562 | 0.0154836 | 8.45961e-06 | 1(Win) | true |
| simdjson (ondemand) | 1754.02 | 0.22042 | 5403.2ms | 676745 | 80 | 5.26224e+07 | 367951 | 0.0344594 | 2.87979 | 10.7088 | 1.9477 | 0.00880127 | 0.0247331 | 2.23681e-05 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 834.726 | 0.335259 | 6078.04ms | 409725 | 40 | 9.85188e+07 | 468111 | 0.331797 | 6.01884 | 28.4619 | 5.5948 | 0.0103682 | 0.026944 | 0.000279456 | 1(Win) | true |
| simdjson (ondemand) | 504.23 | 0.092668 | 4966.79ms | 409725 | 40 | 2.06275e+07 | 774932 | 0.050957 | 10.0182 | 45.9919 | 8.82624 | 0.0220113 | 0.0516131 | 0.00011465 | 2(Loss) | true |

----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 959.169 | 0.0981411 | 5869ms | 409725 | 640 | 1.023e+08 | 407378 | 0.233546 | 5.23775 | 25.5819 | 4.98117 | 0.00742648 | 0.0107217 | 5.25467e-05 | 1(Win) | true |
| simdjson (ondemand) | 550.495 | 0.167223 | 4871.54ms | 409725 | 30 | 4.2266e+07 | 709805 | 0.408705 | 9.22032 | 43.1204 | 8.21268 | 0.018403 | 0.023494 | 1.65151e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1272.31 | 0.143242 | 6660.42ms | 676745 | 40 | 2.11186e+07 | 507261 | 0.0561673 | 3.96966 | 18.0477 | 3.54231 | 0.00799016 | 0.0355314 | 2.23496e-05 | 1(Win) | true |
| simdjson (ondemand) | 807.54 | 0.0767628 | 5160.9ms | 676745 | 30 | 1.12913e+07 | 799210 | 0.453809 | 6.24708 | 28.2863 | 5.33699 | 0.0147421 | 0.05266 | 1.95051e-05 | 2(Loss) | true |

----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1454.22 | 0.470881 | 6385.21ms | 676745 | 80 | 3.49383e+08 | 443807 | 0.0619797 | 3.4678 | 16.3059 | 3.17135 | 0.00492192 | 0.0161775 | 1.22646e-05 | 1(Win) | true |
| simdjson (ondemand) | 877.857 | 0.0491227 | 5009.5ms | 676745 | 320 | 4.17366e+07 | 735193 | 0.0551413 | 5.74013 | 26.5499 | 4.96613 | 0.012542 | 0.0266958 | 2.37719e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2436.02 | 0.0317264 | 4278.49ms | 409725 | 1280 | 3.31492e+06 | 160402 | 0.0258377 | 2.06799 | 10.0949 | 1.87209 | 0.00525909 | 1.83774e-05 | 1.18753e-05 | 1(Win) | true |
| simdjson (ondemand) | 2070.7 | 0.0696633 | 4987.43ms | 409725 | 80 | 1.38245e+06 | 188702 | 0.0970327 | 2.43696 | 10.3899 | 1.79244 | 0.00649295 | 0.000134725 | 1.51321e-05 | 2(Loss) | true |

----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2798.91 | 0.0395191 | 4194.47ms | 409725 | 1280 | 3.89611e+06 | 139606 | 0.0174758 | 1.80036 | 9.07423 | 1.64817 | 0.00427253 | 9.17918e-06 | 5.71077e-06 | 1(Win) | true |
| simdjson (ondemand) | 2320.91 | 0.0807634 | 4930.69ms | 409725 | 30 | 554648 | 168358 | 0.0899886 | 2.17754 | 9.37825 | 1.56799 | 0.00537426 | 2.00134e-05 | 1.34236e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3372.87 | 0.212535 | 5140.62ms | 676745 | 40 | 6.61563e+06 | 191349 | 0.100978 | 1.49715 | 6.71583 | 1.16616 | 0.00629994 | 0.0029199 | 5.689e-06 | 1(Win) | true |
| simdjson (ondemand) | 3112.66 | 0.0861214 | 5482.2ms | 676745 | 30 | 956602 | 207345 | 0.160602 | 1.62264 | 6.86337 | 1.10735 | 0.00446682 | 0.00407839 | 1.6402e-05 | 2(Loss) | true |

----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3847.03 | 0.191755 | 4987.36ms | 676745 | 1280 | 1.32466e+08 | 167764 | 0.341027 | 1.30632 | 6.09894 | 1.03082 | 0.00435048 | 0.00172173 | 6.41397e-06 | 1(Win) | true |
| simdjson (ondemand) | 3473.18 | 0.205237 | 5419.21ms | 676745 | 1280 | 1.86173e+08 | 185822 | 0.174752 | 1.45451 | 6.25095 | 0.971487 | 0.0036908 | 0.00261069 | 2.34925e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1998.33 | 0.0689085 | 5167.03ms | 409725 | 80 | 1.4524e+06 | 195535 | 0.0705037 | 2.52777 | 12.7561 | 2.39941 | 0.00593685 | 9.06096e-06 | 2.47117e-06 | 1(Win) | true |
| simdjson (ondemand) | 1646.48 | 0.117636 | 6255.68ms | 409725 | 320 | 2.49405e+07 | 237322 | 0.138264 | 3.06632 | 14.0585 | 2.44962 | 0.00666057 | 0.000605421 | 8.25249e-06 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2240.22 | 0.0167165 | 5064.07ms | 409725 | 1280 | 1.08818e+06 | 174422 | 0.123872 | 2.25551 | 11.7267 | 2.17192 | 0.00461808 | 1.03347e-05 | 7.85969e-06 | 1(Win) | true |
| simdjson (ondemand) | 1805.74 | 0.0578191 | 6175.5ms | 409725 | 1280 | 2.00369e+07 | 216391 | 0.102011 | 2.80179 | 13.0277 | 2.21997 | 0.00528061 | 0.000507995 | 1.84213e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2716.47 | 0.148654 | 6289.88ms | 676745 | 320 | 3.99157e+07 | 237586 | 0.0954989 | 1.86137 | 8.31695 | 1.50031 | 0.00650016 | 0.000598716 | 9.24462e-06 | 1(Win) | true |
| simdjson (ondemand) | 2536.24 | 0.147886 | 6779.6ms | 676745 | 40 | 5.66476e+06 | 254469 | 0.10345 | 1.99192 | 9.08768 | 1.50665 | 0.00470716 | 0.0033568 | 6.77508e-05 | 2(Loss) | true |

----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3046.69 | 0.0596769 | 6115.65ms | 676745 | 640 | 1.02279e+07 | 211835 | 0.0467997 | 1.65296 | 7.69031 | 1.36191 | 0.00433725 | 0.000245894 | 7.29364e-06 | 1(Win) | true |
| simdjson (ondemand) | 2779.09 | 0.0817944 | 6608.86ms | 676745 | 160 | 5.77313e+06 | 232232 | 0.0521996 | 1.81506 | 8.46322 | 1.36762 | 0.00371527 | 0.00264045 | 4.91322e-06 | 2(Loss) | true |

----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1759.75 | 0.162907 | 7363.64ms | 264040 | 320 | 1.73887e+07 | 143093 | 0.0187129 | 2.85954 | 10.0154 | 1.91154 | 0.0130746 | 0.000133147 | 4.34238e-05 | 1(Win) | true |
| simdjson (ondemand) | 1683.35 | 0.0519083 | 4025.35ms | 264040 | 1280 | 7.71748e+06 | 149588 | 0.10034 | 2.99572 | 10.1865 | 1.78793 | 0.00910468 | 0.000690281 | 2.97777e-05 | 2(Loss) | true |

----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2147.42 | 0.0834756 | 7167.02ms | 264040 | 1280 | 1.22641e+07 | 117261 | 0.0967458 | 2.33705 | 8.68581 | 1.62359 | 0.0100888 | 2.02355e-05 | 1.22407e-05 | 1(Win) | true |
| simdjson (ondemand) | 1972.47 | 0.0651749 | 7689.51ms | 264040 | 640 | 4.43057e+06 | 127661 | 0.429783 | 2.56229 | 8.86268 | 1.50286 | 0.0081907 | 0.000128514 | 7.37933e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2265.91 | 0.173026 | 4185.28ms | 360584 | 320 | 2.20649e+07 | 151762 | 0.62427 | 2.2235 | 7.75588 | 1.41327 | 0.0105223 | 0.000215631 | 2.79495e-05 | 1(Win) | true |
| simdjson (ondemand) | 2148.59 | 0.187668 | 4356.39ms | 360584 | 40 | 3.60867e+06 | 160049 | 0.0445291 | 2.31463 | 7.85184 | 1.32638 | 0.00772954 | 0.000384862 | 9.01316e-06 | 2(Loss) | true |

----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2625.27 | 0.321015 | 7997.02ms | 360584 | 80 | 1.41451e+07 | 130988 | 0.233406 | 1.92262 | 6.78225 | 1.20266 | 0.0108042 | 7.11346e-05 | 3.29327e-05 | 1(Win) | true |
| simdjson (ondemand) | 2442.04 | 0.161055 | 4227.18ms | 360584 | 160 | 8.22952e+06 | 140816 | 0.0662126 | 2.06313 | 6.88138 | 1.11762 | 0.00904652 | 3.22047e-05 | 7.24519e-06 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 588.386 | 0.0871132 | 5576.92ms | 264040 | 640 | 8.89534e+07 | 427964 | 0.0520341 | 8.60327 | 28.3915 | 4.89211 | 0.0487933 | 0.000404881 | 0.000180956 | 1(Win) | true |
| simdjson (ondemand) | 264.33 | 0.224621 | 6115.98ms | 264040 | 80 | 3.66298e+08 | 952626 | 0.338583 | 19.0522 | 62.7237 | 12.1283 | 0.160882 | 0.00245536 | 0.0010354 | 2(Loss) | true |

----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 630.792 | 0.160033 | 5361.3ms | 264040 | 160 | 6.5299e+07 | 399194 | 0.039087 | 8.02025 | 27.0621 | 4.6054 | 0.0435679 | 0.000233464 | 0.00017592 | 1(Win) | true |
| simdjson (ondemand) | 272.488 | 0.115331 | 6000.33ms | 264040 | 320 | 3.63486e+08 | 924106 | 0.053309 | 18.4806 | 61.4027 | 11.8454 | 0.156447 | 0.000742442 | 0.000365534 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 727.609 | 0.268704 | 6115.48ms | 360584 | 80 | 1.29019e+08 | 472616 | 0.0529383 | 6.95235 | 21.4854 | 3.71623 | 0.0428623 | 0.00099481 | 0.000102542 | 1(Win) | true |
| simdjson (ondemand) | 381.515 | 0.125864 | 5747.39ms | 360584 | 160 | 2.05926e+08 | 901354 | 0.145875 | 13.1863 | 45.761 | 8.7777 | 0.0977831 | 0.00135636 | 0.000119962 | 2(Loss) | true |

----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 777.737 | 0.0960977 | 5952.35ms | 360584 | 640 | 1.15546e+08 | 442154 | 0.0661813 | 6.51629 | 20.5113 | 3.50616 | 0.0387886 | 0.000228332 | 0.000112807 | 1(Win) | true |
| simdjson (ondemand) | 394.389 | 0.144113 | 5667.1ms | 360584 | 160 | 2.52632e+08 | 871929 | 0.0997427 | 12.7324 | 44.7913 | 8.5703 | 0.0925811 | 0.000373387 | 0.000136272 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7476.13 | 0.0407692 | 4110.62ms | 264040 | 4890 | 922061 | 33681.6 | 0.134986 | 0.673905 | 3.3959 | 0.485067 | 0.000384023 | 7.6722e-06 | 5.13958e-06 | 1(Win) | true |
| simdjson (ondemand) | 6563.06 | 0.10687 | 4602.44ms | 264040 | 80 | 134501 | 38367.5 | 0.0023131 | 0.772041 | 3.81582 | 0.376009 | 0.000343177 | 9.46826e-07 | 2.36707e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7757.74 | 0.0345687 | 4056.74ms | 264040 | 2560 | 322311 | 32459 | 0.0277377 | 0.651479 | 3.31838 | 0.469274 | 0.000348164 | 9.56886e-06 | 7.44146e-06 | 1(Win) | true |
| simdjson (ondemand) | 6762.6 | 0.075383 | 4543.7ms | 264040 | 80 | 63030.3 | 37235.4 | 0.0771854 | 0.747762 | 3.73873 | 0.360406 | 0.000316382 | 3.73996e-06 | 2.46175e-06 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8580.22 | 0.05634 | 4790.01ms | 360584 | 640 | 326309 | 40078.2 | 0.293766 | 0.590535 | 2.90635 | 0.372069 | 0.000359486 | 2.74295e-06 | 1.4993e-06 | 1(Win) | true |
| simdjson (ondemand) | 7692.91 | 0.0467088 | 5226.93ms | 360584 | 320 | 139501 | 44700.8 | 0.0175861 | 0.655886 | 3.18364 | 0.292053 | 0.000216125 | 2.07996e-06 | 9.35982e-07 | 2(Loss) | true |

----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8792.5 | 0.0245179 | 4744.49ms | 360584 | 4890 | 449641 | 39110.6 | 0.0922431 | 0.574382 | 2.84935 | 0.360504 | 0.000364298 | 5.73711e-06 | 4.56712e-06 | 1(Win) | true |
| simdjson (ondemand) | 7900.79 | 0.10065 | 5222.3ms | 360584 | 40 | 76764.1 | 43524.8 | 0.274985 | 0.639873 | 3.12719 | 0.280627 | 0.000229974 | 7.48785e-06 | 7.00253e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5062.39 | 0.0902772 | 5746.04ms | 264040 | 40 | 80657.5 | 49741 | 0.0778804 | 0.998492 | 4.85974 | 0.762423 | 0.00118694 | 1.52439e-05 | 8.61612e-06 | 1(Win) | true |
| simdjson (ondemand) | 4415.98 | 0.0148038 | 6460.16ms | 264040 | 4890 | 348450 | 57022 | 0.0220923 | 1.14433 | 5.85261 | 0.739375 | 0.000627185 | 8.33207e-06 | 5.62055e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5187.32 | 0.0602857 | 5660.04ms | 264040 | 1280 | 1.0962e+06 | 48543 | 0.0190613 | 0.974698 | 4.78134 | 0.746629 | 0.00119907 | 6.07744e-06 | 4.34652e-06 | 1(Win) | true |
| simdjson (ondemand) | 4497.82 | 0.0560526 | 6415.05ms | 264040 | 2560 | 2.52097e+06 | 55984.6 | 0.00889345 | 1.1218 | 5.77509 | 0.723771 | 0.000626845 | 5.56704e-06 | 3.50622e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5942.97 | 0.0299432 | 6538.03ms | 360584 | 2560 | 768498 | 57863.3 | 0.151642 | 0.847245 | 3.9972 | 0.583207 | 0.000571827 | 5.36673e-06 | 3.58035e-06 | 1(Win) | true |
| simdjson (ondemand) | 5401.62 | 0.0218601 | 7126.05ms | 360584 | 4890 | 947064 | 63662.3 | 0.304987 | 0.932247 | 4.68587 | 0.560307 | 0.000483308 | 5.82559e-06 | 3.89734e-06 | 2(Loss) | true |

----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6064.99 | 0.0507112 | 6494.03ms | 360584 | 1280 | 1.05821e+06 | 56699.1 | 0.0375077 | 0.829259 | 3.93942 | 0.571542 | 0.000543452 | 3.24127e-06 | 1.98896e-06 | 1(Win) | true |
| simdjson (ondemand) | 5524.54 | 0.0408777 | 7061.4ms | 360584 | 320 | 207178 | 62245.8 | 0.0412698 | 0.914232 | 4.62914 | 0.548881 | 0.000462644 | 2.56528e-06 | 1.4993e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1877.24 | 0.0500967 | 870.828ms | 2632 | 4890 | 2194.12 | 1337.11 | 0.146867 | 2.77826 | 10.9491 | 2.06269 | 0.000401073 | 5.94383e-05 | 1.46848e-05 | 1(Win) | true |
| simdjson (ondemand) | 1526.73 | 0.0876243 | 900.966ms | 2632 | 1280 | 2656.47 | 1644.08 | 0.0647264 | 3.39321 | 11.2948 | 2.14172 | 0.00196767 | 5.72877e-05 | 2.22621e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2393.22 | 0.127781 | 851.523ms | 2632 | 80 | 143.691 | 1048.83 | 0.0928748 | 2.19361 | 9.03305 | 1.65502 | 0.000379939 | 3.79939e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1782.54 | 0.0485057 | 887.188ms | 2632 | 4890 | 2281.32 | 1408.14 | 0.230482 | 2.9224 | 9.54445 | 1.76558 | 0.00316546 | 3.20112e-05 | 5.20571e-06 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2296.19 | 0.051325 | 878.341ms | 3370 | 2560 | 1321.12 | 1399.66 | 0.06996 | 2.27669 | 8.93947 | 1.6184 | 0.000412764 | 4.21921e-05 | 1.8546e-05 | 1(Win) | true |
| simdjson (ondemand) | 1910.54 | 0.166758 | 906.62ms | 3370 | 640 | 5036.19 | 1682.18 | 0.108329 | 2.75026 | 9.12849 | 1.68457 | 0.00205907 | 3.75556e-05 | 2.6428e-05 | 2(Loss) | true |

----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2903.24 | 0.0741479 | 855.251ms | 3370 | 320 | 215.596 | 1107 | 0.0505053 | 1.80344 | 7.43709 | 1.3 | 0.00060089 | 1.20549e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2205.67 | 0.0275076 | 892.041ms | 3370 | 4890 | 785.584 | 1457.1 | 0.00266183 | 2.35998 | 7.76142 | 1.3908 | 0.00273349 | 3.05231e-05 | 7.22118e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1281.43 | 0.0757872 | 936.413ms | 2632 | 1280 | 2820.9 | 1958.81 | 0.0340325 | 4.02328 | 15.962 | 3.1041 | 0.00174475 | 7.53942e-05 | 2.73081e-05 | 1(Win) | true |
| simdjson (ondemand) | 771.341 | 0.0560937 | 1063.13ms | 2632 | 4890 | 16293.6 | 3254.17 | 0.0394765 | 6.65077 | 27.8024 | 5.08701 | 0.00338628 | 0.000118022 | 4.4132e-05 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1493.81 | 0.0747071 | 916.039ms | 2632 | 2560 | 4034.09 | 1680.32 | 0.0240085 | 3.46078 | 14.193 | 2.7272 | 0.00104261 | 4.24463e-05 | 1.20215e-05 | 1(Win) | true |
| simdjson (ondemand) | 840.571 | 0.0593157 | 1045.83ms | 2632 | 2560 | 8031.59 | 2986.15 | 0.131443 | 6.10931 | 26.0604 | 4.71087 | 0.0031391 | 4.61567e-05 | 9.49848e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1560.16 | 0.224607 | 937.708ms | 3370 | 640 | 13700.9 | 2059.97 | 0.00970981 | 3.2966 | 13.0335 | 2.51929 | 0.000964392 | 3.84829e-05 | 1.20549e-05 | 1(Win) | true |
| simdjson (ondemand) | 1007.65 | 0.0455891 | 1056.14ms | 3370 | 2560 | 5412.57 | 3189.49 | 0.185727 | 5.09017 | 21.6561 | 3.90742 | 0.00148948 | 4.74082e-05 | 9.273e-06 | 2(Loss) | true |

----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1792.36 | 0.126747 | 924.839ms | 3370 | 40 | 206.605 | 1793.1 | 0.0743039 | 2.8838 | 11.6442 | 2.22493 | 0.00116469 | 1.48368e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1087.31 | 0.140042 | 1048.55ms | 3370 | 30 | 514.028 | 2955.8 | 0.112646 | 4.7267 | 20.4104 | 3.63769 | 0.00207715 | 9.8912e-05 | 4.9456e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3173.1 | 0.160962 | 812.974ms | 2632 | 4890 | 7927.97 | 791.047 | 0.0219265 | 1.67766 | 6.95593 | 1.19985 | 0.000563071 | 4.63075e-05 | 1.92689e-05 | 1(Win) | true |
| simdjson (ondemand) | 2344.9 | 0.0824399 | 842.22ms | 2632 | 160 | 124.6 | 1070.44 | 0.0771307 | 2.23585 | 7.87994 | 1.37272 | 0.00114694 | 7.12386e-06 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3892.11 | 0.280612 | 804.162ms | 2632 | 640 | 2096.02 | 644.913 | 0.143708 | 1.38471 | 5.96543 | 1.0095 | 0.000994372 | 1.24668e-05 | 1.78097e-06 | 1(Win) | true |
| simdjson (ondemand) | 2679.72 | 0.0663668 | 832.678ms | 2632 | 4890 | 1889.75 | 936.692 | 0.0916673 | 1.96848 | 6.91945 | 1.18009 | 0.00134377 | 3.87709e-05 | 1.77927e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3773.81 | 0.0657806 | 820.087ms | 3370 | 2560 | 803.405 | 851.627 | 0.0178 | 1.4112 | 5.85668 | 0.95638 | 0.000319107 | 2.41098e-05 | 4.52059e-06 | 1(Win) | true |
| simdjson (ondemand) | 2955.33 | 0.125659 | 843.81ms | 3370 | 80 | 149.392 | 1087.49 | 0.0172386 | 1.77358 | 6.27804 | 1.04599 | 0.00146884 | 1.11276e-05 | 0 | 2(Loss) | true |

----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4494.77 | 0.0862726 | 810.604ms | 3370 | 4890 | 1860.8 | 715.026 | 0.0547446 | 1.18794 | 5.0908 | 0.807715 | 0.000753612 | 1.30467e-05 | 1.94183e-06 | 1(Win) | true |
| simdjson (ondemand) | 3391.58 | 0.0662687 | 833.839ms | 3370 | 320 | 126.189 | 947.606 | 0.0560309 | 1.55764 | 5.52789 | 0.895549 | 0.00163668 | 1.11276e-05 | 9.273e-07 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2443.92 | 0.100269 | 840.939ms | 2632 | 160 | 169.687 | 1027.07 | 0.0820838 | 2.15053 | 9.02014 | 1.66679 | 0.000501045 | 1.66223e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2049.04 | 0.0823197 | 857.634ms | 2632 | 1280 | 1301.63 | 1225 | 0.028882 | 2.55417 | 9.62956 | 1.65957 | 0.000734648 | 4.03685e-05 | 1.09826e-05 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2849.58 | 0.0746158 | 824.189ms | 2632 | 320 | 138.236 | 880.856 | 0.264664 | 1.89149 | 8.03305 | 1.47644 | 0.00130485 | 1.78097e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2328.8 | 0.0636744 | 845.362ms | 2632 | 4890 | 2303.27 | 1077.84 | 0.0812877 | 2.25353 | 8.67401 | 1.46695 | 0.000686377 | 2.7194e-05 | 7.22584e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2959.1 | 0.114156 | 845.845ms | 3370 | 80 | 122.977 | 1086.1 | 0.00230176 | 1.77083 | 7.46647 | 1.33501 | 0.000333828 | 2.22552e-05 | 1.48368e-05 | 1(Win) | true |
| simdjson (ondemand) | 2692.82 | 0.137724 | 854.331ms | 3370 | 1280 | 3458.39 | 1193.5 | 0.0100162 | 1.94485 | 7.64451 | 1.27003 | 0.00035956 | 2.22552e-05 | 7.88205e-06 | 2(Loss) | true |

----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3380.36 | 0.0331683 | 836.021ms | 3370 | 2560 | 254.577 | 950.751 | 0.0221815 | 1.55932 | 6.69555 | 1.18635 | 0.000877573 | 2.21393e-05 | 6.4911e-06 | 1(Win) | true |
| simdjson (ondemand) | 3037.22 | 0.192348 | 842.876ms | 3370 | 30 | 124.282 | 1058.17 | 0.0598878 | 1.73206 | 6.89822 | 1.11958 | 0.000425321 | 1.97824e-05 | 0 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 746.153 | 0.0358538 | 1333.43ms | 4630 | 2560 | 11524.4 | 5917.7 | 0.0364042 | 6.83928 | 32.0462 | 5.75573 | 0.00352836 | 7.55096e-05 | 2.78415e-05 | 1(Win) | true |
| jsonifier (generic) | 708.757 | 0.0335715 | 1363.02ms | 4630 | 2560 | 11198.2 | 6229.93 | 0.0579319 | 7.17099 | 32.0705 | 6.40757 | 0.00731093 | 5.33207e-05 | 1.80548e-05 | 2(Loss) | true |

----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 878.732 | 0.0981821 | 1338.4ms | 4630 | 30 | 730.189 | 5024.87 | 0.106252 | 5.81053 | 27.6298 | 4.75637 | 0.00230382 | 7.19942e-05 | 4.31965e-05 | 1(Win) | true |
| jsonifier (generic) | 820.005 | 0.0481345 | 1369.38ms | 4630 | 1280 | 8599.1 | 5384.74 | 0.0856723 | 6.21486 | 27.7734 | 5.43089 | 0.00490888 | 5.90578e-05 | 1.43426e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1756.5 | 0.100428 | 1374.44ms | 11579 | 640 | 25511.5 | 6286.7 | 0.0156605 | 2.90347 | 13.6499 | 2.34312 | 0.0012211 | 5.23577e-05 | 3.07669e-05 | 1(Win) | true |
| jsonifier (generic) | 1630.75 | 0.0497563 | 1418.45ms | 11579 | 2560 | 29060.6 | 6771.49 | 0.12633 | 3.11096 | 13.8746 | 2.66396 | 0.00251344 | 3.12392e-05 | 1.20436e-05 | 2(Loss) | true |

----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2039.82 | 0.0348229 | 1373.73ms | 11579 | 2560 | 9097.61 | 5413.5 | 0.101516 | 2.49552 | 11.8635 | 1.93937 | 0.000617969 | 3.99093e-05 | 1.96341e-05 | 1(Win) | true |
| jsonifier (generic) | 1866.98 | 0.0651658 | 1423.37ms | 11579 | 4890 | 72646.1 | 5914.69 | 0.00746853 | 2.72186 | 12.1095 | 2.26419 | 0.00231429 | 4.56189e-05 | 2.22354e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 670.064 | 0.0382936 | 1397.68ms | 4630 | 4890 | 31138.1 | 6589.69 | 0.118466 | 7.57651 | 35.9002 | 6.40691 | 0.0039978 | 7.81336e-05 | 2.14658e-05 | 1(Win) | true |
| jsonifier (generic) | 643.533 | 0.0308667 | 1423.39ms | 4630 | 2560 | 11482.6 | 6861.36 | 0.068339 | 7.90349 | 35.3607 | 6.97171 | 0.00784498 | 7.74501e-05 | 3.72064e-05 | 2(Loss) | true |

----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 770.46 | 0.0446105 | 1404.71ms | 4630 | 160 | 1045.82 | 5731.01 | 0.0498634 | 6.61357 | 31.5123 | 5.41361 | 0.00346382 | 4.58963e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 737.468 | 0.0272003 | 1439.42ms | 4630 | 4890 | 12969.8 | 5987.39 | 0.047601 | 6.89212 | 31.1404 | 6.01102 | 0.00682757 | 5.21185e-05 | 9.58451e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1587.77 | 0.0242715 | 1438.52ms | 11579 | 4890 | 13933.8 | 6954.78 | 0.0274235 | 3.20937 | 15.1293 | 2.59064 | 0.00167229 | 3.85014e-05 | 1.45705e-05 | 1(Win) | true |
| jsonifier (generic) | 1508.82 | 0.0779956 | 1478.06ms | 11579 | 1280 | 41707.7 | 7318.68 | 0.18449 | 3.36365 | 14.9962 | 2.85154 | 0.00307952 | 1.94317e-05 | 6.61219e-06 | 2(Loss) | true |

----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1816.36 | 0.0830657 | 1437.69ms | 11579 | 320 | 8160.83 | 6079.53 | 0.0179361 | 2.80167 | 13.3752 | 2.19345 | 0.000908163 | 1.78124e-05 | 5.3977e-07 | 1(Win) | true |
| jsonifier (generic) | 1725.72 | 0.0667501 | 1474.5ms | 11579 | 640 | 11675.8 | 6398.85 | 0.243663 | 2.94934 | 13.2039 | 2.44641 | 0.00215557 | 1.97016e-05 | 2.56391e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7221.49 | 0.0621738 | 798.28ms | 4630 | 4890 | 706.696 | 611.44 | 0.0554443 | 0.746698 | 3.34903 | 0.461339 | 0.000432275 | 1.22346e-05 | 4.63767e-06 | 1(Win) | true |
| simdjson (ondemand) | 6735.97 | 0.167002 | 795.886ms | 4630 | 80 | 95.8733 | 655.513 | 0.040061 | 0.798342 | 3.81447 | 0.366091 | 0.000237581 | 1.07991e-05 | 2.69978e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7431.34 | 0.0493796 | 789.268ms | 4630 | 1280 | 110.188 | 594.174 | 0.118609 | 0.728154 | 3.31382 | 0.453348 | 0.000431797 | 8.26809e-06 | 3.03726e-06 | 1(Win) | true |
| simdjson (ondemand) | 6820.03 | 0.142389 | 795.232ms | 4630 | 30 | 25.4954 | 647.433 | 0.216707 | 0.787113 | 3.77905 | 0.357883 | 0.000431965 | 0 | 0 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12268.8 | 0.0299367 | 820.757ms | 11579 | 1280 | 92.9299 | 900.054 | 0.703924 | 0.430162 | 1.96649 | 0.204854 | 0.000178259 | 4.72299e-06 | 1.95667e-06 | 1(Win) | true |
| simdjson (ondemand) | 10832.1 | 0.111592 | 829.969ms | 11579 | 2560 | 3313 | 1019.43 | 0.154199 | 0.4861 | 2.33051 | 0.181277 | 0.000167497 | 9.78334e-06 | 3.20489e-06 | 2(Loss) | true |

----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 12518.7 | 0.103899 | 819.353ms | 11579 | 80 | 67.1948 | 882.087 | 0.0184256 | 0.422024 | 1.95233 | 0.201658 | 0.000172726 | 2.15908e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11000.8 | 0.0958788 | 826.11ms | 11579 | 1280 | 1185.63 | 1003.8 | 0.102528 | 0.478563 | 2.31635 | 0.177995 | 0.000170972 | 5.46517e-06 | 1.4169e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5186.75 | 0.0357691 | 817.563ms | 4630 | 640 | 59.3427 | 851.306 | 0.0286407 | 1.01974 | 4.66501 | 0.680346 | 0.000647948 | 4.38715e-06 | 1.01242e-06 | 1(Win) | true |
| simdjson (ondemand) | 5150.8 | 0.0478607 | 816.451ms | 4630 | 2560 | 430.935 | 857.248 | 0.100257 | 1.03062 | 5.04644 | 0.572787 | 0.000293348 | 1.81392e-05 | 8.60556e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5359.41 | 0.0545123 | 814.198ms | 4630 | 1280 | 258.183 | 823.88 | 0.0615988 | 0.993459 | 4.62981 | 0.672354 | 0.000648117 | 7.08693e-06 | 1.18116e-06 | 1(Win) | true |
| simdjson (ondemand) | 5268.79 | 0.0867668 | 810.97ms | 4630 | 4890 | 2585.58 | 838.051 | 0.116378 | 1.00612 | 5.01123 | 0.564579 | 0.000283516 | 1.38247e-05 | 5.47686e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9837.17 | 0.0771643 | 843.214ms | 11579 | 80 | 60.0239 | 1122.54 | 0.00334076 | 0.532304 | 2.49624 | 0.292771 | 0.000278521 | 7.55678e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9017.12 | 0.176223 | 848.17ms | 11579 | 40 | 186.292 | 1224.62 | 0.0224508 | 0.58 | 2.82313 | 0.263926 | 0.000222385 | 1.94317e-05 | 2.15908e-06 | 2(Loss) | true |

----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 9951.11 | 0.0743382 | 844.331ms | 11579 | 2560 | 1742.06 | 1109.69 | 0.149874 | 0.527834 | 2.48217 | 0.289576 | 0.000265803 | 7.92788e-06 | 4.21696e-06 | 1(Win) | true |
| simdjson (ondemand) | 9139.23 | 0.0536155 | 848.956ms | 11579 | 4890 | 2052.17 | 1208.26 | 0.0177517 | 0.573174 | 2.80905 | 0.260644 | 0.000252573 | 7.54133e-06 | 1.85443e-06 | 2(Loss) | true |

----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 1128.55 | 0.0987451 | 1174.05ms | 5092 | 80 | 1444.3 | 4302.98 | 0.0558065 | 4.52369 | 18.0409 | 3.55163 | 0.00316182 | 9.08288e-05 | 3.92773e-05 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1126.45 | 0.0311314 | 1171.53ms | 5092 | 4890 | 8807.69 | 4311 | 0.320947 | 4.5325 | 17.3688 | 3.05951 | 0.00259905 | 8.31731e-05 | 3.03214e-05 | 1(Tie) | true |

----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1332.3 | 0.0428801 | 1154.16ms | 5092 | 4890 | 11945.2 | 3644.91 | 0.0150068 | 3.85114 | 15.9748 | 3.06973 | 0.00267704 | 0.000147109 | 8.739e-05 | 1(Win) | true |
| simdjson (ondemand) | 1274.31 | 0.0781327 | 1155.33ms | 5092 | 1280 | 11347.6 | 3810.78 | 0.0753981 | 4.00784 | 15.6664 | 2.65706 | 0.00326063 | 5.21652e-05 | 1.73372e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2075.69 | 0.0900265 | 1194.89ms | 9739 | 160 | 2596.36 | 4474.57 | 0.231843 | 2.50525 | 10.0644 | 1.88106 | 0.00174492 | 6.03245e-05 | 3.91467e-05 | 1(Win) | true |
| simdjson (ondemand) | 2044.93 | 0.121233 | 1194.69ms | 9739 | 640 | 19404.3 | 4541.89 | 0.091975 | 2.50182 | 9.73632 | 1.62861 | 0.00159731 | 7.21968e-05 | 5.16608e-05 | 2(Loss) | true |

----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2366.43 | 0.0336838 | 1176.16ms | 9739 | 4890 | 8546.6 | 3924.84 | 0.109505 | 2.15789 | 8.986 | 1.62969 | 0.00132159 | 4.061e-05 | 1.86672e-05 | 1(Win) | true |
| simdjson (ondemand) | 2315.41 | 0.0400336 | 1181.31ms | 9739 | 4890 | 12610.5 | 4011.31 | 0.109532 | 2.20648 | 8.84488 | 1.41578 | 0.00165449 | 2.48406e-05 | 8.98712e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 692.168 | 0.0271981 | 1442.03ms | 5092 | 4890 | 17804.9 | 7015.8 | 0.020155 | 7.35321 | 30.8972 | 5.88954 | 0.00380432 | 0.000116667 | 5.83537e-05 | 1(Win) | true |
| simdjson (ondemand) | 474.061 | 0.161452 | 1761.94ms | 5092 | 80 | 21881.8 | 10243.6 | 0.0555531 | 10.7526 | 49.8794 | 8.60664 | 0.0054129 | 5.89159e-05 | 2.20935e-05 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 748.572 | 0.0514295 | 1442.75ms | 5092 | 1280 | 14247.7 | 6487.16 | 0.0621685 | 6.79474 | 29.017 | 5.44629 | 0.00350028 | 0.000128265 | 6.90421e-05 | 1(Win) | true |
| simdjson (ondemand) | 500.442 | 0.0548497 | 1749.32ms | 5092 | 160 | 4532.51 | 9703.65 | 0.106804 | 10.1401 | 48.1915 | 8.2067 | 0.00444938 | 3.19128e-05 | 2.45483e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1218.01 | 0.107371 | 1508.19ms | 9739 | 40 | 2681.37 | 7625.4 | 0.0742579 | 4.17419 | 16.9589 | 3.1764 | 0.00262091 | 0.000110381 | 6.1608e-05 | 1(Win) | true |
| simdjson (ondemand) | 889.279 | 0.0981623 | 1780.79ms | 9739 | 30 | 3153.29 | 10444.2 | 0.0519953 | 5.70989 | 26.6469 | 4.50652 | 0.00278263 | 3.0804e-05 | 3.42266e-06 | 2(Loss) | true |

----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1324.42 | 0.0273016 | 1518.47ms | 9739 | 4890 | 17925.2 | 7012.77 | 0.0176808 | 3.84582 | 15.9474 | 2.93905 | 0.00234629 | 3.34707e-05 | 1.10449e-05 | 1(Win) | true |
| simdjson (ondemand) | 943.856 | 0.0359419 | 1764.41ms | 9739 | 4890 | 61168.6 | 9840.31 | 0.0907895 | 5.39659 | 25.7899 | 4.30052 | 0.00207168 | 4.53556e-05 | 2.0347e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5228.56 | 0.11276 | 824.645ms | 5092 | 320 | 350.97 | 928.766 | 0.00504677 | 1.00879 | 4.4564 | 0.695208 | 0.000480533 | 7.9782e-06 | 1.22742e-06 | 1(Win) | true |
| simdjson (ondemand) | 4769.4 | 0.0684112 | 834.677ms | 5092 | 4890 | 2372.53 | 1018.18 | 0.0561064 | 1.10558 | 5.08425 | 0.537314 | 0.000405986 | 1.17671e-05 | 2.53013e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5539.19 | 0.127279 | 818.114ms | 5092 | 4890 | 6088.49 | 876.682 | 0.0699323 | 0.963754 | 4.34014 | 0.673606 | 0.000239278 | 2.4217e-05 | 1.3976e-05 | 1(Win) | true |
| simdjson (ondemand) | 4872.46 | 0.0849517 | 830.167ms | 5092 | 320 | 229.39 | 996.644 | 0.317558 | 1.0817 | 4.97447 | 0.514925 | 0.000605116 | 9.20562e-06 | 3.06854e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8022.75 | 0.218937 | 846.955ms | 9739 | 80 | 513.939 | 1157.69 | 0.0205192 | 0.651226 | 2.89126 | 0.381148 | 0.000195092 | 1.41185e-05 | 7.701e-06 | 1(Win) | true |
| simdjson (ondemand) | 7414.96 | 0.0436031 | 851.2ms | 9739 | 4890 | 1458.66 | 1252.58 | 0.0210554 | 0.706717 | 3.31502 | 0.309991 | 0.000164309 | 5.56446e-06 | 1.49085e-06 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8335.99 | 0.105136 | 841.648ms | 9739 | 1280 | 1756.41 | 1114.19 | 0.145145 | 0.631989 | 2.83048 | 0.369853 | 0.000202472 | 6.81859e-06 | 2.24612e-06 | 1(Win) | true |
| simdjson (ondemand) | 7632.24 | 0.0851384 | 852.825ms | 9739 | 1280 | 1374 | 1216.92 | 0.0279343 | 0.684998 | 3.25762 | 0.298285 | 0.000125542 | 4.89334e-06 | 3.20875e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3315.23 | 0.0805273 | 879.508ms | 5092 | 2560 | 3561.85 | 1464.79 | 0.0401987 | 1.57339 | 7.67852 | 0.983504 | 0.00035572 | 5.14747e-05 | 3.22964e-05 | 1(Win) | true |
| jsonifier (generic) | 3307.08 | 0.0348339 | 881.907ms | 5092 | 640 | 167.445 | 1468.4 | 0.0766617 | 1.57111 | 7.10291 | 1.17616 | 0.00118384 | 7.67135e-06 | 6.13708e-07 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3460.08 | 0.257621 | 870.098ms | 5092 | 640 | 8366.55 | 1403.47 | 0.0953201 | 1.52683 | 7.56815 | 0.961116 | 0.000330788 | 3.09922e-05 | 2.39346e-05 | 1(Win) | true |
| jsonifier (generic) | 3394.49 | 0.0936315 | 879.202ms | 5092 | 80 | 143.537 | 1430.59 | 0.0235973 | 1.53098 | 6.98743 | 1.15456 | 0.00128142 | 4.90966e-06 | 0 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5421.85 | 0.0484113 | 907.907ms | 9739 | 4890 | 3363.07 | 1713.04 | 0.0128472 | 0.955164 | 4.28586 | 0.639286 | 0.000734697 | 1.60634e-05 | 7.07631e-06 | 1(Win) | true |
| simdjson (ondemand) | 5393.54 | 0.0895089 | 903.259ms | 9739 | 1280 | 3041.05 | 1722.03 | 0.0125653 | 0.958911 | 4.6974 | 0.548414 | 0.000131077 | 2.6392e-05 | 1.62042e-05 | 2(Loss) | true |

----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5596.12 | 0.0709216 | 896.824ms | 9739 | 1280 | 1773.46 | 1659.69 | 0.0116281 | 0.924726 | 4.61372 | 0.531574 | 0.00013934 | 8.9845e-06 | 1.76481e-06 | 1(Win) | true |
| jsonifier (generic) | 5584.68 | 0.0558685 | 905.652ms | 9739 | 640 | 552.519 | 1663.09 | 0.36983 | 0.92904 | 4.22549 | 0.627991 | 0.000608218 | 3.8505e-06 | 4.81312e-07 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1435.55 | 0.0638327 | 1063.37ms | 4857 | 4890 | 20744.1 | 3226.63 | 0.00442375 | 3.56683 | 14.1575 | 2.85423 | 0.00102818 | 0.000176247 | 0.00010926 | 1(Win) | true |
| simdjson (ondemand) | 1321.67 | 0.112287 | 1084.17ms | 4857 | 320 | 4955.64 | 3504.66 | 0.0954068 | 3.87258 | 13.9448 | 2.58184 | 0.00254144 | 6.56269e-05 | 2.76663e-05 | 2(Loss) | true |

----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1860.2 | 0.0716444 | 1010.88ms | 4857 | 2560 | 8147.45 | 2490.05 | 0.203131 | 2.75368 | 11.3525 | 2.25654 | 0.0020276 | 5.15525e-05 | 1.08574e-05 | 1(Win) | true |
| simdjson (ondemand) | 1595.92 | 0.0424603 | 1050.74ms | 4857 | 4890 | 7426.57 | 2902.4 | 0.0328603 | 3.19764 | 11.685 | 2.11839 | 0.00267242 | 7.14925e-05 | 2.64413e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1923.23 | 0.0365195 | 1075.01ms | 6701 | 4890 | 7200.7 | 3322.83 | 0.14417 | 2.65569 | 10.616 | 2.06626 | 0.000857699 | 6.08523e-05 | 2.34681e-05 | 1(Win) | true |
| simdjson (ondemand) | 1794.43 | 0.0427558 | 1094.11ms | 6701 | 4890 | 11337.7 | 3561.34 | 0.122902 | 2.85012 | 10.5293 | 1.88629 | 0.0014231 | 5.5298e-05 | 2.0752e-05 | 2(Loss) | true |

----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2431.24 | 0.0464199 | 1030.34ms | 6701 | 4890 | 7280.12 | 2628.52 | 0.191271 | 2.11075 | 8.60648 | 1.6399 | 0.00165983 | 3.20741e-05 | 7.35476e-06 | 1(Win) | true |
| simdjson (ondemand) | 2153.65 | 0.0441254 | 1054.86ms | 6701 | 4890 | 8383.29 | 2967.32 | 0.181862 | 2.3783 | 8.89136 | 1.55037 | 0.000875949 | 5.01405e-05 | 1.6327e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 681.076 | 0.0294176 | 1423.04ms | 4857 | 4890 | 19573.5 | 6801 | 0.148366 | 7.45962 | 30.5491 | 5.77229 | 0.00489564 | 0.000133385 | 6.53875e-05 | 1(Win) | true |
| simdjson (ondemand) | 255.932 | 0.0610774 | 2547.45ms | 4857 | 640 | 78203.9 | 18098.5 | 0.0797684 | 19.7545 | 99.3652 | 18.4742 | 0.00982506 | 0.000103266 | 5.75844e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 775.869 | 0.082895 | 1369.98ms | 4857 | 40 | 979.661 | 5970.07 | 0.0406028 | 6.56463 | 27.638 | 5.1503 | 0.00459646 | 9.7797e-05 | 4.11777e-05 | 1(Win) | true |
| simdjson (ondemand) | 263.7 | 0.0622787 | 2513.6ms | 4857 | 320 | 38295.3 | 17565.4 | 0.0198405 | 19.2026 | 97.1237 | 18.0124 | 0.0129742 | 5.21155e-05 | 4.50381e-06 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 874.965 | 0.116619 | 1479.17ms | 6701 | 40 | 2902.01 | 7303.8 | 0.015976 | 5.81266 | 22.9719 | 4.39696 | 0.00410013 | 0.000145501 | 4.10387e-05 | 1(Win) | true |
| simdjson (ondemand) | 352.414 | 0.14585 | 2570.32ms | 6701 | 80 | 55959.4 | 18133.7 | 0.0453781 | 14.3617 | 72.2325 | 13.3526 | 0.00881771 | 7.27503e-05 | 4.10387e-05 | 2(Loss) | true |

----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 992.961 | 0.0528236 | 1418.36ms | 6701 | 1280 | 14793.8 | 6435.87 | 0.172513 | 5.11195 | 20.8646 | 3.94613 | 0.00434299 | 4.13884e-05 | 8.86062e-06 | 1(Win) | true |
| simdjson (ondemand) | 362.331 | 0.0792448 | 2522.84ms | 6701 | 320 | 62511.5 | 17637.4 | 0.0236126 | 13.9828 | 70.6078 | 13.0179 | 0.0104443 | 4.1505e-05 | 1.11924e-05 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3919.88 | 0.0823936 | 853.147ms | 4857 | 160 | 151.669 | 1181.67 | 0.0850825 | 1.33391 | 5.44245 | 0.934527 | 0.000721896 | 5.14721e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3772.31 | 0.0617385 | 859.506ms | 4857 | 320 | 183.901 | 1227.89 | 0.0096701 | 1.383 | 5.75664 | 0.794317 | 0.000205888 | 1.09378e-05 | 3.86041e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4620.14 | 0.0968069 | 844.187ms | 4857 | 2560 | 2411.45 | 1002.57 | 0.0722107 | 1.13707 | 4.88285 | 0.819024 | 0.0003669 | 1.64067e-05 | 5.54934e-06 | 1(Win) | true |
| simdjson (ondemand) | 4295.26 | 0.134115 | 849.375ms | 4857 | 1280 | 2677.44 | 1078.4 | 0.0102883 | 1.22038 | 5.22298 | 0.682109 | 0.00023275 | 1.75327e-05 | 1.76935e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4987.66 | 0.0690741 | 866.328ms | 6701 | 4890 | 3830.24 | 1281.28 | 0.106343 | 1.04533 | 4.36577 | 0.697657 | 0.000180634 | 1.80359e-05 | 6.3782e-06 | 1(Win) | true |
| simdjson (ondemand) | 4799.92 | 0.104067 | 868.006ms | 6701 | 1280 | 2457.24 | 1331.39 | 0.019771 | 1.08499 | 4.59588 | 0.592897 | 0.000150281 | 1.77212e-05 | 6.2957e-06 | 2(Loss) | true |

----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5825.96 | 0.122186 | 849.149ms | 6701 | 160 | 287.414 | 1096.91 | 0.078568 | 0.91644 | 3.95374 | 0.613938 | 0.00015203 | 2.42501e-05 | 6.52888e-06 | 1(Win) | true |
| simdjson (ondemand) | 5409.16 | 0.0694512 | 857.121ms | 6701 | 1280 | 861.766 | 1181.43 | 0.331123 | 0.96894 | 4.20907 | 0.511566 | 0.000183858 | 9.09379e-06 | 1.04928e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2967.78 | 0.113642 | 892.219ms | 4857 | 80 | 251.677 | 1560.76 | 0.0440684 | 1.74829 | 7.22792 | 1.31686 | 0.000234198 | 1.54416e-05 | 7.72082e-06 | 1(Win) | true |
| simdjson (ondemand) | 2376.7 | 0.0449315 | 927.763ms | 4857 | 4890 | 3749.72 | 1948.92 | 0.0820344 | 2.18072 | 9.75603 | 1.51925 | 0.000269423 | 2.45045e-05 | 6.94715e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3279.2 | 0.114402 | 884.549ms | 4857 | 80 | 208.91 | 1412.54 | 0.0274404 | 1.58753 | 6.65967 | 1.20136 | 0.000805538 | 5.14721e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2584.26 | 0.064767 | 914.728ms | 4857 | 2560 | 3449.92 | 1792.38 | 0.0700173 | 2.01273 | 9.2236 | 1.40704 | 0.000264438 | 1.12595e-05 | 3.45828e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3737.61 | 0.0904177 | 907.643ms | 6701 | 80 | 191.2 | 1709.8 | 0.0746258 | 1.3846 | 5.68736 | 0.994628 | 0.000248097 | 9.32697e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3132.98 | 0.0681031 | 939.041ms | 6701 | 1280 | 2470.06 | 2039.78 | 0.00804252 | 1.64566 | 7.42456 | 1.10387 | 0.000243434 | 1.22416e-05 | 3.03126e-06 | 2(Loss) | true |

----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4183.46 | 0.0486919 | 895.276ms | 6701 | 320 | 177.04 | 1527.58 | 0.140123 | 1.2411 | 5.27548 | 0.910909 | 0.000210789 | 1.53895e-05 | 1.86539e-06 | 1(Win) | true |
| simdjson (ondemand) | 3403.34 | 0.0867385 | 929.611ms | 6701 | 30 | 79.5816 | 1877.73 | 0.0106523 | 1.51987 | 7.03865 | 1.02253 | 0.000313386 | 1.49231e-05 | 1.49231e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1269.8 | 0.138833 | 867.358ms | 1691 | 640 | 1989.67 | 1270.02 | 0.0706691 | 4.112 | 14.437 | 2.78533 | 0.000595986 | 7.57688e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1237.64 | 0.107994 | 868.469ms | 1691 | 160 | 316.824 | 1303.02 | 0.00911428 | 4.22203 | 14.741 | 2.82436 | 0.000602454 | 9.9793e-05 | 2.95683e-05 | 2(Loss) | true |

----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1487.22 | 0.21017 | 858.943ms | 1691 | 160 | 830.996 | 1084.35 | 0.057605 | 3.57186 | 12.8362 | 2.39917 | 0.000591366 | 0.000121969 | 7.39208e-05 | 1(Win) | true |
| simdjson (ondemand) | 1434.86 | 0.071855 | 862.778ms | 1691 | 320 | 208.704 | 1123.92 | 0.0908384 | 3.65377 | 13.1301 | 2.4382 | 0.000598758 | 4.43525e-05 | 7.39208e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1560.21 | 0.16848 | 875.062ms | 2158 | 40 | 197.558 | 1319.08 | 0.216224 | 3.3407 | 11.6423 | 2.24467 | 0.000613994 | 0.000127433 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1549.56 | 0.144494 | 872.576ms | 2158 | 1280 | 4714.1 | 1328.14 | 0.119966 | 3.36664 | 11.8401 | 2.22799 | 0.000820711 | 4.70633e-05 | 8.32658e-06 | 2(Loss) | true |

----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1797.35 | 0.0666472 | 859.551ms | 2158 | 320 | 186.359 | 1145.03 | 0.14075 | 2.9172 | 10.5162 | 1.91288 | 0.000470633 | 3.33063e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 1769.74 | 0.0919104 | 864.718ms | 2158 | 160 | 182.782 | 1162.9 | 0.0150463 | 2.96062 | 10.5051 | 1.96617 | 0.000463392 | 8.97822e-05 | 8.6886e-06 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 922.295 | 0.110426 | 918.172ms | 1691 | 30 | 111.844 | 1748.53 | 0.261855 | 5.60879 | 20.0574 | 3.87581 | 0.000768776 | 0.000118273 | 3.94244e-05 | 1(Win) | true |
| simdjson (ondemand) | 765.329 | 0.0776697 | 952.988ms | 1691 | 80 | 214.281 | 2107.15 | 0.100949 | 6.73987 | 26.8817 | 5.08634 | 0.000850089 | 3.69604e-05 | 1.47842e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1023.41 | 0.0638347 | 906.409ms | 1691 | 160 | 161.89 | 1575.77 | 0.0859951 | 5.07129 | 18.5376 | 3.50384 | 0.000595062 | 0.000147842 | 6.65287e-05 | 1(Win) | true |
| simdjson (ondemand) | 839.72 | 0.0773478 | 941.809ms | 1691 | 2560 | 5648.77 | 1920.48 | 0.177639 | 6.17956 | 25.2797 | 4.69959 | 0.000596217 | 0.000156158 | 8.08508e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1120.96 | 0.133403 | 924.083ms | 2158 | 40 | 239.946 | 1835.95 | 0.177334 | 4.61047 | 16.424 | 3.25348 | 0.000521316 | 0.000139018 | 2.31696e-05 | 1(Win) | true |
| simdjson (ondemand) | 976.723 | 0.0709452 | 949.064ms | 2158 | 160 | 357.542 | 2107.07 | 0.0391691 | 5.27983 | 21.1905 | 3.9671 | 0.000463392 | 6.95088e-05 | 1.73772e-05 | 2(Loss) | true |

----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1225.15 | 0.0661698 | 916.651ms | 2158 | 2560 | 3162.88 | 1679.82 | 0.0183741 | 4.22541 | 15.2947 | 2.97451 | 0.000469365 | 0.000106616 | 7.60253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1064.68 | 0.0901178 | 942.35ms | 2158 | 30 | 91.0345 | 1933 | 0.115671 | 4.85493 | 19.9351 | 3.66404 | 0.000463392 | 3.08928e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4537.7 | 0.113703 | 768.827ms | 1691 | 4890 | 798.482 | 355.392 | 0.181456 | 1.24083 | 4.54229 | 0.733295 | 0.000593664 | 4.77688e-05 | 2.12843e-05 | 1(Win) | true |
| simdjson (ondemand) | 4189.22 | 0.0570259 | 770.578ms | 1691 | 1280 | 61.6845 | 384.955 | 0.274933 | 1.33327 | 4.91603 | 0.682436 | 0.000591828 | 1.80182e-05 | 1.84802e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4983.56 | 0.0746848 | 767.312ms | 1691 | 4890 | 285.615 | 323.596 | 0.0443334 | 1.14331 | 4.21999 | 0.667061 | 0.000592213 | 2.80566e-05 | 1.00375e-05 | 1(Win) | true |
| simdjson (ondemand) | 4536.31 | 0.131544 | 769.219ms | 1691 | 4890 | 1069.38 | 355.501 | 0.0916871 | 1.2376 | 4.59255 | 0.615021 | 0.000592938 | 2.35821e-05 | 7.86069e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5291.68 | 0.047076 | 773.764ms | 2158 | 2560 | 85.8131 | 388.918 | 0.0521007 | 1.05608 | 3.9152 | 0.587119 | 0.000464297 | 3.18582e-05 | 1.19468e-05 | 1(Win) | true |
| simdjson (ondemand) | 5066.07 | 0.129558 | 772.206ms | 2158 | 160 | 44.3206 | 406.238 | 0.0399852 | 1.09824 | 4.11956 | 0.545876 | 0.000463392 | 1.15848e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5879.56 | 0.0905891 | 770.817ms | 2158 | 640 | 64.3496 | 350.031 | 0.149316 | 0.961283 | 3.66265 | 0.535218 | 0.000464116 | 1.3757e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5501.74 | 0.101882 | 770.619ms | 2158 | 320 | 46.478 | 374.069 | 0.0500994 | 1.02279 | 3.86608 | 0.493049 | 0.000463392 | 5.7924e-06 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3209.8 | 0.0548771 | 782.727ms | 1691 | 320 | 24.3257 | 502.419 | 0.0534626 | 1.70239 | 6.54997 | 1.12241 | 0.000591366 | 2.40242e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2729.45 | 0.0946249 | 794.783ms | 1691 | 160 | 50.0112 | 590.837 | 0.0951133 | 1.99626 | 7.98699 | 1.23182 | 0.000887049 | 3.32643e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3465.58 | 0.082965 | 782.621ms | 1691 | 160 | 23.8476 | 465.337 | 0.0241818 | 1.58835 | 6.21289 | 1.05618 | 0.000595062 | 1.47842e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2908.98 | 0.119048 | 792.555ms | 1691 | 80 | 34.8449 | 554.375 | 0.0360637 | 1.87121 | 7.66233 | 1.1644 | 0.000591366 | 2.21762e-05 | 7.39208e-06 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3805.26 | 0.0402979 | 790.256ms | 2158 | 1280 | 60.8008 | 540.837 | 0.172754 | 1.43086 | 5.50741 | 0.905005 | 0.000463392 | 1.01367e-05 | 7.2405e-07 | 1(Win) | true |
| simdjson (ondemand) | 3376.45 | 0.0863167 | 797.364ms | 2158 | 160 | 44.2887 | 609.525 | 0.0266672 | 1.60666 | 6.49166 | 0.96988 | 0.000628475 | 1.15848e-05 | 0 | 2(Loss) | true |

----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4084.91 | 0.0452103 | 785.994ms | 2158 | 640 | 33.2042 | 503.812 | 0.0372301 | 1.33536 | 5.24328 | 0.853105 | 0.000463392 | 5.06835e-06 | 7.2405e-07 | 1(Win) | true |
| simdjson (ondemand) | 3578.05 | 0.0878654 | 793.364ms | 2158 | 160 | 40.8663 | 575.181 | 0.0488737 | 1.51346 | 6.23726 | 0.917053 | 0.000463392 | 8.6886e-06 | 0 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1290.74 | 0.0493397 | 1060.09ms | 4390 | 4890 | 12524.2 | 3243.58 | 0.154387 | 3.95631 | 17.6754 | 3.36948 | 0.00157939 | 0.000100014 | 5.58063e-05 | 1(Win) | true |
| simdjson (ondemand) | 1025.37 | 0.0516092 | 1144.2ms | 4390 | 1280 | 5683.69 | 4083.04 | 0.257054 | 4.97325 | 18.9426 | 3.55945 | 0.00397423 | 5.44562e-05 | 2.08215e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1433.72 | 0.0761525 | 1052.19ms | 4390 | 2560 | 12659.4 | 2920.12 | 0.138376 | 3.57233 | 16.2658 | 3.05376 | 0.00189867 | 3.89735e-05 | 1.21014e-05 | 1(Win) | true |
| simdjson (ondemand) | 1127.72 | 0.040058 | 1130.49ms | 4390 | 320 | 707.704 | 3712.46 | 0.00538697 | 4.53764 | 17.4674 | 3.23098 | 0.0042967 | 1.06777e-05 | 7.11845e-07 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2488.24 | 0.107194 | 1098.47ms | 9378 | 320 | 4750.4 | 3594.34 | 0.122913 | 2.05409 | 9.14897 | 1.64502 | 0.000772419 | 2.06601e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 2059.3 | 0.0827556 | 1170ms | 9378 | 1280 | 16534.3 | 4343.01 | 0.145596 | 2.47645 | 9.56771 | 1.6961 | 0.00138981 | 2.63249e-05 | 1.15796e-05 | 2(Loss) | true |

----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2767.46 | 0.0463929 | 1086.49ms | 9378 | 2560 | 5754.41 | 3231.69 | 0.05772 | 1.849 | 8.46353 | 1.492 | 0.000924912 | 2.35758e-05 | 5.6232e-06 | 1(Win) | true |
| simdjson (ondemand) | 2262.07 | 0.0756416 | 1157.64ms | 9378 | 1280 | 11448.2 | 3953.7 | 0.0120916 | 2.25673 | 8.87716 | 1.54233 | 0.00169079 | 1.20795e-05 | 2.74912e-06 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 773.602 | 0.0358287 | 1280.32ms | 4390 | 2560 | 9624.9 | 5411.87 | 0.0201926 | 6.58003 | 28.9196 | 5.6369 | 0.00778029 | 6.47779e-05 | 3.2122e-05 | 1(Win) | true |
| simdjson (ondemand) | 729.018 | 0.177902 | 1312.58ms | 4390 | 30 | 3131.39 | 5742.83 | 0.19832 | 6.89194 | 30.2442 | 5.58428 | 0.0059833 | 6.83371e-05 | 2.2779e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 823.445 | 0.052169 | 1265.67ms | 4390 | 160 | 1125.65 | 5084.29 | 0.111497 | 6.18839 | 27.5062 | 5.32141 | 0.00818052 | 5.26765e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 783.715 | 0.106932 | 1293.91ms | 4390 | 1280 | 41767.4 | 5342.03 | 0.0325145 | 6.5025 | 28.7661 | 5.25581 | 0.0045535 | 2.38468e-05 | 1.01438e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1537.78 | 0.0738059 | 1319.79ms | 9378 | 40 | 737.015 | 5815.9 | 0.0624334 | 3.31227 | 14.7123 | 2.61452 | 0.00210066 | 1.06633e-05 | 0 | 1(Win) | true |
| jsonifier (generic) | 1534.62 | 0.033202 | 1318.98ms | 9378 | 4890 | 18308.6 | 5827.85 | 0.0194324 | 3.31689 | 14.5041 | 2.73747 | 0.00363761 | 3.19898e-05 | 1.2604e-05 | 2(Loss) | true |

----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1638.27 | 0.0936707 | 1302.84ms | 9378 | 320 | 8367.72 | 5459.15 | 0.0216999 | 3.1079 | 14.0204 | 2.46076 | 0.00192072 | 1.26626e-05 | 9.9968e-07 | 1(Win) | true |
| jsonifier (generic) | 1628.05 | 0.134248 | 1305.53ms | 9378 | 160 | 8702.08 | 5493.42 | 0.116981 | 3.12733 | 13.8424 | 2.58979 | 0.00377812 | 1.93271e-05 | 4.66517e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2400.03 | 0.0829367 | 908.792ms | 4390 | 4890 | 10235.2 | 1744.41 | 0.108654 | 2.15949 | 10.1405 | 1.88588 | 0.00034504 | 5.97659e-05 | 2.85553e-05 | 1(Win) | true |
| simdjson (ondemand) | 2134.36 | 0.0631569 | 945.971ms | 4390 | 160 | 245.558 | 1961.54 | 0.021662 | 2.41933 | 10.4064 | 1.75968 | 0.000801538 | 2.84738e-05 | 7.11845e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2542.92 | 0.0865132 | 898.203ms | 4390 | 2560 | 5193.62 | 1646.39 | 0.0367146 | 2.04662 | 9.78474 | 1.80615 | 0.000230549 | 2.18003e-05 | 8.89806e-06 | 1(Win) | true |
| simdjson (ondemand) | 2233.87 | 0.0647343 | 923.134ms | 4390 | 4890 | 7197.65 | 1874.16 | 0.0139121 | 2.31374 | 10.0513 | 1.6795 | 0.000638465 | 4.03408e-05 | 2.55274e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4254.71 | 0.055988 | 957.366ms | 9378 | 640 | 886.442 | 2102.04 | 0.277307 | 1.21487 | 5.64246 | 0.946257 | 0.000611138 | 3.33227e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4032.44 | 0.0913819 | 977.206ms | 9378 | 1280 | 5257.93 | 2217.9 | 0.0346843 | 1.27506 | 5.5707 | 0.853167 | 0.000434194 | 1.56617e-05 | 5.33163e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4443.85 | 0.0485807 | 938.903ms | 9378 | 4890 | 4674.54 | 2012.57 | 0.106694 | 1.16059 | 5.47793 | 0.908936 | 0.000481591 | 1.26258e-05 | 3.44539e-06 | 1(Win) | true |
| simdjson (ondemand) | 4221.64 | 0.0666343 | 946.68ms | 9378 | 1280 | 2550.73 | 2118.51 | 0.122688 | 1.22449 | 5.40446 | 0.815632 | 0.000466684 | 9.58027e-06 | 1.66613e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1884.46 | 0.0646493 | 961.201ms | 4390 | 320 | 660.137 | 2221.66 | 0.0467211 | 2.73401 | 13.0859 | 2.52961 | 0.00138525 | 1.70843e-05 | 2.84738e-06 | 1(Win) | true |
| simdjson (ondemand) | 1843.69 | 0.0504796 | 976.426ms | 4390 | 320 | 420.471 | 2270.79 | 0.0563912 | 2.79214 | 12.5346 | 2.11845 | 0.00103289 | 2.20672e-05 | 1.06777e-05 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1969.16 | 0.0365126 | 951.083ms | 4390 | 4890 | 2946.87 | 2126.1 | 0.110214 | 2.62494 | 12.7287 | 2.44989 | 0.00122071 | 3.83377e-05 | 1.80276e-05 | 1(Win) | true |
| simdjson (ondemand) | 1938.46 | 0.124821 | 953.264ms | 4390 | 640 | 4651.25 | 2159.77 | 0.132145 | 2.65521 | 12.1875 | 2.03827 | 0.000602221 | 1.24573e-05 | 1.77961e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3567.17 | 0.0520726 | 1002.01ms | 9378 | 2560 | 4363.47 | 2507.19 | 0.152453 | 1.4387 | 6.56697 | 1.02111 | 0.000490093 | 1.39955e-05 | 4.04037e-06 | 1(Win) | true |
| jsonifier (generic) | 3510.38 | 0.0570939 | 993.083ms | 9378 | 4890 | 10346.7 | 2547.74 | 0.219693 | 1.46706 | 6.93421 | 1.25037 | 0.000572785 | 1.31056e-05 | 4.44847e-06 | 2(Loss) | true |

----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3727.44 | 0.0510837 | 975.586ms | 9378 | 2560 | 3845.94 | 2399.38 | 0.0644933 | 1.38366 | 6.40446 | 0.983579 | 0.000384335 | 1.2621e-05 | 3.24896e-06 | 1(Win) | true |
| jsonifier (generic) | 3636.73 | 0.0816463 | 989.173ms | 9378 | 160 | 645.047 | 2459.23 | 0.0556886 | 1.41403 | 6.76701 | 1.21305 | 0.000498507 | 1.53284e-05 | 1.33291e-06 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1502.83 | 0.0427584 | 1030.81ms | 4669 | 4890 | 7848.35 | 2962.87 | 0.332144 | 3.42407 | 13.904 | 2.95074 | 0.0021869 | 4.50695e-05 | 1.41472e-05 | 1(Win) | true |
| simdjson (ondemand) | 1409.94 | 0.0870937 | 1048.57ms | 4669 | 1280 | 9683.45 | 3158.08 | 0.193768 | 3.63588 | 14.5826 | 2.50632 | 0.00175375 | 4.36724e-05 | 1.52268e-05 | 2(Loss) | true |

----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1627.01 | 0.0485464 | 1012.37ms | 4669 | 4890 | 8631.53 | 2736.73 | 0.0241353 | 3.17312 | 13.1226 | 2.7839 | 0.00240511 | 4.25729e-05 | 1.3972e-05 | 1(Win) | true |
| simdjson (ondemand) | 1513.72 | 0.0713755 | 1033.33ms | 4669 | 1280 | 5642.43 | 2941.57 | 0.0165755 | 3.39049 | 13.831 | 2.3414 | 0.00172866 | 2.6605e-05 | 6.35843e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2339.77 | 0.0710411 | 1057.49ms | 7932 | 640 | 3376.12 | 3233.03 | 0.0103919 | 2.18771 | 8.83636 | 1.78013 | 0.0012485 | 1.20162e-05 | 1.77288e-06 | 1(Win) | true |
| simdjson (ondemand) | 2292.77 | 0.159524 | 1063.07ms | 7932 | 80 | 2216.09 | 3299.3 | 0.156606 | 2.26813 | 9.15872 | 1.49798 | 0.00129539 | 2.67902e-05 | 4.72769e-06 | 2(Loss) | true |

----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2521.79 | 0.205108 | 1042.24ms | 7932 | 40 | 1514.17 | 2999.68 | 0.0319377 | 2.0336 | 8.38364 | 1.68432 | 0.00127648 | 2.20625e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2437.44 | 0.047569 | 1043.9ms | 7932 | 4890 | 10657.5 | 3103.48 | 0.0970332 | 2.1095 | 8.71949 | 1.40217 | 0.000963326 | 2.44667e-05 | 3.89301e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 556.045 | 0.0905683 | 1536.02ms | 4669 | 4890 | 257211 | 8007.82 | 0.0999046 | 9.21211 | 38.9195 | 7.16064 | 0.00602683 | 7.31886e-05 | 2.91265e-05 | 1(Win) | true |
| simdjson (ondemand) | 296.989 | 0.0628542 | 2259.1ms | 4669 | 80 | 7104.36 | 14992.8 | 0.0160936 | 17.3719 | 89.5937 | 17.1011 | 0.00434247 | 4.28357e-05 | 1.07089e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 576.279 | 0.0384101 | 1512.67ms | 4669 | 2560 | 22548.3 | 7726.65 | 0.0764984 | 8.88574 | 38.1339 | 6.99272 | 0.00619729 | 6.43373e-05 | 3.07882e-05 | 1(Win) | true |
| simdjson (ondemand) | 296.558 | 0.0504127 | 2240.27ms | 4669 | 640 | 36668.1 | 15014.6 | 0.0891594 | 17.0756 | 88.8477 | 16.9355 | 0.00418318 | 2.47644e-05 | 2.00792e-06 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 900.545 | 0.111293 | 1590.69ms | 7932 | 30 | 2621.9 | 8399.97 | 0.0543358 | 5.74917 | 23.9486 | 4.45512 | 0.00350059 | 6.30358e-05 | 2.94167e-05 | 1(Win) | true |
| simdjson (ondemand) | 500.682 | 0.0238377 | 2247.08ms | 7932 | 2560 | 33205.5 | 15108.5 | 0.00278204 | 10.1242 | 52.5646 | 9.9294 | 0.0018566 | 3.3537e-05 | 1.30504e-05 | 2(Loss) | true |

----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 919.559 | 0.0474927 | 1567.3ms | 7932 | 2560 | 39075.2 | 8226.28 | 0.164521 | 5.54322 | 23.4987 | 4.35968 | 0.00286641 | 5.66337e-05 | 2.52143e-05 | 1(Win) | true |
| simdjson (ondemand) | 508.885 | 0.153277 | 2256.04ms | 7932 | 160 | 83061.2 | 14864.9 | 0.0128254 | 9.94806 | 52.1254 | 9.83195 | 0.00140649 | 1.65469e-05 | 1.5759e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4608 | 0.0813268 | 827.808ms | 4669 | 4890 | 3019.94 | 966.298 | 0.478517 | 1.14952 | 5.03277 | 0.808525 | 0.000595539 | 2.40458e-05 | 1.21324e-05 | 1(Win) | true |
| simdjson (ondemand) | 4480.15 | 0.132232 | 824.272ms | 4669 | 40 | 69.0865 | 993.875 | 0.0728936 | 1.17618 | 5.27094 | 0.605697 | 0.000546155 | 1.07089e-05 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4969.12 | 0.0488419 | 821.146ms | 4669 | 2560 | 490.359 | 896.076 | 0.0534734 | 1.06511 | 4.77533 | 0.755836 | 0.000445174 | 1.30515e-05 | 3.84852e-06 | 1(Win) | true |
| simdjson (ondemand) | 4880.65 | 0.0384609 | 818.846ms | 4669 | 1280 | 157.594 | 912.317 | 0.285975 | 1.08693 | 5.02592 | 0.551296 | 0.00022974 | 1.42228e-05 | 5.52179e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) STATISTICAL TIE | 6662.89 | 0.102488 | 844.503ms | 7932 | 160 | 216.623 | 1135.33 | 0.189732 | 0.799055 | 3.52143 | 0.501009 | 0.000127648 | 1.41831e-05 | 7.09153e-06 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 6648.6 | 0.0537446 | 842.73ms | 7932 | 320 | 119.653 | 1137.77 | 0.0519379 | 0.802916 | 3.66856 | 0.377206 | 0.000165863 | 5.90961e-06 | 0 | 1(Tie) | true |

----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7065.1 | 0.0581238 | 836.625ms | 7932 | 1280 | 495.733 | 1070.69 | 0.186156 | 0.754985 | 3.36989 | 0.469995 | 0.000157688 | 1.83198e-05 | 1.14252e-05 | 1(Win) | true |
| simdjson (ondemand) | 7000.56 | 0.20798 | 839.18ms | 7932 | 80 | 404.047 | 1080.56 | 0.132856 | 0.749406 | 3.52433 | 0.345184 | 0.000144982 | 9.45537e-06 | 4.72769e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3229.6 | 0.0771756 | 870.669ms | 4669 | 2560 | 2898.35 | 1378.72 | 0.0860347 | 1.61403 | 6.96595 | 1.21247 | 0.000907498 | 3.5557e-05 | 1.8657e-05 | 1(Win) | true |
| simdjson (ondemand) | 2833.05 | 0.0582863 | 886.482ms | 4669 | 160 | 134.274 | 1571.7 | 0.0190913 | 1.83014 | 8.91647 | 1.22532 | 0.000481902 | 2.67723e-06 | 0 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3420.08 | 0.105891 | 864.979ms | 4669 | 1280 | 2432.8 | 1301.93 | 0.0263362 | 1.52632 | 6.70979 | 1.15978 | 0.000807018 | 1.70674e-05 | 6.1911e-06 | 1(Win) | true |
| simdjson (ondemand) | 2987.37 | 0.052396 | 877.805ms | 4669 | 4890 | 2982.46 | 1490.51 | 0.0725769 | 1.74704 | 8.67423 | 1.17091 | 0.000433788 | 1.63809e-05 | 5.95671e-06 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4758.97 | 0.0452688 | 891.666ms | 7932 | 640 | 331.373 | 1589.53 | 0.0410076 | 1.08898 | 4.67776 | 0.749748 | 0.000599037 | 6.30358e-06 | 2.16686e-06 | 1(Win) | true |
| simdjson (ondemand) | 4410.79 | 0.036222 | 903.454ms | 7932 | 320 | 123.489 | 1715.01 | 0.126479 | 1.17338 | 5.80005 | 0.73878 | 0.000130405 | 5.90961e-06 | 3.93974e-07 | 2(Loss) | true |

----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5000.28 | 0.0939317 | 883.498ms | 7932 | 160 | 323.089 | 1512.83 | 0.154274 | 1.03767 | 4.52698 | 0.718734 | 0.000788736 | 7.09153e-06 | 7.87948e-07 | 1(Win) | true |
| simdjson (ondemand) | 4579.26 | 0.0720629 | 894.328ms | 7932 | 160 | 226.734 | 1651.91 | 0.0113492 | 1.13035 | 5.65746 | 0.706757 | 0.000138679 | 5.51563e-06 | 3.93974e-06 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 554.057 | 0.0281741 | 1535.05ms | 4604 | 4890 | 24376.6 | 7924.67 | 0.163693 | 9.21188 | 36.3656 | 7.74892 | 0.0111928 | 0.000124014 | 4.84153e-05 | 1(Win) | true |
| simdjson (ondemand) | 543.871 | 0.0396436 | 1549.48ms | 4604 | 2560 | 26221.9 | 8073.09 | 0.211786 | 9.39679 | 37.3827 | 7.15856 | 0.0108628 | 9.25656e-05 | 4.27617e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 636.129 | 0.08381 | 1524.63ms | 4604 | 640 | 21416.6 | 6902.24 | 0.0249178 | 8.03928 | 31.7402 | 6.70287 | 0.00919852 | 3.69923e-05 | 2.71503e-06 | 1(Win) | true |
| simdjson (ondemand) | 623.597 | 0.0307095 | 1533.17ms | 4604 | 4890 | 22862.2 | 7040.95 | 0.0355873 | 8.19184 | 32.8104 | 6.12554 | 0.0085528 | 0.000165145 | 0.000104337 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1998.07 | 0.0345434 | 1619.8ms | 18245 | 320 | 2895.64 | 8708.28 | 0.0689242 | 2.54283 | 10.0901 | 2.00754 | 0.00278758 | 1.37024e-05 | 3.25432e-06 | 1(Win) | true |
| simdjson (ondemand) | 1964.81 | 0.0383136 | 1636.52ms | 18245 | 2560 | 29470.8 | 8855.7 | 0.322578 | 2.59661 | 10.4421 | 1.84083 | 0.00295306 | 3.06377e-05 | 1.47943e-05 | 2(Loss) | true |

----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2274.69 | 0.20604 | 1673.15ms | 18245 | 80 | 19871.8 | 7649.3 | 0.2224 | 2.23277 | 8.90386 | 1.73987 | 0.00240682 | 1.91833e-05 | 6.16607e-06 | 1(Win) | true |
| simdjson (ondemand) | 2221.78 | 0.0876042 | 1620.17ms | 18245 | 320 | 15062.1 | 7831.46 | 0.0400069 | 2.28603 | 9.30222 | 1.5829 | 0.00256337 | 2.5692e-05 | 1.40449e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 329.445 | 0.020649 | 2084.94ms | 4604 | 4890 | 37034.9 | 13327.6 | 0.0422622 | 15.3777 | 64.7669 | 12.9841 | 0.0106776 | 0.000272547 | 0.0001659 | 1(Win) | true |
| simdjson (ondemand) | 242.237 | 0.0219482 | 2558.89ms | 4604 | 4890 | 77392.2 | 18125.7 | 0.017117 | 20.895 | 98.7339 | 17.8231 | 0.012424 | 0.000290314 | 0.000184067 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 355.184 | 0.0536764 | 2079.02ms | 4604 | 1280 | 56356.1 | 12361.8 | 0.0369785 | 14.2661 | 60.3501 | 11.9778 | 0.00981467 | 0.000161884 | 0.000102323 | 1(Win) | true |
| simdjson (ondemand) | 259.567 | 0.0310388 | 2525.95ms | 4604 | 2560 | 70570.1 | 16915.5 | 0.0962874 | 19.5984 | 94.1759 | 16.787 | 0.0101194 | 0.000184622 | 0.00010648 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1202.98 | 0.285114 | 2193.29ms | 18245 | 30 | 51018.9 | 14463.9 | 0.0336356 | 4.20803 | 17.2402 | 3.35884 | 0.00317165 | 4.93286e-05 | 2.37508e-05 | 1(Win) | true |
| simdjson (ondemand) | 927.273 | 0.0515838 | 2617.86ms | 18245 | 1280 | 119925 | 18764.5 | 0.0516577 | 5.46568 | 25.8876 | 4.52483 | 0.00279143 | 0.000107136 | 6.28597e-05 | 2(Loss) | true |

----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1309.66 | 0.0663942 | 2177.17ms | 18245 | 320 | 24899.1 | 13285.8 | 0.119207 | 3.87144 | 16.102 | 3.10011 | 0.00342748 | 1.66141e-05 | 4.79583e-06 | 1(Win) | true |
| simdjson (ondemand) | 990.217 | 0.0789741 | 2604.02ms | 18245 | 320 | 61623.6 | 17571.7 | 0.00793116 | 5.13188 | 24.752 | 4.26627 | 0.00210794 | 4.69307e-05 | 2.94601e-05 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4056.45 | 0.0714246 | 849.326ms | 4604 | 2560 | 1530.08 | 1082.4 | 0.232555 | 1.29245 | 5.77389 | 0.896612 | 0.000469191 | 1.6375e-05 | 6.70273e-06 | 1(Win) | true |
| simdjson (ondemand) | 3723.71 | 0.137764 | 845.225ms | 4604 | 40 | 105.548 | 1179.12 | 0.0162576 | 1.37817 | 6.46221 | 0.727845 | 0.000629887 | 1.08601e-05 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4180.52 | 0.0482839 | 844.766ms | 4604 | 160 | 41.1468 | 1050.28 | 0.216481 | 1.25549 | 5.69027 | 0.877281 | 0.000435762 | 1.49327e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3920.2 | 0.0674353 | 845.768ms | 4604 | 4890 | 2789.57 | 1120.02 | 0.170618 | 1.33675 | 6.38032 | 0.708297 | 0.000270592 | 2.3719e-05 | 6.5294e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10559.8 | 0.0336366 | 902.45ms | 18245 | 640 | 196.597 | 1647.73 | 0.0271133 | 0.490701 | 2.23069 | 0.251631 | 0.000134455 | 9.50603e-06 | 1.02768e-06 | 1(Win) | true |
| simdjson (ondemand) | 9586.71 | 0.136652 | 917.669ms | 18245 | 640 | 3936.96 | 1814.99 | 0.0536904 | 0.539391 | 2.6547 | 0.221211 | 7.57057e-05 | 1.24178e-05 | 3.08304e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 10810.5 | 0.0470236 | 900.588ms | 18245 | 2560 | 1466.46 | 1609.53 | 0.0760512 | 0.479307 | 2.20965 | 0.246807 | 0.000125548 | 7.57913e-06 | 1.02768e-06 | 1(Win) | true |
| simdjson (ondemand) | 9667.52 | 0.0577519 | 910.504ms | 18245 | 160 | 172.866 | 1799.82 | 0.0218724 | 0.534534 | 2.63404 | 0.216278 | 0.000135311 | 6.50863e-06 | 6.85119e-07 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2901.61 | 0.051249 | 886.297ms | 4604 | 160 | 96.2239 | 1513.2 | 0.00660808 | 1.78839 | 8.21286 | 1.34991 | 0.000651607 | 2.17202e-05 | 4.07255e-06 | 1(Win) | true |
| simdjson (ondemand) | 2236.66 | 0.0960838 | 930.027ms | 4604 | 1280 | 4553.87 | 1963.07 | 0.0030645 | 2.30423 | 12.1292 | 1.59774 | 0.000329707 | 1.35752e-05 | 3.39379e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2965.53 | 0.0158094 | 886.834ms | 4604 | 1280 | 70.1306 | 1480.58 | 0.542249 | 1.75029 | 8.12815 | 1.3308 | 0.000652116 | 9.16323e-06 | 1.69689e-07 | 1(Win) | true |
| simdjson (ondemand) | 2234.76 | 0.103918 | 930.91ms | 4604 | 80 | 333.487 | 1964.74 | 0.0133588 | 2.30974 | 12.0474 | 1.57819 | 0.000730343 | 5.43006e-06 | 0 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8326.08 | 0.0609667 | 943.002ms | 18245 | 160 | 259.724 | 2089.79 | 0.0110669 | 0.618786 | 2.845 | 0.367169 | 0.00026103 | 7.53631e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 6529.4 | 0.0476296 | 1003.49ms | 18245 | 4890 | 7877.78 | 2664.84 | 0.0073965 | 0.785267 | 4.08517 | 0.440888 | 0.000156347 | 9.91952e-06 | 3.53068e-06 | 2(Loss) | true |

----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 8494.61 | 0.123691 | 945.574ms | 18245 | 30 | 192.575 | 2048.33 | 0.14994 | 0.606581 | 2.82379 | 0.362346 | 0.000171737 | 1.27889e-05 | 1.82698e-06 | 1(Win) | true |
| simdjson (ondemand) | 6592.51 | 0.0294139 | 1001.39ms | 18245 | 4890 | 2947.14 | 2639.32 | 0.0322933 | 0.778225 | 4.06451 | 0.435955 | 0.000164003 | 5.85083e-06 | 9.52722e-07 | 2(Loss) | true |

----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1310.33 | 0.0579632 | 1100.14ms | 4926 | 2560 | 11055.3 | 3585.2 | 0.0728785 | 3.90322 | 16.7674 | 3.24787 | 0.00404082 | 7.60474e-05 | 2.18071e-05 | 1(Win) | true |
| simdjson (ondemand) | 1016.33 | 0.097671 | 1199.25ms | 4926 | 320 | 6522.33 | 4622.33 | 0.0996204 | 5.01616 | 18.1297 | 3.42976 | 0.00526733 | 4.44072e-05 | 8.88145e-06 | 2(Loss) | true |

----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1630.61 | 0.109654 | 1067.61ms | 4926 | 640 | 6387.27 | 2881.01 | 0.45216 | 3.20308 | 14.1679 | 2.72249 | 0.00410386 | 5.67778e-05 | 3.36226e-05 | 1(Win) | true |
| simdjson (ondemand) | 1195.01 | 0.0593346 | 1164.4ms | 4926 | 1280 | 6964.25 | 3931.19 | 0.0210103 | 4.27321 | 15.512 | 2.89667 | 0.00568079 | 4.63104e-05 | 5.7095e-06 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2003.98 | 0.10757 | 1130.33ms | 8150 | 640 | 11140.2 | 3878.51 | 0.0461466 | 2.5485 | 10.7106 | 1.9811 | 0.00241814 | 8.53144e-05 | 5.19555e-05 | 1(Win) | true |
| simdjson (ondemand) | 1618.36 | 0.0591124 | 1219.35ms | 8150 | 2560 | 20633.1 | 4802.67 | 0.0320276 | 3.14457 | 11.5091 | 2.09644 | 0.00304477 | 4.24176e-05 | 1.68232e-05 | 2(Loss) | true |

----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2446.95 | 0.0703912 | 1093.56ms | 8150 | 1280 | 6398.97 | 3176.38 | 0.0805418 | 2.09241 | 9.13444 | 1.66124 | 0.00217849 | 3.49885e-05 | 1.51457e-05 | 1(Win) | true |
| simdjson (ondemand) | 1899.83 | 0.131547 | 1189.94ms | 8150 | 40 | 1158.52 | 4091.12 | 0.0287125 | 2.69166 | 9.92528 | 1.77411 | 0.00357669 | 4.90798e-05 | 0 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 824.372 | 0.0479513 | 1314.37ms | 4926 | 2560 | 19115.4 | 5698.64 | 0.107776 | 6.20534 | 27.1866 | 5.2834 | 0.00567857 | 6.95449e-05 | 2.50584e-05 | 1(Win) | true |
| simdjson (ondemand) | 516.247 | 0.0346399 | 1652.89ms | 4926 | 2560 | 25437 | 9099.91 | 0.0263551 | 9.82846 | 44.6433 | 8.49269 | 0.010068 | 0.000118631 | 5.31301e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 943.026 | 0.086447 | 1278.23ms | 4926 | 640 | 11869.2 | 4981.62 | 0.0146768 | 5.43431 | 24.5928 | 4.76106 | 0.00543576 | 9.23036e-05 | 5.61434e-05 | 1(Win) | true |
| simdjson (ondemand) | 565.319 | 0.084946 | 1615.71ms | 4926 | 320 | 15945.5 | 8310 | 0.00842288 | 8.98283 | 42.0197 | 7.9594 | 0.0090927 | 3.29882e-05 | 3.17194e-06 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1259.08 | 0.0479257 | 1363.61ms | 8150 | 4890 | 42801.2 | 6173.12 | 0.091108 | 4.04901 | 17.2817 | 3.35448 | 0.0040691 | 4.15522e-05 | 1.31983e-05 | 1(Win) | true |
| simdjson (ondemand) | 837.023 | 0.0779756 | 1675.69ms | 8150 | 1280 | 67107.1 | 9285.82 | 0.050632 | 6.0714 | 27.3418 | 5.11264 | 0.00728988 | 4.19862e-05 | 1.37078e-05 | 2(Loss) | true |

----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1423.66 | 0.0537022 | 1332.55ms | 8150 | 2560 | 22005.4 | 5459.49 | 0.0421606 | 3.57794 | 15.7079 | 3.0362 | 0.00385722 | 2.30061e-05 | 6.13497e-06 | 1(Win) | true |
| simdjson (ondemand) | 903.976 | 0.0669507 | 1630.49ms | 8150 | 80 | 2650.95 | 8598.06 | 0.00421624 | 5.51703 | 25.7569 | 4.79117 | 0.00636043 | 2.45399e-05 | 3.06748e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2504.56 | 0.0904243 | 921.031ms | 4926 | 160 | 460.274 | 1875.7 | 0.143075 | 2.06837 | 9.26898 | 1.69042 | 0.00127385 | 2.2838e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (ondemand) | 2164.65 | 0.0436142 | 953.886ms | 4926 | 2560 | 2293.57 | 2170.24 | 0.0272762 | 2.37803 | 9.53837 | 1.59318 | 0.00233304 | 2.26001e-05 | 7.92986e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2731.32 | 0.172202 | 918.302ms | 4926 | 40 | 350.897 | 1719.97 | 0.113729 | 1.89591 | 8.66565 | 1.55684 | 0.00156821 | 6.59765e-05 | 4.5676e-05 | 1(Win) | true |
| simdjson (ondemand) | 2326.56 | 0.0357585 | 949.029ms | 4926 | 320 | 166.829 | 2019.21 | 0.0046427 | 2.22054 | 8.94641 | 1.45818 | 0.00264096 | 1.90317e-05 | 9.51583e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3728.86 | 0.0647636 | 948.497ms | 8150 | 320 | 583.144 | 2084.4 | 0.0367446 | 1.38159 | 6.22037 | 1.05472 | 0.000852377 | 1.22699e-05 | 7.66871e-07 | 1(Win) | true |
| simdjson (ondemand) | 3360.78 | 0.0486041 | 965.905ms | 8150 | 160 | 202.163 | 2312.69 | 0.0511029 | 1.53165 | 6.3119 | 0.984294 | 0.00116181 | 9.20245e-06 | 3.83436e-06 | 2(Loss) | true |

----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3988.34 | 0.048467 | 946.063ms | 8150 | 4890 | 4362.47 | 1948.79 | 0.133922 | 1.29422 | 5.85448 | 0.974111 | 0.00116607 | 1.49548e-05 | 2.7852e-06 | 1(Win) | true |
| simdjson (ondemand) | 3608.63 | 0.0918157 | 962.414ms | 8150 | 80 | 312.863 | 2153.85 | 0.0859665 | 1.42834 | 5.95411 | 0.902699 | 0.00103834 | 1.68712e-05 | 7.66871e-06 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1917.49 | 0.12807 | 982.584ms | 4926 | 640 | 6300.86 | 2449.97 | 0.0121798 | 2.67751 | 11.9984 | 2.23244 | 0.00220038 | 1.01502e-05 | 1.58597e-06 | 1(Win) | true |
| simdjson (ondemand) | 1675.53 | 0.0711356 | 1017.97ms | 4926 | 4890 | 19452.2 | 2803.77 | 0.0590659 | 3.05078 | 13.2369 | 2.25619 | 0.00212067 | 3.48719e-05 | 1.5983e-05 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2049.86 | 0.114529 | 976.438ms | 4926 | 2560 | 17636.4 | 2291.76 | 0.00407353 | 2.51616 | 11.3649 | 2.09198 | 0.0032273 | 5.04339e-05 | 2.41068e-05 | 1(Win) | true |
| simdjson (ondemand) | 1825.29 | 0.123641 | 1008.7ms | 4926 | 30 | 303.789 | 2573.73 | 0.0336622 | 2.86826 | 12.611 | 2.11449 | 0.00236839 | 1.35336e-05 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2902.53 | 0.0832074 | 1005.1ms | 8150 | 640 | 3177.37 | 2677.82 | 0.0336207 | 1.76693 | 7.86147 | 1.39791 | 0.00140951 | 1.16948e-05 | 1.34202e-06 | 1(Win) | true |
| simdjson (ondemand) | 2626.85 | 0.0523032 | 1031.09ms | 8150 | 160 | 383.197 | 2958.85 | 0.0966502 | 1.95105 | 8.54933 | 1.38601 | 0.00146012 | 9.96933e-06 | 0 | 2(Loss) | true |

----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3069.21 | 0.0824305 | 1000.5ms | 8150 | 1280 | 5577.59 | 2532.39 | 0.00697169 | 1.67401 | 7.47853 | 1.31301 | 0.00198169 | 1.70629e-05 | 2.68405e-06 | 1(Win) | true |
| simdjson (ondemand) | 2794.73 | 0.0353588 | 1024.61ms | 8150 | 320 | 309.443 | 2781.11 | 0.015284 | 1.838 | 8.17104 | 1.30037 | 0.00160813 | 1.53374e-05 | 3.83436e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2159.6 | 0.0805583 | 863.433ms | 2821 | 320 | 322.277 | 1245.75 | 0.0524559 | 2.41668 | 8.89046 | 1.68167 | 0.000354484 | 3.65562e-05 | 1.8832e-05 | 1(Win) | true |
| simdjson (ondemand) | 1990.86 | 0.0396472 | 872.719ms | 2821 | 640 | 183.709 | 1351.33 | 0.0387499 | 2.61627 | 8.9145 | 1.51767 | 0.000365562 | 4.09872e-05 | 9.41599e-06 | 2(Loss) | true |

----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2375.54 | 0.121976 | 857.391ms | 2821 | 2560 | 4885.07 | 1132.51 | 0.0949779 | 2.19828 | 8.31691 | 1.53385 | 0.0003603 | 2.46477e-05 | 3.60023e-06 | 1(Win) | true |
| simdjson (ondemand) | 2139.98 | 0.117556 | 865.349ms | 2821 | 30 | 65.523 | 1257.17 | 0.0477036 | 2.4436 | 8.53066 | 1.419 | 0.000378117 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2761.11 | 0.0570374 | 868.97ms | 3770 | 4890 | 2697.39 | 1302.14 | 0.507585 | 1.88447 | 6.97454 | 1.2565 | 0.000267259 | 1.83886e-05 | 3.41736e-06 | 1(Win) | true |
| simdjson (ondemand) | 2536.09 | 0.0952237 | 882.094ms | 3770 | 80 | 145.792 | 1417.67 | 0.0158685 | 2.05063 | 7.03448 | 1.15066 | 0.000553714 | 3.64721e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 2992.76 | 0.0874839 | 866.882ms | 3770 | 160 | 176.732 | 1201.35 | 0.00624259 | 1.74841 | 6.58912 | 1.1557 | 0.00026691 | 1.49204e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2720.45 | 0.0682719 | 871.852ms | 3770 | 4890 | 3981.01 | 1321.6 | 0.153946 | 1.9156 | 6.74775 | 1.07692 | 0.00028402 | 5.64135e-05 | 3.30345e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 799.551 | 0.0553764 | 1075.82ms | 2821 | 4890 | 16977.4 | 3364.78 | 0.0427371 | 6.40461 | 26.1762 | 4.5016 | 0.00132652 | 7.66237e-05 | 2.55171e-05 | 1(Win) | true |
| simdjson (ondemand) | 412.111 | 0.0582665 | 1393.65ms | 2821 | 40 | 578.728 | 6528.12 | 0.0190166 | 12.3455 | 57.8018 | 11.1928 | 0.00167494 | 9.74832e-05 | 6.20347e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 827.506 | 0.0594622 | 1068.2ms | 2821 | 1280 | 4783.62 | 3251.11 | 0.0923131 | 6.18056 | 25.6597 | 4.36654 | 0.00158272 | 6.50811e-05 | 1.8832e-05 | 1(Win) | true |
| simdjson (ondemand) | 414.383 | 0.0440905 | 1396.06ms | 2821 | 2560 | 20976.5 | 6492.34 | 0.0667709 | 12.2935 | 57.4184 | 11.0947 | 0.00209907 | 0.000157718 | 0.000109115 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 965.532 | 0.0535273 | 1113.97ms | 3770 | 4890 | 19427.1 | 3723.7 | 0.303325 | 5.27725 | 20.2324 | 3.50584 | 0.00121728 | 0.000174122 | 0.00011299 | 1(Win) | true |
| simdjson (ondemand) | 555.581 | 0.059009 | 1386.87ms | 3770 | 80 | 1166.58 | 6471.34 | 0.209242 | 9.15797 | 42.9897 | 8.25889 | 0.00153846 | 5.96817e-05 | 3.64721e-05 | 2(Loss) | true |

----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1003.93 | 0.0764433 | 1107.8ms | 3770 | 1280 | 9593.26 | 3581.28 | 0.0512256 | 5.08767 | 19.8464 | 3.40478 | 0.00136543 | 0.000133869 | 7.14937e-05 | 1(Win) | true |
| simdjson (ondemand) | 563.043 | 0.0804163 | 1383.03ms | 3770 | 640 | 16875.9 | 6385.57 | 0.00929745 | 9.02315 | 42.7027 | 8.18541 | 0.000931698 | 9.32527e-05 | 6.1754e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5842.63 | 0.0896086 | 777.802ms | 2821 | 4890 | 832.526 | 460.463 | 0.146099 | 0.939317 | 3.69479 | 0.530663 | 0.000354919 | 4.19727e-05 | 1.55132e-05 | 1(Win) | true |
| simdjson (ondemand) | 5695.73 | 0.160276 | 777.761ms | 2821 | 640 | 366.797 | 472.339 | 0.253704 | 0.981777 | 3.93655 | 0.391351 | 0.000357808 | 6.70197e-05 | 4.48644e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5932.89 | 0.0745652 | 780.955ms | 2821 | 640 | 73.1688 | 453.458 | 0.0561341 | 0.925619 | 3.62035 | 0.512584 | 0.000354484 | 2.21553e-05 | 5.53882e-06 | 1(Win) | true |
| simdjson (ondemand) | 5774.37 | 0.0387575 | 777.973ms | 2821 | 2560 | 83.4735 | 465.907 | 0.0400086 | 0.951088 | 3.86175 | 0.372917 | 0.000354623 | 2.20168e-05 | 6.92352e-06 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 6833.2 | 0.114015 | 784.638ms | 3770 | 320 | 115.163 | 526.159 | 0.353321 | 0.795037 | 3.13873 | 0.41008 | 0.000265252 | 2.48674e-05 | 1.24337e-05 | 1(Win) | true |
| simdjson (ondemand) | 6461.73 | 0.162705 | 789.128ms | 3770 | 2560 | 2098.09 | 556.407 | 0.168213 | 0.834722 | 3.30902 | 0.308488 | 0.000266703 | 3.04625e-05 | 1.47132e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 7030 | 0.08968 | 785.798ms | 3770 | 640 | 134.63 | 511.43 | 0.218576 | 0.778185 | 3.08223 | 0.396552 | 0.000265252 | 1.53349e-05 | 6.6313e-06 | 1(Win) | true |
| simdjson (ondemand) | 6672.89 | 0.354433 | 785.044ms | 3770 | 30 | 109.407 | 538.8 | 0.260514 | 0.81626 | 3.25305 | 0.294695 | 0.000265252 | 1.76835e-05 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4365.1 | 0.0959116 | 794.141ms | 2821 | 4890 | 1708.72 | 616.324 | 0.159317 | 1.23405 | 5.04218 | 0.785892 | 0.000393122 | 3.53759e-05 | 1.47883e-05 | 1(Win) | true |
| simdjson (ondemand) | 3872.98 | 0.155681 | 804.094ms | 2821 | 640 | 748.46 | 694.638 | 0.00629865 | 1.37948 | 5.77207 | 0.718894 | 0.00051234 | 3.32329e-05 | 2.27091e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4444.76 | 0.107976 | 795.892ms | 2821 | 4890 | 2088.7 | 605.279 | 0.0182585 | 1.2217 | 4.96597 | 0.767813 | 0.000381524 | 7.4159e-05 | 5.39338e-05 | 1(Win) | true |
| simdjson (ondemand) | 3974.46 | 0.0965103 | 802.326ms | 2821 | 80 | 34.1418 | 676.9 | 0.0774994 | 1.34758 | 5.69692 | 0.700461 | 0.000496278 | 0 | 0 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5150.11 | 0.0813252 | 800.88ms | 3770 | 2560 | 825.164 | 698.112 | 0.0567616 | 1.03846 | 4.17294 | 0.608753 | 0.000420673 | 3.9477e-05 | 1.98939e-05 | 1(Win) | true |
| simdjson (ondemand) | 4563.86 | 0.0799203 | 811.788ms | 3770 | 2560 | 1014.78 | 787.787 | 0.00743832 | 1.15265 | 4.69284 | 0.555703 | 0.00058314 | 3.28457e-05 | 1.94794e-05 | 2(Loss) | true |

----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5301.12 | 0.231298 | 804.633ms | 3770 | 40 | 98.4353 | 678.225 | 0.0430229 | 1.00818 | 4.11592 | 0.595225 | 0.000265252 | 1.98939e-05 | 1.32626e-05 | 1(Win) | true |
| simdjson (ondemand) | 4760.42 | 0.067369 | 810.604ms | 3770 | 640 | 165.688 | 755.259 | 0.149146 | 1.11816 | 4.6366 | 0.54191 | 0.00059433 | 7.87467e-06 | 2.48674e-06 | 2(Loss) | true |

----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 5077.57 | 0.0385988 | 5978.08ms | 277673 | 2560 | 1.03739e+06 | 52152.8 | 0.140366 | 0.996249 | 3.87685 | 0.683904 | 0.00480353 | 4.814e-06 | 3.47756e-06 | 1(Win) | true |
| simdjson (ondemand) | 4379.43 | 0.0283797 | 6838.53ms | 277673 | 1280 | 376927 | 60466.7 | 0.0509928 | 1.15453 | 4.58727 | 0.783367 | 0.00499473 | 6.61468e-06 | 4.97438e-06 | 2(Loss) | true |

----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 3928.36 | 0.0783495 | 7986.78ms | 10548466 | 160 | 6.44092e+08 | 2.56081e+06 | 0.0846058 | 1.2828 | 3.87769 | 0.68476 | 0.0147582 | 0.0170264 | 9.20436e-05 | 1(Win) | true |
| simdjson (ondemand) | 3877.91 | 0.210493 | 8122.18ms | 10548466 | 30 | 8.94499e+08 | 2.59413e+06 | 0.0516888 | 1.30602 | 4.5883 | 0.784883 | 0.0096293 | 0.0171295 | 0.000935564 | 2(Loss) | true |

----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 4181.2 | 0.120691 | 5495.28ms | 16002592 | 80 | 1.55246e+09 | 3.64997e+06 | 0.311122 | 1.20429 | 6.77384 | 0.857805 | 0.00056519 | 0.0361076 | 0.00239073 | 1(Win) | true |
| jsonifier (generic) | 4122.54 | 0.364461 | 5544.82ms | 16002592 | 40 | 7.2814e+09 | 3.70191e+06 | 0.345515 | 1.22408 | 6.87792 | 1.07711 | 0.000437015 | 0.0334303 | 0.00587477 | 2(Loss) | true |

----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 4070.68 | 0.0741048 | 5633.25ms | 16002591 | 80 | 6.1749e+08 | 3.74907e+06 | 0.192517 | 1.23551 | 6.92896 | 1.16079 | 0.000443074 | 0.0355465 | 0.00379416 | 1(Win) | true |
| simdjson (ondemand) | 1998.06 | 0.104656 | 5355.09ms | 16002591 | 40 | 2.55595e+09 | 7.63805e+06 | 0.71951 | 2.52646 | 11.751 | 2.39983 | 0.000592014 | 0.0525076 | 0.00795748 | 2(Loss) | true |

----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 22076.2 | 0.131884 | 4473.6ms | 16197086 | 80 | 6.81243e+07 | 699702 | 0.0286272 | 0.228003 | 1.12436 | 0.0659773 | 7.27639e-05 | 0.015724 | 0.000192664 | 1(Win) | true |
| simdjson (ondemand) | 18159 | 0.176621 | 5420.03ms | 16197086 | 320 | 7.22309e+08 | 850638 | 0.223311 | 0.276596 | 1.31715 | 0.0683657 | 7.57405e-05 | 0.0157258 | 0.000216613 | 2(Loss) | true |

----
### Stream Formats Large Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 21860.5 | 0.0955114 | 4498.29ms | 16197085 | 320 | 1.45752e+08 | 706605 | 0.0410254 | 0.229859 | 1.12504 | 0.0673222 | 7.28084e-05 | 0.015731 | 0.000213402 | 1(Win) | true |
| simdjson (ondemand) | 16978 | 0.112181 | 5851.79ms | 16197085 | 320 | 3.33343e+08 | 909809 | 0.0970265 | 0.295165 | 1.39967 | 0.0940532 | 8.67021e-05 | 0.0157739 | 9.56403e-05 | 2(Loss) | true |

----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1712 | 0.105258 | 4444.77ms | 4212000 | 30 | 1.8298e+08 | 2.34631e+06 | 0.384598 | 2.94934 | 11.5022 | 2.12663 | 0.0229782 | 0.0671856 | 0.00129735 | 1(Win) | true |
| simdjson (ondemand) | 1549.58 | 0.194036 | 4787.94ms | 4212000 | 30 | 7.58989e+08 | 2.59223e+06 | 0.140202 | 3.2611 | 12.5487 | 2.42736 | 0.0121496 | 0.0660602 | 0.000514403 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1326.93 | 0.107702 | 5442.76ms | 4212000 | 80 | 8.50395e+08 | 3.02719e+06 | 0.048559 | 3.79808 | 15.209 | 2.98888 | 0.0271045 | 0.0667858 | 0.00452712 | 1(Win) | true |
| simdjson (ondemand) | 1279.79 | 0.116414 | 5608.12ms | 4212000 | 40 | 5.34034e+08 | 3.1387e+06 | 0.152976 | 3.91529 | 15.9224 | 3.05958 | 0.017317 | 0.0661459 | 0.000142165 | 2(Loss) | true |

----
### Apache Builds Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1532.85 | 0.119675 | 4846.19ms | 4211999 | 40 | 3.93411e+08 | 2.62053e+06 | 0.114067 | 3.28738 | 12.3411 | 2.29956 | 0.0295265 | 0.068432 | 0.00181451 | 1(Win) | true |
| simdjson (ondemand) | 1270.87 | 0.427917 | 5595.76ms | 4211999 | 80 | 1.46347e+10 | 3.16073e+06 | 0.54692 | 3.96707 | 15.0221 | 3.19469 | 0.0125618 | 0.0681303 | 0.00386849 | 2(Loss) | true |

----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1294.3 | 0.20807 | 5524.57ms | 4211999 | 40 | 1.66796e+09 | 3.10351e+06 | 0.373883 | 3.89157 | 15.3657 | 3.031 | 0.0266483 | 0.0692151 | 0.00347282 | 1(Win) | true |
| simdjson (ondemand) | 1105.42 | 0.0818553 | 6375.8ms | 4211999 | 40 | 3.53899e+08 | 3.63381e+06 | 0.268603 | 4.56672 | 18.396 | 3.82696 | 0.0175125 | 0.067666 | 0.00338089 | 2(Loss) | true |

----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1531.99 | 0.183724 | 4529.47ms | 4525120 | 80 | 2.14274e+09 | 2.81692e+06 | 0.127754 | 3.29249 | 15.6581 | 2.98931 | 0.0127363 | 0.0774377 | 3.17229e-05 | 1(Win) | true |
| simdjson (ondemand) | 1392.77 | 0.239076 | 4995.52ms | 4525120 | 40 | 2.19498e+09 | 3.09848e+06 | 0.32999 | 3.62528 | 15.7445 | 2.58874 | 0.0126838 | 0.0770484 | 4.4032e-05 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 776.392 | 0.121958 | 4049.63ms | 4525120 | 30 | 1.37861e+09 | 5.55839e+06 | 0.00909879 | 6.49434 | 30.0297 | 5.64419 | 0.022163 | 0.0784498 | 0.000327704 | 1(Win) | true |
| simdjson (ondemand) | 578.074 | 0.149525 | 5368.71ms | 4525120 | 40 | 4.98405e+09 | 7.46529e+06 | 0.100639 | 8.71013 | 37.7869 | 6.37691 | 0.0355476 | 0.077874 | 0.000181393 | 2(Loss) | true |

----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1364.27 | 0.154189 | 5059ms | 4525119 | 80 | 1.90307e+09 | 3.16322e+06 | 0.152681 | 3.68368 | 17.4344 | 3.30371 | 0.0139009 | 0.0780328 | 3.84134e-05 | 1(Win) | true |
| simdjson (ondemand) | 1014.54 | 0.111056 | 6709.31ms | 4525119 | 40 | 8.92631e+08 | 4.25366e+06 | 0.136182 | 4.9635 | 20.9566 | 4.13346 | 0.0155293 | 0.0921563 | 0.00613736 | 2(Loss) | true |

----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 792.777 | 0.0773475 | 4002.69ms | 4525119 | 30 | 5.31829e+08 | 5.44351e+06 | 0.179966 | 6.36068 | 29.664 | 5.61124 | 0.0184621 | 0.0787453 | 0.00225622 | 1(Win) | true |
| simdjson (ondemand) | 503.516 | 0.0936702 | 6217.77ms | 4525119 | 40 | 2.57808e+09 | 8.57072e+06 | 0.25605 | 10.0546 | 42.9987 | 7.92158 | 0.0386902 | 0.0932008 | 0.000981002 | 2(Loss) | true |

----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1248.97 | 0.0398758 | 5106.69ms | 4203059 | 80 | 1.31019e+08 | 3.20932e+06 | 0.109967 | 4.04223 | 17.5375 | 3.30979 | 0.0222262 | 0.0891034 | 0.00101446 | 1(Win) | true |
| simdjson (ondemand) | 979.323 | 0.116721 | 6441.1ms | 4203059 | 40 | 9.12931e+08 | 4.09298e+06 | 0.332105 | 5.15506 | 18.6365 | 3.51292 | 0.0265379 | 0.0892893 | 0.000168913 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 757.881 | 0.10683 | 8195.35ms | 4203059 | 30 | 9.5771e+08 | 5.28889e+06 | 0.396559 | 6.62813 | 27.9221 | 5.48002 | 0.0355321 | 0.0894806 | 0.00117878 | 1(Win) | true |
| simdjson (ondemand) | 705.58 | 0.0560935 | 4088.37ms | 4203059 | 40 | 4.06184e+08 | 5.68093e+06 | 0.203962 | 7.14736 | 26.4017 | 4.94228 | 0.0406698 | 0.0880202 | 0.000605345 | 2(Loss) | true |

----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1124.75 | 0.115034 | 5657.42ms | 4203058 | 40 | 6.72249e+08 | 3.56378e+06 | 0.0223687 | 4.48745 | 19.2428 | 3.61567 | 0.0245874 | 0.0894014 | 0.000347556 | 1(Win) | true |
| simdjson (ondemand) | 772.115 | 0.12346 | 8046ms | 4203058 | 30 | 1.23237e+09 | 5.19139e+06 | 0.195378 | 6.52617 | 23.7466 | 5.07763 | 0.0282454 | 0.104888 | 0.00856829 | 2(Loss) | true |

----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 758.156 | 0.0703128 | 8282.1ms | 4203058 | 30 | 4.14575e+08 | 5.28697e+06 | 0.308215 | 6.6659 | 29.6635 | 5.80217 | 0.0280046 | 0.0884434 | 0.00257823 | 1(Win) | true |
| simdjson (ondemand) | 594.186 | 0.146286 | 4862.92ms | 4203058 | 30 | 2.92155e+09 | 6.74595e+06 | 0.097249 | 8.52576 | 31.5101 | 6.50644 | 0.0423159 | 0.103441 | 0.0179809 | 2(Loss) | true |

----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1756.75 | 0.0896419 | 7351.1ms | 4197496 | 80 | 3.3379e+08 | 2.27866e+06 | 0.111647 | 2.84965 | 14.459 | 2.98772 | 0.000519131 | 0.0817666 | 6.00001e-05 | 1(Win) | true |
| simdjson (ondemand) | 1484.4 | 0.0414919 | 4202.76ms | 4197496 | 30 | 3.756e+07 | 2.69674e+06 | 0.259913 | 3.39981 | 15.6102 | 2.64247 | 0.00392313 | 0.0809906 | 2.77943e-05 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 996.184 | 0.129537 | 6182.02ms | 4197496 | 30 | 8.12847e+08 | 4.01838e+06 | 0.350004 | 5.0558 | 27.2842 | 5.63017 | 0.000735168 | 0.0823864 | 0.000138884 | 1(Win) | true |
| simdjson (ondemand) | 793.107 | 0.0376446 | 7731.73ms | 4197496 | 40 | 1.44405e+08 | 5.04729e+06 | 0.00619182 | 6.36409 | 29.3747 | 5.44501 | 0.0193161 | 0.0813202 | 0.000415057 | 2(Loss) | true |

----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1669.45 | 0.119052 | 7732.38ms | 4197495 | 40 | 3.25962e+08 | 2.39783e+06 | 0.0274327 | 2.99917 | 16.4768 | 3.36303 | 0.000485641 | 0.0841415 | 9.46457e-05 | 1(Win) | true |
| simdjson (ondemand) | 1014.7 | 0.0812572 | 6144.75ms | 4197495 | 30 | 3.08285e+08 | 3.94506e+06 | 0.250732 | 4.95575 | 21.302 | 4.41991 | 0.00454149 | 0.102309 | 0.000520072 | 2(Loss) | true |

----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 983.131 | 0.0689884 | 6284.59ms | 4197495 | 40 | 3.15624e+08 | 4.07173e+06 | 0.319727 | 5.12504 | 27.3453 | 5.68164 | 0.000753485 | 0.0844373 | 0.000114402 | 1(Win) | true |
| simdjson (ondemand) | 625.135 | 0.161013 | 4581.7ms | 4197495 | 40 | 4.25221e+09 | 6.40349e+06 | 0.325429 | 8.03562 | 35.0663 | 7.22239 | 0.0231839 | 0.103171 | 0.00316154 | 2(Loss) | true |

----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1420.37 | 0.150229 | 5293.88ms | 4506447 | 40 | 8.26485e+08 | 3.02576e+06 | 0.00647483 | 3.55342 | 15.4498 | 2.94805 | 0.0159111 | 0.0806108 | 0.00682804 | 1(Win) | true |
| simdjson (ondemand) | 1129.03 | 0.0828647 | 6472.94ms | 4506447 | 80 | 7.95955e+08 | 3.80654e+06 | 0.508138 | 4.47073 | 16.8348 | 3.1875 | 0.0131718 | 0.0791224 | 0.000966687 | 2(Loss) | true |

----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 852.516 | 0.172264 | 8310.41ms | 4506447 | 80 | 6.03315e+09 | 5.04118e+06 | 0.4191 | 5.90996 | 26.2628 | 5.21572 | 0.0209261 | 0.0810461 | 0.00973786 | 1(Win) | true |
| simdjson (ondemand) | 556.178 | 0.0671762 | 5789.05ms | 4506447 | 40 | 1.07779e+09 | 7.72718e+06 | 0.385274 | 9.06088 | 39.9988 | 7.6832 | 0.0277988 | 0.0791201 | 0.00319705 | 2(Loss) | true |

----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1346.09 | 0.116803 | 5527.11ms | 4506446 | 80 | 1.11255e+09 | 3.19271e+06 | 0.0200213 | 3.75527 | 16.8044 | 3.19589 | 0.0159129 | 0.0812851 | 0.000741934 | 1(Win) | true |
| simdjson (ondemand) | 908.076 | 0.0799581 | 7863.49ms | 4506446 | 30 | 4.29605e+08 | 4.73273e+06 | 0.131092 | 5.56825 | 20.8982 | 4.44755 | 0.013457 | 0.0872082 | 0.00106964 | 2(Loss) | true |

----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 872.471 | 0.0532635 | 8164.45ms | 4506446 | 80 | 5.50701e+08 | 4.92587e+06 | 0.050751 | 5.78884 | 26.0494 | 5.20965 | 0.0157141 | 0.0816805 | 0.000373135 | 1(Win) | true |
| simdjson (ondemand) | 498.925 | 0.0932139 | 6390.24ms | 4506446 | 30 | 1.93411e+09 | 8.61388e+06 | 0.0835757 | 10.1443 | 44.0617 | 8.94306 | 0.0277655 | 0.0868447 | 0.0162019 | 2(Loss) | true |

----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1870.6 | 0.154139 | 7521.95ms | 4219120 | 160 | 1.75882e+09 | 2.151e+06 | 0.102327 | 2.68634 | 8.97173 | 1.64354 | 0.0220643 | 0.0575053 | 0.000533575 | 1(Win) | true |
| simdjson (ondemand) | 1810.41 | 0.104525 | 7775.44ms | 4219120 | 80 | 4.3174e+08 | 2.22251e+06 | 0.141305 | 2.78134 | 8.9529 | 1.51769 | 0.0153732 | 0.0541099 | 0.000317726 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 636.568 | 0.149073 | 4663.15ms | 4219120 | 40 | 3.5515e+09 | 6.32088e+06 | 0.412281 | 7.91756 | 26.8699 | 4.63776 | 0.0389687 | 0.0583 | 0.00239447 | 1(Win) | true |
| simdjson (ondemand) | 267.988 | 0.133258 | 4605.25ms | 4219120 | 30 | 1.20094e+10 | 1.50143e+07 | 0.563543 | 18.708 | 60.383 | 11.6686 | 0.162773 | 0.0554945 | 0.00900422 | 2(Loss) | true |

----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 1727.74 | 0.143613 | 8096.82ms | 4219119 | 40 | 4.47442e+08 | 2.32886e+06 | 0.241043 | 2.90461 | 9.78884 | 1.78962 | 0.0226379 | 0.0564746 | 0.00136912 | 1(Win) | true |
| simdjson (ondemand) | 1425.65 | 0.224931 | 4653.39ms | 4219119 | 30 | 1.20903e+09 | 2.82234e+06 | 0.228447 | 3.52055 | 11.3945 | 2.27643 | 0.0181515 | 0.0541887 | 0.000560496 | 2(Loss) | true |

----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="400"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| jsonifier (generic) | 656.049 | 0.130284 | 4502.6ms | 4219119 | 40 | 2.55397e+09 | 6.13318e+06 | 0.249377 | 7.68706 | 26.7067 | 4.62317 | 0.0322103 | 0.0583013 | 0.000643736 | 1(Win) | true |
| simdjson (ondemand) | 259.522 | 0.110042 | 4762.79ms | 4219119 | 30 | 8.73233e+09 | 1.55041e+07 | 0.400942 | 19.3989 | 62.825 | 12.4274 | 0.163922 | 0.0554071 | 0.00993497 | 2(Loss) | true |
